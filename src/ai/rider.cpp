#include "common.h"
#include "ai/rider.h"

// R5900 128-bit GPR quadword, for functions that copy a 16-byte block via a
// single lq/sq pair instead of word-by-word.
typedef int cQuad128 __attribute__((mode(TI)));

INCLUDE_ASM("ai/rider", cRider_cRider);

//100%
struct sVE_11B978 {
    short delta;
    short index;
    void (*fn)(void*, int);
};
extern "C" void* func_0028B180();
// PORT: cSSXAudio_removeRider__FPv takes (mgr, rider); the mangled name says one void* param.
void cSSXAudio_removeRider__FPv_impl(void* mgr, void* rider) __asm__("cSSXAudio_removeRider__FPv__FPv");
extern "C" void func_002832D8(void* p);
extern "C" void func_00283228(void* p, int flags);
extern "C" void func_0030D540(void* p, int flags);
extern "C" void cRiderSphereTree_destroy(void* p, int flags);
extern "C" void cAirPredictor_destroy(void* p, int flags);
extern "C" void FocusMan_RemoveFocusBox(void* a, void* p);
extern "C" void func_00117290(void* p, int flags);
extern "C" void BoaderShadow_dtor(void* p, int flags);
void operator_delete(int* p);
extern void* D_004A28A8;
extern void* D_00459C18[];
extern char D_00459B90[];
extern void* D_00459BD0[];
extern void* D_00482018[];
extern void* D_00481FD8[];
extern void* D_00459CC8[];

static inline void vdel_11B978(char* o, int off)
{
    sVE_11B978* vt = *(sVE_11B978**)(o + off);
    vt[1].fn(o + vt[1].delta, 3);
}

extern "C" void cRider_destroy(char* self, int flags)
{
    *(void***)(self + 0x6E8) = D_00459BD0;
    *(void**)(self + 0x6D0) = D_00459B90;
    *(void***)(self + 0x6C0) = D_00459C18;
    cSSXAudio_removeRider__FPv_impl(func_0028B180(), self);
    func_002832D8(self + 0x6DC);
    char* o = *(char**)(self + 0x784);
    if (o != 0)
        vdel_11B978(o, 0x58);
    void* p = *(void**)(self + 0x780);
    if (p != 0)
        func_0030D540(p, 3);
    p = *(void**)(self + 0xAA0);
    if (p != 0)
        cRiderSphereTree_destroy(p, 3);
    operator_delete(*(int**)(self + 0xAC0));
    operator_delete(*(int**)(self + 0xABC));
    p = *(void**)(self + 0x788);
    if (p != 0)
        cAirPredictor_destroy(p, 3);
    void* box = *(void**)(self + 0x78C);
    if (box != 0)
        FocusMan_RemoveFocusBox(*(void**)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0xA4), box);
    operator_delete(*(int**)(self + 0x78C));
    p = *(void**)(self + 0x790);
    if (p != 0)
        func_00117290(p, 3);
    operator_delete(*(int**)(self + 0x860));
    operator_delete(*(int**)(self + 0x868));
    operator_delete(*(int**)(self + 0x864));
    o = *(char**)(self + 0x890);
    if (o != 0)
        vdel_11B978(o, 0xC4);
    o = *(char**)(self + 0x88C);
    if (o != 0)
        vdel_11B978(o, 0xA4);
    p = *(void**)(self + 0xAA8);
    if (p != 0)
        BoaderShadow_dtor(p, 3);
    *(void***)(self + 0x6E8) = D_00482018;
    *(void***)(self + 0x6D0) = D_00481FD8;
    func_00283228(self + 0x6DC, 0);
    *(void***)(self + 0x6C0) = D_00459CC8;
    if (flags & 1)
        operator_delete((int*)self);
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_00457960[];
extern void* D_004A28A8;
extern "C" void func_001033B0(void* self, void* box);

struct sRider_addFocusBox
{
    char pad[0x78C];
    void* mFocusBox;
};

extern "C" void cRider_addFocusBox(sRider_addFocusBox* self)
{
    void* box = cMemMan_alloc(0x10, D_00457960, 0, 0);
    self->mFocusBox = box;
    func_001033B0(*(void**)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0xA4), box);
}

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cRiderMetrix_ctor(void* mem);
extern "C" void cRiderMetrix_linkToRider(void* metrix);
extern const char D_00457970[];

//100%
// PORT: cRiderMetrix_linkToRider really takes (metrix, rider); the unit declares one arg.
extern "C" void cRiderMetrix_linkToRider_impl(void* metrix, cRider* rider) __asm__("cRiderMetrix_linkToRider");

void cRider_addRiderMetrix(cRider* self)
{
    void* mem = cMemMan_alloc(0x1CC, D_00457970, 0, 0);
    void* metrix = cRiderMetrix_ctor(mem);
    self->mRiderMetrix = metrix;
    cRiderMetrix_linkToRider_impl(metrix, self);
}

