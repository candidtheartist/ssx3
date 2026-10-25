#include "common.h"

//100%
class cUIText;
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_E758(void* be, int kind) __asm__("cBE_getInterface__Fv");
int GetHashValue32(char*);
void cUIText_setAsciiString(cUIText* text, const char* str);
void cUIText_setUnicodeStringByID(cUIText* text, int id);
extern "C" unsigned short* func_002C2540(unsigned short* dst, char* src);
extern "C" void func_002C26D0(unsigned short* dst, unsigned short* fmt, int n);
extern "C" void func_003A0E90(cUIText* self, const unsigned short* str);
extern "C" char* func_00144C60(void* iface, int id);

struct sChalVEnt_E758 {
    short delta;
    short index;
    int (*fn)(void*, int);
};

struct sChalSlot_E758 {
    signed char type;
    signed char val;
};

extern sChalSlot_E758 D_0045AAD8[][4][5];
extern char* D_004A28A8;
extern char D_00466BB8[], D_00466BD0[], D_00466BE8[];
extern char D_00466C00[], D_00466C10[], D_00466C20[], D_00466C30[];
extern char D_00466C40[], D_00466C50[], D_00466C60[];
extern char D_00466C70[], D_00466C80[], D_00466C90[], D_00466CA8[], D_00466CB8[], D_00466CC8[];

extern "C" void setChallengeName(cUIText* text, int mountain, int peak, int idx)
{
    if (peak == 3) {
        cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466BB8));
        return;
    }
    if (peak == 2) {
        if (idx == 0) cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466BD0));
        else cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466BE8));
        return;
    }
    void* iface = cBE_getInterface_E758(cBE_getBE(), 0);
    int type = D_0045AAD8[mountain][peak][idx].type;
    int val = D_0045AAD8[mountain][peak][idx].val;
    if (type == 4) {
        unsigned short out[200];
        unsigned short buf[32];
        if (mountain == 0) func_002C2540(buf, D_00466C00);
        else if (mountain == 1) func_002C2540(buf, D_00466C10);
        else if (mountain == 2) func_002C2540(buf, D_00466C20);
        char* obj = *(char**)(D_004A28A8 + 0x8C);
        sChalVEnt_E758* vt = *(sChalVEnt_E758**)(obj + 4);
        int n = vt[4].fn(obj + vt[4].delta, GetHashValue32(D_00466C30));
        func_002C26D0(out, buf, n);
        func_003A0E90(text, out);
    } else if (type == 5) {
        if (mountain == 0) cUIText_setAsciiString(text, D_00466C40);
        else if (mountain == 1) cUIText_setAsciiString(text, D_00466C50);
        else if (mountain == 2) cUIText_setAsciiString(text, D_00466C60);
    } else if (type == 6) {
        cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466C70));
    } else if (type == 7) {
        cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466C80));
    } else if (type == 8) {
        cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466C90));
    } else if (type == 9) {
        cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466CA8));
    } else if (type == 10) {
        cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466CB8));
    } else if (type == 11) {
        cUIText_setUnicodeStringByID(text, GetHashValue32(D_00466CC8));
    } else {
        cUIText_setAsciiString(text, func_00144C60(iface, val));
    }
}

