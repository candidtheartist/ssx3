#include "common.h"

INCLUDE_ASM("worldpainter/quadtree", cQuadTree_getFreeNode);

extern "C" void func_002C18E8(void* self, unsigned short a, unsigned short b, unsigned short c, unsigned short d)
{
    char* nodes = *(char**)((char*)self + 0x20);
    *(unsigned short*)(nodes + (a << 3)) = b;
    *(unsigned short*)(nodes + (b << 3)) = c;
    *(unsigned short*)(nodes + (c << 3)) = d;
    *(unsigned short*)(nodes + (d << 3)) = **(unsigned short**)((char*)self + 0x24);
    **(unsigned short**)((char*)self + 0x24) = a;
    *(int*)((char*)self + 0xC) -= 4;
}

INCLUDE_ASM("worldpainter/quadtree", func_002C1950);

INCLUDE_ASM("worldpainter/quadtree", func_002C1A00);

//100%
extern "C" void* func_002C1CD8(void* self, float fx, float fz)
{
    int x = (int)((fx - *(float*)((char*)self + 4)) * *(float*)self);
    int z = (int)((fz - *(float*)((char*)self + 8)) * *(float*)self);
    if ((unsigned int)x > 0x7FFF || (unsigned int)z > 0x7FFF) {
        return (char*)self + 0x18;
    }
    unsigned short ux = x << 1;
    unsigned short uz = z << 1;
    char* nodes = *(char**)((char*)self + 0x20);
    unsigned short* node = (unsigned short*)(nodes + *(unsigned short*)((char*)self + 0x14) * 8);
    while (node[0] & 1) {
        int idx = ((ux >> 15) << 1) | (uz >> 15);
        ux <<= 1;
        uz <<= 1;
        node = (unsigned short*)(nodes + (*(unsigned short*)((char*)node + (idx << 1)) >> 1) * 8);
    }
    if (node[0] & 1) {
        return 0;
    }
    return node;
}

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator new[](unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" void* func_00416210(void* dst, int c, int n);
extern "C" void func_002C16B8(unsigned short* p, unsigned short a, unsigned short b, unsigned short c, unsigned short d);
struct func_002C2088_sOut;
struct func_002C2088_sNode;
extern "C" void func_002C2088(void* self, func_002C2088_sOut* out, int* count, int* map, func_002C2088_sNode* node);
extern char D_00485FB0[];
extern char D_00485FC8[];

struct sQTHeader_1DA8 {
    float f0;           // 0x00
    float f4;           // 0x04
    float f8;           // 0x08
    int fC;             // 0x0C
    int f10;            // 0x10
    unsigned short f14; // 0x14
    unsigned short f16;
    int f18;            // 0x18
    int f1C;            // 0x1C
    char* f20;          // 0x20
    int f24;            // 0x24
};

extern "C" void cQuadTree_exportTree(sQTHeader_1DA8* self, char** out, int* size, void* ctx,
                                     float (*fixFloat)(void*, float), int (*fixInt)(int, void*),
                                     unsigned short (*fixShort)(unsigned short, void*))
{
    int i;
    *size = self->fC * 8 + 0x28;
    int* map = new (D_00485FB0, 0, 0) int[self->f10];
    for (i = 0; i < self->f10; i++)
        map[i] = -1;
    *out = new (D_00485FC8, 0, 0) char[*size];
    func_00416210(*out, 0xDEADBEEF, *size);
    sQTHeader_1DA8* o = (sQTHeader_1DA8*)*out;
    *o = *self;
    int cnt = 0;
    unsigned short* p = (unsigned short*)(o + 1);
    func_002C2088(self, (func_002C2088_sOut*)p, &cnt, map, (func_002C2088_sNode*)(self->f20 + self->f14 * 8));
    for (i = 0; i < cnt; i++, p += 4) {
        if (p[0] & 1) {
            func_002C16B8(p, map[p[0] >> 1], map[p[1] >> 1], map[p[2] >> 1], map[p[3] >> 1]);
            p[0] = fixShort(p[0], ctx);
            p[1] = fixShort(p[1], ctx);
            p[2] = fixShort(p[2], ctx);
            p[3] = fixShort(p[3], ctx);
        } else {
            ((int*)p)[0] = fixInt(((int*)p)[0], ctx);
            ((int*)p)[1] = fixInt(((int*)p)[1], ctx);
        }
    }
    o->f10 = 0;
    o->f24 = 0;
    o->f1C = fixInt(self->f1C, ctx);
    o->f18 = fixInt(self->f18, ctx);
    o->f0 = fixFloat(ctx, o->f0);
    o->f4 = fixFloat(ctx, o->f4);
    o->f8 = fixFloat(ctx, o->f8);
    o->fC = fixInt(o->fC, ctx);
}

//100%
struct func_002C2088_sNode {
    unsigned short child[4];
};
struct func_002C2088_sOut {
    int f0;
    int f4;
};

// PORT: node index computed from pointers cast to unsigned int
extern "C" void func_002C2088(void* self, func_002C2088_sOut* out, int* count, int* map, func_002C2088_sNode* node)
{
    int i;
    unsigned short* p;
    out[*count].f4 = *(int*)((char*)node + 4);
    out[*count].f0 = *(int*)((char*)node + 0);
    map[(unsigned short)(((unsigned int)node - *(unsigned int*)((char*)self + 0x20)) >> 3)] = (*count)++;
    if (node->child[0] & 1) {
        p = node->child;
        for (i = 0; i < 4; i++) {
            func_002C2088(self, out, count, map, *(func_002C2088_sNode**)((char*)self + 0x20) + (*p++ >> 1));
        }
    }
}

extern "C" int func_002C2178(void* self, func_002C2088_sNode* node)
{
    int n = 1;
    int i;
    unsigned short* p;
    if (node != 0 && (node->child[0] & 1)) {
        p = node->child;
        for (i = 3; i >= 0; i--) {
            n += func_002C2178(self, *(func_002C2088_sNode**)((char*)self + 0x20) + (*p++ >> 1));
        }
    }
    return n;
}

extern "C" void func_002C2200()
{
}

extern "C" void func_002C2208()
{
}

//100%
extern "C" short func_002C2338(unsigned char c);

extern "C" void func_002C2210(void* self, short* dst, const char* src)
{
    while (*src != 0) {
        *dst++ = func_002C2338(*src++);
    }
    *dst = 0;
}

//100%
extern "C" char func_002C2430(short c);

extern "C" void func_002C2268(void* self, char* dst, const short* src)
{
    for (; *src != 0; src++, dst++) {
        *dst = func_002C2430(*src);
    }
    *dst = 0;
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_002C3FA8(void*);
extern const char D_00485FF0[];

extern "C" void* func_002C22C8(void)
{
    return func_002C3FA8(cMemMan_alloc(0x1500, D_00485FF0, 0x100, 0));
}

//100%
class func_002C2300_cObj {
public:
    virtual ~func_002C2300_cObj();
};

extern "C" void func_002C2300(func_002C2300_cObj* self)
{
    delete self;
}

//100%
struct func_002C2338_sRange {
    unsigned short base;
    unsigned short first;
};
extern func_002C2338_sRange D_00445940[];
extern unsigned short D_00445950[];

extern "C" short func_002C2338(unsigned char c)
{
    int off = 0;
    int idx = 0;
    unsigned short v;

    if (c >= 0x20 && c <= 0x2F) {
        off = 1;
    } else if (c >= 0x30 && c <= 0x39) {
    } else if (c >= 0x3A && c <= 0x40) {
        off = 0xB;
    } else if (c >= 0x41 && c <= 0x5A) {
        idx = 1;
    } else if (c >= 0x5B && c <= 0x60) {
        off = 0x25;
    } else if (c >= 0x61 && c <= 0x7A) {
        idx = 2;
    } else if (c >= 0x7B && c <= 0x7E) {
        off = 0x3F;
    } else {
        return 0;
    }
    if (off != 0) {
        v = D_00445950[(c - 0x20) + 1 - off];
    } else {
        v = D_00445940[idx].base + c - D_00445940[idx].first;
    }
    return (v << 8) | (v >> 8);
}

INCLUDE_ASM("worldpainter/quadtree", func_002C2430);

//100%
extern "C" int func_002C24D0(unsigned short* s)
{
    int n = 0;
    while (*s++ != 0) {
        n++;
    }
    return n;
}

//100%
extern "C" unsigned short* func_002C2508(unsigned short* dst, unsigned short* src)
{
    unsigned short* ret = dst;
    while (*src != 0) {
        *dst++ = *src++;
    }
    *dst = 0;
    return ret;
}

//100%
extern "C" unsigned short* func_002C2540(unsigned short* dst, char* src)
{
    unsigned short* ret = dst;
    while (*src != 0) {
        *dst++ = *src++;
    }
    *dst = 0;
    return ret;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
// The unit declares this as extern "C" void* func_002C2580(void*) further down
// (its caller func_002C5500 passes one arg); bind the 2-arg body to the symbol.
char* func_002C2580_impl(char* dst, unsigned short* src) __asm__("func_002C2580");
char* func_002C2580_impl(char* dst, unsigned short* src)
{
    char* ret = dst;
    while (*src != 0) {
        *dst++ = *src++;
    }
    *dst = 0;
    return ret;
}

//100%
extern "C" unsigned short* func_002C25B8(unsigned short* dst, unsigned short* src, int n)
{
    unsigned short* ret = dst;
    while (*src != 0 && n > 0) {
        *dst++ = *src++;
        n--;
    }
    *dst = 0;
    return ret;
}

// Copies an 8-bit string into a 16-bit one, at most n characters; returns dst
extern "C" short* func_002C25F8(short* dst, signed char* src, int n)
{
    short* start = dst;
    while (*src && n > 0) {
        *dst++ = *src++;
        n--;
    }
    *dst = 0;
    return start;
}

// Copies a 16-bit string into an 8-bit one, at most n characters; returns dst
extern "C" char* func_002C2640(char* dst, unsigned short* src, int n)
{
    char* start = dst;
    while (*src && n > 0) {
        *dst++ = *src++;
        n--;
    }
    *dst = 0;
    return start;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" unsigned short* func_002C2508(unsigned short* dst, unsigned short* src);

extern "C" unsigned short* func_002C2688(unsigned short* dst, unsigned short* src)
{
    while (*dst != 0) {
        dst++;
    }
    return func_002C2508(dst, src);
}

//100%
// PORT: hand-rolled EE EABI va_start (gcc 2.95 va-mips.h form); use <stdarg.h> off-PS2.
typedef char* func_002C26D0_va_list;
#define func_002C26D0_va_start(ap)                                       \
    (ap = (char*)__builtin_next_arg()                                    \
          - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern "C" int USTR_vsprintf(unsigned short* dst, const unsigned short* fmt, char* ap);

extern "C" int func_002C26D0(unsigned short* dst, const unsigned short* fmt, ...)
{
    func_002C26D0_va_list ap;
    func_002C26D0_va_start(ap);
    return USTR_vsprintf(dst, fmt, ap);
}

//100%
extern "C" int strlen(const char* s);

// PORT: hand-rolled EE EABI va_start (func_002C26D0_va_start, defined above); use <stdarg.h> off-PS2.
extern "C" int func_002C2718(unsigned short* dst, const char* fmt, ...)
{
    func_002C26D0_va_list ap;
    unsigned short buf[0x400];
    unsigned short* p;
    int n;
    int i;
    p = buf;
    n = strlen(fmt);
    for (i = 0; i < n; i++) {
        *p++ = *fmt++;
    }
    *p = 0;
    func_002C26D0_va_start(ap);
    return USTR_vsprintf(dst, buf, ap);
}

//100%
extern "C" int strlen(const char* s);

// PORT: hand-rolled EE EABI va_start (func_002C26D0_va_start, defined above); use <stdarg.h> off-PS2.
extern "C" int func_002C27C0(unsigned short* dst, const char* fmt, ...)
{
    func_002C26D0_va_list ap;
    unsigned short buf[0x400];
    unsigned short* p;
    int n;
    int i;
    p = buf;
    n = strlen(fmt);
    for (i = 0; i < n; i++) {
        *p++ = *fmt++;
    }
    *p = 0;
    func_002C26D0_va_start(ap);
    return USTR_vsprintf(dst, buf, ap);
}

//100%
extern "C" void func_002C2868(char* s)
{
    while (*s != 0) {
        if (*s >= 'A' && *s <= 'Z') {
            *s += 'a' - 'A';
        }
        s++;
    }
}

extern "C" void func_003E4E98();

extern "C" void func_002C28A0()
{
    func_003E4E98();
}

extern char D_00486030[];

extern "C" void* func_002C28C0(void* self, int size, int big)
{
    return operator new[](size, D_00486030, big ? 0x100 : 0, 0);
}

extern "C" int MEM_free_result(void* p) __asm__("MEM_free");

extern "C" int func_002C28F8(void* p)
{
    return MEM_free_result(p) != 0;
}

extern "C" void func_003E6574(void* dst, const void* src, int size);

extern "C" void* func_002C2918(void* dst, const void* src, int size)
{
    func_003E6574(dst, src, size);
    return dst;
}

extern void* gMemMutex[16];
extern "C" void MUTEX_lock_p(void* m) __asm__("MUTEX_lock");
extern "C" void MUTEX_unlock_p(void* m) __asm__("MUTEX_unlock");
extern "C" void* cMemMan_internalResizeBlock(void* p, int size);

extern "C" void* func_002C2940(void* ptr, void* self, int size, int big)
{
    if (ptr == 0) {
        return func_002C28C0(self, size, big);
    }
    if (size == 0) {
        func_002C28F8(ptr);
        return 0;
    }
    MUTEX_lock_p(gMemMutex);
    ptr = cMemMan_internalResizeBlock(ptr, size);
    MUTEX_unlock_p(gMemMutex);
    return ptr;
}

INCLUDE_ASM("worldpainter/quadtree", func_002C29D0);

extern "C" void func_002C2AA8(void** self)
{
    if (*self != 0) {
        func_002C28F8(*self);
        *self = 0;
    }
    if (self != 0) {
        if (*self != 0) {
            func_002C28F8(*self);
        }
        func_002C28F8(self);
    }
}

extern "C" void func_003E5398();

extern "C" void func_002C2B08()
{
    func_003E5398();
}

extern char D_004A3898[];
extern "C" void MUTEX_init(void* p);

extern "C" void* func_002C2B28()
{
    void* p = func_002C28C0(D_004A3898, 0x10, 0);
    MUTEX_init(p);
    return p;
}

extern "C" void MUTEX_destroy(void* p);

extern "C" void func_002C2B68(void* p)
{
    MUTEX_destroy(p);
    func_002C28F8(p);
}

extern "C" void MUTEX_lock();

extern "C" void func_002C2B98()
{
    MUTEX_lock();
}

extern "C" void MUTEX_unlock();

extern "C" void func_002C2BB8()
{
    MUTEX_unlock();
}

INCLUDE_ASM("worldpainter/quadtree", func_002C2BD8);

extern char D_00486098[];

extern "C" void* func_002C2D30(void* self, int size, int big)
{
    return operator new[](size, D_00486098, big ? 0x100 : 0, 0);
}

extern "C" int func_002C2D68(void* p)
{
    return MEM_free_result(p) != 0;
}

extern "C" void* func_002C2D88(void* dst, const void* src, int size)
{
    func_003E6574(dst, src, size);
    return dst;
}

extern "C" void* func_002C2DB0(void* ptr, void* self, int size, int big)
{
    if (ptr == 0) {
        return func_002C2D30(self, size, big);
    }
    if (size == 0) {
        func_002C2D68(ptr);
        return 0;
    }
    MUTEX_lock_p(gMemMutex);
    ptr = cMemMan_internalResizeBlock(ptr, size);
    MUTEX_unlock_p(gMemMutex);
    return ptr;
}

extern "C" int func_002C2E40(unsigned short* s)
{
    int n = 0;
    while (*s++ != 0) {
        n++;
    }
    return n;
}

extern "C" int strlen(const char* s);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void func_0041610C();
extern "C" void func_00415FC8();
extern "C" void func_004162D0();
extern "C" void func_004187C0();

extern "C" void func_002C2E78(void** t)
{
    t[7] = (void*)func_002C2D30;
    t[8] = (void*)func_002C2DB0;
    t[9] = (void*)func_002C2D68;
    t[11] = (void*)func_002C2D88;
    t[10] = (void*)func_00416210;
    t[12] = (void*)func_0041610C;
    t[13] = (void*)func_00415FC8;
    t[1] = (void*)func_004162D0;
    t[2] = (void*)strlen;
    t[3] = (void*)func_002C2E40;
    t[4] = (void*)sprintf;
    t[5] = (void*)strcpy;
    t[6] = (void*)func_004187C0;
}

INCLUDE_ASM("worldpainter/quadtree", func_002C2F18);

//100%
void func_002C3FA0(void* self)
{
}

//100%
extern "C" void func_002C4050(void*);
extern void* D_00486F78[];

extern "C" void* func_002C3FA8(void* self)
{
    *(void***)self = D_00486F78;
    func_002C4050(self);
    return self;
}

//100%
void operator_delete(int* ptr);
extern "C" void MEM_free(void* p);
extern "C" void func_002C6360(void* self);
extern void* D_00486F78[];
extern void* D_004871E8[];

extern "C" void func_002C3FE0(void* self, int flags)
{
    *(void***)self = D_00486F78;
    func_002C6360(self);
    void* p = *(void**)((char*)self + 0x30);
    if (p != 0) {
        MEM_free(p);
    }
    *(void***)self = D_004871E8;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

INCLUDE_ASM("worldpainter/quadtree", func_002C4050);

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
char* func_002C2580_impl(char* dst, unsigned short* src) __asm__("func_002C2580");

struct sVEntry002C4198 {
    short delta;
    short index;
    void (*fn)(void*, char*);
};

extern "C" void func_002C4198(void* self, unsigned short* name)
{
    char buf[1000];
    func_002C2580_impl(buf, name);
    sVEntry002C4198* vt = *(sVEntry002C4198**)self;
    vt[6].fn((char*)self + vt[6].delta, buf);
}

//100%
extern "C" void* func_002C48C0(void*, int);

extern "C" void func_002C41D8(void* self, const char* name)
{
    strcpy((char*)self + 0x139, name);
    func_002C48C0(self, 5);
}

//100%
extern "C" int func_0040A688(int h, int a1, char* name, int a3, int a4, void* buf);
extern int D_004A3940;
extern "C" void* func_003E6448(void* dst, int c, int n);

extern "C" void func_002C4210(void* self)
{
    char* buf = (char*)self + 0x4C0;
    func_003E6448(buf, 0, 0x1000);
    int r = func_0040A688(*(int*)((char*)self + 0xC), 0, (char*)self + 0x139, 0, 6, buf);
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 6);
    }
}

extern "C" void* func_002C48C0(void*, int);

//100%
void* func_002C4290(void* self, int a1)
{
    *(int*)((char*)self + 0x1c) = a1;
    return func_002C48C0(self, 0x22);
}

//100%
extern "C" int func_0040A688(int h, int a1, char* name, int a3, int a4, void* buf);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern int D_004A3940;
extern char D_004A3948[];

extern "C" void func_002C42B0(void* self)
{
    char* name = (char*)self + 0xB9;
    *(int*)((char*)self + 0x3C) = 0;
    char* path = (char*)self + 0xF9;
    strcpy(name, (char*)self + *(int*)((char*)self + 0x1C) * 0x78 + 0x1B0);
    sprintf(path, D_004A3948, name, name);
    int r = func_0040A688(*(int*)((char*)self + 0xC), 0, path, 0, 1, (char*)self + 0x480);
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x23);
    }
}

//100%
void* func_002C4368(void* self)
{
    return func_002C48C0(self, 0x11);
}

//100%
extern "C" int func_0040A998(int h, int a1);
extern int D_004A3940;

extern "C" void func_002C4388(void* self)
{
    int r = func_0040A998(*(int*)((char*)self + 0xC), 0);
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x12);
    }
}

