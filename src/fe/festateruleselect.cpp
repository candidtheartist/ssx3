#include "common.h"

//100%
struct cUIText;
struct cUIScreen;
int GetHashValue32(char* str);
void cUIText_setUnicodeStringByID(cUIText* text, int id);
int cUIScreen_getFrameByLabel(cUIScreen* screen, int hash);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" unsigned char cUIListBox_addEntryByStringID(void* self, int id, int data);
extern "C" unsigned char cUIListBox_addEntryByAsciiString(void* self, const char* text, unsigned int data);
extern "C" void func_0039A670(void* self);
extern "C" int func_0039A768(void* self, int key, unsigned char* out);
extern "C" void func_0039A7A8(void* self, unsigned char a1);
extern "C" int func_00192240(void* self, int opt);
extern "C" void cFEStateRuleSelect_updateMenuColor(void* self);
extern char D_004A16A8[];
extern char D_004A16B0[];
extern long long D_004A1708_1390[] __asm__("D_004A1708");
extern long long D_0045FAD8_1390[] __asm__("D_0045FAD8");
extern char D_00441008[];
extern char* D_00441018[];
extern char D_004A1398[];
extern char D_0045E270[];
extern char D_0045E280[];
extern char D_0045DF40[];
extern char D_0045E028[];
extern char D_0045FA80[];
extern char D_0045DCC8[];
extern char D_0045FA90[];
extern char D_0045FAA8[];
extern char D_0045FAC0[];
extern char D_004A16B8[];
extern char D_004A16C0[];
extern char D_004A16C8[];
extern char D_004A16D0[];
extern char D_004A16D8[];
extern char D_004A16E0[];
extern char D_004A16E8[];
extern char D_004A16F0[];
extern char D_004A16F8[];
extern char D_004A1700[];
extern char D_004A13A0[];
extern char D_004A14F8[];
extern char D_004A1500[];
extern char D_004A1508[];
extern char D_004A1510[];
extern char D_004A1518[];

struct sVE_1390 { short delta; short index; void (*fn)(void*, int); };

static inline void Hide_1390(char* o)
{
    sVE_1390* vt = *(sVE_1390**)(o + 8);
    vt[9].fn(o + vt[9].delta, 0);
}

