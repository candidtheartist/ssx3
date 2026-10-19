#include "common.h"

//100%
extern void* D_00538B00[16];
extern char D_004FF250[];
extern unsigned int D_004A3EBC;
extern unsigned int D_004A3EC0;
extern int D_004A3EB8;
extern "C" void func_003E5698(void* mutex);
extern "C" void cMemHeap_init(void* heap, unsigned int base, unsigned int size);
extern "C" void cMemBlockMan_initialize(void);

extern "C" void cMemMan_initialize(unsigned int base, unsigned int size)
{
    func_003E5698(D_00538B00);
    D_004A3EBC = base;
    D_004A3EC0 = size;
    cMemHeap_init(D_004FF250, base, size);
    D_004A3EB8 = 1;
    cMemBlockMan_initialize();
}

//100%
extern "C" void* cMemBlockMan_alloc(unsigned int size);
extern "C" void func_003E6220(void* p, unsigned int n);
extern char D_004FF250[];
// PORT: cMemHeap_memalign__FPv / cMemHeap_memalignOffset__FPv take (heap, align, size); the defining unit declares 1 arg.
void* cMemHeap_memalign_K2(void* heap, unsigned int align, unsigned int size) __asm__("cMemHeap_memalign__FPv");
void* cMemHeap_memalignOffset_K2(void* heap, unsigned int align, unsigned int size) __asm__("cMemHeap_memalignOffset__FPv");

extern "C" void* cMemMan_internalAlloc(unsigned int size, unsigned int align, int flags, int top)
{
    void* p;
    if (top == 0 && size != 0 && size <= 0x200) {
        p = cMemBlockMan_alloc(size);
    } else {
        if (align <= 15)
            align = 16;
        if (top != 0)
            p = cMemHeap_memalignOffset_K2(D_004FF250, align, size);
        else
            p = cMemHeap_memalign_K2(D_004FF250, align, size);
    }
    if (p != 0 && flags < 0)
        func_003E6220(p, size);
    return p;
}

//100%
extern "C" int cMemBlockMan_owns(void* p);
extern "C" void cMemBlockMan_free(void* p);
extern char D_004FF250[];
// PORT: cMemHeap_free__FPv is called with (list, item) here; bind the 2-arg form to that symbol.
int cMemHeap_free_2(void* list, void* item) __asm__("cMemHeap_free__FPv");

extern "C" void cMemMan_internalFree(void* p)
{
    if (p != 0)
    {
        if (cMemBlockMan_owns(p) != 0)
        {
            cMemBlockMan_free(p);
        }
        else
        {
            cMemHeap_free_2(D_004FF250, p);
        }
    }
}

//100%
extern "C" int cMemBlockMan_blockSize(void* self);
void dl_malloc_usable_size(void* list, void* item);
extern char D_004FF250[];

