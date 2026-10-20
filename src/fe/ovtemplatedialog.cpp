#include "common.h"

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
// PORT: func_002C26D0 is a varargs formatter (dst, fmt, ...)
extern "C" void func_002C26D0_v(void* dst, int fmt, ...) __asm__("func_002C26D0");
extern "C" void func_003A0E90(void* text, char* str);
extern void* D_004A28A8;
extern char D_00471A10[];
extern char D_004A2718[];
extern char D_00471A20[];

struct sVEntry_PDA {
    short delta;
    short index;
    int (*fn)(void*, int);
};

static inline int Loc_PDA(int hash)
{
    char* obj = *(char**)((char*)D_004A28A8 + 0x8C);
    sVEntry_PDA* vt = *(sVEntry_PDA**)(obj + 4);
    return vt[4].fn(obj + vt[4].delta, hash);
}

static inline int div_PDA(int a, int b)
{
    return a / b;
}

extern "C" void cPDATemplate_onCreateScreen(char* self)
{
    *(int*)(self + 0xC) = 0x29;
    void* engine = *(void**)(self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_00471A10), 0);
    *(void**)(self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    engine = *(void**)(self + 0x10);
    screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_004A2718), 0);
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 1);
    }
    char* text = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_00471A20));
    if (text != 0) {
        int fmt = Loc_PDA(*(int*)(text + 0xB0));
        if (fmt != 0) {
            char buf[48];
            func_002C26D0_v(buf, fmt, -10 - div_PDA(*(int*)((char*)D_004A28A8 + 0x1C), 3600) % 15, 0x43);
            func_003A0E90(text, buf);
        }
    }
}

//100%
extern "C" int func_0020A8B0(int a0, int a1)
{
    if ((unsigned int)(a0 - 6) < 6) {
        return 0x16;
    }
    if ((unsigned int)(a0 - 4) < 2 || a0 == 0 || a1 == 3) {
        return 0xb;
    }
    return 0xa;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_0020AB50(int state);
int func_00158F30(void* self);
extern "C" void func_002706B8(void* p);
extern void* D_004A28A8;
extern char* D_004A2EEC;
extern int D_00534B30[];
extern char D_00535BC8[];
extern int D_004A26FC;
extern int D_004A2704;
extern int D_004A2700;
extern int D_004A1228;

static inline bool isKind_A8F8(int k, int v)
{
    return k == v;
}

extern "C" void GameUI_OpenScreenForState(int mode)
{
    int v = **(int**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28);
    int busy = v != 0 && v < 10;
    if (busy) return;
    int state = 0;
    cBE_getInterface_Fv(cBE_getBE(), 0);
    signed char* g = (signed char*)D_00535BC8;
    int type = **(int**)((char*)D_004A28A8 + 0xC0);
    int sub = g[0x48];
    int team = g[0x49];
    int kind = g[0x4A];
    switch (mode) {
    case 2:
        D_004A2704 = 0;
        if (D_004A1228 != 0) {
            state = 0x11;
        } else if (sub == 4) {
            D_004A26FC = mode;
        } else {
            D_004A26FC = 0;
            if (kind == 0) {
                state = 8;
            } else if (team == mode) {
                state = 0x15;
            } else {
                if (kind >= 4 && kind <= 11) state = 0x14;
                else state = 9;
            }
        }
        break;
    case 7:
        cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
        if (sub == 4) {
            D_004A26FC = sub;
            return;
        }
        D_004A26FC = 0;
        char* a = (char*)cBE_getInterface_Fv(cBE_getBE(), 8);
        char* b = (char*)cBE_getInterface_Fv(cBE_getBE(), 0xD);
        int any = 0;
        if (*(int*)(a + 0x18) >= 0 || *(int*)(a + 0x1C) >= 0) any = 1;
        if (any) {
            if (D_00534B30[0] != 0) {
                state = func_0020A8B0(kind, type);
            } else {
                D_004A2700 = 0;
                state = 0xF;
            }
        } else {
            if (func_00158F30(b) > 0 || *(int*)(b + 0x10) != 0) {
                state = 0x10;
            } else {
                state = func_0020A8B0(kind, type);
            }
        }
        int z = !isKind_A8F8(kind, 6) && !isKind_A8F8(kind, 7) && !isKind_A8F8(kind, 8) && !isKind_A8F8(kind, 9) &&
                !isKind_A8F8(kind, 10) && !isKind_A8F8(kind, 11);
        if (z) func_002706B8(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28));
        if (D_00534B30[0] != 0) *(int*)(D_004A2EEC + 0x64) = 0x8CA0;
        break;
    }
    if (state == 0) {
        D_004A26FC = 2;
    } else {
        func_0020AB50(state);
    }
}

