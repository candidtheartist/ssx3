#include "common.h"

//100%
struct cUIText;
int GetHashValue32(char* str);
void cUIText_setUnicodeStringByID(cUIText* text, int id);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" unsigned char cUIListBox_addEntryByStringID(void* self, int id, int data);
extern "C" unsigned char cUIListBox_addEntryByAsciiString(void* self, const char* text, int data);
extern "C" int func_0039A768(void* self, int key, unsigned char* out);
extern "C" void func_0039A7A8(void* self, unsigned char a1);
extern "C" void func_00192740(void* self, int a1);
void func_00192968(void* self, int val);
extern "C" void func_00192970(void* self, void* screen);
extern "C" int func_00193F38(void* self, int player, int opt);
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern int D_004A1A70;
extern char D_00535BC8[];
extern char D_004A1710[8];
extern char D_004A1718[8];
extern char D_004A1720[8];
extern char D_004A1728[8];
extern char D_004A1730[8];
extern char D_004A1738[8];
extern char D_004A14F8[];
extern char* D_00441108[];
extern char D_0045FCC8[];
extern char D_0045FCD8[];
extern char D_0045DCC8[];
extern char D_0045DF40[];
extern char D_004A16E0[];
extern char D_004A16D8[];
extern char D_004A1758[];
extern char D_004A1760[];
extern char D_004A1768[];
extern char D_004A1770[];
extern char D_004A1778[];
extern char D_004A1780[];
extern char D_004A1580[];
extern char D_004A1588[];
extern char D_0045FCE8[];
extern char D_0045FCF8[];
extern char D_0045FD08[];

struct sSide_192D90 { char pad[8]; char* lb[11]; };

struct sVE_192D90 { short delta; short index; void (*fn)(void*, int); };

static inline void Show_192D90(char* o, int on)
{
    sVE_192D90* vt = *(sVE_192D90**)(o + 8);
    vt[9].fn(o + vt[9].delta, on);
}

static inline int IsOn_192D90()
{
    return D_004A1A70 == 1;
}

static inline char* Find_192D90(char* self, char* name)
{
    return (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(name));
}

extern "C" void cFEStateBraggingRights_onCreateScreen(char* self)
{
    char* ui = *(char**)(self + 0x10);
    void* scr = cUIEngine_addScreenByHashName(ui, self, GetHashValue32(D_0045FCC8), 0);
    *(void**)(self + 0x40) = scr;
    if (scr != 0) {
        cUIScreen_playFrame(scr, 0, 0);
    }
    char* a = self + 0x6D0;
    char* b = self + 0x704;
    if ((*(int*)(self + 0x1C) >> 4) & 1) {
        func_00192740(a, 0);
        func_00192740(b, 0);
    }
    int count = 0;
    cBE_getInterface_Fv(cBE_getBE(), 0);
    int mask = 0;
    switch (D_00535BC8[0x4A]) {
    case 0:
        *(char**)(self + 0x738) = D_004A1710;
        count = 6;
        break;
    case 1:
        *(char**)(self + 0x738) = D_004A1718;
        count = 7;
        break;
    case 3:
        *(char**)(self + 0x738) = D_004A1720;
        count = 7;
        break;
    case 2:
        *(char**)(self + 0x738) = D_004A1728;
        count = 7;
        break;
    case 4:
        *(char**)(self + 0x738) = D_004A1730;
        count = 5;
        break;
    case 5:
        *(char**)(self + 0x738) = D_004A1738;
        count = 7;
        break;
    }
    int i;
    for (i = 0; i < count; i++) {
        mask |= 1 << i;
    }
    func_00192968(a, mask);
    func_00192968(b, mask);
    func_00192970(a, *(void**)(self + 0x40));
    func_00192970(b, *(void**)(self + 0x40));
    char name[2];
    __builtin_memcpy(name, D_004A14F8, 2);
    int row;
    for (row = 0; row < count; row++) {
        name[0] = row + '1';
        cUIText* t = (cUIText*)Find_192D90(self, name);
        if (t != 0) {
            cUIText_setUnicodeStringByID(t, GetHashValue32(D_00441108[(*(signed char**)(self + 0x738))[row]]));
        }
        int col;
        for (col = 0; col < 2; col++) {
            unsigned char sel = 0;
            char* lb = ((sSide_192D90*)(self + 0x6D0))[col].lb[row];
            int type = (*(signed char**)(self + 0x738))[row];
            switch (type) {
            case 1 ... 6:
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045FCD8), 0);
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045DCC8), 1);
                func_0039A768(lb, func_00193F38(self, col, (*(signed char**)(self + 0x738))[row]), &sel);
                func_0039A7A8(lb, sel);
                break;
            case 0:
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045DF40), 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A16E0, 5);
                cUIListBox_addEntryByAsciiString(lb, D_004A16D8, 10);
                cUIListBox_addEntryByAsciiString(lb, D_004A1758, 15);
                cUIListBox_addEntryByAsciiString(lb, D_004A1760, 20);
                func_0039A768(lb, func_00193F38(self, col, (*(signed char**)(self + 0x738))[row]), &sel);
                func_0039A7A8(lb, sel);
                break;
            case 7:
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045DF40), 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A1768, 3000);
                cUIListBox_addEntryByAsciiString(lb, D_004A1770, 5000);
                cUIListBox_addEntryByAsciiString(lb, D_004A1778, 10000);
                cUIListBox_addEntryByAsciiString(lb, D_004A1780, 15000);
                func_0039A768(lb, func_00193F38(self, col, (*(signed char**)(self + 0x738))[row]), &sel);
                func_0039A7A8(lb, sel);
                break;
            }
        }
    }
    char* o = Find_192D90(self, D_004A1580);
    if (o != 0) {
        if (IsOn_192D90()) {
            Show_192D90(o, 1);
            char* p = Find_192D90(self, D_0045FCE8);
            if (p != 0) {
                Show_192D90(p, 0);
            }
            char* q = Find_192D90(self, D_0045FCF8);
            if (q != 0) {
                Show_192D90(q, 0);
            }
        } else {
            Show_192D90(o, 0);
        }
    }
    if (IsOn_192D90()) {
        char* p = Find_192D90(self, D_004A1588);
        if (p != 0) {
            Show_192D90(p, 0);
        }
        char* q = Find_192D90(self, D_0045FD08);
        if (q != 0) {
            Show_192D90(q, 0);
        }
    }
}

