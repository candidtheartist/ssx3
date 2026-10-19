#ifndef MEM_MEMSTD_H
#define MEM_MEMSTD_H

#include "common.h"

// EA's block allocator (MEM_ / MEMCLASS_). Memory is split into up to 64
// classes (heaps), each a run of blocks with a 0x10-byte header:
//
//   [LOW sentinel] [block] [block] ... [HIGH sentinel]
//
// Blocks are chained in address order through next/prev. Free blocks are
// also on the class's free list (freenext/freeprev, in the first 8 bytes of
// the payload), which is kept in address order and runs through the class's
// freehead sentinel. The payload of a block starts at header + 0x10, and the
// public API passes payload pointers.

// Block tags: two ASCII letters stored as a halfword.
#define MEM_TAG_USED 0x424D     // 'BM' block written by MEM_initblock
#define MEM_TAG_FREE 0x4246     // 'BF' on its class's free list
#define MEM_TAG_STOP 0x4253     // 'BS' sentinel: free-list head, LOW/HIGH ends
#define MEM_TAG_OUT  0x424F     // 'BO' just taken off the free list

// Block flags.
#define MEM_FLAG_SYSTEM  0x8000 // class bookkeeping block (LOW/HIGH/LINK); never CRC'd
#define MEM_FLAG_FREE    0x4000 // on the free list
#define MEM_FLAG_GUARD   0x2000 // 'BEND' word follows the payload
#define MEM_FLAG_TRAILER 0x0800 // a pointer-sized word follows the payload
#define MEM_FLAG_HIGH    0x0100 // set on a class's HIGH sentinel

#define MEM_GUARD_WORD 0x42454E44 // 'BEND', stored big-endian

#define MEM_MAX_CLASSES 0x40

struct sMemBlock {
    unsigned short tag;     // 0x00 MEM_TAG_*
    unsigned short flags;   // 0x02 MEM_FLAG_*, plus the class id in the low bits
    int size;               // 0x04 used: payload bytes; free: bytes to the next header
    sMemBlock* next;        // 0x08 next block in memory
    sMemBlock* prev;        // 0x0C previous block in memory
    // Free blocks only (overlays the payload):
    sMemBlock* freenext;    // 0x10
    sMemBlock* freeprev;    // 0x14
};

struct sMemClass {
    char name[8];           // 0x00
    sMemBlock* first;       // 0x08 LOW sentinel (lowest block)
    sMemBlock* last;        // 0x0C HIGH sentinel (highest block)
    sMemBlock freehead;     // 0x10 free-list sentinel ('BS', size 0x7FFFFFFF)
    int defaultalign;       // 0x28 alignment used when an allocation passes none
    int align;              // 0x2C block-start alignment of the class's arenas
    int hdr;                // 0x30 extra header bytes per block
    int flags;              // 0x34 flags every block of the class carries
    int locked;             // 0x38 1 when the class has a mutex
    int mutex[4];           // 0x3C MUTEX_lock/MUTEX_unlock state
    int pad4C;              // 0x4C
};

extern void* D_004D2438[]; // sMemClass* per class id (MEM_MAX_CLASSES)

// PORT: debugmenu defines MEM_initblock with a short flags parameter; memstd passes the int unconverted.
extern "C" void* MEM_initblock(void* self, const char* name, int size, int hdr, int flags, void* prev, void* next);

extern "C" int MEMCLASS_create(int id, char* name, char* mem, int size, int defaultalign, int align, int hdr, int guard, int a8, int lock);
extern "C" int MEMCLASS_destroy(int id);
extern "C" void* MEMCLASS_freeall(int id);
extern "C" int MEMCLASS_findunused();
extern "C" int MEMCLASS_link(int id, char* mem, int size);
extern "C" int MEMCLASS_hdrsize(void* unused, int id);
extern "C" sMemBlock* MEMCLASS_firstfit(sMemClass* cls, int size, int backward);
extern "C" sMemBlock* MEMCLASS_largestfree(sMemClass* cls, int size, int backward);
extern "C" int MEMCLASS_totalfree(sMemClass* cls, int backward);
extern "C" void MEMCLASS_linkfree(sMemClass* cls, sMemBlock* blk);

extern "C" int MEM_initram(char* mem, int size);
extern "C" void* MEM_findnamed(const char* name);
extern "C" void MEM_printf(const char* fmt, ...);
extern "C" int MEM_validheader(void* p);
extern "C" int MEM_checkblock(sMemBlock* blk);
extern "C" void* MEM_free(void* p);
extern "C" int MEM_getsize(void* p);
extern "C" unsigned short MEM_getflags(void* p);
int MEM_getname(void* p);
extern "C" int MEM_gettrailer(void* p);
extern "C" int MEM_settrailer(void* p, int value);
extern "C" void* MEM_resize(void* p, int size);
extern "C" void MEM_unlinkfree(sMemBlock* blk);

#endif /* MEM_MEMSTD_H */
