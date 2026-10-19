#include "common.h"

//100%
extern "C" void func_00116FA8(void* p);
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern char D_004A1078[];

inline void* operator new[](unsigned int, void* p) { return p; }

struct sMetrixEntry_001172E0
{
    char pad_0x00[0x98];
    int index;
    sMetrixEntry_001172E0() { func_00116FA8(this); }
};

// PORT: element address built through int (pointer in int).
INCLUDE_ASM("ai/ridermetrix", cRiderMetrix_linkToRider);
extern "C" void cRiderMetrix_linkToRider(char* self, char* rider);

//100%
struct sRiderMetrixEntry_001173B8
{
    int state;
    char pad[0x98];
};

struct sRiderMetrix_001173B8
{
    char pad[0x1B0];
    sRiderMetrixEntry_001173B8* entries;
    int count;
};

extern "C" void cRiderMetrix_clearAllMsgs(sRiderMetrix_001173B8* self)
{
    if (self->entries != 0)
    {
        for (int i = 0; i < self->count; i++)
        {
            self->entries[i].state = 0x34;
        }
    }
}

//100%
struct sRiderMetrixEntry_00117400
{
    int type;
    char pad[0x98];
};

struct sRiderMetrix_00117400
{
    char pad[0x1B0];
    sRiderMetrixEntry_00117400* entries;
    int count;
    int bits[2];
    int dirty;
};

static inline bool rmBitTest00117400(int* bits, int i)
{
    int mask = 1 << i;
    return (*(int*)((char*)bits + ((i & ~0x1F) >> 3)) & mask) != 0;
}

extern "C" int cRiderMetrix_isMsgTypeShown(sRiderMetrix_00117400* self, int type)
{
    if (self->entries == 0)
        return 0;
    if (self->dirty)
    {
        for (int i = 0; i < self->count; i++)
        {
            int t = self->entries[i].type;
            if (t != 0x34)
            {
                int off = (t & ~0x1F) >> 3;
                int* b = self->bits;
                *(int*)((char*)b + off) |= 1 << t;
            }
        }
        self->dirty = 0;
    }
    return rmBitTest00117400(self->bits, type);
}

//100%
struct sVEntry001174B0 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cRiderMetrix_saveState(void* self, void* obj)
{
    sVEntry001174B0* vt = *(sVEntry001174B0**)obj;
    vt[1].fn((char*)obj + vt[1].delta, self, 0x1AC);
}

//100%
struct sVEntry001174E8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cRiderMetrix_loadState(void* self, void* obj)
{
    sVEntry001174E8* vt = *(sVEntry001174E8**)obj;
    vt[2].fn((char*)obj + vt[2].delta, self, 0x1AC);
}

