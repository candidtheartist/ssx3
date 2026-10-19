#include "common.h"

//100%
struct sVec4HP {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sVec4HP vu0SubHP(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
    __asm__ __volatile__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector divided by scalar).
static inline sVec4HP vu0DivHP(const sVec4HP& v, float s)
{
    sVec4HP r;
    int t;
    __asm__ __volatile__(
        "mfc1      %1, %3\n"
        "qmtc2.ni  %1, $vf3\n"
        "vdiv      Q, $vf0w, $vf3x\n"
        "lqc2      $vf4, %2\n"
        "vwaitq\n"
        "vmulq.xyzw $vf4, $vf4, Q\n"
        "sqc2      $vf4, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s));
    return r;
}

extern "C" void cHandplantMotion_gainFocus(char* self)
{
    char* rider = *(char**)(self + 0xA0);
    *(sVec4HP*)(rider + 0x1E0) = vu0DivHP(vu0SubHP(*(sVec4HP*)(self + 0x30), *(sVec4HP*)(rider + 0x110)), *(float*)(self + 0x84));
}

INCLUDE_ASM("ai/control/handplantcontrol", func_00138BA0);

typedef int cQuad128_139178 __attribute__((mode(TI)));
extern "C" void func_00139548(void* self);

// Runs func_00139548, then copies the 16-byte vector at +0x10 into the rider (+0xA0) at +0x1E0;
// returns the rider.
extern "C" char* cHandplantMotion_loseFocus(void* self)
{
    func_00139548(self);
    char* rider = *(char**)((char*)self + 0xA0);
    *(cQuad128_139178*)(rider + 0x1E0) = *(cQuad128_139178*)((char*)self + 0x10);
    return rider;
}

INCLUDE_ASM("ai/control/handplantcontrol", cHandplantMotion_update);

extern "C" void* cRider_updateQueryBounds(int, int);

//100%
void* cHandplantMotion_postUpdate(void* self)
{
    return cRider_updateQueryBounds(*(int*)((char*)self + 0xa0), 0);
}

INCLUDE_ASM("ai/control/handplantcontrol", func_00139548);

//100%
struct sVEntry00139970 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cHandplantMotion_writeToReplayFrame(void* self, void* obj)
{
    sVEntry00139970* vt = *(sVEntry00139970**)obj;
    vt[1].fn((char*)obj + vt[1].delta, self, 0xA0);
}

//100%
struct sVEntry001399A8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cHandplantMotion_readFromReplayFrame(void* self, void* obj)
{
    sVEntry001399A8* vt = *(sVEntry001399A8**)obj;
    vt[2].fn((char*)obj + vt[2].delta, self, 0xA0);
}

//100%
extern "C" void cAirPredictor_startLaunchIntoAir(void* self, void* a, void* b, float t);

extern "C" void cAirMotion_gainFocus(void* self, int state)
{
    *(int*)self = state == 5;
    char* r = *(char**)((char*)self + 0x4);
    cAirPredictor_startLaunchIntoAir(*(void**)(r + 0x788), r + 0x110, r + 0x1E0, 3333.33349609375f);
}

//100%
void cAirMotion_loseFocus(void* self)
{
}

//100%
extern "C" void cRider_updateOrientationImplicit(void*);
extern "C" void cAirPredictor_update(void* ap, void* pos, void* vel, float dt);
extern "C" void cRider_approachOrientation(void* rider, void* a, void* b, float x, float y);
extern "C" void cRider_applyWindPush(char* self);
int cRider_getControlState(void* rider);
extern void* D_004A28A8;
extern void* D_004FF120[];

// PORT: PS2-only VU0 inline asm (in-place vector times scalar).
static inline void vu0ScaleEq_139A20(sVec4HP& v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(v), "=&r"(t)
        : "m"(v), "f"(s));
}

// PORT: PS2-only VU0 inline asm (4-component dot product, by-value second operand).
static inline float vu0Dot_139A20(const sVec4HP& a, sVec4HP b)
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

// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_139A20(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

extern "C" void cAirMotion_update(void* p)
{
    char* self = (char*)p;
    cRider_applyWindPush(*(char**)(self + 0x4));
    char* r = *(char**)(self + 0x4);
    cAirPredictor_update(*(void**)(r + 0x788), r + 0x110, r + 0x1E0, *(float*)(r + 0x300) * 0.01666666753590107f);
    char* r1 = *(char**)(self + 0x4);
    {
        sVec4HP up = *(sVec4HP*)(r1 + 0x180);
        *(sVec4HP*)(r1 + 0x370) = up;
    }
    *(sVec4HP*)(*(char**)(self + 0x4) + 0x3D0) = *(sVec4HP*)D_004FF120;
    int st = *(int*)(*(char**)(*(char**)(self + 0x4) + 0x788) + 0xAC);
    int ok = 0;
    if (st == 1 || st == 3) ok = 1;
    if (ok) {
        char* r2 = *(char**)(self + 0x4);
        char* ap = *(char**)(r2 + 0x788);
        int idx = *(int*)(ap + 0x90);
        char* e = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x44) + idx * 0xB0;
        int flag = 0;
        short sf = *(short*)(ap + 0x94);
        if (sf != -1) {
            int m = sf & 8;
            flag = m != 0;
        }
        if (idx != 0x12 && *(int*)(e + 0x44) == 0 && flag) {
            float d = *(float*)(ap + 0x98) - *(float*)(ap + 0xA0);
            float t = *(float*)(r2 + 0x300);
            float x;
            if (d >= 0.01666666753590107f)
                x = t / d;
            else
                x = t * 59.999996185302734f;
            float y = *(float*)(*(char**)(self + 0x4) + 0x300) * 1.396263599395752f;
            if (cRider_getControlState(*(void**)(self + 0x4)) == 5) {
                char* r3 = *(char**)(self + 0x4);
                int big = 1;
                if (!(0.0872664749622345f < absf_139A20(*(float*)(*(char**)(r3 + 0x77C) + 0x258)))) big = 0;
                if (big) {
                    cRider_approachOrientation(r3, *(char**)(r3 + 0x788) + 0x20, D_004FF120, x, y);
                    goto done;
                }
            }
            char* r4 = *(char**)(self + 0x4);
            char* ap4 = *(char**)(r4 + 0x788);
            char* tgt = ap4 + 0x20;
            if (*(float*)(ap4 + 0x28) < 0.30000001192092896f || *(int*)self != 0) {
                sVec4HP v = *(sVec4HP*)(ap4 + 0x10);
                if (vu0Dot_139A20(v, *(sVec4HP*)(r4 + 0x1B0)) < 0.0f) {
                    vu0ScaleEq_139A20(v, -1.0f);
                }
                char* r5 = *(char**)(self + 0x4);
                cRider_approachOrientation(r5, *(char**)(r5 + 0x788) + 0x20, &v, x, y);
            } else {
                cRider_approachOrientation(r4, tgt, D_004FF120, x, y);
            }
        }
    }
done:
    cRider_updateOrientationImplicit(*(void**)(self + 0x4));
}

INCLUDE_ASM("ai/control/handplantcontrol", cAirMotion_postUpdate);

