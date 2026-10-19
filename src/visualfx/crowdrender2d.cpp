#include "visualfx/crowdrender2d.h"
#include <stdint.h>

//100%
//https://decomp.me/scratch/pOTwa

int cCrowdRender2D_cCrowdRender2D(int param_1) {
	cCrowdRender2D_init();
	return param_1;
}

//100%
//https://decomp.me/scratch/zsTkS
void cCrowdRender2D__cCrowdRender2D(int* param_1, int param_2)
{
	cCrowdRender2D_purge(param_1);

	if ((param_2 & 1) != 0) {
		operator_delete(param_1);
	}

	return;
}

//100%
struct sCR2D_init {
    void* file;     // 0x0
    int w;          // 0x4
    int h;          // 0x8
    int fmt;        // 0xC
};
struct sCrowdDef_B7A8 {
    int f0;
    int count;              // 0x4
    char names[16][5];      // 0x8
    char* shapes[16];       // 0x58
    int frames[16];         // 0x98
};
struct sVEnt_B7A8 {
    short delta;
    short index;
    int (*fn)(void*, char*, char*, int, int, int);
};
// PORT: same table as D_00445D38 below, typed with the name and shape fields this function fills
extern sCrowdDef_B7A8 D_00445D38_B7A8[] __asm__("D_00445D38");
extern const char D_004875C0[];
extern char* D_004A5B80;
extern "C" void* FILE_load(const char* name, int flags);
extern "C" char* SHAPE_locate(void* file, const char* name);
// PORT: the mangled name says (void) but the code takes the object in $a0
void cCrowdRender2D_init_impl(sCR2D_init* self) __asm__("cCrowdRender2D_init__Fv");
void cCrowdRender2D_init_impl(sCR2D_init* self)
{
    self->file = FILE_load(D_004875C0, 0x5000000);
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < D_00445D38_B7A8[i].count; j++) {
            char* s = SHAPE_locate(self->file, D_00445D38_B7A8[i].names[j]);
            D_00445D38_B7A8[i].shapes[j] = s;
            char* g = D_004A5B80;
            sVEnt_B7A8* vt = *(sVEnt_B7A8**)(g + 0x10D8);
            D_00445D38_B7A8[i].frames[j] = vt[46].fn(g + vt[46].delta, s, D_00445D38_B7A8[i].names[j], 0, 0, -1);
        }
    }
    char* s = D_00445D38_B7A8[0].shapes[0];
    self->w = *(short*)(s + 4);
    self->h = *(short*)(s + 6);
    self->fmt = *(unsigned char*)s;
}

//100%
struct sVEntP_B8E0 {
    short delta;
    short index;
    void (*fn)(void*, int);
};
extern "C" void MEM_free(void* p);
int cCrowdRender2D_purge(int* param_1)
{
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < D_00445D38_B7A8[i].count; j++) {
            char* g = D_004A5B80;
            sVEntP_B8E0* vt = *(sVEntP_B8E0**)(g + 0x10D8);
            vt[50].fn(g + vt[50].delta, D_00445D38_B7A8[i].frames[j]);
        }
    }
    MEM_free(*(void**)param_1);
}

//100%
//https://decomp.me/scratch/Rbiv4

extern "C" void* cMemMan_alloc(int a, const char* b, uint32_t c, int d);

void* cCrowdRender2D_constructCrowdAnim2D(void* param) {
	void* memory = cMemMan_alloc(0x20, D_004875D8, 0x20000000, 0);
	return cCrowdAnim2D_cCrowdAnim2D(memory, param);
}

//100%
struct sCrowdAnim2D {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    void* f1C;
};

extern int D_00445DD0[];
extern char* D_004A5B64;

void* cCrowdAnim2D_cCrowdAnim2D(void* memory, void* param_1)
{
    sCrowdAnim2D* a = (sCrowdAnim2D*)memory;
    a->f1C = param_1;
    a->f8 = 4;
    a->f4 = 0;
    a->fC = 0;
    a->f10 = D_00445DD0[0];
    a->f0 = 0;
    a->f18 = *(int*)(D_004A5B64 + 0x1C);
    a->f14 = 3;
    return a;
}