INCLUDE_ASM("fe/ovtemplatedialog", func_0020AB50);

INCLUDE_ASM("fe/ovtemplatedialog", GameUI_PushPopupScreen);

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_0020AB50(int state);
extern "C" void func_00258C00(void* net);
extern "C" void func_00258790(void* net, int a1);
extern "C" int func_0030B8C0(void* self);
extern void* D_004A28A8;
extern void* D_004A3DD8;
extern char* D_004A2EEC;
extern char D_004A2468;
extern int D_00534B30[];
extern char D_00535BC8[];

static inline bool notMode4_0020CA10(signed char* g)
{
    return g[0x48] != 4;
}

extern "C" void GameUI_OpenPauseMenu(void)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
    if (D_00534B30[0] != 0) {
        char* net = D_004A2EEC;
        if (net != 0) {
            char* game = *(char**)((char*)D_004A28A8 + 0x84);
            if (game != 0 && *(int*)(game + 0x224) != 0) {
                func_00258C00(net);
            }
            func_00258790(D_004A2EEC, 1);
            char* n = D_004A2EEC;
            *(int*)(n + 0x68) = 0xE10;
            *(int*)(n + 0x64) = 0x708;
        }
        func_0020AB50(6);
    } else if (func_0030B8C0(D_004A3DD8) != 0) {
        func_0020AB50(2);
    } else {
        signed char* g = (signed char*)D_00535BC8;
        if (g[0x49] == 0 && notMode4_0020CA10(g)) {
            func_0020AB50(1);
        } else if (*(int*)(*(char**)((char*)D_004A28A8 + 0x84) + 0x214) == 0xB) {
            func_0020AB50(4);
        } else {
            signed char* g2 = (signed char*)D_00535BC8;
            if (g2[0x48] == 4) {
                func_0020AB50(3);
            } else {
                func_0020AB50(5);
            }
        }
    }
    D_004A2468 = 0;
}

//100%
int GetHashValue32(char* str);
extern "C" int func_0039F9D8(void* stack, int hash);
extern char D_00471A40[];

extern "C" int GameUI_IsReplayMenuOpen(void)
{
    char* stack = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48) + 0x18;
    return func_0039F9D8(stack, GetHashValue32(D_00471A40)) != 0;
}

//100%
int GetHashValue32(char* str);
extern "C" int func_0039F9D8(void* stack, int hash);
extern void* D_004A28A8;
extern char D_0046F818[];

extern "C" int GameUI_IsPauseMenuOpen(void)
{
    char* stack = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48) + 0x18;
    return func_0039F9D8(stack, GetHashValue32(D_0046F818)) != 0;
}

//100%
class cUIState20CBE8 {
public:
    int pad[2];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual int v25();
};
extern "C" void* cUIStateStack_getCurrentState(void* stack);
extern "C" int GameUI_IsPauseMenuOpen(void);
extern void* D_004A28A8;

extern "C" int GameUI_CanOpenPauseMenu(void)
{
    char* mgr = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48);
    if (GameUI_IsPauseMenuOpen() == 0) {
        cUIState20CBE8* s = (cUIState20CBE8*)cUIStateStack_getCurrentState(mgr + 0x18);
        if (s != 0) {
            if (*(int*)((char*)s + 0x1C) & 1) {
                return 0;
            }
            return s->v25();
        }
        return 1;
    }
    return 0;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_0020AB50(int state);
