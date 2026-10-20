#include "common.h"
#include "animation/rideranimbase.h"

//100%
void cGameAnimMap_testResolve()
{
}

extern "C" void* func_003150B8(void* p, ...)
{
    return p;
}

INCLUDE_ASM("animation/gameanimmap", __sti__gameanimmap_cpp);

extern "C" void* __sti__gameanimmap_cpp(int, int);

extern "C" float cRiderAnimBase_getPendingRate(void* self)
{
    return ((cRiderAnimBase*)self)->mPendingRate;
}

//100%
extern "C" long cRiderAnimBase_getBoneMask(void* self)
{
    return ((cRiderAnimBase*)self)->mBoneMask;
}

extern "C" void* cRiderAnimBase_getDefaultRoot(void* self)
{
    return &((cRiderAnimBase*)self)->mDefaultRootPos;
}

extern "C" int cRiderAnimBase_getMirror(void* self)
{
    return ((cRiderAnimBase*)self)->mMirror;
}

extern "C" void cRiderAnimBase_setMirror(void* self, int value)
{
    ((cRiderAnimBase*)self)->mMirror = value;
}

extern "C" void cRiderAnimBase_setPendingRate(void* self, float value)
{
    ((cRiderAnimBase*)self)->mPendingRate = value;
}

//100%
// Resets mDefaultRootPos to D_004FF130 and sets mDefaultRootRot to a rotation of -angle about the axis D_004FF160.
extern "C" void func_0031BE50(float* s, float* c, float angle);

struct sQuat_003158E8
{
    float x, y, z, w;
    sQuat_003158E8() {}
    sQuat_003158E8(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
} __attribute__((aligned(16)));

extern sQuat_003158E8 D_004FF130_3158E8 __asm__("D_004FF130");
extern sQuat_003158E8 D_004FF160_3158E8 __asm__("D_004FF160");

static inline sQuat_003158E8 AxisAngle_3158E8(const sQuat_003158E8& axis, float angle)
{
    float s, c;
    func_0031BE50(&s, &c, angle * 0.5f);
    return sQuat_003158E8(s * axis.x, s * axis.y, s * axis.z, c);
}

extern "C" void cRiderAnimBase_setDefaultHeading(void* self, float angle)
{
    cRiderAnimBase* ra = (cRiderAnimBase*)self;
    *(sQuat_003158E8*)&ra->mDefaultRootPos = D_004FF130_3158E8;
    *(sQuat_003158E8*)&ra->mDefaultRootRot = AxisAngle_3158E8(D_004FF160_3158E8, -angle);
}

//100%
// Copies the 0x20-byte pair of vectors from src into mDefaultRootPos/mDefaultRootRot.
struct sVec4_315988
{
    float x, y, z, w;
} __attribute__((aligned(16)));
struct sPair_315988 { sVec4_315988 a, b; };

extern "C" void cRiderAnimBase_setDefaultRoot(char* self, sPair_315988* src)
{
    *(sPair_315988*)&((cRiderAnimBase*)self)->mDefaultRootPos = *src;
}

//100%
extern "C" void cRiderAnimBase_setBoneMask(void* self, long v)
{
    ((cRiderAnimBase*)self)->mBoneMask = v;
}

//100%
extern "C" void cRiderAnimBase_resetBoneMask(void* self)
{
    ((cRiderAnimBase*)self)->mBoneMask = -1;
}

//100%
// Moves bit n from the mask at 0x0 to the mask at 0x8. Same body as moveFlagBit (0x00144670).
extern "C" void func_003159B8(long* self, int n)
{
    long bit = 1L << n;
    self[1] |= bit & self[0];
    self[0] &= ~bit;
}

//100%
// Tests bit in the mask at 0x0. Same body as testFlagBit (0x001446A0).
extern "C" int func_003159E8(long* self, int bit)
{
    long mask = 1L << bit;
    return (*self & mask) != 0;
}

//99.38%
// Static-constructor table entry (0x0043CEB0) for this unit.
void* gameanimmapStaticInit(void* self)
{
    return __sti__gameanimmap_cpp(1, 0xffff);
}

INCLUDE_ASM("animation/gameanimmap", func_00315A20);

extern "C" void* func_00315A20(int, int);

//99.38%
void* func_00316878(void* self)
{
    return func_00315A20(1, 0xffff);
}

