#include "common.h"

struct cMenuItem {
    char pad_0x00[0x4];
    int field_0x4;
    void* field_0x8;
    int field_0xC;
    void* vtable; // 0x10
};
extern void* D_00486F28[16];

//100%
cMenuItem* cMenuItem_cMenuItem(cMenuItem* self, void* text)
{
    self->vtable = D_00486F28;
    self->field_0x4 = 1;
    self->field_0x8 = text;
    self->field_0xC = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern "C" void func_002CA280(int* self, int flags)
{
    *(void***)((char*)self + 0x10) = D_00486F28;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
extern "C" int func_002CA3E8(void** self);

extern "C" int func_002CA2B0(void* self)
{
    switch (func_002CA3E8((void**)self)) {
    case 8:
        return 1;
    case 7:
        return 2;
    case 0:
        return 4;
    case 1:
        return 3;
    }
    return 0;
}

//100%
extern "C" int func_002CA378(void* self);
extern "C" int func_002CA3B0(void* self);

extern "C" int func_002CA320(void* self)
{
    int r = 0;
    if (func_002CA378(self) != 0) {
        r = func_002CA3B0(self) == 0;
    }
    return r;
}

//100%
void func_002CA368(void* self)
{
}

//100%
void func_002CA370(void* self)
{
}

//100%
extern "C" int func_002CA378(void* self)
{
    return *(int*)((char*)self + 0x4) & 1;
}

//100%
extern "C" void func_002CA388(void* self, int enable)
{
    if (enable) {
        *(int*)((char*)self + 0x4) |= 1;
    } else {
        *(int*)((char*)self + 0x4) &= ~1;
    }
}

//100%
extern "C" int func_002CA3B0(void* self)
{
    return *(int*)((char*)self + 0x4) & 8;
}

//100%
extern "C" void func_002CA3C0(void* self, int enable)
{
    if (enable) {
        *(int*)((char*)self + 0x4) |= 8;
    } else {
        *(int*)((char*)self + 0x4) &= ~8;
    }
}

//100%
int func_002CC248(void* self);

extern "C" int func_002CA3E8(void** self)
{
    return func_002CC248(*(void**)((char*)*self + 0x124));
}

// PORT: func_002CC260 is C++ (void*); this caller passes an int handle.
void* func_002CC260(int) __asm__("func_002CC260__FPv");

//100%
void* func_002CA408(void* self)
{
    return func_002CC260(*(int*)((char*)*(void**)self + 0x124));
}

// PORT: func_002CC280 is C++ (void*); this caller passes an int handle.
void* func_002CC280(int) __asm__("func_002CC280__FPv");

//100%
void* func_002CA428(void* self)
{
    return func_002CC280(*(int*)((char*)*(void**)self + 0x124));
}

// PORT: func_002CC2A0 is C++ (void*); this caller passes an int handle.
void* func_002CC2A0(int) __asm__("func_002CC2A0__FPv");

//100%
void* func_002CA448(void* self)
{
    return func_002CC2A0(*(int*)((char*)*(void**)self + 0x124));
}

// PORT: func_002CC2C0 is C++ (void*); this caller passes an int handle.
void* func_002CC2C0(int) __asm__("func_002CC2C0__FPv");

//100%
void* func_002CA468(void* self)
{
    return func_002CC2C0(*(int*)((char*)*(void**)self + 0x124));
}

extern "C" void* func_002CC2E0(int);

//100%
void* func_002CA488(void* self)
{
    return func_002CC2E0(*(int*)((char*)*(void**)self + 0x124));
}

extern "C" void* func_002CC318(int);

//100%
void* func_002CA4A8(void* self)
{
    return func_002CC318(*(int*)((char*)*(void**)self + 0x124));
}

INCLUDE_ASM("util/menu", func_002CA4C8);

//100%
extern "C" void func_00391CB0(void* self, float x, float y, const char* str);
extern "C" float func_00391FB0(void* self, const char* str, void* out, int n, float sx, float sy);

struct sRect_2CA768 { float x, y, w, h; };
struct sColor_2CA768 { float r, g, b, a; };
struct sVec2_2CA768 {
    float x, y;
    sVec2_2CA768(float ax, float ay) : x(ax), y(ay) {}
};

struct sVEnt_2CA768 { short delta; short index; void (*fn)(void*, sRect_2CA768*, char*); };

static inline char* font_2CA768(char* item)
{
    return *(char**)(*(char**)(*(char**)item + 0x124) + 0x58);
}

// PORT: the unit's callers declare func_002CA768 as (void*, int, int, int, void*, char*, sColor*) returning void*;
// the body takes (item, rect, left, center, right, style, color) and returns nothing. Bound by asm label.
extern "C" void func_002CA768_impl(char* item, sRect_2CA768* rect, const char* left, const char* center, const char* right, char* style, sColor_2CA768* color) __asm__("func_002CA768");

extern "C" void func_002CA768_impl(char* item, sRect_2CA768* rect, const char* left, const char* center, const char* right, char* style, sColor_2CA768* color)
{
    char* menu = *(char**)item;
    sVEnt_2CA768* vt = *(sVEnt_2CA768**)(menu + 0x12C);
    vt[8].fn(menu + vt[8].delta, rect, style);
    *(sColor_2CA768*)(font_2CA768(item) + 0x40) = *color;
    char* f0 = font_2CA768(item);
    sVec2_2CA768 sc(2.0f, 2.0f);
    *(sVec2_2CA768*)(f0 + 0x28) = sc;
    if (left) {
        func_00391CB0(font_2CA768(item), rect->x + 16.0f, rect->y + 6.0f - 1.0f, left);
    }
    if (center) {
        char* f = font_2CA768(item);
        float w = func_00391FB0(f, center, 0, 0, *(float*)(f + 0x38), *(float*)(f + 0x3C));
        func_00391CB0(font_2CA768(item), rect->x + (rect->w - w) * 0.5f, rect->y + 6.0f - 1.0f, center);
    }
    if (right) {
        char* f = font_2CA768(item);
        float w = func_00391FB0(f, right, 0, 0, *(float*)(f + 0x38), *(float*)(f + 0x3C));
        func_00391CB0(font_2CA768(item), rect->x + (rect->w - w) - 16.0f, rect->y + 6.0f - 1.0f, right);
    }
    *(sVec2_2CA768*)(font_2CA768(item) + 0x28) = sVec2_2CA768(0.0f, 0.0f);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* func_002CBF30(void* self);
extern char D_004D5380[];
extern char D_004D5390[];

struct func_002CA988_sVec3 {
    float x;
    float y;
    float z;
};
extern func_002CA988_sVec3 D_004D53A0;
extern func_002CA988_sVec3 D_004D53B0;

struct func_002CA988_sColor {
    float a;
    float r;
    float g;
    float b;
};

extern "C" void* func_002CA768(void* self, int a1, int a2, int a3, void* a4, char* style, func_002CA988_sColor* col);

// PORT: the unit's 4-arg declaration of func_002CA988 is wrong: the body reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

void* func_002CA988_5(void* self, int a1, int a2, int a3, void* a4)
{
    int focused = self == func_002CBF30(*(void**)self);
    char* style = focused ? D_004D5380 : D_004D5390;
    func_002CA988_sVec3* v = focused ? &D_004D53A0 : &D_004D53B0;
    func_002CA988_sColor c;
    c.a = 1.0f;
    c.r = v->x;
    c.g = v->y;
    c.b = v->z;
    return func_002CA768(self, a1, a2, a3, a4, style, &c);
}

extern void* D_00486ED0[];

//100%
void* func_002CAA58(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x12c) = (int)(void*)D_00486ED0;
    *(int*)((char*)self + 0x4) = t0;
    *(int*)((char*)self + 0x8) = t0;
    *(int*)((char*)self + 0x124) = t0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern void* D_00486ED0[];

extern "C" void func_002CAA80(int* self, int flags)
{
    *(void***)((char*)self + 0x12C) = D_00486ED0;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
class func_002CAAB0_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual int v03();
};

extern "C" void func_002CAB08(void* self);

extern "C" void func_002CAAB0(void* self)
{
    func_002CAAB0_cItem* item = *(func_002CAAB0_cItem**)((char*)self + (*(int*)((char*)self + 0x4) << 2) + 0xC);
    if (item->v03() == 0) {
        func_002CAB08(self);
    }
}

//100%
class func_002CAB08_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual int v03();
    virtual void v04();
    virtual void v05();
    virtual void v06(int);
    virtual void v07();
};

struct func_002CAB08_sMenu {
    int count;
    int cur;
    int f8;
    func_002CAB08_cItem* items[1];
};

extern "C" void func_002CAB08(void* menu)
{
    func_002CAB08_sMenu* self = (func_002CAB08_sMenu*)menu;
    int start = self->cur;
    do {
        self->cur = (self->cur + 1) % self->count;
        if (self->cur == start) {
            return;
        }
    } while (!self->items[self->cur]->v03());
    self->items[start]->v07();
    self->items[self->cur]->v06(0);
}

//100%
class func_002CABE0_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual int v03();
    virtual void v04();
    virtual void v05();
    virtual void v06(int);
    virtual void v07();
};

struct func_002CABE0_sMenu {
    int count;
    int cur;
    int f8;
    func_002CABE0_cItem* items[1];
};

extern "C" void func_002CABE0(void* menu)
{
    func_002CABE0_sMenu* self = (func_002CABE0_sMenu*)menu;
    int start = self->cur;
    do {
        self->cur = (self->cur + self->count - 1) % self->count;
        if (self->cur == start) {
            return;
        }
    } while (!self->items[self->cur]->v03());
    self->items[start]->v07();
    self->items[self->cur]->v06(1);
}

//100% - objdiff report; single-function view differs only in a relocation name
class func_002CACC0_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual int v02();
};

extern "C" void func_002CABE0(void* self);

extern "C" int func_002CACC0(void* self)
{
    func_002CAAB0(self);
    func_002CACC0_cItem* item = *(func_002CACC0_cItem**)((char*)self + (*(int*)((char*)self + 0x4) << 2) + 0xC);
    int r = item->v02();
    switch (r) {
    case 3:
        func_002CAB08(self);
        return 0;
    case 4:
        func_002CABE0(self);
        return 0;
    }
    return r;
}

//100%
int func_002CAD48(void* self)
{
    return 0;
}

//100%
void func_002CAD50(void* self)
{
}

INCLUDE_ASM("util/menu", func_002CAD58);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct func_002CB180_sRS {
    int f0;
    unsigned int f4_0 : 2;
    unsigned int f4_2 : 5;
    unsigned int f4_7 : 5;
    unsigned int f4_12 : 8;
    unsigned int f4_20 : 2;
    unsigned int f4_22 : 1;
    unsigned int f4_23 : 2;
    unsigned int f4_25 : 7;
    unsigned int f8_0 : 5;
    unsigned int f8_5 : 5;
    unsigned int f8_10 : 22;
    int fC;
    int f10;
};

class func_002CB180_cCtx {
public:
    char pad0[0xE84];
    func_002CB180_sRS* top;
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
    virtual void v26(int a, int b, float x, float y, float w, float h, float zn, float zf);
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34(void* p);
};

// Typed view of the render context (the unit declares D_004A289C with another class later).
extern func_002CB180_cCtx* D_004A289C_cb180 __asm__("D_004A289C");
extern char D_004FF1A0[];

static inline void func_002CB180_setF8_5(func_002CB180_sRS* rs, int v) { rs->f8_5 = v; }
static inline void func_002CB180_setF4_23(func_002CB180_sRS* rs, int v) { rs->f4_23 = v; }
static inline void func_002CB180_setF4_20(func_002CB180_sRS* rs, int v) { rs->f4_20 = v; }
static inline void func_002CB180_setF4_12(func_002CB180_sRS* rs, int v) { rs->f4_12 = v; }
static inline void func_002CB180_setF4_2(func_002CB180_sRS* rs, int v) { rs->f4_2 = v; }

