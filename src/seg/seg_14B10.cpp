#include "common.h"

//100%
extern "C" void cAI_forceAIState(void *);

extern "C" void cAI_setAIState(void *arg0, int arg1) {
    int old = *(int *)((char*)arg0 + 0);
    if (arg1 != old) {
        *(int *)((char*)arg0 + 4) = old;
        *(int *)((char*)arg0 + 0x9C) = *(int *)((char*)arg0 + 0x98);
        cAI_forceAIState(arg0);
    }
}

//100%
extern char D_00456C58[];
extern char D_00456C68[];
extern char D_004A0E90[];
extern char D_00456C78[];
extern char D_004A0E98[];
extern char D_004A0EA0[];
extern char D_00456C88[];
// The unit declares cAI_forceAIState with one arg; bind the real 2-arg form here.
void cAI_forceAIState_2(char* self, int state) __asm__("cAI_forceAIState");

void cAI_forceAIState_2(char* self, int state)
{
    switch (state) {
    case 1:
        *(int*)(self + 0x0) = 1;
        *(char**)(self + 0xA0) = D_00456C58;
        *(char**)(self + 0x98) = self + 0xAC;
        return;
    case 2:
        *(int*)(self + 0x0) = 2;
        *(char**)(self + 0xA0) = D_00456C68;
        *(char**)(self + 0x98) = self + 0xB0;
        return;
    case 3:
        *(int*)(self + 0x0) = 3;
        *(char**)(self + 0xA0) = D_004A0E90;
        *(char**)(self + 0x98) = self + 0xB4;
        return;
    case 4:
        *(int*)(self + 0x0) = 4;
        *(char**)(self + 0xA0) = D_00456C78;
        *(char**)(self + 0x98) = self + 0xBC;
        return;
    case 5:
        *(int*)(self + 0x0) = 5;
        *(char**)(self + 0xA0) = D_004A0E98;
        *(char**)(self + 0x98) = self + 0xC0;
        return;
    case 6:
        *(int*)(self + 0x0) = 6;
        *(char**)(self + 0xA0) = D_004A0EA0;
        *(char**)(self + 0x98) = self + 0xC4;
        return;
    case 7:
        *(int*)(self + 0x0) = 7;
        *(char**)(self + 0xA0) = D_00456C88;
        *(char**)(self + 0x98) = self + 0xC8;
        return;
    }
    *(char**)(self + 0x98) = 0;
    *(char**)(self + 0xA0) = 0;
    *(int*)(self + 0x0) = 0;
}

//100%
class cAIState_3C20 {
public:
    virtual void m0(void *);
    virtual void m1(void *);
    virtual void m2(void *);
};

extern "C" void func_00113C20(char *self) {
    if (*(int *)(self + 4) != *(int *)(self + 0)) {
        cAIState_3C20 *prev = *(cAIState_3C20 **)(self + 0x9C);
        if (prev != 0)
            prev->m1(self);
        (*(cAIState_3C20 **)(self + 0x98))->m0(self);
        *(cAIState_3C20 **)(self + 0x9C) = 0;
        *(int *)(self + 4) = *(int *)(self + 0);
    }
    (*(cAIState_3C20 **)(self + 0x98))->m2(self);
}

extern "C" void RaceStateGameInit_Enter(void) {
}

//100%
extern "C" void cAI_setAIState(void *, int);

extern "C" void func_00113CC0(void *arg0, void *arg1) {
    cAI_setAIState(arg1, 2);
}

extern "C" void RaceStateGameInit_Exit(void) {
}

//100%
extern "C" void RaceStateFreeride_Enter(void *arg0, void *arg1) {
    (*(int *)((char*)(arg1) + (0x14))) = 0;
}

//100%
extern "C" void cAI_setAIState(void *, int);

extern "C" void func_00113CF0(void *arg0, void *arg1) {
    cAI_setAIState(arg1, 5);
}

extern "C" void RaceStateFreeride_Exit(void) {
}

//100%
extern "C" void RaceStatePreRace_Enter(void *arg0, void *arg1) {
    (*(int *)((char*)(arg1) + (0xC))) = 0;
    (*(int *)((char*)(arg0) + (4))) = 0;
}

extern "C" void RaceStatePreRace_Update(void) {
}

extern "C" void RaceStatePreRace_Exit(void) {
}

