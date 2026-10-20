#include "common.h"

//100%
int GetHashValue32(char* str);
extern char D_004A1830[];
extern char D_004A1838[];
extern char D_004A1840[];
extern char D_004A1848[];
extern char D_00460420[];
extern char D_00460430[];
extern char D_00460440[];
extern char D_00460450[];
extern char D_00460460[];

struct sAudioOpts_196540 {
    char pad0[0x4C];
    char* items[4];   // 0x4C
    int on;           // 0x5C
    int off;          // 0x60
    char* w64;        // 0x64
    char* w68;        // 0x68
    char* w6C;        // 0x6C
    char pad70[8];
    int sel;          // 0x78
};

static inline void SetState_196540(char* w, int a, int b)
{
    *(int*)(w + 0x78) = a;
    *(int*)(w + 0x7C) = b;
}
static inline void SetItem_196540(sAudioOpts_196540* self, char* w, int k)
{
    self->items[k] = w;
    if (self->sel == k) SetState_196540(w, -1, self->on); else SetState_196540(w, -1, self->off);
}
extern "C" void cFEStateAudioOptions_onWidgetCreate(sAudioOpts_196540* self, char* w)
{
    int h = *(int*)(w + 0x38);
    if (h == GetHashValue32(D_004A1830)) {
        SetItem_196540(self, w, 0);
    } else if (h == GetHashValue32(D_004A1838)) {
        SetItem_196540(self, w, 2);
    } else if (h == GetHashValue32(D_004A1840)) {
        SetItem_196540(self, w, 1);
    } else if (h == GetHashValue32(D_004A1840)) { // the retail code tests this name twice
        SetItem_196540(self, w, 1);
    } else if (h == GetHashValue32(D_004A1848)) {
        SetItem_196540(self, w, 3);
    } else if (h == GetHashValue32(D_00460420)) {
        *(int*)(w + 0x18) = 0;
    } else if (h == GetHashValue32(D_00460430)) {
        *(int*)(w + 0x18) = 2;
    } else if (h == GetHashValue32(D_00460440)) {
        self->w68 = w;
        *(int*)(w + 0x18) = 1;
    } else if (h == GetHashValue32(D_00460450)) {
        self->w64 = w;
        *(int*)(w + 0x18) = 4;
    } else if (h == GetHashValue32(D_00460460)) {
        self->w6C = w;
        *(int*)(w + 0x18) = 3;
    }
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_00196B90(void* p, int a1, signed char idx, int a3);
extern "C" void cUIStateStack_pushSpecial(void* self, void* st, int a2, int a3);
extern "C" void func_0039F400(void* list, void* item);
extern "C" void* func_0039F190(void* list, int count);
extern "C" void func_001587F8(void* self, int a1, int a2, int value);
extern "C" void func_0028BF78(void* self, int state);
extern "C" void* func_0028B180();
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int GetHashValue32(char* str);
struct cUIText;
void cUIText_setUnicodeStringByID(cUIText* self, int id);
extern "C" cUIText* cUIScreen_getObjectByHashName(void* screen, int hash);
extern void* D_004A28A8;
extern char D_00460470[];
extern char D_00460488[];
extern char D_00460498[];
extern char D_004604B0[];
extern char D_004604C0[];
extern char D_004604E0[];
extern char D_004604F8[];
extern char D_00460510[];
extern char D_00460528[];
extern char D_00460540[];

struct sVEntry_196700 {
    short delta;
    short index;
    void* (*fn)(void*, ...);
};
struct sVEntryF_196700 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

static inline void Apply_196700(char* self, char* menu)
{
    struct sArr { char* it[1]; };
    sArr* arr = (sArr*)(self + 0x4C);
    int n = -1;
    int v = *(int*)(self + 0x60);
    char* it = arr->it[*(int*)(self + 0x78)];
    *(int*)(it + 0x78) = n;
    *(int*)(it + 0x7C) = v;
    int sel = *(int*)(menu + 0x18);
    int w = *(int*)(self + 0x5C);
    *(int*)(self + 0x78) = sel;
    char* it2 = arr->it[sel];
    *(int*)(it2 + 0x78) = n;
    *(int*)(it2 + 0x7C) = w;
}

static inline void Notify_196700(char* self)
{
    func_001587F8(cBE_getInterface_Fv(cBE_getBE(), 0xD), *(signed char*)(self + 0x44), *(int*)(self + 0x70), *(int*)(self + 0x78));
    func_0028BF78(func_0028B180(), *(int*)(self + 0x78));
}

static inline void SetText_196700(cUIText* text, char* id)
{
    cUIText_setUnicodeStringByID(text, GetHashValue32(id));
}

static inline void SetFlag_196700(char* obj, int v)
{
    sVEntryF_196700* vt = *(sVEntryF_196700**)(obj + 8);
    vt[6].fn(obj + vt[6].delta, v);
}

extern "C" void cFEStateAudioOptions_onWidgetEvent(char* self, char* menu, unsigned int msg)
{
    char* st;
    if (menu == 0) {
        return;
    }
    switch (msg) {
    case 5: {
        int sel = *(int*)(menu + 0x18);
        if (sel == 0 || sel == 2) {
            Apply_196700(self, menu);
            Notify_196700(self);
            return;
        } else if (sel == 1 || sel == 3) {
            if (*(int*)(self + 0x7C) != 0) {
                Apply_196700(self, menu);
                Notify_196700(self);
            }
            return;
        }
        if (sel != 4) {
            return;
        }
        if (*(int*)(self + 0x74) == 0 && *(int*)(self + 0x7C) == 0) {
            return;
        }
        st = (char*)func_00196B90(cMemMan_alloc(0x210, D_00460470, 0, 0), *(int*)(self + 0x10), *(signed char*)(self + 0x44), *(int*)(self + 0x74));
        if (*(int*)((char*)D_004A28A8 + 0x84) != 0) {
            *(int*)(st + 0x1C) = (*(int*)(st + 0x1C) & ~0x3F00) | 0x100;
            cUIStateStack_pushSpecial(*(char**)(self + 0x10) + 0x18, st, 0, 0);
            return;
        }
        func_0039F400(*(char**)(self + 0x10) + 0x18, st);
        return;
    }
    case 6: {
        Notify_196700(self);
        if (*(int*)((char*)D_004A28A8 + 0x84) != 0) {
            func_0039F190(*(char**)(self + 0x10) + 0x18, 1);
            return;
        }
        char* obj = **(char***)(self + 0x10);
        sVEntry_196700* vt = *(sVEntry_196700**)(obj + 4);
        char* st2 = (char*)vt[5].fn(obj + vt[5].delta, self, *(int*)(menu + 0x18));
        if (st2 != 0) {
            func_0039F400(*(char**)(self + 0x10) + 0x18, st2);
        }
        return;
    }
    case 1: {
        cUIText* text = cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_00460488));
        if (text == 0) {
            return;
        }
        int a = 0;
        int b = 0;
        int c = 0;
        switch (*(unsigned int*)(menu + 0x18)) {
        case 0:
            SetText_196700(text, D_00460498);
            break;
        case 2:
            SetText_196700(text, D_004604B0);
            break;
        case 1:
            if (*(int*)(self + 0x7C) == 0) {
                c = *(int*)((char*)D_004A28A8 + 0x84) != 0;
                if (*(int*)((char*)D_004A28A8 + 0x84) != 0) {
                    SetText_196700(text, D_004604C0);
                } else if (*(int*)(self + 0x74) != 0) {
                    SetText_196700(text, D_004604E0);
                } else {
                    SetText_196700(text, D_004604F8);
                }
            } else {
                SetText_196700(text, D_00460510);
            }
            break;
        case 3:
            if (*(int*)(self + 0x7C) == 0) {
                a = *(int*)((char*)D_004A28A8 + 0x84) != 0;
                if (*(int*)((char*)D_004A28A8 + 0x84) != 0) {
                    SetText_196700(text, D_004604C0);
                } else if (*(int*)(self + 0x74) != 0) {
                    SetText_196700(text, D_004604E0);
                } else {
                    SetText_196700(text, D_004604F8);
                }
            } else {
                SetText_196700(text, D_00460528);
            }
            break;
        case 4:
            if (*(int*)(self + 0x74) == 0 && *(int*)(self + 0x7C) == 0) {
                b = *(int*)((char*)D_004A28A8 + 0x84) != 0;
                if (*(int*)((char*)D_004A28A8 + 0x84) != 0) {
                    SetText_196700(text, D_004604C0);
                } else {
                    SetText_196700(text, D_004604F8);
                }
            } else {
                SetText_196700(text, D_00460540);
            }
            break;
        }
        if (*(int*)((char*)D_004A28A8 + 0x84) != 0) {
            SetFlag_196700(*(char**)(self + 0x64), b);
            SetFlag_196700(*(char**)(self + 0x68), c);
            SetFlag_196700(*(char**)(self + 0x6C), a);
        }
        return;
    }
    }
}