extern "C" void func_002CB180()
{
    func_002CB180_cCtx* ctx = D_004A289C_cb180;
    ctx->top[1] = ctx->top[0];
    ctx->top++;
    D_004A289C_cb180->v21();
    D_004A289C_cb180->v31();
    func_002CB180_setF8_5(D_004A289C_cb180->top, 0x11);
    func_002CB180_setF4_23(D_004A289C_cb180->top, 2);
    func_002CB180_setF4_20(D_004A289C_cb180->top, 3);
    func_002CB180_setF4_12(D_004A289C_cb180->top, 0x14);
    func_002CB180_setF4_2(D_004A289C_cb180->top, 5);
    D_004A289C_cb180->v26(0, 0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    D_004A289C_cb180->v34(D_004FF1A0);
}

//100%
class func_002CB2F8_cObj {
public:
    char data[0x10D8];
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
};

extern func_002CB2F8_cObj* D_004A289C;

extern "C" void func_002CB2F8()
{
    D_004A289C->v32();
    D_004A289C->v22();
    *(int*)((char*)D_004A289C + 0xE84) = *(int*)((char*)D_004A289C + 0xE84) - 0x14;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct func_002CB350_sVec4 {
    float x, y, z, w;
    func_002CB350_sVec4(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
} __attribute__((aligned(16)));

struct func_002CB350_sVtx {
    float u, v;
    char pad[0x18];
    func_002CB350_sVec4 pos;
};

class func_002CB350_cCtx {
public:
    char pad0[0x10D8];
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

// Typed view of the render context (the unit declares D_004A289C with another class later).
extern func_002CB350_cCtx* D_004A289C_cb350 __asm__("D_004A289C");

extern "C" void func_002CB350(func_002CB350_sVtx* v, float* r, float* t)
{
    v[0].pos = func_002CB350_sVec4(r[0], r[1], 0.0f, 1.0f);
    v[0].u = t[0];
    v[0].v = t[1];
    v[1].pos = func_002CB350_sVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    v[1].u = t[0] + t[2];
    v[1].v = t[1];
    v[2].pos = func_002CB350_sVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    v[2].u = t[0];
    v[2].v = t[1] + t[3];
    v[3].pos = func_002CB350_sVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    v[3].u = t[0] + t[2];
    v[3].v = t[1] + t[3];
    D_004A289C_cb350->v71(4, v, 0);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sVtx_2CB498 {
    float u, v, q;
    int pad;
    int r, g, b, a;
    float pos[4] __attribute__((aligned(16)));
    sVtx_2CB498() {}
};

struct sRS_2CB498 {
    int f0;
    unsigned int f4_0 : 2;
    unsigned int f4_2 : 5;
    unsigned int f4_7 : 25;
    int f8;
    int fC;
    short f10;
};

class cCtx_2CB498 {
public:
    char pad0[0xE84];
    sRS_2CB498* top;
};

extern cCtx_2CB498* D_004A289C_cb498 __asm__("D_004A289C");

static inline int func_002CB498_getF8_5(sRS_2CB498* rs)
{
    return (unsigned int)(rs->f8 & 0x3E0) >> 5;
}

static inline void func_002CB498_setF8_5(sRS_2CB498* rs, int v)
{
    if (v < 0) v = 0;
    rs->f8 = (rs->f8 & ~0x3E0) | ((v << 5) & 0x3E0);
}

INCLUDE_ASM("util/menu", func_002CB498);
extern "C" void func_002CB498(void* self, float* rect, func_002CA988_sColor* col);

//100%
extern char D_004D5380[];
extern char D_004D5390[];

typedef void (*fn2CB880)(void*, void*, char*);

struct sVEntry2CB880 {
    short delta;
    short index;
    fn2CB880 fn;
};

extern "C" void func_002CB880(void* self, void* a1, int on)
{
    sVEntry2CB880* vt = *(sVEntry2CB880**)((char*)self + 0x12C);
    fn2CB880* f = &vt[8].fn;
    (*f)((char*)self + vt[8].delta, a1, on ? D_004D5380 : D_004D5390);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sVec4_2CB8C8 {
    float x, y, z, w;
    sVec4_2CB8C8() {}
    sVec4_2CB8C8(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
} __attribute__((aligned(16)));

struct sVtx_2CB8C8 {
    float u, v, q;
    int pad;
    int r, g, b, a;
    sVec4_2CB8C8 pos;
    sVtx_2CB8C8() {}
};

struct sRS_2CB8C8 {
    int f0;
    unsigned int f4_0 : 2;
    unsigned int f4_2 : 5;
    unsigned int f4_7 : 25;
    int f8;
    int fC;
    short f10;
};

class cCtx_2CB8C8 {
public:
    char pad0[0xE84];
    sRS_2CB8C8* top;
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

extern cCtx_2CB8C8* D_004A289C_cb8c8 __asm__("D_004A289C");

INCLUDE_ASM("util/menu", func_002CB8C8);
extern "C" void func_002CB8C8(void* self, float* rect);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sVec4_2CBAC8 {
    float x, y, z, w;
    sVec4_2CBAC8() {}
    sVec4_2CBAC8(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
} __attribute__((aligned(16)));

struct sVtx_2CBAC8 {
    float u, v, q;
    int pad;
    int r, g, b, a;
    sVec4_2CBAC8 pos;
    sVtx_2CBAC8() {}
};

struct sRS_2CBAC8 {
    int f0;
    unsigned int f4_0 : 2;
    unsigned int f4_2 : 5;
    unsigned int f4_7 : 25;
    int f8;
    int fC;
    short f10;
};

class cCtx_2CBAC8 {
public:
    char pad0[0xE84];
    sRS_2CBAC8* top;
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

extern cCtx_2CBAC8* D_004A289C_cbac8 __asm__("D_004A289C");

INCLUDE_ASM("util/menu", func_002CBAC8);
extern "C" void func_002CBAC8(void* self, float* rect);

//100%
struct cMenuList {
    int count;          // 0x0
    int selected;       // 0x4
    int unk8;           // 0x8
    void* items[70];    // 0xC
    int wrap;           // 0x124
};

extern "C" void cMenu_addItem(cMenuList* menu, void** item, int index)
{
    *item = menu;
    if (index < 0) {
        index = menu->count;
    }
    for (int i = menu->count; index < i; i--) {
        menu->items[i] = menu->items[i - 1];
    }
    menu->items[index] = item;
    if (menu->wrap != 0 && menu->selected >= index && menu->count != 0) {
        menu->selected++;
    }
    menu->count++;
}

//100%
struct sMenuList_CBD50 {
    int count;      // 0x0
    int sel;        // 0x4
    int pad8;
    int items[1];   // 0xC
};

extern "C" void func_002CBD50(void* self, int index)
{
    sMenuList_CBD50* m = (sMenuList_CBD50*)self;
    for (int i = index; i < m->count - 1; i++) {
        m->items[i] = m->items[i + 1];
    }
    m->count--;
    if (index < m->sel) {
        m->sel--;
    }
    if (m->sel >= m->count) {
        m->sel = m->count - 1;
    }
    if (index == m->sel) {
        func_002CAAB0(m);
    }
    if (m->sel < 0) {
        m->sel = 0;
    }
}

//100%
extern "C" void func_002CBE10(int* self)
{
    self[1] = 0;
    self[0] = 0;
}

//100%
extern int (*D_004A54BC)(int, int);
extern "C" void func_002D4008(int* a, int* b);
extern "C" void func_00418EF8_2CBE20(void* base, int n, int size, void (*cmp)(int*, int*)) __asm__("func_00418EF8");
extern "C" void func_002CAAB0(void* self);

// Sorts the menu's items with the given compare function.
extern "C" void func_002CBE20(cMenuList* menu, int (*cmp)(int, int))
{
    D_004A54BC = cmp;
    func_00418EF8_2CBE20(menu->items, menu->count, 4, func_002D4008);
    D_004A54BC = 0;
    func_002CAAB0(menu);
}

//100% - objdiff report; single-function view differs only in a relocation name
class func_002CBE68_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06(int);
    virtual void v07();
};

struct func_002CBE68_sMenu {
    int count;          // 0x0
    int selected;       // 0x4
    int unk8;           // 0x8
    func_002CBE68_cItem* items[70];    // 0xC
    int wrap;           // 0x124
};

extern "C" void func_002CBE68(func_002CBE68_sMenu* self, int index)
{
    if (index < 0) {
        index += self->count;
    }
    if (index != self->selected) {
        self->items[self->selected]->v07();
        self->selected = index;
        self->items[index]->v06(2);
        func_002CAAB0(self);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CAAB0(void* self);

extern "C" int func_002CBF08(void* self)
{
    func_002CAAB0(self);
    return *(int*)((char*)self + 0x4);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* func_002CBF30(void* self)
{
    return *(void**)((char*)self + (func_002CBF08(self) << 2) + 0xC);
}

//100% - objdiff report; single-function view differs only in a relocation name
class func_002CBF60_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06(int);
};

struct func_002CBF60_sMenu {
    int count;          // 0x0
    int selected;       // 0x4
    int unk8;           // 0x8
    func_002CBF60_cItem* items[70];    // 0xC
    int wrap;           // 0x124
};

extern "C" void func_002CBF60(void* p, int wrap)
{
    func_002CBF60_sMenu* self = (func_002CBF60_sMenu*)p;
    self->wrap = wrap;
    if (self->selected >= self->count) {
        self->selected = self->count - 1;
    }
    self->items[self->selected]->v06(2);
    func_002CAAB0(self);
}

//100%
struct sVEntry2CBFD0 {
    short delta;
    short index;
    void (*fn)(void*);
};

struct s2CBFD0Menu {
    int count;          // 0x0
    int selected;       // 0x4
    int unk8;           // 0x8
    void* items[70];    // 0xC
    int wrap;           // 0x124
};

extern "C" void func_002CBFD0(void* p)
{
    s2CBFD0Menu* self = (s2CBFD0Menu*)p;
    void* item = self->items[self->selected];
    sVEntry2CBFD0* vt = *(sVEntry2CBFD0**)((char*)item + 0x10);
    vt[7].fn((char*)item + vt[7].delta);
    self->wrap = 0;
}

//100%
void func_002CC070(void* self);

extern "C" void* func_002CC018(void* self)
{
    *(int*)self = 0;
    func_002CC070(self);
    return self;
}

//100%
void operator_delete(int* ptr);

extern "C" void func_002CC048(int* self, int flags)
{
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void func_002CC070(void* self)
{
    *(int*)((char*)self + 0x58) = 0;
    *(int*)((char*)self + 0x54) = 0;
    *(int*)self = 0;
    *(int*)((char*)self + 0x64) = 0;
    *(int*)((char*)self + 0x4c) = -1;
    *(int*)((char*)self + 0x48) = 11;
    *(int*)((char*)self + 0x50) = -1;
}

//100%
extern "C" int func_002CC098(void* self)
{
    int r = 0;
    if (*(int*)self != 0) {
        r = *(int*)((char*)self + 0x54) != 0;
    }
    return r;
}

//100%
void func_002CC0B8(void* self, int val)
{
    *(int*)((char*)self + 0x54) = val;
}

//100%
float func_00320BF0_C0C0(int, int) __asm__("func_00320BF0");
extern "C" int func_00266BA8(void* self, int a1, int* a2, int* a3);
extern void* D_004A33F0;
extern "C" void func_002CC460(void* p);

class func_002CC0C0_cMenu {
public:
    char pad[0x12C];
    // vptr at 0x12C; slot N at vtable offset N*8
    virtual void v01();
    virtual int v02();
};

struct func_002CC0C0_sStack {
    int count;                          // 0x0
    func_002CC0C0_cMenu* entries[0x11]; // 0x4
    int action;                         // 0x48
    int key;                            // 0x4C
    int mod;                            // 0x50
    int pad54[2];
    int** pad;                          // 0x5C
};

extern "C" void func_002CC0C0(void* p)
{
    func_002CC0C0_sStack* self = (func_002CC0C0_sStack*)p;
    if (self->count == 0) {
        return;
    }
    int ok = 0;
    if (*self->pad != 0) {
        ok = **self->pad != 0;
    }
    if (!ok) {
        return;
    }
    int btn = (int)func_00320BF0_C0C0((int)self->pad, 0x3D);
    int* key = &self->key;
    int* mod = &self->mod;
    *key = -1;
    *mod = -1;
    self->action = btn;
    if (btn == -1 && D_004A33F0 != 0 && func_00266BA8(D_004A33F0, 0, key, mod)) {
        if (self->mod < 0x20) {
            self->mod = -1;
        }
        switch (self->key) {
        case 0x26: self->action = 0; break;
        case 0x28: self->action = 1; break;
        case 0x25: self->action = 2; break;
        case 0x27: self->action = 3; break;
        case 0x2D: self->action = 9; break;
        case 0x2E: self->action = 10; break;
        case 0xD: self->action = 6; break;
        case 0x1B: self->action = 7; break;
        }
    }
    int r = self->entries[self->count - 1]->v02();
    switch (r) {
    case 1:
        func_002CC460(self);
        break;
    case 2:
        while (self->count != 0) {
            func_002CC460(self);
        }
        break;
    }
}

//100%
int func_002CC248(void* self)
{
    return *(int*)((char*)self + 0x48);
}

//100%
int func_002CC250(void* self)
{
    return *(int*)((char*)self + 0x4C);
}

//100%
int func_002CC258(void* self)
{
    return *(int*)((char*)self + 0x50);
}

extern "C" void* func_00320BF0(int, int);

//100%
void* func_002CC260(void* self)
{
    return func_00320BF0(*(int*)((char*)self + 0x5c), 0x3e);
}

//100%
void* func_002CC280(void* self)
{
    return func_00320BF0(*(int*)((char*)self + 0x5c), 0x3f);
}

//100%
void* func_002CC2A0(void* self)
{
    return func_00320BF0(*(int*)((char*)self + 0x5c), 0x40);
}

//100%
void* func_002CC2C0(void* self)
{
    return func_00320BF0(*(int*)((char*)self + 0x5c), 0x41);
}

//100%
// PORT: func_00320BF0 is declared returning void* in this unit; this caller reads a float result ($f0).
float func_00320BF0_f(int, int) __asm__("func_00320BF0");
// PORT: the unit declares func_002CC2E0 as void*(int); the body takes the object pointer.
int func_002CC2E0_impl(void* self) __asm__("func_002CC2E0");

int func_002CC2E0_impl(void* self)
{
    return func_00320BF0_f(*(int*)((char*)self + 0x5c), 0x42) != 0.0f;
}

//100%
// PORT: func_00320BF0 is declared returning void* in this unit; this caller reads a float result ($f0).
float func_00320BF0_f(int, int) __asm__("func_00320BF0");
// PORT: the unit declares func_002CC318 as void*(int); the body takes the object pointer.
int func_002CC318_impl(void* self) __asm__("func_002CC318");

int func_002CC318_impl(void* self)
{
    return func_00320BF0_f(*(int*)((char*)self + 0x5c), 0x43) != 0.0f;
}

//100%
class func_002CC350_cObj {
public:
    char data[0x12C];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
};

struct func_002CC350_sVec2 {
    float x;
    float y;
    func_002CC350_sVec2(float a, float b)
    {
        x = a;
        y = b;
    }
};

struct func_002CC350_sStack {
    int count;
    func_002CC350_cObj* items[1];
};

extern "C" void func_002CC350(void* self)
{
    func_002CC350_sVec2 scale(0.8500000238418579f, 0.8500000238418579f);
    char* o = *(char**)((char*)self + 0x58);
    *(float*)(o + 0x38) = *(float*)(o + 0x30) * scale.x;
    *(float*)(o + 0x3C) = *(float*)(o + 0x34) * scale.y;
    func_002CC350_sStack* st = (func_002CC350_sStack*)self;
    st->items[st->count - 1]->v05();
}

//100% - objdiff report; single-function view differs only in a relocation name
void func_002CC0B8(void*, int);

class func_002CC3B8_cMenu {
public:
    char pad[0x12C];
    // vptr at 0x12C; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06(void*);
    virtual void v07();
};

struct func_002CC3B8_sStack {
    int count;
    func_002CC3B8_cMenu* items[1];
};

extern "C" void func_002CC3B8(void* stack, void* item)
{
    func_002CC3B8_sStack* self = (func_002CC3B8_sStack*)stack;
    if (self->count != 0) {
        self->items[self->count - 1]->v07();
    }
    self->items[self->count++] = (func_002CC3B8_cMenu*)item;
    self->items[self->count - 1]->v06(self);
    func_002CC0B8(self, 1);
}

//100% - objdiff report; single-function view differs only in a relocation name
class func_002CC460_cMenu {
public:
    char pad[0x12C];
    // vptr at 0x12C; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06(void*);
    virtual void v07();
};

struct func_002CC460_sStack {
    int count;                          // 0x0
    func_002CC460_cMenu* entries[8];    // 0x4
};

extern "C" void func_002CC460(void* p)
{
    func_002CC460_sStack* self = (func_002CC460_sStack*)p;
    self->count--;
    self->entries[self->count]->v07();
    if (self->count != 0) {
        self->entries[self->count - 1]->v06(self);
        if (self->count != 0) {
            return;
        }
    }
    func_002CC0B8(self, 0);
}

//100%
struct sMenuItem_2CC500 {
    char pad_0x00[0x10];
    void* vtable;   // 0x10
    int field_0x14;
    int field_0x18;
    int field_0x1C;
    int field_0x20;
};
extern void* D_00486E80[];

extern "C" sMenuItem_2CC500* func_002CC500(sMenuItem_2CC500* self, void* text, int a2, int a3, int a4, int a5)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = a3;
    self->field_0x18 = a4;
    self->field_0x1C = a5;
    self->field_0x20 = a2;
    self->vtable = D_00486E80;
    return self;
}

//100%
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3B0(void* self);
extern "C" int func_002CA3E8(void** self);

class func_002CC578_cMenu {
public:
    char pad[0x12C];
    // vptr at 0x12C; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04(void*);
};

extern "C" int func_002CC578(void** self)
{
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) == 0 && r == 0) {
        if ((self[6] != 0 && self[7] != 0 && (func_002CA3E8(self) == 2 || func_002CA3E8(self) == 3)) || func_002CA3E8(self) == 6) {
            *(int*)self[8] ^= 1;
            ((func_002CC578_cMenu*)self[0])->v04(self);
        }
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);

struct sMenuRectC648 { float x, y, z, w; };

extern "C" sMenuRectC648* func_002CC648(sMenuRectC648* ret, char* item)
{
    if (*(void**)(item + 0x18) != 0 && *(void**)(item + 0x1C) != 0) {
        sMenuRectC648 a;
        sMenuRectC648 b;
        sMenuRectC648 tmp;
        func_002CA4C8(&tmp, item, *(int*)(item + 0x14), 0, *(void**)(item + 0x18));
        a = tmp;
        func_002CA4C8(&tmp, item, *(int*)(item + 0x14), 0, *(void**)(item + 0x1C));
        b = tmp;
        *ret = (a.z > b.z) ? a : b;
    } else {
        func_002CA4C8(ret, item, 0, *(int*)(item + 0x14), 0);
    }
    return ret;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: the unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

extern "C" void func_002CC758(void* self, int a1)
{
    void* a = *(void**)((char*)self + 0x18);
    void* b;
    if (a != 0 && (b = *(void**)((char*)self + 0x1C)) != 0) {
        func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, **(int**)((char*)self + 0x20) ? a : b);
    } else {
        func_002CA988_5(self, a1, 0, *(int*)((char*)self + 0x14), 0);
    }
}

//100%
struct sMenuItem_2CC7B0 {
    char pad_0x00[0x10];
    void* vtable;   // 0x10
    int field_0x14;
    int field_0x18;
    int field_0x1C;
    int field_0x20;
};
extern void* D_00486E30[];
// PORT: these callers pass a string id (-1) in place of the text pointer.
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

extern "C" sMenuItem_2CC7B0* func_002CC7B0(sMenuItem_2CC7B0* self)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = 0;
    self->vtable = D_00486E30;
    self->field_0x20 = 0;
    self->field_0x18 = 0;
    return self;
}

//100%
extern "C" sMenuItem_2CC7B0* func_002CC7F8(sMenuItem_2CC7B0* self, void* text)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = 0;
    self->vtable = D_00486E30;
    self->field_0x20 = 0;
    self->field_0x18 = 0;
    return self;
}

struct sMenuItem_2CC838 {
    char pad_0x00[0x10];
    void* vtable;   // 0x10
    int field_0x14;
    int field_0x18;
    int field_0x1C;
    int field_0x20;
};

extern "C" sMenuItem_2CC838* func_002CC838(sMenuItem_2CC838* self, void* text, int a, int b, int c, int d)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->vtable = D_00486E30;
    self->field_0x14 = b;
    self->field_0x20 = a;
    self->field_0x18 = c;
    self->field_0x1C = d;
    return self;
}

//100%
struct sListEntry_2CC8B0 {
    void* name;
    int value;
};

// Points the item at a null-terminated entry list and counts its entries.
extern "C" void func_002CC8B0(void* self, sListEntry_2CC8B0* list)
{
    *(sListEntry_2CC8B0**)((char*)self + 0x1C) = list;
    *(int*)((char*)self + 0x18) = 0;
    while (list[*(int*)((char*)self + 0x18)].name != 0)
        (*(int*)((char*)self + 0x18))++;
}

//100%
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3B0(void* self);
extern "C" int func_002CA3E8(void** self);

struct sVEnt_2CC8F0 { short delta; short index; void* fn; };
typedef int (*Pick_2CC8F0)(void*, void*, int);
typedef void (*Notify_2CC8F0)(void*, void*);

struct sEnt_2CC8F0 {
    const char* name;
    int value;
};

struct sList_2CC8F0 {
    char* menu;
    char pad04[0x14];
    int count;
    sEnt_2CC8F0* entries;
    int* value;
};

static inline void notify_2CC8F0(sList_2CC8F0* self)
{
    sVEnt_2CC8F0* vt = *(sVEnt_2CC8F0**)(self->menu + 0x12C);
    ((Notify_2CC8F0)vt[4].fn)(self->menu + vt[4].delta, self);
}

extern "C" int func_002CC8F0(void* vself)
{
    sList_2CC8F0* self = (sList_2CC8F0*)vself;
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) != 0) {
        return r;
    }
    if (r != 0) {
        return r;
    }
    if (func_002CA3E8((void**)self) == 6) {
        sVEnt_2CC8F0* vt = *(sVEnt_2CC8F0**)(self->menu + 0x12C);
        r = ((Pick_2CC8F0)vt[3].fn)(self->menu + vt[3].delta, self, 0);
    } else {
    int n = self->count;
    int i = 0;
    for (;;) {
        if (i == n) {
            if (func_002CA3E8((void**)self) == 2 || func_002CA3E8((void**)self) == 0) {
                *self->value = self->entries[0].value;
                notify_2CC8F0(self);
            } else if (func_002CA3E8((void**)self) == 3 || func_002CA3E8((void**)self) == 1) {
                *self->value = self->entries[self->count - 1].value;
                notify_2CC8F0(self);
            }
            goto done;
        }
        if (*self->value == self->entries[i].value) {
            if (func_002CA3E8((void**)self) == 2 || func_002CA3E8((void**)self) == 0) {
                *self->value = self->entries[(i + self->count - 1) % self->count].value;
                notify_2CC8F0(self);
            } else if (func_002CA3E8((void**)self) == 3 || func_002CA3E8((void**)self) == 1) {
                *self->value = self->entries[(i + 1) % self->count].value;
                notify_2CC8F0(self);
            }
            goto done;
        }
        i++;
    }
done:
    return r;
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);
extern char D_004866B8[];

struct sMenuRectCB18 { float x, y, z, w; };
struct sMenuEntCB18 { void* name; int data; };

extern "C" sMenuRectCB18* func_002CCB18(sMenuRectCB18* ret, char* item)
{
    sMenuRectCB18 best;
    sMenuRectCB18 tmp;
    func_002CA4C8(&tmp, item, *(int*)(item + 0x14), 0, D_004866B8);
    best = tmp;
    for (int i = 0; i < *(int*)(item + 0x18); i++) {
        func_002CA4C8(&tmp, item, *(int*)(item + 0x14), 0, (*(sMenuEntCB18**)(item + 0x1C))[i].name);
        if (tmp.z > best.z) {
            best = tmp;
        }
    }
    *ret = best;
    return ret;
}

//100%
extern char D_004866B8[];

struct func_002CCC38_sEntry {
    char* name;  // 0x0
    int value;   // 0x4
};

extern "C" void func_002CCC38(void* self, int a1)
{
    int i = 0;
    for (;;) {
        if (i == *(int*)((char*)self + 0x18)) {
            func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, D_004866B8);
            break;
        }
        // PORT: pointer held in int (index-first address arithmetic)
        func_002CCC38_sEntry* e = (func_002CCC38_sEntry*)((i << 3) + *(int*)((char*)self + 0x1C));
        if (**(int**)((char*)self + 0x20) == e->value) {
            func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, e->name);
            return;
        }
        i++;
    }
}

//100%
// PORT: the base ctor's 2nd arg is really an int (id/text handle; -1 = none).
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

extern void* D_00486DE0[];

struct cSubMenuItem_sItem {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    void* field_0x14;
    void* field_0x18;
};

extern "C" cSubMenuItem_sItem* cSubMenuItem_cSubMenuItem(cSubMenuItem_sItem* self, void* a1, void* a2)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = a2;
    self->field_0x18 = a1;
    self->vtable = D_00486DE0;
    return self;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3E8(void** self);
extern "C" void func_002CC3B8(void* stack, void* item);

extern "C" int func_002CCD20(void* self)
{
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) == 0 && r == 0 && func_002CA3E8((void**)self) == 6) {
        func_002CC3B8(*(void**)((char*)*(void**)self + 0x124), *(void**)((char*)self + 0x18));
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);

extern "C" void* func_002CCD90(void* self, void* a1)
{
    func_002CA4C8(self, a1, 0, *(int*)((char*)a1 + 0x14), 0);
    return self;
}

extern "C" void* func_002CA988(void*, int, int, int);

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
// The unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

void* func_002CCDC8(void* self, int a1)
{
    return func_002CA988_5(self, a1, 0, *(int*)((char*)self + 0x14), 0);
}

//100%
// PORT: the base ctor's 2nd arg is really an int (id/text handle; -1 = none).
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

extern void* D_00486D90[];

struct s2CCDF0Item {
    char pad_0x00[0x10];
    void* vtable;
    void* field_0x14;
};

extern "C" s2CCDF0Item* func_002CCDF0(s2CCDF0Item* self, void* text)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = text;
    self->vtable = D_00486D90;
    return self;
}

//100%
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3E8(void** self);
extern "C" void func_002CC460(void* stack);

extern "C" int func_002CCE38(void* self)
{
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) == 0 && r == 0 && func_002CA3E8((void**)self) == 6) {
        func_002CC460(*(void**)((char*)*(void**)self + 0x124));
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);

extern "C" void* func_002CCEA8(void* self, void* a1)
{
    func_002CA4C8(self, a1, 0, *(int*)((char*)a1 + 0x14), 0);
    return self;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
// The unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

void* func_002CCEE0(void* self, int a1)
{
    return func_002CA988_5(self, a1, 0, *(int*)((char*)self + 0x14), 0);
}

//100%
// PORT: the base ctor's 2nd arg is really an int (id/text handle; -1 = none).
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

extern void* D_00486D40[];

struct s2CCF08Item {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    int field_0x14;
    int field_0x18;
    int field_0x1C;
    int field_0x20;
};

extern "C" s2CCF08Item* func_002CCF08(s2CCF08Item* self)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = 0;
    self->vtable = D_00486D40;
    self->field_0x1C = 0;
    self->field_0x20 = 0;
    self->field_0x18 = 0;
    return self;
}

//100%
extern void* D_00486D40[];

extern "C" sMenuItem_2CC7B0* func_002CCF50(sMenuItem_2CC7B0* self, void* text)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = 0;
    self->vtable = D_00486D40;
    self->field_0x1C = 0;
    self->field_0x20 = 0;
    self->field_0x18 = 0;
    return self;
}

