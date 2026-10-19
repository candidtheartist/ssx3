#include "common.h"
#include "bx/dlmalloc.h"

//100%
void func_0031D790(void* self);
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern char D_0048DB38[];

struct sCubicSplineFlags {
    unsigned int b0 : 1;
    unsigned int b1 : 1;
    unsigned int b2 : 1;
    unsigned int f3 : 8;
    unsigned int count : 8;
};

struct sCubicSpline {
    sCubicSplineFlags flags;
    float f4;
    void* data;
};

// PORT: binds the real 2-arg body; the unit declares a 1-arg prototype used by callers
extern "C" void cCubicSplineInterpolant_initCommon_impl(sCubicSpline* self, int n) __asm__("cCubicSplineInterpolant_initCommon");
extern "C" void cCubicSplineInterpolant_initCommon_impl(sCubicSpline* self, int n)
{
    if (self->data != 0) {
        func_0031D790(self);
    }
    self->flags.count = n - 1;
    self->data = operator_new_tag(self->flags.count * 0x14, D_0048DB38, 0, 0);
    self->flags.b1 = 1;
    self->flags.f3 = 0;
}

extern "C" void cCubicSplineInterpolant_initCommon(void* self);

//99.62%
void func_0031D700(void* self)
{
    cCubicSplineInterpolant_initCommon(self);
    *(int*)self &= -2;
}

//99.76%
void func_0031D738(void* self, float a, float b)
{
    cCubicSplineInterpolant_initCommon(self);
    unsigned int flags = *(unsigned int*)self;
    void* ptr = *(void**)((char*)self + 0x8);
    flags |= 1;
    *(unsigned int*)self = flags;
    *(float*)((char*)ptr + 0x10) = a;
    *(float*)((char*)self + 0x4) = b;
}

void* cMemMan_free(void* ptr);

//100%
void func_0031D790(void* self)
{
    if (*(void**)((char*)self + 0x8) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x8));
        *(void**)((char*)self + 0x8) = 0;
    }
    int flags = *(int*)self;
    flags &= -3;
    flags &= -5;
    *(int*)self = flags;
}

//100%
struct sCubicSplineKeyK2 {
    float x;  // 0x0
    float y;  // 0x4
    float tx; // 0x8
    float ty; // 0xC
    float pad_0x10;
};

extern "C" void func_0031D8B0(sCubicSpline* self);

extern "C" void func_0031D7E0(sCubicSpline* self, float x, float y)
{
    if (self->flags.f3 == self->flags.count) {
        ((sCubicSplineKeyK2*)self->data)[self->flags.f3 - 1].tx = x;
        ((sCubicSplineKeyK2*)self->data)[self->flags.f3 - 1].ty = y;
        func_0031D8B0(self);
        self->flags.b2 = 1;
    } else {
        ((sCubicSplineKeyK2*)self->data)[self->flags.f3].x = x;
        ((sCubicSplineKeyK2*)self->data)[self->flags.f3].y = y;
        self->flags.f3++;
    }
}

INCLUDE_ASM("bx/cubicspline", func_0031D8B0);

INCLUDE_ASM("bx/cubicspline", func_0031DEE0);

//100%
// Samples the spline in 99 even steps from the first key to the end value at 0x4. The first, empty loop is in the original.
extern "C" float func_0031DEE0(sCubicSpline* self, float x);

extern "C" void func_0031E0E0(sCubicSpline* self)
{
    float start = ((sCubicSplineKeyK2*)self->data)->pad_0x10;
    float end = self->f4;
    float step = (end - start) * 0.01010101f;
    float t;
    float x;
    for (t = start; t <= end; t += step)
        ;
    for (x = start; x <= end; x += step)
        func_0031DEE0(self, x);
}

INCLUDE_ASM("bx/cubicspline", func_0031E190);

//100%
// dlmalloc 2.7 largebin_index() (portable highest-bit version).
extern "C" int dl_largebin_index(unsigned int sz)
{
    unsigned int x = sz >> 8;
    unsigned int m;
    if (x >= 0x10000)
        return 95;
    {
        unsigned int n = ((x - 0x100) >> 16) & 8;
        x <<= n;
        m = ((x - 0x1000) >> 16) & 4;
        n += m;
        x <<= m;
        m = ((x - 0x4000) >> 16) & 2;
        n += m;
        x = (x << m) >> 14;
        m = 13 - n + (x & ~(x >> 1));
    }
    return 32 + (m << 2) + ((sz >> (m + 6)) & 3);
}

//100%
void dl_malloc_init_state(void* self)
{
    char* p = (char*)self + 0x38;
    for (int i = 0x5E; i >= 0; i--) {
        *(void**)(p + 0xC) = p;
        *(void**)(p + 0x8) = p;
        p += 8;
    }
    *(int*)((char*)self + 0x34C) = 0x40000;
    *(int*)((char*)self + 0x344) = 0x8000;
    *(int*)((char*)self + 0x360) |= 1;
    *(int*)self = (*(int*)self & 3) | 0x50;
    *(void**)((char*)self + 0x30) = (char*)self + 0x38;
    *(int*)((char*)self + 0x348) = 0;
    *(int*)((char*)self + 0x354) = 0;
    *(int*)((char*)self + 0x35C) = 0x1000;
}

//100%
// dlmalloc 2.7 sYSMALLOc()
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t/uint64_t off-PS2.
extern "C" unsigned int cMemHeap_sbrk(void* self, long incr); // PORT: 64-bit long param
extern "C" void* dl_malloc(void* ms, unsigned int bytes);
extern "C" void dl_malloc_consolidate(void* ms, sMallocState* av);
// PORT: the unit declares dl_free(void*); the body really takes (ms, mem).
extern "C" void dl_free_E2D8(void* ms, void* mem) __asm__("dl_free");
extern "C" int* func_00415FB8();



