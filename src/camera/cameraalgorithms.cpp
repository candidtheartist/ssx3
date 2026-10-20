#include "common.h"

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
struct sVec4_15D088 { float x, y, z, w; } __attribute__((aligned(16)));
extern "C" void* IdleChaseCameraAlgorithm_ctor(void* self);
extern "C" void* MidRightChaseCameraAlgorithm_ctor(void* self);
extern "C" void* MidLeftChaseCameraAlgorithm_ctor(void* self);
extern "C" void* ManualChaseCameraAlgorithm_ctor(void* self);
extern "C" void* LazyChaseCameraAlgorithm_ctor(void* self);
extern "C" void* LookBackChaseCameraAlgorithm_ctor(void* self);
extern "C" void* MatrixChaseCameraAlgorithm_ctor(void* self);
extern "C" void* Default_2ChaseCameraAlgorithm_ctor(void* self);
extern "C" void* Default_4ChaseCameraAlgorithm_ctor(void* self);
extern "C" void* Default_3ChaseCameraAlgorithm_ctor(void* self);
extern "C" void* SpokeChaseCameraAlgorithm_ctor(void* self);
extern "C" void* DirectionChaseCameraAlgorithm_ctor(void* self, int n);
extern "C" void* RelativeChaseCameraAlgorithm_ctor(void* self, float f);
extern "C" void* func_00161060(char* self, float* p0, float* p1, float* p2, float* p3, float dur, float a, float b, float c);
extern "C" void func_00161E58(void* self, void* algo, float w);
extern "C" void* func_00174190(void* self);
extern "C" void* func_00178520(void* self, sVec4_15D088* a, sVec4_15D088* b);
extern "C" void* Post_Race_1ChaseCameraAlgorithm_ctor(char* self, char* src);
extern "C" void func_00170240(sVec4_15D088* out, char* r);
extern "C" void func_001707B0(sVec4_15D088* out, char* r);
extern "C" void func_00170D20(sVec4_15D088* out, char* r, int i);
extern void* D_004A28A8;
extern char D_0045B250[];
extern char D_0045B278[];
extern char D_0045B298[];
extern char D_0045B2B0[];
extern char D_0045B2D8[];
extern char D_0045B300[];
extern char D_0045B328[];
extern char D_0045B348[];
extern char D_0045B370[];
extern char D_0045B390[];
extern char D_0045B3B0[];
extern char D_0045B3D0[];
extern char D_0045B3F8[];
extern char D_0045B420[];
extern char D_0045B448[];
extern char D_0045B470[];
extern char D_0045B498[];
extern char D_0045B4C0[];
extern char D_0045B4E8[];
extern char D_0045B510[];
extern char D_0045B538[];
extern char D_0045B558[];
extern char D_0045B578[];
extern char D_0045B598[];

struct sVE_15D088 { short delta; short index; void (*fn)(void*, ...); };

