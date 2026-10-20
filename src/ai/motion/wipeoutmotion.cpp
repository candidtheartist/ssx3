#include "common.h"

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void cAirPredictor_startLaunchIntoAir(void* self, void* a, void* b, float t);
struct cRiderSphereTree;
cRiderSphereTree* cRiderSphereTree_cRiderSphereTree(cRiderSphereTree* self);
extern char D_00458210[];

struct sVec4WG {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0DotWG(const sVec4WG& a, const sVec4WG& b)
{
    float r;
    __asm__ __volatile__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf5, %2\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf5\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "qmfc2.ni  %0, $vf4\n"
        : "=r"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4WG vu0ScaleMemWG(const sVec4WG& v, float s)
{
    sVec4WG r;
    int t;
    __asm__ __volatile__(
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

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline void vu0SubWG(sVec4WG& dst, const sVec4WG& a, const sVec4WG& b)
{
    __asm__ __volatile__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(dst)
        : "m"(a), "m"(b));
}

extern "C" void cWipeoutMotion_gainFocus(char* self, int a1)
{
    if (*(void**)(self + 0x44) == 0)
    {
        *(void**)(self + 0x44) = cRiderSphereTree_cRiderSphereTree((cRiderSphereTree*)cMemMan_alloc(0x2B0, D_00458210, 0, 0));
    }
    char* r = *(char**)(self + 0x40);
    sVec4WG* pos = (sVec4WG*)(r + 0x110);
    *(sVec4WG*)(self + 0x50) = *pos;
    *(sVec4WG*)(self + 0x60) = *pos;
    if (a1 == 0)
    {
        sVec4WG* n = (sVec4WG*)(r + 0x370);
        float d = vu0DotWG(*(sVec4WG*)(r + 0x1E0), *n);
        sVec4WG t = vu0ScaleMemWG(*n, d);
        sVec4WG* p = (sVec4WG*)(*(char**)(self + 0x40) + 0x1E0);
        vu0SubWG(*p, *p, t);
        *(int*)self = 0;
    }
    else
    {
        *(int*)self = 1;
        cAirPredictor_startLaunchIntoAir(*(void**)(r + 0x788), pos, r + 0x1E0, 3333.33349609375f);
    }
    *(int*)(self + 0x4) = 0;
    *(int*)(*(char**)(self + 0x40) + 0x2DC) = 0;
    *(int*)(*(char**)(self + 0x40) + 0x2E0) = 0;
}

//100%
struct sVec4WM {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sVecPairWM {
    sVec4WM a;
    sVec4WM b;
};

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0DotWM(const sVec4WM& a, const sVec4WM& b)
{
    float r;
    __asm__ __volatile__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf5, %2\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf5\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "qmfc2.ni  %0, $vf4\n"
        : "=r"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4WM vu0ScaleWM(const sVec4WM& v, float s)
{
    sVec4WM r;
    int t;
    __asm__ __volatile__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline void vu0SubWM(sVec4WM& dst, const sVec4WM& a, const sVec4WM& b)
{
    __asm__ __volatile__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(dst)
        : "m"(a), "m"(b));
}

extern "C" void cWipeoutMotion_detachBoard(char* self, sVec4WM* a, sVec4WM* b, sVecPairWM* c)
{
    *(sVecPairWM*)(*(char**)(self + 0x40) + 0x130) = *c;
    *(int*)(*(char**)(self + 0x40) + 0x150) = 1;
    *(sVec4WM*)(self + 0x20) = *b;
    *(sVec4WM*)(self + 0x10) = *a;
    if (*(int*)self == 0)
    {
        sVec4WM* n = (sVec4WM*)(*(char**)(self + 0x40) + 0x370);
        float d = vu0DotWM(*n, *a);
        sVec4WM t = vu0ScaleWM(*n, d);
        vu0SubWM(*(sVec4WM*)(self + 0x10), *(sVec4WM*)(self + 0x10), t);
    }
}

//100%
extern "C" void cAirPredictor_startLaunchIntoAir(void* self, void* a, void* b, float t);

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4WM vu0ScaleMemWM_136DE0(const sVec4WM& v, float s)
{
    sVec4WM r;
    int t;
    __asm__ __volatile__(
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

extern "C" void cWipeoutMotion_setVelocity(char* self, sVec4WM* a, sVec4WM* b)
{
    *(sVec4WM*)(self + 0x30) = *b;
    *(sVec4WM*)(*(char**)(self + 0x40) + 0x1E0) = *a;
    if (*(int*)self == 0)
    {
        sVec4WM* n = (sVec4WM*)(*(char**)(self + 0x40) + 0x370);
        float d = vu0DotWM(*n, *a);
        sVec4WM t = vu0ScaleMemWM_136DE0(*n, d);
        sVec4WM* p = (sVec4WM*)(*(char**)(self + 0x40) + 0x1E0);
        vu0SubWM(*p, *p, t);
    }
    else
    {
        char* r = *(char**)(self + 0x40);
        cAirPredictor_startLaunchIntoAir(*(void**)(r + 0x788), r + 0x110, r + 0x1E0, 3333.33349609375f);
    }
    *(int*)(self + 0x4) = 0;
}

//100%
extern "C" void cWipeoutMotion_updateBoard();
extern "C" void cWipeoutMotion_updateSliding(void*);
extern "C" void cWipeoutMotion_updateAirborne(void*);

extern "C" void cWipeoutMotion_update(int* self)
{
    cWipeoutMotion_updateBoard();
    if (*self == 0)
    {
        cWipeoutMotion_updateSliding(self);
    }
    else
    {
        cWipeoutMotion_updateAirborne(self);
    }
}

//100%
extern "C" void func_00137138();
extern "C" void cWipeoutMotion_collideSliding(void*);
extern "C" void cWipeoutMotion_collideAirborne(void*);

extern "C" void cWipeoutMotion_postUpdate(int* self)
{
    func_00137138();
    if (*self == 0)
    {
        cWipeoutMotion_collideSliding(self);
    }
    else
    {
        cWipeoutMotion_collideAirborne(self);
    }
}

//100%
void cWipeoutMotion_loseFocus(void* self)
{
}

//100%
struct sVec4_6F30 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sRider_6F30 {
    char pad_0x0[0x130];
    sVec4_6F30 pos;         // 0x130
    sVec4_6F30 quat;        // 0x140
    int active;             // 0x150
    char pad_0x154[0x1AC];
    float rate;             // 0x300
};

struct sWipeout_6F30 {
    char pad_0x0[0x10];
    sVec4_6F30 vel;         // 0x10
    sVec4_6F30 angVel;      // 0x20
    char pad_0x30[0x10];
    sRider_6F30* rider;     // 0x40
};

// PORT: PS2-only VU0 inline asm (vector * scalar).
static inline void vu0Scale_6F30(sVec4_6F30& out, const sVec4_6F30& v, float s)
{
    sVec4_6F30 r;
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
    out = r;
}

// PORT: PS2-only VU0 inline asm (in-place vector * scalar).
static inline void vu0ScaleEq_6F30(sVec4_6F30& v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %2\n"
        "lqc2      $vf4, %0\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "+m"(v), "=&r"(t)
        : "f"(s)
        : "memory");
}

// PORT: PS2-only VU0 inline asm (a += b).
static inline void vu0AddEq_6F30(sVec4_6F30& a, const sVec4_6F30& b)
{
    __asm__(
        "lqc2      $vf3, %0\n"
        "lqc2      $vf4, %1\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "+m"(a)
        : "m"(b)
        : "memory");
}

// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float vu0Length_6F30(const sVec4_6F30& v)
{
    float r;
    int t;
    __asm__(
        "lqc2      $vf3, %2\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vsqrt     Q, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni   %1, $vi22\n"
        "mtc1      %1, %0\n"
        : "=f"(r), "=&r"(t)
        : "m"(v));
    return r;
}

// PORT: PS2-only VU0 inline asm (quaternion derivative 0.5 * (0, w) * q).
static inline void vu0QuatDeriv_6F30(sVec4_6F30& out, const sVec4_6F30& q, const sVec4_6F30& w)
{
    sVec4_6F30 r;
    __asm__(
        "qmtc2.ni  %3, $vf1\n"
        "lqc2      $vf4, %1\n"
        "lqc2      $vf5, %2\n"
        "vsuba.w   ACC, $vf0, $vf0\n"
        "vmsubx.w  $vf2, $vf0, $vf1x\n"
        "vmul.xyz  $vf7, $vf4, $vf5\n"
        "vmulw.xyz $vf3, $vf5, $vf4w\n"
        "vopmula.xyz ACC, $vf5, $vf4\n"
        "vopmsub.xyz $vf6, $vf4, $vf5\n"
        "vmulax.w  ACC, $vf2, $vf7x\n"
        "vmadday.w ACC, $vf2, $vf7y\n"
        "vmaddz.w  $vf8, $vf2, $vf7z\n"
        "vmulax.xyz ACC, $vf3, $vf1x\n"
        "vmaddx.xyz $vf8, $vf6, $vf1x\n"
        "sqc2      $vf8, %0\n"
        : "=m"(r)
        : "m"(q), "m"(w), "r"(0x3F000000)
        : "memory");
    out = r;
}

// PORT: PS2-only VU0 inline asm (in-place normalize).
static inline void vu0NormalizeEq_6F30(sVec4_6F30& v)
{
    __asm__(
        "lqc2      $vf3, %0\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vrsqrt    Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf3, Q\n"
        "sqc2      $vf5, %0\n"
        : "+m"(v)
        :
        : "memory");
}

extern "C" void cWipeoutMotion_updateBoard(sWipeout_6F30* self)
{
    if (self->rider->active == 0) {
        return;
    }
    float dt = self->rider->rate * 0.01666666753590107f;
    sVec4_6F30 tmp;
    vu0Scale_6F30(tmp, self->vel, dt);
    vu0AddEq_6F30(self->rider->pos, tmp);
    sVec4_6F30 v2;
    v2.x = self->vel.x * -0.20000000298023224f;
    v2.y = self->vel.y * -0.20000000298023224f;
    v2.z = -1800.0f;
    v2.w = 0.0f;
    vu0Scale_6F30(tmp, v2, dt);
    vu0AddEq_6F30(self->vel, tmp);
    float len = vu0Length_6F30(self->vel);
    if (3333.33349609375f < len) {
        vu0ScaleEq_6F30(self->vel, 3333.33349609375f / len);
    }
    vu0ScaleEq_6F30(self->angVel, 1.0f - dt * 0.5f);
    vu0QuatDeriv_6F30(v2, self->rider->quat, self->angVel);
    vu0Scale_6F30(tmp, v2, dt);
    sRider_6F30* r = self->rider;
    r->quat.x += tmp.x;
    r->quat.y += tmp.y;
    r->quat.z += tmp.z;
    r->quat.w += tmp.w;
    vu0NormalizeEq_6F30(self->rider->quat);
}

INCLUDE_ASM("ai/motion/wipeoutmotion", func_00137138);

//100%
struct sVec4_7550 {
    float x, y, z, w;
    sVec4_7550() {}
    sVec4_7550(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

struct sQuat_7550 {
    float x, y, z, w;
};

struct sBone_7550 {
    sVec4_7550 pos;     // 0x00
    sQuat_7550 rot;     // 0x10
};

struct sRadii_7550 {
    float r[4];
};
extern const sRadii_7550 D_00458220;

extern "C" void cRiderSphereTree_setSpheres(void* tree, int n, sVec4_7550* pos, float* radii, sVec4_7550* center, float radius);

// PORT: PS2-only VU0 inline asm (non-volatile) (vector times scalar).
static inline sVec4_7550 vu0Scale_7550(const sVec4_7550& v, float s)
{
    sVec4_7550 r;
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

// PORT: PS2-only VU0 inline asm (non-volatile) (vector add).
static inline sVec4_7550 vu0Add_7550(const sVec4_7550& a, const sVec4_7550& b)
{
    sVec4_7550 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (non-volatile) (vector subtract).
static inline sVec4_7550 vu0Sub_7550(const sVec4_7550& a, const sVec4_7550& b)
{
    sVec4_7550 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b)
        : "memory");
    return r;
}

static inline sVec4_7550 xAxis_7550(const sBone_7550* b)
{
    return sVec4_7550(1.0f - 2.0f * (b->rot.y * b->rot.y + b->rot.z * b->rot.z),
                      2.0f * (b->rot.x * b->rot.y + b->rot.w * b->rot.z),
                      2.0f * (b->rot.x * b->rot.z - b->rot.w * b->rot.y),
                      0.0f);
}

INCLUDE_ASM("ai/motion/wipeoutmotion", func_00137550);
extern "C" void func_00137550(char* self);

//100%
extern "C" void cRider_updateOrientationImplicit(void*);
extern "C" void cAirPredictor_update(void* ap, void* pos, void* vel, float dt);
extern "C" void cRider_approachOrientation(void* rider, void* a, void* b, float x, float y);

struct sVec4W7 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (vector times-assign scalar).
static inline void vu0ScaleEqW7(sVec4W7& v, float s)
{
    int t;
    __asm__ __volatile__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(v), "=&r"(t)
        : "m"(v), "f"(s));
}

extern "C" void cWipeoutMotion_updateAirborne(void* p)
{
    char* self = (char*)p;
    char* r = *(char**)(self + 0x40);
    float dt = *(float*)(r + 0x300) * 0.01666666753590107f;
    cAirPredictor_update(*(void**)(r + 0x788), r + 0x110, r + 0x1E0, dt);
    int st = *(int*)(*(char**)(*(char**)(self + 0x40) + 0x788) + 0xAC);
    int ok = 0;
    if (st == 1 || st == 3) ok = 1;
    if (ok)
    {
        char* r2 = *(char**)(self + 0x40);
        char* ap = *(char**)(r2 + 0x788);
        float d = *(float*)(ap + 0x98) - *(float*)(ap + 0xA0);
        float x = *(float*)(r2 + 0x300);
        if (d >= 0.01666666753590107f)
            x /= d;
        else
            x *= 59.999996185302734f;
        char* r3 = *(char**)(self + 0x40);
        float k = 6.632251739501953f;
        cRider_approachOrientation(r3, *(char**)(r3 + 0x788) + 0x20, *(char**)(r3 + 0x788) + 0x10, x, *(float*)(r3 + 0x300) * k);
    }
    vu0ScaleEqW7(*(sVec4W7*)(self + 0x30), 1.0f - dt * 1.5f);
    cRider_updateOrientationImplicit(*(void**)(self + 0x40));
}

INCLUDE_ASM("ai/motion/wipeoutmotion", cWipeoutMotion_collideAirborne);

INCLUDE_ASM("ai/motion/wipeoutmotion", cWipeoutMotion_updateSliding);

INCLUDE_ASM("ai/motion/wipeoutmotion", cWipeoutMotion_collideSliding);

//100%
extern "C" void* cWorldLine_cWorldLine(void* seg, const sVec4WG& a, const sVec4WG& b, int n, float r);
extern "C" float cOverlapList_queryNearest(void* world, void* seg, void* hit, int flags);

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4WG vu0Scale_138960(const sVec4WG& v, float s)
{
    sVec4WG r;
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

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sVec4WG vu0Sub_138960(const sVec4WG& a, const sVec4WG& b)
{
    sVec4WG r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector add).
static inline sVec4WG vu0Add_138960(const sVec4WG& a, const sVec4WG& b)
{
    sVec4WG r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

struct sVEntry_138960 { short delta; short index; void (*fn)(void*, void*); };

extern "C" float cWipeoutMotion_probeTerrain(void* self, char* hit, sVec4WG* dir)
{
    char* rider = *(char**)((char*)self + 0x40);
    char seg[0xB0];
    sVec4WG* pt = (sVec4WG*)(rider + 0x110);
    cWorldLine_cWorldLine(seg, vu0Sub_138960(*pt, vu0Scale_138960(*dir, 200.0f)), vu0Add_138960(*pt, vu0Scale_138960(*dir, 200.0f)), 2, 0.574999988079071f);
    char* r2 = *(char**)((char*)self + 0x40);
    float d = cOverlapList_queryNearest(*(void**)(r2 + 0x860), seg, hit, *(int*)(r2 + 0x864));
    if (d >= 0.0f)
    {
        char* obj = *(char**)(hit + 0x54);
        if (obj)
        {
            *(int*)(*(char**)((char*)self + 0x40) + 0x430) = *(int*)(obj + 0x150);
            *(float*)(*(char**)((char*)self + 0x40) + 0xAAC) = *(float*)(hit + 0x6C);
            *(float*)(*(char**)((char*)self + 0x40) + 0xAB0) = *(float*)(hit + 0x70);
            *(unsigned short*)(*(char**)((char*)self + 0x40) + 0x2D4) = *(unsigned short*)(*(char**)(hit + 0x54) + 0xA);
        }
        else
        {
            *(unsigned int*)(*(char**)((char*)self + 0x40) + 0x430) = 0xFFFFFFFF;
        }
        char* o = *(char**)(hit + 0x50);
        if (o)
        {
            char* h = *(char**)(o + 0xC);
            if (h)
            {
                sVEntry_138960* vt = *(sVEntry_138960**)(h + 0xC);
                vt[42].fn(h + vt[42].delta, hit);
            }
        }
    }
    return d;
}

//100%
struct sVEntry00138AD8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cWipeoutMotion_writeToReplayFrame(void* self, void* obj)
{
    sVEntry00138AD8* vt = *(sVEntry00138AD8**)obj;
    vt[1].fn((char*)obj + vt[1].delta, self, 0x40);
}

//100%
struct sVEntry00138B10 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cWipeoutMotion_readFromReplayFrame(void* self, void* obj)
{
    sVEntry00138B10* vt = *(sVEntry00138B10**)obj;
    vt[2].fn((char*)obj + vt[2].delta, self, 0x40);
}

