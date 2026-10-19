#include "common.h"
#include "mem/memstd.h"

//100%
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void* func_003E6448(void* dst, int value, int size);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int MUTEX_init(void* mutex);
extern char D_004A2E38[]; // "%s LOW"
extern char D_004A2E40[]; // "%s HIGH"

// Set up class id over [mem, mem+size): the class record and its LOW sentinel
// at the bottom, one free block, and the HIGH sentinel at the top. Returns the
// free block's size.
extern "C" int MEMCLASS_create(int id, char* name, char* mem, int size, int defaultalign, int align, int hdr, int guard, int a8, int lock)
{
    char buf[0x100];
    int flags = id;
    if (guard) {
        flags |= MEM_FLAG_GUARD;
    }
    if (a8) {
        flags |= 0x1000;
    }
    char* data = mem;
    data += hdr + 0x60;
    data += align + 0x2F;
    data = (char*)((int)data & -align);
    char* end = mem + size;
    end -= hdr + 0x30;
    sprintf(buf, D_004A2E38, name);
    sMemBlock* blk = (sMemBlock*)(data - 0x10);
    sMemClass* cls = (sMemClass*)(mem + 0x10);
    MEM_initblock(mem, buf, 0x50, hdr, flags | MEM_FLAG_SYSTEM, 0, blk);
    MEM_initblock(blk, 0, end - (char*)blk - 0x10, hdr, flags, mem, end);
    sprintf(buf, D_004A2E40, name);
    MEM_initblock(end, buf, 0, hdr, flags | MEM_FLAG_SYSTEM | MEM_FLAG_HIGH, blk, 0);
    D_004D2438[id & 0x3F] = cls;
    func_003E6448(cls, 0, sizeof(sMemClass));
    strcpy(cls->name, name);
    // The fields are written through mem (mem + 0x10 + field offset): with
    // cls-> stores gcc reuses mem for cls->first->tag instead of reloading it.
    *(char**)(mem + 0x1C) = end;                        // cls->last
    *(char**)(mem + 0x18) = mem;                        // cls->first
    cls->first->tag = MEM_TAG_STOP;
    cls->last->tag = MEM_TAG_STOP;
    *(unsigned short*)(mem + 0x20) = MEM_TAG_STOP;      // cls->freehead.tag
    *(int*)(mem + 0x24) = 0x7FFFFFFF;                   // cls->freehead.size
    *(int*)(mem + 0x38) = defaultalign;                 // cls->defaultalign
    *(int*)(mem + 0x3C) = align;                        // cls->align
    *(int*)(mem + 0x40) = hdr;                          // cls->hdr
    *(int*)(mem + 0x44) = flags;                        // cls->flags
    sMemBlock* h = (sMemBlock*)(mem + 0x20);            // &cls->freehead
    *(sMemBlock**)(mem + 0x30) = h;                     // cls->freehead.freenext
    *(sMemBlock**)(mem + 0x34) = h;                     // cls->freehead.freeprev
    *(int*)(mem + 0x48) = 0;                            // cls->locked
    // Same as MEMCLASS_linkfree, inlined.
    sMemBlock* q = h;
    sMemBlock* p = q;
    int sz = *(char**)(data - 8) - (char*)blk;         // blk->next - blk
    if (*(char**)(mem + 0x30) + (*(char**)(mem + 0x34) - *(char**)(mem + 0x30)) / 2 < (char*)blk) {
        do
            p = p->freeprev;
        while (blk < p);
        q = p->freenext;
    } else {
        do
            q = q->freenext;
        while (q < blk);
        p = q->freeprev;
    }
    blk->size = sz;
    blk->freenext = q;
    blk->freeprev = p;
    p->freenext = blk;
    q->freeprev = blk;
    blk->tag = MEM_TAG_FREE;
    blk->flags |= MEM_FLAG_FREE;
    if (lock) {
        MUTEX_init(cls->mutex);
        cls->locked = 1;
    }
    return blk->size;
}

extern "C" void MUTEX_destroy(void* mutex);

// Destroy class id: release its mutex, clear it and free the slot.
extern "C" int MEMCLASS_destroy(int id)
{
    void** slot = &D_004D2438[id & 0x3F];
    sMemClass* cls = (sMemClass*)*slot;
    int r = 0;
    if (cls != 0) {
        if (cls->locked) {
            MUTEX_destroy(cls->mutex);
        }
        func_003E6448(cls, 0, sizeof(sMemClass));
        *slot = 0;
        r = 1;
    }
    return r;
}

//100%
// MEM_free every in-use block of class id; stops at the first failure.
extern "C" void* MEMCLASS_freeall(int id)
{
    sMemClass* cls = (sMemClass*)D_004D2438[id & 0x3F];
    void* ok = (void*)1;
    for (sMemBlock* blk = cls->first; blk != 0 && ok != 0; blk = blk->next) {
        if ((blk->flags & (MEM_FLAG_SYSTEM | MEM_FLAG_FREE)) == 0) {
            ok = MEM_free((char*)blk + 0x10);
        }
    }
    return ok;
}

// First unused class id (ids 0 and 1 are reserved), or MEM_MAX_CLASSES if full.
extern "C" int MEMCLASS_findunused()
{
    int i;
    for (i = 2; i < MEM_MAX_CLASSES; i++) {
        if (D_004D2438[i] == 0) {
            break;
        }
    }
    return i;
}

INCLUDE_ASM("mem/memstd", func_00251AC0);

INCLUDE_ASM("mem/memstd", func_00251B50);

