#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void cBEScoreInterface_ctor(void* self);
extern const char D_0045A858[];
extern void* D_004A1248;

struct cBEScoreInterface {
    char pad_0x00[8];
    int field_0x8;
    char pad_0xC[4];
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1C;
};

//100%
// PORT: the unit declares cBEScoreInterface_ctor as returning void; the body returns self.
void* cBEScoreInterface_ctor_impl(void* self) __asm__("cBEScoreInterface_ctor");

void* cBEScoreInterface_getThis()
{
    if (D_004A1248 == 0) {
        void* mem = cMemMan_alloc(0x230, D_0045A858, 0, 0);
        cBEScoreInterface* s = (cBEScoreInterface*)cBEScoreInterface_ctor_impl(mem);
        D_004A1248 = s;
        s->field_0x8 = 0;
        s->field_0x10 = 0;
        s->field_0x14 = 0;
        s->field_0x18 = -1;
        s->field_0x1C = -1;
    }
    return D_004A1248;
}

//100%
extern "C" void cBEScoreInterface_Reset(void* self);
extern void* D_0045ACA8[];

// PORT: the unit declares cBEScoreInterface_ctor as returning void (used by getThis);
// the body returns self, so it is bound to the symbol with an asm label.
void* cBEScoreInterface_ctor_impl(void* self) __asm__("cBEScoreInterface_ctor");

void* cBEScoreInterface_ctor_impl(void* self)
{
    *(void***)((char*)self + 0xC) = D_0045ACA8;
    cBEScoreInterface_Reset(self);
    return self;
}

//100%
void func_001549E0(void* self)
{
}

//100%
extern "C" void func_003E6448(void* dst, int value, int size);

struct sScoreSlot_001549E8 {
    char pad_0x00[0xAC];
    int last; // 0xAC
};

struct sScore_001549E8 {
    char pad_0x00[0x10];
    int a;    // 0x10
    int b;    // 0x14
    int c;    // 0x18
    int d;    // 0x1C
    sScoreSlot_001549E8 slots[2]; // 0x20
};

extern "C" void cBEScoreInterface_Reset(void* p)
{
    sScore_001549E8* self = (sScore_001549E8*)p;
    self->a = 0;
    self->b = 0;
    self->c = -1;
    self->d = -1;
    func_003E6448(self->slots, 0, sizeof(self->slots));
    for (int i = 1; i >= 0; i--)
    {
        self->slots[i].last = -1;
    }
}

//100%
int cBELibrary_getProfileIndex(int);
extern "C" void func_00155420(int rider, int a, int b, int c);
extern signed char D_005305F9[];

extern "C" void func_00154A58(int rider, int a)
{
    int profile = cBELibrary_getProfileIndex(rider);
    if (D_005305F9[0] == 0 && profile < 2)
    {
        func_00155420(rider, a, -1, -1);
    }
}

INCLUDE_ASM("be/beintscore", func_00154AB8);

//100%
// Records the rider's race result: stores it on the profile slot, reports the event, and posts the medal (gold/silver/bronze or none) when the time or score beats the course target.
struct sGame54EE8 {
    char pad_0x0[0x40];
    int course;         // 0x40
    char pad_0x44[4];
    signed char f48;    // 0x48
    signed char f49;    // 0x49
};
extern sGame54EE8 D_005305B0_54EE8 __asm__("D_005305B0");
extern int D_0043D950[];
extern signed char D_00535C12[];
struct sCourse54EE8 { int id; char pad[0x60]; };
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
signed char cBELibrary_getCharacterID(int index);
extern "C" int func_00155328(void* self, int a);
extern "C" void func_001E25D8(int mode, int course, int a);
extern "C" void func_001E1EB8();
extern "C" void func_001E1550();
extern "C" int func_001456A0(void* self, int idx, int mode);
extern "C" void func_001591E8(void* self, int profile, int c, int mode, int course, int medal);

extern "C" void func_00154EE8(char* self, int rider, int result, int target)
{
    int profile = cBELibrary_getProfileIndex(rider);
    if (profile >= 2)
        return;
    *(int*)(self + profile * 0xB0 + 0xCC) = result;
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 0);
    int c = cBELibrary_getCharacterID(rider);
    int course = ((sCourse54EE8*)D_0043D950)[D_005305B0_54EE8.course].id;
    int mode = D_00535C12[0];
    if (course == 0x16)
        course = 0;
    int medal = func_00155328(self, result);
    if (mode == 4 || mode == 5)
        medal = result == 0 ? 1 : -1;
    if (D_005305B0_54EE8.f49 == 0)
        func_001E25D8(mode, course, result);
    if (medal == -1)
        return;
    if (D_005305B0_54EE8.f49 == 0)
    {
        func_001E1EB8();
        if (D_005305B0_54EE8.f49 == 0 && mode != 4 && mode != 5)
            func_001E1550();
    }
    void* score = cBE_getInterface_Fv(cBE_getBE(), 0xD);
    if (D_005305B0_54EE8.f49 != 0 || D_005305B0_54EE8.f48 == 4)
        return;
    int best = func_001456A0(iface, course, mode);
    if (best != -1)
    {
        if (mode == 0 || mode == 4)
        {
            if (!(best * 60 < target))
                medal = 0;
        }
        else if (!(target < best))
            medal = 0;
    }
    func_001591E8(score, profile, c, mode, course, medal);
}

