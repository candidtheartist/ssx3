#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
void* cPSPBezierMan_cPSPBezierMan(void* self);
extern const char D_00492EA0[];

//99.23%
void* cBezierMan_construct()
{
    void* mem = cMemMan_alloc(0x9C90, D_00492EA0, 0, 0);
    return cPSPBezierMan_cPSPBezierMan(mem);
}

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag_AF30(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" void func_00372B78(void* self, int a1, int a2, int a3, int a4, int a5, int a6);
struct cBezierVirt;
extern "C" void func_0038D638(cBezierVirt* self);
extern const char D_00492EB0[];
extern const char D_00492EC0[];
extern const char D_00492ED0[];

struct sUV_AF30 {
    float u, v;
};

struct sUVTables_AF30 {
    char pad0[0x40];
    sUV_AF30 grid6[8][6];       // 0x40
    sUV_AF30 grid8[8][8];       // 0x1C0
};

extern sUVTables_AF30 D_005049C0;

extern "C" void func_0038AF30(void* self)
{
    char* s = (char*)self;
    func_00372B78(s + 0x10, 0x384, 0xDC, 0x8C, 0, 0x92, 0x5D);
    *(void**)(s + 0x440) = operator_new_tag_AF30(0x38400, D_00492EB0, 0, 0);
    *(void**)(s + 0x444) = operator_new_tag_AF30(0xDC00, D_00492EC0, 0, 0);
    *(void**)(s + 0x448) = operator_new_tag_AF30(0x8C00, D_00492ED0, 0, 0);
    *(void**)(s + 0x44C) = *(void**)(s + 0x440);
    *(void**)(s + 0x450) = *(void**)(s + 0x444);
    *(void**)(s + 0x454) = *(void**)(s + 0x448);
    *(int*)(s + 0x344) = 1;
    *(int*)(s + 0x348) = 1;
    *(int*)(s + 0x34C) = 1;
    *(int*)(s + 0x350) = 1;
    *(int*)(s + 0x354) = 0;
    *(float*)(s + 0x358) = 8.0f;
    *(float*)(s + 0x33C) = 3000.0f;
    *(float*)(s + 0x340) = 15000.0f;
    func_0038D638((cBezierVirt*)self);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            sUV_AF30 t;
            t.v = (float)i * 0.2f;
            t.u = (float)j * 0.2f;
            D_005049C0.grid6[j][i] = t;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sUV_AF30 t;
            t.v = (float)i * 0.1428571492433548f;
            t.u = (float)j * 0.1428571492433548f;
            D_005049C0.grid8[j][i] = t;
        }
    }
}

//100%
void func_0038D660(void*);
void cMemMan_free(void*);

extern "C" void func_0038B0F8(void* self)
{
    func_0038D660(self);
    if (*(void**)((char*)self + 0x440) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x440));
    }
    if (*(void**)((char*)self + 0x444) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x444));
    }
    if (*(void**)((char*)self + 0x448) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x448));
    }
}

extern "C" void* func_003739D0(void*);

//100%
void* PS2BezierMan_v04(void* self)
{
    return func_003739D0((char*)self + 0x10);
}

//100%
void func_0038B178(void* self)
{
    *(int*)((char*)self + 0x458) = 0;
    *(int*)((char*)self + 0x3c9c) = 0;
    *(int*)((char*)self + 0x4a60) = 0;
    *(int*)((char*)self + 0x4d84) = 0;
}

//100%
struct sBezPatch_B190 {
    void* obj;              // 0x0
    int extra;              // 0x4
    int kind;               // 0x8
    unsigned short tex;     // 0xC
    short pad;
};

struct sBezMixPatch_B190 {
    void* obj;              // 0x0
    int extra;              // 0x4
    int kind;               // 0x8
    unsigned short tex;     // 0xC
    short pad;
    unsigned char types[4]; // 0x10
};