INCLUDE_ASM("mem/memstd", func_00251BB0);

//100%
extern "C" int func_0041AA88(const char* a, const char* b);

// Find the allocation named name in any class; returns its payload pointer.
extern "C" void* MEM_findnamed(const char* name)
{
    for (int i = 0; i < MEM_MAX_CLASSES; i++) {
        sMemClass* cls = (sMemClass*)D_004D2438[i & 0x3F];
        if (cls != 0) {
            sMemBlock* blk = cls->first;
            do {
                char* data = (char*)blk + 0x10;
                const char* n = (const char*)MEM_getname(data);
                if (n != 0 && func_0041AA88(n, name) == 0) {
                    return data;
                }
                blk = blk->next;
            } while (blk != 0);
        }
    }
    return 0;
}

extern "C" int func_00251CF0()
{
    return 0;
}

extern "C" int func_00251CF8()
{
    return 0;
}

extern "C" void func_00251D00()
{
}

extern char D_004A2E48[]; // "RAM"

// Create class 0 ("RAM") over [mem, mem+size).
extern "C" int MEM_initram(char* mem, int size)
{
    return MEMCLASS_create(0, D_004A2E48, mem, size, 0x40, 0x80, 0, 0, 0, 1);
}

//100%
extern char D_004A2E50[]; // "%s LINK"

// Add the arena [mem, mem+size) to class id: the old HIGH sentinel and a new
// LINK block at mem bridge the gap, then one free block and a new HIGH sentinel.
extern "C" int MEMCLASS_link(int id, char* mem, int size)
{
    sMemClass* cls = (sMemClass*)D_004D2438[id & 0x3F];
    char buf[0x100];
    int hdr = cls->hdr;
    int align = cls->align;
    char* end = mem + size;
    char* data = mem;
    data += hdr + 0x10;
    data += align + 0x2F;
    data = (char*)((int)data & -align);
    end -= hdr + 0x30;
    int flags = cls->flags;
    sMemBlock* blk = (sMemBlock*)(data - 0x10);
    sMemBlock* last = cls->last;
    sprintf(buf, D_004A2E50, cls);
    MEM_initblock(last, buf, 0, hdr, flags | MEM_FLAG_SYSTEM, last->prev, mem);
    MEM_initblock(mem, buf, 0, hdr, flags | MEM_FLAG_SYSTEM, last, blk);
    MEM_initblock(blk, 0, end - (char*)blk - 0x10, hdr, flags, mem, end);
    sprintf(buf, D_004A2E40, cls);
    MEM_initblock(end, buf, 0, hdr, flags | MEM_FLAG_SYSTEM | MEM_FLAG_HIGH, blk, 0);
    cls->last = (sMemBlock*)end;
    // Same as MEMCLASS_linkfree, inlined.
    sMemBlock* q = &cls->freehead;
    sMemBlock* p = q;
    int sz = *(char**)(data - 8) - (char*)blk;         // blk->next - blk
    if ((char*)cls->freehead.freenext + ((char*)cls->freehead.freeprev - (char*)cls->freehead.freenext) / 2 < (char*)blk) {
        do
            p = p->freeprev;
        while (blk < p);
        q = p->freenext;
    } else {
        do
            q = q->freenext;
        while (q < blk);
        p = q->freeprev;
    }
    blk->size = sz;
    blk->freenext = q;
    blk->freeprev = p;
    p->freenext = blk;
    q->freeprev = blk;
    blk->tag = MEM_TAG_FREE;
    blk->flags |= MEM_FLAG_FREE;
    return 1;
}

