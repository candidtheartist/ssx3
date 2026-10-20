#include "common.h"

//100%
struct sSndPlayerD9C8;
extern "C" sSndPlayerD9C8* cSndTimerSys_cSndTimerSys(sSndPlayerD9C8* self, int inchrg, int heap);
extern "C" void* func_002ADE88(void* self, int a);
extern "C" void* cBankMonitorInstance_cBankMonitorInstance(void* self);
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator new[](unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern const char D_00483238[];
extern void* D_00483B48[];

struct sBmVEntryCD08 {
    short delta;
    short index;
    void* fn;
};
struct sBmVtblCD08 {
    sBmVEntryCD08 e[4];
} __attribute__((aligned(8)));
extern const sBmVtblCD08 D_00483B88;

struct sBmVoiceCD08 {
    char pad_0x0[0xC0];
    sBmVoiceCD08() { cBankMonitorInstance_cBankMonitorInstance(this); }
    void operator delete[](void* p, unsigned int size);
};

struct sBankMonitorCD08 {
    char* vbase;                // 0x0
    char pad_0x4[0x8D8 - 0x4];
    void** vtbl;                // 0x8D8
    int f8DC;                   // 0x8DC
    int f8E0;                   // 0x8E0
    int f8E4;                   // 0x8E4
    int f8E8;                   // 0x8E8
    sBmVoiceCD08* voices;       // 0x8EC
    char vb[0x4];               // 0x8F0
};

extern "C" sBankMonitorCD08* cBankMonitor_cBankMonitor(sBankMonitorCD08* self, int inchrg, int heap)
{
    if (inchrg) {
        self->vbase = self->vb;
        func_002ADE88(self->vb, heap);
    }
    cSndTimerSys_cSndTimerSys((sSndPlayerD9C8*)self, 0, heap);
    *(const sBmVtblCD08**)(self->vbase + 4) = &D_00483B88;
    if (!inchrg) {
        // PORT: g++ 2.95 virtual-base this-adjust fix-up (copied vtable on the stack), written out by hand.
        sBmVtblCD08 vt = D_00483B88;
        *(sBmVtblCD08**)(self->vbase + 4) = &vt;
        char* base = self->vbase - 0x8F0;
        int d = (char*)self - base;
        vt.e[1].delta = D_00483B88.e[1].delta + d;
    }
    self->vtbl = D_00483B48;
    self->f8DC = 0;
    self->f8E0 = 1;
    self->f8E4 = 1;
    sBmVoiceCD08** slot = &self->voices;
    *slot = new (D_00483238, 0, 0) sBmVoiceCD08[64];
    return self;
}

//100%
void cMemMan_free(void*);
void operator_delete(int* ptr);
extern "C" void cBankMonitorInstance_destroy(void* self, int flags);
struct sSndPlayerDAC8;
extern "C" void cSndTimerSys_destroy(sSndPlayerDAC8* self, int flags);
extern "C" void func_002ADEE8(void* self, int flags);
extern void* D_00483B48[];

struct sBmVEntryE40 {
    short delta;
    short index;
    void* fn;
};
struct sBmVtblE40 {
    sBmVEntryE40 e[4];
} __attribute__((aligned(8)));
extern const sBmVtblE40 D_00483B88_E40 __asm__("D_00483B88");

struct sBmVoiceE40 {
    char pad_0x0[0xC0];
};

struct sBankMonitorE40 {
    char* vbase;                // 0x0
    char pad_0x4[0x8D8 - 0x4];
    void** vtbl;                // 0x8D8
    char pad_0x8DC[0x8EC - 0x8DC];
    sBmVoiceE40* voices;        // 0x8EC
};

extern "C" void cBankMonitor_destroy(sBankMonitorE40* self, int flags)
{
    self->vtbl = D_00483B48;
    *(const sBmVtblE40**)(self->vbase + 4) = &D_00483B88_E40;
    if (flags == 0) {
        // PORT: g++ 2.95 virtual-base this-adjust fix-up (copied vtable on the stack), written out by hand.
        sBmVtblE40 vt = D_00483B88_E40;
        *(sBmVtblE40**)(self->vbase + 4) = &vt;
        char* base = self->vbase - 0x8F0;
        int d = (char*)self - base;
        vt.e[1].delta = D_00483B88_E40.e[1].delta + d;
    }
    if (self->voices != 0) {
        sBmVoiceE40* q = self->voices + ((int*)self->voices)[-4];
        while (self->voices != q) {
            q--;
            cBankMonitorInstance_destroy(q, 0);
        }
        cMemMan_free((char*)self->voices - 0x10);
    }
    cSndTimerSys_destroy((sSndPlayerDAC8*)self, 0);
    if (flags & 2) {
        func_002ADEE8(self->vbase, 0);
    }
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern "C" int cBankMonitorInstance_isFree(void*);

extern "C" int cBankMonitor_findFreeVoice(void* self, int n)
{
    for (int i = 0; i < 64; i++) {
        if (cBankMonitorInstance_isFree((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0) != 0) {
            if (--n == 0) {
                return i;
            }
        }
    }
    return -1;
}

INCLUDE_ASM("sound/bankmonitor", cBankMonitor_BANKMONITOR_Create);

//100%
extern "C" void cBankMonitorInstance_pause(void*);

extern "C" void cBankMonitor_pauseVoices(void* self)
{
    *(int*)((char*)self + 0x8E8) = 1;
    for (int i = 0; i < 64; i++) {
        cBankMonitorInstance_pause((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0);
    }
}

//100%
extern "C" void cBankMonitorInstance_resume(void*);

extern "C" void cBankMonitor_resumeVoices(void* self)
{
    for (int i = 0; i < 64; i++) {
        cBankMonitorInstance_resume((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0);
    }
    *(int*)((char*)self + 0x8E8) = 0;
}

extern "C" void* cBankMonitor_findVoice(void* self, int idx, int a2);
extern "C" void cBankMonitorInstance_fadeTo(void* voice, int a, int b, float v);

extern "C" void cBankMonitor_fadeOutVoice(void* self, int idx, int a2, float v)
{
    void* voice = cBankMonitor_findVoice(self, idx, a2);
    if (voice != 0) {
        cBankMonitorInstance_fadeTo(voice, -1, 0, v);
    }
}

//100%
extern "C" void cBankMonitorInstance_stop(void*);

extern "C" void cBankMonitor_stopVoiceAt(void* self, int i)
{
    cBankMonitorInstance_stop((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cBankMonitor_stopVoiceAt(void* self, int i);

extern "C" void cBankMonitor_stopAll(void* self)
{
    int i;
    for (i = 0; i < 64; i++) {
        cBankMonitor_stopVoiceAt(self, i);
    }
}

//100%
extern "C" void cBankMonitorInstance_stop(void*);

struct sBmKeyD410 {
    short a;
    short id;
    union {
        int v;
        short s;
    };
};

static inline int cBankMonitor_stopByKey_match(char* e, sBmKeyD410 k)
{
    int r = 0;
    if (k.id == *(short*)(e + 0xAA)) {
        if ((k.id != -1 && k.s == *(short*)(e + 0xAC)) || k.v == *(int*)(e + 0xAC)) {
            r = 1;
        }
    }
    return r;
}

extern "C" void cBankMonitor_stopByKey(void* self, sBmKeyD410 key)
{
    for (int i = 0; i < 64; i++) {
        if (cBankMonitor_stopByKey_match((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0, key)) {
            cBankMonitorInstance_stop((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0);
        }
    }
}

//100%
extern "C" void cBankMonitor_stopByOwner(void* self, int id)
{
    for (int i = 0; i < 64; i++) {
        if (*(int*)((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0 + 0x80) == id) {
            cBankMonitorInstance_stop((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0);
        }
    }
}

//100%
struct sVoiceC0 { int key; int idx; char pad[0xC0 - 8]; };

extern "C" void* cBankMonitor_findVoice(void* self, int idx, int key)
{
    for (int i = 0; i < 64; i++) {
        if (cBankMonitorInstance_isFree((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0) == 0
            && (*(sVoiceC0**)((char*)self + 0x8EC))[i].key == key
            && (*(sVoiceC0**)((char*)self + 0x8EC))[i].idx == idx) {
            return &(*(sVoiceC0**)((char*)self + 0x8EC))[i];
        }
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* cBankMonitor_findVoice(void* self, int idx, int a2);
extern "C" void cBankMonitorInstance_stop(void*);
extern "C" void cBankMonitorInstance_fadeTo(void* voice, int a, int b, float v);

extern "C" void cBankMonitor_stopVoice(void* self, int idx, int a2, float v)
{
    void* voice = cBankMonitor_findVoice(self, idx, a2);
    if (voice != 0) {
        if (v != 0.0f) {
            cBankMonitorInstance_fadeTo(voice, -1, 1, v);
        } else {
            cBankMonitorInstance_stop(voice);
        }
    }
}

//100%
extern "C" int cBankMonitorInstance_isFree(void*);
extern "C" void cBankMonitorInstance_stop(void*);
// PORT: same ABI as the unit's cBankMonitorInstance_fadeTo(void*, int, int, float); the float is
// the 2nd parameter in the original, which orders the argument moves.
void cBankMonitorInstance_fadeTo_f(void* voice, float v, int a, int b) __asm__("cBankMonitorInstance_fadeTo");

struct sVoiceD650 {
    int state;      // 0x0
    int pad_4[2];
    int id;         // 0xC
    char pad[0xC0 - 0x10];
};

extern "C" void cBankMonitor_stopBankVoices(void* self, int id, float v)
{
    for (int i = 0; i < 64; i++) {
        if (cBankMonitorInstance_isFree((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0) == 0) {
            // PORT: pointer arithmetic through int
            sVoiceD650* e = (sVoiceD650*)(i * 0xC0 + *(int*)((char*)self + 0x8EC));
            if (e->state == 1 && e->id == id) {
                if (v != 0.0f) {
                    cBankMonitorInstance_fadeTo_f(e, v, -1, 1);
                } else {
                    cBankMonitorInstance_stop(e);
                }
            }
        }
    }
}

extern "C" int cBankMonitor_countAudibleVoices(void* self)
{
    int n = 0;
    for (int i = 0; i < 64; i++) {
        if (cBankMonitorInstance_isFree((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0) == 0) {
            if (*(int*)((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0 + 0x8) != 0) {
                n++;
            }
        }
    }
    return n;
}

// Number of the 64 voices for which cBankMonitorInstance_isFree returns 0 (active voices).
extern "C" int cBankMonitor_countActiveVoices(void* self)
{
    int n = 0;
    for (int i = 0; i < 64; i++) {
        if (cBankMonitorInstance_isFree((char*)*(void**)((char*)self + 0x8EC) + i * 0xC0) == 0) {
            n++;
        }
    }
    return n;
}

//100%
struct sBankVoice {
    char pad[0x5c];
    float value;
    char pad2[0xc0 - 0x60];
};

extern "C" void cBankMonitor_resetVoiceDistances(void* self)
{
    for (int i = 0; i < 64; i++) {
        (*(sBankVoice**)((char*)self + 0x8ec))[i].value = -1.0f;
    }
}

//100%
void* cSndTimer_cSndTimer(void* self)
{
    *(int*)self = 0;
    *(int*)((char*)self + 0x4) = -1;
    return self;
}

//100%
void operator_delete(int* ptr);

extern "C" void cSndTimer_destroy(int* self, int flags)
{
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
extern "C" void cSndTimer_clear(void*);
void cSndTimer_setPeriod(void* self, int a1);
void cSndTimer_activate(void* self);

struct sBmKeyD888 {
    short a;
    short id;
    int v;
};

// PORT: 64-bit long sound key
extern "C" void cSndTimer_set(void* self, int a1, long key, int b, int c, int d, int e, int f)
{
    cSndTimer_clear(self);
    cSndTimer_setPeriod(self, a1);
    // PORT: the 8-byte key is copied through its in-memory layout
    *(sBmKeyD888*)((char*)self + 0xC) = *(sBmKeyD888*)&key;
    *(int*)((char*)self + 0x18) = b;
    *(int*)((char*)self + 0x1C) = c;
    *(int*)((char*)self + 0x20) = d;
    *(int*)((char*)self + 0x24) = e;
    *(int*)((char*)self + 0x28) = f;
    cSndTimer_activate(self);
}

//100%
extern "C" int cSndTimer_isFree(void* self)
{
    return *(int*)((char*)self + 0x4) == -1;
}

//100%
void cSndTimer_deactivate(void* self);
void cSndTimer_setPeriod(void* self, int a1);

extern "C" void cSndTimer_clear(void* self)
{
    cSndTimer_deactivate(self);
    cSndTimer_setPeriod(self, -1);
}

//100%
void cSndTimer_setPeriod(void* self, int a1)
{
    *(int*)((char*)self + 0x4) = a1;
    *(int*)((char*)self + 0x8) = a1;
}

//100%
void cSndTimer_activate(void* self)
{
    *(int*)self = 1;
}

//100%
void cSndTimer_deactivate(void* self)
{
    *(int*)((char*)self + 0x0) = 0;
}

//100%
class cSndTimerSys_timerCallback_cObj {
public:
    char data[0x8D8];
    virtual void v01();
};

extern cSndTimerSys_timerCallback_cObj* D_004A3778;

extern "C" void cSndTimerSys_timerCallback()
{
    D_004A3778->v01();
}

INCLUDE_ASM("sound/bankmonitor", cSndTimerSys_cSndTimerSys);

//100%
void operator_delete(int* ptr);
extern "C" void func_003B5948(int id);
extern "C" void cSndPlayOpts_destroy(void* self, int flags);
extern "C" void func_002ADEE8(void* self, int flags);
extern void* D_00483BA8[];

struct sBmVEntryDAC8 {
    short delta;
    short index;
    void* fn;
};
struct sBmVtblDAC8 {
    sBmVEntryDAC8 e[4];
} __attribute__((aligned(8)));
extern const sBmVtblDAC8 D_00483BC0_DAC8 __asm__("D_00483BC0");

struct sBmSlotDAC8 {
    char pad_0x0[0x2C];
};

struct sSndPlayerDAC8 {
    char* vbase;                // 0x0
    char pad_0x4[0x98 - 0x4];
    sBmSlotDAC8 slots[48];      // 0x98
    void** vtbl;                // 0x8D8
};

extern "C" void cSndTimerSys_destroy(sSndPlayerDAC8* self, int flags)
{
    sBmSlotDAC8* end = self->slots + 48;
    self->vtbl = D_00483BA8;
    *(const sBmVtblDAC8**)(self->vbase + 4) = &D_00483BC0_DAC8;
    if (flags == 0) {
        // PORT: g++ 2.95 virtual-base this-adjust fix-up (copied vtable on the stack), written out by hand.
        sBmVtblDAC8 vt = D_00483BC0_DAC8;
        *(sBmVtblDAC8**)(self->vbase + 4) = &vt;
        char* base = self->vbase - 0x8DC;
        int d = (char*)self - base;
        vt.e[1].delta = D_00483BC0_DAC8.e[1].delta + d;
    }
    // PORT: function pointer passed as int
    func_003B5948((int)cSndTimerSys_timerCallback);
    D_004A3778 = 0;
    if (self->slots != 0) {
        sBmSlotDAC8* p = end;
        while (self->slots != p) {
            p--;
            cSndTimer_destroy((int*)p, 0);
        }
    }
    cSndPlayOpts_destroy(self, 0);
    if (flags & 2) {
        func_002ADEE8(self->vbase, 0);
    }
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

extern "C" void cSndTimerSys_timerCallback();
extern "C" void* func_003B5910(void*);

//98.75%
void* cSndTimerSys_installCallback(void* self)
{
    return func_003B5910((void*)cSndTimerSys_timerCallback);
}

//100%
extern "C" void cSndTimerSys_update(void* self)
{
    if (*(int*)((char*)self + 0x94) == 0) {
        *(int*)((char*)self + 0x88) += 1;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cSndTimerSys_findFreeTimer(void* self, int n)
{
    for (int i = 0; i < 48; i++) {
        if (cSndTimer_isFree((char*)self + 0x98 + i * 0x2C) != 0) {
            if (--n == 0) {
                return i;
            }
        }
    }
    return -1;
}

INCLUDE_ASM("sound/bankmonitor", cSndTimerSys_addTimer);

extern "C" void cSndTimer_clear(void*);

extern "C" void cSndTimerSys_removeTimer(void* self, int i)
{
    cSndTimer_clear((char*)self + (i * 0x2C + 0x98));
}

//100%
extern "C" void cSndTimer_clear(void*);

extern "C" void cSndTimerSys_removeAllTimers(void* self)
{
    char* p = (char*)self + 0x98;
    int i;
    for (i = 47; i >= 0; i--) {
        cSndTimer_clear(p);
        p += 0x2C;
    }
}

//100%
extern "C" void cSndTimer_clear(void*);

struct sBmKeyDDE0 {
    short a;
    short id;
    union {
        int v;
        short s;
    };
};

static inline int cSndTimerSys_removeTimersByKey_match(char* e, sBmKeyDDE0 k)
{
    int r = 0;
    if (k.id == *(short*)(e + 0xE)) {
        if ((k.id != -1 && k.s == *(short*)(e + 0x10)) || k.v == *(int*)(e + 0x10)) {
            r = 1;
        }
    }
    return r;
}

// Release-build assert: expands to an empty do { } while (0). Its loop notes keep GCC from reversing the
// slot loop into a count-down, as in the target.
#define ASSERT_DDE0(cond) do { } while (0)

// PORT: callers in this unit declare cSndTimerSys_removeTimersByKey(void*, long); the key is the same 8 bytes viewed as a struct.
void cSndTimerSys_removeTimersByKey_impl(void* self, sBmKeyDDE0 key) __asm__("cSndTimerSys_removeTimersByKey");

// Stops every one of the 48 monitored sounds that matches the key.
void cSndTimerSys_removeTimersByKey_impl(void* self, sBmKeyDDE0 key)
{
    for (int i = 0; i < 48; i++) {
        if (cSndTimerSys_removeTimersByKey_match((char*)self + 0x98 + i * 0x2C, key)) {
            cSndTimer_clear((char*)self + 0x98 + i * 0x2C);
        }
        ASSERT_DDE0(i < 48);
    }
}

//100%
class func_002ADE88_cObj {
public:
    virtual void v01(int a);
};

extern "C" func_002ADE88_cObj* func_002A8FA0();
extern char D_00483C00[];
extern void* D_004A377C;

extern "C" void* func_002ADE88(void* self, int a)
{
    *(void**)((char*)self + 0x4) = D_00483C00;
    D_004A377C = self;
    func_002ADE88_cObj* obj = func_002A8FA0();
    *(func_002ADE88_cObj**)self = obj;
    obj->v01(a);
    return self;
}

//100%
class func_002ADEE8_cObj {
public:
    virtual void v01();
    virtual void v02();
    virtual void v03(int a);
};

void operator_delete(int* ptr);
extern char D_00483C00[];
extern void* D_004A377C;

extern "C" void func_002ADEE8(void* self, int flags)
{
    *(void**)((char*)self + 0x4) = D_00483C00;
    (*(func_002ADEE8_cObj**)self)->v03(flags);
    operator_delete(*(int**)self);
    D_004A377C = 0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

extern "C" void func_002ADF58()
{
}

//100%
int BXrand();

extern "C" int cSoundManager_rand()
{
    return BXrand();
}

//100%
class cSoundManager_setSoundMode_cObj {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void v01();
    virtual int v02(int a);
};

struct cSoundManager_setSoundMode_sHolder {
    cSoundManager_setSoundMode_cObj* obj;
};

extern "C" int cSoundManager_setSoundMode(cSoundManager_setSoundMode_sHolder* self, int a)
{
    return self->obj->v02(a);
}

extern void* D_004D3E98[];

//100%
int PATHX_getPlayer(int self)
{
    return *(int*)((char*)(void*)D_004D3E98 + self * 4);
}

extern "C" void* MEM_free(void* self);

extern void* (*D_004A378C)(void*, int, int);
extern char D_00483288[];

// Allocate through the installed allocator hook, if any.
extern "C" void* PATHX_alloc(int size)
{
    void* r = 0;
    if (D_004A378C != 0) {
        r = D_004A378C(D_00483288, size, 0);
    }
    return r;
}

//100%
void* PATHX_free(void* self)
{
    return MEM_free(self);
}

//100%
extern void (*D_004A3798)();

extern "C" int PATHX_serviceTask()
{
    if (D_004A3798 != 0) {
        D_004A3798();
    }
    return 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void REAL_abortmessage();
extern "C" void func_004175C8();
extern "C" void* func_00252FA0(void* a0, int a1, int a2);
extern "C" void* MEM_resize(void* block, int size);
extern "C" void SYNCTASK_add(int (*fn)(), int a, int b);
extern int D_004A379C;
extern void (*D_004A3780)();
extern void (*D_004A3784)();
extern void* (*D_004A378C)(void*, int, int);
extern void* (*D_004A3790)(void*, int);
extern void* (*D_004A3794)(void*);

struct sBankMonSlot28_E048 {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
};
// D_004D3EF8's own type is defined later in the unit; bind a same-layout view.
extern sBankMonSlot28_E048 D_004D3EF8_E048[] __asm__("D_004D3EF8");

extern "C" void PATHX_init(void (*cb)(), int id)
{
    for (int i = 0; i < 24; i++) {
        D_004D3E98[i] = 0;
        D_004D3EF8_E048[i].f8 = -1;
        D_004D3EF8_E048[i].f4 = -1;
        D_004D3EF8_E048[i].f0 = -1;
        D_004D3EF8_E048[i].f18 = 0;
    }
    D_004A3798 = cb;
    D_004A379C = id;
    func_003B5910((void*)id);
    SYNCTASK_add(PATHX_serviceTask, 5, 100);
    D_004A3780 = REAL_abortmessage;
    D_004A3784 = func_004175C8;
    D_004A378C = func_00252FA0;
    D_004A3790 = MEM_resize;
    D_004A3794 = PATHX_free;
}

//100%
extern "C" int PATHX_serviceTask();
extern "C" void SYNCTASK_del(int (*fn)());
extern "C" void func_003B5948(int id);
extern void (*D_004A3798)();
extern int D_004A379C;

extern "C" void PATHX_shutdown()
{
    if (D_004A3798 != 0) {
        func_003B5948(D_004A379C);
        SYNCTASK_del(PATHX_serviceTask);
        D_004A3798 = 0;
        D_004A379C = 0;
    }
}

//100%
extern "C" void* func_00416210(void* dst, int c, int n);

extern "C" void PATHX_initPlayer(void* self)
{
    func_00416210(self, 0, 0x70);
    *(int*)((char*)self + 0x0) = -1;
    *(int*)((char*)self + 0x4) = -1;
    *(char*)((char*)self + 0x66) = -1;
    *(int*)((char*)self + 0x5C) = -1;
    *(int*)((char*)self + 0x8) = -1;
    *(char*)((char*)self + 0x65) = 1;
}

//100%
extern "C" void PATHX_removePlayer(void* p)
{
    for (int i = 0; i < 24; i++) {
        if (D_004D3E98[i] == p) {
            D_004D3E98[i] = 0;
        }
    }
}

//100%
extern "C" int PATHX_findFreePlayer(void)
{
    for (int i = 0; i < 24; i++) {
        if (D_004D3E98[i] == 0) {
            return i;
        }
    }
    return -1;
}

//100%
extern "C" void* func_00416210(void* dst, int c, int n);

extern "C" void PATHX_clearBankSlot(int* self)
{
    func_00416210(self, 0, 0x28);
    self[2] = -1;
    self[1] = -1;
    self[0] = -1;
}

// Find a slot: with a < 0 the first unused one (f8 < 0), otherwise the one with
// f8 == a and (b < 0 or f0 == b). Returns -8 when none matches.
extern "C" int PATHX_findBankSlot(int a, int b)
{
    int i;
    for (i = 0; i < 24; i++) {
        sBankMonSlot28_E048* e = &D_004D3EF8_E048[i];
        if (a < 0) {
            if (e->f8 >= 0) {
                continue;
            }
            return i;
        }
        if (e->f8 != a) {
            continue;
        }
        if (b < 0) {
            return i;
        }
        if (e->f0 == b) {
            return i;
        }
    }
    return -8;
}

extern "C" int func_002AE290()
{
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sBankMonSlot28v {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
};
// sBankMonSlot28 / D_004D3EF8 are defined later in the unit; bind a same-layout view.
extern sBankMonSlot28v D_004D3EF8_v[] __asm__("D_004D3EF8");
extern "C" int PATHX_findBankSlot(int a, int b);

extern "C" int PATHX_attachBank(int a, int unused, int b, int c)
{
    int i = PATHX_findBankSlot(a, b);
    if (i >= 0 || (i = PATHX_findBankSlot(-1, -1)) >= 0) {
        sBankMonSlot28v* e = &D_004D3EF8_v[i];
        e->f1C = 1;
        e->f8 = a;
        e->f0 = b;
        e->f4 = c;
        return c;
    }
    return -13;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sBankMonSlot28 {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
};
extern sBankMonSlot28 D_004D3EF8[];
extern "C" int PATHX_findBankSlot(int a, int b);
extern "C" int func_003B6300(int id);

extern "C" int PATHX_detachBank(int a, int b)
{
    int none = -1;
    int i = PATHX_findBankSlot(a, b);
    if (i < 0) {
        return -1;
    }
    sBankMonSlot28* e = &D_004D3EF8[i];
    if (e->f4 >= 0) {
        func_003B6300(-1);
        e->f14 = 0;
        e->f4 = none;
        e->f8 = none;
        e->f0 = none;
        e->f1C = 0;
        e->f24 = none;
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern sBankMonSlot28 D_004D3EF8[];
extern "C" int PATHX_findBankSlot(int a, int b);
extern "C" int PATHX_detachBank(int a, int b);

extern "C" int PATHX_detachOldestBank(int a)
{
    int best = 0x7FFFFFF;
    int bestIdx = -1;
    int i = 0;
    sBankMonSlot28* tbl = D_004D3EF8;
    int id;
    while (i < 24 && (id = PATHX_findBankSlot(a, i)) >= 0) {
        int t = tbl[id].f24;
        if (t >= 0 && t < best) {
            best = t;
            bestIdx = i;
        }
        i++;
    }
    if (bestIdx == -1) {
        return 0;
    }
    return PATHX_detachBank(a, bestIdx);
}

//100%
extern "C" int func_003B7B00(int n, int m);

extern "C" int PATHX_getPlayerMemSize(int n, int m)
{
    int size = n * 0xC + 0x70;
    if (m > 0) {
        size += func_003B7B00(n, m);
    }
    return size + (0x10 - (size & 0xF));
}

//100%
struct sBankDesc_2AE4C0 { char c[24]; };
struct sBankEnt_2AE4C0 { int f0; int f4; int f8; };
extern "C" int PATHX_findFreePlayer(void);
extern "C" void PATHX_initPlayer(void* self);
extern "C" int func_003B7818(void* desc, int n, int m, void* mem, int size);
extern "C" int func_003BA020(void* desc);
extern char D_004A37A8[];
extern "C" int sprintf(char* buf, const char* fmt, ...);

extern "C" int PATHX_createPlayer(char* name, sBankDesc_2AE4C0* desc, int count, int m, char* mem, int size)
{
    int slot = PATHX_findFreePlayer();
    if (slot < 0)
        return -13;
    D_004D3E98[slot] = mem;
    mem += 0x70;
    PATHX_initPlayer(D_004D3E98[slot]);
    char* b = (char*)D_004D3E98[slot];
    *(char**)(b + 0x6C) = mem;
    mem = count * 12 + mem;
    int off = mem - b;
    mem = mem + (0x10 - off % 16);
    size -= mem - b;
    int i;
    for (i = 0; i < count; i++)
        (*(sBankEnt_2AE4C0**)(b + 0x6C))[i].f4 = -1;
    if (desc)
        *(sBankDesc_2AE4C0*)(b + 0x30) = *desc;
    else
        func_003BA020(b + 0x30);
    *(char*)(b + 0x35) = 0;
    sprintf(b + 0x1C, D_004A37A8, 11, name);
    if (m > 0)
        *(int*)(b + 0x0) = func_003B7818(b + 0x30, count, m, mem, size);
    else
        *(char*)(b + 0x64) = 1;
    if (*(int*)(b + 0x0) < 0 && *(signed char*)(b + 0x64) == 0)
        return *(int*)(b + 0x0);
    *(char*)(b + 0x66) = count;
    *(int*)(b + 0x14) = 0x7F;
    *(int*)(b + 0x10) = 0;
    return slot;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern void* (*D_004A3794)(void*);
extern "C" void func_003B7838(int id);

extern "C" void PATHX_destroyPlayer(int idx)
{
    void* m = D_004D3E98[idx];
    if (*(signed char*)((char*)m + 0x64) != 0) {
        int id = PATHX_findBankSlot(idx, -1);
        while (id >= 0) {
            sBankMonSlot28* e = &D_004D3EF8[id];
            if (D_004A3794 != 0 && e->f14 != 0) {
                D_004A3794((void*)e->f14);
            }
            PATHX_clearBankSlot((int*)e);
            id = PATHX_findBankSlot(idx, -1);
        }
    } else {
        func_003B7838(*(int*)m);
    }
    PATHX_removePlayer(m);
}

//100%
extern "C" void func_002AE768(unsigned int idx, int a1, int a2)
{
    if (idx < 24) {
        void* m = D_004D3E98[idx];
        if (m != 0 && *(signed char*)((char*)m + 0x64) == 0) {
            *(int*)((char*)m + 0x28) = a1;
            *(int*)((char*)m + 0x2c) = a2;
        }
    }
}

INCLUDE_ASM("sound/bankmonitor", PATHX_queueSample);

//100%
extern "C" void func_003B7D80(void*);

extern "C" void func_002AE9F8(int i)
{
    void* p = D_004D3E98[i];
    if (*(signed char*)((char*)p + 0x64) == 0) {
        func_003B7D80(*(void**)((char*)*(void**)((char*)p + 0x6C) + 0x4));
    }
}

extern void* D_004D3E98[];
extern "C" void PATHX_updateAllPlayers(int a);

extern "C" int func_002AEA38(int i)
{
    if (D_004D3E98[i] != 0 && *((signed char*)D_004D3E98[i] + 0x65) != 0) {
        PATHX_updateAllPlayers(0);
    }
    return *(int*)((char*)D_004D3E98[i] + 0x50);
}

//100%
extern "C" void PATHX_updateAllPlayers(int a0);

struct sMonEntC { int f0; int f4; int f8; };

extern "C" int PATHX_getItemPos(int idx, int sub)
{
    void* m = D_004D3E98[idx];
    if (m != 0 && *(signed char*)((char*)m + 0x65) != 0) {
        PATHX_updateAllPlayers(0);
    }
    if (sub < 0) {
        return *(int*)((char*)m + 0x54);
    }
    if (sub < *(signed char*)((char*)m + 0x66)) {
        if ((*(sMonEntC**)((char*)m + 0x6C))[sub].f4 >= 0) {
            return (*(sMonEntC**)((char*)m + 0x6C))[sub].f8;
        }
        return -8;
    }
    return -8;
}

extern "C" int PATHX_getItemPosById(int idx, int key)
{
    void* m = D_004D3E98[idx];
    int i;
    if (m != 0 && *(signed char*)((char*)m + 0x65) != 0) {
        PATHX_updateAllPlayers(0);
    }
    for (i = 0; i < *(signed char*)((char*)m + 0x66); i++) {
        if ((*(sMonEntC**)((char*)m + 0x6C))[i].f4 == key) {
            return (*(sMonEntC**)((char*)m + 0x6C))[i].f8;
        }
    }
    return -8;
}

//100%
extern "C" void PATHX_updateAllPlayers(int a0);

extern "C" int PATHX_canQueue(int idx)
{
    if (D_004D3E98[idx] != 0) {
        if (*(signed char*)((char*)D_004D3E98[idx] + 0x65) != 0) {
            PATHX_updateAllPlayers(0);
        }
        return *(int*)((char*)D_004D3E98[idx] + 0x58);
    }
    return -8;
}

//100%
extern "C" int PATHX_invalidatePlayer(int idx)
{
    void* m = D_004D3E98[idx];
    if (m == 0) {
        return -8;
    }
    *(char*)((char*)m + 0x65) = 1;
    return 1;
}

//100%
extern void* D_004D3E98[];
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" int func_003B6670(int h, int sub, void* hdr, void* buf, unsigned int* pos);
extern "C" int func_003B8AD8(int h);
extern "C" int func_003B86C0(int h);
extern "C" int func_003B7B48(int h, void* out);
// PORT: the unit declares func_003B7C40(int, int); the second argument is an out-pointer
extern "C" void func_003B7C40(int h, int v);
extern "C" int func_003B7F18(int h);

struct sMonSub_EC58 {
    int size;   // 0x0
    int id;     // 0x4
    int pos;    // 0x8
};

struct sMonSlot_EC58 {
    int h;              // 0x0
    int sub;            // 0x4
    char pad08[0x4];
    int status;         // 0xC
    char pad10[0x38];
    int f48;            // 0x48
    int f4C;            // 0x4C
    int f50;            // 0x50
    int f54;            // 0x54
    int busy;           // 0x58
    int f5C;            // 0x5C
    int f60;            // 0x60
    signed char isMem;  // 0x64
    signed char dirty;  // 0x65
    signed char count;  // 0x66
    char pad67[0x5];
    sMonSub_EC58* subs; // 0x6C
};

struct sStrmInfo_EC58 {
    int count;
    int pad[3];
};

struct sStrmState_EC58 {
    int state;  // 0x0
    int a;      // 0x4
    int b;      // 0x8
    int c;      // 0xC
};

struct sStrmPos_EC58 {
    unsigned int samples;   // 0x0
    int pad[7];
};

struct sStrmHdr_EC58 {
    unsigned short rate;
    char pad[0xE];
};

// PORT: the end of this function stores the out-pointers themselves into the slot (as in the original)
extern "C" int PATHX_updatePlayer(int idx, int* outA, int* outB)
{
    sMonSlot_EC58* m = (sMonSlot_EC58*)D_004D3E98[idx];
    *outA = 0;
    *outB = 0;
    if (m == 0) {
        return -1;
    }
    int f60 = -8;
    m->busy = 1;
    if (m->h < 0) {
        return -2;
    }
    m->dirty = 1;
    func_003B58A0();
    sStrmInfo_EC58 info;
    sStrmState_EC58 st;
    sStrmHdr_EC58 hdr;
    char buf[0x70];
    sStrmPos_EC58 pos;
    if (m->isMem != 0) {
        if (m->sub >= 0 && m->subs->id >= 0) {
            f60 = func_003B6670(m->h, m->sub, &hdr, buf, &pos.samples);
            if (f60 >= 0) {
                *outB = func_003B8AD8(m->subs->id);
                if (*outB < 0) {
                    *outB = 0;
                    m->subs->id = -1;
                    goto done;
                }
                *outB *= 10;
                *outA = (int)((float)pos.samples / (float)hdr.rate * 1000.0f) - *outB;
            }
            m->subs->pos = *outB;
            m->f50 = m->subs->size;
            m->status = func_003B86C0(m->subs->id);
            m->f5C = m->subs->id;
        }
    } else {
        f60 = func_003B7B48(m->h, &info);
        m->f50 = 0;
        if (info.count >= m->count) {
            m->busy = 0;
        }
        for (int j = 0; j < m->count; j++) {
            m->subs[j].pos = 0;
            if (m->subs[j].id < 0) {
                continue;
            }
            func_003B7C40(m->subs[j].id, (int)&st);
            switch (st.state) {
            case 1:
                m->subs[j].pos = m->subs[j].size;
                m->f54 += m->subs[j].size;
                m->f50 += st.c;
                m->busy = 0;
                m->f5C = m->subs[j].id;
                break;
            case 0:
            case 2:
                *outA = st.a;
                *outB = st.b;
                if (outA == 0 && outB == 0) {
                    *outA = 0;
                    *outB = m->subs[j].size;
                }
                m->subs[j].pos = *outB;
                m->f54 += *outB;
                m->f50 += st.c;
                if (st.c < st.b) {
                    m->busy = 0;
                }
                m->f5C = m->subs[j].id;
                break;
            default:
                m->subs[j].id = -1;
                break;
            }
        }
        m->status = func_003B7F18(m->h);
    }
done:
    m->f48 = (int)outA;
    m->f4C = (int)outB;
    m->f60 = f60;
    m->dirty = 0;
    func_003B58D8();
    return 0;
}

//100%
extern void* D_004D3E98[];
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" int func_003B6670(int h, int sub, void* hdr, void* buf, unsigned int* pos);
extern "C" int func_003B8AD8(int h);
extern "C" int func_003B86C0(int h);
extern "C" int func_003B7B48(int h, void* out);
// PORT: the unit declares func_003B7C40(int, int); the second argument is an out-pointer
extern "C" void func_003B7C40(int h, int v);
extern "C" int func_003B7F18(int h);

struct sMonSub_EFA8 {
    int size;   // 0x0
    int id;     // 0x4
    int pos;    // 0x8
};

struct sMonSlot_EFA8 {
    int h;              // 0x0
    int sub;            // 0x4
    char pad08[0x4];
    int status;         // 0xC
    char pad10[0x38];
    int f48;            // 0x48
    int f4C;            // 0x4C
    int f50;            // 0x50
    int f54;            // 0x54
    int busy;           // 0x58
    int f5C;            // 0x5C
    int f60;            // 0x60
    signed char isMem;  // 0x64
    signed char dirty;  // 0x65
    signed char count;  // 0x66
    char pad67[0x5];
    sMonSub_EFA8* subs; // 0x6C
};

struct sStrmInfo_EFA8 {
    int count;
    int pad[3];
};

struct sStrmState_EFA8 {
    int state;  // 0x0
    int a;      // 0x4
    int b;      // 0x8
    int c;      // 0xC
};

struct sStrmPos_EFA8 {
    unsigned int samples;   // 0x0
    int pad[7];
};

struct sStrmHdr_EFA8 {
    unsigned short rate;
    char pad[0xE];
};

extern "C" void PATHX_updateAllPlayers(int reset)
{
    func_003B58A0();
    for (int i = 0; i < 24; i++) {
        sMonSlot_EFA8* m = (sMonSlot_EFA8*)D_004D3E98[i];
        if (m == 0) {
            continue;
        }
        if (reset != 0) {
            m->f60 = 0;
            m->dirty = 1;
            continue;
        }
        int f60 = -8;
        int f48 = 0;
        int f4C = 0;
        m->busy = 1;
        if (m->h >= 0) {
            sStrmInfo_EFA8 info;
            sStrmState_EFA8 st;
            sStrmHdr_EFA8 hdr;
            char buf[0x70];
            sStrmPos_EFA8 pos;
            if (m->isMem != 0) {
                if (m->sub >= 0 && m->subs->id >= 0) {
                    f60 = func_003B6670(m->h, m->sub, &hdr, buf, &pos.samples);
                    if (f60 >= 0) {
                        f4C = func_003B8AD8(m->subs->id);
                        if (f4C < 0) {
                            f4C = 0;
                            m->subs->id = -1;
                            goto done;
                        }
                        f4C *= 10;
                        f48 = (int)((float)pos.samples / (float)hdr.rate * 1000.0f) - f4C;
                    }
                    m->subs->pos = f4C;
                    m->f50 = m->subs->size;
                    m->status = func_003B86C0(m->subs->id);
                    m->f5C = m->subs->id;
                }
            } else {
                f60 = func_003B7B48(m->h, &info);
                m->f50 = 0;
                if (info.count >= m->count) {
                    m->busy = 0;
                }
                for (int j = 0; j < m->count; j++) {
                    m->subs[j].pos = 0;
                    if (m->subs[j].id < 0) {
                        continue;
                    }
                    func_003B7C40(m->subs[j].id, (int)&st);
                    switch (st.state) {
                    case 1:
                        m->subs[j].pos = m->subs[j].size;
                        m->f54 += m->subs[j].size;
                        m->f50 += st.c;
                        m->busy = 0;
                        m->f5C = m->subs[j].id;
                        break;
                    case 0:
                    case 2:
                        f48 = st.a;
                        f4C = st.b;
                        if (f48 == 0 && f4C == 0) {
                            f48 = f4C;
                            f4C = m->subs[j].size;
                        }
                        m->subs[j].pos = f4C;
                        m->f54 += f4C;
                        m->f50 += st.c;
                        if (st.c < st.b) {
                            m->busy = 0;
                        }
                        m->f5C = m->subs[j].id;
                        break;
                    default:
                        m->subs[j].id = -1;
                        break;
                    }
                }
                m->status = func_003B7F18(m->h);
            }
        }
    done:
        m->f48 = f48;
        m->f4C = f4C;
        m->f60 = f60;
        m->dirty = 0;
    }
    func_003B58D8();
}

//100%
extern "C" void PATHX_updateAllPlayers(int a0);

extern "C" int PATHX_getPlayStatus(int idx, int* a, int* b)
{
    void* m = D_004D3E98[idx];
    if (m == 0) {
        return -8;
    }
    if (*(signed char*)((char*)m + 0x65) != 0) {
        PATHX_updateAllPlayers(0);
    }
    *a = *(int*)((char*)m + 0x48);
    *b = *(int*)((char*)m + 0x4C);
    if (*(int*)((char*)m + 0x60) != 0) {
        return *(int*)((char*)m + 0x60);
    }
    return *(int*)((char*)m + 0x5C);
}

//100%
extern "C" int func_003E4E98();
extern "C" void func_004139F8(float);
extern int D_00450DC8[];

extern "C" void PATHX_getTimeMs(void)
{
    func_004139F8((float)func_003E4E98() / (float)D_00450DC8[0] * 1000.0f);
}

extern "C" int PATHX_getBankHandle(int idx)
{
    void* m = D_004D3E98[idx];
    if (m != 0 && *(signed char*)((char*)m + 0x64) != 0) {
        return *(int*)m;
    }
    return -1;
}

extern "C" int PATHX_getStreamHandle(int idx)
{
    void* m = D_004D3E98[idx];
    if (m != 0 && *(signed char*)((char*)m + 0x64) == 0) {
        return *(int*)m;
    }
    return -1;
}

//100%
extern "C" void PATHX_updateAllPlayers(int a0);

extern "C" int PATHX_getVolume(int idx)
{
    if (D_004D3E98[idx] != 0) {
        if (*(signed char*)((char*)D_004D3E98[idx] + 0x65) != 0) {
            PATHX_updateAllPlayers(0);
        }
        return *(int*)((char*)D_004D3E98[idx] + 0xC);
    }
    return -8;
}

//100%
extern "C" int func_002AF480(int idx)
{
    void* m = D_004D3E98[idx];
    if (m != 0) {
        return *(int*)((char*)m + 0x14);
    }
    return -8;
}

//100%
extern "C" int func_002AF4B0(int idx)
{
    void* m = D_004D3E98[idx];
    if (m != 0) {
        return *(int*)((char*)m + 0x10);
    }
    return -8;
}

//100%
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" int func_003B8050(void* h, int a, int b);
extern "C" int func_003B88C8(void* h, int a, int b);

extern "C" int func_002AF4E0(int idx, int a, int b)
{
    void* m = D_004D3E98[idx];
    int r = -8;
    if (m != 0) {
        func_003B58A0();
        if (*(signed char*)((char*)m + 0x64) != 0) {
            r = func_003B88C8(*(void**)m, a, b);
        } else {
            r = func_003B8050(*(void**)m, a, b);
        }
        func_003B58D8();
        *(int*)((char*)m + 0x10) = b;
    }
    return r;
}

//100%
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" int func_003B8010(void* h, int a);
extern "C" int func_003B8700(void* h, int a);

extern "C" int func_002AF580(int idx, int a)
{
    void* m = D_004D3E98[idx];
    int r = -8;
    if (m != 0) {
        func_003B58A0();
        if (*(signed char*)((char*)m + 0x64) != 0) {
            r = func_003B8700(*(void**)m, a);
        } else {
            r = func_003B8010(*(void**)m, a);
        }
        func_003B58D8();
        *(int*)((char*)m + 0x14) = a;
    }
    return r;
}

//100%
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" int func_003B8530(int h, int v, int c);
// PORT: the unit declares func_003B7EB0 as void; this caller uses its result.
int func_003B7EB0_r(int h, int v, int c) __asm__("func_003B7EB0");

extern "C" int PATHX_fadeVolume(int idx, int c, int v, char busy)
{
    void* m = D_004D3E98[idx];
    int r = 0;
    if (busy == 0) {
        func_003B58A0();
        *(int*)((char*)m + 0x8) = c;
        if (*(signed char*)((char*)m + 0x64) != 0) {
            r = func_003B8530(*(int*)((char*)*(void**)((char*)m + 0x6C) + 0x4), v / 10, c);
        } else {
            r = func_003B7EB0_r(*(int*)m, v, c);
        }
        func_003B58D8();
    }
    return r;
}

//100%
extern "C" void* func_0028B180();
extern "C" void PATHX_updateAllPlayers(int a0);
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" void func_003B85F0(int h, int v);
extern "C" void func_003B7E70(int h, int v);

extern "C" int PATHX_setVolume(int idx, int v)
{
    void* m = D_004D3E98[idx];
    int r = 0;
    if (*(int*)((char*)func_0028B180() + 0x6280) == 0) return 0;
    if (*(signed char*)((char*)m + 0x65) != 0) {
        PATHX_updateAllPlayers(0);
    }
    int cur = *(int*)((char*)m + 0xC);
    if (*(int*)((char*)m + 0x8) < 0 || *(int*)((char*)m + 0x8) == cur) {
        *(int*)((char*)m + 0x8) = -1;
        if (cur != v && v >= 0 && cur >= 0) {
            func_003B58A0();
            if (*(signed char*)((char*)m + 0x64) != 0) {
                func_003B85F0(*(int*)((char*)*(void**)((char*)m + 0x6C) + 0x4), v);
            } else {
                func_003B7E70(*(int*)m, v);
            }
            func_003B58D8();
            *(int*)((char*)m + 0xC) = v;
        }
    } else {
        r = -8;
    }
    return r;
}

//100%
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" void func_003B7FB8(int h, int v);
extern "C" void func_003B8790(int h, int v);

extern "C" int PATHX_setPaused(int idx, int reset)
{
    void* m = D_004D3E98[idx];
    unsigned short v;
    if (reset != 0) {
        v = 0;
        *(int*)((char*)m + 0x18) = *(unsigned short*)((char*)m + 0x3C);
    } else {
        v = *(int*)((char*)m + 0x18);
    }
    func_003B58A0();
    if (*(signed char*)((char*)m + 0x64) != 0) {
        func_003B8790(*(int*)((char*)*(void**)((char*)m + 0x6C) + 4), v);
    } else {
        func_003B7FB8(*(int*)m, v);
    }
    func_003B58D8();
    *(char*)((char*)m + 0x65) = 1;
    return 0;
}

//100%
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" void func_003B78F8(int);
extern "C" void func_003B89E0(int);

extern "C" int PATHX_flush(int idx)
{
    void* m = D_004D3E98[idx];
    func_003B58A0();
    if (*(signed char*)((char*)m + 0x64) != 0) {
        func_003B89E0(*(int*)((char*)*(void**)((char*)m + 0x6C) + 0x4));
    } else {
        func_003B78F8(*(int*)((char*)m + 0x0));
    }
    func_003B58D8();
    *(char*)((char*)m + 0x65) = 1;
    return 0;
}

//100%
extern "C" int cSpeechManager_playEvent(void* self, int a1);
extern char* D_004A37B4;
extern int D_004A37BC;

// PORT: real signature is int(int); the unit later declares cSpeechManager_eventCallback as void() for its callback use.
extern "C" int cSpeechManager_eventCallback_impl(int a) __asm__("cSpeechManager_eventCallback");
extern "C" int cSpeechManager_eventCallback_impl(int a)
{
    if (D_004A37BC != 0) {
        return -1;
    }
    return cSpeechManager_playEvent(D_004A37B4, a);
}

//100%
void* cSpeechBank_cSpeechBank(void* self)
{
    int t0 = 0;
    *(int*)((char*)self + 0x48) = t0;
    *(int*)self = -1;
    *(int*)((char*)self + 0x44) = t0;
    *(signed char*)((char*)self + 0x4) = (signed char)t0;
    return self;
}

//100%
extern "C" void func_003D6CA0(void* a0);

extern "C" void cSpeechBank_destroy(int* self, int flags)
{
    func_003D6CA0(*(void**)self);
    if (*(int*)((char*)self + 0x48) != 0) {
        MEM_free(*(void**)((char*)self + 0x44));
    }
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
extern "C" int BXFILE_exists(const char* name);
extern "C" void* FILE_load(const char* name, int a1);
extern "C" int func_003D69F0(void* data);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" char* func_0041ACC0(const char* s, int c);
void* cSpeechBank_cSpeechBank(void* self);
extern char D_004A37C0[];
extern char D_004832B0[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" int sprintf(char* buf, const char* fmt, ...);

// PORT: callers declare cSpeechBank_create as int(int, int, int); the body is (name, unused, data) returning an object pointer.
void* cSpeechBank_create_impl(const char* name, int unused, void* data) __asm__("cSpeechBank_create");

void* cSpeechBank_create_impl(const char* name, int unused, void* data)
{
    char buf[0x50];
    int owned = data == 0;
    sprintf(buf, D_004A37C0, name);
    if (data == 0) {
        if (BXFILE_exists(buf) == 0) {
            return 0;
        }
        data = FILE_load(buf, 0);
    }
    char* obj = (char*)cSpeechBank_cSpeechBank(cMemMan_alloc(0x4C, D_004832B0, 0, 0));
    *(int*)(obj + 0x48) = owned;
    *(void**)(obj + 0x44) = data;
    *(int*)obj = func_003D69F0(data);
    strcpy(obj + 4, name);
    char* p = func_0041ACC0(obj + 4, '\\');
    if (p == 0) {
        *(char**)(obj + 0x40) = obj + 4;
    } else {
        *(char**)(obj + 0x40) = p + 1;
    }
    return obj;
}

//100%
extern "C" int cSpeechBank_hasId(void* self, int a1)
{
    return a1 == *(int*)self;
}

//100%
extern char* D_004A37B4;
extern "C" void cStreamSys_createStream(void* sys, int id, int a, int b, int c);
extern "C" void cSpeechInstance_loadConfig(void* self, int a, int b, int c);

struct sBmPair_FA68 {
    int a;
    int b;
};

struct sBmStream_FA68 {
    int f0;                     // 0x0
    int f4;                     // 0x4
    int f8;                     // 0x8
    char fC;                    // 0xC
    char pad_0xD[0xCC - 0xD];
    sBmPair_FA68 pairs[4];      // 0xCC
    int fEC;                    // 0xEC
    int fF0;                    // 0xF0
    char pad_0xF4[0x8C4 - 0xF4];
    int f8C4;                   // 0x8C4
    int f8C8;                   // 0x8C8
    int f8CC;                   // 0x8CC
    int f8D0;                   // 0x8D0
    char pad_0x8D4[0x8F4 - 0x8D4];
    int f8F4;                   // 0x8F4
    char pad_0x8F8[0x900 - 0x8F8];
    int f900;                   // 0x900
};

extern "C" void* cSpeechInstance_cSpeechInstance(void* mem, int a1, int a2, int a3, int a4, int a5, int a6)
{
    sBmStream_FA68* self = (sBmStream_FA68*)mem;
    self->f0 = a1;
    self->f4 = a2;
    self->f900 = 1;
    self->f8 = a6;
    self->fEC = 0;
    self->fF0 = 0;
    self->f8C4 = 0;
    self->f8C8 = 0;
    self->f8CC = 0;
    self->f8D0 = 0;
    self->f8F4 = 0;
    self->fC = 0;
    for (int i = 0; i < 4; i++) {
        self->pairs[i].a = 0;
        self->pairs[i].b = 0;
    }
    cStreamSys_createStream(*(void**)D_004A37B4, self->f4, a4, 0, 0x20000);
    cSpeechInstance_loadConfig(self, a1, a3, a5);
    return self;
}

//100%
extern "C" void cStreamSys_deleteStream(void* self, int i);
extern "C" void cSpeechBank_destroy(int* self, int flags);
extern char* D_004A37B4;
extern int D_004A37B8;

struct sBmVoiceFB38 {
    void* handle;           // 0x0
    int active;             // 0x4
};

struct sBmPairFB38 {
    void* p[2];
};

struct sBankMonFB38 {
    int field_0x0;
    int id;                         // 0x4
    char pad_0x8[0xC4];
    sBmVoiceFB38 voices[(0xEC - 0xCC) / 8];   // 0xCC
    int voiceCount;                 // 0xEC
    int streamCount;                // 0xF0
    int* streams[(0x8D4 - 0xF4) / 4];         // 0xF4
    sBmPairFB38 pairs[1];           // 0x8D4
};

extern "C" void cSpeechInstance_destroy(void* selfp, int flags)
{
    sBankMonFB38* self = (sBankMonFB38*)selfp;
    int i;
    for (i = 0; i < self->streamCount; i++) {
        if (self->streams[i] != 0) {
            cSpeechBank_destroy(self->streams[i], 3);
        }
    }
    D_004A37B8 -= self->streamCount;
    for (i = 0; i < self->voiceCount; i++) {
        for (int j = 0; j < 2; j++) {
            if (self->pairs[i].p[j] != 0) {
                MEM_free(self->pairs[i].p[j]);
            }
        }
        if (self->voices[i].active != 0) {
            MEM_free(self->voices[i].handle);
            self->voices[i].active = 0;
            self->voices[i].handle = 0;
        }
    }
    cStreamSys_deleteStream(*(void**)D_004A37B4, self->id);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern "C" int cSpeechInstance_canPlay(void* p);
extern "C" void* func_003D7EC8(void* p);
extern "C" void* func_003D8040(void* p);
extern char* D_004A37B4;

class cSpeechInstance_update_cObj {
public:
    char data[0x1BC];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
};

// PORT: i is passed through as a pointer-sized handle
extern "C" void cSpeechInstance_update(void* self, int i)
{
    if (cSpeechInstance_canPlay(self) != 0) {
        if (*(int*)((char*)self + 0x900) != 0) {
            ((cSpeechInstance_update_cObj*)D_004A37B4)->v04();
            if (func_003D7EC8((void*)i) != 0) {
                *(int*)((char*)self + 0x900) = 0;
            }
        } else {
            func_003D8040((void*)i);
            *(int*)((char*)self + 0x900) = 1;
        }
    } else {
        *(int*)((char*)self + 0x900) = 1;
    }
}

//100%
extern "C" void* func_003D7EC8(void* p);

// PORT: real arity is (self, p); the unit later declares cSpeechInstance_flushRequests(int)
void* cSpeechInstance_flushRequests_impl(void* self, void* p) __asm__("cSpeechInstance_flushRequests");

void* cSpeechInstance_flushRequests_impl(void* self, void* p)
{
    void* r = func_003D7EC8(p);
    if (r != 0) {
        *(int*)((char*)self + 0x900) = 0;
    }
    return r;
}

INCLUDE_ASM("sound/bankmonitor", cSpeechInstance_loadHeaderBig);

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void func_002A77F8(void* parser, void* src, int n);
extern "C" void func_002A7890(void* parser, int flags);
extern "C" void func_002A7A20(void* parser);
extern "C" int func_002A7C68(void* parser, int file);
extern "C" char* func_002A7DA0(void* parser);
extern "C" int func_002A7F90(void* parser);
extern "C" int func_002A7FF8(void* parser, const char* key, char* out);
void cStreamSys_openBigFile_2B0088(void* self, int i, char* val) __asm__("cStreamSys_openBigFile");
extern "C" int cSpeechInstance_loadHeaderBig(void* self, int a, char* name, int b, int c);
extern "C" int func_0041AA88(const char* a, const char* b);
extern void* D_004A37B0;
extern char* D_004A37B4;
extern char D_004A37C8[];
extern char D_004828C0[];
extern char D_004A37D0[];
extern char D_004832D8[];
extern char D_004832E8[];
extern char D_004A36E0[];
struct sBankList_0348;
extern "C" void cSpeechInstance_addBank(sBankList_0348* self, int a, int b, int c);

extern "C" void cSpeechInstance_loadConfig(void* p, int a1, int a2, int a3)
{
    char* self = (char*)p;
    char parser[0x810];
    char value[0x100];
    char v40[0x40];
    char path[0x80];
    char name[0x60];
    func_002A77F8(parser, D_004A37B0, 0x100);
    if (func_002A7C68(parser, a2) != 0)
    {
        func_002A7A20(parser);
        while (func_002A7F90(parser) == 0)
        {
            char* key = func_002A7DA0(parser);
            if (func_0041AA88(D_004A37C8, key) == 0)
            {
                func_002A7FF8(parser, D_004A37C8, v40);
                cStreamSys_openBigFile_2B0088(*(void**)D_004A37B4, *(int*)(self + 4), v40);
            }
            if (func_0041AA88(D_004828C0, key) == 0)
            {
                func_002A7FF8(parser, D_004828C0, self + 0x6C);
                sprintf(value, D_004832D8, self + 0x6C);
                if (cSpeechInstance_loadHeaderBig(self, 1, value, a1, a2) == 0)
                    break;
                if (a3)
                {
                    sprintf(value, D_004832E8, self + 0x6C);
                    cSpeechInstance_loadHeaderBig(self, 0, value, a1, a2);
                }
                *(int*)(self + 0xEC) += 1;
            }
            if (func_0041AA88(D_004A37D0, key) == 0)
            {
                func_002A7FF8(parser, D_004A37D0, value);
                sprintf(path, D_004A36E0, self + 0x6C, name);
                cSpeechInstance_addBank((sBankList_0348*)self, (int)path, (int)name, 0);
            }
        }
    }
    func_002A7890(parser, 2);
}

//100%
extern "C" int cStreamSys_getState(void* self, int i);
extern "C" float cStreamSys_getTimeLeft(void* self, int i);
extern "C" int cStreamSys_isPlaying(void* self, int i);
extern char* D_004A37B4;

extern "C" int cSpeechInstance_canPlay(void* p)
{
    int state = cStreamSys_getState(*(void**)D_004A37B4, *(int*)((char*)p + 0x4));
    if (state == 0) {
        return 1;
    }
    if (state != 1) {
        return 0;
    }
    if (cStreamSys_isPlaying(*(void**)D_004A37B4, *(int*)((char*)p + 0x4)) == 0) {
        return 0;
    }
    int ok = (int)cStreamSys_getTimeLeft(*(void**)D_004A37B4, *(int*)((char*)p + 0x4)) < 500;
    int r = 0;
    if (ok) {
        r = state;
    }
    return r;
}

//100%
extern "C" void cStreamSys_stop(void* self, int i);
extern char* D_004A37B4;

extern "C" void cSpeechInstance_stop(void* p)
{
    cStreamSys_stop(*(void**)D_004A37B4, *(int*)((char*)p + 0x4));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cSpeechBank_create(int a, int b, int c);
extern int D_004A37B8;

struct sBankList_0348 {
    char pad[0xF0];
    int count;     // 0xF0
    int ids[1];    // 0xF4
};

extern "C" void cSpeechInstance_addBank(sBankList_0348* self, int a, int b, int c)
{
    self->ids[self->count] = cSpeechBank_create(a, b, c);
    if (self->ids[self->count] != 0) {
        self->count++;
        D_004A37B8++;
    }
}

//100%
extern "C" unsigned int strlen(const char* s);

extern "C" int cSpeechInstance_getBankLanguage(const char* name)
{
    int lang = 0;
    int len = strlen(name);
    if (name[len - 4] == '_') {
        if (name[len - 3] == 'e' && name[len - 2] == 'n' && name[len - 1] == 'g') {
            lang = 1;
        } else if (name[len - 3] == 'f' && name[len - 2] == 'r' && name[len - 1] == 'n') {
            lang = 2;
        } else if (name[len - 3] == 'g' && name[len - 2] == 'r' && name[len - 1] == 'm') {
            lang = 3;
        } else if (name[len - 3] == 's' && name[len - 2] == 'p' && name[len - 1] == 'n') {
            lang = 4;
        }
    }
    return lang;
}

//100%
struct sSndKey8_04D8 {
    long v;
} __attribute__((packed));
extern sSndKey8_04D8 D_004A37D8_p3[] __asm__("D_004A37D8");
extern sSndKey8_04D8 D_004A37E0_p3[] __asm__("D_004A37E0");
extern char* D_004A37B4;
extern char D_004832F8[];
extern char D_004A3590[];
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" int cSpeechBank_hasId(void* self, int a1);
extern "C" int cSpeechManager_applyRequest_p3(void* sys, int a, int b) __asm__("cSpeechManager_applyRequest");
extern "C" int cSpeechInstance_getBankLanguage(const char* name);
extern "C" int cStreamSys_getState(void* self, int i);
extern "C" float cStreamSys_getTimeLeft(void* self, int i);
extern "C" int cStreamSys_isPlaying(void* self, int i);
extern "C" void cStreamSys_setGainPtr(void* self, int i, int w);
// PORT: cSndTimerSys_addTimer takes a 64-bit sound key by value and returns int.
extern "C" int cSndTimerSys_addTimer_04D8(void*, int, long, void*, int, int, int, int) __asm__("cSndTimerSys_addTimer");

typedef int (*Fn1_04D8)(void*, int, char*, int, int, int, int, float, int, int);

struct sBmVE_04D8 {
    short delta;
    short index;
    void* fn;
};

struct sBmObj_04D8 {
    char pad[0x40];
    int f40;
};

struct sBmList_04D8 {
    int f0;                     // 0x0
    int f4;                     // 0x4
    char pad8[0xE8];
    int count;                  // 0xF0
    sBmObj_04D8* ids[1];        // 0xF4
};

struct sBmArgs_04D8 {
    int f0;
    int f4;
    char pad8[4];
    unsigned short fC;
};

static inline sBmObj_04D8** at_04D8(sBmObj_04D8** base, int i)
{
    return base + i;
}

extern "C" int cSpeechInstance_playEvent_impl(sBmList_04D8* self, sBmArgs_04D8* a) __asm__("cSpeechInstance_playEvent");

extern "C" int cSpeechInstance_playEvent_impl(sBmList_04D8* self, sBmArgs_04D8* a)
{
    int idx = -1;
    int i;
    if (cSpeechBank_hasId(self->ids[a->f0], a->f0)) {
        idx = a->f0;
    } else {
        for (i = 0; i < self->count; i++) {
            if (cSpeechBank_hasId(self->ids[i], a->f0)) {
                idx = i;
            }
        }
    }
    if (idx >= 0 && cSpeechManager_applyRequest_p3(D_004A37B4, self->f0, a->fC)) {
        sBmObj_04D8** slot = at_04D8(self->ids, idx);
        int lang = cSpeechInstance_getBankLanguage((char*)*slot + 4);
        char buf[0x100];
        sprintf(buf, D_004832F8, D_004A3590, D_004A37B4 + 0x158 + lang * 0x14, (char*)*slot + 4);
        char* d0 = D_004A37B4;
        sBmVE_04D8* vt0 = *(sBmVE_04D8**)(d0 + 0x1BC);
        int h = ((int (*)(void*, int, int))vt0[2].fn)(d0 + vt0[2].delta, self->f0, (*slot)->f40);
        char* d; sBmVE_04D8* vt;
        int t = (int)cStreamSys_getTimeLeft(*(void**)D_004A37B4, self->f4);
        int r;
        if (cStreamSys_getState(*(void**)D_004A37B4, self->f4) != 0) {
            if (cStreamSys_isPlaying(*(void**)D_004A37B4, self->f4) != 0) {
                d = D_004A37B4;
                vt = *(sBmVE_04D8**)(d + 0x1BC);
                r = ((Fn1_04D8)vt[1].fn)(d + vt[1].delta, self->f4, buf, a->f4, *(int*)((char*)self + 0x8CC), -1, *(int*)((char*)self + 0x8D0), *(float*)((char*)self + 0x8F4), *(int*)((char*)self + 0x8F8), *(int*)((char*)self + 0x8FC));
                if (r >= 0) {
                    cSndTimerSys_addTimer_04D8(**(char***)D_004A37B4 + 0x1D8, t, D_004A37D8_p3[0].v, self, r, h, 0, 0);
                }
                return r;
            }
            d = D_004A37B4;
            vt = *(sBmVE_04D8**)(d + 0x1BC);
            r = ((Fn1_04D8)vt[1].fn)(d + vt[1].delta, self->f4, buf, a->f4, *(int*)((char*)self + 0x8CC), -1, *(int*)((char*)self + 0x8D0), *(float*)((char*)self + 0x8F4), *(int*)((char*)self + 0x8F8), *(int*)((char*)self + 0x8FC));
            if (r >= 0) {
                cSndTimerSys_addTimer_04D8(**(char***)D_004A37B4 + 0x1D8, 0xC8, D_004A37E0_p3[0].v, self, r, h, 0, 0);
            }
            return r;
        }
        d = D_004A37B4;
        vt = *(sBmVE_04D8**)(d + 0x1BC);
        int w = ((int (*)(void*, int, int, int))vt[3].fn)(d + vt[3].delta, self->f0, h, *(int*)((char*)self + 0x8D0));
        if (w != 0) {
            cStreamSys_setGainPtr(*(void**)D_004A37B4, self->f4, w);
        }
        char* d2 = D_004A37B4;
        sBmVE_04D8* vt2 = *(sBmVE_04D8**)(d2 + 0x1BC);
        return ((Fn1_04D8)vt2[1].fn)(d2 + vt2[1].delta, self->f4, buf, a->f4, *(int*)((char*)self + 0x8CC), *(int*)((char*)self + 0x8C8), *(int*)((char*)self + 0x8D0), *(float*)((char*)self + 0x8F4), *(int*)((char*)self + 0x8F8), *(int*)((char*)self + 0x8FC));
    }
    return -1;
}

extern char* D_004A37B4;
extern "C" int cStreamSys_isPlaying(void* self, int i);

extern "C" int cSpeechInstance_isPlaying(void* p)
{
    return cStreamSys_isPlaying(*(void**)D_004A37B4, *(int*)((char*)p + 0x4));
}

extern "C" void func_002B07E8(void* self, int value)
{
    *(int*)((char*)self + 0x8C4) = value;
}

extern "C" void func_002B07F0(void* self, int value)
{
    *(int*)((char*)self + 0x8C8) = value;
}

//100%
extern "C" void* cBankManager_cBankManager(void* self, int embedded, int count, int heap);
extern "C" void* cStreamSys_cStreamSys(void* self, int inchrg, int banks, int count, int heap);
struct sBankSlots;
extern "C" void cSpeechManager_clearRequests(sBankSlots* self);
extern char* D_004A37B4;
extern void* D_00483870[];
extern void* D_00483B48[];
extern const char D_00483308[];

struct sName17_07F8 { char s[17]; };
struct sName18_07F8 { char s[18]; } __attribute__((aligned(2)));
extern const sName17_07F8 D_00483318;
extern const sName18_07F8 D_00483330;
extern const sName17_07F8 D_00483348;
extern const sName17_07F8 D_00483360;
extern const sName18_07F8 D_00483378;

struct sBmonVEntry07F8 {
    short delta;
    short index;
    void* fn;
};
struct sBmonVtblA07F8 {
    sBmonVEntry07F8 e[4];
} __attribute__((aligned(8)));
struct sBmonVtblB07F8 {
    sBmonVEntry07F8 e[7];
} __attribute__((aligned(8)));
// The unit declares these vtables later with its own types; bind views by asm label.
extern const sBmonVtblA07F8 D_004838A0_07F8 __asm__("D_004838A0");
extern const sBmonVtblB07F8 D_004838C0_07F8 __asm__("D_004838C0");

// PORT: g++ 2.95 constructor of a class with virtual bases (stack vtable this-adjust fix-ups written out by hand).
extern "C" char* cSpeechManager_cSpeechManager(char* self, int inchrg, int a2, int a3, int heap)
{
    if (inchrg) {
        char* vb = self + 0x1C0;
        char* vb2 = self + 0xC98;
        *(char**)(self + 0xC98) = self + 0x1C8;
        *(char**)self = vb2;
        *(char**)(self + 0x3A0) = vb;
        func_002ADE88(vb, heap);
        cBankManager_cBankManager(*(void**)(self + 0xC98), 0, a2, heap);
        cStreamSys_cStreamSys(*(void**)self, 0, a2, a3, heap);
    }
    *(const sBmonVtblA07F8**)(*(char**)(**(char***)self + 0x1D8) + 4) = &D_004838A0_07F8;
    *(void***)(**(char***)self + 0xAB0) = D_00483B48;
    *(const sBmonVtblB07F8**)(**(char***)self + 0x1D4) = &D_004838C0_07F8;
    if (inchrg == 0) {
        sBmonVtblA07F8 t1 = D_004838A0_07F8;
        *(sBmonVtblA07F8**)(*(char**)(**(char***)self + 0x1D8) + 4) = &t1;
        char* base1 = *(char**)(**(char***)self + 0x1D8) - 0x1C0;
        int d1 = self - base1;
        t1.e[1].delta = D_004838A0_07F8.e[1].delta + d1;
        sBmonVtblB07F8 t2 = D_004838C0_07F8;
        *(sBmonVtblB07F8**)(**(char***)self + 0x1D4) = &t2;
        char* base2 = **(char***)self - 0x1C8;
        int d2 = self - base2;
        t2.e[1].delta = D_004838C0_07F8.e[1].delta + d2;
    }
    *(void***)(self + 0x1BC) = D_00483870;
    *(int*)(self + 0x10) = -1;
    *(int*)(self + 0x8) = 0;
    *(int*)(self + 0xC) = 0;
    D_004A37B4 = self;
    *(void***)(self + 0x4) = new (D_00483308, 0, 0) void*[2];
    for (int i = 0; i < 2; i++)
        (*(void***)(self + 0x4))[i] = 0;
    cSpeechManager_clearRequests((sBankSlots*)self);
    *(sName17_07F8*)(self + 0x158) = D_00483318;
    *(sName18_07F8*)(self + 0x16C) = D_00483330;
    *(sName17_07F8*)(self + 0x180) = D_00483348;
    *(sName17_07F8*)(self + 0x194) = D_00483360;
    *(sName18_07F8*)(self + 0x1A8) = D_00483378;
    return self;
}

//100%
void cMemMan_free(void*);
void operator_delete(int* ptr);
extern "C" void cBankManager_destroy(void* self, int flags);
extern "C" void cStreamSys_destroy(void* self, int flags);
extern "C" void func_002ADEE8(void* self, int flags);
extern char* D_004A37B4;
extern void* D_00483870[];
extern void* D_00483B48[];

struct sBmonVEntry0AE8 {
    short delta;
    short index;
    void* fn;
};
struct sBmonVtblA0AE8 {
    sBmonVEntry0AE8 e[4];
} __attribute__((aligned(8)));
struct sBmonVtblB0AE8 {
    sBmonVEntry0AE8 e[7];
} __attribute__((aligned(8)));
extern const sBmonVtblA0AE8 D_004838A0;
extern const sBmonVtblB0AE8 D_004838C0;

// PORT: g++ 2.95 virtual-base destruction with stack vtable this-adjust fix-ups, written out by hand.
extern "C" void cSpeechManager_destroy(char* self, int flags)
{
    *(void***)(self + 0x1BC) = D_00483870;
    *(const sBmonVtblA0AE8**)(*(char**)(**(char***)self + 0x1D8) + 4) = &D_004838A0;
    *(void***)(**(char***)self + 0xAB0) = D_00483B48;
    *(const sBmonVtblB0AE8**)(**(char***)self + 0x1D4) = &D_004838C0;
    if (flags == 0) {
        sBmonVtblA0AE8 t1 = D_004838A0;
        *(sBmonVtblA0AE8**)(*(char**)(**(char***)self + 0x1D8) + 4) = &t1;
        char* base1 = *(char**)(**(char***)self + 0x1D8) - 0x1C0;
        int d1 = self - base1;
        t1.e[1].delta = D_004838A0.e[1].delta + d1;
        sBmonVtblB0AE8 t2 = D_004838C0;
        *(sBmonVtblB0AE8**)(**(char***)self + 0x1D4) = &t2;
        char* base2 = **(char***)self - 0x1C8;
        int d2 = self - base2;
        t2.e[1].delta = D_004838C0.e[1].delta + d2;
    }
    if (*(void**)(self + 4) != 0) {
        cMemMan_free(*(void**)(self + 4));
    }
    D_004A37B4 = 0;
    if (flags & 2) {
        cStreamSys_destroy(*(void**)self, 0);
        cBankManager_destroy(**(void***)self, 0);
        func_002ADEE8(*(void**)(**(char***)self + 0x1D8), 0);
    }
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sBankSlots;
extern "C" void cSpeechInstance_update(void*, int);
extern "C" void cSpeechManager_tickRequests(sBankSlots*);

extern "C" void cSpeechManager_update(void* self)
{
    for (int i = 0; i < 2; i++) {
        void* p = (*(void***)((char*)self + 0x4))[i];
        if (p != 0) {
            cSpeechInstance_update(p, i);
        }
    }
    cSpeechManager_tickRequests((sBankSlots*)self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int func_003D6778(int a, int b, int c);
// PORT: the unit defines cSoundManager_rand() with no args; this caller passes one.
int cSoundManager_rand_a(int seed) __asm__("cSoundManager_rand");
extern "C" void bxLogPrint(const char* fmt, ...);
extern "C" void func_003D6840(void* fn, int seed, int buf);
extern "C" int func_003D6C58(int n);
extern "C" void* func_00252FA0(void* a0, int a1, int a2);
extern "C" void func_003D6C60(int n, void* p);
extern "C" void* func_003D6768();
extern "C" void cSpeechManager_eventCallback();
extern "C" int func_003E4E98();
extern char D_00483390[];
extern char D_004833A8[];

extern "C" void cSpeechManager_init(void* self)
{
    int buf = func_003D6778(0x5622, 0x10, 1);
    int seed = cSoundManager_rand_a(*(int*)(**(char***)self + 0x1D8));
    bxLogPrint(D_00483390, seed);
    func_003D6840((void*)cSpeechManager_eventCallback, seed, buf);
    int n = func_003D6C58(500);
    void* p = func_00252FA0(D_004833A8, n, 0);
    *(void**)((char*)self + 0x8) = p;
    func_003D6C60(500, p);
    *(void**)((char*)func_003D6768() + 0x8) = (void*)func_003E4E98;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSpeechInstance_destroy(void* p, int mode);
extern "C" void func_003D67F8(void);

extern "C" void cSpeechManager_shutdown(void* self)
{
    for (int i = 0; i < 2; i++) {
        void* p = (*(void***)((char*)self + 0x4))[i];
        if (p != 0) {
            cSpeechInstance_destroy(p, 3);
        }
        (*(void***)((char*)self + 0x4))[i] = 0;
    }
    func_003D67F8();
    MEM_free(*(void**)((char*)self + 0x8));
    *(void**)((char*)self + 0x8) = 0;
}

//100%
extern "C" int cSpeechInstance_canPlay(void* p);

extern "C" int cSpeechManager_canPlay(void* self, int i)
{
    void* p = (*(void***)((char*)self + 0x4))[i];
    if (p != 0) {
        return cSpeechInstance_canPlay(p);
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cSpeechInstance_cSpeechInstance(void* mem, int i, int a, int b, int c, int d, int e);
extern const char D_004833B8[];

extern "C" void cSpeechManager_createInstance(void* self, int i, int a, int b, int c, int d, int e)
{
    // PORT: pointer arithmetic through int
    void** slot = (void**)(i * 4 + *(int*)((char*)self + 0x4));
    *slot = cSpeechInstance_cSpeechInstance(cMemMan_alloc(0x904, D_004833B8, 0, 0), i, a, b, c, d, e);
}

extern "C" void cSpeechManager_loadInstanceConfig(void* self, int i, int a2)
{
    void* e = (*(void***)((char*)self + 0x4))[i];
    if (e != 0) {
        cSpeechInstance_loadConfig(e, i, a2, 0);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cSpeechInstance_playEvent(void* p, int a1);

extern "C" int cSpeechManager_playEvent(void* self, int a1)
{
    for (int i = 0; i < 2; i++) {
        void* p = (*(void***)((char*)self + 0x4))[i];
        if (p != 0) {
            int r = cSpeechInstance_playEvent(p, a1);
            if (r >= 0) {
                if (*(int*)((char*)self + 0x10) == i) {
                    (*(void (**)(int))((char*)self + 0xC))(r);
                }
                return r;
            }
        }
    }
    return -1;
}

extern "C" void func_002B07E8(void* self, int value);

extern "C" void func_002B0FE8(void* self, int i, int value)
{
    void* e = (*(void***)((char*)self + 0x4))[i];
    if (e != 0) {
        func_002B07E8(e, value);
    }
}

extern "C" void func_002B07F0(void* self, int value);

extern "C" void func_002B1020(void* self, int i, int value)
{
    void* e = (*(void***)((char*)self + 0x4))[i];
    if (e != 0) {
        func_002B07F0(e, value);
    }
}

extern "C" void* func_003D8040(void* p);
extern "C" void cSpeechManager_processEvents(void* self_, int i, int v, int k, int w, float t)
{
    char* self = (char*)self_;
    if ((*(char***)(self + 0x4))[i] == 0) {
        return;
    }
    *(int*)((*(char***)(self + 0x4))[i] + 0x8CC) = v;
    if (0.0f < t) {
        *(float*)((*(char***)(self + 0x4))[i] + 0x8F4) = t;
    }
    *(int*)((*(char***)(self + 0x4))[i] + 0x8D0) = w;
    if (k != 0) {
        *(int*)(self + 0x10) = i;
        *(int*)(self + 0xC) = k;
    }
    func_003D8040((void*)i);
    *(int*)(self + 0xC) = 0;
    *(int*)(self + 0x10) = -1;
    *(float*)((*(char***)(self + 0x4))[i] + 0x8F4) = 0.0f;
    *(int*)((*(char***)(self + 0x4))[i] + 0x8CC) = 0;
    *(int*)((*(char***)(self + 0x4))[i] + 0x8D0) = 0;
}

extern "C" void cSpeechManager_processEvents(void* self, int i, int a, int b, int c, float f);
extern "C" void cSpeechManager_drainEvents(void* self, int i)
{
    int k;
    if ((*(void***)((char*)self + 0x4))[i] != 0) {
        D_004A37BC = 1;
        for (k = 3; k >= 0; k--) {
            cSpeechManager_processEvents(self, i, 0, 0, 0, 0.0f);
        }
        D_004A37BC = 0;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSpeechInstance_stop(void* p);

extern "C" void cSpeechManager_stop(void* self, int i)
{
    void* p = (*(void***)((char*)self + 0x4))[i];
    if (p != 0) {
        cSpeechInstance_stop(p);
    }
}

extern "C" int cSpeechInstance_isPlaying(void* p);

extern "C" int cSpeechManager_isPlaying(void* self, int i)
{
    void* e = (*(void***)((char*)self + 0x4))[i];
    if (e != 0) {
        return cSpeechInstance_isPlaying(e);
    }
    return 0;
}

//100%
extern "C" int cSpeechManager_getStreamId(void* self, int i)
{
    void* e = (*(void***)((char*)self + 0x4))[i];
    if (e != 0) {
        return *(int*)((char*)e + 0x4);
    }
    return -1;
}

extern "C" void func_002AB1A0(void* p);

extern "C" void func_002B1248(void* self)
{
    func_002AB1A0(*(void**)((char*)self + 0x0));
}

struct sBankId_1268 {
    long v;
} __attribute__((packed));
extern char D_004A37E0[];
extern "C" int cStreamSys_getCurrentItem(void* self, int i);
extern "C" void cStreamSys_setGainPtr(void* self, int i, int v);
extern "C" void cSndTimerSys_addTimer(void* p, int a, long b, int c, int d, int e, int f, int g);
// PORT: func_002B1248 takes the message as an ignored second argument here.
extern "C" int func_002B1248_m(void* self, void* m) __asm__("func_002B1248");

//100%
extern "C" int cSpeechManager_onLineStartTimer(void* self_, void* m_)
{
    char* self = (char*)self_;
    char* m = (char*)m_;
    char* e = *(char**)(m + 0x18);
    int st = cStreamSys_getCurrentItem(*(void**)self, cSpeechManager_getStreamId(D_004A37B4, *(int*)e));
    if (st != *(int*)(m + 0x1C)) {
        cSndTimerSys_addTimer(**(char***)D_004A37B4 + 0x1D8, 0xC8, ((sBankId_1268*)D_004A37E0)->v,
                      *(int*)(m + 0x18), *(int*)(m + 0x1C), *(int*)(m + 0x20), 0, 0);
        return 1;
    }
    int v = *(int*)(m + 0x20);
    if (v != -1) {
        char* vt = *(char**)(self + 0x1BC);
        int r = (*(int (**)(void*, int, int, int))(vt + 0x1C))(self + *(short*)(vt + 0x18), *(int*)e, v, *(int*)(e + 0x8D0));
        if (r != 0) {
            cStreamSys_setGainPtr(*(void**)self, *(int*)(e + 0x4), r);
        }
    }
    return func_002B1248_m(self, m);
}

extern char D_004A37D8[];

//100%
extern "C" int cSpeechManager_onLineQueuedTimer(void* self, void* m)
{
    int* e = *(int**)((char*)m + 0x18);
    if (cStreamSys_getState(*(void**)self, e[1]) - 1 > 0) {
        if (cStreamSys_isPlaying(*(void**)self, e[1]) != 0) {
            float f = cStreamSys_getTimeLeft(*(void**)self, e[1]);
            cSndTimerSys_addTimer(**(char***)D_004A37B4 + 0x1D8, (int)f,
                          ((sBankId_1268*)D_004A37D8)->v, (int)e, *(int*)((char*)m + 0x1C), *(int*)((char*)m + 0x20), 0, 0);
            return 1;
        }
        if (cStreamSys_getCurrentItem(*(void**)self, cSpeechManager_getStreamId(D_004A37B4, e[0])) == *(int*)((char*)m + 0x1C)) {
            return cSpeechManager_onLineStartTimer(self, m);
        }
        return 0;
    }
    return cSpeechManager_onLineStartTimer(self, m);
}

//100%
struct sBankSlot0018 {
    int value;
    int timer;
    char pad[0x18];
};

struct sBankSlots {
    char pad[0x18];
    sBankSlot0018 slots[10];
};

extern "C" void cSpeechManager_clearRequests(sBankSlots* self)
{
    for (int i = 9; i >= 0; i--) {
        self->slots[i].value = 0;
    }
}

//100%
struct sBankEntry20 {
    int used;
    int timer;
    int a;
    int b;
    int c;
    int d;
    float f;
    int e;
};

struct sBankEntries {
    char pad[0x18];
    sBankEntry20 entries[10];
};

extern "C" int cSpeechManager_addRequest(sBankEntries* self, int a, int b, int c, int d, int e, int refresh, float f)
{
    int freeIdx = -1;
    int i;
    for (i = 0; i < 10; i++) {
        if (self->entries[i].used != 0) {
            if (self->entries[i].a == a && self->entries[i].b == b) {
                if (refresh == 0) {
                    return 0;
                }
                self->entries[i].timer = 180;
                return 1;
            }
        } else {
            if (freeIdx == -1) {
                freeIdx = i;
            }
        }
    }
    if (freeIdx == -1) {
        return 0;
    }
    self->entries[freeIdx].used = 1;
    self->entries[freeIdx].timer = 180;
    self->entries[freeIdx].a = a;
    self->entries[freeIdx].b = b;
    self->entries[freeIdx].c = c;
    self->entries[freeIdx].d = d;
    self->entries[freeIdx].f = f;
    self->entries[freeIdx].e = e;
    return 1;
}

//100%
class cBMVoice_1520 {
public:
    // vptr at 0; slot N at vtable offset N*8
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual int v04();
    virtual int v05();
    virtual int v06();
    virtual int v07();
    virtual int v08();
};

struct sBMObj_1520 {
    char pad[0x6C0];
    char voice[4];          // 0x6C0, a cBMVoice_1520
    char pad6C4[0x870 - 0x6C4];
    int z;                  // 0x870
};

struct sBMEnt_1520 {
    int used;       // 0x18
    int pad1C;
    int id;         // 0x20
    int key;        // 0x24
    sBMObj_1520* obj;   // 0x28
    int w;          // 0x2C
    float t;        // 0x30
    int k;          // 0x34
};

struct sBMon_1520 {
    int pad0;
    char** slots;           // 0x4
    char pad8[0xC - 0x8];
    int curK;               // 0xC
    int curId;              // 0x10
    char pad14[0x18 - 0x14];
    sBMEnt_1520 ents[10];   // 0x18
};

extern "C" int cSpeechManager_applyRequest(sBMon_1520* self, int id, int key)
{
    for (int j = 0; j < 10; j++) {
        if (self->ents[j].used != 0 && self->ents[j].id == id && self->ents[j].key == key) {
            int v = 0;
            int u = 0;
            int z = -1;
            if (self->ents[j].obj != 0) {
                v = ((cBMVoice_1520*)self->ents[j].obj->voice)->v05();
                u = ((cBMVoice_1520*)self->ents[j].obj->voice)->v08();
                z = self->ents[j].obj->z;
            }
            *(int*)(self->slots[id] + 0x8CC) = v;
            *(int*)(self->slots[id] + 0x8F8) = u;
            *(int*)(self->slots[id] + 0x8FC) = z;
            *(float*)(self->slots[id] + 0x8F4) = self->ents[j].t;
            *(int*)(self->slots[id] + 0x8D0) = self->ents[j].w;
            int k = self->ents[j].k;
            if (k != 0) {
                self->curK = k;
                self->curId = id;
            } else {
                self->curK = 0;
                self->curId = -1;
            }
            return 1;
        }
    }
    return 0;
}

//100%
struct sSlot16A0 {
    int active;     // 0x0
    int pad4;
    int idx;        // 0x8
    int key;        // 0xC
    char pad[0x10];
};

extern "C" void cSpeechManager_removeRequest(void* self, int idx, int key)
{
    sSlot16A0* slots = (sSlot16A0*)((char*)self + 0x18);
    for (int i = 0; i < 10; i++) {
        if (slots[i].active != 0 && slots[i].idx == idx && slots[i].key == key) {
            *(int*)((char*)self + 0xC) = 0;
            *(int*)((char*)self + 0x10) = -1;
            *(int*)((char*)(*(int**)((char*)self + 4))[idx] + 0x8F4) = 0;
            *(int*)((char*)(*(int**)((char*)self + 4))[idx] + 0x8CC) = 0;
            *(int*)((char*)(*(int**)((char*)self + 4))[idx] + 0x8D0) = 0;
            slots[i].active = 0;
        }
    }
}

//100%
extern "C" void cSpeechManager_tickRequests(sBankSlots* self)
{
    for (int i = 0; i < 10; i++) {
        if (self->slots[i].value != 0) {
            if (--self->slots[i].timer <= 0) {
                self->slots[i].value = 0;
            }
        }
    }
}

extern "C" void* cSpeechInstance_flushRequests(int);

//100%
// The index is passed through as cSpeechInstance_flushRequests's second argument.
void* cSpeechManager_flush(void* self, int a1)
{
    return cSpeechInstance_flushRequests_impl((*(void***)((char*)self + 0x4))[a1], (void*)a1);
}

INCLUDE_ASM("sound/bankmonitor", cMusicManager_createStream);

extern void*** D_004A37EC;
extern "C" void cStreamSys_stop(void* self, int i);

extern "C" void cMusicManager_stopStream()
{
    cStreamSys_stop(*D_004A37EC, 2);
}

//100%
extern char D_00483980[];
extern unsigned char D_004A35A8[];

struct cSongConfiguration_cSongConfiguration_sElem20 {
    unsigned char b;
    char pad[0x1F];
};

extern "C" void* cSongConfiguration_cSongConfiguration(void* self)
{
    *(void**)((char*)self + 0xA8) = D_00483980;
    *(int*)((char*)self + 0x40) = 0;
    *(int*)((char*)self + 0x64) = 4;
    *(int*)((char*)self + 0x68) = 2;
    *(int*)((char*)self + 0x6C) = 4;
    *(int*)((char*)self + 0x70) = 8;
    *(int*)((char*)self + 0x74) = 0x10;
    *(int*)((char*)self + 0x78) = 0;
    *(int*)((char*)self + 0x7C) = 0x5A;
    *(int*)((char*)self + 0x80) = 100;
    *(int*)((char*)self + 0x84) = 0x32;
    *(int*)((char*)self + 0x88) = 100;
    *(int*)((char*)self + 0x8C) = 100;
    *(float*)((char*)self + 0x90) = 120.0f;
    *(int*)((char*)self + 0x94) = 1;
    *(int*)((char*)self + 0x98) = -1;
    *(int*)((char*)self + 0x9C) = 0xFFFF;
    *(int*)((char*)self + 0xA0) = -1;
    *(int*)((char*)self + 0xA4) = 1;
    *(unsigned char*)((char*)self + 0x0) = D_004A35A8[0];
    *(unsigned char*)((char*)self + 0x20) = D_004A35A8[0];
    cSongConfiguration_cSongConfiguration_sElem20* p = (cSongConfiguration_cSongConfiguration_sElem20*)((char*)self + 0x44);
    for (int i = 0; i >= 0; i--, p++) {
        p->b = D_004A35A8[0];
    }
    return self;
}

//100%
extern char D_00483980[];

extern "C" void cSongConfiguration_destroy(int* self, int flags)
{
    *(void**)((char*)self + 0xA8) = D_00483980;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cSongInstance_cSongInstance(void* mem, int a0, int a1, int a2, int a3, char a4, int a5, int a6, int a7);
extern const char D_004833E0[];

extern "C" void* cSongInstance_create(int a0, int a1, int a2, int a3, char a4, int a5, int a6, int a7)
{
    return cSongInstance_cSongInstance(cMemMan_alloc(0xC4, D_004833E0, 0, 0), a0, a1, a2, a3, a4, a5, a6, a7);
}

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* bmNew_1C50(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" int func_003D3058(int a, int b);
extern "C" void cMusicManager_loadMpf(void* self, void* name, int sync);
extern "C" void cSongInstance_update(void*, int);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char D_004833F0[];
extern char D_00483408[];
extern char D_00483420[];
extern char D_00483430[];
extern char D_004A3588[];
extern char D_004A3590[];
extern char D_004A36E0[];
extern void*** D_004A37EC;

struct sBankEntry_1C50 {
    unsigned char vol;      // 0x0
    char pad1[0x13];
    unsigned short f14;     // 0x14
    short pad16;
};

struct sBankDef_1C50 {
    char pad00[0x1C];
    volatile int cur;           // 0x1C
    sBankEntry_1C50* entries;   // 0x20
    char pad24[0x14];
    int* vols;                  // 0x38
};

struct sBankMon_1C50 {
    char* snd;                  // 0x0
    sBankEntry_1C50 entry;      // 0x4
    int f1C;                    // 0x1C
    int f20;
    void* buf24;                // 0x24
    void* buf28;                // 0x28
    int f2C;                    // 0x2C
    int f30;                    // 0x30
    int f34;                    // 0x34
    int f38;                    // 0x38
    int f3C;                    // 0x3C
    char f40;                   // 0x40
    int f44;                    // 0x44
    int f48;                    // 0x48
    int f4C;                    // 0x4C
    int f50;                    // 0x50
    int f54;                    // 0x54
    int f58;                    // 0x58
    int f5C;                    // 0x5C
    char name[0x40];            // 0x60
};

#define BM_MIN_1C50(a, b) ((a) < (b) ? (a) : (b))
#define BM_MAX_1C50(a, b) ((a) >= (b) ? (a) : (b))

static inline sBankEntry_1C50* bankCur_1C50(sBankDef_1C50* d)
{
    return &d->entries[d->cur];
}

// PORT: callers declare the first parameter as void*; the body takes the typed object (bound by asm label)
extern "C" void* cSongInstance_cSongInstance_body(sBankMon_1C50* self, int a0, int a1, int a2, int a3, char a4, int a5, int a6, int a7) __asm__("cSongInstance_cSongInstance");

extern "C" void* cSongInstance_cSongInstance_body(sBankMon_1C50* self, int a0, int a1, int a2, int a3, char a4, int a5, int a6, int a7)
{
    char* snd = (char*)a2;
    sBankDef_1C50* def = (sBankDef_1C50*)a3;
    self->f1C = -1;
    self->buf24 = 0;
    self->buf28 = 0;
    self->f2C = 0;
    self->f30 = -1;
    self->f38 = 0;
    self->f34 = a6;
    self->f3C = a5;
    self->f40 = a4;
    self->f48 = 0;
    self->f4C = 0;
    self->f50 = 0;
    self->f54 = 1;
    self->f58 = -1;
    self->f5C = 0;
    self->f44 = bankCur_1C50(def)->f14;
    self->buf24 = bmNew_1C50(0x37000, D_004833F0, 0, 0);
    self->buf28 = bmNew_1C50(func_003D3058(1, 0), D_00483408, 0, 0);
    float scale = (float)*(int*)(snd + 0x88) * 0.01f;
    def->vols[def->cur] = (int)BM_MAX_1C50(BM_MIN_1C50((float)def->vols[def->cur] * scale, 127.0f), 0.0f);
    def->entries[def->cur].vol = BM_MAX_1C50(BM_MIN_1C50(def->vols[def->cur], 127), 0);
    if (*(int*)(snd + 0xA4) == 1) {
        sprintf(self->name, D_004A3588, D_004A3590, D_00483420, a0);
    } else {
        sprintf(self->name, D_004A3588, D_004A3590, D_00483430, a0);
    }
    self->snd = snd;
    self->entry = *bankCur_1C50(def);
    char buf[0x100];
    sprintf(buf, D_004A36E0, self->name, snd);
    cMusicManager_loadMpf(D_004A37EC, buf, a7);
    if (a7 != 0) {
        cSongInstance_update(self, 1);
    }
    return self;
}

//100%
extern "C" void cAsyncSys_cancelRequest(void* self, int i);
extern "C" int func_003D2A68(int id);
void cMemMan_free(void*);
void operator_delete(int* ptr);
extern void*** D_004A37EC;

extern "C" void cSongInstance_destroy(void* self, int flags)
{
    cAsyncSys_cancelRequest(**D_004A37EC, *(int*)((char*)self + 0x34));
    func_003D2A68(0x11000001);
    if (*(int*)(*(char**)self + 0x40) > 0) {
        func_003D2A68(0x11000002);
    }
    if (*(void**)((char*)self + 0x24) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x24));
    }
    if (*(void**)((char*)self + 0x28) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x28));
    }
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern "C" int func_002B2488(void* self);
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" void func_003B7FB8(int h, int v);
extern "C" void func_003D1038(int cmd, int v);

extern "C" void cSongInstance_pause(void* self)
{
    func_003B58A0();
    int h = func_002B2488(self);
    if (h >= 0) {
        func_003B7FB8(h, 0);
    }
    func_003B58D8();
    func_003D1038(0x11000002, 1);
}

//100%
extern "C" int func_002B2488(void* self);
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" void func_003B7FB8(int h, int v);
extern "C" void func_003D1038(int cmd, int v);

extern "C" void cSongInstance_resume(void* self)
{
    func_003B58A0();
    int h = func_002B2488(self);
    if (h >= 0) {
        func_003B7FB8(h, 0x1000);
    }
    func_003B58D8();
    func_003D1038(0x11000002, 0);
}

//100%
extern "C" void func_003D16F0(int id, short v);

extern "C" void cSongInstance_sendEvent(void* self, int v, int force)
{
    if (*(int*)((char*)self + 0x5C) != 0 && force == 0) {
        return;
    }
    if (*(int*)((char*)self + 0x2C) != 0) {
        func_003D16F0(-1, v);
    } else if (*(int*)((char*)self + 0x30) == -1) {
        *(int*)((char*)self + 0x30) = v;
    }
}

extern "C" void func_003D0D70(unsigned int);

//100%
extern "C" void cSongInstance_setIntensity()
{
    func_003D0D70(0x11000001U);
}

extern "C" void func_003D15C8(unsigned int);

extern "C" void func_002B2140()
{
    func_003D15C8(0x11000001U);
}

//100%
extern "C" int func_002B2488(void* self);
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" void func_003B80A0(int h, int v);

extern "C" void cSongInstance_setLowpass(void* self, int v)
{
    if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    if (v < 0) {
        v = 0;
    }
    if (v != *(int*)((char*)self + 0x44)) {
        func_003B58A0();
        int h = func_002B2488(self);
        if (h >= 0) {
            *(int*)((char*)self + 0x44) = v;
            func_003B80A0(h, v);
        }
        func_003B58D8();
    }
}

//100%
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void cSongInstance_sendEvent(void* mon, int a1, int a2);
extern "C" void cSongInstance_setLowpass(void* self, int v);
extern "C" int func_002B2488(void* self);
extern "C" int cMusicManager_isMpfLoaded(void* self, int force);
int cMusicManager_getMpfData(void* self);
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" void func_003B7E70(int h, int v);
extern "C" void func_003D2350(int a);
extern "C" int func_003D25F0(int id, char* name, int a2, void* a3, int a4, int a5, void* buf, int size);
extern void*** D_004A37EC;
extern char D_004A36E0[];
extern float D_004A3508;

struct sBmStrm_2B21E0 { char pad[0x2C]; int f2C; };

// PORT: g++ `<?` / `>?` (min/max) operators.
extern "C" void cSongInstance_update(void* mon, int force)
{
    char* self = (char*)mon;
    if (*(int*)(self + 0x2C) == 0)
    {
        if (cMusicManager_isMpfLoaded(D_004A37EC, force) == 0)
            return;
        ((sBmStrm_2B21E0*)self)->f2C = 1;
        func_003D2350(cMusicManager_getMpfData(D_004A37EC));
        char buf[256];
        sprintf(buf, D_004A36E0, self + 0x60, *(char**)self + 0x20);
        *(int*)(self + 0x1C) = func_003D25F0(0x11000001, buf, 500, self + 4, 2, 150, *(void**)(self + 0x24), 0x37000);
        if (*(int*)(*(char**)self + 0x40) > 0)
        {
            sprintf(buf, D_004A36E0, self + 0x60, *(char**)self + 0x44);
            *(int*)(self + 0x20) = func_003D25F0(0x11000002, buf, 10, self + 4, 1, 0, *(void**)(self + 0x28), 0x6A400);
        }
        if (*(int*)(self + 0x30) != -1)
        {
            cSongInstance_sendEvent(self, *(int*)(self + 0x30), 1);
            *(int*)(self + 0x30) = -1;
        }
        return;
    }
    cSongInstance_setLowpass(self, *(int*)(*(char**)self + 0x9C));
    if (*(int*)(self + 0x48) != 0)
        return;
    if (*(int*)(self + 0x54) == 0)
        return;
    float v;
    float* p = *(float**)(self + 0x3C);
    if (p)
        v = (float)*(signed char*)(self + 0x40) * 0.009999999776482582f * (float)*(int*)(*(char**)self + 0x88) * *p;
    else
        v = (float)*(signed char*)(self + 0x40) * 0.009999999776482582f * (float)*(int*)(*(char**)self + 0x88);
    v *= D_004A3508;
    func_003B58A0();
    int h = func_002B2488(self);
    if (h >= 0)
    {
        signed char vol = (int)((v <? 127.0f) >? 0.0f);
        func_003B7E70(h, vol);
    }
    func_003B58D8();
}

//100%
extern "C" void func_003D5508(int cmd, int v);

extern "C" void cSongInstance_setLoopLevel(void* self, signed char v)
{
    if (*(int*)((char*)self + 0x54) != 0) {
        func_003D5508(0x11000002, v);
    }
}

//100%
extern "C" int func_002B2488(void* self);
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" void func_003B7EB0(int h, int v, int c);

extern "C" void cSongInstance_fadeOut(void* self, float t)
{
    func_003B58A0();
    int h = func_002B2488(self);
    if (h >= 0) {
        func_003B7EB0(h, (int)(t * 1000.0f), 0);
    }
    func_003B58D8();
    *(int*)((char*)self + 0x48) = 1;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int func_003D3030(int id);

extern "C" int func_002B2488(void* self)
{
    int idx = func_003D3030(0x11000001);
    if (idx < 0) {
        return -1;
    }
    // PORT: PATHX_getPlayer returns a pointer held in int
    return *(int*)PATHX_getPlayer(idx);
}

//100%
// PORT: cSoundManager_rand is defined () but this caller passes the monitor.
unsigned int cSoundManager_rand_p(void* p) __asm__("cSoundManager_rand");
extern void* D_004A377C;

extern "C" int cSongInstance_pickLoopBank(void* p)
{
    return cSoundManager_rand_p(D_004A377C) % *(unsigned int*)(*(char**)p + 0x40);
}

extern "C" int cSongInstance_pickPhraseOffset(void* self)
{
    unsigned int r = cSoundManager_rand_p(D_004A377C);
    void* p = *(void**)self;
    return (r % (*(unsigned int*)((char*)p + 0x6C) - 1)) * *(int*)((char*)p + 0x74);
}

extern "C" void func_003D11B8(unsigned int id, void* out);

extern "C" int cSongInstance_getStatus()
{
    int info[0xC];
    func_003D11B8(0x11000001U, info);
    return info[9];
}

//100%
extern "C" int func_002B2488(void* self);
extern "C" int func_003B7B48(int h, void* out);

// PORT: returns int; a later caller in this unit declares it void(void*, void*)
int cSongInstance_getStreamInfo_impl(void* self, void* out) __asm__("cSongInstance_getStreamInfo");

int cSongInstance_getStreamInfo_impl(void* self, void* out)
{
    return func_002B2488(self) < 0 ? -1 : func_003B7B48(func_002B2488(self), out);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSongInstance_getStreamInfo(void* self, void* out);
extern "C" void func_003B7C40(int h, int v);

struct sBmInfo {
    int a;
    int handle;
    int c;
    int d;
};

extern "C" void cSongInstance_getItemStatus(void* self, int v)
{
    sBmInfo info;
    cSongInstance_getStreamInfo(self, &info);
    func_003B7C40(info.handle, v);
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
// The unit declares cSongInstance_getItemStatus(void*, int); its second arg is really an out pointer.
void cSongInstance_getItemStatus_out(void* self, void* out) __asm__("cSongInstance_getItemStatus");

struct cSongInstance_getPlayPosMs_sInfo {
    int type;
    int value;
    int c;
    int d;
};

extern "C" float cSongInstance_getPlayPosMs(void* self)
{
    cSongInstance_getPlayPosMs_sInfo info;
    cSongInstance_getItemStatus_out(self, &info);
    if (info.type == 2) {
        return (float)info.value;
    }
    return 0.0f;
}

extern "C" float cSongInstance_getBarMs(void* self);

extern "C" float func_002B2640(void* self)
{
    cSongInstance_getPlayPosMs_sInfo info;
    cSongInstance_getItemStatus_out(self, &info);
    if (info.type == 2) {
        return (float)info.c;
    }
    return cSongInstance_getBarMs(self);
}

//100%
extern "C" float cSongInstance_getBeatMs(void* self)
{
    void* p = *(void**)self;
    return (60.0f / *(float*)((char*)p + 0x90)) * 1000.0f;
}

extern "C" float cSongInstance_getBarMs(void* self)
{
    float f = cSongInstance_getBeatMs(self);
    void* p = *(void**)self;
    return f * (float)*(int*)((char*)p + 0x64) * (float)*(int*)((char*)p + 0x68);
}

extern "C" float func_002B26F8(void* self)
{
    return func_002B2640(self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" float cSongInstance_getPlayPosMs(void* self);
extern "C" float func_0040D8D0(float x, float y);

extern "C" float cSongInstance_getTimeToNextBeat(void* self)
{
    float a = cSongInstance_getBeatMs(self);
    float b = cSongInstance_getPlayPosMs(self);
    return a - func_0040D8D0(b, cSongInstance_getBeatMs(self));
}

extern "C" int cSongInstance_getBeatIndex(void* self)
{
    float a = cSongInstance_getPlayPosMs(self);
    return (int)(a / cSongInstance_getBeatMs(self));
}

extern "C" int func_002B9F88_i(void* bm, int idx) __asm__("func_002B9F88");
extern "C" int func_003B65D0(int p);

// inlined copy of func_002B9F08 (bx/seg_1BA100.cpp)
static inline int bmIsReady_2B27C0(void* bm, int idx)
{
    int r = 0;
    func_003B58A0();
    bool ok = *(int*)((char*)(*(int*)((char*)bm + 0xACC)) + idx * 0x60) != 1;
    if (!ok) {
        r = func_003B65D0(func_002B9F88_i(bm, idx)) == 1;
    }
    func_003B58D8();
    return r;
}

extern "C" int cSongInstance_isLoopBankReady(void* m, void* bm)
{
    if (*(int*)((char*)m + 0x4C) != 0 || bmIsReady_2B27C0(bm, *(int*)((char*)m + 0x34))) {
        return 1;
    }
    return 0;
}

//100%
struct sBMVec16 {
    int x;
    int y;
    int z;
    int w;
};

struct sBMTrack {
    char pad0[0x1F4];
    int cur;
    char pad1F8[0x248 - 0x1F8];
    sBMVec16* vecs;
};

struct sBMSrc {
    char pad0[0x78];
    int a;
    int b;
    int c;
};

extern "C" void func_002B2850(sBMSrc** src, sBMTrack*** dst)
{
    (**dst)->vecs[(**dst)->cur].y = (*src)->a;
    (**dst)->vecs[(**dst)->cur].z = (*src)->b;
    (**dst)->vecs[(**dst)->cur].x = (*src)->c;
}

INCLUDE_ASM("sound/bankmonitor", cMusicManager_cMusicManager);

//100%
void cMemMan_free(void*);
void operator_delete(int* ptr);
extern "C" void cBankManager_destroy(void* self, int flags);
extern "C" void cStreamSys_destroy(void* self, int flags);
extern "C" void func_002ADEE8(void* self, int flags);
extern "C" void cSongInstance_destroy(void* self, int flags);
extern void*** D_004A37EC;
extern void* D_004838F8[];
extern void* D_00483B48[];

struct sBmonVEntry3398 {
    short delta;
    short index;
    void* fn;
};
struct sBmonVtblA3398 {
    sBmonVEntry3398 e[4];
} __attribute__((aligned(8)));
struct sBmonVtblB3398 {
    sBmonVEntry3398 e[7];
} __attribute__((aligned(8)));
extern const sBmonVtblA3398 D_00483928;
extern const sBmonVtblB3398 D_00483948;

struct sBmonVcall3398 { short delta; short index; void (*fn)(void*, int); };

// PORT: g++ 2.95 virtual-base destruction with stack vtable this-adjust fix-ups, written out by hand.
extern "C" void cMusicManager_destroy(char* self, int flags)
{
    *(void***)(self + 0x5440) = D_004838F8;
    *(const sBmonVtblA3398**)(*(char**)(**(char***)self + 0x1D8) + 4) = &D_00483928;
    *(void***)(**(char***)self + 0xAB0) = D_00483B48;
    *(const sBmonVtblB3398**)(**(char***)self + 0x1D4) = &D_00483948;
    if (flags == 0) {
        sBmonVtblA3398 t1 = D_00483928;
        *(sBmonVtblA3398**)(*(char**)(**(char***)self + 0x1D8) + 4) = &t1;
        char* base1 = *(char**)(**(char***)self + 0x1D8) - 0x5448;
        int d1 = self - base1;
        t1.e[1].delta = D_00483928.e[1].delta + d1;
        sBmonVtblB3398 t2 = D_00483948;
        *(sBmonVtblB3398**)(**(char***)self + 0x1D4) = &t2;
        char* base2 = **(char***)self - 0x5450;
        int d2 = self - base2;
        t2.e[1].delta = D_00483948.e[1].delta + d2;
    }
    for (int i = 0; i < *(int*)(self + 0x3E4); i++) {
        char* o = ((char**)(self + 4))[i];
        if (o != 0) {
            sBmonVcall3398* e = &(*(sBmonVcall3398**)(o + 0xA8))[1];
            e->fn(o + e->delta, 3);
        }
    }
    if (*(void**)(self + 0x5434) != 0) {
        cMemMan_free(*(void**)(self + 0x5434));
    }
    if (*(void**)(self + 0x408) != 0) {
        cSongInstance_destroy(*(void**)(self + 0x408), 3);
    }
    D_004A37EC = 0;
    if (flags & 2) {
        cStreamSys_destroy(*(void**)self, 0);
        cBankManager_destroy(**(void***)self, 0);
        func_002ADEE8(*(void**)(**(char***)self + 0x1D8), 0);
    }
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern "C" void cMusicManager_startSong(void* self, int a1, int a2, int a3);

struct sBmEnt35A0 {
    signed char b0;
    char pad1[3];
    int f4[5];
};

struct sBmPair35A0 {
    int a;
    int b;
};

struct sBmV16_35A0 {
    int f0;
    int f4;
    int f8;
    int fC;
};

struct sBmSub35A0 {
    int f0;
    sBmEnt35A0 cfg;         // 0x04
    volatile int cur;       // 0x1C (target re-reads it after every store and twice back-to-back: volatile)
    sBmEnt35A0* ents;       // 0x20
    int arr24[4];           // 0x24
    int* p34;               // 0x34
    int* p38;               // 0x38
    int* p3C;               // 0x3C
    sBmPair35A0 arr40[4];   // 0x40
    int* p60;               // 0x60
    int* p64;               // 0x64
    int* p68;               // 0x68
    int* p6C;               // 0x6C
    sBmV16_35A0* p70;       // 0x70
    int* p74;               // 0x74
    int* p78;               // 0x78
    int* p7C;               // 0x7C
    int* p80;               // 0x80
    int* p84;               // 0x84
};

struct sBmTrack35A0 {
    char pad0[0x1D8];
    sBmSub35A0 sub;         // 0x1D8
};

extern "C" void cMusicManager_playSong(sBmTrack35A0*** self, int a1, int a2, int a3, int a4)
{
    sBmTrack35A0* t = **self;
    sBmSub35A0* s = &t->sub;
    t->sub.cur++;
    s->ents[t->sub.cur] = s->cfg;
    t->sub.arr24[t->sub.cur] = 0;
    s->p34[t->sub.cur] = 0;
    s->p38[t->sub.cur] = s->ents[t->sub.cur].b0;
    s->p3C[t->sub.cur] = 0;
    func_00416210((char*)s + t->sub.cur * 8 + 0x40, 0, 8);
    s->p60[t->sub.cur] = 0;
    s->p64[t->sub.cur] = 0;
    s->p68[t->sub.cur] = 0;
    s->p6C[t->sub.cur] = 0;
    s->p70[t->sub.cur].f4 = 0;
    s->p70[t->sub.cur].f0 = 100;
    s->p70[t->sub.cur].f8 = 90;
    s->p70[t->sub.cur].fC = 50;
    s->p74[t->sub.cur] = 0;
    s->p80[t->sub.cur] = 0;
    s->p84[t->sub.cur] = 0;
    s->p78[t->sub.cur] = 0x7F;
    s->p7C[t->sub.cur] = 1;
    sBmTrack35A0* t2 = **self;
    t2->sub.p3C[t2->sub.cur] = a3;
    cMusicManager_startSong(self, a1, a2, a4);
    sBmTrack35A0* t3 = **self;
    t3->sub.cur--;
}

//100%
extern "C" void cMusicManager_stopSong(char* self);
extern "C" void cMusicManager_loadLoopBank(void* self);
extern "C" int func_004165A8(const char* a, const char* b);

extern "C" void cMusicManager_startSong(void* selfp, int a1, int a2, int a3)
{
    char* self = (char*)selfp;
    cMusicManager_stopSong(self);
    sBmTrack35A0* t = **(sBmTrack35A0***)self;
    sBmSub35A0* s = &t->sub;
    signed char vol = *(signed char*)&s->p38[s->cur];
    float* scale = (float*)s->p3C[s->cur];
    if (scale != 0) {
        float f = (float)vol * *scale;
        f = f <? 127.0f;
        f = f >? 0.0f;
        s->p38[t->sub.cur] = (signed char)(int)f;
        sBmEnt35A0* e = (sBmEnt35A0*)(t->sub.cur * 0x18 + (int)s->ents);
        // Clamped again to 0..127 with each read going back through the volatile cur index.
        e->b0 = ((s->p38[s->cur] < 127 ? s->p38[s->cur] : 127) < 0) ? 0 : (s->p38[s->cur] < 127 ? s->p38[s->cur] : 127);
    }
    if (a1 != 0) {
        int i;
        for (i = *(int*)(self + 0x3E4) - 1; i >= 0; i--) {
            if (func_004165A8(self + 0x124 + i * 11, (const char*)a1) == 0) break;
        }
        *(int*)(self + 0x3F0) = i;
        char* head = self + 0x104;
        int* q = (int*)(self + 4);
        q += i;
        *(void**)(self + 0x408) = cSongInstance_create((int)head, a1, *q, (int)&(**(sBmTrack35A0***)self)->sub, vol, (int)scale, a2, a3);
    } else {
        int i = *(int*)(self + 0x3F0);
        char* q = self;
        q += i * 4;
        *(void**)(self + 0x408) = cSongInstance_create((int)(self + 0x104), (int)(self + 0x124 + i * 11), *(int*)(q + 4), (int)&(**(sBmTrack35A0***)self)->sub, vol, (int)scale, a2, a3);
    }
    cMusicManager_loadLoopBank(self);
    *(int*)(self + 0x41C) = -1;
    *(int*)(self + 0x418) = 1;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSongInstance_pause(void*);

extern "C" void func_002B3A70(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        cSongInstance_pause(p);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSongInstance_resume(void*);

extern "C" void func_002B3A98(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        cSongInstance_resume(p);
    }
}

//100%
struct sBankId_3AC0 {
    long v;
} __attribute__((packed));
extern char D_004A3838[];
extern char D_004A3840[];
extern char D_004A3848[];
void cSndTimerSys_removeTimersByKey_3AC0(void* bm, long id) __asm__("cSndTimerSys_removeTimersByKey");
extern "C" void cBankManager_unloadBank(void* self, int i);

extern "C" void cMusicManager_stopSong(char* self)
{
    cSndTimerSys_removeTimersByKey_3AC0(**(char***)self + 0x1D8, ((sBankId_3AC0*)D_004A3838)->v);
    cSndTimerSys_removeTimersByKey_3AC0(**(char***)self + 0x1D8, ((sBankId_3AC0*)D_004A3840)->v);
    cSndTimerSys_removeTimersByKey_3AC0(**(char***)self + 0x1D8, ((sBankId_3AC0*)D_004A3848)->v);
    if (*(void**)(self + 0x408) != 0) {
        cAsyncSys_cancelRequest(**(void***)self, *(int*)(*(char**)(self + 0x408) + 0x34));
        cBankManager_unloadBank(**(void***)self, *(int*)(*(char**)(self + 0x408) + 0x34));
    }
    func_002B3A98(self);
    *(int*)(self + 0x418) = 0;
    if (*(void**)(self + 0x408) != 0) {
        cSongInstance_destroy(*(void**)(self + 0x408), 3);
    }
    *(void**)(self + 0x408) = 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSongInstance_sendEvent(void* mon, int a1, int a2);

extern "C" void cMusicManager_sendEventForced(void* self, int a1)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* m = *(void**)((char*)self + 0x408);
        if (m != 0) {
            cSongInstance_sendEvent(m, a1, 0);
        }
    }
}

//100%
struct sBankMonVEntry {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" int cMusicManager_sendEvent(void* self, int v)
{
    int r = 0;
    if (*(int*)((char*)self + 0x418) != 0 && v != *(int*)((char*)self + 0x41C)) {
        sBankMonVEntry* vt = *(sBankMonVEntry**)((char*)self + 0x5440);
        vt[3].fn((char*)self + vt[3].delta);
        *(int*)((char*)self + 0x41C) = v;
        r = 1;
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: called with the monitor as `this`; the unit declares cSongInstance_setIntensity() with no args
void cSongInstance_setIntensity_m(void* mon) __asm__("cSongInstance_setIntensity");

extern "C" void cMusicManager_setIntensity(void* self)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* m = *(void**)((char*)self + 0x408);
        if (m != 0) {
            cSongInstance_setIntensity_m(m);
        }
    }
}

void func_002B2140_p(void* p) __asm__("func_002B2140");

extern "C" void func_002B3C60(void* self)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* p = *(void**)((char*)self + 0x408);
        if (p != 0) {
            func_002B2140_p(p);
        }
    }
}

//100%
extern "C" void cMusicManager_setPathVolume(void* self, signed char a1)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* p = *(void**)((char*)self + 0x408);
        if (p != 0) {
            *(signed char*)((char*)p + 0x40) = a1;
        }
    }
}

//100%
extern "C" void cMusicManager_setVolumeControl(void* self, int a1)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        *(int*)((char*)p + 0x54) = a1;
    }
}

extern "C" void cMusicManager_setLowpass(void* self, int v)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* p = *(void**)((char*)self + 0x408);
        if (p != 0) {
            cSongInstance_setLowpass(p, v);
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSongInstance_setLoopLevel(void* self, signed char v);

extern "C" void cMusicManager_setLoopLevel(void* self, signed char v)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* m = *(void**)((char*)self + 0x408);
        if (m != 0) {
            cSongInstance_setLoopLevel(m, v);
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSongInstance_fadeOut(void* mon, float v);

extern "C" void cMusicManager_fadeOut(void* self, float v)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* m = *(void**)((char*)self + 0x408);
        if (m != 0) {
            cSongInstance_fadeOut(m, v);
        }
    }
}

//100%
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t/uint64_t off-PS2.
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sPacked8_3D80 { long v; } __attribute__((packed));
extern const sPacked8_3D80 D_004A3850_3D80[] __asm__("D_004A3850");
extern void cSndTimerSys_addTimer_3D80(int a, int b, long t, int c, int d, int e, int f, int g) __asm__("cSndTimerSys_addTimer");

extern "C" void cMusicManager_rampPathVolume(void* self, signed char target, float duration)
{
    signed char cur;
    void* voice = *(void**)((char*)self + 0x408);
    if (voice != 0 && target != (cur = *(signed char*)((char*)voice + 0x40))) {
        int steps = (target - cur) / 25;
        *(int*)((char*)self + 0x414) = target;
        *(float*)((char*)self + 0x410) = (float)cur;
        *(float*)((char*)self + 0x40C) = (float)steps / duration;
        cSndTimerSys_addTimer_3D80(**(int**)self + 0x1D8, 0x28, D_004A3850_3D80[0].v, 0, 0, 0, 0, 0);
    }
}

//100%
extern "C" int cMusicManager_onPathVolumeRamp(void* self)
{
    float step = *(float*)((char*)self + 0x40C);
    float cur = *(float*)((char*)self + 0x410) + step;
    *(float*)((char*)self + 0x410) = cur;
    if ((step > 0.0f && cur < (float)*(int*)((char*)self + 0x414))
        || (step < 0.0f && cur > (float)*(int*)((char*)self + 0x414))) {
        *(signed char*)((char*)*(void**)((char*)self + 0x408) + 0x40) = (signed char)(int)*(float*)((char*)self + 0x410);
        return 0;
    }
    signed char t = *(int*)((char*)self + 0x414);
    *(signed char*)((char*)*(void**)((char*)self + 0x408) + 0x40) = t;
    return 1;
}

//100%
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t/uint64_t off-PS2.
extern "C" void cMusicManager_clearPlaylist(void* self)
{
    *(ulong*)((char*)self + 0x3f8) = 0;
    *(int*)((char*)self + 0x3e8) = 0;
    for (int i = 4; i >= 0; i--) {
        ((int*)((char*)self + 0x920))[i] = 0;
    }
}

//100%
extern "C" int func_0041AD80(const char* a, const char* b);

// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t/uint64_t off-PS2.
struct sBankMonFind {
    char pad0[0x124];
    char names[64][11];         // 0x124
    int nnames;                 // 0x3E4
    int count;                  // 0x3E8
    char pad3EC[0x3F8 - 0x3EC];
    ulong mask;                 // 0x3F8
    char pad400[0x420 - 0x400];
    int grid[64][5];            // 0x420
    int totals[5];              // 0x920
};

extern "C" void cMusicManager_addSongByName(sBankMonFind* self, const char* name)
{
    if (self->count < 64) {
        for (int i = 0; i < self->nnames; i++) {
            if (func_0041AD80(self->names[i], name) != 0) {
                self->mask |= (ulong)1 << i;
                self->count++;
                for (int j = 0; j < 5; j++) {
                    if (self->grid[i][j] != 0) {
                        self->totals[j]++;
                    }
                }
                return;
            }
        }
    }
}

//100%
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t/uint64_t off-PS2.
struct sBankMonUse {
    char pad0[0x3E8];
    int count;                  // 0x3E8
    char pad3EC[0x3F8 - 0x3EC];
    ulong mask;                 // 0x3F8
    char pad400[0x420 - 0x400];
    int grid[64][5];            // 0x420
    int totals[5];              // 0x920
};

extern "C" void cMusicManager_addSongByIndex(sBankMonUse* self, int idx)
{
    if (self->count < 64) {
        self->count++;
        self->mask |= (ulong)1 << idx;
        for (int i = 0; i < 5; i++) {
            if (self->grid[idx][i] != 0) {
                self->totals[i]++;
            }
        }
    }
}

//100%
void func_002B4060(void* self)
{
}

extern "C" long cMusicManager_getPlaylistMask(void* self)
{
    return *(long*)((char*)self + 0x3F8);
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: 64-bit `long` mask (8 bytes on EE); use uint64_t off-PS2.
struct sBankMonUse;
extern "C" void cMusicManager_clearPlaylist(void* self);
extern "C" void cMusicManager_addSongByIndex(sBankMonUse* self, int idx);
void func_002B4060(void* self);

extern "C" void cMusicManager_setPlaylist(void* self, ulong mask)
{
    cMusicManager_clearPlaylist(self);
    for (int i = 0; i < *(int*)((char*)self + 0x3EC); i++) {
        int bit = (mask >> i) & 1;
        if (bit) {
            cMusicManager_addSongByIndex((sBankMonUse*)self, i);
        }
    }
    func_002B4060(self);
}

//100%
struct sBankEntry64 {
    char data[0x64];
};

struct sBankMonitor934 {
    char pad[0x3f0];
    int current;                // 0x3F0
    char pad2[0x934 - 0x3f4];
    sBankEntry64 a[64];         // 0x934
    sBankEntry64 b[64];         // 0x2234
    sBankEntry64 c[64];         // 0x3B34
};

extern "C" sBankEntry64* func_002B40F0(sBankMonitor934* self, int i)
{
    if (i < 0) {
        i = self->current;
        if (i < 0) {
            return 0;
        }
    }
    return &self->a[i];
}

//100%
extern "C" sBankEntry64* func_002B4120(sBankMonitor934* self, int i)
{
    if (i < 0) {
        i = self->current;
        if (i < 0) {
            return 0;
        }
    }
    return &self->b[i];
}

//100%
extern "C" sBankEntry64* cMusicManager_getSongAlbum(sBankMonitor934* self, int i)
{
    if (i < 0) {
        i = self->current;
        if (i < 0) {
            return 0;
        }
    }
    return &self->c[i];
}

// cMusicManager_nextSong is defined later in the unit with its own monitor type.
void cMusicManager_nextSong_v(void* self, int a, int b) __asm__("cMusicManager_nextSong");

extern "C" void cMusicManager_resetSongIndex(void* self, int n)
{
    *(int*)((char*)self + 0x3F0) = -1;
    cMusicManager_nextSong_v(self, 0, 0);
    for (int i = 0; i < n; i++) {
        cMusicManager_nextSong_v(self, 0, 0);
    }
}

//100%
struct cMusicManager_prevSong_sMon {
    char pad[0x3E4];
    int count;              // 0x3E4
    char pad3E8[0x3F0 - 0x3E8];
    int current;            // 0x3F0
    char pad3F4[0x3F8 - 0x3F4];
    unsigned long mask;     // 0x3F8 (PORT: 64-bit long)
    char pad400[0x420 - 0x400];
    int table[64][5];       // 0x420
    int counts[5];          // 0x920
};

extern "C" void cMusicManager_prevSong(cMusicManager_prevSong_sMon* self, int filter, int kind)
{
    if (filter == 0 || self->counts[kind] == 0) {
        do {
            if (--self->current < 0) {
                self->current = self->count - 1;
            }
        } while (!((self->mask >> self->current) & 1));
    } else {
        do {
            if (--self->current < 0) {
                self->current = self->count - 1;
            }
        } while (!((self->mask >> self->current) & 1) || self->table[self->current][kind] == 0);
    }
}

//100%
struct cMusicManager_nextSong_sMon {
    char pad[0x3E4];
    int count;              // 0x3E4
    char pad3E8[0x3F0 - 0x3E8];
    int current;            // 0x3F0
    char pad3F4[0x3F8 - 0x3F4];
    unsigned long mask;     // 0x3F8 (PORT: 64-bit long)
    char pad400[0x420 - 0x400];
    int table[64][5];       // 0x420
    int counts[5];          // 0x920
};

extern "C" void cMusicManager_nextSong(cMusicManager_nextSong_sMon* self, int filter, int kind)
{
    if (filter == 0 || self->counts[kind] == 0) {
        do {
            if (++self->current >= self->count) {
                self->current = 0;
            }
        } while (!((self->mask >> self->current) & 1));
    } else {
        do {
            if (++self->current >= self->count) {
                self->current = 0;
            }
        } while (!((self->mask >> self->current) & 1) || self->table[self->current][kind] == 0);
    }
}

//100%
extern "C" void cSongInstance_update(void*, int);
extern "C" void cMusicManager_attachLoopBank(void*);

extern "C" void cMusicManager_update(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        cSongInstance_update(p, 0);
        if (*(int*)((char*)*(void**)((char*)self + 0x408) + 0x50) != 0) {
            cMusicManager_attachLoopBank(self);
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" int cSongInstance_pickLoopBank(void* p);
extern "C" void cBankManager_loadBankAsync(void* self, int i, void* id, int a3);
extern char D_004A36E0[];

struct sBankMonHdr { char pad[0x40]; int f40; char names[1][0x20]; };

extern "C" void cMusicManager_loadLoopBank(void* self)
{
    char buf[256];
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        int bank = *(int*)((char*)p + 0x34);
        if ((*(sBankMonHdr**)p)->f40 != 0) {
            int n = cSongInstance_pickLoopBank(p);
            void* q = *(void**)((char*)self + 0x408);
            sprintf(buf, D_004A36E0, (char*)q + 0x60, (*(sBankMonHdr**)q)->names[n]);
            cBankManager_loadBankAsync(**(void***)self, bank, buf, 0x100);
            *(int*)((char*)*(void**)((char*)self + 0x408) + 0x38) = 1;
        }
    }
}

//100%
struct sPacked8_4470 { long v; } __attribute__((packed));
extern const sPacked8_4470 D_004A3838_4470[] __asm__("D_004A3838");
extern void cSndTimerSys_addTimer_4470(int a, int b, long t, int c, int d, int e, int f, int g) __asm__("cSndTimerSys_addTimer");

// PORT: 64-bit long sound key, read unaligned from a const table
extern "C" void cMusicManager_startLoopSlices(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0 && *(int*)((char*)p + 0x4C) == 0) {
        *(int*)((char*)p + 0x4C) = 1;
        cSndTimerSys_addTimer_4470(*(int*)(*(int*)self) + 0x1D8, 0, D_004A3838_4470[0].v, 0, 0, 0, 0, 0);
    }
}

// 64-bit bank id stored word-aligned; read with an unaligned 64-bit load and
// passed in a single register.
struct sBankId_44D8 {
    long v;
} __attribute__((packed));
extern char D_004A3838[];
extern char D_004A3840[];
void cSndTimerSys_removeTimersByKey_id(void* bm, long id) __asm__("cSndTimerSys_removeTimersByKey");

extern "C" void cMusicManager_clearLoopsEngaged(void* self);

extern "C" void cMusicManager_stopLoopSlices(void* self)
{
    if (*(void**)((char*)self + 0x408) != 0) {
        cSndTimerSys_removeTimersByKey_id(**(char***)self + 0x1D8, ((sBankId_44D8*)D_004A3838)->v);
        cSndTimerSys_removeTimersByKey_id(**(char***)self + 0x1D8, ((sBankId_44D8*)D_004A3840)->v);
        cMusicManager_clearLoopsEngaged(self);
    }
}

struct sVEntry_2B4540 {
    short delta;
    short index;
    int (*fn)(void*, int);
};

extern "C" int cMusicManager_onSliceTimer(void* self, int a1)
{
    sVEntry_2B4540* vt = *(sVEntry_2B4540**)((char*)self + 0x5440);
    return vt[1].fn((char*)self + vt[1].delta, a1);
}

extern "C" void cSndTimerSys_addTimer(void* p, int a, long b, int c, int d, int e, int f, int g);
extern "C" void cMusicManager_scheduleSlice(void* self, void* m)
{
    char* s = (char*)self;
    if (*(void**)(s + 0x408) != 0) {
        float a = cSongInstance_getBeatMs(m);
        float b = cSongInstance_getTimeToNextBeat(m);
        int c = cSongInstance_getBeatIndex(m) + 1;
        int d = cSongInstance_pickPhraseOffset(m);
        cSndTimerSys_addTimer(**(char***)s + 0x1D8, (int)b, ((sBankId_44D8*)D_004A3840)->v, *(int*)(s + 0x408), d, c, (int)a, 0);
    }
}

//100%
extern "C" void func_003D2DF8(int cmd, int a, int b);

struct sBmStream4620 {
    int state;      // 0x0
    int handle;     // 0x4
    char pad[0x60 - 8];
};

static inline int cMusicManager_attachLoopBank_ready(sBmStream4620* e)
{
    return e->state == 1;
}

// PORT: the unit declares cMusicManager_attachLoopBank as void; it really returns 0/1.
int cMusicManager_attachLoopBank_impl(void* self) __asm__("cMusicManager_attachLoopBank");

int cMusicManager_attachLoopBank_impl(void* self)
{
    int one = 1;
    if (*(char**)((char*)self + 0x408) == 0) return 0;
    *(int*)(*(char**)((char*)self + 0x408) + 0x4C) = one;
    int r = 0;
    char* m = *(char**)((char*)self + 0x408);
    int st = *(int*)(m + 0x38);
    if (st == one) {
        // PORT: pointer arithmetic through int
        sBmStream4620* e = (sBmStream4620*)(*(int*)(m + 0x34) * 0x60 + *(int*)(**(char***)self + 0xACC));
        if (cMusicManager_attachLoopBank_ready(e)) {
            func_003D2DF8(0x11000002, 0, e->handle);
            *(int*)(*(char**)((char*)self + 0x408) + 0x38) = 2;
            r = 1;
        }
    } else if (st == 2) {
        r = one;
    }
    return r;
}

//100%
extern "C" void cMusicManager_setAutoLoops(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        *(int*)((char*)p + 0x50) = 1;
    }
}

//100%
extern "C" void* cMusicManager_areLoopsEngaged(void* self)
{
    void* inner = *(void**)((char*)self + 0x408);
    if (inner == 0) {
        return 0;
    }
    return *(void**)((char*)inner + 0x4C);
}

//100%
extern "C" void cMusicManager_clearLoopsEngaged(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        *(int*)((char*)p + 0x4c) = 0;
    }
}

extern "C" int cMusicManager_getPathVolume(void* self)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p == 0) {
        return 0;
    }
    return *(signed char*)((char*)p + 0x40);
}

extern "C" void cMusicManager_scheduleSlice(void* self, void* m);
extern "C" int cMusicManager_onSliceTick(void* self)
{
    char* m = *(char**)((char*)self + 0x408);
    int st = *(int*)(*(char**)(**(char***)self + 0xACC) + *(int*)(m + 0x34) * 0x60);
    switch (st) {
    case 0:
        return 1;
    case 1:
        cMusicManager_scheduleSlice(self, m);
        return 1;
    case 2:
        return 0;
    }
    return 1;
}

extern "C" int cMusicManager_onLoopBankCheck(void* self)
{
    int idx = *(int*)(*(char**)((char*)self + 0x408) + 0x34);
    void* bm = **(void***)self;
    if (!bmIsReady_2B27C0(bm, idx)) {
        *(int*)(*(char**)((char*)self + 0x408) + 0x4C) = 0;
        return 1;
    }
    return 0;
}

//100%
int cSongInstance_getDuckToLoops(void* self)
{
    return *(int*)((char*)*(void**)self + 0x94);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cMusicManager_getDuckToLoops(void* self)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* m = *(void**)((char*)self + 0x408);
        if (m != 0) {
            return cSongInstance_getDuckToLoops(m);
        }
    }
    return 1;
}

extern "C" int cSongInstance_getSedValue(void* self)
{
    return *(int*)(*(char**)self + 0x98);
}

extern "C" int cSongInstance_getSedValue(void* self);

extern "C" int cMusicManager_getSedValue(void* self)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* p = *(void**)((char*)self + 0x408);
        if (p != 0) {
            return cSongInstance_getSedValue(p);
        }
    }
    return -1;
}

//100%
int cMusicManager_getSelectedSedValue(void* self)
{
    void* p = *(void**)((char*)self + (*(int*)((char*)self + 0x3f0) << 2) + 0x4);
    return *(int*)((char*)p + 0x98);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_003B58A0(void);
extern "C" void func_003B58D8(void);
extern "C" float cSongInstance_getTimeToNextBeat(void* self);

extern "C" float cMusicManager_getTimeToNextBeat(void* self)
{
    if (*(int*)((char*)self + 0x418) == 0) {
        return 0.0f;
    }
    func_003B58A0();
    float r = cSongInstance_getTimeToNextBeat(*(void**)((char*)self + 0x408));
    func_003B58D8();
    return r;
}

//100%
class cMusicManager_previewSong_cObj {
public:
    int unk0;
    void* entries[(0x5440 - 4) / 4];
    // vptr at 0x5440; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03(int a);
};

extern "C" void cMusicManager_previewSong(cMusicManager_previewSong_cObj* self, int i)
{
    int v = *(int*)((char*)self->entries[i] + 0xA0);
    if (v >= 0) {
        self->v03(v);
    }
}

//100%
extern "C" void cMusicManager_setSongId(void* self, int a1)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* p = *(void**)((char*)self + 0x408);
        if (p != 0) {
            *(int*)((char*)p + 0x58) = a1;
        }
    }
}

//100%
extern "C" int cMusicManager_getSongId(void* self)
{
    if (*(int*)((char*)self + 0x418) != 0) {
        void* p = *(void**)((char*)self + 0x408);
        if (p != 0) {
            return *(int*)((char*)p + 0x58);
        }
    }
    return -1;
}

//100%
extern "C" void cMusicManager_setEventLock(void* self, int a1)
{
    void* p = *(void**)((char*)self + 0x408);
    if (p != 0) {
        *(int*)((char*)p + 0x5c) = a1;
    }
}

//100%
extern "C" void func_003DFAF0(void* f);
extern "C" void ASYNCFILE_release(void* f, int a, int b);
extern "C" void* func_003DF748(void* name, void* buf, int size);
extern "C" void func_003E1B68(void* name, void* buf, int size);

extern "C" void cMusicManager_loadMpf(void* self, void* name, int sync)
{
    if (*(void**)((char*)self + 0x5438) != 0) {
        func_003DFAF0(*(void**)((char*)self + 0x5438));
        ASYNCFILE_release(*(void**)((char*)self + 0x5438), 0, 0);
    }
    if (sync == 0) {
        *(void**)((char*)self + 0x5438) = func_003DF748(name, *(void**)((char*)self + 0x5434), 0x6400);
    } else {
        func_003E1B68(name, *(void**)((char*)self + 0x5434), 0x6400);
    }
}

//100%
extern "C" int func_003DF980(void*);

extern "C" int cMusicManager_isMpfLoaded(void* self, int force)
{
    void* p;
    if (force != 0) {
        return 1;
    }
    p = *(void**)((char*)self + 0x5438);
    if (p != 0 && func_003DF980(p) == 1) {
        return 1;
    }
    return 0;
}

//100%
int cMusicManager_getMpfData(void* self)
{
    return *(int*)((char*)self + 0x5434);
}

//100%
// PORT: needs a 64-bit return (ulong); use uint64_t off-PS2.
extern "C" ulong cMusicManager_isSongInPlaylist(void* self)
{
    return (*(ulong*)((char*)self + 0x3f8) >> *(int*)((char*)self + 0x3f0)) & 1;
}