//100%
extern "C" int func_00196B08(void* self, int a1, int a2, int a3)
{
    if (a2 == 6 && (a3 == 2 || a3 == 3 || a3 == 4)) {
        if (a3 == 2 && *(int*)((char*)self + 0x7C) == 0) {
            goto ok;
        }
        if (a3 == 3 && *(int*)((char*)self + 0x7C) == 0) {
            goto ok;
        }
        if (a3 == 4 && *(int*)((char*)self + 0x74) == 0 && *(int*)((char*)self + 0x7C) == 0) {
        ok:
            return 0x10;
        }
    } else if (a2 == 8 || a2 == 9) {
        return 0;
    }
    return 0x101;
}

//100%
extern "C" void* func_0039E2A0(void* self);
extern "C" unsigned char func_001A1CD0(void* self, signed char a1);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBENewPlayerInterface_getPlayerCharID(void* self, int index);
int GetHashValue32(char* str);
extern "C" void func_003E6448(void* p, int c, int n);
extern "C" int func_00398380(void* list, int hash);
extern "C" int func_00150928(void* iface, int idx, int ch);
// PORT: 64-bit results (long is 8 bytes on the EE).
extern "C" long func_00158728(void* iface, int idx, int ch);
extern "C" long func_00158750(void* iface, int idx, int ch);
extern "C" void* func_0028B180();
extern "C" void func_00197AD8(void* self);
extern void* D_00469378[];
extern char D_0045DA48[];
extern char D_0045DA38[];
extern char D_0045DA58[];