//100%
int func_00193310(void* self)
{
    return 0;
}

extern "C" void* func_0039E6B8(void* self);

//100%
void* func_00193318(void* self)
{
    return func_0039E6B8(self);
}

INCLUDE_ASM("fe/festatebigradio", func_00193338);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct cUIScreen;
int GetHashValue32(char* str);
unsigned short cUIScreen_getFrameByLabel(cUIScreen* self, int label);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern char D_004A1790[];
extern char D_004A1798[];
extern int D_004A1A70;
extern "C" void func_001A87D0(void* self, int a1);
extern "C" void func_001927B0(void* p);
// func_0039E4C0 returns nothing (ends in a void vcall).
void func_0039E4C0_v(void* self) __asm__("func_0039E4C0");

static inline int isOn00193568()
{
    return D_004A1A70 == 1;
}

static inline int get6F8_3568(void* p) { return *(int*)((char*)p + 0x6F8); }

extern "C" void func_00193568(void* self, int a1)
{
    if (isOn00193568()) {
        func_001A87D0(self, a1);
        return;
    }
    func_0039E4C0_v(self);
    if (*(int*)((char*)self + 0x6F8) != 0 && *(int*)((char*)self + 0x72C) == 0) {
        int frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0x40), GetHashValue32(D_004A1790));
        if (frame != 0xFFFF) {
            cUIScreen_playFrame(*(void**)((char*)self + 0x40), frame, 1);
        }
    } else if (get6F8_3568(self) == 0 && *(int*)((char*)self + 0x72C) != 0) {
        int frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0x40), GetHashValue32(D_004A1798));
        if (frame != 0xFFFF) {
            cUIScreen_playFrame(*(void**)((char*)self + 0x40), frame, 1);
        }
    }
    func_001927B0((char*)self + 0x6D0);
    func_001927B0((char*)self + 0x704);
}

//100%
int GetHashValue32(char* str);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
struct cUIText;
void cUIText_setAsciiString(cUIText* text, const char* s);
extern "C" int func_00146E98(void* iface, int a1);
extern "C" const char* func_0014EE58(void* iface, int a1);
extern char D_004A17A0[];
extern char D_004A17A8[];
extern char D_0045FD38[];
extern char D_0045FD48[];
extern char D_0045FD58[];
extern char D_0045FD68[];
extern char D_0045FD78[];
extern char D_0045FD88[];

class cUIObj_193650 {
public:
    int pad[2];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07(int on);
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
    virtual void v24(int on);
};

static inline int Is_193650(int id, char* s) { return id == GetHashValue32(s); }