extern char D_00535BC8[];
extern int D_004A26FC;

extern "C" void GameUI_OpenFinishScreen(void)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    signed char* g = (signed char*)D_00535BC8;
    int mode = g[0x48];
    int players = g[0x49];
    if (mode == 0 || players == 2) {
        func_0020AB50(0xC);
    } else if ((mode >= 1 && mode <= 3) || mode == 6) {
        func_0020AB50(0xD);
    } else if (mode == 4) {
        D_004A26FC = 2;
    } else {
        func_0020AB50(0xC);
    }
}

//100%
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cUIStateStack_getCurrentState(void* stack);
extern "C" void func_0020AB50(int state);
extern "C" int func_0020A8B0(int a0, int a1);
int func_00158F30(void* self);
void cReplay_stopAutoReplay(void* self);
extern "C" void func_00231250(void* self, int a, int b, int refresh);
extern "C" void func_0026F8A0(void* self, void* a1, int a2, int a3);
extern "C" void func_00257610(void* self, int a1);
extern "C" void cGame_exit(void* game, int a);
extern void* D_004A28A8;
extern char* D_004A2EEC;
extern int D_00534B30[];
extern char D_00535BC8[];
extern int D_004A26FC;
extern int D_004A2700;
extern int D_004A2708;
extern unsigned int D_004A2594;

struct sGame84_20CCF8 {
    char pad[0x48];
    char* ui;
};
struct sGM_20CCF8 {
    char pad[0x84];
    sGame84_20CCF8* game;
};

static inline void* Replay_20CCF8()
{
    return *(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28);
}

extern "C" void GameUI_HandleMenuResult(void)
{
    D_004A26FC = 0;
    char* s = (char*)cUIStateStack_getCurrentState(((sGM_20CCF8*)D_004A28A8)->game->ui + 0x18);
    cBE_getInterface_Fv(cBE_getBE(), 0);
    signed char* g = (signed char*)D_00535BC8;
    int kind = g[0x4A];
    int type = **(int**)((char*)D_004A28A8 + 0xC0);
    switch (*(int*)(s + 0x98)) {
    case 10:
    case 11:
        switch (D_004A2700) {
        case 2:
            cReplay_stopAutoReplay(Replay_20CCF8());
            D_004A26FC = 4;
            break;
        case 3:
            cReplay_stopAutoReplay(Replay_20CCF8());
            D_004A2594 = 1;
            func_0020AB50(0x21);
            break;
        case 1:
            cReplay_stopAutoReplay(Replay_20CCF8());
            func_00231250(*(void**)((char*)D_004A28A8 + 0x84), 0xD, 0, 1);
            break;
        case 4:
            func_0020AB50(0x23);
            break;
        case 5:
            D_004A2708 = 0;
            func_0020AB50(0x17);
            break;
        case 6:
            cReplay_stopAutoReplay(Replay_20CCF8());
            func_0020AB50(0x11);
            func_0026F8A0(Replay_20CCF8(), 0, 0, 0);
            break;
        case 7:
            D_004A2700 = 1;
            func_0020AB50(0xF);
            break;
        case 8:
            cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
            if (D_00534B30[0] != 0) {
                if (D_004A2EEC != 0)
                    func_00257610(D_004A2EEC, 0);
                cGame_exit(*(void**)((char*)D_004A28A8 + 0x84), 0);
            } else {
                func_0020AB50(0x18);
            }
            break;
        }
        break;
    case 15:
        if (D_004A2700 == 0x13) {
            func_0020AB50(0x13);
            break;
        } else {
            void* b = cBE_getInterface_Fv(cBE_getBE(), 0xD);
            if (func_00158F30(b) > 0 || *(int*)((char*)b + 0x10) != 0) {
                func_0020AB50(0x10);
                break;
            }
        }
    case 16:
        func_0020AB50(func_0020A8B0(kind, type));
        break;
    case 8:
    case 9:
    case 20:
    case 21:
        D_004A26FC = 2;
        break;
    case 22:
        switch (D_004A2700) {
        case 2:
            cReplay_stopAutoReplay(Replay_20CCF8());
            D_004A26FC = 4;
            break;
        case 5:
            D_004A2708 = 0;
            func_0020AB50(0x17);
            break;
        case 8:
            func_0020AB50(0x18);
            break;
        }
        break;
    case 35:
        break;
    }
}

