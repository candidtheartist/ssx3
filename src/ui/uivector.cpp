#include "common.h"

// Flag words at cUIVector + 0x14 and + 0x74. The setters take an int and store it into a
// bool bitfield: that int->bool conversion is the `sltu` in their asm.
// Flag words at cUIVector + 0x14 and + 0x74. The setters take an int and store it into a
// bool bitfield: that int->bool conversion is the `sltu` in their asm.
struct sUIVectorFlags {
    bool bit0 : 1;
    bool bit1 : 1;
    bool bit2 : 1;
    bool bit3 : 1;
    bool bit4 : 1;
    bool bit5 : 1;
    bool bit6 : 1;
    bool bit7 : 1;
};

// The same flag word at + 0x14, read/written as plain unsigned fields.
struct sUIVectorFields {
    unsigned int bit0 : 1;
    unsigned int bit1 : 1;
    unsigned int bit2 : 1;
    unsigned int bit3 : 1;
    unsigned int bit4 : 1;
    unsigned int bit5 : 1;
    unsigned int bit6 : 1;
    unsigned int bit7 : 1;
    unsigned int layer : 5;
    unsigned int f13 : 6;
};

// The word at cUIVector + 0x74 (bits 17..31 hold the point count).
struct sUIVector74 {
    unsigned int bit0 : 1;
    unsigned int bit1 : 1;
    unsigned int bits2 : 2;
};

// Generic 2-bit fields used by the setters of the other UI classes in this file.
struct sUIBits2At0 {
    unsigned int f0 : 2;
};

struct sUIBits2At1 {
    unsigned int bit0 : 1;
    unsigned int f1 : 2;
};

// Flag word at + 0x1C of a UI text-like class (see the getters/setters at 0x3A5848..0x3A5A88).
struct sUIFlags1C {
    unsigned int bit0 : 1;
    unsigned int f1 : 2;
    unsigned int bit3 : 1;
    unsigned int bit4 : 1;
    unsigned int bit5 : 1;
    unsigned int bit6 : 1;
    unsigned int bit7 : 1;
    unsigned int f8 : 6;
    unsigned int bit14 : 1;
    unsigned int bit15 : 1;
};

// 12 bytes, 4-byte aligned (copied with ldl/ldr + lw). Float fields are a guess.
struct sVec3 {
    float x;
    float y;
    float z;
};

INCLUDE_ASM("ui/uivector", cUIVector_setUIData);

INCLUDE_ASM("ui/uivector", func_003A36D0);

INCLUDE_ASM("ui/uivector", func_003A3808);

//100%
INCLUDE_ASM("ui/uivector", func_003A39F8);
#ifdef SKIP_ASM
// PORT: func_004139F8 is libgcc's __fixunssfsi (float -> unsigned); called by its address name.
extern "C" unsigned int func_004139F8(float f);
extern void* D_004A289C;

struct sV3_3A39F8 {
    float x, y, z;
};

struct sV4_3A39F8 {
    float v[4];
} __attribute__((aligned(16)));

struct sCol_3A39F8 {
    float r, g, b, a;
};

struct sVtx_3A39F8 {
    float s;
    float t;
    float q;
    int padC;
    int col[4];         // 0x10
    sV4_3A39F8 pos;     // 0x20
};

struct sCount_3A39F8 {
    unsigned int flag : 1;
    unsigned int pad1 : 1;
    unsigned int mode : 15;
    unsigned int count : 15;
};

struct sFlags14_3A39F8 {
    unsigned char b14;
    unsigned char layer : 5;
};

struct sRS_3A39F8 {
    int f0;
    int f4;
    int f8;
    int fC;
    short f10;
};

struct sVE_3A39F8 { short delta; short index; void* fn; };

typedef void (*tDraw_3A39F8)(void*, int, int, void*, void*, int, void*, void*);
typedef void (*tDraw2_3A39F8)(void*, int, void*, int);

static inline void SetCol_3A39F8(sVtx_3A39F8& vtx, int k, float v)
{
    vtx.col[k] = func_004139F8(v * 0.5f);
}

static inline void AddPos_3A39F8(sV4_3A39F8& p, int k, float d)
{
    p.v[k] += d;
}

extern "C" void func_003A39F8(char* self, float x, float y)
{
    if (*(sV3_3A39F8**)(self + 0x80) == 0)
        return;
    for (unsigned int i = 0; i < ((sCount_3A39F8*)(self + 0x74))->count; i++)
    {
        (*(sV3_3A39F8**)(self + 0x84))[i] = (*(sV3_3A39F8**)(self + 0x80))[i];
        (*(sV3_3A39F8**)(self + 0x84))[i].x *= *(float*)(self + 0x50);
        (*(sV3_3A39F8**)(self + 0x84))[i].y *= *(float*)(self + 0x54);
    }
    sRS_3A39F8* rs = *(sRS_3A39F8**)((char*)D_004A289C + 0xE84);
    rs->f8 = (rs->f8 & ~0x3E0) | (((((sFlags14_3A39F8*)(self + 0x14))->layer) + 9) << 5 & 0x3E0);
    *(short*)(*(char**)((char*)D_004A289C + 0xE84) + 0x10) = -1;
    if (((sCount_3A39F8*)(self + 0x74))->flag)
    {
        float pos[3];
        pos[0] = *(float*)(self + 0x44) + x;
        pos[1] = *(float*)(self + 0x48) + y;
        pos[2] = 0.0f;
        char* g = (char*)D_004A289C;
        sVE_3A39F8* vt = *(sVE_3A39F8**)(g + 0x10D8);
        ((tDraw_3A39F8)vt[72].fn)(g + vt[72].delta, ((sCount_3A39F8*)(self + 0x74))->mode, ((sCount_3A39F8*)(self + 0x74))->count,
                                  *(void**)(self + 0x78), *(void**)(self + 0x84), 0, *(void**)(self + 0x7C), pos);
        return;
    }
    if (*(sVtx_3A39F8**)(self + 0x8C) == 0)
        return;
    for (unsigned int i = 0; i < ((sCount_3A39F8*)(self + 0x74))->count; i++)
    {
        sV4_3A39F8 tt;
        tt.v[0] = (*(sV3_3A39F8**)(self + 0x84))[i].x;
        tt.v[1] = (*(sV3_3A39F8**)(self + 0x84))[i].y;
        tt.v[2] = (*(sV3_3A39F8**)(self + 0x84))[i].z;
        tt.v[3] = 1.0f;
        (*(sVtx_3A39F8**)(self + 0x8C))[i].pos = tt;
        AddPos_3A39F8((*(sVtx_3A39F8**)(self + 0x8C))[i].pos, 0, *(float*)(self + 0x44) + x);
        AddPos_3A39F8((*(sVtx_3A39F8**)(self + 0x8C))[i].pos, 1, *(float*)(self + 0x48) + y);
        (*(sVtx_3A39F8**)(self + 0x8C))[i].q = 1.0f;
        (*(sVtx_3A39F8**)(self + 0x8C))[i].s = 0.0f;
        (*(sVtx_3A39F8**)(self + 0x8C))[i].t = 0.0f;
        SetCol_3A39F8((*(sVtx_3A39F8**)(self + 0x8C))[i], 3, (*(sCol_3A39F8**)(self + 0x7C))[i].r);
        SetCol_3A39F8((*(sVtx_3A39F8**)(self + 0x8C))[i], 0, (*(sCol_3A39F8**)(self + 0x7C))[i].g);
        SetCol_3A39F8((*(sVtx_3A39F8**)(self + 0x8C))[i], 1, (*(sCol_3A39F8**)(self + 0x7C))[i].b);
        SetCol_3A39F8((*(sVtx_3A39F8**)(self + 0x8C))[i], 2, (*(sCol_3A39F8**)(self + 0x7C))[i].a);
    }
    char* g = (char*)D_004A289C;
    sVE_3A39F8* vt = *(sVE_3A39F8**)(g + 0x10D8);
    ((tDraw2_3A39F8)vt[73].fn)(g + vt[73].delta, ((sCount_3A39F8*)(self + 0x74))->count, *(void**)(self + 0x8C), 0);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A3D28);
