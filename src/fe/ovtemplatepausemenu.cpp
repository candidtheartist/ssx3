#include "common.h"

INCLUDE_ASM("fe/ovtemplatepausemenu", cOVTemplate_PauseMenu_onCreateScreen);

//100%
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char* D_00441C30[];
extern char D_0046F840[];

struct sVec3_001F8448 {
    float x, y, z;
};
struct sVEnt_001F8448 { short delta; short index; void (*fn)(void*, int); };

extern "C" int OVScreenPauseFreeride_TransitionIn(void* self)
{
    char buf[64];
    if (*(int*)((char*)self + 0xD4) != 0) {
        *(int*)((char*)self + 0xD4) = 0;
        for (int i = 0; i < 14; i++) {
            sprintf(buf, D_0046F840, D_00441C30[i]);
            char* obj = (char*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0xC0), GetHashValue32(buf));
            if (obj != 0) {
                sVEnt_001F8448* vt = *(sVEnt_001F8448**)(obj + 8);
                vt[9].fn(obj + vt[9].delta, 0);
            }
        }
        for (int i = 0; i < 8; i++) {
            if (i < *(int*)((char*)self + 0xBC)) {
                sprintf(buf, D_0046F840, D_00441C30[((int*)((char*)self + 0x9C))[i]]);
                char* obj = (char*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0xC0), GetHashValue32(buf));
                if (obj != 0) {
                    sVEnt_001F8448* vt = *(sVEnt_001F8448**)(obj + 8);
                    vt[9].fn(obj + vt[9].delta, 1);
                    sVec3_001F8448 v;
                    v.x = 0.0f;
                    v.z = 0.0f;
                    v.y = (float)i * 40.0f;
                    *(sVec3_001F8448*)(obj + 0x44) = v;
                }
            }
        }
    }
    return 0;
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void func_0039E4C0(void* self, int a1);
extern unsigned char D_004A2468;
extern char D_004A2138[];
extern char D_004C8AE8[];
extern char D_004C8AF8[];
extern char D_004C8B08[];
extern char D_004C8B18[];

struct sVEnt_001F85C0 { short delta; short index; void (*fn)(void*, void*); };

static inline void setColor_001F85C0(char* obj, void* c)
{
    sVEnt_001F85C0* vt = *(sVEnt_001F85C0**)(obj + 8);
    vt[11].fn(obj + vt[11].delta, c);
}

extern "C" void OVScreenPauseFreeride_OnActivate(void* self, int a1)
{
    char buf[32];
    char* obj;
    int* sel = (int*)((char*)self + 0x9C);
    char* flags = (char*)self + 0xD8;
    int i = 0;
    while (i < 8 && (sprintf(buf, D_004A2138, i),
                     obj = (char*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0xC0), GetHashValue32(buf)),
                     i < *(int*)((char*)self + 0xBC))) {
        if (obj != 0) {
            if (i == D_004A2468) {
                if (*(int*)(flags + (*sel << 2)) != 0) {
                    setColor_001F85C0(obj, D_004C8AF8);
                } else {
                    setColor_001F85C0(obj, D_004C8AE8);
                }
            } else {
                if (*(int*)(flags + (*sel << 2)) != 0) {
                    setColor_001F85C0(obj, D_004C8B18);
                } else {
                    setColor_001F85C0(obj, D_004C8B08);
                }
            }
        }
        sel++;
        i++;
    }
    func_0039E4C0(self, a1);
}