extern "C" void* dl_sysmalloc(void* ms, unsigned int nb, sMallocState* av)
{
    sMallocChunk* old_top;
    unsigned int old_size;
    char* old_end;
    long size;
    char* brk;
    long correction;
    char* snd_brk;
    unsigned int front_misalign;
    unsigned int end_misalign;
    char* aligned_brk;
    sMallocChunk* p;
    sMallocChunk* remainder;
    unsigned int remainder_size;
    unsigned int sum;
    unsigned int pagemask = av->pagesize - 1;

    if (av->max_fast & 2) {
        dl_malloc_consolidate(ms, (sMallocState*)av);
        return dl_malloc(ms, nb - 15);
    }

    old_top = av->top;
    old_size = old_top->size & ~3U;
    old_end = (char*)old_top + old_size;

    brk = snd_brk = (char*)0xFFFFFFFF;

    size = nb + av->top_pad + 16;
    if (av->morecore_properties & 1)
        size -= old_size;
    size = (size + pagemask) & ~pagemask;
    if (size > 0)
        brk = (char*)cMemHeap_sbrk(ms, size);

    if (brk != (char*)0xFFFFFFFF) {
        av->sbrked_mem += size;

        if (brk == old_end && snd_brk == (char*)0xFFFFFFFF) {
            old_top->size = (size + old_size) | 1;
        } else {
            front_misalign = 0;
            end_misalign = 0;
            correction = 0;
            aligned_brk = brk;

            if ((av->morecore_properties & 1) && old_size != 0 && brk < old_end) {
                av->morecore_properties &= ~1U;
            }

            if (av->morecore_properties & 1) {
                if (old_size != 0)
                    av->sbrked_mem += brk - old_end;

                front_misalign = (unsigned int)(brk + 8) & 15;
                if (front_misalign > 0) {
                    correction = 16 - front_misalign;
                    aligned_brk += correction;
                }

                correction += old_size;

                end_misalign = (unsigned int)(brk + size + correction);
                correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;

                snd_brk = (char*)cMemHeap_sbrk(ms, correction);

                if (snd_brk == (char*)0xFFFFFFFF) {
                    correction = 0;
                    snd_brk = (char*)cMemHeap_sbrk(ms, 0);
                } else if (snd_brk < brk) {
                    snd_brk = brk + size;
                    correction = 0;
                    av->morecore_properties &= ~1U;
                }
            } else {
                if (snd_brk == (char*)0xFFFFFFFF) {
                    snd_brk = (char*)cMemHeap_sbrk(ms, 0);
                    av->sbrked_mem += snd_brk - brk - size;
                }
            }

            if (snd_brk != (char*)0xFFFFFFFF) {
                av->top = (sMallocChunk*)aligned_brk;
                av->top->size = (snd_brk - aligned_brk + correction) | 1;
                av->sbrked_mem += correction;

                if (old_size != 0) {
                    old_size = (old_size - 12) & ~15U;
                    old_top->size = old_size | 1;
                    ((sMallocChunk*)((char*)old_top + old_size))->size = 5;
                    ((sMallocChunk*)((char*)old_top + old_size + 4))->size = 5;
                    if (old_size >= 16) {
                        unsigned int tt = av->trim_threshold;
                        av->trim_threshold = 0xFFFFFFFF;
                        dl_free_E2D8(ms, (char*)old_top + 8);
                        av->trim_threshold = tt;
                    }
                }
            }
        }

        sum = av->sbrked_mem;
        if (sum > av->max_sbrked_mem)
            av->max_sbrked_mem = sum;
        sum += av->mmapped_mem;
        if (sum > av->max_total_mem)
            av->max_total_mem = sum;

        p = av->top;
        size = p->size & ~3U;
        if ((unsigned int)size >= (unsigned int)(nb + 16)) {
            remainder_size = size - nb;
            remainder = (sMallocChunk*)((char*)p + nb);
            av->top = remainder;
            p->size = nb | 1;
            remainder->size = remainder_size | 1;
            return (char*)p + 8;
        }
    }

    *func_00415FB8() = 12;
    return 0;
}

//100%
extern "C" unsigned int cMemHeap_sbrk(void* self, long incr); // PORT: 64-bit long param
// PORT: libgcc 64-bit helpers called by name so the relocations match
// (__divdi3 / __muldi3 in the retail ELF's unnamed libgcc copy).
extern "C" long func_0040FCB0(long a, long b);
extern "C" long func_004114D0(long a, long b);



