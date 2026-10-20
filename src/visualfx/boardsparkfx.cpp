#include "common.h"

//100%
// g++ 2.95 vtable entry (no thunks): {delta, index, fn}. Vtables are double-aligned.
struct sVtEntBS {
    short delta;
    short index;
    void* fn;
};

struct sVt9_BS {
    sVtEntBS e[9];
} __attribute__((aligned(8)));

struct sVt22_BS {
    sVtEntBS e[22];
} __attribute__((aligned(8)));

extern const sVt9_BS D_00488CB0;
extern const sVt22_BS D_00488CF8;
extern char D_00459B90[];
extern char D_00487588[];
extern char D_00487598[];
extern char D_004875A8[];

extern "C" void cRider_cRider(void* self);
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* mEmitter_ctor(void* self);
void* func_002F7A68(void* self);
extern "C" void func_0036CCB8(void* self);
extern "C" void func_0036CE00(void* self, float a, float b, float c);
extern "C" void func_0036CE28(void* self, float a, float b);
extern "C" void func_0036D008(void* self);
extern "C" void func_0036D3D8(void* self, float val);
extern "C" void func_00416210(void* dst, int c, int n);
extern "C" void func_002DAA78(void* self);

struct sBsVec4 {
    float x, y, z, w;
    sBsVec4() {}
};

extern "C" void func_0036CBF8(void* sys, int w, int h, float x, float y, float s, sBsVec4* v);

struct sBsIds {
    short id[2];
    sBsIds()
    {
        for (unsigned int i = 0; i < 2; i++) {
            id[i] = -1;
        }
    }
};

struct sBsSlot {
    char data[0x10];
    sBsIds ids;
    sBsSlot() { func_00416210(data, 0, 0x10); }
    void* operator new(unsigned int, void* p) { return p; }
};

struct sBsElem {
    float v[4];
    sBsElem() {}
    void* operator new[](unsigned int, void* p) { return p; }
};

struct sBsParams {
    int mode;           // 0x00
    int f04;            // 0x04
    float f08;          // 0x08
    float f0C;          // 0x0C
    float f10;          // 0x10
    float f14;          // 0x14
    float f18;          // 0x18
    float f1C[13];      // 0x1C
    float f50;          // 0x50
    float f54;          // 0x54
    float f58;          // 0x58
    float f5C;          // 0x5C
    float f60;          // 0x60
    float f64;          // 0x64
    float f68;          // 0x68
    float f6C;          // 0x6C
    float f70;          // 0x70
    float f74;          // 0x74
    float f78;          // 0x78
    float f7C;          // 0x7C
    float f80;          // 0x80
    float f84;          // 0x84
    float f88;          // 0x88
    float f8C;          // 0x8C
    float f90;          // 0x90
    float f94;          // 0x94
    float f98;          // 0x98
    float f9C;          // 0x9C
    float fA0;          // 0xA0
    float fA4[8];       // 0xA4
    int count;          // 0xC4
    int fC8;            // 0xC8
    float fCC;          // 0xCC
    int fD0;            // 0xD0
    float fD4;          // 0xD4
};

struct sBsVE {
    short delta;
    short index;
    void (*fn)(void*, sBsParams*, float);
};

struct sBsEmitter {
    char pad0[0x58];
    float rate;         // 0x58
    char pad5C[0x1F8 - 0x5C];
    sBsVE* vt;          // 0x1F8
};

struct cBoardSparkFX {
    char* vbase;            // 0x00
    char pad04[0x1C];
    sBsEmitter* emitter;    // 0x20
    sBsParams* params;      // 0x24
    void* gfx;              // 0x28
    char pad2C[0x40];
    int active;             // 0x6C
    char pad70[0xC];
    sBsSlot slotA;          // 0x7C
    sBsSlot slotB;          // 0x90
};

// PORT: hand-written form of g++ 2.95's constructor for a class with a virtual base
// (cRider at +0xB0): vtable copies with delta fixups when not in charge.
INCLUDE_ASM("visualfx/boardsparkfx", cBoardSparkFX_cBoardSparkFX);
extern "C" void* cBoardSparkFX_cBoardSparkFX(cBoardSparkFX* self, int inChrg);

INCLUDE_ASM("visualfx/boardsparkfx", func_002DA8E8);

//100%
struct sV4_AA78 { float x, y, z, w; } __attribute__((aligned(16)));
struct sRS_AA78 {
    int f0;
    int flagsA;     // 0x4
    int flagsB;     // 0x8
    int fC;
    short tex;      // 0x10
    short pad;
};
extern sV4_AA78 D_004FF130;
extern sRS_AA78 D_00501420_AA78 __asm__("D_00501420");
extern char* D_004A289C_AA78 __asm__("D_004A289C");

// Render-state field setters (mask, shift, value), as the unit's other effects write them.
#define RS_SETA_AA78(rs, mask, shift, v) ((rs).flagsA = ((rs).flagsA & ~(mask)) | (((v) << (shift)) & (mask)))
#define RS_SETB_AA78(rs, mask, shift, v) ((rs).flagsB = ((rs).flagsB & ~(mask)) | (((v) << (shift)) & (mask)))

struct sSparkFx_AA78 {
    char pad0[0x10];
    sV4_AA78 pos;           // 0x10
    char pad20[0x50];
    int f70, f74, f78;      // 0x70
    sRS_AA78 rsA;           // 0x7C
    sRS_AA78 rsB;           // 0x90
};