//100%
extern "C" void* cUIStateStack_getCurrentState(void* self);
extern "C" void func_0039F840(void* list);
extern "C" void func_00231250(void* game, int a, int b, int c);
extern "C" void GameUI_HandleMenuResult();
extern "C" void func_0020D190();
void cReplay_stopAutoReplay(void* self);

struct sGame_20CFD0 {
    char pad[0x28];
    void* replay;
};
struct sGM_20CFD0 {
    char pad[0x84];
    sGame_20CFD0* game;
};

extern "C" void GameUI_Update()
{
    char* ui = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48);
    char* state = 0;

    if (ui + 0x18)
        state = (char*)cUIStateStack_getCurrentState(ui + 0x18);
    switch (D_004A26FC) {
    case 0:
        break;
    case 1:
        GameUI_HandleMenuResult();
        break;
    case 2: {
        D_004A26FC = 0;
        cReplay_stopAutoReplay(((sGM_20CFD0*)D_004A28A8)->game->replay);
        char* g = (char*)D_004A28A8;
        *(int*)(*(char**)(*(char**)(g + 0x84) + 0x200) + 8) = 1;
        if (state == 0)
            break;
        if (*(int*)(*(char**)(g + 0x84) + 0x214) != 2)
            break;
        if (*(int*)(state + 0x98) != 8)
            break;
        cBE_getInterface_Fv(*(void**)(g + 0x78), 7);
        if (D_00534B30[0] == 0)
            break;
        func_0039F840(ui + 0x18);
        break;
    }
    case 3:
        D_004A26FC = 0;
        func_0020D190();
        func_0039F840(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48) + 0x18);
        break;
    case 4: {
        D_004A26FC = 0;
        func_00231250(((sGM_20CFD0*)D_004A28A8)->game, 0xE, 2, 0);
        break;
    }
    }
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_0039E2A0(void* self, void* mgr);
extern "C" void cUIStateStack_pushExplicit(void* stack, void* state);
extern void* D_004A270C;
extern void* D_004A28A8;
extern char D_00471A10[];
extern char D_004743F0[];

extern "C" void cOVStateManager_addPDATemplate(void)
{
    if (D_004A270C == 0) {
        char* mgr = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48);
        void* t = cMemMan_alloc(0x48, D_00471A10, 0x100, 0);
        func_0039E2A0(t, mgr);
        *(void**)((char*)t + 8) = D_004743F0;
        D_004A270C = t;
        cUIStateStack_pushExplicit(mgr + 0x18, t);
    }
}

//100%
class cOVTemplate20D190 {
public:
    int pad[2];
    virtual ~cOVTemplate20D190();
};
extern "C" void cListNode_removeFromList(void* node);
extern void* D_004A270C;

extern "C" void func_0020D190(void)
{
    if (D_004A270C != 0) {
        cListNode_removeFromList(D_004A270C);
        delete (cOVTemplate20D190*)D_004A270C;
    }
    D_004A270C = 0;
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
struct cUIText;
void cUIText_setUnicodeStringByID(cUIText* t, int id);
extern "C" void func_0020A380(void* self);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern int D_004A2860[2];
extern char* D_00441D10[];
extern char D_0046E510[];
extern char D_0046E4C0[];

class cUIObj_20D1D8 {
public:
    int pad[2];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void setEnabled(int v);
    virtual void setVisible(int v);
};

extern "C" void func_0020D1D8(void* self)
{
    func_0020A380(self);
    char* list = (char*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_0046E510));
    *(int*)(list + 0x90) |= 8;
    for (int i = 0; i < 5; i++) {
        char buf[32];
        sprintf(buf, D_0046E4C0, i);
        cUIObj_20D1D8* o = (cUIObj_20D1D8*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(buf));
        if (o != 0) {
            if (i < 1) {
                int v = D_004A2860[i];
                cUIText_setUnicodeStringByID((cUIText*)o, GetHashValue32(D_00441D10[v]));
                *(int*)((char*)o + 0x18) = v;
            } else {
                o->setVisible(0);
                o->setEnabled(1);
            }
        }
    }
}