//100%
void func_001F8720(void* self)
{
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
int GetHashValue32(char* str);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
class cUIScreen;
unsigned short cUIScreen_getFrameByLabel(cUIScreen* self, int label);
extern "C" int func_001E3408(void);
extern "C" void func_0020E900(void* self);
extern "C" void func_00258790(void* self, int a1);
extern "C" void func_0020D190(void);
// func_0039F190 returns its last list node in $v0; the unit declares it void.
void* func_0039F190_r(void* self, int a1) __asm__("func_0039F190");
extern char* D_004A2EEC;
extern int D_004A2A50;
extern int D_004A2A54;
extern int D_005366E8[];
extern int D_004428F0[];
extern char D_004A2478[];
extern char D_0046F850[];

struct sColor_1F8728 { float r, g, b, a; };
struct sVEnt_1F8728 { short delta; short index; void (*fn)(void*, void*); };

extern "C" void OVScreenPauseFreeride_Update(void* self)
{
    int st = *(int*)((char*)self + 0x110);
    if ((st == 1 || st == 2 || st == 4) && func_001E3408() > 0)
    {
        float a = *(float*)((char*)self + 0xC8) + *(float*)((char*)self + 0xCC);
        *(float*)((char*)self + 0xC8) = a;
        if (a >= 1.0f)
        {
            *(float*)((char*)self + 0xC8) = 1.0f;
            *(float*)((char*)self + 0xCC) = -*(float*)((char*)self + 0xCC);
        }
        else if (a < 0.0f)
        {
            *(float*)((char*)self + 0xC8) = 0.0f;
            *(float*)((char*)self + 0xCC) = -*(float*)((char*)self + 0xCC);
        }
        char* o = (char*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0xC0), GetHashValue32(D_004A2478));
        if (o != 0)
        {
            sColor_1F8728 c = *(sColor_1F8728*)(o + 0x1C);
            c.r = *(float*)((char*)self + 0xC8);
            sVEnt_1F8728* vt = *(sVEnt_1F8728**)(o + 8);
            vt[11].fn(o + vt[11].delta, &c);
        }
    }
    func_0020E900(self);
    char* g = D_004A2EEC;
    if (g == 0)
        return;
    int go = 0;
    if (*(int*)(g + 0x68) == 0 || *(int*)(g + 0x64) == 0)
        go = 1;
    if (!go)
        return;
    func_00258790(D_004A2EEC, 0);
    char* g2 = D_004A2EEC;
    *(int*)(g2 + 0x68) = -1;
    *(int*)(g2 + 0x64) = -1;
    int frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0xC0), GetHashValue32(D_0046F850));
    cUIScreen_playFrame(*(void**)((char*)self + 0xC0), frame, 1);
    *(int*)((char*)self + 0xD0) = 1;
    func_0020D190();
    func_0039F190_r(*(char**)((char*)self + 0x10) + 0x18, 1);
    D_004A2A50 = D_004428F0[D_005366E8[--D_004A2A54]];
}

extern "C" void* func_0020A430(void*);

//100%
void* OVScreenPauseFreeride_Shutdown(void* self)
{
    *(int*)((char*)self + 0xc4) = 0;
    return func_0020A430(self);
}

//100%
extern "C" int func_001F8908(void* self, int a1, unsigned int a2)
{
    switch (a2) {
    case 8:
    case 9:
        return 0x100;
    case 6:
        return 0;
    }
    return 0x101;
}

//100%
class cUIText;
void cUIText_setUnicodeStringByID(cUIText* self, int id);
extern "C" void func_0020AB50(int id);
extern "C" void* func_00195FF0(void* self, void* engine, signed char idx, int a3);
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void cUIStateStack_pushSpecial(void* stack, void* st, int a2, int a3);
extern "C" void* func_0028B180_8960() __asm__("func_0028B180");
extern "C" void func_00289BB8(void* self);
extern "C" void OVScreenPauseFreeride_PlayIconAnim(void* self, int idx, int on);
extern void* D_004A28A8;
extern char D_004A5A58;
extern char D_004A2470[];
extern char D_004A2480[];
extern char D_0046F860[];
extern char* D_00441BF8[];
extern int D_004A2708;
extern unsigned int D_004A2594;
extern char D_004C8AE8[];
extern char D_004C8AF8[];
extern char D_004C8B08[];
extern char D_004C8B18[];

struct sVEi_8960 { short delta; short index; int (*fn)(void*, ...); };
struct sVEv_8960 { short delta; short index; void (*fn)(void*, int); };
struct sStFlags_8960 { char pad[0x1C]; unsigned int lo : 8; unsigned int mode : 6; };