//100%
extern "C" void RaceStateCountdown_Enter(void *arg0, void *arg1) {
    (*(int *)((char*)(arg1) + (0x1C))) = 0xB4;
}

//100%
extern "C" void cAI_setAIState(void *, int);

extern "C" void func_00113D48(void *arg0, void *arg1) {
    int temp_2;

    temp_2 = (*(int *)((char*)(arg1) + (0x1C)));
    if (temp_2 <= 0) {
        cAI_setAIState(arg1, 5);
        return;
    }
    (*(int *)((char*)(arg1) + (0x1C))) = (int) (temp_2 - 1);
}

//100%
extern "C" void RaceStateCountdown_Exit(void *arg0, void *arg1) {
    (*(int *)((char*)(arg1) + (0x1C))) = 0;
}

//100%
extern "C" void cGameComm_OnRaceStart(int);
extern int D_004A2EEC;

extern "C" void func_00113D88(void) {
    if (D_004A2EEC != 0) {
        cGameComm_OnRaceStart(D_004A2EEC);
    }
}

//100%
extern "C" void cAI_setAIState(void *, int);
extern "C" int cAI_haveAllPlayersFinished(void *);
extern "C" void func_00231250(int, int, int, int);
extern void *D_004A28A8;

extern "C" void func_00113DB0(void *arg0, void *arg1) {
    (*(int *)((char*)(arg1) + (0xC))) = (int) ((*(int *)((char*)(arg1) + (0xC))) + 1);
    if (cAI_haveAllPlayersFinished(arg1) == 1) {
        cAI_setAIState(arg1, 6);
        func_00231250((*(int *)((char*)(D_004A28A8) + (0x84))), 5, 0, 0);
    }
}

//100%
extern "C" void cGameComm_OnRaceEnd(int);
extern int D_004A2EEC;

extern "C" void func_00113E18(void) {
    if (D_004A2EEC != 0) {
        cGameComm_OnRaceEnd(D_004A2EEC);
    }
}

extern "C" void RaceStateEndRace_Update(void) {
}

extern "C" void RaceStateEndRace_Exit(void) {
}

//100%
extern "C" void cAI_removeAllRiders(int);

extern "C" void func_00113E50(int arg0, int arg1) {
    cAI_removeAllRiders(arg1);
}

extern "C" void RaceStateShutdown_Update(void) {
}

extern "C" void RaceStateShutdown_Exit(void) {
}

//100%
struct sV4_3E80 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float Len_3E80(const sV4_3E80& v)
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