//100%
extern void* D_00486D40[];

struct func_002CCF98_sItem {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    int field_0x14;
    int field_0x18;
    int field_0x1C;
    int field_0x20;
};

extern "C" func_002CCF98_sItem* func_002CCF98(func_002CCF98_sItem* self, void* text, int a2, int a3)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = a2;
    self->vtable = D_00486D40;
    self->field_0x1C = a3;
    self->field_0x20 = 0;
    self->field_0x18 = 0;
    return self;
}

//100%
extern "C" void func_002CCFF8(void* self, int a, int b)
{
    *(int*)((char*)self + 0x14) = a;
    *(int*)((char*)self + 0x1C) = b;
    *(int*)((char*)self + 0x18) = 0;
}

//100%
class func_002CD008_cMenu {
public:
    char pad[0x12C];
    // vptr at 0x12C; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual int v03(void* item, void* data);
};

extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3E8(void** self);

extern "C" int func_002CD008(void* self)
{
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) == 0 && r == 0 && func_002CA3E8((void**)self) == 6) {
        r = (*(func_002CD008_cMenu**)self)->v03(self, *(void**)((char*)self + 0x1C));
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);

extern "C" void* func_002CD090(void* self, void* a1)
{
    void* p = *(void**)((char*)a1 + 0x18);
    if (p != 0) {
        func_002CA4C8(self, a1, *(int*)((char*)a1 + 0x14), 0, p);
    } else {
        func_002CA4C8(self, a1, 0, *(int*)((char*)a1 + 0x14), 0);
    }
    return self;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: The unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

extern "C" void func_002CD0E8(void* self, int a1)
{
    void* p = *(void**)((char*)self + 0x18);
    if (p != 0) {
        func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, p);
    } else {
        func_002CA988_5(self, a1, 0, *(int*)((char*)self + 0x14), 0);
    }
}