//100%
struct sScoreEntry_001550E8 {
    int value;
    char pad[0x10];
};
extern "C" sScoreEntry_001550E8* func_0014AB20(int a, int b);

extern "C" int func_001550E8(void* self, int i, int a, int b)
{
    sScoreEntry_001550E8* t = func_0014AB20(a, b);
    if (t != 0) {
        return t[i].value;
    }
    return 0;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern int D_005305F0[];
extern signed char D_00535C12[];

extern "C" int func_00155130(void* self, int i)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    sScoreEntry_001550E8* t = func_0014AB20(D_005305F0[0], D_00535C12[0]);
    if (t != 0)
    {
        return t[i].value;
    }
    return 0;
}

//100%
struct sScoreEntryB_00155190
{
    int value;
    int idx;
    char pad[0xC];
};
struct sScoreSlot_00155190
{
    char data[0x88];
};
extern sScoreSlot_00155190 D_00530990[];
extern void* D_004A1244;

extern "C" void* func_00155190(void* self, int i)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    sScoreEntryB_00155190* t = (sScoreEntryB_00155190*)func_0014AB20(D_005305F0[0], D_00535C12[0]);
    if (t == 0)
        return D_004A1244;
    return &D_00530990[t[i].idx];
}

//100%
struct sScoreEntryB_00155208
{
    int value;
    int idx;
    char f8[0xC];
};
extern void* D_004A1244;

extern "C" void* func_00155208(void* self, int i)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    sScoreEntryB_00155208* t = (sScoreEntryB_00155208*)func_0014AB20(D_005305F0[0], D_00535C12[0]);
    if (t != 0)
        return t[i].f8;
    return D_004A1244;
}

//100%
extern "C" void* func_00155270(void* self, int a1)
{
    return (char*)self + (a1 * 0xb0 + 0x20);
}

//100%
extern char D_004A6CA8[];

extern "C" void* func_00155288(void* self, int a1, int a2)
{
    char* p = D_004A6CA8 + (a1 * 0x9b50 + a2 * 0xf88);
    return p + 0xde4;
}

signed char cBELibrary_getCharacterID(int index);
extern char D_004A6CA8[];

//97.94%
INCLUDE_ASM("be/beintscore", cBEScoreInterface_getCurrentHighlightLevel__FPvi);

//100%
// Compares two scores where -1 means none: none for b gives 0, none for a gives 1, otherwise b < a.
extern "C" int func_001552F8(void* self, int a, int b)
{
    if (b == -1)
        return 0;
    if (a == -1)
        return 1;
    return b < a;
}

//100%
extern "C" int func_00155328(void* self, int a)
{
    switch (a) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    }
    return -1;
}

//100%
void cBEScoreInterface_SaveState(void* self)
{
}

//100%
void cBEScoreInterface_LoadState(void* self)
{
}

//100%
extern short D_00440ED0[][3];

extern "C" void func_00155390(char* self, int idx, int score)
{
    signed char cur = *(signed char*)(self + idx + 0xBB8);
    int level = 0;
    int i;
    for (i = 2; i >= 0; i--) {
        if (score >= D_00440ED0[idx][i]) {
            level = i + 1;
            break;
        }
    }
    if (cur < level) {
        *(signed char*)(self + idx + 0xBB8) = level;
    }
}

//100%
struct sGame5420 {
    char pad_0x0[0x40];
    int course;         // 0x40
    char pad_0x44[4];
    signed char f48;    // 0x48
    signed char f49;    // 0x49
    signed char f4A;    // 0x4A
};
extern sGame5420 D_005305B0_5420[] __asm__("D_005305B0");
extern int D_0043D950[];

struct sStats5420 {
    char pad_0x0[0x18];
    int f18;
    int f1C;
    int f20;
    char pad_0x24[8];
    int f2C;
    char pad_0x30[0x20];
    float f50;
    char pad_0x54[4];
    float f58;
    float f5C;
    char pad_0x60[0x28];
    int f88;
};

struct sProf5420 { char s[0xF88]; };

struct sCourse5420 { int id; char pad[0x60]; };

struct sRec5420 {
    int score;
    int course;
};

