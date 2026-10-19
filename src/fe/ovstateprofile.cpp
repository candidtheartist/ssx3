#include "common.h"

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void cUIScreen_playFrame(void* screen, int a1, int a2);
extern "C" void cOVStateManager_addPDATemplate();
extern "C" void func_0020A380(void* self);
extern "C" void func_00212080(void* self);
extern char D_00471D50[];

extern "C" void cOVState_PROFILE_onCreateScreen(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_00471D50), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    cOVStateManager_addPDATemplate();
    func_00212080(self);
    func_0020A380(self);
}

//100%
extern "C" void func_00211380(void* self);
extern "C" void func_00211270(void* self);

extern "C" void func_00211220(void* self)
{
    if (*(int*)((char*)self + 0x1C0) != 0) {
        *(int*)((char*)self + 0x22C) = 1;
    }
    if (*(int*)((char*)self + 0x214) == 3) {
        func_00211380(self);
    } else {
        func_00211270(self);
    }
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void func_00211380(void* self);
extern "C" void* func_00227F80(void* app);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern void* D_004A28A8;
extern char D_00471D68[];

struct cSelf_11270 {
    int f0;
    int f4;
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
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void setState(int s);
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual int isReady();
};
struct cCard_11270 {
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
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual int isPresent();
};
struct cUIObj_11270 {
    int f0;
    int f4;
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void setEnabled(int v);
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
    virtual void setSelected(int v);
};

extern "C" void func_00211270(void* p)
{
    cSelf_11270* self = (cSelf_11270*)p;
    if (self->isReady() != 0) {
        if ((*(cCard_11270**)((char*)func_00227F80(D_004A28A8) + 0x434))->isPresent() != 0) {
            self->setState(3);
            func_00211380(self);
            return;
        }
    }
    for (int i = 1; i < 7; i++) {
        char buf[64];
        sprintf(buf, D_00471D68, i);
        cUIObj_11270* o = (cUIObj_11270*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(buf));
        o->setSelected(0);
        o->setEnabled(1);
    }
}

//100%
class cMCSub_1380 {
public:
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual int v04();
    virtual int v05();
    virtual int v06();
    virtual int v07();
    virtual int v08();
    virtual int v09();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual void v14(int, void*);
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
    virtual int v26();
    virtual int v27();
    virtual int v28();
    virtual int v29();
    virtual int v30();
    virtual int v31();
    virtual int v32();
    virtual int v33();
    virtual int v34();
    virtual int v35();
    virtual int v36();
    virtual int v37();
    virtual int v38();
    virtual int v39();
    virtual int v40();
    virtual int v41();
    virtual int v42();
    virtual int v43();
    virtual int v44();
    virtual int v45();
    virtual int v46();
    virtual int v47();
    virtual int v48();
    virtual int v49();
    virtual int v50();
    virtual int v51();
    virtual int v52();
    virtual int v53();
    virtual int v54(int);
    virtual int v55();
    virtual int v56();
    virtual int v57();
    virtual int v58();
    virtual int v59();
    virtual int v60();
    virtual int v61();
    virtual int v62();
    virtual int v63();
    virtual void v64(void*);
    virtual int v65();
    virtual int v66(int);
    virtual int v67(int);
};

class cState_1380 {
public:
    int pad[2];
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual int v04();
    virtual int v05();
    virtual int v06();
    virtual int v07();
    virtual int v08();
    virtual int v09();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
    virtual int v26();
    virtual int v27();
    virtual int v28();
    virtual int v29();
    virtual int v30();
    virtual int v31();
    virtual int v32();
    virtual int v33();
    virtual int v34();
    virtual void v35(int);
    virtual int v36();
    virtual int v37();
    virtual int v38();
    virtual int v39();
    virtual int v40();
    virtual int v41();
    virtual int v42();
    virtual void v43();
};

class cUIObj_1380 {
public:
    int pad[2];
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual int v04();
    virtual int v05();
    virtual int v06();
    virtual int v07();
    virtual void v08(int);
    virtual void v09(int);
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual void v25(int);
};

struct sVE_1380 {
    short delta;
    short index;
    unsigned short* (*fn)(void*, int);
};

class cG_1380 {
public:
    int pad;
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual void v04(int);
};

int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void func_001D8240();
extern "C" void func_00211270(void* self);
extern "C" int func_001D97E0(void* self, void* mp, int dev, int a3);
extern "C" void cMCOverlayManager_GetDeviceDisplayString(void* mp, int dev, unsigned short* buf, int len);
extern "C" void func_003A0D00(void* obj, unsigned short* s);
extern "C" void func_003A0E90(void* obj, unsigned short* s);
extern "C" void* func_00227F80(void* self);
extern void* D_004A28A8;
extern char D_004700F0[];
extern char D_00471D68[];
extern char D_00471D78[];
extern char D_00471D90[];
extern char D_00471DA0[];

struct sCol_1380 {
    float r, g, b, a;
};

extern sCol_1380 D_004C66C8_1380 __asm__("D_004C66C8");

static inline cUIObj_1380* getObj_1380(cState_1380* self, char* name)
{
    return (cUIObj_1380*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(name));
}

// Refreshes the memory-card profile list: device name, then the six profile slots and the arrow hints.
extern "C" void func_00211380(void* p)
{
    cState_1380* self = (cState_1380*)p;
    unsigned short buf[0x320];
    char name[0x40];
    char* mp = (char*)func_00227F80(D_004A28A8);
    if (self->v42()) {
        if (!(*(cMCSub_1380**)(mp + 0x434))->v53()) {
            func_001D8240();
            func_00211270(self);
            return;
        }
        if (*(int*)((char*)self + 0x214) != 3)
            self->v35(3);
    }
    if (self->v42()) {
        cMCOverlayManager_GetDeviceDisplayString(mp, *(int*)(mp + 0x428), buf, 0x320);
        int first = 0;
        func_003A0D00(getObj_1380(self, D_00471D78), buf);
        *(int*)((char*)self + 0x21C) = *(int*)(mp + 0x428);
        self->v43();
        cUIObj_1380* o = getObj_1380(self, D_004700F0);
        *(sCol_1380*)((char*)o + 0x88) = D_004C66C8_1380;
        (*(cMCSub_1380**)(mp + 0x434))->v64(buf);
        func_003A0E90(o, buf);
        o->v09(0);
        for (int i = 1; i < 7; i++) {
            sprintf(name, D_00471D68, i);
            o = getObj_1380(self, name);
            (*(cMCSub_1380**)(mp + 0x434))->v14(i - 1, (char*)self + 0x234);
            func_003A0E90(o, (unsigned short*)((char*)self + 0x234));
            if (!(*(cMCSub_1380**)(mp + 0x434))->v67(i - 1) && !(*(cMCSub_1380**)(mp + 0x434))->v66(i - 1)
                && (*(cMCSub_1380**)(mp + 0x434))->v55()) {
                if (!first) {
                    first = 1;
                    o->v08(0);
                } else {
                    o->v25(1);
                    o->v08(1);
                }
            } else if ((*(cMCSub_1380**)(mp + 0x434))->v54(*(int*)(mp + 0x428))) {
                if ((*(cMCSub_1380**)(mp + 0x434))->v66(i - 1)) {
                    o->v08(1);
                    o->v25(1);
                } else {
                    o->v08(0);
                    o->v25(0);
                }
            } else {
                o->v25(1);
                o->v08(1);
            }
        }
        if (func_001D97E0(self, mp, *(int*)(mp + 0x428), 1) == -1)
            getObj_1380(self, D_00471D90)->v09(0);
        else
            getObj_1380(self, D_00471D90)->v09(1);
        if (func_001D97E0(self, mp, *(int*)(mp + 0x428), 0) == -1)
            getObj_1380(self, D_00471DA0)->v09(0);
        else
            getObj_1380(self, D_00471DA0)->v09(1);
    }
}

//100%
class cUIObj_211850 {
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
    virtual void setVisible(int v);
};
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern char D_004A2090[];
extern char D_004A2568[];
extern char D_00471DB0[];
extern char D_004A20A0[];

extern "C" void func_00211850(void* self, bool show)
{
    bool on = true;
    if (*(int*)((char*)self + 0x22C) != 0) {
        on = show;
    }
    if (*(int*)((char*)self + 0x230) != on) {
        int off = !on;
        cUIObj_211850* a = (cUIObj_211850*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2090));
        if (a != 0) {
            a->setVisible(off);
        }
        ((cUIObj_211850*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2568)))->setVisible(off);
        ((cUIObj_211850*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_00471DB0)))->setVisible(off);
        cUIObj_211850* d = (cUIObj_211850*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A20A0));
        if (d != 0) {
            d->setVisible(off);
        }
        *(int*)((char*)self + 0x230) = on;
    }
}