extern "C" int dl_systrim(void* ms, unsigned int pad, sMallocState* av)
{
    long top_size;
    long extra;
    long released;
    char* current_brk;
    char* new_brk;
    unsigned int pagesz;

    pagesz = av->pagesize;
    top_size = av->top->size & ~3;
    extra = func_004114D0(func_0040FCB0(top_size - pad - 16 + (pagesz - 1), pagesz) - 1, pagesz);
    if (extra > 0) {
        current_brk = (char*)cMemHeap_sbrk(ms, 0);
        if (current_brk == (char*)av->top + top_size) {
            cMemHeap_sbrk(ms, -extra);
            new_brk = (char*)cMemHeap_sbrk(ms, 0);
            if (new_brk != (char*)0xFFFFFFFF) {
                released = current_brk - new_brk;
                if (released != 0) {
                    av->sbrked_mem -= released;
                    av->top->size = (top_size - released) | 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}

//100%
// dlmalloc 2.7.0 malloc()


extern "C" int dl_largebin_index(unsigned int sz);
// PORT: the unit declares these with their own state types; bind the malloc view by asm label.
extern "C" void dl_malloc_consolidate_E818(void* ms, sMallocState* av) __asm__("dl_malloc_consolidate");
extern "C" void* dl_sysmalloc_E818(void* ms, unsigned int nb, sMallocState* av) __asm__("dl_sysmalloc");

#define BIN_AT_31E818(av, i) ((sMallocChunk*)((char*)&(av)->bins[(i) << 1] - 8))

extern "C" void* dl_malloc(void* ms, unsigned int bytes)
{
    sMallocState* av = *(sMallocState**)ms;
    unsigned int nb;
    unsigned int idx;
    sMallocChunk* bin;
    sMallocChunk** fb;
    sMallocChunk* victim;
    unsigned int size;
    int victim_index;
    sMallocChunk* remainder;
    unsigned int remainder_size;
    unsigned int block;
    unsigned int bit;
    unsigned int map;
    sMallocChunk* fwd;
    sMallocChunk* bck;

    if (bytes >= (unsigned int)-32) {
        *func_00415FB8() = 12;
        return 0;
    }
    nb = (bytes + 4 + 15 < 16) ? 16 : (bytes + 4 + 15) & ~15U;

    if (!(av->max_fast & 1)) {
        if (av->max_fast == 0)
            dl_malloc_consolidate_E818(ms, av);
        goto use_top;
    }

    if (nb <= av->max_fast) {
        fb = &av->fastbins[(nb >> 3) - 2];
        if ((victim = *fb) != 0) {
            *fb = victim->fd;
            return (char*)victim + 8;
        }
    }

    if (nb < 256) {
        idx = nb >> 3;
        sMallocChunk** base = &av->bins[idx << 1];
        bin = (sMallocChunk*)((char*)base - 8);
        if ((victim = base[1]) != bin) {
            bck = victim->bk;
            ((sMallocChunk*)((char*)victim + nb))->size |= 1;
            base[1] = bck;
            bck->fd = bin;
            return (char*)victim + 8;
        }
    } else {
        idx = dl_largebin_index(nb);
        if (av->max_fast & 2)
            dl_malloc_consolidate_E818(ms, av);
    }

    while ((victim = BIN_AT_31E818(av, 1)->bk) != BIN_AT_31E818(av, 1)) {
        bck = victim->bk;
        size = victim->size & ~3U;

        if (nb < 256 && bck == BIN_AT_31E818(av, 1) && victim == av->last_remainder && size > nb + 16) {
            remainder_size = size - nb;
            remainder = (sMallocChunk*)((char*)victim + nb);
            av->bins[3] = av->bins[2] = remainder;
            av->last_remainder = remainder;
            remainder->bk = remainder->fd = BIN_AT_31E818(av, 1);
            victim->size = nb | 1;
            remainder->size = remainder_size | 1;
            ((sMallocChunk*)((char*)remainder + remainder_size))->prev_size = remainder_size;
            return (char*)victim + 8;
        }

        BIN_AT_31E818(av, 1)->bk = bck;
        bck->fd = BIN_AT_31E818(av, 1);

        if (size == nb) {
            ((sMallocChunk*)((char*)victim + size))->size |= 1;
            return (char*)victim + 8;
        }

        if (size < 256) {
            victim_index = size >> 3;
            sMallocChunk** base = &av->bins[victim_index << 1];
            bck = (sMallocChunk*)((char*)base - 8);
            fwd = base[0];
        } else {
            victim_index = dl_largebin_index(size);
            sMallocChunk** base = &av->bins[victim_index << 1];
            bck = (sMallocChunk*)((char*)base - 8);
            fwd = base[0];
            if (fwd != bck) {
                if (size < bck->bk->size) {
                    fwd = bck;
                    bck = base[1];
                } else if (size >= 256) {
                    size |= 1;
                    while (size < fwd->size)
                        fwd = fwd->fd;
                    bck = fwd->bk;
                }
            }
        }

        av->binmap[victim_index >> 5] |= 1U << (victim_index & 31);
        victim->bk = bck;
        victim->fd = fwd;
        fwd->bk = victim;
        bck->fd = victim;
    }

    if (!(nb < 256)) {
        sMallocChunk** base = &av->bins[idx << 1];
        bin = (sMallocChunk*)((char*)base - 8);
        for (victim = base[1]; victim != bin; victim = victim->bk) {
            size = victim->size & ~3U;
            if (size >= nb) {
                remainder_size = size - nb;
                fwd = victim->fd;
                bck = victim->bk;
                fwd->bk = bck;
                bck->fd = fwd;
                void* mem = (char*)victim + 8;
                if (remainder_size < 16) {
                    ((sMallocChunk*)((char*)victim + size))->size |= 1;
                    return mem;
                } else {
                    remainder = (sMallocChunk*)((char*)victim + nb);
                    av->bins[3] = av->bins[2] = remainder;
                    remainder->bk = remainder->fd = BIN_AT_31E818(av, 1);
                    victim->size = nb | 1;
                    remainder->size = remainder_size | 1;
                    ((sMallocChunk*)((char*)remainder + remainder_size))->prev_size = remainder_size;
                    return mem;
                }
            }
        }
    }

    ++idx;
    bin = BIN_AT_31E818(av, idx);
    block = idx >> 5;
    map = av->binmap[block];
    bit = 1U << (idx & 31);

    for (;;) {
        if (bit > map || bit == 0) {
            do {
                if (++block >= 3)
                    goto use_top;
            } while ((map = av->binmap[block]) == 0);
            bin = BIN_AT_31E818(av, block << 5);
            bit = 1;
        }

        while ((bit & map) == 0) {
            bin = (sMallocChunk*)((char*)bin + 8);
            bit <<= 1;
        }

        victim = bin->bk;
        if (victim == bin) {
            av->binmap[block] = map &= ~bit;
            bin = (sMallocChunk*)((char*)bin + 8);
            bit <<= 1;
        } else {
            size = victim->size & ~3U;
            remainder_size = size - nb;
            bck = victim->bk;
            bin->bk = bck;
            bck->fd = bin;
            if (remainder_size < 16) {
                ((sMallocChunk*)((char*)victim + size))->size |= 1;
                return (char*)victim + 8;
            } else {
                remainder = (sMallocChunk*)((char*)victim + nb);
                av->bins[3] = av->bins[2] = remainder;
                remainder->bk = remainder->fd = BIN_AT_31E818(av, 1);
                if (nb < 256)
                    av->last_remainder = remainder;
                victim->size = nb | 1;
                remainder->size = remainder_size | 1;
                ((sMallocChunk*)((char*)remainder + remainder_size))->prev_size = remainder_size;
                return (char*)victim + 8;
            }
        }
    }

use_top:
    victim = av->top;
    size = victim->size & ~3U;
    if (size >= nb + 16) {
        remainder_size = size - nb;
        remainder = (sMallocChunk*)((char*)victim + nb);
        av->top = remainder;
        victim->size = nb | 1;
        remainder->size = remainder_size | 1;
        return (char*)victim + 8;
    }
    return dl_sysmalloc_E818(ms, nb, av);
}

//100%
// dlmalloc 2.7 free()



extern "C" void dl_malloc_consolidate(void* ms, sMallocState* av);
extern "C" int dl_systrim(void* ms, unsigned int pad, sMallocState* av);

// PORT: the unit declares dl_free(void*); the body really takes (ms, mem).
extern "C" void dl_free_free(sMemHeap* ms, void* mem) __asm__("dl_free");

extern "C" void dl_free_free(sMemHeap* ms, void* mem)
{
    sMallocState* av = ms->av;
    sMallocChunk* p;
    sMallocChunk* nextchunk;
    unsigned int size;
    unsigned int nextsize;
    unsigned int prevsize;
    int nextinuse;
    sMallocChunk* bck;
    sMallocChunk* fwd;
    sMallocChunk** fb;

    // PORT: chunk header reads go through (int)mem - 8 (pointer in int) to match gcc 2.95 offset folding
    if (mem != 0)
    {
        size = ((sMallocChunk*)((int)mem - 8))->size & ~3U;
        p = (sMallocChunk*)((char*)mem - 8);
        if (size <= av->max_fast)
        {
            av->max_fast |= 3;
            fb = &av->fastbins[(size >> 3) - 2];
            *(sMallocChunk**)mem = *fb;
            *fb = p;
        }
        else if (!(((sMallocChunk*)((int)mem - 8))->size & 2))
        {
            av->max_fast |= 1;
            nextchunk = (sMallocChunk*)((char*)p + size);
            nextsize = nextchunk->size & ~3U;
            if (!(((sMallocChunk*)((int)mem - 8))->size & 1))
            {
                prevsize = p->prev_size;
                size += prevsize;
                p = (sMallocChunk*)((char*)p - (long)prevsize);
                fwd = p->fd;
                bck = p->bk;
                fwd->bk = bck;
                bck->fd = fwd;
            }
            if (nextchunk != av->top)
            {
                nextinuse = ((sMallocChunk*)((char*)nextchunk + nextsize))->size & 1;
                nextchunk->size = nextsize;
                if (!nextinuse)
                {
                    fwd = nextchunk->fd;
                    bck = nextchunk->bk;
                    fwd->bk = bck;
                    bck->fd = fwd;
                    size += nextsize;
                }
                fwd = ((sMallocChunk*)((char*)&av->bins[1 << 1] - 8))->fd;
                p->bk = (sMallocChunk*)((char*)&av->bins[1 << 1] - 8);
                p->fd = fwd;
                ((sMallocChunk*)((char*)&av->bins[1 << 1] - 8))->fd = p;
                fwd->bk = p;
                p->size = size | 1;
                ((sMallocChunk*)((char*)p + size))->prev_size = size;
            }
            else
            {
                size += nextsize;
                p->size = size | 1;
                av->top = p;
            }
            if (size >= 0x4000)
            {
                if (av->max_fast & 2)
                    dl_malloc_consolidate(ms, (sMallocState*)av);
                if ((av->top->size & ~3U) >= av->trim_threshold)
                    dl_systrim(ms, av->top_pad, (sMallocState*)av);
            }
        }
    }
}

//100%
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t/uint64_t off-PS2.
void dl_malloc_init_state(void* av);

// dlmalloc 2.7 malloc_consolidate()


extern "C" void dl_malloc_consolidate(void* ms, sMallocState* av)
{
    sMallocChunk** fb;
    sMallocChunk** maxfb;
    sMallocChunk* p;
    sMallocChunk* nextp;
    sMallocChunk* unsorted_bin;
    sMallocChunk* first_unsorted;
    sMallocChunk* nextchunk;
    unsigned int size;
    unsigned int nextsize;
    unsigned int prevsize;
    int nextinuse;
    sMallocChunk* bck;
    sMallocChunk* fwd;

    if (av->max_fast != 0) {
        av->max_fast &= ~2U;
        unsorted_bin = (sMallocChunk*)((char*)&av->bins[1 << 1] - 8);
        maxfb = &av->fastbins[(av->max_fast >> 3) - 2];
        fb = &av->fastbins[0];
        do {
            if ((p = *fb) != 0) {
                *fb = 0;
                do {
                    nextp = p->fd;
                    size = p->size & ~1U;
                    nextchunk = (sMallocChunk*)((char*)p + size);
                    nextsize = nextchunk->size & ~3U;
                    if (!(p->size & 1)) {
                        prevsize = p->prev_size;
                        size += prevsize;
                        p = (sMallocChunk*)((char*)p - (long)prevsize);
                        fwd = p->fd;
                        bck = p->bk;
                        fwd->bk = bck;
                        bck->fd = fwd;
                    }
                    if (nextchunk != av->top) {
                        nextinuse = ((sMallocChunk*)((char*)nextchunk + nextsize))->size & 1;
                        nextchunk->size = nextsize;
                        if (!nextinuse) {
                            size += nextsize;
                            fwd = nextchunk->fd;
                            bck = nextchunk->bk;
                            fwd->bk = bck;
                            bck->fd = fwd;
                        }
                        first_unsorted = unsorted_bin->fd;
                        unsorted_bin->fd = p;
                        first_unsorted->bk = p;
                        p->size = size | 1;
                        p->bk = unsorted_bin;
                        p->fd = first_unsorted;
                        ((sMallocChunk*)((char*)p + size))->prev_size = size;
                    } else {
                        size += nextsize;
                        p->size = size | 1;
                        av->top = p;
                    }
                } while ((p = nextp) != 0);
            }
        } while (fb++ != maxfb);
    } else {
        dl_malloc_init_state(av);
    }
}

//100%
// dlmalloc 2.7 realloc() (no mmap support: an mmapped chunk fails with ENOMEM).

extern "C" void func_003E6574(void* d, void* s, int n);

extern "C" void* dl_realloc(void* ms, void* oldmem, unsigned int bytes)
{
    char* av = *(char**)ms;
    unsigned int nb;
    sMallocChunk* oldp;
    unsigned int oldsize;
    sMallocChunk* newp;
    unsigned int newsize;
    char* newmem;
    sMallocChunk* next;
    sMallocChunk* remainder;
    unsigned int remainder_size;
    unsigned int head;

    if (oldmem == 0)
        return dl_malloc(ms, bytes);

    if (bytes >= (unsigned int)-32)
        goto nomem;
    nb = (bytes + 4 + 15 < 16) ? 16 : (bytes + 4 + 15) & ~15;

    head = *(unsigned int*)((char*)oldmem - 4);
    oldp = (sMallocChunk*)((char*)oldmem - 8);
    oldsize = head & ~3;
    if (head & 2)
        goto nomem;

    if (oldsize >= nb) {
        newp = oldp;
        newsize = oldsize;
    } else {
        next = (sMallocChunk*)((char*)oldp + oldsize);
        if (next == *(sMallocChunk**)(av + 0x30)) {
            if ((newsize = oldsize + (next->size & ~3)) >= nb + 16) {
                *(unsigned int*)((int)oldmem - 4) = (head & 1) | nb;
                *(sMallocChunk**)(av + 0x30) = (sMallocChunk*)((char*)oldp + nb);
                ((sMallocChunk*)((char*)oldp + nb))->size = (newsize - nb) | 1;
                return oldmem;
            }
        } else if (!(((sMallocChunk*)((char*)next + (next->size & ~1)))->size & 1) &&
                   (newsize = oldsize + (next->size & ~3)) >= nb) {
            sMallocChunk* bck;
            sMallocChunk* fwd;
            newp = oldp;
            fwd = next->fd;
            bck = next->bk;
            fwd->bk = bck;
            bck->fd = fwd;
            goto split;
        }

        newmem = (char*)dl_malloc(ms, nb - 15);
        if (newmem == 0)
            return 0;
        newp = (sMallocChunk*)(newmem - 8);
        newsize = *(unsigned int*)(newmem - 4) & ~3;
        if (newp == next) {
            newsize += oldsize;
            newp = oldp;
        } else {
            unsigned int copysize = oldsize - 4;
            unsigned int* sp = (unsigned int*)oldmem;
            unsigned int* dp = (unsigned int*)newmem;
            unsigned int ncopies = copysize / 4;
            if (ncopies > 9) {
                func_003E6574(dp, sp, copysize);
            } else {
                dp[0] = sp[0];
                dp[1] = sp[1];
                dp[2] = sp[2];
                if (ncopies > 4) {
                    dp[3] = sp[3];
                    dp[4] = sp[4];
                    if (ncopies > 6) {
                        dp[5] = sp[5];
                        dp[6] = sp[6];
                        if (ncopies > 8) {
                            dp[7] = sp[7];
                            dp[8] = sp[8];
                        }
                    }
                }
            }
            dl_free_E2D8(ms, oldmem);
            return (char*)newp + 8;
        }
    }

split:
    remainder_size = newsize - nb;
    if (remainder_size < 16) {
        newp->size = (newp->size & 1) | newsize;
        ((sMallocChunk*)((char*)newp + newsize))->size |= 1;
    } else {
        remainder = (sMallocChunk*)((char*)newp + nb);
        newp->size = (newp->size & 1) | nb;
        remainder->size = remainder_size | 1;
        ((sMallocChunk*)((char*)remainder + remainder_size))->size |= 1;
        dl_free_E2D8(ms, (char*)remainder + 8);
    }
    return (char*)newp + 8;

nomem:
    *func_00415FB8() = 12;
    return 0;
}

//100%
// dlmalloc 2.7 memalign().
extern "C" void* dl_memalign_impl(void* ms, unsigned int alignment, unsigned int bytes) __asm__("dl_memalign");
extern "C" void* dl_memalign_impl(void* ms, unsigned int alignment, unsigned int bytes)
{
    unsigned int nb;
    char* m;
    char* p;
    char* brk;
    char* newp;
    unsigned int newsize;
    unsigned int leadsize;
    unsigned int size;
    unsigned int req;
    unsigned int head;

    if (alignment <= 16)
        return dl_malloc(ms, bytes);

    if (alignment < 16)
        alignment = 16;

    if ((alignment & (alignment - 1)) != 0) {
        unsigned int a = 32;
        while (a < alignment)
            a <<= 1;
        alignment = a;
    }

    req = bytes;
    if (req >= (unsigned int)-32) {
        *func_00415FB8() = 12;
        return 0;
    }
    nb = (req + 4 + 15 < 16) ? 16 : (req + 4 + 15) & ~15;

    m = (char*)dl_malloc(ms, nb + alignment + 16);
    if (m == 0)
        return 0;

    p = m - 8;

    if ((unsigned int)(m) % alignment != 0) {
        brk = (char*)(((unsigned int)(m + alignment - 1)) & -alignment) - 8;
        if ((unsigned int)(brk - p) < 16)
            brk += alignment;

        newp = brk;
        leadsize = brk - p;
        head = *(unsigned int*)((int)m - 4);
        newsize = (head & ~3) - leadsize;

        if (head & 2) {
            *(unsigned int*)newp = *(unsigned int*)((int)m - 8) + leadsize;
            *(unsigned int*)(newp + 4) = newsize | 2;
            return newp + 8;
        }

        *(unsigned int*)(newp + 4) = newsize | 1;
        *(unsigned int*)(newp + newsize + 4) |= 1;
        *(unsigned int*)((int)m - 4) = (*(unsigned int*)((int)m - 4) & 1) | leadsize;
        dl_free_E2D8(ms, m);
        p = newp;
    }

    if (!(*(unsigned int*)(p + 4) & 2)) {
        size = *(unsigned int*)(p + 4) & ~3;
        if (size > nb + 16) {
            char* remainder = p + nb;
            *(unsigned int*)(remainder + 4) = (size - nb) | 1;
            *(unsigned int*)(p + 4) = (*(unsigned int*)(p + 4) & 1) | nb;
            dl_free_E2D8(ms, remainder + 8);
        }
    }
    return p + 8;
}

//100%
// dlmalloc 2.7 memalign() with an offset: returns memory where (mem + offset) is aligned.
extern "C" void* dl_memalign_offset_impl(void* ms, unsigned int alignment, unsigned int bytes, unsigned int offset) __asm__("dl_memalign_offset");
extern "C" void* dl_memalign_offset_impl(void* ms, unsigned int alignment, unsigned int bytes, unsigned int offset)
{
    unsigned int nb;
    char* m;
    char* p;
    char* brk;
    char* newp;
    unsigned int newsize;
    unsigned int leadsize;
    unsigned int size;
    unsigned int req;
    unsigned int head;

    if (alignment <= 16)
        return dl_malloc(ms, bytes);

    if (alignment < 16)
        alignment = 16;

    if ((alignment & (alignment - 1)) != 0) {
        unsigned int a = 32;
        while (a < alignment)
            a <<= 1;
        alignment = a;
    }

    req = bytes + offset;
    if (req >= (unsigned int)-32) {
        *func_00415FB8() = 12;
        return 0;
    }
    nb = (req + 4 + 15 < 16) ? 16 : (req + 4 + 15) & ~15;

    m = (char*)dl_malloc(ms, nb + alignment + 16);
    if (m == 0)
        return 0;

    p = m - 8;

    if ((unsigned int)(m + offset) % alignment != 0) {
        brk = (char*)(((unsigned int)(m + offset + alignment - 1)) & -alignment) - offset - 8;
        if ((unsigned int)(brk - p) < 16)
            brk += alignment;

        newp = brk;
        leadsize = brk - p;
        head = *(unsigned int*)((int)m - 4);
        newsize = (head & ~3) - leadsize;

        if (head & 2) {
            *(unsigned int*)newp = *(unsigned int*)((int)m - 8) + leadsize;
            *(unsigned int*)(newp + 4) = newsize | 2;
            return newp + 8;
        }

        *(unsigned int*)(newp + 4) = newsize | 1;
        *(unsigned int*)(newp + newsize + 4) |= 1;
        *(unsigned int*)((int)m - 4) = (*(unsigned int*)((int)m - 4) & 1) | leadsize;
        dl_free_E2D8(ms, m);
        p = newp;
    }

    if (!(*(unsigned int*)(p + 4) & 2)) {
        size = *(unsigned int*)(p + 4) & ~3;
        if (size > nb + 16) {
            char* remainder = p + nb;
            *(unsigned int*)(remainder + 4) = (size - nb) | 1;
            *(unsigned int*)(p + 4) = (*(unsigned int*)(p + 4) & 1) | nb;
            dl_free_E2D8(ms, remainder + 8);
        }
    }
    return p + 8;
}

//100%
// dlmalloc calloc: allocate n * size bytes and clear them (unrolled for small chunks).
extern "C" void func_003E6448(void* p, int v, int n);

extern "C" void* dl_calloc(void* ms, unsigned int n, unsigned int size)
{
    unsigned int* d = (unsigned int*)dl_malloc(ms, n * size);
    if (d != 0) {
        unsigned int head = d[-1];
        if (!(head & 2)) {
            unsigned int clearsize = (head & ~3) - 4;
            unsigned int nclears = clearsize / 4;
            if (nclears > 9) {
                func_003E6448(d, 0, clearsize);
            } else {
                d[0] = 0;
                d[1] = 0;
                d[2] = 0;
                if (nclears > 4) {
                    d[3] = 0;
                    d[4] = 0;
                    if (nclears > 6) {
                        d[5] = 0;
                        d[6] = 0;
                        if (nclears > 8) {
                            d[7] = 0;
                            d[8] = 0;
                        }
                    }
                }
            }
        } else {
            func_003E6448(d, 0, (head & ~3) - 8);
        }
    }
    return d;
}

extern "C" int dl_free(void* self);

extern "C" int dl_cfree(void* self)
{
    return dl_free(self);
}

extern "C" void dl_ialloc(void* a, void* b, void* c, int d, int e);

extern "C" void dl_independent_calloc(void* a, void* b, int c, int e)
{
    int v = c;
    dl_ialloc(a, b, &v, 3, e);
}

extern "C" void dl_independent_comalloc(void* a, void* b, void* c, int e)
{
    dl_ialloc(a, b, c, 0, e);
}

//100%
// dlmalloc 2.7 independent_calloc/comalloc core (iALLOc): carve n chunks out of one allocation.
#define REQ2SIZE_31F858(req) (((req) + 4 + 15 < 16) ? 16 : ((req) + 4 + 15) & ~15)

extern "C" void** dl_ialloc_impl(void* ms, unsigned int n_elements, unsigned int* sizes, int opts, void** chunks) __asm__("dl_ialloc");
extern "C" void** dl_ialloc_impl(void* ms, unsigned int n_elements, unsigned int* sizes, int opts, void** chunks)
{
    char* av = *(char**)ms;
    unsigned int element_size;
    unsigned int contents_size;
    unsigned int array_size;
    char* mem;
    char* p;
    unsigned int remainder_size;
    void** marray;
    char* array_chunk;
    int mmx;
    unsigned int size;
    unsigned int i;

    if (*(unsigned int*)av == 0)
        dl_malloc_consolidate(ms, (sMallocState*)av);

    if (chunks != 0) {
        if (n_elements == 0)
            return chunks;
        marray = chunks;
        array_size = 0;
    } else {
        if (n_elements == 0)
            return (void**)dl_malloc(ms, 0);
        marray = 0;
        array_size = REQ2SIZE_31F858(n_elements * sizeof(void*));
    }

    if (opts & 1) {
        element_size = REQ2SIZE_31F858(*sizes);
        contents_size = n_elements * element_size;
    } else {
        element_size = 0;
        contents_size = 0;
        for (i = 0; i != n_elements; ++i)
            contents_size += REQ2SIZE_31F858(sizes[i]);
    }

    size = contents_size + array_size - 15;

    mmx = *(int*)(av + 0x354);
    *(int*)(av + 0x354) = 0;
    mem = (char*)dl_malloc(ms, size);
    *(int*)(av + 0x354) = mmx;
    if (mem == 0)
        return 0;

    remainder_size = *(unsigned int*)(mem - 4) & ~3;
    p = mem - 8;

    if (opts & 2)
        func_003E6448(mem, 0, remainder_size - 4 - array_size);

    if (marray == 0) {
        array_chunk = p + contents_size;
        marray = (void**)(array_chunk + 8);
        *(unsigned int*)(array_chunk + 4) = (remainder_size - contents_size) | 1;
        remainder_size = contents_size;
    }

    for (i = 0; ; ++i) {
        marray[i] = p + 8;
        if (i != n_elements - 1) {
            if (element_size != 0)
                size = element_size;
            else
                size = REQ2SIZE_31F858(sizes[i]);
            remainder_size -= size;
            *(unsigned int*)(p + 4) = size | 1;
            p = p + size;
        } else {
            *(unsigned int*)(p + 4) = remainder_size | 1;
            break;
        }
    }
    return marray;
}


extern "C" void* dl_memalign_3(void* ms, unsigned int alignment, unsigned int bytes) __asm__("dl_memalign");

// dlmalloc 2.7 vALLOc(): memalign to the page size, consolidating first if needed.
extern "C" void* dl_valloc(void* ms, unsigned int bytes)
{
    sMallocState* av = *(sMallocState**)ms;
    if (av->max_fast == 0)
        dl_malloc_consolidate(ms, (sMallocState*)av);
    return dl_memalign_3(ms, av->pagesize, bytes);
}

// dlmalloc 2.7 pVALLOc(): vALLOc() of bytes rounded up to a whole page.
extern "C" void* dl_pvalloc(void* ms, unsigned int bytes)
{
    sMallocState* av = *(sMallocState**)ms;
    if (av->max_fast == 0)
        dl_malloc_consolidate(ms, (sMallocState*)av);
    unsigned int pagesz = av->pagesize;
    return dl_memalign_3(ms, pagesz, (bytes + pagesz - 1) & -pagesz);
}

// dlmalloc 2.7 mTRIm(): consolidate, then give memory above pad back.
extern "C" int dl_malloc_trim(void* ms, unsigned int pad)
{
    sMallocState* av = *(sMallocState**)ms;
    dl_malloc_consolidate(ms, (sMallocState*)av);
    return dl_systrim(ms, pad, (sMallocState*)av);
}

//100%
unsigned int dl_malloc_usable_size(void* self, void* mem)
{
    if (mem != 0) {
        unsigned int size = *(unsigned int*)((char*)mem - 4);
        char* p = (char*)mem - 8;
        if (size & 2) {
            return (size & ~3U) - 8;
        } else if (*(unsigned int*)(p + (size & ~1U) + 4) & 1) {
            return (size & ~3U) - 4;
        }
    }
    return 0;
}

//100%
// dlmalloc 2.7 mALLINFo()



extern "C" void dl_malloc_consolidate(void* ms, sMallocState* av);

extern "C" sMallinfo dl_mallinfo(void* ms)
{
    sMallocState* av = *(sMallocState**)ms;
    sMallinfo mi;
    int i;
    sMallocChunk* b;
    sMallocChunk* p;
    unsigned int avail;
    unsigned int fastavail;
    int nblocks;
    int nfastblocks;

    if (av->top == 0) {
        dl_malloc_consolidate(ms, (sMallocState*)av);
    }

    avail = av->top->size & ~3U;
    nblocks = 1;

    nfastblocks = 0;
    fastavail = 0;

    for (i = 0; (unsigned int)i < 11U; ++i) {
        for (p = av->fastbins[i]; p != 0; p = p->fd) {
            ++nfastblocks;
            fastavail += p->size & ~3U;
        }
    }

    avail += fastavail;

    for (i = 1; i < 96; ++i) {
        sMallocChunk** bp = &av->bins[i << 1];
        b = (sMallocChunk*)((char*)bp - 8);
        for (p = bp[1]; p != b; p = p->bk) {
            ++nblocks;
            avail += p->size & ~3U;
            if (p == p->bk->bk) break;
            if (p == p->bk && p != b) break;
        }
    }

    mi.smblks = nfastblocks;
    mi.ordblks = nblocks;
    mi.fordblks = avail;
    mi.uordblks = av->sbrked_mem - avail;
    mi.arena = av->sbrked_mem;
    mi.hblks = av->n_mmaps;
    mi.hblkhd = av->mmapped_mem;
    mi.fsmblks = fastavail;
    mi.keepcost = av->top->size & ~3U;
    mi.usmblks = av->max_total_mem;
    return mi;
}

extern "C" void func_0031FE28()
{
}

//100%
void dl_malloc_consolidate_c(void* ms, char* av) __asm__("dl_malloc_consolidate");

extern "C" int dl_mallopt(void** ms, int which, unsigned int val)
{
    char* s = (char*)*ms;
    dl_malloc_consolidate_c(ms, s);
    switch (which) {
    case 1: {
        // dlmalloc mallopt(M_MXFAST): set_max_fast(av, request2size(val))
        if (val <= 0x50) {
            *(unsigned int*)s = ((val == 0) ? 8
                : ((val + 0x13 < 0x10) ? 0x10 : (val + 0x13) & ~0xF))
                | (*(unsigned int*)s & 3);
            return 1;
        }
        return 0;
    }
    case -1:
        *(unsigned int*)(s + 0x344) = val;
        return 1;
    case -2:
        *(unsigned int*)(s + 0x348) = val;
        return 1;
    case -3:
        *(unsigned int*)(s + 0x34C) = val;
        return 1;
    case -4:
        if (val != 0)
            return 0;
        *(unsigned int*)(s + 0x354) = 0;
        return 1;
    case 0:
        break;
    }
    return 0;
}

//100%
void* cMemHeap_cMemHeap(void* self)
{
    sMemHeap* heap = (sMemHeap*)self;
    heap->base = 0;
    heap->brk = 0;
    heap->size = 0;
    heap->av = 0;
    return self;
}

void operator_delete(int* ptr);

//100%
void cMemHeap_delete(void* self, int flags)
{
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern "C" void func_003E6448(void* dst, int c, int n);

// Put the heap over [base, base + size): a cleared malloc_state at the
// 16-aligned start, and the rest as the region cMemHeap_sbrk hands out.
extern "C" void cMemHeap_init(void* self, unsigned int base, unsigned int size)
{
    sMemHeap* heap = (sMemHeap*)self;
    unsigned int start = (base + 0xF) & 0xFFFFFFF0;
    heap->base = (char*)start;
    heap->av = (sMallocState*)start;
    heap->size = (size - (start - base)) & 0xFFFFFFF0;
    func_003E6448((void*)start, 0, sizeof(sMallocState));
    heap->base += 0x380;
    heap->size -= 0x380;
    heap->brk = heap->base;
}

//100%
// MORECORE for dlmalloc: move heap->brk (0x8) by incr inside [base, base + size)
// (0x4, 0xC); returns the old break, or -1 when the region is full.
extern "C" unsigned int cMemHeap_sbrk(void* self, long incr) // PORT: 64-bit long param
{
    if (incr >= 0) {
        unsigned int old = *(unsigned int*)((char*)self + 0x8);
        unsigned int top = old + incr;
        if (top <= *(unsigned int*)((char*)self + 0x4) + *(unsigned int*)((char*)self + 0xC)) {
            *(unsigned int*)((char*)self + 0x8) = top;
            return old;
        }
    } else {
        return *(unsigned int*)((char*)self + 0x8) += incr;
    }
    return 0xFFFFFFFF;
}

extern "C" int dl_memalign(void* self);

extern "C" void* dl_malloc(void* ms, unsigned int bytes);

extern "C" void* cMemHeap_malloc(void* ms, unsigned int bytes)
{
    return dl_malloc(ms, bytes);
}

//99.29%
int cMemHeap_memalign(void* self)
{
    return dl_memalign(self);
}

extern "C" int dl_memalign_offset(void* self);

//99.29%
int cMemHeap_memalignOffset(void* self)
{
    return dl_memalign_offset(self);
}

extern "C" int dl_free(void* self);

// Whether p lies inside the heap region (heap->base at 0x4, heap->size at 0xC), exclusive at base.
int cMemHeap_contains(void* self, unsigned int p)
{
    unsigned int base = *(unsigned int*)((char*)self + 0x4);
    unsigned int end = base + *(unsigned int*)((char*)self + 0xC);
    return base < p && p < end;
}

//100%
int cMemHeap_free(void* self)
{
    return dl_free(self);
}

extern "C" void func_003200E0()
{
}

//100%
void* cMemPool8_init(void* self)
{
    *(void**)((char*)self + 0x800) = self;
    char* p = (char*)self;
    char* next = (char*)self + 8;
    for (unsigned int i = 0; i < 0xFF; i++) {
        *(void**)p = next;
        p += 8;
        next += 8;
    }
    *(int*)((char*)self + 0x7F8) = 0;
    return self;
}

//100%
void* cMemPool16_init(void* self)
{
    *(void**)((char*)self + 0x2000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x10;
    for (unsigned int i = 0; i < 0x1FF; i++) {
        *(void**)p = next;
        p += 0x10;
        next += 0x10;
    }
    *(int*)((char*)self + 0x1FF0) = 0;
    return self;
}

//100%
void* cMemPool32_init(void* self)
{
    *(void**)((char*)self + 0x6000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x20;
    for (unsigned int i = 0; i < 0x2FF; i++) {
        *(void**)p = next;
        p += 0x20;
        next += 0x20;
    }
    *(int*)((char*)self + 0x5FE0) = 0;
    return self;
}

//100%
void* cMemPool64_init(void* self)
{
    unsigned int i = 0;
    *(void**)((char*)self + 0x32000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x40;
    for (; i < 0xC7F; i++) {
        *(void**)p = next;
        p += 0x40;
        next += 0x40;
    }
    *(int*)((char*)self + 0x31FC0) = 0;
    return self;
}

//100%
void* cMemPool128_init(void* self)
{
    unsigned int i = 0;
    *(void**)((char*)self + 0x25800) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x80;
    for (; i < 0x4AF; i++) {
        *(void**)p = next;
        p += 0x80;
        next += 0x80;
    }
    *(int*)((char*)self + 0x25780) = 0;
    return self;
}

//100%
void* cMemPool256_init(void* self)
{
    unsigned int i = 0;
    *(void**)((char*)self + 0x20000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x100;
    for (; i < 0x1FF; i++) {
        *(void**)p = next;
        p += 0x100;
        next += 0x100;
    }
    *(int*)((char*)self + 0x1FF00) = 0;
    return self;
}

//100%
void* cMemPool512_init(void* self)
{
    unsigned int i = 0;
    *(void**)((char*)self + 0x20000) = self;
    char* p = (char*)self;
    char* next = (char*)self + 0x200;
    for (; i < 0xFF; i++) {
        *(void**)p = next;
        p += 0x200;
        next += 0x200;
    }
    *(int*)((char*)self + 0x1FE00) = 0;
    return self;
}

extern "C" void* cMemBlockMan_alloc(int size);

//100%
void* cMemPool8_alloc(void* self)
{
    void* node = *(void**)((char*)self + 0x800);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x800) = next;
        return node;
    }
    return cMemBlockMan_alloc(0xC);
}

//100%
void* cMemPool16_alloc(void* self)
{
    void* node = *(void**)((char*)self + 0x2000);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x2000) = next;
        return node;
    }
    return cMemBlockMan_alloc(0x14);
}

//100%
void* cMemPool32_alloc(void* self)
{
    void* node = *(void**)((char*)self + 0x6000);
    if (node != 0) {
        void* next = *(void**)node;
        *(void**)((char*)self + 0x6000) = next;
        return node;
    }
    return cMemBlockMan_alloc(0x24);
}

//100%
static inline void* popFreeNode(void** head)
{
    void* node = *head;
    *head = *(void**)node;
    return node;
}

void* cMemPool64_alloc(void* self)
{
    if (*(void**)((char*)self + 0x32000) != 0) {
        return popFreeNode((void**)((char*)self + 0x32000));
    }
    return cMemBlockMan_alloc(0x44);
}

//100%
void* cMemPool128_alloc(void* self)
{
    if (*(void**)((char*)self + 0x25800) != 0) {
        return popFreeNode((void**)((char*)self + 0x25800));
    }
    return cMemBlockMan_alloc(0x84);
}

//92.5%
INCLUDE_ASM("bx/cubicspline", cMemPool256_alloc__FPv);

//92.5%
INCLUDE_ASM("bx/cubicspline", cMemPool512_alloc__FPv);

//100%
void cMemPool8_free(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x800);
    *(void**)((char*)self + 0x800) = node;
}

//100%
void cMemPool16_free(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x2000);
    *(void**)((char*)self + 0x2000) = node;
}

//100%
void cMemPool32_free(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x6000);
    *(void**)((char*)self + 0x6000) = node;
}

//100%
void cMemPool64_free(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x32000);
    *(void**)((char*)self + 0x32000) = node;
}

//100%
void cMemPool128_free(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x25800);
    *(void**)((char*)self + 0x25800) = node;
}

