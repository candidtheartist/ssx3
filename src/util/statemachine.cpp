#include "common.h"

//100%
extern "C" int func_002C27C0(char* buf, const char* fmt, ...);
extern "C" void func_002C25B8(char* dst, const char* src, int size);
extern char D_00486500[];
extern char D_00486510[];
extern char D_00486528[];

extern "C" void cConsoleConfig_setTimeString(void* self, char* dst, int size, int hour, int min, int sec, int mode)
{
    char buf[0x40];
    switch (mode) {
    case 0:
        func_002C27C0(buf, D_00486500, hour, min, sec);
        break;
    case 1:
        if (hour < 12) {
            func_002C27C0(buf, D_00486510, hour, min, sec);
        } else {
            func_002C27C0(buf, D_00486528, hour % 13 - 12, min, sec);
        }
        break;
    }
    func_002C25B8(dst, buf, size);
}

extern char D_00486540[];
extern char D_00486550[];

extern "C" void func_002C7038(void* self, char* dst, int size, int day, int month, int year, int mode)
{
    char buf[0x40];
    switch (mode) {
    case 0:
        func_002C27C0(buf, D_00486540, year, month, day);
        break;
    case 1:
        func_002C27C0(buf, D_00486550, month, day, year);
        break;
    case 2:
        func_002C27C0(buf, D_00486550, day, month, year);
        break;
    }
    func_002C25B8(dst, buf, size);
}

extern "C" void func_002C73C0(void* self);

extern "C" void func_002C7100(void* self, int* a, int* b, int* c)
{
    func_002C73C0(self);
    *a = *(int*)((char*)self + 0x8);
    *b = *(int*)((char*)self + 0xC);
    *c = *(int*)((char*)self + 0x10);
}

extern "C" void func_002C7160(void* self, int* a, int* b, int* c)
{
    func_002C73C0(self);
    *a = *(int*)((char*)self + 0x1C);
    *b = *(int*)((char*)self + 0x18);
    *c = *(int*)((char*)self + 0x14);
}

extern "C" int func_002C71C0(void* self, int year)
{
    int r = 0;
    if ((year & 3) == 0) {
        r = 1;
        if (year % 100 == 0) {
            r = year % 400 == 0;
        }
    }
    return r;
}

extern "C" int func_002C7208(void* self, int month, int year)
{
    if (month == 2) {
        if (func_002C71C0(self, year)) return 29;
        return 28;
    }
    if (month >= 8) month++;
    int r = 30;
    if (month & 1) r = 31;
    return r;
}

extern "C" void func_002C7260(void* self, int* day, int* month, int* year, int n)
{
    while (n > 0) {
        int dim = func_002C7208(self, *month, *year);
        int d = *day;
        if (dim < d + n) {
            *day = 1;
            n -= dim - d + 1;
            (*month)++;
            if (*month >= 13) {
                *month = 1;
                (*year)++;
            }
        } else {
            *day = d + n;
            n = 0;
        }
    }
}

extern "C" int func_002C7328(void* self, int* sec, int* min, int* hour, int n)
{
    int t = *hour * 3600 + *min * 60 + *sec + n;
    int d = t / 86400;
    t = t % 86400;
    *hour = (t / 3600) % 24;
    *min = (t / 60) % 60;
    *sec = t % 60;
    return d;
}

extern "C" int func_002C7328(void* self, int* a, int* b, int* c, int n);
extern "C" void func_002C7260(void* self, int* a, int* b, int* c, int n);
extern void* D_004A28A8;

extern "C" void func_002C73C0(void* self)
{
    char* s = (char*)self;
    int now = *(int*)((char*)D_004A28A8 + 0x18);
    int n = (now - *(int*)(s + 0x20)) / *(int*)((char*)D_004A28A8 + 0x10);
    if (n != 0) {
        *(int*)(s + 0x20) = now;
        n = func_002C7328(self, (int*)(s + 0x10), (int*)(s + 0xC), (int*)(s + 0x8), n);
        if (n != 0) {
            func_002C7260(self, (int*)(s + 0x1C), (int*)(s + 0x18), (int*)(s + 0x14), n);
        }
    }
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cPS2ConsoleConfig_ctor(void* self);
extern char D_00486560[];

extern "C" void* cPS2ConsoleConfig_Create(void)
{
    return cPS2ConsoleConfig_ctor(cMemMan_alloc(0x38, D_00486560, 0, 0));
}

//100%
extern "C" int func_0040BAA8(void);
extern "C" int func_0040B9E8(void);
extern "C" int func_0040BB38(void);
extern "C" int func_0040BC08(void);
extern "C" int func_00402520(unsigned char* clock);
extern "C" void func_0040BFE0(unsigned char* clock);
extern char D_00486798[];
extern void* D_004A28A8;

extern "C" void* cPS2ConsoleConfig_ctor(void* self_)
{
    int* self = (int*)self_;
    unsigned char clock[8];
    self[9] = 0;
    *(char**)&self[13] = D_00486798;
    int r = func_0040BAA8();
    switch (r) {
    case 0:
        self[10] = 1;
        break;
    case 1:
        self[10] = 0;
        break;
    default:
        self[10] = 0;
        break;
    }
    self[11] = 1;
    switch (func_0040B9E8()) {
    case 0:
        self[12] = 0;
        break;
    case 1:
        self[12] = 1;
        break;
    case 2:
        self[12] = 2;
        break;
    case 3:
        self[12] = 3;
        break;
    case 4:
        self[12] = 4;
        break;
    case 5:
        self[12] = 5;
        break;
    case 6:
        self[12] = 6;
        break;
    case 7:
        self[12] = 7;
        break;
    default:
        self[12] = 1;
        break;
    }
    r = func_0040BB38();
    switch (r) {
    case 0:
        self[0] = 0;
        break;
    case 1:
        self[0] = r;
        break;
    case 2:
        self[0] = r;
        break;
    default:
        self[0] = 0;
        break;
    }
    r = func_0040BC08();
    switch (r) {
    case 0:
        self[1] = 0;
        break;
    case 1:
        self[1] = 1;
        break;
    default:
        self[1] = 0;
        break;
    }
    if (func_00402520(clock) != 0) {
        func_0040BFE0(clock);
        self[2] = (clock[3] & 0xF) + (clock[3] >> 4) * 10;
        self[3] = (clock[2] & 0xF) + (clock[2] >> 4) * 10;
        self[4] = (clock[1] & 0xF) + (clock[1] >> 4) * 10;
        self[5] = (clock[7] & 0xF) + (clock[7] >> 4) * 10 + 2000;
        self[6] = (clock[6] & 0xF) + (clock[6] >> 4) * 10;
        self[7] = (clock[5] & 0xF) + (clock[5] >> 4) * 10;
    } else {
        self[5] = 2003;
        self[6] = 10;
        self[7] = 14;
        self[2] = 0;
        self[3] = 0;
        self[4] = 0;
    }
    self[8] = *(int*)((char*)D_004A28A8 + 0x18);
    return self;
}

INCLUDE_ASM("util/statemachine", func_002C76C0);

