#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_00492EE0[];
extern void* D_00493650[16];

struct cPSPLightMan;
cPSPLightMan* cPSPLightMan_cPSPLightMan(cPSPLightMan* self);

//100%
void* cLightMan_construct()
{
    void* mem = cMemMan_alloc(0x14, D_00492EE0, 0, 0);
    cPSPLightMan_cPSPLightMan((cPSPLightMan*)mem);
    *(void**)mem = D_00493650;
    return mem;
}

extern "C" void func_0038DC20()
{
}

extern "C" void func_0038DC28(unsigned int* self)
{
    self[0] = 0xFFFFFFFF;
    self[1] = 0xFFFFFFFF;
    self[2] = 0xFFFFFFFF;
    self[3] = 0xFFFFFFFF;
}

extern "C" void func_0038DC48()
{
}

//100%
void func_0038DC50(void* self)
{
}

//100%
void func_0038DC58(void* self)
{
}

//100%
void func_0038DC60(void* self)
{
}

//100%
void func_0038DC68(void* self)
{
}

//100%
struct sV3_DC70 {
    float x, y, z;
    sV3_DC70() {}
    sV3_DC70(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    sV3_DC70(const sV3_DC70& o) : x(o.x), y(o.y), z(o.z) {}
};

struct sCol_DC70 {
    float a, r, g, b;
};

struct sLight_DC70 {
    char pad_0x0[0x10];
    int type;               // 0x10
    float intensity;        // 0x14
    char pad_0x18[0x8];
    float r, g, b;          // 0x20
    sV3_DC70 dir;           // 0x2C
    char pos[0x24];         // 0x38
    float cone;             // 0x5C
    char pad_0x60[0x4];
    signed char c64;        // 0x64
    signed char c65;        // 0x65
    char pad_0x66[0xA];
};

class cLightSrc_DC70 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void* v01(int a);
    virtual void* v02(int a);
};

extern "C" float func_0031C128(float x);
// PORT: the unit's empty stubs take (void*); these callers pass more, bound by asm label.
void func_0038DC50_DC70(void* p, sCol_DC70* c, float f) __asm__("func_0038DC50__FPv");
void func_0038DC58_DC70(void* p, sCol_DC70* c, sV3_DC70* d, float f) __asm__("func_0038DC58__FPv");
void func_0038DC60_DC70(void* p, sCol_DC70* c, void* pos, float f, int e) __asm__("func_0038DC60__FPv");
void func_0038DC68_DC70(void* p, sCol_DC70* c, void* pos, sV3_DC70* d, float x, float y, int e, float z) __asm__("func_0038DC68__FPv");

static inline sV3_DC70 Normalize_DC70(float x, float y, float z)
{
    float d2 = x * x + y * y + z * z;
    float d;
    // PORT: sqrt.s (sqrtf without errno check)
    __asm__("sqrt.s %0, %1" : "=f"(d) : "f"(d2));
    if (d != 0.0f) {
        float k = 1.0f / d;
        return sV3_DC70(x * k, y * k, z * k);
    }
    return sV3_DC70(x, y, z);
}

extern "C" void func_0038DC70(cLightSrc_DC70* self, sLight_DC70* lights, int n, int base)
{
    int i;
    for (i = 0; i < n; i++) {
        void** obj = (void**)self->v02(base + i);
        obj[0] = &lights[i];
        sCol_DC70 col;
        col.a = 1.0f;
        col.r = lights[i].r;
        col.g = lights[i].g;
        col.b = lights[i].b;
        switch (lights[i].type) {
        case 0: {
            sV3_DC70 dir = Normalize_DC70(lights[i].dir.x, lights[i].dir.y, lights[i].dir.z);
            func_0038DC58_DC70(obj, &col, &dir, lights[i].intensity);
            break;
        }
        case 2:
            func_0038DC60_DC70(obj, &col, lights[i].pos, lights[i].intensity, lights[i].c64);
            break;
        case 1: {
            char* pos = lights[i].pos;
            sV3_DC70 dir = Normalize_DC70(lights[i].dir.x, lights[i].dir.y, lights[i].dir.z);
            func_0038DC68_DC70(obj, &col, pos, &dir, 1.5707963705062866f - func_0031C128(lights[i].cone), lights[i].intensity, lights[i].c64, (float)lights[i].c65);
            break;
        }
        case 3:
            func_0038DC50_DC70(obj, &col, lights[i].intensity);
            break;
        }
    }
}

//100%
class cObj0038DEE8 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void* v01(int a);
    virtual void* v02(int a);
};

// PORT: the unit defines func_0038DC50(void*) (an empty stub), but this caller
// passes (void*, int, float); bind the 3-arg call by asm label.
void func_0038DC50_3(void* p, int b, float f) __asm__("func_0038DC50__FPv");

extern "C" void func_0038DEE8(cObj0038DEE8* obj, int a, int b, float f)
{
    func_0038DC50_3(obj->v02(a), b, f);
}

//100%
class cObj0038DF38 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void* v01(int a);
    virtual void* v02(int a);
};

// PORT: the unit defines func_0038DC58(void*) (an empty stub), but this caller
// passes (void*, int, int, float); bind the 4-arg call by asm label.
void func_0038DC58_4(void* p, int b, int c, float f) __asm__("func_0038DC58__FPv");

extern "C" void func_0038DF38(cObj0038DF38* obj, int a, int b, int c, float f)
{
    func_0038DC58_4(obj->v02(a), b, c, f);
}

