#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void cBEOptionInterface_Init(void* self);
extern const char D_0045A6B0[];
extern void* D_0045ADC8[16];
extern void* D_004A120C;

struct cBEOptionInterface {
    char pad_0x00[8];
    int field_0x8;
    void* vtable;
};

//100%
void* cBEOptionInterface_getThis()
{
    if (D_004A120C == 0) {
        cBEOptionInterface* mem = (cBEOptionInterface*)cMemMan_alloc(0x10, D_0045A6B0, 0, 0);
        mem->vtable = D_0045ADC8;
        D_004A120C = mem;
        mem->field_0x8 = 0;
        cBEOptionInterface_Init(mem);
    }
    return D_004A120C;
}

//100%
struct sOptions_0014F2A8
{
    int data[0x288 / 4];
};

extern sOptions_0014F2A8 D_00535610;
extern sOptions_0014F2A8 D_00535898;

extern "C" void func_0014F2A8(void)
{
    D_00535898 = D_00535610;
}

//100%
extern sOptions_0014F2A8 D_00535610;
extern sOptions_0014F2A8 D_00535898;

extern "C" void func_0014F360(void)
{
    D_00535610 = D_00535898;
}

//100%
extern "C" void func_0014F648(void* self);
extern "C" void func_0014F600(void* self);
extern "C" void func_0014F4F8(void* self);
extern "C" void func_0014F458(void* self);