extern "C" void cFEStateRuleSelect_setupMenu(void* selfp, signed char start)
{
    char* self = (char*)selfp;
    char box[3];
    char text[3];
    unsigned char sel;
    signed char i;
    __builtin_memcpy(box, D_004A16A8, 3);
    __builtin_memcpy(text, D_004A16B0, 3);
    i = 0;
    do {
        char* lb = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(box));
        cUIText* tx = (cUIText*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(text));
        if (lb != 0 && tx != 0) {
            signed char idx = i + start;
            if (idx >= *(signed char*)(self + 0x50)) {
                break;
            }
            int rule = (*(signed char**)(self + 0x48))[idx];
            int type = D_00441008[rule];
            cUIText_setUnicodeStringByID(tx, GetHashValue32(D_00441018[rule]));
            func_0039A670(lb);
            *(int*)(lb + 0x18) = rule;
            switch (type) {
            case 0:
                break;
            case 1:
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045DF40), 0);
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045E028), 1);
                break;
            case 2:
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045FA80), 0);
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045DCC8), 1);
                break;
            case 3:
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045DF40), 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A16B8, 0x5A);
                cUIListBox_addEntryByAsciiString(lb, D_004A16C0, 0x50);
                cUIListBox_addEntryByAsciiString(lb, D_004A16C8, 0x46);
                cUIListBox_addEntryByAsciiString(lb, D_004A16D0, 0x3C);
                break;
            case 4:
                cUIListBox_addEntryByAsciiString(lb, D_004A16D8, 10);
                cUIListBox_addEntryByAsciiString(lb, D_004A16E0, 5);
                cUIListBox_addEntryByAsciiString(lb, D_004A16E8, 3);
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045DF40), 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A16F0, -3);
                cUIListBox_addEntryByAsciiString(lb, D_004A16F8, -5);
                cUIListBox_addEntryByAsciiString(lb, D_004A1700, -10);
                break;
            case 5:
                cUIListBox_addEntryByAsciiString(lb, D_004A13A0, 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A14F8, 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A1500, 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A1508, 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A1510, 0);
                cUIListBox_addEntryByAsciiString(lb, D_004A1518, 0);
                break;
            case 6:
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045FA90), 0);
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045FAA8), 0);
                cUIListBox_addEntryByStringID(lb, GetHashValue32(D_0045FAC0), 0);
                break;
            }
            if (rule != 0) {
                func_0039A768(lb, func_00192240(self, rule), &sel);
                func_0039A7A8(lb, sel);
            } else {
                Hide_1390(lb);
            }
        }
        if (i < 9) {
            box[0]++;
            text[0]++;
        } else {
            text[0] = box[0] = i + 0x58;
        }
        i++;
    } while (i < 11);
    char frame[0x20];
    int cur = 0xFF;
    char* o = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_004A1398));
    if (o != 0) {
        cur = *(unsigned char*)(o + 0x95);
    }
    if ((*(signed char**)(self + 0x48))[cur] == 0) {
        char* a = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_0045E270));
        char* b = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_0045E280));
        if (a != 0) {
            Hide_1390(a);
        }
        if (b != 0) {
            Hide_1390(b);
        }
        __builtin_memcpy(frame, D_004A1708_1390, 7);
    } else {
        __builtin_memcpy(frame, D_0045FAD8_1390, 10);
    }
    int f = cUIScreen_getFrameByLabel(*(cUIScreen**)(self + 0x40), GetHashValue32(frame));
    if (f != 0xFFFF) {
        cUIScreen_playFrame(*(void**)(self + 0x40), f, 1);
    }
    cFEStateRuleSelect_updateMenuColor(self);
}

//100%
struct cUIText;
int GetHashValue32(char* str);
void cUIText_setUnicodeStringByID(cUIText* text, int id);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv_1940(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void cFEStateRuleSelect_setupMenu(void* self, signed char idx);
extern "C" void func_0039B760(void* self, unsigned char a1);
extern "C" void cUIMenu_setSelectedByIndex(void* menu, unsigned char idx);
extern "C" void func_003E6448(void* dst, int c, int n);
extern char D_00535BC8[];
extern char D_005308B8[];
extern char D_0045FB10[];
extern char D_0045FB20[];
extern char D_004A1398[];
extern char* D_00441058[];
extern signed char D_00441098[];
extern signed char D_004410A8[];
extern signed char D_004410B8[];
extern signed char D_004A1690[8];
extern signed char D_004A1698[8];
extern signed char D_004A16A0[8];
extern char D_004A16A8[];
extern char D_004A13A0[];

struct sVE_1940 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sObj_1940 {
    char pad0[0x8];
    sVE_1940* vt;
};

extern "C" void cFEStateRuleSelect_onCreateScreen(char* self)
{
    void* engine = *(void**)(self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0045FB10), 0);
    *(void**)(self + 0x40) = screen;
    if (screen != 0)
        cUIScreen_playFrame(screen, 0, 0);
    *(signed char**)(self + 0x48) = 0;
    int count = 0;
    cBE_getInterface_Fv_1940(cBE_getBE(), 0);
    switch ((signed char)D_00535BC8[0x4A]) {
    case 0:
        *(signed char**)(self + 0x48) = D_00441098;
        count = 11;
        break;
    case 1:
        *(signed char**)(self + 0x48) = D_004410A8;
        count = 10;
        break;
    case 3:
        *(signed char**)(self + 0x48) = D_004A1690;
        count = 8;
        break;
    case 2:
        *(signed char**)(self + 0x48) = D_004A1698;
        count = 8;
        break;
    case 4:
        *(signed char**)(self + 0x48) = D_004410B8;
        count = 11;
        break;
    case 5:
        *(signed char**)(self + 0x48) = D_004A16A0;
        count = 8;
        break;
    }
    for (int i = 0; i < 15; i++)
        self[0x51 + i] = 0;
    self[0x50] = count;
    func_003E6448(D_005308B8, 0, 0x20);
    cFEStateRuleSelect_setupMenu(self, 0);
    char* menu = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_004A1398));
    if (menu != 0) {
        *(int*)(menu + 0x14) |= 0x80;
        func_0039B760(menu, count);
        cUIMenu_setSelectedByIndex(menu, 0);
        cUIText* t = (cUIText*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_0045FB20));
        signed char sel = **(signed char**)(self + 0x48);
        if (t != 0)
            cUIText_setUnicodeStringByID(t, GetHashValue32(D_00441058[sel]));
    }
    char name0[16];
    char name1[16];
    __builtin_memcpy(name0, D_004A16A8, 3);
    __builtin_memcpy(name1, D_004A13A0, 2);
    for (signed char i = 0; i < 11; i++) {
        char* a = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(name0));
        *(int*)(a + 0x14) &= ~1;
        char* b = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(name1));
        if (i >= count) {
            ((sObj_1940*)b)->vt[9].fn(b + ((sObj_1940*)b)->vt[9].delta, 0);
            ((sObj_1940*)b)->vt[8].fn(b + ((sObj_1940*)b)->vt[8].delta, 1);
        }
        if (i < 9) {
            name1[0]++;
            name0[0]++;
        } else {
            name0[0] = name1[0] = i + 0x58;
        }
    }
}