extern "C" void cFEStateBraggingRights_onWidgetCreate(char* self, cUIObj_193650* w)
{
    char* wp = (char*)w;
    if (Is_193650(*(int*)(wp + 0x38), D_004A17A0)) {
        *(void**)(self + 0x6D0) = 0;
        w->v07(1);
        *(void**)(self + 0x6D0) = w;
        *(int*)(wp + 0x14) |= 1;
        *(int*)(wp + 0x90) |= 1;
    } else if (Is_193650(*(int*)(wp + 0x38), D_004A17A8)) {
        *(void**)(self + 0x704) = 0;
        w->v07(1);
        *(void**)(self + 0x704) = w;
        *(int*)(wp + 0x14) |= 1;
        *(int*)(wp + 0x90) |= 1;
    } else if (Is_193650(*(int*)(wp + 0x38), D_0045FD38) || Is_193650(*(int*)(wp + 0x38), D_0045FD48)) {
        void* p1 = cBE_getInterface_Fv(cBE_getBE(), 1);
        void* p2 = cBE_getInterface_Fv(cBE_getBE(), 2);
        cUIText_setAsciiString((cUIText*)w, func_0014EE58(p2, func_00146E98(p1, 0)));
    } else if (Is_193650(*(int*)(wp + 0x38), D_0045FD58) || Is_193650(*(int*)(wp + 0x38), D_0045FD68)) {
        void* p1 = cBE_getInterface_Fv(cBE_getBE(), 1);
        void* p2 = cBE_getInterface_Fv(cBE_getBE(), 2);
        cUIText_setAsciiString((cUIText*)w, func_0014EE58(p2, func_00146E98(p1, 1)));
    } else if (Is_193650(*(int*)(wp + 0x38), D_0045FD78)) {
        *(void**)(self + 0x6D4) = w;
    } else if (Is_193650(*(int*)(wp + 0x38), D_0045FD88)) {
        *(void**)(self + 0x708) = w;
    } else {
        char name[3];
        name[2] = 0;
        for (int i = 0; i < 2; i++) {
            void** slots = (void**)(self + i * 0x34 + 0x6D8);
            for (int j = 0; j < 8; j++) {
                name[0] = '1' + i;
                name[1] = '1' + j;
                if (*(int*)(wp + 0x38) == GetHashValue32(name)) {
                    slots[j] = w;
                    *(int*)(wp + 0x18) = i;
                    *(int*)(wp + 0x14) &= ~1;
                    w->v24(1);
                }
            }
        }
    }
}

//100%
int GetHashValue32(char* str);
void func_001C57C0(void* self, int a1, int a2);
extern "C" void* func_001A9C50(void* self);
extern "C" void func_001A9BC0(void* self, void* popup);
extern "C" void func_001A8918(void* self, int a1, int msg);
extern "C" int func_00192918(void* self, int val);
extern "C" void func_00192740(void* self, int a1);
extern "C" void func_001927B0(void* p);
extern "C" void func_00194080(void* self);
extern "C" void func_00193DE0(void* self, int player, int opt, int value);
extern "C" void func_00265688(void* snd);
extern "C" void func_00265568(void* self, int a, int b);
extern "C" int func_0039A738(void* self);
extern "C" void func_0039F400_38F8(void* list, void* item) __asm__("func_0039F400");
extern "C" void func_003E6448(void* p, int v, int n);
extern int D_004A1A70;
extern void* D_004A33CC;
extern char D_0045DCC8[];
extern char D_0045FCD8[];
extern char D_0045FD98[];
extern char D_005308B8[];

class cBRObj_38F8 {
public:
    int f0;
    virtual void* v01(void* owner, int idx);
    virtual void* v02(void* owner, int idx);
    virtual void* v03(void* owner, int idx);
    virtual void* v04(void* owner, int idx);
    virtual void* v05(void* owner, int idx);
};

static inline int isOn001938F8()
{
    return D_004A1A70 == 1;
}