#ifdef SKIP_ASM
extern "C" void func_003975E0(void*, void*, unsigned char, unsigned short);
extern "C" void func_003974B0(void*, unsigned char);

extern "C" void func_003A3D28(void* self, unsigned short ev)
{
    void* a = *(void**)((char*)self + 0xC);
    if (a != 0) {
        func_003975E0(a, self, *(unsigned char*)((char*)self + 0x10), ev);
        func_003974B0(*(void**)((char*)self + 0xC), *(unsigned char*)((char*)self + 0x10));
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A3D70);
#ifdef SKIP_ASM
struct func_003A3D70_sVec3 {
    float x;
    float y;
    float z;
};

extern func_003A3D70_sVec3 D_004FF0D8;

extern "C" void func_003A3D70(void* self, func_003A3D70_sVec3* out)
{
    if (*(func_003A3D70_sVec3**)((char*)self + 0x80) == 0) {
        return;
    }
    *out = D_004FF0D8;
    float minX = 1000.0f;
    float maxX = -1000.0f;
    float minY = 1000.0f;
    float maxY = -1000.0f;
    unsigned int i;
    for (i = 0; i < *(unsigned int*)((char*)self + 0x74) >> 17; i++) {
        func_003A3D70_sVec3* p = &(*(func_003A3D70_sVec3**)((char*)self + 0x80))[i];
        if (p->x < minX) {
            minX = p->x;
        }
        if (maxX < p->x) {
            maxX = p->x;
        }
        if (p->y < minY) {
            minY = p->y;
        }
        if (maxY < p->y) {
            maxY = p->y;
        }
    }
    out->x = maxX - minX;
    out->y = maxY - minY;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A3E38);
#ifdef SKIP_ASM
struct func_003A3E38_sVec3 {
    float x;
    float y;
    float z;
};

struct func_003A3E38_sCount74 {
    unsigned int lo : 17;
    unsigned int count : 15;
};

extern "C" void func_003A3E38(void* self, func_003A3E38_sVec3* off)
{
    if (((func_003A3E38_sCount74*)((char*)self + 0x74))->count == 4) {
        signed char i;
        for (i = 1; i < 4; i++) {
            (*(func_003A3E38_sVec3**)((char*)self + 0x80))[i] = (*(func_003A3E38_sVec3**)((char*)self + 0x80))[0];
        }
        (*(func_003A3E38_sVec3**)((char*)self + 0x80))[1].x += off->x;
        (*(func_003A3E38_sVec3**)((char*)self + 0x80))[3].y += off->y;
        (*(func_003A3E38_sVec3**)((char*)self + 0x80))[2].x += off->x;
        (*(func_003A3E38_sVec3**)((char*)self + 0x80))[2].y += off->y;
    }
    *(func_003A3E38_sVec3*)((char*)self + 0x60) = *off;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A3F08);
#ifdef SKIP_ASM
extern "C" void* func_003A3F08(void* self, ...)
{
    return self;
}
#endif

INCLUDE_ASM("ui/uivector", func_003A3F48);

//100%
INCLUDE_ASM("ui/uivector", func_003A4778);
#ifdef SKIP_ASM
extern void* D_00494D08[];

extern "C" void* func_003A4778(void* self)
{
    *(void***)((char*)self + 0x10) = D_00494D08;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4790);
#ifdef SKIP_ASM
extern "C" int func_003A4790(void* self)
{
    return *(int*)(*(char**)self + 0x8);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A47A0);
#ifdef SKIP_ASM
extern "C" void func_003A47A0(void* self, short value)
{
    *(short*)((char*)self + 0xA) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A47A8);
#ifdef SKIP_ASM
void operator_delete(int* ptr);

extern void* D_00494CE8[];

extern "C" void func_003A47A8(int* self, int flags)
{
    *(void***)self = D_00494CE8;
    if (flags & 1) {
        operator_delete(self);
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A47D8);
#ifdef SKIP_ASM
extern void* D_00494CC0[];

// Empty list head: next/prev point to itself.
extern "C" void* func_003A47D8(void* self)
{
    *(void**)((char*)self + 0x4) = self;
    *(void***)((char*)self + 0x8) = D_00494CC0;
    *(void**)((char*)self + 0x0) = self;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A47F8);
#ifdef SKIP_ASM
void operator_delete(int* ptr);
extern "C" void func_003A4868(void* self);

extern void* D_00494CC0[];

extern "C" void func_003A47F8(int* self, int flags)
{
    *(void***)((char*)self + 0x8) = D_00494CC0;
    func_003A4868(self);
    if (flags & 1) {
        operator_delete(self);
    }
}
#endif

extern "C" void cListNode_removeFromList(void*);

//100%
INCLUDE_ASM("ui/uivector", func_003A4848);
#ifdef SKIP_ASM
extern "C" int func_003A4848(void* self)
{
    return *(int*)((char*)self + 0x0);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4850);
#ifdef SKIP_ASM
extern "C" int func_003A4850(void* self)
{
    return *(int*)((char*)self + 0x4);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4858);
#ifdef SKIP_ASM
extern "C" void func_003A4858(void* self, int value)
{
    *(int*)((char*)self + 0x0) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4860);
#ifdef SKIP_ASM
extern "C" void func_003A4860(void* self, int value)
{
    *(int*)((char*)self + 0x4) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4868);
#ifdef SKIP_ASM
extern "C" void func_003A4868(void* self)
{
    cListNode_removeFromList(self);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4888);
#ifdef SKIP_ASM
extern "C" void* func_00397948(void*);
extern void* D_00494C98[];
extern void* D_00494CC0[];

extern "C" void func_003A4888(void* self, int flags)
{
    *(void***)((char*)self + 0x18) = D_00494C98;
    func_00397948(self);
    *(void***)((char*)self + 0x14) = D_00494CC0;
    func_003A4868((char*)self + 0xC);
    *(void***)((char*)self + 0x8) = D_00494CC0;
    func_003A4868(self);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4900);
#ifdef SKIP_ASM
extern void* D_00494BD8[];
extern "C" void* func_003A6548(void* p);

extern "C" void* func_003A4900(void* self)
{
    *(void**)((char*)self + 0x4) = self;
    *(void**)((char*)self + 0x0) = self;
    *(void***)((char*)self + 0x8) = D_00494BD8;
    func_003A6548((char*)self + 0x14);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4940);
#ifdef SKIP_ASM
extern "C" int func_003A4940(void* self)
{
    return *(int*)((char*)self + 0xC) != 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4950);
#ifdef SKIP_ASM
extern "C" int func_003A4950(void* self)
{
    return *(int*)((char*)self + 0xC);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4958);
#ifdef SKIP_ASM
extern "C" int func_003A4958(void* self)
{
    return (*(int*)((char*)self + 0x14) ^ 1) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4968);
#ifdef SKIP_ASM
extern "C" int func_003A4968(void* self)
{
    return *(int*)((char*)self + 0x14) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4978);
#ifdef SKIP_ASM
extern "C" int func_003A4978(void* self)
{
    return (*(int*)((char*)self + 0x14) >> 1) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4988);
#ifdef SKIP_ASM
extern "C" int func_003A4988(void* self)
{
    return (*(int*)((char*)self + 0x14) >> 2) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4998);
#ifdef SKIP_ASM
extern "C" int func_003A4998(void* self)
{
    return (*(int*)((char*)self + 0x14) >> 3) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A49A8);
#ifdef SKIP_ASM
extern "C" int func_003A49A8(void* self)
{
    return (*(int*)((char*)self + 0x14) >> 4) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A49B8);
#ifdef SKIP_ASM
extern "C" int func_003A49B8(void* self)
{
    return (*(int*)((char*)self + 0x14) >> 5) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A49C8);
#ifdef SKIP_ASM
extern "C" int func_003A49C8(void* self)
{
    return (*(int*)((char*)self + 0x14) >> 6) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A49D8);
#ifdef SKIP_ASM
extern "C" int func_003A49D8(void* self)
{
    return (*(int*)((char*)self + 0x14) & 0x80) != 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A49E8);
#ifdef SKIP_ASM
extern "C" void func_003A49E8(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit1 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4A08);
#ifdef SKIP_ASM
extern "C" void func_003A4A08(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit2 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4A28);
#ifdef SKIP_ASM
extern "C" void func_003A4A28(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit3 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4A48);
#ifdef SKIP_ASM
extern "C" void func_003A4A48(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit4 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4A68);
#ifdef SKIP_ASM
extern "C" void func_003A4A68(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit5 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4A88);
#ifdef SKIP_ASM
extern "C" void func_003A4A88(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit6 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4AA8);
#ifdef SKIP_ASM
extern "C" void func_003A4AA8(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit7 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4AC8);
#ifdef SKIP_ASM
extern "C" int func_003A4AC8(void* self)
{
    return *(int*)((char*)self + 0x18);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4AD0);
#ifdef SKIP_ASM
extern "C" void func_003A4AD0(void* self, int value)
{
    *(int*)((char*)self + 0x18) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4AD8);
#ifdef SKIP_ASM
extern "C" void func_003A4AD8(void* self, int value)
{
    ((sUIVectorFields*)((char*)self + 0x14))->bit0 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4AF8);
#ifdef SKIP_ASM
// 16 bytes, 4-byte aligned (copied with ldl/ldr pairs). Float fields are a guess.
struct sVec4 {
    float x;
    float y;
    float z;
    float w;
};

extern "C" void func_003A4AF8(void* self, sVec4* in)
{
    *(sVec4*)((char*)self + 0x1C) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4B20);
#ifdef SKIP_ASM
extern "C" void* func_003A4B20(void* self)
{
    return (char*)self + 0x1C;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4B28);
#ifdef SKIP_ASM
extern "C" void func_003A4B28(void* self, sVec4* out)
{
    *out = *(sVec4*)((char*)self + 0x1C);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4B50);
#ifdef SKIP_ASM
extern "C" void func_003A4B50(void* self, float value)
{
    *(float*)((char*)self + 0x34) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4B58);
#ifdef SKIP_ASM
extern "C" float func_003A4B58(void* self)
{
    return *(float*)((char*)self + 0x34);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4B60);
#ifdef SKIP_ASM
extern "C" int func_003A4B60(void* self)
{
    return ((sUIVectorFields*)((char*)self + 0x14))->layer;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4B70);
#ifdef SKIP_ASM
extern "C" void func_003A4B70(void* self, int value)
{
    ((sUIVectorFields*)((char*)self + 0x14))->layer = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4B90);
#ifdef SKIP_ASM
extern "C" void func_003A4B90(void* self, int value)
{
    ((sUIVectorFields*)((char*)self + 0x14))->f13 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4BB8);
#ifdef SKIP_ASM
extern "C" int func_003A4BB8(void* self)
{
    return ((sUIVectorFields*)((char*)self + 0x14))->f13;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4BC8);
#ifdef SKIP_ASM
extern "C" void func_003A4BC8(void* self, int value)
{
    *(int*)((char*)self + 0x38) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4BD0);
#ifdef SKIP_ASM
extern "C" int func_003A4BD0(void* self)
{
    return *(int*)((char*)self + 0x38);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4BD8__FPv);
#ifdef SKIP_ASM
int func_003A4BD8(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4BE0__FPv);
#ifdef SKIP_ASM
void func_003A4BE0(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4BE8__FPv);
#ifdef SKIP_ASM
void func_003A4BE8(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4BF0__FPv);
#ifdef SKIP_ASM
void func_003A4BF0(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4BF8);
#ifdef SKIP_ASM
extern "C" void func_003A4BF8(void* self, int value)
{
    *(int*)((char*)self + 0x40) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4C00);
#ifdef SKIP_ASM
extern "C" int func_003A4C00(void* self)
{
    return *(int*)((char*)self + 0x40);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4C08);
#ifdef SKIP_ASM
extern "C" void func_003A4C08(void* self, sVec3* out)
{
    *out = *(sVec3*)((char*)self + 0x44);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4C28);
#ifdef SKIP_ASM
extern "C" void func_003A4C28(void* self, sVec3* in)
{
    *(sVec3*)((char*)self + 0x44) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4C48);
#ifdef SKIP_ASM
extern "C" void func_003A4C48(void* self, sVec3* out)
{
    *out = *(sVec3*)((char*)self + 0x50);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4C68);
#ifdef SKIP_ASM
extern "C" void func_003A4C68(void* self, sVec3* in)
{
    *(sVec3*)((char*)self + 0x50) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4C88);
#ifdef SKIP_ASM
extern "C" int func_003A4C88(void* self)
{
    return *(int*)((char*)self + 0x5C);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4C90);
#ifdef SKIP_ASM
extern "C" void func_003A4C90(void* self, sVec3* out)
{
    *out = *(sVec3*)((char*)self + 0x60);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4CB0);
#ifdef SKIP_ASM
extern "C" void func_003A4CB0(void* self, sVec3* in)
{
    *(sVec3*)((char*)self + 0x60) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4CD0);
#ifdef SKIP_ASM
void operator_delete(int* ptr);

extern void* D_00494CE8[];

extern "C" void func_003A4CD0(int* self, int flags)
{
    *(void***)self = D_00494CE8;
    if (flags & 1) {
        operator_delete(self);
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4D00);
#ifdef SKIP_ASM
struct sVEntry3A4D00 {
    short delta;
    short index;
    int (*fn)(void*, void*);
};

extern "C" void* func_003A4D00(void* self, void* obj)
{
    sVEntry3A4D00* vt = *(sVEntry3A4D00**)((char*)obj + 8);
    if (vt[0xF].fn((char*)obj + vt[0xF].delta, *(void**)((char*)self + 4)) == 0) {
        return 0;
    }
    return obj;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4D40);
#ifdef SKIP_ASM
void operator_delete(int* ptr);

extern void* D_00494CE8[];

extern "C" void func_003A4D40(int* self, int flags)
{
    *(void***)self = D_00494CE8;
    if (flags & 1) {
        operator_delete(self);
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4D70);
#ifdef SKIP_ASM
class func_003A4D70_cVirt {
public:
    char pad[0x8];
    // vptr at 0x8; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07(int);
};

extern "C" int func_003A4D70(void* self, func_003A4D70_cVirt* obj)
{
    obj->v07(*(int*)((char*)self + 0x4));
    return 0;
}
#endif

extern void* D_00494AA8[];
extern "C" void* func_0039FC48(void*);

//100%
INCLUDE_ASM("ui/uivector", func_003A4DA8);
#ifdef SKIP_ASM
extern void* D_0046DD60[];

extern "C" void func_003A4DA8(int* self, int flags)
{
    *(void***)self = D_0046DD60;
    if (flags & 1) {
        operator_delete(self);
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4DD8);
#ifdef SKIP_ASM
extern "C" void func_003A4DD8()
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4DE0);
#ifdef SKIP_ASM
extern "C" void func_003A4DE0()
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4DE8);
#ifdef SKIP_ASM
extern "C" void func_003A4DE8()
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4DF0);
#ifdef SKIP_ASM
// Base UI element constructor.
extern "C" void* func_0039FB30(void* self, int a, int b);
extern "C" void* func_0021CCC8(void* p);

extern "C" void* func_003A4DF0(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_00494AA8;
    func_0021CCC8((char*)self + 0x74);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4E38);
#ifdef SKIP_ASM
extern "C" void* func_003A4E38(void* self, int a, int b)
{
    func_0039FB30(self, a, b);
    *(void***)((char*)self + 0x8) = D_00494AA8;
    func_0021CCC8((char*)self + 0x74);
    *(int*)((char*)self + 0x78) = -1;
    *(int*)((char*)self + 0x7C) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4E80__FPv);
#ifdef SKIP_ASM
void* func_003A4E80(void* self)
{
    *(int*)((char*)self + 0x8) = (int)(void*)D_00494AA8;
    return func_0039FC48(self);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4EA8__FPv);
#ifdef SKIP_ASM
int func_003A4EA8(void* self)
{
    return 0x11;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4EB0);
#ifdef SKIP_ASM
extern "C" void* func_003A4EB0(void* self)
{
    *(unsigned char*)self &= 0xF0;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4EC8);
#ifdef SKIP_ASM
extern "C" int func_003A4EC8(void* self)
{
    return *(int*)((char*)self + 0x74) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4ED8);
#ifdef SKIP_ASM
extern "C" void func_003A4ED8(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit0 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4EF8);
#ifdef SKIP_ASM
extern "C" int func_003A4EF8(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 1) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4F08);
#ifdef SKIP_ASM
extern "C" void func_003A4F08(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit1 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4F28);
#ifdef SKIP_ASM
extern "C" int func_003A4F28(void* self)
{
    return (*(int*)((char*)self + 0x74) & 0xC) != 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4F38);
#ifdef SKIP_ASM
extern "C" void func_003A4F38(void* self, int enable)
{
    ((sUIVector74*)((char*)self + 0x74))->bits2 = enable != 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4F58);
#ifdef SKIP_ASM
extern "C" int func_003A4F58(void* self)
{
    return *(int*)((char*)self + 0x7C);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4F60);
#ifdef SKIP_ASM
extern "C" void func_003A4F60(void* self, int value)
{
    *(int*)((char*)self + 0x7C) = value;
    *(int*)((char*)self + 0x78) = -1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4F70);
#ifdef SKIP_ASM
extern "C" int func_003A4F70(void* self)
{
    return *(int*)((char*)self + 0x78);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4F78);
#ifdef SKIP_ASM
extern "C" void func_003A4F78(void* self, int value)
{
    *(int*)((char*)self + 0x78) = value;
    *(int*)((char*)self + 0x7C) = 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4F88);
#ifdef SKIP_ASM
struct sVec2 {
    float x;
    float y;
};

extern "C" sVec2* func_003A4F88(sVec2* out, void* self)
{
    *out = *(sVec2*)((char*)self + 0x80);
    return out;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4FA0);
#ifdef SKIP_ASM
extern "C" void func_003A4FA0(void* self, sVec2* in)
{
    *(sVec2*)((char*)self + 0x80) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4FB8);
#ifdef SKIP_ASM
extern "C" void func_003A4FB8(void* self, float x, float y)
{
    sVec2 v;
    v.x = x;
    v.y = y;
    *(sVec2*)((char*)self + 0x80) = v;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A4FE0);
#ifdef SKIP_ASM
extern void* D_004949E8[];
extern "C" void* func_003977E8(void* p);

extern "C" void* func_003A4FE0(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_004949E8;
    func_003977E8((char*)self + 0x74);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5028);
#ifdef SKIP_ASM
extern "C" void* func_003A5028(void* self, int a, int b)
{
    func_0039FB30(self, a, b);
    *(void***)((char*)self + 0x8) = D_004949E8;
    func_003977E8((char*)self + 0x74);
    return self;
}
#endif

INCLUDE_ASM("ui/uivector", func_003A5068);

//100%
INCLUDE_ASM("ui/uivector", func_003A50F8__FPv);
#ifdef SKIP_ASM
int func_003A50F8(void* self)
{
    return 0x10;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5100);
#ifdef SKIP_ASM
struct cList;
struct cListNode;
cListNode* cList_first(cList* list);
void cList_addToFront(cList* list, cListNode* newNode);
void cList_addToEnd(cList* list, cListNode* newNode);

// The child list lives at + 0x74.
extern "C" cListNode* func_003A5100(void* self)
{
    return cList_first((cList*)((char*)self + 0x74));
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5120);
#ifdef SKIP_ASM
extern "C" void func_00397858(void* p);

extern "C" void func_003A5120(void* self)
{
    func_00397858((char*)self + 0x74);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5140);
#ifdef SKIP_ASM
extern "C" void func_00397870(void* p);

extern "C" void func_003A5140(void* self)
{
    func_00397870((char*)self + 0x74);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5160);
#ifdef SKIP_ASM
extern "C" void func_003A5160(void* self, cListNode* node)
{
    cList_addToFront((cList*)((char*)self + 0x74), node);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5180);
#ifdef SKIP_ASM
extern "C" void func_003A5180(void* self, cListNode* node)
{
    cList_addToEnd((cList*)((char*)self + 0x74), node);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A51A0);
#ifdef SKIP_ASM
class func_003A51A0_cVirt {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void v01();
    virtual int v02(void*);
};

extern "C" int func_003A51A0(void* a, func_003A51A0_cVirt* obj)
{
    return obj->v02(a);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A51D0);
#ifdef SKIP_ASM
class func_003A51D0_cFunctor {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void v01();
    virtual int v02(void*);
};

extern "C" void* func_00397A68(void* list, func_003A51D0_cFunctor* fn);

extern "C" void* func_003A51D0(void* self, func_003A51D0_cFunctor* fn)
{
    if (fn->v02(self) != 0) {
        return self;
    }
    return func_00397A68((char*)self + 0x74, fn);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5230);
#ifdef SKIP_ASM
extern void* D_00494928[];
extern "C" void* func_003A5338(void* self);

extern "C" void* func_003A5230(void* self, int a, int b)
{
    func_0039FB30(self, a, b);
    *(void***)((char*)self + 0x8) = D_004949E8;
    func_003977E8((char*)self + 0x74);
    *(void***)((char*)self + 0x8) = D_00494928;
    func_003A5338((char*)self + 0x90);
    *(unsigned char*)((char*)self + 0xA4) = 0xFF;
    *(char*)((char*)self + 0x95) = 0;
    *(char*)((char*)self + 0x96) = 0;
    *(char*)((char*)self + 0x97) = 0;
    *(char*)((char*)self + 0x98) = 0;
    *(int*)((char*)self + 0x9C) = 0;
    *(int*)((char*)self + 0xA0) = 0;
    return self;
}
#endif

INCLUDE_ASM("ui/uivector", func_003A52A0);

//100%
INCLUDE_ASM("ui/uivector", func_003A5330__FPv);
#ifdef SKIP_ASM
int func_003A5330(void* self)
{
    return 0x13;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5338);
#ifdef SKIP_ASM
extern "C" void* func_003A5338(void* self)
{
    *(unsigned char*)self &= 0xf0;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5350);
#ifdef SKIP_ASM
extern "C" int func_003A5350(void* self)
{
    return (*(int*)((char*)self + 0x90) >> 1) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5360);
#ifdef SKIP_ASM
extern "C" void func_003A5360(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x90))->bit1 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5380);
#ifdef SKIP_ASM
extern "C" int func_003A5380(void* self)
{
    return (*(int*)((char*)self + 0x90) >> 3) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5390);
