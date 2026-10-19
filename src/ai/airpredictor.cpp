#include "common.h"
#include "ai/airpredictor.h"

//100%
struct sQuadR {
    int x[4];
} __attribute__((aligned(16)));

struct sPair8 {
    int x[2];
};

extern sQuadR D_004FF160;
extern sQuadR D_004FF120;
extern sPair8 D_004A5960[];

extern "C" void cAirPredictor_reset(cAirPredictor* ap)
{
    ap->mStatus = AIRPRED_EXTENDING;
    *(int*)&ap->mElapsed = 0;
    *(int*)&ap->mPredTime = 0;
    *(int*)&ap->mApexTime = 0;
    *(int*)&ap->mStepTime = 0;
    *(sQuadR*)&ap->mHitNormal = D_004FF160;
    *(sQuadR*)&ap->mHitHeading = D_004FF120;
    ap->mHitType = -1;
    *(unsigned int*)&ap->mHitSurface = 0xFFFFFFFF;
    *(sPair8*)&ap->mHitParam = D_004A5960[0];
}

INCLUDE_ASM("ai/airpredictor", cAirPredictor_extendPrediction);

//100%
struct sQuad;
void cAirPredictor_initLaunch(cAirPredictor* ap, sQuad* a, sQuad* b);

extern "C" void cAirPredictor_startLaunchIntoAir(cAirPredictor* ap, sQuad* a, sQuad* b, float t)
{
    cAirPredictor_reset(ap);
    ap->mSpeedCap = t;
    cAirPredictor_initLaunch(ap, a, b);
}

// 16-byte aligned: the original copies these with lq/sq, which require it
// (PS2 VU-style quadword).
struct sQuad {
    int x[4];
} __attribute__((aligned(16)));

