#include "common.h"

INCLUDE_ASM("seg/seg_1DCD10", FXLoader_ctor);

//100%
struct Pre_BEE0 { char pad[0x10D8]; };
class Mgr_BEE0 : Pre_BEE0 {
public:
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
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
  virtual void v48b();
  virtual void v50(int);
};
extern Mgr_BEE0 *D_004A5B80;
void operator_delete(int *);
extern "C" void func_002DBEE0(int *self, int flags) {
    Mgr_BEE0 *m = D_004A5B80;
    int i;
    for (i = 0; i < 0x51; i++) {
        int *slot = (int*)((char*)m + 0xF50) + i;
        if (*slot != -1) {
            m->v50(*slot);
            *slot = -1;
        }
    }
    if (flags & 1) operator_delete(self);
}

//100%
extern char D_00488308[];
extern "C" void *func_002DBF80(int *self) {
    self[0] = 0;
    *(char**)((char*)self + 4) = D_00488308;
    return self;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_00418EF8_BF98(void* base, int n, int size, int (*cmp)(void*, void*)) __asm__("func_00418EF8");
extern "C" int func_002DC168(void* arg0, void* arg1);
struct RS_BF98 {
    unsigned int w0_lo : 2;
    unsigned int a : 2;
    unsigned int w0_hi : 28;
    unsigned int b : 2;
    unsigned int c : 5;
    unsigned int w1_p7 : 5;
    unsigned int d : 8;
    unsigned int e : 2;
    unsigned int f : 1;
    unsigned int g : 2;
    unsigned int w1_hi : 7;
    unsigned int w2_lo : 5;
    unsigned int h : 5;
    unsigned int i : 19;
    unsigned int w2_hi : 3;
    int w3;
    int w4;
};
struct Ctx_BF98 { char pad[0xE84]; RS_BF98* top; char pad2[0xF60 - 0xE88]; int f60; };
extern Ctx_BF98* D_004A289C;
extern char D_00537AC0[];
struct VEnt_BF98 { short delta; short idx; void (*fn)(void*); };
struct Obj_BF98 { int n; char* vt; };

static inline void Push_BF98() {
    Ctx_BF98* ctx = D_004A289C;
    ctx->top[1] = ctx->top[0];
    ctx->top++;
}
static inline void Pop_BF98() {
    D_004A289C->top--;
}
static inline void G3_BF98(int c, int f, int g, int e, int d) {
    Ctx_BF98* ctx = D_004A289C;
    ctx->top->c = c;
    ctx->top->f = f;
    ctx->top->g = g;
    ctx->top->e = e;
    ctx->top->d = d;
}

extern "C" void func_002DBF98(Obj_BF98* self) {
    if (self->n) {
        func_00418EF8_BF98(D_00537AC0, self->n, 8, func_002DC168);
        Push_BF98();
        {
            Ctx_BF98* ctx = D_004A289C;
            int v = ctx->f60;
            ctx->top->h = 7;
            ctx->top->b = 2;
            ctx->top->i = 0x3FF;
            *(short*)((char*)ctx->top + 0x10) = v;
        }
        {
            Ctx_BF98* ctx = D_004A289C;
            ctx->top->a = 3;
            *(short*)((char*)ctx->top + 0x12) = -1;
        }
        G3_BF98(5, 1, 0, 3, 0);
        {
            VEnt_BF98* e = (VEnt_BF98*)(self->vt + 0x18);
            e->fn((char*)self + e->delta);
        }
        Pop_BF98();
        self->n = 0;
    }
}

//100%
extern "C" int func_002DC168(void *arg0, void *arg1) {
    int temp_3;
    int temp_4;

    temp_4 = (*(int *)((char*)(arg0) + (4)));
    temp_3 = (*(int *)((char*)(arg1) + (4)));
    if (temp_4 >= temp_3) {
        return (temp_3 >= temp_4) ? 0 : -1;
    }
    return 1;
}

INCLUDE_ASM("seg/seg_1DCD10", cPS2FogParticleMan_v02);

//100%
struct sDma_C7B0 {
    char pad[0x10];
    int size : 28;
};
struct sRS_C7B0 {
    int f0;
    int f4;
    int f8;
    int fC;
    short tex;
    short pad;
};
struct sEnt_C7B0 {
    sRS_C7B0 rs;
    unsigned int buf;
    unsigned int next;
    short key;
    short flag;
    char pad_0x20[0x60];
};
struct sRing_C7B0 {
    int count;
    char pad_0x4[0x7C];
    sEnt_C7B0 ents[1];
};
struct sGfx_C7B0 {
    char pad_0x0[0xE84];
    sRS_C7B0* top;
    char pad_0xE88[0x18F0 - 0xE88];
    sRing_C7B0* ring;
    char pad_0x18F4[0x5A00 - 0x18F4];
    unsigned int bufAddr;
};
struct sVtx_C7B0 {
    float x0, y0, z0, q;
    float x1, y1, z1, w1;
    float a, r, g, b;
};
struct sList_C7B0 {
    int count;
    int pad[3];
    sVtx_C7B0 v[1];
};
struct sSort_C7B0 { int idx; int key; };

// PORT: asm-label aliases; these globals and calls are declared with other types elsewhere.
// GS packet words are 64-bit `unsigned long`, and uncached (0x30000000) pointers are held in int.
extern sDma_C7B0* D_004A4474_C7B0 __asm__("D_004A4474");
extern sGfx_C7B0* D_004A5B80_C7B0 __asm__("D_004A5B80");
extern "C" unsigned long* func_0038F460_C7B0(sDma_C7B0* dma, unsigned int buf, int a2, int a3) __asm__("func_0038F460");
extern "C" unsigned int func_0038F668_C7B0(sDma_C7B0* dma, unsigned long* p, int a2) __asm__("func_0038F668");

static inline int FBits_C7B0(float f) { return *(int*)&f; }

extern "C" void func_002DC7B0(sList_C7B0* list)
{
    int left = list->count;
    int start = 0;
    int max = (D_004A4474_C7B0->size - 4) * 2 / 5 - 1;
    sGfx_C7B0* g = D_004A5B80_C7B0;
    if (left <= 0) return;
    float one = 1.0f;
    do {
        int n = max;
        unsigned int buf = g->bufAddr;
        if (left < n) n = left;
        unsigned long* p = func_0038F460_C7B0(D_004A4474_C7B0, buf, -1, 0);
        int pad;
        int qwc;
        float st0[2];
        float st1[2];
        st0[0] = 0.0f;
        st0[1] = 0.0f;
        st1[0] = one;
        st1[1] = one;
        if ((n & 1) == 0) {
            pad = 0;
            qwc = (n * 5 >> 1) + 3;
        } else {
            pad = 1;
            qwc = (n * 5 >> 1) + 4;
        }
        p[0] = (qwc + 1) | 0x10000000;
        p[1] = 0;
        p[2] = 0;
        p[3] = (unsigned long)(qwc | 0x50000000) << 32;
        p[4] = ((unsigned long)0x14000000 << 32) | 0x8001;
        p[5] = 0;
        p[6] = 0x56;
        p[7] = 0;
        p[8] = (n | 0x8000) | ((unsigned long)0xA800 << 47);
        p[9] = 0x52512;
        int rest = left - n;
        p += 10;
        for (int i = start; i < start + n; i++) {
            sVtx_C7B0* v = &list->v[((sSort_C7B0*)D_00537AC0)[i].idx];
            float q = v->q;
            p[0] = FBits_C7B0(st0[0] * q) | ((unsigned long)FBits_C7B0(st0[1] * q) << 32);
            p[1] = (int)v->r | ((unsigned long)(int)v->g << 8) | ((unsigned long)(int)v->b << 16) | ((unsigned long)(int)v->a << 24) | ((unsigned long)FBits_C7B0(q) << 32);
            p[2] = (int)v->x0 | ((unsigned long)(int)v->y0 << 16) | ((unsigned long)(int)(v->z0 * q) << 32);
            p[3] = FBits_C7B0(st1[0] * q) | ((unsigned long)FBits_C7B0(st1[1] * q) << 32);
            p[4] = (int)v->x1 | ((unsigned long)(int)v->y1 << 16) | ((unsigned long)(int)(v->z1 * q) << 32);
            p += 5;
        }
        if (pad) *p++ = 0;
        unsigned int next = func_0038F668_C7B0(D_004A4474_C7B0, p, 4);
        sRing_C7B0* ring = g->ring;
        sRS_C7B0* rs = g->top;
        if (ring->count < 0xA28) {
            rs->f8 = (rs->f8 & ~0x1F) | (*(int*)((char*)ring + 0x69CC4) & 0x1F);
            int key = *(int*)((char*)ring + 0x69CC0);
            sEnt_C7B0* e = (sEnt_C7B0*)((ring->count++ << 7) + ((unsigned int)ring->ents | 0x30000000));
            e->rs = *rs;
            e->buf = buf;
            e->next = next;
            e->key = key;
            e->flag = 0;
        }
        g->bufAddr = next + 0x10;
        left = rest;
        start += n;
    } while (left > 0);
}
