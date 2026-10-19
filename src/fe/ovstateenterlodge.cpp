#include "common.h"

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void cUIScreen_playFrame(void* screen, int a1, int a2);
extern "C" void cOVStateManager_addPDATemplate();
extern "C" void func_0020A380(void* self);
extern char D_0046F4D0[];

extern "C" void cOVState_ENTERLODGE_onCreateScreen(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0046F4D0), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    cOVStateManager_addPDATemplate();
    func_0020A380(self);
}

//100%
int GetHashValue32(char* str);
extern char D_004A23E0[];
extern char D_004A23E8[];
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void func_0039E4C0(void* self, void* a1);

extern "C" void func_001F7210(void* self, void* a1)
{
    void* obj = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A23E0));
    if (obj != 0) {
        *(int*)((char*)obj + 0x18) = 0;
    }
    obj = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A23E8));
    if (obj != 0) {
        *(int*)((char*)obj + 0x18) = 1;
    }
    func_0039E4C0(self, a1);
}

extern "C" void* func_0020A430(void*);

//100%
void* func_001F7298(void* self)
{
    *(int*)((char*)self + 0x50) = 0;
    return func_0020A430(self);
}

//100%
// Key filter: keys 8 and 9 return 0x100, every other key 0x101.
extern "C" int func_001F72B8(void* self, int a1, unsigned int key)
{
    int r = 0x101;
    if (key < 10) {
        if (key < 8) {
            r = 0x101;
        } else {
            return 0x100;
        }
    }
    return r;
}

//100%
extern void* D_004A28A8;
extern int D_004A19C4;
extern "C" void cGame_exit(void* game, int a);
extern "C" void func_0039F190(void*, int);
struct sFlag001F72E0 {
    int f0;
    int f4;
    int active;
};
struct sGame001F72E0 {
    char pad[0x200];
    sFlag001F72E0* flag;
};
struct sSelf001F72E0 {
    char pad[0x10];
    char* mgr;
    char pad14[0x40];
    int done;
};

extern "C" void func_001F72E0(sSelf001F72E0* self, void* widget, int msg)
{
    if (widget != 0) {
        switch (msg) {
        case 5:
            (*(sGame001F72E0**)((char*)D_004A28A8 + 0x84))->flag->active = 1;
            switch (*(int*)((char*)widget + 0x18)) {
            case 0:
                {
                    void* game = *(void**)((char*)D_004A28A8 + 0x84);
                    D_004A19C4 = 0x27;
                    cGame_exit(game, 0);
                }
                break;
            case 1:
                self->done = 1;
                func_0039F190(self->mgr + 0x18, 1);
                break;
            }
            break;
        case 6:
            self->done = 1;
            (*(sGame001F72E0**)((char*)D_004A28A8 + 0x84))->flag->active = 1;
            func_0039F190(self->mgr + 0x18, 1);
            break;
        }
    }
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void cUIScreen_playFrame(void* screen, int a1, int a2);
extern "C" void func_0020A380(void* self);
extern char D_0046F4E0[];

extern "C" void cOVState_BIGCHALLENGE_START_onCreateScreen(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0046F4E0), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    func_0020A380(self);
}

//100%
int GetHashValue32(char* str);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void* func_00153C88(void* iface, int id);
extern "C" void* func_00153D28(void* iface, int id);
extern "C" void func_003A0E90(void* text, void* str);
extern "C" void func_003A0D00(void* text, void* str);
extern char D_0046F4F0[];
extern char D_004A23F0[];

extern "C" int cOVState_BIGCHALLENGE_START_onGainTransition(void* self, int gained)
{
    if (gained) {
        void* iface = cBE_getInterface_Fv(cBE_getBE(), 0xA);
        void* obj = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_0046F4F0));
        if (obj) {
            func_003A0E90(obj, func_00153C88(iface, *(int*)((char*)self + 0x9C)));
        }
        obj = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A23F0));
        if (obj) {
            func_003A0D00(obj, func_00153D28(iface, *(int*)((char*)self + 0x9C)));
        }
    }
    return 0;
}

