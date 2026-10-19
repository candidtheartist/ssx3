#include "common.h"

//100%
// Sets one AI rider's speed/skill tuning for a difficulty level (1..5) and race mode.
extern "C" void cComputer_setIndividualRiderDifficulty(char* self, int level, int mode)
{
    switch (level) {
    case 1:
        *(float*)(self + 0xDF8) = 100.0f;
        *(float*)(self + 0xDFC) = 86.9153976f;
        *(float*)(*(char**)(self + 0x18) + 0xDC) = -49670.1406f;
        *(float*)(*(char**)(self + 0x18) + 0xE0) = 47500.0f;
        *(int*)(*(char**)(self + 0x18) + 0xE4) = 0;
        break;
    case 2:
        *(float*)(self + 0xDF8) = 80.3891449f;
        *(float*)(self + 0xDFC) = 79.5998383f;
        *(float*)(*(char**)(self + 0x18) + 0xDC) = -70000.0f;
        *(float*)(*(char**)(self + 0x18) + 0xE0) = 45000.0f;
        *(int*)(*(char**)(self + 0x18) + 0xE4) = 1;
        break;
    case 3:
        *(float*)(self + 0xDF8) = 51.007576f;
        *(float*)(self + 0xDFC) = 68.9012375f;
        *(float*)(*(char**)(self + 0x18) + 0xDC) = -81571.1797f;
        *(float*)(*(char**)(self + 0x18) + 0xE0) = 40000.0f;
        *(int*)(*(char**)(self + 0x18) + 0xE4) = 1;
        break;
    case 4:
        *(float*)(self + 0xDF8) = 46.6018982f;
        *(float*)(self + 0xDFC) = 56.8430748f;
        *(float*)(*(char**)(self + 0x18) + 0xDC) = -80321.1797f;
        *(float*)(*(char**)(self + 0x18) + 0xE0) = 37500.0f;
        *(int*)(*(char**)(self + 0x18) + 0xE4) = 1;
        break;
    case 5:
        *(float*)(self + 0xDF8) = 14.000701f;
        *(float*)(self + 0xDFC) = 42.4410439f;
        *(float*)(*(char**)(self + 0x18) + 0xDC) = -92500.0f;
        *(float*)(*(char**)(self + 0x18) + 0xE0) = 32500.0f;
        *(int*)(*(char**)(self + 0x18) + 0xE4) = 1;
        break;
    }
    if (mode == 0) {
        switch (level) {
        case 1:
            *(float*)(self + 0xDF8) = 100.0f;
            *(float*)(self + 0xDFC) = 83.8930817f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 45000.0f;
            break;
        case 2:
            *(float*)(self + 0xDF8) = 55.8049736f;
            *(float*)(self + 0xDFC) = 64.6436768f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 42500.0f;
            break;
        case 3:
            *(float*)(self + 0xDF8) = 40.2501869f;
            *(float*)(self + 0xDFC) = 60.0044975f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 37500.0f;
            break;
        case 4:
            *(float*)(self + 0xDF8) = 15.5423021f;
            *(float*)(self + 0xDFC) = 52.0049553f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 32500.0f;
            break;
        case 5:
            *(float*)(self + 0xDF8) = 7.95483208f;
            *(float*)(self + 0xDFC) = 35.0202637f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 30000.0f;
            break;
        }
    } else if (mode == 2) {
        switch (level) {
        case 1:
            *(float*)(self + 0xDF8) = 100.0f;
            *(float*)(self + 0xDFC) = 100.0f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 50000.0f;
            break;
        case 2:
            *(float*)(self + 0xDF8) = 84.9981003f;
            *(float*)(self + 0xDFC) = 82.6824875f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 47500.0f;
            break;
        case 3:
            *(float*)(self + 0xDF8) = 74.9987259f;
            *(float*)(self + 0xDFC) = 70.8223801f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 40000.0f;
            break;
        case 4:
            *(float*)(self + 0xDF8) = 54.9958344f;
            *(float*)(self + 0xDFC) = 59.9440651f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 37500.0f;
            break;
        case 5:
            *(float*)(self + 0xDF8) = 29.9814339f;
            *(float*)(self + 0xDFC) = 46.9987717f;
            *(float*)(*(char**)(self + 0x18) + 0xE0) = 32500.0f;
            break;
        }
    }
    *(float*)(self + 0xDFC) = *(float*)(self + 0xDFC) * 0.01f;
}

INCLUDE_ASM("ai/computer", cComputer_updateRiderDifficulty);

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int func_00144C98(void* iface);
extern "C" void func_00148AA8(void* iface, int a1, int a2);

struct sVEntry10C9A8 { short delta; short index; int (*fn)(void*); };

static inline int riderV7_10C9A8(char* rider)
{
    char* obj = rider + 0x6C0;
    sVEntry10C9A8* vt = *(sVEntry10C9A8**)obj;
    return vt[7].fn(obj + vt[7].delta);
}

extern "C" void func_0010C9A8(void* self)
{
    void* s = cBE_getInterface_Fv(cBE_getBE(), 3);
    void* g = cBE_getInterface_Fv(cBE_getBE(), 0);
    if (func_00144C98(g) == 2)
    {
        func_00148AA8(s, riderV7_10C9A8(*(char**)((char*)self + 0x18)), 7);
    }
    else if (func_00144C98(g) == 1)
    {
        func_00148AA8(s, riderV7_10C9A8(*(char**)((char*)self + 0x18)), 4);
    }
    else
    {
        func_00148AA8(s, riderV7_10C9A8(*(char**)((char*)self + 0x18)), 1);
    }
}

extern "C" void cComputer_updateRiderDifficulty(void*);

//99.29% - identical instructions; jal addend differs only because the
// callee sits at a different .text offset in our object than in the target
extern "C" void func_0010CAB8(void* self)
{
    cComputer_updateRiderDifficulty(self);
}

//100%
extern "C" int func_0010C258(void* self);
extern "C" int func_0010C320(void* self);
extern "C" int func_0010C3B8(void* self);
extern "C" int func_0010CF68(void* self, float t);
extern "C" int func_0010CD20(void* self, float t);
extern "C" int func_0010CBE0(void* self, float t);

extern "C" int cComputer_chooseGrab(void* self, float t)
{
    int r = -1;
    int skip = *(int*)((char*)self + 0xE20) != 0 && t < 1.0f;
    if (!skip && t > 0.75f && t != 100.0f)
    {
        if (func_0010C258(self)) r = func_0010CF68(self, t);
        if (r == -1)
        {
            if (func_0010C320(self)) r = func_0010CD20(self, t);
            if (r == -1)
            {
                if (func_0010C3B8(self)) r = func_0010CBE0(self, t);
            }
        }
    }
    return r;
}

//100%
unsigned int AIrand();
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" unsigned short func_001500D8(void* self, int a1, int a2);
extern "C" float func_00120038(void* self);
extern "C" float func_00312820(char* self, int a1, int frame);

struct sVEntry10CBE0 { short delta; short index; int (*fn)(void*); };

static inline int riderV7_10CBE0(char* rider)
{
    char* obj = rider + 0x6C0;
    sVEntry10CBE0* vt = *(sVEntry10CBE0**)obj;
    return vt[7].fn(obj + vt[7].delta);
}

struct sComputer_0010CBE0
{
    char pad0[0x18];
    char* mRider;       // 0x18
    char pad1C[0xE24 - 0x1C];
    int fE24;           // 0xE24
    int fE28;           // 0xE28
    float fE2C;         // 0xE2C
    float fE30;         // 0xE30
    float fE34;         // 0xE34
    char padE38[0xE7C - 0xE38];
    int a[15];          // 0xE7C
};

extern "C" int func_0010CBE0(void* p, float t)
{
    sComputer_0010CBE0* self = (sComputer_0010CBE0*)p;
    self->fE24 = 0;
    self->fE28 = 0;
    self->fE30 = t;
    int idx = AIrand() % 15;
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 6);
    int anim = func_001500D8(iface, riderV7_10CBE0(self->mRider), idx);
    float spd = func_00120038(self->mRider);
    float a = func_00312820(*(char**)(self->mRider + 0x784), anim, 2) / spd;
    float b = func_00312820(*(char**)(self->mRider + 0x784), anim, 1) / spd;
    if (t < a) return -1;
    self->fE34 = t - a;
    self->fE2C = a - b;
    if (idx != -1 && idx < 15)
    {
        self->a[idx]++;
    }
    return idx;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" unsigned short func_001500D8(void* self, int a1, int a2);
extern "C" int func_00150138(void* self, int a1, int a2);
extern "C" int func_00150198(void* self, int a1, int a2, int a3);
extern "C" float func_00120038(void* self);
extern "C" float func_00312820(char* self, int a1, int frame);

struct sVEntry10CD20 { short delta; short index; int (*fn)(void*); };

static inline int riderV7_10CD20(char* rider)
{
    char* obj = rider + 0x6C0;
    sVEntry10CD20* vt = *(sVEntry10CD20**)obj;
    return vt[7].fn(obj + vt[7].delta);
}

struct sComputer_0010CD20
{
    char pad0[0x18];
    char* mRider;       // 0x18
    char pad1C[0xE24 - 0x1C];
    int fE24;           // 0xE24
    int fE28;           // 0xE28
    float fE2C;         // 0xE2C
    float fE30;         // 0xE30
    float fE34;         // 0xE34
    char padE38[0xEF4 - 0xE38];
    int c[15];          // 0xEF4
};

extern "C" int func_0010CD20(void* p, float t)
{
    sComputer_0010CD20* self = (sComputer_0010CD20*)p;
    self->fE24 = 0;
    self->fE30 = t;
    int found = -1;
    int best = 10000;
    int i = 1;
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 6);
    float spd = func_00120038(self->mRider);
    for (; i < 15; i++)
    {
        int anim = func_00150138(iface, riderV7_10CD20(self->mRider), i);
        if (anim == 0x1B6)
            continue;
        int alt = (*(int*)(self->mRider + 0xB2C) & 1) ? func_00150198(iface, riderV7_10CD20(self->mRider), i, *(int*)(self->mRider + 0x2F4) >= 5) : 0x1B6;
        if (0.0f < *(float*)(self->mRider + 0x2F0) && alt != 0x1B6)
            continue;
        int anim2 = func_001500D8(iface, riderV7_10CD20(self->mRider), i);
        float a = func_00312820(*(char**)(self->mRider + 0x784), anim2, 1) / spd;
        float b = func_00312820(*(char**)(self->mRider + 0x784), anim, 1) / spd;
        float c = func_00312820(*(char**)(self->mRider + 0x784), anim, 2) / spd;
        float sum = c + a;
        if (sum < t && self->c[i] < best)
        {
            self->fE28 = 1;
            found = i;
            self->fE2C = c - b;
            self->fE34 = t - sum;
            best = self->c[i];
        }
    }
    if (found != -1 && found < 15)
    {
        self->c[found]++;
    }
    return found;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" unsigned short func_001500D8(void* self, int a1, int a2);
extern "C" int func_00150198(void* self, int a1, int a2, int a3);
extern "C" float func_00120038(void* self);
extern "C" float func_00312820(char* self, int a1, int frame);

struct sVEntry10CF68 { short delta; short index; int (*fn)(void*); };

static inline int riderV7_10CF68(char* rider)
{
    char* obj = rider + 0x6C0;
    sVEntry10CF68* vt = *(sVEntry10CF68**)obj;
    return vt[7].fn(obj + vt[7].delta);
}

struct sComputer_0010CF68
{
    char pad0[0x18];
    char* mRider;       // 0x18
    char pad1C[0xE24 - 0x1C];
    int fE24;           // 0xE24
    int fE28;           // 0xE28
    float fE2C;         // 0xE2C
    float fE30;         // 0xE30
    float fE34;         // 0xE34
    char padE38[0xEB8 - 0xE38];
    int b[15];          // 0xEB8
};

extern "C" int func_0010CF68(void* p, float t)
{
    sComputer_0010CF68* self = (sComputer_0010CF68*)p;
    self->fE28 = 0;
    if (*(float*)(self->mRider + 0x2F0) <= 0.0f)
        return -1;
    self->fE30 = t;
    int found = -1;
    int best = 10000;
    int i = 0;
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 6);
    float spd = func_00120038(self->mRider);
    for (; i < 15; i++)
    {
        int anim = func_00150198(iface, riderV7_10CF68(self->mRider), i, *(int*)(self->mRider + 0x2F4) >= 5);
        if (anim == 0x1B6)
            continue;
        int anim2 = func_001500D8(iface, riderV7_10CF68(self->mRider), i);
        float a = func_00312820(*(char**)(self->mRider + 0x784), anim2, 1) / spd;
        float b = func_00312820(*(char**)(self->mRider + 0x784), anim, 1) / spd;
        float c = func_00312820(*(char**)(self->mRider + 0x784), anim, 2) / spd;
        float sum = c + a;
        if (sum < t && self->b[i] < best)
        {
            self->fE24 = 1;
            found = i;
            self->fE2C = c - b;
            self->fE34 = t - sum;
            best = self->b[i];
        }
    }
    if (found != -1 && found < 15)
    {
        self->b[found]++;
    }
    return found;
}