#ifdef SKIP_ASM
extern "C" void func_003A5390(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x90))->bit3 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A53B0);
#ifdef SKIP_ASM
extern "C" int func_003A53B0(void* self)
{
    return *(int*)((char*)self + 0x90) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A53C0);
#ifdef SKIP_ASM
extern "C" void func_003A53C0(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x90))->bit0 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A53E0);
#ifdef SKIP_ASM
extern "C" unsigned char func_003A53E0(void* self)
{
    return *(unsigned char*)((char*)self + 0x95);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A53E8);
#ifdef SKIP_ASM
extern "C" unsigned char func_003A53E8(void* self)
{
    return *(unsigned char*)((char*)self + 0x98);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A53F0);
#ifdef SKIP_ASM
extern "C" unsigned char func_003A53F0(void* self)
{
    return *(unsigned char*)((char*)self + 0x96);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A53F8);
#ifdef SKIP_ASM
extern "C" void func_003A53F8(void* self, char value)
{
    *(char*)((char*)self + 0x95) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5400);
#ifdef SKIP_ASM
extern "C" void func_003A5400(void* self, char value)
{
    *(char*)((char*)self + 0x96) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5408);
#ifdef SKIP_ASM
extern "C" void func_003A5408(void* self, char value)
{
    *(char*)((char*)self + 0x98) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5410);