extern "C" void cChaseCameraController_createChaseAlgorithmBlend(char* self, unsigned int type, char* info, float blend)
{
    char* cam = 0;
    if (*(int*)(self + 0x30) & 2) {
        blend = 1.0f;
    }
    switch (type) {
    case 91: {
        int v = **(int**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28);
        int busy = v != 0 && v < 10;
        if (!busy) {
            char* r = *(char**)(info + 8);
            if (*(int*)(r + 0x28) == 2) {
                void* mem = cMemMan_alloc(0x3B0, D_0045B250, 0x20000000, 0);
                sVec4_15D088 a;
                sVec4_15D088 b;
                func_00170240(&a, r);
                func_001707B0(&b, r);
                cam = (char*)func_00178520(mem, &a, &b);
                break;
            }
        }
        cam = (char*)func_00174190(cMemMan_alloc(0x90, D_0045B278, 0x20000000, 0));
        *(char**)(cam + 0x80) = info;
        break;
    }
    case 92: {
        char* r = *(char**)(info + 8);
        void* mem = cMemMan_alloc(0x3D0, D_0045B298, 0x20000000, 0);
        sVec4_15D088 p0;
        sVec4_15D088 p1;
        sVec4_15D088 p2;
        sVec4_15D088 p3;
        func_00170D20(&p0, r, 0);
        func_00170D20(&p1, r, 1);
        func_00170D20(&p2, r, 2);
        func_00170D20(&p3, r, 3);
        cam = (char*)func_00161060((char*)mem, (float*)&p0, (float*)&p1, (float*)&p2, (float*)&p3, *(float*)(info + 0x18), *(float*)(info + 0x14), *(float*)(info + 0x1C), *(float*)(info + 0x10));
        break;
    }
    case 7:
        cam = (char*)IdleChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B328, 0x20000000, 0));
        break;
    case 9:
        cam = (char*)MidRightChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B348, 0x20000000, 0));
        break;
    case 10:
        cam = (char*)MidLeftChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B370, 0x20000000, 0));
        break;
    case 11:
        cam = (char*)ManualChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B390, 0x20000000, 0));
        break;
    case 13:
        cam = (char*)LazyChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B3B0, 0x20000000, 0));
        break;
    case 18:
        cam = (char*)DirectionChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B3D0, 0x20000000, 0), 0);
        break;
    case 19:
        cam = (char*)DirectionChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B3F8, 0x20000000, 0), 1);
        break;
    case 20:
        cam = (char*)DirectionChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B420, 0x20000000, 0), 2);
        break;
    case 21:
        cam = (char*)DirectionChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B448, 0x20000000, 0), 3);
        break;
    case 22:
        cam = (char*)DirectionChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B470, 0x20000000, 0), 4);
        break;
    case 23:
        cam = (char*)DirectionChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B498, 0x20000000, 0), 5);
        break;
    case 24:
        cam = (char*)DirectionChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B4C0, 0x20000000, 0), 6);
        break;
    case 25:
        cam = (char*)DirectionChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B4E8, 0x20000000, 0), 7);
        break;
    case 32:
        cam = (char*)LookBackChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B510, 0x20000000, 0));
        break;
    case 41:
        cam = (char*)MatrixChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B538, 0x20000000, 0));
        break;
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
        {
            float ang = (float)(int)(type - 0x21) * 0.7853982f;
            cam = (char*)RelativeChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3C0, D_0045B558, 0x20000000, 0), ang);
        }
        *(int*)(cam + 0xC) = type;
        break;
    case 2:
    case 60:
        cam = (char*)Default_2ChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B2D8, 0x20000000, 0));
        break;
    case 1:
    case 62:
        cam = (char*)Default_4ChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B300, 0x20000000, 0));
        break;
    case 0:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
    case 12:
    case 14:
    case 15:
    case 16:
    case 17:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 61:
    case 63:
    case 64:
    case 65:
    case 74:
        cam = (char*)Default_3ChaseCameraAlgorithm_ctor(cMemMan_alloc(0x390, D_0045B2B0, 0x20000000, 0));
        break;
    case 66:
        cam = (char*)SpokeChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3A0, D_0045B578, 0x20000000, 0));
        break;
    case 67:
        cam = 0;
        break;
    case 68:
        cam = (char*)Post_Race_1ChaseCameraAlgorithm_ctor((char*)cMemMan_alloc(0x3B0, D_0045B598, 0x20000000, 0), *(char**)(self + 0x20));
        break;
    case 94:
        cam = (char*)RelativeChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3C0, D_0045B558, 0x20000000, 0), -0.3926991f);
        *(int*)(cam + 0xC) = type;
        break;
    case 95:
        cam = (char*)RelativeChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3C0, D_0045B558, 0x20000000, 0), 0.3926991f);
        *(int*)(cam + 0xC) = type;
        break;
    case 96:
        cam = (char*)RelativeChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3C0, D_0045B558, 0x20000000, 0), -2.3561945f);
        *(int*)(cam + 0xC) = type;
        break;
    case 97:
        cam = (char*)RelativeChaseCameraAlgorithm_ctor(cMemMan_alloc(0x3C0, D_0045B558, 0x20000000, 0), 2.3561945f);
        *(int*)(cam + 0xC) = type;
        break;
    }
    {
        sVE_15D088* vt = *(sVE_15D088**)(cam + 0x10);
        vt[12].fn(cam + vt[12].delta, *(void**)(self + 0x20));
    }
    func_00161E58(self, cam, blend);
    {
        sVE_15D088* vt = *(sVE_15D088**)(cam + 0x10);
        vt[4].fn(cam + vt[4].delta);
    }
}