extern "C" void func_001938F8(char* self, char* item, int id)
{
    int k;
    switch (id) {
    case 5:
        {
            int i = 0;
            do {
                if (func_00192918(self + 0x6D0 + i * 0x34, (int)item) != -1) {
                    if (isOn001938F8() && i == 0)
                        func_00265688(D_004A33CC);
                    func_00192740(self + 0x6D0 + i * 0x34, 1);
                    func_00194080(self);
                    break;
                }
                i++;
            } while (i < 2);
        }
        if (!isOn001938F8() && *(int*)(self + 0x6F8) != 0 && *(int*)(self + 0x72C) != 0) {
            cBRObj_38F8* o = **(cBRObj_38F8***)(self + 0x10);
            void* r = o->v04(self, *(int*)(item + 0x18));
            if (r != 0)
                func_0039F400_38F8(*(char**)(self + 0x10) + 0x18, r);
        }
        break;
    case 6:
        if (isOn001938F8()) {
            char* p = (char*)func_001A9C50(self);
            *(int*)(p + 0xBC) = 2;
            char* sub = p + 0xBC;
            *(int*)(p + 0xC4) = GetHashValue32(D_0045FD98);
            *(int*)(p + 0xC0) = 3;
            func_001C57C0(sub, 0, GetHashValue32(D_0045DCC8));
            func_001C57C0(sub, 1, GetHashValue32(D_0045FCD8));
            *(int*)(p + 0x150) = 0x838;
            *(int*)(p + 0x168) = 1;
            func_001A9BC0(self, p);
        } else {
            cBRObj_38F8* o = **(cBRObj_38F8***)(self + 0x10);
            void* r = o->v05(self, *(int*)(item + 0x18));
            if (r != 0)
                func_0039F400_38F8(*(char**)(self + 0x10) + 0x18, r);
            func_003E6448(D_005308B8, 0, 0x20);
        }
        break;
    case 1:
    case 2:
        k = *(int*)(item + 0x18);
        func_001927B0(self + 0x6D0 + k * 0x34);
        break;
    case 7:
        if (isOn001938F8())
            func_001A8918(self, (int)item, id);
        break;
    case 9:
        if (isOn001938F8()) {
            void* snd = D_004A33CC;
            int h = func_00192918(self + 0x6D0, (int)item);
            func_00265568(snd, h, func_0039A738(item));
        } else {
            k = *(int*)(item + 0x18);
            int r = func_00192918(self + 0x6D0 + k * 0x34, (int)item);
            int v = (*(signed char**)(self + 0x738))[r];
            if (v != -1)
                func_00193DE0(self, k, v, func_0039A738(item));
        }
        break;
    }
}


//100%
int GetHashValue32(char* str);
void func_001DA510(void* self, int i, int a, int b);
void func_001DA528(void* self, int val);
void func_001DA530(void* self, int i, int value);
extern char D_0045FDE8[];
extern char D_0045FE00[];
extern char D_0045FE20[];
extern char D_0045FE40[];
extern char D_0045FE60[];
extern char D_0045FE80[];
extern char D_0045FE98[];

extern "C" void func_00193C00(void* self, void* popup)
{
    func_001DA528(popup, 4);
    *(int*)((char*)popup + 0x54) = GetHashValue32(D_0045FDE8);
    func_001DA530(popup, 0, GetHashValue32(D_0045FE00));
    func_001DA530(popup, 1, GetHashValue32(D_0045FE20));
    func_001DA510(popup, 0, GetHashValue32(D_0045FE40), 4);
    func_001DA510(popup, 1, GetHashValue32(D_0045FE60), 3);
    func_001DA510(popup, 2, GetHashValue32(D_0045FE80), 0);
    func_001DA510(popup, 3, GetHashValue32(D_0045FE98), 1);
}

//100%
extern int D_004A1A70;
extern void* D_004A33CC;
extern "C" void func_001927B0(void* p);
extern "C" void func_00265458(void* self, int id);

static inline int isOn00193CF8()
{
    return D_004A1A70 == 1;
}

extern "C" int func_00193CF8(char* self, unsigned char* item, int kind)
{
    char* a = self + 0x6D0;
    char* list;
    int first = 0;
    if (*(unsigned char**)a == item) {
        list = a;
        first = 1;
    } else {
        list = self + 0x704;
        if (*(unsigned char**)list != item)
            list = 0;
    }
    switch (kind) {
    case 8:
    case 9:
        return 0x100;
    case 5:
        if (isOn00193CF8() && first)
            func_00265458(D_004A33CC, item[0x95]);
        func_001927B0(list);
        return 0x101;
    case 6:
        if (*(int*)(self + 0x6F8) == 0 || *(int*)(self + 0x72C) == 0)
            return 1;
        return 0x101;
    case 7:
        if (isOn00193CF8())
            return 0;
        break;
    }
    return 0x101;
}

