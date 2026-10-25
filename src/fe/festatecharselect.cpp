#include "common.h"

//100%
struct sVec4_181148 { float x, y, z, w; } __attribute__((aligned(16)));
struct sCam_181148 { char pad[0x10]; float fov; };
int GetHashValue32(char* str);
extern char D_0045D600[];
extern void* D_004A28A8;
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void func_0015E050(void* cam, sVec4_181148* a, sVec4_181148* b);
extern "C" void* func_001A0548(void* self, int a1);
extern "C" void func_0019E538(void* self, int a1);

extern "C" void cFEStateCharSelect_onCreateScreen(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0045D600), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    sCam_181148* cam = *(sCam_181148**)((char*)D_004A28A8 + 0x7C);
    sVec4_181148 pos;
    pos.x = 0.0f;
    pos.y = 200.0f;
    pos.z = 0.0f;
    pos.w = 1.0f;
    sVec4_181148 at;
    at.x = 0.0f;
    at.y = 0.0f;
    at.z = 0.0f;
    at.w = 1.0f;
    func_0015E050((char*)cam + 0x10, &pos, &at);
    cam->fov = 0.4363323450088501f;
    func_0019E538(func_001A0548(*(char**)((char*)D_004A28A8 + 0x7C) + 0xB0, *(signed char*)((char*)self + 0x44)), 0);
    *(int*)((char*)self + 0x80) = 1;
    *(float*)((char*)self + 0x5C) = -1.0f;
    *(int*)((char*)self + 0x58) = 0;
    *(int*)((char*)self + 0x60) = 0;
}

//100%
extern void* D_004A28A8;
extern signed char D_00535C11[];
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* func_001A0548(void* self, int a1);
extern "C" void func_0019E538(void* self, int a1);
void* func_0039E4A0(void* self);

extern "C" void func_00181238(void* self)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    char* mgr = *(char**)((char*)D_004A28A8 + 0x7C);
    if (mgr != 0 && D_00535C11[0] != 0) {
        func_0019E538(func_001A0548(mgr + 0xB0, *(signed char*)((char*)self + 0x44)), 0);
    }
    func_0039E4A0(self);
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBENewPlayerInterface_getPlayerCharID(void* self, int index);
extern "C" void func_00181BD0(void* self, int index, signed char charID);

extern "C" int func_001812A8(void* self, int on)
{
    if (on != 0) {
        int id = cBENewPlayerInterface_getPlayerCharID(cBE_getInterface_Fv(cBE_getBE(), 1), *(signed char*)((char*)self + 0x44));
        func_00181BD0(self, *(signed char*)((char*)self + 0x44), id);
    }
    return 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
int GetHashValue32(char* str);
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBENewPlayerInterface_getPlayerCharID(void* self, int index);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void cUIMenu_setSelectedByIndex(void* menu, unsigned char idx);
extern "C" void func_001A0508(void* self, int idx, int a2, int a3);
extern "C" void* func_001A0548(void* self, int a1);
extern "C" void cFEStateCharSelect_UpdateRiderPreview(void* self);
extern "C" void func_0039E4C0(void* self, int a1);
extern void* D_004A28A8;
extern signed char D_00440F68[];
extern char D_004A1398[];

extern "C" void func_00181308(void* self, int a1)
{
    int i = 0;
    int id = cBENewPlayerInterface_getPlayerCharID(cBE_getInterface_Fv(cBE_getBE(), 1), *(signed char*)((char*)self + 0x44));
    for (; i < 10; i++) {
        if (D_00440F68[i] == id) {
            void* menu = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A1398));
            if (menu != 0)
                cUIMenu_setSelectedByIndex(menu, i);
            break;
        }
    }
    func_001A0508(*(char**)((char*)D_004A28A8 + 0x7C) + 0xB0, *(signed char*)((char*)self + 0x44), D_00440F68[0], 0);
    char* r = (char*)func_001A0548(*(char**)((char*)D_004A28A8 + 0x7C) + 0xB0, *(signed char*)((char*)self + 0x44));
    *(int*)(r + 0xCCC) = 0;
    cFEStateCharSelect_UpdateRiderPreview(self);
    func_0039E4C0(self, a1);
}