#ifdef SKIP_ASM
extern "C" int func_003A5410(void* self)
{
    return *(int*)((char*)self + 0xA0);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5418);
#ifdef SKIP_ASM
extern "C" unsigned char func_003A5418(void* self)
{
    return *(unsigned char*)((char*)self + 0x95);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5420);
#ifdef SKIP_ASM
extern void* D_00494868[];
extern "C" void* func_003A5508(void* self);

extern "C" void* func_003A5420(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_00494868;
    func_003A5508((char*)self + 0x74);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5468);
#ifdef SKIP_ASM
extern "C" void* func_003A5468(void* self, int a, int b)
{
    func_0039FB30(self, a, b);
    *(void***)((char*)self + 0x8) = D_00494868;
    func_003A5508((char*)self + 0x74);
    *(int*)((char*)self + 0x78) = 0;
    *(int*)((char*)self + 0x7C) = 0;
    ((sUIVectorFields*)((char*)self + 0x14))->bit1 = 1;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A54B8);
#ifdef SKIP_ASM
extern void* D_00494868[];
extern "C" void func_0039BE70(void* self);
// PORT: the unit declares func_0039FC48 with one parameter; the real body is a
// destructor taking (self, flags). Bound to the same symbol with an asm label.
extern "C" void* func_0039FC48_dtor(void* self, int flags) __asm__("func_0039FC48");

