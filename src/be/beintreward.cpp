#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0045A938[];
extern void* D_0045AE88[16];
extern void* D_004A1264;

struct cBERewardInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//99.84%
void* cBERewardInterface_getThis()
{
    if (D_004A1264 == 0) {
        cBERewardInterface* mem = (cBERewardInterface*)cMemMan_alloc(0x18, D_0045A938, 0, 0);
        mem->field_0x8 = 0;
        mem->vtable = D_0045AE88;
        D_004A1264 = mem;
    }
    return D_004A1264;
}

//100%
extern "C" void cBERewardDB_init(void* db, int flag);
extern void* D_004C3E98[];

extern "C" void func_00156A10()
{
    cBERewardDB_init(D_004C3E98, 1);
}

//100%
// PORT: compares a pointer cast to int against -1; not 64-bit safe.
extern void* D_004C3E98[];

extern "C" int func_00156A38(void)
{
    int r = 0;
    if ((int)D_004C3E98[0] == -1) {
        r = D_004C3E98[1] != 0;
    }
    return r;
}

//100%
int cBERewardInterface_isBetterMedal(void* self, int a, int b)
{
    if (b == -1) {
        return 0;
    }
    if (a == -1) {
        return 1;
    }
    return b < a;
}

//100%
extern "C" void* func_0015A478(void* self);

extern "C" char* func_00156A90(void* self, int a1, int a2)
{
    return *(char**)((char*)func_0015A478(self) + 0x8) + (a2 * 3 + a1) * 0xC;
}

//100%
extern "C" void* func_0015A478(void* self);

extern "C" char* func_00156AE0(void* self, int a1, int a2)
{
    return *(char**)((char*)func_0015A478(self) + 0xC) + (a1 * 4 + a2) * 0xC;
}

//100%
extern "C" void* func_0015A478(void* self);

extern "C" char* func_00156B28(void* self, int a1, int a2)
{
    return *(char**)((char*)func_0015A478(self) + 0x10) + (a2 * 3 + a1) * 8;
}

extern "C" int func_00156B70(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x8);
}

extern "C" int func_00156B90(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0xC);
}

extern "C" int func_00156BB0(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x10);
}

extern "C" int func_00156BD0(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x14);
}

extern "C" int func_00156BF0(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x18);
}

extern "C" int func_00156C10(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x1C);
}

extern "C" int func_00156C30(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x20);
}

extern "C" int func_00156C50(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x24);
}

//100%
extern int D_004A6CA8[];
struct sBELibTables;
// PORT: func_0014BDB8 is declared (void*) but never reads its argument; called here with none
void* func_0014BDB8_noarg() __asm__("func_0014BDB8__FPv");
int func_0014D988(void* self, int i);
extern "C" void* func_0014D998(sBELibTables* self, int i);
unsigned int BXrand();

struct sBEFlagEntry_6C70 {
    unsigned short field_0x0;
    unsigned short flags;
};

struct sBEEntry_6C70 {
    char pad_0x0[4];
    short id;           // 0x4
    char pad_0x6[0x2E];
    int flags;          // 0x34
};

static inline sBEFlagEntry_6C70* Flag_6C70(char* p, sBEEntry_6C70* e)
{
    short s = (*(short**)(p + 0x288))[e->id];
    if (s >= 0)
        return (sBEFlagEntry_6C70*)(p + 0x290) + s;
    return 0;
}

static inline int Match_6C70(sBEEntry_6C70* e, int type)
{
    return (type == 0 && (e->flags & 0x100)) || (type == 1 && (e->flags & 0x200)) || (type == 2 && (e->flags & 0x400));
}

extern "C" int func_00156C70(void* self, int a1, int a2, int type)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    int n = 0;
    void* lib = func_0014BDB8_noarg();
    int count = func_0014D988(lib, a2);
    sBEEntry_6C70* e = (sBEEntry_6C70*)func_0014D998((sBELibTables*)lib, a2);
    int i;
    for (i = 0; i < count; i++, e++)
    {
        if (type == 0 && (*(unsigned char*)((char*)e + 0x35) & 1))
        {
            if ((Flag_6C70(p, e)->flags & 2) == 0)
                n++;
        }
        else if (type == 1 && (e->flags & 0x200))
        {
            if ((Flag_6C70(p, e)->flags & 2) == 0)
                n++;
        }
        else if (type == 2 && (e->flags & 0x400))
        {
            if ((Flag_6C70(p, e)->flags & 2) == 0)
                n++;
        }
    }
    if (n > 0)
    {
        n = BXrand() % n;
        e = (sBEEntry_6C70*)func_0014D998((sBELibTables*)lib, a2);
        int j;
        for (j = 0; j < count; j++, e++)
        {
            if (type == 0 && (*(unsigned char*)((char*)e + 0x35) & 1))
            {
                short id = e->id;
                short s = (*(short**)(p + 0x288))[id];
                sBEFlagEntry_6C70* f;
                if (s >= 0)
                    f = (sBEFlagEntry_6C70*)(p + 0x290) + s;
                else
                    f = 0;
                if ((f->flags & 2) == 0)
                {
                    if (--n < 0)
                        return id;
                }
            }
            else if (type == 1 && (e->flags & 0x200))
            {
                short id = e->id;
                short s = (*(short**)(p + 0x288))[id];
                sBEFlagEntry_6C70* f;
                if (s >= 0)
                    f = (sBEFlagEntry_6C70*)(p + 0x290) + s;
                else
                    f = 0;
                if ((f->flags & 2) == 0)
                {
                    if (--n < 0)
                        return id;
                }
            }
            else if (type == 2 && (e->flags & 0x400))
            {
                short id = e->id;
                short s = (*(short**)(p + 0x288))[id];
                sBEFlagEntry_6C70* f;
                if (s >= 0)
                    f = (sBEFlagEntry_6C70*)(p + 0x290) + s;
                else
                    f = 0;
                if ((f->flags & 2) == 0)
                {
                    if (--n < 0)
                        return id;
                }
            }
        }
    }
    return -1;
}

//100%
extern int D_004A6CA8[];
struct sBELibTables;
// PORT: func_0014BDB8 is declared (void*) but never reads its argument; called here with none
void* func_0014BDB8_noarg() __asm__("func_0014BDB8__FPv");
int func_0014D988(void* self, int i);
extern "C" void* func_0014D998(sBELibTables* self, int i);
unsigned int BXrand();

struct sBEFlagEntry_6EE0 {
    unsigned short field_0x0;
    unsigned short flags;
};

struct sBEEntry_6EE0 {
    char pad_0x0[4];
    short id;           // 0x4
    char pad_0x6[0x2E];
    int flags;          // 0x34
};

static inline sBEFlagEntry_6EE0* Flag_6EE0(char* p, sBEEntry_6EE0* e)
{
    short s = (*(short**)(p + 0x288))[e->id];
    if (s >= 0)
        return (sBEFlagEntry_6EE0*)(p + 0x290) + s;
    return 0;
}

extern "C" int func_00156EE0(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    int n = 0;
    void* lib = func_0014BDB8_noarg();
    int count = func_0014D988(lib, a2);
    sBEEntry_6EE0* e = (sBEEntry_6EE0*)func_0014D998((sBELibTables*)lib, a2);
    int i;
    for (i = 0; i < count; i++, e++)
    {
        if (e->flags & 0x800)
        {
            if ((Flag_6EE0(p, e)->flags & 2) == 0)
                n++;
        }
    }
    if (n > 0)
    {
        n = BXrand() % n;
        e = (sBEEntry_6EE0*)func_0014D998((sBELibTables*)lib, a2);
        int j;
        for (j = 0; j < count; j++, e++)
        {
            if (e->flags & 0x800)
            {
                short id = e->id;
                short s = (*(short**)(p + 0x288))[id];
                sBEFlagEntry_6EE0* f;
                if (s >= 0)
                    f = (sBEFlagEntry_6EE0*)(p + 0x290) + s;
                else
                    f = 0;
                if ((f->flags & 2) == 0)
                {
                    if (--n < 0)
                        return id;
                }
            }
        }
    }
    return -1;
}