//100%
void* func_002C43E0(void* self, int a1)
{
    *(int*)((char*)self + 0x1c) = a1;
    return func_002C48C0(self, 0x13);
}

//100%
int func_002C4400(void* self)
{
    return *(int*)((char*)self + 0x490);
}

//100%
void func_002C4408(void* self, int val)
{
    *(int*)((char*)self + 0x24) = val;
}

//100%
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void* func_002C48C0(void*, int);
extern char D_004A3948[];

extern "C" void func_002C4410(void* self)
{
    char* name = (char*)self + 0xB9;
    *(int*)((char*)self + 0x3C) = 0;
    strcpy(name, (char*)self + *(int*)((char*)self + 0x1C) * 0x78 + 0x1B0);
    sprintf((char*)self + 0xF9, D_004A3948, name, name);
    func_002C48C0(self, 0x36);
}

//100%
class func_002C4480_cObj {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
    virtual int v11(); // 0x58
};

extern "C" void func_002C4480(func_002C4480_cObj* self, int a1)
{
    *(int*)((char*)self + 0xC) = a1;
    if (self->v11() == 0) {
        *(int*)((char*)self + 0x10) = a1;
        func_002C48C0(self, 3);
    }
}

//100%
struct sQTLevel {
    int f00;
    void* f04;
    int f08;
    int f0C;
    int f10;
};