//100%
struct sBigRadioBits_3DE0 {
    unsigned int b0 : 1;
    unsigned int b1 : 1;
    unsigned int b2 : 1;
    unsigned int b3 : 1;
    unsigned int b4 : 1;
    unsigned int b5 : 1;
};
struct sBigRadioOpt_3DE0 {
    sBigRadioBits_3DE0 flags;
    int f4;
    int f8;
};
extern sBigRadioOpt_3DE0 D_005308B8_3DE0[] __asm__("D_005308B8");

extern "C" void func_00193DE0(void* self, int player, int opt, int value)
{
    switch (opt) {
    case 0: {
        unsigned int o = player == 0;
        D_005308B8_3DE0[o].f8 = value;
        break;
    }
    case 1: {
        unsigned int o = player == 0;
        D_005308B8_3DE0[o].flags.b3 = value;
        break;
    }
    case 2: {
        unsigned int o = player == 0;
        D_005308B8_3DE0[o].flags.b0 = value;
        break;
    }
    case 3:
        D_005308B8_3DE0[player].flags.b4 = value;
        break;
    case 4:
        D_005308B8_3DE0[player].flags.b5 = value;
        break;
    case 5:
        D_005308B8_3DE0[player].flags.b1 = value;
        break;
    case 6:
        D_005308B8_3DE0[player].flags.b2 = value;
        break;
    case 7: {
        unsigned int o = player == 0;
        D_005308B8_3DE0[o].f4 = value;
        break;
    }
    }
}

//100%
struct sBigRadioOpt_3F38 {
    unsigned int flags;
    int f4;
    int f8;
};
extern sBigRadioOpt_3F38 D_005308B8_3F38[] __asm__("D_005308B8");

extern "C" int func_00193F38(void* self, int player, int opt)
{
    switch (opt) {
    case 0: {
        unsigned int o = player == 0;
        return D_005308B8_3F38[o].f8;
    }
    case 1: {
        unsigned int o = player == 0;
        return (D_005308B8_3F38[o].flags >> 3) & 1;
    }
    case 2: {
        unsigned int o = player == 0;
        return D_005308B8_3F38[o].flags & 1;
    }
    case 3:
        return (D_005308B8_3F38[player].flags >> 4) & 1;
    case 4:
        return (D_005308B8_3F38[player].flags >> 5) & 1;
    case 5:
        return (D_005308B8_3F38[player].flags >> 1) & 1;
    case 6:
        return (D_005308B8_3F38[player].flags >> 2) & 1;
    case 7: {
        unsigned int o = player == 0;
        return D_005308B8_3F38[o].f4;
    }
    }
    return -1;
}

//100%
struct cUIScreen;
int GetHashValue32(char* str);
unsigned short cUIScreen_getFrameByLabel(cUIScreen* self, int label);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern char D_004A1790[];
extern char D_004A1798[];

static inline int get6F8_4080(void* p) { return *(int*)((char*)p + 0x6F8); }
extern "C" void func_00194080(void* self)
{
    if (*(int*)((char*)self + 0x6F8) != 0 && *(int*)((char*)self + 0x72C) == 0) {
        int frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0x40), GetHashValue32(D_004A1790));
        if (frame != 0xFFFF) {
            cUIScreen_playFrame(*(void**)((char*)self + 0x40), frame, 1);
        }
    } else if (get6F8_4080(self) == 0 && *(int*)((char*)self + 0x72C) != 0) {
        int frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0x40), GetHashValue32(D_004A1798));
        if (frame != 0xFFFF) {
            cUIScreen_playFrame(*(void**)((char*)self + 0x40), frame, 1);
        }
    }
}

//100%
extern int D_004A1A70;
extern "C" void* func_001A8B88(void* self, int size, int a2);

static inline int isOn00194138()
{
    return D_004A1A70 == 1;
}

extern "C" void* cFEStateBraggingRights_v24(void* self, int a1, int a2)
{
    if (isOn00194138()) {
        return func_001A8B88(self, a1, a2);
    }
    return 0;
}

//100%
extern int D_004A1A70;
extern "C" void func_00194440(void* self, void* a1, int a2);
extern "C" int func_001A97B8(void* self, void* a1, int a2);

static inline int isOn00194168()
{
    return D_004A1A70 == 1;
}

extern "C" void func_00194168(void* self, void* a1, int a2)
{
    if (isOn00194168()) {
        if (*(int*)((char*)a1 + 0x18) == 0x838) {
            func_00194440(self, a1, a2);
        } else {
            func_001A97B8(self, a1, a2);
        }
    }
}