extern "C" void func_0039F190_v(void* self, int a1) __asm__("func_0039F190");
struct sOn_8960 { char pad[0xD8]; int on[1]; };
extern "C" void cOVTemplate_PauseMenu_onWidgetEvent(char* self, char* w, int ev)
{
    if (w == 0) {
        return;
    }
    switch (ev) {
    case 5: {
        char* l = &D_004A5A58;
        char* p = *(char**)(*(char**)(self + 0x10) + 0x14);
        if (p) {
            l = p;
        }
        char* o = (char*)cUIScreen_getObjectByHashName(*(void**)(self + 0xC0), GetHashValue32(D_004A2470));
        if (((sOn_8960*)self)->on[*(int*)(w + 0x18)] == 0) {
            sVEv_8960* vt = *(sVEv_8960**)l;
            vt[2].fn(l + vt[2].delta, 4);
            return;
        }
        sVEv_8960* vt = *(sVEv_8960**)l;
        vt[2].fn(l + vt[2].delta, 6);
        D_004A2468 = *(unsigned char*)(o + 0x95);
        int frame = cUIScreen_getFrameByLabel(*(cUIScreen**)(self + 0xC0), GetHashValue32(D_0046F850));
        cUIScreen_playFrame(*(void**)(self + 0xC0), frame, 1);
        *(int*)(self + 0xD0) = 1;
        switch (*(int*)(w + 0x18)) {
        case 1:
            if (D_004A2EEC) {
                func_00258790(D_004A2EEC, 0);
                char* g = D_004A2EEC;
                *(int*)(g + 0x68) = -1;
                *(int*)(g + 0x64) = -1;
            }
            func_0020D190();
            func_0039F190_r(*(char**)(self + 0x10) + 0x18, 1);
            D_004A2A50 = D_004428F0[D_005366E8[--D_004A2A54]];
            func_00289BB8(func_0028B180_8960());
            break;
        case 2:
            D_004A2708 = 1;
            func_0020AB50(0x17);
            break;
        case 3:
            func_0020AB50(7);
            break;
        case 4: {
            char* ui = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x48);
            sStFlags_8960* st = (sStFlags_8960*)func_00195FF0(cMemMan_alloc(0x80, D_0046F860, 0, 0), ui, 0, 0);
            st->mode = 1;
            cUIStateStack_pushSpecial(ui + 0x18, st, 0, 0);
            break;
        }
        case 5:
        case 13:
            func_0020AB50(0x18);
            break;
        case 6:
            func_0020AB50(0x1C);
            break;
        case 7:
            func_0020AB50(0x19);
            break;
        case 8:
            func_0020AB50(0x1A);
            break;
        case 9:
            func_0020AB50(0x1B);
            break;
        case 10:
            func_0020AB50(0x20);
            break;
        case 11:
            D_004A2594 = 2;
            func_0020AB50(0x21);
            break;
        case 12:
            func_0020AB50(0x22);
            break;
        }
        break;
    }
    case 6: {
        if (D_004A2EEC) {
            func_00258790(D_004A2EEC, 0);
            char* g = D_004A2EEC;
            *(int*)(g + 0x68) = -1;
            *(int*)(g + 0x64) = -1;
        }
        func_0020D190();
        char* q = *(char**)(self + 0x10);
        D_004A2A50 = D_004428F0[D_005366E8[--D_004A2A54]];
        func_0039F190_r(q + 0x18, 1);
        func_00289BB8(func_0028B180_8960());
        break;
    }
    case 1: {
        if (*(int*)(self + 0xD0) == 0) {
            if (((sOn_8960*)self)->on[*(int*)(w + 0x18)]) {
                sVEi_8960* vt = *(sVEi_8960**)(w + 8);
                vt[11].fn(w + vt[11].delta, D_004C8AF8);
            } else {
                sVEi_8960* vt = *(sVEi_8960**)(w + 8);
                vt[11].fn(w + vt[11].delta, D_004C8AE8);
            }
            if (*(int*)(self + 0xD0) == 0) {
                OVScreenPauseFreeride_PlayIconAnim(self, *(int*)(w + 0x18), 1);
            }
        }
        cUIText* t = (cUIText*)cUIScreen_getObjectByHashName(*(void**)(self + 0xC0), GetHashValue32(D_004A2480));
        if (t) {
            cUIText_setUnicodeStringByID(t, GetHashValue32(D_00441BF8[*(int*)(w + 0x18)]));
        }
        break;
    }
    case 2:
        if (*(int*)(self + 0xD0) == 0) {
            if (((sOn_8960*)self)->on[*(int*)(w + 0x18)]) {
                sVEi_8960* vt = *(sVEi_8960**)(w + 8);
                vt[11].fn(w + vt[11].delta, D_004C8B18);
            } else {
                sVEi_8960* vt = *(sVEi_8960**)(w + 8);
                vt[11].fn(w + vt[11].delta, D_004C8B08);
            }
            if (*(int*)(self + 0xD0) == 0) {
                OVScreenPauseFreeride_PlayIconAnim(self, *(int*)(w + 0x18), 0);
            }
        }
        break;
    case 3:
    case 4:
    case 7:
    case 8:
        break;
    }
}


//100%
int func_001F8DF0(void* self)
{
    return 0;
}

//100%
struct cUIScreen;
int GetHashValue32(char* str);
unsigned short cUIScreen_getFrameByLabel(cUIScreen* self, int label);
extern "C" void* cUIScreen_playFrame(void* self, unsigned short frame, int flag);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char* D_00441C30[];
extern char D_004A2488[];
extern char D_004A2490[];

