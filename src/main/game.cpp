#include "common.h"

// 16-byte array elements; indexing as arr[i].field (rather than manual
// pointer arithmetic) is what makes GCC emit the target's base-first addu
struct sGameEntry {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
};
extern sGameEntry D_00442168[];

//100%
struct sRState_C078 {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
};

struct sRVEntry_C078 {
    short delta;
    short index;
    int (*fn)(void*, int, int, int, int);
};

struct sRCtx_C078 {
    char pad0[0x24];
    int cur;
    char pad28[0xE84 - 0x28];
    sRState_C078* top;
    char padE88[0xF50 - 0xE88];
    int tbl[(0x10D8 - 0xF50) / 4];
    sRVEntry_C078* vt;
};

extern sRCtx_C078* D_004A289C;

static inline int curLayer_C078(sRCtx_C078* c)
{
    return c->tbl[c->cur];
}

extern "C" void cGame_renderModels(void* self, void* world)
{
    *(short*)((char*)D_004A289C->top + 0x12) = curLayer_C078(D_004A289C);
    sRCtx_C078* ctx = D_004A289C;
    ctx->top->f4 = (ctx->top->f4 & ~0xF80) | 0x880;
    ctx->top->f0 |= 0x30;
    int flag = 0xC00;
    if (*(unsigned int*)(*(char**)((char*)self + 0x84) + 0x10) >= 2) {
        flag = 0x400;
    }
    int n = *(int*)((char*)world + 0x209C);
    int* items = (int*)((char*)world + 0x20A0);
    for (int i = 0; i < n; i++) {
        D_004A289C->vt[0x60].fn((char*)D_004A289C + D_004A289C->vt[0x60].delta, items[i], 0, 0, flag);
    }
    int n2 = *(int*)((char*)world + 0x40A0);
    items = (int*)((char*)world + 0x40A4);
    for (int i = 0; i < n2; i++) {
        D_004A289C->vt[0x60].fn((char*)D_004A289C + D_004A289C->vt[0x60].delta, items[i], 0, 0, flag | 0x20);
    }
}

//100%
extern void* D_004A4248;

