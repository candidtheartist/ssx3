#include "common.h"

struct cList;
struct cUIText;

struct sVec3_CG { float x, y, z; };
extern sVec3_CG D_004FF0D8;

class cUIThing_CG {
public:
    char pad0[0x8];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08(int a);
    virtual void v09(int a);
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
    virtual void v20(sVec3_CG *p);
};

struct sThing_CG {
    char pad0[0x18];
    int x18;
    char pad1C[0x44 - 0x1C];
    sVec3_CG pos;           /* 0x44 */
    char pad50[0x78 - 0x50];
    int x78;
    int x7C;
};
/* cUIThing_CG has only virtuals (vptr at 0x8); fields go through this view. */
#define T_(o) ((sThing_CG *)(o))

struct sEnt_CG { int f0; unsigned short id; short f6; };
struct sRider_CG { char pad0[0x18]; signed char slot; };
struct sPlayer_CG { char pad0[0xA0]; sRider_CG *rider; };
struct sMan_CG {
    char pad0[0x10];
    char *x10;
    char pad14[0x24 - 0x14];
    char list[0x20];        /* 0x24 */
    signed char player;     /* 0x44 */
    char pad45[0x4C - 0x45];
    sPlayer_CG *p4C;
    char pad50[0x54 - 0x50];
    int x54;
    int x58;
    int x5C;
};