extern "C" void* func_0039E4C0(void* self);

//100%
void* func_00191C48(void* self)
{
    return func_0039E4C0(self);
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void cUIStateStack_pushSpecial(void* stack, void* state, int a2, int a3);
extern "C" void* func_001887A0(void* mem, void* owner, int a2);
extern "C" void func_00192088(void* self, int idx, int a2);
struct sRuleSel_2380;
extern "C" void cFEStateRuleSelect_ApplyRuleDependencies(sRuleSel_2380* self, void* item);
extern "C" int func_0039A738(void* self);
extern "C" void func_0039F400(void* stack, void* state);
extern "C" void func_003E6448(void* dst, int c, int n);
extern char D_0045D698[];
extern char D_005308B8[];

struct sVE_1C68 {
    short delta;
    short index;
    void* (*fn)(void*, void*, int);
};

struct sMsg_1C68 {
    char pad_0x0[0x18];
    int id;             // 0x18
    char pad_0x1C[0x60];
    int* info;          // 0x7C
};

extern "C" void func_00191C68(char* self, sMsg_1C68* msg, unsigned int type)
{
    if (msg == 0) {
        return;
    }
    switch (type) {
    case 5:
        if (msg->info[6] == 0) {
            char* o = **(char***)(self + 0x10);
            sVE_1C68* vt = *(sVE_1C68**)(o + 0x4);
            void* st = vt[4].fn(o + vt[4].delta, self, msg->id);
            if (st) {
                func_0039F400(*(char**)(self + 0x10) + 0x18, st);
            }
        }
        break;
    case 6: {
        char* o = **(char***)(self + 0x10);
        sVE_1C68* vt = *(sVE_1C68**)(o + 0x4);
        void* st = vt[5].fn(o + vt[5].delta, self, msg->id);
        if (st) {
            func_0039F400(*(char**)(self + 0x10) + 0x18, st);
        }
        func_003E6448(D_005308B8, 0, 0x20);
        break;
    }
    case 9: {
        int id = msg->id;
        func_00192088(self, id, func_0039A738(msg));
        cFEStateRuleSelect_ApplyRuleDependencies((sRuleSel_2380*)self, msg);
        break;
    }
    case 7: {
        char* st = (char*)func_001887A0(cMemMan_alloc(0x54, D_0045D698, 0x100, 0), *(void**)(self + 0x10), 1);
        *(int*)(st + 0x1C) = (*(int*)(st + 0x1C) & ~0x3F00) | 0x100;
        cUIStateStack_pushSpecial(*(char**)(self + 0x10) + 0x18, st, 0, 0);
        break;
    }
    }
}

//100%
int GetHashValue32(char* str);
extern char D_004A13A0[];

extern "C" int func_00191E08(void* self, void* msg)
{
    int id = *(int*)((char*)msg + 0x38);
    return (id == GetHashValue32(D_004A13A0)) ? 0x101 : 0x100;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct cUIScreen;
struct cUIText;
int GetHashValue32(char* str);
extern "C" void cFEStateRuleSelect_setupMenu(void* self, signed char idx);
int cUIScreen_getFrameByLabel(cUIScreen* self, int hash);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
void cUIText_setUnicodeStringByID(cUIText* text, int id);
extern char D_0045E270[];
extern char D_0045E280[];
extern char D_0045FB20[];
extern char* D_00441058[];

// PORT: the frame labels are copied with the builtin block move (the original likely used
// strcpy on string literals); the two strings live at these symbols.
extern char D_0045FAD8[] __attribute__((aligned(8)));
extern char D_004A1708[] __attribute__((aligned(8)));

struct sVE_1E48 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

static inline void SetVisible_1E48(char* o, int on)
{
    sVE_1E48* vt = *(sVE_1E48**)(o + 0x8);
    vt[9].fn(o + vt[9].delta, on);
}

extern "C" int func_00191E48(char* self, void* unused, unsigned int type, int idx)
{
    switch (type) {
    case 9:
        return 0x100;
    case 1: {
        int sel = (*(signed char**)(self + 0x48))[idx];
        int play = 0;
        char* a = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_0045E270));
        char* b = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_0045E280));
        int locked = *(signed char*)(self + sel + 0x51) < 1;
        cUIText* t = (cUIText*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(D_0045FB20));
        if (locked && t) {
            cUIText_setUnicodeStringByID(t, GetHashValue32(D_00441058[sel]));
        }
        char label[32];
        if (sel) {
            if (locked) {
                if (a) SetVisible_1E48(a, 1);
                if (b) SetVisible_1E48(b, 1);
                play = 1;
                __builtin_memcpy(label, D_0045FAD8, 10);
            }
        } else {
            if (a) SetVisible_1E48(a, 0);
            if (b) SetVisible_1E48(b, 0);
            play = 1;
            __builtin_memcpy(label, D_004A1708, 7);
        }
        if (play) {
            int f = cUIScreen_getFrameByLabel(*(cUIScreen**)(self + 0x40), GetHashValue32(label));
            if (f != 0xFFFF) {
                cUIScreen_playFrame(*(void**)(self + 0x40), f, 1);
            }
        }
        return locked;
    }
    case 4:
        cFEStateRuleSelect_setupMenu(self, idx);
        return 0x101;
    }
    return 0x101;
}