extern "C" void OVScreenPauseFreeride_PlayIconAnim(void* self, int idx, int on)
{
    char buf[64];
    if (on) {
        sprintf(buf, D_004A2488, D_00441C30[idx]);
        unsigned short frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0xC0), GetHashValue32(buf));
        if (frame != 0xFFFF && *(void**)((char*)self + 0xC4) == 0) {
            *(void**)((char*)self + 0xC4) = cUIScreen_playFrame(*(void**)((char*)self + 0xC0), frame, 1);
        }
    } else {
        sprintf(buf, D_004A2490, D_00441C30[idx]);
        unsigned short frame = cUIScreen_getFrameByLabel(*(cUIScreen**)((char*)self + 0xC0), GetHashValue32(buf));
        if (frame != 0xFFFF) {
            *(unsigned short*)((char*)*(void**)((char*)self + 0xC4) + 0xC) = frame;
            *(unsigned short*)((char*)*(void**)((char*)self + 0xC4) + 0xE) = 0xFFFF;
            *(void**)((char*)self + 0xC4) = 0;
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cOVTemplate_PauseMenu_onCreateScreen(void* self);
extern int D_00478160[];

extern "C" void OVScreenPauseMode1_Init(void* self)
{
    int i;
    *(int*)((char*)self + 0xBC) = 6;
    for (i = 0; i < *(int*)((char*)self + 0xBC); i++) {
        ((int*)((char*)self + 0x9C))[i] = D_00478160[i];
    }
    *(int*)((char*)self + 0x110) = 1;
    cOVTemplate_PauseMenu_onCreateScreen(self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cOVTemplate_PauseMenu_onCreateScreen(void* self);
extern int D_00478178[];

extern "C" void OVScreenPauseMode2_Init(void* self)
{
    int i;
    *(int*)((char*)self + 0xBC) = 6;
    for (i = 0; i < *(int*)((char*)self + 0xBC); i++) {
        ((int*)((char*)self + 0x9C))[i] = D_00478178[i];
    }
    *(int*)((char*)self + 0x110) = 2;
    cOVTemplate_PauseMenu_onCreateScreen(self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cOVTemplate_PauseMenu_onCreateScreen(void* self);
extern int D_00478140[];

extern "C" void OVScreenPauseMode3_Init(void* self)
{
    int i;
    *(int*)((char*)self + 0xBC) = 7;
    for (i = 0; i < *(int*)((char*)self + 0xBC); i++) {
        ((int*)((char*)self + 0x9C))[i] = D_00478140[i];
    }
    *(int*)((char*)self + 0x110) = 3;
    cOVTemplate_PauseMenu_onCreateScreen(self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cOVTemplate_PauseMenu_onCreateScreen(void* self);
extern int D_00478190[];

extern "C" void OVScreenPauseMode4_Init(void* self)
{
    int i;
    *(int*)((char*)self + 0xBC) = 5;
    for (i = 0; i < *(int*)((char*)self + 0xBC); i++) {
        ((int*)((char*)self + 0x9C))[i] = D_00478190[i];
    }
    *(int*)((char*)self + 0x110) = 4;
    cOVTemplate_PauseMenu_onCreateScreen(self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cOVTemplate_PauseMenu_onCreateScreen(void* self);
extern int D_004781A8[];

extern "C" void OVScreenPauseMode5_Init(void* self)
{
    int i;
    *(int*)((char*)self + 0xBC) = 5;
    for (i = 0; i < *(int*)((char*)self + 0xBC); i++) {
        ((int*)((char*)self + 0x9C))[i] = D_004781A8[i];
    }
    *(int*)((char*)self + 0x110) = 5;
    cOVTemplate_PauseMenu_onCreateScreen(self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cOVTemplate_PauseMenu_onCreateScreen(void* self);
extern "C" int func_00231AB8(void* game);
extern void* D_004A28A8;
extern int D_004781C0[];
extern int D_004A2868[2];

extern "C" void OVScreenPauseMode6_Init(void* self)
{
    int* items = D_004781C0;
    *(int*)((char*)self + 0xBC) = 3;
    if (func_00231AB8(*(void**)((char*)D_004A28A8 + 0x84)) == 0) {
        items = D_004A2868;
        *(int*)((char*)self + 0xBC) = 2;
    }
    int i;
    for (i = 0; i < *(int*)((char*)self + 0xBC); i++) {
        ((int*)((char*)self + 0x9C))[i] = items[i];
    }
    *(int*)((char*)self + 0x110) = 6;
    cOVTemplate_PauseMenu_onCreateScreen(self);
}