//100%
struct sComputer_0010D170
{
    char pad[0xE7C];
    int a[15];
    int b[15];
    int c[15];
};

extern "C" void cComputer_resetGrabUsage(sComputer_0010D170* self)
{
    for (int i = 0; i < 15; i++)
    {
        self->a[i] = 0;
        self->b[i] = 0;
        self->c[i] = 0;
    }
}

//100%
int cRider_getMotionMode(void* self);
int cRider_getControlState(void* self);
extern "C" float func_0031C228(float x);

struct sVec_0010D1A0 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sRider_0010D1A0 {
    char pad0[0x1B0];
    sVec_0010D1A0 vel;  // 0x1B0
    char pad1C0[0x4C8 - 0x1C0];
    float speed;        // 0x4C8
    float heading;      // 0x4CC
    char pad4D0[0x788 - 0x4D0];
    char* board;        // 0x788

    sVec_0010D1A0 getVel() { return vel; }
};

struct sComputer_0010D1A0 {
    char pad0[0x18];
    sRider_0010D1A0* rider;  // 0x18
    char pad1C[0xE70 - 0x1C];
    int dir;                 // 0xE70
    int stuckTime;           // 0xE74
    int wrongTime;           // 0xE78
};

static inline float atan2_0010D1A0(float y, float x)
{
    if (x == 0.0f) {
        if (y == 0.0f) {
            return y;
        }
        if (y >= 0.0f) {
            return 1.5707963705062866f;
        }
        return -1.5707963705062866f;
    }
    float a = func_0031C228(y / x);
    if (x < 0.0f) {
        if (y > 0.0f) {
            a += 3.1415927410125732f;
        } else {
            a -= 3.1415927410125732f;
        }
    }
    return a;
}

// PORT: PS2-only inline asm (EE cvt.w.s truncates in the FPU; the C cast goes through a GPR).
static inline float ffloor_0010D1A0(float x)
{
    float t;
    __asm__("cvt.w.s %0,%1\n\tcvt.s.w %0,%0" : "=f"(t) : "f"(x));
    if (x < t) {
        t -= 1.0f;
    }
    return t;
}

static inline float wrap_0010D1A0(float x)
{
    return x - ffloor_0010D1A0(x * 0.15915493667125702f + 0.5f) * 6.2831854820251465f;
}

extern "C" int func_0010D1A0(sComputer_0010D1A0* self)
{
    float ang = atan2_0010D1A0(self->rider->getVel().y, self->rider->getVel().x);
    float d = wrap_0010D1A0(self->rider->heading - ang);
    if (self->dir < 0) {
        if (__builtin_fabsf(d) > 1.047197699546814f) {
            self->wrongTime++;
        } else {
            self->wrongTime = 0;
        }
    } else {
        self->wrongTime = 0;
    }
    int wrong = self->wrongTime >= 0x3D;
    if (cRider_getMotionMode(self->rider) == 2) {
        wrong = 0;
        self->stuckTime++;
    } else if (cRider_getMotionMode(self->rider) == 4 && self->wrongTime > 0) {
        return 1;
    } else if (cRider_getMotionMode(self->rider) == 1 || self->rider->speed < 1000.0f) {
        self->stuckTime = 0;
        wrong = 0;
        if (cRider_getMotionMode(self->rider) == 1 && *(float*)(self->rider->board + 0xA0) > 30.0f) {
            return 1;
        }
    } else {
        self->stuckTime++;
    }
    int stuck = wrong || self->stuckTime >= 0xDF;
    if (cRider_getControlState(self->rider) != 8) {
        stuck = stuck && self->dir < 0;
    }
    return stuck;
}

//100%
unsigned int AIrand();
extern "C" float func_0010D870(void* self, int a1, int a2, int a3);
struct sAi0010FC30;
extern "C" int cAI_countComputersOnRoute(sAi0010FC30* self, int team);
extern "C" float func_00112588(void* self, int arg1);
extern "C" float func_0026A428(void* path, void* a1, void* a2, void* a3, int n);
extern void* D_004A28A8;

struct sVec4_10D410 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (vector length).
static inline float vu0Length_10D410(const sVec4_10D410& v)
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

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_10D410 vu0Scale_10D410(const sVec4_10D410& v, float s)
{
    sVec4_10D410 r;
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
static inline sVec4_10D410 vu0Add_10D410(const sVec4_10D410& a, const sVec4_10D410& b)
{
    sVec4_10D410 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

static inline int speedLimit_10D410(int kind)
{
    if (kind == 1) {
        return 20;
    }
    if (kind == 2) {
        return 40;
    }
    if (kind == 3) {
        return 60;
    }
    if (kind == 4) {
        return 80;
    }
    if (kind == 5) {
        return 100;
    }
    if (kind == 6) {
        return 120;
    }
    return 0;
}

struct sAi_10D410 {
    char pad0[0x28];
    char* riders[20];
    int count;
};

extern "C" float cComputer_scoreRoute(char* self, char* tgt)
{
    float sc[7];
    char* ai = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC);
    int flags = *(int*)(tgt + 0x38);
    int kind = (flags >> 7) & 7;
    int lvl = (flags >> 4) & 7;
    int solo = flags & 1;
    if (kind > 8) {
        kind = 0;
    }
    int b2 = (flags >> 2) & 1;
    int b1 = (flags >> 1) & 1;
    int b3 = (flags >> 3) & 1;
    float base = func_0010D870(self, b3, b2, b1);
    if (base <= 0.0f) {
        return 0.0f;
    }
    if (*(int*)(self + 0xE04) == 0 && solo != 0) {
        return 0.0f;
    }
    float speed = vu0Length_10D410(*(sVec4_10D410*)(*(char**)(self + 0x18) + 0x1E0)) * 0.035999998450279236f;
    if (lvl == 0) {
        if ((float)speedLimit_10D410(kind) < speed) {
            return 0.0f;
        }
    } else if (lvl == 3) {
        if (speed < (float)speedLimit_10D410(kind)) {
            return 0.0f;
        }
    }
    char* r = *(char**)(self + 0x18);
    float len = vu0Length_10D410(*(sVec4_10D410*)(r + 0x1E0));
    float total = 22.0f;
    float s = func_00112588(r, 1) / len;
    sVec4_10D410 pos = vu0Add_10D410(*(sVec4_10D410*)(*(char**)(self + 0x18) + 0x110), vu0Scale_10D410(*(sVec4_10D410*)(*(char**)(self + 0x18) + 0x1E0), s));
    sVec4_10D410 out;
    float t;
    func_0026A428(tgt, &pos, &out, &t, 1);
    float d = t;
    float v = 100.0f - d * d * 1.5999999959603883e-05f;
    if (v < 0.0f) {
        v = 0.0f;
    }
    if (5000.0f < d) {
        return -1.0f;
    }
    sc[0] = v * 0.22727273404598236f;
    char* r2 = *(char**)(self + 0x18);
    if (*(int*)(r2 + 0xF0) != 0 && *(char**)(((sAi_10D410*)ai)->riders[*(int*)(r2 + 0xF8)] + 0xAB8) == tgt) {
        return 100.0f;
    }
    float zero = 0.0f;
    sc[1] = zero;
    float w = 1.0f / total;
    sc[2] = (float)lvl * (w * 0.3333333432674408f);
    // PORT: the path pointer is passed as cAI_countComputersOnRoute's int team
    int n = cAI_countComputersOnRoute((sAi0010FC30*)ai, (int)tgt);
    n -= tgt == *(char**)(*(char**)(self + 0x18) + 0xAB8);
    float c;
    if (n <= 0) {
        c = 100.0f;
    } else if (n == 1) {
        c = 25.0f;
    } else {
        c = zero;
    }
    w = 5.0f / total;
    sc[3] = c * w;
    w = base / total;
    sc[4] = w;
    w = 5.0f / total;
    if (*(int*)(self + 0xE04) != 0 && solo != 0) {
        sc[5] = w * 100.0f;
    } else {
        sc[5] = 0.0f;
    }
    w = 2.0f / total;
    if (*(int*)(self + 0xE08) != 0) {
        sc[6] = (float)(AIrand() % 100) * w;
    } else {
        sc[6] = 0.0f;
    }
    float sum = 0.0f;
    for (int i = 0; i < 7; i++) {
        sum += sc[i];
    }
    return sum;
}

//100%
extern "C" float func_0010D870(void* self, int a1, int a2, int a3)
{
    short s = *(short*)((char*)self + 0xE00);
    if (s == 0)
    {
        if (!a1)
            return 0.0f;
    }
    else if (s == 1)
    {
        if (!a2)
            return 0.0f;
    }
    else if (s == 2)
    {
        if (!a3)
            return 0.0f;
    }
    else if ((a1 == a2) != a3)
        return 0.0f;
    int n = 4;
    if (a1)
        n--;
    if (a2)
        n--;
    if (a3)
        n--;
    return n * 33.29999923706055f;
}

//100%
struct sComputer_0010D8F8
{
    int a;
    int b;
    char pad[0x1C];
};

extern "C" int func_0010D8F8(void* self)
{
    sComputer_0010D8F8* p = *(sComputer_0010D8F8**)((char*)self + 0x18);
    for (int i = 0; i < 6; i++, p++)
    {
        if (p->a != 0 && p->b != 0)
            return i;
    }
    return -1;
}

extern "C" int func_0010DEB0(void* self);
float cRider_getRemainingDistance(void* self);

extern "C" int func_0010D938(void* self)
{
    int p = func_0010DEB0(self);
    if (p == 0)
        return 0;
    float d = cRider_getRemainingDistance((void*)p) - *(float*)(*(char**)((char*)self + 0x18) + 0x4D0);
    if (d < *(float*)(*(char**)((char*)self + 0x18) + 0xDC))
        return 1;
    return 0;
}

extern "C" int func_0010D990(void* self)
{
    int p = func_0010DEB0(self);
    if (p == 0)
        return 0;
    float d = cRider_getRemainingDistance((void*)p) - *(float*)(*(char**)((char*)self + 0x18) + 0x4D0);
    if (*(float*)(*(char**)((char*)self + 0x18) + 0xE0) < d)
        return 1;
    return 0;
}

//100%
extern "C" int func_0010D9E8(void* self, int a1)
{
    void* p = *(void**)((char*)self + 0x18);
    int r = 0;
    if (*(int*)((char*)p + 0xf0) != 0) {
        r = *(int*)((char*)p + 0xf8) == a1;
    }
    return r;
}

//100%
struct sVE_0010DA10 { short delta; short index; int (*fn)(void*); };
struct sEnt_0010DA10 { int vis; int val; float dist; int c; int d; int e; int f; int g; int h; };
struct sRider_0010DA10 { sEnt_0010DA10 ent[6]; };
struct sAI_0010DA10 { char pad[0x28]; char* riders[20]; int count; };
extern void* D_004A28A8;
extern "C" int getGameTick();
extern "C" int func_00311AE8(void*, int);
unsigned int AIrand();

extern "C" int func_0010DA10(char* self)
{
    float t = *(float*)(self + 0xF30);
    if (t < 0.0f)
    {
        *(float*)(self + 0xF30) = 0.0f;
        return 0;
    }
    if (0.0f < t)
    {
        *(float*)(self + 0xF30) = t - 0.01666666753590107f;
        return *(int*)(self + 0xF34);
    }
    if (getGameTick() % 6 != 0)
        return 0;
    sAI_0010DA10* ai = *(sAI_0010DA10**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC);
    int i;
    for (i = 0; i < ai->count; i++)
    {
        char* o = *(char**)(self + 0x18) + 0x6C0;
        sVE_0010DA10* ve = &(*(sVE_0010DA10**)o)[7];
        if (i == ve->fn(o + ve->delta))
            continue;
        char* o2 = ai->riders[i] + 0x6C0;
        sVE_0010DA10* ve2 = &(*(sVE_0010DA10**)o2)[8];
        if (ve2->fn(o2 + ve2->delta) == 0)
            continue;
        if (!((*(sRider_0010DA10**)(self + 0x18))->ent[i].dist < 200.0f))
            continue;
        if (func_00311AE8(*(void**)(ai->riders[i] + 0x784), 1) != 13)
            continue;
        unsigned int r = AIrand() % 100;
        int* pf = (int*)(self + 0xF34);
        *pf = (float)r < 25.0f;
        *(float*)(self + 0xF30) = 2.0f;
        return *(int*)(self + 0xF34);
    }
    return 0;
}

INCLUDE_ASM("ai/computer", func_0010DBF0);

//100%
extern void* D_004A28A8;

extern "C" int func_0010DEB0(void* self)
{
    int i = func_0010D8F8(self);
    if (i < 0)
        return 0;
    return *(int*)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + (i << 2) + 0x28);
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
float cRider_getRemainingDistance(void* self);
extern signed char D_00535C11[];

extern "C" float cComputer_getPacingScale(void* self)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    // PORT: func_0010DEB0 returns a pointer as int (unit declaration).
    int p = func_0010DEB0(self);
    if (p == 0) return 1.0f;
    char* r = *(char**)((char*)self + 0x18);
    if (*(int*)(r + 0xE4) == 0) return 1.0f;
    if (D_00535C11[0] == 2) return 1.0f;
    if (*(float*)(r + 0x4D0) < 50000.0f) return 1.0f;
    float m;
    float d = cRider_getRemainingDistance((void*)p) - *(float*)(*(char**)((char*)self + 0x18) + 0x4D0);
    char* r2 = *(char**)((char*)self + 0x18);
    float k = *(float*)(r2 + 0xDC);
    if (d < k && (*(int*)(r2 + 0xE4) == 2 || *(int*)(r2 + 0xE4) == 3))
    {
        m = ((d - k) / k + 1.0f) * 1.100000023841858f;
    }
    else
    {
        char* r3 = *(char**)((char*)self + 0x18);
        float k2 = *(float*)(r3 + 0xE0);
        if (k2 < d && (*(int*)(r3 + 0xE4) == 1 || *(int*)(r3 + 0xE4) == 3))
        {
            m = 1.0f / ((d - k2) / k2 + 1.0f);
            m *= 0.9090908765792847f;
        }
        else
            m = 1.0f;
    }
    return m;
}