//100%
extern int D_005308B8_2088[] __asm__("D_005308B8");
extern int D_005308D4_2088[] __asm__("D_005308D4");

extern "C" void func_00192088(void* self, int idx, int v)
{
    switch (idx) {
    case 4:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -2) | ((v & 1) << 0);
        break;
    case 3:
        D_005308B8_2088[0] = (D_005308B8_2088[0] & -9) | ((v & 1) << 3);
        break;
    case 5:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -9) | ((v & 1) << 3);
        break;
    case 14:
        D_005308B8_2088[0] = (D_005308B8_2088[0] & -33) | ((v & 1) << 5);
        break;
    case 7:
        D_005308B8_2088[0] = (D_005308B8_2088[0] & -17) | ((v & 1) << 4);
        break;
    case 8:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -3) | ((v & 1) << 1);
        break;
    case 1:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -5) | ((v & 1) << 2);
        break;
    case 2:
        D_005308D4_2088[0] = v;
        break;
    case 6:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -17) | ((v & 1) << 4);
        break;
    case 9:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -33) | ((v & 1) << 5);
        break;
    case 10:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -65) | ((v & 1) << 6);
        break;
    case 11:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -129) | ((v & 1) << 7);
        break;
    case 12:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -257) | ((v & 1) << 8);
        break;
    case 13:
        D_005308B8_2088[6] = (D_005308B8_2088[6] & -513) | ((v & 1) << 9);
        break;
    }
}