//100%
class cUIObj_211970 {
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
    virtual void setVisible(int v);
};
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern char D_00471DB0[];
extern char D_004A20A0[];

extern "C" void func_00211970(void* self, bool on)
{
    ((cUIObj_211970*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_00471DB0)))->setVisible(!on);
    ((cUIObj_211970*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A20A0)))->setVisible(!on);
    *(int*)((char*)self + 0x220) = !on;
}

//100%
class cUIObj_211A08 {
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
    virtual void setVisible(int v);
};
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern char D_004A2090[];
extern char D_004A2568[];

extern "C" void func_00211A08(void* self, int a1, bool on)
{
    cUIObj_211A08* a = (cUIObj_211A08*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2090));
    ((cUIObj_211A08*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2568)))->setVisible(!on);
    *(int*)((char*)self + 0x224) = !on;
    a->setVisible(!on);
}

//100%
extern "C" void cGame_exit(void* game, int a);
extern void* D_004A28A8;
extern "C" void func_0039F718(void* self);

extern "C" void func_00211AA8(void* self)
{
    if (*(int*)((char*)self + 0x1AC) == 0) {
        if (*(int*)((char*)self + 0x278) == 0x18) {
            cGame_exit(*(void**)((char*)D_004A28A8 + 0x84), 0);
        } else {
            func_0039F718(*(char**)((char*)self + 0x10) + 0x18);
        }
    }
    *(int*)((char*)self + 0x1AC) = 1;
}