//100%
extern "C" int getGameTick();

extern "C" void cRider_requestReaction(void* self, int mode, float t)
{
    int v;
    if (mode == 0)
    {
        v = -1;
        *(int*)((char*)self + 0x358) = 0;
    }
    else
    {
        int frames = (int)(t * 60.0f);
        v = getGameTick() + frames;
        *(int*)((char*)self + 0x358) = mode;
    }
    *(int*)((char*)self + 0x354) = v;
}

//100%
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cBE_getBE();
extern "C" void* func_0028B180();
extern "C" void func_00149690(void* iface, int rider, int b);
extern "C" void func_0029AB08(void* mgr, void* rider, float cur, float amt);
extern "C" void cRider_requestReaction(void* self, int mode, float t);

// PORT: g++ `<?` (min) operator.
static inline float clamp_10E098(float v, float lo, float hi)
{
    if (v >= lo) return v <? hi;
    return lo;
}

extern "C" void cRider_addBoostMeter(void* self, int mask, float amt)
{
    if (*(int*)((char*)self + 0x304) == 3)
        return;
    float zero = 0.0f;
    if (amt == zero)
        return;
    if (amt > zero)
    {
        func_00149690(cBE_getInterface_Fv(cBE_getBE(), 3), *(int*)((char*)self + 0x86C), *(int*)((char*)self + 0xB34));
        if ((mask & *(int*)((char*)self + 0xB28)) == 0)
            return;
    }
    func_0029AB08(func_0028B180(), self, *(float*)((char*)self + 0x2F8), amt);
    *(float*)((char*)self + 0x2F8) = clamp_10E098(*(float*)((char*)self + 0x2F8) + amt, zero, 1.0f);
    if (*(float*)((char*)self + 0x2F8) == 1.0f && amt > zero && *(int*)((char*)self + 0xB2C) != 0)
    {
        if (*(float*)((char*)self + 0x2F0) == zero)
            cRider_requestReaction(self, 5, zero);
        if (*(int*)((char*)self + 0x2F4) <= 0)
            *(int*)((char*)self + 0x2F4) += 1;
        if (*(int*)((char*)self + 0x2F4) >= 1 && *(int*)((char*)self + 0x2F4) <= 9)
        {
            // PORT: g++ `>?` (max) operator.
            *(float*)((char*)self + 0x2F0) = *(float*)((char*)self + 0x2F0) >? 20.0f;
        }
    }
    else if (amt < 0.0f && *(int*)((char*)self + 0x2F4) < 10)
    {
        *(float*)((char*)self + 0x2F0) = 0.0f;
    }
}

//100%
struct sVEntry0010E228 {
    short delta;
    short index;
    int (*fn)(void*);
};

extern "C" void* func_0028B180();
extern "C" void func_00298488(void* snd, void* a, void* b);
extern "C" void func_002A0A30(void* snd, void* a, void* b, int c, int d);
void* cBEAggressionInterface_getThis();
extern "C" void func_00155BF0(void* agg, int a, int b, int c);

extern "C" void func_0010E228(void* a, void* b)
{
    func_00298488(func_0028B180(), a, b);
    func_002A0A30(func_0028B180(), b, a, 1, 0);
    void* agg = cBEAggressionInterface_getThis();
    char* ob = (char*)b + 0x6C0;
    sVEntry0010E228* eb = &(*(sVEntry0010E228**)ob)[7];
    int rb = eb->fn(ob + eb->delta);
    char* oa = (char*)a + 0x6C0;
    sVEntry0010E228* ea = &(*(sVEntry0010E228**)oa)[7];
    func_00155BF0(agg, rb, ea->fn(oa + ea->delta), 0);
}

//100%
struct sVEntry0010E2E8 {
    short delta;
    short index;
    int (*fn)(void*);
};

extern "C" void* func_0028B180();
extern "C" void func_00298488(void* snd, void* a, void* b);
extern "C" void func_002A0A30(void* snd, void* a, void* b, int c, int d);
void* cBEAggressionInterface_getThis();
extern "C" void func_00155BF0(void* agg, int a, int b, int c);

extern "C" void func_0010E2E8(void* a, void* b)
{
    func_00298488(func_0028B180(), a, b);
    func_002A0A30(func_0028B180(), b, a, 1, 1);
    void* agg = cBEAggressionInterface_getThis();
    char* ob = (char*)b + 0x6C0;
    sVEntry0010E2E8* eb = &(*(sVEntry0010E2E8**)ob)[7];
    int rb = eb->fn(ob + eb->delta);
    char* oa = (char*)a + 0x6C0;
    sVEntry0010E2E8* ea = &(*(sVEntry0010E2E8**)oa)[7];
    func_00155BF0(agg, rb, ea->fn(oa + ea->delta), 1);
}

//100%
struct sVEntry0010E3A8 {
    short delta;
    short index;
    int (*fn)(void*);
};

extern "C" void* func_0028B180();
extern "C" void func_00298138(void* snd, void* a, void* b);
extern "C" void func_002A0A30(void* snd, void* a, void* b, int c, int d);
void* cBEAggressionInterface_getThis();
extern "C" void func_00155BF0(void* agg, int a, int b, int c);