//100%
extern int D_005308D0_2240[] __asm__("D_005308D0");
extern unsigned int D_005308B8_2240[] __asm__("D_005308B8");
extern int D_005308D4_2240[] __asm__("D_005308D4");

extern "C" int func_00192240(void* self, int opt)
{
    switch (opt) {
    case 4:
        return D_005308D0_2240[0] & 1;
    case 3:
        return (D_005308B8_2240[0] >> 3) & 1;
    case 5:
        return (D_005308D0_2240[0] & 0x8) != 0;
    case 14:
        return (D_005308B8_2240[0] >> 5) & 1;
    case 7:
        return (D_005308B8_2240[0] >> 4) & 1;
    case 8:
        return (D_005308D0_2240[0] & 0x2) != 0;
    case 1:
        return (D_005308D0_2240[0] & 0x4) != 0;
    case 2:
        return D_005308D4_2240[0];
    case 6:
        return (D_005308D0_2240[0] & 0x10) != 0;
    case 9:
        return (D_005308D0_2240[0] & 0x20) != 0;
    case 10:
        return (D_005308D0_2240[0] & 0x40) != 0;
    case 11:
        return (D_005308D0_2240[0] & 0x80) != 0;
    case 12:
        return (D_005308D0_2240[0] & 0x100) != 0;
    case 13:
        return (D_005308D0_2240[0] & 0x200) != 0;
    }
    return -1;
}

//100%
extern "C" int func_0039A738(void* self);
extern "C" void func_00192088(void* self, int idx, int a2);
extern "C" void cFEStateRuleSelect_updateMenuColor(void* self);
extern int D_004410C8[];

struct sRuleSel_2380 {
    char pad[0x51];
    unsigned char count[15];
};

extern "C" void cFEStateRuleSelect_ApplyRuleDependencies(sRuleSel_2380* self, void* item)
{
    int mask = D_004410C8[*(int*)((char*)item + 0x18)] << 1;
    if (func_0039A738(item) == 0) {
        for (int i = 1; i < 15; i++) {
            int bit = 1 << i;
            if ((bit & mask) == 0) {
                int v = self->count[i] - 1;
                self->count[i] = v;
                if ((signed char)v <= 0) {
                    self->count[i] = 0;
                }
            }
        }
    } else {
        for (int i = 1; i < 15; i++) {
            int bit = 1 << i;
            if ((bit & mask) == 0) {
                self->count[i] += 1;
                func_00192088(self, i, 0);
            }
        }
    }
    cFEStateRuleSelect_updateMenuColor(self);
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);

struct sVE_2488 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sQuad_2488 {
    int a, b, c, d;
};
extern sQuad_2488 D_004C66C8;

struct sObj_2488 {
    char pad0[0x8];
    sVE_2488* vt;
    char padC[0x18 - 0xC];
    int idx;
    char pad1C[0x88 - 0x1C];
    sQuad_2488 q88;
};

// PORT: the names are built with the builtin block move (the original likely used
// strcpy on string literals); the two strings live at these symbols.
extern char D_004A16A8[];
extern char D_004A16B0[];