//100%
extern "C" void* cBE_getBE();
void* cBE_getInterface(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBELibrary_getCharacterID(int c);
extern "C" int func_0014A0B0(int c);
// PORT: func_0014BDB8 is declared (void*) but never reads its argument; called here with none
void* func_0014BDB8_noarg() __asm__("func_0014BDB8__FPv");
extern "C" void* func_0014AD50(void* iface, int id);
int func_0014D988(void* tbl, int g);
extern "C" void* func_0014D998(void* tbl, int g);

struct sItem_11BBE8 {
    short a;
    unsigned short flags;
};

struct sDb_11BBE8 {
    char pad0[0x288];
    short* map;                 // 0x288
    char pad28C[0x4];
    sItem_11BBE8 items[1];      // 0x290
};

struct sEnt_11BBE8 {
    char pad0[0x4];
    short item;                 // 0x04
    char pad6[0x32];
};

static inline sItem_11BBE8* lookup_11BBE8(sDb_11BBE8* d, int i)
{
    short k = d->map[i];
    if (k >= 0) {
        return &d->items[k];
    }
    return 0;
}

extern "C" int cRider_collectEquippedItems(void* selfp, char** listp)
{
    char* self = (char*)selfp;
    sEnt_11BBE8** list = (sEnt_11BBE8**)listp;
    int n = 0;
    void* iface = cBE_getInterface(cBE_getBE(), 9);
    int g = cBELibrary_getCharacterID(*(int*)(self + 0x86C));
    int alt = func_0014A0B0(*(int*)(self + 0x86C));
    void* tbl = func_0014BDB8_noarg();
    if (alt) {
        g = alt;
        sEnt_11BBE8* e = (sEnt_11BBE8*)func_0014D998(tbl, g);
        int cnt = func_0014D988(tbl, g);
        for (int i = 0; i < cnt; i++, e++)
            list[n++] = e;
        return n;
    }
    sDb_11BBE8* db = (sDb_11BBE8*)func_0014AD50(iface, *(int*)(self + 0x86C));
    int cnt = func_0014D988(tbl, g);
    sEnt_11BBE8* e = (sEnt_11BBE8*)func_0014D998(tbl, g);
    for (int i = 0; i < cnt; i++, e++) {
        if (lookup_11BBE8(db, e->item)->flags & 0x10)
            list[n++] = e;
    }
    return n;
}

//100%
extern "C" int func_004165A8(const void* a, const void* b);
extern "C" char* strcpy(char* dst, const char* src);
void* cRider_LoadListCompare(void* self);
extern "C" void func_00418EF8(void* base, int n, int size, void* (*cmp)(void*));

struct sAnimName_11BD60
{
    char name[0x100];
    int f100;
    int f104;
};

struct sAnimNameTable_11BD60
{
    sAnimName_11BD60 e[40];
    int count;      // 0x2940
};

extern "C" void cRider_AddBoltNamesToLoadList(void* self, void** list, int n)
{
    for (int i = 0; i < n; i++, list++)
    {
        char* name = *(char**)((char*)*list + 0x28);
        sAnimNameTable_11BD60* t = *(sAnimNameTable_11BD60**)((char*)self + 0x894);
        if (name == 0) continue;
        if (*name == 0) continue;
        int j;
        for (j = 0; j < t->count; j++)
        {
            if (func_004165A8(name, &t->e[j]) == 0) goto next;
        }
        {
            sAnimName_11BD60* e = &t->e[t->count];
            strcpy(e->name, name);
            e->f100 = -1;
            e->f104 = 0;
            t->count++;
        }
    next:;
    }
    sAnimNameTable_11BD60* t2 = *(sAnimNameTable_11BD60**)((char*)self + 0x894);
    func_00418EF8(t2, t2->count, 0x108, cRider_LoadListCompare);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
void* cBE_getInterface(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int func_004165A8(const void* a, const void* b);
extern "C" char* strcpy(char* dst, const char* src);
void* cRider_LoadListCompare(void* self);
extern "C" void func_00418EF8(void* base, int n, int size, void* (*cmp)(void*));
extern "C" int func_0014AC30(int c);
extern "C" int func_0014A0B0(int c);
extern "C" int func_0014AC50(int c);
extern "C" int func_0014B988(void* iface, int b, int a, void* item, char* out);

struct sAnimName_11BE88
{
    char name[0x100];
    int f100;
    int f104;
};

struct sAnimNameTable_11BE88
{
    sAnimName_11BE88 e[40];
    int start;      // 0x2940
    int count;      // 0x2944
};

extern "C" void cRider_AddBoltFilesToLoadList(void* self, void** list, int n)
{
    void* iface = cBE_getInterface(cBE_getBE(), 9);
    int a = func_0014AC30(*(int*)((char*)self + 0x86C));
    if (func_0014A0B0(*(int*)((char*)self + 0x86C))) {
        for (int i = 0; i < n; i++) {
            char* name = *(char**)((char*)list[i] + 0x2C);
            sAnimNameTable_11BE88* t = *(sAnimNameTable_11BE88**)((char*)self + 0x894);
            if (name == 0) continue;
            if (*name == 0) continue;
            int j;
            int end = t->count + t->start;
            for (j = t->start; j < end; j++) {
                if (func_004165A8(name, &t->e[j]) == 0) goto next;
            }
            {
                sAnimName_11BE88* e = &t->e[end];
                strcpy(e->name, name);
                e->f100 = -1;
                e->f104 = 0;
                t->count++;
            }
        next:;
        }
    } else {
        int b = func_0014AC50(*(int*)((char*)self + 0x86C));
        for (int i = 0; i < n; i++) {
            char buf[0x100];
            if (func_0014B988(iface, b, a, list[i], buf) == 0) continue;
            char* name = buf;
            sAnimNameTable_11BE88* t = *(sAnimNameTable_11BE88**)((char*)self + 0x894);
            if (*name == 0) continue;
            int j;
            int end = t->count + t->start;
            for (j = t->start; j < end; j++) {
                if (func_004165A8(name, &t->e[j]) == 0) goto next2;
            }
            {
                sAnimName_11BE88* e = &t->e[end];
                strcpy(e->name, name);
                e->f100 = -1;
                e->f104 = 0;
                t->count++;
            }
        next2:;
        }
    }
    sAnimNameTable_11BE88* t2 = *(sAnimNameTable_11BE88**)((char*)self + 0x894);
    func_00418EF8(&t2->e[t2->start], t2->count, 0x108, cRider_LoadListCompare);
}

//100%
struct sRiderVE_0011C0E0
{
    short delta;
    short index;
    int (*fn)(void*);
};
extern void* D_004A289C;

extern "C" int cRider_HasRenderSlot(void* self)
{
    if (*(int*)((char*)self + 0x888) != -1)
    {
        void* g = D_004A289C;
        sRiderVE_0011C0E0* vt = *(sRiderVE_0011C0E0**)((char*)g + 0x10D8);
        return *(int*)((char*)self + 0x888) < vt[114].fn((char*)g + vt[114].delta);
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
void* cMdfArchive_cMdfArchive(void* self);
void cMdfArchive_adoptData(void* self, int a1);
extern "C" void cMdfArchive__cMdfArchive(int* self, int flags);
extern "C" void* cMdfArchive_getModelPart(void* self, const char* name);
extern "C" int cRider_collectEquippedItems(void* self, char** list);
extern "C" void cAnimModel_addModelPartLOD(void* model, int lod, void* part, int a3);

struct sMdfArchive_11C138
{
    int a[4];
};

extern "C" void cRider_addEquippedModelParts(void* self, int a1)
{
    sMdfArchive_11C138 arc;
    char* list[52];
    cMdfArchive_cMdfArchive(&arc);
    cMdfArchive_adoptData(&arc, a1);
    int n = cRider_collectEquippedItems(self, list);
    for (int i = 0; i < n; i++)
    {
        char* item = list[i];
        for (int j = 0; j < 4; j++)
        {
            const char* name = ((const char**)(item + 0x18))[j];
            if (name != 0)
            {
                void* part = cMdfArchive_getModelPart(&arc, name);
                if (part != 0)
                {
                    cAnimModel_addModelPartLOD(*(void**)((char*)self + 0x780), j, part, 0);
                }
            }
        }
    }
    cMdfArchive__cMdfArchive((int*)&arc, 2);
}

//100%
extern "C" void cRider_initStep(void* self);
extern "C" void THREAD_yieldticks(int ticks);

extern "C" void cRider_initOnce(void* self, int immediate)
{
    if (immediate)
    {
        cRider_initStep(self);
        return;
    }
    while (*(int*)((char*)self + 0x880) != 7)
    {
        cRider_initStep(self);
        THREAD_yieldticks(1);
    }
}

INCLUDE_ASM("ai/rider", cRider_initStep);

INCLUDE_ASM("ai/rider", cRider_placeOnArrival);

//100%
extern "C" int cRider_isInitDone(void* self)
{
    int s = *(int*)((char*)self + 0x880);
    if (s == 7)
        return 1;
    return s == 7;
}

INCLUDE_ASM("ai/rider", cRider_placeAt);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* cPathSys_FindMarker(void*, int, int);
extern char D_004D33A0[];
extern "C" float func_00115B08(void* self);

struct sVec4_0011DD98
{
    float x, y, z, w;
} __attribute__((aligned(16)));

// The unit declares cRider_placeAt later with its own vector type; bind it by asm label.
void cRider_placeAt_11DD98(void* self, sVec4_0011DD98* a, sVec4_0011DD98* b, int n, float t) __asm__("cRider_placeAt");

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_0011DD98 vu0Scale_11DD98(const sVec4_0011DD98& v, float s)
{
    sVec4_0011DD98 r;
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
static inline void vu0AddEq_11DD98(sVec4_0011DD98& dst, sVec4_0011DD98 b)
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

extern "C" void func_0011DD98(void* self)
{
    float* p = (float*)cPathSys_FindMarker(D_004D33A0, 2, *(int*)((char*)self + 0x86C));
    sVec4_0011DD98 dir;
    sVec4_0011DD98 pos;
    dir.x = p[5];
    dir.y = p[6];
    dir.z = p[7];
    dir.w = 0.0f;
    pos.x = p[2];
    pos.y = p[3];
    pos.z = p[4];
    pos.w = 1.0f;
    vu0AddEq_11DD98(pos, vu0Scale_11DD98(dir, func_00115B08(self)));
    cRider_placeAt_11DD98(self, &pos, &dir, 0x11F, 2999.942626953125f);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* cPathSys_FindMarker(void*, int, int);
extern char D_004D33A0[];
extern "C" void cRiderMetrix_onReset(void* metrix, int flag);
// PORT: prototype mismatch. The unit defines cRider_setControlState/cRider_setMotionMode with one
// param, but their bodies forward $5 to cMotionOwner_setControlState/cMotionOwner_setMotionMode (int arg).
void cRider_setControlState_impl(void* self, int v) __asm__("cRider_setControlState__FPv");
void cRider_setMotionMode_impl(void* self, int v) __asm__("cRider_setMotionMode__FPv");

struct sVec4_0011DE60
{
    float x, y, z, w;
};

extern "C" void cRider_placeAt(void* self, sVec4_0011DE60* a, sVec4_0011DE60* b, int n, float t);

extern "C" void cRider_placeAtRegion(void* self, int a1, int a2)
{
    float* p = (float*)cPathSys_FindMarker(D_004D33A0, a2, a1);
    sVec4_0011DE60 pos;
    sVec4_0011DE60 dir;
    float px = p[2];
    float py = p[3];
    float pz = p[4];
    pos.x = px;
    pos.y = py;
    pos.z = pz;
    pos.w = 1.0f;
    float dx = p[5];
    float dy = p[6];
    float dz = p[7];
    dir.x = dx;
    dir.y = dy;
    dir.z = dz;
    dir.w = 1.0f;
    cRiderMetrix_onReset(*(void**)((char*)self + 0x790), 1);
    cRider_setControlState_impl(self, 0);
    cRider_setMotionMode_impl(self, 0);
    cRider_placeAt(self, &pos, &dir, 5, 0.0f);
}

//100%
extern "C" char* cRiderAnimBase_getChannelSequence(void*, int);
extern "C" void cMotionOwner_resetFX(void* self);
extern "C" void func_003099F8(void* self);
extern void* D_004A3DD8;

struct sVec4_0011DF18
{
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sVEntryA_0011DF18 { short delta; short index; int (*fn)(void*); };
struct sVEntryB_0011DF18 { short delta; short index; void (*fn)(void*, int); };

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_0011DF18 vu0Scale_11DF18(const sVec4_0011DF18& v, float s)
{
    sVec4_0011DF18 r;
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

extern "C" void cRider_finishPlacement(void* self, int notify)
{
    char* s = (char*)self;
    sVec4_0011DF18 v = *(sVec4_0011DF18*)(s + 0x1B0);
    *(int*)(cRiderAnimBase_getChannelSequence(*(void**)(s + 0x784), 2) + 0x90) = 0;
    sVec4_0011DF18 t = vu0Scale_11DF18(v, 833.3333740234375f);
    *(sVec4_0011DF18*)(s + 0x1E0) = t;
    *(float*)(s + 0x1E8) = 0.0f;
    cMotionOwner_resetFX(*(void**)(s + 0x77C));
    if (notify != 0)
    {
        char* sub = s + 0x6C0;
        sVEntryA_0011DF18* vtA = *(sVEntryA_0011DF18**)sub;
        char* obj = *(char**)(*(char**)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x84) + 0x4) + 0xA0);
        sVEntryB_0011DF18* vtB = *(sVEntryB_0011DF18**)(obj + 0x14);
        char* objB = obj + vtB[3].delta;
        vtB[3].fn(objB, vtA[7].fn(sub + vtA[7].delta));
    }
    func_003099F8(D_004A3DD8);
}

INCLUDE_ASM("ai/rider", cRider_rotateAboutAxis);

//100%
// PORT: PS2-only VU0 macro-mode asm. Normalises the orientation quaternion at
// self+0x120, then builds the rider matrix at self+0x1A0 from it (rows 0-2)
// and the position at self+0x110 (row 3).
INCLUDE_ASM("ai/rider", cRider_updateOrientationImplicit);
extern "C" void cRider_updateOrientationImplicit(char* self);

INCLUDE_ASM("ai/rider", cRider_updateQueryBounds);

//100%
extern "C" void cRiderAnimBase_update(void*, int);
extern "C" void cRiderAnimBase_dispatchCompletions(void*);

extern "C" void cRider_updateAnimator(void* self, float value)
{
    cRiderAnimBase_update(*(void**)((char*)self + 0x784), *(int*)((char*)self + 0xB1C));
    cRiderAnimBase_dispatchCompletions(*(void**)((char*)self + 0x784));
}

INCLUDE_ASM("ai/rider", cRider_buildWorldPose);

INCLUDE_ASM("ai/rider", cRider_solveLegIK);

INCLUDE_ASM("ai/rider", cRider_doLeanPoseAdjust);

extern "C" void* cMotionOwner_setMotionMode(int);

//100%
void* cRider_setMotionMode(void* self)
{
    return cMotionOwner_setMotionMode(*(int*)((char*)self + 0x77c));
}

//100%
int cRider_getMotionMode(void* self)
{
    return *(int*)((char*)*(void**)((char*)self + 0x77c) + 0xde0);
}

extern "C" void* cMotionOwner_setControlState(int);

extern "C" void cMotionOwner_getMotionModeName(void* p);

extern "C" void func_0011FEA8(void* self)
{
    cMotionOwner_getMotionModeName(*(void**)((char*)self + 0x77C));
}

//100%
void* cRider_setControlState(void* self)
{
    return cMotionOwner_setControlState(*(int*)((char*)self + 0x77c));
}

//100%
int cRider_getControlState(void* self)
{
    return *(int*)((char*)*(void**)((char*)self + 0x77c) + 0xde4);
}

extern "C" void cMotionOwner_getControlStateName(void* p);

extern "C" void func_0011FEF8(void* self)
{
    cMotionOwner_getControlStateName(*(void**)((char*)self + 0x77C));
}

//100%
// Calls the first virtual of the object at 0x77C with a (its vtable pointer sits at 0xDE8).
class cRiderSub_11FF18 {
public:
    char pad_0x000[0xDE8];
    virtual void v01(int a);
};

extern "C" void func_0011FF18(char* self, int a)
{
    (*(cRiderSub_11FF18**)(self + 0x77C))->v01(a);
}

//100%
// 0x20-byte elements with the quadword at offset 0
struct sRiderXform {
    cQuad128 q;
    char pad_0x10[0x10];
};

extern "C" void* func_0011FF48(void* dst, void* self)
{
    void* q = *(void**)((char*)self + 0x780);
    int i = *(int*)((char*)self + 0x89c);
    sRiderXform* b = *(sRiderXform**)((char*)q + 0x2c);
    *(cQuad128*)dst = b[i].q;
    return dst;
}

extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv really takes (be, kind); bind the 2-arg form to that symbol.
void* cBE_getInterface(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBECharacterInterface_getWeight(void* iface, int character);
extern "C" float cBEStatInterface_getCollisionAttrib(void* iface, int character, int stat);

//100%
// Returns the first vector of the current entry (index at 0x8A8) in the 0x20-byte table of the object at 0x780.
struct sVec4_11FF70
{
    float x, y, z, w;
} __attribute__((aligned(16)));
struct sEntry_11FF70 { sVec4_11FF70 v; char pad[0x10]; };

extern "C" sVec4_11FF70 cRider_getHeadBonePos(char* self)
{
    char* o = *(char**)(self + 0x780);
    return (*(sEntry_11FF70**)(o + 0x2C))[*(int*)(self + 0x8A8)].v;
}

//100%
extern "C" float cRider_getMass(void* self)
{
    int weight = cBECharacterInterface_getWeight(cBE_getInterface(cBE_getBE(), 2), *(int*)((char*)self + 0x86c));
    float toughness = cBEStatInterface_getCollisionAttrib(cBE_getInterface(cBE_getBE(), 3),
                                                          *(int*)((char*)self + 0x86c), *(int*)((char*)self + 0xb34));

    return (float)weight * (toughness * 1.5003352165222168f + 1.0f) * (*(float*)((char*)self + 0x2fc) * 10.0f + 1.0f);
}

extern "C" float func_00149690(void* iface, int character, int stat);

// Grab playback speed: 1 + grab stat * 0.2998.
//100%
extern "C" float cRider_GetGrabStatFactor(void* self)
{
    void* iface = cBE_getInterface(cBE_getBE(), 3);
    return func_00149690(iface, *(int*)((char*)self + 0x86c), *(int*)((char*)self + 0xb34)) * 0.29988324642181396f + 1.0f;
}

//100%
extern "C" void cRider_approachTimeScale(void* self, float x)
{
    float cur = *(float*)((char*)self + 0x300);
    if (x + 0.00083333341171965f < cur)
        x = cur - 0.00083333341171965f;
    else if (cur < x - 0.00083333341171965f)
        x = cur + 0.00083333341171965f;
    *(float*)((char*)self + 0x300) = x;
}

//100%
extern "C" void cRider_requestReaction(void* self, int mode, float t);

struct sVt_1200D0 {
    short delta;
    short index;
    int (*fn)(void*);
};

static inline float decay_1200D0(float v, float step)
{
    if (step < v) {
        return v - step;
    }
    if (v < -step) {
        return v + step;
    }
    return 0.0f;
}

extern "C" void cRider_updateBoostTimers(void* vself)
{
    char* self = (char*)vself;
    float step = *(float*)(self + 0x300) * 0.01666666753590107f;
    *(float*)(self + 0x2E8) = decay_1200D0(*(float*)(self + 0x2E8), step);
    if (0.01666666753590107f < *(float*)(self + 0x2EC) || cRider_getMotionMode(self) != 1) {
        *(float*)(self + 0x2EC) = decay_1200D0(*(float*)(self + 0x2EC), step);
    }
    char* sub = self + 0x6C0;
    sVt_1200D0* e = &(*(sVt_1200D0**)sub)[9];
    e->fn(sub + e->delta);
    if ((cRider_getMotionMode(self) == 1 || cRider_getControlState(self) == 12) && 0.0f < *(float*)(self + 0x2F0) && *(float*)(self + 0x2F0) <= 0.01666666753590107f) {
        *(float*)(self + 0x2F0) = 0.01666666753590107f;
    } else if (0.0f < *(float*)(self + 0x2F0)) {
        *(float*)(self + 0x2F0) = decay_1200D0(*(float*)(self + 0x2F0), step);
        if (*(float*)(self + 0x2F0) == 0.0f) {
            cRider_requestReaction(self, 6, 0.0f);
        }
    }
    if (*(int*)(self + 0x2F4) == 10) {
        *(float*)(self + 0x2F8) = 1.0f;
        if (*(float*)(self + 0x2F0) == 0.0f) {
            *(int*)(self + 0x2F4) = 5;
            *(float*)(self + 0x2F0) = 20.0f;
        }
    } else {
        switch (*(int*)(self + 0x304)) {
        case 0:
            *(float*)(self + 0x2F8) = 1.0f;
            break;
        case 1:
            if (cRider_getControlState(self) != 6) {
                *(float*)(self + 0x2F8) = decay_1200D0(*(float*)(self + 0x2F8), step * 0.004999999888241291f);
            }
            break;
        case 2:
            if (cRider_getControlState(self) != 6) {
                *(float*)(self + 0x2F8) = decay_1200D0(*(float*)(self + 0x2F8), step * 0.02398611046373844f);
            }
            break;
        }
    }
}

INCLUDE_ASM("ai/rider", cRider_updateHair);

//100%
extern "C" void func_00120D58(void* self)
{
    *(float*)((char*)self + 0x2f8) = *(float*)((char*)self + 0xb24);
    int state = *(int*)((char*)self + 0x304);
    if (state == 3) {
        *(float*)((char*)self + 0x2f8) = 0.0f;
    } else if (state == 0) {
        *(float*)((char*)self + 0x2f8) = 1.0f;
    }
}

//100%
extern "C" int cRiderAnimBase_getChannelAnimClass(void*, int);

static inline float riderApproach_00120D90(float v, float t, float s)
{
    if (v > t + s)
        return v - s;
    if (v < t - s)
        return v + s;
    return t;
}

extern "C" void cRider_updateLegIKWeight(void* self)
{
    int a = cRiderAnimBase_getChannelAnimClass(*(void**)((char*)self + 0x784), 2);
    if (a >= 0x14 && a <= 0x1A)
        *(float*)((char*)self + 0x318) = riderApproach_00120D90(*(float*)((char*)self + 0x318), 0.0f, 0.05000000447034836f);
    else
        *(float*)((char*)self + 0x318) = riderApproach_00120D90(*(float*)((char*)self + 0x318), 1.0f, 0.05000000447034836f);
}

//100%
extern "C" void cRider_updateFocusBox(void* self)
{
    void* p = *(void**)((char*)self + 0x78c);
    if (p != 0) {
        *(cQuad128*)p = *(cQuad128*)((char*)self + 0x110);
    }
}

//100%
extern "C" void cOverlapList_build(void*, void*);
extern "C" void cRider_selectLocalLights(void*);

extern "C" void cRider_refreshLights(void* self)
{
    cOverlapList_build(*(void**)((char*)self + 0x860), (char*)self + 0x400);
    cRider_selectLocalLights(self);
}

//100%
extern "C" void func_002F1A08(void*);
extern "C" void func_002ECF78(void*);

extern "C" void cRider_updateFX(void* self)
{
    func_002F1A08(*(void**)((char*)self + 0x88C));
    func_002ECF78(*(void**)((char*)self + 0x890));
}

extern "C" void cMotionOwner_updateFX(void* p);

extern "C" void cRider_UpdateFX(void* self)
{
    cMotionOwner_updateFX(*(void**)((char*)self + 0x77C));
}

//100%
extern "C" void cRider_buildWorldPose(void* self);

extern "C" void cRider_rebuildPose(char* self)
{
    cRider_updateOrientationImplicit(self);
    if (*(int*)(self + 0xAC4) == 0)
    {
        cRider_updateAnimator(self, 1.0f);
        cRider_buildWorldPose(self);
    }
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" int getGameTick();
extern "C" int func_001448A8(void* obj);
extern "C" void cOverlapList_build(void*, void*);
extern "C" void cRider_selectLocalLights(void*);
extern "C" void cRider_ProbeGround(void* self, void* p);
extern "C" void updateRiderSpeedLimit(void* self);
extern void* D_004A28A8;

struct sQuad_120F20
{
    float v[4];
} __attribute__((aligned(16)));
// D_004FF120 is declared later in the unit as a 4-aligned sVec4; this view gives the lq/sq copy.
extern sQuad_120F20 D_004FF120_q120F20 __asm__("D_004FF120");

static inline int IsState1_120F20(void* obj)
{
    return *(int*)((char*)obj + 0x70) == 1;
}

extern "C" void cRider_BeginFrame(char* self)
{
    *(int*)(self + 0x3FC) = 0;
    *(int*)(self + 0xAA4) = 0;
    int a = getGameTick() % 3;
    if (a != *(int*)(self + 0x86C) % 3)
    {
        char* g = *(char**)((char*)D_004A28A8 + 0x84);
        if (*(int*)(*(char**)(self + 0x860) + 4) == *(int*)(*(char**)(g + 0x20) + 0xA0))
        {
            void* obj = *(void**)(g + 0x34);
            int busy = 0;
            if (func_001448A8(obj) || IsState1_120F20(obj))
                busy = 1;
            if (busy == 0)
                goto skip;
        }
    }
    cOverlapList_build(*(void**)(self + 0x860), self + 0x400);
    cRider_selectLocalLights(self);
skip:
    if (*(int*)(self + 0xAC4))
    {
        char* p = self + 0x110;
        if (*(int*)(self + 0xAFC))
            p = *(char**)(*(char**)(self + 0x780) + 0x2C) + (*(int*)(self + 0x8A0) << 5);
        cRider_ProbeGround(self, p);
    }
    *(sQuad_120F20*)(self + 0x9D0) = D_004FF120_q120F20;
    *(int*)(self + 0xA30) = 0;
    *(unsigned*)(self + 0x5B8) = 0xFFFFFFFF;
    updateRiderSpeedLimit(self);
    float t = *(float*)(self + 0x470);
    if (t >= 0.0f)
        *(float*)(self + 0x470) = t + 0.01666666753590107f;
}

//100%
struct sVEntry00121068 {
    short delta;
    short index;
    void (*fn)(void*, void*);
};

extern "C" void cMotionOwner_updateControl(void* obj, void* v);

extern "C" void cRider_updateController(void* self)
{
    int buf[4];
    char* obj = *(char**)((char*)self + 0x77C);
    sVEntry00121068* vt = *(sVEntry00121068**)(obj + 0xDE8);
    vt[1].fn(obj + vt[1].delta, buf);
    cMotionOwner_updateControl(*(void**)((char*)self + 0x77C), buf);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cRider_CheckResetPath(void* rider, int a, int b);
extern "C" void cRider_updateBoostTimers(void* self);
extern "C" void cRider_updateLegIKWeight(void* self);

struct sVec4_1210B0
{
    float v[4];
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (v *= s).
static inline void VecScale_1210B0(sVec4_1210B0* v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(*v), "=&r"(t)
        : "m"(*v), "f"(s));
}

extern "C" void cRider_updateTimers(char* self)
{
    VecScale_1210B0((sVec4_1210B0*)(self + 0x3E0), 0.9800000190734863f);
    *(float*)(self + 0x3F0) *= 0.9559999704360962f;
    *(float*)(self + 0x3F4) *= 0.9783333539962769f;
    if (*(float*)(self + 0x3F0) > 4.5f)
    {
        cRider_CheckResetPath(self, 0, 2);
    }
    else if (cRider_getMotionMode(self) == 1 ||
             (cRider_getMotionMode(self) == 2 && *(int*)(*(char**)(self + 0x77C) + 0x30) == 1))
    {
        char* obj = *(char**)(self + 0x788);
        int ok = 0;
        if (*(int*)(obj + 0xAC) == 1 || *(int*)(obj + 0xAC) == 3)
            ok = 1;
        obj = *(char**)(self + 0x788);
        if ((ok && *(float*)(obj + 0x98) - *(float*)(obj + 0xA0) > 45.0f) || *(float*)(self + 0x3F4) > 5.0f)
            cRider_CheckResetPath(self, 0, 2);
    }
    cRider_updateBoostTimers(self);
    cRider_updateLegIKWeight(self);
}

INCLUDE_ASM("ai/rider", cRider_smoothControls);

extern "C" void* cMotionOwner_updateMotion(int);

//100%
void* cRider_updateMotion(void* self)
{
    return cMotionOwner_updateMotion(*(int*)((char*)self + 0x77c));
}

//100%
extern "C" void cRider_updateAnimator(void* self, float value);

extern "C" void cRider_updateAnimatorPhase(void* self)
{
    if (*(int*)((char*)self + 0xAC4) == 0)
    {
        cRider_updateAnimator(self, *(float*)((char*)self + 0x300));
    }
}

//100%
extern "C" void cRider_buildWorldPose(void* self);

extern "C" void cRider_buildWorldPosePhase(void* self)
{
    if (*(int*)((char*)self + 0xAC4) == 0)
    {
        cRider_buildWorldPose(self);
    }
}

//100%
extern "C" void cMotionOwner_postUpdateMotion(void* p);
extern "C" void cAnimModel_translate(void* model, void* v);

struct sVec4_00121750
{
    float x, y, z, w;
};
extern sVec4_00121750 D_004FF120;

static inline int VecChanged_00121750(char* self, const sVec4_00121750& b)
{
    return *(float*)(self + 0x9D0) != b.x || *(float*)(self + 0x9D4) != b.y
        || *(float*)(self + 0x9D8) != b.z || *(float*)(self + 0x9DC) != b.w;
}

extern "C" void cRider_updatePostMotion(char* self)
{
    cMotionOwner_postUpdateMotion(*(void**)(self + 0x77C));
    if (VecChanged_00121750(self, D_004FF120))
    {
        cAnimModel_translate(*(void**)(self + 0x780), self + 0x9D0);
    }
}

extern "C" void* cAnimModel_buildBoneMatrices(int);

//100%
void* cRider_BuildBoneMatrices(void* self)
{
    return cAnimModel_buildBoneMatrices(*(int*)((char*)self + 0x780));
}

//100%
extern void* D_004A3DD8;
extern "C" void func_0030A060(void* mgr, void* a, void* b, void* c);
void cRider_EmptyProgressHook(void* self);
extern "C" void cRider_updateCourseProgress(void* self);
extern "C" void cRider_updateRouteProgress(void* self);
extern "C" int cRider_checkTimeLimit(void* self);
extern "C" void cRiderMetrix_update(void* metrix);

struct sVEntry00121818 { short delta; short index; void (*fn)(void*, void*, void*, void*); };

extern "C" void cRider_updateProgress(void* self)
{
    char* s = (char*)self;
    char* h = *(char**)(s + 0xA30);
    if (h != 0)
    {
        char* obj = *(char**)(h + 0xC);
        if (obj != 0)
        {
            sVEntry00121818* vt = *(sVEntry00121818**)(obj + 0xC);
            vt[40].fn(obj + vt[40].delta, s + 0xA60, s + 0x9E0, s + 0x6C0);
        }
        else
        {
            func_0030A060(D_004A3DD8, s + 0xA60, s + 0x9E0, s + 0x6C0);
        }
    }
    cRider_EmptyProgressHook(self);
    if (*(int*)(s + 0xAC4) == 0)
    {
        cRider_updateCourseProgress(self);
    }
    cRider_updateRouteProgress(self);
    cRider_checkTimeLimit(self);
    if (*(int*)(s + 0xAC4) == 0)
    {
        cRiderMetrix_update(*(void**)(s + 0x790));
    }
    cRider_updateFocusBox(self);
}

//100%
extern void* D_004A28A8;
extern "C" int func_0022E0E0(void* self, int a1);
extern "C" void func_002ED490(void* obj, float a, float b, float c);
extern "C" void func_00392D18(void* p);

struct sRiderVE_001218D0
{
    short delta;
    short index;
    void* (*fn)(void*);
};

extern "C" void cRider_updateEnvironment(void* self)
{
    char* s = (char*)self;
    if (~*(int*)(s + 0x430) != 0)
        *(int*)(s + 0x434) = func_0022E0E0(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x78), (unsigned char)*(int*)(s + 0x430));
    char* obj = s + 0x6C0;
    sRiderVE_001218D0* vt = *(sRiderVE_001218D0**)obj;
    func_002ED490(vt[7].fn(obj + vt[7].delta), *(float*)(s + 0x460), *(float*)(s + 0x464), -99999.0f);
    char* p = *(char**)(s + 0x77C);
    func_00392D18(p ? p + 0xD30 : 0);
}

//100%
extern "C" int cRider_isGrounded(void* self);
extern "C" void* func_0028B180();
extern "C" void cSSXAudio_updateRiderZones(void* mgr, void* rider);
extern "C" float func_0031C228(float x);
extern "C" void cRider_UpdateDangerState(void* self);

struct sVec2_121950
{
    float x, y;
    sVec2_121950(float a, float b) : x(a), y(b) {}
};

// PORT: PS2 sqrt.s asm helper; use sqrtf on PC.
static inline float Sqrt_121950(float x)
{
    float r;
    __asm__("sqrt.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

static inline float Length_121950(const sVec2_121950& v)
{
    return Sqrt_121950(v.x * v.x + v.y * v.y);
}

static inline float Atan2_121950(float y, float x)
{
    if (x == 0.0f)
    {
        if (y == 0.0f)
            return y;
        float a = -1.5707963705062866f;
        if (y >= 0.0f)
            a = 1.5707963705062866f;
        return a;
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

extern "C" void cRider_UpdateHeadingAndAudio(char* self)
{
    cSSXAudio_updateRiderZones(func_0028B180(), self);
    if (cRider_isGrounded(self))
    {
        sVec2_121950 v(*(float*)(self + 0x370), *(float*)(self + 0x374));
        float z = *(float*)(self + 0x378);
        float ang = Atan2_121950(Length_121950(v), z);
        float d = ang - *(float*)(self + 0x5B4);
        if (d > 3.1415927410125732f)
            d -= 6.2831854820251465f;
        else if (d < -3.1415927410125732f)
            d += 6.2831854820251465f;
        *(float*)(self + 0x5B4) += d * 0.15000000596046448f;
    }
    cRider_UpdateDangerState(self);
}

INCLUDE_ASM("ai/rider", cRider_approachOrientation);

//100%
extern void* D_004A289C;
extern "C" void func_0031BE50(float* s, float* c, float angle);

struct sVec4_121F30
{
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sVEntryP_121F30 { short delta; short index; void* (*fn)(void*); };
struct sVEntryF_121F30 { short delta; short index; float (*fn)(void*); };

// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4x4 matrix * vector).
static inline sVec4_121F30 mtxMulVec_121F30(sVec4_121F30* m, sVec4_121F30* v)
{
    sVec4_121F30 r;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2         $vf8, %1\n"
        "lqc2         $vf4, 0x0(%2)\n"
        "lqc2         $vf5, 0x10(%2)\n"
        "lqc2         $vf6, 0x20(%2)\n"
        "lqc2         $vf7, 0x30(%2)\n"
        "vmulax.xyzw  ACC, $vf4, $vf8x\n"
        "vmadday.xyzw ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw  $vf12, $vf7, $vf8w\n"
        "sqc2         $vf12, %0\n"
        ".set pop\n"
        : "=m"(r)
        : "m"(*v), "r"(m)
        : "memory");
    return r;
}

extern "C" void cRider_updateLOD(char* self)
{
    void* g = D_004A289C;
    sVEntryP_121F30* gvt = *(sVEntryP_121F30**)((char*)g + 0x10D8);
    sVec4_121F30* m = (sVec4_121F30*)gvt[35].fn((char*)g + gvt[35].delta);
    char* obj = self + 0x6C0;
    sVEntryP_121F30* vt = *(sVEntryP_121F30**)obj;
    sVec4_121F30* pos = (sVec4_121F30*)vt[5].fn(obj + vt[5].delta);
    sVec4_121F30 v = mtxMulVec_121F30(m, pos);
    float z = v.z;
    void* g2 = D_004A289C;
    sVEntryF_121F30* gvt2 = *(sVEntryF_121F30**)((char*)g2 + 0x10D8);
    float fov = gvt2[29].fn((char*)g2 + gvt2[29].delta);
    float s, c;
    func_0031BE50(&s, &c, fov);
    z = z * (s / c);
    z = z * 0.009999999776482582f;
    if (z < 6.0f)
    {
        *(int*)(self + 0x898) = 0;
    }
    else
    {
        int lod = 2;
        if (z < 10.0f) lod = 1;
        *(int*)(self + 0x898) = lod;
    }
}

//100%
// Builds a 0xA0-byte record with func_00389C38 and passes it to virtual slot 69 of the object at D_004A289C.
class cRiderSys_122048
{
public:
    char pad_0x00[0x10D8];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69(void* rec, int flags);
};
extern "C" void func_00389C38(void* rec, int flags);

extern "C" void func_00122048()
{
    char rec[0xA0];
    func_00389C38(rec, 0);
    ((cRiderSys_122048*)D_004A289C)->v69(rec, 0);
}

//100%
extern void* D_004A28A8;
extern "C" void func_002F5B68(void* a, void* q, int b, void* c, int d);

extern "C" void cRider_selectLocalLights(void* self)
{
    cQuad128 q;
    func_0011FF48(&q, self);
    func_002F5B68(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x90), &q, *(int*)((char*)self + 0x860), (char*)self + 0x794, 8);
}

//100%
struct sVE_20D8 {
    short delta;
    short index;
    void* (*fn)(void*);
};
struct sXf_20D8 {
    float m[40];
} __attribute__((aligned(16)));
struct sV3_20D8 {
    float x, y, z;
    sV3_20D8() {}
    sV3_20D8(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct sPt_20D8 { float x, y, z; };
struct sQ_20D8 { float v[4]; };
struct sPath_20D8 {
    float x, y, z;
    int n;
    sPt_20D8 pts[5];
    int pad;
    sQ_20D8 q[5];
};
extern "C" void func_00389260(void* p);
extern "C" void* func_002EDFB8(void* p);
extern "C" float func_002EEFA8(void* p);
extern "C" void* func_0011FF48(void* dst, void* self);
extern "C" void func_00389CB8(void* m, void* q, float f);
extern "C" void func_0038A6A8(void* m, void* q, void* p);
extern "C" void func_00389558(void* m, sV3_20D8* v);
extern "C" void func_00389520(void* m, sQ_20D8* q, sV3_20D8* v);

extern "C" void cRider_buildLighting(void* selfp)
{
    char* self = (char*)selfp;
    sQ_20D8 q;
    func_00389260(self + 0x7C0);
    {
        char* obj = self + 0x6C0;
        sVE_20D8* vt = *(sVE_20D8**)obj;
        *(sXf_20D8*)(self + 0x7C0) = *(sXf_20D8*)func_002EDFB8(vt[7].fn(obj + vt[7].delta));
    }
    func_0011FF48(&q, self);
    char* m = self + 0x7C0;
    {
        char* obj = self + 0x6C0;
        sVE_20D8* vt = *(sVE_20D8**)obj;
        func_00389CB8(m, &q, func_002EEFA8(vt[7].fn(obj + vt[7].delta)));
    }
    for (int i = 0; i < 8; i++) {
        void* p = ((void**)(self + 0x794))[i];
        if (p != 0)
            func_0038A6A8(self + 0x7C0, &q, p);
    }
    char* x = *(char**)(self + 0x77C);
    sPath_20D8* t = x ? (sPath_20D8*)(x + 0xD30) : 0;
    if (t != 0) {
        {
            sV3_20D8 v(t->x, t->y, t->z);
            func_00389558(self + 0x7C0, &v);
        }
        for (int j = 0; j < t->n; j++) {
            sQ_20D8* qq = &t->q[j];
            sV3_20D8 v(t->pts[j].x, t->pts[j].y, t->pts[j].z);
            func_00389520(self + 0x7C0, qq, &v);
        }
    }
}

//100%
// PORT: PS2-only VU0 microprogram call (lqc2/ctc2/vcallmsr/cfc2); the PC port needs a C version.
extern void* D_004A289C;
extern void* D_004A28A8;
extern char D_828[];

struct sMat_122278 { float m[16]; };
struct sQ128_122278 { float v[4]; } __attribute__((aligned(16)));
struct sVE_122278 {
    short delta;
    short index;
    void* fn;
};
typedef sMat_122278 (*GetMatFn_122278)(void*);
typedef int (*TestFn_122278)(void*, void*, void*, sMat_122278*);

static inline int inFrustum_122278(sQ128_122278* v)
{
    char* inst = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x8C);
    int mask = *(int*)(inst + 0x110);
    for (int i = 0; i < *(int*)(inst + 0x10C); i++) {
        int bit = 1 << i;
        if (mask & bit) {
            sQ128_122278* m = (sQ128_122278*)(*(char**)(inst + 8 + i * 8) + 0x50);
            int r;
            __asm__ __volatile__(
                ".set push\n"
                ".set noreorder\n"
                "lqc2      $vf1, %1\n"
                "lqc2      $vf2, %2\n"
                "lqc2      $vf3, %3\n"
                "lqc2      $vf4, %4\n"
                "lqc2      $vf5, %5\n"
                "lqc2      $vf6, %6\n"
                "ctc2.ni   %7, $vi27\n"
                "vnop\n"
                "vnop\n"
                "vcallmsr  $vi27\n"
                "cfc2.i    %0, $vi1\n"
                ".set pop\n"
                : "=&r"(r)
                : "m"(m[0]), "m"(m[1]), "m"(m[2]), "m"(m[3]), "m"(m[4]), "m"(*v), "r"((int)D_828 >> 3)
                : "memory");
            int ok = r == 1;
            if (ok)
                return 1;
        }
    }
    return 0;
}

static inline int test_122278(char* a, char* b)
{
    char* g = (char*)D_004A289C;
    sVE_122278* vt = *(sVE_122278**)(g + 0x10D8);
    char* obj = g + vt[93].delta;
    sMat_122278 m = ((GetMatFn_122278)vt[43].fn)(g + vt[43].delta);
    return ((TestFn_122278)vt[93].fn)(obj, a, b, &m);
}

extern "C" int cRider_updateVisibility(char* self)
{
    if (*(int*)(self + 0x884) == 0 || *(int*)(self + 0x880) != 7 || *(int*)(self + 0xAD0) != 0) {
        *(int*)(self + 0xB18) = 0;
        return 0;
    }
    *(int*)(self + 0xB18) = test_122278(self + 0x400, self + 0x410) != 1;
    if (*(int*)(self + 0x150) != 0) {
        if (*(int*)(self + 0xB18) == 0) {
            char* s = *(char**)(self + 0x77C);
            *(int*)(self + 0xB18) = test_122278(s + 0x80, s + 0x90) != 1;
        }
    }
    if (*(int*)(self + 0x150) == 0) {
        if (inFrustum_122278((sQ128_122278*)(self + 0x420)))
            *(int*)(self + 0xB18) = 0;
    }
    return *(int*)(self + 0xB18);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern void* D_004A289C;
extern void* D_004A28A8;
extern "C" void cRider_updateLOD(char* self);
extern "C" void cAnimModel_draw(void* model, int lod, int a, int b);

struct sVec4_122448 { float v[4]; };
extern sVec4_122448 D_004FF120_v122448 __asm__("D_004FF120");

struct sVEntryI_122448 { short delta; short index; void (*fn)(void*, void*, int); };
struct sVEntryF_122448 { short delta; short index; void (*fn)(void*, float, void*); };

extern "C" void cRider_draw(char* self)
{
    if (*(int*)(self + 0xB18))
    {
        char* p = *(char**)(self + 0x77C);
        char* q = p ? p + 0xD30 : 0;
        int b = 0;
        if (*(int*)(q + 0xA0) || *(int*)(self + 0x2F4) >= 11)
            b = 1;
        int a = 0;
        if (*(int*)(q + 0xA4) || *(int*)(self + 0x2F4) >= 11)
            a = 1;
        cRider_updateLOD(self);
        void* g = D_004A289C;
        sVEntryI_122448* vt = *(sVEntryI_122448**)((char*)g + 0x10D8);
        vt[69].fn((char*)g + vt[69].delta, self + 0x7C0, 1);
        void* g2 = D_004A289C;
        int* rs = *(int**)((char*)g2 + 0xE84);
        rs[1] = (rs[1] & ~0x7C) | 0x14;
        sVEntryF_122448* vt2 = *(sVEntryF_122448**)((char*)g2 + 0x10D8);
        vt2[27].fn((char*)g2 + vt2[27].delta, 0.0f, self + 0x110);
        cAnimModel_draw(*(void**)(self + 0x780), *(int*)(self + 0x898), a, b);
        void* g3 = D_004A289C;
        sVEntryF_122448* vt3 = *(sVEntryF_122448**)((char*)g3 + 0x10D8);
        vt3[27].fn((char*)g3 + vt3[27].delta, 0.0f, &D_004FF120_v122448);
    }
    if (*(int*)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x84) + 0x14) == 0 || *(int*)(self + 0xB1C))
    {
        int* f = (int*)(self + 0xB1C);
        int v = 0;
        if (*(int*)(self + 0xB18) == 0 || *(int*)(self + 0x898) == 2)
            v = 1;
        *f = v;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cRider_buildLighting(void*);

extern "C" int cRider_updateLightingIfVisible(void* self)
{
    if (*(int*)((char*)self + 0xB18) != 0) {
        cRider_buildLighting(self);
    }
    return 1;
}

//100%
extern "C" void cRider_buildShadow(void* self);

extern "C" void cRider_updateShadow(void* self)
{
    if (*(int*)((char*)self + 0xB18) != 0)
    {
        cRider_buildShadow(self);
    }
}

extern "C" void* func_002F2088(int);

extern "C" void cMotionOwner_drawFX(void* p);

extern "C" void cRider_DrawFX(void* self)
{
    cMotionOwner_drawFX(*(void**)((char*)self + 0x77C));
}

//100%
void* cRider_RenderAttachedFX(void* self)
{
    return func_002F2088(*(int*)((char*)self + 0x88c));
}

//100%
// func_003E6448 looks like memset(dst, value, size).
extern "C" void* func_003E6448(void* dst, int value, int size);

extern "C" void cRider_clearLocalLights(void* self)
{
    func_003E6448((char*)self + 0x794, 0, 0x20);
}

INCLUDE_ASM("ai/rider", func_00122680);

//100%
struct sV4_2898 {
    float x, y, z, w;
    sV4_2898() {}
    sV4_2898(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

struct sV3_2898 {
    float x, y, z;
};

struct sMat_2898 {
    float m[4][4];
} __attribute__((aligned(16)));

struct sRS_2898 {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
};

struct sModel_2898 {
    char pad0[0x30];
    sMat_2898* bones;               // 0x30
};

struct sObj_2898 {
    char pad0[0x110];
    sMat_2898 mat;                  // 0x110
    sV4_2898 f150;                  // 0x150
    sV4_2898 f160;                  // 0x160
    void* f170;                     // 0x170
};

struct sRider_2898 {
    char pad0[0x1C0];
    sV4_2898 pos;                   // 0x1C0
    char pad1D0[0x780 - 0x1D0];
    sModel_2898* model;             // 0x780
    char pad784[0x8E8 - 0x784];
    int boneA;                      // 0x8E8
    char pad8EC[0x918 - 0x8EC];
    int boneB;                      // 0x918
    char pad91C[0xAA4 - 0x91C];
    int drawn;                      // 0xAA4
    sObj_2898* obj;                 // 0xAA8
};

struct sVE0_2898 { short delta; short index; void (*fn)(void*); };
struct sVEI_2898 { short delta; short index; int (*fn)(void*); };
struct sVEI3_2898 { short delta; short index; int (*fn)(void*, void*, const sV4_2898&); };
struct sVE2_2898 { short delta; short index; void (*fn)(void*, void*, int); };
struct sVE3_2898 { short delta; short index; void (*fn)(void*, void*, void*); };
struct sVE4_2898 { short delta; short index; void (*fn)(void*, void*, void*, void*); };

extern void* D_004A289C;
extern int D_004A4C00;
extern sV3_2898 D_004A5E40;

extern "C" void func_00374D00(void* obj, sV3_2898* a, sV3_2898* b, sV3_2898* dir, sMat_2898* bones, int f);
extern "C" void cAnimModel_drawShadow(void* model, int lod, sV4_2898* a, sV4_2898* b);
extern "C" void func_00375890(void* obj);
int cRider_getMotionMode(void*);

// PORT: PS2-only VU0 inline asm (vector add).
static inline sV4_2898 Add_2898(const sV4_2898& a, const sV4_2898& b)
{
    sV4_2898 r;
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

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sV4_2898 Scale_2898(const sV4_2898& v, float s)
{
    sV4_2898 r;
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

// PORT: PS2-only VU0 inline asm (4x4 matrix copy).
static inline void CopyMat_2898(sMat_2898* d, sMat_2898* s)
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

static inline void Set3_2898(sV3_2898& v, float x, float y, float z)
{
    v.x = x;
    v.y = y;
    v.z = z;
}

static inline sV4_2898 BonePos_2898(sRider_2898* r, int i) { return *(sV4_2898*)((char*)r->model->bones + (i << 6) + 0x30); }

static inline void* Tex_2898(sObj_2898* o) { return o->f170; }

static inline sRS_2898*& top_2898(void* g) { return *(sRS_2898**)((char*)g + 0xE84); }

extern "C" void cRider_buildShadow(void* vself)
{
    sRider_2898* self = (sRider_2898*)vself;
    if (self->drawn == 0) {
        self->drawn = 1;
        void* g = D_004A289C;
        top_2898(g)[1] = top_2898(g)[0];
        top_2898(g)++;
        sV3_2898 a;
        {
            sV4_2898 m = Scale_2898(Add_2898(BonePos_2898(self, self->boneB), BonePos_2898(self, self->boneA)), 0.5f);
            a.x = m.x;
            a.y = m.y;
            a.z = m.z;
        }
        if (D_004A4C00 == 0) {
            Set3_2898(D_004A5E40, 0.0f, 0.0f, -1.0f);
            D_004A4C00 = 1;
        }
        sV3_2898 b;
        {
            sV4_2898 p = self->pos;
            b.x = p.x;
            b.y = p.y;
            b.z = p.z;
        }
        float k = 0.3f;
        func_00374D00(self->obj, &a, &b, &D_004A5E40, self->model->bones, 0);
        void* g2 = D_004A289C;
        top_2898(g2)->f8 = (top_2898(g2)->f8 & ~0x3E0) | 0x20;
        top_2898(g2)->f4 = (top_2898(g2)->f4 & 0xFE7FFFFF) | 0x1000000;
        top_2898(g2)->f4 = top_2898(g2)->f4 & 0xFFCFFFFF;
        top_2898(g2)->f4 = (top_2898(g2)->f4 & 0xFFF00FFF) | 0x14000;
        top_2898(g2)->f4 = (top_2898(g2)->f4 & 0xFFBFFFFF) | 0x400000;
        top_2898(g2)->f4 = (top_2898(g2)->f4 & ~0x7C) | 4;
        sVE0_2898* vt = *(sVE0_2898**)((char*)g2 + 0x10D8);
        vt[31].fn((char*)g2 + vt[31].delta);
        void* g3 = D_004A289C;
        sVE2_2898* vt3 = *(sVE2_2898**)((char*)g3 + 0x10D8);
        vt3[53].fn((char*)g3 + vt3[53].delta, self->obj->f170, 1);
        void* g4 = D_004A289C;
        sVEI3_2898* vt4 = *(sVEI3_2898**)((char*)g4 + 0x10D8);
        vt4[55].fn((char*)g4 + vt4[55].delta, Tex_2898(self->obj), sV4_2898(0.0f, 0.0f, 0.0f, 0.0f));
        if (cRider_getMotionMode(self) == 0) {
            k = 0.0f;
        }
        sMat_2898 mat;
        CopyMat_2898(&mat, &self->obj->mat);
        sV4_2898 p0 = self->obj->f150;
        sV4_2898 p1 = self->obj->f160;
        void* g5 = D_004A289C;
        sVE4_2898* vt5 = *(sVE4_2898**)((char*)g5 + 0x10D8);
        vt5[101].fn((char*)g5 + vt5[101].delta, &mat, &p0, &p1);
        sV4_2898 c1;
        c1.x = 1.0f;
        c1.y = k;
        c1.z = k;
        c1.w = k;
        sV4_2898 c2;
        c2.x = 1.0f;
        c2.y = 0.3f;
        c2.z = 0.3f;
        c2.w = 0.3f;
        cAnimModel_drawShadow(self->model, 3, &c1, &c2);
        void* g6 = D_004A289C;
        sVEI_2898* vt6 = *(sVEI_2898**)((char*)g6 + 0x10D8);
        vt6[54].fn((char*)g6 + vt6[54].delta);
        void* g7 = D_004A289C;
        sVE0_2898* vt7 = *(sVE0_2898**)((char*)g7 + 0x10D8);
        vt7[32].fn((char*)g7 + vt7[32].delta);
        void* g8 = D_004A289C;
        top_2898(g8)--;
    }
    func_00375890(self->obj);
}

//100%
extern "C" void* cPathSys_FindMarker(void*, int, int);
extern char D_004D33A0[];

extern "C" float* func_00122C28(float* out, void* rider)
{
    float* p = (float*)cPathSys_FindMarker(D_004D33A0, 1, *(int*)((char*)rider + 0x86C));
    out[0] = p[2];
    out[1] = p[3];
    out[2] = p[4];
    out[3] = 1.0f;
    return out;
}

extern "C" float func_00122C88()
{
    return 0.9250819683074951f;
}

//100%
extern "C" int cRider_isOnSteepSlope(void* self)
{
    float v = *(float*)((char*)self + 0x5B4);
    float k = 0.9250819683074951f;
    return v >= k || v < -k;
}

extern "C" int cRider_isGrounded(void* self);

//100%
void* cRider_isGrounded_Wrapper(void* self)
{
    return (void*)cRider_isGrounded(self);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern void* D_004A28A8;
extern "C" int DangerMan_GetRiderDanger(void* self, int character);
extern "C" int cRider_isOnSteepSlope(void* self);
float cRiderMetrix_ReturnZero_a0c0_2(void* self, int state) __asm__("cRiderMetrix_ReturnZero_a0c0__FPv");

extern "C" void cRider_UpdateDangerState(void* self)
{
    char* s = (char*)self;
    int old = *(int*)(s + 0x5B0);
    int r = DangerMan_GetRiderDanger(*(void**)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0xA8), *(int*)(s + 0x86C));
    *(int*)(s + 0x5B0) = r;
    if (r == 0)
    {
        if (cRider_isGrounded_Wrapper(self) != 0)
        {
            if (cRider_isOnSteepSlope(self))
                *(int*)(s + 0x5B0) = 1;
        }
    }
    int cur = *(int*)(s + 0x5B0);
    if (old != cur)
        cRiderMetrix_ReturnZero_a0c0_2(*(void**)(s + 0x790), cur);
}

//100%
float cRider_getProgressOrigin(void* self);

struct sVEntry00122D78 { short delta; short index; int (*fn)(void*); };

extern "C" int cRider_estimateFinishTicks(void* self)
{
    char* s = (char*)self;
    char* sub = s + 0x6C0;
    int n = *(int*)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0xC);
    float rate = (cRider_getProgressOrigin(self) - *(float*)(s + 0x4D0)) / (float)n;
    sVEntry00122D78* vt = *(sVEntry00122D78**)sub;
    if (rate < 30.0f - (float)vt[7].fn(sub + vt[7].delta))
    {
        sVEntry00122D78* vt2 = *(sVEntry00122D78**)sub;
        rate = 30.0f - (float)vt2[7].fn(sub + vt2[7].delta);
    }
    return n + (int)(*(float*)(s + 0x4D0) / rate);
}

//100%
float cRider_getProgressOrigin(void* self);

extern "C" int cRider_estimateFinalScore(void* self)
{
    int n = *(int*)(*(char**)((char*)self + 0x790) + 0x198) + 1;
    float t = cRider_getProgressOrigin(self) - *(float*)((char*)self + 0x4D0);
    if (t < 1.0f)
        t = 1.0f;
    float r = (float)n / t;
    float d = *(float*)((char*)self + 0x4D0) - 1000.0f;
    if (d < 0.0f)
        d = 0.0f;
    return n + (int)(d * r);
}

//100%
int cRider_getMotionMode(void* self);
int cRider_getControlState(void* self);
extern "C" int func_00135EB0(void* self);
extern "C" int func_00135EF0(void* self);
extern "C" int func_00135F30(void* self);
extern "C" int cRiderAnimBase_getChannelAnimClass(void*, int);
extern "C" char* cRiderAnimBase_getChannelSequence(void*, int);
extern "C" int testFlagBit(void* self, int a1);

// Tests one rider condition by id (used by the scripted-event checks).
extern "C" int cRider_testCondition(char* self, int cond)
{
    switch (cond) {
    case 0:
        return cRider_getMotionMode(self) == 2;
    case 1:
        return cRider_getControlState(self) == 9;
    case 2: {
        int r = 0;
        if (cRider_getMotionMode(self) == 1
            || (cRider_getMotionMode(self) == 2 && *(int*)(*(char**)(self + 0x77C) + 0x30) == 1)) {
            r = 1;
        }
        return r;
    }
    case 3:
        return cRider_getMotionMode(self) == 0;
    case 4:
        return cRider_getMotionMode(self) == 4;
    case 5: {
        int r = 0;
        if (cRider_getControlState(self) == 5) {
            r = func_00135EB0(*(char**)(self + 0x77C) + 0x230) != 0;
        }
        return r;
    }
    case 6: {
        int r = 0;
        if (cRider_getControlState(self) == 5) {
            r = func_00135EF0(*(char**)(self + 0x77C) + 0x230) != 0;
        }
        return r;
    }
    case 7: {
        int r = 0;
        if (cRider_getControlState(self) == 5) {
            r = func_00135F30(*(char**)(self + 0x77C) + 0x230) != 0;
        }
        return r;
    }
    case 9:
        return *(int*)(self + 0x330) == 1;
    case 10:
        return *(int*)(self + 0x330) == 2;
    case 11:
        return *(float*)(self + 0x2FC) != 0.0f;
    case 8:
        return *(int*)(*(char**)(self + 0x790) + 0x198);
    case 15:
        return *(int*)(*(char**)(self + 0x790) + 0x138);
    case 16:
        return *(int*)(*(char**)(self + 0x790) + 0x13C);
    case 17:
        return *(int*)(*(char**)(self + 0x790) + 0x19C);
    case 18: {
        int r = 0;
        if (cRiderAnimBase_getChannelAnimClass(*(void**)(self + 0x784), 1) == 0xD) {
            if (testFlagBit(cRiderAnimBase_getChannelSequence(*(void**)(self + 0x784), 1) + 0xB0, 0) != 0) {
                r = testFlagBit(cRiderAnimBase_getChannelSequence(*(void**)(self + 0x784), 1) + 0xB0, 1) == 0;
            }
        }
        return r;
    }
    }
    return 0;
}

//100%
signed char cBENewPlayerInterface_getRiderCharID(void* self, int riderIndex);
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");

extern "C" int cRider_getCharacterID(void* self)
{
    return cBENewPlayerInterface_getRiderCharID(cBE_getInterface_Fv(cBE_getBE(), 1), *(int*)((char*)self + 0x86C));
}

//100%
extern "C" int func_00147410(void* iface, int riderIndex);
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");

extern "C" int func_00123168(void* self)
{
    return func_00147410(cBE_getInterface_Fv(cBE_getBE(), 1), *(int*)((char*)self + 0x86C));
}

// Grounded predicate: motion 0, or motion 2 with owner+0x30 == 0.
//100%
extern "C" int cRider_isGrounded(void* self)
{
    int grounded = 0;

    if (cRider_getMotionMode(self) == 0 ||
        (cRider_getMotionMode(self) == 2 && *(int*)((char*)*(void**)((char*)self + 0x77c) + 0x30) == 0)) {
        grounded = 1;
    }
    return grounded;
}

INCLUDE_ASM("ai/rider", cRider_teleportToMatrix);

INCLUDE_ASM("ai/rider", cRider_placeAtInstance);

//100%
// PORT: prototype mismatch. The unit defines cRider_setControlState/cRider_setMotionMode with one
// param, but their bodies forward $5 to cMotionOwner_setControlState/cMotionOwner_setMotionMode (int arg).
void cRider_setControlState_impl(void* self, int v) __asm__("cRider_setControlState__FPv");
void cRider_setMotionMode_impl(void* self, int v) __asm__("cRider_setMotionMode__FPv");

extern "C" void func_001235F8(void* self)
{
    *(int*)(*(char**)((char*)self + 0x77C) + 0x350) = 1;
    cRider_setControlState_impl(self, 9);
    cRider_setMotionMode_impl(self, 3);
    *(int*)(*(char**)((char*)self + 0x77C) + 0x290) = 0;
}

INCLUDE_ASM("ai/rider", cRider_startNISActor);

//100%
extern "C" void func_002803F0(void* self);
extern "C" void cRider_placeOnArrival(void* self);
extern "C" void* func_0028B180();
void func_002A1BD0(void* p);
extern "C" void cAnimModel_hidePart(void* model, int i, int channel);
extern "C" void cAnimModel_showPart(void* model, int i, int channel);
int func_0027C958(void* self);
// PORT: func_0014BDB8 is declared (void*) but never reads its argument; called here with none
void* func_0014BDB8_noarg() __asm__("func_0014BDB8__FPv");
extern "C" void* func_0014AD50(void* iface, int id);
int func_0014D988(void* tbl, int g);
extern "C" void* func_0014D998(void* tbl, int g);
extern "C" void cBankMonitor_stopVoice(void* bank, int id, int a, float f);

struct sItem_123B48 {
    short a;
    unsigned short flags;
};

struct sDb_123B48 {
    char pad0[0x288];
    short* map;                 // 0x288
    char pad28C[0x4];
    sItem_123B48 items[1];      // 0x290
};

struct sEnt_123B48 {
    char pad0[0x4];
    short item;                 // 0x04
    char pad6[0xA];
    signed char id;             // 0x10
    char pad11[0x23];
    int flags;                  // 0x34
};

static inline sItem_123B48* lookup_123B48(sDb_123B48* d, int i)
{
    short k = d->map[i];
    if (k >= 0) {
        return &d->items[k];
    }
    return 0;
}

static inline int entId_123B48(sEnt_123B48* e)
{
    return e->id;
}

static inline int entOn_123B48(sEnt_123B48* e)
{
    return e->flags & 0x40;
}

static inline void* model_123B48(char* self)
{
    return *(void**)(self + 0x780);
}

static inline void setChan_123B48(char* self, int id, int ch)
{
    cAnimModel_showPart(model_123B48(self), id, ch);
}

static inline int entItem_123B48(sEnt_123B48* e)
{
    return e->item;
}

static inline unsigned short itemFlags_123B48(sDb_123B48* db, sEnt_123B48* e)
{
    return lookup_123B48(db, entItem_123B48(e))->flags;
}

extern "C" void cRider_stopNISActor(char* self)
{
    func_002803F0(self + 0x6D0);
    cRider_placeOnArrival(self);
    if (*(int*)(self + 0xAC8) != 0) {
        func_002A1BD0(func_0028B180());
    }
    *(int*)(self + 0xAFC) = 0;
    *(int*)(self + 0xB04) = 0;
    *(int*)(self + 0xAC4) = 0;
    int* ids = (int*)(self + 0xB08);
    *(int*)(self + 0xAD0) = 0;
    *(int*)(self + 0xB00) = 1;
    cAnimModel_hidePart(*(void**)(self + 0x780), 5, 0);
    cAnimModel_hidePart(*(void**)(self + 0x780), 6, 0);
    cAnimModel_hidePart(*(void**)(self + 0x780), 8, 0);
    cAnimModel_hidePart(*(void**)(self + 0x780), 9, 0);
    cAnimModel_hidePart(*(void**)(self + 0x780), 11, 0);
    cAnimModel_showPart(*(void**)(self + 0x780), 4, 0);
    cAnimModel_showPart(*(void**)(self + 0x780), 7, 0);
    // PORT: func_0027C958 returns a record pointer as int
    if (*(signed char*)((char*)func_0027C958(*(void**)(self + 0x6D8)) + 6) != 0) {
        void* iface = cBE_getInterface(cBE_getBE(), 9);
        void* tbl = func_0014BDB8_noarg();
        sDb_123B48* db = (sDb_123B48*)func_0014AD50(iface, *(int*)(self + 0x86C));
        int g = cRider_getCharacterID(self);
        int n = func_0014D988(tbl, g);
        sEnt_123B48* e = (sEnt_123B48*)func_0014D998(tbl, g);
        int i;
        for (i = 0; i < n; i++, e++) {
            int id = entId_123B48(e);
            if (id >= 0 && entOn_123B48(e)) {
                if (itemFlags_123B48(db, e) & 0x10) {
                    setChan_123B48(self, id, 0);
                    setChan_123B48(self, id, 1);
                    setChan_123B48(self, id, 2);
                    setChan_123B48(self, id, 3);
                }
            }
        }
    }
    int j;
    for (j = 0; j < 4; j++) {
        if (ids[j] >= 0) {
            cBankMonitor_stopVoice(*(char**)*(char**)((char*)func_0028B180() + 0x118) + 0x1D8, ids[j], 1, 0.0f);
        }
        ids[j] = -1;
    }
}

//100%
extern "C" void ScriptRider_ReadFields(int, void*);
extern "C" void cRider_updateNISClip(void*, void*, float, float, int);
extern "C" void cRider_updateNISSounds(void*, void*, float, float, int);

extern "C" void cRider_onNISEvent(void* self, int id, float a, float b, int unused, int flags)
{
    int buf[12];
    if (*(int*)((char*)self + 0xAC4))
    {
        ScriptRider_ReadFields(id, buf);
        cRider_updateNISClip(self, buf, a, b, flags);
        cRider_updateNISSounds(self, buf, a, b, flags);
    }
}

//100%
extern "C" void ScriptRider_ReadFields(int, void*);
extern "C" void* func_0028B180();
extern "C" int func_002A1B58(void* self, int msg, int a);
extern "C" int func_002A1B88(void* self, int type, int a, int b);
extern "C" void* ScriptEngine_GetTargetObject(void* self, int i, int a2);
extern void* D_004A28A4;

struct sAnimEvent_123E30
{
    int id;
    signed char* arg;
};

struct sAnimEventInfo_123E30
{
    int pad[4];
    int count;                      // 0x10
    sAnimEvent_123E30* events;      // 0x14
    int pad18[6];
};

extern "C" void cRider_onSpeechEvent(void* self, int id, float a, float b, int unused, int flags)
{
    sAnimEventInfo_123E30 info;
    if (flags & 0x10)
    {
        ScriptRider_ReadFields(id, &info);
        for (int i = 0; i < info.count; i++)
        {
            sAnimEvent_123E30* e = &info.events[i];
            int ev = e->id;
            if (ev == 0x66) continue;
            if (ev < 0x64)
            {
                func_002A1B58(func_0028B180(), ev, (int)self);
                *(int*)((char*)self + 0xAC8) = 1;
            }
            else
            {
                ev -= 0x64;
                void* snd = func_0028B180();
                // PORT: id is a handle that is also read as a pointer here.
                int v = (int)ScriptEngine_GetTargetObject(D_004A28A4, *e->arg, *(int*)(id + 8));
                func_002A1B88(snd, ev, (int)self, v);
                *(int*)((char*)self + 0xAC8) = 1;
            }
        }
    }
}

INCLUDE_ASM("ai/rider", func_00123F38);

//100%
extern "C" void func_0031BE50(float* s, float* c, float angle);

struct sQuat_001241C0
{
    float x, y, z, w;
} __attribute__((aligned(16)));

extern "C" void cRider_eulerToQuat(void* self, sQuat_001241C0* out, float rx, float ry, float rz)
{
    sQuat_001241C0 q;
    float sz, cz, sy, cy, sx, cx;
    func_0031BE50(&sz, &cz, rz * 0.5f);
    func_0031BE50(&sy, &cy, ry * 0.5f);
    func_0031BE50(&sx, &cx, rx * 0.5f);
    float cc = cy * cx;
    float ss = sy * sx;
    q.w = cz * cc + sz * ss;
    q.x = sz * cc - cz * ss;
    q.y = cz * sy * cx + sz * cy * sx;
    q.z = cz * cy * sx - sz * sy * cx;
    *out = q;
}

INCLUDE_ASM("ai/rider", cRider_ProbeGround);

INCLUDE_ASM("ai/rider", cRider_updateNISClip);

//100%
extern void* D_004A28A8;
void* func_00230698(void* self, int id);
extern "C" void func_002E4578(void* p);

extern "C" void cRider_stopScreenFade(void* self)
{
    void* w = *(void**)((char*)D_004A28A8 + 0x84);
    if (*(void**)((char*)w + 0x84) != 0 && *(int*)((char*)self + 0x870) >= 0)
    {
        if (*(int*)((char*)func_00230698(w, *(int*)((char*)self + 0x870)) + 0x78) == 1)
            func_002E4578(func_00230698(*(void**)((char*)D_004A28A8 + 0x84), *(int*)((char*)self + 0x870)));
    }
}

//100%
extern "C" void cAirPredictor_startLaunchIntoAir(void* self, void* a, void* b, float t);

struct sRiderVec4_001250A8
{
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (a += b).
static inline void riderAddEq_001250A8(sRiderVec4_001250A8& a, const sRiderVec4_001250A8& b)
{
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(a)
        : "m"(a), "m"(b));
}

extern "C" void cRider_addVelocity(void* self, sRiderVec4_001250A8* v)
{
    sRiderVec4_001250A8* p = (sRiderVec4_001250A8*)((char*)self + 0x1E0);
    riderAddEq_001250A8(*p, *v);
    if (cRider_getMotionMode(self) == 1)
        cAirPredictor_startLaunchIntoAir(*(void**)((char*)self + 0x788), (char*)self + 0x110, p, 3333.33349609375f);
}

//100%
extern void* D_004A28A8;
extern char* D_004A2EEC;
extern "C" float cRiderMetrix_onFinish(void* self);
extern "C" void func_00162258(void* self);
extern "C" void cGameModeMan_OnRiderFinished(void* self, int a1, int a2);
extern "C" void cSSXAudio_onRiderFinish(void* self, void* rider);
extern "C" void* func_0028B180();

struct sVEntry125108 { short delta; short index; int (*fn)(void*); };

static inline void* getC0_125108()
{
    return *(void**)((char*)D_004A28A8 + 0xC0);
}

extern "C" void cRider_finish(char* self)
{
    char* g = D_004A2EEC;
    if (g != 0 && *(int*)(self + 0x480) == 0 && *(int*)(self + 0x874) != 0)
    {
        if (*(int*)(self + 0x87C) != 0)
            *(int*)(g + 0xA0) = 1;
        else
            *(int*)(g + 0xA4) = 1;
    }
    cRiderMetrix_onFinish(*(void**)(self + 0x790));
    *(int*)(self + 0x478) = *(int*)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0xC) + *(int*)(self + 0x47C);
    if (*(float*)(self + 0x470) < 0.0f) *(float*)(self + 0x470) = 0.0f;
    char* obj = self + 0x6C0;
    sVEntry125108* vt = *(sVEntry125108**)obj;
    cGameModeMan_OnRiderFinished(getC0_125108(), vt[7].fn(obj + vt[7].delta), *(int*)(self + 0x790) + 0xFC);
    unsigned int k = *(unsigned int*)(self + 0x870);
    if (k < 2)
    {
        char* tbl = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x84);
        func_00162258(*(void**)(*(char**)(tbl + (k << 2) + 4) + 0xA8));
    }
    cSSXAudio_onRiderFinish(func_0028B180(), self);
    if (*(int*)(self + 0x480) == 1) *(int*)(self + 0x100) = 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sVE_125228 {
    short delta;
    short index;
    int (*fn)(void*);
};
extern "C" void* cBE_getBE();
void* cBE_getInterface(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void cRider_finish(char* self);
extern "C" void* func_0028B180();
extern "C" void cSSXAudio_ArcadeSay20A8(void* a, void* self, int n);
extern "C" unsigned int func_004139F8(float f);
extern void* D_004A28A8;
extern signed char D_00535C10[];
extern int D_005308D0[];

extern "C" int cRider_checkTimeLimit(void* selfp)
{
    char* self = (char*)selfp;
    char* obj = self + 0x6C0;
    sVE_125228* vt = *(sVE_125228**)obj;
    if (vt[8].fn(obj + vt[8].delta)) {
        float h = *(float*)(self + 0x470);
        float zero = 0.0f;
        int done = h >= zero;
        if (!done) {
            cBE_getInterface(cBE_getBE(), 0);
            if (D_00535C10[0] == 4)
                return *(float*)(self + 0x470) >= zero;
            char* g = (char*)D_004A28A8;
            char* p = *(char**)(g + 0xC0);
            if (*(int*)(p + 0x88) != 0 && ((D_005308D0[0] >> 9) & 1) == 0) {
                int t = *(int*)(*(char**)(*(char**)(g + 0x84) + 0xC) + 0xC);
                int secs = func_004139F8((float)*(unsigned int*)(p + 0x78) * 0.01666666753590107f);
                if (secs * 60 < t) {
                    *(int*)(self + 0x480) = 1;
                    cRider_finish(self);
                    cSSXAudio_ArcadeSay20A8(func_0028B180(), self, 2);
                    goto end;
                }
            }
            if (*(int*)(self + 0x480) == 1 && *(int*)(*(char**)((char*)D_004A28A8 + 0x84) + 0x214) == 4)
                cRider_finish(self);
        }
    }
end:
    return *(float*)(self + 0x470) >= 0.0f;
}

//100%
struct sVEntry001253D0 {
    short delta;
    short index;
    int (*fn)(void*);
};

extern int D_005366D0[];

static inline bool riderHasFinished001253D0(char* rider)
{
    return *(float*)(rider + 0x470) >= 0.0f;
}

extern "C" void cRider_quitEvent(char* self)
{
    bool finished = riderHasFinished001253D0(self);
    if (!finished)
    {
        *(int*)(self + 0x480) = 1;
        char* sub = self + 0x6C0;
        sVEntry001253D0* vt = *(sVEntry001253D0**)sub;
        D_005366D0[vt[7].fn(sub + vt[7].delta)] = 1;
    }
}

//100%
extern "C" void* func_0028B180();
extern "C" void* func_00416210(void* dst, int c, int n);
extern "C" void* cSSXAudio_getBusVolumePtr(void* self, int a1, int a2);
extern "C" int func_002906B8(void* self);
extern "C" int cSSXAudio_getRiderListener(void* self, void* obj);
extern "C" int cBankMonitor_findVoice(void* bank, int id, int a);
extern "C" void cBankMonitor_stopVoice(void* bank, int id, int a, float f);
void func_00280548(void* self, int a1, void* a2, void* a3);

struct sSnd5448Ch {
    signed char vol;
    char pad1[0x17];
};
struct sSnd5448E16 {
    int f0;
    int f4;
    int f8;
    int fC;
};
struct sSnd5448Sub {
    char pad0[4];
    sSnd5448Ch def;          // 0x04
    volatile int cur;        // 0x1C
    sSnd5448Ch* ch;          // 0x20
    void* tgt[4];            // 0x24
    int* p34;                // 0x34
    int* vals;               // 0x38
    int* p3C;                // 0x3C
    char e40[4][8];          // 0x40
    int* p60;                // 0x60
    int* p64;                // 0x64
    int* p68;                // 0x68
    int* p6C;                // 0x6C
    sSnd5448E16* p70;        // 0x70
    int* p74;                // 0x74
    int* p78;                // 0x78
    int* p7C;                // 0x7C
    int* p80;                // 0x80
    int* p84;                // 0x84
};
struct sSnd5448Mgr {
    char pad0[0x1D8];
    sSnd5448Sub sub;         // 0x1D8
};
struct sSnd5448Sys {
    sSnd5448Mgr* mgr;
    int* a4;                 // 0x4
    int* a8;                 // 0x8
    char padC[0x118 - 0xC];
    sSnd5448Mgr** p118;      // 0x118
};

// Animation sound event: one entry per voice of the event.
struct sSndEvt5448 {
    int id;                  // 0x00
    int frame;               // 0x04
    char pad8[0x4];
    int slot;                // 0x0C
    char pad10[0xC];
    signed char* vol;        // 0x1C
    sSndEvt5448* next;       // 0x20
};

struct sRider5448 {
    char pad0[0xB08];
    int ids[4];              // 0xB08
};

#define SND_5448_MIN(a, b) ((a) < (b) ? (a) : (b))
#define SND_5448_MAX(a, b) ((a) > (b) ? (a) : (b))

static inline void snd5448AddVoice(sSnd5448Sys* snd, int a, int b)
{
    sSnd5448Mgr* m = snd->mgr;
    sSnd5448Sub* s = &m->sub;
    m->sub.cur++;
    s->ch[m->sub.cur] = m->sub.def;
    m->sub.tgt[m->sub.cur] = 0;
    s->p34[m->sub.cur] = 0;
    s->vals[m->sub.cur] = s->ch[m->sub.cur].vol;
    s->p3C[m->sub.cur] = 0;
    func_00416210((char*)s + m->sub.cur * 8 + 0x40, 0, 8);
    s->p60[m->sub.cur] = 0;
    s->p64[m->sub.cur] = 0;
    s->p68[m->sub.cur] = 0;
    s->p6C[m->sub.cur] = 0;
    s->p70[m->sub.cur].f4 = 0;
    s->p70[m->sub.cur].f0 = 100;
    s->p70[m->sub.cur].f8 = 90;
    s->p70[m->sub.cur].fC = 50;
    s->p74[m->sub.cur] = 0;
    s->p80[m->sub.cur] = 0;
    s->p84[m->sub.cur] = 0;
    s->p78[m->sub.cur] = 0x7F;
    s->p7C[m->sub.cur] = 1;
    snd->a4[snd->mgr->sub.cur] = a;
    snd->a8[snd->mgr->sub.cur] = b;
}

// Rider animation sounds: drops finished voices, then starts the event's voices for this frame (flag 1) or
// stops the voices the event no longer lists (flag 2).
extern "C" void cRider_updateNISSounds(void* vself, void* vevt, float frame, float unused, int flags)
{
    char* self = (char*)vself;
    char* evt = (char*)vevt;
    sRider5448* rd = (sRider5448*)vself;
    sSnd5448Sys* snd = (sSnd5448Sys*)func_0028B180();
    int j;
    for (j = 0; j < 4; j++) {
        if (rd->ids[j] >= 0 && cBankMonitor_findVoice(&(*snd->p118)->sub, rd->ids[j], 1) == 0) {
            rd->ids[j] = -1;
        }
    }
    if (flags & 1) {
        for (sSndEvt5448* e = *(sSndEvt5448**)(evt + 0xC); e; e = e->next) {
            char* pos = self + 0x110;
            if ((float)e->frame != frame) goto done;
            int b;
            int a;
            func_00280548(self + 0x6D0, e->id, &b, &a);
            snd5448AddVoice(snd, a, b);
            sSnd5448Mgr* m2 = *snd->p118;
            sSnd5448Sub* s2 = &m2->sub;
            s2->vals[m2->sub.cur] = *e->vol;
            s2->ch[m2->sub.cur].vol = SND_5448_MAX(0, SND_5448_MIN(s2->vals[s2->cur], 0x7F));
            sSnd5448Mgr** pp = snd->p118;
            int r = (int)cSSXAudio_getBusVolumePtr(snd, 4, 0);
            (*pp)->sub.p3C[(*pp)->sub.cur] = r;
            sSnd5448Mgr* m3 = *snd->p118;
            m3->sub.tgt[m3->sub.cur] = pos;
            sSnd5448Mgr** pq = snd->p118;
            int q = cSSXAudio_getRiderListener(snd, self);
            (*pq)->sub.p64[(*pq)->sub.cur] = q;
            rd->ids[e->slot] = func_002906B8(snd);
        }
    done:;
    } else if (flags & 2) {
        int stop[4];
        for (j = 0; j < 4; j++) stop[j] = 1;
        for (sSndEvt5448* e = *(sSndEvt5448**)(evt + 0xC); e; e = e->next) {
            stop[e->slot] = 0;
        }
        for (j = 0; j < 4; j++) {
            if (stop[j] && rd->ids[j] >= 0) {
                cBankMonitor_stopVoice(&(*snd->p118)->sub, rd->ids[j], 1, 0.0f);
                rd->ids[j] = -1;
            }
        }
    }
}

//100%
extern "C" void func_00125958(void* self, int a1)
{
    *(int*)((char*)self + 0xb2c) = a1;
    if (a1 == 0) {
        *(int*)((char*)self + 0x2f4) = 0;
        *(int*)((char*)self + 0x2f0) = 0;
    }
}

//100%
extern "C" float func_002EF0A0(int rider);
extern "C" float func_002EE570(int rider);
extern float D_00504FB8[];

struct sVec4_125970
{
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sVEntry_125970 { short delta; short index; void (*fn)(void*, sVec4_125970*); };

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float Dot_125970(const sVec4_125970& a, const sVec4_125970& b)
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

// PORT: PS2-only VU0 inline asm (v * s).
static inline sVec4_125970 Scale_125970(const sVec4_125970& v, float s)
{
    sVec4_125970 r;
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

extern "C" void cRider_applyWindPush(char* self)
{
    if (*(int*)(self + 0x874) == 0)
        return;
    float maxSpeed = 1388.888916015625f;
    float speed = func_002EF0A0(*(int*)(self + 0x86C)) * 27.77777862548828f;
    if (speed > maxSpeed)
        speed = maxSpeed;
    if (speed >= 277.77777099609375f)
    {
        float ang = func_002EE570(*(int*)(self + 0x86C)) * 0.01745329424738884f;
        sVec4_125970 dir;
        dir.z = 0.0f;
        dir.w = 0.0f;
        int idx = (int)(ang * 81.4873275756836f) & 0x1FF;
        dir.y = D_00504FB8[idx];
        dir.x = D_00504FB8[idx + 0x80];
        float d = speed - Dot_125970(*(sVec4_125970*)(self + 0x1E0), dir);
        if (d > dir.z)
        {
            sVec4_125970 imp = Scale_125970(Scale_125970(dir, d), 0.015000000596046448f);
            char* obj = self + 0x6C0;
            sVEntry_125970* vt = *(sVEntry_125970**)obj;
            vt[4].fn(obj + vt[4].delta, &imp);
        }
    }
}

//100%
void cRider_EmptyProgressHook(void* self)
{
}

//100%
extern "C" int cRider_GetSyncChecksum(void* self)
{
    union { float f; int i; } u;
    u.f = *(float*)((char*)self + 0x110) + *(float*)((char*)self + 0x114) + *(float*)((char*)self + 0x118)
        + (*(float*)((char*)self + 0x120) + *(float*)((char*)self + 0x124) + *(float*)((char*)self + 0x128) + *(float*)((char*)self + 0x12C));
    return u.i;
}

//100%
extern "C" void func_00326CF0(void* obj);

struct sVEntryI_125B18 { short delta; short index; int (*fn)(void*); };
struct sVEntryF_125B18 { short delta; short index; void (*fn)(void*, float, int); };

// PORT: the unit declares (void*, int, int); the second argument is really an object pointer.
extern "C" void updatePadRumble(void* p, int a, int on)
{
    float* s = (float*)p;
    void* obj = (void*)a;
    if (on == 0)
    {
        s[0] = s[1] = 0.0f;
        func_00326CF0(obj);
        return;
    }
    float v = s[0] * 0.9133333563804626f - 18.518518447875977f;
    float r = 0.0f;
    if (v >= 0.0f)
        r = v;
    s[0] = r;
    s[1] *= 0.9916666746139526f;
    sVEntryI_125B18* vt = *(sVEntryI_125B18**)obj;
    if (vt[3].fn((char*)obj + vt[3].delta) == 2)
    {
        sVEntryF_125B18* vt2 = *(sVEntryF_125B18**)obj;
        vt2[4].fn((char*)obj + vt2[4].delta, ((s[1] - 0.5f) * 0.009999999776482582f >? (s[0] - 2.0f) / 972.2222290039062f) >? 0.0f, 0);
        sVEntryF_125B18* vt3 = *(sVEntryF_125B18**)obj;
        vt3[4].fn((char*)obj + vt3[4].delta, ((s[1] - 70.0f) * 0.0062500000931322575f >? (s[0] - 100.0f) / 5000.0f) >? 0.0f, 1);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
// g++ 2.95 vtable entry (no thunks): {delta, index, fn}. Vtables are double-aligned.
struct sVtEnt_125C70 {
    short delta;
    short index;
    void* fn;
};
struct sVt9_125C70 {
    sVtEnt_125C70 e[9];
} __attribute__((aligned(8)));
struct sVt22_125C70 {
    sVtEnt_125C70 e[22];
} __attribute__((aligned(8)));
extern const sVt9_125C70 D_00458360;
extern const sVt22_125C70 D_004583A8;
extern char D_00459B90[];
extern char D_00458338[];
extern void* D_004A28A8;
extern "C" void cRider_cRider(void* self);
extern "C" void cMotionOwner_cMotionOwner(void* self, int inChrg);
extern "C" void* cReplay_addCache(void* p);

// PORT: hand-written form of g++ 2.95's constructor for a class with a virtual base
// (cRider at +0xE10): vtable copies with delta fixups when not in charge.
extern "C" void* cPlayer_cPlayer(char* self, int inChrg)
{
    sVt9_125C70 t1;
    sVt22_125C70 t2;
    if (inChrg) {
        char* vb = self + 0xE10;
        *(void**)(self + 0xD20) = vb;
        *(void**)(self + 0xC70) = vb;
        *(void**)(self + 0xB40) = vb;
        *(void**)(self + 0xB00) = vb;
        *(void**)(self + 0xAF0) = vb;
        *(void**)(self + 0xAD0) = vb;
        *(void**)(self + 0x9C0) = vb;
        *(void**)(self + 0x610) = vb;
        *(void**)(self + 0x520) = vb;
        *(void**)(self + 0x470) = vb;
        *(void**)(self + 0x3B0) = vb;
        *(void**)(self + 0x3A0) = vb;
        *(void**)(self + 0x398) = vb;
        *(void**)(self + 0x384) = vb;
        *(void**)(self + 0x364) = vb;
        *(void**)(self + 0x358) = vb;
        *(void**)(self + 0x340) = vb;
        *(void**)(self + 0x2B8) = vb;
        *(void**)(self + 0x2A4) = vb;
        *(void**)(self + 0x288) = vb;
        *(void**)(self + 0x224) = vb;
        *(void**)(self + 0x200) = vb;
        *(void**)(self + 0x1F0) = vb;
        *(void**)(self + 0x1E4) = vb;
        *(void**)(self + 0x1C0) = vb;
        *(void**)(self + 0x1B0) = vb;
        *(void**)(self + 0x100) = vb;
        *(void**)(self + 0xA0) = vb;
        *(void**)(self + 0x70) = vb;
        *(void**)(self + 0x24) = vb;
        *(void**)(self + 0x18) = vb;
        cRider_cRider(vb);
    }
    cMotionOwner_cMotionOwner(self, 0);
    *(void**)(*(char**)(self + 0x18) + 0x6E8) = (void*)&D_00458360;
    *(void**)(*(char**)(self + 0x18) + 0x6D0) = D_00459B90;
    *(void**)(*(char**)(self + 0x18) + 0x6C0) = (void*)&D_004583A8;
    if (inChrg == 0) {
        int vc;
        t1 = D_00458360;
        *(void**)(*(char**)(self + 0x18) + 0x6E8) = &t1;
        {
            char* vbo = *(char**)(self + 0x18) - 0xE10;
            vc = self - vbo;
        }
        t1.e[1].delta = D_00458360.e[1].delta + vc;
        t2 = D_004583A8;
        *(void**)(*(char**)(self + 0x18) + 0x6C0) = &t2;
        t2.e[1].delta = D_004583A8.e[1].delta + vc;
        t2.e[16].delta = D_004583A8.e[16].delta + vc;
        t2.e[17].delta = D_004583A8.e[17].delta + vc;
        t2.e[18].delta = D_004583A8.e[18].delta + vc;
        t2.e[19].delta = D_004583A8.e[19].delta + vc;
        t2.e[20].delta = D_004583A8.e[20].delta + vc;
    }
    *(void**)(self + 0xDE8) = D_00458338;
    *(int*)(self + 0xDF4) = 0;
    *(int*)(self + 0xDFC) = 0;
    *(int*)(self + 0xE00) = 0;
    *(int*)(*(char**)(self + 0x18) + 0x874) = 1;
    *(void**)(self + 0xDF8) = cReplay_addCache(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28));
    return self;
}

INCLUDE_ASM("ai/rider", cPlayer_destroy);

//100%
int func_00320C48(void*, int);
extern "C" int cPlayer_getGrabInput(char* self)
{
    if (func_00320C48(*(void**)(self + 0xDF0), 0x1F))
        return 0;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x20))
        return 1;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x21))
        return 2;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x22))
        return 3;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x23))
        return 4;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x24))
        return 5;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x25))
        return 6;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x26))
        return 7;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x27))
        return 8;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x28))
        return 9;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x29))
        return 10;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x2A))
        return 11;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x2B))
        return 12;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x2C))
        return 13;
    if (func_00320C48(*(void**)(self + 0xDF0), 0x2D))
        return 14;
    return -1;
}