struct sQTState {
    char pad000[0xC];
    int level;
    char pad010[0x16C];
    sQTLevel levels[1];
};

extern "C" void func_002C44E0(sQTState* self)
{
    self->levels[self->level].f10 = 0;
    if (self->levels[self->level].f08 == -1) {
        self->levels[self->level].f08 = 0;
    }
}

//100%
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char D_004A3950[];

extern "C" void func_002C4520(void* self, const char* name)
{
    char* p = (char*)self + 0xB9;
    strcpy(p, name);
    sprintf((char*)self + 0xF9, D_004A3950, p);
    func_002C48C0(self, 0x14);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char D_004A3950[];
// PORT: func_002C2580 takes (dst, src); the unit declares it with one arg
char* func_002C2580_impl(char* dst, unsigned short* src) __asm__("func_002C2580");

extern "C" void func_002C4578(void* self, unsigned short* name)
{
    char* p = (char*)self + 0xB9;
    func_002C2580_impl(p, name);
    sprintf((char*)self + 0xF9, D_004A3950, p);
    func_002C48C0(self, 0x14);
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: func_002C2580 takes (dst, src); the unit declares it with one arg
char* func_002C2580_impl(char* dst, unsigned short* src) __asm__("func_002C2580");
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void* func_002C48C0(void*, int);
extern char D_004A3948[];

extern "C" void func_002C45D0(void* self, unsigned short* wname, int a2, int a3)
{
    char* name = (char*)self + 0xB9;
    func_002C2580_impl(name, wname);
    sprintf((char*)self + 0xF9, D_004A3948, name, name);
    *(int*)((char*)self + 0x2C) = a2;
    *(int*)((char*)self + 0x20) = a3;
    func_002C48C0(self, 0x15);
}

//100%
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void* func_002C48C0(void*, int);
extern char D_004A3948[];

extern "C" void func_002C4648(void* self, const char* src, int a2, int a3)
{
    char* name = (char*)self + 0xB9;
    strcpy(name, src);
    sprintf((char*)self + 0xF9, D_004A3948, name, name);
    *(int*)((char*)self + 0x2C) = a2;
    *(int*)((char*)self + 0x20) = a3;
    func_002C48C0(self, 0x15);
}

//100%
class func_002C46C0_cObj {
public:
    // vptr at 0x0; slot N at vtable offset N*8
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
    virtual void v36(char* name, int a2, int a3); // 0x120
};

extern "C" void func_002C54D0(void* self, int a1, char* dst);

extern "C" void func_002C46C0(func_002C46C0_cObj* self, int a1, int a2, int a3)
{
    char name[64];
    func_002C54D0(self, a1, name);
    self->v36(name, a2, a3);
}

//100%
void* func_002C4720(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x2c) = a1;
    *(int*)((char*)self + 0x20) = a2;
    return func_002C48C0(self, 0x17);
}

//100%
extern "C" int func_002C4748(void* self)
{
    return *(int*)((char*)self + 0x4) == 0x34;
}

//100%
void func_002C4758(void* self)
{
    *(int*)((char*)self + 0x48) = 1;
}

//100%
void* func_002C4768(void* self)
{
    return func_002C48C0(self, 0x18);
}

//100%
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void* func_002C48C0(void*, int);
extern char D_004A3948[];

extern "C" void func_002C4788(void* self, char* src, int a2, int a3)
{
    char* name = (char*)self + 0xB9;
    strcpy(name, src);
    sprintf((char*)self + 0xF9, D_004A3948, name, name);
    *(int*)((char*)self + 0x2C) = a2;
    *(int*)((char*)self + 0x20) = a3;
    func_002C48C0(self, 0x1B);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002C54D0(void* self, int a1, char* dst);
extern "C" void func_002C4788(void* self, char* name, int a2, int a3);

extern "C" void func_002C4800(void* self, int a1, int a2, int a3)
{
    char name[64];
    func_002C54D0(self, a1, name);
    func_002C4788(self, name, a2, a3);
}

//100%
void* func_002C4858(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x2c) = a1;
    *(int*)((char*)self + 0x20) = a2;
    return func_002C48C0(self, 0x1d);
}

//100%
extern "C" int func_002C4880(void* self)
{
    return *(int*)((char*)self + 0x4) == 0x35;
}

//100%
void func_002C4890(void* self)
{
    *(int*)((char*)self + 0x44) = 1;
}

//100%
void* func_002C48A0(void* self)
{
    return func_002C48C0(self, 0x1e);
}

//100%
struct sVEnt_48C0 { short delta; short index; int (*fn)(void*, int); };
struct sPort_48C0 { int status; char pad[0x10]; };
struct sEntry_48C0 { char name[0x78]; };
struct sMC_48C0 {
    sVEnt_48C0* vt;
    int state;
    int len;
    int port;
    int pad10;
    int count;
    int fd;
    int x1C;
    int size;
    int pad24;
    int index;
    int data;
    void* buf;
    int bufSize;
    int handle;
    int x3C;
    int busy;
    int x44;
    int x48;
    char pad4C[0xC];
    char name[0x21];
    char path[0x40];
    char dir[0x40];
    char file[0x40];
    char pad139[0x4B];
    sPort_48C0 ports[2];
    char pad1AC[0x4];
    sEntry_48C0 entries[6];
    char dirbuf[0x40];
    char pad4C0[0x1000];
    char root[0x40];
};
extern "C" int func_00409D10(int h, int a1, char* name, int a3);
extern "C" int func_00409E70(int h);
extern "C" int func_00409E38(int h, int a1, char* name);
extern "C" int func_0040A090(int h, int a1, int a2);
extern "C" int func_0040A1A8(int h, int a1, int a2);
extern "C" int func_0040AA68(int h, int a1, char* name);
extern "C" int func_003DF690(char* name, int a1);
extern "C" int func_002C50E0(void* self);
extern "C" void func_002C5570(void* self, int a1);
extern char D_004A3958[];
extern int D_004A3960[];
extern char D_00487460[];
extern char* D_004459F0[];
extern char D_00445A00[];
extern char D_00445A40[];
extern char D_00445A70[];
extern char D_00445AA0[];
struct sIconSys_48C0 {
    char magic[4];
    short reserved;
    short titleOffset;
    int pad08;
    int transparency;
    int bgColor[0x10];
    int lightDir[0xC];
    int lightColor[0xC];
    int ambient[4];
    short title[0x22];
    char iconList[0x40];
    char iconCopy[0x40];
    char iconDelete[0x40];
    char pad1C4[0x200];
};
extern sIconSys_48C0 D_005376F8;

extern "C" void* func_002C48C0(void* selfp, int st)
{
    sMC_48C0* self = (sMC_48C0*)selfp;
    self->state = st;
    switch (st) {
    case 1:
        self->ports[self->port].status = D_004A3940;
        if (self->buf != 0) {
            MEM_free(self->buf);
            self->buf = 0;
        }
        if (self->fd >= 0) {
            D_004A3940 = func_00409E70(self->fd);
            if (D_004A3940 >= 0) {
                func_002C48C0(self, 2);
            }
            self->fd = -1;
        }
        self->data = 0;
        self->x1C = -1;
        self->size = 0;
        break;
    case 3:
        func_002C50E0(self);
        break;
    case 36:
        self->x48 = 0;
        D_004A3940 = func_00409E38(self->port, 0, self->file);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 37:
        sprintf(self->path, D_004A3958, self->file, D_00487460);
        D_004A3940 = func_00409D10(self->port, 0, self->path, 0x203);
        self->fd = -1;
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 38: {
        char* name = self->name;
        func_003E6448(&D_005376F8, 0, 0x3C4);
        __builtin_memcpy(&D_005376F8, D_004A3960, 5);
        func_002C2210(self, D_005376F8.title, name);
        if (self->len > 0) D_005376F8.titleOffset = self->len; else D_005376F8.titleOffset = strlen(name) * 2;
        D_005376F8.transparency = 0x60;
        func_003E6574(D_005376F8.bgColor, D_00445A00, 0x40);
        func_003E6574(D_005376F8.lightDir, D_00445A40, 0x30);
        func_003E6574(D_005376F8.lightColor, D_00445A70, 0x30);
        func_003E6574(D_005376F8.ambient, D_00445AA0, 0x10);
        strcpy(D_005376F8.iconList, D_004459F0[0]);
        strcpy(D_005376F8.iconCopy, D_004459F0[1]);
        strcpy(D_005376F8.iconDelete, D_004459F0[2]);
        D_004A3940 = func_0040A1A8(self->fd, (int)&D_005376F8, 0x3C4);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    }
    case 39:
        D_004A3940 = func_00409E70(self->fd);
        if (D_004A3940 < 0) {
            self->fd = -1;
            func_002C48C0(self, 1);
        } else {
            self->fd = -1;
        }
        break;
    case 40:
    case 44:
    case 48: {
        char buf[0x40];
        if (self->buf != 0) {
            MEM_free(self->buf);
            self->buf = 0;
        }
        int i = self->state == 0x2C ? 1 : self->state == 0x30 ? 2 : 0;
        sprintf(buf, D_004A3958, self->root, D_004459F0[i]);
        self->handle = func_003DF690(buf, 0x100);
        break;
    }
    case 41:
    case 45:
    case 49: {
        int i = self->state == 0x2D ? 1 : self->state == 0x31 ? 2 : 0;
        sprintf(self->path, D_004A3948, self->dir, D_004459F0[i]);
        D_004A3940 = func_00409D10(self->port, 0, self->path, 0x203);
        if (D_004A3940 < 0) {
            self->fd = -1;
            func_002C48C0(self, 1);
        } else {
            self->fd = -1;
        }
        break;
    }
    case 42:
    case 46:
    case 50:
        D_004A3940 = func_0040A1A8(self->fd, (int)self->buf, self->bufSize);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 43:
    case 47:
    case 51:
        if (self->buf != 0) {
            MEM_free(self->buf);
            self->buf = 0;
        }
        D_004A3940 = func_00409E70(self->fd);
        if (D_004A3940 < 0) {
            self->fd = -1;
            func_002C48C0(self, 1);
        } else {
            self->fd = -1;
        }
        break;
    case 22:
        D_004A3940 = func_00409D10(self->port, 0, self->file, 0x203);
        if (D_004A3940 < 0) {
            self->fd = -1;
            func_002C48C0(self, 1);
        } else {
            self->fd = -1;
        }
        break;
    case 23:
        D_004A3940 = func_0040A1A8(self->fd, self->data, self->size);
        self->data = 0;
        self->size = 0;
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 24:
        if (self->fd >= 0) {
            D_004A3940 = func_00409E70(self->fd);
            if (D_004A3940 < 0) {
                self->fd = -1;
                func_002C48C0(self, 1);
            } else {
                self->fd = -1;
            }
        } else {
            func_002C48C0(self, 0x19);
        }
        break;
    case 28:
        self->x44 = 0;
        D_004A3940 = func_00409D10(self->port, 0, self->file, 1);
        self->fd = -1;
        if (D_004A3940 != 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 29:
        D_004A3940 = func_0040A090(self->fd, self->data, self->size);
        if (D_004A3940 != 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 30:
        if (self->fd >= 0) {
            D_004A3940 = func_00409E70(self->fd);
            if (D_004A3940 < 0) {
                self->fd = -1;
                func_002C48C0(self, 1);
            } else {
                self->fd = -1;
            }
        } else {
            func_002C48C0(self, 0x1F);
        }
        break;
    case 54:
        self->ports[self->port].status = 0;
        D_004A3940 = func_0040AA68(self->port, 0, self->file);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 55:
    case 56:
    case 57: {
        int i = self->state == 0x38 ? 1 : self->state == 0x39 ? 2 : 0;
        sprintf(self->path, D_004A3948, self->dir, D_004459F0[i]);
        D_004A3940 = func_0040AA68(self->port, 0, self->path);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    }
    case 58:
        sprintf(self->path, D_004A3948, self->dir, D_00487460);
        D_004A3940 = func_0040AA68(self->port, 0, self->path);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 59:
        D_004A3940 = func_0040AA68(self->port, 0, self->dir);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 1);
        }
        break;
    case 7:
        for (self->index = 0; self->index < self->count; self->index++) {
            if (self->vt[0x43].fn((char*)self + self->vt[0x43].delta, self->index)) {
                sprintf(self->path, D_004A3948, (char*)self + self->index * 0x78 + 0x1B0, D_00487460);
                return func_002C48C0(self, 8);
            }
        }
        break;
    case 8:
        D_004A3940 = func_00409D10(self->port, 0, self->path, 1);
        if (D_004A3940 < 0) {
            self->fd = -1;
            func_002C5570(self, self->index);
            func_002C48C0(self, 0x10);
        } else {
            self->fd = -1;
        }
        break;
    case 10:
        D_004A3940 = func_0040A090(self->fd, (int)&D_005376F8, 0x3C4);
        if (D_004A3940 < 0) {
            func_002C5570(self, self->index);
            func_002C48C0(self, 0xF);
        }
        break;
    case 9:
        D_004A3940 = func_00409E70(self->fd);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 0x10);
        } else {
            self->fd = -1;
        }
        break;
    case 11:
        self->x3C = 0;
        sprintf(self->file, D_004A3948, (char*)self + self->index * 0x78 + 0x1B0, (char*)self + self->index * 0x78 + 0x1B0);
        func_003E6448(self->dirbuf, 0, 0x40);
        D_004A3940 = func_0040A688(self->port, 0, self->file, 0, 1, self->dirbuf);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 0x10);
        }
        break;
    case 12:
    case 13:
    case 14: {
        int i = self->state == 0xD ? 1 : self->state == 0xE ? 2 : 0;
        sprintf(self->path, D_004A3948, (char*)self + self->index * 0x78 + 0x1B0, D_004459F0[i]);
        func_003E6448(self->dirbuf, 0, 0x40);
        D_004A3940 = func_0040A688(self->port, 0, self->path, 0, 1, self->dirbuf);
        if (D_004A3940 < 0) {
            func_002C48C0(self, 0x10);
        }
        break;
    }
    case 15:
        D_004A3940 = func_00409E70(self->fd);
        if (D_004A3940 < 0) {
            self->fd = -1;
            func_002C48C0(self, 0x10);
        } else {
            self->fd = -1;
        }
        break;
    case 2:
        break;
    case 4:
        break;
    case 6:
        break;
    case 16:
        break;
    case 18:
        break;
    case 21:
        break;
    case 25:
        break;
    case 27:
        break;
    case 31:
        break;
    case 35:
        break;
    case 52:
        break;
    case 53:
        break;
    case 61:
        break;
    case 64:
        break;
    case 66:
        break;
    case 68:
        break;
    case 70:
        break;
    case 72:
        break;
    case 74:
        break;
    case 76:
        break;
    case 78:
        break;
    default:
        if (self->busy == 0) {
            func_002C50E0(self);
        }
        break;
    }
}