//100%
void cMemPool256_free(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x20000);
    *(void**)((char*)self + 0x20000) = node;
}

//100%
void cMemPool512_free(void* self, void** node)
{
    *node = *(void**)((char*)self + 0x20000);
    *(void**)((char*)self + 0x20000) = node;
}

//100%
void cMemPool8_purge(void)
{
}

//100%
void cMemPool16_purge(void)
{
}

//100%
void cMemPool32_purge(void)
{
}

//100%
void cMemPool64_purge(void)
{
}

//100%
void cMemPool128_purge(void)
{
}

//100%
void cMemPool256_purge(void)
{
}

//100%
void cMemPool512_purge(void)
{
}

//100%
void* func_00316A00(void* self);
void* func_00317930(void* self);
void* cMemHeap_cMemHeap(void* self);
void cMemHeap_delete(void* self, int flags);

inline void* operator new(unsigned int, void* p) { return p; }

struct sV2_0550 {
    float x, y;
    sV2_0550(const float& ax, const float& ay) : x(ax), y(ay) {}
};
struct sV3_0550 {
    float x, y, z;
    sV3_0550(const float& ax, const float& ay, const float& az) : x(ax), y(ay), z(az) {}
};
struct sV4_0550 {
    float x, y, z, w;
    sV4_0550(const float& ax, const float& ay, const float& az, const float& aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));
