#ifndef BX_DLMALLOC_H
#define BX_DLMALLOC_H

#include "common.h"

// The game heap is Doug Lea's malloc 2.7 (dlmalloc), built without mmap and
// with every entry point taking the heap it works on. cMemMan sends
// allocations over 0x200 bytes here (see bx/memblockman.cpp).

struct sMallocChunk {
    unsigned int prev_size;             // 0x0 size of the previous chunk, if it is free
    unsigned int size;                  // 0x4 size in bytes; bit 0 PREV_INUSE, bit 1 IS_MMAPPED
    sMallocChunk* fd;                   // 0x8 free chunks only: next in bin
    sMallocChunk* bk;                   // 0xC free chunks only: previous in bin
};

struct sMallocState {
    unsigned int max_fast;              // 0x000 low 2 bits are flags (FASTCHUNKS_BIT, ...)
    sMallocChunk* fastbins[11];         // 0x004
    sMallocChunk* top;                  // 0x030
    sMallocChunk* last_remainder;       // 0x034
    sMallocChunk* bins[192];            // 0x038 96 bins as fd/bk pairs
    unsigned int binmap[3];             // 0x338
    unsigned int trim_threshold;        // 0x344
    unsigned int top_pad;               // 0x348
    unsigned int mmap_threshold;        // 0x34C
    int n_mmaps;                        // 0x350
    int n_mmaps_max;                    // 0x354
    int max_n_mmaps;                    // 0x358
    unsigned int pagesize;              // 0x35C
    unsigned int morecore_properties;   // 0x360
    unsigned int mmapped_mem;           // 0x364
    unsigned int sbrked_mem;            // 0x368
    unsigned int max_sbrked_mem;        // 0x36C
    unsigned int max_mmapped_mem;       // 0x370
    unsigned int max_total_mem;         // 0x374
};

struct sMallinfo {
    int arena;
    int ordblks;
    int smblks;
    int hblks;
    int hblkhd;
    int usmblks;
    int fsmblks;
    int uordblks;
    int fordblks;
    int keepcost;
};

// One heap: a malloc_state at the start of its memory, then the region
// cMemHeap_sbrk hands out as MORECORE.
struct sMemHeap {
    sMallocState* av;                   // 0x0
    char* base;                         // 0x4 first byte after the state (state + 0x380)
    char* brk;                          // 0x8 current break
    unsigned int size;                  // 0xC bytes from base to the end of the region
};

#endif /* BX_DLMALLOC_H */