extern "C" int sprintf(char *, const char *, ...);
extern char D_0045D940[];
extern char D_004A1418[];
extern char D_004A1420[];
extern char D_004A1428[];
extern char D_004A1430[];
extern char D_004A1438[];
extern char D_0045D950[];
extern char D_0045D960[];
extern char D_0045D970[];
extern char D_0045D980[];
extern char D_004A1440[];
extern char D_004A1448[];
extern char D_004A1450[];
void *cList_first_CG(cList *list) __asm__("cList_first__FP5cList");
int GetHashValue32_CG(char *) __asm__("GetHashValue32__FPc");
extern "C" cUIThing_CG *cUIScreen_getObjectByHashName_CG(void *self, int hash) __asm__("cUIScreen_getObjectByHashName");
void cUIText_setAsciiString_CG(void *self, const char *str) __asm__("cUIText_setAsciiString__FP7cUITextPCc");
extern "C" void *cBE_getBE_CG() __asm__("cBE_getBE");
void *cBE_getInterface_CG(void *be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" sEnt_CG *func_0014FF90_CG(void *iface, int player, int slot, int *out) __asm__("func_0014FF90");
extern "C" int func_0014FEA8_CG(void *iface, int player, int slot, int second) __asm__("func_0014FEA8");
extern "C" int func_00150048_CG(void *iface, int player, int slot, int i) __asm__("func_00150048");
extern "C" int func_0014FFB8_CG(void *iface, int player, int slot, int i) __asm__("func_0014FFB8");
extern "C" const char *Trick_GetGrabName_CG(int id) __asm__("Trick_GetGrabName");
extern "C" void *func_00398380_CG(void *self, int id) __asm__("func_00398380");
extern "C" void UI_SetWidgetSizeFromTexRect_CG(cUIThing_CG *self, void *rect, float scale) __asm__("UI_SetWidgetSizeFromTexRect");
extern "C" void func_003A1030_CG(cUIThing_CG *self, sVec3_CG *out) __asm__("func_003A1030");
extern "C" void func_003A0290_CG(cUIThing_CG *self, sVec3_CG *out) __asm__("func_003A0290");

static inline void setRect_CG(cUIThing_CG *o, void *r) { UI_SetWidgetSizeFromTexRect_CG(o, r, 0.8f); }
extern "C" void cWScriptMan_checkGate(void *self)
{
    sMan_CG *s = (sMan_CG *)self;
    cUIThing_CG *a[9];
    cUIThing_CG *b[9];
    void *screen = cList_first_CG((cList *)s->list);
    int i;
    for (i = 0; i < 9; i++) {
        char buf[16];
        cUIThing_CG *o;
        sprintf(buf, D_0045D940, i);
        o = cUIScreen_getObjectByHashName_CG(screen, GetHashValue32_CG(buf));
        if (o != 0) {
            a[i] = o;
            o->v08(1);
            o->v09(0);
            T_(o)->x18 = -1;
        } else {
            a[i] = 0;
        }
        sprintf(buf, D_004A1418, i);
        o = cUIScreen_getObjectByHashName_CG(screen, GetHashValue32_CG(buf));
        if (o != 0) {
            b[i] = o;
            o->v09(0);
            T_(o)->x18 = -1;
        } else {
            b[i] = 0;
        }
    }

    int lvl = 1;
    sRider_CG *r = s->p4C->rider;
    if (r != 0) lvl = r->slot;
    void *iface = cBE_getInterface_CG(cBE_getBE_CG(), 6);
    int count;
    sEnt_CG *tbl = func_0014FF90_CG(iface, s->player, lvl, &count);
    int cur = func_0014FEA8_CG(iface, s->player, lvl, 1);
    int k = 0;
    for (int j = 0; j < count; j++) {
        if (func_00150048_CG(iface, s->player, lvl, j)) {
            cUIThing_CG *o = a[k];
            if (o != 0) {
                cUIText_setAsciiString_CG(o, Trick_GetGrabName_CG(tbl[j].id));
                o->v09(1);
                o->v08(0);
                T_(o)->x18 = j;
            }
            o = b[k];
            if (o != 0) {
                o->v09(1);
                int c;
                if (func_0014FFB8_CG(iface, s->player, lvl, j)) {
                    c = s->x5C;
                    T_(o)->x78 = -1;
                    T_(o)->x7C = c;
                } else if (cur == j) {
                    c = s->x54;
                    T_(o)->x78 = -1;
                    T_(o)->x7C = c;
                } else {
                    c = s->x58;
                    T_(o)->x78 = -1;
                    T_(o)->x7C = c;
                }
            }
            k++;
        }
    }

    char *th22 = s->x10;
    int hhh22 = GetHashValue32_CG(D_004A1420);
    void *h22 = func_00398380_CG(th22 + 0x58, hhh22);
    void *sel = 0;
    void *sel2 = 0;
    char *th21 = s->x10;
    int hhh21 = GetHashValue32_CG(D_004A1428);
    void *h21 = func_00398380_CG(th21 + 0x58, hhh21);
    char *th20 = s->x10;
    int hhh20 = GetHashValue32_CG(D_004A1430);
    void *h20 = func_00398380_CG(th20 + 0x58, hhh20);
    char *th19 = s->x10;
    int hhh19 = GetHashValue32_CG(D_004A1438);
    void *h19 = func_00398380_CG(th19 + 0x58, hhh19);
    char *th18 = s->x10;
    int hhh18 = GetHashValue32_CG(D_0045D950);
    void *h18 = func_00398380_CG(th18 + 0x58, hhh18);
    switch (lvl) {
    case 1:
        sel = h21;
        break;
    case 3:
        sel = h19;
        break;
    case 0:
        sel = h22;
        break;
    case 4:
        sel = h22;
        sel2 = h21;
        break;
    case 9:
        sel2 = h19;
        sel = h20;
        break;
    case 2:
        sel = h20;
        break;
    }

    cUIThing_CG *o19 = cUIScreen_getObjectByHashName_CG(screen, GetHashValue32_CG(D_0045D960));
    setRect_CG(o19, sel);
    T_(o19)->x78 = -1;
    T_(o19)->x7C = (int)sel;
    cUIThing_CG *o17 = cUIScreen_getObjectByHashName_CG(screen, GetHashValue32_CG(D_0045D970));
    setRect_CG(o17, sel2);
    T_(o17)->x78 = -1;
    T_(o17)->x7C = (int)sel2;
    cUIThing_CG *o18 = cUIScreen_getObjectByHashName_CG(screen, GetHashValue32_CG(D_0045D980));
    setRect_CG(o18, h18);
    T_(o18)->x78 = -1;
    T_(o18)->x7C = (int)h18;
    cUIThing_CG *o20 = cUIScreen_getObjectByHashName_CG(screen, GetHashValue32_CG(D_004A1440));
    cUIThing_CG *o21 = cUIScreen_getObjectByHashName_CG(screen, GetHashValue32_CG(D_004A1448));
    cUIThing_CG *o16 = cUIScreen_getObjectByHashName_CG(screen, GetHashValue32_CG(D_004A1450));
    /* pad90 is never used; it keeps the original frame layout (slot at sp+0x90). */
    sVec3_CG sz20, sz21, sz16, pad90, p20, q21, p16;
    func_003A1030_CG(o20, &sz20);
    sz20.x += 10.0f;
    func_003A1030_CG(o21, &sz21);
    func_003A1030_CG(o16, &sz16);
    sz16.x += 10.0f;
    func_003A0290_CG(o20, &p20);
    func_003A0290_CG(o16, &p16);
    sVec3_CG P19 = T_(o19)->pos;
    sVec3_CG P17 = T_(o17)->pos;
    sVec3_CG P18 = T_(o18)->pos;
    sVec3_CG f, g, h;
    o19->v20(&f);
    o17->v20(&g);
    o18->v20(&h);
    P19.x = p20.x + sz20.x;
    P17.x = P19.x;
    if (T_(o17)->x7C != 0) {
        P17.x += f.x + 10.0f;
        g.x += 10.0f;
    } else {
        g = D_004FF0D8;
    }
    P18.x = p16.x + sz16.x;
    T_(o19)->pos = P19;
    T_(o17)->pos = P17;
    T_(o18)->pos = P18;
    p20 = T_(o20)->pos;
    q21 = T_(o21)->pos;
    q21.x = p20.x + sz20.x + 10.0f + f.x + g.x;
    T_(o21)->pos = q21;
}

//100%
struct cList;
struct cUIText;

struct sWSMEntry4520 {
    int f0;
    short f4;
    unsigned short id;          // 0x6
};

struct sWSMRider4520 {
    char pad0[0x18];
    signed char slot;           // 0x18
};

struct sWSMPlayer4520 {
    char pad0[0xA0];
    sWSMRider4520* rider;       // 0xA0
};

struct sWSMission4520 {
    char pad0[0x24];
    char list[0x20];            // 0x24 (cList)
    signed char player;         // 0x44
    char pad45[0x7];
    sWSMPlayer4520* p4C;        // 0x4C
    sWSMPlayer4520* p50;        // 0x50
};

extern char D_0045D9B8[];
extern char D_0045D9C8[];
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBENewPlayerInterface_getPlayerCharID(void* self, int index);
void* cList_first(cList* list);
int GetHashValue32(char*);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
void cUIText_setAsciiString(cUIText* self, const char* str);
extern "C" sWSMEntry4520* func_0014FF90(void* iface, int player, int slot, void* out);
extern "C" int func_00150928(void* iface, int player, int charID);
extern "C" const char* func_00198AF0(int id);

extern "C" void func_00184520(sWSMission4520* self)
{
    signed char b = self->p4C->rider->slot;
    signed char a = self->p50->rider->slot;
    char buf[16];
    sWSMEntry4520* tbl = func_0014FF90(cBE_getInterface_Fv(cBE_getBE(), 6), self->player, b, buf);
    void* screen = cList_first((cList*)self->list);
    cUIText* t = (cUIText*)cUIScreen_getObjectByHashName(screen, GetHashValue32(D_0045D9B8));
    if (t != 0) {
        cUIText_setAsciiString(t, func_00198AF0(tbl[a].id));
    }
    cUIText* t2 = (cUIText*)cUIScreen_getObjectByHashName(screen, GetHashValue32(D_0045D9C8));
    if (t2 != 0) {
        signed char cid = cBENewPlayerInterface_getPlayerCharID(cBE_getInterface_Fv(cBE_getBE(), 1), self->player);
        cUIText_setAsciiString(t2, func_00198AF0(func_00150928(cBE_getInterface_Fv(cBE_getBE(), 0xB), self->player, cid)));
    }
}