//100%
extern void* D_00486CF0[];

extern "C" sMenuItem_2CC7B0* func_002CD128(sMenuItem_2CC7B0* self)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = 0;
    self->vtable = D_00486CF0;
    self->field_0x18 = 0;
    return self;
}

//100%
extern "C" sMenuItem_2CC7B0* func_002CD168(sMenuItem_2CC7B0* self, void* text, int a2, int a3)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = a2;
    self->field_0x18 = a3;
    self->vtable = D_00486CF0;
    return self;
}

//100%
extern "C" void func_002CD1C0(void* self, int a, int b)
{
    *(int*)((char*)self + 0x14) = a;
    *(int*)((char*)self + 0x18) = b;
}

//100%
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3E8(void** self);

extern "C" int func_002CD1D0(void* self)
{
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) == 0 && r == 0 && func_002CA3E8((void**)self) == 6) {
        (*(void (**)())((char*)self + 0x18))();
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);
extern void* D_004866C8[];

extern "C" void* func_002CD240(void* self, void* a1)
{
    func_002CA4C8(self, a1, *(int*)((char*)a1 + 0x14), 0, D_004866C8);
    return self;
}

extern void* D_004866C8[];
extern "C" void* func_002CA988(void*, int, int, int);

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
// The unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

void* func_002CD278(void* self, int a1)
{
    return func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, D_004866C8);
}

extern void* D_00486CA0[16];

struct cNullMenuItem {
    char pad_0x00[0x10];
    void* vtable;
    void* field_0x14;
};

//100%
// PORT: the base ctor's 2nd arg is really an int (id/text handle; -1 = none).
// A void* constant -1 materializes as lui/ori; the original passed an int.
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

cNullMenuItem* cNullMenuItem_cNullMenuItem(cNullMenuItem* self, void* text)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = text;
    self->vtable = D_00486CA0;
    return self;
}

//100%
int func_002CD2E8(void* self)
{
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);

extern "C" void* func_002CD2F0(void* self, void* a1)
{
    func_002CA4C8(self, a1, 0, *(int*)((char*)a1 + 0x14), 0);
    return self;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
// The unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

void* func_002CD328(void* self, int a1)
{
    return func_002CA988_5(self, a1, 0, *(int*)((char*)self + 0x14), 0);
}

extern void* D_00486C50[16];

struct cSpaceMenuItem {
    char pad_0x00[0x10];
    void* vtable;
    void* field_0x14;
};

//100%
// PORT: the base ctor's 2nd arg is really an int (id/text handle; -1 = none).
// A void* constant -1 materializes as lui/ori; the original passed an int.
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

cSpaceMenuItem* cSpaceMenuItem_cSpaceMenuItem(cSpaceMenuItem* self, void* text)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = text;
    self->vtable = D_00486C50;
    return self;
}

//100%
int func_002CD398(void* self)
{
    return 0;
}

//100%
struct s2CD3A0Vec {
    float x, y, z, w;
};

extern "C" s2CD3A0Vec func_002CD3A0(void* self)
{
    s2CD3A0Vec v;
    v.x = v.y = v.z = 0.0f;
    v.w = (float)*(int*)((char*)self + 0x14);
    return v;
}

//100%
void func_002CD3F0(void* self)
{
}

//100%
struct sCharMenuItem_2CD3F8 {
    char pad_0x00[0x10];
    void* vtable;   // 0x10
    int field_0x14;
    signed char* value; // 0x18
    signed char min; // 0x1C
    signed char max; // 0x1D
    char pad_0x1E[2];
    int field_0x20;
    int field_0x24;
    int field_0x28;
};
extern void* D_00486C00[];

extern "C" sCharMenuItem_2CD3F8* func_002CD3F8(sCharMenuItem_2CD3F8* self)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = 0;
    self->vtable = D_00486C00;
    self->value = 0;
    self->min = 0;
    self->max = 0;
    self->field_0x24 = 0;
    self->field_0x20 = 0;
    self->field_0x28 = 0;
    return self;
}

//100%
extern "C" sCharMenuItem_2CD3F8* func_002CD450(sCharMenuItem_2CD3F8* self, void* text)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = 0;
    self->vtable = D_00486C00;
    self->value = 0;
    self->min = 0;
    self->max = 0;
    self->field_0x24 = 0;
    self->field_0x20 = 0;
    self->field_0x28 = 0;
    return self;
}

//100%
extern "C" sCharMenuItem_2CD3F8* func_002CD4A0(sCharMenuItem_2CD3F8* self, void* text, signed char* value, signed char min, signed char max, int a5)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = a5;
    self->value = value;
    self->min = min;
    self->max = max;
    self->vtable = D_00486C00;
    self->field_0x24 = 0;
    self->field_0x20 = 0;
    self->field_0x28 = 0;
    return self;
}

//100%
// Sets the min/max range and clamps the bound value to it.
extern "C" void func_002CD528(sCharMenuItem_2CD3F8* self, int min, int max)
{
    self->max = max;
    self->min = min;
    signed char* value = self->value;
    if (value != 0) {
        if (*value < (signed char)min)
            *value = min;
        if (self->max < *self->value)
            *self->value = self->max;
    }
}

//100%
extern "C" void func_002CD578(void* self)
{
    if (*(signed char*)((char*)self + 0x1C) <= 0) {
        **(signed char**)((char*)self + 0x18) = 0;
    } else {
        **(signed char**)((char*)self + 0x18) = *(signed char*)((char*)self + 0x1C);
    }
}

//100%
// PORT: func_002CA408/func_002CA428 return a float (axis value, $f0); the unit declares them void*.
float func_002CA408_f(void* self) __asm__("func_002CA408__FPv");
float func_002CA428_f(void* self) __asm__("func_002CA428__FPv");

struct sVEntry002CD5A0 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

// PORT: PS2-only inline asm (EE cvt.w.s truncates in the FPU; the C cast goes through a GPR).
static inline float ffloor_002CD5A0(float x)
{
    float t;
    __asm__("cvt.w.s %0,%1\n\tcvt.s.w %0,%0" : "=f"(t) : "f"(x));
    if (x < t) {
        t -= 1.0f;
    }
    return t;
}

extern "C" int func_002CD5A0(void* self)
{
    char* s = (char*)self;
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) != 0) {
        return r;
    }
    if (r != 0) {
        return r;
    }
    float d = func_002CA428_f(self) - func_002CA408_f(self);
    int dir;
    if (d <= -0.1f || d >= 0.1f) {
        dir = 1;
        if (d < 0.0f) {
            dir = -1;
        }
    } else {
        dir = 0;
    }
    if (dir == *(int*)(s + 0x24)) {
        *(int*)(s + 0x20) += 1;
    } else {
        *(int*)(s + 0x20) = 0;
        *(int*)(s + 0x24) = dir;
        *(float*)(s + 0x28) = (float)dir;
    }
    if (dir != 0) {
        int n = *(int*)(s + 0x20);
        d *= 0.1f;
        d *= (float)(n * n / 0x120);
        float div = 1.0f;
        if (func_002CA488(self) != 0 && func_002CA4A8(self) != 0) {
            div = 50.0f;
        } else if (func_002CA488(self) != 0) {
            div = 20.0f;
        } else if (func_002CA4A8(self) != 0) {
            div = 5.0f;
        }
        d = d / div;
        *(float*)(s + 0x28) += d;
        d = *(float*)(s + 0x28);
        signed char* p = *(signed char**)(s + 0x18);
        int cur = *p;
        int v = (int)ffloor_002CD5A0((float)cur + d);
        int lo = *(signed char*)(s + 0x1C);
        int hi = *(signed char*)(s + 0x1D);
        if (v < lo) {
            v = lo;
        }
        if (hi < v) {
            v = hi;
        }
        *(float*)(s + 0x28) = d + (float)(cur - v);
        *p = v;
        char* menu = *(char**)s;
        sVEntry002CD5A0* e = &(*(sVEntry002CD5A0**)(menu + 0x12C))[4];
        e->fn(menu + e->delta, self);
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);
extern void* D_004866E0[];

extern "C" void* func_002CD7B8(void* self, void* a1)
{
    func_002CA4C8(self, a1, *(int*)((char*)a1 + 0x14), 0, D_004866E0);
    return self;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int sprintf(char* buf, const char* fmt, ...);
// PORT: the unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");
extern char D_004A3970[];

extern "C" void func_002CD7F0(void* self, int a1)
{
    char buf[0x70];
    sprintf(buf, D_004A3970, **(signed char**)((char*)self + 0x18));
    func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, buf);
}

//100%
extern void* D_00486BB0[];

extern "C" sMenuItem_2CC7B0* func_002CD850(sMenuItem_2CC7B0* self)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = 0;
    self->vtable = D_00486BB0;
    self->field_0x18 = 0;
    self->field_0x1C = 0;
    self->field_0x20 = 0;
    *(int*)((char*)self + 0x28) = 0;
    *(int*)((char*)self + 0x24) = 0;
    *(int*)((char*)self + 0x2C) = 0;
    return self;
}

//100%
extern "C" sMenuItem_2CC7B0* func_002CD8A8(sMenuItem_2CC7B0* self, void* text)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = 0;
    self->vtable = D_00486BB0;
    self->field_0x18 = 0;
    self->field_0x1C = 0;
    self->field_0x20 = 0;
    *(int*)((char*)self + 0x28) = 0;
    *(int*)((char*)self + 0x24) = 0;
    *(int*)((char*)self + 0x2C) = 0;
    return self;
}

//100%
extern void* D_00486BB0[];

struct cIntMenuItem_sItem {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    int field_0x14;
    int field_0x18;
    int field_0x1C;
    int field_0x20;
    int field_0x24;
    int field_0x28;
    int field_0x2C;
};

extern "C" cIntMenuItem_sItem* cIntMenuItem_cIntMenuItem(cIntMenuItem_sItem* self, void* text, int a2, int a3, int a4, int a5)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = a5;
    self->field_0x18 = a2;
    self->field_0x1C = a3;
    self->field_0x20 = a4;
    self->vtable = D_00486BB0;
    self->field_0x28 = 0;
    self->field_0x24 = 0;
    self->field_0x2C = 0;
    return self;
}

//100%
// Sets the min/max range and clamps the bound value to it.
extern "C" void func_002CD978(void* self, int min, int max)
{
    *(int*)((char*)self + 0x20) = max;
    *(int*)((char*)self + 0x1C) = min;
    int* value = *(int**)((char*)self + 0x18);
    if (value != 0) {
        if (*value < min)
            *value = min;
        value = *(int**)((char*)self + 0x18);
        max = *(int*)((char*)self + 0x20);
        if (max < *value)
            *value = max;
    }
}

//100%
extern "C" void func_002CD9B8(void* self)
{
    int* p = *(int**)((char*)self + 0x18);
    int v = *(int*)((char*)self + 0x1c);
    if (v <= 0) {
        *p = 0;
    } else {
        *p = v;
    }
}

//100%
// PORT: func_002CA408/func_002CA428 return a float (axis value, $f0); the unit declares them void*.
float func_002CA408_f(void* self) __asm__("func_002CA408__FPv");
float func_002CA428_f(void* self) __asm__("func_002CA428__FPv");

struct sVEntry002CD9D8 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

// PORT: PS2-only inline asm (EE cvt.w.s truncates in the FPU; the C cast goes through a GPR).
static inline float ffloor_002CD9D8(float x)
{
    float t;
    __asm__("cvt.w.s %0,%1\n\tcvt.s.w %0,%0" : "=f"(t) : "f"(x));
    if (x < t) {
        t -= 1.0f;
    }
    return t;
}

extern "C" int func_002CD9D8(void* self)
{
    char* s = (char*)self;
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) != 0) {
        return r;
    }
    if (r != 0) {
        return r;
    }
    float d = func_002CA428_f(self) - func_002CA408_f(self);
    int dir;
    if (d <= -0.1f || d >= 0.1f) {
        dir = 1;
        if (d < 0.0f) {
            dir = -1;
        }
    } else {
        dir = 0;
    }
    if (dir == *(int*)(s + 0x28)) {
        *(int*)(s + 0x24) += 1;
    } else {
        *(int*)(s + 0x24) = 0;
        *(int*)(s + 0x28) = dir;
        *(float*)(s + 0x2C) = (float)dir;
    }
    if (dir != 0) {
        int n = *(int*)(s + 0x24);
        d *= 0.1f;
        d *= (float)(n * n / 0x120);
        float div = 1.0f;
        if (func_002CA488(self) != 0 && func_002CA4A8(self) != 0) {
            div = 50.0f;
        } else if (func_002CA488(self) != 0) {
            div = 20.0f;
        } else if (func_002CA4A8(self) != 0) {
            div = 5.0f;
        }
        d = d / div;
        *(float*)(s + 0x2C) += d;
        d = *(float*)(s + 0x2C);
        int* p = *(int**)(s + 0x18);
        int cur = *p;
        int v = (int)ffloor_002CD9D8((float)cur + d);
        int lo = *(int*)(s + 0x1C);
        int hi = *(int*)(s + 0x20);
        if (v < lo) {
            v = lo;
        }
        if (hi < v) {
            v = hi;
        }
        *(float*)(s + 0x2C) = d + (float)(cur - v);
        *p = v;
        char* menu = *(char**)s;
        sVEntry002CD9D8* e = &(*(sVEntry002CD9D8**)(menu + 0x12C))[4];
        e->fn(menu + e->delta, self);
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);
extern void* D_004866E0[];