//100%
extern "C" int func_0020D308(void* self, int a1, int a2)
{
    return a2 == 6 ? 0x101 : 0;
}

//100%
extern int D_004A26FC;

extern "C" void func_0020D318(void* self, int a1, int key)
{
    if (a1 != 0 && key == 5) {
        D_004A26FC = 1;
    }
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void func_0020A380(void* self);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
struct cUIText;
void cUIText_setUnicodeStringByID(cUIText* t, int id);
extern char D_00471AF8[];
extern char D_004A23E0[];
extern char D_004A23E8[];
extern char D_00471B08[];
extern char D_00471B18[];
extern char D_0046F5B8[];
extern char D_0046F630[];
extern char D_0046F618[];
extern char D_00471B48[];
extern char D_0046F608[];
extern char D_0046EF08[];
extern char D_00471B30[];
extern char D_0046F648[];

struct sVE_20D338 { short delta; short index; void (*fn)(void*, int); };

extern "C" void cOVTemplate_Dialog_onCreateScreen(char* self)
{
    void* engine = *(void**)(self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_00471AF8), 0);
    *(void**)(self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    func_0020A380(self);
    *(int*)((char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_004A23E0)) + 0x18) = 0;
    *(int*)((char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_004A23E8)) + 0x18) = 1;
    cUIText* t = (cUIText*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_00471B08));
    switch (*(int*)(self + 0x9C)) {
    case 1: {
        cUIText_setUnicodeStringByID(t, GetHashValue32(D_00471B18));
        char* o = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_00471B30));
        sVE_20D338* e = &(*(sVE_20D338**)(o + 8))[9];
        e->fn(o + e->delta, 0);
        break;
    }
    case 0:
        cUIText_setUnicodeStringByID(t, GetHashValue32(D_0046F5B8));
        break;
    case 3:
        cUIText_setUnicodeStringByID(t, GetHashValue32(D_0046F630));
        break;
    case 2:
        cUIText_setUnicodeStringByID(t, GetHashValue32(D_0046F618));
        break;
    case 4:
        cUIText_setUnicodeStringByID(t, GetHashValue32(D_00471B48));
        break;
    case 5:
        cUIText_setUnicodeStringByID(t, GetHashValue32(D_0046F608));
        break;
    case 6: {
        cUIText_setUnicodeStringByID(t, GetHashValue32(D_0046EF08));
        char* o = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_00471B30));
        sVE_20D338* e = &(*(sVE_20D338**)(o + 8))[9];
        e->fn(o + e->delta, 0);
        break;
    }
    default:
        cUIText_setUnicodeStringByID(t, GetHashValue32(D_0046F648));
        break;
    }
}

//100%
int GetHashValue32(char* str);
extern "C" void cUIMenu_setSelectedByIndex(void* menu, int idx);
extern char D_0046E818[];

extern "C" void cOVTemplate_Dialog_OnWidgetCreated(void* self, void* item)
{
    int id = *(int*)((char*)item + 0x38);
    if (id == GetHashValue32(D_0046E818)) {
        if (*(int*)((char*)self + 0x9C) == 6) {
            cUIMenu_setSelectedByIndex(item, 0);
        } else {
            cUIMenu_setSelectedByIndex(item, 1);
        }
    }
}

