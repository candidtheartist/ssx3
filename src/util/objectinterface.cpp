#include "common.h"

struct cObjectInterface {
    char pad_0x00[0x84];
    struct cObjectInterface_Impl* mImpl; // offset 0x84
};

struct cObjectInterface_Impl {
    char pad_0x00[0x88];
    void* mInstanceMan; // offset 0x88
};

extern cObjectInterface* D_004A28A8;

//100%
void* cObjectInterface_getInstanceMan()
{
    return D_004A28A8->mImpl->mInstanceMan;
}

extern "C" void* func_002D9C00(void* self);

//100%
void* func_002D1CF0(void* self)
{
    return func_002D9C00(self);
}

INCLUDE_ASM("util/objectinterface", func_002D1D10);

//100%
// VU0 microprogram entry (micro-memory address 0x828)
extern char D_828[];

struct sQ128 { float v[4]; } __attribute__((aligned(16)));

// PORT: PS2-only VU0 microprogram call (ctc2/vcallmsr/cfc2); the PC port needs a C version.
extern "C" int func_002D2058(sQ128* v)
{
    char* inst = (char*)*(void**)((char*)D_004A28A8->mImpl + 0x8C);
    int mask = *(int*)(inst + 0x110);
    for (int i = 0; i < *(int*)(inst + 0x10C); i++) {
        int bit = 1 << i;
        if (mask & bit) {
            sQ128* m = (sQ128*)(*(char**)(inst + 8 + i * 8) + 0x50);
            int r;
            __asm__ __volatile__(
                ".set push\n"
                ".set noreorder\n"
                "lqc2      $vf1, %1\n"
                "lqc2      $vf2, %2\n"
                "lqc2      $vf3, %3\n"
                "lqc2      $vf4, %4\n"
                "lqc2      $vf5, %5\n"
                "lqc2      $vf6, %6\n"
                "ctc2.ni   %7, $vi27\n"
                "vnop\n"
                "vnop\n"
                "vcallmsr  $vi27\n"
                "cfc2.i    %0, $vi1\n"
                ".set pop\n"
                : "=&r"(r)
                : "m"(m[0]), "m"(m[1]), "m"(m[2]), "m"(m[3]), "m"(m[4]), "m"(*v), "r"((int)D_828 >> 3)
                : "memory");
            int ok = r == 1;
            if (ok) return 1;
        }
    }
    return 0;
}

extern void* D_004A3A00;

// The object interface singleton
extern "C" void* func_002D20F8()
{
    return D_004A3A00;
}

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* SSXStatsMan_ctor(void* p);
extern char D_00486758[];

extern "C" void* func_002D2100()
{
    return SSXStatsMan_ctor(cMemMan_alloc(1, D_00486758, 0, 0));
}

extern "C" void func_002D2138()
{
}

extern "C" void func_002D2140()
{
}

extern sQ128 D_004FF120;

extern "C" sQ128 func_002D2148()
{
    return D_004FF120;
}

extern "C" sQ128 func_002D2160()
{
    return D_004FF120;
}

extern "C" sQ128 func_002D2178()
{
    return D_004FF120;
}

extern "C" float func_002D2190()
{
    return 0.0f;
}

extern "C" float func_002D21A0()
{
    return 0.0f;
}

//100%
void func_002D21B0(void* self)
{
}

//100%
void func_002D21B8(void* self)
{
}

//100%
extern void* D_004A3A00;

extern "C" void* SSXStatsMan_ctor(void* p)
{
    D_004A3A00 = p;
    return p;
}


// Writes a float to the stream at *cursor, little-endian; returns its size
extern "C" int func_002D21D0(char** cursor, float value)
{
    union { float f; unsigned int i; } u;
    char* p = *cursor;
    u.f = value;
    p[0] = u.i;
    p[1] = u.i >> 8;
    p[2] = u.i >> 16;
    p[3] = u.i >> 24;
    *cursor += 4;
    return 4;
}

extern "C" int Serialize_WriteU32(char** cursor, unsigned int value)
{
    char* p = *cursor;
    p[0] = value;
    p[1] = value >> 8;
    p[2] = value >> 16;
    p[3] = value >> 24;
    *cursor += 4;
    return 4;
}

extern "C" int func_002D2248(char** cursor, float* v)
{
    int i;
    for (i = 2; i >= 0; i--)
        func_002D21D0(cursor, *v++);
    return 12;
}

extern "C" int func_002D22A8(char** cursor, float* v)
{
    int i;
    for (i = 3; i >= 0; i--)
        func_002D21D0(cursor, *v++);
    return 16;
}

extern "C" int func_002D2308(char** cursor, float* v)
{
    int i;
    for (i = 15; i >= 0; i--)
        func_002D21D0(cursor, *v++);
    return 64;
}

// Writes a quaternion, w first
extern "C" int func_002D2368(char** cursor, float* q)
{
    func_002D21D0(cursor, q[3]);
    func_002D21D0(cursor, q[0]);
    func_002D21D0(cursor, q[1]);
    func_002D21D0(cursor, q[2]);
    return 16;
}

extern "C" int func_002D23C8(char** cursor, char value)
{
    **cursor = value;
    (*cursor)++;
    return 1;
}

extern "C" unsigned int strlen(const char*);
extern "C" int func_002D23E8(char** cursor, const char* s)
{
    unsigned int i;
    const char* p = s;
    int total = 0;
    for (i = 0; i < strlen(s); i++) {
        total += func_002D23C8(cursor, *p++);
    }
    func_002D23C8(cursor, 0);
    return total + 1;
}

struct sOIStr_2478 { unsigned int n; char* s; };
extern "C" int func_002D2478(char** cursor, sOIStr_2478** str)
{
    int total = Serialize_WriteU32(cursor, (*str)->n);
    for (unsigned int i = 0; i < (*str)->n; i++) {
        total += func_002D23C8(cursor, (*str)->s[i]);
    }
    return total;
}