extern "C" void cBEOptionInterface_Init(void* self)
{
    func_0014F648(self);
    func_0014F600(self);
    func_0014F4F8(self);
    func_0014F458(self);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sOptBits_0014F458
{
    unsigned int a : 4;
    unsigned int b : 4;
    unsigned int c : 4;
    unsigned int d : 2;
    unsigned int e : 2;
    unsigned int f : 1;
    unsigned int g : 1;
    unsigned int h : 1;
    unsigned int rest0 : 13;
    unsigned int w1a : 2;
    unsigned int rest1 : 30;
};
extern sOptBits_0014F458 D_00535610_v0014F458[] __asm__("D_00535610");

class cBEOptionInterfaceV_0014F458
{
public:
    char pad_0x00[0xC];
    virtual void apply();
};

extern "C" void func_0014F458(void* self)
{
    sOptBits_0014F458* o = D_00535610_v0014F458;
    o->a = 0xA;
    o->b = 0xA;
    o->c = 0xA;
    o->d = 0;
    o->e = 0;
    o->f = 1;
    o->g = 1;
    o->h = 1;
    o->w1a = 1;
    ((cBEOptionInterfaceV_0014F458*)D_004A120C)->apply();
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern void* D_004A28A8;

struct sOptBits_0014F4F8
{
    unsigned int pad0 : 19;
    unsigned int i : 1;     // 19
    unsigned int j : 2;     // 20-21
    unsigned int k : 3;     // 22-24
    unsigned int l : 4;     // 25-28
    unsigned int m : 1;     // 29
    unsigned int top : 2;   // 30-31
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
    unsigned char b7;
};
extern sOptBits_0014F4F8 D_00535610_v0014F4F8[] __asm__("D_00535610");

class cBEOptionInterfaceV_0014F4F8
{
public:
    char pad_0x00[0xC];
    virtual void apply();
};

extern "C" void func_0014F4F8(void* self)
{
    switch (*(int*)(*(char**)((char*)D_004A28A8 + 0x9C) + 0x24))
    {
    case 1:
        D_00535610_v0014F4F8[0].j = 2;
        break;
    case 2:
        D_00535610_v0014F4F8[0].j = 1;
        break;
    case 0:
    default:
        D_00535610_v0014F4F8[0].j = 0;
        break;
    }
    D_00535610_v0014F4F8[0].k = 0;
    D_00535610_v0014F4F8[0].i = 0;
    D_00535610_v0014F4F8[0].m = 0;
    D_00535610_v0014F4F8[0].l = 9;
    D_00535610_v0014F4F8[0].b5 = 0;
    D_00535610_v0014F4F8[0].b6 = 0;
    ((cBEOptionInterfaceV_0014F4F8*)D_004A120C)->apply();
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sOptBits_0014F600
{
    unsigned int pad : 30;
    unsigned int top : 2;
};
extern sOptBits_0014F600 D_00535610_v0014F600[] __asm__("D_00535610");

class cBEOptionInterfaceV_0014F600
{
public:
    char pad_0x00[0xC];
    virtual void apply();
};

extern "C" void func_0014F600(void* self)
{
    D_00535610_v0014F600[0].top = 0;
    ((cBEOptionInterfaceV_0014F600*)D_004A120C)->apply();
}

//100%
class cBEOptionInterfaceV_0014F648
{
public:
    char pad_0x00[0xC];
    virtual void apply();
};

extern "C" void func_0014F648(void* self)
{
    ((cBEOptionInterfaceV_0014F648*)D_004A120C)->apply();
}

extern "C" int sprintf(char* buf, const char* fmt, ...);
int GetHashValue32(char* str);
extern const char D_0045A6C0[];

//100%
int cBEOptionInterface_getDefaultQuickKeyMessageHashValue(void* self, int value)
{
    char buf[24];
    sprintf(buf, D_0045A6C0, value);
    return GetHashValue32(buf);
}

//100%
extern "C" unsigned int strlen(const char* s);
extern char D_00535617[][0x40];

extern "C" char* func_0014F6A8(void* self, int i)
{
    char* s = D_00535617[i];
    if (strlen(s) == 0) {
        return 0;
    }
    return s;
}

//100%
extern void* D_004A28A8;
extern "C" void func_003DCB20(char* dst, void* src);

struct sVEntry_0014F6E8
{
    short delta;
    short index;
    void* (*fn)(void*, int);
};

extern "C" void func_0014F6E8(void* self, int i)
{
    char* obj = *(char**)((char*)D_004A28A8 + 0x8C);
    sVEntry_0014F6E8* vt = *(sVEntry_0014F6E8**)(obj + 0x4);
    char* o2 = obj + vt[4].delta;
    int h = cBEOptionInterface_getDefaultQuickKeyMessageHashValue(self, i);
    void* text = vt[4].fn(o2, h);
    func_003DCB20(D_00535617[i], text);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_0014F6E8(void* self, int i);

extern "C" void func_0014F758(void* self)
{
    for (int i = 0; i < 10; i++)
    {
        func_0014F6E8(self, i);
    }
}

//100%
struct sOptionTripleView_0014F7A8 {
    int a;
    int b;
    int c;
};

struct sOptionTriplesView_0014F7A8 {
    sOptionTripleView_0014F7A8 triples[2]; // 0x0
};

struct sOptionGlobal_005308B8;
extern sOptionGlobal_005308B8 D_005308B8;
extern "C" int func_0014F870();

extern "C" int func_0014F7A8(int i)
{
    int c = ((sOptionTriplesView_0014F7A8*)&D_005308B8)->triples[i].c;
    return func_0014F870() - c;
}

//100%
extern "C" int func_0014F870();
extern int D_005308D4[]; // D_005308B8 + 0x1C, addressed through its own symbol

extern "C" int func_0014F7E8(void* self)
{
    return func_0014F870() - D_005308D4[0];
}

//100%
// View of D_005308B8 (the unit defines sOptionGlobal_005308B8 further down).
struct sOptionTriple_005308B8 {
    int a;
    int b;
    int c;
};

struct sOptionView_005308B8 {
    sOptionTriple_005308B8 triples[2]; // 0x0
    int field_0x18;
    int field_0x1C;
};

struct sOptionGlobal_005308B8;
extern sOptionGlobal_005308B8 D_005308B8;

extern "C" int func_0014F810(int i)
{
    sOptionView_005308B8* g = (sOptionView_005308B8*)&D_005308B8;
    if (g->triples[i].a != 0 || g->triples[i].b != 0 || g->triples[i].c != 0 || g->field_0x18 != 0 || g->field_0x1C != 0)
    {
        return 1;
    }
    return 0;
}

//100%
struct sOptionGlobal_005308B8 {
    char pad_0x00[0x8];
    int field_0x8;
    char pad_0xC[0x8];
    int field_0x14;
    char pad_0x18[0x4];
    int field_0x1C;
};
extern sOptionGlobal_005308B8 D_005308B8;

extern "C" int func_0014F870()
{
    int m = D_005308B8.field_0x1C;
    if (m < D_005308B8.field_0x8)
        m = D_005308B8.field_0x8;
    if (m < D_005308B8.field_0x14)
        m = D_005308B8.field_0x14;
    return m;
}

//100%
struct sOptionTriple_0014F898 {
    int a;
    int b;
    int c;
};

// Swaps the two 12-byte triples at the start of D_005308B8.
extern "C" void func_0014F898()
{
    sOptionTriple_0014F898* t = (sOptionTriple_0014F898*)&D_005308B8;
    sOptionTriple_0014F898 tmp = t[0];
    t[0] = t[1];
    t[1] = tmp;
}