//100%
// Key filter: keys 8 and 9 return 0x100, every other key 0x101.
extern "C" int func_0020D568(void* self, int a1, unsigned int key)
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
struct cUIScreen;
unsigned short cUIScreen_getFrameByLabel(cUIScreen* self, int label);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void func_0039F190(void* self, int a1);
extern "C" void cGame_exit(void* game, int toFrontEnd);
extern "C" void cGame_restart(void* self);
void cReplay_stopAutoReplay(void* self);
extern "C" void cRider_quitEvent(char* self);
extern "C" void func_00231250(void* self, int a, int b, int refresh);
extern "C" void cGameModeMan_initGameMode(void* self, int mode);
extern "C" void cBENewRaceInterface_setGameEvent(void* self, int ev);
extern "C" void cBENewRaceInterface_setGameMode(void* self, int mode);
extern "C" void cBE_setState(int state);
extern "C" void* OVScreenAutosave_ctor(void* self, void* a1, int a2);
extern "C" void* func_00211088(void* self, void* a1, int a2, int a3);
extern "C" void func_0030B758(void* self);
extern "C" void func_00128A10(void* self);
extern "C" void cRider_placeAtRegion(void* self, int a1, int a2);
extern "C" void cRider_finishPlacement(void* self, int notify);
extern "C" void func_00230180(void* self);
void func_00238348(void* self);
extern "C" void func_00257610(void* self, int a1);
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void cUIStateStack_pushSpecial(void* stack, void* st, int a2, int a3);
extern int D_004A2708;
extern int D_004A2A54;
extern int D_004A2A50;
extern int D_005366E8[];
extern int D_004428F0[];
extern int D_004A11BC;
extern int D_004A11B8;
extern char D_0046E050[];
extern char D_0046F9C0[];

struct sI10_D5A8 { char pad[0x10]; int f10; };
struct sSelf_D5A8 { char pad[0x54]; int f54; };
// Same vtable entry; the void/int return only changes v0/v1 choice around the call.
struct sVV_D5A8 { short delta; short index; void (*fn)(void*); };
struct sGame_D5A8 { char pad[0xC]; char* f0C; };
struct sApp_D5A8 { char pad[0x84]; char* game; };
struct sP40_D5A8 { char pad[0x40]; char* f40; };
struct sP18_D5A8 { char pad[0x18]; char* f18; };
static inline char* Game_D5A8() { return ((sApp_D5A8*)D_004A28A8)->game; }
static inline char* Rider_D5A8() { return ((sP18_D5A8*)((sP40_D5A8*)((sGame_D5A8*)Game_D5A8())->f0C)->f40)->f18; }
struct sVE_20D5A8 { short delta; short index; int (*fn)(void*); };
struct sStFlags_20D5A8 { char pad[0x1C]; unsigned int lo : 8; unsigned int mode : 6; };

static inline void Play_20D5A8(char* self)
{
    int f = cUIScreen_getFrameByLabel(*(cUIScreen**)(self + 0x40), GetHashValue32(D_0046E050));
    if (f != 0xFFFF) {
        cUIScreen_playFrame(*(void**)(self + 0x40), f, 1);
    }
}

static inline void Pop_20D5A8()
{
    D_004A26FC = 3;
    D_004A2A50 = D_004428F0[D_005366E8[--D_004A2A54]];
}

