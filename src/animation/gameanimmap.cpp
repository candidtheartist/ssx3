#include "common.h"

//100%
INCLUDE_ASM("animation/gameanimmap", cGameAnimMap_testResolve__Fv);
#ifdef SKIP_ASM
void cGameAnimMap_testResolve()
{
}
#endif

//100%
INCLUDE_ASM("animation/gameanimmap", func_003150B8);
#ifdef SKIP_ASM
extern "C" void* func_003150B8(void* p, ...)
{
    return p;
}
#endif

INCLUDE_ASM("animation/gameanimmap", func_003150F8);

extern "C" void* func_003150F8(int, int);

//100%
INCLUDE_ASM("animation/gameanimmap", func_003158B8);
#ifdef SKIP_ASM
extern "C" float func_003158B8(void* self)
{
    return *(float*)((char*)self + 0x1C);
}
#endif

//100%
INCLUDE_ASM("animation/gameanimmap", func_003158C0);
#ifdef SKIP_ASM
extern "C" long func_003158C0(void* self)
{
    return *(long*)((char*)self + 0x20);
}
#endif

//100%
INCLUDE_ASM("animation/gameanimmap", func_003158C8);
#ifdef SKIP_ASM
extern "C" void* func_003158C8(void* self)
{
    return (char*)self + 0x30;
}
#endif

//100%
INCLUDE_ASM("animation/gameanimmap", func_003158D0);
#ifdef SKIP_ASM
extern "C" int func_003158D0(void* self)
{
    return *(int*)((char*)self + 0x18);
}
#endif

//100%
INCLUDE_ASM("animation/gameanimmap", func_003158D8);
#ifdef SKIP_ASM
extern "C" void func_003158D8(void* self, int value)
{
    *(int*)((char*)self + 0x18) = value;
}
#endif

//100%
INCLUDE_ASM("animation/gameanimmap", func_003158E0);
#ifdef SKIP_ASM
extern "C" void func_003158E0(void* self, float value)
{
    *(float*)((char*)self + 0x1C) = value;
}
#endif

INCLUDE_ASM("animation/gameanimmap", func_003158E8);

INCLUDE_ASM("animation/gameanimmap", func_00315988);

//100%
INCLUDE_ASM("animation/gameanimmap", func_003159A0);
#ifdef SKIP_ASM
extern "C" void func_003159A0(void* self, long v)
{
    *(long*)((char*)self + 0x20) = v;
}
#endif

//100%
INCLUDE_ASM("animation/gameanimmap", func_003159A8);
#ifdef SKIP_ASM
extern "C" void func_003159A8(void* self)
{
    *(long*)((char*)self + 0x20) = -1;
}
#endif

INCLUDE_ASM("animation/gameanimmap", func_003159B8);

//100%
INCLUDE_ASM("animation/gameanimmap", func_003159E8);
#ifdef SKIP_ASM
extern "C" int func_003159E8(long* self, int bit)
{
    long mask = 1L << bit;
    return (*self & mask) != 0;
}
#endif

//99.38%
INCLUDE_ASM("animation/gameanimmap", func_00315A00__FPv);
#ifdef SKIP_ASM
void* func_00315A00(void* self)
{
    return func_003150F8(1, 0xffff);
}
#endif

INCLUDE_ASM("animation/gameanimmap", func_00315A20);

extern "C" void* func_00315A20(int, int);

//99.38%
INCLUDE_ASM("animation/gameanimmap", func_00316878__FPv);
#ifdef SKIP_ASM
void* func_00316878(void* self)
{
    return func_00315A20(1, 0xffff);
}
#endif

