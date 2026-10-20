#include "common.h"

INCLUDE_ASM("object/deadfadenode", cDeadFadeNode_cDeadFadeNode);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
void* cInstanceNode_ctor_v(void* self) __asm__("cInstanceNode_cInstanceNode");
extern char D_00491980[];

extern "C" void* func_00350B98(void* self)
{
    cInstanceNode_ctor_v(self);
    *(void**)((char*)self + 0xC) = D_00491980;
    *(unsigned int*)((char*)self + 0x1C) = 0xFFFFFFFFU;
    *(int*)((char*)self + 0x38) = 0;
    return self;
}

//100%
extern char D_00491980[];
void cMemMan_free(void*);
extern "C" void func_0034FBF0(void* self, int flags);

extern "C" void DeadFade_dtor(void* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_00491980;
    void* p = *(void**)((char*)self + 0x38);
    if (p != 0) {
        cMemMan_free(p);
    }
    func_0034FBF0(self, flags);
}

//100%
// PORT: the project names this func_002D1CC0__FPv (one void* arg), but it is a
// pass-through wrapper and this caller passes two args (prototype mismatch).
void* func_002D1CC0_2(void*, void*) __asm__("func_002D1CC0__FPv");

extern "C" void func_00350C38(void* self)
{
    float t;
    *(float*)((char*)self + 0x30) += *(float*)((char*)self + 0x34);
    t = *(float*)((char*)self + 0x28);
    if (t > 0.0f) {
        *(float*)((char*)self + 0x28) = t - *(float*)((char*)self + 0x2C);
    } else {
        func_002D1CC0_2(*(void**)((char*)self + 0x18), (char*)self + 0x1C);
    }
}

//100%
// PORT: the project names this func_002D1CC0__FPv (one void* arg), but it is a
// pass-through wrapper and this caller passes two args (prototype mismatch).
void* func_002D1CC0_2(void*, void*) __asm__("func_002D1CC0__FPv");

extern "C" void DeadFade_Kill(void* self)
{
    func_002D1CC0_2(*(void**)((char*)self + 0x18), (char*)self + 0x1C);
}

INCLUDE_ASM("object/deadfadenode", func_00350CB8);

extern "C" void* func_0034FE90(void* self);

//100%
void* func_00350E70(void* self)
{
    return func_0034FE90(self);
}

//100%
extern "C" void* func_0034FB00(void* self, int a1, int type, void* a3);
extern char D_00491800[];

extern "C" void* func_00350E90(void* self, void* a1)
{
    func_0034FB00(self, 1, 0x10, a1);
    *(void**)((char*)self + 0xC) = D_00491800;
    unsigned int* f = (unsigned int*)(*(char**)((char*)self + 0x18) + 0x8);
    *f &= 0xFFFFFF9F;
    f = (unsigned int*)(*(char**)((char*)self + 0x18) + 0x8);
    *f = (*f & 0xFFFFFFFD) | 4;
    return self;
}

//100%
extern "C" void cInstanceNode_cInstanceNode(void* self);
extern char D_00491800[];

extern "C" void* func_00350F08(void* self)
{
    cInstanceNode_cInstanceNode(self);
    *(void**)((char*)self + 0xC) = D_00491800;
    return self;
}

//100%
void* func_00350F40(void* self)
{
    return func_0034FE90(self);
}

//100%
extern "C" void* func_0034FB00(void* self, int a1, int type, void* a3);
extern char D_00491680[];

extern "C" void* func_00350F60(void* self, void* a1)
{
    func_0034FB00(self, 1, 0x13, a1);
    *(void**)((char*)self + 0xC) = D_00491680;
    unsigned int* f = (unsigned int*)(*(char**)((char*)self + 0x18) + 0x8);
    *f &= 0xFFFFFF9F;
    f = (unsigned int*)(*(char**)((char*)self + 0x18) + 0x8);
    *f = (*f & 0xFFFFFFFD) | 4;
    return self;
}

//100%
extern "C" void cInstanceNode_cInstanceNode(void* self);
extern char D_00491680[];

extern "C" void* func_00350FD8(void* self)
{
    cInstanceNode_cInstanceNode(self);
    *(void**)((char*)self + 0xC) = D_00491680;
    return self;
}

//100%
void* func_00351010(void* self)
{
    return func_0034FE90(self);
}