struct sBezMan_B190 {
    char pad_0x0[0x458];
    int n4;                         // 0x458
    sBezPatch_B190 list4[900];      // 0x45C
    int n6;                         // 0x3C9C
    sBezPatch_B190 list6[220];      // 0x3CA0
    int n8;                         // 0x4A60
    sBezPatch_B190 list8[50];       // 0x4A64
    int nMix;                       // 0x4D84
    sBezMixPatch_B190 mix[75];      // 0x4D88
};

struct sBezObj_B190 {
    char pad_0x0[0x1A6];
    unsigned short tex4;    // 0x1A6
    unsigned short tex6;    // 0x1A8
    unsigned short tex8;    // 0x1AA
};

extern "C" void func_0038B190(sBezMan_B190* m, sBezObj_B190* o, unsigned char* t, int unused, int extra)
{
    if (t[0] == t[2] && t[1] == t[3] && t[0] == t[1]) {
        switch (t[0]) {
        case 4:
            if (m->n4 < 900) {
                sBezPatch_B190* e = &m->list4[m->n4++];
                e->extra = extra;
                e->obj = o;
                e->kind = 0;
                e->tex = o->tex4;
            }
            break;
        case 6:
            if (m->n6 < 220) {
                sBezPatch_B190* e = &m->list6[m->n6++];
                e->extra = extra;
                e->kind = 1;
                e->obj = o;
                e->tex = o->tex6;
            }
            break;
        case 8:
            if (m->n8 < 50) {
                sBezPatch_B190* e = &m->list8[m->n8++];
                e->extra = extra;
                e->kind = 2;
                e->obj = o;
                e->tex = o->tex8;
            }
            break;
        }
        return;
    }
    if (m->nMix < 75) {
        sBezMixPatch_B190* e = &m->mix[m->nMix++];
        e->extra = extra;
        e->obj = o;
        int* pk = &e->kind;
        *pk = (t[0] == 8 || t[1] == 8 || t[2] == 8 || t[3] == 8) ? 2 : 0;
        e->tex = o->tex8;
        for (int i = 0; i < 4; i++) {
            e->types[i] = t[i];
        }
    }
}

//100%
extern int D_004A44D4;

struct sBezVEntry_B338 {
    short delta;
    short index;
    void (*fn)(void*, void*, void*, void*, void*, int);
};

extern "C" void PS2BezierMan_v21(void* self, void* a, void* b, void* c, void* d)
{
    if (D_004A44D4 == 0) {
        sBezVEntry_B338* vt = *(sBezVEntry_B338**)((char*)self + 0x4);
        vt[22].fn((char*)self + vt[22].delta, a, b, c, d, 0);
    }
}

INCLUDE_ASM("render/bezierman", PS2BezierMan_v18);

INCLUDE_ASM("render/bezierman", func_0038C590);

//100%
struct sBezMan_C788 {
    char pad0[0x58];
    unsigned int vtx[3];
    unsigned int nrm[3];
    unsigned int col[3];
    char pad7C[0x44C - 0x7C];
    unsigned int pkt[3];
};

static inline unsigned int bezVtx_C788(sBezMan_C788* self, int mode, int idx)
{
    switch (mode) {
    case 0:
        return self->vtx[0] + idx * 0xC0;
    case 1:
        return self->vtx[1] + idx * 0x1B0;
    case 2:
        return self->vtx[2] + idx * 0x300;
    }
    return 0;
}

static inline unsigned int bezNrm_C788(sBezMan_C788* self, int mode, int idx)
{
    switch (mode) {
    case 0:
        return self->nrm[0] + idx * 0x80;
    case 1:
        return self->nrm[1] + idx * 0x120;
    case 2:
        return self->nrm[2] + idx * 0x200;
    }
    return 0;
}

static inline unsigned int bezCol_C788(sBezMan_C788* self, int mode, int idx)
{
    switch (mode) {
    case 0:
        return self->col[0] + idx * 0x80;
    case 1:
        return self->col[1] + idx * 0x120;
    case 2:
        return self->col[2] + idx * 0x200;
    }
    return 0;
}