//100%
extern "C" void cRiderMetrix_setStartingScore(void* self, int a1)
{
    int delta = a1 - *(int*)((char*)self + 0x1c8);
    *(int*)((char*)self + 0x1c8) = a1;
    *(int*)((char*)self + 0x198) += delta;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cRiderMetrix_resetRunStats(char* self);
extern "C" void func_003E6448(void* dst, int value, int size);
extern "C" void cRiderMetrix_resetTrick(void* self);
extern "C" void cRiderMetrix_resetCombo(void* self);

extern "C" void cRiderMetrix_resetRun(char* self)
{
    cRiderMetrix_resetRunStats(self);
    cRiderMetrix_clearAllMsgs((sRiderMetrix_001173B8*)self);
    func_003E6448(self + 0xA8, 0, 0x50);
    *(int*)(self + 0xF8) = 0;
    cRiderMetrix_resetTrick(self);
    cRiderMetrix_resetCombo(self);
    *(int*)(self + 0x1A8) = 0;
    *(float*)(self + 0xA4) = -1.0f;
    func_003E6448(self + 0x1B8, 0, 8);
    *(int*)(self + 0x1C0) = 1;
}

//100%
extern "C" void func_003E6448(void* dst, int value, int size);

extern "C" void cRiderMetrix_resetRunStats(char* self)
{
    func_003E6448(self + 0xFC, 0, 0xAC);
    *(int*)(self + 0x18C) = -1;
    *(int*)(self + 0x198) = *(int*)(self + 0x1C8);
}

//100%
extern "C" void cRiderMetrix_clearMsgType(void* self, int type);

extern "C" void cRiderMetrix_resetCombo(void* self)
{
    cRiderMetrix_clearMsgType(self, 3);
    *(int*)((char*)self + 0x9C) = 0;
    *(int*)((char*)self + 0xA0) = 0;
    *(float*)((char*)self + 0xA4) = -1.0f;
}

//100%
extern "C" void func_001171A8(void* self, int type, int value, int arg, float f);

// PORT: g++ <? (min) operator, removed in GCC 4.3.
static inline float rmClamp_117638(float v, float lo, float hi)
{
    if (v >= lo)
        return v <? hi;
    return lo;
}

static inline bool rmIsState_117638(char* p, int st)
{
    return *(int*)p == st;
}

// PORT: g++ <? (min) operator, removed in GCC 4.3.
extern "C" void cRiderMetrix_addComboTrick(void* self, int points)
{
    char* s = (char*)self;
    if (points > 0)
    {
        int n = *(int*)(s + 0x9C) + 1;
        *(int*)(s + 0x9C) = n;
        float m = ((float)n + 10.0f) * 0.05000000074505806f;
        float k = rmClamp_117638(m, 0.5f, 2.0f);
        *(float*)(s + 0xA4) = -1.0f;
        *(int*)(s + 0xA0) += (int)(points * k);
        char* r = *(char**)(s + 0x1B0);
        if (r != 0)
        {
            int v = 0;
            char* p = r + 0x1D4;
            if (!rmIsState_117638(p, 0x34))
                v = *(int*)(r + 0x1E8);
            func_001171A8(p, 3, v, n, 0.0f);
        }
    }
}

//100%
extern "C" void cRiderMetrix_suspendComboClock(void* self)
{
    *(float*)((char*)self + 0xa4) = -1.0f;
}

//100%
// PORT: g++ >? (max) operator, removed in GCC 4.3.
extern "C" void func_00117708(void* self, float seconds)
{
    *(float*)((char*)self + 0xa4) = *(float*)((char*)self + 0xa4) >? seconds;
}

//100%
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
// Same function as cRiderMetrix_postPointsMsg(self, type, value, arg, duration): the float travels in $f12 either way,
// but the original prototype lists it before arg, which decides the argument evaluation order.
extern "C" void cRiderMetrix_postPointsMsg_f(void* self, int type, int value, float duration, int arg) __asm__("cRiderMetrix_postPointsMsg");
extern "C" void func_00119EF8(void* self, int type, int value);

struct sRaceSettings_117718 {
    char pad[0x48];
    signed char mode;       // 0x48
    signed char online;     // 0x49
};
extern sRaceSettings_117718 D_00535BC8_117718 __asm__("D_00535BC8");

// Records a trick combo (count at 0x9C, score at 0xA0) in the rider metrics and awards it.
extern "C" void cRiderMetrix_payCombo(void* self_)
{
    char* self = (char*)self_;
    int n = *(int*)(self + 0x9C);
    if (n >= 2) {
        int pts = *(int*)(self + 0xA0);
        if (pts > 0) {
            *(int*)(self + 0x198) += pts;
            *(int*)(self + 0x134) += n;
            if (*(int*)(self + 0x188) < pts)
                *(int*)(self + 0x188) = pts;
            if (*(int*)(self + 0x9C) > *(int*)(self + 0x184))
                *(int*)(self + 0x184) = *(int*)(self + 0x9C);
            cBE_getInterface_Fv(cBE_getBE(), 0);
            int offline = 0;
            if (D_00535BC8_117718.mode == 4)
                offline = D_00535BC8_117718.online == 0;
            if (!offline) {
                cRiderMetrix_postPointsMsg_f(self, 0x26, *(int*)(self + 0xA0), 1.5f, *(int*)(self + 0x9C));
                cRiderMetrix_postPointsMsg_f(self, 0x18, *(int*)(self + 0xA0), 0.7f, 0);
            } else {
                int v = *(int*)(self + 0xA0) / 500;
                func_00119EF8(self, 2, v > 20 ? 20 : v);
            }
        }
    }
    cRiderMetrix_resetCombo(self);
}

//100%
extern "C" void func_003E6448(void* dst, int value, int size);

extern "C" void cRiderMetrix_resetTrick(void* p)
{
    char* self = (char*)p;
    *(int*)(self + 0x14) = 0;
    *(float*)(self + 0x18) = 1.0f;
    *(int*)(self + 0x1C) = 0;
    *(int*)(self + 0x0) = 0;
    *(int*)(self + 0x4) = 0;
    *(int*)(self + 0x8) = 0;
    *(int*)(self + 0xC) = 0;
    *(int*)(self + 0x10) = 0;
    *(int*)(self + 0x20) = 0;
    *(float*)(self + 0x24) = -1.0f;
    *(int*)(self + 0x28) = 0;
    *(float*)(self + 0x2C) = -1.0f;
    *(float*)(self + 0x30) = -1.0f;
    *(int*)(self + 0x34) = 0;
    *(int*)(self + 0x38) = 0;
    *(int*)(self + 0x3C) = 0;
    *(float*)(self + 0x40) = -1.0f;
    *(int*)(self + 0x44) = 0;
    *(int*)(self + 0x48) = 0;
    *(int*)(self + 0x4C) = 0;
    *(int*)(self + 0x50) = 0;
    *(int*)(self + 0x54) = 0;
    *(int*)(self + 0x58) = 0;
    *(int*)(self + 0x5C) = 0;
    *(int*)(self + 0x70) = 0;
    *(float*)(self + 0x6C) = -1.0f;
    *(int*)(self + 0x74) = 0;
    *(float*)(self + 0x78) = -1.0f;
    *(int*)(self + 0x7C) = 0;
    *(int*)(self + 0x80) = 0;
    *(int*)(self + 0x84) = 0;
    *(int*)(self + 0x88) = 0;
    *(int*)(self + 0x8C) = 0;
    *(int*)(self + 0x90) = 0;
    *(int*)(self + 0x94) = 0;
    *(int*)(self + 0x98) = 0;
    func_003E6448(self + 0x60, 0, 0xC);
}

//100%
float func_00117900(void* self)
{
    return *(float*)((char*)self + 0x14);
}

//100%
extern "C" int cRiderMetrix_getInvertedPoints(void* self)
{
    int v = (int)(*(float*)((char*)self + 0x1C) * 10000.0f + 5.0f);
    return v - v % 10;
}

//100%
extern "C" int cRiderMetrix_getPendingPoints(void* self)
{
    int v = (int)(*(float*)((char*)self + 0x1C4) * *(float*)((char*)self + 0x14) * 10000.0f + 5.0f);
    return v - v % 10;
}

//100%
extern "C" int cRiderMetrix_getMultipliedPoints(void* self)
{
    int v = (int)(*(float*)((char*)self + 0x1C4) * *(float*)((char*)self + 0x18) * *(float*)((char*)self + 0x14) * 10000.0f + 5.0f);
    return v - v % 10;
}

//100%
struct sMetrixSlot {
    int type;
    char pad_0x04[0x98];
};

struct sMetrixSlots {
    char pad_0x00[0x1B0];
    sMetrixSlot* slots;
    int count;
};

extern "C" void cRiderMetrix_clearMsgType(void* self_, int type)
{
    sMetrixSlots* self = (sMetrixSlots*)self_;
    if (self->slots != 0)
    {
        if (type < 0x22)
        {
            self->slots[type].type = 0x34;
        }
        else
        {
            for (int i = 0x23; i < self->count; i++)
            {
                if (self->slots[i].type == type)
                {
                    self->slots[i].type = 0x34;
                }
            }
        }
    }
}

//100%
struct sMetrixSlotR {
    int type;
    float total;
    float value;
    char pad_0x0C[0x90];
};

struct sMetrixSlotsR {
    char pad_0x00[0x1B0];
    sMetrixSlotR* slots;
    int count;
};

static inline bool slotIsFreeR(const sMetrixSlotR& s)
{
    return s.type == 0x34;
}

extern "C" int cRiderMetrix_allocMsgSlot(void* self_, int type)
{
    sMetrixSlotsR* self = (sMetrixSlotsR*)self_;
    if (type < 0x22)
    {
        return type;
    }
    float best = 1.0f;
    int bestIdx = -1;
    for (int i = 0x23; i < self->count; i++)
    {
        if (slotIsFreeR(self->slots[i]))
        {
            return i;
        }
        float r = self->slots[i].value / self->slots[i].total;
        if (r < best)
        {
            best = r;
            bestIdx = i;
        }
    }
    return bestIdx;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sMetrixSlotAE8 {
    char pad_0x00[0x9C];
};

extern "C" void func_00117048(void* slot, int a, const char* b, float c, int d);

// PORT: returns the slot index, but the unit's later declaration (used by
// cRiderMetrix_evAutoResetSurface) says void; bind the int-returning body here.
int cRiderMetrix_postTextMsg_impl(void* self, int a, const char* b, float c, int d) __asm__("cRiderMetrix_postTextMsg");

int cRiderMetrix_postTextMsg_impl(void* self, int a, const char* b, float c, int d)
{
    if (*(sMetrixSlotAE8**)((char*)self + 0x1B0) == 0)
        return -1;
    int idx = cRiderMetrix_allocMsgSlot(self, a);
    func_00117048(&(*(sMetrixSlotAE8**)((char*)self + 0x1B0))[idx], a, b, c, d);
    return idx;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sMetrixSlotB88 {
    char pad_0x00[0x9C];
};

extern "C" void func_001170A8(void* slot, int type, int value, float duration, int arg);

// PORT: returns the slot index, but the unit's later declarations say void;
// bind the int-returning body here.
int cRiderMetrix_postPointsMsg_impl(void* self, int type, int value, int arg, float duration) __asm__("cRiderMetrix_postPointsMsg");

int cRiderMetrix_postPointsMsg_impl(void* self, int type, int value, int arg, float duration)
{
    if (*(sMetrixSlotB88**)((char*)self + 0x1B0) == 0)
        return -1;
    int idx = cRiderMetrix_allocMsgSlot(self, type);
    func_001170A8(&(*(sMetrixSlotB88**)((char*)self + 0x1B0))[idx], type, value, duration, arg);
    return idx;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cRiderMetrix_payCombo(void*);
extern "C" void* func_0028B180();
struct sGradeStep_119210;
extern "C" int cRiderMetrix_checkDurationBonus(void* self, int* idx, sGradeStep_119210* tbl, int type, float x);
extern "C" void func_00116FB8(void* slot);
extern "C" void cRiderMetrix_updateHud(void* self);
extern "C" void func_00290F58(void* audio, void* rider, float mult);
extern "C" void* func_00416210(void* dst, int c, int n);
int cRider_getMotionMode(void* rider);
int cRider_getControlState(void* rider);

extern sGradeStep_119210 D_00459E00[];
extern sGradeStep_119210 D_00459E20[];
extern sGradeStep_119210 D_00459F68[];
extern sGradeStep_119210 D_00459E40[];
extern sGradeStep_119210 D_00459F08[];

struct sVec17C28 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sRider17C28 {
    char pad_0x000[0x1C0];
    sVec17C28 up;        // 0x1C0
    char pad_0x1D0[0x10];
    sVec17C28 vel;       // 0x1E0
    char pad_0x1F0[0x110];
    float timeScale;     // 0x300
};

struct sMetrixSlot17C28 {
    char pad_0x00[0x9C];
};

struct sMetrix17C28 {
    char pad_0x00[0x14];
    float mult;          // 0x14
    char pad_0x18[0x4];
    float f1C;           // 0x1C
    char pad_0x20[0x4];
    float airTime;       // 0x24
    char pad_0x28[0x4];
    float t2C;           // 0x2C
    float t30;           // 0x30
    char pad_0x34[0x8];
    float add3C;         // 0x3C
    float t40;           // 0x40
    char pad_0x44[0x28];
    float t6C;           // 0x6C
    char pad_0x70[0x8];
    float t78;           // 0x78
    char pad_0x7C[0x8];
    int points;          // 0x84
    int idx88;           // 0x88
    int idx8C;           // 0x8C
    int idx90;           // 0x90
    int idx94;           // 0x94
    int idx98;           // 0x98
    char pad_0x9C[0x8];
    float tA4;           // 0xA4
    char pad_0xA8[0xB4];
    float maxSpeed;      // 0x15C
    float maxAvg;        // 0x160
    float speedSum;      // 0x164
    float frames;        // 0x168
    char pad_0x16C[0x3C];
    float avgSpeed;      // 0x1A8
    sRider17C28* rider;  // 0x1AC
    sMetrixSlot17C28* slots; // 0x1B0
    int count;           // 0x1B4
    char clear[8];       // 0x1B8
    int dirty;           // 0x1C0
};

// PORT: PS2-only VU0 inline asm (vector length).
static inline float len17C28(const sVec17C28& v)
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

extern "C" void cRiderMetrix_update(sMetrix17C28* self)
{
    float dt = self->rider->timeScale * 0.016666668f;
    float speed = len17C28(self->rider->vel);
    if (self->tA4 >= 0.0f) {
        if (cRider_getMotionMode(self->rider) == 0 && cRider_getControlState(self->rider) != 1) {
            self->tA4 = self->tA4 - dt;
            if (self->tA4 <= 0.0f) {
                cRiderMetrix_payCombo(self);
            }
        }
    }
    if (self->t30 >= 0.0f) {
        self->t30 += dt;
        self->points += cRiderMetrix_checkDurationBonus(self, &self->idx88, D_00459E00, 0x1C, self->t30);
    }
    if (self->t40 >= 0.0f) {
        self->t40 += dt;
        self->mult += self->add3C;
        self->points += cRiderMetrix_checkDurationBonus(self, &self->idx8C, D_00459E20, 0x20, self->t40);
    }
    if (self->airTime >= 0.0f) {
        float d = speed * dt;
        self->airTime += d;
        self->mult += d * 5e-05f;
        sVec17C28 up = self->rider->up;
        if (up.z < 0.0f) {
            self->f1C += d * 0.0002f;
        }
        self->points += cRiderMetrix_checkDurationBonus(self, &self->idx98, D_00459F68, 0x1D, self->airTime);
    }
    if (self->t2C >= 0.0f) {
        self->t2C += dt;
        self->mult += dt * 0.01f;
        self->points += cRiderMetrix_checkDurationBonus(self, &self->idx90, D_00459E40, 0x1E, self->t2C);
    }
    if (self->t6C >= 0.0f) {
        self->t6C += dt;
        self->mult += dt * 0.04999999701976776f;
    }
    if (self->t78 >= 0.0f) {
        self->t78 += dt;
        self->mult += dt * 0.04999999701976776f;
        self->points += cRiderMetrix_checkDurationBonus(self, &self->idx94, D_00459F08, 0x1F, self->t78);
    }
    self->avgSpeed = self->avgSpeed * 0.9f + speed * 0.1f;
    self->speedSum += speed;
    self->frames += 1.0f;
    if (self->maxAvg < self->avgSpeed) {
        self->maxAvg = self->avgSpeed;
    }
    if (self->maxSpeed < speed) {
        self->maxSpeed = speed;
    }
    cRiderMetrix_updateHud(self);
    if (self->slots != 0) {
        for (int i = 0; i < self->count; i++) {
            func_00116FB8(&self->slots[i]);
        }
    }
    func_00416210(self->clear, 0, 8);
    self->dirty = 1;
    func_00290F58(func_0028B180(), self->rider, self->mult);
}

INCLUDE_ASM("ai/ridermetrix", cRiderMetrix_updateHud);

//100%
struct sTrickId;
extern "C" void gGenTrickName(char* buf, sTrickId* id, int size);
extern "C" void cRiderMetrix_postTextMsg(void* self, int a, const char* b, float c, int d);
extern "C" void func_00309918(void* self, void* d);
extern void* D_004A3DD8;

extern "C" void cRiderMetrix_showTrickName(void* self, sTrickId* id, int repeat)
{
    char buf[0x100];
    gGenTrickName(buf, id, 0xFF);
    cRiderMetrix_postTextMsg(self, 0, buf, 3.0f, repeat);
    func_00309918(D_004A3DD8, id);
}

//100%
struct sMetrixRecent {
    char pad_0x00[0x60];
    int recent[3];
};

extern "C" void cRiderMetrix_addGrab(void* self_, int value)
{
    sMetrixRecent* self = (sMetrixRecent*)self_;
    for (int i = 0; i < 3; i++)
    {
        if (self->recent[i] == 0)
        {
            self->recent[i] = value;
            break;
        }
        if (self->recent[i] == value && i < 2 && self->recent[i + 1] == 0)
        {
            self->recent[i] = value;
            return;
        }
    }
}

//100%
struct sTrickId;

struct sTrickId190F0 {
    int w0;
    int w1;
};

struct sTrickHist190F0 {
    char pad0[0x8];
    int u8;                       // 0x8
    char padC[0x20 - 0xC];
    int u20;                      // 0x20
    int u24;
    int u28;                      // 0x28
    char pad2C[0x70 - 0x2C];
    int u70;                      // 0x70
    char pad74[0x7C - 0x74];
    int u7C;                      // 0x7C
    char pad80[0xA8 - 0x80];
    sTrickId190F0 hist[10];       // 0xA8
    int histIdx;                  // 0xF8
};

static inline int func_trickIdEqual(const void* a, const void* b, int size)
{
    const unsigned char* p = (const unsigned char*)a;
    const unsigned char* q = (const unsigned char*)b;
    while (size--) {
        if (*p != *q) {
            return 0;
        }
        p++;
        q++;
    }
    return 1;
}

// sTrickId is defined later in the unit, hence the casts. Don't copy id_ into a typed
// local: a separate local shifts every register by one.
extern "C" int cRiderMetrix_updateRepeatHistory(void* self_, sTrickId* id_)
{
    sTrickHist190F0* self = (sTrickHist190F0*)self_;
    int count;

    if (self->u8 != 0 || self->u20 != 0 || self->u70 != 0 || self->u7C != 0 || self->u28 != 0) {
        return 0;
    }
    count = 0;
    if ((((sTrickId190F0*)id_)->w1 & 0x3F800) != 0x800 && (((sTrickId190F0*)id_)->w0 & 0xFC00000) != 0x400000) {
        for (int i = 0; i < 10; i++) {
            if (func_trickIdEqual(id_, &self->hist[i], 8)) {
                count++;
            }
        }
    }
    self->hist[self->histIdx] = *(sTrickId190F0*)id_;
    self->histIdx++;
    self->histIdx %= 10;
    return count;
}

//100%
extern "C" void cRiderMetrix_clearMsgType(void* self, int type);
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);

struct sGradeStep_119210
{
    float threshold;
    float mult;
};

extern "C" int cRiderMetrix_checkDurationBonus(void* self, int* idx, sGradeStep_119210* tbl, int type, float x)
{
    // PORT: pointer arithmetic through int.
    sGradeStep_119210* e = (sGradeStep_119210*)(*idx * 8 + (int)tbl);
    float t = e->threshold;
    if (t < 0.0f) return 0;
    if (t <= x)
    {
        float m = *(float*)((char*)self + 0x1C4);
        int v = (int)(e->mult * m + 0.5f);
        *idx = *idx + 1;
        cRiderMetrix_clearMsgType(self, 0x1C);
        cRiderMetrix_clearMsgType(self, 0x1D);
        cRiderMetrix_clearMsgType(self, 0x1E);
        cRiderMetrix_clearMsgType(self, 0x1F);
        cRiderMetrix_clearMsgType(self, 0x20);
        cRiderMetrix_postPointsMsg(self, type, v, (int)t, 1.5f);
        return v;
    }
    return 0;
}

//100%
extern "C" int func_00119310(void* self, int points)
{
    if (points < 1000)
    {
        return 0;
    }
    if (points < 2500)
    {
        return 1;
    }
    if (points < 4000)
    {
        return 2;
    }
    if (points < 7500)
    {
        return 3;
    }
    if (points < 11500)
    {
        return 4;
    }
    return 5;
}

//100%
extern "C" int cRiderMetrix_dropPendingPoints(void* self);

extern "C" float cRiderMetrix_onReset(void* self, int a1)
{
    *(int*)((char*)self + 0x1A4) += cRiderMetrix_dropPendingPoints(self);
    cRiderMetrix_resetTrick(self);
    cRiderMetrix_resetCombo(self);
    *(int*)((char*)self + 0x120) += 1;
    if (!a1)
        return *(float*)(*(char**)((char*)self + 0x1AC) + 0x2F8) * -0.10000000149011612f;
    return *(float*)(*(char**)((char*)self + 0x1AC) + 0x2F8) * -0.699999988079071f;
}

extern "C" void cRiderMetrix_payCombo(void*);

//99.38% - identical instructions; jal addend differs only because the
// callee sits at a different .text offset in our object than in the target
extern "C" float func_001193E0(void* self)
{
    cRiderMetrix_payCombo(self);
    return 0.0f;
}

//100%
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);

extern "C" float cRiderMetrix_onKnockout(char* self)
{
    *(int*)(self + 0x128) += 1;
    cRiderMetrix_postPointsMsg(self, 0x2C, 0, 0, 1.5f);
    return 1.0f;
}

//100%
extern "C" void func_001171A8(void* self, int type, int value, int arg, float f);

extern "C" float cRiderMetrix_onMultiplierPickup(char* self, float value)
{
    *(int*)(self + 0x130) += 1;
    char* p = *(char**)(self + 0x1B0);
    if (p != 0)
    {
        if (*(float*)(self + 0x18) < value)
        {
            func_001171A8(p + 0x270, 4, (int)value, 0, 0.0f);
            *(float*)(self + 0x18) = value;
        }
    }
    return 0.0f;
}

//100%
extern void* D_004A28A8;
extern "C" void* func_0028B180();
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);
extern "C" int func_00238510(void* mgr, int id, int a2);
extern "C" void func_002A3CE8(void* snd, void* rider, int a2);

struct sVEntry001194C0 { short delta; short index; int (*fn)(void*); };

static inline bool rmRiderFlags_1194C0(char* r)
{
    return *(int*)(r + 0x874) != 0 && *(int*)(r + 0x87C) != 0;
}

extern "C" float func_001194C0(char* self, int a1)
{
    char* sub = *(char**)(self + 0x1AC) + 0x6C0;
    sVEntry001194C0* vt = *(sVEntry001194C0**)sub;
    if (vt[8].fn(sub + vt[8].delta) != 0)
    {
        void* mgr = *(void**)((char*)D_004A28A8 + 0xC0);
        char* sub2 = *(char**)(self + 0x1AC) + 0x6C0;
        sVEntry001194C0* vt2 = *(sVEntry001194C0**)sub2;
        if (func_00238510(mgr, vt2[7].fn(sub2 + vt2[7].delta), a1) != 0)
        {
            cRiderMetrix_postPointsMsg(self, 0x29, a1, 0, 2.5f);
            if (rmRiderFlags_1194C0(*(char**)(self + 0x1AC)))
            {
                func_002A3CE8(func_0028B180(), *(void**)(self + 0x1AC), 1);
            }
        }
    }
    return 0.0f;
}

//100%
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);