extern "C" void* func_002CDBF0(void* self, void* a1)
{
    func_002CA4C8(self, a1, *(int*)((char*)a1 + 0x14), 0, D_004866E0);
    return self;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int sprintf(char* buf, const char* fmt, ...);
// PORT: the unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");
extern char D_004A3970[];

extern "C" void func_002CDC28(void* self, int a1)
{
    char buf[0x70];
    sprintf(buf, D_004A3970, **(int**)((char*)self + 0x18));
    func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, buf);
}

//100%
struct sFloatMenuItem_2CDC88 {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    int field_0x14;
    int field_0x18;
    float field_0x1C;
    float field_0x20;
    float field_0x24;
    int field_0x28;
    int field_0x2C;
    int field_0x30;
};
extern void* D_00486B60[];

extern "C" sFloatMenuItem_2CDC88* func_002CDC88(sFloatMenuItem_2CDC88* self)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->vtable = D_00486B60;
    self->field_0x24 = 1.0f;
    self->field_0x14 = 0;
    self->field_0x18 = 0;
    self->field_0x1C = 0;
    self->field_0x20 = 0;
    self->field_0x30 = 0;
    self->field_0x2C = 0;
    self->field_0x28 = 0;
    return self;
}

//100%
extern void* D_00486B60[];

struct cFloatMenuItem_sItem {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    int field_0x14;
    int field_0x18;
    float field_0x1C;
    float field_0x20;
    float field_0x24;
    int field_0x28;
    int field_0x2C;
    int field_0x30;
};

extern "C" cFloatMenuItem_sItem* cFloatMenuItem_cFloatMenuItem(cFloatMenuItem_sItem* self, void* text, int a2, int a3, float f1, float f2)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = a3;
    self->field_0x18 = a2;
    self->field_0x1C = f1;
    self->field_0x20 = f2;
    self->vtable = D_00486B60;
    self->field_0x24 = 1.0f;
    self->field_0x30 = 0;
    self->field_0x2C = 0;
    self->field_0x28 = 0;
    return self;
}

//100%
struct sFItem_DD78 {
    char* menu;
    char pad4[0x14];
    float* p;
    float lo;
    float hi;
    float scale;
    float off;
    int n;
    int dir;
};

extern "C" int func_002CDD78(void* self)
{
    char* s = (char*)self;
    sFItem_DD78* it = (sFItem_DD78*)self;
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) != 0) {
        return r;
    }
    if (r != 0) {
        return r;
    }
    float d = func_002CA428_f(self) - func_002CA408_f(self);
    int dir;
    if (d <= -0.1f || d >= 0.1f) {
        dir = 1;
        if (d < 0.0f) {
            dir = -1;
        }
    } else {
        dir = 0;
    }
    if (dir == it->dir) {
        it->n += 1;
    } else {
        it->n = 0;
        it->dir = dir;
    }
    if (dir != 0) {
        float div = 1.0f;
        if (func_002CA488(self) != 0 && func_002CA4A8(self) != 0) {
            div = 50.0f;
        } else if (func_002CA488(self) != 0) {
            div = 20.0f;
        } else if (func_002CA4A8(self) != 0) {
            div = 5.0f;
        }
        int n = it->n;
        float* p = it->p;
        float f = (float)(n * n) * 50.0f / div * 6.9444446e-05f;
        f = f >? 1.0f;
        float v = it->scale * *p + it->off;
        // Going through a variable keeps the constant as the first operand (register choice).
        float c = 5e-05f;
        c *= f;
        v += d * (c / div) * (it->hi - it->lo);
        if (v < it->lo) {
            v = it->lo;
        }
        if (it->hi < v) {
            v = it->hi;
        }
        *p = (v - it->off) / it->scale;
        char* menu = *(char**)s;
        sVEntry002CD5A0* e = &(*(sVEntry002CD5A0**)(menu + 0x12C))[4];
        e->fn(menu + e->delta, self);
    }
    return r;
}

//100%
extern "C" void func_002CDF78(void* self)
{
    float* p = *(float**)((char*)self + 0x18);
    float v = *(float*)((char*)self + 0x1c);
    if (v <= 0.0f) {
        *p = 0.0f;
    } else {
        *p = v;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);
extern void* D_004866F0[];

extern "C" void* func_002CDFA0(void* self, void* a1)
{
    func_002CA4C8(self, a1, *(int*)((char*)a1 + 0x14), 0, D_004866F0);
    return self;
}

//100%
extern void* D_004A3E90;
extern "C" void cBXString__cBXString(void* self, int flags);
extern "C" void cBXString_cBXString1(void* self, void* src);
extern "C" int func_003194A8(void* str, const char* fmt, ...);
extern "C" float func_0040DA10(float x);
extern "C" int func_00413AF8(float f);
extern char D_004A3998[];
extern char D_004A39A0[];
extern char D_004A39A8[];
extern char D_004A39B0[];
extern char D_004A39B8[];
extern char D_004A39C0[];

struct sBXStrDFD8 { char* p; };

// returns a cBXString by value (hidden result pointer in $4); the unit's later declaration says void.
void* func_002CDFD8_impl(void* out, float v) __asm__("func_002CDFD8");

void* func_002CDFD8_impl(void* out, float v)
{
    float d = func_0040DA10(v) / func_0040DA10(10.0f) + 4.3431620724732056e-05f;
    float t;
    // PORT: FPU-only float->int->float round trip (floor helper); no C cast reproduces it.
    __asm__("cvt.w.s %0,%1\n\tcvt.s.w %0,%0" : "=f"(t) : "f"(d));
    if (d < t) t -= 1.0f;
    int n = (int)t;
    const char* fmt;
    if (n < 0) {
        fmt = D_004A3998;
    } else if (n < 1) {
        fmt = D_004A39A0;
    } else if (n < 2) {
        fmt = D_004A39A8;
    } else if (n < 3) {
        fmt = D_004A39B0;
    } else if (n < 7) {
        fmt = D_004A39B8;
    } else {
        fmt = D_004A39C0;
    }
    sBXStrDFD8 s;
    s.p = (char*)D_004A3E90;
    func_003194A8(&s, fmt, func_00413AF8(v));
    cBXString_cBXString1(out, &s);
    cBXString__cBXString(&s, 2);
    return out;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: the unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");
extern "C" void cBXString__cBXString(void* self, int flags);

struct func_002CE100_sString {
    char* str;
};

// returns a cBXString by value (hidden result pointer in $4)
extern "C" void func_002CDFD8(func_002CE100_sString* out, float v);

extern "C" void func_002CE100(void* self, int a1)
{
    func_002CE100_sString s;
    func_002CDFD8(&s, **(float**)((char*)self + 0x18) * *(float*)((char*)self + 0x24) + *(float*)((char*)self + 0x28));
    func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, s.str);
    cBXString__cBXString(&s, 2);
}

//100%
extern void* D_00486B10[];

extern "C" sFloatMenuItem_2CDC88* func_002CE170(sFloatMenuItem_2CDC88* self, void* text, int a2, int a3, float f1, float f2)
{
    cMenuItem_cMenuItem((cMenuItem*)self, text);
    self->field_0x14 = a3;
    self->field_0x18 = a2;
    self->field_0x1C = f1;
    self->field_0x20 = f2;
    self->vtable = D_00486B10;
    self->field_0x28 = 0;
    self->field_0x24 = 0;
    return self;
}

//100%
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3B0(void* self);

// PORT: uses g++'s >? (max) operator.
extern "C" int func_002CE1F0(void* self)
{
    char* s = (char*)self;
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) != 0) {
        return r;
    }
    if (r != 0) {
        return r;
    }
    float d = func_002CA428_f(self) - func_002CA408_f(self);
    int dir;
    if (d <= -0.1f || d >= 0.1f) {
        dir = 1;
        if (d < 0.0f) {
            dir = -1;
        }
    } else {
        dir = 0;
    }
    if (dir == *(int*)(s + 0x28)) {
        *(int*)(s + 0x24) += 1;
    } else {
        *(int*)(s + 0x24) = 0;
        *(int*)(s + 0x28) = dir;
    }
    if (dir != 0) {
        int n = *(int*)(s + 0x24);
        float k = (float)(n * n) * 0.0034722222480922937f;
        k = k >? 1.0f;
        float step = 4.999999873689376e-05f;
        step = k * step;
        float* p = *(float**)(s + 0x18);
        *p = *p + d * step * (*(float*)(s + 0x20) - *(float*)(s + 0x1C));
        if (**(float**)(s + 0x18) < *(float*)(s + 0x1C)) {
            **(float**)(s + 0x18) = *(float*)(s + 0x1C);
        }
        if (*(float*)(s + 0x20) < **(float**)(s + 0x18)) {
            **(float**)(s + 0x18) = *(float*)(s + 0x20);
        }
        char* menu = *(char**)s;
        sVEntry002CD9D8* vt = *(sVEntry002CD9D8**)(menu + 0x12C);
        vt[4].fn(menu + vt[4].delta, self);
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);
extern void* D_004866F0[];

extern "C" void* func_002CE368(void* self, void* a1)
{
    func_002CA4C8(self, a1, *(int*)((char*)a1 + 0x14), 0, D_004866F0);
    return self;
}

//100%
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" int func_00413AF8(float f);
// PORT: the unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");
extern char D_004A39C8[];

extern "C" void cAngleMenuItem_render(void* self, int a1)
{
    char buf[0x70];
    sprintf(buf, D_004A39C8, func_00413AF8(**(float**)((char*)self + 0x18) * 57.2957763671875f));
    func_002CA988_5(self, a1, *(int*)((char*)self + 0x14), 0, buf);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");
extern "C" char* strncpy(char* dst, const char* src, unsigned int n);
extern void* D_00486AC0[];

struct func_002CE418_sItem {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    int field_0x14;
    char name[0x10]; // 0x18
    int field_0x28;
};

extern "C" func_002CE418_sItem* func_002CE418(func_002CE418_sItem* self, int a1, const char* name)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = a1;
    self->field_0x28 = 0;
    self->vtable = D_00486AC0;
    strncpy(self->name, name, 0xF);
    self->name[0xF] = 0;
    return self;
}

//100%
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3E8(void** self);
extern "C" int strlen(const char* s);
int func_002CC250(void* self);
int func_002CC258(void* self);

struct sTextItem_E488 {
    char* menu;                 // 0x00
    char pad4[0x14];            // 0x04
    char name[0x10];            // 0x18
    int cursor;                 // 0x28
};

static inline int validChar_E488(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '!';
}