extern "C" void* func_0039E6B8(void* self);

//100%
void* func_00181400(void* self)
{
    return func_0039E6B8(self);
}

//100%
extern "C" void cFEStateCharSelect_UpdateRiderPreview(void* self);
extern "C" void* func_0039E510(void* self);

extern "C" void func_00181420(void* self)
{
    cFEStateCharSelect_UpdateRiderPreview(self);
    func_0039E510(self);
}

//100%
struct sPadVtI_1450 { short delta; short index; int (*fn)(void*); };
struct sPadVtF_1450 { short delta; short index; float (*fn)(void*); };

static inline int padBtn_1450(char* pad, int slot)
{
    sPadVtI_1450* vt = *(sPadVtI_1450**)(pad + 8);
    return vt[slot].fn(pad + vt[slot].delta);
}

static inline float padAxis_1450(char* pad, int slot)
{
    sPadVtF_1450* vt = *(sPadVtF_1450**)(pad + 8);
    return vt[slot].fn(pad + vt[slot].delta);
}

static inline float wrapHi_1450(float a)
{
    while (a >= 360.0f)
        a -= 360.0f;
    return a;
}

static inline float wrapLo_1450(float a)
{
    while (a < 0.0f)
        a += 360.0f;
    return a;
}

// PORT: g++ `<?` (min) operator.
static inline float clamp_1450(float v, float lo, float hi)
{
    if (v >= lo) return v <? hi;
    return lo;
}

extern "C" int func_00181450(char* self, char* pad)
{
    int changed = 0;
    if (padBtn_1450(pad, 35)) {
        *(float*)(self + 0x60) += padAxis_1450(pad, 38) * 3.0f;
        if (*(float*)(self + 0x60) >= 360.0f) {
            float a = *(float*)(self + 0x60);
            do
                a -= 360.0f;
            while (a >= 360.0f);
            *(float*)(self + 0x60) = a;
        }
        float a = *(float*)(self + 0x60);
        float zero = 0.0f;
        if (a < zero) {
            float b;
            do {
                b = a + 360.0f;
                a = b;
            } while (b < zero);
            *(float*)(self + 0x60) = b;
        }
        changed = 1;
    }
    if (padBtn_1450(pad, 33)) {
        *(float*)(self + 0x58) = clamp_1450(*(float*)(self + 0x58) + padAxis_1450(pad, 36) * -0.10000000149011612f, 0.0f, 1.0f);
        changed = 1;
    }
    if (padBtn_1450(pad, 34)) {
        *(float*)(self + 0x5C) = clamp_1450(*(float*)(self + 0x5C) + padAxis_1450(pad, 37) * -0.10000000149011612f, -1.0f, 1.0f);
        changed = 1;
    }
    return changed;
}

//100%
int GetHashValue32(char* str);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
struct cUIText;
void cUIText_setAsciiString(cUIText* text, const char* str);
void cUIText_setUnicodeStringByID(cUIText* text, int id);
extern "C" void* func_0014EEC8(void* self, int player, int index);
extern signed char D_00535C11[];
extern signed char D_00440F68[];
extern char D_0045D610[];
extern char D_0045D620[];
extern char D_0045D638[];
extern char D_0045D658[];
extern char D_0045D678[];
struct sCharKey_1620 { char c[2]; };
extern sCharKey_1620 D_004A13A0[];

struct sWVt_1620 { short delta; short index; void (*fn)(void*, int); };
struct sWidget_1620 {
    int f0;
    int f4;
    sWVt_1620* vt;              // 0x8
    int fC;
    int f10;
    unsigned b0 : 1;            // 0x14
    unsigned b1 : 6;
    unsigned b7 : 1;
    unsigned b8 : 24;
    int id18;                   // 0x18
    char pad1C[0x38 - 0x1C];
    int hash;                   // 0x38
};

static inline void refresh_1620(sWidget_1620* w)
{
    w->vt[9].fn((char*)w + w->vt[9].delta, 0);
}