struct sVec_C1B0 {
    float x, y, z, w;
    sVec_C1B0() {}
    sVec_C1B0(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

struct sMat_C1B0 {
    float m[4][4];
};

struct sVEm_C1B0 { short delta; short index; sMat_C1B0* (*fn)(void*); };
struct sVEf_C1B0 { short delta; short index; float (*fn)(void*); };
struct sVEv_C1B0 { short delta; short index; void (*fn)(void*); };

struct sRCtx_C1B0 {
    char pad0[0x10D8];
    sVEm_C1B0* vt;      // 0x10D8
};
extern sRCtx_C1B0* D_004A289C_C1B0 __asm__("D_004A289C");

struct sCamObj_C1B0 {
    char pad0[4];
    sVEf_C1B0* vt;      // 0x4
};

struct sRenderCam_C1B0 {
    sCamObj_C1B0* cam;  // 0x0
    char pad4[0xC];
    sVec_C1B0 pos;      // 0x10
    float k;            // 0x20
    float c;            // 0x24
    float n;            // 0x28
    float f;            // 0x2C
};

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec_C1B0 Scale_C1B0(const sVec_C1B0& v, float s)
{
    sVec_C1B0 r;
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

static inline sVec_C1B0 MulVec_C1B0(const sMat_C1B0* m, const sVec_C1B0& v)
{
    return sVec_C1B0(v.x * m->m[0][0] + v.y * m->m[0][1] + v.z * m->m[0][2] + v.w * m->m[0][3],
                     v.x * m->m[1][0] + v.y * m->m[1][1] + v.z * m->m[1][2] + v.w * m->m[1][3],
                     v.x * m->m[2][0] + v.y * m->m[2][1] + v.z * m->m[2][2] + v.w * m->m[2][3],
                     v.x * m->m[3][0] + v.y * m->m[3][1] + v.z * m->m[3][2] + v.w * m->m[3][3]);
}

static inline sMat_C1B0* viewMat_C1B0()
{
    sRCtx_C1B0* c = D_004A289C_C1B0;
    return c->vt[35].fn((char*)c + c->vt[35].delta);
}

// PORT: the unit declares func_0022C1B0 as void(void*); the body returns self, bound by asm label.
sRenderCam_C1B0* func_0022C1B0_impl(sRenderCam_C1B0* self) __asm__("func_0022C1B0");

sRenderCam_C1B0* func_0022C1B0_impl(sRenderCam_C1B0* self)
{
    self->cam = (sCamObj_C1B0*)D_004A4248;
    self->pos = Scale_C1B0(sVec_C1B0(*(sVec_C1B0*)viewMat_C1B0()->m[3]), -1.0f);
    sMat_C1B0* m = viewMat_C1B0();
    self->pos = sVec_C1B0(self->pos.x * m->m[0][0] + self->pos.y * m->m[0][1] + self->pos.z * m->m[0][2] + self->pos.w * m->m[0][3],
                          self->pos.x * m->m[1][0] + self->pos.y * m->m[1][1] + self->pos.z * m->m[1][2] + self->pos.w * m->m[1][3],
                          self->pos.x * m->m[2][0] + self->pos.y * m->m[2][1] + self->pos.z * m->m[2][2] + self->pos.w * m->m[2][3],
                          self->pos.x * m->m[3][0] + self->pos.y * m->m[3][1] + self->pos.z * m->m[3][2] + self->pos.w * m->m[3][3]);
    self->n = 1.0f;
    self->f = 3.0f;
    self->pos.w = 1.0f;
    sCamObj_C1B0* o = self->cam;
    float a = o->vt[8].fn((char*)o + o->vt[8].delta);
    o = self->cam;
    float b = o->vt[9].fn((char*)o + o->vt[9].delta);
    a = a * a * 2.0f;
    b = b * b * 2.0f;
    self->k = (self->n - self->f) / (b - a);
    self->c = self->f - self->k * a;
    o = self->cam;
    ((sVEv_C1B0*)o->vt)[17].fn((char*)o + o->vt[17].delta);
    return self;
}

//100%
void operator_delete(int* ptr);
struct sVEntry_func_0022C3B8 {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void func_0022C3B8(void* self, int flags)
{
    void* obj = *(void**)self;
    sVEntry_func_0022C3B8* vt = *(sVEntry_func_0022C3B8**)((char*)obj + 0x4);
    vt[18].fn((char*)obj + vt[18].delta);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

INCLUDE_ASM("main/game", func_0022C410);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_0022C1B0(void* ctx);
extern "C" void func_0022C410(void* ctx, int patch, int flag);
extern "C" void func_0022C3B8(void* self, int flags);
extern void* D_004A4248;

struct sVEntry0022C620 {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void cGame_renderPatches(void* self, void* world)
{
    char ctx[0x30];
    func_0022C1B0(ctx);
    int n = *(int*)((char*)world + 0x50A8);
    int* items = (int*)((char*)world + 0x50AC);
    for (int i = 0; i < n; i++) {
        func_0022C410(ctx, items[i], 0);
    }
    n = *(int*)((char*)world + 0x70AC);
    items = (int*)((char*)world + 0x70B0);
    for (int i = 0; i < n; i++) {
        func_0022C410(ctx, items[i], 1);
    }
    if (*(int*)(*(char**)((char*)self + 0x84) + 0x14) == 0) {
        void* obj = D_004A4248;
        sVEntry0022C620* vt = *(sVEntry0022C620**)((char*)obj + 4);
        vt[5].fn((char*)obj + vt[5].delta);
    }
    func_0022C3B8(ctx, 2);
}

//100%
struct sVEntry_renderFog {
    short delta;
    short index;
    void (*fn)(void*, void*, int, int);
};
extern "C" void func_002DBF98(void* r);

extern "C" void cGame_renderFogVolumes(void* self, void* world)
{
    void* fog = (char*)world + 0x78B8;
    int n = *(int*)((char*)world + 0x78B4);
    if (n != 0) {
        void* r = *(void**)((char*)self + 0x18);
        sVEntry_renderFog* vt = *(sVEntry_renderFog**)((char*)r + 0x4);
        vt[2].fn((char*)r + vt[2].delta, fog, n, 0);
    }
    fog = (char*)world + 0x7AC0;
    n = *(int*)((char*)world + 0x7ABC);
    if (n != 0) {
        void* r = *(void**)((char*)self + 0x18);
        sVEntry_renderFog* vt = *(sVEntry_renderFog**)((char*)r + 0x4);
        vt[2].fn((char*)r + vt[2].delta, fog, n, 2);
    }
    func_002DBF98(*(void**)((char*)self + 0x18));
}

//100%
void func_002E2F98(void* self, int a1);
extern "C" void func_002E2FF8(void* self, void* list, int n, int mode, int a4);
extern "C" void func_002E30D0(void* self, int a1);

extern "C" void cGame_renderLightHalos(void* self, void* world, int a2)
{
    *(int*)((char*)*(void**)((char*)self + 0x1C) + 0x6494) = 1;
    func_002E2F98(*(void**)((char*)self + 0x1C), a2);
    void* p = (char*)world + 0x7BC4;
    int n = *(int*)((char*)world + 0x7BC0);
    if (n != 0) {
        func_002E2FF8(*(void**)((char*)self + 0x1C), p, n, 0, a2);
    }
    p = (char*)world + 0x7FC8;
    n = *(int*)((char*)world + 0x7FC4);
    if (n != 0) {
        func_002E2FF8(*(void**)((char*)self + 0x1C), p, n, 2, a2);
    }
    func_002E30D0(*(void**)((char*)self + 0x1C), a2);
    *(int*)((char*)*(void**)((char*)self + 0x1C) + 0x6494) = 0;
}

INCLUDE_ASM("main/game", func_0022C830);

//100%
extern "C" void func_0022CD40(void* self);

extern "C" void* SectionMan_ctor(void* self, int a1)
{
    *(int*)((char*)self + 0x1B0) = a1;
    func_0022CD40(self);
    return self;
}

//100%
void operator_delete(int* ptr);

extern "C" void func_0022CD18(void* self, int flags)
{
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
struct cWorldView;
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cWorldView_getNumSections(cWorldView* view);
extern "C" void* func_003A9820(cWorldView* self, unsigned int i);
extern "C" int func_004165A8(const void* a, const void* b);
extern "C" void* func_00144D38(void* iface, int i);
extern "C" void func_0022E228(void* self);

static inline cWorldView* gameWorldView_22CD40(void* self)
{
    return (cWorldView*)(*(char**)*(char**)(*(char**)((char*)self + 0x1B0) + 0x10) + 0x10);
}

extern "C" void func_0022CD40(void* self)
{
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 0);
    int i;
    unsigned int j;

    for (int k = 0; k < 50; k++) {
        D_00442168[k].field_0x4 = -1;
        D_00442168[k].field_0x8 = 0;
    }
    D_00442168[49].field_0x4 = 0;
    for (i = 0; i < 50; i++) {
        for (j = 0; j < (unsigned int)cWorldView_getNumSections(gameWorldView_22CD40(self)); j++) {
            void* name = func_00144D38(iface, i);
            if (func_004165A8(name, func_003A9820(gameWorldView_22CD40(self), j)) == 0) {
                D_00442168[i].field_0x4 = j;
            }
        }
    }
    *(int*)((char*)self + 0x1B8) = 0;
    *(int*)((char*)self + 0x1B4) = 0;
    *(int*)((char*)self + 0x1C0) = 0;
    *(int*)((char*)self + 0x1C8) = 0;
    *(int*)((char*)self + 0x1CC) = 0;
    *(int*)((char*)self + 0x1BC) = 0x16;
    *(int*)((char*)self + 0x1D0) = 1;
    func_0022E228(self);
    *(int*)((char*)self + 0x1AC) = -1;
    *(int*)((char*)self + 0x1A4) = 0;
    *(int*)((char*)self + 0x1A8) = 0;
    *(int*)((char*)self + 0x1C4) = 0;
}

//100%
struct sGroup_CEA8 {
    int f0;
    int count;
    int a;
    int b;
    int ids[6];
};
struct sPair_CEA8 {
    int f0;
    int f4;
};
extern sGroup_CEA8 D_00442488_CEA8[] __asm__("D_00442488");
extern sPair_CEA8 D_00442820[];
extern "C" void func_0022D3D8(void* self, int i);
extern "C" void func_0022D598(void* self, int i);
extern "C" void func_0022D640(void* self, int a1);

extern "C" void func_0022CEA8(char* self, int s, int k)
{
    int arg;
    if (k == 7) {
        arg = D_00442820[s].f4;
    } else {
        arg = k;
    }
    int a = D_00442488_CEA8[s].a;
    int neg = 0;
    if (a < 0) neg = 1;
    int def = 0x31;
    for (int i = 0; i < 0x32; i++) {
        int keep = 1;
        for (int j = 0; j < D_00442488_CEA8[s].count; j++) {
            if (i == D_00442488_CEA8[s].ids[j]) {
                keep = 0;
                break;
            }
        }
        if (i >= 0x2C && i <= 0x30) keep = 0;
        if (i == 0x2B) keep = 0;
        if (keep) {
            func_0022D598(self, i);
        }
    }
    *(int*)(self + 0x1BC) = s;
    *(int*)(self + 0x1C0) = 0;
    for (int j = 0; j < D_00442488_CEA8[s].count; j++) {
        func_0022D3D8(self, D_00442488_CEA8[s].ids[j]);
    }
    // Picking the sky after the loops, from inputs set up before them, keeps gcse from hoisting the xor.
    int sky = neg ? def : a;
    int t = sky ^ 0x31;
    if (t) {
        *(int*)(self + 0x1A4) = 0;
        func_0022D3D8(self, sky);
    }
    if (D_00442488_CEA8[s].b >= 0) {
        func_0022D3D8(self, D_00442488_CEA8[s].b);
    }
    func_0022D640(self, arg);
}

//100%
extern "C" void func_0022D478(void* self, int i);
extern "C" void func_0022D668(char* self, int a1);
extern "C" void cSectionMan_setSky(void* self, int sky);
void func_0022D088_impl(char* self, int s, int k) __asm__("func_0022D088");

void func_0022D088_impl(char* self, int s, int k)
{
    int arg;
    if (k == 7) {
        arg = D_00442820[s].f4;
    } else {
        arg = k;
    }
    int a = D_00442488_CEA8[s].a;
    int neg = 0;
    if (a < 0) neg = 1;
    int def = 0x31;
    for (int i = 0; i < 0x32; i++) {
        int keep = 1;
        for (int j = 0; j < D_00442488_CEA8[s].count; j++) {
            if (i == D_00442488_CEA8[s].ids[j]) {
                keep = 0;
                break;
            }
        }
        if (i >= 0x2C && i <= 0x30) keep = 0;
        if (i == 0x2B) keep = 0;
        if (keep) {
            func_0022D598(self, i);
        }
    }
    *(int*)(self + 0x1C0) = 1;
    *(int*)(self + 0x1BC) = s;
    for (int j = 0; j < D_00442488_CEA8[s].count; j++) {
        func_0022D478(self, D_00442488_CEA8[s].ids[j]);
    }
    cSectionMan_setSky(self, s);
    // Same sky setup as func_0022CEA8.
    int sky = neg ? def : a;
    int t = sky ^ 0x31;
    if (t) {
        func_0022D478(self, sky);
    }
    if (D_00442488_CEA8[s].b >= 0) {
        func_0022D478(self, D_00442488_CEA8[s].b);
    }
    func_0022D668(self, arg);
}

//100%
struct sGroup_D278 {
    int f0;
    int count;
    int a;
    int b;
    int ids[6];
};
extern sGroup_D278 D_00442488_D278[] __asm__("D_00442488");
extern "C" int func_0022E078(void* self, int id);

// PORT: the unit declares func_0022D278(void*) for its callers; the body reads a1, bound by asm label
int func_0022D278_impl(void* self, int idx) __asm__("func_0022D278");

int func_0022D278_impl(void* self, int idx)
{
    int ok = 1;
    for (int i = 0; i < D_00442488_D278[idx].count; i++) {
        if (func_0022E078(self, D_00442488_D278[idx].ids[i]) == 0) {
            ok = 0;
            break;
        }
    }
    int a = D_00442488_D278[idx].a;
    if (a >= 0 && D_00442168[a].field_0x4 >= 0) {
        if (func_0022E078(self, a) == 0) {
            ok = 0;
        }
    }
    int b = D_00442488_D278[idx].b;
    if (b >= 0 && D_00442168[b].field_0x4 >= 0) {
        if (func_0022E078(self, b) == 0) {
            ok = 0;
        }
    }
    return ok;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int func_0022D278(void* self);

extern "C" int func_0022D390(void* self)
{
    int r = 0;
    if (func_0022D278(self) != 0) {
        r = *(int*)((char*)self + 0x1C0) != 0;
    }
    return r;
}

//100%
extern "C" void func_0022E298(void*);

extern "C" void func_0022D3D8(void* self, int i)
{
    int changed;
    if (D_00442168[i].field_0x4 < 0)
        return;
    changed = 0;
    switch (D_00442168[i].field_0x8) {
    case 5:
        D_00442168[i].field_0x8 = 1;
        changed = 1;
        break;
    case 0: case 7:
        D_00442168[i].field_0x8 = 3;
        changed = 1;
        break;
    case 1: case 2: case 3: case 4: case 6: case 8:
        break;
    }
    if (changed)
        func_0022E298(self);
}

//100%
void func_0022E298_478(void* self, int i) __asm__("func_0022E298");
void func_003A99D8_478(void* mgr, int handle) __asm__("func_003A99D8");

extern "C" void func_0022D478(void* self_, int i)
{
    char* self = (char*)self_;
    int changed;
    if (D_00442168[i].field_0x4 < 0)
        return;
    changed = 0;
    switch (D_00442168[i].field_0x8) {
    case 0:
        D_00442168[i].field_0x8 = 4;
        changed = 1;
        break;
    case 7:
        D_00442168[i].field_0x8 = 4;
        changed = 1;
        break;
    case 3:
        D_00442168[i].field_0x8 = 4;
        changed = 1;
        break;
    case 6:
        D_00442168[i].field_0x8 = 8;
        changed = 1;
        break;
    case 1:
    case 5:
        D_00442168[i].field_0x8 = 2;
        func_003A99D8_478(*(char**)*(char**)(*(char**)(self + 0x1B0) + 0x10) + 0x10, D_00442168[i].field_0x4);
        changed = 1;
        break;
    case 8:
        break;
    }
    if (changed)
        func_0022E298_478(self, i);
}

//100%
extern "C" void func_0022E298(void*);

extern "C" void func_0022D598(void* self, int i)
{
    int changed;
    if (D_00442168[i].field_0x4 < 0)
        return;
    changed = 0;
    switch (D_00442168[i].field_0x8) {
    case 3:
        D_00442168[i].field_0x8 = 0;
        changed = 1;
        break;
    case 1: case 2: case 6:
        D_00442168[i].field_0x8 = 5;
        changed = 1;
        break;
    case 0: case 4: case 5: case 7: case 8:
        break;
    }
    if (changed)
        func_0022E298(self);
}

//100%
extern "C" void func_0022D640(void* self, int a1)
{
    if (a1 != 0 && *(int*)((char*)self + 0x1B4) == 0) {
        *(int*)((char*)self + 0x1B4) = 1;
        *(int*)((char*)self + 0x1B8) = a1;
    }
}

//100%
extern "C" void func_0022D668(char* self, int arg)
{
    if (arg != 0) {
        switch (*(int*)(self + 0x1B4)) {
        case 0:
            *(int*)(self + 0x1B8) = arg;
            *(int*)(self + 0x1B4) = 3;
            break;
        case 1:
            *(int*)(self + 0x1B4) = 3;
            break;
        case 2:
            *(int*)(self + 0x1B4) = 4;
            break;
        case 3:
        case 4:
            break;
        }
    }
}

//100%
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void cBE_setState(int state);
extern "C" void cAI_commitRunStats(void* riders);
extern "C" void cBENewRaceInterface_setGameMode(void* self, int mode);
extern "C" void cBENewRaceInterface_setGameEvent(void* self, int evt);
extern "C" void cGameModeMan_initGameMode(void* self, int mode);
extern "C" void func_00231250(void* gm, int state, int a, int b);
extern void* D_004A28A8;

// View of sGameSettings; bound to the same symbol by asm label.
struct sGameSettings_D6C8 {
    char pad_0x00[0x48];
    signed char eventKind; // 0x48: 4 = free ride
    signed char gameType;  // 0x49: 0 = Conquer the Mountain
    signed char mode;      // 0x4A
};
extern sGameSettings_D6C8 D_00535BC8_D6C8 __asm__("D_00535BC8");

struct sVE_D6C8 {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void func_0022D6C8(char* self, int mode)
{
    char* iface = (char*)cBE_getInterface_Fv(cBE_getBE(), 0);
    int skip = 0;
    if (D_00535BC8_D6C8.gameType != 0) {
        skip = 1;
    } else {
        int notFree = D_00535BC8_D6C8.eventKind != 4;
        if (notFree || (unsigned int)(*(int*)(self + 0x1BC) - 0xE) < 3 || mode == 1) {
            skip = 1;
        }
    }
    if (skip) {
        return;
    }
    cBE_setState(0);
    char* game = *(char**)((char*)D_004A28A8 + 0x84);
    if (*(int*)(game + 0x214) != 4) {
        return;
    }
    cAI_commitRunStats(*(void**)(game + 0xC));
    char* g = (char*)D_004A28A8;
    *(int*)(*(char**)(*(char**)(g + 0x84) + 0xC) + 0xC) = 0;
    if ((unsigned int)(*(int*)(*(char**)(*(char**)(g + 0x84) + 0x78) + 0x1BC) - 0xE) < 3) {
        cBENewRaceInterface_setGameMode(iface, 4);
        cBENewRaceInterface_setGameEvent(iface, 0xC);
    } else {
        switch (mode) {
        case 2:
            cBENewRaceInterface_setGameMode(iface, 0);
            cBENewRaceInterface_setGameEvent(iface, 0);
            break;
        case 3:
            cBENewRaceInterface_setGameMode(iface, 1);
            cBENewRaceInterface_setGameEvent(iface, 1);
            break;
        case 4:
            cBENewRaceInterface_setGameMode(iface, 2);
            cBENewRaceInterface_setGameEvent(iface, 3);
            break;
        case 5:
            cBENewRaceInterface_setGameMode(iface, 3);
            cBENewRaceInterface_setGameEvent(iface, 2);
            break;
        case 6:
            cBENewRaceInterface_setGameMode(iface, 5);
            cBENewRaceInterface_setGameEvent(iface, 4);
            break;
        case 0:
        case 1:
            break;
        }
    }
    sVE_D6C8* vt = *(sVE_D6C8**)(iface + 0xC);
    vt[1].fn(iface + vt[1].delta);
    cGameModeMan_initGameMode(*(void**)((char*)D_004A28A8 + 0xC0), D_00535BC8_D6C8.mode);
    func_00231250(*(void**)(self + 0x1B0), 1, 1, 0);
}

//100%
extern "C" void func_0022DE58(void* self, int v);
extern "C" void func_0022DE98(void* self);
extern "C" void func_0022DF50(void* self);
void* func_0022DFD0(void* self);
extern "C" void func_0022DFF0(void* self);
struct sSectionNode_D8D8 {
    int id;
    sSectionNode_D8D8* next;
};
extern "C" sSectionNode_D8D8* func_0022E348_D8D8(void* self, sSectionNode_D8D8* prev) __asm__("func_0022E348");
extern "C" void func_0022E360_D8D8(void* self, sSectionNode_D8D8* prev, sSectionNode_D8D8* node) __asm__("func_0022E360");
extern "C" int func_003A9890_D8D8(cWorldView* view, int section) __asm__("func_003A9890");
extern "C" int func_003A9958(cWorldView* view, int section);
extern "C" int func_003A98C8(cWorldView* view, int section, float t);
int cWorldView_isSectionLoaded(cWorldView* view, int section);
extern "C" void func_00230338_D8D8(void* gm, int section) __asm__("func_00230338");
extern "C" void func_00230360_D8D8(void* gm, int section) __asm__("func_00230360");
extern "C" int func_00144D50(void* iface, int i);
extern "C" void func_003A7058(void* self, int rate);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern int D_00442150[];
extern float D_0044C208[];
extern char D_0047B470[];
extern char D_0047B480[];
extern char D_004A2A18[];

extern "C" void func_0022D8D8(void* self_)
{
    char* self = (char*)self_;
    char buf[256];
    void* iface;
    int flag104;
    int flag108;
    char* fmt;
    sSectionNode_D8D8* node;
    sSectionNode_D8D8* prev;
    int changed;
    int waiting;
    int done;
    int idx;
    int section;

    if (*(int*)(self + 0x1A8)) {
        func_0022DE98(self);
    }
    node = func_0022E348_D8D8(self, 0);
    prev = 0;
    if (node == 0 && *(int*)(self + 0x1B4) == 0) {
        return;
    }
    changed = 0;
    iface = cBE_getInterface_Fv(cBE_getBE(), 0);
    waiting = 0;
    flag104 = 0;
    flag108 = 0;
    while (node) {
        idx = node->id;
        done = 0;
        section = D_00442168[idx].field_0x4;
        switch (D_00442168[idx].field_0x8) {
        case 7:
            if (func_003A9890_D8D8(gameWorldView_22CD40(self), section)) {
                D_00442168[idx].field_0x8 = 0;
            } else {
                changed = 1;
            }
            break;
        case 5:
            if (func_003A9958(gameWorldView_22CD40(self), section)) {
                D_00442168[idx].field_0x8 = 7;
                func_00230360_D8D8(*(void**)(self + 0x1B0), section);
            }
            changed = 1;
            break;
        case 6:
            if (cWorldView_isSectionLoaded(gameWorldView_22CD40(self), section)) {
                D_00442168[idx].field_0x8 = 1;
                func_00230338_D8D8(*(void**)(self + 0x1B0), section);
            } else {
                waiting = 1;
            }
            break;
        case 8:
            if (cWorldView_isSectionLoaded(gameWorldView_22CD40(self), section)) {
                D_00442168[idx].field_0x8 = 2;
                func_00230338_D8D8(*(void**)(self + 0x1B0), section);
                func_003A99D8_478(gameWorldView_22CD40(self), section);
            } else {
                waiting = 1;
                flag104 = 1;
            }
            break;
        case 3:
            flag108 = 1;
            break;
        case 4:
            flag108 = 1;
            flag104 = 1;
            break;
        case 1:
            if (func_00144D50(iface, idx) == 4) {
                func_0022DE58(self, idx);
            }
            done = 1;
            break;
        case 2:
            if (func_00144D50(iface, idx) == 4) {
                func_0022DE58(self, idx);
            }
            if (*(int*)(self + 0x1A8)) {
                func_0022DE98(self);
            }
            done = 1;
            break;
        case 0:
            done = 1;
            break;
        }
        if (done) {
            func_0022E360_D8D8(self, prev, node);
            node = prev;
        }
        prev = node;
        node = func_0022E348_D8D8(self, prev);
    }

    if (!changed && flag108) {
        node = func_0022E348_D8D8(self, 0);
        if ((unsigned int)cWorldView_getNumSections(gameWorldView_22CD40(self)) >= 2) {
            fmt = D_0047B470;
        } else {
            fmt = D_0047B480;
        }
        while (node) {
            int id = node->id;
            int sec = D_00442168[id].field_0x4;
            sprintf(buf, D_004A2A18, fmt, func_00144D38(iface, id));
            if (D_00442168[id].field_0x8 == 3) {
                if (func_003A98C8(gameWorldView_22CD40(self), sec, D_0044C208[D_00442168[id].field_0xc])) {
                    waiting = 1;
                    D_00442168[id].field_0x8 = 6;
                }
            } else if (D_00442168[id].field_0x8 == 4) {
                if (func_003A98C8(gameWorldView_22CD40(self), sec, D_0044C208[D_00442168[id].field_0xc])) {
                    D_00442168[id].field_0x8 = 8;
                    waiting = 1;
                    flag104 = 1;
                }
            }
            node = func_0022E348_D8D8(self, node);
        }
    }

    if (waiting) {
        *(int*)(self + 0x1C4) = 2;
    } else if (*(int*)(self + 0x1C0) == 0) {
        *(int*)(self + 0x1C4) = 3;
    } else {
        char* w = *(char**)*(char**)(*(char**)(self + 0x1B0) + 0x10);
        if (*(int*)(w + 0x250) == 0) {
            *(int*)(self + 0x1C4) = 0;
        } else if (*(int*)(w + 0x2A0)) {
            *(int*)(self + 0x1C4) = 1;
        } else {
            *(int*)(self + 0x1C4) = 0;
        }
    }

    int r = 0;
    switch (*(int*)(self + 0x1B4)) {
    case 0:
    case 2:
        break;
    case 1:
        func_0022DF50(self);
        *(int*)(self + 0x1B4) = 2;
        break;
    case 3:
        func_0022DF50(self);
        r = 1;
        *(int*)(self + 0x1B4) = 4;
        break;
    case 4:
        if (flag104) {
            r = 1;
        } else if (func_0022DFD0(self)) {
            func_0022DFF0(self);
            *(int*)(self + 0x1B4) = 0;
            *(int*)(self + 0x1B8) = 0;
        } else {
            r = 1;
        }
        break;
    }
    if (flag104 || r) {
        *(int*)(self + 0x1D0) = 0;
        *(int*)(self + 0x1C4) = 4;
    } else {
        *(int*)(self + 0x1D0) = 1;
    }
    func_003A7058(*(char**)*(char**)(*(char**)(self + 0x1B0) + 0x10) + 0x300, D_00442150[*(int*)(self + 0x1C4)]);
}

//100%
extern "C" void func_0022D478(void* self, int v);

extern "C" void func_0022DE58(void* self, int v)
{
    if (*(int*)((char*)self + 0x1AC) != v) {
        *(int*)((char*)self + 0x1AC) = v;
        func_0022D478(self, v);
        *(int*)((char*)self + 0x1A8) = 1;
    }
}

//100%
extern "C" void func_0022D598(void* self, int id);
void func_00353D98(void* self);
extern "C" void func_00353CF0(void* self, int id);

extern "C" void func_0022DE98(void* self)
{
    if (*(int*)((char*)self + 0x1A8) == 0) {
        return;
    }
    if (*(int*)((char*)self + 0x1A4) == 0) {
        return;
    }
    int i;
    for (i = 0x2C; i < 0x31; i++) {
        if (i != *(int*)((char*)self + 0x1AC)) {
            func_0022D598(self, i);
        }
    }
    int id = D_00442168[*(int*)((char*)self + 0x1AC)].field_0x4;
    void* o = *(void**)((char*)*(void**)((char*)self + 0x1B0) + 0x14);
    if (*(int*)((char*)o + 0x10) != id) {
        func_00353D98(o);
        func_00353CF0(*(void**)((char*)*(void**)((char*)self + 0x1B0) + 0x14), id);
    }
    *(int*)((char*)self + 0x1A4) = 0;
    *(int*)((char*)self + 0x1A8) = 0;
    *(int*)((char*)self + 0x1AC) = -1;
}

//100%
class cBEIface22DF50 {
public:
    int pad[3];
    virtual void v01();
};
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_00231250(void* gm, int state, int a, int b);
void func_00231278(void* gm, int state);
extern int D_00535C08[];
extern int D_004A11B8;

extern "C" void func_0022DF50(void* self)
{
    func_00231250(*(void**)((char*)self + 0x1B0), 0xB, 0, 1);
    cBEIface22DF50* iface = (cBEIface22DF50*)cBE_getInterface_Fv(cBE_getBE(), 0);
    D_00535C08[0] = *(int*)((char*)self + 0x1BC);
    D_004A11B8 = 1;
    iface->v01();
    func_00231278(*(void**)((char*)self + 0x1B0), 0xA);
}

extern "C" void* func_002312D8(int);

//100%
void* func_0022DFD0(void* self)
{
    return func_002312D8(*(int*)((char*)self + 0x1b0));
}

//100%
class cRace22DFF0 {
public:
    char pad[0xCC];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05(int);
};
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int* func_00144BC0(void* iface);
extern "C" void cSectionMan_setSky(void* self, int sky);
extern "C" void func_00231250(void* gm, int state, int a, int b);
extern void* D_004A28A8;

extern "C" void func_0022DFF0(void* self)
{
    cSectionMan_setSky(self, *func_00144BC0(cBE_getInterface_Fv(cBE_getBE(), 0)));
    if (*(int*)((char*)self + 0x1CC) != 0) {
        *(int*)((char*)self + 0x1CC) = 0;
        (*(cRace22DFF0**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC))->v05(3);
    }
    func_00231250(*(void**)((char*)self + 0x1B0), 0xA, 0, 0);
}

//100%
extern "C" int func_0022E078(void* self, int a1)
{
    int v = D_00442168[a1].field_0x8;
    return (unsigned int)(v - 1) < 2;
}

//100%
struct sGameEntry2 {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1c;
    int field_0x20;
    int field_0x24;
};
extern sGameEntry2 D_00442488[];

extern "C" int func_0022E098(void* self, int a1)
{
    return D_00442168[D_00442488[a1].field_0x10].field_0x4;
}

//100%
extern "C" int func_0022E0C8(void* self, int a1)
{
    return D_00442168[a1].field_0x4;
}

//100%
extern "C" int func_0022E0E0(void* self, int a1)
{
    int i;
    for (i = 0; i < 50; i++) {
        if (a1 == D_00442168[i].field_0x4) {
            return i;
        }
    }
    return 50;
}

//100%
extern signed char D_00535C11[];
extern "C" void func_0022D088(void* self, void* a1, int a2);

extern "C" void func_0022E118(void* self, void* a1)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    if (D_00535C11[0] == 0) {
        func_0022D088(self, a1, 1);
        *(int*)((char*)self + 0x1CC) = 1;
    }
}