extern "C" void func_0038C788(sBezMan_C788* self, int mode, int idx)
{
    int n = mode * 2 + 4;
    unsigned int a0 = bezVtx_C788(self, mode, idx);
    unsigned int a1 = bezNrm_C788(self, mode, idx);
    unsigned int a2 = bezCol_C788(self, mode, idx);
    int sq = n * n;
    ulong* p = (ulong*)((self->pkt[mode] + idx * 0x100) | 0x30000000);
    p[0] = 0x10000003;
    p[1] = 0;
    p[2] = 0x3000000005000000;
    p[3] = 0;
    p[4] = 0x3F8000003F800000;
    p[5] = 0x4040404020000000;
    p[6] = 0;
    p[7] = (ulong)((sq << 16) | 0x78008000) << 32;
    p[8] = ((sq * 3) >> 2) | 0x30000000 | ((ulong)a0 << 32);
    p[9] = 0;
    p[10] = 0x10000001;
    p[11] = 0;
    p[12] = 0x5050505020000000;
    p[13] = (ulong)((sq << 16) | 0x74008040) << 32;
    p[14] = (sq >> 1) | 0x30000000 | ((ulong)a1 << 32);
    p[15] = 0;
    p += 16;
    p[0] = 0x10000001;
    p[1] = 0;
    p[2] = 0x5050505020000000;
    p[3] = (ulong)((sq << 16) | 0x74008080) << 32;
    p[4] = (sq >> 1) | 0x30000000 | ((ulong)a2 << 32);
    p[5] = 0;
    p += 6;
    p[0] = 0x60000000;
    p[1] = 0;
}

//100%
extern void* D_004A5B80;
extern "C" unsigned int func_0037DF88(void* self, void* a1, void* a2);

struct sBezVec4_CA08 {
    float x, y, z, w;
};

extern "C" void func_0038CA08(void* self, void* obj)
{
    char* o = (char*)obj;
    sBezVec4_CA08 a;
    sBezVec4_CA08 b;
    a.x = *(float*)(o + 0x158);
    a.y = *(float*)(o + 0x15C);
    a.z = *(float*)(o + 0x160);
    a.w = 1.0f;
    b.x = *(float*)(o + 0x164);
    b.y = *(float*)(o + 0x168);
    b.z = *(float*)(o + 0x16C);
    b.w = 1.0f;
    func_0037DF88(D_004A5B80, &a, &b);
}

struct sBezRS_CE20 {
    int w0;
    int w4;
    int w8;
    int wC;
    short h10;
    short h12;
};

struct sBezRec_CE20 {
    sBezRS_CE20 rs;
    unsigned int start;
    unsigned int end;
    short tag;
    short pad;
    char pad20[0x60];
};

struct sBezCnt_CE20 {
    int count;
    char pad4[0x80 - 4];
    sBezRec_CE20 recs[1];
};

struct sBezGfx_CE20 {
    char pad0[0xE84];
    sBezRS_CE20* top;
    char padE88[0x18F0 - 0xE88];
    sBezCnt_CE20* cnt;
};

struct sBezObj_CE20 {
    char pad0[0xC];
    int flags;
    char pad10[0x1A0 - 0x10];
    short tx;
    short ty;
};

struct sBezMan_CE20 {
    char pad0[0x30];
    unsigned int vtx;
    char pad34[0x454 - 0x34];
    unsigned int pkt;
};

struct sBezTex_CE20 {
    unsigned int reg;
    unsigned int pad;
};