extern "C" void func_003A54B8(void* self, int flags)
{
    *(void***)((char*)self + 8) = D_00494868;
    func_0039BE70(self);
    func_0039FC48_dtor(self, flags);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5500__FPv);
#ifdef SKIP_ASM
int func_003A5500(void* self)
{
    return 0x15;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5508);
#ifdef SKIP_ASM
extern "C" void* func_003A5508(void* self)
{
    *(unsigned char*)((char*)self + 0x1) &= 0xc0;
    *(unsigned char*)((char*)self + 0x0) &= 0xc0;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5528);
#ifdef SKIP_ASM
extern "C" int func_003A5528(void* self)
{
    return *(int*)((char*)self + 0x78);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5530);
#ifdef SKIP_ASM
// Replaces the owned object at + 0x78, deleting the old one (virtual destructor, flags 3).
extern "C" void func_003A5530(void* self, void* obj)
{
    void* old = *(void**)((char*)self + 0x78);
    if (old != 0) {
        sVE_3A39F8* vt = *(sVE_3A39F8**)((char*)old + 0x8);
        ((void (*)(void*, int))vt[1].fn)((char*)old + vt[1].delta, 3);
    }
    *(void**)((char*)self + 0x78) = obj;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5580);
#ifdef SKIP_ASM
extern "C" int func_003A5580(void* self)
{
    return *(int*)((char*)self + 0x7C);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5588);
#ifdef SKIP_ASM
extern "C" void func_003A5588(void* self, void* obj)
{
    void* old = *(void**)((char*)self + 0x7C);
    if (old != 0) {
        sVE_3A39F8* vt = *(sVE_3A39F8**)((char*)old + 0x8);
        ((void (*)(void*, int))vt[1].fn)((char*)old + vt[1].delta, 3);
    }
    *(void**)((char*)self + 0x7C) = obj;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A55D8);
#ifdef SKIP_ASM
extern void* D_00494798[];
extern "C" void* func_003A65A0(void* self);
extern "C" void* func_003A65B8(void* self);

extern "C" void* func_003A55D8(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_00494798;
    func_003A65A0((char*)self + 0x74);
    char* p = (char*)self + 0x98;
    int i = 31;
    do {
        func_003A65B8(p);
        i--;
        p += 0x14;
    } while (i != -1);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5658);
#ifdef SKIP_ASM
extern void* D_00494798[];
extern "C" void func_0039A670(void* self);
// PORT: the unit declares func_0039FC48 with one parameter; the real body is a
// destructor taking (self, flags). Bound to the same symbol with an asm label.
extern "C" void* func_0039FC48_dtor(void* self, int flags) __asm__("func_0039FC48");

extern "C" void func_003A5658(void* self, int flags)
{
    *(void***)((char*)self + 8) = D_00494798;
    func_0039A670(self);
    func_0039FC48_dtor(self, flags);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A56A0__FPv);
#ifdef SKIP_ASM
int func_003A56A0(void* self)
{
    return 0x12;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A56A8);
#ifdef SKIP_ASM
extern "C" void func_003A56A8(void* self, int value)
{
    ((sUIBits2At0*)((char*)self + 0x74))->f0 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A56C8);
#ifdef SKIP_ASM
extern "C" int func_003A56C8(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 2) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A56D8);
#ifdef SKIP_ASM
extern "C" void func_003A56D8(void* self, int enable) {
    ((sUIVectorFlags*)((char*)self + 0x74))->bit2 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A56F8);
#ifdef SKIP_ASM
extern "C" int func_003A56F8(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 5) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5708);
#ifdef SKIP_ASM
extern "C" void func_003A5708(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit5 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5728);
#ifdef SKIP_ASM
extern "C" int func_003A5728(void* self)
{
    return (*(int*)((char*)self + 0x14) & 0x80) != 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5738);
#ifdef SKIP_ASM
extern "C" void func_003A5738(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit7 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5758);
#ifdef SKIP_ASM
extern "C" void func_003A5758(void* self, sVec4* in)
{
    *(sVec4*)((char*)self + 0x78) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5780);
#ifdef SKIP_ASM
extern "C" void func_003A5780(void* self, sVec4* in)
{
    *(sVec4*)((char*)self + 0x88) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A57A8);
#ifdef SKIP_ASM
extern "C" unsigned char func_003A57A8(void* self)
{
    return *(unsigned char*)((char*)self + 0x319);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A57B0);
#ifdef SKIP_ASM
extern "C" unsigned char func_003A57B0(void* self)
{
    return *(unsigned char*)((char*)self + 0x318);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A57B8);
#ifdef SKIP_ASM
extern void* D_004946C8[];
extern "C" void* func_003A65D8(void* self);

extern "C" void* func_003A57B8(void* self)
{
    *(void**)((char*)self + 0x4) = self;
    *(void**)((char*)self + 0x0) = self;
    *(void***)((char*)self + 0x8) = D_004946C8;
    func_003A65D8((char*)self + 0x1C);
    func_003977E8((char*)self + 0x24);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5800);
#ifdef SKIP_ASM
extern "C" void func_003A5800(void* self, int value)
{
    *(int*)((char*)self + 0xC) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5808);
#ifdef SKIP_ASM
extern "C" int func_003A5808(void* self)
{
    return *(int*)((char*)self + 0xC);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5810);
#ifdef SKIP_ASM
extern "C" int func_003A5810(void* self)
{
    return *(int*)((char*)self + 0x10);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5818);
#ifdef SKIP_ASM
extern "C" void func_003A5818(void* self, char value)
{
    *(char*)((char*)self + 0x14) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5820);
#ifdef SKIP_ASM
extern "C" signed char func_003A5820(void* self)
{
    return *(signed char*)((char*)self + 0x14);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5828);
#ifdef SKIP_ASM
extern "C" void func_003A5828(void* self, char value)
{
    *(char*)((char*)self + 0x15) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5830);
#ifdef SKIP_ASM
extern "C" unsigned char func_003A5830(void* self)
{
    return *(unsigned char*)((char*)self + 0x15);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5838);
#ifdef SKIP_ASM
extern "C" int func_003A5838(void* self)
{
    return *(int*)((char*)self + 0x18);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5840);
#ifdef SKIP_ASM
extern "C" void func_003A5840(void* self, int value)
{
    *(int*)((char*)self + 0x18) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5848);
#ifdef SKIP_ASM
extern "C" int func_003A5848(void* self)
{
    return *(unsigned char*)((char*)self + 0x1D) & 0x3F;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5858);
#ifdef SKIP_ASM
extern "C" void func_003A5858(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->f8 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5878);
#ifdef SKIP_ASM
extern "C" int func_003A5878(void* self)
{
    return (*(int*)((char*)self + 0x1C) >> 4) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5888);