//100%
int GetHashValue32(char* str);
extern char D_004A23E0[];
extern char D_004A23E8[];

extern "C" void func_001F74E0(void* self, void* item)
{
    int id = *(int*)((char*)item + 0x38);
    if (id == GetHashValue32(D_004A23E0)) {
        *(int*)((char*)item + 0x18) = 0;
    } else {
        int id2 = *(int*)((char*)item + 0x38);
        if (id2 == GetHashValue32(D_004A23E8)) {
            *(int*)((char*)item + 0x18) = 1;
        }
    }
}

//100%
extern void* D_004A3DD8;
extern "C" int* func_0030C820(void* list);

extern "C" void func_001F7548(void* self)
{
    int* p = func_0030C820((char*)D_004A3DD8 + 0x1C4);
    if (p != 0) {
        *(int*)((char*)self + 0x9C) = *p;
    } else {
        *(int*)((char*)self + 0x9C) = *(int*)((char*)D_004A3DD8 + 0x2A0);
    }
}

//100%
extern "C" int func_001F7590(void* self, int a1, int a2)
{
    return a2 == 6 ? 0x101 : 0;
}

//100%
extern "C" void* func_0028B180();
void func_0029D6D0(void* self);
extern "C" void func_0030B540(void* self);
extern "C" void func_0030B658(void* self);
extern "C" void func_0030B6F8(void* self);
extern "C" int func_0030B8C0(void* self);
extern void* D_004A3DD8;
extern int D_004A26FC;
extern int D_004A2A54;
extern int D_004A2A50;
extern int D_005366E8[];
extern int D_004428F0[];

struct sMgr_75A0 {
    char pad[0x2A0];
    int f2A0;
};

extern "C" void func_001F75A0(void* self, void* item, int msg)
{
    if (item == 0) {
        return;
    }
    switch (msg) {
    case 5:
        if (*(int*)((char*)item + 0x18) == 0) {
            if (func_0030B8C0(D_004A3DD8) != 0) {
                func_0030B6F8(D_004A3DD8);
            } else {
                ((sMgr_75A0*)D_004A3DD8)->f2A0 = *(int*)((char*)self + 0x9C);
                func_0030B540(D_004A3DD8);
            }
            D_004A26FC = 3;
            D_004A2A50 = D_004428F0[D_005366E8[--D_004A2A54]];
            func_0029D6D0(func_0028B180());
            break;
        }
    case 6:
        ((sMgr_75A0*)D_004A3DD8)->f2A0 = *(int*)((char*)self + 0x9C);
        func_0030B658(D_004A3DD8);
        D_004A26FC = 3;
        D_004A2A50 = D_004428F0[D_005366E8[--D_004A2A54]];
        break;
    }
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void cUIScreen_playFrame(void* screen, int a1, int a2);
extern "C" void func_0020A380(void* self);
extern char D_0046F500[];

extern "C" void func_001F76B8(void* self)
{
    void* engine;
    void* screen;
    *(int*)((char*)self + 0xC) = GetHashValue32(D_0046F500);
    engine = *(void**)((char*)self + 0x10);
    screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0046F500), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    func_0020A380(self);
}

//100%
extern void* D_004A3DD8;
extern "C" int* func_0030C820(void* list);

extern "C" void func_001F7738(void* self)
{
    *(int*)((char*)self + 0x9C) = *func_0030C820((char*)D_004A3DD8 + 0x1C4);
}

//100%
int GetHashValue32(char* str);
extern char D_004A23E0[];
extern char D_004A23E8[];
extern char D_004A23F8[];