extern sBezGfx_CE20* D_004A5B80_CE20 __asm__("D_004A5B80");
extern int D_004A44D8;
extern int D_004A44DC;
extern sBezTex_CE20 D_00504960[];
extern "C" void* func_0038F708(void* obj, int a1, int a2);
extern "C" int func_0038CA08_r(void* self, void* obj) __asm__("func_0038CA08");
extern "C" void func_0038D168(void* self, unsigned int vtx, void* obj, int mode, sBezTex_CE20* tex, unsigned int* a2, unsigned int* pp);
extern "C" void func_0038D448(void* self, int mode, sBezTex_CE20* tex, unsigned int* a2, int r, unsigned int* pp);

//100%
struct sBezQ_CA70 {
    short tx;
    short ty;
    int mode;
    unsigned int base;
    int* a3;
};

struct sBezMan_CA70 {
    char pad0[0x28];
    unsigned int vtx[3];
    char pad34[0x44C - 0x34];
    unsigned int pkt[3];
    char pad458[0x5364 - 0x458];
    int qn;
    sBezQ_CA70 q[1];
};

extern sBezTex_CE20* D_0044B9D0[];

extern "C" void func_0038CA70(sBezMan_CA70* self, int mode, int idx, int* a3, unsigned int* pp)
{
    unsigned int vtx = self->vtx[mode] + idx * 0xC;
    sBezObj_CE20* obj = (sBezObj_CE20*)func_0038F708((void*)a3[0], 0x1B0, 2);
    int any = 0;
    unsigned int base = self->pkt[mode] + idx * 0x100;
    int dim = mode * 2 + 4;
    sBezGfx_CE20* gfx = D_004A5B80_CE20;
    int a = (obj->flags & 0x600000) && dim;
    if (a) {
        if (D_004A44D8 != 0) {
            a = 0;
        } else {
            any = a != 0;
        }
    }
    int r = 0;
    if (mode == 2) {
        r = func_0038CA08_r(self, obj);
    }
    int b = r != 0;
    if (b) {
        if (D_004A44DC != 0) {
            b = 0;
        } else {
            any |= b;
        }
    }
    switch (obj->flags & 0x180000) {
    case 0x80000:
        any = 1;
        gfx->top->w0 = (gfx->top->w0 & ~0xC) | 8;
        break;
    case 0x100000:
        any = 1;
        gfx->top->w0 = (gfx->top->w0 & ~0xC) | 4;
        break;
    case 0x180000:
        any = 1;
        gfx->top->w0 |= 0xC;
        break;
    default:
        gfx->top->w0 &= ~0xC;
        break;
    }
    if (any) {
        int tx = obj->tx;
        gfx->top->h10 = tx;
        int ty = obj->ty;
        gfx->top->h12 = ty;
        unsigned int q = *pp;
        ulong* p = (ulong*)(q | 0x30000000);
        p[0] = ((ulong)base << 32) | 0x50000000;
        p[1] = 0;
        p[2] = 0x10000001;
        p[3] = 0;
        int k = a3[1];
        sBezTex_CE20* tex = D_0044B9D0[mode];
        p[4] = 0;
        p[5] = (ulong)(tex[k + 2].reg | 0x14000000) << 32;
        p += 6;
        unsigned int end = (unsigned int)p & 0x0FFFFFFF;
        *pp = end;
        sBezCnt_CE20* cnt = gfx->cnt;
        sBezRS_CE20* top = gfx->top;
        if (cnt->count < 0xA28) {
            top->w8 = (top->w8 & ~0x1F) | (*(int*)((char*)cnt + 0x69CC4) & 0x1F);
            int key = *(int*)((char*)cnt + 0x69CC0);
            sBezRec_CE20* rec = (sBezRec_CE20*)((cnt->count++ << 7) + ((unsigned int)cnt->recs | 0x30000000));
            rec->rs = *top;
            rec->start = q;
            rec->end = end;
            rec->tag = key;
            rec->pad = 0;
        }
        *pp += 0x10;
        if (a) {
            func_0038D168(self, vtx, obj, mode, tex, (unsigned int*)a3, pp);
        }
        if (b) {
            func_0038D448(self, mode, tex, (unsigned int*)a3, r, pp);
        }
    } else {
        self->q[self->qn].tx = obj->tx;
        self->q[self->qn].ty = obj->ty;
        self->q[self->qn].mode = mode;
        self->q[self->qn].base = base;
        self->q[self->qn].a3 = a3;
        self->qn++;
    }
}