struct sAudioState_196B90
{
    char pad0[0x4C];
    char buf[0x100];        // 0x4C
    int f14C;               // 0x14C
    int f150;               // 0x150
    char pad154[4];
    long f158;              // 0x158
    long f160;              // 0x160
    int f168;               // 0x168
    int f16C;               // 0x16C
    int f170;               // 0x170
    int a174[8];            // 0x174
    int a194[8];            // 0x194
    int f1B4;               // 0x1B4
    int f1B8;               // 0x1B8
    int a1BC[6];            // 0x1BC
    int f1D4;               // 0x1D4
    int f1D8;               // 0x1D8
    int f1DC;               // 0x1DC
    int f1E0;               // 0x1E0
    int f1E4;
    int f1E8;
    int f1EC;
    int f1F0;
    int f1F4;
    int f1F8;
    int f1FC;
    int f200;
    int f204;               // 0x204
    int f208;               // 0x208
    int f20C;               // 0x20C
};

static inline int Find_196B90(char* mgr, int hash)
{
    return func_00398380(mgr + 0x58, hash);
}

extern "C" void* func_00196B90(void* p, int a1, signed char idx, int a3)
{
    sAudioState_196B90* self = (sAudioState_196B90*)p;
    func_0039E2A0(self);
    *(int*)((char*)self + 0xC) = 0x11;
    *(void***)((char*)self + 0x8) = D_00469378;
    *(signed char*)((char*)self + 0x44) = idx;
    if (**(void***)((char*)self + 0x10) != 0)
        *(char*)((char*)self + 0x15) = func_001A1CD0(**(void***)((char*)self + 0x10), idx);
    func_003E6448(self->buf, 0, 0x100);
    self->f14C = 0;
    self->f150 = 0;
    self->f170 = 0;
    for (int i = 0; i < 8; i++)
    {
        self->a174[i] = 0;
        self->a194[i] = 0;
    }
    self->f1B4 = 0;
    self->f1B8 = 0;
    for (int i = 5; i >= 0; i--)
        self->a1BC[i] = 0;
    self->f16C = a3;
    self->f1D4 = 0;
    self->f1DC = 0;
    self->f1D8 = 0;
    self->f1E0 = 0;
    self->f1E4 = 0;
    self->f1E8 = 0;
    self->f1EC = 0;
    self->f1F0 = 0;
    self->f1F4 = 0;
    self->f1F8 = 0;
    self->f1FC = 0;
    self->f200 = 0;
    self->f158 = 0;
    {
        char* mgr = *(char**)((char*)self + 0x10);
        self->f204 = Find_196B90(mgr, GetHashValue32(D_0045DA48));
    }
    {
        char* mgr = *(char**)((char*)self + 0x10);
        self->f208 = Find_196B90(mgr, GetHashValue32(D_0045DA38));
    }
    {
        char* mgr = *(char**)((char*)self + 0x10);
        self->f20C = Find_196B90(mgr, GetHashValue32(D_0045DA58));
    }
    *(int*)((char*)self + 0x48) = cBENewPlayerInterface_getPlayerCharID(cBE_getInterface_Fv(cBE_getBE(), 1), *(signed char*)((char*)self + 0x44));
    self->f168 = func_00150928(cBE_getInterface_Fv(cBE_getBE(), 0xB), *(signed char*)((char*)self + 0x44), *(int*)((char*)self + 0x48));
    void* ifc = cBE_getInterface_Fv(cBE_getBE(), 0xD);
    self->f160 = func_00158728(ifc, *(signed char*)((char*)self + 0x44), *(int*)((char*)self + 0x48));
    self->f158 = func_00158750(ifc, *(signed char*)((char*)self + 0x44), *(int*)((char*)self + 0x48));
    self->f14C = *(int*)((char*)func_0028B180() + 0x504);
    func_00197AD8(self);
    return self;
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void func_0039B760(void* self, int a1);
extern "C" void* func_0039F9D8(void* self, int id);
extern void* D_004A28A8;
extern char D_004A18A8[];
extern char D_004A18B0[];
extern char D_00460578[];

struct sVEntry00196DB0 {
    short delta;
    short index;
    int (*fn)(void*, int, int);
};

extern "C" void func_00196DB0(void* self)
{
    char* name = D_004A18B0;
    if (*(void**)((char*)D_004A28A8 + 0x84) != 0) {
        name = D_00460578;
        void* list = *(char**)((char*)self + 0x10) + 0x18;
        char* obj = (char*)func_0039F9D8(list, GetHashValue32(D_004A18A8));
        if (obj != 0) {
            sVEntry00196DB0* vt = *(sVEntry00196DB0**)(obj + 8);
            vt[24].fn(obj + vt[24].delta, 3, 0);
        }
    }
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(name), 0);
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    func_0039B760(*(void**)((char*)self + 0x170), *(unsigned char*)((char*)self + 0x14C));
}

