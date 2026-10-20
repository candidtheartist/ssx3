#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void cInstanceNode_getBoundBoxInfo(void* self, void* out);
extern const char D_0048E890[];

struct cFloatingNode {
    char pad_0x00[0x78];
    void* field_0x78;
};

//100%
// PORT: the unit declares cInstanceNode_getBoundBoxInfo with 2 args; its body uses 3 ($6 is written).
void cInstanceNode_getBoundBoxInfo_3(void* self, void* box, void* out) __asm__("cInstanceNode_getBoundBoxInfo");

void cFloatingNode_initInfo(cFloatingNode* self)
{
    void* mem = cMemMan_alloc(0x30, D_0048E890, 0x20000000, 0);
    self->field_0x78 = mem;
    cInstanceNode_getBoundBoxInfo_3(self, mem, (char*)mem + 0x20);
}

//100%
void operator_delete(int* ptr);

extern "C" void func_0034EF08(cFloatingNode* self)
{
    if (self->field_0x78 != 0) {
        operator_delete((int*)self->field_0x78);
        self->field_0x78 = 0;
    }
}

//100%
struct sBox_F048;
extern "C" void* World_GetNash();
extern "C" void cSpaceHash_moveItem(void* world, int type, void* id, sBox_F048* box, sBox_F048* old);
extern "C" void cMoveNode_v50(void* self);

struct sFlVec4_34EF40 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sFlBox_34EF40 {
    sFlVec4_34EF40 min;
    sFlVec4_34EF40 max;
};

struct sFlInfo_34EF40 {
    sFlBox_34EF40 box;
    float radius;
};

// PORT: PS2-only VU0 inline asm (a - b).
static inline sFlVec4_34EF40 vu0Sub_34EF40(const sFlVec4_34EF40& a, const sFlVec4_34EF40& b)
{
    sFlVec4_34EF40 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (a + b).
static inline sFlVec4_34EF40 vu0Add_34EF40(const sFlVec4_34EF40& a, const sFlVec4_34EF40& b)
{
    sFlVec4_34EF40 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b)
        : "memory");
    return r;
}

struct sFlVEntry_34EF40 {
    short delta;
    short index;
    char* (*fn)(void*);
};

static inline sFlVec4_34EF40 nodePos_34EF40(char* self)
{
    sFlVEntry_34EF40* vt = *(sFlVEntry_34EF40**)(self + 0xC);
    return *(sFlVec4_34EF40*)(vt[24].fn(self + vt[24].delta) + 0x30);
}

extern "C" void Floating_v50(char* self)
{
    sFlInfo_34EF40* info = *(sFlInfo_34EF40**)(self + 0x78);
    if (info != 0) {
        sFlBox_34EF40 nb;
        sFlBox_34EF40 old = info->box;
        float r = info->radius;
        sFlVec4_34EF40 ext;
        ext.x = r;
        ext.y = r;
        ext.z = r;
        ext.w = 0.0f;
        nb.min = vu0Sub_34EF40(nodePos_34EF40(self), ext);
        nb.max = vu0Add_34EF40(nodePos_34EF40(self), ext);
        (*(sFlInfo_34EF40**)(self + 0x78))->box = nb;
        void* id = *(void**)(self + 0x18);
        cSpaceHash_moveItem(World_GetNash(), 0, id, (sBox_F048*)&nb, (sBox_F048*)&old);
    } else {
        cMoveNode_v50(self);
    }
}

//100%
struct sVec4_F048 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct sBox_F048 {
    sVec4_F048 min;
    sVec4_F048 max;
};

struct sInst_F048 {
    char pad_0x00[0x60];
    float min[3];   // 0x60
    float max[3];   // 0x6C
};

extern "C" void* World_GetNash();
extern "C" void cSpaceHash_moveItem(void* world, int type, void* id, sBox_F048* box, sBox_F048* old);
extern "C" void cMoveNode_v49(void* self);