//100%
extern "C" int func_00157210(void* self, int kind);
extern "C" int func_00157518(void* self, int a1, int a2, int kind);

struct sRw7080 { char s[0xF88]; };

extern "C" int func_00157080(void* self, int a1, int a2, int kind)
{
    int total = func_00157210(self, kind);
    int result = -1;
    int have = func_00157518(self, a1, a2, kind);
    unsigned int r;
    char* base;
    char* p;
    int i;
    if (have >= total) return -1;
    r = BXrand() % (unsigned int)(total - have);
    p = 0;
    base = &((sRw7080 (*)[10])D_004A6CA8)[a1][a2].s[0];
    switch (kind) {
    case 3: p = base + 0xF30; break;
    case 4: p = base + 0xF36; break;
    case 5: p = base + 0xF45; break;
    case 6: p = base + 0xF52; break;
    case 7: p = base + 0xF53; break;
    }
    for (i = 0; result < 0; i++) {
        int b;
        for (b = 0; b < 8; b++) {
            if (((p[i] >> b) ^ 1) & 1) {
                if (r == 0) {
                    result = i * 8 + b;
                    break;
                }
                r--;
            }
        }
    }
    return result;
}

//100%
int func_001572B0(void* self);
int func_001572D0(void* self);
int func_001572F0(void* self);
int func_00157310(void* self);
int func_00157330(void* self);

extern "C" int func_00157210(void* self, int kind)
{
    switch (kind) {
    case 3:
        return func_001572B0(self);
    case 4:
        return func_001572D0(self);
    case 5:
        return func_001572F0(self);
    case 6:
        return func_00157330(self);
    case 7:
        return func_00157310(self);
    case 8:
        return 0x14;
    case 9:
        break;
    }
    return 0;
}

extern "C" void* func_0015A478(void* self);

//100%
int func_001572B0(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x3c);
}

//100%
int func_001572D0(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x40);
}

//100%
int func_001572F0(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x44);
}

//100%
int func_00157310(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x48);
}

//100%
int func_00157330(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x4c);
}

extern "C" void* func_0028B180(void* self);

//100%
int func_00157350(void* self)
{
    return *(int*)((char*)func_0028B180(self) + 0x504);
}

//100%
int func_00157370(void* self)
{
    return *(int*)((char*)func_0015A478(self) + 0x50);
}

//100%
// Counts the set bits among the first `count` bits of `bits` (LSB first).
extern "C" int func_00157390(void* self, int count, signed char* bits)
{
    int i = 0;
    int total = 0;
    while (i < count)
    {
        signed char b = *bits++;
        for (int k = 0; k < 8 && i < count; k++)
        {
            i++;
            total += (b >> k) & 1;
        }
    }
    return total;
}

//100%
extern "C" void func_001573F0(void* self, int bit, char* bits)
{
    int shift = bit % 8;
    bits[(unsigned int)bit / 8] |= 1 << shift;
}

//100%
extern "C" int func_00157430(void* self, int bit, char* bits)
{
    int shift = bit % 8;
    return (bits[(unsigned int)bit / 8] >> shift) & 1;
}

//100%
extern "C" int func_00157D60(void* self, int a1, int a2, int bit);
int func_00157DA0_jt(void*, int, int, int) __asm__("func_00157DA0");
int func_00157DE0_jt(void*, int, int, int) __asm__("func_00157DE0");
int func_00157E20_jt(void*, int, int, int) __asm__("func_00157E20");
int func_00157E60_jt(void*, int, int, int) __asm__("func_00157E60");
extern "C" int func_00157EE0(void* self, int a1, int a2, int bit);

extern "C" int func_00157468(void* self, int a1, int a2, int kind, int bit)
{
    switch (kind) {
    case 3: return func_00157D60(self, a1, a2, bit);
    case 4: return func_00157DA0_jt(self, a1, a2, bit);
    case 5: return func_00157DE0_jt(self, a1, a2, bit);
    case 6: return func_00157E60_jt(self, a1, a2, bit);
    case 7: return func_00157E20_jt(self, a1, a2, bit);
    case 8: return func_00157EE0(self, a1, a2, bit + 10);
    }
    return 0;
}

//100%
extern "C" int func_001575C0(void* self, int a1, int a2);
extern "C" int func_00157620(void* self, int a1, int a2);
extern "C" int func_00157680(void* self, int a1, int a2);
extern "C" int func_001576E0(void* self, int a1, int a2);
extern "C" int func_00157740(void* self, int a1, int a2);
extern "C" int func_001577A0(void* self, int a1, int a2);