extern "C" void func_0010E3A8(void* a, void* b)
{
    func_00298138(func_0028B180(), b, a);
    func_002A0A30(func_0028B180(), b, a, 0, 0);
    void* agg = cBEAggressionInterface_getThis();
    char* ob = (char*)b + 0x6C0;
    sVEntry0010E3A8* eb = &(*(sVEntry0010E3A8**)ob)[7];
    int rb = eb->fn(ob + eb->delta);
    char* oa = (char*)a + 0x6C0;
    sVEntry0010E3A8* ea = &(*(sVEntry0010E3A8**)oa)[7];
    func_00155BF0(agg, rb, ea->fn(oa + ea->delta), 2);
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sVEntry0010E468 {
    short delta;
    short index;
    int (*fn)(void*);
};

extern "C" void* func_0028B180();
extern "C" void func_00298138(void* snd, void* a, void* b);
extern "C" void func_002A0A30(void* snd, void* a, void* b, int c, int d);
extern "C" void func_00298D00(void* snd, void* obj);
void* cBEAggressionInterface_getThis();
extern "C" void func_00155BF0(void* agg, int a, int b, int c);
extern "C" float cRiderMetrix_onKnockout(char* self);
extern "C" void cRider_addBoostMeter(void*, int, float);

extern "C" void func_0010E468(void* a, void* b)
{
    func_00298138(func_0028B180(), b, a);
    func_002A0A30(func_0028B180(), b, a, 0, 1);
    func_00298D00(func_0028B180(), b);
    void* agg = cBEAggressionInterface_getThis();
    char* ob = (char*)b + 0x6C0;
    sVEntry0010E468* eb = &(*(sVEntry0010E468**)ob)[7];
    int rb = eb->fn(ob + eb->delta);
    char* oa = (char*)a + 0x6C0;
    sVEntry0010E468* ea = &(*(sVEntry0010E468**)oa)[7];
    func_00155BF0(agg, rb, ea->fn(oa + ea->delta), 3);
    cRider_addBoostMeter(b, 2, cRiderMetrix_onKnockout(*(char**)((char*)b + 0x790)));
}

//100%
extern int D_005308D0[];
extern signed char D_00535C12[];
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_001194C0(void*, int);

extern "C" void func_0010E558(void* self, int* arg)
{
    *(int*)((char*)self + 0xE8) = *(int*)((char*)self + 0xEC);
    if (((D_005308D0[0] >> 9) & 1) == 0)
    {
        cBE_getInterface_Fv(cBE_getBE(), 0);
        if (D_00535C12[0] == 1)
        {
            func_001194C0(*(void**)((char*)self + 0x790), *arg);
        }
    }
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int* func_00144BC0(void* iface);
extern "C" void cRider_finish(void* self);
extern "C" void func_00270AB0(void* a, int b, int c);
extern void* D_004A28A8;
extern signed char D_00535BC8[];

static inline int state_0010E5D8() { return D_00535BC8[0x48]; }

struct sVEntry0010E5D8 { short delta; short index; int (*fn)(void*); };

extern "C" void cRider_onCourseEvent(void* self, int* arg, int a2, int a3)
{
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 0);
    char* s = *(char**)((char*)D_004A28A8 + 0xC0);
    int mode = *func_00144BC0(iface);
    int v = 0;
    if (state_0010E5D8() == 0 || state_0010E5D8() == 1 || state_0010E5D8() == 3 || state_0010E5D8() == 2
        || (state_0010E5D8() == 5 && *(int*)(s + 0x98) != 0)
        || (state_0010E5D8() == 6 && *(int*)(s + 0x98) != 0)
        || mode == 5 || mode == 6 || mode == 7 || mode == 8 || mode == 9
        || mode == 10 || mode == 11 || mode == 12 || mode == 13 || mode == 1
        || D_00535BC8[0x49] != 0)
        v = 1;
    if (*arg == 1 && v != 0)
    {
        int ok = *(float*)((char*)self + 0x470) >= 0.0f;
        if (!ok)
            cRider_finish(self);
    }
    if (*arg == 11)
    {
        char* o = (char*)self + 0x6C0;
        sVEntry0010E5D8* e = &(*(sVEntry0010E5D8**)o)[7];
        void* tgt = *(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28);
        func_00270AB0(tgt, e->fn(o + e->delta), arg[1]);
    }
}

//100%
extern "C" void* func_0028B180();
extern "C" void func_0029CED8(void*, int, void*, float);
extern "C" void func_002A3B18(void*, void*, int);

extern "C" void cRider_awardSpeedBoost(void* self, float amount)
{
    *(float*)((char*)self + 0x2E8) += amount;
    func_0029CED8(func_0028B180(), 0, self, 1.0f);
    func_002A3B18(func_0028B180(), self, 1);
}

//100%
extern "C" void* func_0028B180();
extern "C" void func_0029CED8(void*, int, void*, float);
extern "C" void func_002A3B18(void*, void*, int);

extern "C" void cRider_awardTrickBoost(void* self, float amount)
{
    *(float*)((char*)self + 0x2EC) += amount;
    func_0029CED8(func_0028B180(), 1, self, 1.0f);
    func_002A3B18(func_0028B180(), self, 2);
}

//100% - objdiff report; single-function view differs only in a relocation name
int cRider_getMotionMode(void* self);
extern "C" float cRiderMetrix_onMultiplierPickup(char* self, float value);
extern "C" void cRider_addBoostMeter(void*, int, float);
extern "C" void* func_0028B180();
extern "C" void func_0029CED8(void*, int, void*, float);

extern "C" void cRider_collectMultiplier(void* self, float value)
{
    if (cRider_getMotionMode(self) == 1 || cRider_getMotionMode(self) == 4)
    {
        cRider_addBoostMeter(self, 4, cRiderMetrix_onMultiplierPickup(*(char**)((char*)self + 0x790), value));
        func_0029CED8(func_0028B180(), 2, self, value);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cRider_addBoostMeter(void*, int, float);
extern "C" float cRiderMetrix_onPointPickup(int);
extern "C" void* func_0028B180();
extern "C" void func_0029CED8(void*, int, void*, float);

extern "C" void cRider_collectPointIcon(void* self)
{
    cRider_addBoostMeter(self, 0x10, cRiderMetrix_onPointPickup(*(int*)((char*)self + 0x790)));
    func_0029CED8(func_0028B180(), 3, self, 1.0f);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void cRider_requestReaction(void* self, int mode, float t);
void cRider_addBoostMeter_fi(void*, float, int) __asm__("cRider_addBoostMeter");
void cMotionOwner_triggerSnowImpact_impl(void* self, void* a, void* b, int c, float x) __asm__("cMotionOwner_triggerSnowImpact__FPv");
extern "C" float cRiderMetrix_onLand(void* self, int stance, int alternate, int style, int flag);
extern "C" int func_00149778(void* self, int rider, int value);
void func_00270870_10E910(void* self, int key, void* p) __asm__("func_00270870");
extern "C" void func_002948D0(void* mgr, void* rider, float v);
extern void* D_004A28A8;
extern void* D_004A3500;

struct sVE_0010E910 { short delta; short index; int (*fn)(void*); };
struct sVEf_0010E910 { short delta; short index; void (*fn)(void*, float); };

extern "C" void cRider_awardLanding(char* self, int a1, int a2, int a3, char* evt, float t)
{
    char* m = *(char**)(self + 0x790);
    int c0 = *(int*)(m + 0x114);
    int b0 = *(int*)(m + 0x134);
    int d0 = *(int*)(m + 0x198);
    float r = cRiderMetrix_onLand(m, *(int*)(self + 0x320) != *(int*)(self + 0x324), a1, a2, a3);
    char* m1 = *(char**)(self + 0x790);
    int c1 = *(int*)(m1 + 0x114);
    int b1 = *(int*)(m1 + 0x134);
    int d1 = *(int*)(m1 + 0x198);
    func_00270870_10E910(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28), *(int*)(self + 0x86C), m1 + 0xFC);
    if (c0 < c1)
    {
        int v = *(int*)(self + 0x2F4);
        if (v < 10)
        {
            int d = c1 - c0;
            int lim = 10 - v;
            int nv = v + (d < lim ? d : lim);
            *(int*)(self + 0x2F4) = nv;
            if (nv == 10)
                *(float*)(self + 0x2F0) = 60.0f;
        }
    }
    cMotionOwner_triggerSnowImpact_impl(*(void**)(self + 0x77C), evt, evt + 0x10, *(int*)(evt + 0x4C), t);
    char* o = self + 0x6C0;
    sVE_0010E910* ve = &(*(sVE_0010E910**)o)[8];
    if (ve->fn(o + ve->delta))
    {
        if (b0 < b1)
            cRider_requestReaction(self, 3, 0.0f);
        else if (c0 < c1)
            cRider_requestReaction(self, 2, 0.0f);
        else if (func_00149778(cBE_getInterface_Fv(cBE_getBE(), 3), *(int*)(self + 0x86C), d1 - d0))
            cRider_requestReaction(self, 1, 0.0f);
    }
    cRider_addBoostMeter_fi(self, r, 1);
    if (0.0f < r)
        *(float*)(self + 0x2EC) = 0.0f;
    sVEf_0010E910* vf = &(*(sVEf_0010E910**)(self + 0x6C0))[17];
    vf->fn(self + vf->delta, t * 0.5f);
    func_002948D0(D_004A3500, self, r);
}

INCLUDE_ASM("ai/computer", cRider_enterCrash);

//100%
struct sCpuVt_F1C0 {
    short delta;
    short index;
    int (*fn)(void*);
};

extern "C" void cRider_addBoostMeter(void*, int, float);
// Called with an extra int argument here; bind a two-argument view by asm label.
void cRider_collectPointIcon_i(void* self, int v) __asm__("cRider_collectPointIcon");
extern "C" void func_00116120(void* rider, int a, int b);

extern "C" void cRider_applyPickupEffect(char* self, int cmd, float f)
{
    switch (cmd) {
    case 0:
    case 7:
        break;
    case 1: {
        char* o = self + 0x6C0;
        sCpuVt_F1C0* vt = *(sCpuVt_F1C0**)o;
        vt[13].fn(o + vt[13].delta);
        break;
    }
    case 2: {
        char* o = self + 0x6C0;
        sCpuVt_F1C0* vt = *(sCpuVt_F1C0**)o;
        vt[14].fn(o + vt[14].delta);
        break;
    }
    case 3: {
        char* o = self + 0x6C0;
        sCpuVt_F1C0* vt = *(sCpuVt_F1C0**)o;
        vt[15].fn(o + vt[15].delta);
        break;
    }
    case 4:
        cRider_addBoostMeter(self, 8, f);
        break;
    case 6:
        cRider_collectPointIcon_i(self, (int)f);
        break;
    case 5:
        func_00116120(self, 0, 4);
        break;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" float cRiderMetrix_onQuickRecover(int);
extern "C" void cRider_addBoostMeter(void*, int, float);

extern "C" void func_0010F280(void* self)
{
    cRider_addBoostMeter(self, 1, cRiderMetrix_onQuickRecover(*(int*)((char*)self + 0x790)));
}

extern "C" void* func_0011A0E0(int);

//100%
void* func_0010F2B8(void* self)
{
    return func_0011A0E0(*(int*)((char*)self + 0x790));
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_0011A110(int, int);
extern "C" void func_00159B08(void*, int, int);

extern "C" void func_0010F2D8(void* self, int a, int b)
{
    func_0011A110(*(int*)((char*)self + 0x790), b);
    func_00159B08(cBE_getInterface_Fv(cBE_getBE(), 0xD), *(int*)((char*)self + 0x86C), a);
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_00119EF8(int, int);
extern "C" void func_001599A0(void*, int, int);

extern "C" void func_0010F338(void* self, int a)
{
    func_00119EF8(*(int*)((char*)self + 0x790), 3);
    func_001599A0(cBE_getInterface_Fv(cBE_getBE(), 0xD), *(int*)((char*)self + 0x86C), a);
}

extern "C" void* cAI_initPairRecords(void* self);

//100%
void* func_0010F398(void* self)
{
    return cAI_initPairRecords(self);
}

//100%
struct sVE_0010F3B8 { short delta; short index; int (*fn)(void*); };
struct sEnt_0010F3B8 { int vis; int val; float dist; int c; int d; int e; int f; int g; int h; };
struct sRider_0010F3B8 { sEnt_0010F3B8 ent[6]; char pad[0x10]; int fE8; char pad2[0x4D8 - 0xEC]; float f4D8; };
struct sAI_0010F3B8 { char pad[0x28]; sRider_0010F3B8* riders[20]; int count; };
extern "C" int cRider_isInitDone(void*);
float cRider_getRemainingDistance(void* self);

// PORT: the unit declares this as returning void*; it returns nothing.
extern "C" void cAI_initPairRecords_impl(sAI_0010F3B8* self) __asm__("cAI_initPairRecords");
extern "C" void cAI_initPairRecords_impl(sAI_0010F3B8* self)
{
    int i;
    for (i = 0; i < self->count; i++)
    {
        int j;
        for (j = 0; j < 6; j++)
        {
            sEnt_0010F3B8* e = &self->riders[i]->ent[j];
            int v = 0;
            if (i != j && j < self->count)
                v = cRider_isInitDone(self->riders[i]) != 0;
            e->vis = v;
            if (j < self->count)
            {
                char* o = (char*)self->riders[j] + 0x6C0;
                sVE_0010F3B8* ve = &(*(sVE_0010F3B8**)o)[8];
                self->riders[i]->ent[j].val = ve->fn(o + ve->delta);
            }
            self->riders[i]->ent[j].dist = 10000000000.0f;
            self->riders[i]->ent[j].c = 0;
            self->riders[i]->ent[j].d = 0;
            self->riders[i]->ent[j].e = 0;
            self->riders[i]->ent[j].f = 0;
            self->riders[i]->ent[j].g = 0;
            self->riders[i]->ent[j].h = 0;
        }
        int none = -1;
        self->riders[i]->f4D8 = cRider_getRemainingDistance(self->riders[i]);
        self->riders[i]->fE8 = none;
    }
}

//100%
void* cBEAggressionInterface_getThis();
extern "C" int func_00155B50(void* agg, int a, int b);
extern "C" float func_0031C228(float x);
struct sComputer_0010F878;
extern "C" void cAI_updateDesignatedPeers(sComputer_0010F878* self);
extern "C" void cAI_updateRanking(void* self);

struct sVec_0010F560 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sVEntry0010F560 {
    short delta;
    short index;
    sVec_0010F560* (*fn)(void*);
};

struct sRiderInfo_0010F560 {
    int active;     // 0x0
    int f4;         // 0x4
    float dist;     // 0x8
    float angle;    // 0xC
    char pad10[0xC];
    int aggressive; // 0x1C
    int f20;        // 0x20
};

struct sRider_0010F560 {
    sRiderInfo_0010F560 info[6];  // 0x0
    char padD8[0xDC - 0xD8];
    float minDist;                // 0xDC
    float maxDist;                // 0xE0

    sVec_0010F560* getPos()
    {
        char* o = (char*)this + 0x6C0;
        sVEntry0010F560* e = &(*(sVEntry0010F560**)o)[5];
        return e->fn(o + e->delta);
    }
};

struct sComputer_0010F560 {
    char pad0[0x8];
    int frame;                       // 0x8
    char padC[0x28 - 0xC];
    sRider_0010F560* riders[0x14];   // 0x28
    int count;                       // 0x78
    char pad7C[0x84 - 0x7C];
    int skip;                        // 0x84
};

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sVec_0010F560 sub_0010F560(const sVec_0010F560& a, const sVec_0010F560& b)
{
    sVec_0010F560 r;
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

static inline float atan2_0010F560(float y, float x)
{
    if (x == 0.0f) {
        if (y == 0.0f) {
            return y;
        }
        if (y >= 0.0f) {
            return 1.5707963705062866f;
        }
        return -1.5707963705062866f;
    }
    float a = func_0031C228(y / x);
    if (x < 0.0f) {
        if (y > 0.0f) {
            a += 3.1415927410125732f;
        } else {
            a -= 3.1415927410125732f;
        }
    }
    return a;
}

// PORT: PS2-only inline asm (EE cvt.w.s truncates in the FPU; the C cast goes through a GPR).
static inline float ffloor_0010F560(float x)
{
    float t;
    __asm__("cvt.w.s %0,%1\n\tcvt.s.w %0,%0" : "=f"(t) : "f"(x));
    if (x < t) {
        t -= 1.0f;
    }
    return t;
}

static inline float wrap_0010F560(float x)
{
    return x - ffloor_0010F560(x * 0.15915493667125702f + 0.5f) * 6.2831854820251465f;
}

extern "C" void cAI_updatePairProximity(sComputer_0010F560* self)
{
    if (self->frame % 6 != 0) {
        return;
    }
    cAI_updateRanking(self);
    int n = self->count - self->skip;
    if (n < 2) {
        return;
    }
    for (int i = 0; i < n; i++) {
        self->riders[i]->minDist = -50000.0f;
        self->riders[i]->maxDist = 50000.0f;
        for (int j = i + 1; j < n; j++) {
            if (self->riders[i]->info[j].active == 0) {
                continue;
            }
            sVec_0010F560 d = sub_0010F560(*self->riders[i]->getPos(), *self->riders[j]->getPos());
            float dist;
            float dx = d.x;
            float dy = d.y;
            float sq = dx * dx + dy * dy;
            // PORT: sqrt.s (sqrtf without errno check)
            __asm__("sqrt.s %0, %1" : "=f"(dist) : "f"(sq));
            float ang = atan2_0010F560(dy, dx);
            self->riders[i]->info[j].dist = dist;
            self->riders[j]->info[i].dist = dist;
            self->riders[i]->info[j].angle = wrap_0010F560(ang + 3.1415927410125732f);
            self->riders[j]->info[i].angle = ang;
            if (func_00155B50(cBEAggressionInterface_getThis(), i, j) >= 2) {
                self->riders[i]->info[j].aggressive = 1;
            } else {
                self->riders[i]->info[j].aggressive = 0;
            }
        }
    }
    cAI_updateDesignatedPeers((sComputer_0010F878*)self);
}

//100%
void* cBEAggressionInterface_getThis();
extern "C" int func_00155B50(void* self, int a, int b);

struct sComputer_0010F878
{
    char pad0[0x28];
    char* mRiders[20];  // 0x28
    int mCount;         // 0x78
    int pad7C;          // 0x7C
    int f80;            // 0x80
};

extern "C" void cAI_updateDesignatedPeers(sComputer_0010F878* self)
{
    if (self->f80 <= 0) return;
    for (int i = 0; i < self->mCount; i++)
    {
        *(int*)(self->mRiders[i] + 0xF0) = 0;
        *(int*)(self->mRiders[i] + 0xF8) = -1;
        for (int j = 0; j < self->mCount; j++)
        {
            if (i == j) continue;
            int a = func_00155B50(cBEAggressionInterface_getThis(), i, j);
            if (a == 4)
            {
                *(int*)(self->mRiders[i] + 0xF0) = 1;
                *(int*)(self->mRiders[i] + 0xF8) = j;
            }
            *(int*)(self->mRiders[i] + 0xFC) = a;
        }
    }
}

INCLUDE_ASM("ai/computer", cAI_updateRanking);

// Number of riders whose value at +0xAB8 is v
extern "C" int cAI_countRidersOnRoute(void* self, int v)
{
    int n = 0;
    int i;
    for (i = 0; i < *(int*)((char*)self + 0x78); i++) {
        if (*(int*)(((char**)((char*)self + 0x28))[i] + 0xAB8) == v)
            n++;
    }
    return n;
}

//100%
struct sVEntry0010FC30 {
    short delta;
    short index;
    int (*fn)(void*);
};

struct sAi0010FC30
{
    char pad0[0x28];
    char* mRiders[20];
    int mCount;
};

extern "C" int cAI_countComputersOnRoute(sAi0010FC30* self, int team)
{
    int n = 0;
    for (int i = 0; i < self->mCount; i++)
    {
        char* obj = self->mRiders[i] + 0x6C0;
        sVEntry0010FC30* e = &(*(sVEntry0010FC30**)obj)[9];
        if (e->fn(obj + e->delta))
        {
            if (*(int*)(self->mRiders[i] + 0xAB8) == team)
                n++;
        }
    }
    return n;
}

INCLUDE_ASM("ai/computer", cMotionOwner_cMotionOwner);

//100%
extern "C" void cMotionOwner_loseMotionFocus();
extern "C" void cMotionOwner_gainMotionFocus(void*, int);

extern "C" void cMotionOwner_setMotionMode(void* self, int v)
{
    cMotionOwner_loseMotionFocus();
    int old = *(int*)((char*)self + 0xDE0);
    *(int*)((char*)self + 0xDE0) = v;
    cMotionOwner_gainMotionFocus(self, old);
}

//100%
extern "C" void cGroundMotion_loseFocus(void*, int);
// These take (self) in their own units; here the caller's second argument is passed through
void cAirMotion_loseFocus_pass(void*, int) __asm__("cAirMotion_loseFocus__FPv");
void cWipeoutMotion_loseFocus_pass(void*, int) __asm__("cWipeoutMotion_loseFocus__FPv");
extern "C" void cRailSlideMotion_loseFocus(void*, int);
extern "C" void cHandplantMotion_loseFocus(void*, int);

extern "C" void cMotionOwner_loseMotionFocus(char* self, int a1)
{
    switch (*(int*)(self + 0xDE0)) {
    case 0:
        cGroundMotion_loseFocus(self, a1);
        break;
    case 1:
        cAirMotion_loseFocus_pass(self + 0x20, a1);
        break;
    case 2:
        cWipeoutMotion_loseFocus_pass(self + 0x30, a1);
        break;
    case 3:
        break;
    case 4:
        cRailSlideMotion_loseFocus(self + 0xB0, a1);
        break;
    case 5:
        cHandplantMotion_loseFocus(self + 0x110, a1);
        break;
    }
}

//100%
void cGroundMotion_gainFocus_d(void*, int) __asm__("cGroundMotion_gainFocus");
void cAirMotion_gainFocus_d(void*, int) __asm__("cAirMotion_gainFocus");
void cWipeoutMotion_gainFocus_d(void*, int) __asm__("cWipeoutMotion_gainFocus");
void cRailSlideMotion_gainFocus_d(void*, int) __asm__("cRailSlideMotion_gainFocus");
void cHandplantMotion_gainFocus_d(void*, int) __asm__("cHandplantMotion_gainFocus");

extern "C" void cMotionOwner_gainMotionFocus(void* self_, int a1)
{
    char* self = (char*)self_;
    switch (*(int*)(self + 0xDE0)) {
    case 0:
        cGroundMotion_gainFocus_d(self, a1);
        break;
    case 1:
        cAirMotion_gainFocus_d(self + 0x20, a1);
        break;
    case 2:
        cWipeoutMotion_gainFocus_d(self + 0x30, a1);
        break;
    case 4:
        cRailSlideMotion_gainFocus_d(self + 0xB0, a1);
        break;
    case 5:
        cHandplantMotion_gainFocus_d(self + 0x110, a1);
        break;
    case 3:
        break;
    }
}

//100%
void cGroundMotion_update_d(void*) __asm__("cGroundMotion_update");
void cAirMotion_update_d(void*) __asm__("cAirMotion_update");
void cWipeoutMotion_update_d(void*) __asm__("cWipeoutMotion_update");
void func_00136958_d(void*) __asm__("func_00136958");
void cRailSlideMotion_update_d(void*) __asm__("cRailSlideMotion_update");
void cHandplantMotion_update_d(void*) __asm__("cHandplantMotion_update");

extern "C" void cMotionOwner_updateMotion(char* self)
{
    switch (*(int*)(self + 0xDE0)) {
    case 0:
        cGroundMotion_update_d(self);
        break;
    case 1:
        cAirMotion_update_d(self + 0x20);
        break;
    case 2:
        cWipeoutMotion_update_d(self + 0x30);
        break;
    case 3:
        func_00136958_d(self + 0xA0);
        break;
    case 4:
        cRailSlideMotion_update_d(self + 0xB0);
        break;
    case 5:
        cHandplantMotion_update_d(self + 0x110);
        break;
    }
}

//100%
void cGroundMotion_postUpdate_d(void*) __asm__("cGroundMotion_postUpdate");
void cAirMotion_postUpdate_d(void*) __asm__("cAirMotion_postUpdate");
void cWipeoutMotion_postUpdate_d(void*) __asm__("cWipeoutMotion_postUpdate");
void func_00136978_d(void*) __asm__("func_00136978__FPv");
void cRailSlideMotion_postUpdate_d(void*) __asm__("cRailSlideMotion_postUpdate");
void cHandplantMotion_postUpdate_d(void*) __asm__("cHandplantMotion_postUpdate__FPv");

extern "C" void cMotionOwner_postUpdateMotion(char* self)
{
    switch (*(int*)(self + 0xDE0)) {
    case 0:
        cGroundMotion_postUpdate_d(self);
        break;
    case 1:
        cAirMotion_postUpdate_d(self + 0x20);
        break;
    case 2:
        cWipeoutMotion_postUpdate_d(self + 0x30);
        break;
    case 3:
        func_00136978_d(self + 0xA0);
        break;
    case 4:
        cRailSlideMotion_postUpdate_d(self + 0xB0);
        break;
    case 5:
        cHandplantMotion_postUpdate_d(self + 0x110);
        break;
    }
}

//100%
extern "C" void cMotionOwner_loseControlFocus();
extern "C" void cMotionOwner_gainControlFocus(void*, int);

extern "C" void cMotionOwner_setControlState(void* self, int v)
{
    cMotionOwner_loseControlFocus();
    int old = *(int*)((char*)self + 0xDE4);
    *(int*)((char*)self + 0xDE4) = v;
    cMotionOwner_gainControlFocus(self, old);
}

//100%
void cCruiseControl_loseFocus_d(void*, int) __asm__("cCruiseControl_loseFocus");
void cBoardPressControl_loseFocus_d(void*, int) __asm__("cBoardPressControl_loseFocus");
void cPrewindControl_loseFocus_d(void*, int) __asm__("cPrewindControl_loseFocus__FPv");
void cNaturalAirControl_loseFocus_d(void*, int) __asm__("cNaturalAirControl_loseFocus");
void cSpinControl_loseFocus_d(void*, int) __asm__("cSpinControl_loseFocus");
void cRailSlideControl_loseFocus_d(void*, int) __asm__("cRailSlideControl_loseFocus");
void cWipeoutControl_loseFocus_d(void*, int) __asm__("cWipeoutControl_loseFocus");
void cHandplantControl_loseFocus_d(void*, int) __asm__("cHandplantControl_loseFocus");

extern "C" void cMotionOwner_loseControlFocus(char* self, int a1)
{
    switch (*(int*)(self + 0xDE4)) {
    case 0:
        cCruiseControl_loseFocus_d(self + 0x1C0, a1);
        break;
    case 1:
        cBoardPressControl_loseFocus_d(self + 0x1D0, a1);
        break;
    case 2:
        cPrewindControl_loseFocus_d(self + 0x1F0, a1);
        break;
    case 4:
        cNaturalAirControl_loseFocus_d(self + 0x210, a1);
        break;
    case 5:
        cSpinControl_loseFocus_d(self + 0x230, a1);
        break;
    case 7:
        cRailSlideControl_loseFocus_d(self + 0x2B0, a1);
        break;
    case 8:
        cWipeoutControl_loseFocus_d(self + 0x2C0, a1);
        break;
    case 11:
        cHandplantControl_loseFocus_d(self + 0x370, a1);
        break;
    case 3: case 6: case 9: case 10: case 12: case 13:
        break;
    }
}

//100%
void cCruiseControl_gainFocus_d(void*, int) __asm__("cCruiseControl_gainFocus__FPv");
void cBoardPressControl_gainFocus_d(void*, int) __asm__("cBoardPressControl_gainFocus__FPv");
void cPrewindControl_gainFocus_d(void*, int) __asm__("cPrewindControl_gainFocus");
void cNaturalAirControl_gainFocus_d(void*, int) __asm__("cNaturalAirControl_gainFocus");
void cSpinControl_gainFocus_d(void*, int) __asm__("cSpinControl_gainFocus");
void cGateControl_gainFocus_d(void*, int) __asm__("cGateControl_gainFocus");
void cRailSlideControl_gainFocus_d(void*, int) __asm__("cRailSlideControl_gainFocus");
void cWipeoutControl_gainFocus_d(void*, int) __asm__("cWipeoutControl_gainFocus");
void cResetControl_gainFocus_d(void*, int) __asm__("cResetControl_gainFocus");
void func_0012C5C8_d(void*, int) __asm__("func_0012C5C8");
void cHandplantControl_gainFocus_d(void*, int) __asm__("cHandplantControl_gainFocus");
void cUberGrindControl_gainFocus_d(void*, int) __asm__("cUberGrindControl_gainFocus");

extern "C" void cMotionOwner_gainControlFocus(void* self_, int a1)
{
    char* self = (char*)self_;
    switch (*(int*)(self + 0xDE4)) {
    case 0:
        cCruiseControl_gainFocus_d(self + 0x1C0, a1);
        break;
    case 1:
        cBoardPressControl_gainFocus_d(self + 0x1D0, a1);
        break;
    case 2:
        cPrewindControl_gainFocus_d(self + 0x1F0, a1);
        break;
    case 4:
        cNaturalAirControl_gainFocus_d(self + 0x210, a1);
        break;
    case 5:
        cSpinControl_gainFocus_d(self + 0x230, a1);
        break;
    case 6:
        cGateControl_gainFocus_d(self + 0x290, a1);
        break;
    case 7:
        cRailSlideControl_gainFocus_d(self + 0x2B0, a1);
        break;
    case 8:
        cWipeoutControl_gainFocus_d(self + 0x2C0, a1);
        break;
    case 9:
        cResetControl_gainFocus_d(self + 0x350, a1);
        break;
    case 10:
        func_0012C5C8_d(self + 0x360, a1);
        break;
    case 11:
        cHandplantControl_gainFocus_d(self + 0x370, a1);
        break;
    case 12:
        cUberGrindControl_gainFocus_d(self + 0x390, a1);
        break;
    case 3: case 13:
        break;
    }
}

//100%
void cCruiseControl_update_d(void*, int) __asm__("cCruiseControl_update");
void cBoardPressControl_update_d(void*, int) __asm__("cBoardPressControl_update");
void cPrewindControl_update_d(void*, int) __asm__("cPrewindControl_update");
void func_0012E778_d(void*, int) __asm__("func_0012E778");
void cNaturalAirControl_update_d(void*, int) __asm__("cNaturalAirControl_update");
void cSpinControl_update_d(void*, int) __asm__("cSpinControl_update");
void cGateControl_update_d(void*, int) __asm__("cGateControl_update");
void cRailSlideControl_update_d(void*, int) __asm__("cRailSlideControl_update");
void cWipeoutControl_update_d(void*, int) __asm__("cWipeoutControl_update");
void cResetControl_update_d(void*, int) __asm__("cResetControl_update");
void cFinishControl_update_d(void*, int) __asm__("cFinishControl_update");
void cHandplantControl_update_d(void*, int) __asm__("cHandplantControl_update");
void cUberGrindControl_update_d(void*, int) __asm__("cUberGrindControl_update");

extern "C" void cMotionOwner_updateControl(char* self, int a1)
{
    switch (*(int*)(self + 0xDE4)) {
    case 0:
        cCruiseControl_update_d(self + 0x1C0, a1);
        break;
    case 1:
        cBoardPressControl_update_d(self + 0x1D0, a1);
        break;
    case 2:
        cPrewindControl_update_d(self + 0x1F0, a1);
        break;
    case 3:
        func_0012E778_d(self + 0x200, a1);
        break;
    case 4:
        cNaturalAirControl_update_d(self + 0x210, a1);
        break;
    case 5:
        cSpinControl_update_d(self + 0x230, a1);
        break;
    case 6:
        cGateControl_update_d(self + 0x290, a1);
        break;
    case 7:
        cRailSlideControl_update_d(self + 0x2B0, a1);
        break;
    case 8:
        cWipeoutControl_update_d(self + 0x2C0, a1);
        break;
    case 9:
        cResetControl_update_d(self + 0x350, a1);
        break;
    case 10:
        cFinishControl_update_d(self + 0x360, a1);
        break;
    case 11:
        cHandplantControl_update_d(self + 0x370, a1);
        break;
    case 12:
        cUberGrindControl_update_d(self + 0x390, a1);
        break;
    case 13:
        break;
    }
}

extern char* D_00459D70[];
extern char D_00456C48[];

extern "C" char* cMotionOwner_getMotionModeName(void* self)
{
    unsigned int i = *(unsigned int*)((char*)self + 0xDE0);
    if (i >= 7)
        return D_00456C48;
    return D_00459D70[i];
}

extern char* D_00459DC8[];

extern "C" char* cMotionOwner_getControlStateName(void* self)
{
    unsigned int i = *(unsigned int*)((char*)self + 0xDE4);
    if (i >= 15)
        return D_00456C48;
    return D_00459DC8[i];
}

//100%
extern "C" void func_002DCF28(void*);
extern "C" void func_002DAA78(void*);
extern "C" void func_002E8560(void*);
extern "C" void func_002E6640(void*);
void func_002EADC0(void*);
extern "C" void func_002EF6A0(void*);
extern "C" void func_002D4BE0(void*);
extern "C" void func_002E3930(void*);
extern "C" void func_002DF3B0(void*);
extern "C" void func_002F1148(void*);
void func_002F64E8(void*);
// PORT: cWorldPainterMan_reset is defined with an unused self param; this caller passes none.
void cWorldPainterMan_reset_noarg() __asm__("cWorldPainterMan_reset__FPv");
void* func_002306A8(void* self, int i);
extern void* D_004A28A8;

struct sVEntry00111890 { short delta; short index; void (*fn)(void*); };

extern "C" void cMotionOwner_resetFX(void* self)
{
    char* s = (char*)self;
    func_002DCF28(s + 0x3B0);
    func_002DAA78(s + 0x470);
    func_002E8560(s + 0x520);
    func_002E6640(s + 0x610);
    func_002EADC0(s + 0x9C0);
    func_002EF6A0(s + 0xAD0);
    func_002D4BE0(s + 0xAF0);
    func_002E3930(s + 0xB00);
    func_002DF3B0(s + 0xB40);
    func_002F1148(s + 0xC70);
    func_002F64E8(s + 0xD20);
    cWorldPainterMan_reset_noarg();
    int id = *(int*)(*(char**)(s + 0x18) + 0x870);
    if (id >= 0)
    {
        char* obj = (char*)func_002306A8(*(void**)((char*)D_004A28A8 + 0x84), id);
        if (obj != 0)
        {
            sVEntry00111890* vt = *(sVEntry00111890**)(obj + 0xC);
            vt[14].fn(obj + vt[14].delta);
        }
    }
}

extern "C" void* func_002E23E0(void*);

//100%
extern int D_004A4534;

// Runs the per-frame update of each AI controller block, unless D_004A4534 is set and the rider says to skip (virtual slot 9).
extern "C" void func_00392D18(void* p);
extern "C" void func_002DD0B8(void* p);
extern "C" void func_002DABC8(void* p);
extern "C" void func_002E8938(void* p);
extern "C" void func_002E66B8(void* p);
extern "C" void func_002EADD0(void* p);
extern "C" void func_002EF6D0(void* p);
extern "C" void func_002D4C08(void* p);
extern "C" void func_002E39D8(void* p);
extern "C" void func_002DF920(void* p);
extern "C" void func_002F1150(void* p);
extern "C" void func_002F6518(void* p);

extern "C" void cMotionOwner_updateFX(char* self)
{
    if (D_004A4534 != 0)
    {
        char* o = *(char**)(self + 0x18) + 0x6C0;
        sVE_0010DA10* ve = &(*(sVE_0010DA10**)o)[9];
        if (ve->fn(o + ve->delta))
            return;
    }
    func_00392D18(self + 0xD30);
    func_002DD0B8(self + 0x3B0);
    func_002DABC8(self + 0x470);
    func_002E8938(self + 0x520);
    func_002E66B8(self + 0x610);
    func_002EADD0(self + 0x9C0);
    func_002EF6D0(self + 0xAD0);
    func_002D4C08(self + 0xAF0);
    func_002E39D8(self + 0xB00);
    func_002DF920(self + 0xB40);
    func_002F1150(self + 0xC70);
    func_002F6518(self + 0xD20);
}

//100%
// Runs the second update pass of each AI controller block, with the same skip check.
extern "C" void func_002DDAB8(void* p);
extern "C" void func_002DB478(void* p);
extern "C" void func_002EA480(void* p);
extern "C" void func_002E7A10(void* p);
extern "C" void func_002EB198(void* p);
extern "C" void func_002EF950(void* p);
extern "C" void func_002D5048(void* p);
extern "C" void func_002E3AF8(void* p);
extern "C" void func_002E24D0(void* p);
extern "C" void func_002F1510(void* p);
void func_002F6908(void* p);

extern "C" void func_001119F8(char* self)
{
    if (D_004A4534 != 0)
    {
        char* o = *(char**)(self + 0x18) + 0x6C0;
        sVE_0010DA10* ve = &(*(sVE_0010DA10**)o)[9];
        if (ve->fn(o + ve->delta))
            return;
    }
    func_002DDAB8(self + 0x3B0);
    func_002DB478(self + 0x470);
    func_002EA480(self + 0x520);
    func_002E7A10(self + 0x610);
    func_002EB198(self + 0x9C0);
    func_002EF950(self + 0xAD0);
    func_002D5048(self + 0xAF0);
    func_002E3AF8(self + 0xB00);
    func_002E24D0(self + 0xB40);
    func_002F1510(self + 0xC70);
    func_002F6908(self + 0xD20);
}

//100%
// PORT: prototype mismatch. The project names this cMotionOwner_triggerSnowImpact__FPv (one
// void* param), but every caller passes (self, vecA, vecB, int, float) and the
// body forwards them to func_002E23E0 with an extra 0 flag. The unit declares
// func_002E23E0 as (void*), so both are bound by asm label.
void func_002E23E0_impl(void* self, void* a, void* b, int c, int flag, float x) __asm__("func_002E23E0");

void cMotionOwner_triggerSnowImpact_impl(void* self, void* a, void* b, int c, float x) __asm__("cMotionOwner_triggerSnowImpact__FPv");

void cMotionOwner_triggerSnowImpact_impl(void* self, void* a, void* b, int c, float x)
{
    func_002E23E0_impl((char*)self + 0xB40, a, b, c, 0, x);
}

//100%
class cStream_00111AC0 {
public:
    virtual void Write(void* p, int n);
};

extern char D_004D33A0[];
extern "C" void func_00104D68(void* self, void* s);
extern "C" void func_00310EA8(void* self, void* s);
extern "C" void cAirPredictor_saveState(void* self, void* s);
extern "C" void cRiderMetrix_saveState(void* self, void* s);
extern "C" void cGroundMotion_writeToReplayFrame(void* self, void* s);
extern "C" void cAirMotion_writeToReplayFrame(void* self, void* s);
extern "C" void cWipeoutMotion_writeToReplayFrame(void* self, void* s);
extern "C" void cRailSlideMotion_writeToReplayFrame(void* self, void* s);
extern "C" void cHandplantMotion_writeToReplayFrame(void* self, void* s);
extern "C" void cBoardPressControl_writeToReplayFrame(void* self, void* s);
extern "C" void cNaturalAirControl_writeToReplayFrame(void* self, void* s);
extern "C" void cSpinControl_writeToReplayFrame(void* self, void* s);
extern "C" void cGateControl_writeToReplayFrame(void* self, void* s);
extern "C" void cRailSlideControl_writeToReplayFrame(void* self, void* s);
extern "C" void cWipeoutControl_writeToReplayFrame(void* self, void* s);
extern "C" void cResetControl_writeToReplayFrame(void* self, void* s);
extern "C" void cFinishControl_writeToReplayFrame(void* self, void* s);
extern "C" void cHandplantControl_writeToReplayFrame(void* self, void* s);
extern "C" void cUberGrindControl_writeToReplayFrame(void* self, void* s);
extern "C" void func_002F6A58(void* self, void* s);
extern "C" int func_0026B508(void* tree, void* path);
extern "C" int func_0026B550(void* tree, void* path);

extern "C" void cMotionOwner_saveState(char* self, char* s)
{
    cStream_00111AC0* st = (cStream_00111AC0*)s;
    st->Write(*(void**)(self + 0x18), 0x6C0);
    func_00104D68(*(void**)(*(char**)(self + 0x18) + 0x784), s);
    func_00310EA8(*(void**)(*(char**)(self + 0x18) + 0x780), s);
    cAirPredictor_saveState(*(void**)(*(char**)(self + 0x18) + 0x788), s);
    cRiderMetrix_saveState(*(void**)(*(char**)(self + 0x18) + 0x790), s);
    unsigned int id0 = 0xFFFFFFFF;
    char* p0 = **(char***)(*(char**)(self + 0x18) + 0x864);
    if (p0 != 0) {
        id0 = *(unsigned int*)(p0 + 0x150);
    }
    st->Write(&id0, 4);
    st->Write(*(void**)(*(char**)(self + 0x18) + 0x864), 0x10);
    unsigned int id1 = 0xFFFFFFFF;
    char* p1 = **(char***)(*(char**)(self + 0x18) + 0x868);
    if (p1 != 0) {
        id1 = *(unsigned int*)(p1 + 0x150);
    }
    st->Write(&id1, 4);
    st->Write(*(void**)(*(char**)(self + 0x18) + 0x868), 0x10);
    st->Write(self + 0xDE0, 4);
    st->Write(self + 0xDE4, 4);
    cGroundMotion_writeToReplayFrame(self, s);
    cAirMotion_writeToReplayFrame(self + 0x20, s);
    cWipeoutMotion_writeToReplayFrame(self + 0x30, s);
    cRailSlideMotion_writeToReplayFrame(self + 0xB0, s);
    cHandplantMotion_writeToReplayFrame(self + 0x110, s);
    cBoardPressControl_writeToReplayFrame(self + 0x1D0, s);
    cNaturalAirControl_writeToReplayFrame(self + 0x210, s);
    cSpinControl_writeToReplayFrame(self + 0x230, s);
    cGateControl_writeToReplayFrame(self + 0x290, s);
    cRailSlideControl_writeToReplayFrame(self + 0x2B0, s);
    cWipeoutControl_writeToReplayFrame(self + 0x2C0, s);
    cResetControl_writeToReplayFrame(self + 0x350, s);
    cFinishControl_writeToReplayFrame(self + 0x360, s);
    cHandplantControl_writeToReplayFrame(self + 0x370, s);
    cUberGrindControl_writeToReplayFrame(self + 0x390, s);
    func_002F6A58(self + 0xD20, s);
    st->Write(*(void**)(*(char**)(self + 0x18) + 0xABC), 0x20);
    st->Write(*(void**)(*(char**)(self + 0x18) + 0xAC0), 0x20);
    int ids[2];
    ids[0] = func_0026B508(D_004D33A0, *(void**)(*(char**)(self + 0x18) + 0xAB4));
    ids[1] = func_0026B550(D_004D33A0, *(void**)(*(char**)(self + 0x18) + 0xAB8));
    st->Write(ids, 8);
}

//100%
class cStream_00111D98 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void v01(void* p, int n);
    virtual void Read(void* p, int n);
};

struct sRefSet_00111D98 {
    char pad_0x0[0xC];
    unsigned int* refs;     // 0xC
};

struct sRefWorld_00111D98 {
    char pad_0x0[0x8];
    sRefSet_00111D98** sets;    // 0x8
};

extern sRefWorld_00111D98** D_004A47B8;
extern char D_004D33A0[];
extern "C" void func_00104DE0(void* self, void* s);
extern "C" void func_00310EE0(void* self, void* s);
extern "C" void cAirPredictor_loadState(void* self, void* s);
extern "C" void cRiderMetrix_loadState(void* self, void* s);
extern "C" void cGroundMotion_readFromReplayFrame(void* self, void* s);
extern "C" void cAirMotion_readFromReplayFrame(void* self, void* s);
extern "C" void cWipeoutMotion_readFromReplayFrame(void* self, void* s);
extern "C" void cRailSlideMotion_readFromReplayFrame(void* self, void* s);
extern "C" void cHandplantMotion_readFromReplayFrame(void* self, void* s);
extern "C" void cBoardPressControl_readFromReplayFrame(void* self, void* s);
extern "C" void cNaturalAirControl_readFromReplayFrame(void* self, void* s);
extern "C" void cSpinControl_readFromReplayFrame(void* self, void* s);
extern "C" void cGateControl_readFromReplayFrame(void* self, void* s);
extern "C" void cRailSlideControl_readFromReplayFrame(void* self, void* s);
extern "C" void cWipeoutControl_readFromReplayFrame(void* self, void* s);
extern "C" void cResetControl_readFromReplayFrame(void* self, void* s);
extern "C" void cFinishControl_readFromReplayFrame(void* self, void* s);
extern "C" void cHandplantControl_readFromReplayFrame(void* self, void* s);
extern "C" void cUberGrindControl_readFromReplayFrame(void* self, void* s);
extern "C" void func_002DCF28(void*);
extern "C" void func_002DAA78(void*);
extern "C" void func_002E8560(void*);
extern "C" void func_002E6640(void*);
void func_002EADC0(void*);
extern "C" void func_002EF6A0(void*);
extern "C" void func_002D4BE0(void*);
extern "C" void func_002E3930(void*);
extern "C" void func_002F1148(void*);
extern "C" void func_002F6A90(void* self, void* s);
extern "C" void* func_0026AF70(void* tree, int id);
extern "C" void* func_0026AF88(void* tree, int id);
extern "C" void func_00312598(void* self, int a1);
extern "C" void func_003103F0(void* self);
extern "C" void func_00106828(void* self);

static inline void* idxToPtr_00111D98(unsigned int i)
{
    return (void*)(i << 2);
}

static inline void* refToPtr_00111D98(unsigned int v)
{
    unsigned int i = v >> 8;
    if (i == 0) {
        return 0;
    }
    return idxToPtr_00111D98(i);
}

struct sRef_00111D98 {
    unsigned int id;
    sRef_00111D98() : id(0xFFFFFFFF) {}

    void* get()
    {
        sRefSet_00111D98* set = (*D_004A47B8)->sets[id & 0xFF];
        if (set == 0) {
            return 0;
        }
        return refToPtr_00111D98(set->refs[id >> 8]);
    }
};

struct sQuad_00111D98 {
    int v[4];
} __attribute__((aligned(16)));

extern "C" void cMotionOwner_loadState(char* self, char* s)
{
    cStream_00111D98* st = (cStream_00111D98*)s;
    st->Read(*(void**)(self + 0x18), 0x6C0);
    func_00104DE0(*(void**)(*(char**)(self + 0x18) + 0x784), s);
    func_00310EE0(*(void**)(*(char**)(self + 0x18) + 0x780), s);
    cAirPredictor_loadState(*(void**)(*(char**)(self + 0x18) + 0x788), s);
    cRiderMetrix_loadState(*(void**)(*(char**)(self + 0x18) + 0x790), s);
    int ids[2];
    sRef_00111D98 r0;
    st->Read(&r0, 4);
    st->Read(*(void**)(*(char**)(self + 0x18) + 0x864), 0x10);
    if (~r0.id != 0) {
        **(void***)(*(char**)(self + 0x18) + 0x864) = r0.get();
    }
    sRef_00111D98 r1;
    st->Read(&r1, 4);
    st->Read(*(void**)(*(char**)(self + 0x18) + 0x868), 0x10);
    if (~r1.id != 0) {
        **(void***)(*(char**)(self + 0x18) + 0x868) = r1.get();
    }
    st->Read(self + 0xDE0, 4);
    st->Read(self + 0xDE4, 4);
    cGroundMotion_readFromReplayFrame(self, s);
    cAirMotion_readFromReplayFrame(self + 0x20, s);
    cWipeoutMotion_readFromReplayFrame(self + 0x30, s);
    cRailSlideMotion_readFromReplayFrame(self + 0xB0, s);
    cHandplantMotion_readFromReplayFrame(self + 0x110, s);
    cBoardPressControl_readFromReplayFrame(self + 0x1D0, s);
    cNaturalAirControl_readFromReplayFrame(self + 0x210, s);
    cSpinControl_readFromReplayFrame(self + 0x230, s);
    cGateControl_readFromReplayFrame(self + 0x290, s);
    cRailSlideControl_readFromReplayFrame(self + 0x2B0, s);
    cWipeoutControl_readFromReplayFrame(self + 0x2C0, s);
    cResetControl_readFromReplayFrame(self + 0x350, s);
    cFinishControl_readFromReplayFrame(self + 0x360, s);
    cHandplantControl_readFromReplayFrame(self + 0x370, s);
    cUberGrindControl_readFromReplayFrame(self + 0x390, s);
    func_002DCF28(self + 0x3B0);
    func_002DAA78(self + 0x470);
    func_002E8560(self + 0x520);
    func_002E6640(self + 0x610);
    func_002EADC0(self + 0x9C0);
    func_002EF6A0(self + 0xAD0);
    func_002D4BE0(self + 0xAF0);
    func_002E3930(self + 0xB00);
    func_002F1148(self + 0xC70);
    func_002F6A90(self + 0xD20, s);
    st->Read(*(void**)(*(char**)(self + 0x18) + 0xABC), 0x20);
    st->Read(*(void**)(*(char**)(self + 0x18) + 0xAC0), 0x20);
    st->Read(ids, 8);
    *(void**)(*(char**)(self + 0x18) + 0xAB4) = func_0026AF70(D_004D33A0, ids[0]);
    *(void**)(*(char**)(self + 0x18) + 0xAB8) = func_0026AF88(D_004D33A0, ids[1]);
    sQuad_00111D98* q = *(sQuad_00111D98**)(*(char**)(self + 0x18) + 0x78C);
    if (q != 0) {
        *q = *(sQuad_00111D98*)(*(char**)(self + 0x18) + 0x110);
    }
    func_00312598(*(void**)(*(char**)(self + 0x18) + 0x784), 0);
    func_003103F0(*(void**)(*(char**)(self + 0x18) + 0x780));
    func_00106828(*(void**)(self + 0x18));
}

//100%
extern "C" void* func_0026B5E0(void*, int, int);
extern char D_004D33A0[];
extern "C" float func_00115B08(void* self);

struct sVec4_00112180
{
    float x, y, z, w;
} __attribute__((aligned(16)));

void cRider_placeAt_112180(void* self, sVec4_00112180* a, sVec4_00112180* b, int n, float t) __asm__("cRider_placeAt");
extern "C" float func_0026A638(void* path, void* a1, void* a2, void* a3, void* hint, int n);
sVec4_00112180 func_0026AB20_112180(void* path, int* inRange, float t) __asm__("func_0026AB20");

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_00112180 vu0Scale_112180(const sVec4_00112180& v, float s)
{
    sVec4_00112180 r;
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

// PORT: PS2-only VU0 inline asm (vector add-assign).
static inline void vu0AddEq_112180(sVec4_00112180& dst, sVec4_00112180 b)
{
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        ".set pop\n"
        : "=m"(dst)
        : "m"(dst), "m"(b));
}

extern "C" void func_00112180(char* self, int flag)
{
    float* p = (float*)func_0026B5E0(D_004D33A0, 1, *(int*)(self + 0x86C));
    if (flag)
    {
        sVec4_00112180 dir;
        sVec4_00112180 pos;
        dir.x = p[5];
        dir.y = p[6];
        dir.z = p[7];
        dir.w = 0.0f;
        pos.x = p[2];
        pos.y = p[3];
        pos.z = p[4];
        pos.w = 1.0f;
        vu0AddEq_112180(pos, vu0Scale_112180(dir, func_00115B08(self)));
        cRider_placeAt_112180(self, &pos, &dir, 5, 0.0f);
    }
    *(int*)(*(char**)(self + 0xABC) + 0x14) = -1;
    *(int*)(*(char**)(self + 0xAC0) + 0x14) = -1;
    *(void**)(self + 0xAB4) = ((void**)p)[8];
    *(void**)(self + 0xAB8) = ((void**)p)[9];
    sVec4_00112180 up;
    up.x = 0.0f;
    up.y = 0.0f;
    up.z = 0.0f;
    up.w = 1.0f;
    float out;
    float res = func_0026A638(*(void**)(self + 0xAB4), self + 0x110, &up, &out, *(void**)(self + 0xAC0), 1);
    float t = *(float*)(*(char**)(self + 0xAB4) + 0x38);
    if (t < res)
        res = 0.0f;
    *(float*)(self + 0x4D0) = *(float*)(self + 0x4D4) = t - res;
    res = func_0026A638(*(void**)(self + 0xAB8), self + 0x110, self + 0x490, self + 0x4C8, *(void**)(self + 0xABC), 1);
    *(float*)(self + 0x4C0) = *(float*)(self + 0x4C4) = res;
    sVec4_00112180 pos2 = func_0026AB20_112180(*(void**)(self + 0xAB8), 0, res + 796.0f);
    *(sVec4_00112180*)(self + 0x4A0) = pos2;
}

//100%
struct sEnt_00112338 { int a; int b; int c; int d; };
struct sComp_00112338 { char pad[0x4DC]; sEnt_00112338 ent[12]; int count; };
struct sVec4_00112338 { float x, y, z, w; } __attribute__((aligned(16)));
struct sVE_00112338 { short delta; short index; int (*fn)(void*, float, float); };

extern sEnt_00112338 D_004A5D60[];
extern void* D_004A28A8;
extern "C" void* func_003E6574(void*, void*, int);
extern "C" void func_00112FB0(void* self, float* a, float* b, sVec4_00112338* c);
extern "C" void cRider_selectCoursePath(void* self, int a);
extern "C" float func_0026AC48(void* self);
extern "C" void cRider_onCourseEvent(void* self, int* arg, int a2, int a3);

extern "C" void cRider_updateCourseProgress(char* self)
{
    sComp_00112338* s = (sComp_00112338*)self;
    func_003E6574(D_004A5D60, s->ent, s->count << 4);
    int n = s->count;
    sVec4_00112338 c;
    float a;
    float b;
    func_00112FB0(self, &a, &b, &c);
    if (0.0f < *(float*)(self + 0x4D4))
    {
        void* old = *(void**)(self + 0xAB4);
        if (500.0f < a && *(int*)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0x8) % 60 == 0)
            cRider_selectCoursePath(self, 0);
        else if (func_0026AC48(*(void**)(self + 0xAB4)) - 200.0f < b)
            cRider_selectCoursePath(self, 1);
        else
        {
            char* o = *(char**)(self + 0xAB4);
            sVE_00112338* ve = &(*(sVE_00112338**)(o + 0x34))[2];
            if (ve->fn(o + ve->delta, *(float*)(self + 0x4D4), *(float*)(self + 0x4D0)))
                cRider_selectCoursePath(self, 0);
        }
        if (*(void**)(self + 0xAB4) != old)
        {
            *(int*)(*(char**)(self + 0xAC0) + 0x14) = -1;
            func_00112FB0(self, &a, &b, &c);
        }
    }
    int i;
    for (i = 0; i < s->count; i++)
    {
        int j;
        for (j = 0; j < n; j++)
        {
            if (s->ent[i].a == D_004A5D60[j].a && s->ent[i].b == D_004A5D60[j].b)
            {
                D_004A5D60[j].a = 0;
                break;
            }
        }
        cRider_onCourseEvent(self, (int*)&s->ent[i], j < n, 1);
    }
    for (i = 0; i < n; i++)
    {
        if (D_004A5D60[i].a)
            cRider_onCourseEvent(self, (int*)&D_004A5D60[i], 1, 0);
    }
}

//100%
extern "C" float func_00112588(void* self, int arg1)
{
    float v = 796.0f;
    if (arg1 == 0) {
        v = 200.0f;
    }
    return v;
}

// R5900 128-bit GPR quadword, for functions that copy/return a 16-byte
// block via a single lq/sq pair instead of word-by-word.
typedef int cQuad128 __attribute__((mode(TI)));

//100%
extern "C" cQuad128 func_001125A8(void* self)
{
    cQuad128 v = *(cQuad128*)((char*)self + 0x4A0);
    *(cQuad128*)((char*)self + 0x4B0) = v;
    return v;
}

//100%
int func_001125B8(void* self)
{
    return 0;
}

//100%
struct sVec4_001125C0
{
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sVE_001125C0 { short delta; short index; int (*fn)(void*, float, float); };

// PORT: the unit defines func_001125B8 as int; here its result is used as a bool (xori 1).
bool func_001125B8_b(void* self) __asm__("func_001125B8__FPv");
// PORT: the unit defines func_001125A8(void* self); callers pass a second arg in $5.
cQuad128 func_001125A8_2(void* self, int a) __asm__("func_001125A8");
extern "C" float func_0026A638(void* path, void* a1, void* a2, void* a3, void* hint, int n);
extern "C" float func_0026A428(void* path, void* a1, void* a2, void* a3, int n);
sVec4_001125C0 func_0026AB20_1125C0(void* path, int* inRange, float t) __asm__("func_0026AB20");
extern "C" float func_0026AC48(void* self);
extern "C" void cRider_selectRoute(void* self, int a);
extern void* D_004A28A8;

static inline float atan2_001125C0(float y, float x)
{
    if (x == 0.0f) {
        if (y == 0.0f) {
            return y;
        }
        if (y >= 0.0f) {
            return 1.5707963705062866f;
        }
        return -1.5707963705062866f;
    }
    float a = func_0031C228(y / x);
    if (x < 0.0f) {
        if (y > 0.0f) {
            a += 3.1415927410125732f;
        } else {
            a -= 3.1415927410125732f;
        }
    }
    return a;
}

extern "C" void cRider_updateRouteProgress(char* self)
{
    *(float*)(self + 0x4C0) = *(float*)(self + 0x4C4);
    int nf = !func_001125B8_b(self);
    if (nf)
        *(float*)(self + 0x4C4) = func_0026A638(*(void**)(self + 0xAB8), self + 0x110, self + 0x490, self + 0x4C8, *(void**)(self + 0xABC), nf);
    else
        *(float*)(self + 0x4C4) = func_0026A428(*(void**)(self + 0xAB8), self + 0x110, self + 0x490, self + 0x4C8, 0);
    float k = func_00112588(self, nf);
    *(sVec4_001125C0*)(self + 0x4A0) = func_0026AB20_1125C0(*(void**)(self + 0xAB8), 0, *(float*)(self + 0x4C4) + k);
    func_001125A8_2(self, nf);
    if (0.0f < *(float*)(self + 0x4D4))
    {
        if (500.0f < *(float*)(self + 0x4C8) && *(int*)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0x8) % 60 == 0)
            cRider_selectRoute(self, 0);
        else if (func_0026AC48(*(void**)(self + 0xAB8)) - 200.0f < *(float*)(self + 0x4C4))
            cRider_selectRoute(self, 1);
        else
        {
            char* o = *(char**)(self + 0xAB8);
            sVE_001125C0* ve = &(*(sVE_001125C0**)(o + 0x34))[2];
            if (ve->fn(o + ve->delta, *(float*)(self + 0x4C0), *(float*)(self + 0x4C4)))
                cRider_selectRoute(self, 0);
        }
    }
    float dx = *(float*)(self + 0x4A0) - *(float*)(self + 0x490);
    float dy = *(float*)(self + 0x4A4) - *(float*)(self + 0x494);
    *(float*)(self + 0x4CC) = atan2_001125C0(dy, dx);
}

//100%
struct sVec4_1127F0 {
    float x, y, z, w;
} __attribute__((aligned(16)));

extern char D_004D33A0[];
extern "C" int func_0026B178(void* tree, void* pos, void** out, int maxOut);
extern "C" float func_0026A428(void* path, void* a1, void* a2, void* a3, int n);
sVec4_1127F0 func_0026AB20_1127F0(void* path, int* inRange, float t) __asm__("func_0026AB20");

// PORT: PS2-only VU0 inline asm (vector length).
static inline float vu0Length_1127F0(const sVec4_1127F0& v)
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

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_1127F0 vu0Scale_1127F0(const sVec4_1127F0& v, float s)
{
    sVec4_1127F0 r;
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
static inline sVec4_1127F0 vu0Add_1127F0(const sVec4_1127F0& a, const sVec4_1127F0& b)
{
    sVec4_1127F0 r;
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
static inline sVec4_1127F0 vu0Sub_1127F0(const sVec4_1127F0& a, const sVec4_1127F0& b)
{
    sVec4_1127F0 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0Dot_1127F0(const sVec4_1127F0& a, const sVec4_1127F0& b)
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

extern "C" void cRider_selectCoursePath(void* vself, int skipCur)
{
    char* self = (char*)vself;
    void* paths[3];
    sVec4_1127F0 out;
    sVec4_1127F0 pos;
    float len = vu0Length_1127F0(*(sVec4_1127F0*)(self + 0x1E0));
    void* best = *(void**)(self + 0xAB4);
    float bestD = 9.999999933815813e+36f;
    if (len == 0.0f) {
        pos = *(sVec4_1127F0*)(self + 0x110);
    } else {
        float s = func_00112588(self, 1) / len;
        pos = vu0Add_1127F0(*(sVec4_1127F0*)(self + 0x110), vu0Scale_1127F0(*(sVec4_1127F0*)(self + 0x1E0), s));
    }
    int n = func_0026B178(D_004D33A0, &pos, paths, 3);
    for (int i = 0; i < n; i++) {
        if (skipCur && paths[i] == *(void**)(self + 0xAB4)) {
            continue;
        }
        float tOut;
        float t = func_0026A428(paths[i], &pos, &out, &tOut, 1);
        if (paths[i] == *(void**)(self + 0xAB4)) {
            if (1592.0f < __builtin_fabsf(*(float*)((char*)paths[i] + 0x38) - *(float*)(self + 0x4D0) - t)) {
                *(int*)(*(char**)(self + 0xAC0) + 0x14) = -1;
            }
        }
        t += 796.0f;
        sVec4_1127F0 d1 = vu0Sub_1127F0(pos, func_0026AB20_1127F0(paths[i], 0, t));
        sVec4_1127F0 d0 = vu0Sub_1127F0(*(sVec4_1127F0*)(self + 0x110), out);
        float dist = vu0Dot_1127F0(d0, d0) + vu0Dot_1127F0(d1, d1);
        if (dist < bestD) {
            best = paths[i];
            bestD = dist;
        }
    }
    *(void**)(self + 0xAB4) = best;
}

//100%
struct sVec4_112A50 {
    float x, y, z, w;
} __attribute__((aligned(16)));

extern char D_004D33A0[];
extern "C" int func_0026AFB8(void* tree, void* pos, void** out, int maxOut, int a4);
extern "C" float func_0026AC48(void* self);
extern "C" float func_0026A638(void* path, void* a1, void* a2, void* a3, void* hint, int n);
extern "C" float func_0026A428(void* path, void* a1, void* a2, void* a3, int n);
sVec4_112A50 func_0026AB20_112A50(void* path, int* inRange, float t) __asm__("func_0026AB20");

// PORT: PS2-only VU0 inline asm (vector length).
static inline float vu0Length_112A50(const sVec4_112A50& v)
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

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_112A50 vu0Scale_112A50(const sVec4_112A50& v, float s)
{
    sVec4_112A50 r;
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
static inline sVec4_112A50 vu0Add_112A50(const sVec4_112A50& a, const sVec4_112A50& b)
{
    sVec4_112A50 r;
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
static inline sVec4_112A50 vu0Sub_112A50(const sVec4_112A50& a, const sVec4_112A50& b)
{
    sVec4_112A50 r;
    __asm__ __volatile__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0Dot_112A50(const sVec4_112A50& a, const sVec4_112A50& b)
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

struct sVEi_112A50 { short delta; short index; int (*fn)(void*); };
struct sVEf_112A50 { short delta; short index; float (*fn)(void*, void*); };

extern "C" void cRider_selectRoute(void* vself, int keep)
{
    char* self = (char*)vself;
    void* paths[6];
    sVec4_112A50 out;
    sVec4_112A50 pos;
    float len = vu0Length_112A50(*(sVec4_112A50*)(self + 0x1E0));
    void* best = 0;
    float bestD = 9.999999933815813e+36f;
    float bestW = -1.0f;
    if (len == 0.0f) {
        pos = *(sVec4_112A50*)(self + 0x110);
    } else {
        pos = vu0Add_112A50(*(sVec4_112A50*)(self + 0x110), vu0Scale_112A50(*(sVec4_112A50*)(self + 0x1E0), 796.0f / len));
    }
    int n = func_0026AFB8(D_004D33A0, &pos, paths, 6, 0);
    for (int i = 0; i < n; i++) {
        if (paths[i] == *(void**)(self + 0xAB8) && keep) {
            continue;
        }
        float tOut;
        float t = func_0026A428(paths[i], &pos, &out, &tOut, 1);
        if (func_0026AC48(paths[i]) - 200.0f < t) {
            continue;
        }
        sVec4_112A50 d1 = vu0Sub_112A50(pos, func_0026AB20_112A50(paths[i], 0, t + 796.0f));
        sVec4_112A50 d0 = vu0Sub_112A50(*(sVec4_112A50*)(self + 0x110), out);
        float dist = vu0Dot_112A50(d0, d0) + vu0Dot_112A50(d1, d1);
        char* o = self + 0x6C0;
        sVEi_112A50* ve = &(*(sVEi_112A50**)o)[9];
        if (ve->fn(o + ve->delta) == 1) {
            sVEf_112A50* vf = &(*(sVEf_112A50**)(self + 0x6C0))[20];
            dist = vf->fn(self + vf->delta, paths[i]);
            if (bestW < dist) {
                best = paths[i];
                bestW = dist;
                if (best == *(void**)(self + 0xAB8)) {
                    best = 0;
                }
            }
        } else {
            if (dist < bestD) {
                best = paths[i];
                bestD = dist;
                if (best == *(void**)(self + 0xAB8)) {
                    best = 0;
                }
            }
        }
    }
    if (best != 0) {
        *(void**)(self + 0xAB8) = best;
        *(int*)(*(char**)(self + 0xABC) + 0x14) = -1;
        float r = func_0026A638(*(void**)(self + 0xAB8), self + 0x110, self + 0x490, self + 0x4C8, *(void**)(self + 0xABC), 1);
        *(float*)(self + 0x4C4) = r;
        *(sVec4_112A50*)(self + 0x4A0) = func_0026AB20_112A50(*(void**)(self + 0xAB8), 0, r + 796.0f);
        *(float*)(self + 0x4C0) = *(float*)(self + 0x4C4);
    }
}

//100%
struct sVec4_112D58 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sVE_112D58 { short delta; short index; int (*fn)(void*); };

extern char D_004D33A0[];
int func_0026AF98_112D58(void* self, void* a1, void** out, int maxOut) __asm__("func_0026AF98__FPv");
extern "C" float func_0026A428(void* path, void* a1, void* a2, void* a3, int n);
extern "C" float func_0026A638(void* path, void* a1, void* a2, void* a3, void* hint, int n);
extern "C" float func_0026AC48(void* self);
sVec4_112D58 func_00269F18_112D58(void* path, float* t) __asm__("func_00269F18");

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sVec4_112D58 vu0Sub_112D58(const sVec4_112D58& a, const sVec4_112D58& b)
{
    sVec4_112D58 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0Dot_112D58(const sVec4_112D58& a, const sVec4_112D58& b)
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

extern "C" void func_00112D58(char* self)
{
    void* paths[6];
    sVec4_112D58 pos;
    int n = func_0026AF98_112D58(D_004D33A0, self + 0x110, paths, 6);
    void* best = 0;
    float bestD = 9.999999933815813e+36f;
    int i;
    for (i = 0; i < n; i++)
    {
        float tOut;
        float t = func_0026A428(paths[i], self + 0x110, &pos, &tOut, 1);
        float len = func_0026AC48(paths[i]);
        char* o = self + 0x6C0;
        sVE_112D58* ve = &(*(sVE_112D58**)o)[8];
        if (ve->fn(o + ve->delta) == 0 && len - 200.0f < t)
            continue;
        float t2 = t + 796.0f;
        sVec4_112D58 d1 = vu0Sub_112D58(*(sVec4_112D58*)(self + 0x110), func_00269F18_112D58(paths[i], &t2));
        sVec4_112D58 d0 = vu0Sub_112D58(*(sVec4_112D58*)(self + 0x110), pos);
        float dist = vu0Dot_112D58(d0, d0) + vu0Dot_112D58(d1, d1);
        if (dist < bestD)
        {
            best = paths[i];
            bestD = dist;
            if (best == *(void**)(self + 0xAB8))
                best = 0;
        }
    }
    if (*(void**)(self + 0xAB8) == 0)
        return;
    if (best)
        *(void**)(self + 0xAB8) = best;
    *(int*)(*(char**)(self + 0xABC) + 0x14) = -1;
    *(float*)(self + 0x4C4) = func_0026A638(*(void**)(self + 0xAB8), self + 0x110, self + 0x490, self + 0x4C8, *(void**)(self + 0xABC), 1);
    *(sVec4_112D58*)(self + 0x490) = func_00269F18_112D58(*(void**)(self + 0xAB8), (float*)(self + 0x4C4));
    float t3 = *(float*)(self + 0x4C4) + 796.0f;
    *(sVec4_112D58*)(self + 0x4A0) = func_00269F18_112D58(*(void**)(self + 0xAB8), &t3);
    *(float*)(self + 0x4C0) = *(float*)(self + 0x4C4);
}

INCLUDE_ASM("ai/computer", func_00112FB0);

//100%
float cRider_getRemainingDistance(void* self)
{
    return *(float*)((char*)self + 0x4D0);
}

//100%
float func_00113130(void* self)
{
    return *(float*)((char*)self + 0x4D8);
}

//100%
extern "C" void cAirPredictor_reset(char* self);

extern "C" void* cAirPredictor_cAirPredictor(void* self)
{
    *(unsigned int*)((char*)self + 0x30) = 0xFFFFFFFF;
    cAirPredictor_reset((char*)self);
    return self;
}

//100%
void operator_delete(int* ptr);

extern "C" void func_00113170(void* self, int flags)
{
    if (flags & 1)
    {
        operator_delete((int*)self);
    }
}