//100%
extern "C" void func_0038CE20(sBezMan_CE20* self, int idx, unsigned int* a2, int* a3, unsigned int* pp)
{
    unsigned int vtx = self->vtx + idx * 0xC;
    sBezObj_CE20* obj = (sBezObj_CE20*)func_0038F708((void*)a2[0], 0x1B0, 2);
    unsigned int base = self->pkt + idx * 0x100;
    sBezGfx_CE20* gfx = D_004A5B80_CE20;
    int a = (obj->flags & 0x600000) != 0;
    if (a && D_004A44D8 != 0) {
        a = 0;
    }
    int r = func_0038CA08_r(self, obj);
    int tx = obj->tx;
    int b = r != 0;
    gfx->top->h10 = tx;
    if (D_004A44DC != 0) {
        b = 0;
    }
    int ty = obj->ty;
    gfx->top->h12 = ty;
    switch (obj->flags & 0x180000) {
    case 0x80000:
        gfx->top->w0 = (gfx->top->w0 & ~0xC) | 8;
        break;
    case 0x100000:
        gfx->top->w0 = (gfx->top->w0 & ~0xC) | 4;
        break;
    case 0x180000:
        gfx->top->w0 |= 0xC;
        break;
    default:
        gfx->top->w0 &= ~0xC;
        break;
    }
    unsigned int q = *pp;
    ulong* p = (ulong*)(q | 0x30000000);
    if (a3 != 0) {
        p[0] = 0x10000002;
        p[1] = 0;
        p[2] = ((ulong)*a3 << 32) | 0x6E0180D0;
        p[3] = 0;
        p[4] = 0;
        p[5] = (ulong)0x6C1080C0 << 32;
        p[6] = ((ulong)(*a2 + 0x40) << 32) | 0x30000010;
        p[7] = 0;
        p += 8;
    }
    sBezTex_CE20* tex = D_00504960;
    p[0] = ((ulong)base << 32) | 0x50000000;
    p[1] = 0;
    p[2] = 0x10000001;
    p[3] = 0;
    int k = a2[1] + 2;
    p[4] = 0;
    p[5] = (ulong)(tex[k].reg | 0x14000000) << 32;
    p += 6;
    unsigned int end = (unsigned int)p & 0x0FFFFFFF;
    *pp = end;
    sBezCnt_CE20* cnt = gfx->cnt;
    sBezRS_CE20* top = gfx->top;
    if (cnt->count < 0xA28) {
        top->w8 = (top->w8 & ~0x1F) | (*(int*)((char*)cnt + 0x69CC4) & 0x1F);
        int key = *(int*)((char*)cnt + 0x69CC0);
        sBezRec_CE20* rec = (sBezRec_CE20*)((cnt->count++ << 7) + ((unsigned int)cnt->recs | 0x30000000));
        rec->rs = *top;
        rec->start = q;
        rec->end = end;
        rec->tag = key;
        rec->pad = 0;
    }
    *pp += 0x10;
    if (a) {
        func_0038D168(self, vtx, obj, 2, tex, a2, pp);
    }
    if (b) {
        func_0038D448(self, 2, tex, a2, r, pp);
    }
}

INCLUDE_ASM("render/bezierman", func_0038D168);

INCLUDE_ASM("render/bezierman", func_0038D448);

//100%
class cBezierVirt {
public:
    int field_0x0;
    // vptr lands at 0x4 (g++ 2.95 places it after the class's own data);
    // slot N lives at vtable offset N*8 (delta at +0, function at +4)
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
};

extern "C" void func_0038D638(cBezierVirt* self)
{
    self->v17();
}