//100%
extern "C" int func_0040A498(int h, int a1, int* a2, int* a3, int* a4);
extern int D_004A3938;
extern int D_004A393C;
extern int D_004A3944;

extern "C" int func_002C50E0(void* self)
{
    D_004A3938 = 0;
    *(int*)((char*)self + 0x20) = 0;
    int h = *(int*)((char*)self + 0xC);
    D_004A3944 = 0;
    D_004A393C = 0;
    int r = func_0040A498(h, 0, &D_004A3938, &D_004A393C, &D_004A3944) == 0;
    *(int*)((char*)self + 0x40) = r;
    *(int*)((char*)self + 0x4C) = 5;
    return r;
}

//100%
extern "C" int func_002C5140(void* self)
{
    if (*(int*)((char*)self + 0x4) != 0 || *(int*)((char*)self + 0x40) != 0) {
        return 1;
    }
    return 0;
}

//100%
extern "C" int func_002C5168(sQTState* self)
{
    switch (self->levels[self->level].f08) {
    case -1:
    case -3:
    case -8:
    case -9:
    case -10:
    case -10001:
    case -10002:
        return 1;
    }
    return 0;
}

//100%
// PORT: the unit declares this as `extern "C" void* func_002C51D0(void*, int)`
// for its callers; the body returns an int code, bound with an asm label.
extern "C" int func_002C51D0_impl(sQTState* self, int i) __asm__("func_002C51D0");