//100%
struct sReq_CE758
{
    signed char type;
    signed char track;
};
extern sReq_CE758 D_0045AAD8_CE758[][4][5] __asm__("D_0045AAD8");
extern "C" void func_002C26D0_CE758(void* dst, void* fmt, ...) __asm__("func_002C26D0");
struct sVEntry_CE758 {
    short delta;
    short index;
    int (*fn)(void*, int);
};
static inline int Loc_CE758(char* key)
{
    char* obj = *(char**)((char*)D_004A28A8 + 0x8C);
    sVEntry_CE758* vt = *(sVEntry_CE758**)(obj + 4);
    return vt[4].fn(obj + vt[4].delta, GetHashValue32(key));
}
void* cBE_getInterface_CE758(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBEEconInterface_getTotalMoneyEarned(void* econ, int a, int b);
extern "C" const char* func_00198AF0_price(int price) __asm__("func_00198AF0");
extern "C" int func_002C27C0(void* buf, const char* fmt, ...);
extern "C" int sprintf(char* buf, const char* fmt, ...);
// PORT: SN soft-float float->double helper called by name
extern "C" double func_00413AF8(float f);
extern "C" int func_00153390(void* iface, int peak);
extern "C" int func_00153688(void* iface, int a, int b, int peak);
extern "C" int func_00154368(void* iface, int peak);
extern "C" int func_001544D0(void* iface, int a, int b, int peak);
extern "C" unsigned int func_00158960(void* self, int b, int c, int d, int e);
extern char D_004A1EE0[];
extern char D_00466CE0[];
extern char D_00466CF8[];
extern char D_00466D10[];
extern char D_00466D28[];
extern char D_00466D38[];
extern char D_00466D50[];

static inline unsigned int udiv_CE758(unsigned int a, unsigned int b)
{
    return a / b;
}

static inline unsigned int umod_CE758(unsigned int a, unsigned int b)
{
    return a % b;
}

extern "C" void setChallengeStats(cUIText* text, int a1, int a2, int peak, int kind, int idx)
{
    unsigned short buf[100];
    char num[200];
    void* reward = cBE_getInterface_CE758(cBE_getBE(), 0xD);
    if (kind == 3) {
        int money = cBEEconInterface_getTotalMoneyEarned(cBE_getInterface_CE758(cBE_getBE(), 0xB), a1, a2);
        int fmt = Loc_CE758(D_00466CE0);
        func_002C27C0(num, D_004A1EE0, func_00198AF0_price(money));
        if (fmt != 0) {
            func_002C26D0_CE758(buf, (void*)fmt, num);
            func_003A0E90(text, buf);
        }
    } else if (kind == 2) {
        void* iface = cBE_getInterface_CE758(cBE_getBE(), 0xA);
        if (idx == 0) {
            int t = func_00153390(iface, peak);
            int v = func_00153688(iface, a1, a2, peak);
            int fmt = Loc_CE758(D_00466CF8);
            if (fmt != 0) {
                func_002C26D0_CE758(buf, (void*)fmt, v, t);
                func_003A0E90(text, buf);
            }
        } else {
            int t = func_00154368(iface, peak);
            int v = func_001544D0(iface, a1, a2, peak);
            int fmt = Loc_CE758(D_00466D10);
            if (fmt != 0) {
                func_002C26D0_CE758(buf, (void*)fmt, v, t);
                func_003A0E90(text, buf);
            }
        }
    } else if (kind == 0) {
        int track = D_0045AAD8_CE758[peak][kind][idx].track;
        int type = D_0045AAD8_CE758[peak][kind][idx].type;
        unsigned int time = func_00158960(reward, a1, a2, type, track);
        unsigned int min = udiv_CE758(time, 60);
        unsigned int sec = umod_CE758(time, 60);
        sprintf(num, D_00466D28, func_00413AF8((float)(int)min), func_00413AF8((float)(int)sec));
        int fmt = Loc_CE758(D_00466D38);
        if (fmt != 0) {
            func_002C26D0_CE758(buf, (void*)fmt, num);
            func_003A0E90(text, buf);
        }
    } else if (kind == 1) {
        int track = D_0045AAD8_CE758[peak][kind][idx].track;
        int type = D_0045AAD8_CE758[peak][kind][idx].type;
        int v = func_00158960(reward, a1, a2, type, track);
        int fmt = Loc_CE758(D_00466D50);
        if (fmt != 0) {
            func_002C26D0_CE758(buf, (void*)fmt, v);
            func_003A0E90(text, buf);
        }
    }
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
void* cBE_getInterface_ED90(void* be, int kind) __asm__("cBE_getInterface__Fv");
signed char cBERewardInterface_getTrackMedal(void* self, int a, int b, int track, int kind);
extern "C" int cBERewardInterface_getEarningsMedal(void* self, int a, int b, int kind);
extern "C" int cBERewardInterface_GetCollectibleTier(void* self, int a, int b, int kind);
extern "C" int cBERewardInterface_GetMissionTier(void* self, int a, int b, int kind);
struct sReq_ED90
{
    signed char track;
    signed char kind;
};
extern sReq_ED90 D_0045AAD8_ED90[][4][5] __asm__("D_0045AAD8");

extern "C" void func_001CED90(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    void* r = cBE_getInterface_ED90(cBE_getBE(), 0xD);
    if (arg3 == 2)
    {
        if (arg4 == 0)
        {
            cBERewardInterface_GetCollectibleTier(r, arg0, arg1, arg2);
            return;
        }
        cBERewardInterface_GetMissionTier(r, arg0, arg1, arg2);
        return;
    }
    if (arg3 != 3)
    {
        int kind = D_0045AAD8_ED90[arg2][arg3][arg4].kind;
        int track = D_0045AAD8_ED90[arg2][arg3][arg4].track;
        cBERewardInterface_getTrackMedal(r, arg0, arg1, track, kind);
        return;
    }
    cBERewardInterface_getEarningsMedal(r, arg0, arg1, arg2);
}

//100%
extern "C" void* func_0039E2A0(void* self, void* engine);
extern "C" unsigned char func_001A1CD0(void* self, signed char a1);
extern "C" int func_00146D98(void* self, int index);
extern "C" int func_00150928(void* self, int a, int b);
int cBENewPlayerInterface_getPlayerCharID(void* self, int index);
int cBELibrary_getRiderIndex(int);
extern void* D_0046A3C8[];
struct sVE_CEEA0
{
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void* func_001CEEA0(void* self, void* engine, signed char idx, int a4, int a5)
{
    char* s = (char*)self;
    func_0039E2A0(self, engine);
    *(int*)(s + 0xC) = 0x2F;
    *(void***)(s + 0x8) = D_0046A3C8;
    *(signed char*)(s + 0x44) = idx;
    *(unsigned char*)(s + 0x15) = func_001A1CD0(**(void***)(s + 0x10), idx);
    *(int*)(s + 0x4C) = a5;
    *(int*)(s + 0x58) = 4;
    *(int*)(s + 0x5C) = 8;
    *(int*)(s + 0x8EC) = -2;
    *(int*)(s + 0x48) = 0;
    *(int*)(s + 0x64) = 0;
    *(int*)(s + 0x8F4) = 0;
    *(int*)(s + 0x8F8) = 0;
    *(int*)(s + 0x70) = 0;
    *(int*)(s + 0x74) = 0;
    *(int*)(s + 0x8FC) = 0;
    *(int*)(s + 0x900) = 0;
    *(int*)(s + 0x904) = 0;
    *(int*)(s + 0x908) = 0;
    *(int*)(s + 0x90C) = 0;
    *(int*)(s + 0x910) = 0;
    *(int*)(s + 0x914) = 0;
    *(int*)(s + 0x918) = 0;
    *(int*)(s + 0x91C) = 0;
    *(int*)(s + 0x920) = 0;
    *(int*)(s + 0x68) = 0;
    *(int*)(s + 0x6C) = 0;
    *(int*)(s + 0x78) = 0;
    int(*ta)[8] = (int(*)[8])(s + 0x924);
    int(*tb)[8] = (int(*)[8])(s + 0x9A4);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ta[i][j] = 0;
            tb[i][j] = 0;
        }
    }
    char* pi = (char*)cBE_getInterface_ED90(cBE_getBE(), 1);
    *(int*)(s + 0x50) = cBENewPlayerInterface_getPlayerCharID(pi, *(signed char*)(s + 0x44));
    if (a4 != 0)
    {
        switch (func_00146D98(pi, cBELibrary_getRiderIndex(*(signed char*)(s + 0x44))))
        {
        case 0x11:
            *(int*)(s + 0x8F0) = 1;
            break;
        case 0x12:
            *(int*)(s + 0x8F0) = 1;
            break;
        case 0x13:
            *(int*)(s + 0x8F0) = 2;
            break;
        case 0x14:
            *(int*)(s + 0x8F0) = 2;
            break;
        case 0x15:
            *(int*)(s + 0x8F0) = 3;
            break;
        default:
            *(int*)(s + 0x8F0) = 1;
            break;
        }
    }
    else
    {
        *(int*)(s + 0x8F0) = -1;
    }
    sVE_CEEA0* e = (sVE_CEEA0*)(*(char**)(pi + 0xC) + 0x10);
    e->fn(pi + e->delta);
    *(int*)(s + 0x54) = func_00150928(cBE_getInterface_ED90(cBE_getBE(), 0xB), *(signed char*)(s + 0x44), *(int*)(s + 0x50));
    return self;
}