//100%
struct sVEntry00196E80 {
    short delta;
    short index;
    int (*fn)(void*, int, int);
};

int GetHashValue32(char* str);
void* func_0039E4A0(void* self);
extern "C" void* func_0039F9D8(void* self, int id);
extern char D_004A18A8[];
extern void* D_004A28A8;

extern "C" void func_00196E80(void* self)
{
    if (*(int*)((char*)D_004A28A8 + 0x84) != 0) {
        void* obj = func_0039F9D8(*(char**)((char*)self + 0x10) + 0x18, GetHashValue32(D_004A18A8));
        if (obj != 0) {
            sVEntry00196E80* e = &(*(sVEntry00196E80**)((char*)obj + 8))[24];
            e->fn((char*)obj + e->delta, 4, 0);
        }
    }
    func_0039E4A0(self);
}

//100%
extern "C" void func_00186518(void* self);
extern "C" void func_00197B88(void* self);
extern "C" void func_00197E70(void* self);
extern "C" void cFEStateRequestLine_updateButtonsText(void* self, int a1);
extern "C" void cFEStateRequestLine_updateHelpText(void* self, int a1);

extern "C" void func_00196F00(void* self)
{
    func_00186518(self);
    *(int*)((char*)self + 0x150) = 0;
    func_00197B88(self);
    func_00197E70(self);
    cFEStateRequestLine_updateButtonsText(self, 0);
    cFEStateRequestLine_updateHelpText(self, 0);
}

//100%
extern "C" void func_00197DB8(void* self);
extern "C" void cFEStateRequestLine_updateButtonsText(void* self, int a1);
extern "C" void cFEStateRequestLine_updateHelpText(void* self, int a1);

extern "C" int func_00196F50(void* self, int a1)
{
    if (a1 != 0) {
        func_00197DB8(self);
        cFEStateRequestLine_updateButtonsText(self, 0);
        cFEStateRequestLine_updateHelpText(self, 0);
    }
    return 0;
}

