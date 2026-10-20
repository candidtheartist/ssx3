#include "common.h"

//100%
extern char* D_004A5B80;
extern char D_0048E850[];
unsigned int BXrand();
extern "C" void func_0034BCA0(void* self, void* verts);

// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator new[](unsigned int size, const char* tag, unsigned int flags, int d) __asm__("operator_new__FUi");

struct sFsV3_CM {
    float x, y, z;
    sFsV3_CM() {}
    sFsV3_CM(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

struct sFsV2_CM {
    float x, y;
    sFsV2_CM() {}
    sFsV2_CM(float ax, float ay) : x(ax), y(ay) {}
};

struct sFsCol_CM {
    float a, r, g, b;
    sFsCol_CM() {}
};

inline sFsV3_CM operator+(const sFsV3_CM& a, const sFsV3_CM& b) { return sFsV3_CM(a.x + b.x, a.y + b.y, a.z + b.z); }
inline sFsV3_CM operator*(const sFsV3_CM& a, float s) { return sFsV3_CM(a.x * s, a.y * s, a.z * s); }
inline sFsV2_CM operator+(const sFsV2_CM& a, const sFsV2_CM& b) { return sFsV2_CM(a.x + b.x, a.y + b.y); }
inline sFsV2_CM operator*(const sFsV2_CM& a, float s) { return sFsV2_CM(a.x * s, a.y * s); }

// Uniform float in [0, 1) built from the random mantissa bits.
static inline float randf_CM()
{
    union {
        int i;
        float f;
    } u;
    u.i = (BXrand() & 0x7FFFFF) | 0x3F800000;
    return u.f - 1.0f;
}

struct sFsVE_CM {
    short delta;
    short index;
    void* (*fn)(void*, int, int, unsigned int);
};

struct sFsQuadVE_CM {
    short delta;
    short index;
    void (*fn)(void*, void*, int, sFsV3_CM*, sFsV2_CM*, sFsCol_CM*);
};

struct sFsMeshVE_CM {
    short delta;
    short index;
    void (*fn)(void*, sFsV3_CM*, sFsCol_CM*, sFsV2_CM*);
};

struct sFsMesh_CM {
    int pad0;
    sFsMeshVE_CM* vt;   // 0x4
};

struct sFlagElem_CM {
    char pad0[0x1C];
    float windX;            // 0x1C
    float windY;            // 0x20
    char pad24[0x3C];
    sFsMesh_CM* mesh;       // 0x60
    int cols;               // 0x64
    int rows;               // 0x68
    float colScale;         // 0x6C
    float rowScale;         // 0x70
    sFsV3_CM* verts;        // 0x74
    float phase[4];         // 0x78
    float u;                // 0x88
    float v;                // 0x8C
};

INCLUDE_ASM("object/flagset", cFlagSet_CreateMesh);
extern "C" void cFlagSet_CreateMesh(void* p, void* item);

//100%
extern char* D_004A5B80;
void cMemMan_free(void*);

struct sFlagSetVEntryB7B8 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

extern "C" void func_0034B7B8(void* self)
{
    char* s = (char*)self;
    void* h = *(void**)(s + 0x60);
    if (h != 0) {
        char* mgr = D_004A5B80;
        sFlagSetVEntryB7B8* vt = *(sFlagSetVEntryB7B8**)(mgr + 0x10D8);
        vt[77].fn(mgr + vt[77].delta, h);
        *(void**)(s + 0x60) = 0;
    }
    void* m = *(void**)(s + 0x74);
    if (m != 0) {
        cMemMan_free(m);
        *(void**)(s + 0x74) = 0;
    }
}

//100%
extern int D_004A4240;
extern "C" void* World_GetFlagManager();
extern "C" int World_GetAIFrameCount();
extern "C" void func_0034BCA0(void* self, void* verts);

struct sFlagVert_B818 {
    float x, y, z;
    sFlagVert_B818() {}
};

struct sFlagVEntry_B818 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

struct sFlagMesh_B818 {
    int pad0;
    sFlagVEntry_B818* vt;   // 0x4
};

struct sFlagElem_B818 {
    char pad0[0x4];
    float speed[4];         // 0x4
    char pad14[0x38];
    float blend;            // 0x4C
    float scrollU;          // 0x50
    float scrollV;          // 0x54
    char pad58[0x4];
    int active;             // 0x5C
    sFlagMesh_B818* mesh;   // 0x60
    char pad64[0x14];
    float phase[4];         // 0x78
    float u;                // 0x88
    float v;                // 0x8C
    int parity;             // 0x90
};

INCLUDE_ASM("object/flagset", func_0034B818);
extern "C" void func_0034B818(void* elem);

//100%
extern char* D_004A5B80;
extern char* D_004A47B8;
extern int D_004A4244;
// PORT: 128-bit integer mode for VU0 asm memory operands
typedef int cQuad128_34B9B0 __attribute__((mode(TI)));
extern char D_004FF1A0[];

struct sRS_34B9B0 {
    unsigned int f0_0 : 12;
    unsigned int f0_12 : 8;
    unsigned int f0_20 : 12;
    unsigned int f4_0 : 2;
    unsigned int f4_2 : 5;
    unsigned int f4_7 : 25;
    int f8;
    int fC;
    int f10;
};
extern sRS_34B9B0 D_00501420;

struct sVec4_34B9B0 {
    float x, y, z, w;
    sVec4_34B9B0() {}
    sVec4_34B9B0(const float& a, const float& b, const float& c, const float& d) : x(a), y(b), z(c), w(d) {}
} __attribute__((aligned(16)));

struct sRow_34B9B0 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sMat_34B9B0 {
    sRow_34B9B0 r[4];
};

struct sModel_34B9B0 {
    char pad_0x0[0x7D];
    unsigned char page;     // 0x7D
    short slot;             // 0x7E
};

static inline int IsLoaded_34B9B0(sModel_34B9B0* m)
{
    char* wc = *(char**)D_004A47B8;
    if (m->page == 0xFF)
        return 1;
    int ok = *(int*)(wc + (m->page << 3) + 0x24) == 6;
    return ok ? *(int*)(wc + m->slot * 0x18 + 0x3F0) == 3 : 0;
}

struct sPair_34B9B0 { sRow_34B9B0 r[4]; };
struct sVE43_34B9B0 { short delta; short index; sPair_34B9B0 (*fn)(void*); };
struct sPair_34B9B0;
struct sVE93_34B9B0 { short delta; short index; int (*fn)(void*, sVec4_34B9B0*, sVec4_34B9B0*, sPair_34B9B0*); };
struct sVE96_34B9B0 { short delta; short index; void (*fn)(void*, void*, int, int, int); };
struct sVE7_34B9B0 { short delta; short index; void (*fn)(void*, void*, void*, sMat_34B9B0*); };

static inline void SetF0_12_34B9B0(sRS_34B9B0* rs, int v) { rs->f0_12 = v; }
static inline void SetF4_2_34B9B0(sRS_34B9B0* rs, int v) { rs->f4_2 = v; }

// PORT: PS2-only VU0 inline asm (4x4 matrix copy).
static inline void MatCopy_34B9B0(sMat_34B9B0* d, const sMat_34B9B0* s)
{
    __asm__(
        "lqc2      $vf1, 0x0(%1)\n"
        "lqc2      $vf2, 0x10(%1)\n"
        "lqc2      $vf3, 0x20(%1)\n"
        "lqc2      $vf4, 0x30(%1)\n"
        "sqc2      $vf1, 0x0(%0)\n"
        "sqc2      $vf2, 0x10(%0)\n"
        "sqc2      $vf3, 0x20(%0)\n"
        "sqc2      $vf4, 0x30(%0)\n"
        :
        : "r"(d), "r"(s)
        : "memory");
}

struct sFlagSetEntry;
struct sFSE_34B9B0 {
    char pad[0x94];
    sModel_34B9B0* models[1];
};

#define TOP_34B9B0(c) (*(sRS_34B9B0**)((c) + 0xE84))

extern "C" void func_0034B9B0(sFlagSetEntry* e)
{
    char* self = (char*)e;
    if (D_004A4244 == 0) {
        return;
    }
    char* ctx = D_004A5B80;
    TOP_34B9B0(ctx)[1] = TOP_34B9B0(ctx)[0];
    *++TOP_34B9B0(ctx) = D_00501420;
    if (*(signed char*)(self + 3) != 0) {
        SetF0_12_34B9B0(TOP_34B9B0(D_004A5B80), 0xFF);
        SetF4_2_34B9B0(TOP_34B9B0(D_004A5B80), 11);
    } else {
        SetF4_2_34B9B0(TOP_34B9B0(ctx), 5);
    }
    float one = 1.0f;
    for (int i = 0; i < *(int*)(self + 0x5C); i++) {
        sModel_34B9B0* m = ((sFSE_34B9B0*)self)->models[i];
        if (!IsLoaded_34B9B0(m)) {
            continue;
        }
        {
            sVE93_34B9B0* vt = *(sVE93_34B9B0**)(ctx + 0x10D8);
            char* thisp = ctx + vt[93].delta;
            sVec4_34B9B0 a(*(float*)((char*)m + 0x60), *(float*)((char*)m + 0x64), *(float*)((char*)m + 0x68), one);
            sVec4_34B9B0 b(*(float*)((char*)m + 0x6C), *(float*)((char*)m + 0x70), *(float*)((char*)m + 0x74), one);
            sVec4_34B9B0* pb = &b;
            sVE43_34B9B0* vt43 = *(sVE43_34B9B0**)(ctx + 0x10D8);
            sPair_34B9B0 c = vt43[43].fn(ctx + vt43[43].delta);
            if (vt[93].fn(thisp, &a, pb, &c) == 1) {
                continue;
            }
        }
        {
            char* pos = (char*)m + 0x10;
            sMat_34B9B0 mat;
            MatCopy_34B9B0(&mat, (sMat_34B9B0*)D_004FF1A0);
            mat.r[3].x = *(float*)(self + 0x88);
            mat.r[3].y = *(float*)(self + 0x8C);
            char* h = *(char**)(self + 0x60);
            if (h != 0) {
                sVE7_34B9B0* hv = *(sVE7_34B9B0**)(h + 4);
                hv[7].fn(h + hv[7].delta, pos, *(void**)((char*)m + 0x94), &mat);
            } else {
                sVE96_34B9B0* v96 = *(sVE96_34B9B0**)(ctx + 0x10D8);
                v96[96].fn(ctx + v96[96].delta, m, 0, 0, 0);
            }
        }
    }
    TOP_34B9B0(ctx)--;
}

INCLUDE_ASM("object/flagset", func_0034BCA0);

//100%
struct sFlagSetVEntryC2E0a {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

struct sFlagSetVEntryC2E0b {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

struct sFlagSet_C2E0 {
    char pad0[0x5C];
    int count;          // 0x5C
    char pad60[0x34];
    void* items[1];     // 0x94
};

extern "C" void func_0034C2E0(void* elem, void* stream)
{
    int i;
    sFlagSet_C2E0* self = (sFlagSet_C2E0*)elem;
    sFlagSetVEntryC2E0a* e = &(*(sFlagSetVEntryC2E0a**)stream)[1];
    e->fn((char*)stream + e->delta, self, 0x60);
    for (i = 0; i < self->count; i++) {
        sFlagSetVEntryC2E0b* e2 = &(*(sFlagSetVEntryC2E0b**)stream)[5];
        e2->fn((char*)stream + e2->delta, self->items[i]);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sFlagSetVEntryC378a {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

struct sFlagSetVEntryC378b {
    short delta;
    short index;
    void* (*fn)(void*);
};

extern "C" void cFlagSet_CreateMesh(void* self, void* item);

extern "C" void func_0034C378(void* elem, void* stream)
{
    int i;
    sFlagSet_C2E0* self = (sFlagSet_C2E0*)elem;
    sFlagSetVEntryC378a* e = &(*(sFlagSetVEntryC378a**)stream)[2];
    e->fn((char*)stream + e->delta, self, 0x60);
    for (i = 0; i < self->count; i++) {
        sFlagSetVEntryC378b* e2 = &(*(sFlagSetVEntryC378b**)stream)[3];
        self->items[i] = e2->fn((char*)stream + e2->delta);
    }
    if (self->count > 0) {
        cFlagSet_CreateMesh(self, self->items[0]);
    }
}

//100%
extern "C" void* func_00354648(void* self, void* a1);
extern "C" void* func_0034AF38(void* self);
extern void* D_0048FB80[];

struct sFlagSetElem_C428 {
    char data[0x188];
};

struct sFlagSet_C428 {
    char pad0[0xC];
    void** vtable;                  // 0xC
    int field_0x10;                 // 0x10
    float field_0x14;               // 0x14
    float field_0x18;               // 0x18
    int field_0x1c;                 // 0x1C
    sFlagSetElem_C428 elems[15];    // 0x20
};

extern "C" sFlagSet_C428* cFlagManager_ctor(sFlagSet_C428* self, void* a1)
{
    int i;
    sFlagSetElem_C428* p = self->elems;
    func_00354648(self, a1);
    self->vtable = D_0048FB80;
    for (i = 14; i != -1; i--, p++) {
        func_0034AF38(p);
    }
    self->field_0x14 = 0.5f;
    self->field_0x18 = 0.25f;
    self->field_0x1c = 0;
    self->field_0x10 = 0;
    return self;
}

//100%
extern "C" void func_003546C8(void* self, int flags);
extern void* D_0048FB80[];

struct sFlagSetVEntry_C4B8 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sFlagSetElem_C4B8 {
    char pad0[0x184];
    sFlagSetVEntry_C4B8* vt;        // 0x184
};

struct sFlagSet_C4B8 {
    char pad0[0xC];
    void** vtable;                  // 0xC
    char pad10[0x10];
    sFlagSetElem_C4B8 elems[15];    // 0x20
};

extern "C" void cFlagManager_dtor(sFlagSet_C4B8* self, int flags)
{
    self->vtable = D_0048FB80;
    if (self->elems != 0) {
        sFlagSetElem_C4B8* p = self->elems + 15;
        while (self->elems != p) {
            p--;
            p->vt[1].fn((char*)p + p->vt[1].delta, 0);
        }
    }
    func_003546C8(self, flags);
}

//100%
struct sFlagSetElem_C548 {
    char pad0[0x5C];
    int active; // 0x5C
    char pad60[0x188 - 0x60];
};

struct sFlagSet_C548 {
    char pad0[0x20];
    sFlagSetElem_C548 elems[15]; // 0x20
};

extern "C" int func_0034AFE8(void* self, void* data, void* ctx);
extern "C" void func_0034B038(void* self, void* data, void* ctx);

extern "C" void func_0034C548(sFlagSet_C548* self, void* node, void* desc)
{
    int i;
    sFlagSetElem_C548* e;
    for (i = 0, e = self->elems; i < 15; i++, e++) {
        if (e->active != 0 && func_0034AFE8(e, desc, node) != 0) {
            func_0034B038(e, desc, node);
            return;
        }
    }
    sFlagSetElem_C548* f = self->elems;
    for (int j = 0; j < 15; j++, f++) {
        if (f->active == 0) {
            func_0034B038(f, desc, node);
            return;
        }
    }
}

//100%
struct sFlagSetElem_C600 {
    char pad0[0x5C];
    int active; // 0x5C
    char pad60[0x188 - 0x60];
};

struct sFlagSet_C600 {
    char pad0[0x20];
    sFlagSetElem_C600 elems[15]; // 0x20
};

extern "C" int func_0034B168(void* elem, void* arg);

extern "C" void func_0034C600(sFlagSet_C600* self, void* arg)
{
    int i;
    sFlagSetElem_C600* e = self->elems;
    for (i = 0; i < 15; i++, e++) {
        if (e->active != 0 && func_0034B168(e, arg) != 0) {
            return;
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sFlagSetElem_C668 {
    char pad0[0x5C];
    int active; // 0x5C
    char pad60[0x188 - 0x60];
};

struct sFlagSet_C668 {
    char pad0[0x10];
    float level;    // 0x10
    float base;     // 0x14
    float delta;    // 0x18
    float t;        // 0x1C
    sFlagSetElem_C668 elems[15]; // 0x20
};

extern "C" int func_002D1BA0();
extern "C" void func_0034B818(void* elem);
unsigned int BXrand();
extern char* D_004A5B64;

// Uniform float in [0, 1) built from the random mantissa bits.
static inline float randf_34C668()
{
    union {
        int i;
        float f;
    } u;
    u.i = (BXrand() & 0x7FFFFF) | 0x3F800000;
    return u.f - 1.0f;
}

extern "C" void func_0034C668(sFlagSet_C668* self)
{
    float amp = 0.15f;
    switch (func_002D1BA0()) {
    case 1:
        break;
    case 2:
        amp = 0.3f;
        break;
    case 3:
        amp = 0.45f;
        break;
    }
    float one = 1.0f;
    self->t += one / (float)*(int*)(D_004A5B64 + 0x10);
    if (one <= self->t) {
        self->t -= one;
        self->base += self->delta;
        float lo = -amp;
        self->delta = lo + (amp - lo) * randf_34C668();
        if (self->base + self->delta < 0.0f) {
            self->delta = -self->base;
        }
        if (one < self->base + self->delta) {
            self->delta = one - self->base;
        }
    }
    self->level = self->base + self->delta * self->t;
    int i;
    for (i = 0; i < 15; i++) {
        sFlagSetElem_C668* e = &self->elems[i];
        if (e->active != 0) {
            func_0034B818(e);
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sFlagSetEntry {
    char pad_0x0[0x5C];
    int active; // 0x5C
    char pad_0x60[0x128];
};

struct sFlagSetOwner {
    char pad_0x0[0x20];
    sFlagSetEntry entries[15]; // 0x20
};

extern "C" void func_0034B9B0(sFlagSetEntry* e);

extern "C" void func_0034C7F8(sFlagSetOwner* self)
{
    int i;
    for (i = 0; i < 15; i++) {
        sFlagSetEntry* e = &self->entries[i];
        if (e->active != 0) {
            func_0034B9B0(e);
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sFlagSetElem_C848 {
    char data[0x188];
};

struct sFlagSet_C848 {
    char pad0[0x20];
    sFlagSetElem_C848 elems[15]; // 0x20
};

extern "C" void func_0034C2E0(void* elem, void* arg);

extern "C" void func_0034C848(sFlagSet_C848* self, void* arg)
{
    int i;
    for (i = 0; i < 15; i++) {
        func_0034C2E0(&self->elems[i], arg);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sFlagSetElem_C898 {
    char data[0x188];
};

struct sFlagSet_C898 {
    char pad0[0x20];
    sFlagSetElem_C898 elems[15]; // 0x20
};

extern "C" void func_0034C378(void* elem, void* arg);

extern "C" void func_0034C898(sFlagSet_C898* self, void* arg)
{
    int i;
    for (i = 0; i < 15; i++) {
        func_0034C378(&self->elems[i], arg);
    }
}

INCLUDE_ASM("object/flagset", func_0034C8E8);

//100%
struct sFlagBlock_CAB8 {
    unsigned int w[4];
};

struct sFlagElem_CAB8 {
    float v[4];
    sFlagElem_CAB8() {}
    void* operator new[](unsigned int, void* p) { return p; }
};

struct sFlagSet_CAB8 {
    char pad0[0xC];
    void** vtable;              // 0xC
    char pad10[0xC];
    sFlagBlock_CAB8 block;      // 0x1C
    int field_0x2c;             // 0x2C
    int field_0x30;             // 0x30
    int field_0x34;             // 0x34
    int field_0x38;             // 0x38
    int field_0x3c;             // 0x3C
};

extern "C" void* func_0034FB00(void* self, int a1, int type, void* obj);
extern "C" void func_0034D1E8(void* self);
extern "C" void func_0034D6F0(void* self, float dt);
extern void* D_0048FA00[];

// PORT: the unit declares this as void (callers ignore the result); bound by asm label.
extern "C" sFlagSet_CAB8* Fence_ctor_ctor(sFlagSet_CAB8* self, int a1, void* obj, sFlagBlock_CAB8* desc, int flag, float dt) __asm__("Fence_ctor");
INCLUDE_ASM("object/flagset", Fence_ctor);
extern "C" sFlagSet_CAB8* Fence_ctor_ctor(sFlagSet_CAB8* self, int a1, void* obj, sFlagBlock_CAB8* desc, int flag, float dt);

//100%
extern char* D_004A5B80;
extern void* D_0048FA00[];
extern "C" void func_0034FBF0(void* self, int flags);

struct sFlagSetVEntryCB80 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

extern "C" void Fence_dtor(void* self, int flags)
{
    char* s = (char*)self;
    *(void***)(s + 0xC) = D_0048FA00;
    void* h = *(void**)(s + 0x40);
    if (h != 0) {
        char* mgr = D_004A5B80;
        sFlagSetVEntryCB80* vt = *(sFlagSetVEntryCB80**)(mgr + 0x10D8);
        vt[77].fn(mgr + vt[77].delta, h);
    }
    func_0034FBF0(self, flags);
}

//100%
extern "C" void* cInstanceNode_cInstanceNode(void* self, void* a1, void* stream);
extern "C" void func_0034D1E8(void* self);
extern void* D_0048FA00[];

struct sFlagSetVEntry_CBE8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

struct sFlagElem_CBE8 {
    float v[4];
    sFlagElem_CBE8() {}
    void* operator new[](unsigned int, void* p) { return p; }
};

INCLUDE_ASM("object/flagset", func_0034CBE8);
extern "C" void* func_0034CBE8(void* self, void* a1, void* stream);

//100% - objdiff report; single-function view differs only in a relocation name
class cFlagObj_CC80 {
public:
    int f0, f4, f8;
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual int isA(int type);
};

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void Fence_ctor(void* self, int a1, void* obj, void* pos, int flag, float force);
extern "C" void func_0034CDE8(void* self, int flag, float force);
extern char D_004A4018[];

// PORT: SN abs.s asm helper (PS2 FPU).
static inline float fabs_34CC80(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

extern "C" void func_0034CC80(char* self, char* obj, int flag)
{
    if (*(int*)(self + 0x40) == 0) {
        return;
    }
    if (obj == 0) {
        return;
    }
    float force;
    if (*(float*)(self + 0x34) < 0.0f) {
        force = *(float*)(self + 0x30) * 0.4f;
    } else {
        force = *(float*)(self + 0x30) * -0.4f;
    }
    cFlagObj_CC80* o = *(cFlagObj_CC80**)(obj + 0xC);
    if (o != 0) {
        if (o->isA(9) == 0) {
            return;
        }
        if (!(0.25f <= fabs_34CC80(force))) {
            return;
        }
        if (flag != 0) {
            char* p = *(char**)(self + 0x104);
            if (p == 0) {
                return;
            }
            void* q = *(void**)(p + 0xC);
            if (q == 0) {
                return;
            }
            func_0034CDE8(q, flag, force);
        } else {
            char* p = *(char**)(self + 0x108);
            if (p == 0) {
                return;
            }
            void* q = *(void**)(p + 0xC);
            if (q == 0) {
                return;
            }
            func_0034CDE8(q, 0, force);
        }
    } else if (0.25f <= fabs_34CC80(force)) {
        void* m = cMemMan_alloc(0x10C, D_004A4018, 0x20000000, 0);
        Fence_ctor(m, 1, obj, self + 0x1C, flag, force);
    }
}

//100%
extern "C" void func_0034D6F0(void* self, float dt);

extern "C" void func_0034CDE8(void* self, int on, float dt)
{
    func_0034D6F0(self, dt);
    if (on) {
        if (*(int*)((char*)self + 0x38) == 0) {
            *(int*)((char*)self + 0x38) = 4;
        }
    } else {
        if (*(int*)((char*)self + 0x3C) == 0) {
            *(int*)((char*)self + 0x3C) = 4;
        }
    }
}

//100%
extern "C" void func_0034CC80(char* self, char* obj, int flag);
extern "C" void func_0034CF98(void* self);

struct sFlagVE_34CE48 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

// PORT: SN abs.s asm helper (PS2 FPU).
static inline float fabs_34CE48(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

extern "C" void func_0034CE48(char* self)
{
    if (*(int*)(self + 0x38) > 0) {
        if (--*(int*)(self + 0x38) == 0) {
            func_0034CC80(self, *(char**)(self + 0x104), 1);
        }
    }
    if (*(int*)(self + 0x3C) > 0) {
        if (--*(int*)(self + 0x3C) == 0) {
            func_0034CC80(self, *(char**)(self + 0x108), 0);
        }
    }
    char* osc = self + 0x1C;
    *(float*)(self + 0x2C) += *(float*)(self + 0x34);
    if (*(float*)(self + 0x30) < 0.01f && fabs_34CE48(*(float*)(osc + 0x10)) < 0.01f) {
        sFlagVE_34CE48* vt = *(sFlagVE_34CE48**)(self + 0xC);
        vt[34].fn(self + vt[34].delta, 1);
        return;
    }
    if (0.0f <= *(float*)(self + 0x34)) {
        if (*(float*)(self + 0x2C) >= *(float*)(self + 0x30)) {
            float a = *(float*)(self + 0x30);
            *(float*)(self + 0x2C) = a;
            float h = a * 0.5f;
            *(float*)(self + 0x30) = h;
            *(float*)(self + 0x34) = -h * 0.1f;
        }
    } else {
        float a = *(float*)(self + 0x30);
        float na = -a;
        if (*(float*)(self + 0x2C) <= na) {
            *(float*)(self + 0x2C) = na;
            float h = a * 0.5f;
            *(float*)(self + 0x30) = h;
            *(float*)(self + 0x34) = h * 0.1f;
        }
    }
    func_0034CF98(self);
}

//100%
extern float D_0044AFD0[];

struct sFsVec4_CF98 {
    float x, y, z, w;
    sFsVec4_CF98() {}
    sFsVec4_CF98(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

struct sFsVec3_CF98 {
    float x, y, z;
    sFsVec3_CF98() {}
    sFsVec3_CF98(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

// PORT: VU0 macro-mode vector scale in place (v *= s).
static inline void fsScaleIn_CF98(sFsVec4_CF98& v, float s)
{
    __asm__(
        "mfc1       $2, %2\n"
        "lqc2       $vf4, 0x0(%1)\n"
        "qmtc2.ni   $2, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2       $vf5, 0x0(%1)\n"
        : "=m"(v)
        : "r"(&v), "f"(s)
        : "$2");
}

// PORT: VU0 macro-mode vector scale (a * s).
static inline sFsVec4_CF98 fsScale_CF98(const sFsVec4_CF98& a, float s)
{
    sFsVec4_CF98 r;
    __asm__(
        "mfc1       $2, %2\n"
        "lqc2       $vf4, 0x0(%1)\n"
        "qmtc2.ni   $2, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2       $vf5, %0\n"
        : "=m"(r)
        : "r"(&a), "f"(s)
        : "$2");
    return r;
}

static inline sFsVec3_CF98 fsAdd_CF98(const sFsVec3_CF98& a, const sFsVec4_CF98& b)
{
    return sFsVec3_CF98(a.x + b.x, a.y + b.y, a.z + b.z);
}

struct sFlagVEntry_CF98 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

struct sFlagMesh_CF98 {
    int pad0;
    sFlagVEntry_CF98* vt;   // 0x4
};

struct sFlagSet_CF98 {
    char pad0[0x20];
    int mode;               // 0x20
    float scale;            // 0x24
    char pad28[0x4];
    float wind;             // 0x2C
    char pad30[0x10];
    sFlagMesh_CF98* mesh;   // 0x40
    sFsVec3_CF98 top[8];    // 0x44
    sFsVec3_CF98 bottom[8]; // 0xA4
};

INCLUDE_ASM("object/flagset", func_0034CF98);
extern "C" void func_0034CF98(void* p);

//100%
extern char* D_004A5B80;
extern "C" void func_0034CF98(void* self);

struct sFsV3_D1E8 {
    float x, y, z;
    sFsV3_D1E8() {}
    sFsV3_D1E8(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

struct sFsV2_D1E8 {
    float x, y;
    sFsV2_D1E8() {}
    sFsV2_D1E8(float ax, float ay) : x(ax), y(ay) {}
};

struct sFsCol_D1E8 {
    float a, r, g, b;
    sFsCol_D1E8() {}
};

inline sFsV3_D1E8 operator+(const sFsV3_D1E8& a, const sFsV3_D1E8& b) { return sFsV3_D1E8(a.x + b.x, a.y + b.y, a.z + b.z); }
inline sFsV3_D1E8 operator-(const sFsV3_D1E8& a, const sFsV3_D1E8& b) { return sFsV3_D1E8(a.x - b.x, a.y - b.y, a.z - b.z); }
inline sFsV3_D1E8 operator*(const sFsV3_D1E8& a, float s) { return sFsV3_D1E8(a.x * s, a.y * s, a.z * s); }
inline sFsV2_D1E8 operator+(const sFsV2_D1E8& a, const sFsV2_D1E8& b) { return sFsV2_D1E8(a.x + b.x, a.y + b.y); }
inline sFsV2_D1E8 operator-(const sFsV2_D1E8& a, const sFsV2_D1E8& b) { return sFsV2_D1E8(a.x - b.x, a.y - b.y); }
inline sFsV2_D1E8 operator*(const sFsV2_D1E8& a, float s) { return sFsV2_D1E8(a.x * s, a.y * s); }

struct sFsVE_D1E8 {
    short delta;
    short index;
    void* (*fn)(void*, int, int, unsigned int);
};

struct sFsQuadVE_D1E8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int, sFsV3_D1E8*, sFsV2_D1E8*, sFsCol_D1E8*);
};

struct sFsMeshVE_D1E8 {
    short delta;
    short index;
    void (*fn)(void*, sFsV3_D1E8*, sFsCol_D1E8*, sFsV2_D1E8*);
};

struct sFsMesh_D1E8 {
    int pad0;
    sFsMeshVE_D1E8* vt;   // 0x4
};

struct sFsNode_D1E8 {
    char pad0[0x8];
    unsigned int flags;   // 0x8
};

struct sFlagSet_D1E8 {
    char pad0[0x18];
    sFsNode_D1E8* node;     // 0x18
    char pad1C[0x24];
    sFsMesh_D1E8* mesh;     // 0x40
    sFsV3_D1E8 top[8];      // 0x44
    sFsV3_D1E8 bottom[8];   // 0xA4
    void* obj104;           // 0x104
    void* obj108;           // 0x108
};

INCLUDE_ASM("object/flagset", func_0034D1E8);
extern "C" void func_0034D1E8(void* p);

//100%
extern "C" void func_0034D6F0(void* self, float dt);

struct sFsVec4_D650 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float fsDot_D650(const sFsVec4_D650& a, const sFsVec4_D650& b)
{
    float r;
    int t;
    __asm__(
        "lqc2      $vf3, %2\n"
        "lqc2      $vf5, %3\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf5\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "qmfc2.ni  %1, $vf4\n"
        "mtc1      %1, %0\n"
        : "=f"(r), "=&r"(t)
        : "m"(a), "m"(b));
    return r;
}

extern "C" void Fence_v40(void* self, void* obj)
{
    char* s = (char*)self;
    char* o = (char*)obj;
    if (*(float*)(s + 0x30) >= 1.0f) return;
    float d = fsDot_D650(*(sFsVec4_D650*)(o + 0x20), *(sFsVec4_D650*)(o + 0x10));
    func_0034D6F0(self, d * 0.0010000000474974513f * *(float*)(o + 0x30));
    if (*(int*)(s + 0x38) == 0) *(int*)(s + 0x38) = 4;
    if (*(int*)(s + 0x3C) == 0) *(int*)(s + 0x3C) = 4;
}

INCLUDE_ASM("object/flagset", func_0034D6F0);

//100%
extern "C" void func_0034D778(char* self)
{
    if (!IsLoaded_34B9B0(*(sModel_34B9B0**)(self + 0x18))) {
        return;
    }
    char* ctx = D_004A5B80;
    float one = 1.0f;
    {
        sModel_34B9B0* m = *(sModel_34B9B0**)(self + 0x18);
        sVE93_34B9B0* vt = *(sVE93_34B9B0**)(ctx + 0x10D8);
        char* thisp = ctx + vt[93].delta;
        sVec4_34B9B0 a(*(float*)((char*)m + 0x60), *(float*)((char*)m + 0x64), *(float*)((char*)m + 0x68), one);
        sVec4_34B9B0 b(*(float*)((char*)m + 0x6C), *(float*)((char*)m + 0x70), *(float*)((char*)m + 0x74), one);
        sVec4_34B9B0* pb = &b;
        sVE43_34B9B0* vt43 = *(sVE43_34B9B0**)(ctx + 0x10D8);
        sPair_34B9B0 c = vt43[43].fn(ctx + vt43[43].delta);
        if (vt[93].fn(thisp, &a, pb, &c) == 1) {
            return;
        }
    }
    TOP_34B9B0(ctx)[1] = TOP_34B9B0(ctx)[0];
    sRS_34B9B0* t = TOP_34B9B0(ctx);
    TOP_34B9B0(ctx) = t + 1;
    ((int*)t)[6] = (((int*)t)[6] & ~0x7C) | 0x14;
    sModel_34B9B0* m = *(sModel_34B9B0**)(self + 0x18);
    char* pos = (char*)m + 0x10;
    char* h = *(char**)(self + 0x40);
    if (h != 0) {
        sVE7_34B9B0* hv = *(sVE7_34B9B0**)(h + 4);
        hv[7].fn(h + hv[7].delta, pos, *(void**)((char*)m + 0x94), 0);
    } else {
        sVE96_34B9B0* v96 = *(sVE96_34B9B0**)(ctx + 0x10D8);
        v96[96].fn(ctx + v96[96].delta, m, 0, 0, 0);
    }
    TOP_34B9B0(ctx)--;
}

//100%
struct sSerVEntry_0034D960 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void func_0034FE90(void* self, void* stream);

extern "C" void func_0034D960(void* self, void* stream)
{
    func_0034FE90(self, stream);
    sSerVEntry_0034D960* vt = *(sSerVEntry_0034D960**)stream;
    vt[1].fn((char*)stream + vt[1].delta, (char*)self + 0x1C, 0x24);
}

//100%
extern "C" void* func_00355280(void* self, void* a1, int type, void* a3);
extern "C" void cAnimNode_setAnimMeshCache(void* self);
extern "C" float func_00351508(void* p);
struct sFlagOwner_E348;
extern "C" void cAnimObjectNode_v52(sFlagOwner_E348* self);
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator new[](unsigned int size, const char* tag, unsigned int flags, int d) __asm__("operator_new__FUi");
extern void* D_00490CC8[];
extern char D_0048E758[];

struct sFlagSlot_34D9B0 {
    int v[16];
    sFlagSlot_34D9B0() {}
};

INCLUDE_ASM("object/flagset", func_0034D9B0);
extern "C" void* func_0034D9B0(char* self, void* a1, int a2, void* a3, int force);

INCLUDE_ASM("object/flagset", func_0034DAC8);

//100%
struct sFlagVEntry_DBA8 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sFlagItem_DBA8 {
    char pad_0x0[0x84];
    sFlagVEntry_DBA8* vt;       // 0x84
    char pad_0x88[0x48];
};

struct sFlagOwner_DBA8 {
    char pad_0x0[0x14];
    char node[0xC];             // 0x14
    void** vtable;              // 0x20
    char pad_0x24[0x20];
    void* cache;                // 0x44
    sFlagItem_DBA8* items;      // 0x48, array-new block (count at -0x10)
    void* buf;                  // 0x4C
};

void cMemMan_free(void*);
void operator_delete(int*);
extern "C" void func_003553C0(void* self, int flags);
extern void* D_00490CC8[];

extern "C" void func_0034DBA8(sFlagOwner_DBA8* self, int flags)
{
    self->vtable = D_00490CC8;
    if (self->cache != 0) {
        cMemMan_free(self->cache);
    }
    sFlagItem_DBA8* items = self->items;
    if (items != 0) {
        sFlagItem_DBA8* p = items + ((int*)items)[-4];
        while (self->items != p) {
            p--;
            p->vt[1].fn((char*)p + p->vt[1].delta, 0);
        }
        cMemMan_free((char*)self->items - 0x10);
    }
    if (self->buf != 0) {
        cMemMan_free(self->buf);
    }
    func_003553C0(self->node, 0);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
struct sFlagSetVEntry_DC90a {
    short delta;
    short index;
    void (*fn)(void*);
};

struct sFlagSetVEntry_DC90b {
    short delta;
    short index;
    void* (*fn)(void*);
};

struct sFlagSetVEntry_DC90c {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cAnimObjectNode_v51(void* self)
{
    sFlagSetVEntry_DC90a* vt = *(sFlagSetVEntry_DC90a**)((char*)self + 0x20);
    vt[52].fn((char*)self + vt[52].delta);
    char* sub = (char*)self + 0x14;
    sFlagSetVEntry_DC90c* vt2 = *(sFlagSetVEntry_DC90c**)((char*)self + 0x20);
    void* objB = sub + vt2[33].delta;
    void* r = ((sFlagSetVEntry_DC90b*)vt2)[24].fn(sub + vt2[24].delta);
    vt2[33].fn(objB, r, *(int*)((char*)self + 0x44));
    *(unsigned short*)((char*)self + 0x26) &= ~1;
}

INCLUDE_ASM("object/flagset", cAnimObjectNode_BuildMatrices);

//100%
extern char D_004FF1A0[];

extern "C" void* func_0034E320(void* self, int i) {
    char* base = *(char**)((char*)self + 0x48);
    if (base == 0) {
        return D_004FF1A0;
    }
    return base + i * 0xD0 + 0x90;
}

//100%
struct sFlagSetVEntry_E348 {
    short delta;
    short index;
    void (*fn)(void*, float);
};

struct sFlagItem_E348 {
    char pad0[0x84];
    sFlagSetVEntry_E348* vt;    // 0x84
    char pad88[0x48];
};

struct sFlagOwner_E348 {
    int field_0x0;
    float time;                 // 0x4
    char pad8[0x8];
    int dirty;                  // 0x10
    char pad14[0x2C];
    int count;                  // 0x40
    int field_0x44;
    sFlagItem_E348* items;      // 0x48
};

extern "C" void cAnimObjectNode_v52(sFlagOwner_E348* self)
{
    int i;
    if (self->items != 0) {
        for (i = 0; i < self->count; i++) {
            // PORT: pointer arithmetic done in int (gives the target's offset-first addu).
            sFlagItem_E348* e = (sFlagItem_E348*)(i * 0xD0 + (int)self->items);
            e->vt[2].fn((char*)e + e->vt[2].delta, self->time);
        }
    }
    self->dirty = 1;
}

//100%
struct sSerVEntry_0034E3D8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void func_00356B30(void* self, void* stream);

extern "C" void func_0034E3D8(void* self, void* stream)
{
    int dummy;
    func_00356B30((char*)self + 0x14, stream);
    sSerVEntry_0034E3D8* e = &(*(sSerVEntry_0034E3D8**)stream)[1];
    e->fn((char*)stream + e->delta, self, 0x14);
    e = &(*(sSerVEntry_0034E3D8**)stream)[1];
    e->fn((char*)stream + e->delta, &dummy, 4);
}