extern "C" void cFEStateRuleSelect_updateMenuColor(void* selfp)
{
    char* self = (char*)selfp;
    char name0[16];
    char name1[16];
    __builtin_memcpy(name0, D_004A16A8, 3);
    __builtin_memcpy(name1, D_004A16B0, 3);
    signed char n = *(signed char*)(self + 0x50) < 12 ? *(signed char*)(self + 0x50) : 11;
    for (signed char i = 0; i < n; i++) {
        sObj_2488* a = (sObj_2488*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(name0));
        sObj_2488* b = (sObj_2488*)cUIScreen_getObjectByHashName(*(void**)(self + 0x40), GetHashValue32(name1));
        if (a && b) {
            if (*(signed char*)(self + a->idx + 0x51) > 0) {
                b->vt[25].fn((char*)b + b->vt[25].delta, 1);
                b->q88 = D_004C66C8;
                b->vt[8].fn((char*)b + b->vt[8].delta, 1);
                a->vt[24].fn((char*)a + a->vt[24].delta, 1);
                a->q88 = D_004C66C8;
                a->vt[8].fn((char*)a + a->vt[8].delta, 1);
            } else {
                b->vt[25].fn((char*)b + b->vt[25].delta, 0);
                b->vt[8].fn((char*)b + b->vt[8].delta, 0);
                a->vt[24].fn((char*)a + a->vt[24].delta, 0);
                a->vt[8].fn((char*)a + a->vt[8].delta, 0);
            }
        }
        if (i < 9) {
            name0[0]++;
            name1[0]++;
        } else {
            name1[0] = name0[0] = i + 0x58;
        }
    }
}

//100%
extern void* D_0046B078[];

extern "C" void* func_001926F0(void* self)
{
    int i;
    *(void***)((char*)self + 0x30) = D_0046B078;
    for (i = 7; i >= 0; i--) {
        ((int*)((char*)self + 0x8))[i] = 0;
    }
    *(int*)((char*)self + 0x0) = 0;
    *(int*)((char*)self + 0x2c) = 0;
    *(int*)((char*)self + 0x28) = 0;
    *(int*)((char*)self + 0x4) = 0;
    return self;
}

//100%
struct sVEntry00192740 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sObj00192740 {
    int pad[2];
    sVEntry00192740* vt;
};

extern "C" void func_00192740(void* self, int a1)
{
    int i;
    *(int*)((char*)self + 0x28) = a1;
    for (i = 0; i < 8; i++) {
        sObj00192740* o = ((sObj00192740**)((char*)self + 0x8))[i];
        if (o != 0) {
            o->vt[8].fn((char*)o + o->vt[8].delta, a1);
        }
    }
}

//100%
extern "C" int func_0039A738(void* self);
extern "C" int func_00192948(void* self, int idx);

struct sColor_001927B0 {
    float r, g, b, a;
    sColor_001927B0(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}
};
struct sVEnt_001927B0 { short delta; short index; void (*fn)(void*, const sColor_001927B0&); };
struct sObj_001927B0 { int pad[2]; sVEnt_001927B0* vt; };
struct sRuleSel_001927B0 { void* owner; int f4; sObj_001927B0* items[8]; };

extern "C" void func_001927B0(sRuleSel_001927B0* self)
{
    void* owner = self->owner;
    if (owner == 0) {
        return;
    }
    int sel = *(signed char*)((char*)owner + 0x95);
    for (int i = 0; i < 8; i++) {
        if (self->items[i] == 0) {
            continue;
        }
        if (func_00192948(self, i) == 0) {
            continue;
        }
        if (i == sel) {
            sObj_001927B0* o = self->items[i];
            sVEnt_001927B0* e = &o->vt[11];
            e->fn((char*)o + e->delta, sColor_001927B0(1.0f, 1.0f, 1.0f, 1.0f));
        } else if (func_0039A738(self->items[i])) {
            sObj_001927B0* o = self->items[i];
            sVEnt_001927B0* e = &o->vt[11];
            e->fn((char*)o + e->delta, sColor_001927B0(1.0f, 0.5921568870544434f, 0.04313725605607033f, 0.0f));
        } else {
            sObj_001927B0* o = self->items[i];
            sVEnt_001927B0* e = &o->vt[11];
            e->fn((char*)o + e->delta, sColor_001927B0(1.0f, 0.14509804546833038f, 0.027450982481241226f, 0.019607843831181526f));
        }
    }
}