//100%
void cAirPredictor_initLaunch(cAirPredictor* ap, sQuad* a, sQuad* b)
{
    ap->mStatus = AIRPRED_EXTENDING;
    *(sQuad*)&ap->mCurPos = *a;
    *(sQuad*)&ap->mCurVel = *b;
    *(sQuad*)&ap->mPredPos = *a;
    *(sQuad*)&ap->mPredVel = *b;
    ap->mPredTime = ap->mElapsed;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern sQuadR D_004FF130;
extern sQuadR D_004FF140;
extern sQuadR D_004FF160;
extern "C" void cAirPredictor_extendPrediction(cAirPredictor* ap);

struct sVec4_3648
{
    float x, y, z, w;
    sVec4_3648() {}
} __attribute__((aligned(16)));

// cAirPredictor_integrateStep is defined later in the unit (with its own vector type).
float cAirPredictor_integrateStep_3648(cAirPredictor* ap, sVec4_3648* pos, sVec4_3648* vel, sVec4_3648* outPos, sVec4_3648* outVel) __asm__("cAirPredictor_integrateStep");

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_3648 vu0Scale_3648(const sVec4_3648& v, float s)
{
    sVec4_3648 r;
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
static inline sVec4_3648 vu0Add_3648(const sVec4_3648& a, const sVec4_3648& b)
{
    sVec4_3648 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

extern "C" void cAirPredictor_update(cAirPredictor* ap, sQuad* a, sQuad* b, float dt)
{
    if (ap->mPredTime > 60.0f) {
        if (ap->mStatus == AIRPRED_RESTARTED) {
            ap->mStatus = AIRPRED_GAVE_UP;
            *(sQuadR*)&ap->mHitPos = D_004FF130;
            *(sQuadR*)&ap->mHitHeading = D_004FF140;
            *(sQuadR*)&ap->mHitNormal = D_004FF160;
            ap->mHitType = 0xD;
        } else {
            cAirPredictor_initLaunch(ap, a, b);
            ap->mStatus = AIRPRED_RESTARTED;
        }
    } else {
        if (ap->mStatus == AIRPRED_LANDED && ap->mPredTime - ap->mElapsed < -0.2f) {
            cAirPredictor_initLaunch(ap, a, b);
        }
        int st = ap->mStatus;
        if (st == AIRPRED_EXTENDING) {
            cAirPredictor_extendPrediction(ap);
            while (ap->mStatus == AIRPRED_EXTENDING && ap->mPredTime < ap->mElapsed + dt) {
                cAirPredictor_extendPrediction(ap);
            }
        } else if (st == AIRPRED_RESTARTED) {
            cAirPredictor_extendPrediction(ap);
            while (ap->mStatus == AIRPRED_RESTARTED && ap->mPredTime < ap->mElapsed + dt) {
                cAirPredictor_extendPrediction(ap);
            }
        }
    }
    float t = ap->mElapsed - ap->mStepTime + dt;
    while (t >= 0.01666666753590107f) {
        t -= 0.01666666753590107f;
        cAirPredictor_integrateStep_3648(ap, (sVec4_3648*)&ap->mCurPos, (sVec4_3648*)&ap->mCurVel, (sVec4_3648*)&ap->mCurPos, (sVec4_3648*)&ap->mCurVel);
        ap->mStepTime += 0.01666666753590107f;
    }
    if (t > 0.009999999776482582f) {
        sVec4_3648 p;
        sVec4_3648 v;
        cAirPredictor_integrateStep_3648(ap, (sVec4_3648*)&ap->mCurPos, (sVec4_3648*)&ap->mCurVel, &p, &v);
        float k = t * 59.999996185302734f;
        *(sVec4_3648*)a = vu0Add_3648(vu0Scale_3648(p, k), vu0Scale_3648(*(sVec4_3648*)&ap->mCurPos, 1.0f - k));
        *(sVec4_3648*)b = vu0Add_3648(vu0Scale_3648(v, k), vu0Scale_3648(*(sVec4_3648*)&ap->mCurVel, 1.0f - k));
        ((float*)a)[3] = 1.0f;
    } else {
        *(sQuad*)a = *(sQuad*)&ap->mCurPos;
        *(sQuad*)b = *(sQuad*)&ap->mCurVel;
    }
    ap->mElapsed += dt;
}

//100%
void func_00113998(void* self)
{
    *(int*)&((cAirPredictor*)self)->mPredTime = 0;
}

//100%
struct sVec4_1139A0
{
    float x, y, z, w;
    sVec4_1139A0() {}
    sVec4_1139A0(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_1139A0 vu0Scale_1139A0(const sVec4_1139A0& v, float s)
{
    sVec4_1139A0 r;
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
static inline sVec4_1139A0 vu0Add_1139A0(const sVec4_1139A0& a, const sVec4_1139A0& b)
{
    sVec4_1139A0 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector times-assign scalar).
static inline void vu0ScaleEq_1139A0(sVec4_1139A0& v, float s)
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

// PORT: PS2-only VU0 inline asm (4-component length).
static inline float vu0Length_1139A0(const sVec4_1139A0& v)
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

extern "C" float cAirPredictor_integrateStep(cAirPredictor* ap, sVec4_1139A0* pos, sVec4_1139A0* vel, sVec4_1139A0* outPos, sVec4_1139A0* outVel)
{
    *outPos = vu0Add_1139A0(*pos, vu0Scale_1139A0(*vel, 0.01666666753590107f));
    float dx = vel->x * -0.0033333336468786f;
    float dy = vel->y * -0.0033333336468786f;
    float g = -31.666667938232422f;
    if (vel->z > 0.0f) g = -14.166666984558105f;
    *outVel = vu0Add_1139A0(*vel, sVec4_1139A0(dx, dy, g, 0.0f));
    float len = vu0Length_1139A0(*outVel);
    if (ap->mSpeedCap < len)
    {
        vu0ScaleEq_1139A0(*outVel, ap->mSpeedCap / len);
        len = ap->mSpeedCap;
    }
    return len;
}

extern "C" void func_00113A98()
{
}

//100%
struct sVEntry00113AA0 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cAirPredictor_saveState(cAirPredictor* ap, void* obj)
{
    sVEntry00113AA0* vt = *(sVEntry00113AA0**)obj;
    vt[1].fn((char*)obj + vt[1].delta, ap, 0xB0);
}

//100%
struct sVEntry00113AD8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cAirPredictor_loadState(cAirPredictor* ap, void* obj)
{
    sVEntry00113AD8* vt = *(sVEntry00113AD8**)obj;
    vt[2].fn((char*)obj + vt[2].delta, ap, 0xB0);
}