struct sQ_0550 {
    float x, y, z, w;
    sQ_0550(const float& ax, const float& ay, const float& az, const float& aw)
    {
        w = aw;
        x = ax;
        y = ay;
        z = az;
    }
} __attribute__((aligned(16)));
struct sM33_0550 {
    float m[3][3];
    sM33_0550()
    {
        m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f;
        m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
    }
};
struct sM44_0550 {
    float m[4][4];
    sM44_0550(float d)
    {
        m[0][0] = d;    m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
        m[0][1] = 0.0f; m[1][1] = d;    m[2][1] = 0.0f; m[3][1] = 0.0f;
        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = d;    m[3][2] = 0.0f;
        m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3] = d;
    }
};
struct sXf_0550 {
    sV4_0550 a;
    sQ_0550 b;
    sXf_0550(const sV4_0550& aa, const sQ_0550& ab) : a(aa), b(ab) {}
};

extern char D_004FF000[];
extern char D_004FF018[];
extern char D_004FF030[];
extern char D_004FF048[], D_004FF058[], D_004FF068[], D_004FF078[], D_004FF088[], D_004FF098[], D_004FF0A8[], D_004FF0B8[], D_004FF0C8[];
extern char D_004A5958;
extern void* D_004A3E94;
extern char D_004A5960[], D_004A5968[], D_004A5970[];
extern char D_004FF0D8[], D_004FF0E8[], D_004FF0F8[], D_004FF108[];
extern char D_004FF120[], D_004FF130[], D_004FF140[], D_004FF150[], D_004FF160[];
extern char D_004FF170[], D_004FF1A0[], D_004FF1E0[], D_004FF220[], D_004FF230[], gMemHeap[];