//100%
extern "C" int cCrowdAnim2D_advanceFrame(void* self, int frame, int count, int* dir)
{
    switch (*dir) {
    case 0:
        frame++;
        if (frame >= count)
            frame = count - 1;
        break;
    case 1:
        frame--;
        if (frame < 0)
            frame = 0;
        break;
    case 2:
        if (count == 1)
            break;
        frame++;
        if (frame >= count) {
            *dir = 3;
            frame = count - 2;
        }
        break;
    case 3:
        if (count == 1)
            break;
        frame--;
        if (frame < 0) {
            *dir = 2;
            frame = 1;
        }
        break;
    case 4:
        if (count == 1)
            break;
        frame++;
        if (frame >= count)
            frame = 0;
        break;
    }
    return frame;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sCrowdAnimDef_BAC0 {
    int f0;
    int count;              // 0x4
    char pad_0x8[0x90];
    int frames[16];         // 0x98
};

struct sCrowdTrans_BAC0 {
    int anim;
    int mode;
    int kind;
};

extern sCrowdAnimDef_BAC0 D_00445D38[];
extern sCrowdTrans_BAC0 D_00445E10[];
extern int D_00445E20[];
extern "C" int cCrowdAnim2D_advanceFrame(void* self, int frame, int count, int* dir);

struct sCrowdAnim2D_BAC0 {
    int type;               // 0x0
    int anim;               // 0x4
    int dir;                // 0x8
    int frame;              // 0xC
    int tex;                // 0x10
    int delay;              // 0x14
    int last;               // 0x18
    void* param;            // 0x1C
};

extern "C" void cCrowdAnim2D_update(sCrowdAnim2D_BAC0* self)
{
    int now = *(int*)(D_004A5B64 + 0x1C);
    if (now - self->last < self->delay) {
        return;
    }
    self->last = now;
    sCrowdTrans_BAC0* base = &D_00445E10[D_00445E20[self->type]];
    // PORT: int arithmetic on the table address (matches the original operand order).
    sCrowdTrans_BAC0* tr = (sCrowdTrans_BAC0*)(self->anim * (int)sizeof(sCrowdTrans_BAC0) + (int)base);
    if (tr->anim == self->anim) {
        self->frame = cCrowdAnim2D_advanceFrame(self, self->frame, D_00445D38[tr->anim].count, &self->dir);
    } else {
        switch (tr->kind) {
        case 0: {
            int* dir = &self->dir;
            if (*dir == 0) {
                *dir = 1;
            }
            if (self->frame == 0) {
                self->anim = tr->anim;
                self->dir = tr->mode;
                if (self->dir == 1) {
                    self->frame = D_00445D38[self->anim].count - 1;
                } else {
                    self->frame = 0;
                }
            } else {
                self->frame = cCrowdAnim2D_advanceFrame(self, self->frame, D_00445D38[self->anim].count, dir);
            }
            break;
        }
        case 1: {
            int* dir = &self->dir;
            if (*dir == 1) {
                *dir = 0;
            }
            int cnt = D_00445D38[self->anim].count;
            if (self->frame == cnt - 1) {
                self->anim = tr->anim;
                self->dir = tr->mode;
                if (self->dir == 1) {
                    self->frame = D_00445D38[self->anim].count - 1;
                } else {
                    self->frame = 0;
                }
            } else {
                self->frame = cCrowdAnim2D_advanceFrame(self, self->frame, cnt, dir);
            }
            break;
        }
        case 2:
            self->anim = tr->anim;
            self->dir = tr->mode;
            self->frame = cCrowdAnim2D_advanceFrame(self, self->frame, D_00445D38[self->anim].count, &self->dir);
            break;
        }
    }
    self->tex = D_00445D38[self->anim].frames[self->frame];
}