//100%
int func_00320C48(void*, int);

extern "C" int cPlayer_getUberInput(void* self)
{
    if (func_00320C48(*(void**)((char*)self + 0xDF0), 0x1B))
        return 0;
    if (func_00320C48(*(void**)((char*)self + 0xDF0), 0x1C))
        return 1;
    if (func_00320C48(*(void**)((char*)self + 0xDF0), 0x1D))
        return 2;
    if (func_00320C48(*(void**)((char*)self + 0xDF0), 0x1E))
        return 3;
    return -1;
}

//100%
void cPlayer_clearRumble(void* self)
{
    *(float*)((char*)self + 0xE00) = 0.0f;
    *(float*)((char*)self + 0xDFC) = 0.0f;
}

//100%
extern "C" void cPlayer_addRumbleImpact(void* self, float val)
{
    *(float*)((char*)self + 0xDFC) = val >? *(float*)((char*)self + 0xDFC);
}

//100%
void cPlayer_setRumbleSlide(void* self, float val)
{
    *(float*)((char*)self + 0xE00) = val;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int func_001474E8(void* iface, int id);
extern "C" void updatePadRumble(void* p, int a, int b);

struct sVEntry001278E8 { short delta; short index; int (*fn)(void*); };

static inline bool riderInRange_1278E8(int v)
{
    return v != 0 && v < 10;
}

extern "C" void cPlayer_updateRumble(void* self)
{
    char* s = (char*)self;
    if (*(int*)(s + 0xDF4) != 0)
    {
        int flag = 0;
        void* iface = cBE_getInterface_Fv(cBE_getBE(), 1);
        char* sub = *(char**)(s + 0x18) + 0x6C0;
        sVEntry001278E8* vt = *(sVEntry001278E8**)sub;
        if (func_001474E8(iface, vt[7].fn(sub + vt[7].delta)) != 0)
        {
            flag = !riderInRange_1278E8(**(int**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28));
        }
        updatePadRumble(s + 0xDFC, *(int*)(s + 0xDF4), flag);
    }
}

INCLUDE_ASM("ai/rider", cPlayer_buildInputCommand);

extern "C" void* cMotionOwner_saveState(void* self);

//100%
void* cPlayer_saveState(void* self)
{
    return cMotionOwner_saveState(self);
}

extern "C" void* cMotionOwner_loadState(void* self);

//100%
void* cPlayer_loadState(void* self)
{
    return cMotionOwner_loadState(self);
}