extern "C" int func_002C51D0_impl(sQTState* self, int i)
{
    switch (self->levels[i].f08) {
    case -10002:
    case -10001:
    case -7:
    case -6:
    case -5:
    case -4:
    case -3:
    case -2:
    case -1:
    case 0:
        return self->levels[i].f08;
    case -10:
    case -9:
    case -8:
    default:
        return -10;
    }
}

extern "C" void* func_002C51D0(void*, int);

//99.38%
int func_002C5230(void* self)
{
    return (func_002C51D0(self, *(int*)((char*)self + 0xc)) != 0);
}

//100%
extern "C" void func_002C5250(sQTState* self)
{
    self->levels[self->level].f00 = 0;
    self->levels[self->level].f04 = 0;
}

//100%
extern "C" void* func_003E6448(void* dst, int c, int n);
extern "C" void func_002C52D8(void* self);

extern "C" void func_002C5278(void* self)
{
    *(int*)((char*)self + 0x50) = 0;
    *(int*)((char*)self + 0x54) = 0;
    func_003E6448((char*)self + 0x480, 0, 0x40);
    func_003E6448((char*)self + 0x1A4, 0, 0x2D0);
    func_003E6448((char*)self + 0x4C0, 0, 0x1000);
    func_002C52D8(self);
}

//100%
extern "C" void* func_003E6448(void* dst, int c, int n);

extern "C" void func_002C52D8(void* self)
{
    func_003E6448((char*)self + 0x480, 0, 0x40);
}

//100%
extern "C" int func_002C5300(void* self, int a1)
{
    char* p = (char*)self + a1 * 0x14;
    return *(int*)(p + 0x184) == -0x2712;
}

//100%
extern "C" void* func_002C5320(void* self, int a1)
{
    return *(void**)((char*)self + a1 * 0x14 + 0x180);
}

//99.29%
void* func_002C5338(void* self)
{
    return func_002C5320(self, *(int*)((char*)self + 0xc));
}

//100%
extern "C" int func_002C5358(sQTState* self, int i)
{
    switch (self->levels[i].f08) {
    case -10001:
    case -7:
    case -5:
    case -4:
    case -3:
    case -2:
    case -1:
    case 0:
        return 1;
    }
    return 0;
}

//100%
extern "C" int func_002C53B0(void* self, int a1)
{
    char* p = (char*)self + a1 * 0x14;
    return *(int*)(p + 0x188) != 0;
}

//100%
extern "C" int func_002C53C8(void* self, int a1)
{
    char* p = (char*)self + a1 * 0x14;
    return *(int*)(p + 0x18c) != 0;
}

//100%
int GetHashValue32(char*);
extern "C" unsigned short* func_002C2540(unsigned short* dst, char* src);
extern "C" int func_002C26D0(unsigned short* dst, const unsigned short* fmt, ...);
// PORT: the unit defines func_002C5320 as returning void*; it returns an int count here.
extern "C" int func_002C5320_i(void* self, int idx) __asm__("func_002C5320");
extern char D_004A3968[];
extern char D_004861F8[];
extern char* D_004A28A8;

struct sQTEntry_53E0 {
    int count;
    int status;
    void* data;
    int fC;
    int f10;
};

struct sQT_53E0 {
    char pad[0x180];
    sQTEntry_53E0 entries[1];
};

struct func_002C53E0_sVEntry {
    short delta;
    short index;
    unsigned short* (*fn)(void*, int);
};

extern "C" void func_002C53E0(sQT_53E0* self, int idx, unsigned short* dst)
{
    if (self->entries[idx].data == 0) {
        func_002C2540(dst, D_004A3968);
        return;
    }
    switch (self->entries[idx].status) {
    case -2:
        func_002C2540(dst, D_004A3968);
        break;
    case 0: {
        // PORT: g++ `>?` (max) operator, removed in GCC 4.3.
        int v = func_002C5320_i(self, idx) >? 0;
        char* obj = *(char**)(D_004A28A8 + 0x8C);
        func_002C53E0_sVEntry* vt = *(func_002C53E0_sVEntry**)(obj + 4);
        char* thisp = obj + vt[4].delta;
        func_002C26D0(dst, vt[4].fn(thisp, GetHashValue32(D_004861F8)), v);
        break;
    }
    default:
        func_002C2540(dst, D_004A3968);
        break;
    }
}

//100%
extern "C" char* strcpy(char* dst, const char* src);

extern "C" void func_002C54D0(void* self, int a1, char* dst)
{
    char* p = (char*)self + a1 * 0x78;
    strcpy(dst, p + 0x1b0);
}

extern "C" void* func_002C2580(void*);

//99.29%
void* func_002C5500(void* self)
{
    return func_002C2580((char*)self + 0x58);
}

//100%
void func_002C5520(void* self)
{
}

//100%
extern "C" int strlen(const char* s);

extern "C" bool func_002C5528(void* self, int a1)
{
    char* p = (char*)self + a1 * 0x78;
    return strlen(p + 0x1b0) != 0;
}

//100%
extern "C" void func_002C5558(void* self, int a1)
{
    char* p = (char*)self + a1 * 0x78;
    *(int*)(p + 0x1a4) = 1;
}

//100%
extern "C" void func_002C5570(void* self, int a1)
{
    char* p = (char*)self + a1 * 0x78;
    *(int*)(p + 0x1a8) = 1;
}

//100%
struct sQTSlot {
    int a;
    int b;
    char pad08[0x70];
};

struct sQTSlots {
    char pad000[0x1A4];
    sQTSlot slots[1];
};

extern "C" int func_002C5588(sQTSlots* self, int i)
{
    if (self->slots[i].b != 0 || self->slots[i].a != 0) {
        return 1;
    }
    return 0;
}

//100%
extern "C" int func_002C55C0(void* self, int a1)
{
    char* p = (char*)self + a1 * 0x78;
    return *(int*)(p + 0x1ac) != 0;
}

//100%
struct sMCPort_55D8 {
    int a;
    int b;
    int status;
    int d;
    int e;
};
struct sMCEnt_55D8 {
    int f0;
    int f4;
    int f8;
    char name[0x40];
    char x4C[0x22];
    char x6E[8];
    char pad76[2];
};
struct sMC_55D8 {
    char* vt;
    int state;
    int x08;
    int port;
    int port2;
    int count;
    int x18;
    int x1C;
    int size;
    int x24;
    int index;
    int x2C;
    int x30;
    int x34;
    int handle;
    int x3C;
    int busy;
    int x44;
    int x48;
    int x4C;
    int x50;
    int x54;
    char name[0x21];
    char path[0x40];
    char dir[0x40];
    char padF9[0x83];
    sMCPort_55D8 ports[2];
    sMCEnt_55D8 entries[6];
    char pad474[0x14];
    char x488[8];
    int x490;
    char pad494[0x4C];
    char dirbuf[0x40][0x40];
};
typedef int (*fn1_55D8)(void*);
typedef int (*fn2_55D8)(void*, int);
typedef void (*fn2v_55D8)(void*, int);
// PORT: the unit declares these later with other signatures; bound by asm label.
extern "C" int func_0040A360_i(int a0, int* a1, int* out) __asm__("func_0040A360");
extern "C" int func_002C51D0_i(void* self, int i) __asm__("func_002C51D0");
extern "C" void func_002C6280_v(void* self) __asm__("func_002C6280");
extern "C" int func_002C63E8(void* self, unsigned int a1);
extern "C" int func_003DF980(int h);
extern "C" void ASYNCFILE_release(int h, int* a, int* b);
extern "C" void func_002C4210(void* self);
extern "C" void func_002C42B0(void* self);
extern "C" void func_002C4388(void* self);
extern "C" void func_002C4410(void* self);
extern "C" void func_002C6848(void* self);
extern "C" void func_002C69A0(void* self);
extern "C" void func_002C6A28(void* self);
extern "C" void func_002C6A88(void* self);
extern "C" void func_002C6B00(void* self);
extern "C" void func_002C6B78(void* self);
extern "C" void func_002C6BF8(void* self);
extern "C" void func_002C6C88(void* self);
extern "C" void func_002C6D18(void* self);
extern int D_00487450[];
// PORT: void-returning alias of func_003E6448 (memset); the unused result changes register choice in case 6.
extern "C" void func_003E6448_v(void* dst, int c, int n) __asm__("func_003E6448");
extern short D_005377B8[];