extern "C" void Floating_v49(cFloatingNode* self)
{
    sBox_F048* info = (sBox_F048*)self->field_0x78;
    if (info != 0) {
        sBox_F048 nb;
        sBox_F048 old = *info;
        sInst_F048* inst = *(sInst_F048**)((char*)self + 0x18);
        sVec4_F048 t;
        t.x = inst->min[0];
        t.y = inst->min[1];
        t.z = inst->min[2];
        t.w = 1.0f;
        nb.min = t;
        t.x = inst->max[0];
        t.y = inst->max[1];
        t.z = inst->max[2];
        nb.max = t;
        *info = nb;
        void* id = *(void**)((char*)self + 0x18);
        cSpaceHash_moveItem(World_GetNash(), 0, id, &nb, &old);
        func_0034EF08(self);
    } else {
        cMoveNode_v49(self);
    }
}

INCLUDE_ASM("object/floatingnode", Floating_BuildMatrices);

INCLUDE_ASM("object/floatingnode", Floating_v43);

INCLUDE_ASM("object/floatingnode", Floating_v42);

//100%
extern char* D_004A5B64_F930 __asm__("D_004A5B64");

struct sFloatSpring_F930 {
    float k;            // 0x2C
    float d;            // 0x30
    float c;            // 0x34
    float k2;           // 0x38
    float d2;           // 0x3C
    float c2;           // 0x40
    float force;        // 0x44
    float vel;          // 0x48
    float rest;         // 0x4C
    float pos;          // 0x50
    float ang0;         // 0x54
    float pad58;
    float vel0;         // 0x5C
    float force0;       // 0x60
    float ang1;         // 0x64
    float pad68;
    float vel1;         // 0x6C
    float force1;       // 0x70
};

struct sFloatNode_F930 {
    char pad0[0x12];
    unsigned short flags;       // 0x12
    char pad14[0x2C - 0x14];
    sFloatSpring_F930 s;        // 0x2C
};

extern "C" int func_0034F930(sFloatNode_F930* self)
{
    float dt = 1.0f / (float)*(int*)(D_004A5B64_F930 + 0x10);
    float a = -self->s.k * (self->s.pos - self->s.rest) + self->s.c * self->s.force + -self->s.d * self->s.vel;
    float a0 = -self->s.k2 * self->s.ang0 + self->s.c2 * self->s.force0 + -self->s.d2 * self->s.vel0;
    float a1 = -self->s.k2 * self->s.ang1 + self->s.c2 * self->s.force1 + -self->s.d2 * self->s.vel1;
    self->s.pos += self->s.vel * dt;
    self->s.vel += a * dt;
    self->s.ang0 += self->s.vel0 * dt;
    self->s.vel0 += a0 * dt;
    self->s.ang1 += self->s.vel1 * dt;
    self->s.vel1 += a1 * dt;
    sFloatSpring_F930* s = &self->s;
    float lo = -1.3962634801864624f;
    float hi = 1.3962634801864624f;
    // PORT: `<?` is the g++ minimum operator (EE min.s).
    self->s.ang0 = lo <= s->ang0 ? s->ang0 <? hi : lo;
    self->s.ang1 = lo <= s->ang1 ? s->ang1 <? hi : lo;
    self->s.force = 0.0f;
    self->s.force0 = 0.0f;
    self->s.force1 = 0.0f;
    self->flags |= 1;
    return 1;
}

//100%
struct sFloatingVEntryFA88 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void func_00356B30(void* self, void* stream);

extern "C" void func_0034FA88(cFloatingNode* self, void* stream)
{
    int has;
    func_00356B30(self, stream);
    has = self->field_0x78 != 0;
    sFloatingVEntryFA88* e = &(*(sFloatingVEntryFA88**)stream)[1];
    e->fn((char*)stream + e->delta, &has, 4);
    e = &(*(sFloatingVEntryFA88**)stream)[1];
    e->fn((char*)stream + e->delta, (char*)self + 0x2C, 0x48);
}

//100%
extern "C" void* func_00354850(void* self, void* a1, int type);
extern "C" void func_0034FC78(void* self, void* node);
extern "C" void World_AddFocusObject(void* node);
extern char D_00491C80[];

extern "C" void* func_0034FB00(void* self, void* a1, int type, void* node)
{
    func_00354850(self, a1, type);
    *(void**)((char*)self + 0x18) = node;
    *(void**)((char*)self + 0xC) = D_00491C80;
    func_0034FC78(self, node);
    if ((*(int*)((char*)node + 0x8) & 0x100) == 0) {
        if (type != 6 && type != 0x10 && type != 0x16) {
            World_AddFocusObject(node);
        }
    }
    return self;
}

