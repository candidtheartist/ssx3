#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A718[];
extern void* D_0045AC78[16];
extern void* D_004A1214;

struct cBEEconInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//99.58%
void* cBEEconInterface_getThis()
{
    if (D_004A1214 == 0) {
        cBEEconInterface* mem = (cBEEconInterface*)cMemMan_alloc(0x10, D_0045A718, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045AC78;
        D_004A1214 = mem;
    }
    return D_004A1214;
}

//100%
extern int D_004A6CA8[];

extern "C" int func_00150928(void* self, int a, int b)
{
    if (a >= 2) {
        return 0;
    }
    int bOff = b * 0xF88;
    int aOff = a * 0x9B50;
    int off = bOff + aOff;
    char* p = (char*)D_004A6CA8 + off;
    return *(int*)(p + 0xAC4);
}

//100%
int cBELibrary_getProfileIndex(int);
int cBELibrary_getCharacterID(int);

extern "C" int func_00150960(void* self, int rider)
{
    int a = cBELibrary_getProfileIndex(rider);
    int b = cBELibrary_getCharacterID(rider);
    int bOff = b * 0xF88;
    int aOff = a * 0x9B50;
    int off = bOff + aOff;
    char* p = (char*)D_004A6CA8 + off;
    return *(int*)(p + 0xAC4);
}

extern int D_004A6CA8[];

//100%
int cBEEconInterface_getTotalMoneyEarned(void* self, int a, int b)
{
    if (a >= 2) {
        return 0;
    }
    int bOff = b * 0xF88;
    int aOff = a * 0x9B50;
    int off = bOff + aOff;
    char* p = (char*)D_004A6CA8 + off;
    return *(int*)(p + 0xAC8);
}

//100%
int cBELibrary_getProfileIndex(int);
int cBELibrary_getCharacterID(int);

extern "C" int func_001509F8(void* self, int rider)
{
    int a = cBELibrary_getProfileIndex(rider);
    int b = cBELibrary_getCharacterID(rider);
    int bOff = b * 0xF88;
    int aOff = a * 0x9B50;
    int off = bOff + aOff;
    char* p = (char*)D_004A6CA8 + off;
    return *(int*)(p + 0xAC8);
}

extern "C" void func_00150A58(void* self, int a, int b, int value)
{
    if (a >= 2) {
        return;
    }
    int bOff = b * 0xF88;
    int aOff = a * 0x9B50;
    int off = bOff + aOff;
    char* p = (char*)D_004A6CA8 + off;
    *(int*)(p + 0xAC4) = value;
}

//100%
extern int D_004A6CA8[];

extern "C" int func_00150A90(void* self, int a, int b, int amount)
{
    if (a >= 2) {
        return 0;
    }
    int bOff = b * 0xF88;
    int aOff = a * 0x9B50;
    int off = bOff + aOff;
    char* p = (char*)D_004A6CA8 + off;
    *(int*)(p + 0xAC4) += amount;
    *(int*)(p + 0xAC8) += amount;
    return *(int*)(p + 0xAC4);
}

//100%
// Applies amount to the rider's profile and character through func_00150A90.
int cBELibrary_getProfileIndex(int);
int cBELibrary_getCharacterID(int);

extern "C" int func_00150AE0(void* self, int rider, int amount)
{
    int profile = cBELibrary_getProfileIndex(rider);
    int c = cBELibrary_getCharacterID(rider);
    return func_00150A90(self, profile, c, amount);
}

//100%
extern int D_004A6CA8[];

extern "C" int func_00150B48(void* self, int a, int b, int amount)
{
    if (a >= 2) {
        return 0;
    }
    int bOff = b * 0xF88;
    int aOff = a * 0x9B50;
    int off = bOff + aOff;
    char* p = (char*)D_004A6CA8 + off;
    return *(int*)(p + 0xAC4) -= amount;
}

//100%
extern int D_004A6CA8[];

// PORT: 64-bit unsigned long flag word (bit 12 = peak 1 locked, bit 13 = peak 2).
struct sPeakBits_0B88 {
    unsigned long low : 12;
    unsigned long peak1 : 1;
    unsigned long peak2 : 1;
    unsigned long rest : 50;
};

// Sets the locked state of a peak for a profile/character: stores the inverse of `unlocked`.
extern "C" int BE_SetPeakUnlocked(void* self, int a, int b, int peak, int unlocked)
{
    if (a >= 2) {
        return 0;
    }
    unlocked ^= 1;
    if (peak == 1) {
        int bOff = b * 0xF88;
        int aOff = a * 0x9B50;
        int off = bOff + aOff;
        char* p = (char*)D_004A6CA8 + off;
        ((sPeakBits_0B88*)(p + 0x278))->peak1 = unlocked;
    } else if (peak == 2) {
        int bOff = b * 0xF88;
        int aOff = a * 0x9B50;
        int off = bOff + aOff;
        char* p = (char*)D_004A6CA8 + off;
        ((sPeakBits_0B88*)(p + 0x278))->peak2 = unlocked;
    }
    return 1;
}

//100%
struct sProf0C20 { char s[0xF88]; };
extern "C" void* func_00147F78(void);
typedef void (*fn0C20)(void*);
int func_00150E50(void* self, int a1);

extern "C" int func_00150C20(void* self, int profile, int c, unsigned int kind)
{
    char* p;
    int money;
    int cost;
    if (profile >= 2) return 0;
    p = 0;
    {
        int off = c * 0xF88 + profile * 0x9B50;
        char* q = (char*)D_004A6CA8 + off;
        money = *(int*)(q + 0xAC4);
    }
    switch (kind) {
    case 0: p = &((sProf0C20 (*)[10])D_004A6CA8)[profile][c].s[0xBDF]; break;
    case 1: p = &((sProf0C20 (*)[10])D_004A6CA8)[profile][c].s[0xBE0]; break;
    case 2: p = &((sProf0C20 (*)[10])D_004A6CA8)[profile][c].s[0xBE1]; break;
    case 3: p = &((sProf0C20 (*)[10])D_004A6CA8)[profile][c].s[0xBE2]; break;
    case 4: p = &((sProf0C20 (*)[10])D_004A6CA8)[profile][c].s[0xBE3]; break;
    case 5: p = &((sProf0C20 (*)[10])D_004A6CA8)[profile][c].s[0xBE4]; break;
    case 6: p = &((sProf0C20 (*)[10])D_004A6CA8)[profile][c].s[0xBE5]; break;
    }
    cost = func_00150E50(self, *p / 5 - 1);
    if (money < cost) return 0;
    if (*p != 0x37) {
        {
            int off = c * 0xF88 + profile * 0x9B50;
            char* q = (char*)D_004A6CA8 + off;
            *(int*)(q + 0xAC4) -= cost;
        }
        (*p)++;
        {
            char* o = (char*)func_00147F78();
            char* vt = *(char**)(o + 0xC);
            ((fn0C20)*(void**)(vt + 0x14))(o + *(short*)(vt + 0x10));
        }
        return 1;
    }
    return 0;
}

extern void* D_00440550[];

//100%
struct sEconEntry {
    int key;
    int value;
};

struct sEconTable {
    sEconEntry entries[1];
};

int func_00150E50(void* self, int a1)
{
    return ((sEconTable*)D_00440550)->entries[a1].value;
}

//100%
struct sProf0E68 { char s[0xF88]; };
struct sEcon0E68 { int a; int b; };
extern sEcon0E68 D_00440550_0E68[] __asm__("D_00440550");

extern "C" int func_00150E68(void* self, int profile, int c, unsigned int kind)
{
    char* p;
    if (profile >= 2) return 0;
    p = 0;
    switch (kind) {
    case 0: p = &((sProf0E68 (*)[10])D_004A6CA8)[profile][c].s[0xBDF]; break;
    case 1: p = &((sProf0E68 (*)[10])D_004A6CA8)[profile][c].s[0xBE0]; break;
    case 2: p = &((sProf0E68 (*)[10])D_004A6CA8)[profile][c].s[0xBE1]; break;
    case 3: p = &((sProf0E68 (*)[10])D_004A6CA8)[profile][c].s[0xBE2]; break;
    case 4: p = &((sProf0E68 (*)[10])D_004A6CA8)[profile][c].s[0xBE3]; break;
    case 5: p = &((sProf0E68 (*)[10])D_004A6CA8)[profile][c].s[0xBE4]; break;
    case 6: p = &((sProf0E68 (*)[10])D_004A6CA8)[profile][c].s[0xBE5]; break;
    }
    if (*p == 5) return 0;
    {
        int v = D_00440550_0E68[(*p - 1) / 5].b;
        int off = c * 0xF88 + profile * 0x9B50;
        char* q = (char*)D_004A6CA8 + off;
        *(int*)(q + 0xAC4) += v;
    }
    (*p)++;
    return 1;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int func_00145630(void* race, int place, int kind);

struct sEconPrize_151040
{
    int key;
    int prize[4];
};
extern sEconPrize_151040 D_004405A0[];

extern "C" int func_00151040(void* self, int medal, int key, int place)
{
    void* race = cBE_getInterface_Fv(cBE_getBE(), 0);
    int r = 0;
    if ((unsigned int)(place - 6) < 6)
    {
        switch (medal)
        {
        case 0:
        case 1:
            r = func_00145630(race, place, 2);
            break;
        case 2:
            r = func_00145630(race, place, 1);
            break;
        case 3:
            r = func_00145630(race, place, 0);
            break;
        }
    }
    else
    {
        for (int i = 0; i < 17; i++)
        {
            if (D_004405A0[i].key != key) continue;
            switch (medal)
            {
            case 0:
                r = D_004405A0[i].prize[0] * 100;
                break;
            case 1:
                r = D_004405A0[i].prize[1] * 100;
                break;
            case 2:
                r = D_004405A0[i].prize[2] * 100;
                break;
            case 3:
                r = D_004405A0[i].prize[3] * 100;
                break;
            }
        }
    }
    return r;
}

//100%
extern "C" int func_00151178(void* self, int level)
{
    switch (level)
    {
    case 0:
    default:
        return 500;
    case 1:
        return 1000;
    case 2:
        return 2000;
    }
}

//100%
extern "C" int func_001511B0(void* self, int level)
{
    switch (level)
    {
    case 1:
    default:
        return 2000;
    case 2:
        return 4000;
    case 3:
        return 6000;
    }
}

//100%
struct sProf11E8 { char s[0xF88]; };
struct sEcon11E8 { int a; int b; };
extern sEcon11E8 D_00440550_11E8[] __asm__("D_00440550");

extern "C" int func_001511E8(void* self, int profile, int c, unsigned int kind)
{
    char* p;
    if (profile >= 2) return 0;
    p = 0;
    switch (kind) {
    case 0: p = &((sProf11E8 (*)[10])D_004A6CA8)[profile][c].s[0xBDF]; break;
    case 1: p = &((sProf11E8 (*)[10])D_004A6CA8)[profile][c].s[0xBE0]; break;
    case 2: p = &((sProf11E8 (*)[10])D_004A6CA8)[profile][c].s[0xBE1]; break;
    case 3: p = &((sProf11E8 (*)[10])D_004A6CA8)[profile][c].s[0xBE2]; break;
    case 4: p = &((sProf11E8 (*)[10])D_004A6CA8)[profile][c].s[0xBE3]; break;
    case 5: p = &((sProf11E8 (*)[10])D_004A6CA8)[profile][c].s[0xBE4]; break;
    case 6: p = &((sProf11E8 (*)[10])D_004A6CA8)[profile][c].s[0xBE5]; break;
    }
    return D_00440550_11E8[(*p + 1) / 5].b;
}

//100%
void cMemMan_free(void*);
void operator_delete(int*);

extern "C" void BE_CharProfile_dtor(void* self, int flags)
{
    void* p = *(void**)((char*)self + 0x288);
    if (p != 0)
    {
        cMemMan_free(p);
    }
    *(void**)((char*)self + 0x288) = 0;
    if (flags & 1)
    {
        operator_delete((int*)self);
    }
}

//100%
int func_0014DC40(void* self, int kind);
extern "C" void* func_0014DC50(void* self, int kind);
int func_0014D988(void* self, int i);
extern "C" void* func_0014D998(void* self, int i);
extern "C" int func_00151C90(void* self, int id, int on);
extern char D_004A6750[];

struct sEconItem_1513B8
{
    short id;
    short flags;
};

struct sEconItems_1513B8
{
    char pad[0x288];
    short* lookup;                  // 0x288
    int count;                      // 0x28C
    sEconItem_1513B8 items[0x20D];  // 0x290
    char pad2[0xBC0 - 0x290 - 0x20D * 4];
    signed char kind;               // 0xBC0
};

struct sEconGroup_1513B8
{
    int f0;
    short id;       // 0x4
    short prize;    // 0x6
};

struct sEconDef_1513B8
{
    int f0;
    short id;       // 0x4
    char pad6[0x8];
    short price;    // 0xE
    char pad10[0x28];
};

static inline sEconItem_1513B8* Find_1513B8(sEconItems_1513B8* self, int id)
{
    int idx = self->lookup[id];
    if (idx >= 0)
        return &self->items[idx];
    return 0;
}

static inline int Price_1513B8(sEconDef_1513B8* d)
{
    short v = d->price;
    int p = v;
    if (v > 0)
        p = v * 10;
    return p;
}

extern "C" void BE_ApplyDefaultCharProfileBolts(void* vself)
{
    sEconItems_1513B8* self = (sEconItems_1513B8*)vself;
    void* db = D_004A6750;
    int n = func_0014DC40(db, self->kind);
    sEconGroup_1513B8* g = (sEconGroup_1513B8*)func_0014DC50(db, self->kind);
    for (int i = 0; i < n; i++, g++)
    {
        func_00151C90(self, g->prize, 1);
    }
    int j;
    for (j = 0; j < self->count; j++)
    {
        sEconItem_1513B8* it = &self->items[j];
        if (it->flags & 0x10)
            it->flags |= 0x26;
    }
    int m = func_0014D988(db, self->kind);
    sEconDef_1513B8* d = (sEconDef_1513B8*)func_0014D998(db, self->kind);
    int changed = 0;
    for (int i = 0; i < m; i++, d++)
    {
        if (Price_1513B8(d) == 0)
        {
            Find_1513B8(self, d->id)->flags |= 2;
        }
        else if (Price_1513B8(d) == -1)
        {
            Find_1513B8(self, d->id)->flags |= 2;
            func_00151C90(self, d->id, 1);
            changed = 1;
        }
    }
    if (changed)
    {
        int k;
        for (k = 0; k < self->count; k++)
        {
            sEconItem_1513B8* it = &self->items[k];
            if (it->flags & 0x10)
                it->flags |= 6;
            else
                it->flags &= ~4;
        }
    }
}

//100%
struct sEconItem_001515B8
{
    short id;
    short flags;
};

struct sEconItems_001515B8
{
    char pad[0x28C];
    int count;
    sEconItem_001515B8 items[1];
};

extern "C" void func_001515B8(sEconItems_001515B8* self)
{
    int n = self->count;
    sEconItem_001515B8* p = self->items;
    for (int i = 0; i < n; i++, p++)
    {
        if (p->flags & 4)
            p->flags |= 0x10;
        else
            p->flags &= ~0x10;
    }
}

INCLUDE_ASM("be/beintecon", func_00151600);

//100%
struct sEconColor_001519E0
{
    signed char a;
    signed char b;
    signed char c;
};

struct sEconRange_001519E0
{
    int lo;
    int hi;
    int pad;
};

extern sEconColor_001519E0 D_004A1218[];
extern sEconRange_001519E0 D_004406FC[];

struct sEcon_001519E0
{
    char pad0[0xBC1];
    sEconColor_001519E0 colors[10];  // 0xBC1
};

extern "C" void func_001519E0(sEcon_001519E0* self, int k)
{
    sEconColor_001519E0 def = D_004A1218[0];
    for (int i = 0; i < 10; i++)
    {
        self->colors[i] = def;
        if (i == D_004406FC[k].lo)
        {
            self->colors[i].a = 0;
            self->colors[i].b = 0;
        }
        else if (i == D_004406FC[k].hi)
        {
            self->colors[i].a = 3;
            self->colors[i].b = 2;
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
int func_0014D988(void* self, int i);
extern "C" void* func_0014D998(void* self, int i);
extern "C" void BE_ApplyDefaultCharProfileBolts(void* self);
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern int D_004A11E8;
extern const char D_0045A7A8[];
extern char D_004A6750[];

struct sEconDef_151A88
{
    int f0;
    short id;           // 0x4
    char pad[0x32];
};

struct sEconItem_151A88
{
    short id;
    short flags;
};

struct sEconItems_151A88
{
    char pad[0x288];
    short* lookup;              // 0x288
    int count;                  // 0x28C
    sEconItem_151A88 items[0x20D]; // 0x290
    char pad2[0xBC0 - 0x290 - 0x20D * 4];
    signed char kind;           // 0xBC0
};

extern "C" void func_00151A88(sEconItems_151A88* self, int k)
{
    void* db = D_004A6750;
    sEconDef_151A88* d = (sEconDef_151A88*)func_0014D998(db, k);
    int n = func_0014D988(db, k);
    self->kind = k;
    self->count = n;
    if (self->lookup == 0)
        self->lookup = (short*)operator_new_tag(D_004A11E8 * 2, D_0045A7A8, 0, 0);
    int i;
    for (i = 0; i < D_004A11E8; i++)
        self->lookup[i] = -1;
    for (i = 0; i < n; i++, d++)
    {
        sEconItem_151A88* p = &self->items[i];
        p->flags = 0;
        int id = d->id;
        p->id = id;
        self->lookup[d->id] = i;
    }
    for (i = n; i < 0x20D; i++)
    {
        sEconItem_151A88* q = &self->items[i];
        q->id = -1;
        q->flags = 0;
    }
    BE_ApplyDefaultCharProfileBolts(self);
}

// A character's bolt-on store (0xF88 bytes, see be/belibrary)
struct sEconBoltOn {
    short id;
    unsigned short flags;
};

struct sEconBoltCharacter {
    char pad_0x000[0x288];
    short* slots;               // 0x288
    int count;                  // 0x28C
    sEconBoltOn items[525];     // 0x290
};

//100%
// Resets the per-item state bits: items with flag 0x20 get 0x16 set, the rest lose 0x10 and 0x4.
struct sEconItem_151BD0
{
    short id;
    short flags;
};

struct sEconItems_151BD0
{
    char pad[0x288];
    short* lookup;                  // 0x288
    int count;                      // 0x28C
    sEconItem_151BD0 items[0x20D];  // 0x290
};

extern "C" void func_00151BD0(sEconItems_151BD0* self)
{
    for (int i = 0; i < self->count; i++)
    {
        sEconItem_151BD0* it = &self->items[i];
        if (it->flags & 0x20)
        {
            it->flags |= 0x16;
        }
        else
        {
            it->flags &= ~0x10;
            it->flags &= ~0x4;
        }
    }
}

// The id of item i, or -1
extern "C" int func_00151C20(sEconBoltCharacter* c, int i)
{
    if (i >= c->count)
        return -1;
    return *(short*)(i * 4 + (char*)c + 0x290);
}

//100%
struct sEconItem_00151C48
{
    short id;
    short flags;
};

struct sEconItems_00151C48
{
    char pad[0x288];
    short* lookup;
    int count;
    sEconItem_00151C48 items[1];
};

extern "C" void func_00151C48(sEconItems_00151C48* self, int id, int on)
{
    int idx = self->lookup[id];
    sEconItem_00151C48* p;
    if (idx >= 0)
        p = &self->items[idx];
    else
        p = 0;
    if (on)
        p->flags |= 2;
    else
        p->flags &= ~2;
}

INCLUDE_ASM("be/beintecon", func_00151C90);

//100%
// Applies item id's dependency list: each linked item whose state differs from the wanted one
// (or that is off and marked 0x8) is switched on or off, recursing through func_00151C90.
// PORT: func_0014BDB8 is declared (void*) but never reads its argument; called here with none
void* func_0014BDB8_151EF0() __asm__("func_0014BDB8__FPv");
extern "C" void* func_0014DB40(void* self, int g, int key, int want, int* out);
extern "C" int func_0014D448(void* self, int g, int key);

struct sEconItem_151EF0
{
    short id;
    unsigned short flags;
};

struct sEconItems_151EF0
{
    char pad[0x288];
    short* lookup;                  // 0x288
    int count;                      // 0x28C
    sEconItem_151EF0 items[0x20D];  // 0x290
    char pad2[0xBC0 - 0x290 - 0x20D * 4];
    signed char kind;               // 0xBC0
};

struct sEconDep_151EF0
{
    char pad0[0x5];
    signed char reqOn;  // 0x5
    short reqId;        // 0x6
    char pad8;
    signed char on;     // 0x9
    short id;           // 0xA
};

struct sEconDef_151EF0
{
    char pad0[0x34];
    int flags;          // 0x34
};

struct sEconDb_151EF0
{
    char pad0[0x4];
    sEconDef_151EF0* defs;  // 0x4
};

static inline sEconItem_151EF0* getItem_151EF0(sEconItems_151EF0* self, int id)
{
    int idx = self->lookup[id];
    if (idx >= 0)
        return &self->items[idx];
    return 0;
}

static inline sEconDef_151EF0* getDef_151EF0(sEconDb_151EF0* db, int i)
{
    if (i < 0)
        return 0;
    return &db->defs[i];
}

extern "C" int func_00151EF0(sEconItems_151EF0* self, int id, int on)
{
    sEconDb_151EF0* db = (sEconDb_151EF0*)func_0014BDB8_151EF0();
    int n = 0;
    sEconDep_151EF0* d = (sEconDep_151EF0*)func_0014DB40(db, self->kind, id, on, &n);
    sEconItem_151EF0* me = getItem_151EF0(self, id);
    for (int i = 0; i < n; i++, d++)
    {
        if (d->id == -1)
            continue;
        if (d->reqId != -1)
        {
            int req = getItem_151EF0(self, d->reqId)->flags & 0x10;
            if ((req != 0) != (d->reqOn != 0))
                continue;
        }
        sEconItem_151EF0* it = &self->items[self->lookup[d->id]];
        int has = it->flags & 0x10;
        int h = has != 0;
        if ((h != (d->on != 0)) || (!h && (getDef_151EF0(db, func_0014D448(db, self->kind, d->id))->flags & 0x8)))
        {
            if (it->id == id)
            {
                if (d->on)
                    me->flags |= 0x10;
                else
                    me->flags &= ~0x10;
            }
            else if (func_00151C90(self, it->id, d->on != 0) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

//100%
void* func_0014BDB8(void* self);
int func_0014D988(void* self, int i);
extern "C" void* func_0014D998(void* self, int i);
struct sEconItem_001520E8
{
    short id;
    unsigned short flags;
};

struct sEconItems_001520E8
{
    char pad[0x288];
    short* lookup;              // 0x288
    int count;                  // 0x28C
    sEconItem_001520E8 items[1];    // 0x290
};

struct sEconDef_001520E8
{
    char pad0[0x4];
    short id;           // 0x4
    char pad6[0x2E];
    int flags;          // 0x34
};

static inline sEconItem_001520E8* getItem_001520E8(sEconItems_001520E8* self, int id)
{
    int idx = self->lookup[id];
    if (idx >= 0)
        return &self->items[idx];
    return 0;
}

extern "C" int func_001520E8(sEconItems_001520E8* self, int* changed)
{
    void* db = func_0014BDB8(self);
    int n = func_0014D988(db, *((signed char*)self + 0xBC0));
    sEconDef_001520E8* d = (sEconDef_001520E8*)func_0014D998(db, *((signed char*)self + 0xBC0));
    *changed = 0;
    for (int i = 0; i < n; i++, d++)
    {
        if (d->flags & 0x1000)
        {
            if (getItem_001520E8(self, d->id)->flags & 0x10)
            {
                *changed = 1;
                if (func_00151EF0((sEconItems_151EF0*)self, d->id, 1) == 0)
                    return 0;
            }
        }
    }
    return 1;
}

//100%
// PORT: func_0014BDB8 is declared (void*) but never reads its argument; called here with none
void* func_0014BDB8_noarg() __asm__("func_0014BDB8__FPv");
int func_0014DC40(void* self, int kind);
extern "C" void* func_0014DC50(void* self, int kind);
extern "C" int func_0014D608(void* self, int kind, int id, void** out, int a, int b);
extern "C" int func_00151C90(void* self, int id, int on);

struct sEconItem_1521F0
{
    short id;
    unsigned short flags;
};

struct sEconItems_1521F0
{
    char pad[0x288];
    short* lookup;                  // 0x288
    int count;                      // 0x28C
    sEconItem_1521F0 items[0x20D];  // 0x290
    char pad2[0xBC0 - 0x290 - 0x20D * 4];
    signed char kind;               // 0xBC0
};

struct sEconGroup_1521F0
{
    int f0;
    short id;       // 0x4
    short prize;    // 0x6
};

struct sEconDef_1521F0
{
    int f0;
    short id;       // 0x4
    char pad[0x2E];
    int flags;      // 0x34
};

static inline sEconItem_1521F0* Find_1521F0(sEconItems_1521F0* self, int id)
{
    int idx = self->lookup[id];
    if (idx >= 0)
        return &self->items[idx];
    return 0;
}

extern "C" int func_001521F0(sEconItems_1521F0* self)
{
    int i = 0;
    int ok = 1;
    void* db = func_0014BDB8_noarg();
    sEconGroup_1521F0* g = (sEconGroup_1521F0*)func_0014DC50(db, self->kind);
    int n = func_0014DC40(db, self->kind);
    for (; i < n; i++, g++)
    {
        sEconDef_1521F0* list[528];
        int cnt = func_0014D608(db, self->kind, g->id, (void**)list, -1, 1);
        int j;
        for (j = 0; j < cnt; j++)
        {
            if (!(Find_1521F0(self, list[j]->id)->flags & 0x10))
                continue;
            if (list[j]->flags & 0x10)
                break;
        }
        if (j == cnt)
        {
            if (func_00151C90(self, g->prize, 1) == 0)
            {
                ok = 0;
                break;
            }
        }
    }
    return ok;
}


//100%
// Returns whether item id has flag 0x10.
extern "C" int func_00152340(sEconItems_151BD0* self, int id)
{
    sEconItem_151BD0* it = &self->items[self->lookup[id]];
    int f = it->flags & 0x10;
    return f != 0;
}

//100%
// Returns whether item id has every flag in mask.
extern "C" int func_00152368(sEconItems_151BD0* self, int id, int mask)
{
    sEconItem_151BD0* it = &self->items[self->lookup[id]];
    return (~(unsigned short)it->flags & mask) == 0;
}
