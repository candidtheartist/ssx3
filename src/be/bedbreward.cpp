#include "common.h"

//100%
INCLUDE_ASM("be/bedbreward", cBERewardDB_init);
#ifdef SKIP_ASM
extern "C" int func_00317F60(const char* name);
extern "C" int func_003E1BB8(const char* name, void* buf, int size);
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator new[](unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" void func_0015A818(void* self, void* data);
extern "C" int func_0019DA10(void* self, int bank, const char* name, int a3, int a4, int a5);
extern const char* D_004A1270;
extern const char D_0045AB78[];
extern void* D_004A28A8;

// Loads the reward database: synchronously when flag is 0, otherwise as an async sound-bank request.
extern "C" void cBERewardDB_init(void* self, int flag)
{
    if (flag == 0)
    {
        unsigned int size = func_00317F60(D_004A1270);
        char* buf = new (D_0045AB78, 0, 0) char[size];
        func_003E1BB8(D_004A1270, buf, size);
        func_0015A818(self, buf);
        *(int*)self = -1;
    }
    else
    {
        *(int*)self = func_0019DA10(*(char**)((char*)D_004A28A8 + 0x7C) + 0x1A70, 0, D_004A1270, 0xA, flag, 0);
    }
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015AE00);
#ifdef SKIP_ASM
extern void* D_004A28A8;
extern "C" void func_0019DC20(void* self, int bank, int i);
extern "C" void func_0019D4B8(void* self, int bank, int i);
void cMemMan_free(void* p);

struct sBEDB_0015AE00
{
    int handle;
    void* data;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
    int f28;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
    int f44;
    int f48;
    int f4C;
};

extern "C" void func_0015AE00(sBEDB_0015AE00* self)
{
    if (self->handle >= 0)
    {
        char* snd = *(char**)((char*)D_004A28A8 + 0x7C) + 0x1A70;
        func_0019DC20(snd, 0, self->handle);
        func_0019D4B8(snd, 0, self->handle);
    }
    if (self->data != 0)
    {
        cMemMan_free(self->data);
    }
    self->handle = -1;
    self->data = 0;
    self->f8 = 0;
    self->fC = 0;
    self->f10 = 0;
    self->f14 = 0;
    self->f18 = 0;
    self->f1C = 0;
    self->f20 = 0;
    self->f24 = 0;
    self->f2C = 0;
    self->f30 = 0;
    self->f34 = 0;
    self->f38 = 0;
    self->f3C = 0;
    self->f40 = 0;
    self->f44 = 0;
    self->f48 = 0;
    self->f4C = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015AEC0);
#ifdef SKIP_ASM
extern "C" int func_0019E238(void* self, int bank, int handle);
extern "C" void* func_0019E330(void* self, int bank, int handle);

extern "C" void func_0015AEC0(sBEDB_0015AE00* self)
{
    if (self->handle >= 0)
    {
        char* snd = *(char**)((char*)D_004A28A8 + 0x7C) + 0x1A70;
        if (func_0019E238(snd, 0, self->handle))
        {
            func_0015A818(self, func_0019E330(snd, 0, self->handle));
            func_0019DC20(snd, 0, self->handle);
            self->handle = -1;
        }
    }
}
#endif

INCLUDE_ASM("be/bedbreward", func_0015AF40);

//100%
INCLUDE_ASM("be/bedbreward", func_0015AFE8);
#ifdef SKIP_ASM
// Variadic no-op (probably a stripped debug print); returns its first argument.
extern "C" void* func_0015AFE8(void* a, ...)
{
    return a;
}
#endif

INCLUDE_ASM("be/bedbreward", func_0015B028);

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB00__FPv);
#ifdef SKIP_ASM
void func_0015BB00(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB08__FPv);
#ifdef SKIP_ASM
void func_0015BB08(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB10__FPv);
#ifdef SKIP_ASM
void func_0015BB10(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB18__FPv);
#ifdef SKIP_ASM
void func_0015BB18(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB20);
#ifdef SKIP_ASM
void operator_delete(int* ptr);
extern int* D_004A11B4;

extern "C" void func_0015BB20()
{
    operator_delete(D_004A11B4);
    D_004A11B4 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB48);