#ifdef SKIP_ASM
extern "C" void func_003A5888(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->bit4 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A58A8);
#ifdef SKIP_ASM
extern "C" int func_003A58A8(void* self)
{
    return (*(int*)((char*)self + 0x1C) >> 5) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A58B8);
#ifdef SKIP_ASM
extern "C" void func_003A58B8(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->bit5 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A58D8);
#ifdef SKIP_ASM
extern "C" int func_003A58D8(void* self)
{
    return (*(int*)((char*)self + 0x1C) >> 14) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A58E8);
#ifdef SKIP_ASM
extern "C" void func_003A58E8(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->bit14 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5908);
#ifdef SKIP_ASM
extern "C" int func_003A5908(void* self)
{
    return (*(int*)((char*)self + 0x1C) >> 15) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5918);
#ifdef SKIP_ASM
extern "C" void func_003A5918(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->bit15 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5940);
#ifdef SKIP_ASM
extern "C" int func_003A5940(void* self)
{
    return (*(int*)((char*)self + 0x1C) >> 6) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5950);
#ifdef SKIP_ASM
extern "C" void func_003A5950(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->bit6 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5970);
#ifdef SKIP_ASM
extern "C" int func_003A5970(void* self)
{
    return (*(int*)((char*)self + 0x1C) & 0x80) != 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5980);
#ifdef SKIP_ASM
extern "C" void func_003A5980(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->bit7 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A59A0);
#ifdef SKIP_ASM
extern "C" int func_003A59A0(void* self)
{
    return (*(int*)((char*)self + 0x1C) & 0x6) != 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A59B0);
#ifdef SKIP_ASM
extern "C" int func_003A59B0(void* self)
{
    return (*(unsigned int*)((char*)self + 0x1C) >> 1) & 0x3;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A59C0);
#ifdef SKIP_ASM
extern "C" void func_003A59C0(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->f1 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A59E0);
#ifdef SKIP_ASM
extern "C" void func_003A59E0(void* self)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->f1++;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5A10);
#ifdef SKIP_ASM
extern "C" void func_003A5A10(void* self)
{
    if (((sUIFlags1C*)((char*)self + 0x1C))->f1 != 0) {
        ((sUIFlags1C*)((char*)self + 0x1C))->f1--;
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5A48);
#ifdef SKIP_ASM
extern "C" int func_003A5A48(void* self)
{
    return *(int*)((char*)self + 0x1C) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5A58);
#ifdef SKIP_ASM
extern "C" void func_003A5A58(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->bit0 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5A78);
#ifdef SKIP_ASM
extern "C" int func_003A5A78(void* self)
{
    return (*(int*)((char*)self + 0x1C) >> 3) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5A88);
#ifdef SKIP_ASM
extern "C" void func_003A5A88(void* self, int value)
{
    ((sUIFlags1C*)((char*)self + 0x1C))->bit3 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AA8__FPv);
#ifdef SKIP_ASM
void func_003A5AA8(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AB0__FPv);
#ifdef SKIP_ASM
int func_003A5AB0(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AB8__FPv);
#ifdef SKIP_ASM
int func_003A5AB8(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AC0__FPv);
#ifdef SKIP_ASM
int func_003A5AC0(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AC8__FPv);
#ifdef SKIP_ASM
void func_003A5AC8(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AD0__FPv);
#ifdef SKIP_ASM
void func_003A5AD0(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AD8__FPv);
#ifdef SKIP_ASM
int func_003A5AD8(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AE0);
#ifdef SKIP_ASM
extern "C" void func_003A5AE0(void* self, int value)
{
    *(int*)((char*)self + 0x20) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AE8);
#ifdef SKIP_ASM
extern "C" int func_003A5AE8(void* self)
{
    return *(int*)((char*)self + 0x20);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AF0);
#ifdef SKIP_ASM
extern "C" int func_003A5AF0(void* self)
{
    return *(int*)((char*)self + 0x40);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5AF8);
#ifdef SKIP_ASM
extern "C" void func_003A5AF8(void* self, char value)
{
    *(char*)((char*)self + 0x44) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B00);
#ifdef SKIP_ASM
extern "C" signed char func_003A5B00(void* self)
{
    return *(signed char*)((char*)self + 0x44);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B08__FPv);
#ifdef SKIP_ASM
void func_003A5B08(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B10__FPv);
#ifdef SKIP_ASM
void func_003A5B10(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B18__FPv);
#ifdef SKIP_ASM
void func_003A5B18(void* self)
{
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B20__FPv);
#ifdef SKIP_ASM
int func_003A5B20(void* self)
{
    return 0x101;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B28__FPv);
#ifdef SKIP_ASM
int func_003A5B28(void* self)
{
    return 0x101;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B30__FPv);
#ifdef SKIP_ASM
int func_003A5B30(void* self)
{
    return 0x101;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B38__FPv);
#ifdef SKIP_ASM
int func_003A5B38(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B40__FPv);
#ifdef SKIP_ASM
int func_003A5B40(void* self)
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B48);
#ifdef SKIP_ASM
void operator_delete(int* ptr);
extern "C" void func_003A4868(void* self);

extern void* D_00494CC0[];

extern "C" void func_003A5B48(int* self, int flags)
{
    *(void***)((char*)self + 0x8) = D_00494CC0;
    func_003A4868(self);
    if (flags & 1) {
        operator_delete(self);
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5B98);
#ifdef SKIP_ASM
extern void* D_00494670[];
extern "C" void* func_001DD580(void* p);

extern "C" void* func_003A5B98(void* self)
{
    *(void**)((char*)self + 0x4) = self;
    *(void**)((char*)self + 0x0) = self;
    *(void***)((char*)self + 0x8) = D_00494670;
    func_001DD580((char*)self + 0x14);
    func_003977E8((char*)self + 0x18);
    func_0039FB30((char*)self + 0x40, 0, 0);
    *(void***)((char*)self + 0x48) = D_004949E8;
    func_003977E8((char*)self + 0xB4);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5C08);
#ifdef SKIP_ASM
extern "C" void* func_003A5C08(void* self, int arg)
{
    *(void**)((char*)self + 0x4) = self;
    *(void**)((char*)self + 0x0) = self;
    *(int*)((char*)self + 0xC) = 0;
    *(int*)((char*)self + 0x10) = 0;
    *(void***)((char*)self + 0x8) = D_00494670;
    func_001DD580((char*)self + 0x14);
    func_003977E8((char*)self + 0x18);
    *(int*)((char*)self + 0x34) = 0;
    *(int*)((char*)self + 0x38) = 0;
    *(int*)((char*)self + 0x3C) = 0;
    func_0039FB30((char*)self + 0x40, 0, 0);
    *(void***)((char*)self + 0x48) = D_004949E8;
    func_003977E8((char*)self + 0xB4);
    *(int*)((char*)self + 0xD0) = arg;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5C98);
#ifdef SKIP_ASM
extern "C" int func_003A5C98(void* self)
{
    return **(int**)((char*)self + 0x10);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5CA8);
#ifdef SKIP_ASM
extern "C" void* func_003A5CA8(void* self)
{
    *(unsigned short*)self = (*(unsigned short*)self | 0x1) & 0xFFFD;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5CC0);
#ifdef SKIP_ASM
extern "C" int func_003A5CC0(void* self)
{
    return *(int*)((char*)self + 0x14) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5CD0);
#ifdef SKIP_ASM
extern "C" void func_003A5CD0(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x14))->bit0 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5CF0);
#ifdef SKIP_ASM
extern "C" void func_003A5CF0(void* self, cListNode* node)
{
    cList_addToEnd((cList*)((char*)self + 0xB4), node);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5D10);
#ifdef SKIP_ASM
extern "C" void* func_003A5D10(void* self)
{
    return (char*)self + 0x40;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5D18);
#ifdef SKIP_ASM
extern "C" void func_003A5D18(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x54))->bit6 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5D38);
#ifdef SKIP_ASM
extern "C" int func_003A5D38(void* self)
{
    return (*(int*)((char*)self + 0x54) >> 6) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5D48);
#ifdef SKIP_ASM
extern "C" int func_003A5D48(void* self)
{
    return *(int*)(*(char**)((char*)self + 0xD0) + 0x10);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5D58);
