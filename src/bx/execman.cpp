#include "common.h"

struct cExecutionMan {
    int field_0x0;
    int field_0x4;
    void* field_0x8;
};

extern void* D_0048DC30[16];
void operator_delete(int* ptr);

//100%
void cExecutionMan__cExecutionMan(cExecutionMan* self, int flags)
{
    self->field_0x8 = D_0048DC30;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
void cExecutionMan_prepause()
{
}

//100%
void cExecutionMan_postpause()
{
}

extern "C" int func_00320960(char* self)
{
    return *(int*)(self + 0x4) != 0;
}

extern "C" void func_00320970(void* self, float value)
{
    *(float*)((char*)self + 0x24) = value;
}

extern "C" int func_00320978(void* self)
{
    return *(int*)((char*)self + 0x10);
}

extern "C" float func_00320980(void* self)
{
    return *(float*)((char*)self + 0x14);
}

extern "C" float func_00320988(void* self)
{
    return *(float*)((char*)self + 0x24);
}

extern "C" float func_00320990(void* self)
{
    return *(float*)((char*)self + 0x2C);
}

extern "C" int func_00320998(void* self)
{
    return *(int*)((char*)self + 0x1C);
}

extern "C" int func_003209A0(void* self)
{
    return *(int*)((char*)self + 0x18);
}

extern "C" int func_003209A8(void* self)
{
    return *(int*)((char*)self + 0xC);
}

extern "C" void func_003209B0(void* self, int value)
{
    *(int*)((char*)self + 0xC) = value;
}

extern "C" int func_003209B8(void* self)
{
    return *(int*)((char*)self + 0x0);
}

// Virtual calls on the object at +0x8 (vtable at its +0x8)
extern "C" void func_003209C0(char* self)
{
    char* obj = *(char**)(self + 0x8);
    char* vt = *(char**)(obj + 0x8);
    (*(void (**)(char*))(vt + 0x2C))(obj + *(short*)(vt + 0x28));
}

extern "C" void func_003209F0(char* self)
{
    char* obj = *(char**)(self + 0x8);
    char* vt = *(char**)(obj + 0x8);
    (*(void (**)(char*))(vt + 0x24))(obj + *(short*)(vt + 0x20));
}

extern "C" unsigned int func_00320A20(char* self)
{
    char* obj = *(char**)(self + 0x8);
    if (obj) {
        char* vt = *(char**)(obj + 0x8);
        return (*(unsigned int (**)(char*))(vt + 0x34))(obj + *(short*)(vt + 0x30));
    }
    return 0xFFFFFFFF;
}

extern "C" void func_00320A60(char* self)
{
    char* obj = *(char**)(self + 0x8);
    char* vt = *(char**)(obj + 0x8);
    (*(void (**)(char*))(vt + 0x5C))(obj + *(short*)(vt + 0x58));
}

extern "C" void func_00320A90(char* self)
{
    char* obj = *(char**)(self + 0x8);
    char* vt = *(char**)(obj + 0x8);
    (*(void (**)(char*))(vt + 0x64))(obj + *(short*)(vt + 0x60));
}

extern "C" void* func_00320AC0(void* self)
{
    return (char*)self + 0x38;
}

extern int D_004A5B64;

extern "C" int func_00320AC8()
{
    return D_004A5B64;
}

extern "C" void func_00320AD0(void* self, int value)
{
    *(int*)((char*)self + 0x34) = value;
}

//100%
// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void PS2ExecutionMan_v01(cExecutionMan* self, int flags)
{
    self->field_0x8 = D_0048DC30;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

extern "C" void* func_00423C90(void* self);

//100%
void* PS2ExecutionMan_v06(void* self)
{
    return func_00423C90(self);
}

extern "C" void* func_00320550(int, int);

//100%
void* func_00320B28(void* self)
{
    return func_00320550(1, 0xffff);
}

extern "C" void* func_00320550(int, int);

//100%
void* func_00320B48(void* self)
{
    return func_00320550(0, 0xffff);
}

//100%
// Branchless ceil(log2(x)) for x > 0: count leading zeros by halving, then round up for non-powers of two.
extern "C" int func_00320B68(int x)
{
    int n;
    int t;
    int y;
    n = ((x - 0x10000) >> 31) & 16;
    y = x << n;
    t = ((y - 0x1000000) >> 31) & 8;
    y <<= t;
    n += t;
    t = ((y - 0x10000000) >> 31) & 4;
    y <<= t;
    n += t;
    t = ((y - 0x40000000) >> 31) & 2;
    y <<= t;
    n += t;
    n += 1 + (y >> 31);
    n += (-(x & (x - 1))) >> 31;
    return n ^ 31;
}

//100%
extern "C" void* func_00320FA8(int, int, int);

extern "C" void* func_00320BF0(void* self, int a1)
{
    return func_00320FA8(*(int*)((char*)self + 0x4), *(int*)self, a1);
}

extern "C" void* func_00321108(int, int, int);

extern "C" void func_00321010(void* a, void* b, int c, int d);

extern "C" void func_00320C18(void** self, int c, int d)
{
    func_00321010(self[1], self[0], c, d);
}

//100%
void* func_00320C48(void* self, int a1)
{
    return func_00321108(*(int*)((char*)self + 0x4), *(int*)self, a1);
}


extern "C" void func_00321188(void* a, void* b, int c, int d);

extern "C" void func_00320C70(void** self, int c, int d)
{
    func_00321188(self[1], self[0], c, d);
}
