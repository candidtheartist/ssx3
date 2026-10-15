#include "common.h"

struct cExecutionMan {
    int field_0x0;
    int field_0x4;
    void* field_0x8;
};

extern void* D_0048DC30[16];
void operator_delete(int* ptr);

//100%
INCLUDE_ASM("bx/execman", cExecutionMan__cExecutionMan__FP13cExecutionMani);
#ifdef SKIP_ASM
void cExecutionMan__cExecutionMan(cExecutionMan* self, int flags)
{
    self->field_0x8 = D_0048DC30;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}
#endif

//100%
INCLUDE_ASM("bx/execman", cExecutionMan_prepause__Fv);
#ifdef SKIP_ASM
void cExecutionMan_prepause()
{
}
#endif

//100%
INCLUDE_ASM("bx/execman", cExecutionMan_postpause__Fv);
#ifdef SKIP_ASM
void cExecutionMan_postpause()
{
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320960);
#ifdef SKIP_ASM
extern "C" int func_00320960(char* self)
{
    return *(int*)(self + 0x4) != 0;
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320970);
#ifdef SKIP_ASM
extern "C" void func_00320970(void* self, float value)
{
    *(float*)((char*)self + 0x24) = value;
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320978);
#ifdef SKIP_ASM
extern "C" int func_00320978(void* self)
{
    return *(int*)((char*)self + 0x10);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320980);
#ifdef SKIP_ASM
extern "C" float func_00320980(void* self)
{
    return *(float*)((char*)self + 0x14);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320988);
#ifdef SKIP_ASM
extern "C" float func_00320988(void* self)
{
    return *(float*)((char*)self + 0x24);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320990);
#ifdef SKIP_ASM
extern "C" float func_00320990(void* self)
{
    return *(float*)((char*)self + 0x2C);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320998);
#ifdef SKIP_ASM
extern "C" int func_00320998(void* self)
{
    return *(int*)((char*)self + 0x1C);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_003209A0);
#ifdef SKIP_ASM
extern "C" int func_003209A0(void* self)
{
    return *(int*)((char*)self + 0x18);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_003209A8);
#ifdef SKIP_ASM
extern "C" int func_003209A8(void* self)
{
    return *(int*)((char*)self + 0xC);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_003209B0);
#ifdef SKIP_ASM
extern "C" void func_003209B0(void* self, int value)
{
    *(int*)((char*)self + 0xC) = value;
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_003209B8);
#ifdef SKIP_ASM
extern "C" int func_003209B8(void* self)
{
    return *(int*)((char*)self + 0x0);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_003209C0);
#ifdef SKIP_ASM
// Virtual calls on the object at +0x8 (vtable at its +0x8)
extern "C" void func_003209C0(char* self)
{
    char* obj = *(char**)(self + 0x8);
    char* vt = *(char**)(obj + 0x8);
    (*(void (**)(char*))(vt + 0x2C))(obj + *(short*)(vt + 0x28));
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_003209F0);
#ifdef SKIP_ASM
extern "C" void func_003209F0(char* self)
{
    char* obj = *(char**)(self + 0x8);
    char* vt = *(char**)(obj + 0x8);
    (*(void (**)(char*))(vt + 0x24))(obj + *(short*)(vt + 0x20));
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320A20);
#ifdef SKIP_ASM
extern "C" unsigned int func_00320A20(char* self)
{
    char* obj = *(char**)(self + 0x8);
    if (obj) {
        char* vt = *(char**)(obj + 0x8);
        return (*(unsigned int (**)(char*))(vt + 0x34))(obj + *(short*)(vt + 0x30));
    }
    return 0xFFFFFFFF;
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320A60);
#ifdef SKIP_ASM
extern "C" void func_00320A60(char* self)
{
    char* obj = *(char**)(self + 0x8);
    char* vt = *(char**)(obj + 0x8);
    (*(void (**)(char*))(vt + 0x5C))(obj + *(short*)(vt + 0x58));
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320A90);
#ifdef SKIP_ASM
extern "C" void func_00320A90(char* self)
{
    char* obj = *(char**)(self + 0x8);
    char* vt = *(char**)(obj + 0x8);
    (*(void (**)(char*))(vt + 0x64))(obj + *(short*)(vt + 0x60));
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320AC0);
#ifdef SKIP_ASM
extern "C" void* func_00320AC0(void* self)
{
    return (char*)self + 0x38;
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320AC8);
#ifdef SKIP_ASM
extern int D_004A5B64;

extern "C" int func_00320AC8()
{
    return D_004A5B64;
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320AD0);
#ifdef SKIP_ASM
extern "C" void func_00320AD0(void* self, int value)
{
    *(int*)((char*)self + 0x34) = value;
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320AD8);
#ifdef SKIP_ASM
// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void func_00320AD8(cExecutionMan* self, int flags)
{
    self->field_0x8 = D_0048DC30;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}
#endif

extern "C" void* func_00423C90(void* self);

//100%
INCLUDE_ASM("bx/execman", func_00320B08__FPv);
#ifdef SKIP_ASM
void* func_00320B08(void* self)
{
    return func_00423C90(self);
}
#endif

extern "C" void* func_00320550(int, int);

//100%
INCLUDE_ASM("bx/execman", func_00320B28__FPv);
#ifdef SKIP_ASM
void* func_00320B28(void* self)
{
    return func_00320550(1, 0xffff);
}
#endif

extern "C" void* func_00320550(int, int);

//100%
INCLUDE_ASM("bx/execman", func_00320B48__FPv);
#ifdef SKIP_ASM
void* func_00320B48(void* self)
{
    return func_00320550(0, 0xffff);
}
#endif

INCLUDE_ASM("bx/execman", func_00320B68);

//100%
INCLUDE_ASM("bx/execman", func_00320BF0);
#ifdef SKIP_ASM
extern "C" void* func_00320FA8(int, int, int);

extern "C" void* func_00320BF0(void* self, int a1)
{
    return func_00320FA8(*(int*)((char*)self + 0x4), *(int*)self, a1);
}
#endif

extern "C" void* func_00321108(int, int, int);

//100%
INCLUDE_ASM("bx/execman", func_00320C18);
#ifdef SKIP_ASM
extern "C" void func_00321010(void* a, void* b, int c, int d);

extern "C" void func_00320C18(void** self, int c, int d)
{
    func_00321010(self[1], self[0], c, d);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320C48__FPvi);
#ifdef SKIP_ASM
void* func_00320C48(void* self, int a1)
{
    return func_00321108(*(int*)((char*)self + 0x4), *(int*)self, a1);
}
#endif

//100%
INCLUDE_ASM("bx/execman", func_00320C70);
#ifdef SKIP_ASM
extern "C" void func_00321188(void* a, void* b, int c, int d);

extern "C" void func_00320C70(void** self, int c, int d)
{
    func_00321188(self[1], self[0], c, d);
}
#endif