//100%
extern "C" void* func_0032E100(void* seg, const sVec4HP& a, const sVec4HP& b, int n, float r);
extern "C" float func_003342D0(void* world, void* seg, void* hit, int flags);

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4HP vu0Scale_13A7B0(const sVec4HP& v, float s)
{
    sVec4HP r;
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector add).
static inline sVec4HP vu0Add_13A7B0(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sVec4HP vu0Sub_13A7B0(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

struct sVEntry_13A7B0 { short delta; short index; void (*fn)(void*, void*); };

extern "C" float cAirMotion_queryLanding(void* self, char* hit)
{
    char* rider = *(char**)((char*)self + 0x4);
    sVec4HP* pt = (sVec4HP*)(*(char**)(*(char**)(rider + 0x780) + 0x2C) + (*(int*)(rider + 0x8A0) << 5));
    sVec4HP dir = *(sVec4HP*)(rider + 0x180);
    char seg[0xB0];
    func_0032E100(seg, vu0Sub_13A7B0(*pt, vu0Scale_13A7B0(dir, 200.0f)), vu0Add_13A7B0(*pt, vu0Scale_13A7B0(dir, 200.0f)), 2, 0.574999988079071f);
    char* r2 = *(char**)((char*)self + 0x4);
    float d = func_003342D0(*(void**)(r2 + 0x860), seg, hit, *(int*)(r2 + 0x864));
    if (d >= 0.0f)
    {
        char* o = *(char**)(hit + 0x50);
        if (o)
        {
            char* h = *(char**)(o + 0xC);
            if (h)
            {
                sVEntry_13A7B0* vt = *(sVEntry_13A7B0**)(h + 0xC);
                vt[42].fn(h + vt[42].delta, hit);
            }
        }
    }
    return d;
}

//100%
// PORT: cRiderAnimBase_play is declared void elsewhere; callers here match only with an int return.
extern "C" int cRiderAnimBase_play_i(void* self, int anim, int flags, float blend) __asm__("cRiderAnimBase_play");

extern "C" void func_0013A8F8(void* self, float v)
{
    if (v < -2222.22216796875f)
    {
        cRiderAnimBase_play_i(*(void**)(*(char**)((char*)self + 0x4) + 0x784), 0x41, 0, -1.0f);
        *(int*)(*(char**)((char*)self + 0x4) + 0x2DC) = 0;
    }
    else
    {
        cRiderAnimBase_play_i(*(void**)(*(char**)((char*)self + 0x4) + 0x784), 0x40, 0, -1.0f);
    }
}

//100%
extern "C" void cAirMotion_playLandingClip(void* self, float v)
{
    if (v < -2222.22216796875f)
    {
        cRiderAnimBase_play_i(*(void**)(*(char**)((char*)self + 0x4) + 0x784), 0x3F, 0, -1.0f);
        *(int*)(*(char**)((char*)self + 0x4) + 0x2DC) = 0;
    }
    else
    {
        char* r = *(char**)((char*)self + 0x4);
        float pi = 3.1415929794311523f;
        float a = *(float*)(r + 0x2DC);
        if (a < -pi)
            cRiderAnimBase_play_i(*(void**)(r + 0x784), 0x42, 0, -1.0f);
        else if (a > pi)
            cRiderAnimBase_play_i(*(void**)(r + 0x784), 0x43, 0, -1.0f);
        else if (v < -1250.0f)
            cRiderAnimBase_play_i(*(void**)(r + 0x784), 0x3E, 0, -1.0f);
        else
            cRiderAnimBase_play_i(*(void**)(r + 0x784), 0x3D, 0, -1.0f);
    }
}

INCLUDE_ASM("ai/control/handplantcontrol", func_0013AA48);

//100%
struct sVEntry0013ACB0 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cAirMotion_writeToReplayFrame(void* self, void* obj)
{
    sVEntry0013ACB0* vt = *(sVEntry0013ACB0**)obj;
    vt[1].fn((char*)obj + vt[1].delta, self, 0x4);
}

//100%
struct sVEntry0013ACE8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cAirMotion_readFromReplayFrame(void* self, void* obj)
{
    sVEntry0013ACE8* vt = *(sVEntry0013ACE8**)obj;
    vt[2].fn((char*)obj + vt[2].delta, self, 0x4);
}

//100%
extern "C" void cRider_updateOrientationImplicit(void*);
extern "C" void cRider_doLeanPoseAdjust(void* self, void* q);
struct sQuadHP_0013AD20 { float x, y, z, w; } __attribute__((aligned(16)));

extern "C" void cRailSlideMotion_gainFocus(void* self)
{
    char* s = (char*)self;
    char* r = *(char**)(s + 0x50);
    cRider_doLeanPoseAdjust(r, r + 0x110);
    cRider_updateOrientationImplicit(*(void**)(s + 0x50));
    char* a = *(char**)(s + 0x50);
    // G1
    *(float*)(a + 0x1F8) = 0.0f;
    *(float*)(a + 0x1F0) = 0.0f;
    *(float*)(a + 0x1F4) = 0.0f;
    // E1
    char* b = *(char**)(s + 0x50);
    *(float*)(b + 0x210) = 0.0f;
    *(float*)(b + 0x208) = 0.0f;
    *(float*)(b + 0x20C) = 0.0f;
    char* c = *(char**)(s + 0x50);
    *(float*)(c + 0x258) = 0.0f;
    *(float*)(c + 0x250) = 0.0f;
    *(float*)(c + 0x254) = 0.0f;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(*(char**)(s + 0x50) + 0x2DC) = 0;
    char* d = *(char**)(s + 0x50);
    *(float*)(d + 0x260) = 0.05000000447034836f;
    *(int*)(d + 0x264) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x1C) = 0;
    *(sQuadHP_0013AD20*)(s + 0x30) = *(sQuadHP_0013AD20*)(*(char**)(s + 0x50) + 0x110);
    *(int*)(s + 0x40) = 0;
}

extern "C" sVec4HP cRailSlideMotion_computeContactNormal(void* self, sVec4HP* p);
extern "C" float func_0031C228(float); // atan

// PORT: PS2-only VU0 inline asm (3D cross product, w = 0).
static inline sVec4HP vu0Cross_13ADC0(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
    __asm__(
        "lqc2      $vf4, %1\n"
        "lqc2      $vf5, %2\n"
        "vopmula.xyz ACC, $vf4, $vf5\n"
        "vopmsub.xyz $vf6, $vf5, $vf4\n"
        "vsub.w    $vf6, $vf6, $vf6\n"
        "sqc2      $vf6, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component dot product, by-value first operand).
static inline float vu0DotV_13ADC0(sVec4HP a, const sVec4HP& b)
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

// atan2(y, x) built on a single-argument atan.
static inline float Atan2_13ADC0(float y, float x)
{
    if (x == 0.0f)
    {
        if (y == 0.0f)
            return y;
        return y >= 0.0f ? 1.5707964f : -1.5707964f;
    }
    float r = func_0031C228(y / x);
    if (x < 0.0f)
    {
        if (y > 0.0f)
            r += 3.1415927f;
        else
            r -= 3.1415927f;
    }
    return r;
}

static inline float Clamp_13ADC0(float x, float lo, float hi)
{
    return (lo <= x) ? (x <? hi) : lo;
}

// Signed angle (clamped to +-45 degrees) between the rider's velocity at +0x1B0 and the target direction p.
extern "C" void cRailSlideMotion_computeHeadingOffset(char* self, sVec4HP* p)
{
    sVec4HP v = cRailSlideMotion_computeContactNormal(self, p);
    sVec4HP c = vu0Cross_13ADC0(v, *p);
    char* rider = *(char**)(self + 0x50);
    *(float*)(self + 0x1C) = Atan2_13ADC0(vu0DotV_13ADC0(*(sVec4HP*)(rider + 0x1B0), c),
                                          vu0DotV_13ADC0(*(sVec4HP*)(rider + 0x1B0), *p));
    float lim = 0.7853982448577881f;
    *(float*)(self + 0x1C) = Clamp_13ADC0(*(float*)(self + 0x1C), -lim, lim);
}

INCLUDE_ASM("ai/control/handplantcontrol", cRailSlideMotion_update);

INCLUDE_ASM("ai/control/handplantcontrol", cRailSlideMotion_computeContactNormal);

//100%
extern "C" void func_00114298(void* rider, float v);
// PORT: cRider_updateQueryBounds is declared void* in this unit; this caller ignores the result (void call).
extern "C" void cRider_updateQueryBounds_v(void* rider, int a1) __asm__("cRider_updateQueryBounds");
extern "C" void func_00105398(void* rider, int a1);
extern "C" void func_00107888(void* rider);
extern "C" void func_0013C140(void* self);
extern "C" void func_00294170(void* snd, void* rider);
int cRider_getControlState(void* rider);
int cRider_getMotionMode(void* rider);
// PORT: cRider_setMotionMode is defined with one parameter but this caller passes (rider, 1).
void cRider_setMotionMode_impl_BFA8(void* rider, int v) __asm__("cRider_setMotionMode__FPv");
extern char* D_004A3500;

struct sTbl_BFA8 {
    int v[4];
};
extern sTbl_BFA8 D_00458230;

struct sVec4_BFA8 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float vu0Length_BFA8(const sVec4_BFA8& v)
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

// PORT: PS2-only VU0 inline asm (in-place vector times scalar).
static inline void vu0ScaleEq_BFA8(sVec4_BFA8& v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %2\n"
        "lqc2      $vf4, %0\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "+m"(v), "=&r"(t)
        : "f"(s));
}

#define RIDER_BFA8 (*(char**)((char*)self + 0x50))

extern "C" void cRailSlideMotion_postUpdate(void* self)
{
    cRider_updateQueryBounds_v(RIDER_BFA8, 0);
    if (*(int*)((char*)self + 0x20) != 0) {
        char* r = RIDER_BFA8;
        *(int*)(r + 0x234) = 0;
        *(float*)(r + 0x230) = 0.03333333507180214f;
        func_00114298(RIDER_BFA8, -1.0f);
    }
    sTbl_BFA8 tbl = D_00458230;
    if (cRider_getControlState(RIDER_BFA8) == 0xC) {
        char* r = RIDER_BFA8;
        *(int*)(*(char**)(r + 0xAA0) + 0x28) = tbl.v[*(int*)(*(char**)(r + 0x77C) + 0x394)];
    } else {
        *(int*)(*(char**)(RIDER_BFA8 + 0xAA0) + 0x28) = 0x16;
    }
    func_00105398(RIDER_BFA8, 0);
    *(int*)(*(char**)(RIDER_BFA8 + 0xAA0) + 0x28) = 3;
    func_0013C140(self);
    *(unsigned int*)(*(char**)(RIDER_BFA8 + 0xAA0) + 0x28) = 0xFFFFFFFF;
    func_00107888(RIDER_BFA8);
    if (*(int*)((char*)self + 0x20) != 0 && cRider_getMotionMode(RIDER_BFA8) == 4) {
        cRider_setMotionMode_impl_BFA8(RIDER_BFA8, 1);
        func_00294170(D_004A3500, RIDER_BFA8);
    }
    char* r = RIDER_BFA8;
    float len = vu0Length_BFA8(*(sVec4_BFA8*)(r + 0x1E0));
    if (*(float*)(r + 0x2E4) < len)
        vu0ScaleEq_BFA8(*(sVec4_BFA8*)(r + 0x1E0), *(float*)(r + 0x2E4) / len);
}

INCLUDE_ASM("ai/control/handplantcontrol", func_0013C140);

//100%
extern "C" void cRailSlideMotion_loseFocus(void* self)
{
    char* a = *(char**)((char*)self + 0x50);
    *(float*)(a + 0x25C) = *(float*)(a + 0x264) = -0.25f;
    *(float*)(a + 0x260) = 0.0f;
    char* b = *(char**)((char*)self + 0x50);
    *(float*)(b + 0x264) = 1.0f;
    *(float*)(b + 0x260) = 0.03333333507180214f;
    *(int*)(*(char**)((char*)self + 0x50) + 0x5AC) = 0;
}

//100%
struct sVEntry0013C5E0 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cRailSlideMotion_writeToReplayFrame(void* self, void* obj)
{
    sVEntry0013C5E0* vt = *(sVEntry0013C5E0**)obj;
    vt[1].fn((char*)obj + vt[1].delta, self, 0x50);
}

//100%
struct sVEntry0013C618 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cRailSlideMotion_readFromReplayFrame(void* self, void* obj)
{
    sVEntry0013C618* vt = *(sVEntry0013C618**)obj;
    vt[2].fn((char*)obj + vt[2].delta, self, 0x50);
}

//100%
extern "C" void cRider_cRider(void* self);

struct sVEntry_13C650 { short delta; short index; void* fn; };
struct sVtbl9_13C650 { sVEntry_13C650 e[9]; } __attribute__((aligned(8)));
struct sVtbl22_13C650 { sVEntry_13C650 e[22]; } __attribute__((aligned(8)));

extern const sVtbl9_13C650 D_00459A98;
extern char D_00459B90[];
extern const sVtbl22_13C650 D_00459AE0;

// PORT: g++ 2.95 virtual-base construction. The class derives virtually from cRider (vbase pointer at
// +0x18, vbase at +0x20); when not most-derived, g++ copies cRider's overridden vtables to the stack and
// fixes up the this-deltas (expand_upcast_fixups). Written out by hand here.
extern "C" void* cGroundMotion_cGroundMotion(void* self, int inChrg)
{
    if (inChrg)
    {
        char* vb = (char*)self + 0x20;
        *(char**)((char*)self + 0x18) = vb;
        cRider_cRider(vb);
    }
    *(void**)(*(char**)((char*)self + 0x18) + 0x6E8) = (void*)&D_00459A98;
    *(void**)(*(char**)((char*)self + 0x18) + 0x6D0) = D_00459B90;
    *(void**)(*(char**)((char*)self + 0x18) + 0x6C0) = (void*)&D_00459AE0;
    if (!inChrg)
    {
        sVtbl9_13C650 t1 = D_00459A98;
        *(void**)(*(char**)((char*)self + 0x18) + 0x6E8) = &t1;
        char* base = *(char**)((char*)self + 0x18) - 0x20;
        int d = (char*)self - base;
        t1.e[1].delta = D_00459A98.e[1].delta + d;
        sVtbl22_13C650 t2 = D_00459AE0;
        *(void**)(*(char**)((char*)self + 0x18) + 0x6C0) = &t2;
        t2.e[1].delta = D_00459AE0.e[1].delta + d;
    }
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0x10) = 0;
    *(int*)(*(char**)((char*)self + 0x18) + 0x31C) = 0;
    return self;
}

//100%
extern void* D_004A28A8;
extern "C" int getGameTick();

struct sHpVec4_13C7A8 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sHpEntry_13C7A8 {
    char pad0[0x14];
    float m14;
    float m18;
    char pad1C[0xB0 - 0x1C];
};

// PORT: PS2-only VU0 inline asm (in-place vector times scalar).
static inline void vu0ScaleEq_13C7A8(sHpVec4_13C7A8& v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %2\n"
        "lqc2      $vf4, %0\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "+m"(v), "=&r"(t)
        : "f"(s));
}