#ifdef SKIP_ASM
extern "C" int func_003A5D58(void* self)
{
    return *(int*)((char*)self + 0xD0);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5D60);
#ifdef SKIP_ASM
extern void* D_00494588[];
extern "C" void* func_003A65E8(void* self);

extern "C" void* func_003A5D60(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_00494588;
    func_003A65E8((char*)self + 0x74);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5DA8);
#ifdef SKIP_ASM
extern void* D_00494588[];
extern "C" void cUIText_deleteText(void* self);
// PORT: the unit declares func_0039FC48 with one parameter; the real body is a
// destructor taking (self, flags). Bound to the same symbol with an asm label.
extern "C" void* func_0039FC48_dtor(void* self, int flags) __asm__("func_0039FC48");

extern "C" void func_003A5DA8(void* self, int flags)
{
    *(void***)((char*)self + 8) = D_00494588;
    cUIText_deleteText(self);
    func_0039FC48_dtor(self, flags);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5DF0__FPv);
#ifdef SKIP_ASM
int func_003A5DF0(void* self)
{
    return 0x17;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5DF8);
#ifdef SKIP_ASM
extern "C" void func_003A5DF8(void* self, int value)
{
    ((sUIBits2At0*)((char*)self + 0x74))->f0 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5E18);
#ifdef SKIP_ASM
extern "C" int func_003A5E18(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 2) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5E28);
#ifdef SKIP_ASM
extern "C" int func_003A5E28(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 3) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5E38);
#ifdef SKIP_ASM
extern "C" int func_003A5E38(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 4) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5E48);
#ifdef SKIP_ASM
extern "C" int func_003A5E48(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 5) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5E58);
#ifdef SKIP_ASM
extern "C" int func_003A5E58(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 6) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5E68);
#ifdef SKIP_ASM
extern "C" void func_003A5E68(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit2 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5E88);
#ifdef SKIP_ASM
extern "C" void func_003A5E88(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit3 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5EA8);
#ifdef SKIP_ASM
extern "C" void func_003A5EA8(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit4 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5EC8);
#ifdef SKIP_ASM
extern "C" void func_003A5EC8(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit5 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5EE8);
#ifdef SKIP_ASM
extern "C" void func_003A5EE8(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit6 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5F08);
#ifdef SKIP_ASM
extern "C" void func_003A5F08(void* self, sVec4* in)
{
    *(sVec4*)((char*)self + 0x78) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5F30);
#ifdef SKIP_ASM
extern "C" void func_003A5F30(void* self, sVec4* in)
{
    *(sVec4*)((char*)self + 0x88) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5F58);
#ifdef SKIP_ASM
extern "C" int func_003A5F58(void* self)
{
    return *(int*)((char*)self + 0xB0);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5F60);
#ifdef SKIP_ASM
extern void* D_004944C8[];

extern "C" void* func_003A5F60(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_004944C8;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A5FA0);
#ifdef SKIP_ASM
extern "C" void* func_003A5FA0(void* self, int a, int b)
{
    func_0039FB30(self, a, b);
    *(void***)((char*)self + 0x8) = D_004944C8;
    *(int*)((char*)self + 0x74) = 0;
    *(int*)((char*)self + 0x78) = 0;
    *(int*)((char*)self + 0x7C) = 0;
    *(int*)((char*)self + 0x80) = 0;
    *(int*)((char*)self + 0x84) = 0;
    *(int*)((char*)self + 0x88) = 0;
    *(int*)((char*)self + 0xC0) = 0;
    *(int*)((char*)self + 0xC4) = 0;
    *(int*)((char*)self + 0xC8) = 0;
    *(char*)((char*)self + 0x8C) = 0;
    *(char*)((char*)self + 0xA5) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6000__FPv);
#ifdef SKIP_ASM
int func_003A6000(void* self)
{
    return 0x21;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6008);
#ifdef SKIP_ASM
extern "C" void func_003A6008(void* self, int value)
{
    *(int*)((char*)self + 0x74) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6010);
#ifdef SKIP_ASM
extern "C" void func_003A6010(void* self, int value)
{
    *(int*)((char*)self + 0x78) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6018);
#ifdef SKIP_ASM
extern "C" void func_003A6018(void* self, int value)
{
    *(int*)((char*)self + 0x7C) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6020);
#ifdef SKIP_ASM
extern "C" void func_003A6020(void* self, int value)
{
    *(int*)((char*)self + 0x80) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6028);
#ifdef SKIP_ASM
extern "C" void func_003A6028(void* self, int value)
{
    *(int*)((char*)self + 0x84) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6030);
#ifdef SKIP_ASM
extern "C" void func_003A6030(void* self, int value)
{
    *(int*)((char*)self + 0x88) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6038);
#ifdef SKIP_ASM
extern "C" unsigned int strlen(const char* s);
extern "C" char* strcpy(char* dst, const char* src);

// Copies a name (max 24 chars) into the buffer at + 0x8C; too-long names clear it.
extern "C" void func_003A6038(void* self, const char* name)
{
    if (strlen(name) > 24) {
        *((char*)self + 0x8C) = 0;
    } else {
        strcpy((char*)self + 0x8C, name);
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6088);
#ifdef SKIP_ASM
extern "C" void func_003A6088(void* self, const char* name)
{
    if (strlen(name) > 24) {
        *((char*)self + 0xA5) = 0;
    } else {
        strcpy((char*)self + 0xA5, name);
    }
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A60D8);
#ifdef SKIP_ASM
extern "C" int func_003A60D8(void* self)
{
    return *(int*)((char*)self + 0xC0);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A60E0);
#ifdef SKIP_ASM
extern void* D_00494408[];

extern "C" void* func_003A60E0(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_00494408;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6120);
#ifdef SKIP_ASM
extern "C" void* func_003A6120(void* self, int a, int b)
{
    func_0039FB30(self, a, b);
    *(void***)((char*)self + 0x8) = D_00494408;
    *(int*)((char*)self + 0x74) = 0;
    *(int*)((char*)self + 0x78) = 0;
    *(int*)((char*)self + 0x7C) = 0;
    *(int*)((char*)self + 0x80) = 0;
    *(int*)((char*)self + 0x84) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6168__FPv);
#ifdef SKIP_ASM
int func_003A6168(void* self)
{
    return 0x19;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6170);
#ifdef SKIP_ASM
extern "C" void func_003A6170(void* self, int value)
{
    *(int*)((char*)self + 0x74) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6178);
#ifdef SKIP_ASM
extern "C" void func_003A6178(void* self, int value)
{
    *(int*)((char*)self + 0x78) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6180);
#ifdef SKIP_ASM
extern "C" int func_003A6180(void* self)
{
    return *(int*)((char*)self + 0x7C);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6188);
#ifdef SKIP_ASM
extern "C" void func_003A6188(void* self, int value)
{
    *(int*)((char*)self + 0x80) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6190);
#ifdef SKIP_ASM
extern void* D_00494348[];

extern "C" void* func_003A6190(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_00494348;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A61D0);
#ifdef SKIP_ASM
extern "C" void* func_003A61D0(void* self, int a, int b)
{
    func_0039FB30(self, a, b);
    *(void***)((char*)self + 0x8) = D_00494348;
    *(int*)((char*)self + 0x74) = 0;
    *(int*)((char*)self + 0x78) = 0;
    *(int*)((char*)self + 0x7C) = 0;
    *(int*)((char*)self + 0x80) = 0;
    *(int*)((char*)self + 0x88) = 0;
    *(int*)((char*)self + 0x8C) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6220__FPv);
#ifdef SKIP_ASM
int func_003A6220(void* self)
{
    return 0x16;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6228);
#ifdef SKIP_ASM
extern "C" int func_003A6228(void* self)
{
    return *(int*)((char*)self + 0x74);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6230);
#ifdef SKIP_ASM
extern "C" void func_003A6230(void* self, int value)
{
    *(int*)((char*)self + 0x74) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6238);
#ifdef SKIP_ASM
extern "C" void func_003A6238(void* self, int value)
{
    *(int*)((char*)self + 0x78) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6240);
#ifdef SKIP_ASM
extern "C" void func_003A6240(void* self, int value)
{
    *(int*)((char*)self + 0x88) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6248);
#ifdef SKIP_ASM
extern "C" void func_003A6248(void* self, int value)
{
    *(int*)((char*)self + 0x8C) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6250);
#ifdef SKIP_ASM
extern void* D_00494278[];
extern "C" void* func_003A6600(void* self);

extern "C" void* func_003A6250(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_00494278;
    func_003A6600((char*)self + 0x74);
    func_003977E8((char*)self + 0x8C);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A62A0);
#ifdef SKIP_ASM
extern void* D_00494278[];
extern void* D_00494C98[];
extern void* D_00494CC0[];
extern "C" void func_003A4868(void* self);
extern "C" void func_003A18C0(void* self);
// PORT: the unit declares func_00397948 as returning void*; its body (util/list) is void.
extern "C" void func_00397948_v(void* self) __asm__("func_00397948");
// PORT: the unit declares func_0039FC48 with one parameter; the real body is a
// destructor taking (self, flags). Bound to the same symbol with an asm label.
extern "C" void* func_0039FC48_dtor(void* self, int flags) __asm__("func_0039FC48");

extern "C" void func_003A62A0(void* self, int flags)
{
    *(void***)((char*)self + 0x8) = D_00494278;
    func_003A18C0(self);
    *(void***)((char*)self + 0xA4) = D_00494C98;
    func_00397948_v((char*)self + 0x8C);
    *(void***)((char*)self + 0xA0) = D_00494CC0;
    func_003A4868((char*)self + 0x98);
    *(void***)((char*)self + 0x94) = D_00494CC0;
    func_003A4868((char*)self + 0x8C);
    func_0039FC48_dtor(self, flags);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6330__FPv);
#ifdef SKIP_ASM
int func_003A6330(void* self)
{
    return 0x20;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6338);
#ifdef SKIP_ASM
extern "C" void func_003A6338(void* self, int value)
{
    ((sUIBits2At1*)((char*)self + 0x74))->f1 = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6358);
#ifdef SKIP_ASM
extern "C" int func_003A6358(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 3) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6368);
#ifdef SKIP_ASM
extern "C" int func_003A6368(void* self)
{
    return (*(int*)((char*)self + 0x74) >> 4) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6378);