extern "C" void* func_001D58B8(void*);

//100%
void func_00211B10(void* self)
{
    func_001D58B8(self);
    *(int*)((char*)self + 0x1a4) = 0;
}

//100%
class cOvl211B38 {
public:
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
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual int v54(void*);
};

extern void* D_004A28A8;
extern "C" void* func_00227F80(void* app);

extern "C" int func_00211B38(void* self, int a1, unsigned int key)
{
    char* mgr = (char*)func_00227F80(D_004A28A8);
    switch (key) {
    case 6:
    case 8:
        if ((*(cOvl211B38**)(mgr + 0x434))->v54(*(void**)(mgr + 0x428)) == 0) return 0x100;
        break;
    case 9:
        return 0x100;
    }
    return 0x101;
}

//100%
int GetHashValue32(char* str);
extern "C" void* cBE_getBE();
void* cBE_getInterface_1BC8(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_001CB030(void* self, void* engine, void* owner, int a3, unsigned char a4);
extern "C" void func_001CD088(void* self, int a1);
extern "C" void func_001CD0B0(void* self, int a1);
extern "C" void func_001CE3C8(void* self, int key, int a2, int a3);
extern "C" void func_001CE408(void* self, int a1);
extern "C" void func_001CB418(void* self, const char* str);
extern "C" void cKeyboardPopup_setStatic(void* self, void* str);
extern "C" const char* func_00147170(void* iface, int player);
extern "C" void func_00147138(void* self, int a1, const char* name);
extern "C" void func_0039F290(void* list, void* item);
extern "C" void func_002C2540(void* dst, const char* src);
extern "C" void func_002C2580(char* dst, void* src);
extern "C" void func_0023CAE8(void* mp, int a1, int a2);
extern "C" void func_0023D570(void* mp, int a1);
extern "C" int strlen(const char* s);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char D_00471DC0[];
extern char D_00471DD8[];
extern char D_00471DE8[];

struct sVEs_1BC8 { short delta; short index; void* (*fn)(void*, int); };
struct sVEv_1BC8 { short delta; short index; void (*fn)(void*, ...); };
struct sVEi_1BC8 { short delta; short index; int (*fn)(void*, ...); };

static inline void* Loc_1BC8(char* s)
{
    char* o = *(char**)((char*)D_004A28A8 + 0x8C);
    sVEs_1BC8* vt = *(sVEs_1BC8**)(o + 4);
    return vt[4].fn(o + vt[4].delta, GetHashValue32(s));
}

extern "C" void func_00211BC8(char* self, char* w, int ev)
{
    switch (ev) {
    case 13: {
        char* name = *(char**)(self + 0x1A4) + 0x74;
        func_002C2540((char*)func_00227F80(D_004A28A8) + 0x276, name);
        char* np = (char*)cBE_getInterface_1BC8(cBE_getBE(), 1);
        if (strlen(name) != 0) {
            func_00147138(np, *(int*)(self + 0x1CC), name);
        } else {
            char buf[0x70];
            char fmt[0x70];
            func_002C2580(fmt, Loc_1BC8(D_00471DC0));
            sprintf(buf, fmt, *(int*)(self + 0x1CC) + 1);
            func_00147138(np, *(int*)(self + 0x1CC), buf);
        }
        sVEv_1BC8* vt = *(sVEv_1BC8**)(np + 0xC);
        vt[1].fn(np + vt[1].delta);
        func_0023CAE8(func_00227F80(D_004A28A8), 1, *(int*)(self + 0x1CC));
        *(int*)(self + 0x1A8) = 1;
        *(int*)(self + 0x1DC) = 1;
        *(int*)(self + 0x1C0) = 3;
        break;
    }
    case 5: {
        if (w == 0) {
            return;
        }
        if (*(int*)(self + 0x1A8) != 0) {
            return;
        }
        char* mp = (char*)func_00227F80(D_004A28A8);
        if (*(int*)(self + 0x214) != 3) {
            return;
        }
        int idx = *(int*)(w + 0x18);
        *(int*)(self + 0x1C4) = idx;
        *(int*)(mp + 0xF8) = idx;
        if (*(int*)(self + 0x1C0) != 1) {
            return;
        }
        if (*(void**)(self + 0x1A4) == 0) {
            *(char**)(self + 0x1A4) = (char*)func_001CB030(cMemMan_alloc(0x444, D_00471DD8, 0x100, 0), *(void**)(self + 0x10), self, 0, *(unsigned char*)(self + 0x15));
            *(int*)(*(char**)(self + 0x1A4) + 0x140) = 0x37;
            func_001CD088(*(void**)(self + 0x1A4), 8);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x4B, 1, 2);
            *(int*)(*(char**)(self + 0x1A4) + 0x58) = 1;
            func_001CE408(*(void**)(self + 0x1A4), 1);
            func_001CE3C8(*(void**)(self + 0x1A4), 0xE, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x27, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x28, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x34, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x1A, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x19, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x35, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x40, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x41, 0, 2);
            func_001CE3C8(*(void**)(self + 0x1A4), 0x42, 0, 2);
            func_001CD0B0(*(void**)(self + 0x1A4), 1);
        }
        cKeyboardPopup_setStatic(*(void**)(self + 0x1A4), Loc_1BC8(D_00471DE8));
        *(int*)(*(char**)(self + 0x1A4) + 0x54) = 1;
        func_001CB418(*(void**)(self + 0x1A4), func_00147170(cBE_getInterface_1BC8(cBE_getBE(), 1), *(int*)(self + 0x1CC)));
        func_0039F290(*(char**)(*(char**)(*(char**)(self + 0x40) + 0xD0) + 0x10) + 0x18, *(void**)(self + 0x1A4));
        *(int*)(self + 0x1A0) = 1;
        *(int*)(self + 0x19C) = 0;
        break;
    }
    case 6: {
        char* mp = (char*)func_00227F80(D_004A28A8);
        if (*(int*)(self + 0x1A8) == 1) {
            return;
        }
        int st = *(int*)(self + 0x1C0);
        if (st == 6) {
            return;
        }
        *(int*)(self + 0x1E4) = 1;
        if (st == 0 || st == 2 || st == 1) {
            sVEv_1BC8* vt = *(sVEv_1BC8**)(mp + 0x748);
            vt[1].fn(mp + vt[1].delta, 0);
        }
        *(int*)(self + 0x1C0) = 6;
        break;
    }
    case 7: {
        if (*(int*)(self + 0x1A8) == 1) {
            return;
        }
        if (*(int*)(self + 0x1C0) == 6) {
            return;
        }
        char* mp = (char*)func_00227F80(D_004A28A8);
        char* o = *(char**)(mp + 0x434);
        sVEi_1BC8* ovt = *(sVEi_1BC8**)o;
        if (ovt[54].fn(o + ovt[54].delta, *(void**)(mp + 0x428)) == 0) {
            return;
        }
        int idx = *(int*)(w + 0x18);
        *(int*)(self + 0x1C4) = idx;
        *(int*)(mp + 0xF8) = idx;
        if (*(int*)(self + 0x1C0) != 1) {
            return;
        }
        char* o2 = *(char**)(mp + 0x434);
        sVEi_1BC8* ovt2 = *(sVEi_1BC8**)o2;
        if (ovt2[67].fn(o2 + ovt2[67].delta, *(int*)(self + 0x1C4)) == 0) {
            return;
        }
        *(int*)(self + 0x1A8) = 1;
        *(int*)(self + 0x1C0) = 4;
        func_0023D570(mp, 0);
        sVEv_1BC8* vt = *(sVEv_1BC8**)(mp + 0x748);
        vt[1].fn(mp + vt[1].delta, 0x18);
        break;
    }
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 14:
        break;
    }
}