extern "C" void cFEStateCharSelect_onWidgetCreate(char* self, sWidget_1620* w)
{
    int h = w->hash;
    if (h == GetHashValue32(D_0045D610)) {
        w->b0 = 0;
        w->b7 = 1;
        return;
    }
    cBE_getInterface_Fv(cBE_getBE(), 0);
    if (h == GetHashValue32(D_0045D620) && D_00535C11[0] == 2) {
        refresh_1620(w);
        return;
    }
    if (h == GetHashValue32(D_0045D638)) {
        if (D_00535C11[0] == 2) {
            switch (*(signed char*)(self + 0x44)) {
            case 0:
                cUIText_setUnicodeStringByID((cUIText*)w, GetHashValue32(D_0045D658));
                break;
            case 1:
                cUIText_setUnicodeStringByID((cUIText*)w, GetHashValue32(D_0045D678));
                break;
            }
            return;
        }
        refresh_1620(w);
        return;
    }
    sCharKey_1620 key = D_004A13A0[0];
    for (int i = 0; i < 10; i++) {
        key.c[0] = '0' + i;
        if (h == GetHashValue32(key.c)) {
            cUIText_setAsciiString((cUIText*)w, (const char*)func_0014EEC8(cBE_getInterface_Fv(cBE_getBE(), 2), D_00440F68[i], 0));
            w->id18 = i;
            refresh_1620(w);
            return;
        }
    }
}

//100%
extern void* D_004A28A8;
extern "C" void* func_001A0548(void* self, int a1);
extern "C" void func_001472C8(void* self, int a1, int a2);
extern "C" void func_00147448(void* self, int a1, int charID);
extern "C" void func_001474A8(void* iface, int rider, int id);
extern "C" void func_001A1CB8(void* self, int a1, int val);
extern "C" void func_0039F400(void* list, void* item);
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_001887A0(void* mem, void* owner, int a2);
extern "C" void* func_0018ECA0(void* mem, void* owner, int a2, int mask);
extern "C" void cUIStateStack_pushSpecial(void* stack, void* state, int a2, int a3);
extern char D_0045D698[];
extern char D_0045D6A8[];

struct sVE_17E8 {
    short delta;
    short index;
    void (*fn)(void*, ...);
};
struct sVEP_17E8 {
    short delta;
    short index;
    void* (*fn)(void*, ...);
};

static inline void Refresh_17E8(void* iface)
{
    sVE_17E8* vt = *(sVE_17E8**)((char*)iface + 0xC);
    vt[1].fn((char*)iface + vt[1].delta);
}

static inline void ApplyRider_17E8(int rider, int slot, int charID, int board)
{
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 1);
    func_001472C8(iface, rider, slot);
    func_00147448(iface, rider, charID);
    func_001474A8(iface, rider, board);
    Refresh_17E8(iface);
}

static inline void* StateCall_17E8(char* self, int slot, int sel)
{
    char* o = **(char***)(self + 0x10);
    sVEP_17E8* vt = *(sVEP_17E8**)(o + 0x4);
    return vt[slot].fn(o + vt[slot].delta, self, sel);
}

static inline void Finish_17E8(char* self)
{
    func_0019E538(func_001A0548(*(char**)((char*)D_004A28A8 + 0x7C) + 0xB0, *(signed char*)(self + 0x44)), 0);
    *(int*)(self + 0x80) = 0;
}