struct sHpCtl_13C7A8 {
    int m0;
    float m4;
    float m8;
    int mC;
    int m10;
    int m14;
    char* mRider;
};

extern "C" void cGroundMotion_gainFocus(sHpCtl_13C7A8* self)
{
    self->m0 = 0;
    char* r = self->mRider;
    sHpEntry_13C7A8* tbl = *(sHpEntry_13C7A8**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x44);
    sHpEntry_13C7A8* e = &tbl[*(int*)(r + 0x438)];
    float k = *(float*)(*(char**)(r + 0x780) + 0x140);
    self->m4 = k * e->m14;
    self->m8 = k * e->m18;
    *(sHpVec4_13C7A8*)(r + 0x390) = *(sHpVec4_13C7A8*)(r + 0x370);
    self->mC = 0;
    int t = getGameTick();
    self->m10 = t;
    int d = t - self->m14;
    float f;
    if (d > 0x28)
        f = (d - 0x28) * 0.010000000707805157f + 0.699999988079071f;
    else
        f = 0.699999988079071f;
    vu0ScaleEq_13C7A8(*(sHpVec4_13C7A8*)(self->mRider + 0x1E0), f <? 1.0f);
}

extern "C" float cGroundMotion_computeNormalAccel(sHpCtl_13C7A8* self, float* p, float a, float b)
{
    float r;
    if (a > 0.0f)
    {
        r = p[0] * (a * -0.033333f);
        if (b > 0.0f)
            r -= p[7] * b;
    }
    else if (-self->m4 < a)
    {
        r = -p[0] * a / self->m4;
        r -= p[7] * b;
    }
    else
    {
        a = -self->m8 >? a;
        r = p[0] * (1.0f - (a + self->m4 + (a + self->m4)) / (self->m8 - self->m4));
        r -= p[7] * b;
    }
    *(float*)(self->mRider + 0x758) = -a / self->m8 >? 0.0f;
    return r;
}

INCLUDE_ASM("ai/control/handplantcontrol", func_0013C948);

//100%
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cBE_getBE();
extern "C" float func_001494C0(void* self, int rider, int value);
extern "C" float func_001493D8(void* self, int rider, int value);
extern "C" float func_00148D80(void* self, int rider, int value);

struct sCurvePt_13CCF0 { float x, y; };