extern "C" void func_00155420(int index, int stats_, int a2, int a3)
{
    sStats5420* stats = (sStats5420*)stats_;
    sGame5420* g = D_005305B0_5420;
    int profile;
    int c;
    int course;
    signed char mode;
    signed char f48;
    char* p;
    sRec5420* rec;
    int i;
    if (g->f49 != 0) return;
    profile = cBELibrary_getProfileIndex(index);
    if ((unsigned int)profile >= 3) return;
    c = cBELibrary_getCharacterID(index);
    mode = g->f4A;
    f48 = g->f48;
    p = ((sProf5420 (*)[10])D_004A6CA8)[profile][c].s;
    course = ((sCourse5420*)D_0043D950)[g->course].id;
    rec = (sRec5420*)(p + 0xDE4);
    if (course == 0x16) course = 0;
    {
        int start = 0;
        if (stats == 0 || mode == 12) start = 8;
        i = start;
    }
    for (; i < 10; i++) {
        sRec5420* e = &rec[i];
        int v;
        switch (i) {
        case 0:
            v = stats->f2C;
            if (v >= e->score) { e->score = v; e->course = course; func_00155390(p, 3, v); }
            break;
        case 1:
            v = stats->f18;
            if (v >= e->score) { e->score = v; e->course = course; }
            break;
        case 2:
            v = stats->f1C;
            if (v >= e->score) { e->score = v; e->course = course; func_00155390(p, 5, v); }
            break;
        case 3:
            v = stats->f20;
            if (v >= e->score) { e->score = v; e->course = course; func_00155390(p, 4, v); }
            break;
        case 4:
            v = stats->f88;
            if (v >= e->score) { e->score = v; e->course = course; func_00155390(p, 7, v); }
            break;
        case 5:
            v = (int)(stats->f5C + 0.5f);
            if (v >= e->score) { e->score = v; e->course = course; func_00155390(p, 1, v); }
            break;
        case 6:
            v = (int)(stats->f58 + 0.5f);
            if (v >= e->score) { e->score = v; e->course = course; func_00155390(p, 0, v); }
            break;
        case 7:
            v = (int)(stats->f50 + 0.5f);
            if (v >= e->score) { e->score = v; e->course = course; func_00155390(p, 2, v); }
            break;
        case 8:
            if (a3 > 0 && mode == 0) {
                if (e->score == 0 || e->score >= a3) { e->score = a3; e->course = course; }
            }
            break;
        case 9:
            if (a2 > 0) {
                if ((unsigned int)(mode - 1) < 3 || f48 == 6) {
                    if (a2 >= e->score) { e->score = a2; e->course = course; func_00155390(p, 6, a2 / 100); }
                }
            }
            break;
        }
    }
    if (stats != 0) {
        if (stats->f88 >= rec[10].score) rec[10].score = stats->f88;
    }
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" bool func_0014F810(int i);
extern int D_00535BFC[];

extern "C" bool func_001557E0(void* self, int rider)
{
    if (rider >= 2 || func_0014F810(0))
        return false;
    cBE_getInterface_Fv(cBE_getBE(), 0);
    if (D_00535BFC[0] >= 2)
        return !func_0014F810(0);
    return true;
}

//100%
// Returns the 16-bit value at 0x2 of the rider's score stats for (a, b), or 0 when unavailable.
void* cBECharProfileDB_getScoreStats(void* self, int a, int b);
extern signed char D_005305F9[];
extern char D_004A6CA8[];

extern "C" int func_00155848(void* self, int rider, int a, int b)
{
    if (D_005305F9[0] != 0)
        return 0;
    int profile = cBELibrary_getProfileIndex(rider);
    if ((unsigned int)profile >= 3)
        return 0;
    int c = cBELibrary_getCharacterID(rider);
    unsigned short* stats = (unsigned short*)cBECharProfileDB_getScoreStats(D_004A6CA8 + profile * 0x9b50 + c * 0xf88, a, b);
    if (stats == 0)
        return 0;
    return stats[1];
}

//100%
int cBELibrary_getProfileIndex(int);
signed char cBELibrary_getCharacterID(int index);
void* cBECharProfileDB_getScoreStats(void* self, int a, int b);
extern signed char D_005305F9[];
extern char D_004A6CA8[];

extern "C" int func_001558F8(void* self, int rider, int a, int b)
{
    if (D_005305F9[0] != 0)
        return -1;
    int profile = cBELibrary_getProfileIndex(rider);
    if ((unsigned int)profile >= 3)
        return -1;
    int c = cBELibrary_getCharacterID(rider);
    signed char* stats = (signed char*)cBECharProfileDB_getScoreStats(D_004A6CA8 + profile * 0x9b50 + c * 0xf88, a, b);
    if (stats == 0)
        return -1;
    return stats[1];
}


//100%
// Passes a, b and c to func_00152528 on the rider's character profile record.
extern "C" void func_00152528(void* rec, int a, int b, int c);

extern "C" void func_001559A8(void* self, int rider, int a, int b, int c)
{
    if (D_005305F9[0] != 0)
        return;
    int profile = cBELibrary_getProfileIndex(rider);
    if ((unsigned int)profile >= 3)
        return;
    int ch = cBELibrary_getCharacterID(rider);
    func_00152528(D_004A6CA8 + profile * 0x9b50 + ch * 0xf88, a, b, c);
}