extern "C" void func_001817E8(char* self, char* menu, int msg)
{
    if (menu == 0)
        return;
    switch (msg) {
    case 5: {
        char* p = (char*)func_001A0548(*(char**)((char*)D_004A28A8 + 0x7C) + 0xB0, *(signed char*)(self + 0x44));
        *(int*)(p + 0xC20) = 1;
        *(int*)(p + 0xC1C) = 0;
        ApplyRider_17E8(*(signed char*)(self + 0x44), *(signed char*)(self + 0x14),
                        D_00440F68[*(int*)(menu + 0x18)], *(int*)(self + 0x4C));
        {
            int mask = 1 << *(signed char*)(self + 0x14);
            func_001A1CB8(**(void***)(self + 0x10), *(signed char*)(self + 0x44), mask & 0xFF);
        }
        void* st = StateCall_17E8(self, 4, *(int*)(menu + 0x18));
        if (st != 0)
            func_0039F400(*(char**)(self + 0x10) + 0x18, st);
        Finish_17E8(self);
        return;
    }
    case 6: {
        void* st = StateCall_17E8(self, 5, *(int*)(menu + 0x18));
        if (st == 0)
            return;
        func_0039F400(*(char**)(self + 0x10) + 0x18, st);
        Finish_17E8(self);
        return;
    }
    case 1: {
        sVE_17E8* vt = *(sVE_17E8**)(menu + 0x8);
        vt[9].fn(menu + vt[9].delta, 1);
        func_00181BD0(self, *(signed char*)(self + 0x44), D_00440F68[*(int*)(menu + 0x18)]);
        ApplyRider_17E8(*(signed char*)(self + 0x44), *(signed char*)(self + 0x14),
                        D_00440F68[*(int*)(menu + 0x18)], *(int*)(self + 0x4C));
        return;
    }
    case 2: {
        sVE_17E8* vt = *(sVE_17E8**)(menu + 0x8);
        vt[9].fn(menu + vt[9].delta, 0);
        return;
    }
    case 7: {
        void* iface = cBE_getInterface_Fv(cBE_getBE(), 1);
        func_001472C8(iface, *(signed char*)(self + 0x44), *(signed char*)(self + 0x14));
        Refresh_17E8(iface);
        char* st = (char*)func_001887A0(cMemMan_alloc(0x54, D_0045D698, 0x100, 0), *(void**)(self + 0x10), 1);
        *(int*)(st + 0x1C) = (*(int*)(st + 0x1C) & ~0x3F00) | 0x100;
        cUIStateStack_pushSpecial(*(char**)(self + 0x10) + 0x18, st, 0, 0);
        Finish_17E8(self);
        return;
    }
    case 8: {
        void* iface = cBE_getInterface_Fv(cBE_getBE(), 1);
        func_001472C8(iface, *(signed char*)(self + 0x44), *(signed char*)(self + 0x14));
        Refresh_17E8(iface);
        void* st = func_0018ECA0(cMemMan_alloc(0x280, D_0045D6A8, 0x100, 0), *(void**)(self + 0x10), 2,
                                 (1 << *(signed char*)(self + 0x14)) & 0xFF);
        func_0039F400(*(char**)(self + 0x10) + 0x18, st);
        char* o = **(char***)(self + 0x10);
        if (o != 0)
            *(int*)(o + 0xC) = 9;
        break;
    }
    default:
        return;
    }
    Finish_17E8(self);
}


//100%
int GetHashValue32(char* str);
struct cUIText;
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
void cUIText_setAsciiString(cUIText* text, const char* str);
extern "C" int func_00148B78(void* iface, int a, int b);
extern "C" int func_00148BC8(void* iface, int a, int b);
extern "C" int func_00148C18(void* iface, int a, int b);
extern "C" int func_00148C68(void* iface, int a, int b);
extern "C" int func_00148CB8(void* iface, int a, int b);
extern "C" int func_00148D08(void* iface, int a, int b);
extern "C" int func_00148D58(void* iface, int a, int b);
extern "C" void func_001A0508(void* self, int idx, int a2, int a3);
extern "C" void func_0039C428(void* bar, int v);
extern "C" double func_00413AF8(float f);
extern "C" void* func_00416210(void* dst, int c, int n);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern void* D_004A28A8;
extern char D_004A13B0;
extern char D_0045D6F0[];
extern char D_004A13B8[];
struct sStr9_181BD0 { char c[9]; };
struct sStr4_181BD0 { char c[4]; };
extern sStr9_181BD0 D_0045D6E0;
extern char D_004A13A8[];

class cFEVObj_181BD0 {
public:
    char pad[0x8];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09(int on);
};

// PORT: the unit declares func_00181BD0 with an int index; the body sign-extends both id arguments.
extern "C" void func_00181BD0_impl(void* self, signed char rider, signed char charID) __asm__("func_00181BD0");