extern "C" int func_00157518(void* self, int a1, int a2, int kind)
{
    switch (kind) {
    case 3: return func_001575C0(self, a1, a2);
    case 4: return func_00157620(self, a1, a2);
    case 5: return func_00157680(self, a1, a2);
    case 6: return func_00157740(self, a1, a2);
    case 7: return func_001576E0(self, a1, a2);
    case 8: return func_001577A0(self, a1, a2);
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");
extern "C" int func_00157390(void* self, int count, signed char* bits);

extern "C" int func_001575C0(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157390(self, *(int*)((char*)func_0015A478_noargs() + 0x3C), (signed char*)(p + 0xF30));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");
extern "C" int func_00157390(void* self, int count, signed char* bits);

extern "C" int func_00157620(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157390(self, *(int*)((char*)func_0015A478_noargs() + 0x40), (signed char*)(p + 0xF36));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");
extern "C" int func_00157390(void* self, int count, signed char* bits);

extern "C" int func_00157680(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157390(self, *(int*)((char*)func_0015A478_noargs() + 0x44), (signed char*)(p + 0xF45));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");
extern "C" int func_00157390(void* self, int count, signed char* bits);

extern "C" int func_001576E0(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157390(self, *(int*)((char*)func_0015A478_noargs() + 0x48), (signed char*)(p + 0xF53));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");
extern "C" int func_00157390(void* self, int count, signed char* bits);

extern "C" int func_00157740(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157390(self, *(int*)((char*)func_0015A478_noargs() + 0x4C), (signed char*)(p + 0xF52));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
extern "C" int func_00157390(void* self, int count, signed char* bits);

extern "C" int func_001577A0(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157390(self, 0x14, (signed char*)(p + 0xF57));
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBEScoreInterface_getCurrentHighlightLevel(void* self, int i);
extern "C" int func_00157920(void* self, int a, int b, int i);

extern "C" int func_001577E0(void* self, int a, int b)
{
    for (int i = 0; i < 3; i++)
    {
        if (!func_00157920(self, a, b, i))
            return 0;
    }
    int total = 0;
    void* score = cBE_getInterface_Fv(cBE_getBE(), 8);
    for (int i = 0; i < 8; i++)
    {
        total += cBEScoreInterface_getCurrentHighlightLevel(score, i);
    }
    return total >= 24;
}

//100%
extern "C" int func_00157A78(void* self, int a, int b, int i);

extern "C" int func_001578A0(void* self, int a, int b)
{
    for (int i = 0; i < 3; i++)
    {
        if (func_00157A78(self, a, b, i) == 0)
            return 0;
    }
    return 1;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
signed char cBERewardInterface_getTrackMedal(void* self, int a, int b, int track, int kind);
int cBERewardInterface_isBetterMedal(void* self, int a, int b);
extern "C" int func_001589B0(void* self, int a, int b, int kind);
extern "C" int func_00158A50(void* self, int a, int b, int kind);

struct sRewardReq_157920
{
    signed char track;
    signed char kind;
};
extern sRewardReq_157920 D_0045AAD8_v157920[][4][5] __asm__("D_0045AAD8");

extern "C" int func_00157920(void* self, int a, int b, int k)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int track = D_0045AAD8_v157920[k][i][j].track;
            int kind = D_0045AAD8_v157920[k][i][j].kind;
            if (track < 0)
                break;
            if (i == 3)
                continue;
            if (i == 2)
            {
                if (func_001589B0(self, a, b, k))
                    return 0;
                if (func_00158A50(self, a, b, k))
                    return 0;
            }
            else
            {
                int m = cBERewardInterface_getTrackMedal(self, a, b, track, kind);
                if ((unsigned int)(track - 4) < 8)
                {
                    if (!cBERewardInterface_isBetterMedal(self, -1, m))
                        return 0;
                }
                else if ((unsigned int)m >= 2)
                    return 0;
            }
        }
    }
    return 1;
}

//100%
extern "C" int func_00157BF0(void* self, int a, int b, int c, int i);

extern "C" int func_00157A78(void* self, int a, int b, int c)
{
    for (int i = 0; i < 4; i++)
    {
        if (func_00157BF0(self, a, b, c, i) == 0)
            return 0;
    }
    return 1;
}

//100%
int cBELibrary_getProfileIndex(int);
int cBELibrary_getCharacterID(int);
extern "C" int func_00157B70(void* self, int a, int b, int peak);

extern "C" int func_00157B08(void* self, int rider, int peak)
{
    int profile = cBELibrary_getProfileIndex(rider);
    return func_00157B70(self, profile, cBELibrary_getCharacterID(rider), peak);
}

//100%
extern int D_004A6CA8[];

// PORT: 64-bit ulong flag word (bit 12 = peak 1 locked, bit 13 = peak 2).
extern "C" int func_00157B70(void* self, int a, int b, int peak)
{
    if (peak == 1)
    {
        int bOff = b * 0xF88;
        int aOff = a * 0x9B50;
        int off = bOff + aOff;
        char* p = (char*)D_004A6CA8 + off;
        return (int)(*(ulong*)(p + 0x278) >> 12) & 1;
    }
    if (peak == 2)
    {
        int bOff = b * 0xF88;
        int aOff = a * 0x9B50;
        int off = bOff + aOff;
        char* p = (char*)D_004A6CA8 + off;
        return (int)(*(ulong*)(p + 0x278) >> 13) & 1;
    }
    return 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
signed char cBERewardInterface_getTrackMedal(void* self, int b, int c, int d, int e);
int cBERewardInterface_isBetterMedal(void* self, int a, int b);
extern "C" int cBERewardInterface_getEarningsMedal(void* self, int a, int b, int medal);
extern "C" int func_001589B0(void* self, int a, int b, int kind);
extern "C" int func_00158A50(void* self, int a, int b, int kind);

struct sRewardReq_157BF0
{
    signed char track;
    signed char kind;
};
extern sRewardReq_157BF0 D_0045AAD8_v157BF0[][4][5] __asm__("D_0045AAD8");

extern "C" int func_00157BF0(void* self, int a, int b, int k, int i)
{
    switch (i)
    {
    case 0:
    case 1:
        for (int j = 0; j < 5; j++)
        {
            int track = D_0045AAD8_v157BF0[k][i][j].track;
            int kind = D_0045AAD8_v157BF0[k][i][j].kind;
            if (track < 0)
                break;
            if (!cBERewardInterface_isBetterMedal(self, -1, cBERewardInterface_getTrackMedal(self, a, b, track, kind)))
                return 0;
        }
        return 1;
    case 2:
    {
        int r = 0;
        if (cBERewardInterface_isBetterMedal(self, -1, func_001589B0(self, a, b, k)))
            r = cBERewardInterface_isBetterMedal(self, -1, func_00158A50(self, a, b, k)) != 0;
        return r;
    }
    case 3:
        return cBERewardInterface_isBetterMedal(self, -1, cBERewardInterface_getEarningsMedal(self, a, b, k));
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
extern "C" int func_00157430(void* self, int bit, char* bits);

extern "C" int func_00157D60(void* self, int a1, int a2, int bit)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157430(self, bit, p + 0xF30);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
extern "C" int func_00157430(void* self, int bit, char* bits);

extern "C" int func_00157DA0(void* self, int a1, int a2, int bit)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157430(self, bit, p + 0xF36);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
extern "C" int func_00157430(void* self, int bit, char* bits);

extern "C" int func_00157DE0(void* self, int a1, int a2, int bit)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157430(self, bit, p + 0xF45);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
extern "C" int func_00157430(void* self, int bit, char* bits);

extern "C" int func_00157E20(void* self, int a1, int a2, int bit)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157430(self, bit, p + 0xF53);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
extern "C" int func_00157430(void* self, int bit, char* bits);

extern "C" int func_00157E60(void* self, int a1, int a2, int bit)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157430(self, bit, p + 0xF52);
}

extern "C" int func_00157EA0(void* self, int a1, int a2, int bit)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return (*(unsigned long*)(p + 0xf78) >> bit) & 1;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
extern "C" int func_00157430(void* self, int bit, char* bits);

extern "C" int func_00157EE0(void* self, int a1, int a2, int bit)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157430(self, bit-10, p + 0xF57);
}

//100%
int func_00157FD0_jt(void*, int, int, int, int) __asm__("func_00157FD0");
int func_001580F8_jt(void*, int, int, int, int) __asm__("func_001580F8");
int func_00158220_jt(void*, int, int, int, int) __asm__("func_00158220");
int func_00158348_jt(void*, int, int, int, int) __asm__("func_00158348");
int func_00158470_jt(void*, int, int, int, int) __asm__("func_00158470");
int func_00158618_jt(void*, int, int, int, int) __asm__("func_00158618");

extern "C" int func_00157F20(void* self, int a1, int a2, int kind, int bit, int give)
{
    switch (kind) {
    case 3: return func_00157FD0_jt(self, a1, a2, bit, give);
    case 4: return func_001580F8_jt(self, a1, a2, bit, give);
    case 5: return func_00158220_jt(self, a1, a2, bit, give);
    case 6: return func_00158470_jt(self, a1, a2, bit, give);
    case 7: return func_00158348_jt(self, a1, a2, bit, give);
    case 8: return func_00158618_jt(self, a1, a2, bit + 10, give);
    }
    return 0;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_001573F0(void* self, int bit, char* bits);
extern "C" int func_00150928(void* self, int a, int b);
extern "C" int func_00150B48(void* self, int a, int b, int amount);
extern "C" int func_001575C0(void* self, int a1, int a2);
int func_001572B0(void* self);
extern "C" void func_00158618(void* self, int a1, int a2, int a3, int a4);
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");

struct sRewardDef_157FD0
{
    char pad0[0xC];
    short amount;   // 0xC
    short padE;
};

extern "C" void func_00157FD0(void* self, int a1, int a2, int bit, int give)
{
    void* econ = cBE_getInterface_Fv(cBE_getBE(), 0xB);
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    func_001573F0(self, bit, p + 0xF30);
    if (give)
    {
        char* defs = *(char**)((char*)func_0015A478_noargs() + 0x14);
        int amount = ((sRewardDef_157FD0*)(defs + (bit << 4)))->amount;
        if (amount > 0) amount *= 10;
        func_00150B48(econ, a1, a2, amount);
    }
    if (func_001575C0(self, a1, a2) == func_001572B0(self))
    {
        func_00158618(self, a1, a2, 0x14, 0);
    }
    func_00150928(econ, a1, a2);
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_001573F0(void* self, int bit, char* bits);
extern "C" int func_00150928(void* self, int a, int b);
extern "C" int func_00150B48(void* self, int a, int b, int amount);
extern "C" int func_00157620(void* self, int a1, int a2);
int func_001572D0(void* self);
extern "C" void func_00158618(void* self, int a1, int a2, int a3, int a4);
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");

struct sRewardDef_1580F8
{
    char pad0[0xC];
    short amount;   // 0xC
    short padE;
};

extern "C" void func_001580F8(void* self, int a1, int a2, int bit, int give)
{
    void* econ = cBE_getInterface_Fv(cBE_getBE(), 0xB);
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    func_001573F0(self, bit, p + 0xF36);
    if (give)
    {
        char* defs = *(char**)((char*)func_0015A478_noargs() + 0x18);
        int amount = ((sRewardDef_1580F8*)(defs + (bit << 4)))->amount;
        if (amount > 0) amount *= 10;
        func_00150B48(econ, a1, a2, amount);
    }
    if (func_00157620(self, a1, a2) == func_001572D0(self))
    {
        func_00158618(self, a1, a2, 0x11, 0);
    }
    func_00150928(econ, a1, a2);
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_001573F0(void* self, int bit, char* bits);
extern "C" int func_00150928(void* self, int a, int b);
extern "C" int func_00150B48(void* self, int a, int b, int amount);
extern "C" int func_00157680(void* self, int a1, int a2);
int func_001572F0(void* self);
extern "C" void func_00158618(void* self, int a1, int a2, int a3, int a4);
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");

struct sRewardDef_158220
{
    char pad0[0xC];
    short amount;   // 0xC
    short padE;
};

extern "C" void func_00158220(void* self, int a1, int a2, int bit, int give)
{
    void* econ = cBE_getInterface_Fv(cBE_getBE(), 0xB);
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    func_001573F0(self, bit, p + 0xF45);
    if (give)
    {
        char* defs = *(char**)((char*)func_0015A478_noargs() + 0x1C);
        int amount = ((sRewardDef_158220*)(defs + (bit << 4)))->amount;
        if (amount > 0) amount *= 10;
        func_00150B48(econ, a1, a2, amount);
    }
    if (func_00157680(self, a1, a2) == func_001572F0(self))
    {
        func_00158618(self, a1, a2, 0x16, 0);
    }
    func_00150928(econ, a1, a2);
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_001573F0(void* self, int bit, char* bits);
extern "C" int func_00150928(void* self, int a, int b);
extern "C" int func_00150B48(void* self, int a, int b, int amount);
extern "C" int func_001576E0(void* self, int a1, int a2);
int func_00157310(void* self);
extern "C" void func_00158618(void* self, int a1, int a2, int a3, int a4);
extern int D_004A6CA8[];
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");

struct sRewardDef_158348
{
    char pad0[0xC];
    short amount;   // 0xC
    short padE;
};

extern "C" void func_00158348(void* self, int a1, int a2, int bit, int give)
{
    void* econ = cBE_getInterface_Fv(cBE_getBE(), 0xB);
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    func_001573F0(self, bit, p + 0xF53);
    if (give)
    {
        char* defs = *(char**)((char*)func_0015A478_noargs() + 0x20);
        int amount = ((sRewardDef_158348*)(defs + (bit << 4)))->amount;
        if (amount > 0) amount *= 10;
        func_00150B48(econ, a1, a2, amount);
    }
    if (func_001576E0(self, a1, a2) == func_00157310(self))
    {
        func_00158618(self, a1, a2, 0x13, 0);
    }
    func_00150928(econ, a1, a2);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");
extern int D_004A6CA8[];
extern "C" void func_001573F0(void* self, int bit, char* bits);
extern "C" int func_00150928(void* self, int a, int b);
extern "C" int func_00150B48(void* self, int a, int b, int amount);

extern "C" void func_00158470(void* self, int profile, int c, int idx, int award)
{
    void* econ = cBE_getInterface_Fv(cBE_getBE(), 0xB);
    char* p = (char*)D_004A6CA8 + profile * 0x9b50 + c * 0xf88;
    func_001573F0(self, idx, p + 0xF52);
    if (award)
    {
        int v = *(short*)(*(char**)((char*)func_0015A478_noargs() + 0x24) + (idx << 4) + 0xC);
        if (v > 0)
            v *= 10;
        func_00150B48(econ, profile, c, v);
    }
    func_00150928(econ, profile, c);
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern int D_004A6CA8[];
extern "C" int func_00150928(void* self, int a, int b);
extern "C" int func_00150B48(void* self, int a, int b, int amount);

// PORT: 64-bit ulong bit set (sd/ld).
extern "C" void func_00158558(void* self, int profile, int c, int bit, int award)
{
    void* econ = cBE_getInterface_Fv(cBE_getBE(), 0xB);
    char* p = (char*)D_004A6CA8 + profile * 0x9b50 + c * 0xf88;
    *(ulong*)(p + 0xF70) |= (ulong)1 << bit;
    if (award)
    {
        func_00150B48(econ, profile, c, 5000);
    }
    func_00150928(econ, profile, c);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
// PORT: the unit declares func_0015A478(void*), but it takes no args (returns &D_004C3E98).
void* func_0015A478_noargs() __asm__("func_0015A478");
extern int D_004A6CA8[];
extern "C" void func_001573F0(void* self, int bit, char* bits);
extern "C" int func_00150928(void* self, int a, int b);
extern "C" int func_00150B48(void* self, int a, int b, int amount);

extern "C" void func_00158618(void* self, int profile, int c, int idx, int award)
{
    idx -= 10;
    void* econ = cBE_getInterface_Fv(cBE_getBE(), 0xB);
    char* p = (char*)D_004A6CA8 + profile * 0x9b50 + c * 0xf88;
    func_001573F0(self, idx, p + 0xF57);
    if (award)
    {
        int v = *(short*)(*(char**)((char*)func_0015A478_noargs() + 0x28) + (idx << 4) + 0xC);
        if (v > 0)
            v *= 10;
        func_00150B48(econ, profile, c, v);
    }
    func_00150928(econ, profile, c);
}

//100%
extern int D_004A6CA8[];

extern "C" int func_00158700(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return *(int*)(p + 0xf80);
}

//100%
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t off-PS2.
extern int D_004A6CA8[];

extern "C" long func_00158728(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return *(long*)(p + 0xf70);
}

//100%
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t off-PS2.
extern int D_004A6CA8[];

extern "C" long func_00158750(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return *(long*)(p + 0xf78);
}

extern "C" int func_00158778(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157390(self, 0x40, (signed char*)(p + 0xF70));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern int D_004A6CA8[];
extern "C" int func_00157390(void* self, int count, signed char* bits);

extern "C" int func_001587B8(void* self, int a1, int a2)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_00157390(self, 0x40, (signed char*)(p + 0xF78));
}

//100%
extern int D_004A6CA8[];

extern "C" void func_001587F8(void* self, int a1, int a2, int value)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    *(int*)(p + 0xf80) = value;
}

//100%
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t off-PS2.
extern int D_004A6CA8[];

extern "C" void func_00158820(void* self, int a1, int a2, long value)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    *(long*)(p + 0xf70) = value;
}

//100%
// PORT: 64-bit `long` (8 bytes on EE, 4 on Windows); use int64_t off-PS2.
extern int D_004A6CA8[];

extern "C" void func_00158848(void* self, int a1, int a2, long value)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    *(long*)(p + 0xf78) = value;
}

extern int D_0045AFE8[];

//100%
extern "C" int func_00158870(void* self, int a1, int a2)
{
    return *(int*)((char*)D_0045AFE8 + ((a2 << 2) + (a1 << 4)));
}

extern int D_0045B018[];

//100%
extern "C" int func_00158890(void* self, int a1, int a2)
{
    return *(int*)((char*)D_0045B018 + ((a2 << 2) + (a1 << 4)));
}

extern void* D_0045B048[];

//100%
int func_001588B0(void* self, int a1)
{
    return *(int*)((char*)(void*)D_0045B048 + a1 * 4);
}

void* cBECharProfileDB_getScoreStats(void* self, int a, int b);
extern int D_004A6CA8[];

extern int D_0045AFE8[];

extern "C" int func_001588C8(void* self, int kind, int value)
{
    int* t = D_0045AFE8 + kind * 4;
    for (int i = 0; i < 4; i++)
    {
        if (value >= t[i])
            return i;
    }
    return -1;
}

//100%
struct sProfileSlot_00158910
{
    char data[0xF88];
};

signed char cBERewardInterface_getTrackMedal(void* self, int b, int c, int d, int e)
{
    void* result = cBECharProfileDB_getScoreStats(&((sProfileSlot_00158910 (*)[10])D_004A6CA8)[b][c], e, d);
    if (result == 0) {
        return -1;
    }
    return ((signed char*)result)[1];
}

//100%
extern "C" int func_00158960(void* self, int b, int c, int d, int e)
{
    void* result = cBECharProfileDB_getScoreStats(&((sProfileSlot_00158910 (*)[10])D_004A6CA8)[b][c], e, d);
    if (result == 0) {
        return 0;
    }
    return ((int*)result)[1];
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int func_00153708(void* iface, int a, int b, int c);

extern "C" int func_001589B0(void* self, int a, int b, int kind)
{
    int v = func_00153708(cBE_getInterface_Fv(cBE_getBE(), 0xA), a, b, kind);
    int* t = D_0045AFE8 + kind * 4;
    for (int i = 0; i < 4; i++)
    {
        if (v >= t[i])
            return i;
    }
    return -1;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int func_001544D0(void* iface, int a, int b, int c);

extern "C" int func_00158A50(void* self, int a, int b, int kind)
{
    int v = func_001544D0(cBE_getInterface_Fv(cBE_getBE(), 0xA), a, b, kind);
    int* t = D_0045B018 + kind * 4;
    for (int i = 0; i < 4; i++)
    {
        if (v >= t[i])
            return i;
    }
    return -1;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBEEconInterface_getTotalMoneyEarned(void* self, int a, int b);

extern "C" int cBERewardInterface_getEarningsMedal(void* self, int a, int b, int medal)
{
    unsigned int earned = cBEEconInterface_getTotalMoneyEarned(cBE_getInterface_Fv(cBE_getBE(), 0xB), a, b);
    if (earned >= *(unsigned int*)((char*)(void*)D_0045B048 + medal * 4))
        return 1;
    return -1;
}

extern int D_0045B018[];

extern "C" int func_00158B70(void* self, int kind, int value)
{
    int* t = D_0045B018 + kind * 4;
    for (int i = 0; i < 4; i++)
    {
        if (value >= t[i])
            return i;
    }
    return -1;
}

extern "C" int func_00158BB8(void* self, int medal, unsigned int value)
{
    if (value >= *(unsigned int*)((char*)(void*)D_0045B048 + medal * 4))
        return 1;
    return -1;
}

//100%
int cBERewardInterface_isBetterMedal(void* self, int a, int b);

extern "C" void* func_00158BE0(void* self, int a, int b)
{
    for (int i = 0; i < 3; i++)
    {
        if (!cBERewardInterface_isBetterMedal(self, -1, cBERewardInterface_getEarningsMedal(self, a, b, i)))
            return D_0045B048[i];
    }
    return 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" int func_001589B0(void* self, int a, int b, int kind);
extern int D_0045AFE8_2d[][4] __asm__("D_0045AFE8");

extern "C" int func_00158C80(void* self, int a, int b, int kind)
{
    int medal = func_001589B0(self, a, b, kind);
    int best = 0;
    for (int i = 0; i < 4; i++)
    {
        if (cBERewardInterface_isBetterMedal(self, medal, i))
        {
            if (best == 0 || D_0045AFE8_2d[kind][i] < best)
                best = D_0045AFE8_2d[kind][i];
        }
    }
    return best;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" int func_00158A50(void* self, int a, int b, int kind);
extern int D_0045B018_2d[][4] __asm__("D_0045B018");

extern "C" int func_00158D58(void* self, int a, int b, int kind)
{
    int medal = func_00158A50(self, a, b, kind);
    int best = 0;
    for (int i = 0; i < 4; i++)
    {
        if (cBERewardInterface_isBetterMedal(self, medal, i))
        {
            if (best == 0 || D_0045B018_2d[kind][i] < best)
                best = D_0045B018_2d[kind][i];
        }
    }
    return best;
}

//100%
int cBELibrary_getRiderIndex(int);
extern void* D_004A1260;
extern int D_00440F48[];
extern int D_00440F58[];
extern void* D_004C3EF0[];
extern "C" void func_0015A510(void* self);

extern "C" void func_00158E30(void* self)
{
    func_0015A510(D_004C3EF0);
    int charID = cBELibrary_getCharacterID(cBELibrary_getRiderIndex(0));
    D_004A1260 = func_00158BE0(self, 0, charID);
    for (int i = 0; i < 3; i++)
        D_00440F48[i] = func_00158C80(self, 0, charID, i);
    for (int i = 0; i < 3; i++)
        D_00440F58[i] = func_00158D58(self, 0, charID, i);
    char* p = (char*)D_004A1264;
    *(int*)(p + 0x10) = 0;
    *(int*)(p + 0x14) = -1;
}

extern void* D_004C3EF0[];

//100%
void* func_00158F20(void* self)
{
    return (void*)D_004C3EF0;
}

extern "C" void* func_0015A6F0(void*);

//100%
void* func_00158F30(void* self)
{
    return func_0015A6F0((void*)D_004C3EF0);
}

extern void* D_004C3EF0[];

extern "C" void* func_00158F50()
{
    return D_004C3EF0[0];
}

//100%
struct sReward_0015A628;
extern "C" void func_0015A628(sReward_0015A628* self, int row, int col, int value);
extern void* D_004C3EF0[];
extern int D_004A6CA8[];

// PORT: 64-bit `long` flags word (ld/sd).
struct sCharRec_158F60 {
    char pad0[0x278];
    long flags;     // 0x278
    char pad280[0xF88 - 0x280];
};

extern "C" void func_00158F60(void* self, int profile, int c, int row, int mode)
{
    sReward_0015A628* q = (sReward_0015A628*)D_004C3EF0;
    switch (mode)
    {
    case 0:
        break;
    case 2:
        if ((int)((*(sCharRec_158F60*)((char*)D_004A6CA8 + (profile * 0x9B50 + c * 0xF88))).flags >> 13) & 1)
        {
            (*(sCharRec_158F60*)((char*)D_004A6CA8 + (profile * 0x9B50 + c * 0xF88))).flags &= ~0x2000L;
            func_0015A628(q, row, 2, c * 3 + 2);
        }
    case 1:
        if ((int)((*(sCharRec_158F60*)((char*)D_004A6CA8 + (profile * 0x9B50 + c * 0xF88))).flags >> 12) & 1)
        {
            (*(sCharRec_158F60*)((char*)D_004A6CA8 + (profile * 0x9B50 + c * 0xF88))).flags &= ~0x1000L;
            func_0015A628(q, row, 2, c * 3 + 1);
        }
        break;
    }
}

//100%
extern "C" int func_00159080(void* self, int a1, int a2, int kind, int tier)
{
    int r = -1;
    switch (tier)
    {
    case 0:
        if (kind == 0)
            r = 5;
        else if (kind == 1)
            r = 6;
        else if (kind == 2)
            r = 7;
        break;
    case 1:
        if (kind == 0)
            r = 8;
        else if (kind == 1)
            r = 9;
        else if (kind == 2)
            r = 10;
        break;
    case 2:
        if (kind == 0)
            r = 11;
        else if (kind == 1)
            r = 12;
        else if (kind == 2)
            r = 13;
        break;
    case 3:
        if (kind == 0)
            r = 14;
        else if (kind == 1)
            r = 15;
        else if (kind == 2)
            r = 16;
        break;
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int func_0015A2E0(void* self, int a1, int a2, int bit);
extern "C" void func_00159CD0(void* self, int a1, int a2, int bit);

extern "C" void func_00159170(void* self, int a1, int a2, int kind, int tier)
{
    int bit = func_00159080(self, a1, a2, kind, tier);
    if (func_0015A2E0(self, a1, a2, bit) == 0)
    {
        func_00159CD0(self, a1, a2, bit);
    }
}

INCLUDE_ASM("be/beintreward", func_001591E8);

//100%
int cBELibrary_getProfileIndex(int);
int cBELibrary_getCharacterID(int);
extern "C" void func_00159818(void* self, int a, int b, int c);

extern "C" void func_001597B0(void* self, int rider, int c)
{
    int profile = cBELibrary_getProfileIndex(rider);
    func_00159818(self, profile, cBELibrary_getCharacterID(rider), c);
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBEEconInterface_getTotalMoneyEarned(void* self, int a, int b);
extern "C" int func_00157BF0(void* self, int a, int b, int c, int i);
extern "C" void func_00150A90(void* econ, int a, int b, int amount);
extern "C" void* func_00158BE0(void* self, int a, int b);
extern "C" void func_00159170(void* self, int a1, int a2, int kind, int tier);
extern void* D_004A1260;
extern void* D_004C3EF0[];

extern "C" void func_00159818(void* self, int a, int b, int amount)
{
    void* econ = cBE_getInterface_Fv(cBE_getBE(), 0xB);
    *(int*)D_004C3EF0 += amount;
    if (D_004A1260 != 0 && (unsigned int)(cBEEconInterface_getTotalMoneyEarned(econ, a, b) + amount) >= (unsigned int)D_004A1260)
    {
        int before[3];
        int i;
        for (i = 0; i < 3; i++)
            before[i] = func_00157BF0(self, a, b, i, 3);
        func_00150A90(econ, a, b, amount);
        D_004A1260 = func_00158BE0(self, a, b);
        for (i = 0; i < 3; i++)
        {
            if (before[i] == 0 && func_00157BF0(self, a, b, i, 3))
                func_00159170(self, a, b, i, 3);
        }
    }
    else
    {
        func_00150A90(econ, a, b, amount);
    }
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int cBEMissionInterface_getCurrentCollectForPeak(void* self, int rider, int owner);
int cBELibrary_getProfileIndex(int);
int cBELibrary_getCharacterID(int);
extern "C" int func_001577E0(void* self, int a, int b);
extern "C" int func_00157BF0(void* self, int a, int b, int c, int i);
extern "C" int func_00158C80(void* self, int a, int b, int kind);
extern "C" void func_00159170(void* self, int a1, int a2, int kind, int tier);
extern "C" int func_0015A2E0(void* self, int a1, int a2, int bit);
extern "C" void func_00159CD0(void* self, int a1, int a2, int bit);
extern int D_00440F48[];
extern int D_0045AFE8_2d[][4] __asm__("D_0045AFE8");

extern "C" void cBERewardInterface_OnCollectibleCollected(void* self, int rider, int k)
{
    int cur = cBEMissionInterface_getCurrentCollectForPeak(cBE_getInterface_Fv(cBE_getBE(), 0xA), rider, k);
    int* p = &D_00440F48[k];
    if (*p <= 0)
        return;
    if (cur < *p)
        return;
    int prof = cBELibrary_getProfileIndex(rider);
    int ch = cBELibrary_getCharacterID(rider);
    int was = func_00157BF0(self, prof, ch, k, 2);
    *p = func_00158C80(self, prof, ch, k);
    if (was && cur == D_0045AFE8_2d[k][3])
        func_00159170(self, prof, ch, k, 2);
    if (func_001577E0(self, prof, ch))
    {
        if (func_0015A2E0(self, prof, ch, 0) == 0)
            func_00159CD0(self, prof, ch, 0);
    }
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" int func_001543E0(void* self, int owner);
int cBELibrary_getProfileIndex(int);
int cBELibrary_getCharacterID(int);
extern "C" int func_001577E0(void* self, int a, int b);
extern "C" int func_00157BF0(void* self, int a, int b, int c, int i);
extern "C" int func_00158D58(void* self, int a, int b, int kind);
extern "C" void func_00159170(void* self, int a1, int a2, int kind, int tier);
extern "C" int func_0015A2E0(void* self, int a1, int a2, int bit);
extern "C" void func_00159CD0(void* self, int a1, int a2, int bit);
extern int D_00440F58[];
extern int D_0045B018_2d[][4] __asm__("D_0045B018");

extern "C" void cBERewardInterface_OnMissionCompleted(void* self, int rider, int k)
{
    int cur = func_001543E0(cBE_getInterface_Fv(cBE_getBE(), 0xA), k);
    int* p = &D_00440F58[k];
    if (*p <= 0)
        return;
    if (cur < *p)
        return;
    int prof = cBELibrary_getProfileIndex(rider);
    int ch = cBELibrary_getCharacterID(rider);
    int was = func_00157BF0(self, prof, ch, k, 2);
    *p = func_00158D58(self, prof, ch, k);
    if (was && cur == D_0045B018_2d[k][3])
        func_00159170(self, prof, ch, k, 2);
    if (func_001577E0(self, prof, ch))
    {
        if (func_0015A2E0(self, prof, ch, 0) == 0)
            func_00159CD0(self, prof, ch, 0);
    }
}

extern "C" void func_00159CD0(void* self, int a1, int a2, int bit);

extern "C" void func_00159C68(void* self, int rider, int bit)
{
    int profile = cBELibrary_getProfileIndex(rider);
    func_00159CD0(self, profile, cBELibrary_getCharacterID(rider), bit);
}

//100%
extern "C" void func_001E2578();
extern "C" void func_001E2518();
extern "C" void func_001E2428(int);
extern "C" void func_001E38B8(int);
extern "C" int func_0014B560(void*, int, int, int, int);
extern "C" void func_0015A358(void* self, int bit, unsigned char* bits);
struct sI4_9CD0 { int v[4]; };
extern sI4_9CD0 D_0045AA28_9CD0 __asm__("D_0045AA28");
struct sI2_9CD0 { int v[2]; };
extern int D_004A1268_9CD0[] __asm__("D_004A1268");

extern "C" void func_00159CD0(void* self, int a, int b, int bit)
{
    char* p = (char*)D_004A6CA8 + a * 0x9b50 + b * 0xf88;
    sReward_0015A628* q = (sReward_0015A628*)D_004C3EF0;
    sI4_9CD0 t1 = D_0045AA28_9CD0;
    sI2_9CD0 t2 = *(sI2_9CD0*)D_004A1268_9CD0;
    int x = -1;
    int code = 0;
    int i, j;

    if (!((unsigned)(bit - 0x11) < 3)) {
        if (func_0015A2E0(self, a, b, bit)) {
            return;
        }
    }

    switch (bit) {
    case 0:
        func_001E2578();
        code = 0x1D;
        break;
    case 1:
        func_001E2518();
        code = 0x18;
        break;
    case 2:
        func_001E2428(0);
        code = 0x12;
        break;
    case 3:
        func_001E2428(1);
        code = 0x19;
        break;
    case 4:
        func_001E2428(2);
        code = 0x1A;
        break;
    case 5:
    case 8:
    case 11:
    case 14:
        for (i = 0; i < 4; i++) {
            t1.v[i] = func_00157080(self, a, b, 4);
            if (t1.v[i] < 0) {
                break;
            }
            func_001580F8_jt(self, a, b, t1.v[i], 0);
            func_0015A628(q, bit, 4, t1.v[i]);
        }
        {
            int r = func_00157080(self, a, b, 3);
            if (r >= 0) {
                func_00157FD0_jt(self, a, b, r, 0);
                func_0015A628(q, bit, 3, r);
            }
        }
        if (bit == 0xB) {
            func_001E38B8(a);
        }
        func_00158F60(self, a, b, bit, 1);
        break;
    case 6:
    case 9:
    case 12:
    case 15:
        {
            int r = func_00157080(self, a, b, 7);
            if (r >= 0) {
                func_00158348_jt(self, a, b, r, 0);
                func_0015A628(q, bit, 7, r);
            }
        }
        for (i = 0; i < 2; i++) {
            t2.v[i] = func_00157080(self, a, b, 5);
            if (t2.v[i] < 0) {
                break;
            }
            func_00158220_jt(self, a, b, t2.v[i], 0);
            func_0015A628(q, bit, 5, t2.v[i]);
        }
        if (bit == 0xC) {
            func_001E38B8(a);
        }
        func_00158F60(self, a, b, bit, 2);
        break;
    case 7:
        code = 0x1B;
        break;
    case 10:
        code = 0x17;
        break;
    case 13:
        code = 0x1C;
        break;
    case 16:
        code = 0x15;
        break;
    case 17:
        x = func_00156C70(self, a, b, 0);
        break;
    case 18:
        x = func_00156C70(self, a, b, 1);
        break;
    case 19:
        x = func_00156C70(self, a, b, 2);
        break;
    case 20: case 21: case 22: case 23: case 24: case 25:
    case 26: case 27: case 28: case 29: case 30: case 31:
        x = func_00156EE0(self, a, b);
        break;
    }

    func_0015A358(self, bit, (unsigned char*)(p + 0xF28));
    if (code) {
        func_0015A628(q, bit, 8, code);
        func_00158618_jt(self, a, b, code, 0);
    }
    if (x != -1) {
        void* iface = cBE_getInterface_Fv(cBE_getBE(), 9);
        func_0015A628(q, bit, 9, x);
        func_0014B560(iface, a, b, x, 0);
    }
    if (func_001577E0(self, a, b)) {
        if (func_0015A2E0(self, a, b, 0) == 0) {
            func_00159CD0(self, a, b, 0);
        }
    }
    if (func_001578A0(self, a, b)) {
        if (func_0015A2E0(self, a, b, 1) == 0) {
            func_00159CD0(self, a, b, 1);
        }
    }
    for (j = 0; j < 3; j++) {
        if (func_00157A78(self, a, b, j)) {
            if (func_0015A2E0(self, a, b, j + 2) == 0) {
                func_00159CD0(self, a, b, j + 2);
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            int bb = func_00159080(self, a, b, i, j);
            if (func_00157BF0(self, a, b, i, j)) {
                if (func_0015A2E0(self, a, b, bb) == 0) {
                    func_00159170(self, a, b, i, j);
                }
            }
        }
    }
}

//100%
extern int D_004A6CA8[];
extern "C" int func_0015A320(void* self, int bit, unsigned char* bits);

extern "C" int func_0015A2E0(void* self, int a1, int a2, int bit)
{
    char* p = (char*)D_004A6CA8 + a1 * 0x9b50 + a2 * 0xf88;
    return func_0015A320(self, bit, (unsigned char*)(p + 0xF28));
}

//100%
extern "C" int func_0015A320(void* self, int bit, unsigned char* bits)
{
    int shift = bit % 8;
    return (bits[(unsigned int)bit / 8] >> shift) & 1;
}

//100%
extern "C" void func_0015A358(void* self, int bit, unsigned char* bits)
{
    int shift = bit % 8;
    bits[(unsigned int)bit / 8] |= 1 << shift;
}

// 0x64-byte array elements; arr[i].field indexing reproduces the target's
// base-first addu
struct sBERewardEntry {
    char pad_0x00[0x54];
    int field_0x54;
    char pad_0x58[0xc];
};
extern sBERewardEntry D_0043D950[];

//100%
extern "C" int func_0015A398(void* self, int a1)
{
    return D_0043D950[a1].field_0x54;
}

//100%
struct sRewardPair_0015A3B8
{
    signed char a;
    signed char b;
};

extern sRewardPair_0015A3B8 D_0045AAD8[3][4][5];

extern "C" int func_0015A3B8(void* self, int a, int b)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (D_0045AAD8[i][j][k].a == a)
                {
                    if (D_0045AAD8[i][j][k].b == b || a == 6 || a == 7 || a == 8 || a == 9 || a == 10 || a == 11)
                        return j;
                }
            }
        }
    }
    return -1;
}

extern void* D_004C3E98[];

void* func_0015A478(void* self)
{
    return (void*)D_004C3E98;
}

//100%
extern "C" void func_0015A510(void* self);

struct sRewardStrings_0015A488 {
    char pad_0x000[0x174];
    char* mStrings[10]; // 0x174
};

extern "C" void* func_0015A488(sRewardStrings_0015A488* self)
{
    for (int i = 0; i < 10; i++)
        self->mStrings[i] = 0;
    char* base = (char*)self;
    self->mStrings[0] = base + 0x146;
    self->mStrings[2] = base + 0x170;
    self->mStrings[3] = base + 0x147;
    self->mStrings[4] = base + 0x14D;
    self->mStrings[5] = base + 0x15C;
    self->mStrings[7] = base + 0x169;
    self->mStrings[8] = base + 0x16D;
    func_0015A510(self);
    return self;
}

//100%
extern "C" void func_003E6448(void* dst, int c, int n);

extern "C" void func_0015A510(void* self)
{
    func_003E6448(self, 0, 0x174);
    *(short*)((char*)self + 0x4) = -1;
}

// Counts the set bits among the first `count` bits of `bits` (LSB first).
extern "C" int func_0015A548(void* self, int count, unsigned char* bits)
{
    int i = 0;
    int j = 0;
    int total = 0;
    while (i < count)
    {
        unsigned char b = bits[j++];
        for (int k = 0; k < 8 && i < count; k++)
        {
            i++;
            total += (b >> k) & 1;
        }
    }
    return total;
}

//100%
extern "C" void func_0015A5B0(void* self, int bit, unsigned char* bits)
{
    int shift = bit % 8;
    bits[(unsigned int)bit / 8] |= 1 << shift;
}

//100%
extern "C" int func_0015A5F0(void* self, int bit, unsigned char* bits)
{
    int shift = bit % 8;
    return (bits[(unsigned int)bit / 8] >> shift) & 1;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sRewardRow_0015A628
{
    unsigned char counts[8]; // 0x0
    unsigned char value;     // 0x8
    unsigned char flag;      // 0x9
};

struct sReward_0015A628
{
    char pad_0x000[0x4];
    short mValue;                    // 0x4
    sRewardRow_0015A628 mRows[0x1D]; // 0x6
    char pad_0x128[0x174 - 0x128];
    unsigned char* mBits[10];        // 0x174
};

extern "C" void func_0015A628(sReward_0015A628* self, int row, int col, int value)
{
    switch (col)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        func_0015A5B0(self, value, self->mBits[col]);
        self->mRows[row].counts[col]++;
        break;
    case 8:
        self->mRows[row].value = value;
        break;
    case 9:
        self->mRows[row].flag = 1;
        self->mValue = value;
        break;
    }
}

//100%
struct sRewardGrid_0015A6F0
{
    char pad_0x00[0x6];
    signed char vals[32][10]; // 0x6 (func_0015A750 reads vals[a1][a2])
};

// PORT: the unit declares func_0015A6F0 as returning void* (line ~378, used by
// func_00158F30); the body returns an int sum, so it is bound by asm label.
// The lander should change that declaration to int instead.
int func_0015A6F0_impl(sRewardGrid_0015A6F0* self) __asm__("func_0015A6F0");

int func_0015A6F0_impl(sRewardGrid_0015A6F0* self)
{
    int sum = 0;
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            sum += self->vals[i][j];
        }
    }
    return sum;
}

//100%
extern "C" signed char func_0015A750(void* self, int a1, int a2)
{
    return *(signed char*)((char*)self + (a1 * 0xa + a2) + 0x6);
}

//100%
int func_0015A768(void* self, int i)
{
    return *(int*)((char*)self + (i << 2) + 0x174);
}

//100%
extern "C" void* func_0015A778(void* self)
{
    *(int*)((char*)self + 0x4) = 0;
    *(int*)((char*)self + 0x0) = -1;
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0xC) = 0;
    *(int*)((char*)self + 0x10) = 0;
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0x18) = 0;
    *(int*)((char*)self + 0x1C) = 0;
    *(int*)((char*)self + 0x20) = 0;
    *(int*)((char*)self + 0x24) = 0;
    *(int*)((char*)self + 0x2C) = 0;
    *(int*)((char*)self + 0x30) = 0;
    *(int*)((char*)self + 0x34) = 0;
    *(int*)((char*)self + 0x38) = 0;
    *(int*)((char*)self + 0x3C) = 0;
    *(int*)((char*)self + 0x40) = 0;
    *(int*)((char*)self + 0x44) = 0;
    *(int*)((char*)self + 0x48) = 0;
    *(int*)((char*)self + 0x4C) = 0;
    return self;
}

//100%
void operator_delete(int* ptr);
extern "C" void func_0015AE00(void* self);

extern "C" void cBERewardDB_dtor(int* self, int flags)
{
    func_0015AE00(self);
    if (flags & 1)
    {
        operator_delete(self);
    }
}

//100%
struct sRwE12_A818 { int s[3]; };
struct sRwE8_A818 { int s[2]; };
struct sRwE16_A818 { int s[3]; int pad; };

struct sRwDB_A818 {
    int pad0;
    int* data;
    sRwE12_A818* t0;
    sRwE12_A818* t1;
    sRwE8_A818* t2;
    sRwE16_A818* t3;
    sRwE16_A818* t4;
    sRwE16_A818* t5;
    sRwE16_A818* t7;
    sRwE16_A818* t6;
    sRwE16_A818* t8;
    char* strings;
    int n0;
    int n1;
    int n2;
    int n3;
    int n4;
    int n5;
    int n7;
    int n6;
    int n8;
};

#define FIX_A818(e, k)                                  \
    if ((e)->s[k] != 0) {                               \
        (e)->s[k] = (int)(db->strings + ((e)->s[k] - 1)); \
    }

extern "C" void func_0015A818(sRwDB_A818* db, int* p)
{
    int i;
    db->data = p;
    for (i = 0; i < 9; i++) {
        int type = *p++;
        int n = *p++;
        if (n == 0) {
            continue;
        }
        switch (type) {
        case 0:
            db->t0 = (sRwE12_A818*)p;
            db->n0 = n;
            p = (int*)((sRwE12_A818*)p + n);
            break;
        case 1:
            db->t1 = (sRwE12_A818*)p;
            db->n1 = n;
            p = (int*)((sRwE12_A818*)p + n);
            break;
        case 2:
            db->t2 = (sRwE8_A818*)p;
            db->n2 = n;
            p = (int*)((sRwE8_A818*)p + n);
            break;
        case 3:
            db->t3 = (sRwE16_A818*)p;
            db->n3 = n;
            p = (int*)((sRwE16_A818*)p + n);
            break;
        case 4:
            db->t4 = (sRwE16_A818*)p;
            db->n4 = n;
            p = (int*)((sRwE16_A818*)p + n);
            break;
        case 5:
            db->t5 = (sRwE16_A818*)p;
            db->n5 = n;
            p = (int*)((sRwE16_A818*)p + n);
            break;
        case 6:
            db->t6 = (sRwE16_A818*)p;
            db->n6 = n;
            p = (int*)((sRwE16_A818*)p + n);
            break;
        case 7:
            db->t7 = (sRwE16_A818*)p;
            db->n7 = n;
            p = (int*)((sRwE16_A818*)p + n);
            break;
        case 8:
            db->t8 = (sRwE16_A818*)p;
            db->n8 = n;
            p = (int*)((sRwE16_A818*)p + n);
            break;
        }
    }
    int j;
    p++;
    db->strings = (char*)p;
    for (j = 0; j < db->n0; j++) {
        sRwE12_A818* e = &db->t0[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
        FIX_A818(e, 2);
    }
    for (j = 0; j < db->n1; j++) {
        sRwE12_A818* e = &db->t1[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
        FIX_A818(e, 2);
    }
    for (j = 0; j < db->n2; j++) {
        sRwE8_A818* e = &db->t2[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
    }
    for (j = 0; j < db->n3; j++) {
        sRwE16_A818* e = &db->t3[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
        FIX_A818(e, 2);
    }
    for (j = 0; j < db->n4; j++) {
        sRwE16_A818* e = &db->t4[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
        FIX_A818(e, 2);
    }
    for (j = 0; j < db->n5; j++) {
        sRwE16_A818* e = &db->t5[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
        FIX_A818(e, 2);
    }
    for (j = 0; j < db->n6; j++) {
        sRwE16_A818* e = &db->t6[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
        FIX_A818(e, 2);
    }
    for (j = 0; j < db->n7; j++) {
        sRwE16_A818* e = &db->t7[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
        FIX_A818(e, 2);
    }
    for (j = 0; j < db->n8; j++) {
        sRwE16_A818* e = &db->t8[j];
        FIX_A818(e, 0);
        FIX_A818(e, 1);
        FIX_A818(e, 2);
    }
}