extern "C" void func_001F7770(void* self, void* item)
{
    int id = *(int*)((char*)item + 0x38);
    if (id == GetHashValue32(D_004A23E0)) {
        *(int*)((char*)item + 0x18) = 0;
    } else {
        int id2 = *(int*)((char*)item + 0x38);
        if (id2 == GetHashValue32(D_004A23E8)) {
            *(int*)((char*)item + 0x18) = 1;
        } else {
            int id3 = *(int*)((char*)item + 0x38);
            if (id3 == GetHashValue32(D_004A23F8)) {
                *(int*)((char*)item + 0x18) = 2;
            }
        }
    }
}

//100%
extern "C" int func_001F77F0(void* self, int a1, int a2)
{
    return a2 == 6 ? 0x101 : 0;
}

//100%
extern "C" void func_0020AB50(int id);
// PORT: func_0039F190 returns the last node; the unit declares it void.
void* func_0039F190_r(void* self, int a1) __asm__("func_0039F190");
struct cUIScreen;
int cUIScreen_getFrameByLabel(cUIScreen* screen, int hash);
extern char D_0046E050[];

extern "C" void func_001F7800(void* self, void* item, int msg)
{
    if (item == 0) {
        return;
    }
    switch (msg) {
    case 5: {
        int v = *(int*)((char*)item + 0x18);
        if (v == 0) {
            ((sMgr_75A0*)D_004A3DD8)->f2A0 = *(int*)((char*)self + 0x9C);
            func_0030B6F8(D_004A3DD8);
            func_0039F190_r((char*)*(void**)((char*)self + 0x10) + 0x18, 1);
            D_004A2A50 = D_004428F0[D_005366E8[--D_004A2A54]];
            func_0029D6D0(func_0028B180());
            return;
        }
        if (v == 2) {
            func_0020AB50(0x1D);
            return;
        }
        break;
    }
    case 6: {
        int frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0x40), GetHashValue32(D_0046E050));
        if (frame != 0xFFFF) {
            cUIScreen_playFrame(*(void**)((char*)self + 0x40), frame & 0xFFFF, 1);
        }
        break;
    }
    default:
        return;
    }
    func_0030B658(D_004A3DD8);
    func_0039F190_r((char*)*(void**)((char*)self + 0x10) + 0x18, 1);
    D_004A2A50 = D_004428F0[D_005366E8[--D_004A2A54]];
}