extern "C" void func_00181BD0_impl(void* self, signed char rider, signed char charID)
{
    sStr9_181BD0 name = D_0045D6E0;
    char bar[8];
    *(sStr4_181BD0*)bar = *(sStr4_181BD0*)D_004A13A8;
    func_00416210(bar + 4, 0, 4);
    char buf[100];
    int stats[7];
    float k = 0.2f;
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 3);
    stats[0] = func_00148BC8(iface, rider, charID);
    stats[1] = func_00148C68(iface, rider, charID);
    stats[2] = func_00148B78(iface, rider, charID);
    stats[3] = func_00148CB8(iface, rider, charID);
    stats[4] = func_00148D58(iface, rider, charID);
    stats[5] = func_00148D08(iface, rider, charID);
    stats[6] = func_00148C18(iface, rider, charID);
    int total = 0;
    for (int i = 0; i < 7; i++) {
        name.c[7] = '0' + i;
        cFEVObj_181BD0* t = (cFEVObj_181BD0*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(name.c));
        bar[0] = '0' + i;
        char* b = (char*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(bar));
        if (t != 0 && b != 0) {
            int v = stats[i];
            // PORT: g++ minimum/maximum operator
            int c = v >? 0;
            total += v;
            sprintf(buf, &D_004A13B0, func_00413AF8((float)v * k));
            t->v09(1);
            cUIText_setAsciiString((cUIText*)t, buf);
            *(int*)(b + 0x80) = 0x37;
            func_0039C428(b, c);
        }
    }
    total -= total % 5;
    char* ovr = D_004A13B8;
    cUIText* avg = (cUIText*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_0045D6F0));
    sprintf(buf, &D_004A13B0, func_00413AF8((float)total * 0.02857142873108387f));
    cUIText_setAsciiString(avg, buf);
    char* ob = (char*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(ovr));
    *(int*)(ob + 0x80) = 0x37;
    func_0039C428(ob, total / 7);
    func_001A0508(*(char**)((char*)D_004A28A8 + 0x7C) + 0xB0, rider, charID, 0);
}

INCLUDE_ASM("fe/festatecharselect", cFEStateCharSelect_UpdateRiderPreview);

//100%
int GetHashValue32(char* str);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* func_0014EEC8(void* self, int player, int index);
extern "C" int func_00157EE0(void* iface, int a1, int a2, int a3);
extern "C" void* func_0015A478();
extern "C" int func_00398380(void* self, int id);
extern "C" void* func_0039E318(void* self, void* engine, void* owner);
extern "C" unsigned char func_001A1CD0(void* self, int a1);
extern void* D_0046CF30[];
extern char* D_00440F78[];

struct sCharEnt_2220 { char* name; char* label; int f8; char pad[3]; signed char id; };
struct sCharList_2220 { char pad[0x28]; sCharEnt_2220* ents; char pad2C[0x50 - 0x2C]; int count; };
struct sCharSel_2220 {
    char pad0[0x8];
    void** vt;                  // 0x8
    int fC;                     // 0xC
    char* owner;                // 0x10
    char f14;
    unsigned char f15;          // 0x15
    char pad16[0x44 - 0x16];
    signed char player;         // 0x44
    char pad45[0x54 - 0x45];
    int sel[6];                 // 0x54
    int f6C;
    int f70;                    // 0x70
    int f74;                    // 0x74
    int count;                  // 0x78
    int ids[30];                // 0x7C
    int hashes[30];             // 0xF4
    char* names[30];            // 0x16C
};