//100%
// PORT: hand-rolled EE EABI va_start (gcc 2.95 va-mips.h form); use <stdarg.h> off-PS2.
typedef char* MEM_printf_va_list;
#define MEM_printf_va_start(ap)                                          \
    (ap = (char*)__builtin_next_arg()                                    \
          - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern "C" int func_004186C8(char* dst, const char* fmt, char* ap);
extern "C" void func_003E5D30(int, char*);

// printf to the debug output; the callback MEM_printclass uses.
extern "C" void MEM_printf(const char* fmt, ...)
{
    char buf[0x200];
    MEM_printf_va_list ap;
    MEM_printf_va_start(ap);
    func_004186C8(buf, fmt, ap);
    func_003E5D30(2, buf);
}

extern const char D_004800A8[]; // "%-12s %-24.24s %08lx %11lu %11lu %04x %04x %3s %s"
extern "C" void MEM_printclassf(void* thing, const char* fmt, void (*cb)(const char*, ...));

//100%
void MEM_printclass(void* thing)
{
    MEM_printclassf(thing, D_004800A8, MEM_printf);
}

extern void* D_004A2E78;

//99.25%
void MEM_print()
{
    MEM_printclass(D_004A2E78);
}

//100%
extern "C" int func_003E62D0(void* p, int size, int seed);
extern char D_004800E0[];   // column header
extern char D_00480140[];   // "-----..."
extern char D_00480198[];   // "Not initialized\n"
extern char D_004801B0[];   // "   SPACE "
extern char D_004801C0[];   // "\nTOTAL FREE MEMORY: %ld ($%08lx)\n"
extern char* D_004801E8[];  // MEM_checkblock result names
extern char D_004A2E58[];   // ""
extern char D_004A2E60[];   // "FREE"
extern char D_004A2E68[];   // "unknown"
extern char D_004A2E70[];   // "\n"

// Print a table of every block in class (int)thing through cb: type, name,
// address, size, span to the next block, flags, payload CRC and check result.
// PORT: thing is a memory class id (masked with 0x3F) passed through a void* parameter.
extern "C" void MEM_printclassf(void* thing, const char* fmt, void (*cb)(const char*, ...))
{
    int total = 0;
    int crc = 0;
    cb(D_004800E0);
    cb(D_00480140);
    sMemClass* cls = (sMemClass*)D_004D2438[(int)thing & 0x3F];
    if (cls == 0) {
        cb(D_00480198);
        return;
    }
    for (sMemBlock* blk = cls->first; blk != 0; blk = blk->next) {
        char* data = (char*)blk + 0x10;
        char* n1 = (char*)MEM_getname(data);
        if (n1 == 0)
            n1 = D_004A2E58;
        char* n2 = (char*)MEM_gettrailer(data);
        if (n2 == 0)
            n2 = D_004A2E58;
        if (blk->flags & MEM_FLAG_FREE) {
            int sz = blk->size;
            if (sz > 0x10 && !(blk->flags & MEM_FLAG_SYSTEM))
                crc = func_003E62D0((char*)blk + 0x18, sz - 0x18, 0xFBEA);
            total += sz;
            int st = MEM_checkblock(blk);
            cb(fmt, D_004A2E60, D_004801B0, data, sz, (char*)blk->next - (char*)blk, blk->flags, crc, D_004801E8[st], D_004A2E58);
        } else {
            int sz = blk->size;
            crc = 0;
            if (sz != 0 && !(blk->flags & MEM_FLAG_SYSTEM))
                crc = func_003E62D0(data, sz, 0xFBEA);
            int st = MEM_checkblock(blk);
            cb(fmt, D_004A2E68, n1, data, blk->size, (char*)blk->next - (char*)blk, blk->flags, crc, D_004801E8[st], n2);
        }
        cb(D_004A2E70);
    }
    cb(D_004801C0, total, total);
    cb(D_00480140);
}

//100%
extern int D_004A2E74; // last MEM_validheader/MEM_checkblock error (1-4)
extern "C" int func_003E6240(void* p, int size, int flags);

// 1 if p is readable and starts with a free or sentinel header.
extern "C" int MEM_validheader(void* p)
{
    int ok = 0;
    if (func_003E6240(p, 0x18, 0) != 0) {
        unsigned short m = *(unsigned short*)p;
        if (m == MEM_TAG_FREE || m == MEM_TAG_STOP) {
            ok = 1;
        } else {
            D_004A2E74 = 1;
        }
    } else {
        D_004A2E74 = 1;
    }
    return ok;
}

//100%
static inline unsigned int MEM_readBE32(unsigned char* p)
{
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

// Sanity-check one block header: sentinels must be system blocks, free blocks
// must link to valid headers, and guarded blocks must end in 'BEND'.
// PORT: the block-end address is computed as size + (int)blk (pointer held in int) to get the target's addu operand order.
extern "C" int MEM_checkblock(sMemBlock* blk)
{
    int ok = 0;
    unsigned short tag = blk->tag;
    if (tag == MEM_TAG_STOP) {
        if (blk->flags & MEM_FLAG_SYSTEM) {
            ok = 1;
        } else {
            D_004A2E74 = 2;
        }
    } else if (tag == MEM_TAG_FREE) {
        if (blk->flags & MEM_FLAG_FREE) {
            ok = MEM_validheader(blk->freenext);
            if (ok) {
                ok = MEM_validheader(blk->freeprev);
            }
        }
    } else if (tag == MEM_TAG_USED) {
        if (!(blk->flags & MEM_FLAG_GUARD) || MEM_readBE32((unsigned char*)(blk->size + (int)blk) + 0x10) == MEM_GUARD_WORD) {
            ok = 1;
        } else {
            D_004A2E74 = 3;
        }
    } else {
        D_004A2E74 = 4;
    }
    return ok;
}

extern "C" int func_002523A0()
{
    return 0x1;
}

//100%
void cMemMan_free(void*);

// Free a payload pointer (0 is ignored). Always returns 1.
extern "C" void* MEM_free(void* p)
{
    if (p != 0) {
        cMemMan_free(p);
    }
    return (void*)1;
}

INCLUDE_ASM("mem/memstd", func_002523D0);

extern "C" void MUTEX_lock(void* mutex);
extern "C" void MUTEX_unlock(void* mutex);
extern void* gMemMutex[16];
extern "C" int cMemMan_internalBlockSize(void* p);

extern "C" int func_002525F8(void* p)
{
    MUTEX_lock(gMemMutex);
    int r = cMemMan_internalBlockSize(p);
    MUTEX_unlock(gMemMutex);
    return r;
}

// Payload size of an allocation.
extern "C" int MEM_getsize(void* p)
{
    return *(int*)((char*)p + -0xC);
}

// Header flags of an allocation.
extern "C" unsigned short MEM_getflags(void* p)
{
    return *(unsigned short*)((char*)p + -0xE);
}

//100%
// Allocation names are compiled out of this build: always 0.
int MEM_getname(void* p)
{
    return 0;
}

//100%
struct sMemUnalignedInt {
    int value;
} __attribute__((packed));

// The word after the payload of a MEM_FLAG_TRAILER block (0 if none). It is
// printed as a string by MEM_printclassf.
// PORT: pointer arithmetic done in int; a plain `(char*)p - 0xE` makes gcc 2.95
// emit the offset as unsigned 0xFFFFFFF2 (addiu -0x8000 / 0x7ff2 split).
extern "C" int MEM_gettrailer(void* p)
{
    int r = 0;
    if (*(unsigned short*)((int)p - 0xE) & MEM_FLAG_TRAILER) {
        r = ((sMemUnalignedInt*)((char*)p + *(int*)((int)p - 0xC) + 4))->value;
    }
    return r;
}

// Set the trailer word; returns 0 if the block has none.
extern "C" int MEM_settrailer(void* p, int value)
{
    int r = 0;
    if (*(unsigned short*)((int)p - 0xE) & MEM_FLAG_TRAILER) {
        r = 1;
        ((sMemUnalignedInt*)((char*)p + *(int*)((int)p - 0xC) + 4))->value = value;
    }
    return r;
}

//100%
extern "C" void* cMemMan_internalResizeBlock(void* block, int size);

// Resize an allocation under the memory manager's lock.
extern "C" void* MEM_resize(void* p, int size)
{
    void* r;
    MUTEX_lock(gMemMutex);
    r = cMemMan_internalResizeBlock(p, size);
    MUTEX_unlock(gMemMutex);
    return r;
}

INCLUDE_ASM("mem/memstd", func_00252718);

// Extra header bytes per block of class id (the first argument is unused).
extern "C" int MEMCLASS_hdrsize(void* unused, int id)
{
    return ((sMemClass*)D_004D2438[id & 0x3F])->hdr;
}

//100%
extern "C" int func_00320B68(int);
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");

// PORT: the unit declares func_00252980 as `void* (void*)`; existing callers bind the
// 6-argument form below by asm label (the 6th argument is unused).
void* func_00252980_6(void*, int, int, int, int, int) __asm__("func_00252980");

void* func_00252980_6(void* tag, int size, int align, int d, int flags, int unused)
{
    int lvl = func_00320B68(align) - 2 < 0 ? 0 : func_00320B68(align) - 2;
    return operator_new_tag(size, (const char*)tag, flags | (lvl << 24) | 0x10000000, d);
}

extern "C" void* func_00252980(void*);

INCLUDE_ASM("mem/memstd", func_00252A10);

//100% - objdiff report; single-function view differs only in a relocation name
void* func_00252980_6(void*, int, int, int, int, int) __asm__("func_00252980");

// PORT: the project's symbol name says (void*), but callers pass and this
// forwards 5 args (see func_00253AD0); the real body is bound by asm label.
void* func_00252F60_impl(void* a0, int a1, int a2, int a3, int a4) __asm__("func_00252F60__FPv");

void* func_00252F60_impl(void* a0, int a1, int a2, int a3, int a4)
{
    return func_00252980_6(a0, a1, a2, a3, a4, 1);
}

void* func_00252A10_6(void*, int, int, int, int, int) __asm__("func_00252A10");

extern "C" void* func_00252F80(void* a0, int a1, int a2, int a3, int a4)
{
    return func_00252A10_6(a0, a1, a2, a3, a4, 1);
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
void* func_00252980_6(void*, int, int, int, int, int) __asm__("func_00252980");

extern "C" void* func_00252FA0(void* a0, int a1, int a2)
{
    return func_00252980_6(a0, a1, 0x80, 0, a2, 1);
}

extern "C" void* func_00252FC8(void* a0, int a1, int a2)
{
    return func_00252A10_6(a0, a1, 0x80, 0, a2, 1);
}

extern "C" void* func_00252FF0(void* a0, int a1, int a2)
{
    return func_00252980_6(a0, a1, 0, 0, a2, 0);
}

extern "C" void* func_00253018(void* a0, int a1, int a2)
{
    return func_00252A10_6(a0, a1, 0, 0, a2, 0);
}

extern "C" void* func_00253040(int size)
{
    return func_00252980_6(0, size, 0, 0, 0, 1);
}

extern "C" void* func_00253070(int size)
{
    return func_00252A10_6(0, size, 0, 0, 0, 1);
}

extern "C" void* func_002530A0(int size)
{
    return func_00252980_6(0, size, 0, 0, 0, 0);
}

extern "C" void* func_002530D0(int size)
{
    return func_00252A10_6(0, size, 0, 0, 0, 0);
}

// First free block of at least size bytes, walking the free list forward or
// backward from its head; 0 if the walk gets back to the head.
extern "C" sMemBlock* MEMCLASS_firstfit(sMemClass* cls, int size, int backward)
{
    sMemBlock* b = &cls->freehead;
    if (backward == 0) {
        do {
            b = b->freenext;
        } while (b->size < size);
    } else {
        do {
            b = b->freeprev;
        } while (b->size < size);
    }
    return b->tag != MEM_TAG_STOP ? b : 0;
}

//100%
// Largest free block whose payload exceeds size - 1, walking the free list
// forward (backward 0) or backward; 0 if none.
extern "C" sMemBlock* MEMCLASS_largestfree(sMemClass* cls, int size, int backward)
{
    int best = size - 1;
    if (best < 0) {
        best = 0;
    }
    sMemBlock* r = 0;
    sMemBlock* p;
    if (backward == 0) {
        p = cls->freehead.freenext;
        for (;;) {
            if (best < p->size - 0x10) {
                if (p->tag == MEM_TAG_STOP) {
                    break;
                }
                r = p;
                best = r->size - 0x10;
            }
            p = p->freenext;
        }
    } else {
        p = cls->freehead.freeprev;
        for (;;) {
            if (best < p->size - 0x10) {
                if (p->tag == MEM_TAG_STOP) {
                    break;
                }
                r = p;
                best = r->size - 0x10;
            }
            p = p->freeprev;
        }
    }
    return r;
}

//100%
// Total free payload bytes in a class, walking the free list forward
// (backward 0) or backward.
extern "C" int MEMCLASS_totalfree(sMemClass* cls, int backward)
{
    int total = 0;
    if (backward == 0) {
        sMemBlock* node = cls->freehead.freenext;
        while (node->tag != MEM_TAG_STOP) {
            total += node->size - 0x10;
            node = node->freenext;
        }
    } else {
        sMemBlock* node = cls->freehead.freeprev;
        while (node->tag != MEM_TAG_STOP) {
            total += node->size - 0x10;
            node = node->freeprev;
        }
    }
    return total;
}

//100%
// Mark blk free and link it into the class's address-ordered free list,
// searching from whichever end is nearer.
extern "C" void MEMCLASS_linkfree(sMemClass* cls, sMemBlock* blk)
{
    sMemBlock* next = &cls->freehead;
    sMemBlock* prev = next;
    int size = (char*)blk->next - (char*)blk;
    if ((char*)cls->freehead.freenext + ((char*)cls->freehead.freeprev - (char*)cls->freehead.freenext) / 2 < (char*)blk) {
        do {
            prev = prev->freeprev;
        } while (blk < prev);
        next = prev->freenext;
    } else {
        do {
            next = next->freenext;
        } while (next < blk);
        prev = next->freeprev;
    }
    blk->size = size;
    blk->freenext = next;
    blk->freeprev = prev;
    prev->freenext = blk;
    next->freeprev = blk;
    blk->tag = MEM_TAG_FREE;
    blk->flags |= MEM_FLAG_FREE;
}

// Take blk off the free list and mark it 'BO'.
extern "C" void MEM_unlinkfree(sMemBlock* blk)
{
    sMemBlock* prev = blk->freeprev;
    sMemBlock* next = blk->freenext;
    prev->freenext = next;
    next->freeprev = prev;
    blk->tag = MEM_TAG_OUT;
    blk->flags &= ~MEM_FLAG_FREE;
}

//100%
extern "C" void func_00253390(void* self)
{
    *(float*)((char*)self + 0x20) = 1.0f;
    *(int*)((char*)self + 0x1c) = 31;
    *(int*)((char*)self + 0x0) = 0;
    *(int*)((char*)self + 0x4) = 0;
    *(int*)((char*)self + 0xc) = 0;
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0x10) = 0;
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0x18) = 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_00253AA0();

extern "C" void* func_002533C8(void* self)
{
    func_00253AA0();
    func_00253390((char*)self + 0x14);
    *(float*)((char*)self + 0x10) = *(float*)((char*)self + 0x34);
    *(int*)((char*)self + 0x38) = 0;
    *(int*)((char*)self + 0x3C) = 0;
    *(int*)((char*)self + 0xC) = 0;
    *(int*)((char*)self + 0x40) = 0;
    *(int*)((char*)self + 0x8) = 0;
    return self;
}

//100%
void operator_delete(int*);
extern "C" void func_002535F8(void* self);

extern "C" void func_00253418(void* self, int flags)
{
    func_002535F8(self);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

struct sParams00253460 {
    int w[8];
    float f20;
};

extern "C" void func_002534A8(void* self, sParams00253460* params);

extern "C" void func_00253460(void* self, int a1)
{
    sParams00253460 params;
    func_002535F8(self);
    func_00253390(&params);
    params.w[0] = a1;
    func_002534A8(self, &params);
}

INCLUDE_ASM("mem/memstd", func_002534A8);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_003B0680(void*, void*);
extern "C" void func_003AE300(void* p, int flags);
extern int D_004A2E9C;

class cWorld002535F8 {
public:
    char pad[0x10D8];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
};
extern cWorld002535F8* D_004A5B80_w __asm__("D_004A5B80");

struct sVEntry002535F8 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sStream002535F8 {
    int f0;
    int f4;
    int f8;
    void* fC;
    char pad10[0x28];
    char* f38;
    void* f3C;
    int f40;
};

extern "C" void func_002535F8(void* self)
{
    sStream002535F8* s = (sStream002535F8*)self;
    if (s->f38 != 0 && s->f3C != 0) {
        D_004A5B80_w->v19();
    }
    if (s->f40 != 0 && s->fC != 0) {
        func_003B0680(*(void**)(s->f38 + 0x64), s->fC);
    }
    void* o = s->f3C;
    if (o != 0) {
        sVEntry002535F8* e = &(*(sVEntry002535F8**)((char*)o + 4))[1];
        e->fn((char*)o + e->delta, 3);
        s->f3C = 0;
        D_004A2E9C--;
    }
    char* m = s->f38;
    if (m != 0) {
        func_003AE300(m, 3);
        s->f38 = 0;
    }
    s->f0 = 0;
    s->f4 = 0;
    s->f8 = 0;
    s->fC = 0;
    s->f40 = 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern int D_004A2E9C;
extern int D_004A5B80;
extern "C" int func_003AE450(void* p, int a, int b);
extern "C" void* func_00254368(void* a0, int a1, int a2, int a3);
int func_003AE938(void*);
int func_003AE958_i(void*) __asm__("func_003AE958__FPv");

extern "C" void func_002536C8(void* self)
{
    char* s = (char*)self;
    *(int*)(s + 0x0) = 0;
    *(int*)(s + 0x4) = 0;
    *(int*)(s + 0xC) = 0;
    *(int*)(s + 0xC) = func_003AE450(*(void**)(s + 0x38), 1, 0x21);
    *(int*)(s + 0x40) = 1;
    func_003AE938(*(void**)(s + 0x38));
    *(void**)(s + 0x3C) = func_00254368(*(void**)(*(char**)(s + 0x38) + 0x64), *(int*)(s + 0xC), D_004A5B80, *(int*)(s + 0x30));
    func_003AE958_i(*(void**)(s + 0x38));
    D_004A2E9C++;
}

//100%
struct sVEntry_253748 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

struct sObj_253748 {
    int f0;
    sVEntry_253748* vt;     // 0x4
};

struct sWorld_253748 {
    char pad[0x10D8];
    sVEntry_253748* vt;     // 0x10D8
};

struct sStream_253748 {
    int done;               // 0x0
    int idle;               // 0x4
    int f8;
    void* buf;              // 0xC
    char pad10[0x28];
    char* file;             // 0x38
    sObj_253748* obj;       // 0x3C
    int open;               // 0x40
};

extern sWorld_253748* D_004A5B80_253748 __asm__("D_004A5B80");
extern "C" void SYNCTASK_run(int a);
extern "C" void func_003E5398(int a);
extern "C" int func_003AE780(void* self);
extern "C" int func_003AE6C8(void* self, float f);
extern "C" int func_003AE860(void* self);

// Streams the whole file through obj, running the sync tasks between reads.
extern "C" void func_00253748(sStream_253748* s)
{
    if (s->file == 0) {
        return;
    }
    func_002536C8(s);
    do {
        if (s->idle != 0) {
            sVEntry_253748* e = &s->obj->vt[5];
            ((void (*)(void*))e->fn)((char*)s->obj + e->delta);
        } else {
            sVEntry_253748* e = &s->obj->vt[4];
            e->fn((char*)s->obj + e->delta, s->buf);
        }
        sWorld_253748* w = D_004A5B80_253748;
        sVEntry_253748* we = &w->vt[20];
        ((void (*)(void*))we->fn)((char*)w + we->delta);
        SYNCTASK_run(0);
        func_003E5398(0);
        if (func_003AE780(s->file) != 0) {
            sVEntry_253748* e = &s->obj->vt[6];
            ((void (*)(void*))e->fn)((char*)s->obj + e->delta);
            s->buf = (void*)func_003AE6C8(s->file, *(float*)(s->file + 0x48));
            s->idle = 0;
        } else {
            s->idle = 1;
        }
        if (s->buf == 0) {
            s->idle = 1;
            s->done = func_003AE860(s->file);
        }
    } while (s->done == 0);
    s->open = 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002536C8(void* self);

extern "C" int func_00253860(void* self)
{
    if (*(void**)((char*)self + 0x38) == 0) {
        return 0;
    }
    func_002536C8(self);
    return 1;
}

//100%
class cMemObj_253890 {
public:
    int field_0x0;
    // vptr at 0x4; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04(int a);
    virtual void v05();
};

extern "C" void func_00253890(void* self, int force)
{
    if (*(void**)((char*)self + 0x38) == 0) {
        return;
    }
    cMemObj_253890* obj = *(cMemObj_253890**)((char*)self + 0x3C);
    if (obj == 0) {
        return;
    }
    if (force != 0 || *(int*)((char*)self + 0x8) != 0
        || (*(int*)((char*)self + 0x40) == 0 && *(int*)((char*)self + 0x4) != 0)
        || *(int*)((char*)self + 0x0) != 0) {
        (*(cMemObj_253890**)((char*)self + 0x3C))->v05();
    } else {
        obj->v04(*(int*)((char*)self + 0xC));
        *(int*)((char*)self + 0x40) = 0;
    }
}

//100%
extern "C" int func_003AE780(void* p);
extern "C" int func_003AE6C8(void* p, float f);
extern "C" int func_003AE860(void* p);

class cMemObj_253938 {
public:
    int field_0x0;
    // vptr at 0x4; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04(int a);
    virtual void v05();
    virtual void v06();
};

extern "C" void func_00253938(void* self)
{
    if (*(int*)((char*)self + 0x40) == 0 && func_003AE780(*(void**)((char*)self + 0x38)) != 0) {
        (*(cMemObj_253938**)((char*)self + 0x3C))->v06();
        void* p = *(void**)((char*)self + 0x38);
        *(int*)((char*)self + 0xC) = func_003AE6C8(p, *(float*)((char*)p + 0x48));
        *(int*)((char*)self + 0x40) = 1;
        *(int*)((char*)self + 0x4) = 0;
    } else {
        *(int*)((char*)self + 0x4) = 1;
    }
    if (*(int*)((char*)self + 0xC) == 0 && *(int*)((char*)self + 0x0) == 0) {
        *(int*)((char*)self + 0x40) = 0;
        *(int*)((char*)self + 0x4) = 1;
        *(int*)((char*)self + 0x0) = func_003AE860(*(void**)((char*)self + 0x38));
    }
}

//100%
int func_003AE938(void*);

extern "C" void func_002539E0(void* self)
{
    void* p = *(void**)((char*)self + 0x38);
    if (p != 0 && *(int*)((char*)self + 0x3C) != 0 && *(int*)((char*)self + 0x0) == 0
        && *(int*)((char*)self + 0x8) == 0) {
        func_003AE938(p);
        *(int*)((char*)self + 0x8) = 1;
    }
}

//100%
void func_003AE958(void*);

extern "C" void func_00253A40(void* self)
{
    void* p = *(void**)((char*)self + 0x38);
    if (p != 0 && *(int*)((char*)self + 0x3C) != 0 && *(int*)((char*)self + 0x0) == 0
        && *(int*)((char*)self + 0x8) != 0) {
        func_003AE958(p);
        *(int*)((char*)self + 0x8) = 0;
    }
}

//100%
extern "C" void* func_00253AD0(int size);
void* func_00253AF8(void* self);

struct sMemAllocFuncs {
    void* (*alloc)(int);    // 0x0
    void* (*free)(void*);   // 0x4
    int field_0x8;          // 0x8
};
extern sMemAllocFuncs D_00509430;

extern "C" void func_00253AA0()
{
    D_00509430.alloc = func_00253AD0;
    D_00509430.free = func_00253AF8;
    D_00509430.field_0x8 = 0x400;
}

//100% - objdiff report; single-function view differs only in a relocation name
void* func_00252F60_5(void* a0, int a1, int a2, int a3, int a4) __asm__("func_00252F60__FPv");

// PORT: the unit declares this as (int size); the body uses 5 args (prototype mismatch).
void* func_00253AD0_impl(void* a0, int a1, int align, int a3, int a4) __asm__("func_00253AD0");

void* func_00253AD0_impl(void* a0, int a1, int align, int a3, int a4)
{
    if (align < 64) {
        align = 64;
    }
    return func_00252F60_5(a0, a1, align, a3, a4);
}


//99.29%
void* func_00253AF8(void* self)
{
    return MEM_free(self);
}

extern "C" void* func_00253B18(void* self, ...)
{
    return self;
}

INCLUDE_ASM("mem/memstd", func_00253B58);

extern "C" void* func_00253B58(int, int);

//99.38%
void* func_00254330(void* self)
{
    return func_00253B58(1, 0xffff);
}

//100%
extern "C" int func_00254350(int x)
{
    float fv = (float)x;
    int bits = *(int*)&fv;
    return (bits >> 23) - 0x7f;
}

//100%
extern char D_004A2EA0[];
extern "C" void* func_00254410(void* self, void* a0, int a1, int a2, int a3);

// PORT: the unit's sMemAllocFuncs declares alloc as `void* (*)(int)`; it really
// takes (tag, size, align, d, flags) (see func_00252F60 / func_00253AD0).
typedef void* (*tMemAlloc5_00254368)(void*, int, int, int, int);

extern "C" void* func_00254368(void* a0, int a1, int a2, int a3)
{
    void* p = ((tMemAlloc5_00254368)D_00509430.alloc)(D_004A2EA0, 0x54, 0, 0, D_00509430.field_0x8);
    return func_00254410(p, a0, a1, a2, a3);
}

//100%
extern "C" void func_002543F0(void* self, float a, float b, float c)
{
    *(float*)((char*)self + 0x40) = a;
    *(float*)((char*)self + 0x44) = b;
    *(float*)((char*)self + 0x48) = c;
}

//100%
void func_00254400(void* self, float f0, float f1)
{
    *(float*)((char*)self + 0x4c) = f0;
    *(float*)((char*)self + 0x50) = f1;
}

INCLUDE_ASM("mem/memstd", func_00254410);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern void* D_00480270[];
extern void* D_004802B0[];
extern void* (*D_00509434[])(void*);

struct sRVEntry_2547B8 {
    short delta;
    short index;
    void (*fn)(void*, int);
};
struct sRCtx_2547B8 {
    char pad[0x10D8];
    sRVEntry_2547B8* vt;
};
extern sRCtx_2547B8* D_004A5B80_2547B8 __asm__("D_004A5B80");

struct sTexCache_2547B8 {
    void* owner;
    void** vt;
    int f8;
    void* fC;
    int f10;
    int** texs;
    int count;
};

extern "C" void func_002547B8(sTexCache_2547B8* self, int flags)
{
    self->vt = D_00480270;
    for (int i = 0; i < self->count; i++) {
        int* t = self->texs[i];
        if (t != 0) {
            D_004A5B80_2547B8->vt[50].fn((char*)D_004A5B80_2547B8 + D_004A5B80_2547B8->vt[50].delta, *t);
            *t = -1;
            D_00509430.free(t);
        }
    }
    if (self->texs != 0) {
        cMemMan_free(self->texs);
    }
    self->texs = 0;
    if (self->fC != 0) {
        func_003B0680(self->owner, self->fC);
        self->fC = 0;
    }
    self->vt = D_004802B0;
    if (flags & 1) {
        D_00509434[0](self);
    }
}

//100%
struct sVec4_2548D0 {
    float v[4];
    sVec4_2548D0() {}
} __attribute__((aligned(16)));

struct sVtx_2548D0 {
    float u, v, q;
    int pad;
    int r, g, b, a;
    sVec4_2548D0 pos;
    sVtx_2548D0() {}
};

struct sRS_2548D0 {
    int f0;
    int f4;
    int f8;
    int fC;
    short f10;
};

class cWorld_2548D0 {
public:
    char pad0[0xE84];
    sRS_2548D0* top;
    char pad1[0x10D8 - 0xE88];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual unsigned int v10();
    virtual unsigned int v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual int v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26(int a, int b, float x, float y, float w, float h, float zn, float zf);
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34(void* p);
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71(int n, void* verts, int flags);
};

extern cWorld_2548D0* D_004A5B80_2548D0 __asm__("D_004A5B80");
extern char D_004FF1A0[];

struct sMesh_2548D0 {
    int f0;
    int f4;
    cWorld_2548D0* world;   // 0x8
    void* res;              // 0xC
    char* hdr;              // 0x10
    int** items;            // 0x14
    int f18;
    int rows;               // 0x1C
    int cols;               // 0x20
    int widths[6];          // 0x24
    int f3C;                // 0x3C
    float x;                // 0x40
    float y;                // 0x44
    float z;                // 0x48
    float cw;               // 0x4C
    float ch;               // 0x50
};

// PORT: the unit declares func_002548D0 as returning void*, but it returns nothing (v0 is left as is); bind the real signature.
extern "C" void func_002548D0_impl(void* p) __asm__("func_002548D0");
INCLUDE_ASM("mem/memstd", func_002548D0);
extern "C" void func_002548D0_impl(void* p);

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
class cWorld_254C48 {
public:
    char pad[0x10D8];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49(int a, char* p, int b, int c, int d, int e, int f, int g, int h);
};
extern "C" void* func_002548D0(void* self);
extern cWorld_254C48* D_004A5B80_254C48 __asm__("D_004A5B80");

struct sMesh_254C48 {
    int f0;
    int f4;
    int f8;
    void* res;
    char* hdr;
    char** items;
    int f18;
    int rows;
    int cols;
    int widths[1];
};

extern "C" void func_00254C48(sMesh_254C48* self, void* res)
{
    if (res != 0) {
        self->res = res;
    }
    char* hdr = *(char**)((char*)res + 4);
    self->hdr = hdr;
    char* data;
    if (*(int*)(hdr + 0xC) & 0x1000) {
        data = hdr + *(int*)(hdr + 0x10);
    } else {
        data = hdr + 0x10;
    }
    int k = 0;
    short stride = *(short*)(self->hdr + 6);
    for (int i = 0; i < self->rows; i++) {
        int off = 0;
        for (int j = 0; j < self->cols; j++) {
            int* e = ((int**)self->items)[k];
            D_004A5B80_254C48->v49(e[0], data + ((off << 6) + stride * (i << 6)), e[1], e[2], 0, 0, 0, 0, 0);
            k++;
            off += self->widths[j];
        }
    }
    func_002548D0(self);
}

extern "C" void* func_002548D0(void* self);

//99.29%
void* func_00254DA0(void* self)
{
    return func_002548D0(self);
}

//100%
struct sMemStdVEntry {
    short delta;
    short index;
    int (*fn)(void*);
};

extern "C" void func_003B0680(void*, void*);

extern "C" void func_00254DC0(void* self)
{
    void* o;
    sMemStdVEntry* vt;
    do {
        o = *(void**)((char*)self + 0x8);
        vt = *(sMemStdVEntry**)((char*)o + 0x10D8);
    } while (vt[18].fn((char*)o + vt[18].delta) == 0);
    void* p = *(void**)((char*)self + 0xC);
    if (p != 0) {
        func_003B0680(*(void**)((char*)self + 0x0), p);
        *(void**)((char*)self + 0xC) = 0;
    }
}

extern "C" void* func_00254E20(void* self, ...)
{
    return self;
}

INCLUDE_ASM("mem/memstd", func_00254E60);

//100%
extern void* D_004802B0[];
void operator_delete(int*);

extern "C" void func_00255638(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004802B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
void func_00255668(void* self)
{
}

extern "C" void* func_00254E60(int, int);

extern char D_004A2EA0[];

extern "C" void* func_00255670(int size)
{
    return ((tMemAlloc5_00254368)D_00509430.alloc)(D_004A2EA0, size, 0, 0, D_00509430.field_0x8);
}

extern "C" void* func_002556B0(int size)
{
    return ((tMemAlloc5_00254368)D_00509430.alloc)(D_004A2EA0, size, 0, 0, D_00509430.field_0x8);
}

extern "C" void* func_002556F0(int size, void* tag, int align, int d, int flags)
{
    return ((tMemAlloc5_00254368)D_00509430.alloc)(tag, size, align, d, flags);
}

extern "C" void* func_00255720(int size, void* tag, int align, int d, int flags)
{
    return ((tMemAlloc5_00254368)D_00509430.alloc)(tag, size, align, d, flags);
}

extern "C" void func_00255750(void* p)
{
    D_00509430.free(p);
}

extern "C" void func_00255778(void* p)
{
    D_00509430.free(p);
}

extern "C" int func_002557A0(int a0, int a1)
{
    return a1;
}

extern "C" void func_002557A8()
{
}

extern "C" int func_002557B0(int a0, int a1)
{
    return a1;
}

extern "C" void func_002557B8()
{
}

//99.38%
void* func_002557C0(void* self)
{
    return func_00254E60(1, 0xffff);
}

extern void* D_00481320[];

//100%
void* func_002557E0(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x8) = (int)(void*)D_00481320;
    *(int*)((char*)self + 0x4) = t0;
    return self;
}

//100%
void operator_delete(int*);

extern "C" void func_00255800(void* self, int flags)
{
    *(void***)((char*)self + 0x8) = D_00481320;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
int func_00255830(void* self)
{
    int t0 = 1;
    *(int*)((char*)self + 0x4) = 0;
    *(int*)self = t0;
    return t0;
}

//100%
extern "C" void func_00255840(void* self)
{
    if (*(int*)self != 0) {
        *(int*)self = 0;
        *(int*)((char*)self + 0x4) = 0;
    }
}