#define VC1_55D8(s, o) (((fn1_55D8)*(void**)((s)->vt + (o) + 4))((char*)(s) + *(short*)((s)->vt + (o))))
#define VC2v_55D8(s, o, x) (((fn2v_55D8)*(void**)((s)->vt + (o) + 4))((char*)(s) + *(short*)((s)->vt + (o)), x))
#define VC2_55D8(s, o, x) (((fn2_55D8)*(void**)((s)->vt + (o) + 4))((char*)(s) + *(short*)((s)->vt + (o)), x))

extern "C" void func_002C55D8(sMC_55D8* self)
{
    if (self->ports[self->port].d == 0) {
        self->x50 = 0;
        self->x54 = 0;
        func_003E6448(self->entries, 0, 0x2D0);
    }
    int one = 1;
    self->x3C = one;
    if (self->busy != 0) {
        int tmp;
        D_004A3940 = 0;
        tmp = 0;
        if (func_0040A360_i(1, &tmp, &D_004A3940) == 0) {
            return;
        }
        int r = D_004A3940;
        if (r == -1) {
            goto set;
        }
        if (r == -2) {
        set:
            *(int*)((char*)self + self->port2 * 0x14 + 0x18C) = one;
            r = D_004A3940;
        }
        if ((unsigned)(r + 19) < 9 || (unsigned)(r + 49) < 10 || (unsigned)(r + 59) < 10 || (unsigned)(r + 79) < 10) {
            D_004A3940 = -10;
        }
        if (func_002C63E8(self, D_004A3940) == 0) {
            if (D_004A3938 != 2) {
                D_004A3940 = -10002;
            } else if (D_004A3944 == 0) {
                D_004A3940 = -2;
            }
        }
        self->busy = 0;
        self->ports[self->port2].status = D_004A3940;
        self->ports[self->port2].a = D_004A3938;
        self->ports[self->port2].b = D_004A393C;
        self->ports[self->port2].d = D_004A3944;
    }
    switch (self->state) {
    case 2: case 6: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 18: case 22: case 23: case 24: case 28: case 29: case 30: case 35: case 36: case 37:
    case 38: case 39: case 41: case 42: case 43: case 45: case 46: case 47: case 49: case 50:
    case 51: case 54: case 55: case 56: case 57: case 58: case 59: case 61: case 64: case 66:
    case 68: case 70: case 72: case 74: case 76: case 78:
        {
            self->x3C = 0;
            D_004A3940 = 0;
            if (func_0040A360_i(1, 0, &D_004A3940) == 0) {
                return;
            }
            self->x3C = 1;
            if (D_004A3940 == -1) {
                self->ports[self->port].e = 1;
            }
            int r = D_004A3940;
            if (r < 0) {
                int st = self->state;
                if (st != 36 && (unsigned)(st - 54) >= 6) {
                    if ((unsigned)(st - 8) < 8 && r != -1 && func_002C63E8(self, r) == 0) {
                        VC2v_55D8(self, 0x140, self->index);
                        func_002C48C0(self, 0x10);
                        return;
                    }
                } else {
                    if (r == -4) {
                        D_004A3940 = 0;
                    }
                }
                if (D_004A3940 < 0) {
                    if (self->state == 35 || self->state == 7) {
                        func_002C52D8(self);
                    }
                    if (self->state == 19) {
                        self->x1C = -1;
                    }
                    func_002C48C0(self, 1);
                    return;
                }
            }
            self->ports[self->port].status = 0;
        }
        break;
    }
    if (self->x44 != 0) {
        self->x44 = 0;
        func_002C48C0(self, 0x1E);
        return;
    }
    if (self->x48 != 0) {
        self->x48 = 0;
        func_002C48C0(self, 0x18);
        return;
    }
    switch (self->state) {
    case 0:
    case 1:
    case 78:
        break;
    case 2:
        D_004A3940 = 0;
        if (func_0040A360_i(1, 0, &D_004A3940) == 0) {
            return;
        }
        if (D_004A3940 == -1) {
            self->ports[self->port].e = 1;
        }
        break;
    case 3:
        func_002C48C0(self, 4);
        break;
    case 5:
        if (VC1_55D8(self, 0x248) == 0) {
            func_002C4210(self);
            return;
        }
        break;
    case 34:
        if (VC1_55D8(self, 0x248) == 0) {
            func_002C42B0(self);
            return;
        }
        break;
    case 6:
        {
            int i;
            self->x50 = self->count;
            func_003E6448_v(self->entries, 0, 0x2D0);
            for (i = 0; i < self->count; i++) {
                unsigned char c = i + '1';
                int j;
                for (j = 0; j < self->x50; j++) {
                    int n = strlen(self->dirbuf[j]);
                    if (n != 0 && (unsigned char)self->dirbuf[j][n - 1] == c) {
                        strcpy(self->entries[i].name, self->dirbuf[j]);
                        break;
                    }
                }
            }
            D_004A3940 = 0;
            func_002C48C0(self, 7);
            return;
        }
    case 8:
        self->x18 = D_004A3940;
        func_002C48C0(self, 10);
        return;
    case 10:
        func_002C2268(self, self->entries[self->index].x4C, D_005377B8);
        func_002C48C0(self, 9);
        return;
    case 9:
        func_002C48C0(self, 11);
        return;
    case 11:
        if (self->x490 != self->x24) {
            VC2v_55D8(self, 0x140, self->index);
            func_002C48C0(self, 0x10);
        }
        __builtin_memcpy(self->entries[self->index].x6E, self->x488, 8);
        func_002C48C0(self, 12);
        return;
    case 12:
    case 13:
    case 14:
        {
            int k;
            if (self->state != 13) {
                k = self->state == 14 ? 2 : 0;
            } else {
                k = 1;
            }
            if (self->x490 != D_00487450[k]) {
                func_002C5570(self, self->index);
                func_002C48C0(self, 0x10);
                return;
            }
        }
        goto next;
    case 15:
    case 16:
    next:
        while (++self->index < self->count) {
            if (VC2_55D8(self, 0x218, self->index) != 0) {
                goto found;
            }
        }
    case 7:
        func_002C6280_v(self);
        break;
    case 35:
        if (D_004A3940 != 1) {
            func_002C52D8(self);
        }
        D_004A3940 = 0;
        break;
    case 17:
        if (self->ports[self->port].d != 0) {
            break;
        }
        func_002C4388(self);
        return;
    case 19:
        if (VC1_55D8(self, 0x248) != 0) {
            break;
        }
        func_002C4410(self);
        return;
    case 40:
    case 44:
    case 48:
        if (func_003DF980(self->handle) != 1) {
            return;
        }
        self->x30 = 0;
        self->x34 = 0;
        ASYNCFILE_release(self->handle, &self->x30, &self->x34);
        func_002C48C0(self, self->state + 1);
        return;
    case 22:
    case 28:
    case 37:
    case 41:
    case 45:
    case 49:
        self->x18 = D_004A3940;
        func_002C48C0(self, self->state + 1);
        return;
    case 20:
        if (VC1_55D8(self, 0x248) != 0) {
            break;
        }
        func_002C48C0(self, 0x24);
        return;
    case 27:
        if (VC1_55D8(self, 0x248) != 0) {
            break;
        }
        func_002C48C0(self, 0x1C);
        return;
    case 55:
    case 56:
        func_002C48C0(self, 0x3A);
        return;
    case 36:
    case 38:
    case 39:
    case 42:
    case 46:
    case 50:
    case 54:
    case 57:
    case 58:
        func_002C48C0(self, self->state + 1);
        return;
    case 21:
        if (VC1_55D8(self, 0x248) != 0) {
            break;
        }
        func_002C48C0(self, 0x16);
        return;
    case 23:
        func_002C48C0(self, 0x34);
        return;
    case 29:
        if (D_004A3940 != self->size) {
            D_004A3940 = -10001;
            func_002C48C0(self, 1);
            return;
        }
        func_002C48C0(self, 0x35);
        return;
    case 25:
        self->x3C = 0;
        self->entries[self->x1C].f4 = 0;
        self->entries[self->x1C].f0 = 0;
        self->entries[self->x1C].f8 = 0;
        strcpy(self->entries[self->x1C].name, self->dir);
        strcpy(self->entries[self->x1C].x4C, self->name);
        break;
    case 60:
        if (VC1_55D8(self, 0x248) != 0) {
            break;
        }
        func_002C6848(self);
        return;
    case 61:
        self->x54 = D_004A3940;
        break;
    case 63:
        if (VC1_55D8(self, 0x248) != 0) {
            break;
        }
        func_002C69A0(self);
        return;
    case 73:
        if (VC1_55D8(self, 0x248) != 0 || self->x18 < 0) {
            break;
        }
        func_002C6A28(self);
        return;
    case 65:
        if (VC1_55D8(self, 0x248) != 0 || self->x18 < 0) {
            break;
        }
        func_002C6A88(self);
        return;
    case 71:
        if (VC1_55D8(self, 0x248) != 0 || self->x18 < 0) {
            break;
        }
        func_002C6B00(self);
        return;
    case 67:
        if (VC1_55D8(self, 0x248) != 0 || self->x18 < 0) {
            break;
        }
        func_002C6B78(self);
        return;
    case 69:
        if (VC1_55D8(self, 0x248) != 0 || self->x18 < 0) {
            break;
        }
        func_002C6BF8(self);
        return;
    case 75:
        if (VC1_55D8(self, 0x248) != 0) {
            break;
        }
        func_002C6C88(self);
        return;
    case 77:
        if (VC1_55D8(self, 0x248) != 0) {
            break;
        }
        func_002C6D18(self);
        return;
    case 64:
        {
            int v = D_004A3940;
            self->state = 0;
            self->x18 = v;
        }
        break;
    case 74:
        self->state = 0;
        self->x18 = -1;
        break;
    found:
        sprintf(self->path, D_004A3948, self->entries[self->index].name, D_00487460);
        func_002C48C0(self, 8);
        return;
    case 52:
    case 53:
        return;
    case 66:
    case 68:
    case 70:
    case 72:
        self->state = 0;
        break;
    }
    if (func_002C51D0_i(self, self->port) == -10 || func_002C51D0_i(self, self->port) == -1) {
        func_002C5250((sQTState*)self);
    }
    if (func_002C51D0_i(self, self->port) == -10 || func_002C51D0_i(self, self->port) == -2) {
        func_002C5278(self);
    }
    if (self->state != 0) {
        func_002C48C0(self, 0);
    }
}