extern "C" sCharSel_2220* func_00182220(sCharSel_2220* self, void* engine, void* owner, signed char player, int slot)
{
    func_0039E318(self, engine, owner);
    self->fC = 10;
    self->vt = D_0046CF30;
    self->player = player;
    self->count = 1;
    self->f70 = 0;
    self->ids[0] = 0;
    char* o = self->owner;
    int h = GetHashValue32(D_00440F78[slot]);
    self->hashes[0] = func_00398380(o + 0x58, h);
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 13);
    sCharList_2220* list = (sCharList_2220*)func_0015A478();
    int n = list->count;
    for (int i = 0; i < n; i++) {
        sCharEnt_2220* e = &list->ents[i];
        if (func_00157EE0(iface, self->player, slot, e->id)) {
            char* lbl = e->label;
            self->ids[self->count] = e->id;
            char* o2 = self->owner;
            int h2 = GetHashValue32(lbl);
            self->hashes[self->count] = func_00398380(o2 + 0x58, h2);
            self->names[self->count] = e->name;
            self->count++;
        }
    }
    self->names[0] = (char*)func_0014EEC8(cBE_getInterface_Fv(cBE_getBE(), 2), slot, 0);
    for (int j = 5; j >= 0; j--)
        self->sel[j] = 0;
    self->f74 = 0;
    self->f15 = func_001A1CD0(*(void**)self->owner, self->player);
    return self;
}

//100%
int GetHashValue32(char* str);
extern char D_0045D780[];
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);

extern "C" void func_00182420(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0045D780), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
}

//100%
extern char D_004A1400[];
extern char D_0045D790[];
extern char D_0045D7A0[];
extern char D_0045D7B0[];
extern char D_004A1408[];
extern char* D_00440FA0[];
extern char D_004C66B8[];
extern "C" void func_0039B760(void* w, unsigned char n);

struct sCWVt_2460 { short delta; short index; void (*fn)(void*, int); };
struct sCWVtP_2460 { short delta; short index; void (*fn)(void*, void*); };
struct sCW_2460 {
    int f0;
    int f4;
    sCWVt_2460* vt;             // 0x8
    int fC;
    int f10;
    unsigned b0 : 1;            // 0x14
    unsigned b1 : 31;
    int id18;                   // 0x18
    char pad1C[0x38 - 0x1C];
    int hash;                   // 0x38
    char pad3C[0x78 - 0x3C];
    int f78;                    // 0x78
    int f7C;                    // 0x7C
};
struct sCheat_2460 {
    char pad0[0x48];
    sCW_2460* f48;              // 0x48
    sCW_2460* f4C;              // 0x4C
    sCW_2460* f50;              // 0x50
    sCW_2460* slots[6];         // 0x54
    sCW_2460* f6C;              // 0x6C
    int f70, f74;
    int count;                  // 0x78
    char pad7C[0xF4 - 0x7C];
    int vals[6];                // 0xF4
};

static inline void vcall_2460(sCW_2460* w, int k, int v)
{
    w->vt[k].fn((char*)w + w->vt[k].delta, v);
}

extern "C" void cFEStateCheatCharSelect_onWidgetCreate(sCheat_2460* self, sCW_2460* w)
{
    int h = w->hash;
    if (h == GetHashValue32(D_004A1400)) {
        self->f6C = w;
        w->id18 = 0;
        self->f6C->b0 = 0;
        if (self->count >= 6) func_0039B760(self->f6C, self->count);
        return;
    }
    if (h == GetHashValue32(D_0045D790)) {
        self->f48 = w;
        vcall_2460(w, 9, self->count >= 7);
        return;
    }
    if (h == GetHashValue32(D_0045D7A0)) {
        self->f4C = w;
        vcall_2460(w, 9, self->count >= 7);
        return;
    }
    if (h == GetHashValue32(D_0045D7B0)) {
        self->f50 = w;
        cUIText_setAsciiString((cUIText*)w, D_004A1408);
        return;
    }
    int i = 0;
    char** tb = D_00440FA0;
    sCW_2460** sp = self->slots;
    for (; i < 6; sp++, tb++, i++) {
        if (h == GetHashValue32(*tb)) {
            *sp = w;
            w->id18 = i;
            if (i == 0) {
                sCWVtP_2460* e = &((sCWVtP_2460*)self->slots[0]->vt)[21];
                e->fn((char*)self->slots[0] + e->delta, D_004C66B8);
            }
            if (i >= self->count) {
                vcall_2460(*sp, 9, 0);
                vcall_2460(*sp, 8, 1);
            } else {
                sCW_2460* sl = *sp;
                sl->f7C = (&self->vals[0])[i];
                sl->f78 = -1;
            }
        }
    }
}