//100%
struct cUIText;
void cUIText_setAsciiString(cUIText* self, const char* str);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char D_004A2138[];
extern char D_00471D68[];

extern "C" void func_00212080(void* self)
{
    char buf[16];
    int i;
    for (i = 1; i < 7; i++) {
        sprintf(buf, D_004A2138, i);
        cUIText_setAsciiString((cUIText*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(buf)), buf);
        sprintf(buf, D_00471D68, i);
        *(int*)((char*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(buf)) + 0x18) = i - 1;
    }
}

//100%
extern "C" void* func_001D53B0(void* self, void* a1, int a2);
extern void* D_00471F80[];

extern "C" void* func_00212138(void* self, void* a1, int a2)
{
    func_001D53B0(self, a1, 0);
    *(void***)((char*)self + 0x8) = D_00471F80;
    *(int*)((char*)self + 0xC) = 0x25;
    *(int*)((char*)self + 0x208) = 1;
    *(int*)((char*)self + 0x22C) = a2;
    *(int*)((char*)self + 0x1C4) = 0;
    *(int*)((char*)self + 0x230) = 0;
    return self;
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void cUIScreen_playFrame(void* screen, int a1, int a2);
extern "C" void func_0020A380(void* self);
extern char D_00471E28[];

extern "C" void cOVState_AUTOSAVE_onCreateScreen(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_00471E28), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    func_0020A380(self);
}