//100%
struct sQTVt6128 {
    short delta;
    short index;
    int (*fn)(void*);
};

struct sQTVtI6128 {
    short delta;
    short index;
    int (*fn)(void*, int);
};

struct sQTEnt6128 {
    int f0;                     // 0x00 (self + 0x1A4)
    int f4;                     // 0x04
    int f8;                     // 0x08
    char padC[0x52 - 0xC];
    char name[0x78 - 0x52];     // 0x52 (self + 0x1F6)
};

struct sQT6128 {
    sQTVt6128* vt;              // 0x000
    char pad4[0x1A0];
    sQTEnt6128 ents[1];         // 0x1A4
};

extern char D_00486490[];
extern char D_004864A0[];
extern char D_004864B8[];
extern char D_004864D0[];

static inline unsigned short* qtLoc6128(char* key)
{
    char* obj = *(char**)(D_004A28A8 + 0x8C);
    func_002C53E0_sVEntry* vt = *(func_002C53E0_sVEntry**)(obj + 4);
    char* thisp = obj + vt[4].delta;
    return vt[4].fn(thisp, GetHashValue32(key));
}

extern "C" void func_002C6128(sQT6128* self, int i, unsigned short* dst)
{
    unsigned short buf[64];
    if (self->vt[53].fn((char*)self + self->vt[53].delta) == 0) {
        func_002C2508(buf, qtLoc6128(D_00486490));
    } else if (self->vt[55].fn((char*)self + self->vt[55].delta) == 0) {
        func_002C2508(buf, qtLoc6128(D_004864A0));
    } else if (self->ents[i].f0 != 0 || self->ents[i].f4 != 0) {
        func_002C2508(buf, qtLoc6128(D_004864B8));
    } else if (self->ents[i].f8 != 0) {
        func_002C2508(buf, qtLoc6128(D_004864D0));
    } else if (((sQTVtI6128*)self->vt)[67].fn((char*)self + self->vt[67].delta, i) == 0) {
        func_002C2508(buf, qtLoc6128(D_00486490));
    } else {
        func_002C2540(buf, self->ents[i].name);
    }
    buf[32] = 0;
    func_002C2508(dst, buf);
}

//100%
class func_002C6280_cObj {
public:
    // vptr at 0x0; slot N at vtable offset N*8
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
    virtual int v20();
    virtual void v21();
    virtual int v22(int a);
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
    virtual int v67(int i);
};

struct func_002C6280_sElem {
    int flag;
    char pad[0x74];
};

struct func_002C6280_sData {
    char pad[0x1AC];
    func_002C6280_sElem elems[1];
};

extern "C" void func_002C6280(func_002C6280_cObj* self)
{
    int i = 0;
    int remain = self->v20();
    int unit = self->v22(*(int*)((char*)self + 0x24));
    for (; i < *(int*)((char*)self + 0x14); i++) {
        ((func_002C6280_sData*)self)->elems[i].flag = 0;
        if (self->v67(i) == 0) {
            if (remain >= unit) {
                remain -= unit;
            } else {
                ((func_002C6280_sData*)self)->elems[i].flag = 1;
            }
        }
    }
}

//100%
extern "C" void func_0040A360(int a0, int a1, int* out);
extern "C" void func_002C5278(void* self);
extern int D_004A3940;

extern "C" void func_002C6360(void* p)
{
    sQTState* self = (sQTState*)p;
    if (*(int*)((char*)self + 0x40) != 0) {
        D_004A3940 = 0;
        func_0040A360(0, 0, &D_004A3940);
        if (D_004A3940 == -1) {
            self->levels[self->level].f10 = 1;
        }
    }
    *(int*)((char*)self + 0x40) = 0;
    self->level = 0;
    *(int*)((char*)self + 0x17C) = 0;
    *(int*)((char*)self + 0x180) = 0;
    *(int*)((char*)self + 0x184) = 0;
    *(int*)((char*)self + 0x188) = 0;
    *(int*)((char*)self + 0x3C) = 0;
    func_002C5278(self);
}

//100%
extern "C" int func_002C63E8(void* self, unsigned int a1)
{
    return a1 + 0x270f < 0x2706;
}

//100%
int GetHashValue32(char*);
extern "C" unsigned short* func_002C2540(unsigned short* dst, char* src);
extern "C" int func_002C26D0(unsigned short* dst, const unsigned short* fmt, ...);
// PORT: void view of func_002C26D0 (defined returning int); this caller treats it as void.
extern "C" void func_002C26D0_v(unsigned short* dst, const unsigned short* fmt, ...) __asm__("func_002C26D0");
extern char D_004A3970[];
extern char D_004864E8[];
extern char* D_004A28A8;

struct func_002C63F8_sVEntry {
    short delta;
    short index;
    unsigned short* (*fn)(void*, int);
};