//100%
class cObj0038DF98 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void* v01(int a);
    virtual void* v02(int a);
};

// PORT: the unit defines func_0038DC60(void*) (an empty stub), but this caller
// passes (void*, int, int, float, int); bind the 5-arg call by asm label.
void func_0038DC60_5(void* p, int b, int c, float f, int d) __asm__("func_0038DC60__FPv");

extern "C" void func_0038DF98(cObj0038DF98* obj, int a, int b, int c, float f, int d)
{
    func_0038DC60_5(obj->v02(a), b, c, f, d);
}

//100%
class cObj0038E008 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void* v01(int a);
    virtual void* v02(int a);
};

// PORT: the unit defines func_0038DC68(void*) (an empty stub), but this caller
// passes (void*, int, int, int, float, float, int, float); bind the call by asm label.
void func_0038DC68_8(void* p, int b, int c, int d, float x, float y, int e, float z) __asm__("func_0038DC68__FPv");

extern "C" void func_0038E008(cObj0038E008* obj, int a, int b, int c, int d, float x, float y, int e, float z)
{
    func_0038DC68_8(obj->v02(a), b, c, d, x, y, e, z);
}

//100%
struct sLmVec4_E0A8 {
    float x, y, z, w;
    sLmVec4_E0A8(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

// 2D affine transform of v by the 3x3 matrix m (rows of 3), as a homogeneous point.
sLmVec4_E0A8 func_0038E0A8(const float* v, const float* m)
{
    sLmVec4_E0A8 r(m[0] * v[0] + m[3] * v[1] + m[6], m[1] * v[0] + m[4] * v[1] + m[7], 0.0f, 1.0f);
    return r;
}

//100%
struct sLmRectVec4 {
    float x, y, z, w;
    sLmRectVec4() {}
    sLmRectVec4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

struct sLmRectVtx {
    float s;                // 0x0
    float t;                // 0x4
    char pad_0x8[0x18];
    sLmRectVec4 pos;        // 0x20
};

struct sLmRectVEntry {
    short delta;
    short index;
    void (*fn)(void*, int, sLmRectVtx*, int);
};

struct sLmRectCtx {
    char pad_0x0[0x10D8];
    sLmRectVEntry* vtable;      // 0x10D8
};

extern sLmRectCtx* D_004A5B80_E118 __asm__("D_004A5B80");
sLmRectVec4 func_0038E0A8_r(const sLmRectVec4* v, const float* m) __asm__("func_0038E0A8__FPCfT0");

// Fills a 4-vertex strip with the corners of rect (x, y, w, h) and draws it.
extern "C" void func_0038E118(void* self, sLmRectVtx* v, float* r)
{
    v[0].pos = sLmRectVec4(r[0], r[1], 0.0f, 1.0f);
    v[1].pos = sLmRectVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    v[2].pos = sLmRectVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    v[3].pos = sLmRectVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    sLmRectCtx* ctx = D_004A5B80_E118;
    sLmRectVEntry* e = &ctx->vtable[0x47];
    e->fn((char*)ctx + e->delta, 4, v, 0);
}

//100%
// Same as func_0038E118 with the corners in rotated strip order.
extern "C" void func_0038E200(void* self, sLmRectVtx* v, float* r)
{
    v[1].pos = sLmRectVec4(r[0], r[1], 0.0f, 1.0f);
    v[3].pos = sLmRectVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    v[0].pos = sLmRectVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    v[2].pos = sLmRectVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    sLmRectCtx* ctx = D_004A5B80_E118;
    sLmRectVEntry* e = &ctx->vtable[0x47];
    e->fn((char*)ctx + e->delta, 4, v, 0);
}

//100%
// func_0038E118 with each corner transformed by the 3x3 matrix m.
extern "C" void func_0038E2E8(void* self, sLmRectVtx* v, float* r, float* m)
{
    sLmRectVec4* p0 = &v[0].pos;
    sLmRectVec4* p1 = &v[1].pos;
    sLmRectVec4* p2 = &v[2].pos;
    sLmRectVec4* p3 = &v[3].pos;
    *p0 = sLmRectVec4(r[0], r[1], 0.0f, 1.0f);
    *p1 = sLmRectVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    *p2 = sLmRectVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    *p3 = sLmRectVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    *p0 = func_0038E0A8_r(p0, m);
    *p1 = func_0038E0A8_r(p1, m);
    *p2 = func_0038E0A8_r(p2, m);
    *p3 = func_0038E0A8_r(p3, m);
    sLmRectCtx* ctx = D_004A5B80_E118;
    sLmRectVEntry* e = &ctx->vtable[0x47];
    e->fn((char*)ctx + e->delta, 4, v, 0);
}

//100%
// func_0038E2E8 with the corners in rotated strip order.
extern "C" void func_0038E468(void* self, sLmRectVtx* v, float* r, float* m)
{
    sLmRectVec4* p0 = &v[0].pos;
    sLmRectVec4* p1 = &v[1].pos;
    sLmRectVec4* p2 = &v[2].pos;
    sLmRectVec4* p3 = &v[3].pos;
    *p1 = sLmRectVec4(r[0], r[1], 0.0f, 1.0f);
    *p3 = sLmRectVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    *p0 = sLmRectVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    *p2 = sLmRectVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    *p0 = func_0038E0A8_r(p0, m);
    *p1 = func_0038E0A8_r(p1, m);
    *p2 = func_0038E0A8_r(p2, m);
    *p3 = func_0038E0A8_r(p3, m);
    sLmRectCtx* ctx = D_004A5B80_E118;
    sLmRectVEntry* e = &ctx->vtable[0x47];
    e->fn((char*)ctx + e->delta, 4, v, 0);
}

//100%
// func_0038E118 with texture coordinates from the rect uv (u, v, w, h).
extern "C" void func_0038E5E8(void* self, sLmRectVtx* v, float* r, float* uv)
{
    v[0].pos = sLmRectVec4(r[0], r[1], 0.0f, 1.0f);
    v[0].s = uv[0];
    v[0].t = uv[1];
    v[1].pos = sLmRectVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    v[1].s = uv[0] + uv[2];
    v[1].t = uv[1];
    v[2].pos = sLmRectVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    v[2].s = uv[0];
    v[2].t = uv[1] + uv[3];
    v[3].pos = sLmRectVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    v[3].s = uv[0] + uv[2];
    v[3].t = uv[1] + uv[3];
    sLmRectCtx* ctx = D_004A5B80_E118;
    sLmRectVEntry* e = &ctx->vtable[0x47];
    e->fn((char*)ctx + e->delta, 4, v, 0);
}

//100%
// func_0038E5E8 with the texture rotated a quarter turn.
extern "C" void func_0038E738(void* self, sLmRectVtx* v, float* r, float* uv)
{
    v[0].pos = sLmRectVec4(r[0], r[1], 0.0f, 1.0f);
    v[0].s = uv[0] + uv[2];
    v[0].t = uv[1];
    v[1].pos = sLmRectVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    v[1].s = uv[0] + uv[2];
    v[1].t = uv[1] + uv[3];
    v[2].pos = sLmRectVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    v[2].s = uv[0];
    v[2].t = uv[1];
    v[3].pos = sLmRectVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    v[3].s = uv[0];
    v[3].t = uv[1] + uv[3];
    sLmRectCtx* ctx = D_004A5B80_E118;
    sLmRectVEntry* e = &ctx->vtable[0x47];
    e->fn((char*)ctx + e->delta, 4, v, 0);
}

//100%
// func_0038E5E8 with each corner transformed by the 3x3 matrix m.
extern "C" void func_0038E880(void* self, sLmRectVtx* v, float* r, float* uv, float* m)
{
    sLmRectVec4* p0 = &v[0].pos;
    sLmRectVec4* p1 = &v[1].pos;
    sLmRectVec4* p2 = &v[2].pos;
    sLmRectVec4* p3 = &v[3].pos;
    *p0 = sLmRectVec4(r[0], r[1], 0.0f, 1.0f);
    v[0].s = uv[0];
    v[0].t = uv[1];
    *p1 = sLmRectVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    v[1].s = uv[0] + uv[2];
    v[1].t = uv[1];
    *p2 = sLmRectVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    v[2].s = uv[0];
    v[2].t = uv[1] + uv[3];
    *p3 = sLmRectVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    v[3].s = uv[0] + uv[2];
    v[3].t = uv[1] + uv[3];
    *p0 = func_0038E0A8_r(p0, m);
    *p1 = func_0038E0A8_r(p1, m);
    *p2 = func_0038E0A8_r(p2, m);
    *p3 = func_0038E0A8_r(p3, m);
    sLmRectCtx* ctx = D_004A5B80_E118;
    sLmRectVEntry* e = &ctx->vtable[0x47];
    e->fn((char*)ctx + e->delta, 4, v, 0);
}

//100%
// func_0038E738 with each corner transformed by the 3x3 matrix m.
extern "C" void func_0038EA60(void* self, sLmRectVtx* v, float* r, float* uv, float* m)
{
    sLmRectVec4* p0 = &v[0].pos;
    sLmRectVec4* p1 = &v[1].pos;
    sLmRectVec4* p2 = &v[2].pos;
    sLmRectVec4* p3 = &v[3].pos;
    *p0 = sLmRectVec4(r[0], r[1], 0.0f, 1.0f);
    v[0].s = uv[0] + uv[2];
    v[0].t = uv[1];
    *p1 = sLmRectVec4(r[0] + r[2], r[1], 0.0f, 1.0f);
    v[1].s = uv[0] + uv[2];
    v[1].t = uv[1] + uv[3];
    *p2 = sLmRectVec4(r[0], r[1] + r[3], 0.0f, 1.0f);
    v[2].s = uv[0];
    v[2].t = uv[1];
    *p3 = sLmRectVec4(r[0] + r[2], r[1] + r[3], 0.0f, 1.0f);
    v[3].s = uv[0];
    v[3].t = uv[1] + uv[3];
    *p0 = func_0038E0A8_r(p0, m);
    *p1 = func_0038E0A8_r(p1, m);
    *p2 = func_0038E0A8_r(p2, m);
    *p3 = func_0038E0A8_r(p3, m);
    sLmRectCtx* ctx = D_004A5B80_E118;
    sLmRectVEntry* e = &ctx->vtable[0x47];
    e->fn((char*)ctx + e->delta, 4, v, 0);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sLmQuadVec4 {
    float x, y, z, w;
    sLmQuadVec4() {}
    sLmQuadVec4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

struct sLmQuadVtx {
    float s;                // 0x0
    float t;                // 0x4
    float q;                // 0x8
    int pad_0xC;
    int c[4];               // 0x10
    sLmQuadVec4 pos;        // 0x20
};

struct sLmQuadVEntry {
    short delta;
    short index;
    void (*fn)(void*, int, sLmQuadVtx*, int);
};

struct sLmQuadCtx {
    char pad_0x0[0x10D8];
    sLmQuadVEntry* vtable;      // 0x10D8
};

extern sLmQuadCtx* D_004A5B80_EC40 __asm__("D_004A5B80");

INCLUDE_ASM("render/lightman", func_0038EC40);
extern "C" void func_0038EC40(void* self, float* p0, float* p1, float* col, float z);

INCLUDE_ASM("render/lightman", func_0038ED90);

INCLUDE_ASM("render/lightman", func_0038EE78);

//100%
extern float D_004A4458;

struct sLmCell_F2A8 {
    char data[0x40];
};
extern sLmCell_F2A8 D_00504D80[];

extern "C" sLmCell_F2A8* func_0038F2A8(float* pos)
{
    float d2 = pos[0] * pos[0] + pos[1] * pos[1];
    float d;
    // PORT: sqrt.s (sqrtf without errno check)
    __asm__("sqrt.s %0, %1" : "=f"(d) : "f"(d2));
    int i = (int)(D_004A4458 * d);
    return &D_00504D80[i % 8];
}

//100%
extern "C" void func_0038F768(void);
extern "C" void func_0038F7B0(void);
extern int D_004A5B84;

struct sLightBufs_F300 {
    int mode;
    int count;
    int f8;
    int fC;
    int size;
    int addr[3];
    int b20[3];
    int b2C[3];
};

extern "C" void func_0038F300(sLightBufs_F300* self, int mode)
{
    int i;
    if (self->mode == mode)
        return;
    self->mode = mode;
    switch (mode) {
    case 1:
        self->count = 1;
        break;
    case 2:
        self->count = 2;
        break;
    case 3:
        self->count = 2;
        break;
    case 4:
        self->count = 2;
        break;
    case 5:
        self->count = 2;
        break;
    case 6:
    case 7:
        self->count = 3;
        break;
    }
    self->f8 = 0;
    self->fC = 0;
    switch (mode) {
    case 1:
        self->size = 0x400;
        break;
    case 2:
        self->size = 0x200;
        break;
    case 3:
        self->size = 0x1C0;
        break;
    case 4:
        self->size = 0x180;
        break;
    case 6:
        self->size = 0x140;
        break;
    case 5:
    case 7:
        self->size = 0x100;
        break;
    }
    for (i = 0; i < self->count; i++) {
        self->addr[i] = self->size * i * 16 + 0x70000000;
        self->b20[i] = 0;
        self->b2C[i] = 0;
    }
    if (self->size * self->count < 0x400)
        D_004A5B84 = self->size * self->count * 16 + 0x70000000;
    else
        D_004A5B84 = 0;
    func_0038F768();
    func_0038F7B0();
}

//100%
struct sLightRing {
    int field_0x0;
    int count;        // 0x4
    int next;         // 0x8
    int field_0xC;
    int defSize;      // 0x10
    int result[3];    // 0x14
    unsigned int addr[3]; // 0x20
    int size[3];      // 0x2C
};

extern "C" void func_0038F768(void);

extern "C" int func_0038F460(void* self, unsigned int addr, int size, int flags)
{
    sLightRing* r = (sLightRing*)self;
    if (flags & 4) {
        func_0038F768();
    }
    if (size < 0) {
        size = r->defSize;
    } else {
        size >>= 4;
    }
    int i = r->next++;
    r->next %= r->count;
    r->addr[i] = addr;
    r->size[i] = size;
    return r->result[i];
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int func_0038F460(void* self, unsigned int addr, int size, int flags);
extern "C" void func_00371D10(unsigned int madr, int sadr, int qwc, int flags);

extern "C" int func_0038F4F8(void* self, unsigned int addr, int size, int flags)
{
    int r = func_0038F460(self, addr, size, 0);
    func_00371D10(addr, r, size >> 4, flags);
    return r;
}

struct sLightDma_F598 {
    int field_0x0;
    int count;              // 0x4
    int next;               // 0x8
    int cur;                // 0xC
    int defSize;            // 0x10
    int result[3];          // 0x14
    unsigned int addr[3];   // 0x20
    int sizes[3];           // 0x2C
};
unsigned int func_0038F598_impl(sLightDma_F598* self, int size, int flags) __asm__("func_0038F598");

extern "C" void func_0038F560(sLightDma_F598* self, int flags)
{
    func_0038F598_impl(self, self->sizes[self->cur] << 4, flags);
}

//100%
extern "C" void func_0038F768(void);
extern "C" void func_0038F6A8(void* self);
extern "C" void func_00371DD8(int sadr, unsigned int madr, int qwc, int flags);

// PORT: the unit declares func_0038F598 as `void (sLmStack*, int, int, int)`; the body takes
// (self, size, flags) and returns the buffer address, so it is bound by asm label.
unsigned int func_0038F598_impl(sLightDma_F598* self, int size, int flags) __asm__("func_0038F598");

unsigned int func_0038F598_impl(sLightDma_F598* self, int size, int flags)
{
    if (size == 0) {
        if (flags & 6) {
            func_0038F768();
        }
        unsigned int r = self->addr[self->cur];
        func_0038F6A8(self);
        return r;
    }
    size >>= 4;
    // PORT: EE sync (memory barrier before kicking the DMA)
    __asm__ __volatile__("sync");
    unsigned int* addrs = self->addr;
    func_00371DD8(self->result[self->cur], *(unsigned int*)((char*)addrs + (self->cur << 2)), size, flags);
    int cur = self->cur;
    unsigned int r = *(unsigned int*)((char*)addrs + (cur << 2)) + (size << 4);
    self->cur = (cur + 1) % self->count;
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sLmStack {
    char pad_0x00[0xC];
    int depth;          // 0x0C
    char pad_0x10[4];
    int marks[1];       // 0x14
};

extern "C" void func_0038F598(sLmStack* self, int size, int arg, int base);

extern "C" void func_0038F668(sLmStack* self, int end, int arg)
{
    int base = self->marks[self->depth];
    int size = end - base;
    func_0038F598(self, size + (-size & 0xF), arg, base);
}

//100%
extern "C" void func_0038F6A8(void* self)
{
    *(int*)((char*)self + 0xC) = (*(int*)((char*)self + 0xC) + 1) % *(int*)((char*)self + 0x4);
}

extern "C" char* func_0038F6D0(sLightDma_F598* self, int off)
{
    int d = off - self->result[self->cur];
    d += -d & 0xF;
    return (char*)self->addr[self->cur] + ((d >> 4) << 4);
}

//100%
extern int D_004A5B84;
extern "C" void func_00371D10(unsigned int madr, int sadr, int qwc, int flags);

extern "C" int func_0038F708(unsigned int madr, int size, int flags)
{
    func_00371D10(madr, D_004A5B84, size >> 4, flags);
    return D_004A5B84;
}

//100%
extern int D_004A5B84;
extern "C" void func_00371DD8(int sadr, unsigned int madr, int qwc, int flags);

extern "C" void func_0038F738(unsigned int madr, int size, int flags)
{
    func_00371DD8(D_004A5B84, madr, size >> 4, flags);
}

//100%
// PORT: polls PS2 hardware register 0x1000D000 directly; needs a platform shim.
extern "C" void func_0038F768(void)
{
    while (*(volatile int*)0x1000D000 & 0x100) {
    }
}

//100%
// PORT: polls PS2 hardware register 0x1000D400 directly; needs a platform shim.
extern "C" void func_0038F7B0(void)
{
    while (*(volatile int*)0x1000D400 & 0x100) {
    }
}

//100%
void func_0038F7F8(void* self)
{
}

extern "C" void* func_002BB6B8(void* self);

//100%
void* func_0038F800(void* self)
{
    return func_002BB6B8(self);
}

INCLUDE_ASM("render/lightman", func_0038F820);

//100%
extern int D_0044BDE0[];

extern "C" int func_0038F930(void* self, unsigned char* src, unsigned char* dst)
{
    unsigned int n = 0;
    unsigned int i;
    for (i = 0; i < 4; i++) {
        unsigned int k = (i & 1) * 64;
        unsigned int j;
        for (j = 0; j < 16; j++) {
            unsigned int m;
            for (m = 0; m < 4; m++) {
                dst[n] = src[D_0044BDE0[k]];
                k++;
                n++;
            }
        }
        src += 0x40;
    }
    return 0;
}

//100%
extern int D_0044C060[];
extern int D_0044BFE0[];
extern "C" int func_0038F820(void* self, unsigned char* src, unsigned char* dst);
extern "C" void* func_00416210(void* dst, int c, int n);

struct sRow16_F9C0 {
    unsigned char b[16];
};

struct sRow32_F9C0 {
    unsigned char b[32];
};

extern "C" int func_0038F9C0(void* self, int w, int h, unsigned char* src, unsigned char* dst)
{
    int xmap[32];
    int ymap[32];
    unsigned char block[0x100];
    unsigned char out[0x100];
    int n = 0;
    int i;
    int j;
    int k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            int t = D_0044C060[n++];
            xmap[t] = j;
            ymap[t] = i;
        }
    }
    int bw = w / 32;
    int bh = h / 16;
    int spitch = 0x40;
    int dpitch = 0x100;
    func_00416210(block, 0, 0x100);
    func_00416210(out, 0, 0x100);
    for (i = 0; i < bh; i++) {
        for (j = 0; j < bw; j++) {
            int id = D_0044BFE0[i * bw + j];
            sRow16_F9C0* s = (sRow16_F9C0*)(src + (i * 16) * spitch + j * 16);
            sRow16_F9C0* d = (sRow16_F9C0*)block;
            for (k = 0; k < 16; k++) {
                *d = *s;
                d++;
                s += 4;
            }
            func_0038F820(self, block, out);
            sRow32_F9C0* s2 = (sRow32_F9C0*)out;
            sRow32_F9C0* d2 = (sRow32_F9C0*)(dst + (ymap[id] * 8) * dpitch + xmap[id] * 32);
            for (k = 0; k < 8; k++) {
                *d2 = *s2;
                s2++;
                d2 += 8;
            }
        }
    }
    return 0;
}

//100%
struct sRow16_FC48 {
    unsigned char b[16];
};

struct sRow32_FC48 {
    unsigned char b[32];
};

extern int D_0044C160[];
extern int D_0044C0E0[];
extern "C" void* func_00416210(void* dst, int c, int n);

extern "C" int func_0038FC48(void* self, int w, int h, unsigned char* src, unsigned char* dst)
{
    int xmap[32];
    int ymap[32];
    unsigned char block[0x100];
    unsigned char out[0x100];
    int n = 0;
    int i;
    int j;
    int k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            int t = D_0044C160[n++];
            xmap[t] = j;
            ymap[t] = i;
        }
    }
    int bw = w / 16;
    int bh = h / 16;
    int spitch = 0x80;
    int dpitch = 0x100;
    func_00416210(block, 0, 0x100);
    func_00416210(out, 0, 0x100);
    for (i = 0; i < bh; i++) {
        for (j = 0; j < bw; j++) {
            int id = D_0044C0E0[i * bw + j];
            sRow16_FC48* s = (sRow16_FC48*)(src + (i * 16) * spitch + j * 16);
            sRow16_FC48* d = (sRow16_FC48*)block;
            for (k = 0; k < 16; k++) {
                *d = *s;
                d++;
                s += 8;
            }
            func_0038F930(self, block, out);
            sRow32_FC48* s2 = (sRow32_FC48*)out;
            sRow32_FC48* d2 = (sRow32_FC48*)(dst + (ymap[id] * 8) * dpitch + xmap[id] * 32);
            for (k = 0; k < 8; k++) {
                *d2 = *s2;
                s2++;
                d2 += 8;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("render/lightman", func_0038FED0);

extern "C" void* func_0041605C(void* dst, const void* src, int n);

//100%
// Copies a power-of-two texture through 128x64 tiles, converting each one; -1 on a bad size.
extern "C" int func_00390198(void* self, int w, int h, unsigned char* in, unsigned char* out)
{
    unsigned char buf0[0x2000];
    unsigned char buf1[0x2000];
    int i;
    int x;
    for (i = 0; i < 11; i++) {
        if (w == (0x400 >> i)) break;
    }
    if (i == 11) return -1;
    for (i = 0; i < 11; i++) {
        if (h == (0x400 >> i)) break;
    }
    if (i == 11) return -1;
    func_00416210(buf0, 0, 0x2000);
    func_00416210(buf1, 0, 0x2000);
    int nx = (w - 1) / 128 + 1;
    int ny = (h - 1) / 64 + 1;
    int cw, cw2, rows, rows2;
    if (nx == 1) {
        cw = w;
        cw2 = cw * 2;
    } else {
        cw = 0x80;
        cw2 = 0x100;
    }
    if (ny == 1) {
        rows = h;
        rows2 = h / 2;
    } else {
        rows = 0x40;
        rows2 = 0x20;
    }
    for (i = 0; i < ny; i++) {
        for (x = 0; x < nx; x++) {
            unsigned char* s = in + cw * (nx << 6) * i + cw * x;
            unsigned char* d = buf0;
            for (int k = 0; k < rows; k++) {
                func_0041605C(d, s, cw);
                s += cw * nx;
                d += 0x80;
            }
            func_0038FC48(self, 0x80, 0x40, buf0, buf1);
            unsigned char* s2 = buf1;
            unsigned char* d2 = out + cw2 * rows2 * nx * i + cw2 * x;
            for (int k = 0; k < rows2; k++) {
                func_0041605C(d2, s2, cw2);
                d2 += cw2 * nx;
                s2 += 0x100;
            }
        }
    }
    return 0;
}

//100%
extern float D_004A45E4;
extern float D_004A45E8;
extern float D_004A45EC;
extern float D_004A45F0;
extern float D_004A45F4;
extern float D_004A45F8;

struct sLmEntry_0458 {
    float v[6];
};

struct sLmOwner_0458 {
    char pad[0x6CA4];
    sLmEntry_0458 entries[1];
};

extern "C" void func_00390458(void* self, int idx)
{
    char* e = (char*)&((sLmOwner_0458*)self)->entries[idx];
    *(float*)(e + 0x0) = D_004A45E4;
    *(float*)(e + 0x4) = D_004A45E8;
    *(float*)(e + 0x8) = D_004A45EC;
    *(float*)(e + 0xC) = D_004A45F0;
    *(float*)(e + 0x10) = D_004A45F4;
    *(float*)(e + 0x14) = D_004A45F8;
}

//100%
extern int D_004A45D8;
extern int D_004A45DC;
extern void* D_004A4474;

extern "C" void func_003905E8(void* self, int idx, int* mark);
// PORT: func_0038F668 is declared void in this unit, but it returns its tail call's
// value and this caller uses it; bind an int-returning view to the same symbol.
extern "C" int func_0038F668_r(void* self, int end, int arg) __asm__("func_0038F668");
extern "C" void func_00368138(void* self, void* pkt);

extern "C" void func_003904A0(void* self, int idx, void* pkt, int* addr)
{
    if (D_004A45D8 == 0) {
        return;
    }
    if (D_004A45DC != 0) {
        func_00390458(self, idx);
    }
    float* e = ((sLmOwner_0458*)self)->entries[idx].v;
    if (e[0] == 1.0f && e[1] == 1.0f && e[2] == 1.0f && e[3] == 0.0f && e[4] == 0.0f && e[5] == 0.0f) {
        return;
    }
    void* ring = D_004A4474;
    int mark = func_0038F460(ring, *addr, -1, 0);
    func_003905E8(self, idx, &mark);
    *addr = func_0038F668_r(ring, mark, 4);
    func_00368138(*(void**)((char*)self + 0x18F4), pkt);
}

INCLUDE_ASM("render/lightman", func_003905E8);

//100%
extern char* D_004A5B80;
extern int D_004A44C0;
extern int D_004A44C8;

struct sLmVEntry_0C20 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

extern "C" void func_00390C20()
{
    char* mgr = D_004A5B80;
    sLmVEntry_0C20* vt = *(sLmVEntry_0C20**)(mgr + 0x10D8);
    vt[16].fn(mgr + vt[16].delta, D_004A44C0);
    if (D_004A44C8 != 0) {
        D_004A44C8 = 0;
    }
}

//100%
extern int D_004A460C;
extern int D_004A46B4;
extern int D_004A4698;
extern int D_004A469C;
extern int D_004A4610;
extern float D_004A4614;
extern int D_004A4618;
extern int D_004A461C;
extern int D_004A4620;
extern int D_004A4624;
extern float D_004A4628;
extern float D_004A462C;
extern float D_004A4630;
extern float D_004A4634;
extern float D_004A4638;
extern float D_004A463C;
extern float D_004A4640;
extern float D_004A4644;
extern float D_004A4648;
extern float D_004A464C;
extern float D_004A4650;
extern float D_004A4654;
extern float D_004A45E4;
extern float D_004A45E8;
extern float D_004A45EC;
extern float D_004A46A0;
extern float D_004A46A4;
extern float D_004A46A8;
extern int D_004A46AC;
int BXrand();
extern "C" void func_00390EC8(float t);

static inline float RandF_0C60()
{
    union {
        int i;
        float f;
    } u;
    u.i = (BXrand() & 0x7FFFFF) | 0x3F800000;
    return u.f - 1.0f;
}

static inline float RandRange_0C60(float lo, float hi)
{
    return RandF_0C60() * (hi - lo) + lo;
}

// PORT: D_004A469C holds a float (declared int elsewhere in the unit).
extern "C" void func_00390C60()
{
    if (D_004A460C == 0) {
        return;
    }
    if (D_004A46B4 > 0) {
        D_004A46B4--;
    }
    int t = D_004A4698;
    int trig = D_004A4610;
    if (t < 0) {
        if (RandF_0C60() < D_004A4614 * D_004A4614) {
            func_00390EC8(RandRange_0C60(0.019999999552965164f, 2.0f) * 100000.0f);
        }
        return;
    }
    if (trig < 0 || D_004A4618 + D_004A461C + D_004A4620 + D_004A4624 < trig) {
        D_004A4698 = t + 1;
    } else {
        D_004A4698 = trig;
    }
    int cur = D_004A4698;
    int d0 = D_004A4618;
    if (cur <= d0) {
        *(float*)&D_004A469C = ((float)cur / (float)d0) * D_004A4628;
        D_004A46A0 = D_004A4634;
        D_004A46A4 = D_004A4638;
        D_004A46A8 = D_004A463C;
        D_004A46AC = 5;
    } else if (cur <= d0 + D_004A461C) {
        *(float*)&D_004A469C = D_004A4628;
        D_004A46A0 = D_004A4634;
        D_004A46A4 = D_004A4638;
        D_004A46A8 = D_004A463C;
        D_004A46AC = 5;
    } else if (cur <= d0 + D_004A461C + D_004A4620) {
        *(float*)&D_004A469C = D_004A462C;
        D_004A46A0 = D_004A4640;
        D_004A46A4 = D_004A4644;
        D_004A46A8 = D_004A4648;
        D_004A46AC = 5;
    } else if (cur <= d0 + D_004A461C + D_004A4620 + D_004A4624) {
        *(float*)&D_004A469C = (1.0f - ((float)cur - (float)d0 - (float)D_004A461C - (float)D_004A4620) / (float)D_004A4624) * D_004A4630;
        D_004A46A0 = D_004A464C;
        D_004A46A4 = D_004A4650;
        D_004A46A8 = D_004A4654;
        D_004A46AC = 5;
    } else {
        D_004A4698 = -1;
        D_004A46A0 = D_004A45E4;
        D_004A46A4 = D_004A45E8;
        D_004A46A8 = D_004A45EC;
        D_004A46AC = 5;
        *(float*)&D_004A469C = 0.0f;
    }
}

//100%
extern int D_004A460C;
extern int D_004A4698;
extern int D_004A469C;
extern float D_004A46B0;
extern int D_004A46B4;

extern "C" void func_00390EC8(float t)
{
    if (D_004A460C != 0) {
        D_004A4698 = 0;
        D_004A469C = 0;
        D_004A46B0 = t;
        D_004A46B4 = (int)(t * 0.0018072288949042559f);
    }
}

//100%
extern int D_004A460C;
extern int D_004A46B4;

extern "C" int func_00390EF8()
{
    if (D_004A460C != 0 && D_004A46B4 == 0) {
        D_004A46B4 = -1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("render/lightman", func_00390F20);

//100%
extern char D_0043BD00[];
extern "C" void func_00424020(int);

// PORT: kicks a DMA chain on channel 0 (VIF0) through the PS2 hardware registers at
// 0x10008000 (CHCR), 0x10008020 (QWC) and 0x10008030 (TADR); needs a platform shim.
extern "C" void func_003912A8(void)
{
    while (*(volatile int*)0x10008000 & 0x100) {
    }
    *(volatile int*)0x10008030 = (int)D_0043BD00;
    *(volatile int*)0x10008020 = 0;
    *(volatile int*)0x10008000 = 0x104;
    while (*(volatile int*)0x10008000 & 0x100) {
    }
    func_00424020(0);
}

//100%
extern char D_0043CCA0[];
extern "C" void func_00424020(int);

// PORT: kicks a DMA chain on channel 0 (VIF0) through the PS2 hardware registers at
// 0x10008000 (CHCR), 0x10008020 (QWC) and 0x10008030 (TADR); needs a platform shim.
extern "C" void func_00391360(void)
{
    while (*(volatile int*)0x10008000 & 0x100) {
    }
    *(volatile int*)0x10008030 = (int)D_0043CCA0;
    *(volatile int*)0x10008020 = 0;
    *(volatile int*)0x10008000 = 0x104;
    while (*(volatile int*)0x10008000 & 0x100) {
    }
    func_00424020(0);
}

//100%
// PORT: PS2-only VU0 inline asm (lqc2 x16 into vf1-vf16, then vcallmsr of the
// microprogram at VU0 micro-memory address 0); the PC port needs a C version.
INCLUDE_ASM("render/lightman", func_00391418);
extern "C" void func_00391418(void* self, void* m);

//100%
struct sQuad16 {
    int w[4];
} __attribute__((aligned(16)));

extern "C" void func_00391480(void* self, sQuad16* dst)
{
    sQuad16* src = (sQuad16*)0x11004200;
    int i;
    for (i = 0; i < 10; i++) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
        dst[6] = src[6];
        dst[7] = src[7];
        dst[8] = src[8];
        dst[9] = src[9];
        src += 10;
        dst += 10;
    }
}

//100%
// PORT: PS2-only VU0 integer register read (vi1); the PC port needs a C fallback.
INCLUDE_ASM("render/lightman", func_003914F8);
extern "C" int func_003914F8(void);

//100%
struct sLmV2_1508 {
    float x, y;
    sLmV2_1508() {}
    sLmV2_1508(float ax, float ay) : x(ax), y(ay) {}
};

struct sLmV4_1508 {
    float x, y, z, w;
    sLmV4_1508() {}
    sLmV4_1508(float ax, float ay, float az, float aw)
    {
        x = ax;
        y = ay;
        z = az;
        w = aw;
    }
};

struct sLmState_1508 {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    char pad_0x18[0x10];
    sLmV2_1508 a;           // 0x28
    sLmV2_1508 b;           // 0x30
    sLmV2_1508 c;           // 0x38
    sLmV4_1508 d;           // 0x40
    sLmV4_1508 e;           // 0x50
    int f60;
    char f64;
};

// Resets the state to defaults and returns it.
extern "C" sLmState_1508* func_00391508(sLmState_1508* self)
{
    self->a = sLmV2_1508(0.0f, 0.0f);
    self->b = sLmV2_1508(1.0f, 1.0f);
    self->c = self->b;
    {
        sLmV4_1508 t;
        t.x = 1.0f;
        t.y = 1.0f;
        t.z = 1.0f;
        t.w = 1.0f;
        self->d = t;
    }
    self->e = sLmV4_1508(1.0f, 0.0f, 0.0f, 0.0f);
    self->f60 = -1;
    self->f0 = 0;
    self->f4 = 0;
    self->f8 = 0;
    self->f14 = 0;
    self->fC = 0;
    self->f10 = 0;
    self->f64 = 0;
    return self;
}

//100%
struct sLmVec2_15E8 {
    float x, y;

    sLmVec2_15E8() {}
    sLmVec2_15E8(float a, float b)
    {
        x = a;
        y = b;
    }
};

struct sLmVec4_15E8 {
    float x, y, z, w;

    sLmVec4_15E8() {}
    sLmVec4_15E8(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
};

struct sLmLight_15E8 {
    char pad_0x0[0x8];
    int field_0x8;          // 0x8
    char pad_0xc[0x1C];
    sLmVec2_15E8 v28;       // 0x28
    sLmVec2_15E8 v30;       // 0x30
    sLmVec2_15E8 v38;       // 0x38
    sLmVec4_15E8 v40;       // 0x40
    sLmVec4_15E8 v50;       // 0x50
    char pad_0x60[0x4];
    unsigned char b64;      // 0x64
};

extern "C" void func_00391708(void* self, const char* name, int flags);

extern "C" sLmLight_15E8* func_003915E8(sLmLight_15E8* self, const char* name, int flags)
{
    self->field_0x8 = 0;
    self->v28 = sLmVec2_15E8(0.0f, 0.0f);
    self->v30 = sLmVec2_15E8(1.0f, 1.0f);
    self->v38 = self->v30;
    {
        sLmVec4_15E8 t;
        t.x = 1.0f;
        t.y = 1.0f;
        t.z = 1.0f;
        t.w = 1.0f;
        self->v40 = t;
    }
    self->v50 = sLmVec4_15E8(1.0f, 0.0f, 0.0f, 0.0f);
    self->b64 = 0;
    func_00391708(self, name, flags);
    return self;
}

//100%
extern "C" void func_003919E8(void* self);
void operator_delete(int* ptr);

extern "C" void func_003916C0(int* self, int flags)
{
    func_003919E8(self);
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void* FILE_load(const char* name, int flags);
extern "C" void cFont_linkFont(void* self, void* data, int flags);
void cMemMan_free(void*);
extern const char D_00492F30[];

extern "C" void func_00391708(void* self, const char* name, int flags)
{
    void* data;

    sprintf((char*)self + 0x64, D_00492F30, name);
    data = FILE_load(name, flags ^ 0x100);
    cFont_linkFont(self, data, flags);
    if (data != 0) {
        cMemMan_free(data);
    }
}