// PORT: PS2-only inline asm (float absolute value), as an SDK math-header fabsf would.
static inline float hpAbs_13CCF0(float x)
{
    float r;
    __asm__("abs.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline float hpLerp_13CCF0(const sCurvePt_13CCF0& a, const sCurvePt_13CCF0& b, float x)
{
    float y0 = a.y;
    x -= a.x;
    return y0 + (b.y - y0) * x / (b.x - a.x);
}

struct sHpCfg_13CCF0 { char pad[0x90]; sCurvePt_13CCF0 p[4]; };

static inline float hpCurve_13CCF0(const sHpCfg_13CCF0* c, float x)
{
    if (c->p[1].x < x)
    {
        if (c->p[2].x < x)
        {
            if (c->p[3].x < x)
                return c->p[3].y;
            return hpLerp_13CCF0(c->p[2], c->p[3], x);
        }
        return hpLerp_13CCF0(c->p[1], c->p[2], x);
    }
    if (x < c->p[0].x)
        return c->p[0].y;
    return hpLerp_13CCF0(c->p[0], c->p[1], x);
}

static inline float hpClamp_13CCF0(float v, float lo, float hi)
{
    if (v >= lo)
        return v <? hi;
    return lo;
}

static inline float hpRamp_13CCF0(float v, float lo, float hi)
{
    if (v >= lo)
    {
        if (v <= hi)
            return (v - lo) / (hi - lo);
        return 1.0f;
    }
    return 0.0f;
}

#define RIDER (*(char**)((char*)self + 0x18))

extern "C" float func_0013CCF0(void* self, sHpCfg_13CCF0* cfg, float a)
{
    float one = 1.0f;
    float spd = hpAbs_13CCF0(*(float*)(RIDER + 0x214));
    func_001494C0(cBE_getInterface_Fv(cBE_getBE(), 3), *(int*)(RIDER + 0x86C), *(int*)(RIDER + 0xB34));
    float k1 = one / (func_001493D8(cBE_getInterface_Fv(cBE_getBE(), 3), *(int*)(RIDER + 0x86C), *(int*)(RIDER + 0xB34)) * 0.31941401958465576f + one);
    float k2 = func_00148D80(cBE_getInterface_Fv(cBE_getBE(), 3), *(int*)(RIDER + 0x86C), *(int*)(RIDER + 0xB34)) * 0.46218693256378174f + one;
    float c = hpCurve_13CCF0(cfg, hpAbs_13CCF0(a) * 0.035999998450279236f);
    float t = hpClamp_13CCF0(hpAbs_13CCF0(a) / 1666.666748046875f, 0.0f, 1.0f);
    c = c * (one * (k1 * (1.0f - t) + one * t));
    float ramp = hpRamp_13CCF0(*(float*)(RIDER + 0x378), 0.10000000149011612f, 0.20000000298023224f);
    float lift = ramp * (spd * 3.0004208087921143f) * spd * k2;
    float drag = ramp * (spd * 999.9600219726562f);
    float f8 = 1.0f;
    if (*(int*)(RIDER + 0x438) == 2 || *(int*)(RIDER + 0x438) == 3 || *(int*)(RIDER + 0x438) == 13)
        f8 = 0.5f - *(float*)(RIDER + 0x454) / *(float*)((char*)self + 8);
    float f12 = 1.0f;
    if (0.0f < *(float*)(RIDER + 0x1E8) - *(float*)(RIDER + 0x3D8))
        f12 = 0.5999583005905151f;
    float f2 = 1.0f;
    if (*(int*)(RIDER + 0x320) != *(int*)(RIDER + 0x324) && *(float*)(RIDER + 0x2FC) == 0.0f)
        f2 = 1.1147289276123047f;
    float f5 = 1.0f;
    if (0.0f < a && 0.0f < *(float*)(RIDER + 0x1E8) - *(float*)(RIDER + 0x3D8) && *(int*)(RIDER + 0x438) == 13)
        f5 = 34.84144592285156f;
    return ((-a * f8) * (c + lift) * f12 * f2 - drag) * f5;
}
#undef RIDER

//100%
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cBE_getBE();
extern "C" void func_00148E68(void* iface, int rider, int b);

struct sCurvePt_13D028 { float x, y; };
extern sCurvePt_13D028* D_004A1140;

// PORT: PS2-only inline asm (float absolute value), as an SDK math-header fabsf would.
static inline float hpAbs_13D028(float x)
{
    float r;
    __asm__("abs.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline float hpLerp_13D028(const sCurvePt_13D028& a, const sCurvePt_13D028& b, float x)
{
    float y0 = a.y;
    x -= a.x;
    return y0 + (b.y - y0) * x / (b.x - a.x);
}

static inline float hpCurve_13D028(const sCurvePt_13D028* p, float x)
{
    if (p[1].x < x)
    {
        if (p[2].x < x)
        {
            if (p[3].x < x)
                return p[3].y;
            return hpLerp_13D028(p[2], p[3], x);
        }
        return hpLerp_13D028(p[1], p[2], x);
    }
    if (x < p[0].x)
        return p[0].y;
    return hpLerp_13D028(p[0], p[1], x);
}

extern "C" float func_0013D028(void* self, float* v, float a, float b, float c)
{
    if (a < 0.0f && 0.0f < c)
    {
        a = a * c;
    }
    else if (0.0f < a && c < 0.0f)
    {
        a = a * -c;
    }
    else
    {
        return 0.0f;
    }
    a = a * hpCurve_13D028(D_004A1140, hpAbs_13D028(b) * 0.035999998450279236f);
    a = a * -v[2];
    func_00148E68(cBE_getInterface_Fv(cBE_getBE(), 3), *(int*)(*(char**)((char*)self + 0x18) + 0x86C), *(int*)(*(char**)((char*)self + 0x18) + 0xB34));
    float s = *(float*)(*(char**)((char*)self + 0x18) + 0x2FC);
    float one = 1.0f;
    if (0.0f < s)
        a = a * (one / (s * 4.008637428283691f + one));
    return a;
}

//100%
extern "C" void* func_0032E100(void* seg, const sVec4HP& a, const sVec4HP& b, int n, float r);
extern void* D_004FF120[];

struct sHit_13D1B8 {
    sVec4HP pos;            // 0x00
    sVec4HP normal;         // 0x10
    sVec4HP v20;            // 0x20
    float pad30[4];         // 0x30
    float dist;             // 0x40
    int pad44[2];           // 0x44
    int m4C;                // 0x4C
    char* obj;              // 0x50
    char* tri;              // 0x54
    int pad58[5];           // 0x58
    float m6C;              // 0x6C
    float m70;              // 0x70
    int pad74[3];           // 0x74
    sHit_13D1B8() {}
} __attribute__((aligned(16)));

extern "C" int func_00333EF8(void* world, void* seg, sHit_13D1B8* hits, int max, int flags);
extern sVec4HP D_004FF160;
extern sVec4HP D_004FF120_v __asm__("D_004FF120");

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4HP vu0Scale_13D1B8(const sVec4HP& v, float s)
{
    sVec4HP r;
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

// PORT: PS2-only VU0 inline asm (vector add).
static inline sVec4HP vu0Add_13D1B8(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
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

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sVec4HP vu0Sub_13D1B8(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
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

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0Dot_13D1B8(const sVec4HP& a, const sVec4HP& b)
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

// PORT: PS2-only VU0 inline asm (4-component dot product, by-value first operand).
static inline float vu0DotV_13D1B8(sVec4HP a, const sVec4HP& b)
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

// PORT: PS2-only VU0 inline asm (normalize via rsqrt).
static inline sVec4HP vu0Normalize_13D1B8(const sVec4HP& v)
{
    sVec4HP r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vrsqrt    Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf3, Q\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(v)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (cross product, w = 0).
static inline sVec4HP vu0Cross_13D1B8(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
    __asm__(
        "lqc2      $vf4, %1\n"
        "lqc2      $vf5, %2\n"
        "vopmula.xyz ACC, $vf4, $vf5\n"
        "vopmsub.xyz $vf6, $vf5, $vf4\n"
        "vsub.w    $vf6, $vf6, $vf6\n"
        "sqc2      $vf6, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float vu0Length_13D1B8(const sVec4HP& v)
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

// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_13D1B8(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}


// Non-POD by-value vector (user copy ctor => passed by invisible reference, no callee copy).
struct sVec4P_13D1B8 {
    float x, y, z, w;
    sVec4P_13D1B8(const sVec4HP& v) { *(sVec4HP*)this = v; }
    sVec4P_13D1B8(const sVec4P_13D1B8& v) { *(sVec4HP*)this = *(const sVec4HP*)&v; }
} __attribute__((aligned(16)));

static inline sVec4HP vu0SubV_13D1B8(sVec4P_13D1B8 a, const sVec4HP& b)
{
    return vu0Sub_13D1B8(*(sVec4HP*)&a, b);
}

static inline int isBetter_13D1B8(sHit_13D1B8* a, sHit_13D1B8* b)
{
    if (a->obj != 0) {
        if (b->obj == 0) {
            return 1;
        }
        return *(unsigned int*)(a->obj + 0x78) < *(unsigned int*)(b->obj + 0x78);
    }
    if (b->obj != 0) {
        return 0;
    }
    return *(unsigned int*)(a->tri + 0x150) < *(unsigned int*)(b->tri + 0x150);
}

struct sVEnt_13D1B8 { short delta; short index; void (*fn)(void*, void*); };

#define RIDER (*(char**)((char*)self + 0x18))
#define RV(off) (*(sVec4HP*)(RIDER + (off)))

INCLUDE_ASM("ai/control/handplantcontrol", cGroundMotion_updateContact);
extern "C" int cGroundMotion_updateContact(void* self, sHit_13D1B8* out, float* dist);
#undef RV
#undef RIDER

INCLUDE_ASM("ai/control/handplantcontrol", cGroundMotion_update);

//100%
extern "C" void func_00114298(void* rider, float v);
// PORT: cRider_updateQueryBounds is declared void* in this unit; this caller ignores the result (void call).
extern "C" void cRider_updateQueryBounds_v13F178(void* rider, int a1) __asm__("cRider_updateQueryBounds");
extern "C" void func_00105398(void* rider, int a1);
extern "C" void func_00107888(void* rider);
extern "C" void func_00116120(void* rider, int a, int b);
extern "C" void func_0013F488(void* self);
extern "C" void func_00294170(void* snd, void* rider);
int cRider_getMotionMode(void* rider);
// PORT: cRider_setMotionMode is defined with one parameter but this caller passes (rider, 1).
void cRider_setMotionMode_impl_13F178(void* rider, int v) __asm__("cRider_setMotionMode__FPv");
extern char* D_004A3500;
extern int D_004A115C;
extern void* D_004A28A8;

struct sInfo_13F178 {
    sVec4HP pos;
    sVec4HP dir;
    sVec4HP up;
    int f30;
} __attribute__((aligned(16)));

extern "C" void cRider_enterCrash(void* rider, int a1, int a2, int a3, sInfo_13F178* info);

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4HP vu0Scale_13F178(const sVec4HP& v, float s)
{
    sVec4HP r;
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

// PORT: PS2-only VU0 inline asm (vector add).
static inline sVec4HP vu0Add_13F178(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
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

// PORT: PS2-only VU0 inline asm (normalize via rsqrt).
static inline sVec4HP vu0Normalize_13F178(const sVec4HP& v)
{
    sVec4HP r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vrsqrt    Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf3, Q\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(v)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float vu0Length_13F178(const sVec4HP& v)
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

// PORT: PS2-only VU0 inline asm (in-place vector times scalar).
static inline void vu0ScaleEq_13F178(sVec4HP& v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %2\n"
        "lqc2      $vf4, %0\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "+m"(v), "=&r"(t)
        : "f"(s));
}

// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_13F178(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

#define RIDER_13F178 (*(char**)((char*)self + 0x18))

extern "C" void cGroundMotion_postUpdate(void* self)
{
    if (*(int*)((char*)self + 0xC) != 0) {
        func_00114298(RIDER_13F178, -1.0f);
    } else {
        char* r = RIDER_13F178;
        int idx = *(int*)(r + 0x438);
        char* e = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x44) + idx * 0xB0;
        int fl;
        if (idx == 0x12) {
            sInfo_13F178 info;
            info.pos = *(sVec4HP*)(r + 0x110);
            info.dir = vu0Normalize_13F178(*(sVec4HP*)(r + 0x1E0));
            info.up = *(sVec4HP*)(RIDER_13F178 + 0x370);
            info.f30 = 0;
            cRider_enterCrash(RIDER_13F178, 0x168, 0, *(int*)(RIDER_13F178 + 0x438), &info);
        } else if (*(int*)(e + 0x44) != 0 || (fl = *(short*)(r + 0x2D4), (fl & 2) != 0)) {
            func_00116120(r, 0, 1);
        }
    }
    cRider_updateQueryBounds_v13F178(RIDER_13F178, 0);
    *(int*)(*(char**)(RIDER_13F178 + 0xAA0) + 0x28) = D_004A115C;
    func_0013F488(self);
    *(unsigned int*)(*(char**)(RIDER_13F178 + 0xAA0) + 0x28) = 0xFFFFFFFF;
    func_00105398(RIDER_13F178, 0);
    func_00107888(RIDER_13F178);
    if (*(int*)((char*)self + 0xC) != 0 && cRider_getMotionMode(RIDER_13F178) == 0) {
        cRider_setMotionMode_impl_13F178(RIDER_13F178, 1);
        func_00294170(D_004A3500, RIDER_13F178);
    }
    char* r = RIDER_13F178;
    *(sVec4HP*)(r + 0x390) = vu0Normalize_13F178(vu0Add_13F178(*(sVec4HP*)(RIDER_13F178 + 0x390), vu0Scale_13F178(*(sVec4HP*)(r + 0x370), 0.5f)));
    char* r3 = RIDER_13F178;
    float len = vu0Length_13F178(*(sVec4HP*)(r3 + 0x1E0));
    if (*(float*)(r3 + 0x2E4) < len) {
        vu0ScaleEq_13F178(*(sVec4HP*)(r3 + 0x1E0), *(float*)(r3 + 0x2E4) / len);
    }
    float k = 0.0f;
    float vmax = 3333.33349609375f;
    if (0.0f <= len) {
        k = 1.0f;
        if (len <= vmax) {
            k = len / vmax;
        }
    }
    *(float*)(RIDER_13F178 + 0x75C) = k;
    char* r4 = RIDER_13F178;
    *(float*)(r4 + 0x754) = absf_13F178(*(float*)(r4 + 0x1F0));
    char* r5 = RIDER_13F178;
    *(float*)(r5 + 0x750) = absf_13F178(*(float*)(r5 + 0x214));
}

//100%
extern "C" int getGameTick();

extern "C" void cGroundMotion_loseFocus(void* self)
{
    char* a = *(char**)((char*)self + 0x18);
    *(int*)(a + 0x2C4) = 0;
    *(float*)(a + 0x2C0) = 0.05000000447034836f;
    char* b = *(char**)((char*)self + 0x18);
    *(float*)(b + 0x20C) = 0.05000000447034836f;
    *(int*)(b + 0x210) = 0;
    char* c = *(char**)((char*)self + 0x18);
    *(float*)(c + 0x2CC) = 1.6666667461395264f;
    *(int*)(c + 0x2D0) = 0;
    if (*(int*)((char*)self + 0x14) == -1)
        *(int*)((char*)self + 0x14) = getGameTick() - 500;
    else
        *(int*)((char*)self + 0x14) = getGameTick();
}

//100%
extern "C" void cRider_updateOrientationImplicit(void*);
int cRider_getControlState(void* rider);
extern "C" float func_003342D0(void* world, void* seg, void* hit, int flags);
extern "C" void func_00106538(void* rider, void* v);
extern "C" void func_001065B0(void* rider, void* hit);
extern "C" void func_00105D98(void* rider, void* info, int id);
extern "C" void* func_0028B180();
extern "C" void func_002989A8(void* snd, void* rider);
extern "C" void* func_0032F650(void* self, void* tree, int flag);
extern "C" void func_0032F708(void* self, int flags);

struct sHit_13F488 {
    sVec4HP pos;            // 0x00
    sVec4HP normal;         // 0x10
    sVec4HP v20;            // 0x20
    float pad30[4];         // 0x30
    float dist;             // 0x40
    int pad44[2];           // 0x44
    int m4C;                // 0x4C
    char* obj;              // 0x50
    char* tri;              // 0x54
    int pad58[5];           // 0x58
    float m6C;              // 0x6C
    float m70;              // 0x70
    int pad74[3];           // 0x74
} __attribute__((aligned(16)));

struct sSphere_13F488 {
    int state;              // 0x00
    int f4;                 // 0x04
    int f8;                 // 0x08
    int padC;               // 0x0C
    sVec4HP dir;            // 0x10
    char rest[0x320 - 0x20];
} __attribute__((aligned(16)));

struct sInfo_13F488 {
    sVec4HP pos;
    sVec4HP dir;
    sVec4HP normal;
    float depth;
} __attribute__((aligned(16)));

struct sVEnt_13F488 { short delta; short index; bool (*fn)(void*); };
struct sVEntH_13F488 { short delta; short index; void (*fn)(void*, void*); };

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4HP vu0Scale_13F488(const sVec4HP& v, float s)
{
    sVec4HP r;
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
static inline sVec4HP vu0Sub_13F488(const sVec4HP& a, const sVec4HP& b)
{
    sVec4HP r;
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

// PORT: PS2-only VU0 inline asm (in-place vector add).
static inline void vu0AddEq_13F488(sVec4HP& a, const sVec4HP& b)
{
    __asm__(
        "lqc2      $vf3, %0\n"
        "lqc2      $vf4, %1\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "+m"(a)
        : "m"(b));
}

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0Dot_13F488(const sVec4HP& a, const sVec4HP& b)
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

// PORT: PS2-only VU0 inline asm (normalize via rsqrt).
static inline sVec4HP vu0Normalize_13F488(const sVec4HP& v)
{
    sVec4HP r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vrsqrt    Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf3, Q\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(v)
        : "memory");
    return r;
}

// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_13F488(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

static inline bool riderFlag_13F488(char* r)
{
    char* sub = r + 0x6C0;
    sVEnt_13F488* vt = *(sVEnt_13F488**)sub;
    return vt[8].fn(sub + vt[8].delta);
}

#define RIDER (*(char**)((char*)self + 0x18))
#define RV(off) (*(sVec4HP*)(RIDER + (off)))

extern "C" void func_0013F488(void* self)
{
    if (cRider_getControlState(RIDER) == 9)
        return;
    if (!riderFlag_13F488(RIDER)) {
        char* r = RIDER;
        if (*(float*)(r + 0x4C8) < 50.0f && absf_13F488(*(float*)(r + 0x498) - *(float*)(r + 0x118)) < 50.0f)
            return;
    }
    sHit_13F488 hit;
    sSphere_13F488 sph;
    char* r = RIDER;
    func_0032F650(&sph, *(void**)(r + 0xAA0), !riderFlag_13F488(r));
    sph.f8 = 1;
    sph.dir = RV(0x370);
    float d = func_003342D0(*(void**)(RIDER + 0x860), &sph, &hit, *(int*)(RIDER + 0x868));
    if (d < 0.0f)
        { func_0032F708(&sph, 2); return; }
    if (hit.obj != 0) {
        char* h = *(char**)(hit.obj + 0xC);
        if (h) {
            sVEntH_13F488* vt = *(sVEntH_13F488**)(h + 0xC);
            vt[42].fn(h + vt[42].delta, &hit);
        }
    }
    {
        float dot = vu0Dot_13F488(RV(0x370), hit.normal);
        if (dot < -0.9998999834060669f)
            { func_0032F708(&sph, 2); return; }
        if (dot < 0.0f)
            hit.normal = vu0Normalize_13F488(vu0Sub_13F488(hit.normal, vu0Scale_13F488(RV(0x370), dot)));
    }
    {
        sVec4HP push = vu0Scale_13F488(vu0Scale_13F488(hit.normal, 1.100000023841858f), d);
        func_00106538(RIDER, &push);
        sVec4HP a = vu0Sub_13F488(RV(0x1E0), hit.v20);
        float dot2 = vu0Dot_13F488(vu0Scale_13F488(hit.normal, -1.0f), a);
        if (dot2 < 0.0f)
            { func_0032F708(&sph, 2); return; }
        sVec4HP n = vu0Normalize_13F488(a);
        float k = dot2 * 0.05000000074505806f;
        if (k < 27.77777862548828f)
            k = 27.77777862548828f;
        vu0AddEq_13F488(RV(0x1E0), vu0Scale_13F488(hit.normal, dot2 + k));
        func_001065B0(RIDER, &hit);
        cRider_updateOrientationImplicit(RIDER);
        sInfo_13F488 info;
        info.pos = hit.pos;
        info.dir = n;
        info.normal = hit.normal;
        info.depth = dot2;
        func_00105D98(RIDER, &info, hit.m4C);
        func_002989A8(func_0028B180(), RIDER);
    }
    func_0032F708(&sph, 2);
}
#undef RV
#undef RIDER

//100%
struct sVEntry0013F848 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cGroundMotion_writeToReplayFrame(void* self, void* obj)
{
    sVEntry0013F848* vt = *(sVEntry0013F848**)obj;
    vt[1].fn((char*)obj + vt[1].delta, self, 0x18);
}

//100%
struct sVEntry0013F880 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cGroundMotion_readFromReplayFrame(void* self, void* obj)
{
    sVEntry0013F880* vt = *(sVEntry0013F880**)obj;
    vt[2].fn((char*)obj + vt[2].delta, self, 0x18);
}

// Variadic no-op (probably a stripped debug print); returns its first argument.
extern "C" void* func_0013F8B8(void* a, ...)
{
    return a;
}

//100%
struct sSortObj_F8F8 {
    char pad[0x78];
    unsigned int key;   // 0x78
};

// Merge sort of an object-pointer array by key, using buf as scratch; the sorted result ends up in buf.
extern "C" void func_0013F8F8(sSortObj_F8F8** first, sSortObj_F8F8** last, sSortObj_F8F8** buf, void* cmp)
{
    int n = last - first;
    if (n == 2) {
        if (first[0]->key < first[1]->key) {
            buf[0] = first[0];
            buf[1] = first[1];
        } else {
            buf[0] = first[1];
            buf[1] = first[0];
        }
        return;
    }
    sSortObj_F8F8** mid = first + (n + 1) / 2;
    sSortObj_F8F8** bmid = buf + n / 2;
    sSortObj_F8F8** bend = buf + n;
    if (n < 3)
        *bmid = *first;
    else
        func_0013F8F8(first, mid, bmid, cmp);
    if (n < 4)
        *first = *mid;
    else
        func_0013F8F8(mid, last, first, cmp);
    sSortObj_F8F8** b = bmid;
    sSortObj_F8F8** bend2 = bmid + (n + 1) / 2;
    sSortObj_F8F8** a = first;
    sSortObj_F8F8** aend = first + n / 2;
    sSortObj_F8F8** out = buf;
    while (out < bend) {
        if (a < aend) {
            if (b < bend2 && (*b)->key < (*a)->key)
                *out++ = *b++;
            else
                *out++ = *a++;
        } else {
            *out++ = *b++;
        }
    }
}

struct sSortObj_F8F8;
extern "C" void func_0013F8F8(sSortObj_F8F8** first, sSortObj_F8F8** last, sSortObj_F8F8** buf, void* cmp);

// Sorts [first, last) into buf (merge sort for 2+ entries, plain copy for one).
extern "C" void func_0013FAD8(sSortObj_F8F8** first, sSortObj_F8F8** last, sSortObj_F8F8** buf, void* cmp)
{
    int n = last - first;
    if (n >= 2)
        func_0013F8F8(first, last, buf, cmp);
    else if (n == 1)
        *buf = *first;
}

INCLUDE_ASM("ai/control/handplantcontrol", func_0013FB20);

//100%
void operator_delete(int* ptr);

extern void* D_00459CC8[];

extern "C" void func_00140680(int* self, int flags)
{
    *(void***)self = D_00459CC8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern void* D_004FF120[];

//100%
void* func_001406B0(void* self)
{
    return (void*)D_004FF120;
}

//100%
int func_001406C0(void* self)
{
    return 0;
}

//100%
void func_001406C8(void* self)
{
}

//100%
void* func_001406D0(void* self)
{
    return (void*)D_004FF120;
}

extern void* D_004FF1A0[];

//100%
void* func_001406E0(void* self)
{
    return (void*)D_004FF1A0;
}

//100%
int func_001406F0(void* self)
{
    return 0;
}

//100%
int func_001406F8(void* self)
{
    return 0;
}

//100%
int func_00140700(void* self)
{
    return 0;
}

//100%
void func_00140708(void* self)
{
}

//100%
void func_00140710(void* self)
{
}

//100%
void func_00140718(void* self)
{
}

//100%
void func_00140720(void* self)
{
}

//100%
void func_00140728(void* self)
{
}

//100%
void func_00140730(void* self)
{
}

//100%
struct sHPC140738 {
    char pad0[0x1F0];
    int v[19][3];           // 0x1F0
    char pad2D4[0x430 - 0x2D4];
    unsigned int u430;      // 0x430
    char pad434[0x5B8 - 0x434];
    unsigned int arr[64];   // 0x5B8
};

extern "C" sHPC140738* func_00140738(sHPC140738* self)
{
    self->v[0][2] = 0;
    self->v[0][0] = 0;
    self->v[0][1] = 0;
    self->v[1][2] = 0;
    self->v[1][0] = 0;
    self->v[1][1] = 0;
    self->v[2][2] = 0;
    self->v[2][0] = 0;
    self->v[2][1] = 0;
    self->v[3][2] = 0;
    self->v[3][0] = 0;
    self->v[3][1] = 0;
    self->v[4][2] = 0;
    self->v[4][0] = 0;
    self->v[4][1] = 0;
    self->v[5][2] = 0;
    self->v[5][0] = 0;
    self->v[5][1] = 0;
    self->v[6][2] = 0;
    self->v[6][0] = 0;
    self->v[6][1] = 0;
    self->v[7][2] = 0;
    self->v[7][0] = 0;
    self->v[7][1] = 0;
    self->v[8][2] = 0;
    self->v[8][0] = 0;
    self->v[8][1] = 0;
    self->v[9][2] = 0;
    self->v[9][0] = 0;
    self->v[9][1] = 0;
    self->v[10][2] = 0;
    self->v[10][0] = 0;
    self->v[10][1] = 0;
    self->v[11][2] = 0;
    self->v[11][0] = 0;
    self->v[11][1] = 0;
    self->v[12][2] = 0;
    self->v[12][0] = 0;
    self->v[12][1] = 0;
    self->v[13][2] = 0;
    self->v[13][0] = 0;
    self->v[13][1] = 0;
    self->v[14][2] = 0;
    self->v[14][0] = 0;
    self->v[14][1] = 0;
    self->v[15][2] = 0;
    self->v[15][0] = 0;
    self->v[15][1] = 0;
    self->v[16][2] = 0;
    self->v[16][0] = 0;
    self->v[16][1] = 0;
    self->v[17][2] = 0;
    self->v[17][0] = 0;
    self->v[17][1] = 0;
    self->v[18][2] = 0;
    self->v[18][0] = 0;
    self->v[18][1] = 0;
    self->u430 = 0xFFFFFFFF;
    unsigned int* p = self->arr;
    for (int i = 63; i != -1; i--, p++) {
        *p = 0xFFFFFFFF;
    }
    return self;
}

extern "C" void func_00140868(void* self, int value)
{
    *(int*)((char*)self + 0x87C) = value;
}

extern "C" int func_00140870(void* self)
{
    return *(int*)((char*)self + 0x87C);
}

extern "C" float func_00140878(void* self)
{
    return *(float*)((char*)self + 0x5A4);
}

extern "C" int func_00140880(void* self)
{
    return *(int*)((char*)self + 0x5A8);
}

extern "C" int func_00140888(void* self)
{
    return *(int*)((char*)self + 0x5AC);
}

extern "C" float func_00140890(void* self)
{
    return *(float*)((char*)self + 0x750);
}

extern "C" float func_00140898(void* self)
{
    return *(float*)((char*)self + 0x754);
}

extern "C" float func_001408A0(void* self)
{
    return *(float*)((char*)self + 0x758);
}

extern "C" float func_001408A8(void* self)
{
    return *(float*)((char*)self + 0x75C);
}

extern "C" void* func_001408B0(void* self)
{
    return (char*)self + 0x400;
}

extern "C" int func_001408B8(void* self)
{
    return *(int*)((char*)self + 0xAA0);
}

extern "C" sVec4HP func_001408C0(char* self)
{
    return *(sVec4HP*)(self + 0x1B0);
}

extern "C" sVec4HP func_001408D0(char* self)
{
    return *(sVec4HP*)(self + 0x1A0);
}

extern "C" sVec4HP func_001408E0(char* self)
{
    return *(sVec4HP*)(self + 0x1C0);
}

//100%
void* func_001408F0(void* self)
{
    return (char*)self + 0x110;
}

extern "C" void* func_001408F8(void* self)
{
    return (char*)self + 0x110;
}

extern "C" sVec4HP func_00140900(char* self)
{
    return *(sVec4HP*)(self + 0x120);
}

//100%
void* func_00140910(void* self)
{
    return (char*)self + 0x1E0;
}

extern "C" void func_00140918(char* self, sVec4HP* v)
{
    *(sVec4HP*)(self + 0x1E0) = *v;
}

// PORT: PS2-only VU0 inline asm (4x4 matrix copy).
static inline void CopyMat_HP(void* d, void* s)
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
        : "r"(d), "r"(s)
        : "memory");
}

// Returns the 4x4 matrix at +0x160 (hidden return pointer in out).
extern "C" void* func_00140928(void* out, char* self)
{
    CopyMat_HP(out, self + 0x160);
    return out;
}

extern "C" sVec4HP func_00140958(char* self)
{
    return *(sVec4HP*)(self + 0x370);
}

extern "C" float func_0031C228(float); // atan

// atan2(y, x) built on a single-argument atan.
static inline float Atan2_HP(float y, float x)
{
    if (x == 0.0f)
    {
        if (y == 0.0f)
            return y;
        return y >= 0.0f ? 1.5707964f : -1.5707964f;
    }
    float r = func_0031C228(y / x);
    if (x < 0.0f)
    {
        if (y > 0.0f)
            r += 3.1415927f;
        else
            r -= 3.1415927f;
    }
    return r;
}

static inline sVec4HP GetVec1B0_HP(char* self)
{
    return *(sVec4HP*)(self + 0x1B0);
}

// Heading angle of the vector at +0x1B0 in its x/y plane.
extern "C" float func_00140968(char* self)
{
    sVec4HP v = GetVec1B0_HP(self);
    sVec4HP w = v;
    return Atan2_HP(v.y, w.x);
}

extern "C" int func_00140A28(void* self)
{
    return *(int*)((char*)self + 0x780);
}

extern "C" int func_00140A30(void* self)
{
    return *(int*)((char*)self + 0x784);
}

extern "C" int func_00140A38(void* self)
{
    return *(int*)((char*)self + 0x77C);
}

extern "C" int func_00140A40(void* self)
{
    return *(int*)((char*)self + 0x430);
}

extern "C" int func_00140A48(void* self)
{
    return *(int*)((char*)self + 0x434);
}

extern "C" int func_00140A50(void* self)
{
    return *(int*)((char*)self + 0x434) < 0x11;
}

extern "C" int func_00140A60(void* self)
{
    int v = *(int*)((char*)self + 0x434);
    return v >= 0xB && v <= 0xD;
}

extern "C" void* func_00140A70(void* self)
{
    return (char*)self + 0xAAC;
}

extern "C" void* func_00140A78(void* self)
{
    return (char*)self + 0x490;
}

extern "C" void* func_00140A80(void* self)
{
    return (char*)self + 0x4A0;
}

extern "C" int func_00140A88(void* self)
{
    return *(int*)((char*)self + 0xAB4);
}

extern "C" void func_00140A90(void* self, int value)
{
    *(int*)((char*)self + 0xAB4) = value;
}

extern "C" int func_00140A98(void* self)
{
    return *(int*)((char*)self + 0xAB8);
}

extern "C" void func_00140AA0(void* self, int value)
{
    *(int*)((char*)self + 0xAB8) = value;
}

extern "C" void func_00140AA8(void* self, float value)
{
    *(float*)((char*)self + 0x4D8) = value;
}

extern "C" void func_00140AB0(void* self, int value)
{
    *(int*)((char*)self + 0xE8) = value;
}

extern "C" int func_00140AB8(void* self)
{
    return *(int*)((char*)self + 0xE8);
}

extern "C" void func_00140AC0(void* self)
{
    *(float*)((char*)self + 0x470) = -1.0f;
}

extern "C" void func_00140AD0(void* self)
{
    if (*(float*)((char*)self + 0x470) < 0.0f)
        *(float*)((char*)self + 0x470) = 0.0f;
}

extern "C" int func_00140AF0(void* self)
{
    return *(float*)((char*)self + 0x470) >= 0.0f;
}

extern "C" int func_00140B18(void* self)
{
    return *(float*)((char*)self + 0x470) >= 10.0f;
}

extern "C" void func_00140B40(void* self, int value)
{
    *(int*)((char*)self + 0x474) = value;
}

extern "C" int func_00140B48(void* self)
{
    return *(int*)((char*)self + 0x474);
}

extern "C" void func_00140B50(void* self, int value)
{
    *(int*)((char*)self + 0x478) = value;
}

extern "C" int func_00140B58(void* self)
{
    return *(int*)((char*)self + 0x478);
}

extern "C" void func_00140B60(void* self, int value)
{
    *(int*)((char*)self + 0x47C) = value;
}

extern "C" int func_00140B68(void* self)
{
    return *(int*)((char*)self + 0x47C);
}

extern "C" void func_00140B70(void* self, int value)
{
    *(int*)((char*)self + 0x480) = value;
}

extern "C" int func_00140B78(void* self)
{
    return *(int*)((char*)self + 0x480);
}

//100%
int func_00140B80(void* self)
{
    return *(int*)((char*)self + 0x86C);
}

extern "C" void func_00140B88(void* self, int value)
{
    *(int*)((char*)self + 0x86C) = value;
}

extern "C" int func_00140B90(void* self)
{
    return *(int*)((char*)self + 0x870);
}

extern "C" void func_00140B98(void* self, int value)
{
    *(int*)((char*)self + 0x870) = value;
}

extern "C" void func_00140BA0(void* self)
{
    *(int*)((char*)self + 0x874) = 0x1;
}

extern "C" void func_00140BB0(void* self)
{
    *(int*)((char*)self + 0x878) = 0x1;
}

//100%
int func_00140BC0(void* self)
{
    return *(int*)((char*)self + 0x874);
}

//100%
extern "C" int func_00140BC8(void* self)
{
    return *(int*)((char*)self + 0x874) ^ 1;
}

extern "C" int func_00140BD8(void* self)
{
    return *(int*)((char*)self + 0x878);
}

extern "C" int func_00140BE0(void* self)
{
    return *(int*)((char*)self + 0x874) != 0 && *(int*)((char*)self + 0x87C) != 0;
}

extern "C" int func_00140C00(void* self)
{
    return *(int*)((char*)self + 0x884);
}

extern "C" void func_00140C08(void* self, int value)
{
    *(int*)((char*)self + 0x884) = value;
    *(int*)((char*)self + 0x888) = -1;
}

extern "C" int func_00140C18(void* self)
{
    return *(int*)((char*)self + 0x888);
}

extern "C" void func_00140C20(void* self, int value)
{
    *(int*)((char*)self + 0x888) = value;
}

extern "C" int func_00140C28(void* self)
{
    return *(int*)((char*)self + 0x3FC);
}

extern "C" void func_00140C30(void* self, int value)
{
    *(int*)((char*)self + 0x3FC) = value;
}

extern "C" int func_00140C38(void* self)
{
    return *(int*)((char*)self + 0x790);
}

extern "C" int func_00140C40(void* self)
{
    return *(int*)((char*)self + 0x788);
}

extern "C" int func_00140C48(void* self)
{
    return *(int*)((char*)self + 0x774);
}

extern "C" void func_00140C50(void* self, int value)
{
    *(int*)((char*)self + 0x774) = value;
}

extern "C" int func_00140C58(void* self)
{
    return *(int*)((char*)self + 0x778);
}

extern "C" void func_00140C60(void* self, int value)
{
    *(int*)((char*)self + 0x778) = value;
}

//100%
void func_00140C68(void* self)
{
}

//100%
void func_00140C70(void* self)
{
}

//100%
void func_00140C78(void* self)
{
}

//100%
void func_00140C80(void* self)
{
}

extern "C" int func_00140C88(void* self)
{
    return *(int*)((char*)self + 0x898);
}

extern "C" int func_00140C90(void* self)
{
    return *(int*)((char*)self + 0x78C);
}

extern "C" int func_00140C98(void* self)
{
    return *(int*)((char*)self + 0xAA8);
}

extern "C" float func_00140CA0(void* self)
{
    return *(float*)((char*)self + 0x5B4);
}

extern "C" int func_00140CA8(void* self)
{
    return *(int*)((char*)self + 0xAC4) != 0 && *(int*)((char*)self + 0xAD0) == 0 && *(int*)((char*)self + 0xAFC) != 0;
}

extern "C" int func_00140CD0(void* self)
{
    return *(int*)((char*)self + 0xB00);
}

extern "C" int func_00140CD8(void* self)
{
    return *(int*)((char*)self + 0xAC4);
}

//100%
void* func_00140CE0(void* self)
{
    return self;
}

extern "C" int func_00140CE8(void* self)
{
    return *(int*)((char*)self + 0xB18);
}

extern "C" void func_00120D58(void* self);

extern "C" void func_00140CF0(void* self, int value)
{
    *(int*)((char*)self + 0x304) = value;
    func_00120D58(self);
}

extern "C" void func_00140D10(void* self, int value)
{
    *(int*)((char*)self + 0xB20) = value;
}

extern "C" void func_00140D18(void* self, float value)
{
    *(float*)((char*)self + 0xB24) = value;
}

extern "C" void func_00140D20(void* self, int value)
{
    *(int*)((char*)self + 0xB28) = value;
}

extern "C" void func_00140D28(void* self, int value)
{
    *(int*)((char*)self + 0xB30) = value;
}

extern "C" void func_00140D30(void* self, int value)
{
    *(int*)((char*)self + 0xB34) = value;
}

extern "C" void func_00140D38(void* self, int value)
{
    *(int*)((char*)self + 0x308) = value;
}

extern "C" int func_00140D40(void* self)
{
    return *(int*)((char*)self + 0x304);
}

extern "C" int func_00140D48(void* self)
{
    return *(int*)((char*)self + 0xB20);
}

extern "C" int func_00140D50(void* self)
{
    return *(int*)((char*)self + 0xB2C) & 0x1;
}

extern "C" int func_00140D60(void* self)
{
    return (*(int*)((char*)self + 0xB2C) >> 1) & 0x1;
}

extern "C" int func_00140D70(void* self)
{
    return *(int*)((char*)self + 0xB30);
}

extern "C" int func_00140D78(void* self)
{
    return *(int*)((char*)self + 0x308);
}

INCLUDE_ASM("ai/control/handplantcontrol", cGroundMotion_destroy);

INCLUDE_ASM("ai/control/handplantcontrol", func_00140EE0);

INCLUDE_ASM("ai/control/handplantcontrol", func_00141040);

extern "C" int func_001411A0(void* self)
{
    return *(int*)((char*)self + 0x44);
}

extern "C" void* func_001411A8(void* self)
{
    return (char*)self + 0x50;
}

extern "C" int func_001411B0(void* self)
{
    return *(int*)((char*)self + 0x0);
}

extern "C" void* func_001411B8(void* self)
{
    return (char*)self + 0x30;
}

INCLUDE_ASM("ai/control/handplantcontrol", func_001411C0);

INCLUDE_ASM("ai/control/handplantcontrol", cHandplantMotion_destroy);

//100%
extern "C" void cRider_cRider(void* self);

struct sVEntry_00141480 { short delta; short index; void* fn; };
struct sVtblA_00141480 { sVEntry_00141480 e[9]; } __attribute__((aligned(8)));
struct sVtblB_00141480 { sVEntry_00141480 e[22]; } __attribute__((aligned(8)));

extern const sVtblA_00141480 D_004595C0_00141480 __asm__("D_004595C0");
extern char D_00459B90[];
extern const sVtblB_00141480 D_00459608_00141480 __asm__("D_00459608");

// PORT: g++ 2.95 virtual-base construction. The class derives virtually from cRider (vbase pointer at
// +0xA0, vbase at +0xB0); when not most-derived, g++ copies cRider's overridden vtables to the stack
// and fixes up the this-deltas (expand_upcast_fixups). Written out by hand here.
extern "C" void* cHandplantMotion_cHandplantMotion(void* self, int inChrg)
{
    if (inChrg)
    {
        char* vb = (char*)self + 0xB0;
        *(char**)((char*)self + 0xA0) = vb;
        cRider_cRider(vb);
    }
    *(void**)(*(char**)((char*)self + 0xA0) + 0x6E8) = (void*)&D_004595C0_00141480;
    *(void**)(*(char**)((char*)self + 0xA0) + 0x6D0) = D_00459B90;
    *(void**)(*(char**)((char*)self + 0xA0) + 0x6C0) = (void*)&D_00459608_00141480;
    if (!inChrg)
    {
        sVtblA_00141480 t1 = D_004595C0_00141480;
        *(void**)(*(char**)((char*)self + 0xA0) + 0x6E8) = &t1;
        char* base = *(char**)((char*)self + 0xA0) - 0xB0;
        int d = (char*)self - base;
        t1.e[1].delta = D_004595C0_00141480.e[1].delta + d;
        sVtblB_00141480 t2 = D_00459608_00141480;
        *(void**)(*(char**)((char*)self + 0xA0) + 0x6C0) = &t2;
        t2.e[1].delta = D_00459608_00141480.e[1].delta + d;
    }
    return self;
}

INCLUDE_ASM("ai/control/handplantcontrol", func_001415C8);

INCLUDE_ASM("ai/control/handplantcontrol", func_00141728);

INCLUDE_ASM("ai/control/handplantcontrol", func_00141888);

INCLUDE_ASM("ai/control/handplantcontrol", func_001419E8);

INCLUDE_ASM("ai/control/handplantcontrol", func_00141B48);

INCLUDE_ASM("ai/control/handplantcontrol", func_00141CA8);

INCLUDE_ASM("ai/control/handplantcontrol", func_00141E08);

INCLUDE_ASM("ai/control/handplantcontrol", func_00141F68);

INCLUDE_ASM("ai/control/handplantcontrol", func_001420C8);

INCLUDE_ASM("ai/control/handplantcontrol", cWipeoutControl_destroy);

//100%
extern "C" void cRider_cRider(void* self);

struct sVEntry_00142388 { short delta; short index; void* fn; };
struct sVtblA_00142388 { sVEntry_00142388 e[9]; } __attribute__((aligned(8)));
struct sVtblB_00142388 { sVEntry_00142388 e[22]; } __attribute__((aligned(8)));

extern const sVtblA_00142388 D_00458C10_00142388 __asm__("D_00458C10");
extern char D_00459B90[];
extern const sVtblB_00142388 D_00458C58_00142388 __asm__("D_00458C58");

// PORT: g++ 2.95 virtual-base construction. The class derives virtually from cRider (vbase pointer at
// +0x80, vbase at +0x90); when not most-derived, g++ copies cRider's overridden vtables to the stack
// and fixes up the this-deltas (expand_upcast_fixups). Written out by hand here.
extern "C" void* cWipeoutControl_cWipeoutControl(void* self, int inChrg)
{
    if (inChrg)
    {
        char* vb = (char*)self + 0x90;
        *(char**)((char*)self + 0x80) = vb;
        cRider_cRider(vb);
    }
    *(void**)(*(char**)((char*)self + 0x80) + 0x6E8) = (void*)&D_00458C10_00142388;
    *(void**)(*(char**)((char*)self + 0x80) + 0x6D0) = D_00459B90;
    *(void**)(*(char**)((char*)self + 0x80) + 0x6C0) = (void*)&D_00458C58_00142388;
    if (!inChrg)
    {
        sVtblA_00142388 t1 = D_00458C10_00142388;
        *(void**)(*(char**)((char*)self + 0x80) + 0x6E8) = &t1;
        char* base = *(char**)((char*)self + 0x80) - 0x90;
        int d = (char*)self - base;
        t1.e[1].delta = D_00458C10_00142388.e[1].delta + d;
        sVtblB_00142388 t2 = D_00458C58_00142388;
        *(void**)(*(char**)((char*)self + 0x80) + 0x6C0) = &t2;
        t2.e[1].delta = D_00458C58_00142388.e[1].delta + d;
    }
    return self;
}

INCLUDE_ASM("ai/control/handplantcontrol", func_001424D0);

INCLUDE_ASM("ai/control/handplantcontrol", func_00142630);

INCLUDE_ASM("ai/control/handplantcontrol", func_00142790);

INCLUDE_ASM("ai/control/handplantcontrol", func_001428F0);

INCLUDE_ASM("ai/control/handplantcontrol", func_00142A50);

extern "C" int func_00143FF0(void* self)
{
    return *(int*)((char*)self + 0xDE0);
}

extern "C" int func_00143FF8(void* self)
{
    return *(int*)((char*)self + 0xDE4);
}

extern "C" void func_00144000(void* self, int value)
{
    *(int*)((char*)self + 0xF40) = value;
}

extern "C" int func_00144008(void* self)
{
    return *(int*)((char*)self + 0xE70);
}

extern "C" int func_00144010(void* self, float t)
{
    return *(int*)((char*)self + 0xE20) != 0 && t < 1.0f;
}

struct sBytes8_HP
{
    char b[8];
};
extern sBytes8_HP D_0043CF20_b8[] __asm__("D_0043CF20");

extern "C" void func_00144040(char* self, int i)
{
    *(sBytes8_HP*)(self + 0xF44) = D_0043CF20_b8[i];
    *(short*)(self + 0xF38) = i;
}

//100%
void func_00144068(void* self)
{
}

extern "C" int func_00144070(void* self)
{
    return *(int*)((char*)self + 0xA8);
}

extern "C" int func_00144078(void* self)
{
    return *(int*)((char*)self + 0x78);
}

extern "C" int func_00144080(void* self)
{
    return *(int*)((char*)self + 0x7C);
}

extern "C" int func_00144088(void* self)
{
    return *(int*)((char*)self + 0x80);
}

extern "C" int func_00144090(void* self)
{
    return *(int*)((char*)self + 0x84);
}

extern "C" int func_00144098(void* self)
{
    return *(int*)((char*)self + 0x88);
}

struct sfunc_001440A0 {
    char pad[0x28];
    int values[1];
};

extern "C" int func_001440A0(sfunc_001440A0* self, int i)
{
    return self->values[i];
}

struct sfunc_001440B0 {
    char pad[0x40];
    int values[1];
};

extern "C" int func_001440B0(sfunc_001440B0* self, int i)
{
    return self->values[i];
}

struct sfunc_001440C0 {
    char pad[0x48];
    int values[1];
};

extern "C" int func_001440C0(sfunc_001440C0* self, int i)
{
    return self->values[i];
}

struct sfunc_001440D0 {
    char pad[0x5C];
    int values[1];
};

extern "C" int func_001440D0(sfunc_001440D0* self, int i)
{
    return self->values[i];
}

struct sfunc_001440E0 {
    char pad[0x70];
    int values[1];
};

extern "C" int func_001440E0(sfunc_001440E0* self, int i)
{
    return self->values[i];
}

extern "C" void func_001440F0(void* self, int value)
{
    *(int*)((char*)self + 0x14) = value;
}

extern "C" void func_001440F8(void* self, int value)
{
    *(int*)((char*)self + 0x8C) = value;
}

extern "C" int func_00144100(void* self)
{
    return *(int*)((char*)self + 0x8C);
}

extern "C" int func_00144108(void* self)
{
    return *(int*)((char*)self + 0x8);
}

extern "C" void func_00144110(void* self, int value)
{
    *(int*)((char*)self + 0x8) = value;
}

extern "C" int func_00144118(void* self)
{
    return *(int*)((char*)self + 0xC);
}

extern "C" void func_00144120(void* self)
{
    (*(int*)((char*)self + 0xC))++;
}

extern "C" void func_00144130(void* self, int value)
{
    *(int*)((char*)self + 0xC) = value;
}

// Frame counter at +0xC converted to whole seconds (60 fps).
extern "C" int func_00144138(void* self)
{
    return (int)((float)*(int*)((char*)self + 0xC) * (1.0f / 60.0f));
}

extern "C" int func_00144158(void* self)
{
    return *(int*)((char*)self + 0x0);
}

extern "C" int func_00144160(void* self)
{
    return *(int*)((char*)self + 0x1C);
}

extern "C" void func_00144168(void* self, int value)
{
    *(int*)((char*)self + 0x1C) = value;
}

struct sfunc_00144170 {
    char pad[0x20];
    int values[1];
};

extern "C" void func_00144170(sfunc_00144170* self, int i, int value)
{
    self->values[i] = value;
}

struct sfunc_00144180 {
    char pad[0x20];
    int values[1];
};

extern "C" int func_00144180(sfunc_00144180* self, int i)
{
    return self->values[i];
}

extern "C" int func_00144190(void* self)
{
    return *(int*)((char*)self + 0x18);
}

extern "C" int func_00144198(void* self)
{
    return *(int*)((char*)self + 0xA4);
}

//100%
int func_001441A0(void* self, void* a1)
{
    int t0 = 2;
    *(int*)((char*)a1 + 0x8) = t0;
    *(int*)((char*)self + 0x704) = (int)((char*)*(void**)((char*)self + 0x704) - 0x1);
    return t0;
}

//100%
struct sHpVE_41B8 {
    short delta;
    short index;
    float* (*fn)(void*);
};

struct sHpVec3_41B8 {
    float x, y, z;
};

struct sHpGround_41B8 {
    char pad_0x0[0x14];
    float height;           // 0x14
    char pad_0x18[0x8];
};

// Handplant zone: a sphere (type 2 = disabled).
struct sHpZone_41B8 {
    float radius;           // 0x0
    int f4;
    int type;               // 0x8
    sHpVec3_41B8 center;    // 0xC
    int f18;
};

struct sHpLevel_41B8 {
    int level;
    int f4;
    int f8;
};

struct sHpGame_41B8 {
    char pad_0x0[0x28];
    char* riders[8];        // 0x28
};

struct sHpCtl_41B8 {
    sHpGame_41B8* game;     // 0x0
    sHpZone_41B8 zones[64]; // 0x4
    int numZones;           // 0x704
    int useHeight;          // 0x708
    sHpLevel_41B8 levels[4];// 0x70C
};

extern "C" void func_002DA1C0(sHpGround_41B8* out, sHpVec3_41B8* pos);

// Handplant difficulty level for player pl: at least the height band's level, and only above 1 when the rider is
// inside one of the enabled zones.
extern "C" int func_001441B8(sHpCtl_41B8* self, int pl)
{
    int lvl = self->levels[pl].level;
    char* rider = self->game->riders[pl];
    if (lvl == 0) {
        return 0;
    }
    char* o = rider + 0x6C0;
    sHpVE_41B8* vt = *(sHpVE_41B8**)o;
    float* pos = vt[5].fn(o + vt[5].delta);
    if (self->useHeight != 0) {
        sHpGround_41B8 g;
        sHpVec3_41B8 p;
        p.x = pos[0];
        p.y = pos[1];
        p.z = pos[2];
        func_002DA1C0(&g, &p);
        int band = 1;
        if (g.height < 1200.446f) {
            band = 3;
        } else if (g.height < 2999.697f) {
            band = 2;
        }
        if (lvl < band) {
            return band;
        }
    }
    if (lvl < 2) {
        return 1;
    }
    if (self->numZones == 0) {
        return 1;
    }
    int n = self->numZones;
    sHpZone_41B8* z = self->zones;
    for (int i = 0; i < 64 && n != 0; i++, z++) {
        if (z->type == 2) {
            continue;
        }
        n--;
        float d = z->center.x - pos[0];
        float r2 = z->radius * z->radius;
        d = d * d;
        if (r2 < d) {
            continue;
        }
        float dy = z->center.y - pos[1];
        dy = dy * dy;
        if (r2 < dy) {
            continue;
        }
        float dz = z->center.z - pos[2];
        d = d + dy + dz * dz;
        if (!(r2 < d)) {
            return lvl;
        }
    }
    return 1;
}

//100%
struct sKey_144368 {
    int level;
    int x;
    int y;
    int z;
};

struct sBox_144368 {
    float min[4];
    float max[4];
};

struct sTree_144368 {
    void* f0;
    sBox_144368* boxes;
    int count;
};

struct sNode_144368 {
    sNode_144368* child[8];
};

extern "C" void func_00101A28(void* a, sNode_144368* node, int leaf);

extern "C" void func_00144368(sTree_144368* self, sNode_144368* node, sKey_144368* key)
{
    int n = self->count;
    int i = 0;
    int ok;
    do {
        if (i == n) {
            return;
        }
        union { int i; float f; } u;
        u.i = (key->level + 0x7F) << 23;
        float s = u.f;
        // PORT: pointer arithmetic through int
        sBox_144368* b = (sBox_144368*)((i << 5) + (int)self->boxes);
        ok = 0;
        if (((float)key->x - 0.2f) * s <= b->max[0] && ((float)key->y - 0.2f) * s <= b->max[1] && ((float)key->z - 0.2f) * s <= b->max[2]
            && b->min[0] <= ((float)(key->x + 1) + 0.2f) * s && b->min[1] <= ((float)(key->y + 1) + 0.2f) * s && b->min[2] <= ((float)(key->z + 1) + 0.2f) * s) {
            ok = 1;
        }
        i++;
    } while (!ok);
    int leaf = key->level < 14;
    func_00101A28(self->f0, node, leaf);
    if (leaf) {
        return;
    }
    if (key->level == 11) {
        return;
    }
    sKey_144368 k;
    k.level = key->level - 1;
    k.x = key->x * 2;
    k.y = key->y * 2;
    k.z = key->z * 2;
    if (node->child[0]) func_00144368(self, node->child[0], &k);
    k.x++;
    if (node->child[4]) func_00144368(self, node->child[4], &k);
    k.y++;
    if (node->child[6]) func_00144368(self, node->child[6], &k);
    k.x--;
    if (node->child[2]) func_00144368(self, node->child[2], &k);
    k.z++;
    if (node->child[3]) func_00144368(self, node->child[3], &k);
    k.x++;
    if (node->child[7]) func_00144368(self, node->child[7], &k);
    k.y--;
    if (node->child[5]) func_00144368(self, node->child[5], &k);
    k.x--;
    if (node->child[1]) func_00144368(self, node->child[1], &k);
}

extern "C" void* func_00311958(void* self);

//100%
void* func_00144610(void* self)
{
    return func_00311958(self);
}

extern "C" void cRiderAnimBase_cRiderAnimBase(void* self);
extern char D_00458458[];

extern "C" void* func_00144630(char* self)
{
    cRiderAnimBase_cRiderAnimBase(self);
    *(void**)(self + 0x58) = D_00458458;
    *(int*)(self + 0x60) = 0;
    *(int*)(self + 0x64) = 0;
    return self;
}

//100%
// PORT: ulong is 64-bit here
extern "C" void func_00144670(void* self, int bit)
{
    ulong mask = (ulong)1 << bit;
    ulong a = *(ulong*)self;
    *(ulong*)self = a & ~mask;
    *(ulong*)((char*)self + 0x8) |= mask & a;
}

//100%
extern "C" bool func_001446A0(void* self, int bit)
{
    ulong mask = (ulong)1 << bit;
    return (*(ulong*)self & mask) != 0;
}

//100%
extern "C" bool func_001446B8(void* self, int bit)
{
    ulong mask = (ulong)1 << bit;
    return (*(ulong*)((char*)self + 0x8) & mask) != 0;
}

extern "C" void func_001446D0(void* self, int a, int b)
{
    *(int*)((char*)self + 0xDF0) = a;
    *(int*)((char*)self + 0xDF4) = b;
}

extern "C" int func_001446E0(void* self)
{
    return *(int*)((char*)self + 0xDF0);
}

//100%
float func_001446E8(void* self)
{
    return 0.0f;
}

INCLUDE_ASM("ai/control/handplantcontrol", func_001446F8);

//100%
extern "C" int func_001448A8(void* self)
{
    return *(int*)((char*)self + 0x70) == 3;
}

extern "C" void* func_0013FB20(int, int);

//99.38%
void* func_001448B8(void* self)
{
    return func_0013FB20(1, 0xffff);
}