struct cUIText;
void cUIText_setAsciiString(cUIText* self, const char* str);
extern "C" void* cBE_getBE();
void* cBE_getInterface_7958(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_002C2540(unsigned short* dst, const char* src);
extern "C" void func_002C26D0(unsigned short* dst, const unsigned short* fmt, ...);
extern "C" unsigned short* func_002C2508(unsigned short* dst, unsigned short* src);
extern "C" unsigned short* func_001FD190(int which);
extern "C" int func_00144BF0(void* iface);
extern "C" void cUIState_showObjSafe(void* self, char* name);
extern "C" void cUIState_hideObjSafe(void* self, char* name);
extern "C" const char* func_00155208(void* self, int i);
extern "C" const char* func_00155190(void* self, int i);
extern "C" int func_00155130(void* self, int i);
extern "C" char* func_0020A1A8(int secs);
extern "C" void func_00294F78(void* self, int a1);
extern "C" void* func_0028B180();
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern int D_004A2700;
extern char D_0046F510[];
extern char D_0046E378[];
extern char D_0046F520[];
extern char D_0046F530[];
extern char D_0046F540[];
extern char D_0046F550[];
extern char D_0046E548[];
extern char D_0046E398[];
extern char D_0046E3A8[];
extern char D_0046E3C0[];
extern char D_0046E9E8[];
extern char D_0046E9F8[];
extern char D_004A2400[];
extern char D_004A2408[];
extern char D_004A2410[];
extern char D_004A2418[];
extern char D_004A2420[];
extern char D_004A2090[];
extern char D_004A2138[];
extern char D_004A2428[];
extern char D_004A2430[];
extern char D_004A2438[];

struct sRace_7958 {
    char pad0[0x48];
    signed char mode48;
    signed char flag49;
    signed char sub4A;
};
extern sRace_7958 D_00535BC8_7958 __asm__("D_00535BC8");

struct sVEs_7958 { short delta; short index; unsigned short* (*fn)(void*, int); };

static inline unsigned short* Loc_7958(char* s)
{
    char* o = *(char**)((char*)D_004A28A8 + 0x8C);
    sVEs_7958* vt = *(sVEs_7958**)(o + 4);
    return vt[4].fn(o + vt[4].delta, GetHashValue32(s));
}

extern "C" void func_001F7958(char* self)
{
    char name[0x40];
    char buf[0x40];
    unsigned short title[0x68];
    unsigned short fmt[0x10];
    *(int*)(self + 0xA0) = 0;
    void* engine = *(void**)(self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0046F510), 0);
    *(void**)(self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    engine = *(void**)(self + 0x10);
    screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0046E378), 0);
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    int timed = 1;
    func_0020A380(self);
    void* race = cBE_getInterface_7958(cBE_getBE(), 0);
    void* sc = cBE_getInterface_7958(cBE_getBE(), 8);
    unsigned short* text;
    int sub = D_00535BC8_7958.sub4A;
    int mode = D_00535BC8_7958.mode48;
    if (sub != 5) {
        if (sub >= 5) {
            if (sub < 12) {
                func_002C2508(title, func_001FD190(sub));
                text = title;
                goto done;
            }
        }
    } else {
        func_002C2540(fmt, D_0046F520);
        func_002C26D0(title, fmt, func_00144BF0(race));
        text = title;
        goto done;
    }
    {
        unsigned short* str = 0;
        switch (mode) {
        case 0:
        case 5:
            str = Loc_7958(D_0046E548);
            break;
        case 1:
            str = Loc_7958(D_0046E398);
            break;
        case 2:
            str = Loc_7958(D_0046E3A8);
            break;
        case 3:
            str = Loc_7958(D_0046E3C0);
            break;
        case 4:
            break;
        }
        func_002C2540(fmt, D_004A2400);
        func_002C26D0(title, fmt, func_00144BF0(race), str);
        text = title;
    }
done:
    func_003A0E90(cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_0046F530)), text);
    if (D_00535BC8_7958.mode48 == 0 || D_00535BC8_7958.mode48 == 5) {
        cUIState_showObjSafe(self, D_004A2408);
        cUIState_hideObjSafe(self, D_004A2410);
        cUIState_showObjSafe(self, D_0046F540);
        cUIState_hideObjSafe(self, D_0046F550);
        cUIState_showObjSafe(self, D_0046E9F8);
        cUIState_hideObjSafe(self, D_0046E9E8);
    } else {
        cUIState_hideObjSafe(self, D_004A2408);
        cUIState_showObjSafe(self, D_004A2410);
        cUIState_hideObjSafe(self, D_0046F540);
        cUIState_showObjSafe(self, D_0046F550);
        cUIState_hideObjSafe(self, D_0046E9F8);
        cUIState_showObjSafe(self, D_0046E9E8);
        timed = 0;
    }
    cUIState_showObjSafe(self, D_004A2418);
    cUIState_showObjSafe(self, D_004A2420);
    cUIState_showObjSafe(self, D_004A2090);
    if (D_004A2700 != 0) {
        cUIState_hideObjSafe(self, D_0046E9F8);
        cUIState_hideObjSafe(self, D_0046E9E8);
    }
    int i;
    for (i = 1; i < 6; i++) {
        sprintf(name, D_004A2428, i);
        cUIText* t = (cUIText*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(name));
        cUIText_setAsciiString(t, func_00155208(sc, i - 1));
        sprintf(name, D_004A2430, i);
        t = (cUIText*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(name));
        cUIText_setAsciiString(t, func_00155190(sc, i - 1));
        sprintf(name, D_004A2438, i);
        t = (cUIText*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(name));
        if (timed == 1) {
            sprintf(buf, func_0020A1A8(func_00155130(sc, i - 1)));
        } else {
            sprintf(buf, D_004A2138, func_00155130(sc, i - 1));
        }
        cUIText_setAsciiString(t, buf);
    }
    func_00294F78(func_0028B180(), 0xE);
}