extern "C" void cOVTemplate_Dialog_onWidgetEvent(char* self, char* w, int ev)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    if (w == 0) {
        return;
    }
    switch (ev) {
    case 5:
        Play_20D5A8(self);
        switch (*(int*)(w + 0x18)) {
        case 0:
            *(int*)(self + 0x54) = 1;
            switch (*(int*)(self + 0x9C)) {
            case 0: {
                int kind = D_00535BC8[0x4A];
                if (kind >= 6 && kind <= 11) {
                    if (D_004A2708) {
                        Pop_20D5A8();
                    } else {
                        cReplay_stopAutoReplay(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28));
                        D_004A26FC = 3;
                    }
                    int mode = 0xE;
                    if (kind == 7 || kind == 10) {
                        mode = 0xF;
                    } else if (kind == 8 || kind == 11) {
                        mode = 0x10;
                    }
                    char* iface = (char*)cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 0);
                    void* gm = *(void**)((char*)D_004A28A8 + 0xC0);
                    cBE_setState(0);
                    cBENewRaceInterface_setGameMode(iface, D_00535BC8[0x48]);
                    cBENewRaceInterface_setGameEvent(iface, kind);
                    D_004A11BC = mode;
                    *(int*)(D_00535BC8 + 0x40) = mode;
                    sVV_D5A8* vt = *(sVV_D5A8**)(iface + 0xC);
                    D_004A11B8 = 1;
                    vt[1].fn(iface + vt[1].delta);
                    cGameModeMan_initGameMode(gm, D_00535BC8[0x4A]);
                    cGame_exit(*(void**)((char*)D_004A28A8 + 0x84), 1);
                } else if (D_004A2708) {
                    Pop_20D5A8();
                    cGame_restart(Game_D5A8());
                } else {
                    cReplay_stopAutoReplay(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28));
                    func_00238348(*(void**)((char*)D_004A28A8 + 0xC0));
                    func_00231250(*(void**)((char*)D_004A28A8 + 0x84), 0xD, 0, 1);
                    D_004A26FC = 3;
                }
                break;
            }
            case 1: {
                cReplay_stopAutoReplay(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28));
                *(int*)(self + 0x54) = 0;
                cBE_getInterface_Fv(cBE_getBE(), 4);
                if (D_004A2EEC) {
                    func_00257610(D_004A2EEC, 0);
                }
                int any = 0;
                int z = 0;
                cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
                cBE_getInterface_Fv(cBE_getBE(), 0);
                if (D_00535BC8[0x49] != 0) {
                    cGame_exit(*(void**)((char*)D_004A28A8 + 0x84), 0);
                } else
                chk:
                if (any) {
                    char* ui = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48);
                    sStFlags_20D5A8* st = (sStFlags_20D5A8*)OVScreenAutosave_ctor(cMemMan_alloc(0x234, D_0046F9C0, 0x100, 0), *(void**)(self + 0x10), 1);
                    st->mode = 1;
                    cUIStateStack_pushSpecial(ui + 0x18, st, 0, 0);
                } else {
                    func_0020AB50(0x26);
                    cOVStateManager_addPDATemplate();
                }
                // The dead `goto chk` (folded only at combine) keeps `any = 0` from
                // being propagated by gcse, so the zero flag and its test survive
                // as in the original (same trick as gamestate GameStateReset_OverlayUpdate).
                { int t = z + 1; if (t != 1) { any = 1; goto chk; } }
                break;
            }
            case 2:
                func_0020AB50(0x1D);
                break;
            case 3:
                Pop_20D5A8();
                func_0030B758(D_004A3DD8);
                break;
            case 4: {
                cReplay_stopAutoReplay(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28));
                D_004A26FC = 3;
                char* iface = (char*)cBE_getInterface_Fv(cBE_getBE(), 0);
                char* i10 = (char*)cBE_getInterface_Fv(cBE_getBE(), 10);
                cBE_setState(0);
                cBENewRaceInterface_setGameEvent(iface, 0xC);
                cBENewRaceInterface_setGameMode(iface, 4);
                sVE_20D5A8* vt = *(sVE_20D5A8**)(iface + 0xC);
                vt[1].fn(iface + vt[1].delta);
                cGameModeMan_initGameMode(*(void**)((char*)D_004A28A8 + 0xC0), 0xC);
                func_00128A10(*(void**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC));
                ((sI10_D5A8*)i10)->f10 = 1;
                func_00231250(*(void**)((char*)D_004A28A8 + 0x84), 1, 1, 0);
                func_00230180(*(void**)((char*)D_004A28A8 + 0x84));
                cRider_placeAtRegion(*(void**)(*(char**)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0x40) + 0x18), 1, 2);
                cRider_finishPlacement(*(void**)(*(char**)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0xC) + 0x40) + 0x18), 1);
                break;
            }
            case 5:
                Pop_20D5A8();
                cRider_quitEvent(Rider_D5A8());
                break;
            case 6: {
                ((sSelf_D5A8*)self)->f54 = 0;
                char* ui = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48);
                sStFlags_20D5A8* st = (sStFlags_20D5A8*)func_00211088(cMemMan_alloc(0x27C, D_0046F9C0, 0x100, 0), *(void**)(self + 0x10), *(unsigned char*)(self + 0x14), 0x18);
                st->mode = 1;
                cUIStateStack_pushSpecial(ui + 0x18, st, 0, 0);
                break;
            }
            }
            break;
        case 1:
            if (*(int*)(self + 0x9C) != 6) {
                func_0039F190(*(char**)(self + 0x10) + 0x18, 1);
            } else {
                ((sSelf_D5A8*)self)->f54 = 1;
                cGame_exit(*(void**)((char*)D_004A28A8 + 0x84), 0);
            }
            break;
        }
        break;
    case 6:
        if (*(int*)(self + 0x9C) != ev) {
            Play_20D5A8(self);
            func_0039F190(*(char**)(self + 0x10) + 0x18, 1);
        }
        break;
    }
}