#ifdef SKIP_ASM
extern "C" void func_003A6378(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit3 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6398);
#ifdef SKIP_ASM
extern "C" void func_003A6398(void* self, int enable)
{
    ((sUIVectorFlags*)((char*)self + 0x74))->bit4 = enable;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A63B8);
#ifdef SKIP_ASM
extern "C" void func_003A63B8(void* self, sVec4* in)
{
    *(sVec4*)((char*)self + 0x78) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A63E0);
#ifdef SKIP_ASM
extern "C" cListNode* func_003A63E0(void* self)
{
    return cList_first((cList*)((char*)self + 0x8C));
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6400);
#ifdef SKIP_ASM
extern "C" void func_003A6400(void* self)
{
    func_00397858((char*)self + 0x8C);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6420);
#ifdef SKIP_ASM
extern "C" void func_003A6420(void* self)
{
    func_00397870((char*)self + 0x8C);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6440);
#ifdef SKIP_ASM
extern "C" void func_003A6440(void* self, cListNode* node)
{
    cList_addToFront((cList*)((char*)self + 0x8C), node);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6460);
#ifdef SKIP_ASM
extern "C" void func_003A6460(void* self, cListNode* node)
{
    cList_addToEnd((cList*)((char*)self + 0x8C), node);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6480);
#ifdef SKIP_ASM
extern "C" void func_003A6480(void* self)
{
    *(int*)((char*)self + 0x74) |= 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6490);
#ifdef SKIP_ASM
extern "C" int func_003A6490(void* self)
{
    return *(int*)((char*)self + 0x74) & 0x1;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A64A0);
#ifdef SKIP_ASM
extern "C" void func_003A64A0(void* self, sVec4* in)
{
    *(sVec4*)((char*)self + 0xA8) = *in;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A64C8);
#ifdef SKIP_ASM
extern "C" void func_003A64C8(void* self, int value)
{
    *(int*)((char*)self + 0xB8) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A64D0);
#ifdef SKIP_ASM
extern "C" void func_003A64D0(void* self, short value)
{
    *(short*)((char*)self + 0xC6) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A64D8);
#ifdef SKIP_ASM
extern "C" unsigned short func_003A64D8(void* self)
{
    return *(unsigned short*)((char*)self + 0xC6);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A64E0);
#ifdef SKIP_ASM
extern "C" unsigned short func_003A64E0(void* self)
{
    return *(unsigned short*)((char*)self + 0xC8);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A64E8);
#ifdef SKIP_ASM
extern "C" void func_003A64E8(void* self, short value)
{
    *(short*)((char*)self + 0xC4) = value;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A64F0);
#ifdef SKIP_ASM
extern "C" unsigned short func_003A64F0(void* self)
{
    return *(unsigned short*)((char*)self + 0xC4);
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A64F8);
#ifdef SKIP_ASM
extern void* D_004941B8[];
extern "C" void* func_003A6618(void* self);

extern "C" void* func_003A64F8(void* self)
{
    func_0039FB30(self, 0, 0);
    *(void***)((char*)self + 0x8) = D_004941B8;
    func_003A6618((char*)self + 0x74);
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6540__FPv);
#ifdef SKIP_ASM
int func_003A6540(void* self)
{
    return 0x18;
}
#endif

extern "C" void* func_003A3F48(int, int);

//100%
INCLUDE_ASM("ui/uivector", func_003A6548);
#ifdef SKIP_ASM
// Default flags of a cUIVector.
extern "C" void* func_003A6548(void* self)
{
    sUIVectorFields* f = (sUIVectorFields*)self;
    f->bit0 = 1;
    f->bit7 = 0;
    f->layer = 0;
    f->bit5 = 0;
    f->bit4 = 0;
    f->bit2 = 0;
    f->bit1 = 1;
    f->bit3 = 1;
    f->bit6 = 1;
    f->f13 = 9;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A65A0);
#ifdef SKIP_ASM
extern "C" void* func_003A65A0(void* self)
{
    *(unsigned char*)self = (*(unsigned char*)self | 0x4) & 0xC4;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A65B8);
#ifdef SKIP_ASM
extern "C" void* func_003A65B8(void* self)
{
    *(int*)((char*)self + 0x0) = 0;
    *(int*)((char*)self + 0x4) = 0;
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0xC) = 0;
    *(char*)((char*)self + 0x10) = 0;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A65D8);
#ifdef SKIP_ASM
extern "C" void* func_003A65D8(void* self)
{
    *(short*)self = 0x218;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A65E8);
#ifdef SKIP_ASM
extern "C" void* func_003A65E8(void* self)
{
    *(unsigned char*)self = (*(unsigned char*)self | 0x4) & 0x87;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6600);
#ifdef SKIP_ASM
extern "C" void* func_003A6600(void* self)
{
    *(unsigned char*)self &= 0xC6;
    return self;
}
#endif

//100%
INCLUDE_ASM("ui/uivector", func_003A6618);
#ifdef SKIP_ASM
extern "C" void* func_003A6618(void* self)
{
    ((sCount_3A39F8*)self)->flag = 0;
    ((sCount_3A39F8*)self)->pad1 = 0;
    ((sCount_3A39F8*)self)->count = 0;
    return self;
}
#endif

//99.38%
INCLUDE_ASM("ui/uivector", func_003A6648__FPv);
#ifdef SKIP_ASM
void* func_003A6648(void* self)
{
    return func_003A3F48(1, 0xffff);
}
#endif

extern "C" void* func_003A3F48(int, int);

//99.38%
INCLUDE_ASM("ui/uivector", func_003A6668__FPv);
#ifdef SKIP_ASM
void* func_003A6668(void* self)
{
    return func_003A3F48(0, 0xffff);
}
#endif