extern "C" void func_002C63F8(void* self, int n, unsigned short* dst)
{
    unsigned short fmt[8];
    unsigned short num[8];
    func_002C2540(fmt, D_004A3970);
    func_002C26D0_v(num, fmt, n + 1);
    if (n < 2) {
        if (n >= 0) {
            char* obj = *(char**)(D_004A28A8 + 0x8C);
            func_002C63F8_sVEntry* vt = *(func_002C63F8_sVEntry**)(obj + 4);
            char* thisp = obj + vt[4].delta;
            func_002C26D0(dst, vt[4].fn(thisp, GetHashValue32(D_004864E8)), num);
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A3968[];

extern "C" void func_002C64A8(void* self, int a1, unsigned short* dst)
{
    func_002C2540(dst, D_004A3968);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A3968[];

extern "C" void func_002C64D0(void* self, int a1, unsigned short* dst)
{
    func_002C2540(dst, D_004A3968);
}

//100%
struct sSaveSlot_2C64F8 {
    int busy;               // 0x00
    int locked;             // 0x04
    int bad;                // 0x08
    char pad0C[0x63];
    unsigned char sec;      // 0x6F
    unsigned char min;      // 0x70
    unsigned char hour;     // 0x71
    unsigned char day;      // 0x72
    unsigned char month;    // 0x73
    unsigned short year;    // 0x74
    char pad76[0x2];
};
struct sSaveMgrBase_2C64F8 {
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
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual int v55();
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
    virtual int v67(int slot);
};
struct sSaveMgr_2C64F8 : sSaveMgrBase_2C64F8 {
    char pad4[0x1A0];
    sSaveSlot_2C64F8 slots[6];  // 0x1A4
};

extern "C" int func_002C64F8(sSaveMgr_2C64F8* self)
{
    int best = -1;
    if (self->v55() == 0) {
        return -1;
    }
    for (int i = 0; i < 6; i++) {
        if (self->slots[i].busy == 0 && self->slots[i].locked == 0 && self->v67(i) != 0 && self->slots[i].bad == 0) {
            if (best != -1) {
                unsigned int ct = self->slots[i].hour * 3600 + self->slots[i].min * 60 + self->slots[best].sec;
                unsigned short cy = self->slots[i].year;
                unsigned char cd = self->slots[i].day;
                unsigned int bt = self->slots[best].hour * 3600 + self->slots[best].min * 60 + self->slots[best].sec;
                unsigned short by = self->slots[best].year;
                unsigned char bm = self->slots[best].month;
                unsigned char bd = self->slots[best].day;
                unsigned char cm = self->slots[i].month;
                if (cy < by) {
                } else if (by < cy) {
                    best = i;
                } else if (cm < bm) {
                } else if (bm < cm) {
                    best = i;
                } else if (cd < bd) {
                } else if (bd < cd) {
                    best = i;
                } else if (ct < bt) {
                } else if (bt < ct) {
                    best = i;
                }
            } else {
                best = i;
            }
        }
    }
    return best;
}

//100%
extern "C" char* strcpy(char* dst, const char* src);

extern "C" void func_002C66B8(void* self, const char* name, int flag)
{
    if (flag == 0) {
        strcpy((char*)self + 0x14C0, name);
    }
}

//100%
extern "C" int func_002C66D8(void* self)
{
    char* p = (char*)self + *(int*)((char*)self + 0xc) * 0x14;
    return *(int*)(p + 0x184) == -0xb;
}

//100%
int func_002C6700(void* self)
{
    return 0x1;
}

//100%
int func_002C6708(void* self)
{
    return 0x1;
}

//100%
int func_002C6710(void* self)
{
    return 0x1;
}

//100%
#define QT_V10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
    virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class cQuadTreeVObj {
public:
    // vptr at 0x0; slot N at vtable offset N*8 (delta at +0, function at +4)
    virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    QT_V10(v1)
    virtual void v20(); virtual void v21();
    virtual int v22(int a); // 0xB0
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29();
    QT_V10(v3) QT_V10(v4)
    virtual int v50(int a); // 0x190
    virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
    virtual int v61(int a); // 0x1E8
};

extern "C" void func_002C6718(cQuadTreeVObj* self)
{
    self->v61(*(int*)((char*)self + 0xC));
}

//100%
int func_002C6748(void* self)
{
    return 0x4000;
}

//100%
int func_002C6750(void* self)
{
    return -0x1;
}

//100%
extern "C" int func_002C6758(void* self, int a1)
{
    return (a1 + 0x3ff) / 0x400 + 0x4d;
}

//100%
#define QT_V10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
    virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

extern "C" void func_002C6778(cQuadTreeVObj* self)
{
    self->v22(*(int*)((char*)self + 0x24));
}

//100%
int func_002C67A8(void* self)
{
    return 0;
}

//100%
#define QT_V10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
    virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

extern "C" void func_002C67B0(cQuadTreeVObj* self)
{
    self->v50(*(int*)((char*)self + 0xC));
}

//100%
int func_002C67E0(void* self)
{
    return -0x1;
}

//100%
void* func_002C67E8(void* self, int a1)
{
    *(int*)((char*)self + 0xc) = a1;
    *(int*)((char*)self + 0x10) = a1;
    return func_002C48C0(self, 3);
}

//100%
extern "C" void func_002C6810(void* self, const char* name)
{
    *(int*)((char*)self + 0x54) = 0;
    strcpy((char*)self + 0x139, name);
    func_002C48C0(self, 0x3C);
}

//100%
extern "C" int func_0040A688(int h, int a1, char* name, int a3, int a4, void* buf);
extern int D_004A3940;
extern "C" void* func_003E6448(void* dst, int c, int n);

extern "C" void func_002C6848(void* self)
{
    char* buf = (char*)self + 0x4C0;
    func_003E6448(buf, 0, 0x1000);
    int r = func_0040A688(*(int*)((char*)self + 0xC), 0, (char*)self + 0x139, 0, 0x40, buf);
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x3D);
    }
}

//100%
extern "C" char* strcpy(char* dst, const char* src);

extern "C" void func_002C68C8(void* self, int i, char* dst)
{
    // PORT: (int)self pointer arithmetic (index added first, as in the target).
    strcpy(dst, (char*)((i << 6) + (int)self) + 0x4E0);
}

//100%
extern "C" int strlen(const char* s);

struct func_002C68F0_sName {
    char name[0x78];
};

struct func_002C68F0_sTree {
    char pad_0x00[0x14];
    int count;                          // 0x14
    char pad_0x18[0x1B0 - 0x18];
    func_002C68F0_sName names[1];       // 0x1B0
};

extern "C" int func_002C68F0(func_002C68F0_sTree* self)
{
    int n = 0;
    int i;
    for (i = 0; i < self->count; i++) {
        if (strlen(self->names[i].name) != 0) {
            n++;
        }
    }
    return n;
}

//100%
extern "C" void func_002C6968(void* self, const char* name, int a2)
{
    *(int*)((char*)self + 0x14E0) = a2;
    strcpy((char*)self + 0xF9, name);
    func_002C48C0(self, 0x3F);
}

//100%
extern "C" int func_00409D10(int h, int a1, char* name, int a3);
extern int D_004A3940;

extern "C" void func_002C69A0(void* self)
{
    *(int*)((char*)self + 0x18) = -1;
    int r = func_00409D10(*(int*)((char*)self + 0xC), 0, (char*)self + 0xF9, *(int*)((char*)self + 0x14E0));
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x40);
    }
}

//100%
void* func_002C6A08(void* self)
{
    return func_002C48C0(self, 0x49);
}

//100%
// PORT: the unit declares func_002C48C0 as returning void*, but its body returns
// nothing (v0 is leftover); this caller needs the void prototype.
extern "C" void func_002C48C0_v(void* self, int state) __asm__("func_002C48C0");
extern "C" int func_00409E70(int h);
extern int D_004A3940;

extern "C" void func_002C6A28(void* self)
{
    D_004A3940 = func_00409E70(*(int*)((char*)self + 0x18));
    func_002C48C0_v(self, 0x4A);
}

//100%
void* func_002C6A60(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x14e4) = a1;
    *(int*)((char*)self + 0x14e8) = a2;
    return func_002C48C0(self, 0x41);
}

//100%
extern "C" int func_00409F28(int h, int a1, int a2);
extern int D_004A3940;

extern "C" void func_002C6A88(void* self)
{
    int r = func_00409F28(*(int*)((char*)self + 0x18), *(int*)((char*)self + 0x14E4), *(int*)((char*)self + 0x14E8));
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x42);
    }
}

//100%
void* func_002C6AE0(void* self)
{
    return func_002C48C0(self, 0x47);
}

//100%
extern "C" int func_0040AB80(int h);
extern int D_004A3940;

extern "C" void func_002C6B00(void* self)
{
    int r = func_0040AB80(*(int*)((char*)self + 0x18));
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x48);
    }
}

//100%
void* func_002C6B50(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x2c) = a1;
    *(int*)((char*)self + 0x24) = a2;
    return func_002C48C0(self, 0x43);
}

//100%
extern "C" int func_0040A090(int h, int a1, int a2);
extern int D_004A3940;

extern "C" void func_002C6B78(void* self)
{
    int r = func_0040A090(*(int*)((char*)self + 0x18), *(int*)((char*)self + 0x2C), *(int*)((char*)self + 0x24));
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x44);
    }
}

//100%
void* func_002C6BD0(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x2c) = a1;
    *(int*)((char*)self + 0x24) = a2;
    return func_002C48C0(self, 0x45);
}

//100%
extern "C" int func_0040A1A8(int h, int a1, int a2);
extern int D_004A3940;

extern "C" void func_002C6BF8(void* self)
{
    int r = func_0040A1A8(*(int*)((char*)self + 0x18), *(int*)((char*)self + 0x2C), *(int*)((char*)self + 0x24));
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x46);
    }
}

//100%
extern "C" void func_002C6C50(void* self, const char* name, int a2)
{
    *(int*)((char*)self + 0x20) = a2;
    strcpy((char*)self + 0xF9, name);
    func_002C48C0(self, 0x4B);
}

//100%
extern "C" int func_00409E38(int h, int a1, char* name);
extern int D_004A3940;

extern "C" void func_002C6C88(void* self)
{
    int r = func_00409E38(*(int*)((char*)self + 0xC), 0, (char*)self + 0xF9);
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x4C);
    }
}

//100%
extern "C" void func_002C6CE0(void* self, const char* name)
{
    strcpy((char*)self + 0xF9, name);
    func_002C48C0(self, 0x4D);
}

//100%
extern "C" int func_0040AA68(int h, int a1, char* name);
extern int D_004A3940;

extern "C" void func_002C6D18(void* self)
{
    int r = func_0040AA68(*(int*)((char*)self + 0xC), 0, (char*)self + 0xF9);
    D_004A3940 = r;
    if (r < 0) {
        func_002C48C0(self, 1);
    } else {
        func_002C48C0(self, 0x4E);
    }
}

//100%
void operator_delete(int* ptr);
extern "C" void MEM_free(void* p);

extern "C" void func_002C6D70(void* self, int flags)
{
    void* p = *(void**)((char*)self + 0x4);
    if (p != 0) {
        MEM_free(p);
    }
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

extern "C" void* func_003DBB68(int);

//100%
void* func_002C6DC0(void* self)
{
    return func_003DBB68(*(int*)((char*)self + 0x4));
}

//100%
struct func_002C6DE0_sEntry {
    unsigned int key;
    int value;
};

struct func_002C6DE0_sMap {
    int pad0;
    int pad4;
    int last;
    int count;
    func_002C6DE0_sEntry* entries;
};

extern "C" int func_002C6DE0(func_002C6DE0_sMap* self, unsigned int key)
{
    int lo = 0;
    int hi = self->last;
    if (self->count != 0) {
        if (self->entries[hi].key < key || key < self->entries[0].key) {
            return 0;
        }
        int mid = hi >> 1;
        while (self->entries[mid].key != key) {
            if (key < self->entries[mid].key) {
                hi = mid;
            } else {
                lo = mid;
            }
            int next = ((hi - lo) >> 1) + lo;
            if (next == mid) {
                return 0;
            }
            mid = next;
        }
        return self->entries[mid].value;
    }
    return 0;
}

INCLUDE_ASM("worldpainter/quadtree", func_002C6E98);