extern "C" void cMemMan_internalBlockSize(void* self)
{
    if (cMemBlockMan_blockSize(self) == 0) {
        dl_malloc_usable_size(D_004FF250, self);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void MUTEX_lock(void* mutex);
extern "C" void MUTEX_unlock(void* mutex);
extern "C" void* func_0041605C(void* dst, const void* src, int n);
extern void* D_00538B00[16];
extern char D_0048DA08[];
// PORT: operator_new__FUi takes (size, tag, flags, align) here.
void* operator_new_K2(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
// PORT: cMemMan_internalBlockSize returns the block size; the unit declares it void.
extern "C" unsigned int cMemMan_internalBlockSize_K2(void* p) __asm__("cMemMan_internalBlockSize");

static inline unsigned int cMemMan_blockSizeK2(void* p)
{
    MUTEX_lock(D_00538B00);
    unsigned int n = cMemMan_internalBlockSize_K2(p);
    MUTEX_unlock(D_00538B00);
    return n;
}

static inline void cMemMan_freeBlockK2(void* p)
{
    MUTEX_lock(D_00538B00);
    cMemMan_internalFree(p);
    MUTEX_unlock(D_00538B00);
}

extern "C" void* cMemMan_internalResizeBlock(void* old, unsigned int size)
{
    void* p = operator_new_K2(size, D_0048DA08, 0x100, 0);
    func_0041605C(p, old, size < cMemMan_blockSizeK2(old) ? size : cMemMan_blockSizeK2(old));
    cMemMan_freeBlockK2(old);
    return p;
}

//100%
extern "C" void MUTEX_lock(void* mutex);
extern "C" void MUTEX_unlock(void* mutex);
extern "C" void cMemBlockMan_purge(void);
extern void* D_00538B00[16];

extern "C" void cMemMan_purge(void)
{
    MUTEX_lock(D_00538B00);
    cMemBlockMan_purge();
    MUTEX_unlock(D_00538B00);
}

extern "C" void func_00319D08()
{
}

//100%
void func_00319D10(void* self)
{
}

//100%
int func_00319D18(void* self)
{
    return 0;
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
void* cMemPool8_init(void* p);
void* cMemPool16_init(void* p);
void* cMemPool32_init(void* p);
void* cMemPool64_init(void* p);
void* cMemPool128_init(void* p);
void* cMemPool256_init(void* p);
void* cMemPool512_init(void* p);
extern const char D_0048DA18[];
extern const char D_0048DA28[];
extern const char D_0048DA38[];
extern const char D_0048DA48[];
extern const char D_0048DA58[];
extern const char D_0048DA68[];
extern const char D_0048DA78[];
extern void* D_004A5B60;
extern void* D_004A5B50;
extern void* D_004A5B5C;
extern void* D_004A5B6C;
extern void* D_004A5B74;
extern void* D_004A5B68;
extern void* D_004A5B58;
extern int D_004A3EC8;

// cMemMan serves allocations of up to 0x200 bytes from seven fixed-size pools
// (8, 16, ... 512-byte slots); each pool keeps its free-slot list head just past
// its slots. An empty pool passes the request on to the next size up; anything
// over 0x200 bytes goes to the dlmalloc heap D_004FF250.
extern "C" void cMemBlockMan_initialize(void)
{
    D_004A5B60 = cMemPool8_init(cMemMan_alloc(0x804, D_0048DA18, 0x1000000, 0));
    D_004A5B50 = cMemPool16_init(cMemMan_alloc(0x2004, D_0048DA28, 0x2000000, 0));
    D_004A5B5C = cMemPool32_init(cMemMan_alloc(0x6004, D_0048DA38, 0x3000000, 0));
    D_004A5B6C = cMemPool64_init(cMemMan_alloc(0x32004, D_0048DA48, 0x4000000, 0));
    D_004A5B74 = cMemPool128_init(cMemMan_alloc(0x25804, D_0048DA58, 0x5000000, 0));
    D_004A5B68 = cMemPool256_init(cMemMan_alloc(0x20004, D_0048DA68, 0x6000000, 0));
    D_004A5B58 = cMemPool512_init(cMemMan_alloc(0x20004, D_0048DA78, 0x7000000, 0));
    D_004A3EC8 = 1;
}

//100%
extern "C" void* cMemMan_internalAlloc(unsigned int size, unsigned int align, int flags, int top);
// PORT: the pool allocators are bound with their real (pool, align) arity; the
// symbols are named __FPv upstream.
void* cMemPool8_alloc_impl(void* pool, unsigned int align) __asm__("cMemPool8_alloc__FPv");
void* cMemPool16_alloc_impl(void* pool, unsigned int align) __asm__("cMemPool16_alloc__FPv");
void* cMemPool32_alloc_impl(void* pool, unsigned int align) __asm__("cMemPool32_alloc__FPv");
void* cMemPool64_alloc_impl(void* pool, unsigned int align) __asm__("cMemPool64_alloc__FPv");
void* cMemPool128_alloc_impl(void* pool, unsigned int align) __asm__("cMemPool128_alloc__FPv");
void* cMemPool256_alloc_impl(void* pool, unsigned int align) __asm__("cMemPool256_alloc__FPv");
void* cMemPool512_alloc_impl(void* pool, unsigned int align) __asm__("cMemPool512_alloc__FPv");
extern void* D_004A5B60;
extern void* D_004A5B50;
extern void* D_004A5B5C;
extern void* D_004A5B6C;
extern void* D_004A5B74;
extern void* D_004A5B68;
extern void* D_004A5B58;
extern int D_004A3EC8;

// PORT: binds the real 2-arg body; the unit declares a 1-arg prototype used by callers
extern "C" void* cMemBlockMan_alloc_impl(unsigned int size, unsigned int align) __asm__("cMemBlockMan_alloc");
extern "C" void* cMemBlockMan_alloc_impl(unsigned int size, unsigned int align)
{
    size = size > align ? size : align;
    if (D_004A3EC8) {
        size = size + (-(size & 3) & 3);
        if (size <= 8)
            return cMemPool8_alloc_impl(D_004A5B60, align);
        if (size <= 0x10)
            return cMemPool16_alloc_impl(D_004A5B50, align);
        if (size <= 0x20)
            return cMemPool32_alloc_impl(D_004A5B5C, align);
        if (size <= 0x40)
            return cMemPool64_alloc_impl(D_004A5B6C, align);
        if (size <= 0x80)
            return cMemPool128_alloc_impl(D_004A5B74, align);
        if (size <= 0x100)
            return cMemPool256_alloc_impl(D_004A5B68, align);
        if (size <= 0x200)
            return cMemPool512_alloc_impl(D_004A5B58, align);
    } else
        size = 0x201;
    return cMemMan_internalAlloc(size, align > 7 ? align : 8, 0, 0);
}

//100%
void cMemPool8_free(void* pool, void** p);
void cMemPool16_free(void* pool, void** p);
void cMemPool32_free(void* pool, void** p);
void cMemPool64_free(void* pool, void** p);
void cMemPool128_free(void* pool, void** p);
void cMemPool256_free(void* pool, void** p);
void cMemPool512_free(void* pool, void** p);
extern void* D_004A5B60;
extern void* D_004A5B50;
extern void* D_004A5B5C;
extern void* D_004A5B6C;
extern void* D_004A5B74;
extern void* D_004A5B68;
extern void* D_004A5B58;

template <unsigned int N>
inline bool inPool_319F68(void* pool, void* p)
{
    return (unsigned int)((char*)p - (char*)pool) < N;
}

extern "C" void cMemBlockMan_free(void* p)
{
    if (inPool_319F68<0x800>(D_004A5B60, p))
        cMemPool8_free(D_004A5B60, (void**)p);
    else if (inPool_319F68<0x2000>(D_004A5B50, p))
        cMemPool16_free(D_004A5B50, (void**)p);
    else if (inPool_319F68<0x6000>(D_004A5B5C, p))
        cMemPool32_free(D_004A5B5C, (void**)p);
    else if (inPool_319F68<0x32000>(D_004A5B6C, p))
        cMemPool64_free(D_004A5B6C, (void**)p);
    else if (inPool_319F68<0x25800>(D_004A5B74, p))
        cMemPool128_free(D_004A5B74, (void**)p);
    else if (inPool_319F68<0x20000>(D_004A5B68, p))
        cMemPool256_free(D_004A5B68, (void**)p);
    else if (inPool_319F68<0x20000>(D_004A5B58, p))
        cMemPool512_free(D_004A5B58, (void**)p);
}

//100%
extern void* D_004A5B50;
extern void* D_004A5B58;
extern void* D_004A5B5C;
extern void* D_004A5B60;
extern void* D_004A5B68;
extern void* D_004A5B6C;
extern void* D_004A5B74;

static inline int cMemBlockMan_owns_in(void* p, void* base, unsigned int size)
{
    return (unsigned int)((char*)p - (char*)base) <= size - 1;
}

extern "C" int cMemBlockMan_owns(void* p)
{
    if (cMemBlockMan_owns_in(p, D_004A5B60, 0x800))
        return 1;
    if (cMemBlockMan_owns_in(p, D_004A5B50, 0x2000))
        return 1;
    if (cMemBlockMan_owns_in(p, D_004A5B5C, 0x6000))
        return 1;
    if (cMemBlockMan_owns_in(p, D_004A5B6C, 0x32000))
        return 1;
    if (cMemBlockMan_owns_in(p, D_004A5B74, 0x25800))
        return 1;
    if (cMemBlockMan_owns_in(p, D_004A5B68, 0x20000))
        return 1;
    return cMemBlockMan_owns_in(p, D_004A5B58, 0x20000);
}

//100%
extern void* D_004A5B50;
extern void* D_004A5B58;
extern void* D_004A5B5C;
extern void* D_004A5B60;
extern void* D_004A5B68;
extern void* D_004A5B6C;
extern void* D_004A5B74;

static inline int cMemBlockMan_blockSize_in(void* p, void* base, unsigned int size)
{
    return (unsigned int)((char*)p - (char*)base) <= size - 1;
}

extern "C" int cMemBlockMan_blockSize(void* p)
{
    if (cMemBlockMan_blockSize_in(p, D_004A5B60, 0x800))
        return 0x8;
    if (cMemBlockMan_blockSize_in(p, D_004A5B50, 0x2000))
        return 0x10;
    if (cMemBlockMan_blockSize_in(p, D_004A5B5C, 0x6000))
        return 0x20;
    if (cMemBlockMan_blockSize_in(p, D_004A5B6C, 0x32000))
        return 0x40;
    if (cMemBlockMan_blockSize_in(p, D_004A5B74, 0x25800))
        return 0x80;
    if (cMemBlockMan_blockSize_in(p, D_004A5B68, 0x20000))
        return 0x100;
    if (cMemBlockMan_blockSize_in(p, D_004A5B58, 0x20000))
        return 0x200;
    return 0;
}

//100%
extern int D_004A3EC8;
extern void* D_004A5B50;
extern void* D_004A5B58;
extern void* D_004A5B5C;
extern void* D_004A5B60;
extern void* D_004A5B68;
extern void* D_004A5B6C;
extern void* D_004A5B74;
// PORT: these empty stubs are defined as f(void), but this caller passes one argument.
void cMemPool8_purge_1(void*) __asm__("cMemPool8_purge__Fv");
void cMemPool16_purge_1(void*) __asm__("cMemPool16_purge__Fv");
void cMemPool32_purge_1(void*) __asm__("cMemPool32_purge__Fv");
void cMemPool64_purge_1(void*) __asm__("cMemPool64_purge__Fv");
void cMemPool128_purge_1(void*) __asm__("cMemPool128_purge__Fv");
void cMemPool256_purge_1(void*) __asm__("cMemPool256_purge__Fv");
void cMemPool512_purge_1(void*) __asm__("cMemPool512_purge__Fv");

extern "C" void cMemBlockMan_purge(void)
{
    if (D_004A3EC8 != 0) {
        cMemPool8_purge_1(D_004A5B60);
        cMemPool16_purge_1(D_004A5B50);
        cMemPool32_purge_1(D_004A5B5C);
        cMemPool64_purge_1(D_004A5B6C);
        cMemPool128_purge_1(D_004A5B74);
        cMemPool256_purge_1(D_004A5B68);
        cMemPool512_purge_1(D_004A5B58);
    }
}

extern "C" int func_0031A258()
{
    return 0;
}

extern "C" void func_0031A260()
{
}

//100%
// PORT: PS2-only VU0 FPU-flag probe: builds two float4s from flag bits and multiplies them on VU0.
extern "C" void func_0031A268(int flags)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    int i;
    for (i = 0; i < 4; i++) {
        float f;
        if ((flags & 0x8800) == 0) {
            f = 0.0f;
            if (!(flags & 8))
                f = 1.0f;
        } else {
            f = 1.0000000031710769e-30f;
            if (!(flags & 8))
                f = 1.0000000150474662e+30f;
        }
        a[i] = f;
        if (flags & 0x80)
            f = -f;
        b[i] = f;
        flags <<= 1;
    }
    __asm__ __volatile__(
        "qmfc2.ni   $8, $vf1\n"
        "qmfc2.ni   $9, $vf2\n"
        "lqc2       $vf1, %0\n"
        "lqc2       $vf2, %1\n"
        "vmul.xyzw  $vf1, $vf1, $vf2\n"
        "qmtc2.ni   $8, $vf1\n"
        "qmtc2.ni   $9, $vf2\n"
        "vnop\n"
        :
        : "m"(a[0]), "m"(b[0])
        : "$8", "$9");
}

//100%
// PORT: PS2-only VU0 state save (VF1-VF31, MAC/status/Q/clip flags, ACC) to a 0x210-byte buffer.
INCLUDE_ASM("bx/memblockman", func_0031A308);
extern "C" void func_0031A308(void* buf);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_0031A268(int status);

// PORT: PS2-only VU0 state restore (inverse of func_0031A308): VF1-VF31, flags, ACC.
INCLUDE_ASM("bx/memblockman", func_0031A3C0);
extern "C" void func_0031A3C0(void* buf);

//100%
// PORT: PS2-only handler trampoline: saves/restores all 32 FPU registers around the
// handler call and re-enables interrupts (sync; ei). Needs a native replacement off-PS2.
INCLUDE_ASM("bx/memblockman", func_0031A490);
extern "C" int func_0031A490(int arg, void (*handler)(int));

//100%
extern int D_004A3ECC;
extern "C" void func_00423C30(int, int);

extern "C" void func_0031A6B8(void)
{
    func_00423C30(D_004A3ECC, 0x65);
}

INCLUDE_ASM("bx/memblockman", func_0031A6D8);

//100%
extern "C" void func_00424880(int);
extern "C" void func_00423AA0(int, int);
extern "C" int func_004248E8(int);
extern "C" void func_00423DC0(int);
extern "C" void func_00423CC0();
extern "C" void func_00423BF0(int);
extern "C" void func_00423BB0(int);
extern "C" void func_00423DB0(int);

extern "C" void func_0031A920(void* self)
{
    func_00424880(3);
    func_00423AA0(3, *(int*)((char*)self + 0x14290));
    func_004248E8(3);
    *(int*)((char*)self + 0x20) = 1;
    func_00423DC0(*(int*)((char*)self + 0x14044));
    func_00423DC0(*(int*)((char*)self + 0x4034));
    func_00423CC0();
    func_00423CC0();
    func_00423BF0(*(int*)((char*)self + 0x4030));
    func_00423BB0(*(int*)((char*)self + 0x4030));
    func_00423BF0(*(int*)((char*)self + 0x14040));
    func_00423BB0(*(int*)((char*)self + 0x14040));
    func_00423DB0(*(int*)((char*)self + 0x4034));
    func_00423DB0(*(int*)((char*)self + 0x14044));
    func_00423DB0(*(int*)((char*)self + 0x18));
    func_00423DB0(*(int*)((char*)self + 0xC));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_0031A3C0(void* buf);

extern "C" void func_0031A9D8(void* self)
{
    if (*(int*)((char*)self + 0x14048) != 0) {
        func_0031A3C0((char*)self + 0x14080);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_0031AA18(void* self)
{
    if (*(int*)((char*)self + 0x14048) != 0) {
        func_0031A308((char*)self + 0x14080);
    }
}

//100%
extern "C" void* func_00423DE0(int);
extern "C" int func_00423DF0(int);

struct sMemBlkVEntryA {
    short delta;
    short index;
    int (*fn)(void*);
};
struct sMemBlkVEntryB {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void func_0031AA58(void* self)
{
    *(int*)((char*)self + 0x1C) = 1;
    sMemBlkVEntryA* vt = *(sMemBlkVEntryA**)((char*)self + 0x8);
    vt[11].fn((char*)self + vt[11].delta);
    func_00423DE0(*(int*)((char*)self + 0x18));
    *(int*)((char*)self + 0x1C) = 0;
    while (func_00423DF0(*(int*)((char*)self + 0x18)) == *(int*)((char*)self + 0x18))
    {
    }
    sMemBlkVEntryB* vt2 = *(sMemBlkVEntryB**)((char*)self + 0x8);
    vt2[12].fn((char*)self + vt2[12].delta);
}

//100%
extern "C" void func_00423DC0(int);

extern "C" void func_0031AAC8(void* self)
{
    if (*(int*)((char*)self + 0x1C) != 0) {
        func_00423DC0(*(int*)((char*)self + 0x18));
    }
}

extern "C" void* func_00423DE0(int);

//100%
void* func_0031AAF0(void* self)
{
    return func_00423DE0(*(int*)((char*)self + 0xc));
}

//100%
// Thread entry: passes the handle at 0xC to func_00423DC0, then loops on func_00423CC0 forever.
extern "C" void func_00423CC0();

extern "C" void func_0031AB10(void* self)
{
    func_00423DC0(*(int*)((char*)self + 0xC));
    for (;;)
        func_00423CC0();
}

//100%
// Thread body: marks the thread running, then halts or runs the virtual main.
// PORT: the splat asm covered this together with func_0031AB10; it has no symbol of its own.
extern "C" int func_00423C90_AB30(void) __asm__("func_00423C90");
extern "C" void func_00423D10(int);
int cExecutionMan_checkHalt(void* self, int flag);

extern "C" void func_0031AB30(void* self)
{
    // volatile: other threads poll this flag (see func_0031ABD0), so the store stays before the call.
    *(volatile int*)((char*)self + 0x4038) = 1;
    int id = func_00423C90_AB30();
    if (id != *(int*)((char*)self + 0x14040))
        func_00423D10(*(int*)((char*)self + 0x14040));
    if (id == *(int*)((char*)self + 0x10)) {
        cExecutionMan_checkHalt(self, 0);
    } else {
        sMemBlkVEntryB* vt = *(sMemBlkVEntryB**)((char*)self + 0x8);
        vt[5].fn((char*)self + vt[5].delta);
        func_0031AAF0(self);
    }
}

//100%
void func_0031ABC0(void* self)
{
}

//100%
int func_0031ABC8(void* self)
{
    return 0x3C;
}

//100%
void* func_00317520();
extern "C" void func_00423DD0(int);

extern "C" void func_0031ABD0(void)
{
    char* app = (char*)func_00317520();
    if (*(int*)(app + 0x4038) == 0) {
        func_00423DD0(*(int*)(app + 0x4034));
    }
}

//100%
extern "C" void* func_00423DE0(int);
extern "C" void func_00423CD0(int);
extern "C" void func_00423CC0();
// PORT: func_00317500__Fv is called with self here; bind the 1-arg form to that symbol.
int func_00317500_1(void* self) __asm__("func_00317500__Fv");

extern "C" void func_0031AC08(void* self)
{
    while (func_00423DE0(*(int*)((char*)self + 0x4034)), *(int*)((char*)self + 0x20) == 0)
    {
        func_00317500_1(self);
    }
    func_00423CD0(*(int*)((char*)self + 0x10));
    func_00423CC0();
}

//100%
struct sMemJobVEntry {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void func_0031AC60(void* self)
{
    while (func_00423DE0(*(int*)((char*)self + 0x14044)), *(int*)((char*)self + 0x20) == 0)
    {
        void* obj = *(void* volatile*)((char*)self + 0x14048);
        sMemJobVEntry* vt = *(sMemJobVEntry**)obj;
        vt[2].fn((char*)obj + vt[2].delta);
        *(void* volatile*)((char*)self + 0x14048) = 0;
    }
    func_00423CD0(*(int*)((char*)self + 0x10));
    func_00423CC0();
}

//100%
extern "C" void func_00423DC0(int);

extern "C" void func_0031ACD8(void* self, int a1)
{
    *(int*)((char*)self + 0x14048) = a1;
    func_00423DC0(*(int*)((char*)self + 0x14044));
}

//100%
extern "C" int func_0031AD00(void* self)
{
    return *(int*)((char*)self + 0x14048) == 0;
}

extern "C" unsigned int D_004A3ED0;

//99.5% - single $gp-relative sw; SN's assembler doesn't support %gp_rel(),
// so our object always carries a real relocation here while the target's
// raw disassembly has the offset already baked in as a literal immediate.
extern "C" void func_0031AD18()
{
    D_004A3ED0 = 0;
}

//100%
extern int D_00519C40[];
extern int D_004A3ED4;
extern "C" int func_00402618(int cmd, int* out);
extern "C" void func_003E3D78(void);

extern "C" int func_0031AD20(void)
{
    int flags = D_00519C40[0];
    if (D_004A3ED4 != 0) {
        int r;
        D_004A3ED4 = 0;
        r = 0;
        func_00402618(2, &r);
    }
    if ((flags & 6) == 6) {
        int r2 = 0;
        func_00402618(2, &r2);
        if (r2 != 0)
            D_004A3ED0 = 1;
        D_00519C40[0] &= ~6;
        func_003E3D78();
    }
    return 0;
}