INCLUDE_ASM("fe/ovstateprofile", func_00212208);

//100%
int func_002122E0(void* self)
{
    return 0;
}

//100%
struct sVEntry002122E8 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sObj002122E8 {
    int pad[2];
    sVEntry002122E8* vt;
};

int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void cOVState_AUTOSAVE_displayOn(void* self);
extern char D_00471E38[];

extern "C" void func_002122E8(void* self)
{
    int s = *(int*)((char*)self + 0x1C0);
    if (s != 0 && s != 6) {
        cOVState_AUTOSAVE_displayOn(self);
    } else {
        sObj002122E8* o = (sObj002122E8*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_00471E38));
        o->vt[9].fn((char*)o + o->vt[9].delta, 0);
    }
}

//100%
extern void* D_004A28A8;
extern "C" void* func_00227F80(void* app);
extern "C" int func_0023C898(void* mp);
extern "C" void* cUIAnimationBank_getAnimationByHashName(void* bank, int hash);
extern "C" void func_0039FCC8(void* obj, void* anim, int a2, int a3, int a4);
extern "C" void func_0039FD38(void* obj);
struct cUIText;
void cUIText_setUnicodeStringByID(cUIText* text, int id);
extern char D_004A2770[];
extern char D_00471E48[];
extern char D_00471E58[];

class cUIObj_2360 {
public:
    int pad[2];
    virtual ~cUIObj_2360();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void setEnabled(int v);
    virtual void setVisible(int v);
};

extern "C" void cOVState_AUTOSAVE_displayOn(void* self)
{
    void* mp = func_00227F80(D_004A28A8);
    int v = *(int*)((char*)self + 0x1A8);
    if (v == *(int*)((char*)self + 0x230)) {
        return;
    }
    *(int*)((char*)self + 0x230) = v;
    void* obj = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2770));
    if (obj == 0) {
        return;
    }
    if (*(int*)((char*)self + 0x1A8) != 0 && func_0023C898(mp) == 0 && *(int*)((char*)self + 0x1C0) != 6) {
        void* bank = *(char**)((char*)self + 0x10) + 0x50;
        void* anim = cUIAnimationBank_getAnimationByHashName(bank, GetHashValue32(D_00471E48));
        if (anim != 0) {
            func_0039FCC8(obj, anim, 9, 0, 0);
        }
        cUIObj_2360* t = (cUIObj_2360*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_00471E38));
        t->setVisible(1);
        cUIText_setUnicodeStringByID((cUIText*)t, GetHashValue32(D_00471E58));
    } else {
        func_0039FD38(obj);
        ((cUIObj_2360*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_00471E38)))->setVisible(0);
    }
}