extern "C" int func_002CE488(sTextItem_E488* self)
{
    int r = func_002CA2B0(self);
    if (r == 0) {
    int len = strlen(self->name);
    int mod = len + 1;
    if (mod >= 16) {
        mod = 15;
    }
    int key = func_002CA3E8((void**)self);
    if (key == 2) {
        self->cursor = (self->cursor + mod - 1) % mod;
    } else if (key == 3) {
        self->cursor = (self->cursor + 1) % mod;
    } else if (key == 4) {
        // PORT: pointer in int (index-first address).
        char* c = (char*)(self->cursor + (int)self);
        c += 0x18;
        do {
            (*c)--;
        } while (!validChar_E488(*c));
    } else if (key == 5) {
        // PORT: pointer in int (index-first address).
        char* c = (char*)(self->cursor + (int)self);
        c += 0x18;
        do {
            (*c)++;
        } while (!validChar_E488(*c));
    } else if (key == 9) {
        if (len < 14) {
            for (int i = self->cursor; i < len; i++) {
                self->name[i + 1] = self->name[i];
            }
            self->name[self->cursor] = '_';
        }
    } else if (key == 10) {
        if (len != 0 && self->cursor < len) {
            for (int i = self->cursor; i < len - 1; i++) {
                self->name[i] = self->name[i + 1];
            }
            self->name[len - 1] = 0;
        }
    } else if (key == 6) {
        r = 3;
    } else {
        int code = func_002CC250(*(void**)(self->menu + 0x124));
        int ch = func_002CC258(*(void**)(self->menu + 0x124));
        if (code == 8) {
            if (len != 0 && self->cursor > 0) {
                for (int i = self->cursor; i < len - 1; i++) {
                    self->name[i] = self->name[i + 1];
                }
                self->name[len - 1] = 0;
                self->cursor--;
            }
        } else if (validChar_E488(ch)) {
            if (len < 14) {
                for (int i = self->cursor; i < len; i++) {
                    self->name[i + 1] = self->name[i];
                }
                self->name[self->cursor++] = ch;
            }
        }
    }
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* func_002CBF30(void* self);
extern "C" void func_002CA4C8(void*, void*, int, int, void*);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int strlen(const char* s);
extern "C" char* func_004162D0(char* dst, const char* src);
extern char D_004A39D0[];

struct func_002CE820_sResult {
    int a;
    int b;
    int c;
    int d;
};

static inline func_002CE820_sResult func_002CE820_make(void* item, int id, char* text)
{
    func_002CE820_sResult t;
    func_002CA4C8(&t, item, id, 0, text);
    return t;
}

extern "C" func_002CE820_sResult func_002CE820(void* item)
{
    char buf[0x20];
    char* name = (char*)item + 0x18;
    int focused = item == func_002CBF30(*(void**)item);
    strcpy(buf, name);
    int len = strlen(name);
    if (focused && *(int*)((char*)item + 0x28) == len && *(int*)((char*)item + 0x28) < 15) {
        func_004162D0(buf, D_004A39D0);
    }
    func_002CE820_sResult r = func_002CE820_make(item, *(int*)((char*)item + 0x14), buf);
    return r;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_00391CB0(void* self, float x, float y, const char* str);
extern "C" float func_00391FB0(void* self, const char* str, void* out, int n, float sx, float sy);

struct sVec2_2CE910 {
    float x, y;
    sVec2_2CE910(float ax, float ay) { x = ax; y = ay; }
};

struct sVec4_2CE910 {
    float x, y, z, w;
    sVec4_2CE910() {}
    void Set(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
} __attribute__((aligned(16)));

struct sVtx_2CE910 {
    float u, v, q;
    int pad;
    int r, g, b, a;
    sVec4_2CE910 pos;
    sVtx_2CE910() {}
};

struct sRS_2CE910 {
    int f0;
    unsigned int f4_0 : 2;
    unsigned int f4_2 : 5;
    unsigned int f4_7 : 25;
};

class cCtx_2CE910 {
public:
    char pad0[0xE84];
    sRS_2CE910* top;
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

extern cCtx_2CE910* D_004A289C_ce910 __asm__("D_004A289C");

INCLUDE_ASM("util/menu", func_002CE910);
extern "C" void func_002CE910(void* self, float* rect);

//100%
// PORT: the base ctor's 2nd arg is really an int (id/text handle; -1 = none).
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

extern void* D_00486A70[];

struct cColorMenuItem__cColorMenuItem_sItem {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    void* field_0x14;
    void* field_0x18;
};

extern "C" cColorMenuItem__cColorMenuItem_sItem* cColorMenuItem__cColorMenuItem(cColorMenuItem__cColorMenuItem_sItem* self, void* a1, void* a2)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = a1;
    self->field_0x18 = a2;
    self->vtable = D_00486A70;
    return self;
}

//100%
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3B0(void* self);

// PORT: uses g++'s >? (max) operator.
extern "C" int func_002CED78(void* self)
{
    char* s = (char*)self;
    int r = func_002CA2B0(self);
    if (func_002CA3B0(self) != 0) {
        return r;
    }
    if (r != 0) {
        return r;
    }
    float d = func_002CA428_f(self) - func_002CA408_f(self);
    int dir;
    if (d <= -0.1f || d >= 0.1f) {
        dir = 1;
        if (d < 0.0f) {
            dir = -1;
        }
    } else {
        dir = 0;
    }
    if (dir == *(int*)(s + 0x20)) {
        *(int*)(s + 0x1C) += 1;
    } else {
        *(int*)(s + 0x1C) = 0;
        *(int*)(s + 0x20) = dir;
    }
    if (dir != 0) {
        int n = *(int*)(s + 0x1C);
        int m = (n * n / 0x120) >? 1;
        float* p = (float*)(*(char**)(s + 0x14) + (*(int*)(s + 0x18) << 2));
        float step = 0.0003906250058207661f;
        step = (float)m * step;
        float v = *p;
        v += d * step;
        if (v < 0.0f) {
            v = 0.0f;
        }
        if (1.0f < v) {
            v = 1.0f;
        }
        *p = v;
        char* menu = *(char**)s;
        sVEntry002CD9D8* vt = *(sVEntry002CD9D8**)(menu + 0x12C);
        vt[4].fn(menu + vt[4].delta, self);
    }
    return r;
}

//100%
extern "C" float func_00391FB0(void* self, const char* str, void* out, int n, float sx, float sy);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" int func_00413AF8(float f);
extern char D_00486700[];
extern char* D_00487470[];

struct sRect_2CEEE8 { float x, y, w, h; };

struct sFont_2CEEE8 {
    char pad_0x0[0x14];
    int lineHeight;                 // 0x14
    char pad_0x18[0x18];
    float scaleX;                   // 0x30
    float scaleY;                   // 0x34
    float drawScaleX;               // 0x38
    float drawScaleY;               // 0x3C
};

struct sMenuValueItem_2CEEE8 {
    char* menu;                     // 0x00
    char pad_0x4[0x10];
    float* values;                  // 0x14
    int index;                      // 0x18
};

static inline sFont_2CEEE8* font_2CEEE8(sMenuValueItem_2CEEE8* item)
{
    return *(sFont_2CEEE8**)(*(char**)(item->menu + 0x124) + 0x58);
}

static inline float textWidth_2CEEE8(sMenuValueItem_2CEEE8* item, const char* str)
{
    sFont_2CEEE8* f = font_2CEEE8(item);
    return func_00391FB0(f, str, 0, 0, f->drawScaleX, f->drawScaleY);
}

#define MAX_2CEEE8(a, b) ((a) > (b) ? (a) : (b))

// Returns the rect of a value menu item: sized for the widest of the three option labels plus the formatted value.
extern "C" sRect_2CEEE8* func_002CEEE8(sRect_2CEEE8* ret, sMenuValueItem_2CEEE8* item)
{
    sRect_2CEEE8 r;
    char buf[64];
    sprintf(buf, D_00486700, func_00413AF8(*(float*)((char*)item->values + (item->index << 2))));
    float z = 0.0f;
    r.y = z;
    r.x = z;
    sFont_2CEEE8* font = font_2CEEE8(item);
    r.h = (float)font->lineHeight * font->scaleY + 12.0f;
    r.w = MAX_2CEEE8(MAX_2CEEE8(textWidth_2CEEE8(item, D_00487470[0]), textWidth_2CEEE8(item, D_00487470[1])),
                     textWidth_2CEEE8(item, D_00487470[2]));
    r.w = r.w + textWidth_2CEEE8(item, buf) + 144.0f;
    *ret = r;
    return ret;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_00391CB0(void* self, float x, float y, const char* str);
extern "C" float func_00391FB0(void* self, const char* str, void* out, int n, float sx, float sy);
extern "C" int func_00413AF8(float f);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char* D_00487470[];
extern char D_00486710[];

struct sVEntry_2CF1C8 {
    short delta;
    short index;
    void (*fn)(void*, float*, int);
};

struct sVec2_2CF1C8 {
    float x, y;
    sVec2_2CF1C8(float ax, float ay) { x = ax; y = ay; }
};

struct sRect_2CF1C8 {
    float x, y, w, h;
};

struct sVec4_2CF1C8 {
    float x, y, z, w;
    sVec4_2CF1C8() {}
    void Set(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
} __attribute__((aligned(16)));

struct sVtx_2CF1C8 {
    float u, v, q;
    int pad;
    int r, g, b, a;
    sVec4_2CF1C8 pos;
    sVtx_2CF1C8() {}
};

struct sRS_2CF1C8 {
    int f0;
    unsigned int f4_0 : 2;
    unsigned int f4_2 : 5;
    unsigned int f4_7 : 25;
};

class cCtx_2CF1C8 {
public:
    char pad0[0xE84];
    sRS_2CF1C8* top;
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

extern cCtx_2CF1C8* D_004A289C_cf1c8 __asm__("D_004A289C");

INCLUDE_ASM("util/menu", func_002CF1C8);
extern "C" void func_002CF1C8(void* self, float* rect);

//100%
class func_002CF788_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual int v09(int a, int b);
    virtual int v10(int a);
};

extern "C" int func_002CF788(void* self, int a, int b)
{
    return (*(func_002CF788_cItem**)((char*)self + 0x130))->v09(a, b);
}

//100%
class func_002CF7B8_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual int v09(int a, int b);
    virtual void v10(int a);
};

extern "C" void func_002CF7B8(void* self, int a)
{
    (*(func_002CF7B8_cItem**)((char*)self + 0x130))->v10(a);
}

INCLUDE_ASM("util/menu", func_002CF7E8);

INCLUDE_ASM("util/menu", func_002CF860);

//100%
class func_002CF8D8_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
};

extern "C" void* func_002CBF30(void* self);

extern "C" void func_002CF8D8(void* self)
{
    ((func_002CF8D8_cItem*)func_002CBF30((char*)self + 0x18))->v08();
}

// PORT: cMenu_addItem is extern "C" (list, item, index); this caller leaves $a2 as-is.
void cMenu_addItem2(void* menu, void* item) __asm__("cMenu_addItem");

//100%
void cExpandMenuItem_addItem(void* self, void* item)
{
    cMenu_addItem2((char*)self + 0x18, item);
}

//100%
extern "C" void func_002CBD50(void* menu, int index);

// Removes sub item index from the expand item's menu.
extern "C" void func_002CF928(void* self, int index)
{
    func_002CBD50((char*)self + 0x18, index);
}

//100%
extern "C" void func_002CBE10(int* self);
// PORT: called with a third argument (-1) here; bound to the same symbol.
void cExpandMenuItem_addItem3(void* self, void* item, int index) __asm__("cExpandMenuItem_addItem__FPvT0");

extern "C" void func_002CF948(void* self)
{
    func_002CBE10((int*)((char*)self + 0x18));
    void* item = *(void**)((char*)self + 0x14);
    if (item != 0)
        cExpandMenuItem_addItem3(self, item, -1);
}

//100%
void cExpandMenuItem_addItem3(void* self, void* item, int index) __asm__("cExpandMenuItem_addItem__FPvT0");

// Replaces the expand item's current sub item.
extern "C" void func_002CF988(void* self, void* item)
{
    int i;
    for (i = 0; i < ((cMenuList*)((char*)self + 0x18))->count; i++) {
        if (((cMenuList*)((char*)self + 0x18))->items[i] == *(void**)((char*)self + 0x14)) {
            func_002CBD50((char*)self + 0x18, i);
            break;
        }
    }
    *(void**)((char*)self + 0x14) = item;
    cExpandMenuItem_addItem3(self, item, 0);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int func_002CA3B0(void* self);
extern "C" void func_002CAAB0(void* self);
extern "C" void func_002CAB08(void* self);
extern "C" void func_002CABE0(void* self);

class func_002CFA08_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual int v02();
};

struct func_002CFA08_sOwner {
    char pad[0x18];
    func_002CBE68_sMenu menu;
};

// PORT: returns a key code (int) through the unit's void* declaration.
extern "C" void* func_002CFA08(void* p)
{
    func_002CFA08_sOwner* self = (func_002CFA08_sOwner*)p;
    func_002CAAB0(&self->menu);
    int prev = self->menu.selected;
    int key = ((func_002CFA08_cItem*)self->menu.items[prev])->v02();
    if (func_002CA3B0(self) != 0) {
        return (void*)key;
    }
    switch (key) {
    case 3:
        func_002CAB08(&self->menu);
        if (prev < self->menu.selected) {
            return 0;
        }
        func_002CBE68(&self->menu, prev);
        return (void*)3;
    case 4:
        func_002CABE0(&self->menu);
        if (self->menu.selected < prev) {
            return 0;
        }
        func_002CBE68(&self->menu, prev);
        return (void*)4;
    }
    return (void*)key;
}

//100%
class func_002CFAF8_cMenu {
public:
    char pad[0x12C];
    // vptr at 0x12C; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual int v03(int a, int b);
};

extern "C" int func_002CFAF8(func_002CFAF8_cMenu** self, int a, int b)
{
    return (*self)->v03(a, b);
}

//100%
class func_002CFB28_cMenu {
public:
    char pad[0x12C];
    // vptr at 0x12C; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04(void*);
};

extern "C" void func_002CFB28(func_002CFB28_cMenu** self)
{
    (*self)->v04(self);
}

//100%
extern "C" int func_002CA378(void* self);
extern "C" void* func_002CBF30(void* self);

struct sMenuRect_2CFB58 { float x, y, z, w; };

struct sVEnt_2CFB58 { short delta; short index; sMenuRect_2CFB58 (*fn)(void*); };

struct sItem_2CFB58 {
    char pad00[0x10];
    sVEnt_2CFB58* vt;
};

struct sMenu_2CFB58 {
    char* owner;
    char pad04[0x10];
    sItem_2CFB58* sel;
    int count;
    char pad1C[8];
    sItem_2CFB58* items[70];
    void* f13C;
    char pad140[0xC];
    sMenuRect_2CFB58 rects[1];
};

extern "C" sMenuRect_2CFB58* func_002CFB58(sMenuRect_2CFB58* ret, sMenu_2CFB58* self)
{
    sMenuRect_2CFB58 r;
    float zero = 0.0f;
    r.w = zero;
    r.z = zero;
    r.y = zero;
    r.x = zero;
    self->f13C = *(void**)(self->owner + 0x124);
    for (int i = 0; i < self->count; i++) {
        if (func_002CA378(self->items[i])) {
            sVEnt_2CFB58* vt = self->items[i]->vt;
            self->rects[i] = vt[4].fn((char*)self->items[i] + vt[4].delta);
            if (self == func_002CBF30(self->owner) || self->items[i] == self->sel) {
                r.w += self->rects[i].w;
            }
            float h = self->rects[i].z;
            if (self->items[i] != self->sel) {
                h += 20.0f;
            }
            if (r.z < h) {
                r.z = h;
            }
        } else {
            sMenuRect_2CFB58 z;
            z.x = 0;
            z.y = 0;
            z.z = 0;
            z.w = 0;
            self->rects[i] = z;
        }
    }
    *ret = r;
    return ret;
}

//100%
extern "C" int func_002CA378(void* self);
extern "C" void* func_002CBF30(void* self);

struct func_002CFD28_sRect {
    float x, y, w, h;
};

class func_002CFD28_cItem {
public:
    char pad[0x10];
    // vptr at 0x10; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05(func_002CFD28_sRect* r);
};

struct func_002CFD28_sOwner {
    void* menu;                         // 0x0
    char pad4[0x10];
    func_002CFD28_cItem* cur;           // 0x14
    int count;                          // 0x18
    int selected;                       // 0x1C
    int unk20;                          // 0x20
    func_002CFD28_cItem* items[70];     // 0x24
    int wrap;                           // 0x13C
    char pad140[0xC];
    func_002CFD28_sRect rects[70];      // 0x14C
};

extern "C" void func_002CFD28(func_002CFD28_sOwner* self, func_002CFD28_sRect* r)
{
    func_002CFD28_sRect pos = *r;
    for (int i = 0; i < self->count; i++) {
        if (func_002CA378(self->items[i]) == 0) {
            continue;
        }
        if ((void*)self == func_002CBF30(self->menu) || self->items[i] == self->cur) {
            int off = self->items[i] == self->cur ? 0 : 20;
            self->rects[i].x = pos.x + (float)off;
            self->rects[i].y = pos.y;
            self->rects[i].w = pos.w - (float)off;
            self->items[i]->v05(&self->rects[i]);
            pos.y += self->rects[i].h;
        }
    }
}

//100%
// PORT: the target leaves mode in $a1 for func_002CA368; bind a 2-arg form to that symbol.
void func_002CA368_2(void* self, int a1) __asm__("func_002CA368__FPv");
extern "C" void func_002CBE68_v(void* self, int index) __asm__("func_002CBE68");

extern "C" void func_002CFE78(void* self, int mode)
{
    func_002CA368_2(self, mode);
    switch (mode) {
    case 0:
        func_002CBE68_v((char*)self + 0x18, 0);
        break;
    case 1:
        func_002CBE68_v((char*)self + 0x18, -1);
        break;
    }
    func_002CBF60((char*)self + 0x18, *(int*)(*(char**)self + 0x124));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CBFD0(void* p);

extern "C" void func_002CFEF8(void* self)
{
    func_002CA370(self);
    func_002CBFD0((char*)self + 0x18);
}

//100%
// PORT: the base ctor's 2nd arg is really an int (id/text handle; -1 = none).
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

extern void* D_00486968[];

struct cRGBTitleMenuItem_sItem {
    char pad_0x00[0x10];
    void* vtable;    // 0x10
    void* field_0x14;
    void* field_0x18;
};

extern "C" cRGBTitleMenuItem_sItem* cRGBTitleMenuItem_cRGBTitleMenuItem(cRGBTitleMenuItem_sItem* self, void* a1, void* a2)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = a2;
    self->field_0x18 = a1;
    self->vtable = D_00486968;
    return self;
}

//100%
int func_002CFF80(void* self)
{
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct func_002CFF88_sRect {
    float x;
    float y;
    float w;
    float h;
};

// PORT: `>?` (g++ max operator); returns the rect through the hidden result pointer.
extern "C" func_002CFF88_sRect* func_002CFF88(func_002CFF88_sRect* out, void* item)
{
    func_002CFF88_sRect r;
    func_002CA4C8(&r, item, *(int*)((char*)item + 0x18), 0, 0);
    r.w += 36.0f;
    r.h = r.h >? 29.0f;
    *out = r;
    return out;
}

//100%
// PORT: the unit's 4-arg declaration of func_002CA988 is wrong: the body reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

struct sCol_2D0008 { float a, r, g, b; };

struct sVtx_2D0008 {
    float u, v, q;
    int pad;
    int r, g, b, a;
    float pos[4] __attribute__((aligned(16)));
    sVtx_2D0008() {}
};

struct sVec4_2D0008 {
    float x, y, z, w;
    sVec4_2D0008(const float& ax, const float& ay, const float& az, const float& aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

struct sRect_2D0008 { float x, y, w, h; };

struct sRS_2D0008 {
    int f0;
    unsigned int f4_0 : 2;
    unsigned int f4_2 : 5;
    unsigned int f4_7 : 25;
    int f8;
    int fC;
    short f10;
};

class cCtx_2D0008 {
public:
    char pad0[0xE84];
    sRS_2D0008* top;
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
    virtual void v71(int prim, void* verts, int n);
};

extern cCtx_2D0008* D_004A289C_2d0008 __asm__("D_004A289C");

// PORT: rect pointer passed through func_002CA988's int parameter
INCLUDE_ASM("util/menu", func_002D0008);
extern "C" void func_002D0008(char* self, float* rect);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* func_002CF860(void* self, void* name, void* title);
// PORT: cExpandMenuItem_addItem forwards $a2 (insert index) to cMenu_addItem; bound with that third argument.
void cExpandMenuItem_addItem3(void* self, void* item, int index) __asm__("cExpandMenuItem_addItem__FPvT0");
extern void* D_00486908[];

extern "C" void* cARGBMenuItem_cARGBMenuItem(void* self, void* name, void* title, void* color)
{
    char* s = (char*)self;
    func_002CF860(self, name, s + 0x640);
    *(void**)(s + 0x5AC) = color;
    *(void***)(s + 0x10) = D_00486908;
    // PORT: the channel index is passed in the unit's void* parameter
    cColorMenuItem__cColorMenuItem((cColorMenuItem__cColorMenuItem_sItem*)(s + 0x5B0), color, (void*)0);
    cColorMenuItem__cColorMenuItem((cColorMenuItem__cColorMenuItem_sItem*)(s + 0x5D4), color, (void*)1);
    cColorMenuItem__cColorMenuItem((cColorMenuItem__cColorMenuItem_sItem*)(s + 0x5F8), color, (void*)2);
    cColorMenuItem__cColorMenuItem((cColorMenuItem__cColorMenuItem_sItem*)(s + 0x61C), color, (void*)3);
    cRGBTitleMenuItem_cRGBTitleMenuItem((cRGBTitleMenuItem_sItem*)(s + 0x640), title, color);
    cExpandMenuItem_addItem3(self, s + 0x5B0, -1);
    cExpandMenuItem_addItem3(self, s + 0x5D4, -1);
    cExpandMenuItem_addItem3(self, s + 0x5F8, -1);
    cExpandMenuItem_addItem3(self, s + 0x61C, -1);
    return self;
}

extern "C" void* func_002CFA08(void* self);

//99.29%
void* func_002D03D0(void* self)
{
    return func_002CFA08(self);
}

//100%
extern void* D_004868B8[];

extern "C" sMenuItem_2CC7B0* func_002D03F0(sMenuItem_2CC7B0* self, int a1, int a2)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->field_0x14 = a2;
    self->field_0x18 = a1;
    self->vtable = D_004868B8;
    return self;
}

//100%
int func_002D0448(void* self)
{
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002CA4C8(void*, void*, int, int, void*);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" int func_00413AF8(float f);
extern char D_00486720[];

extern "C" void* func_002D0450(void* ret, void* item)
{
    char buf[0x80];
    const char* fmt = D_00486720;
    int x = func_00413AF8((*(float**)((char*)item + 0x14))[0]);
    int y = func_00413AF8((*(float**)((char*)item + 0x14))[1]);
    int z = func_00413AF8((*(float**)((char*)item + 0x14))[2]);
    sprintf(buf, fmt, x, y, z);
    func_002CA4C8(ret, item, *(int*)((char*)item + 0x18), 0, buf);
    return ret;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" int func_00413AF8(float f);
extern char D_00486720[];
// PORT: the unit's 4-arg declaration of func_002CA988 is wrong: the callee reads $8 (5th arg).
void* func_002CA988_5(void*, int, int, int, void*) __asm__("func_002CA988");

extern "C" void func_002D0500(void* self, int a1)
{
    char buf[0x80];
    const char* fmt = D_00486720;
    int x = func_00413AF8((*(float**)((char*)self + 0x14))[0]);
    int y = func_00413AF8((*(float**)((char*)self + 0x14))[1]);
    int z = func_00413AF8((*(float**)((char*)self + 0x14))[2]);
    sprintf(buf, fmt, x, y, z);
    func_002CA988_5(self, a1, *(int*)((char*)self + 0x18), 0, buf);
}

//100%
//100%
extern void* D_00486858[];
extern char D_004A39D8[];
extern char D_004A39E0[];
extern char D_004A39E8[];

extern "C" void* func_002D05A8(void* self, void* name, float* values, int a3, float lo, float hi)
{
    char* s = (char*)self;
    func_002CF860(self, name, s + 0x654);
    *(float**)(s + 0x5AC) = values;
    *(void***)(s + 0x10) = D_00486858;
    // PORT: the unit types these parameters loosely; the index goes in text, the value pointer and label in the ints
    cFloatMenuItem_cFloatMenuItem((cFloatMenuItem_sItem*)(s + 0x5B8), (void*)0, (int)values, (int)D_004A39D8, lo, hi);
    cFloatMenuItem_cFloatMenuItem((cFloatMenuItem_sItem*)(s + 0x5EC), (void*)1, (int)(values + 1), (int)D_004A39E0, lo, hi);
    cFloatMenuItem_cFloatMenuItem((cFloatMenuItem_sItem*)(s + 0x620), (void*)2, (int)(values + 2), (int)D_004A39E8, lo, hi);
    func_002D03F0((sMenuItem_2CC7B0*)(s + 0x654), a3, (int)values);
    cExpandMenuItem_addItem3(self, s + 0x5B8, -1);
    cExpandMenuItem_addItem3(self, s + 0x5EC, -1);
    cExpandMenuItem_addItem3(self, s + 0x620, -1);
    *(int*)(s + 0x670) = 0;
    return self;
}

//100%
extern "C" void* func_002CFA08(void* self);

struct sMenuChanD6E8 {
    char pad0[0x18];
    float* target;              // 0x18
    char pad1C[0x24 - 0x1C];
    float scale;                // 0x24
    float offset;               // 0x28
    char pad2C[0x34 - 0x2C];
    float get() { return *target; }
    void set(float v) { *target = v; }
};
struct sMenuVecD6E8 {
    float x, y, z;
    sMenuVecD6E8() {}
    sMenuVecD6E8(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct sMenuColD6E8 {
    char pad0[0x5B8];
    sMenuChanD6E8 ch[3];        // 0x5B8
    char pad654[0x670 - 0x654];
    int linked;                 // 0x670
};

static inline void menuNormalizeD6E8(sMenuVecD6E8& out, const sMenuVecD6E8& v)
{
    float d = v.x * v.x + v.y * v.y + v.z * v.z;
    float len;
    // PORT: sqrt.s (sqrtf without errno check)
    __asm__("sqrt.s %0, %1" : "=f"(len) : "f"(d));
    if (len != 0.0f) {
        float inv = 1.0f / len;
        out.x = v.x * inv;
        out.y = v.y * inv;
        out.z = v.z * inv;
    } else {
        out.x = v.x;
        out.y = v.y;
        out.z = v.z;
    }
}

extern "C" void* func_002D06E8(sMenuColD6E8* self)
{
    void* ret = func_002CFA08(self);
    if (self->linked != 0) {
        sMenuVecD6E8 n;
        sMenuVecD6E8 v(self->ch[0].scale * self->ch[0].get() + self->ch[0].offset,
                       self->ch[1].scale * self->ch[1].get() + self->ch[1].offset,
                       self->ch[2].scale * self->ch[2].get() + self->ch[2].offset);
        menuNormalizeD6E8(n, v);
        self->ch[0].set(n.x);
        self->ch[1].set(n.y);
        self->ch[2].set(n.z);
    }
    return ret;
}

//100%
// PORT: the base ctor's 2nd arg is really an int (id/text handle; -1 = none).
cMenuItem* cMenuItem_cMenuItem_id(cMenuItem* self, int id) __asm__("cMenuItem_cMenuItem__FP9cMenuItemPv");

extern char D_00486808[];
extern char D_00486738[];

struct sMenuPair_D0808 {
    long v;
} __attribute__((packed));

struct sMenuItem_D0808 {
    char pad_0x00[0x10];
    void* vtable;           // 0x10
    void* vtable2;          // 0x14
    int a1;                 // 0x18
    int a2;                 // 0x1C
    int a3;                 // 0x20
    int unk24;              // 0x24
    int a5;                 // 0x28
    sMenuPair_D0808 p0;     // 0x2C
    sMenuPair_D0808 p1;     // 0x34
    int a4;                 // 0x3C
    int unk40;              // 0x40
};

extern "C" sMenuItem_D0808* func_002D0808(sMenuItem_D0808* self, int a1, int a2, int a3, int a4, int a5,
                                         sMenuPair_D0808* p0, sMenuPair_D0808* p1)
{
    cMenuItem_cMenuItem_id((cMenuItem*)self, -1);
    self->vtable = D_00486808;
    self->a1 = a1;
    self->a5 = a5;
    self->a2 = a2;
    self->a3 = a3;
    self->a4 = a4;
    self->p0 = *p0;
    self->p1 = *p1;
    self->vtable2 = D_00486738;
    self->unk24 = 0;
    self->unk40 = 0;
    return self;
}

//100% - objdiff report; single-function view differs only in a relocation name
void func_002CA368(void* self);

extern "C" void func_002D08E0(void* self)
{
    func_002CA368(self);
    *(int*)((char*)self + 0x40) = 0;
}

//100%
extern "C" int func_002CA2B0(void* self);
extern "C" int func_002CA3B0(void* self);
extern "C" int func_002CA3E8(void** self);
float func_002CA408_f(void* self) __asm__("func_002CA408__FPv");
float func_002CA428_f(void* self) __asm__("func_002CA428__FPv");
// PORT: the unit declares func_002CA448/func_002CA468 as void*; these callers use the float result.
float func_002CA448_f(void* self) __asm__("func_002CA448__FPv");
float func_002CA468_f(void* self) __asm__("func_002CA468__FPv");

struct sCurvePt_D0908 {
    float x, y;
};

struct sVE_D0908 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

struct sCurveItem_D0908 {
    char* menu;                 // 0x00
    char pad4[0x14];            // 0x04
    int count;                  // 0x18
    unsigned int lockX;         // 0x1C
    unsigned int lockY;         // 0x20
    int cur;                    // 0x24
    sCurvePt_D0908* pts;        // 0x28
    float minX;                 // 0x2C
    float minY;                 // 0x30
    float maxX;                 // 0x34
    float maxY;                 // 0x38
    int order;                  // 0x3C
    int editing;                // 0x40
};

extern "C" int func_002D0908(sCurveItem_D0908* self)
{
    int r = 0;
    if (func_002CA3B0(self) == 0) {
    int changed = 0;
    if (func_002CA3E8((void**)self) == 6) {
        self->editing ^= 1;
    }
    if (self->editing != 0) {
        if (func_002CA3E8((void**)self) == 8) {
            self->editing = 0;
        } else if (func_002CA3E8((void**)self) == 7) {
            self->editing = 0;
        } else if (self->editing != 0) {
            if (func_002CA3E8((void**)self) == 4) {
                if (self->cur > 0) {
                    self->cur--;
                    changed = 1;
                }
            } else if (func_002CA3E8((void**)self) == 5) {
                if (self->cur < self->count - 1) {
                    self->cur++;
                    changed = 1;
                }
            }
            float step = (self->maxX - self->minX) / (float)(self->count * 2 > 49 ? self->count * 2 : 50);
            float dy = func_002CA448_f(self) - func_002CA468_f(self);
            if (dy != 0.0f && (self->lockY & (1 << self->cur)) == 0) {
                self->pts[self->cur].y += dy * (self->maxY - self->minY) * 0.008333333767950535f;
                changed = 1;
                if (self->maxY < self->pts[self->cur].y) {
                    self->pts[self->cur].y = self->maxY;
                }
                if (self->pts[self->cur].y < self->minY) {
                    self->pts[self->cur].y = self->minY;
                }
                if (self->cur < self->count - 1) {
                    if (self->order > 0 && self->pts[self->cur + 1].y < self->pts[self->cur].y) {
                        self->pts[self->cur].y = self->pts[self->cur + 1].y;
                    } else if (self->order < 0 && self->pts[self->cur].y < self->pts[self->cur + 1].y) {
                        self->pts[self->cur].y = self->pts[self->cur + 1].y;
                    }
                }
                if (self->cur > 0) {
                    if (self->order > 0 && self->pts[self->cur].y < self->pts[self->cur - 1].y) {
                        self->pts[self->cur].y = self->pts[self->cur - 1].y;
                    } else if (self->order < 0 && self->pts[self->cur - 1].y < self->pts[self->cur].y) {
                        self->pts[self->cur].y = self->pts[self->cur - 1].y;
                    }
                }
            }
            float dx = func_002CA428_f(self) - func_002CA408_f(self);
            if (dx != 0.0f && (self->lockX & (1 << self->cur)) == 0) {
                self->pts[self->cur].x += dx * (self->maxX - self->minX) * 0.008333333767950535f;
                changed = 1;
                if (self->maxX < self->pts[self->cur].x) {
                    self->pts[self->cur].x = self->maxX;
                }
                if (self->pts[self->cur].x < self->minX) {
                    self->pts[self->cur].x = self->minX;
                }
                if (self->cur < self->count - 1) {
                    if (self->pts[self->cur + 1].x - step < self->pts[self->cur].x) {
                        self->pts[self->cur].x = self->pts[self->cur + 1].x - step;
                    }
                }
                if (self->cur > 0) {
                    if (self->pts[self->cur].x < self->pts[self->cur - 1].x + step) {
                        self->pts[self->cur].x = self->pts[self->cur - 1].x + step;
                    }
                }
            }
        } else {
            r = func_002CA2B0(self);
        }
    } else {
        r = func_002CA2B0(self);
    }
    if (changed) {
        sVE_D0908* vt = *(sVE_D0908**)(self->menu + 0x12C);
        vt[4].fn(self->menu + vt[4].delta, self);
    }
    }
    return r;
}

//100%
extern "C" void* func_002CBF30(void* self);
extern "C" float func_00391FB0(void* self, const char* str, void* out, int n, float sx, float sy);
extern char D_00486748[];

struct sMenuRect_2D0D48 { float x, y, z, w; };

static inline char* font_2D0D48(char* item)
{
    return *(char**)(*(char**)(*(char**)item + 0x124) + 0x58);
}

extern "C" sMenuRect_2D0D48* func_002D0D48(sMenuRect_2D0D48* ret, char* item)
{
    int margin = 100;
    int focused = 0;
    if (item == func_002CBF30(*(void**)item)) {
        focused = *(int*)(item + 0x40) != 0;
    }
    int pad = focused ? 0x50 : 0x14;
    char* font = font_2D0D48(item);
    float lh = (float)*(int*)(font + 0x14) * *(float*)(font + 0x34);
    float w = func_00391FB0(font, *(char**)(item + 0x14), 0, 0, *(float*)(font + 0x38), *(float*)(font + 0x3C));
    char* font2 = font_2D0D48(item);
    float w2 = func_00391FB0(font2, D_00486748, 0, 0, *(float*)(font2 + 0x38), *(float*)(font2 + 0x3C));
    if (w < w2) w = w2;
    sMenuRect_2D0D48 r;
    float zero = 0.0f;
    r.y = zero;
    r.x = zero;
    if (focused) {
        float h = lh + lh + 6.0f;
        float p = (float)pad;
        if (h < p) {
            h = p + 24.0f;
        } else {
            h = h + 24.0f;
        }
        r.w = h;
    } else {
        char* font3 = font_2D0D48(item);
        r.w = (float)*(int*)(font3 + 0x14) * *(float*)(font3 + 0x34) + 12.0f;
    }
    r.z = (float)margin + w + 64.0f;
    *ret = r;
    return ret;
}

INCLUDE_ASM("util/menu", func_002D0EF8);

//100%
extern void* D_004867B0[];

extern "C" cMenuList* func_002D1740(cMenuList* self)
{
    func_002CAA58(self);
    *(void***)((char*)self + 0x12C) = D_004867B0;
    cNullMenuItem_cNullMenuItem((cNullMenuItem*)((char*)self + 0x130), 0);
    cSpaceMenuItem_cSpaceMenuItem((cSpaceMenuItem*)((char*)self + 0x14C), (void*)10);
    func_002CCDF0((s2CCDF0Item*)((char*)self + 0x164), 0);
    cMenu_addItem(self, (void**)((char*)self + 0x130), -1);
    cMenu_addItem(self, (void**)((char*)self + 0x14C), -1);
    cMenu_addItem(self, (void**)((char*)self + 0x164), -1);
    return self;
}

//100%
extern "C" cMenuList* func_002D17F0(cMenuList* self, void* text, void* text2)
{
    func_002CAA58(self);
    *(void***)((char*)self + 0x12C) = D_004867B0;
    cNullMenuItem_cNullMenuItem((cNullMenuItem*)((char*)self + 0x130), text);
    cSpaceMenuItem_cSpaceMenuItem((cSpaceMenuItem*)((char*)self + 0x14C), (void*)0x1E);
    func_002CCDF0((s2CCDF0Item*)((char*)self + 0x164), text2);
    cMenu_addItem(self, (void**)((char*)self + 0x130), -1);
    cMenu_addItem(self, (void**)((char*)self + 0x14C), -1);
    cMenu_addItem(self, (void**)((char*)self + 0x164), -1);
    return self;
}

//100%
extern float D_00445AB0[];

extern "C" float func_002D18B0(float t)
{
    t = t * 160.0f;
    int i = (int)t;
    t = t - (float)i;
    i = i % 160;
    return D_00445AB0[i] * (1.0f - t) + D_00445AB0[i + 1] * t;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" float func_002D18B0(float t);

extern "C" float func_002D1928(int n, float x)
{
    float sum = 0.0f;
    float amp = 1.0f;
    float v = 0.0f;
    float freq = 1.0f;
    int i;
    for (i = 0; i < n; i++) {
        float t = x * freq;
        freq = freq * 2.0f;
        v = func_002D18B0(t) * amp;
        amp = amp * 0.5f;
        sum = sum + v;
    }
    return sum + v;
}

//100%
extern "C" int func_0030A060(void* self, int a, int b, int c);
extern void* D_004A3DD8;

extern "C" int func_002D19B8(int a, int b, int c)
{
    return func_0030A060(D_004A3DD8, a, b, c);
}

//100%
extern "C" int func_0030A598(void* self, int id);
extern "C" void func_0030A5C0(void* self, int id);
extern void* D_004A3DD8;

extern "C" int func_002D19E8(int id)
{
    if (func_0030A598(D_004A3DD8, id) != 0) {
        func_0030A5C0(D_004A3DD8, id);
        return 1;
    }
    return 0;
}

//100%
extern "C" int func_0030A2E8(void* self, int id);
extern "C" void func_0030A548(void* self, int id);
extern void* D_004A3DD8;

extern "C" int func_002D1A30(int id)
{
    if (func_0030A2E8(D_004A3DD8, id) != 0) {
        func_0030A548(D_004A3DD8, id);
        return 1;
    }
    return 0;
}

//100%
extern "C" int func_0030A610(void* mgr, int a);
extern void* D_004A3DD8;

extern "C" int func_002D1A78(int a)
{
    return func_0030A610(D_004A3DD8, a);
}

//100%
extern "C" int func_00309D20(void* mgr, int a, int b);
extern void* D_004A3DD8;

extern "C" int func_002D1AA0(int a, int b)
{
    return func_00309D20(D_004A3DD8, a, b);
}

//100%
extern "C" int func_0030A688(void* self, int id);
extern void* D_004A3DD8;

extern "C" int func_002D1AC8(int id)
{
    return func_0030A688(D_004A3DD8, id);
}

//100%
extern char* D_004A28A8;

extern "C" void* func_002D1AF0()
{
    return *(void**)(*(char**)(*(char**)(D_004A28A8 + 0x84) + 0xC) + 0x78);
}

//100%
extern char* D_004A28A8;

extern "C" void* func_002D1B08(int i)
{
    char* base = *(char**)(*(char**)(D_004A28A8 + 0x84) + 0xC);
    char* p = *(char**)(base + (i << 2) + 0x28);
    return p ? p + 0x6C0 : 0;
}

//100%
class cObj2D1B30 {
public:
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual int v07();
};

extern "C" int func_002D1B30(cObj2D1B30* self)
{
    return self->v07();
}

//100%
class func_002D1B58_cObj {
public:
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual int v05();
};

extern char* D_004A28A8;

extern "C" void func_002D1B58(int i)
{
    char* base = *(char**)(*(char**)(D_004A28A8 + 0x84) + 0xC);
    char* p = *(char**)(base + (i << 2) + 0x28);
    ((func_002D1B58_cObj*)(p + 0x6C0))->v05();
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int func_00144C98(void* iface);

extern "C" int func_002D1BA0()
{
    return func_00144C98(cBE_getInterface_Fv(cBE_getBE(), 0)) + 1;
}

//100%
extern void* D_004A47B8;

extern "C" void* func_002D1BD8()
{
    return D_004A47B8;
}

//100%
extern char* D_004A28A8;

extern "C" void* func_002D1BE0()
{
    return *(void**)(*(char**)(D_004A28A8 + 0x84) + 0x20);
}

//100%
extern "C" int func_001032C0(void* self, int a);
extern char* D_004A28A8;

extern "C" int func_002D1BF0(int a)
{
    return func_001032C0(*(void**)(*(char**)(*(char**)(D_004A28A8 + 0x84) + 0xC) + 0xA4), a);
}

//100%
extern char* D_004A28A8;

extern "C" void* func_002D1C20(int i)
{
    char* riders = *(char**)(*(char**)(D_004A28A8 + 0x84) + 0x84);
    return *(char**)(riders + (i << 2) + 4) + 0x20;
}

//100%
extern char* D_004A28A8;

extern "C" int func_002D1C40()
{
    return *(int*)(*(char**)(*(char**)(D_004A28A8 + 0x84) + 0x84) + 0x10);
}

//100%
extern char* D_004A28A8;

extern "C" void* func_002D1C58()
{
    return *(void**)(*(char**)(*(char**)(D_004A28A8 + 0x84) + 0x84) + 0x14);
}

//100%
extern char* D_004A28A8;

extern "C" float func_002D1C70()
{
    return *(float*)(D_004A28A8 + 0x14);
}

//100%
extern char* D_004A28A8;

extern "C" float func_002D1C80()
{
    return (float)*(int*)(D_004A28A8 + 0x10);
}

//100%
extern char* D_004A28A8;

extern "C" void* func_002D1C98()
{
    return *(void**)(*(char**)(*(char**)(D_004A28A8 + 0x84) + 0xC) + 0x8);
}

//100%
extern char* D_004A28A8;

extern "C" void* func_002D1CB0()
{
    return *(void**)(*(char**)(D_004A28A8 + 0x84) + 0x70);
}

extern "C" void* func_002FC2C0(void* self);

//100%
void* func_002D1CC0(void* self)
{
    return func_002FC2C0(self);
}