//100%
struct cUIScreen;
int GetHashValue32(char* str);
unsigned short cUIScreen_getFrameByLabel(cUIScreen* self, int label);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void func_0020E900(void* self);
extern "C" void func_0039F190(void* self, int a1);
extern char* D_004A2EEC;
extern char D_0046E050[];

extern "C" void OVScreenYNDialogQuitGame_Update(void* self)
{
    func_0020E900(self);
    char* p = D_004A2EEC;
    if (p != 0) {
        int ok = *(int*)(p + 0x68) == 0 || *(int*)(p + 0x64) == 0;
        if (ok) {
            int frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0x40), GetHashValue32(D_0046E050));
            if (frame != 0xFFFF) {
                cUIScreen_playFrame(*(void**)((char*)self + 0x40), frame, 1);
            }
            func_0039F190(*(char**)((char*)self + 0x10) + 0x18, 1);
        }
    }
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void func_0020A380(void* self);
extern "C" void cUIState_hideObjSafe(void* self, char* name);
extern "C" void cUIState_showObjSafe(void* self, char* name);
extern "C" void cOVState_REPLAY_setupCameraName(void* self);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void cUIMenu_setSelectedByIndex(void* menu, int idx);
extern void* D_004A28A8;
extern char D_00471A40[];
extern char D_00471BA0[];
extern char D_00471BB0[];
extern char D_00471BC0[];
extern char D_00471BD0[];
extern char D_00471BE0[];
extern char D_00471BF0[];

struct sVE_20DC68 { short delta; short index; void (*fn)(void*, int); };

extern "C" void func_0020DC68(char* self)
{
    *(int*)(self + 0xC) = GetHashValue32(D_00471A40);
    void* engine = *(void**)(self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_00471A40), 0);
    *(void**)(self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    func_0020A380(self);
    *(int*)(self + 0xA0) = 0;
    *(int*)(self + 0x9C) = 0;
    cUIState_hideObjSafe(self, D_00471BA0);
    cUIState_hideObjSafe(self, D_00471BB0);
    if (*(int*)(self + 0xA0) != 0) {
        cUIState_hideObjSafe(self, D_00471BC0);
        cUIState_showObjSafe(self, D_00471BD0);
    } else {
        cUIState_showObjSafe(self, D_00471BC0);
        cUIState_hideObjSafe(self, D_00471BD0);
    }
    *(int*)(self + 0xA4) = 0xF5;
    *(int*)(self + 0xAC) = 0xF5;
    *(int*)(self + 0xB0) = 0x1E0;
    *(int*)(self + 0xA8) = 0;
    cOVState_REPLAY_setupCameraName(self);
    if (*(int*)(*(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x28) + 0x608) != 0) {
        *(int*)(self + 0xB4) = 1;
    } else {
        *(int*)(self + 0xB4) = 0;
    }
    char* obj = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_00471BE0));
    *(int*)(obj + 0x90) |= 8;
    if (*(int*)(self + 0xB4) != 0) {
        if (obj != 0) cUIMenu_setSelectedByIndex(obj, 2);
        char* o = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_00471BF0));
        if (o != 0) {
            sVE_20DC68* e = &(*(sVE_20DC68**)(o + 8))[9];
            e->fn(o + e->delta, 0);
            e = &(*(sVE_20DC68**)(o + 8))[8];
            e->fn(o + e->delta, 0);
        }
    }
}