extern "C" float func_001195A8(void* self, int value)
{
    cRiderMetrix_postPointsMsg(self, 0x2A, value, 0, 5.0f);
    return 0.0f;
}

//100%
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);

extern "C" float func_001195D8(void* self, int value)
{
    cRiderMetrix_postPointsMsg(self, 0x2B, value, 0, 5.0f);
    return 0.0f;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv really takes (be, kind); bind the 2-arg form to that symbol.
void* cBE_getInterface(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);
extern "C" void func_00119EF8(void* self, int kind, int amount);

// View of sGameSettings (defined later in this unit); bound to the same symbol by asm label.
struct sGameSettings_119608 {
    char pad_0x00[0x48];
    signed char eventKind; // 0x48: 4 = free ride
    signed char gameType;  // 0x49: 0 = Conquer the Mountain
};
extern sGameSettings_119608 D_00535BC8_119608 __asm__("D_00535BC8");

extern "C" float cRiderMetrix_onPointPickup(void* self, int pts)
{
    int v = (int)(pts * *(float*)((char*)self + 0x1C4) + 0.5f);
    cBE_getInterface(cBE_getBE(), 0);
    int career = D_00535BC8_119608.eventKind == 4 && D_00535BC8_119608.gameType == 0;
    if (!career)
    {
        cRiderMetrix_postPointsMsg(self, 0x23, v, 0, 2.5f);
        cRiderMetrix_postPointsMsg(self, 0x18, v, 0, 0.699999988079071f);
    }
    else
    {
        int amount = v / 500;
        if (amount > 20)
        {
            amount = 20;
        }
        func_00119EF8(self, 1, amount);
    }
    *(int*)((char*)self + 0x198) += v;
    return 0.0f;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int func_00150528(void* iface, int id);
int func_00150540(void* iface, int id);

extern "C" float cRiderMetrix_beginGrab(char* self, int id)
{
    float zero = 0.0f;
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 6);
    float a = func_00150528(iface, id) * 9.999999747378752e-05f;
    float b = func_00150540(iface, id) * 1.6666666624587378e-06f;
    *(float*)(self + 0x14) += a;
    *(float*)(self + 0x3C) = b;
    if (*(float*)(self + 0x40) < zero)
    {
        *(float*)(self + 0x40) = zero;
    }
    if (id >= 0x23)
    {
        *(int*)(self + 0x5C) = 1;
    }
    cRiderMetrix_suspendComboClock(self);
    return zero;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cRiderMetrix_addGrab(void* self_, int value);

// PORT: g++ >? (max) operator.
extern "C" float cRiderMetrix_endGrab(void* p, int v)
{
    char* self = (char*)p;
    cRiderMetrix_addGrab(self, v);
    if (v >= 0x23)
    {
        (*(int*)(self + 0x54))++;
        if (*(int*)(*(char**)(self + 0x1AC) + 0x2F4) >= 6)
            (*(int*)(self + 0x58))++;
    }
    else if (v >= 0x13)
    {
        (*(int*)(self + 0x50))++;
    }
    else
    {
        (*(int*)(self + 0x4C))++;
    }
    float t = *(float*)(self + 0x40);
    *(float*)(self + 0x48) = t >? *(float*)(self + 0x48);
    *(int*)(self + 0x5C) = 0;
    *(float*)(self + 0x40) = -1.0f;
    *(float*)(self + 0x44) += t;
    return 0.0f;
}

//100%
// PORT: PS2-only inline asm (float absolute value).
static inline float metrixAbs_00119898(float x)
{
    float r;
    __asm__("abs.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

// PORT: g++ `>?` (max) operator. Prototype mismatch: the unit declares
// `void* cRiderMetrix_setSpinScore(void*)` for an existing caller, but the body takes a float in $f12.
float cRiderMetrix_setSpinScore_impl(void* self, float x) __asm__("cRiderMetrix_setSpinScore");

float cRiderMetrix_setSpinScore_impl(void* self, float x)
{
    *(float*)((char*)self + 0x14) -= metrixAbs_00119898(*(float*)((char*)self + 0x34)) * 0.015915492549538612f;
    *(float*)((char*)self + 0x34) = x;
    *(float*)((char*)self + 0x14) += metrixAbs_00119898(x) * 0.015915492549538612f;
    *(float*)((char*)self + 0x14) = *(float*)((char*)self + 0x14) >? 0.0f;
    return 0.0f;
}

//100%
// PORT: PS2-only inline asm (float absolute value).
static inline float metrixAbs_001198D8(float x)
{
    float r;
    __asm__("abs.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

// PORT: g++ `>?` (max) operator.
extern "C" float cRiderMetrix_setFlipScore(void* self, float x)
{
    *(float*)((char*)self + 0x14) -= metrixAbs_001198D8(*(float*)((char*)self + 0x38)) * 0.028647884726524353f;
    *(float*)((char*)self + 0x38) = x;
    *(float*)((char*)self + 0x14) += metrixAbs_001198D8(x) * 0.028647884726524353f;
    *(float*)((char*)self + 0x14) = *(float*)((char*)self + 0x14) >? 0.0f;
    return 0.0f;
}

extern "C" void* cRiderMetrix_setSpinScore(void*);

//99.29%
void* func_00119918(void* self, int a1)
{
    *(int*)((char*)self + 0x20) = a1;
    return cRiderMetrix_setSpinScore(self);
}

//100%
float func_00119938(void* self, int a1, int a2)
{
    *(float*)((char*)self + 0x6c) = 0.0f;
    *(int*)((char*)self + 0xc) = a2;
    *(int*)((char*)self + 0x20) = a2;
    *(int*)((char*)self + 0x70) = a1;
    *(int*)((char*)self + 0x5c) = 1;
    return *(float*)((char*)self + 0x6c);
}

//100%
extern "C" float cRiderMetrix_commitTrick(void* self, int stance, int alternate, int style, int flag, int takeoff);

extern "C" float func_00119958(void* self, int v)
{
    float s24 = *(float*)((char*)self + 0x24);
    float s30 = *(float*)((char*)self + 0x30);
    (*(int*)((char*)self + 0x54))++;
    (*(int*)((char*)self + 0x74))++;
    float r = cRiderMetrix_commitTrick(self, 0, 0, 0, 0, 0);
    cRiderMetrix_resetTrick(self);
    *(int*)((char*)self + 0xC) = v;
    *(int*)((char*)self + 0x20) = v;
    *(float*)((char*)self + 0x24) = s24;
    *(float*)((char*)self + 0x30) = s30;
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: g++ >?/<? (min/max) operator, removed in GCC 4.3.
extern "C" float func_001199F8(char* self, int v)
{
    *(int*)(self + 0x10) = v;
    *(int*)(self + 0x28) = v;
    *(float*)(self + 0x2C) = *(float*)(self + 0x2C) >? 0.0f;
    cRiderMetrix_suspendComboClock(self);
    return 0.0f;
}

//100%
extern "C" float cRiderMetrix_commitTrick(void* self, int stance, int alternate, int style, int flag, int takeoff);

extern "C" float func_00119A38(void* self)
{
    float s24 = *(float*)((char*)self + 0x24);
    float s30 = *(float*)((char*)self + 0x30);
    int v = *(int*)((char*)self + 0x20);
    float r = cRiderMetrix_commitTrick(self, 0, 0, v, 0, s30 >= 0.0f);
    cRiderMetrix_resetTrick(self);
    *(int*)((char*)self + 0xC) = v;
    *(int*)((char*)self + 0x20) = v;
    *(float*)((char*)self + 0x24) = s24;
    *(float*)((char*)self + 0x30) = s30;
    return r;
}

//100%
// PORT: prototype mismatch (see cRiderMetrix_setSpinScore).
float cRiderMetrix_setSpinScore_impl(void* self, float x) __asm__("cRiderMetrix_setSpinScore");

extern "C" float func_00119AD8(void* self, int a1)
{
    *(int*)((char*)self + 0x28) = a1;
    return cRiderMetrix_setSpinScore_impl(self, *(float*)((char*)self + 0x34) + 3.1415927410125732f);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cRiderMetrix_dropPendingPoints(void* self);
extern "C" int cRiderMetrix_getPendingPoints(void* self);

extern "C" float cRiderMetrix_onBail(void* self, int flag)
{
    if (flag)
    {
        (*(int*)((char*)self + 0x12C))++;
        cRiderMetrix_postPointsMsg(self, 0x2D, 0, 0, 1.5f);
    }
    else
    {
        (*(int*)((char*)self + 0x124))++;
    }
    float r = 0.0f;
    *(int*)((char*)self + 0x1A0) += cRiderMetrix_dropPendingPoints(self);
    if (cRiderMetrix_getPendingPoints(self) > 0)
        r = -0.25f;
    cRiderMetrix_resetTrick(self);
    cRiderMetrix_resetCombo(self);
    return r;
}

//100%
extern "C" float cRiderMetrix_onQuickRecover(void* self, int a1)
{
    float r;
    if (a1)
    {
        cRiderMetrix_postPointsMsg(self, 0x21, 0, 0, 1.5f);
        r = 0.10000000149011612f;
    }
    else
        r = 0.0f;
    return r;
}

//100%
extern "C" float func_00119BF0(void* self, int a1)
{
    *(int*)((char*)self + 0x7C) = a1;
    *(float*)((char*)self + 0x30) = -1.0f;
    *(int*)((char*)self + 0x78) = 0;
    *(float*)((char*)self + 0x14) += 0.04999999701976776f;
    cRiderMetrix_suspendComboClock(self);
    return 0.0f;
}

//100%
extern "C" float cRiderMetrix_commitTrick(void* self, int stance, int alternate, int style, int flag, int takeoff);
extern "C" void cRiderMetrix_resetTrick(void* self);

extern "C" float func_00119C38(void* self)
{
    *(int*)((char*)self + 0x80) += 1;
    float r = cRiderMetrix_commitTrick(self, 0, 0, 0, 0, 1);
    cRiderMetrix_resetTrick(self);
    *(int*)((char*)self + 0x30) = 0;
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_0011A168(void* self, int a, int b, int c, int d);

extern "C" float func_00119C98(void* self, int v)
{
    func_0011A168(self, 0, 0, 0, 0);
    float r = 0.0f;
    if (*(float*)((char*)self + 0x14) > r)
    {
        *(int*)((char*)self + 0x0) = v;
        *(float*)((char*)self + 0x34) = r;
        *(float*)((char*)self + 0x38) = r;
        *(int*)((char*)self + 0x4) = 0;
        *(int*)((char*)self + 0xC) = 0;
        *(int*)((char*)self + 0x10) = 0;
        *(float*)((char*)self + 0x40) = -1.0f;
        *(int*)((char*)self + 0x8) = 1;
        func_003E6448((char*)self + 0x60, 0, 0xC);
    }
    cRiderMetrix_suspendComboClock(self);
    return r;
}

//100%
extern "C" void cRiderMetrix_resetTrick(void* self);
extern "C" float cRiderMetrix_commitTrick(void* self, int stance, int alternate, int style, int flag, int takeoff);

extern "C" float cRiderMetrix_onLand(void* self, int stance, int alternate, int style, int flag)
{
    if (style != 0 && *(float*)((char*)self + 0x14) > 0.0f)
    {
        *(float*)((char*)self + 0x14) += 0.12999999523162842f;
    }
    int saved = *(int*)((char*)self + 0x70);
    float r = cRiderMetrix_commitTrick(self, stance, alternate, style, flag, 0);
    cRiderMetrix_resetTrick(self);
    *(int*)((char*)self + 0x0) = stance;
    *(int*)((char*)self + 0x4) = alternate;
    *(int*)((char*)self + 0xC) = style;
    *(int*)((char*)self + 0x10) = flag;
    if (style != 0)
    {
        *(int*)((char*)self + 0x20) = style;
        *(int*)((char*)self + 0x24) = 0;
    }
    if (flag != 0)
    {
        *(int*)((char*)self + 0x28) = flag;
        *(int*)((char*)self + 0x2C) = 0;
    }
    if (saved != 0)
    {
        *(int*)((char*)self + 0x70) = saved;
        *(int*)((char*)self + 0x5C) = 1;
        *(int*)((char*)self + 0x6C) = 0;
    }
    return r;
}

//100%
extern "C" float cRiderMetrix_commitTrick(void* self, int stance, int alternate, int style, int flag, int takeoff);

extern "C" float cRiderMetrix_onTakeoff(void* self, int a, int b)
{
    float r = 0.0f;
    int v20 = *(int*)((char*)self + 0x20);
    int v28 = *(int*)((char*)self + 0x28);
    if (*(int*)((char*)self + 0x70))
    {
        *(float*)((char*)self + 0x34) = r;
        *(float*)((char*)self + 0x24) = -1.0f;
        *(int*)((char*)self + 0x20) = 0;
    }
    else
    {
        r = cRiderMetrix_commitTrick(self, 0, 0, 0, 0, 1);
        cRiderMetrix_resetTrick(self);
    }
    *(int*)((char*)self + 0xC) = v20;
    *(int*)((char*)self + 0x10) = v28;
    *(int*)((char*)self + 0x4) = b;
    *(int*)((char*)self + 0x0) = a;
    *(int*)((char*)self + 0x30) = 0;
    return r;
}

//100%
extern "C" void func_001E3760(int rider, int amt);
extern "C" void func_001597B0(void* self, int rider, int c);

class cRiderPart_9EF8 {
public:
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual int v07();
};

extern "C" float func_00119EF8_def(char* self, int kind, int amount) __asm__("func_00119EF8");
extern "C" int cRiderMetrix_postPointsMsg_9EF8(void* self, int type, int value, int arg, float duration) __asm__("cRiderMetrix_postPointsMsg");
extern "C" float func_00119EF8_def(char* self, int kind, int amount)
{
    if (amount == 0) {
        return 0.0f;
    }
    int* lvl = *(int**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28);
    int l = *lvl;
    int locked = 0;
    if (l != 0 && l < 10) {
        locked = 1;
    }
    if (locked) {
        return 0.0f;
    }
    void* iface = cBE_getInterface(cBE_getBE(), 0xD);
    func_001E3760(((cRiderPart_9EF8*)(*(char**)(self + 0x1AC) + 0x6C0))->v07(), amount);
    func_001597B0(iface, ((cRiderPart_9EF8*)(*(char**)(self + 0x1AC) + 0x6C0))->v07(), amount);
    cRiderMetrix_postPointsMsg_9EF8(self, 0x18, amount, 0, 0.699999988079071f);
    switch (kind) {
    case 3:
        cRiderMetrix_postPointsMsg(self, 0x31, amount, amount, 1.5f);
        break;
    case 1:
        cRiderMetrix_postPointsMsg(self, 0x2E, amount, 0, 2.5f);
        break;
    case 0:
        cRiderMetrix_postPointsMsg(self, 0x2F, amount, 0, 2.5f);
        break;
    case 2:
        cRiderMetrix_postPointsMsg(self, 0x30, amount, *(int*)(self + 0x9C), 2.5f);
        break;
    case 4:
        break;
    }
    return 0.0f;
}

extern "C" void cRiderMetrix_postTextMsg(void* self, int a, const char* b, float c, int d);
extern const char D_00457888[];

//100%
float cRiderMetrix_evAutoResetSurface(void* self)
{
    cRiderMetrix_postTextMsg(self, 0x33, D_00457888, 1.5f, 0);
    return 0.0f;
}

//100%
float func_0011A0C0(void* self)
{
    return 0.0f;
}

extern "C" float func_0011A0D0()
{
    return 0.0f;
}

//100%
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);

extern "C" float func_0011A0E0(void* self)
{
    cRiderMetrix_postPointsMsg(self, 0x1A, 0, 0, 1.0f);
    return 0.0f;
}

//100%
extern "C" void func_00119EF8(void* self, int kind, int amount);
extern "C" float func_0011A110(void* self, int amount)
{
    cRiderMetrix_postPointsMsg(self, 0x1B, amount, 0, 1.5f);
    func_00119EF8(self, 4, amount);
    return 0.0f;
}

//100%
struct sTrickId;
extern "C" int cRiderMetrix_buildTrickId(void* self, sTrickId* id, int stance, int alternate, int style, int flag);
extern "C" int func_0011B1A8(void* self, sTrickId* id);
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);
extern "C" void* func_0028B180();
extern "C" void func_0029B7E0(void* audio, int rider);
extern "C" int cRiderMetrix_updateRepeatHistory(void* self, sTrickId* id);
extern "C" void cRiderMetrix_showTrickName(void* self, sTrickId* id, int repeat);

// Same layout as sTrickId, which the unit defines after this function.
struct sTrickIdA168 {
    int w0;
    int w1;
};

extern "C" void func_0011A168(void* self, int stance, int alternate, int style, int flag)
{
    sTrickIdA168 idv;
    sTrickId* id = (sTrickId*)&idv;
    if (cRiderMetrix_buildTrickId(self, id, stance, alternate, style, flag) != 0)
    {
        int pts = func_0011B1A8(self, id);
        if (pts > 0)
        {
            *(float*)((char*)self + 0x14) += pts * 9.999999747378752e-05f;
            cRiderMetrix_postPointsMsg(self, 0x32, pts, 0, 1.5f);
            func_0029B7E0(func_0028B180(), *(int*)((char*)self + 0x1AC));
        }
        cRiderMetrix_showTrickName(self, id, cRiderMetrix_updateRepeatHistory(self, id) > 0);
    }
}

// 8-byte packed trick identity built by cRiderMetrix_buildTrickId
struct sTrickId {
    int w0;
    int w1;
};

struct sGameSettings {
    char pad_0x00[0x48];
    signed char eventKind; // 0x48: 4 = free ride
    signed char gameType;  // 0x49: 0 = Conquer the Mountain
};

struct sScoreGrades {
    char pad_0x00[0x16c];
    int gradeCounts[6]; // 0x16c: landed tricks per grade (func_00119310)
};

extern void* D_004A28A8;
extern sGameSettings D_00535BC8;

extern "C" void cRiderMetrix_clearMsgType(void* self, int type);
extern "C" int cAI_haveAllPlayersFinished(void* race);
extern "C" int cRiderMetrix_buildTrickId(void* self, sTrickId* id, int stance, int alternate, int style, int flag);
extern "C" int cRiderMetrix_getPendingPoints(void* self);
extern "C" int func_0011B1A8(void* self, sTrickId* id);
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);
extern "C" void* func_0028B180();
extern "C" void func_0029B7E0(void* audio, int rider);
extern "C" int cRiderMetrix_updateRepeatHistory(void* self, sTrickId* id);
extern "C" void cRiderMetrix_showTrickName(void* self, sTrickId* id, int repeat);
extern "C" int cRiderMetrix_getMultipliedPoints(void* self);
extern "C" int func_00119310(void* self, int points);
extern "C" int cRiderMetrix_getInvertedPoints(void* self);
extern "C" void cRiderMetrix_addComboTrick(void* self, int points);
extern "C" void func_0029B430(void* audio, int rider, int ubers, int runUbers);
extern "C" void func_00119EF8(void* self, int kind, int amount);
extern "C" void func_00117708(void* self, float seconds);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv really takes (be, kind); bind the 2-arg form to that symbol.
void* cBE_getInterface(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int abs(int);

// g++ max operator: the target uses max.s, which only `>?` produces
#define MAX(a, b) ((a) >? (b))

// Rounds whole degrees to the nearest multiple of 180.
static inline int func_roundDegrees(int deg)
{
    int r = deg % 180;
    if (r < -90) {
        return deg - r - 180;
    }
    if (r > 90) {
        return deg - r + 180;
    }
    return deg - r;
}

// Trick landing commit: names and scores the trick that just ended, updates
// the run statistics and the combo, and returns the meter delta.
//100%
extern "C" float cRiderMetrix_commitTrick(void* self, int stance, int alternate, int style, int flag, int takeoff)
{
    sTrickId id;
    float delta;
    int valid;
    int repeats;
    int divisor;
    int pending;
    int grade;
    int inverted;
    int points;
    int total;
    int spin;
    int flip;
    int career;

    cRiderMetrix_clearMsgType(self, 1);
    cRiderMetrix_clearMsgType(self, 2);
    cRiderMetrix_clearMsgType(self, 4);
    cRiderMetrix_clearMsgType(self, 0x1c);
    cRiderMetrix_clearMsgType(self, 0x1d);
    cRiderMetrix_clearMsgType(self, 0x1e);
    cRiderMetrix_clearMsgType(self, 0x1f);
    cRiderMetrix_clearMsgType(self, 0x20);

    if (cAI_haveAllPlayersFinished(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xc))) {
        return 0.0f;
    }

    valid = cRiderMetrix_buildTrickId(self, &id, stance, alternate, style, flag);
    delta = 0.0f;
    if (cRiderMetrix_getPendingPoints(self) > 0) {
        repeats = 0;
        if (valid) {
            int bonus = func_0011B1A8(self, &id);
            if (bonus > 0) {
                *(float*)((char*)self + 0x14) += (float)bonus * 0.0001f;
                cRiderMetrix_postPointsMsg(self, 0x32, bonus, 0, 1.5f);
                func_0029B7E0(func_0028B180(), *(int*)((char*)self + 0x1ac));
            }
            repeats = cRiderMetrix_updateRepeatHistory(self, &id);
            cRiderMetrix_showTrickName(self, &id, repeats > 0);
        }
        divisor = repeats + 1;
        pending = cRiderMetrix_getPendingPoints(self);
        points = cRiderMetrix_getMultipliedPoints(self);
        grade = func_00119310(self, pending);
        inverted = cRiderMetrix_getInvertedPoints(self);
        cRiderMetrix_addComboTrick(self, pending / divisor);
        delta = func_00117900(self) / (float)divisor;

        points /= divisor;
        points -= points % 10;
        *(int*)((char*)self + 0x198) += points + inverted;
        *(int*)((char*)self + 0x19c) += inverted;
        *(int*)((char*)self + 0x110) += 1;
        ((sScoreGrades*)self)->gradeCounts[grade]++;

        if (*(int*)((char*)self + 0x18c) < pending) {
            *(int*)((char*)self + 0x18c) = pending;
            *(sTrickId*)((char*)self + 0x190) = id;
        }

        spin = func_roundDegrees((int)(*(float*)((char*)self + 0x34) * 57.295776f));
        flip = func_roundDegrees((int)(*(float*)((char*)self + 0x38) * 57.295776f));
        *(int*)((char*)self + 0xfc) += abs(spin);
        *(int*)((char*)self + 0x100) += abs(flip);
        *(float*)((char*)self + 0x144) += *(float*)((char*)self + 0x44);
        *(int*)((char*)self + 0x104) += *(int*)((char*)self + 0x4c);
        *(int*)((char*)self + 0x108) += *(int*)((char*)self + 0x80);

        if (*(int*)((char*)self + 0x54) > 0) {
            func_0029B430(func_0028B180(), *(int*)((char*)self + 0x1ac), *(int*)((char*)self + 0x54),
                          *(int*)((char*)self + 0x114));
        }

        *(int*)((char*)self + 0x114) += *(int*)((char*)self + 0x54);
        *(int*)((char*)self + 0x118) += *(int*)((char*)self + 0x58);
        *(int*)((char*)self + 0x11c) += *(int*)((char*)self + 0x74);
        *(float*)((char*)self + 0x14c) = MAX(*(float*)((char*)self + 0x30), *(float*)((char*)self + 0x14c));
        *(float*)((char*)self + 0x150) = MAX(*(float*)((char*)self + 0x48), *(float*)((char*)self + 0x150));
        *(float*)((char*)self + 0x154) = MAX(*(float*)((char*)self + 0x24), *(float*)((char*)self + 0x154));
        *(float*)((char*)self + 0x158) = MAX(*(float*)((char*)self + 0x78), *(float*)((char*)self + 0x158));
        *(int*)((char*)self + 0x198) += *(int*)((char*)self + 0x84);
        total = points + *(int*)((char*)self + 0x84) + inverted;

        cBE_getInterface(cBE_getBE(), 0);
        // free ride in Conquer the Mountain pays the career instead of the HUD
        career = D_00535BC8.eventKind == 4 && D_00535BC8.gameType == 0;
        if (!career) {
            if (repeats > 0) {
                cRiderMetrix_postPointsMsg(self, 0x24, total, grade, 2.5f);
            } else {
                cRiderMetrix_postPointsMsg(self, 0x23, total, grade, 2.5f);
            }
            cRiderMetrix_postPointsMsg(self, 0x18, total, 0, 0.7f);
        } else {
            int amount = total / 500;
            if (amount > 20) {
                amount = 20;
            }
            func_00119EF8(self, 0, amount);
        }
    }

    if (!takeoff) {
        if (style != 0 || flag != 0) {
            return delta;
        }
    } else if (*(int*)((char*)self + 0x20) != 0 || *(int*)((char*)self + 0x28) != 0) {
        return delta;
    }
    if (*(float*)((char*)self + 0x14) > 0.0f || *(float*)((char*)self + 0xa4) < 0.0f) {
        func_00117708(self, 1.5f);
    }
    return delta;
}

//100%
extern "C" int cRiderMetrix_getInvertedPoints(void* self);
extern "C" int cRiderMetrix_getPendingPoints(void* self);
extern "C" void cRiderMetrix_clearMsgType(void* self, int type);
extern "C" void cRiderMetrix_postPointsMsg(void* self, int type, int value, int arg, float duration);

extern "C" int cRiderMetrix_dropPendingPoints(void* self)
{
    int n = cRiderMetrix_getPendingPoints(self);
    if (n > 0)
    {
        cRiderMetrix_clearMsgType(self, 1);
        cRiderMetrix_postPointsMsg(self, 0x25, n, 0, 1.5f);
    }
    if (*(int*)((char*)self + 0xA0) > 0)
    {
        cRiderMetrix_clearMsgType(self, 3);
        cRiderMetrix_postPointsMsg(self, 0x27, *(int*)((char*)self + 0xA0), 0, 1.5f);
    }
    int total = *(int*)((char*)self + 0x84) + cRiderMetrix_getInvertedPoints(self);
    if (total > 0)
    {
        cRiderMetrix_clearMsgType(self, 2);
        cRiderMetrix_clearMsgType(self, 0x1D);
        cRiderMetrix_clearMsgType(self, 0x1C);
        cRiderMetrix_clearMsgType(self, 0x1E);
        cRiderMetrix_clearMsgType(self, 0x1F);
        cRiderMetrix_clearMsgType(self, 0x20);
        cRiderMetrix_postPointsMsg(self, 0x28, total, 0, 1.5f);
    }
    cRiderMetrix_clearMsgType(self, 4);
    return n;
}

INCLUDE_ASM("ai/ridermetrix", cRiderMetrix_buildTrickId);

//100%
extern "C" void func_003E6448(void* dst, int value, int size);

struct sTrickBonus_11B1A8
{
    int grade;              // 0x0
    int points;             // 0x4
    unsigned char a;        // 0x8
    unsigned char b;        // 0x9
    unsigned char c;        // 0xA
    unsigned char d;        // 0xB
    unsigned char e;        // 0xC
    unsigned char f;        // 0xD
    unsigned char g;        // 0xE
    unsigned char pad;      // 0xF
};
extern sTrickBonus_11B1A8 D_0043D608[];

struct sTrickBits_11B1A8
{
    unsigned int pad0 : 10;
    unsigned int a : 2;     // bits 10-11
    unsigned int b : 4;     // bits 12-15
    unsigned int c : 3;     // bits 16-18
    unsigned int d : 3;     // bits 19-21
    unsigned int pad1 : 6;
    unsigned int e : 4;     // bits 28-31
    unsigned int pad2 : 3;
    unsigned int f : 7;     // bits 3-9
    unsigned int pad3 : 1;
    unsigned int g : 7;     // bits 11-17
    unsigned int pad4 : 9;
    unsigned int grade : 5; // bits 27-31
};

extern "C" int func_0011B1A8(void* self, sTrickId* id)
{
    sTrickBits_11B1A8* t = (sTrickBits_11B1A8*)id;
    sTrickBonus_11B1A8* e = D_0043D608;
    for (int i = 0; i < 24; i++, e++)
    {
        if (t->a != e->a) continue;
        if (t->b != e->b) continue;
        if (t->c != e->c) continue;
        if (t->d != e->d) continue;
        if (t->e != e->e) continue;
        if (t->f != e->f) continue;
        if (t->g != e->g) continue;
        func_003E6448(id, 0, 8);
        t->grade = e->grade;
        return e->points;
    }
    return 0;
}

//100%
extern float D_004A6310[2][3][4][2];

extern "C" void func_0011B2C0(void)
{
    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 3; b++) {
            for (int c = 0; c < 4; c++) {
                for (int d = 0; d < 2; d++) {
                    int va = a ? 0 : 5;
                    int vb = b ? (b == 1 ? 11 : 0) : 20;
                    int vc = c ? (c == 1 ? 15 : (c == 2 ? 10 : 0)) : 20;
                    int vd = d ? 0 : 5;
                    D_004A6310[a][b][c][d] = 120.0f - (float)(va + vb + vc + vd);
                }
            }
        }
    }
}

INCLUDE_ASM("ai/ridermetrix", updateRiderSpeedLimit);

extern "C" void* func_0041AA88(void* self);

//100%
void* func_0011B678(void* self)
{
    return func_0041AA88(self);
}