#ifdef SKIP_ASM
extern int D_00535BF8[];
extern int D_00535BFC[];
extern int D_00535C00[];
extern int D_00535C04[];
extern int D_00535C08[];
extern int D_00535C0C[];
extern signed char D_00535C10[];
extern signed char D_00535C11[];
extern signed char D_00535C12[];

extern "C" int func_0015BB48()
{
    return D_00535BF8[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB58);
#ifdef SKIP_ASM
extern "C" int func_0015BB58()
{
    return D_00535BFC[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB68);
#ifdef SKIP_ASM
extern "C" int func_0015BB68()
{
    return D_00535C04[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB78);
#ifdef SKIP_ASM
extern "C" int func_0015BB78()
{
    return D_00535C00[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB88);
#ifdef SKIP_ASM
extern "C" void func_0015BB88(void* self, int value)
{
    D_00535C0C[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BB98);
#ifdef SKIP_ASM
extern "C" int func_0015BB98()
{
    return D_00535C0C[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BBA8);
#ifdef SKIP_ASM
extern "C" int func_0015BBA8()
{
    return D_00535C10[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BBB8);
#ifdef SKIP_ASM
extern "C" int func_0015BBB8()
{
    return D_00535C12[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BBC8);
#ifdef SKIP_ASM
extern "C" int func_0015BBC8()
{
    return D_00535C11[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BBD8);
#ifdef SKIP_ASM
extern int D_004A11B8;

extern "C" void func_0015BBD8(void* self, int value)
{
    D_00535C08[0] = value;
    D_004A11B8 = 1;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BBF0);
#ifdef SKIP_ASM
extern int D_004A11BC;

extern "C" void func_0015BBF0(void* self, int value)
{
    D_004A11BC = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BBF8);
#ifdef SKIP_ASM
extern "C" int func_0015BBF8()
{
    return D_004A11BC;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BC00);
#ifdef SKIP_ASM
extern "C" int func_0015BC00()
{
    return D_004A11B8;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BC08);
#ifdef SKIP_ASM
extern "C" void func_0015BC08()
{
    D_004A11B8 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BC10);
#ifdef SKIP_ASM
extern "C" void* cBXString_cBXString4(void* self, const char* str);
extern "C" void cBXString_cBXString1(void* self, void* src);
extern int D_004A4CB8;

extern "C" void func_0015BC10(void* self, const char* str)
{
    cBXString_cBXString4(&D_004A4CB8, str);
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BC30);
#ifdef SKIP_ASM
extern "C" void* func_0015BC30(void* out)
{
    cBXString_cBXString1(out, &D_004A4CB8);
    return out;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BC60);
#ifdef SKIP_ASM
extern "C" void func_0015BC60(int value)
{
    *(int*)((char*)D_004A11B4 + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BC70);
#ifdef SKIP_ASM
extern char D_0045AE58[];

// Constructor: installs the vtable at +0xC.
extern "C" void* func_0015BC70(void* self)
{
    *(void**)((char*)self + 0xC) = D_0045AE58;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BC88);
#ifdef SKIP_ASM
extern int* D_004A11C0;

extern "C" void func_0015BC88()
{
    operator_delete(D_004A11C0);
    D_004A11C0 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BCB0);
#ifdef SKIP_ASM
extern "C" void func_0015BCB0(int value)
{
    *(int*)((char*)D_004A11C0 + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BCC0__FPv);
#ifdef SKIP_ASM
void func_0015BCC0(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BCC8__FPv);
#ifdef SKIP_ASM
void func_0015BCC8(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BCD0);
#ifdef SKIP_ASM
extern int* D_004A1238;

extern "C" void func_0015BCD0()
{
    operator_delete(D_004A1238);
    D_004A1238 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BCF8);
#ifdef SKIP_ASM
extern "C" int func_0015BCF8(void* self)
{
    return *(int*)((char*)self + 0x10);
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BD00);
#ifdef SKIP_ASM
extern "C" void func_0015BD00(void* self, int value)
{
    *(int*)((char*)self + 0x10) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BD08);
#ifdef SKIP_ASM
extern "C" void func_0015BD08(int value)
{
    *(int*)((char*)D_004A1238 + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BD18);
#ifdef SKIP_ASM
extern char D_0045ADF8[];

extern "C" void* func_0015BD18(void* self)
{
    *(void**)((char*)self + 0xC) = D_0045ADF8;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BD30);
#ifdef SKIP_ASM
extern int* D_004A120C;

extern "C" void func_0015BD30()
{
    operator_delete(D_004A120C);
    D_004A120C = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BD58);
#ifdef SKIP_ASM
// Whole 0x288-byte reward settings block at 0x00535610.
struct sRewardSettings
{
    int w[0x288 / 4];
};
extern sRewardSettings D_00535610_all __asm__("D_00535610");

extern "C" sRewardSettings func_0015BD58()
{
    return D_00535610_all;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BE10);
#ifdef SKIP_ASM
extern "C" void func_0015BE10(void* self, sRewardSettings* src)
{
    D_00535610_all = *src;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BEC0);
#ifdef SKIP_ASM
// Packed reward/option flags word at 0x00535610.
struct sRewardFlags
{
    unsigned int f0 : 4;
    unsigned char f4 : 4;
    unsigned int f8 : 4;
    unsigned int f12 : 2;
    unsigned int f14 : 2;
    unsigned int f16 : 1;
    unsigned int f17 : 1;
    unsigned int f18 : 1;
    unsigned int f19 : 1;
    unsigned int f20 : 2;
    unsigned int f22 : 3;
    unsigned int f25 : 4;
    unsigned int f29 : 1;
    unsigned int f30 : 2;
};

extern sRewardFlags D_00535610[];

extern "C" void func_0015BEC0(void* self, int value)
{
    D_00535610[0].f19 = value != 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BEE8);
#ifdef SKIP_ASM
extern "C" void func_0015BEE8(void* self, int value)
{
    D_00535610[0].f20 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BF10);
#ifdef SKIP_ASM
extern "C" void func_0015BF10(void* self, int value)
{
    D_00535610[0].f22 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BF38);
#ifdef SKIP_ASM
extern "C" void func_0015BF38(void* self, int value)
{
    D_00535610[0].f25 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BF60);
#ifdef SKIP_ASM
extern "C" void func_0015BF60(void* self, int value)
{
    D_00535610[0].f29 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BF88);
#ifdef SKIP_ASM
extern "C" int func_0015BF88()
{
    return 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BF90);
#ifdef SKIP_ASM
extern "C" int func_0015BF90()
{
    return D_00535610[0].f22;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BFA8);
#ifdef SKIP_ASM
extern "C" void func_0015BFA8(void* self, int value)
{
    D_00535610[0].f12 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BFD0);
#ifdef SKIP_ASM
extern "C" void func_0015BFD0(void* self, int value)
{
    D_00535610[0].f14 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015BFF8);
#ifdef SKIP_ASM
extern "C" void func_0015BFF8(void* self, int value)
{
    D_00535610[0].f0 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C018);
#ifdef SKIP_ASM
extern "C" void func_0015C018(void* self, int value)
{
    D_00535610[0].f4 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C040);
#ifdef SKIP_ASM
extern "C" void func_0015C040(void* self, int value)
{
    D_00535610[0].f8 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C068);
#ifdef SKIP_ASM
extern "C" void func_0015C068(void* self, int value)
{
    D_00535610[0].f16 = value != 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C090);
#ifdef SKIP_ASM
extern "C" void func_0015C090(void* self, int value)
{
    D_00535610[0].f17 = value != 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C0B8);
#ifdef SKIP_ASM
extern "C" void func_0015C0B8(void* self, int value)
{
    D_00535610[0].f18 = value != 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C0E0);
#ifdef SKIP_ASM
extern "C" int func_0015C0E0()
{
    return D_00535610[0].f12;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C0F8);
#ifdef SKIP_ASM
extern "C" int func_0015C0F8()
{
    return D_00535610[0].f14;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C110);
#ifdef SKIP_ASM
extern "C" int func_0015C110()
{
    return D_00535610[0].f0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C120);
#ifdef SKIP_ASM
extern "C" int func_0015C120()
{
    return D_00535610[0].f4;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C130);
#ifdef SKIP_ASM
extern "C" int func_0015C130()
{
    return D_00535610[0].f8;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C148);
#ifdef SKIP_ASM
extern "C" bool func_0015C148()
{
    return D_00535610[0].f16;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C158);
#ifdef SKIP_ASM
extern "C" bool func_0015C158()
{
    return D_00535610[0].f17;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C170);
#ifdef SKIP_ASM
extern "C" bool func_0015C170()
{
    return D_00535610[0].f18;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C188);
#ifdef SKIP_ASM
extern "C" char* strcpy(char* dst, const char* src);
extern char D_00535617[][64];

extern "C" void func_0015C188(void* self, int i, const char* name)
{
    strcpy(D_00535617[i], name);
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C1B8);
#ifdef SKIP_ASM
extern "C" void func_0015C1B8(void* self, int value)
{
    D_00535610[0].f30 = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C1E0);
#ifdef SKIP_ASM
extern char D_00535615[];
extern char D_00535616[];

extern "C" void func_0015C1E0(void* self, char value)
{
    D_00535615[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C1F0);
#ifdef SKIP_ASM
extern "C" void func_0015C1F0(void* self, char value)
{
    D_00535616[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C200);
#ifdef SKIP_ASM
extern "C" void func_0015C200(int value)
{
    *(int*)((char*)D_004A120C + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C210);
#ifdef SKIP_ASM
extern char D_0045ADC8[];

extern "C" void* func_0015C210(void* self)
{
    *(void**)((char*)self + 0xC) = D_0045ADC8;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C228);
#ifdef SKIP_ASM
// func_003E6448 looks like memset(dst, value, size).
extern "C" void* func_003E6448(void* dst, int value, int size);
extern char D_005308B8[];

extern "C" void func_0015C228()
{
    func_003E6448(D_005308B8, 0, 0x20);
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C250);
#ifdef SKIP_ASM
extern int* D_004A1204;

extern "C" void func_0015C250()
{
    operator_delete(D_004A1204);
    D_004A1204 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C278);
#ifdef SKIP_ASM
extern int D_00534B30[];
extern int D_00534B34[];
extern int D_00534B38[];
extern int D_00534B3C[];
extern float D_00534B40[];
extern int D_00534D44[];

extern "C" void func_0015C278(void* self, int value)
{
    D_00534B30[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C288);
#ifdef SKIP_ASM
extern "C" int func_0015C288()
{
    return D_00534B30[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C298);
#ifdef SKIP_ASM
extern "C" void func_0015C298(void* self, int value)
{
    D_00534B34[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C2A8);
#ifdef SKIP_ASM
extern "C" int func_0015C2A8()
{
    return D_00534B34[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C2B8);
#ifdef SKIP_ASM
extern "C" void func_0015C2B8(void* self, int value)
{
    D_00534B38[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C2C8);
#ifdef SKIP_ASM
extern "C" int func_0015C2C8()
{
    return D_00534B38[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C2D8);
#ifdef SKIP_ASM
extern "C" void func_0015C2D8(void* self, int value)
{
    D_00534B3C[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C2E8);
#ifdef SKIP_ASM
extern "C" int func_0015C2E8()
{
    return D_00534B3C[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C2F8);
#ifdef SKIP_ASM
extern "C" void func_0015C2F8(void* self, float value)
{
    D_00534B40[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C308);
#ifdef SKIP_ASM
extern "C" float func_0015C308()
{
    return D_00534B40[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C318);
#ifdef SKIP_ASM
extern "C" void func_0015C318(void* self, int value)
{
    D_00534D44[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C328);
#ifdef SKIP_ASM
extern "C" int func_0015C328()
{
    return D_00534D44[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C338);
#ifdef SKIP_ASM
extern char D_00534D48[];

extern "C" void func_0015C338(void* self, const char* src)
{
    strcpy(D_00534D48, src);
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C358);
#ifdef SKIP_ASM
extern "C" void* func_0015C358()
{
    return D_00534D48;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C368);
#ifdef SKIP_ASM
extern char D_00534DC0[];

extern "C" void func_0015C368(void* self, const char* src)
{
    strcpy(D_00534DC0, src);
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C388);
#ifdef SKIP_ASM
extern "C" void* func_0015C388()
{
    return D_00534DC0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C398);
#ifdef SKIP_ASM
extern char D_00534E38[];

extern "C" void func_0015C398(void* self, const char* src)
{
    strcpy(D_00534E38, src);
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C3B8);
#ifdef SKIP_ASM
extern "C" void* func_0015C3B8()
{
    return D_00534E38;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C3C8);
#ifdef SKIP_ASM
extern "C" void func_0015C3C8(int value)
{
    *(int*)((char*)D_004A1204 + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C3D8);
#ifdef SKIP_ASM
extern int D_00534E58[];
extern int D_00534E5C[];

extern "C" void func_0015C3D8(void* self, int value)
{
    D_00534E58[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C3E8);
#ifdef SKIP_ASM
extern "C" int func_0015C3E8()
{
    return D_00534E58[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C3F8);
#ifdef SKIP_ASM
extern "C" void func_0015C3F8(void* self, int value)
{
    D_00534E5C[0] = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C408);
#ifdef SKIP_ASM
extern "C" int func_0015C408()
{
    return D_00534E5C[0];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C418);
#ifdef SKIP_ASM
struct sRewardBlockAC
{
    int w[0xAC / 4];
};
extern sRewardBlockAC D_00534E60_blk __asm__("D_00534E60");
extern sRewardBlockAC D_00534F0C_blk __asm__("D_00534F0C");

extern "C" void func_0015C418(void* self, sRewardBlockAC* src)
{
    D_00534E60_blk = *src;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C4D0);
#ifdef SKIP_ASM
extern char D_00534E60[];

extern "C" void* func_0015C4D0()
{
    return D_00534E60;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C4E0);
#ifdef SKIP_ASM
extern "C" void func_0015C4E0(void* self, sRewardBlockAC* src)
{
    D_00534F0C_blk = *src;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C598);
#ifdef SKIP_ASM
extern char D_00534F0C[];

extern "C" void* func_0015C598()
{
    return D_00534F0C;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C5A8);
#ifdef SKIP_ASM
extern char D_00534FC8[];

extern "C" void* func_0015C5A8()
{
    return D_00534FC8;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C5B8);
#ifdef SKIP_ASM
extern char D_00534FB8[];

extern "C" void* func_0015C5B8()
{
    return D_00534FB8;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C5C8);
#ifdef SKIP_ASM
extern char D_00534FD8[];

struct sBytes7
{
    char b[7];
};

extern "C" void func_0015C5C8(void* self, sBytes7* src)
{
    *(sBytes7*)D_00534FD8 = *src;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C600);
#ifdef SKIP_ASM
extern "C" void* func_0015C600()
{
    return D_00534FD8;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C610);
#ifdef SKIP_ASM
extern "C" int func_0015C610()
{
    return 0x8;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C618);
#ifdef SKIP_ASM
// Sum of the 7 bytes at D_00534FD8, divided by 35.
extern "C" int func_0015C618()
{
    int sum = 0;
    int i;
    for (i = 0; i < 7; i++)
    {
        sum += ((unsigned char*)D_00534FD8)[i];
    }
    return sum / 35;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C660);
#ifdef SKIP_ASM
extern char D_0045AD98[];

extern "C" void* func_0015C660(void* self)
{
    *(void**)((char*)self + 0xC) = D_0045AD98;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C678);
#ifdef SKIP_ASM
extern int* D_004A11C4;

extern "C" void func_0015C678()
{
    operator_delete(D_004A11C4);
    D_004A11C4 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C6A0);
#ifdef SKIP_ASM
extern "C" void func_0015C6A0(int value)
{
    *(int*)((char*)D_004A11C4 + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C6B0);
#ifdef SKIP_ASM
extern char D_0045AD68[];

extern "C" void* func_0015C6B0(void* self)
{
    *(void**)((char*)self + 0xC) = D_0045AD68;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C6C8__FPv);
#ifdef SKIP_ASM
void func_0015C6C8(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C6D0__FPv);
#ifdef SKIP_ASM
void func_0015C6D0(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C6D8__FPv);
#ifdef SKIP_ASM
void func_0015C6D8(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C6E0__FPv);
#ifdef SKIP_ASM
void func_0015C6E0(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C6E8);
#ifdef SKIP_ASM
extern int* D_004A1210;

extern "C" void func_0015C6E8()
{
    operator_delete(D_004A1210);
    D_004A1210 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C710);
#ifdef SKIP_ASM
extern "C" void func_0015C710(int value)
{
    *(int*)((char*)D_004A1210 + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C720);
#ifdef SKIP_ASM
extern char D_0045ACD8[];

extern "C" void* func_0015C720(void* self)
{
    *(void**)((char*)self + 0xC) = D_0045ACD8;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C738);
#ifdef SKIP_ASM
extern int* D_004A1248;

extern "C" void func_0015C738()
{
    operator_delete(D_004A1248);
    D_004A1248 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C760);
#ifdef SKIP_ASM
extern "C" int func_0015C760(void* self)
{
    return *(int*)((char*)self + 0x10) != 0 || *(int*)((char*)self + 0x14) != 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C788);
#ifdef SKIP_ASM
extern "C" int func_0015C788(void* self)
{
    return *(int*)((char*)self + 0x18) >= 0 || *(int*)((char*)self + 0x1C) >= 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C7B0);
#ifdef SKIP_ASM
struct sfunc_0015C7B0 {
    char pad[0x18];
    int values[1];
};

extern "C" int func_0015C7B0(sfunc_0015C7B0* self, int i)
{
    return self->values[i];
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C7C0);
#ifdef SKIP_ASM
extern "C" void func_0015C7C0(int value)
{
    *(int*)((char*)D_004A1248 + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C7D0__FPv);
#ifdef SKIP_ASM
void func_0015C7D0(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C7D8__FPv);
#ifdef SKIP_ASM
void func_0015C7D8(void* self)
{
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C7E0);
#ifdef SKIP_ASM
extern int* D_004A124C;

extern "C" void func_0015C7E0()
{
    operator_delete(D_004A124C);
    D_004A124C = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C808);
#ifdef SKIP_ASM
extern "C" void func_0015C808(int value)
{
    *(int*)((char*)D_004A124C + 0x8) = value;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C818);
#ifdef SKIP_ASM
extern char D_0045AC48[];

extern "C" void* func_0015C818(void* self)
{
    *(void**)((char*)self + 0xC) = D_0045AC48;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C830);
#ifdef SKIP_ASM
extern int* D_004A1258;
void operator_delete(int* ptr);

extern "C" void func_0015C830(void)
{
    operator_delete(D_004A1258);
    D_004A1258 = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C858);
#ifdef SKIP_ASM
extern char D_0045AC18[];

extern "C" void* func_0015C858(void* self)
{
    *(void**)((char*)self + 0x4) = D_0045AC18;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C870);
#ifdef SKIP_ASM
extern int* D_004A122C;
void operator_delete(int* ptr);

extern "C" void func_0015C870(void)
{
    operator_delete(D_004A122C);
    D_004A122C = 0;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C898);
#ifdef SKIP_ASM
extern char D_0045ABE8[];

extern "C" void* func_0015C898(void* self)
{
    *(void**)((char*)self + 0x4) = D_0045ABE8;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C8B0);
#ifdef SKIP_ASM
extern int* D_004A1254;
void operator_delete(int* ptr);

extern "C" void func_0015C8B0(void)
{
    operator_delete(D_004A1254);
    D_004A1254 = 0;
}
#endif

extern "C" void* func_0015B028(int, int);

//100%
INCLUDE_ASM("be/bedbreward", func_0015C8D8);
#ifdef SKIP_ASM
extern char D_0045ABB8[];

extern "C" void* func_0015C8D8(void* self)
{
    *(void**)((char*)self + 0x4) = D_0045ABB8;
    return self;
}
#endif

//99.38%
INCLUDE_ASM("be/bedbreward", func_0015C8F0__FPv);
#ifdef SKIP_ASM
void* func_0015C8F0(void* self)
{
    return func_0015B028(1, 0xffff);
}
#endif

extern "C" void* func_0015B028(int, int);

//99.38%
INCLUDE_ASM("be/bedbreward", func_0015C910__FPv);
#ifdef SKIP_ASM
void* func_0015C910(void* self)
{
    return func_0015B028(0, 0xffff);
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C930__FPv);
#ifdef SKIP_ASM
void* func_0015C930(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x4) = t0;
    return self;
}
#endif

//100%
INCLUDE_ASM("be/bedbreward", func_0015C940);
#ifdef SKIP_ASM
void operator_delete(int* ptr);
extern "C" void func_0015CB08(void* self);

extern "C" void func_0015C940(int* self, int flags)
{
    func_0015CB08(self);
    if (flags & 1)
    {
        operator_delete(self);
    }
}
#endif