//100%
extern "C" void func_0039F718(void* self);

extern "C" void func_002124C8(void* self)
{
    if (*(int*)((char*)self + 0x1AC) == 0) {
        func_0039F718(*(char**)((char*)self + 0x10) + 0x18);
    }
    *(int*)((char*)self + 0x1AC) = 1;
}

//100%
extern void* D_004A28A8;
extern int D_004A11B8;
extern int D_00535C08[];
extern char D_00471E70[];
extern char D_00471E80[];
extern char D_00471E90[];
struct cAppMan;
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void cGame_exit(void* game, int a);
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_00194738(void* self, void* mgr);
extern "C" void* func_001F3700(void* self, void* mgr);
void* func_00232720(void* self);
void cAppMan_setNextModule(cAppMan* self, unsigned int module);
extern "C" void cBENewRaceInterface_setGameMode(void* iface, int mode);
extern "C" void cBENewRaceInterface_setGameEvent(void* iface, int ev);
extern "C" int func_00146D98(void* self, int index);
extern "C" void func_0039F400(void* list, void* item);

struct sVEnt_00212508 { short delta; short index; void (*fn)(void*); };

extern "C" void func_00212508(void* self)
{
    func_001D58B8(self);
    int s = *(int*)((char*)self + 0x22C);
    if (s == 1) {
        cGame_exit(*(void**)((char*)D_004A28A8 + 0x84), 0);
    } else if (s == 6) {
        void* m = func_00194738(cMemMan_alloc(0x4C, D_00471E70, 0, 0), *(void**)((char*)self + 0x10));
        func_0039F400(*(char**)((char*)self + 0x10) + 0x18, m);
    } else if (s == 7) {
        void* m = func_001F3700(cMemMan_alloc(0x58, D_00471E80, 0, 0), *(void**)((char*)self + 0x10));
        func_0039F400(*(char**)((char*)self + 0x10) + 0x18, m);
    } else if (s == 0) {
        void* race = cBE_getInterface_Fv(cBE_getBE(), 0);
        void* player = cBE_getInterface_Fv(cBE_getBE(), 1);
        cBENewRaceInterface_setGameMode(race, 4);
        cBENewRaceInterface_setGameEvent(race, 0xC);
        D_00535C08[0] = func_00146D98(player, 0);
        D_004A11B8 = 1;
        sVEnt_00212508* vt = *(sVEnt_00212508**)((char*)race + 0xC);
        vt[1].fn((char*)race + vt[1].delta);
        cAppMan_setNextModule((cAppMan*)D_004A28A8, (unsigned int)func_00232720(cMemMan_alloc(8, D_00471E90, 0x100, 0)));
    }
}


extern "C" void* func_00212680(void* p, ...)
{
    return p;
}

//100%
extern "C" int func_002126C0(const signed char* a, const signed char* ae, const signed char* b, const signed char* be)
{
    for (; a != ae && b != be; ++a, ++b) {
        if (*a < *b) return 1;
        if (*b < *a) return 0;
    }
    return a == ae && b != be;
}

//100%
extern "C" int func_00212728(const signed char* a, const signed char* ae, const signed char* b, const signed char* be)
{
    while (a != ae && b != be) {
        if (*a < *b) return -1;
        if (*b < *a) return 1;
        ++a;
        ++b;
    }
    if (b == be) return !(a == ae);
    return -1;
}

//100%
extern "C" void operator_delete__FPi(void*);
struct sListNode_212788 { sListNode_212788* next; sListNode_212788* prev; };

extern "C" void func_00212788(void* self)
{
    sListNode_212788* head = *(sListNode_212788**)((char*)self + 4);
    sListNode_212788* cur = head->next;
    while (cur != *(sListNode_212788**)((char*)self + 4)) {
        sListNode_212788* tmp = cur;
        cur = cur->next;
        operator_delete__FPi(tmp);
    }
    (*(sListNode_212788**)((char*)self + 4))->next = *(sListNode_212788**)((char*)self + 4);
    (*(sListNode_212788**)((char*)self + 4))->prev = *(sListNode_212788**)((char*)self + 4);
}