// Spark FX init: two render states copied from the defaults with their mode bits set (the second also sets f0 bits 2-3).
extern "C" void func_002DAA78(void* vself)
{
    sSparkFx_AA78* self = (sSparkFx_AA78*)vself;
    self->pos = D_004FF130;
    self->f70 = 0;
    self->f74 = 0;
    self->f78 = 0;
    self->rsA = D_00501420_AA78;
    RS_SETB_AA78(self->rsA, 0x3E0, 5, 7);
    RS_SETA_AA78(self->rsA, 0x400000, 22, 1);
    RS_SETA_AA78(self->rsA, 0x1800000, 23, 0);
    RS_SETA_AA78(self->rsA, 0x300000, 20, 0);
    RS_SETA_AA78(self->rsA, 0xFF000, 12, 0);
    RS_SETA_AA78(self->rsA, 0x3, 0, 2);
    RS_SETA_AA78(self->rsA, 0x7C, 2, 7);
    int texA = *(int*)(D_004A289C_AA78 + 0xFA8);
    self->rsA.tex = texA;
    self->rsB = D_00501420_AA78;
    RS_SETB_AA78(self->rsB, 0x3E0, 5, 7);
    RS_SETA_AA78(self->rsB, 0x400000, 22, 1);
    RS_SETA_AA78(self->rsB, 0x1800000, 23, 0);
    RS_SETA_AA78(self->rsB, 0x300000, 20, 0);
    RS_SETA_AA78(self->rsB, 0xFF000, 12, 9);
    RS_SETA_AA78(self->rsB, 0x3, 0, 2);
    RS_SETA_AA78(self->rsB, 0x7C, 2, 7);
    int texB = *(int*)(D_004A289C_AA78 + 0xFA8);
    self->rsB.tex = texB;
    self->rsB.f0 |= 0xC;
}

INCLUDE_ASM("visualfx/boardsparkfx", func_002DABC8);

//100%
extern "C" void func_00371688(void* self, int a1);

struct sRS_B478 {
    int v[5];
};
struct sRenderCtx_B478 {
    char pad[0xE84];
    sRS_B478* top;
};
extern sRenderCtx_B478* D_004A289C;
extern char* D_004A5B80;

struct sVec2_B478 {
    float x, y;
    sVec2_B478(float ax, float ay) : x(ax), y(ay) {}
};
struct sVec4_B478 {
    float x, y, z, w;
    sVec4_B478(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};

// Function-local statics `uv0(0,0)`, `uv1(1,1)`, `col(1,1,1,1)` and their init guards, spelled out
// as the globals splat named.
extern float D_004A54D0;
extern float D_004A54D4;
extern int D_004A54D8;
extern float D_004A54E0;
extern float D_004A54E4;
extern int D_004A54E8;
extern int D_004A54EC;
extern sVec4_B478 D_004D57A0;

struct sVE_B478a {
    short delta;
    short index;
    void (*fn)(void*, int);
};
struct sVE_B478b {
    short delta;
    short index;
    void (*fn)(void*, void*, sVec2_B478*, const sVec2_B478*, const sVec2_B478*, const sVec4_B478*);
};

static inline void push_B478(sRenderCtx_B478* ctx)
{
    ctx->top[1] = ctx->top[0];
    ctx->top++;
}

static inline void pop_B478(sRenderCtx_B478* ctx)
{
    ctx->top--;
}

extern "C" void func_002DB478(char* self)
{
    char* o = *(char**)(self + 0x20);
    if (*(int*)(o + 0x1E0) > 0) {
        func_00371688(o, 7);
    }
    if (*(int*)(self + 0x70) != 0) {
        push_B478(D_004A289C);
        *D_004A289C->top = *(sRS_B478*)(self + 0x7C);
        char* ctx = (char*)D_004A289C;
        sVE_B478a* vt = *(sVE_B478a**)(ctx + 0x10D8);
        vt[82].fn(ctx + vt[82].delta, *(int*)(self + 0x28));
        pop_B478(D_004A289C);
    }
    if (*(int*)(self + 0x74) != 0) {
        push_B478(D_004A289C);
        *D_004A289C->top = *(sRS_B478*)(self + 0x90);
        if (D_004A54D8 == 0) {
            D_004A54D8 = 1;
            D_004A54D0 = 0.0f;
            D_004A54D4 = 0.0f;
        }
        if (D_004A54E8 == 0) {
            D_004A54E8 = 1;
            D_004A54E0 = 1.0f;
            D_004A54E4 = 1.0f;
        }
        if (D_004A54EC == 0) {
            D_004A54EC = 1;
            D_004D57A0.x = 1.0f;
            D_004D57A0.y = 1.0f;
            D_004D57A0.z = 1.0f;
            D_004D57A0.w = 1.0f;
        }
        sVec2_B478* uv0 = (sVec2_B478*)&D_004A54D0;
        sVec2_B478* uv1 = (sVec2_B478*)&D_004A54E0;
        for (int i = 0; i < 3; i++) {
            sVec2_B478 size(((float*)(self + 0x60))[i], ((float*)(self + 0x60))[i]);
            char* ctx = D_004A5B80;
            sVE_B478b* vt = *(sVE_B478b**)(ctx + 0x10D8);
            vt[78].fn(ctx + vt[78].delta, self + 0x30 + i * 0x10, &size, uv0, uv1, &D_004D57A0);
        }
        pop_B478(D_004A289C);
    }
}