//100%
void func_0038D660(void* self)
{
}

INCLUDE_ASM("render/bezierman", func_0038D668);

//100%
struct sVec3_D690 { float x, y, z; };
struct sQuad_D690 { long lo; long hi; } __attribute__((aligned(16)));
struct sRS_D690 {
    int f0;
    int f4;
    int f8;
    int fC;
    short tex;
    short pad;
};
struct sEnt_D690 {
    sRS_D690 rs;                    // 0x00
    unsigned int buf;               // 0x14
    unsigned int next;              // 0x18
    short key;                      // 0x1C
    short flag;                     // 0x1E
    char pad_0x20[0x60];
};
struct sRing_D690 {
    int count;                      // 0x0
    char pad_0x4[0x7C];
    sEnt_D690 ents[1];              // 0x80
};
struct sGfx_D690 {
    char pad_0x0[0xC4];
    float detailScale;              // 0xC4
    char pad_0xC8[0xE84 - 0xC8];
    sRS_D690* top;                  // 0xE84
    char pad_0xE88[0x18F0 - 0xE88];
    sRing_D690* ring;               // 0x18F0
};
extern float D_004A4348;
extern void* D_004A4474;
extern sGfx_D690* D_004A5B80_D690 __asm__("D_004A5B80");
extern char D_1460[];
extern "C" char* func_0038F460(void* self, unsigned int addr, int size, int flags);
extern "C" unsigned int func_0038F668(void* self, char* end, int arg);

static inline void CopyQuads_D690(char** pp, sQuad_D690* src, int n)
{
    sQuad_D690* d = (sQuad_D690*)*pp;
    sQuad_D690* end = d + n;
    while (d != end) {
        *d++ = *src++;
    }
    *pp = (char*)d;
}