//100%
struct cUIText;
void cUIText_setAsciiString(cUIText* text, const char* str);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_001474A8(void* iface, int rider, int id);
extern "C" void func_0039F190(void*, int);
extern char D_004C66A8[];
extern char D_004C66B8[];

struct sVEK182690a {
    short delta;
    short index;
    void (*fn)(void*, void*);
};
struct sVEK182690b {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void func_00182690(void* self, void* menu, unsigned int msg)
{
    if (menu == 0)
        return;
    switch (msg) {
    case 2: {
        sVEK182690a* vt = *(sVEK182690a**)((char*)menu + 8);
        vt[21].fn((char*)menu + vt[21].delta, D_004C66A8);
        break;
    }
    case 1: {
        int sel = *(int*)((char*)menu + 0x18) + *(unsigned char*)(*(char**)((char*)self + 0x6C) + 0x98);
        sVEK182690a* vt = *(sVEK182690a**)((char*)menu + 8);
        vt[21].fn((char*)menu + vt[21].delta, D_004C66B8);
        cUIText_setAsciiString(*(cUIText**)((char*)self + 0x50), *(const char**)((char*)self + (sel << 2) + 0x16C));
        break;
    }
    case 6:
        *(int*)((char*)self + 0x70) = 0;
        func_0039F190(*(char**)((char*)self + 0x10) + 0x18, 1);
        break;
    case 5: {
        int sel = *(int*)((char*)menu + 0x18) + *(unsigned char*)(*(char**)((char*)self + 0x6C) + 0x98);
        if (sel == 0)
            *(int*)((char*)self + 0x70) = 0;
        else
            *(int*)((char*)self + 0x70) = *(int*)((char*)self + (sel << 2) + 0x7C);
        char* pl = (char*)cBE_getInterface_Fv(cBE_getBE(), 1);
        func_001474A8(pl, *(signed char*)((char*)self + 0x44), *(int*)((char*)self + 0x70));
        sVEK182690b* vt = *(sVEK182690b**)(pl + 0xC);
        vt[1].fn(pl + vt[1].delta);
        *(int*)((char*)self + 0x74) = 1;
        func_0039F190(*(char**)((char*)self + 0x10) + 0x18, 1);
        break;
    }
    }
}

//100%
extern "C" void cFEStateCheatCharSelect_ApplyOutfit(void* self);

extern "C" int func_00182808(void* self, int a1, unsigned int msg, int value)
{
    switch (msg) {
    case 7:
    case 8:
    case 9:
        return 0x100;
    case 1:
        return value < *(int*)((char*)self + 0x78);
    case 5:
        cFEStateCheatCharSelect_ApplyOutfit(self);
        break;
    }
    return 0x101;
}

//100%
extern "C" void cFEStateCheatCharSelect_ApplyOutfit(void* self)
{
    int i;
    int idx = *(unsigned char*)(*(char**)((char*)self + 0x6c) + 0x98);
    for (i = 0; i < 6; i++) {
        void* it = ((void**)((char*)self + 0x54))[i];
        if (it != 0) {
            int v = ((int*)((char*)self + 0xf4))[idx + i];
            *(int*)((char*)it + 0x78) = -1;
            *(int*)((char*)it + 0x7c) = v;
        }
    }
}

//100%
extern "C" void* func_0039E2A0(void* self, void* engine);
extern "C" unsigned char func_001A1CD0(void* self, int a1);
extern void* D_0046CE60[];

extern "C" void* func_001828C0(void* self, void* engine, signed char idx)
{
    func_0039E2A0(self, engine);
    *(int*)((char*)self + 0xC) = 0xC;
    *(void***)((char*)self + 0x8) = D_0046CE60;
    *(signed char*)((char*)self + 0x44) = idx;
    *(unsigned char*)((char*)self + 0x15) = func_001A1CD0(**(void***)((char*)self + 0x10), idx);
    *(int*)((char*)self + 0x4C) = 0;
    return self;
}