//100%
struct func_0015D698_sVec4 { float x, y, z, w; } __attribute__((aligned(16)));

extern void* D_0045B8B0[];
extern func_0015D698_sVec4 D_004FF140;

extern "C" void* func_0015D698(void* self)
{
    func_0015D698_sVec4 v;
    *(void***)((char*)self + 0x90) = D_0045B8B0;
    v.x = 0; v.y = 0; v.z = 0; v.w = 0;
    *(func_0015D698_sVec4*)((char*)self + 0x20) = v;
    v.w = 1.0f;
    v.x = 0;
    v.y = 1.0f;
    v.z = 0;
    *(func_0015D698_sVec4*)((char*)self + 0x30) = v;
    *(func_0015D698_sVec4*)((char*)self + 0x80) = D_004FF140;
    return self;
}

//100%
extern "C" void* func_0015D928(void* self);

extern "C" void func_0015D700(void* self, float x, float y, float z)
{
    func_0015D698_sVec4 v;
    *(float*)((char*)self + 0xC) = x;
    *(float*)((char*)self + 0x10) = y;
    *(float*)((char*)self + 0x14) = z;
    *(float*)((char*)self + 0x0) = x;
    *(float*)((char*)self + 0x4) = y;
    *(float*)((char*)self + 0x8) = z;
    v.x = 0; v.y = 0; v.z = 0; v.w = 0;
    *(func_0015D698_sVec4*)((char*)self + 0x20) = v;
    v.w = 1.0f;
    v.x = 0;
    v.y = 1.0f;
    v.z = 0;
    *(func_0015D698_sVec4*)((char*)self + 0x30) = v;
    *(func_0015D698_sVec4*)((char*)self + 0x80) = D_004FF140;
    func_0015D928(self);
}

INCLUDE_ASM("camera/cameraalgorithms", func_0015D780);

INCLUDE_ASM("camera/cameraalgorithms", func_0015D880);

//100%
struct sV_D928 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sM_D928 {
    float m[4][4];
} __attribute__((aligned(16)));

extern char D_004C53A0[];

// PORT: PS2-only VU0 inline asm (64-byte matrix copy).
static inline void vu0CopyMtx_D928(void* dst, void* src)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2      $vf1, 0x0(%1)\n"
        "lqc2      $vf2, 0x10(%1)\n"
        "lqc2      $vf3, 0x20(%1)\n"
        "lqc2      $vf4, 0x30(%1)\n"
        "sqc2      $vf1, 0x0(%0)\n"
        "sqc2      $vf2, 0x10(%0)\n"
        "sqc2      $vf3, 0x20(%0)\n"
        "sqc2      $vf4, 0x30(%0)\n"
        ".set reorder\n"
        :
        : "r"(dst), "r"(src)
        : "memory");
}