// PORT: PS2-only FPU asm (absolute value).
static inline float Abs_3E80(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

// PORT: `<?` is the g++ minimum operator (EE min.s).
static inline float Clamp_3E80(float v, float lo, float hi)
{
    return (v >= lo) ? (v <? hi) : lo;
}

extern "C" void cRider_SetSlew0Target(char *self, float arg1) {
    float r = Len_3E80(*(sV4_3E80 *)(self + 0x1E0)) / 694.538818359375f;
    if (r < 1.0f)
        arg1 = arg1 * r;
    float d = Abs_3E80(arg1 - *(float *)(self + 0x1F0)) * 12.002403259277344f;
    float m = Clamp_3E80(d, 0.10000000149011612f, 14.001209259033203f);
    int st = *(int *)(self + 0x438);
    if (st == 2 || st == 3 || st == 0xD)
        m = m * 0.7561339735984802f;
    *(float *)(self + 0x1F8) = arg1;
    *(float *)(self + 0x1F4) = m * 0.01666666753590107f;
}

//100%
// PORT: PS2-only FPU asm (absolute value).
static inline float Abs_3F38(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

// PORT: `<?` is the g++ minimum operator (EE min.s).
static inline float Clamp_3F38(float v, float lo, float hi)
{
    return (v >= lo) ? (v <? hi) : lo;
}

extern "C" void cRider_SetSlew5Target(void *self, float arg1) {
    float d = Abs_3F38(arg1 - *(float *)((char*)self + 0x22C)) * 7.0f;
    float m = Clamp_3F38(d, 0.1f, 8.0f);
    *(float *)((char*)self + 0x234) = arg1;
    *(float *)((char*)self + 0x230) = m * 0.01666666753590107f;
}

INCLUDE_ASM("seg/seg_14B10", cRider_SetSlew3And4Targets);

//100%
extern "C" int func_0028B180();
extern "C" void func_002F6AC8(char *, int);
extern "C" void cSSXAudio_StartBoostSound(int mgr, char* rider, int b);
extern "C" void cSSXAudio_PlayBoostEmptySound(int mgr, char* rider);
extern "C" void cSSXAudio_StopBoostSound(int mgr, char* rider);

extern "C" void cRider_HandleBoostInput(char* s, int a, int b)
{
    if (b) func_002F6AC8(*(char**)(s + 0x77C) + 0xD20, 0);
    if (a) {
        if (*(float*)(s + 0x2F8) > 0.0f) {
            if (*(float*)(s + 0x2FC) == 0.0f) {
                float x = *(float*)(s + 0x2F8);
                if (x > 0.6666666865348816f) *(float*)(s + 0x2FC) = 1.0f;
                else if (x > 0.3333333432674408f) *(float*)(s + 0x2FC) = 0.625f;
                else *(float*)(s + 0x2FC) = 0.25f;
                cSSXAudio_StartBoostSound(func_0028B180(), s, b);
            }
            if (*(float*)(s + 0x2E8) == 0.0f && *(int*)(s + 0x304) != 0 && *(int*)(s + 0x2F4) < 10) {
                *(float*)(s + 0x2F8) -= 0.00150679936632514f;
            }
            return;
        }
        if (b) cSSXAudio_PlayBoostEmptySound(func_0028B180(), s);
    }
    if (*(float*)(s + 0x2FC) > 0.0f) cSSXAudio_StopBoostSound(func_0028B180(), s);
    *(float*)(s + 0x2FC) = 0.0f;
}

INCLUDE_ASM("seg/seg_14B10", cRider_LaunchIntoAir);

INCLUDE_ASM("seg/seg_14B10", cRider_TurnAroundIfBackward);

INCLUDE_ASM("seg/seg_14B10", func_00114DB8);

//100%
struct Q_5168 {
    float x, y, z, w;
    Q_5168() {}
    Q_5168(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
} __attribute__((aligned(16)));

extern "C" void func_0031BE50(float* s, float* c, float angle);
extern "C" void cRiderAnimBase_changeHeadingOffset(void* self, float angle);
extern Q_5168 D_004FF130;
extern Q_5168 D_004FF160;

static inline Q_5168 AxisAngle_5168(const Q_5168& axis, float angle)
{
    float s, c;
    func_0031BE50(&s, &c, angle * 0.5f);
    return Q_5168(s * axis.x, s * axis.y, s * axis.z, c);
}

static inline void SetHeading_5168(char* a, float angle)
{
    *(Q_5168*)(a + 0x30) = D_004FF130;
    *(Q_5168*)(a + 0x40) = AxisAngle_5168(D_004FF160, -angle);
}

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline Q_5168 Scale_5168(const Q_5168& v, float s)
{
    Q_5168 r;
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

extern "C" void cRider_ToggleStance(char* s)
{
    *(int*)(s + 0x320) ^= 1;
    cRiderAnimBase_changeHeadingOffset(*(void**)(s + 0x784), 3.1415927410125732f);
    if (*(int*)(s + 0x320)) {
        SetHeading_5168(*(char**)(s + 0x784), 3.1415927410125732f);
    } else {
        SetHeading_5168(*(char**)(s + 0x784), 0.0f);
    }
    *(int*)(*(char**)(s + 0x784) + 0x18) = *(int*)(s + 0x320);
    *(Q_5168*)(s + 0x3A0) = Scale_5168(*(Q_5168*)(s + 0x3A0), -1.0f);
    *(Q_5168*)(s + 0x3B0) = Scale_5168(*(Q_5168*)(s + 0x3B0), -1.0f);
    *(float*)(s + 0x1F0) = -*(float*)(s + 0x1F0);
    *(float*)(s + 0x1F8) = -*(float*)(s + 0x1F8);
    *(float*)(s + 0x214) = -*(float*)(s + 0x214);
    *(float*)(s + 0x21C) = -*(float*)(s + 0x21C);
    *(float*)(s + 0x208) = -*(float*)(s + 0x208);
    *(float*)(s + 0x210) = -*(float*)(s + 0x210);
    *(float*)(s + 0x1FC) = -*(float*)(s + 0x1FC);
    *(float*)(s + 0x204) = -*(float*)(s + 0x204);
    *(float*)(s + 0x280) = -*(float*)(s + 0x280);
    *(float*)(s + 0x288) = -*(float*)(s + 0x288);
}

INCLUDE_ASM("seg/seg_14B10", func_00115358);

//100%
extern "C" int cRiderAnimBase_play_5B58(void* self, int anim, int flags, float blend) __asm__("cRiderAnimBase_play");
int cRider_getMotionMode(void* self);
extern "C" void cRider_rotateAboutAxis(char* self, Q_5168 q, float angle);
// PORT: the unit defines cRider_EmptyStanceHook with no parameters; this call passes self.
extern "C" void cRider_EmptyStanceHook_5640(char* self) __asm__("cRider_EmptyStanceHook");

extern "C" void func_00115640(char* s)
{
    if (*(int*)(s + 0x328) == 0) return;
    if (cRider_getMotionMode(s) == 1) {
        if ((unsigned int)(*(int*)(s + 0x328) - 3) < 2) {
            SetHeading_5168(*(char**)(s + 0x784), 0.0f);
        }
        if (*(int*)(s + 0x328) == 3) cRiderAnimBase_play_5B58(*(void**)(s + 0x784), 0x11A, 0, -1.0f);
        else if (*(int*)(s + 0x328) == 4) cRiderAnimBase_play_5B58(*(void**)(s + 0x784), 0x115, 0, -1.0f);
        else cRiderAnimBase_play_5B58(*(void**)(s + 0x784), 0x10C, 0, -1.0f);
    } else if (cRider_getMotionMode(s) == 0) {
        if (*(int*)(s + 0x328) == 3) {
            cRider_rotateAboutAxis(s, *(Q_5168*)(s + 0x1C0), 1.5707963705062866f);
            cRiderAnimBase_changeHeadingOffset(*(void**)(s + 0x784), 1.5707963705062866f);
            SetHeading_5168(*(char**)(s + 0x784), 0.0f);
        } else if (*(int*)(s + 0x328) == 4) {
            cRider_rotateAboutAxis(s, *(Q_5168*)(s + 0x1C0), -1.5707963705062866f);
            cRiderAnimBase_changeHeadingOffset(*(void**)(s + 0x784), -1.5707963705062866f);
            SetHeading_5168(*(char**)(s + 0x784), 0.0f);
        }
        cRiderAnimBase_play_5B58(*(void**)(s + 0x784), 5, 0, -1.0f);
    }
    *(int*)(s + 0x328) = 0;
    cRider_EmptyStanceHook_5640(s);
}

//100%
extern "C" float func_0031C228(float x);
extern "C" void func_0031BE50(float* s, float* c, float angle);

// PORT: sqrt.s (sqrtf without errno check)
static inline float Sqrt_58B8(float x)
{
    float r;
    __asm__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline float Atan2_58B8(float y, float x)
{
    if (x == 0.0f)
    {
        if (y == 0.0f)
            return y;
        if (y >= 0.0f)
            return 1.5707963705062866f;
        return -1.5707963705062866f;
    }
    float a = func_0031C228(y / x);
    if (x < 0.0f)
    {
        if (y > 0.0f)
            a += 3.1415927410125732f;
        else
            a -= 3.1415927410125732f;
    }
    return a;
}

// PORT: PS2-only abs.s asm helper (fabsf off-PS2).
static inline float Abs_58B8(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

// PORT: g++ minimum operator
static inline float Clamp_58B8(float v, float lo, float hi)
{
    return v >= lo ? v <? hi : lo;
}

extern "C" void Input_QuantizeStickDirection(void* self, float* y, float* x, float step, float eps)
{
    float px, py, len, ang, t, r;
    float sc[2];
    if (Abs_58B8(*x) <= eps) *x = 0.0f;
    if (Abs_58B8(*y) <= eps) *y = 0.0f;
    px = *x;
    py = *y;
    len = Sqrt_58B8(px * px + py * py);
    if (len == 0.0f) return;
    ang = Atan2_58B8(py, px);
    t = ang / step;
    if (ang < 0.0f) r = t + -0.5f;
    else r = t + 0.5f;
    func_0031BE50(&sc[0], &sc[1], (float)(int)r * step);
    *x = Clamp_58B8(sc[1] * len, -1.0f, 1.0f);
    *y = Clamp_58B8(sc[0] * len, -1.0f, 1.0f);
    if (__builtin_fabsf(*x) < 0.001f) *x = 0.0f;
    if (__builtin_fabsf(*y) < 0.001f) *y = 0.0f;
}

//100%
extern "C" int cBE_getBE();
extern "C" int cBE_getInterface__Fv(int, int);
extern "C" float cBECharacterInterface_GetRiderSizeScale(int, int);

extern "C" float func_00115AB0(void *arg0) {
    return (cBECharacterInterface_GetRiderSizeScale(cBE_getInterface__Fv(cBE_getBE(), 2), (*(int *)((char*)(arg0) + (0x86C)))) * -90.0f) + 75.0f;
}

//100%
extern "C" int cBE_getBE();
extern "C" int cBE_getInterface__Fv(int, int);
extern "C" float cBECharacterInterface_GetRiderSizeScale(int, int);

extern "C" float func_00115B08(void *arg0) {
    return (cBECharacterInterface_GetRiderSizeScale(cBE_getInterface__Fv(cBE_getBE(), 2), (*(int *)((char*)(arg0) + (0x86C)))) * 90.0f) - 90.0f;
}

//100%
extern "C" int cRiderAnimBase_getChannelAnimClass(void*, int);
extern "C" int getGameTick();
extern "C" int cRiderAnimBase_play_5B58(void* self, int anim, int flags, float blend) __asm__("cRiderAnimBase_play");
extern "C" void* func_0028B180_5B58() __asm__("func_0028B180");
extern "C" void cSSXAudio_RiderSay2082(void* snd, void* self, int a);
extern "C" int cRider_getControlState_5B58(void*) __asm__("cRider_getControlState__FPv");

extern "C" void cRider_UpdateTimedEventAnim(char* self)
{
    if (*(int*)(self + 0x358) == 0) {
        return;
    }
    if (cRiderAnimBase_getChannelAnimClass(*(void**)(self + 0x784), 2) == 5) {
        return;
    }
    if (cRiderAnimBase_getChannelAnimClass(*(void**)(self + 0x784), 1) != 0) {
        return;
    }
    if (cRiderAnimBase_getChannelAnimClass(*(void**)(self + 0x784), 2) == 10) {
        return;
    }
    int dt = getGameTick() - *(int*)(self + 0x354);
    if (dt < 0xB4) {
        if (dt < 0) {
            return;
        }
        switch (*(int*)(self + 0x358)) {
        case 1:
            *(long*)(*(char**)(self + 0x784) + 0x20) = *(long*)(self + 0x8C8);
            cRiderAnimBase_play_5B58(*(void**)(self + 0x784), 0x13B, 0, -1.0f);
            *(long*)(*(char**)(self + 0x784) + 0x20) = -1;
            cSSXAudio_RiderSay2082(func_0028B180_5B58(), self, 0);
            break;
        case 2:
            *(long*)(*(char**)(self + 0x784) + 0x20) = *(long*)(self + 0x8C8);
            cRiderAnimBase_play_5B58(*(void**)(self + 0x784), 0x13B, 0, -1.0f);
            *(long*)(*(char**)(self + 0x784) + 0x20) = -1;
            cSSXAudio_RiderSay2082(func_0028B180_5B58(), self, 1);
            break;
        case 3:
            *(long*)(*(char**)(self + 0x784) + 0x20) = *(long*)(self + 0x8C8);
            cRiderAnimBase_play_5B58(*(void**)(self + 0x784), 0x13B, 0, -1.0f);
            *(long*)(*(char**)(self + 0x784) + 0x20) = -1;
            break;
        case 4:
            *(long*)(*(char**)(self + 0x784) + 0x20) = *(long*)(self + 0x8C8);
            cRiderAnimBase_play_5B58(*(void**)(self + 0x784), 0x13A, 0, -1.0f);
            *(long*)(*(char**)(self + 0x784) + 0x20) = -1;
            break;
        case 5:
        case 6:
            if (__builtin_fabsf(*(float*)(self + 0x1FC)) < 0.75f) {
                if (cRider_getControlState_5B58(self) == 0) {
                    cRiderAnimBase_play_5B58(*(void**)(self + 0x784), 0x13E, 0, -1.0f);
                }
            }
            break;
        }
    }
    *(int*)(self + 0x358) = 0;
    *(int*)(self + 0x354) = -1;
}

INCLUDE_ASM("seg/seg_14B10", func_00115D48);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
void cRiderMetrix_evAutoResetSurface(void *);
extern "C" void cRider_setMotionMode_6120(void *, int) __asm__("cRider_setMotionMode__FPv");
extern "C" void cRider_setControlState_6120(void *, int) __asm__("cRider_setControlState__FPv");
extern "C" int func_0028B180();
extern "C" void cSSXAudio_OnRiderReset(int, void *);
extern "C" void Replay_OnRiderReset(int, int);
extern void *D_004A28A8;

extern "C" int cRider_CheckResetPath(char *self, int arg1, int arg2) {
    if (arg1 != 0 || arg2 != 0) {
        *(int *)(self + 0x2E8) = 0;
        *(int *)(self + 0x2EC) = 0;
        if (arg2 == 1 || arg2 == 4)
            cRiderMetrix_evAutoResetSurface(*(void **)(self + 0x790));
        *(int *)(*(char **)(self + 0x77C) + 0x350) = (arg2 != 0);
        cRider_setControlState_6120(self, 9);
        cRider_setMotionMode_6120(self, 3);
        cSSXAudio_OnRiderReset(func_0028B180(), self);
        Replay_OnRiderReset(*(int *)(*(char **)((char *)D_004A28A8 + 0x84) + 0x28), *(int *)(self + 0x86C));
        return 1;
    }
    return 0;
}

//100%
struct V4_61D0 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (4D dot product).
static inline float Dot4_61D0(const V4_61D0& a, const V4_61D0& b)
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

// PORT: returns a value (target keeps the state in v1 across the call)
extern "C" int cRiderAnimBase_play_61D0(void* self, int anim, int flags, float blend) __asm__("cRiderAnimBase_play");
int cRider_getMotionMode(void* self);
// PORT: cRider_setControlState__FPv takes a second argument; bound by asm label
void cRider_setControlState_61D0(void* self, int on) __asm__("cRider_setControlState__FPv");

extern "C" int cRider_TryEnterBoardPress(char* s, float dir)
{
    int st;
    if (dir == 0.0f) return 0;
    if (*(int*)(s + 0x328) == 3 || *(int*)(s + 0x328) == 4) return 0;
    if (!cRider_getMotionMode(s)) {
        if (Dot4_61D0(*(V4_61D0*)(s + 0x1E0), *(V4_61D0*)(s + 0x3A0)) < 0.0f) return 0;
    }
    if (dir > 0.0f) {
        cRiderAnimBase_play_61D0(*(void**)(s + 0x784), 0x18, 0, -1.0f);
        *(int*)(s + 0x330) = 1;
    } else {
        cRiderAnimBase_play_61D0(*(void**)(s + 0x784), 0x20, 0, -1.0f);
        *(int*)(s + 0x330) = 2;
    }
    cRider_setControlState_61D0(s, 1);
    return 1;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void cRider_setControlState_62C8(void *, int) __asm__("cRider_setControlState__FPv");
extern "C" int cRider_getControlState_62C8(void *) __asm__("cRider_getControlState__FPv");
extern "C" void cBoardPressControl_endPress(char *);
extern "C" void func_002F6AC8(char *, int);

extern "C" int cRider_TryEnterPrewind(char *self, int arg1, int arg2) {
    if (arg2 != 0)
        func_002F6AC8(*(char **)(self + 0x77C) + 0xD20, 1);
    if ((*(float *)(self + 0x360) == 0.0f && arg1 != 0) || arg2 != 0) {
        if (cRider_getControlState_62C8(self) == 1)
            cBoardPressControl_endPress(*(char **)(self + 0x77C) + 0x1D0);
        cRider_setControlState_62C8(self, 2);
        return 1;
    }
    *(float *)(self + 0x360) = 1.0f;
    return 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void cRider_setControlState_6378(void *, int) __asm__("cRider_setControlState__FPv");

extern "C" int func_00116378(void *arg0) {
    if (*(float *)((char*)arg0 + 0x470) >= 0.0f) {
        cRider_setControlState_6378(arg0, 10);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("seg/seg_14B10", func_001163B0);

extern "C" void cRider_EmptyStanceHook(void) {
}

//100%
extern int D_0043D160[];

extern "C" int Trick_GetGrabName(int arg0) {
    return D_0043D160[arg0];
}

struct sTrickDesc {
    unsigned int f0 : 3;
    unsigned int f3 : 4;
    unsigned int f7 : 3;
    unsigned int f10 : 2;
    unsigned int f12 : 4;
    unsigned int f16 : 3;
    unsigned int f19 : 3;
    unsigned int f22 : 6;
    unsigned int f28 : 4;
    unsigned int f32 : 3;
    unsigned int f35 : 7;
    unsigned int f42 : 1;
    unsigned int f43 : 7;
    unsigned int f50 : 2;
    unsigned int f52 : 4;
    unsigned int f56 : 3;
    unsigned int f59 : 5;
};

//100%
extern char* D_0043D118[];
extern char* D_0043D130[];
extern char* D_0043CF40[];
extern char* D_0043CF60[];
extern char* D_0043CF70[];
extern char* D_0043CFB0[];
extern char* D_0043CFC8[];
extern char* D_0043CFE0[];
extern char* D_0043D0C0[];
extern char* D_004A0FF0[2];
extern char* D_0043D2B8[];
extern char* D_0043D2D0[];
extern char* D_0043D2E0[];
extern char* D_0043D100[];
extern char* D_0043D320[];

extern "C" void gGenTrickName(char* out, sTrickDesc* t, int)
{
    const char* p;
    p = D_0043D118[t->f0];
    while (*p) *out++ = *p++;
    p = D_0043D130[t->f3];
    while (*p) *out++ = *p++;
    p = D_0043CF40[t->f7];
    while (*p) *out++ = *p++;
    p = D_0043CF60[t->f10];
    while (*p) *out++ = *p++;
    p = D_0043CF70[t->f12];
    while (*p) *out++ = *p++;
    p = D_0043CFB0[t->f16];
    while (*p) *out++ = *p++;
    p = D_0043CFC8[t->f19];
    while (*p) *out++ = *p++;
    p = D_0043CFE0[t->f22];
    while (*p) *out++ = *p++;
    p = D_0043D0C0[t->f28];
    while (*p) *out++ = *p++;
    p = ((char**)D_0043D160)[t->f35];
    while (*p) *out++ = *p++;
    p = D_004A0FF0[t->f42];
    while (*p) *out++ = *p++;
    p = ((char**)D_0043D160)[t->f43];
    while (*p) *out++ = *p++;
    p = D_0043D2B8[t->f32];
    while (*p) *out++ = *p++;
    p = D_0043D2D0[t->f50];
    while (*p) *out++ = *p++;
    p = D_0043D2E0[t->f52];
    while (*p) *out++ = *p++;
    p = D_0043D100[t->f56];
    while (*p) *out++ = *p++;
    p = D_0043D320[t->f59];
    while (*p) *out++ = *p++;
    *out = 0;
}

//100%
// PORT: same layout as sTrickDesc, but the request builder packs it
// through 64-bit fields, so it gets its own type and an asm-label alias.
struct sTrickDesc64 {
    unsigned long f0 : 3;
    unsigned long f3 : 4;
    unsigned long f7 : 3;
    unsigned long f10 : 2;
    unsigned long f12 : 4;
    unsigned long f16 : 3;
    unsigned long f19 : 3;
    unsigned long f22 : 6;
    unsigned long f28 : 4;
    unsigned long f32 : 3;
    unsigned long f35 : 7;
    unsigned long f42 : 1;
    unsigned long f43 : 7;
    unsigned long f50 : 2;
    unsigned long f52 : 4;
    unsigned long f56 : 3;
    unsigned long f59 : 5;
};
struct sMonsterReq_6E08 {
    int key;
    int pad4;
    unsigned char b8, b9, bA, bB, bC, bD, bE, bF;
};


extern sMonsterReq_6E08 D_0043D608[];
extern "C" void func_003E6448(void*, int, int);
extern "C" void gGenTrickName_6E08(char*, sTrickDesc64*, int) __asm__("gGenTrickName");

extern "C" void gGenMonsterTrickReqName(char* out, int key, int a2) {
    sMonsterReq_6E08* e = D_0043D608;
    int i = 0;
    do {
        i++;
        if (e->key == key) {
            sTrickDesc64 b;
            func_003E6448(&b, 0, 8);
            b.f10 = e->b8;
            b.f12 = e->b9;
            b.f16 = e->bA;
            b.f19 = e->bB;
            b.f28 = e->bC;
            b.f35 = e->bD;
            b.f43 = e->bE;
            if (((int*)&b)[1] & 0x3F800) b.f42 = 1;
            gGenTrickName_6E08(out, &b, a2);
            return;
        }
        e++;
    } while (i < 0x18);
    *out = 0;
}

//100%
extern "C" int* func_00116FA8(int *arg0) {
    *arg0 = 0x34;
    return arg0;
}

//100%
extern "C" void func_00116FB8(void *self) {
    if (*(int *)((char*)self + 0) != 0x34) {
        float lim = *(float *)((char*)self + 4);
        if (lim != -1.0f) {
            float t = *(float *)((char*)self + 8) + 0.01666666753590107f;
            *(float *)((char*)self + 8) = t;
            if (lim <= t)
                *(int *)((char*)self + 0) = 0x34;
        }
    }
}

//100%
extern "C" void func_00117008(char *arg0, signed char *arg1) {
    signed char *s = arg1;
    unsigned char *d = (unsigned char*)(arg0 + 0x18);
    if (s != 0) {
        while (*s != 0) {
            *d = *s;
            s++;
            d++;
        }
    }
    *d = 0;
}

//100%
extern "C" void func_00117008(char *, signed char *);

extern "C" void func_00117048(char *arg0, int arg1, signed char *arg2, int arg3, float fparg0) {
    func_00117008(arg0, arg2);
    *(int *)(arg0 + 0) = arg1;
    *(float *)(arg0 + 4) = fparg0;
    *(int *)(arg0 + 0xC) = arg3;
    *(int *)(arg0 + 8) = 0;
    *(int *)(arg0 + 0x14) = 0;
}

extern "C" int sprintf(char*, const char*, ...);
extern char D_004A5E20[];
extern char D_004A1070[];
extern "C" void func_001170A8(char *arg0, int arg1, int arg2, float fparg0, int arg3) {
    sprintf(D_004A5E20, D_004A1070, arg2);
    func_00117008(arg0, (signed char *)D_004A5E20);
    *(int *)(arg0 + 0x14) = arg2;
    *(int *)(arg0 + 0) = arg1;
    *(float *)(arg0 + 4) = fparg0;
    *(int *)(arg0 + 0xC) = arg3;
    *(int *)(arg0 + 8) = 0;
}

//100%
extern "C" void func_00117008(char *, signed char *);

extern "C" void cHUDFX_ShowDelayed(char *arg0, int arg1, signed char *arg2, int arg3, float fparg0) {
    func_00117008(arg0, arg2);
    *(int *)(arg0 + 0) = arg1;
    *(int *)(arg0 + 0xC) = arg3;
    *(float *)(arg0 + 8) = -fparg0;
    *(float *)(arg0 + 4) = -1.0f;
    *(int *)(arg0 + 0x14) = 0;
}

extern "C" void cHUDFX_ShowNumberDelayed(char *arg0, int arg1, int arg2, float fparg0, int arg3) {
    sprintf(D_004A5E20, D_004A1070, arg2);
    func_00117008(arg0, (signed char *)D_004A5E20);
    *(int *)(arg0 + 0x14) = arg2;
    *(int *)(arg0 + 0) = arg1;
    *(float *)(arg0 + 8) = -fparg0;
    *(int *)(arg0 + 0xC) = arg3;
    *(float *)(arg0 + 4) = -1.0f;
}

//100%
extern "C" void cRiderMetrix_resetRun(void *);

extern "C" void *cRiderMetrix_ctor(void *arg0) {
    *(int *)((char*)arg0 + 0x1AC) = 0;
    *(int *)((char*)arg0 + 0x1B0) = 0;
    *(int *)((char*)arg0 + 0x1B4) = 0;
    *(int *)((char*)arg0 + 0x1C8) = 0;
    *(float *)((char*)arg0 + 0x1C4) = 1.0f;
    cRiderMetrix_resetRun(arg0);
    return arg0;
}

//100%
extern "C" void cMemMan_free__FPv(int);
extern "C" void operator_delete__FPi(void *);

extern "C" void func_00117290(void *arg0, int arg1) {
    int temp_4;

    temp_4 = (*(int *)((char*)(arg0) + (0x1B0)));
    if (temp_4 != 0) {
        cMemMan_free__FPv(temp_4);
    }
    if (arg1 & 1) {
        operator_delete__FPi(arg0);
    }
}