struct sGroup_41B0 {
    void* menu;
    char pad4[0x8 - 0x4];
    void* items[(0x34 - 0x8) / 4];
};
struct sMsg_41B0 {
    char pad0[0x8];
    int group;
    int item;
    int key;
};
extern "C" void cUIMenu_setSelectedByIndex(void* menu, unsigned char idx);
extern "C" void func_001AB288(void* self);
extern "C" int func_001A8E40(void* self, int msg, void* data);
extern "C" int func_0025DA90(void* self);
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_001B1F88(void* mem, int a1);
extern "C" void* func_001BFBB8(void* mem, int a1);
extern "C" void func_001A8A40(void* self, void* obj);
extern void* D_004A3028;
extern const char D_0045FF10[];
extern const char D_0045FF28[];
extern char D_004A1788[];
extern char D_004A17B0[];

struct sBigRadio_41B0 {
    char pad0[0x10];
    int f10;
    char pad14[0x40 - 0x14];
    void* screen;
    char pad44[0x6D0 - 0x44];
    sGroup_41B0 groups[2];
    char* opts;
};

extern "C" int cFEStateBraggingRights_v31(sBigRadio_41B0* self, int msg, sMsg_41B0* data)
{
    switch (msg) {
    case 0xFB:
        cUIMenu_setSelectedByIndex(self->groups[data->group].menu, data->item);
        break;
    case 0xFC: {
        unsigned char sel;
        void* item = (&self->groups[data->group])->items[data->item];
        if (func_0039A768(item, data->key, &sel) == 0) {
            return 0;
        }
        func_0039A7A8(item, sel);
        int opt = *(signed char*)(self->opts + func_00192918(&self->groups[data->group], (int)item));
        if (opt == -1) {
            return 0;
        }
        int player = data->group;
        func_00193DE0(self, player, opt, func_0039A738(item));
        break;
    }
    case 0xFD:
        func_00192740(&self->groups[data->group], 1);
        func_00194080(self);
        break;
    case 0xEE:
    case 0xF1:
    case 0xF8:
    case 0xFA:
    case 0x112:
    case 0x113:
        func_001AB288(self);
        break;
    case 0x10C: {
        if (func_0025DA90(D_004A3028) != 0) {
            func_001A8A40(self, func_001B1F88(cMemMan_alloc(0x73C, D_0045FF10, 0, 0), self->f10));
        } else {
            func_001A8A40(self, func_001BFBB8(cMemMan_alloc(0x6D0, D_0045FF28, 0, 0), self->f10));
        }
        break;
    }
    case 0xFE: {
        func_00192740(&self->groups[data->group], 0);
        func_00192970(&self->groups[data->group], self->screen);
        cUIMenu_setSelectedByIndex(self->groups[data->group].menu, 0);
        int frame;
        if (data->group == 0)
            frame = cUIScreen_getFrameByLabel((cUIScreen*)self->screen, GetHashValue32(D_004A1788));
        else
            frame = cUIScreen_getFrameByLabel((cUIScreen*)self->screen, GetHashValue32(D_004A17B0));
        if (frame == 0xFFFF) {
            return 0;
        }
        cUIScreen_playFrame(self->screen, frame, 1);
        break;
    }
    default:
        return func_001A8E40(self, msg, data);
    }
    return 0;
}

//100%
extern void* D_004A33CC;
extern "C" void func_00265768(void* snd, int id);
void func_001A94D8(void* self);
extern "C" int func_001A97B8(void* self, void* a1, int a2);

extern "C" void func_00194440(void* self, void* a1, int a2)
{
    if (a2 == 0xF) {
        if (D_004A33CC != 0) {
            func_00265768(D_004A33CC, 0xF9);
        }
        func_001A94D8(self);
    } else {
        func_001A97B8(self, a1, a2);
    }
}

//100%
struct sColor4_4498 {
    float x, y, z, w;
};

struct sVEntry00194498a {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sVEntry00194498b {
    short delta;
    short index;
    void (*fn)(void*, sColor4_4498*);
};

extern "C" void func_00194498(void* self)
{
    sVEntry00194498a* vt = *(sVEntry00194498a**)((char*)self + 8);
    vt[8].fn((char*)self + vt[8].delta, 1);
    sColor4_4498 c = *(sColor4_4498*)((char*)self + 0x1C);
    if (c.x > 0.5f) {
        c.x = 0.5f;
        sVEntry00194498b* vt2 = *(sVEntry00194498b**)((char*)self + 8);
        vt2[11].fn((char*)self + vt2[11].delta, &c);
    }
}