// PORT: uncached (0x30000000) pointers and VU microprogram addresses held in int.
extern "C" void func_0038D690(void* self, void* obj, void* patch, unsigned int* handle)
{
    char* s = (char*)self;
    char* o = (char*)obj;
    if ((*(int*)(o + 0xC) & 0x800000) == 0) {
        return;
    }
    sVec3_D690 d;
    d.z = *(float*)(o + 0x160) - *(float*)(o + 0x16C);
    sGfx_D690* gfx = D_004A5B80_D690;
    d.x = *(float*)(o + 0x158) - *(float*)(o + 0x164);
    d.y = *(float*)(o + 0x15C) - *(float*)(o + 0x168);
    int n = (int)((d.x * d.x + d.y * d.y + d.z * d.z) * (D_004A4348 * 3.3333333249174757e-07f) * gfx->detailScale);
    if (*(int*)((char*)patch + 8) < 2) {
        n /= 2;
    }
    if (n <= 0) {
        return;
    }
    unsigned int buf = *handle;
    char* p = func_0038F460(D_004A4474, buf, -1, 0);
    ((long*)p)[0] = 0x10000018;
    ((long*)p)[1] = 0;
    ((long*)p)[2] = 0;
    ((long*)p)[3] = (long)0x6C168000 << 32;
    *(int*)(s + 0x43C) = n;
    p += 0x20;
    CopyQuads_D690(&p, (sQuad_D690*)(o + 0x40), 16);
    CopyQuads_D690(&p, (sQuad_D690*)(s + 0x3E0), 4);
    CopyQuads_D690(&p, (sQuad_D690*)(s + 0x420), 2);
    ((long*)p)[0] = (long)(((unsigned int)D_1460 >> 3) | 0x14000000) << 32;
    ((long*)p)[1] = (long)0x11000000 << 32;
    p += 0x10;
    unsigned int next = func_0038F668(D_004A4474, p, 4);
    *handle = next;
    sRing_D690* ring = gfx->ring;
    sRS_D690* rs = gfx->top;
    if (ring->count < 0xA28) {
        rs->f8 = (rs->f8 & ~0x1F) | (*(int*)((char*)ring + 0x69CC4) & 0x1F);
        int key = *(int*)((char*)ring + 0x69CC0);
        sEnt_D690* e = (sEnt_D690*)((ring->count++ << 7) + ((unsigned int)ring->ents | 0x30000000));
        e->rs = *rs;
        e->buf = buf;
        e->next = next;
        e->key = key;
        e->flag = 0;
    }
    *handle += 0x10;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sRS_D968 {
    int field_0x0;
    int flagsA;
    int flagsB;
    int field_0xC;
    short tex;
    short pad;
};
struct sCtx_D968 {
    char pad_0x0[0x64];
    int texSel;                                 // 0x64
    char pad_0x68[0xE84 - 0x68];
    sRS_D968* top;                              // 0xE84
    char pad_0xE88[0xF50 - 0xE88];
    int texIds[(0x6B90 - 0xF50) / 4];           // 0xF50
    int field_0x6B90;                           // 0x6B90
};
struct sBezPatch_D968 {
    void* obj;
    int extra;
    int kind;
    unsigned short tex;
    short pad;
};
struct sBezMixPatch_D968 {
    void* obj;
    int extra;
    int kind;
    unsigned short tex;
    short pad;
    unsigned char types[4];
};
struct sBezMan_D968 {
    char pad_0x0[0x4A60];
    int n8;                         // 0x4A60
    sBezPatch_D968 list8[50];       // 0x4A64
    int nMix;                       // 0x4D84
    sBezMixPatch_D968 mix[75];      // 0x4D88
};
extern int D_004A44E0;
extern sCtx_D968* D_004A5B80_D968 __asm__("D_004A5B80");
extern "C" void func_0037D968(sCtx_D968* ctx);
extern "C" void* func_0038F708(void* obj, int a1, int a2);
extern "C" void func_0038D690(void* self, void* obj, void* patch, unsigned int* handle);

extern "C" void func_0038D968(sBezMan_D968* self, unsigned int* a1)
{
    if (D_004A44E0 != 0) {
        return;
    }
    sCtx_D968* ctx = D_004A5B80_D968;
    ctx->top[1] = ctx->top[0];
    sRS_D968* t = ctx->top;
    ctx->top = t + 1;
    int tex = ctx->texIds[ctx->texSel];
    t[1].tex = tex;
    ctx->top->flagsA = (ctx->top->flagsA & ~0x7C) | 0x54;
    ctx->top->flagsB = (ctx->top->flagsB & ~0x3E0) | 0x80;
    ctx->top->flagsA = (ctx->top->flagsA & 0xFE7FFFFF) | 0x800000;
    ctx->top->flagsA = (ctx->top->flagsA & 0xFFCFFFFF) | 0x300000;
    ctx->top->flagsA = (ctx->top->flagsA & 0xFFF00FFF) | 0x5C000;
    ctx->top->flagsA = (ctx->top->flagsA & 0xFFBFFFFF) | 0x400000;
    if (ctx->field_0x6B90 == 0) {
        func_0037D968(ctx);
    }
    ctx->top->field_0x0 = (ctx->top->field_0x0 & ~0x3C0) | 0x100;
    ctx->top->field_0xC = ctx->top->field_0xC & 0xC0000000;
    ctx->top->flagsA = (ctx->top->flagsA & ~3) | 2;
    ctx->top->flagsB = ctx->top->flagsB & 0xE00003FF;
    for (int i = 0; i < self->n8; i++) {
        sBezPatch_D968* e = &self->list8[i];
        func_0038D690(self, func_0038F708(e->obj, 0x1B0, 2), e, a1);
    }
    for (int i = 0; i < self->nMix; i++) {
        sBezMixPatch_D968* e = &self->mix[i];
        if (e->kind > 0) {
            func_0038D690(self, func_0038F708(e->obj, 0x1B0, 2), e, a1);
        }
    }
    ctx->top--;
}