//100%
extern "C" int func_00192918(void* self, int val)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (((int*)((char*)self + 0x8))[i] == val) {
            return i;
        }
    }
    return -1;
}

//100%
extern "C" int func_00192948(void* self, int a1)
{
    int mask = (int)(0x1000000 << a1) >> 24;
    return (*(int*)((char*)self + 0x2c) & mask) != 0;
}

//100%
void func_00192968(void* self, int val)
{
    *(int*)((char*)self + 0x2C) = val;
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);

struct sName11_00192970 { char c[11]; };
struct sName12_00192970 { char c[12]; };
struct sName13_00192970 { char c[13]; };
struct sName4_00192970 { char c[4]; };
struct sName2_00192970 { char c[2]; };
struct sName5_00192970 { char c[5]; };

extern char D_0045FC88[];
extern char D_0045FC98[];
extern char D_0045FCA8[];
extern char D_0045FCB8[];
extern char D_004A1740[];
extern char D_004A1748[];
extern char D_004A14F8[];
extern char D_004A1750[];

class cFEVObj_00192970 {
public:
    char pad[0x8];
    // vptr at 0x8; slot N at vtable offset N*8
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08(int on);
    virtual void v09(int on);
};

static inline void Hide_00192970(void* screen, char* name)
{
    cFEVObj_00192970* t = (cFEVObj_00192970*)cUIScreen_getObjectByHashName(screen, GetHashValue32(name));
    if (t != 0) {
        t->v09(0);
    }
}

struct sOwner_00192970 {
    char pad[0x8];
    cFEVObj_00192970* items[8];     // 0x8
    int f28;                        // 0x28
    int mask;                       // 0x2C
};

extern "C" void func_00192970(sOwner_00192970* self, void* screen)
{
    sName11_00192970 n0 = *(sName11_00192970*)D_0045FC88;
    sName12_00192970 n1 = *(sName12_00192970*)D_0045FC98;
    sName12_00192970 n2 = *(sName12_00192970*)D_0045FCA8;
    sName13_00192970 n3 = *(sName13_00192970*)D_0045FCB8;
    sName4_00192970 n4 = *(sName4_00192970*)D_004A1740;
    sName4_00192970 n5 = *(sName4_00192970*)D_004A1748;
    sName2_00192970 n6 = *(sName2_00192970*)D_004A14F8;
    sName5_00192970 n7 = *(sName5_00192970*)D_004A1750;
    for (int i = 0; i < 8; i++) {
        if (((self->mask >> i) & 1) == 0) {
            if (self->items[i] != 0) {
                self->items[i]->v08(1);
                self->items[i]->v09(0);
                n0.c[0] = i + '0';
                n1.c[0] = i + '0';
                n2.c[0] = i + '0';
                n3.c[0] = i + '0';
                n6.c[0] = i + '1';
                n7.c[3] = i + '1';
                n4.c[2] = i + '1';
                n5.c[2] = i + '1';
                Hide_00192970(screen, n0.c);
                Hide_00192970(screen, n1.c);
                Hide_00192970(screen, n2.c);
                Hide_00192970(screen, n3.c);
                Hide_00192970(screen, n6.c);
                Hide_00192970(screen, n7.c);
                Hide_00192970(screen, n4.c);
                Hide_00192970(screen, n5.c);
            }
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern void* D_0046AF68[];
extern "C" void* func_001A8500(void* self, int a1, int a2);

extern "C" void* func_00192D00(void* self, int a1)
{
    char* p;
    int i;
    func_001A8500(self, a1, 0);
    *(void***)((char*)self + 0x8) = D_0046AF68;
    p = (char*)self + 0x6D0;
    for (i = 1; i != -1; i--, p += 0x34) {
        func_001926F0(p);
    }
    *(int*)((char*)self + 0xC) = 0x14;
    *(int*)((char*)self + 0x738) = 0;
    return self;
}