//100%
struct cUIText;
int GetHashValue32(char* str);
void cUIText_setUnicodeStringByID(cUIText* self, int id);
extern char D_0046F578[];
extern char D_0046F588[];
extern char D_0046F598[];
extern char D_0046F5A8[];
extern int D_004A2700;

static inline int isHashTOPTIMES(int id, char* s)
{
    return id == GetHashValue32(s);
}

extern "C" void cOVState_TOPTIMES_onWidgetCreate(void* self, cUIText* w)
{
    int id = *(int*)((char*)w + 0x38);
    if (isHashTOPTIMES(id, D_0046F578)) {
        if (D_004A2700 == 0) {
            cUIText_setUnicodeStringByID(w, GetHashValue32(D_0046F588));
        } else {
            cUIText_setUnicodeStringByID(w, GetHashValue32(D_0046F598));
        }
        *(int*)((char*)w + 0x18) = 0;
    } else if (isHashTOPTIMES(id, D_0046F5A8)) {
        *(int*)((char*)w + 0x18) = 1;
    }
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_0039E4C0(void* self, void* a1);
extern "C" void func_0020A6F0(void* self, const char* name, const char* ext);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern signed char D_00535C11[];
extern char D_004A2428[];
extern char D_004A2430[];
extern char D_004A2438[];
extern char D_004A2440[];
extern char D_0046E4E8[];

static inline void LoadRider1F7F08(void* self, int n)
{
    char name[32];
    sprintf(name, D_004A2440, n);
    func_0020A6F0(self, name, D_0046E4E8);
    sprintf(name, D_004A2428, n);
    func_0020A6F0(self, name, D_0046E4E8);
    sprintf(name, D_004A2430, n);
    func_0020A6F0(self, name, D_0046E4E8);
    sprintf(name, D_004A2438, n);
    func_0020A6F0(self, name, D_0046E4E8);
}

extern "C" void func_001F7F08(void* self, void* a1)
{
    func_0039E4C0(self, a1);
    char* prof = (char*)cBE_getInterface_Fv(cBE_getBE(), 8);
    cBE_getInterface_Fv(cBE_getBE(), 0);
    int id = *(int*)(prof + 0x18);
    if (id >= 0) {
        LoadRider1F7F08(self, id + 1);
    }
    if (D_00535C11[0] == 2) {
        int id2 = *(int*)(prof + 0x1C);
        if (id2 >= 0) {
            LoadRider1F7F08(self, id2 + 1);
        }
    }
}

//100%
extern "C" int func_001F80C8(void* self, int a1, int a2)
{
    return a2 == 6 ? 0x101 : 0;
}

//100%
struct sVEntry_001F80D8 {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void func_001F80D8(void* self, void* a1, int a2)
{
    if (a1 != 0) {
        if (a2 == 5) {
            sVEntry_001F80D8* vt = *(sVEntry_001F80D8**)((char*)self + 0x8);
            vt[26].fn((char*)self + vt[26].delta);
        }
    }
}

//100%
extern int D_004A26FC;
extern "C" void func_0020AB50(int id);

extern "C" void func_001F8118(void* self, void* a1)
{
    if (*(int*)((char*)self + 0xA0) == 0) {
        int v = *(int*)((char*)a1 + 0x18);
        switch (v) {
        case 0:
            *(int*)((char*)self + 0xA0) = 1;
            D_004A26FC = 1;
            break;
        case 1:
            *(int*)((char*)self + 0xA0) = v;
            func_0020AB50(0x13);
            break;
        }
    }
}