// PORT: PS2-only VU0 inline asm (4x4 matrix multiply, dst = a * b).
static inline void vu0MulMtx_D928(void* dst, void* a, void* b)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2      $vf4, 0x0(%1)\n"
        "lqc2      $vf5, 0x10(%1)\n"
        "lqc2      $vf6, 0x20(%1)\n"
        "lqc2      $vf7, 0x30(%1)\n"
        "lqc2      $vf8, 0x0(%2)\n"
        "lqc2      $vf9, 0x10(%2)\n"
        "lqc2      $vf10, 0x20(%2)\n"
        "lqc2      $vf11, 0x30(%2)\n"
        "vmulax.xyzw  ACC, $vf4, $vf8x\n"
        "vmadday.xyzw ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw  $vf12, $vf7, $vf8w\n"
        "vmulax.xyzw  ACC, $vf4, $vf9x\n"
        "vmadday.xyzw ACC, $vf5, $vf9y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf9z\n"
        "vmaddw.xyzw  $vf13, $vf7, $vf9w\n"
        "vmulax.xyzw  ACC, $vf4, $vf10x\n"
        "vmadday.xyzw ACC, $vf5, $vf10y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf10z\n"
        "vmaddw.xyzw  $vf14, $vf7, $vf10w\n"
        "vmulax.xyzw  ACC, $vf4, $vf11x\n"
        "vmadday.xyzw ACC, $vf5, $vf11y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf11z\n"
        "vmaddw.xyzw  $vf15, $vf7, $vf11w\n"
        "sqc2      $vf12, 0x0(%0)\n"
        "sqc2      $vf13, 0x10(%0)\n"
        "sqc2      $vf14, 0x20(%0)\n"
        "sqc2      $vf15, 0x30(%0)\n"
        ".set reorder\n"
        :
        : "r"(dst), "r"(a), "r"(b)
        : "memory");
}

// PORT: PS2-only VU0 inline asm (unit quaternion -> rotation matrix, row 3 = identity).
static inline void vu0QuatToMtx_D928(void* m, const sV_D928& q)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2       $vf4, %1\n"
        "vaddw.xyz  $vf1, $vf0, $vf0w\n"
        "vadd.xyz   $vf5, $vf4, $vf4\n"
        "vsub.w     $vf10, $vf10, $vf10\n"
        "vsub.w     $vf11, $vf11, $vf11\n"
        "vsub.w     $vf12, $vf12, $vf12\n"
        "vmul.xyz   $vf6, $vf5, $vf4\n"
        "vmulw.xyz  $vf7, $vf5, $vf4w\n"
        "vopmula.xyz ACC, $vf5, $vf4\n"
        "vmadd.xyz  $vf8, $vf0, $vf0\n"
        "vsubay.x   ACC, $vf1, $vf6y\n"
        "vmsubz.x   $vf10, $vf1, $vf6z\n"
        "vsubaz.y   ACC, $vf1, $vf6z\n"
        "vmsubx.y   $vf11, $vf1, $vf6x\n"
        "vsubax.z   ACC, $vf1, $vf6x\n"
        "vmsuby.z   $vf12, $vf1, $vf6y\n"
        "vaddaz.y   ACC, $vf0, $vf8z\n"
        "vmaddz.y   $vf10, $vf1, $vf7z\n"
        "vaddax.z   ACC, $vf0, $vf8x\n"
        "vmaddx.z   $vf11, $vf1, $vf7x\n"
        "vaddax.y   ACC, $vf0, $vf8x\n"
        "vmsubx.y   $vf12, $vf1, $vf7x\n"
        "vadday.z   ACC, $vf0, $vf8y\n"
        "vmsuby.z   $vf10, $vf1, $vf7y\n"
        "vaddaz.x   ACC, $vf0, $vf8z\n"
        "vmsubz.x   $vf11, $vf1, $vf7z\n"
        "vadday.x   ACC, $vf0, $vf8y\n"
        "vmaddy.x   $vf12, $vf1, $vf7y\n"
        "sqc2       $vf0, 0x30(%0)\n"
        "sqc2       $vf10, 0x0(%0)\n"
        "sqc2       $vf11, 0x10(%0)\n"
        "sqc2       $vf12, 0x20(%0)\n"
        ".set reorder\n"
        :
        : "r"(m), "m"(q)
        : "memory");
}

