#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cWorldPainterQuery_cWorldPainterQuery(void* self, void* arg);
extern const char D_00483DE8[];

struct cWorldPainterManArg {
    void* field_0x0;
};

//100%
void* cWorldPainterMan_getQuery(void* self, cWorldPainterManArg* x)
{
    void* mem = cMemMan_alloc(0x18, D_00483DE8, 0, 0);
    void* arg = x->field_0x0;
    return cWorldPainterQuery_cWorldPainterQuery(mem, arg);
}

extern "C" void func_002C0AA0(void* self, int* a, int* b, float t)
{
    if (t == 1.0f) {
        *a = *b;
    } else {
        *a = (int)((float)*a * (1.0f - t) + (float)*b * t);
    }
}

extern "C" void func_002C0AF0(void* self, float* a, float* b, float t)
{
    if (t == 1.0f) {
        *a = *b;
    } else {
        *a = *a * (1.0f - t) + *b * t;
    }
}

extern "C" void* func_002C0B30(void* p, ...)
{
    return p;
}

INCLUDE_ASM("worldpainter/worldpaintermanquery", func_002C0B70);

//100%
void func_002C1458(void* self)
{
}

//100%
extern void* D_00485D30[];
void operator_delete(int* ptr);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void func_002C1460(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_00485D30;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
void* func_002C1490(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* func_002C1498(void* self)
{
    return (char*)self + 0x10;
}

//100%
void* tWPIGD_Mix_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Ambience_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Speech_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Camera_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Fog_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Fog_Get10(void* self)
{
    return (char*)self + 0x10;
}

//100%
void* func_002C14D0(void* self)
{
    return (char*)self + 0x18;
}

//100%
void* func_002C14D8(void* self)
{
    return (char*)self + 0x20;
}

//100%
void* func_002C14E0(void* self)
{
    return (char*)self + 0x28;
}

//100%
void* func_002C14E8(void* self)
{
    return (char*)self + 0x30;
}

//100%
void* tWPIGD_LightGlow_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_LightGlow_Get10(void* self)
{
    return (char*)self + 0x10;
}

//100%
void* tWPIGD_LightGlow_Get18(void* self)
{
    return (char*)self + 0x18;
}

//100%
void* tWPIGD_LightGlow_Get20(void* self)
{
    return (char*)self + 0x20;
}

//100%
void* tWPIGD_LightGlow_Get28(void* self)
{
    return (char*)self + 0x28;
}

//100%
void* tWPIGD_LightGlow_Get30(void* self)
{
    return (char*)self + 0x30;
}

//100%
void* func_002C1520(void* self)
{
    return (char*)self + 0x38;
}

//100%
void* tWPIGD_ScreenTint_GetTintRed(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_ScreenTint_GetTintGreen(void* self)
{
    return (char*)self + 0x10;
}

//100%
void* tWPIGD_ScreenTint_GetTintBlue(void* self)
{
    return (char*)self + 0x18;
}

//100%
void* tWPIGD_ScreenTint_GetFillRed(void* self)
{
    return (char*)self + 0x20;
}

//100%
void* tWPIGD_ScreenTint_GetFillGreen(void* self)
{
    return (char*)self + 0x28;
}

//100%
void* tWPIGD_ScreenTint_GetFillBlue(void* self)
{
    return (char*)self + 0x30;
}

//100%
void* tWPIGD_SkyBox_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Sun_GetElevation(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Sun_GetAzimuth(void* self)
{
    return (char*)self + 0x10;
}

//100%
void* tWPIGD_Sun_GetRed(void* self)
{
    return (char*)self + 0x18;
}

//100%
void* tWPIGD_Sun_GetGreen(void* self)
{
    return (char*)self + 0x20;
}

//100%
void* tWPIGD_Sun_GetBlue(void* self)
{
    return (char*)self + 0x28;
}

//100%
void* tWPIGD_Sun_GetIntensity(void* self)
{
    return (char*)self + 0x30;
}

//100%
void* tWPIGD_Sun_GetTexture(void* self)
{
    return (char*)self + 0x38;
}

//100%
void* func_002C1598(void* self)
{
    return (char*)self + 0x40;
}

//100%
void* func_002C15A0(void* self)
{
    return (char*)self + 0x48;
}

//100%
void* tWPIGD_Surface_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Lighting_GetIrradianceName0(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Lighting_GetIrradianceName1(void* self)
{
    return (char*)self + 0x18;
}

//100%
void* tWPIGD_Lighting_Get28(void* self)
{
    return (char*)self + 0x28;
}

//100%
void* tWPIGD_Lighting_Get38(void* self)
{
    return (char*)self + 0x38;
}

//100%
void* tWPIGD_Lighting_Get48(void* self)
{
    return (char*)self + 0x48;
}

//100%
void* func_002C15D8(void* self)
{
    return (char*)self + 0x50;
}

//100%
void* tWPIGD_Weather_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Weather_Get10(void* self)
{
    return (char*)self + 0x10;
}

//100%
void* tWPIGD_Weather_Get18(void* self)
{
    return (char*)self + 0x18;
}

//100%
void* tWPIGD_Weather_Get20(void* self)
{
    return (char*)self + 0x20;
}

//100%
void* tWPIGD_Weather_Get28(void* self)
{
    return (char*)self + 0x28;
}

//100%
void* tWPIGD_Weather_Get30(void* self)
{
    return (char*)self + 0x30;
}

//100%
void* tWPIGD_Weather_Get38(void* self)
{
    return (char*)self + 0x38;
}

//100%
void* tWPIGD_Weather_Get40(void* self)
{
    return (char*)self + 0x40;
}

//100%
void* tWPIGD_Weather_Get48(void* self)
{
    return (char*)self + 0x48;
}

//100%
void* tWPIGD_Weather_Get50(void* self)
{
    return (char*)self + 0x50;
}

//100%
void* func_002C1630(void* self)
{
    return (char*)self + 0x58;
}

//100%
void* func_002C1638(void* self)
{
    return (char*)self + 0x60;
}

//100%
void* func_002C1640(void* self)
{
    return (char*)self + 0x68;
}

//100%
void* func_002C1648(void* self)
{
    return (char*)self + 0x70;
}

//100%
void* func_002C1650(void* self)
{
    return (char*)self + 0x78;
}

//100%
void* func_002C1658(void* self)
{
    return (char*)self + 0x80;
}

//100%
void* func_002C1660(void* self)
{
    return (char*)self + 0x88;
}

//100%
void* func_002C1668(void* self)
{
    return (char*)self + 0x90;
}

//100%
void* func_002C1670(void* self)
{
    return (char*)self + 0x98;
}

//100%
void* tWPIGD_Danger_Get08(void* self)
{
    return (char*)self + 0x8;
}

//100%
void* tWPIGD_Danger_Get10(void* self)
{
    return (char*)self + 0x10;
}

extern "C" void* func_002C0B70(int, int);

//99.38%
void* func_002C1688(void* self)
{
    return func_002C0B70(1, 0xffff);
}

//100%
extern "C" void func_002C16A8(int* p, int a, int b)
{
    p[1] = a;
    p[0] = b;
}

//100%
extern "C" void func_002C16B8(unsigned short* p, unsigned short a, unsigned short b, unsigned short c, unsigned short d)
{
    p[0] = (a << 1) | 1;
    p[1] = (b << 1) | (p[1] & 1);
    p[2] = (c << 1) | (p[2] & 1);
    p[3] = (d << 1) | (p[3] & 1);
}

//100%
extern "C" void func_002C1718(int* p)
{
    p[0] = 0;
    p[1] = 0;
}

extern "C" int cQuadTree_getFreeNode(void* self);
extern "C" void* func_002C1728(void* self, int a, int b, float x, float y, float size)
{
    char* s = (char*)self;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0xC) = 0;
    *(float*)(s + 0x4) = x;
    *(float*)(s + 0x8) = y;
    *(float*)(s + 0x0) = 32768.0f / size;
    *(unsigned short*)(s + 0x14) = cQuadTree_getFreeNode(self);
    *(unsigned short*)(s + 0x16) = 0;
    func_002C16A8((int*)(*(char**)(s + 0x20) + *(unsigned short*)(s + 0x14) * 8), a, b);
    *(int*)(s + 0x1C) = a;
    *(int*)(s + 0x18) = b;
    return self;
}

//100%
void func_002C17C0(void* self)
{
    void* t0 = (char*)self + 0x28;
    *(void**)((char*)self + 0x20) = t0;
    *(void**)((char*)self + 0x24) = t0;
}