extern "C" void func_00320550(int init, int prio)
{
    if (prio == 0xFFFF) {
        if (init != 0) {
            func_00316A00(D_004FF000);
            func_00317930(D_004FF018);
            func_00317930(D_004FF030);
            new (D_004FF048) sV3_0550(1.0f, 0.0f, 0.0f);
            new (D_004FF058) sV3_0550(0.0f, 0.0f, 1.0f);
            new (D_004FF068) sV3_0550(1.0f, 1.0f, 0.0f);
            new (D_004FF078) sV3_0550(1.0f, 0.0f, 1.0f);
            new (D_004FF088) sV3_0550(0.0f, 1.0f, 0.0f);
            new (D_004FF098) sV3_0550(1.0f, 0.5f, 0.0f);
            new (D_004FF0A8) sV3_0550(0.0f, 0.0f, 0.0f);
            new (D_004FF0B8) sV3_0550(1.0f, 1.0f, 1.0f);
            new (D_004FF0C8) sV3_0550(0.25f, 0.25f, 0.25f);
            D_004A3E94 = &D_004A5958;
            new (D_004A5960) sV2_0550(0.0f, 0.0f);
            new (D_004A5968) sV2_0550(1.0f, 0.0f);
            new (D_004A5970) sV2_0550(0.0f, 1.0f);
            new (D_004FF0D8) sV3_0550(0.0f, 0.0f, 0.0f);
            new (D_004FF0E8) sV3_0550(1.0f, 0.0f, 0.0f);
            new (D_004FF0F8) sV3_0550(0.0f, 1.0f, 0.0f);
            new (D_004FF108) sV3_0550(0.0f, 0.0f, 1.0f);
            new (D_004FF120) sV4_0550(0.0f, 0.0f, 0.0f, 0.0f);
            new (D_004FF130) sV4_0550(0.0f, 0.0f, 0.0f, 1.0f);
            new (D_004FF140) sV4_0550(1.0f, 0.0f, 0.0f, 0.0f);
            new (D_004FF150) sV4_0550(0.0f, 1.0f, 0.0f, 0.0f);
            new (D_004FF160) sV4_0550(0.0f, 0.0f, 1.0f, 0.0f);
            new (D_004FF170) sM33_0550();
            new (D_004FF1A0) sM44_0550(1.0f);
            new (D_004FF1E0) sM44_0550(0.0f);
            new (D_004FF220) sQ_0550(0.0f, 0.0f, 0.0f, 1.0f);
            new (D_004FF230) sXf_0550(*(sV4_0550*)D_004FF130, *(sQ_0550*)D_004FF220);
            cMemHeap_cMemHeap(gMemHeap);
        } else {
            cMemHeap_delete(gMemHeap, 2);
        }
    }
}