// PORT: PS2-only VU0 inline asm (row 3 of m = m * v).
static inline void vu0TransMtx_D928(void* m, const sV_D928& v)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2         $vf4, 0x0(%0)\n"
        "lqc2         $vf5, 0x10(%0)\n"
        "lqc2         $vf6, 0x20(%0)\n"
        "lqc2         $vf7, 0x30(%0)\n"
        "lqc2         $vf8, %1\n"
        "vmulax.xyzw  ACC, $vf4, $vf8x\n"
        "vmadday.xyzw ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw  $vf12, $vf7, $vf8w\n"
        "sqc2         $vf12, 0x30(%0)\n"
        ".set reorder\n"
        :
        : "r"(m), "m"(v)
        : "memory");
}

extern "C" void func_0015D928_impl(void* self) __asm__("func_0015D928");
extern "C" void func_0015D928_impl(void* self)
{
    char* view = (char*)self + 0x40;
    vu0CopyMtx_D928(view, D_004C53A0);
    sM_D928 rot;
    vu0QuatToMtx_D928(&rot, *(sV_D928*)((char*)self + 0x30));
    vu0MulMtx_D928(view, view, &rot);
    sV_D928 t;
    sV_D928 neg;
    sV_D928 pos;
    pos.x = *(float*)((char*)self + 0x20);
    pos.y = *(float*)((char*)self + 0x24);
    pos.z = *(float*)((char*)self + 0x28);
    neg.x = -pos.x;
    neg.y = -pos.y;
    neg.z = -pos.z;
    t.x = neg.x;
    t.y = neg.y;
    t.z = neg.z;
    t.w = 1.0f;
    vu0TransMtx_D928(view, t);
}

//100%
extern void* D_004A28A8;

extern "C" void func_0015DAC0(void)
{
    void* cam = *(void**)((char*)D_004A28A8 + 0x84);
    void* chase = *(void**)((char*)cam + 0x84);
    void* ctrl = *(void**)((char*)chase + 0x4);
    *(int*)((char*)ctrl + 0x4A4) = 1;
}

//100%
// Updates the first camera target and, when there are two or more, the second (virtual slot 4 of each target's object at 0xA8).
class cCamTarget_15DAE0
{
public:
    char pad_0x00[0x14];
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};
struct sCamTargetRef_15DAE0 { char pad[0xA8]; cCamTarget_15DAE0* obj; };
struct sCamTargets_15DAE0 { int count; sCamTargetRef_15DAE0* first; sCamTargetRef_15DAE0* second; };

extern "C" void func_0015DAE0()
{
    sCamTargets_15DAE0* t = *(sCamTargets_15DAE0**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x84);
    int n = t->count;
    t->first->obj->v4();
    if (n >= 2)
        t->second->obj->v4();
}

//100%
extern "C" void func_0016C968(void* self);
void cCameraTriggerMan_setInGameTriggers(void* self);
extern "C" void func_00162170(void* cam);
extern char D_004C5830[];

struct sCamVE_0015DB58 {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void func_0015DB58(void)
{
    func_0016C968(D_004C5830);
    cCameraTriggerMan_setInGameTriggers(D_004C5830);
    char* riders = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x84);
    int n = *(int*)riders;
    func_00162170(*(void**)(*(char**)(riders + 4) + 0xA8));
    char* cam = *(char**)(*(char**)(riders + 4) + 0xA8);
    sCamVE_0015DB58* e = &(*(sCamVE_0015DB58**)(cam + 0x14))[4];
    e->fn(cam + e->delta);
    *(int*)(*(char**)(riders + 4) + 0x460) = 0;
    *(int*)(*(char**)(riders + 4) + 0x4A4) = 1;
    if (n >= 2)
    {
        func_00162170(*(void**)(*(char**)(riders + 8) + 0xA8));
        char* cam2 = *(char**)(*(char**)(riders + 8) + 0xA8);
        sCamVE_0015DB58* e2 = &(*(sCamVE_0015DB58**)(cam2 + 0x14))[4];
        e2->fn(cam2 + e2->delta);
        *(int*)(*(char**)(riders + 8) + 0x460) = 0;
    }
}

