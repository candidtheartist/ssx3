#include "common.h"

//100%
// PORT: operator_new really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern const char D_00481730[];

// same body as func_0026E950 (setBlock), inlined here
static inline void cReplayFramePtr_setBlockInl(void* self, char* buf, int size)
{
    *(char**)((char*)self + 0x4) = buf;
    *(char**)((char*)self + 0x8) = buf + size;
    *(char**)((char*)self + 0xc) = buf;
    *(int*)((char*)self + 0x10) = size;
}

extern "C" void cReplayFramePtr_initBlock(void* self, unsigned int size)
{
    cReplayFramePtr_setBlockInl(self, (char*)operator_new_tag(size, D_00481730, 0, 0), 0);
}

//100%
extern "C" void func_0026E950(void* self, int a1, int a2)
{
    *(int*)((char*)self + 0x4) = a1;
    *(int*)((char*)self + 0x8) = a1 + a2;
    *(int*)((char*)self + 0xc) = a1;
    *(int*)((char*)self + 0x10) = a2;
}

//100%
void cMemMan_free(void* p);

extern "C" void func_0026E968(void* self)
{
    void* p = *(void**)((char*)self + 0x4);
    if (p != 0) {
        cMemMan_free(p);
    }
    cReplayFramePtr_setBlockInl(self, 0, 0);
}

struct cReplayFramePtr {
    char pad_0x00[0x4];
    int field_0x4;
    char pad_0x08[0x4];
    int field_0xC;
};

//100%
void cReplayFramePtr_readRewind(cReplayFramePtr* self)
{
    self->field_0xC = self->field_0x4;
}

//100%
int func_0026E9C0(void* self)
{
    int t0 = *(int*)((char*)self + 0x4);
    *(int*)((char*)self + 0x10) = 0;
    *(int*)((char*)self + 0x8) = t0;
    return t0;
}

//100%
extern "C" void func_003E6574(void* dst, void* src, int size);

extern "C" void func_0026E9D0(void* self, void* src, int n)
{
    func_003E6574(*(char**)((char*)self + 0x8), src, n);
    *(char**)((char*)self + 0x8) += n;
    *(int*)((char*)self + 0x10) += n;
}

//100%
extern "C" void func_003E6574(void* dst, void* src, int size);

extern "C" void func_0026EA20(void* self, void* dst, int n)
{
    func_003E6574(dst, *(char**)((char*)self + 0xC), n);
    *(char**)((char*)self + 0xC) += n;
}

//100%
class cStream26EA68 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void v01(void* buf, int size);
    virtual void v02(void* buf, int size);
};

// Peek the next frame header's id without consuming it.
extern "C" short func_0026EA68(cStream26EA68* self)
{
    struct {
        short id;
        short size;
    } hdr;
    int pos = *(int*)((char*)self + 0xC);
    self->v02(&hdr, 4);
    *(int*)((char*)self + 0xC) = pos;
    return hdr.id;
}

//100%
extern "C" int func_002C85A0(void* src, int a, int dst);

extern "C" int func_0026EAB8(cReplayFramePtr* self, char** pp, void* src)
{
    struct {
        int tag;
        int size;
    } hdr;
    func_003E6574(&hdr.tag, src, 4);
    func_003E6574(&hdr.size, *pp, 4);
    *pp += 4;
    int n = func_002C85A0(*pp, 0, self->field_0x4);
    *pp += hdr.size;
    *(int*)((char*)self + 0x8) = self->field_0x4 + n;
    cReplayFramePtr_readRewind(self);
    return 1;
}

//100%
extern char* D_004A28A8;

struct sRefSet_EB48 {
    char pad_0x0[0x1C];
    unsigned int* refs;     // 0x1C
};

struct sRefWorld_EB48 {
    char pad_0x0[0x8];
    sRefSet_EB48** sets;    // 0x8
};

extern sRefWorld_EB48** D_004A47B8;

extern "C" void* func_003512C0(void* table, unsigned int id);

class cStream_EB48 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void v01(void* buf, int size);
    virtual void v02(void* buf, int size);
};

static inline void* refToPtr_EB48(unsigned int p)
{
    return (void*)(p << 2);
}

static inline void* lookup_EB48(unsigned int id)
{
    sRefSet_EB48* set = (*D_004A47B8)->sets[id & 0xFF];
    if (set == 0) {
        return 0;
    }
    unsigned int p = set->refs[id >> 8] >> 8;
    if (p == 0) {
        return 0;
    }
    return refToPtr_EB48(p);
}

struct sRefH_EB48 {
    unsigned int id;
    sRefH_EB48() : id(0xFFFFFFFF) {}
};

extern "C" void* func_0026EB48(cStream_EB48* stream)
{
    void* r = 0;
    sRefH_EB48 h;
    stream->v02(&h, 4);
    if (~h.id != 0) {
        r = func_003512C0(*(void**)(*(char**)(D_004A28A8 + 0x84) + 0x88), h.id);
        if (r == 0) {
            void* t = lookup_EB48(h.id);
            r = t;
        }
    }
    return r;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct sRefSet_EC08 {
    char pad_0x0[0x1C];
    unsigned int* refs;     // 0x1C
};

struct sRefWorld_EC08 {
    char pad_0x0[0x8];
    sRefSet_EC08** sets;    // 0x8
};

// asm-label view: func_0026EB48 declares D_004A47B8 with its own struct type in this unit
extern sRefWorld_EC08** D_004A47B8_EC08 __asm__("D_004A47B8");

class cStream_EC08 {
public:
    // vptr at 0x0; slot N at vtable offset N*8
    virtual void v01(void* buf, int size);
    virtual void v02(void* buf, int size);
};

struct sRec_EC08 {
    unsigned int id;
    unsigned short type;
    sRec_EC08() : id(0xFFFFFFFF) {}
};

struct sNode_EC08 {
    char pad_0x0[0x8];
    unsigned int flags;     // 0x8
    void* owner;            // 0xC
};

static inline void* refToPtr_EC08(unsigned int p)
{
    return (void*)(p << 2);
}

static inline void* lookup_EC08(unsigned int id)
{
    sRefSet_EC08* set = (*D_004A47B8_EC08)->sets[id & 0xFF];
    if (set == 0) {
        return 0;
    }
    unsigned int p = set->refs[id >> 8] >> 8;
    if (p == 0) {
        return 0;
    }
    return refToPtr_EC08(p);
}

extern "C" void* func_0026EC08(cStream_EC08* stream, void* owner)
{
    sNode_EC08* r = 0;
    sRec_EC08 rec;
    stream->v02(&rec, 8);
    if (~rec.id != 0) {
        void* t = lookup_EC08(rec.id);
        r = (sNode_EC08*)t;
        r->owner = owner;
        r->flags = (r->flags & 0xFFFF0300) | (rec.type & 0xFCFF);
    }
    return r;
}

//100%
struct sFpSerVEntry {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

struct sFpSerObj {
    sFpSerVEntry* vt;
};

extern "C" void func_0026ECD8(sFpSerObj* out, void* obj)
{
    unsigned int id = 0xFFFFFFFF;
    if (obj != 0) {
        id = *(unsigned int*)((char*)obj + 0x78);
    }
    out->vt[1].fn((char*)out + out->vt[1].delta, &id, 4);
}

//100%
extern "C" void func_0026ED28(sFpSerObj* out, void* obj)
{
    struct {
        unsigned int id;
        unsigned short type;
    } rec;
    rec.id = 0xFFFFFFFF;
    void* p = *(void**)((char*)obj + 0x18);
    if (p != 0) {
        rec.id = *(unsigned int*)((char*)p + 0x78);
        rec.type = *(unsigned short*)((char*)p + 0x8);
    } else {
        rec.type = 0;
    }
    out->vt[1].fn((char*)out + out->vt[1].delta, &rec, 8);
}

//100%
void func_0026ED88(void* self)
{
}

//100%
void cReplayFramePtr_getFrameBlock()
{
}

//100%
extern "C" void func_0026EDD8(void* self);

extern "C" void func_0026ED98(void* self)
{
    *(int*)((char*)self + 0x630) = (*(int*)((char*)self + 0x630) + 1) % 9;
    func_0026EDD8(self);
}

//100%
extern char* D_004A28A8;
extern int D_00445438[];
extern "C" void func_00161FA0(void* self, int mode);

struct sRiderList_EDD8 {
    int count;
    char* riders[1];
};

extern "C" void func_0026EDD8(void* self)
{
    sRiderList_EDD8* list = *(sRiderList_EDD8**)(*(char**)(D_004A28A8 + 0x84) + 0x84);
    int n = list->count;
    int i;
    for (i = 0; i < n; i++) {
        func_00161FA0(*(void**)(list->riders[i] + 0xA8), D_00445438[*(int*)((char*)self + 0x630)]);
    }
}

//100%
void* func_0016D1D8(void* p);
extern void* D_004C5830[];
extern "C" void func_0026EDD8(void* self);

extern "C" void func_0026EE68(void* self)
{
    func_0016D1D8(D_004C5830);
    func_0026EDD8(self);
}

//100%
extern char* D_004A28A8;
extern void* D_004C5830[];
void cCameraTriggerMan_setInGameTriggers(void* self);
extern "C" void func_0015DFD8(void* self, int mode);
extern "C" void func_00161F50(void* cam);

struct sRiderList_EEA0 {
    int count;
    char* riders[1];
};

extern "C" void func_0026EEA0(void* self)
{
    cCameraTriggerMan_setInGameTriggers(D_004C5830);
    sRiderList_EEA0* list = *(sRiderList_EEA0**)(*(char**)(D_004A28A8 + 0x84) + 0x84);
    int n = list->count;
    int i;
    for (i = 0; i < n; i++) {
        char* r = list->riders[i];
        void* cam = *(void**)(r + 0xA8);
        func_0015DFD8(r, 2);
        func_00161F50(cam);
    }
    *(int*)((char*)self + 0x630) = 0;
}

//100%
extern "C" void func_0026EF30(void* self)
{
    func_0016D1D8(D_004C5830);
    *(int*)((char*)self + 0x634) = (*(int*)((char*)self + 0x634) + 1) % 9;
}

//100%
extern char* D_004A28A8;
extern void* D_004C5830[];
void cCameraTriggerMan_setInGameTriggers(void* self);
extern "C" void func_0015DFD8(void* self, int mode);

extern "C" void func_0026EF80()
{
    cCameraTriggerMan_setInGameTriggers(D_004C5830);
    func_0015DFD8(*(void**)(*(char**)(*(char**)(D_004A28A8 + 0x84) + 0x84) + 0x4), 2);
}

//100%
extern "C" void* func_0026D5E8(void* self);
void* func_0026E5A8(void* self);
extern "C" void* func_00272288(void* self);
void func_0026F4A0(void* self, int state);

extern "C" void* Replay_ctor(void* self)
{
    char* p = (char*)self + 0x2C;
    for (int i = 15; i != -1; i--, p += 0x38) {
        func_0026D5E8(p);
    }
    char* q = (char*)self + 0x494;
    func_0026E5A8((char*)self + 0x3B0);
    func_0026E5A8((char*)self + 0x3BC);
    for (int i = 1; i != -1; i--, q += 0xB4) {
        func_00272288(q);
    }
    func_0026F4A0(self, 15);
    for (int i = 1; i >= 0; i--) {
        int* a = (int*)(0x48C + (char*)self);
        a[i] = 0;
    }
    return self;
}

//100%
struct sFpOwner26F428;
struct cReplayFramePtr_F980;
extern "C" void func_0026F428(sFpOwner26F428* self);
extern "C" void func_0026F980(cReplayFramePtr_F980* self);
void func_0026F498(void* self);
void operator_delete(int* ptr);

struct sFpVEntryF088 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sFpNodeF088 {
    sFpVEntryF088* vtable;  // 0x0
    char pad_0x4[0x34];
};

struct sFpKeyF088 {
    char pad_0x0[0xB4];
    ~sFpKeyF088() {}
};

extern "C" void func_0026F088(int* self, int flags)
{
    char* s = (char*)self;
    int ok = 0;
    int v = *self;
    if (v != 0) {
        ok = v;
        ok = ok < 10;
    }
    if (ok) {
        func_0026F980((cReplayFramePtr_F980*)self);
    }
    func_0026F498(self);
    func_0026F428((sFpOwner26F428*)self);
    if (s + 0x494 != 0) {
        char* p = s + 0x494 + 0x168;
        while (s + 0x494 != p) {
            p -= 0xB4;
            ((sFpKeyF088*)p)->~sFpKeyF088();
        }
    }
    if (s + 0x2C != 0) {
        char* p = s + 0x2C + 0x380;
        while (s + 0x2C != p) {
            p -= 0x38;
            sFpVEntryF088* vt = ((sFpNodeF088*)p)->vtable;
            vt[7].fn(p + vt[7].delta, 0);
        }
    }
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
struct sReplayBlock_F180 {
    char data[0x38];
};

struct cReplayFramePtr_F180 {
    char pad_0x0[0x8];
    int numBlocks;          // 0x8
    char pad_0xc[0x8];
    int blockSize;          // 0x14
    int field_0x18;         // 0x18
    char pad_0x1c[0x10];
    sReplayBlock_F180 blocks[1];    // 0x2C
};

extern "C" void cReplayFramePtr_initBlock(void* self, unsigned int size);
extern "C" void func_0026F228(void* self);
void func_0026F4A0(void* self, int state);

extern "C" void func_0026F180(cReplayFramePtr_F180* self)
{
    self->blockSize = 0x14000;
    self->numBlocks = 0xC9800 / self->blockSize;
    self->field_0x18 = 0;
    int i = 0;
    do {
        cReplayFramePtr_initBlock(&self->blocks[i], self->blockSize);
        i++;
    } while (i < self->numBlocks);
    func_0026F4A0(self, 10);
    func_0026F228(self);
}

//100%
void func_0026D168(void* self);
void func_0026E5C0(void* self);
extern "C" void func_0026E5D0(void* list, void* block);
extern "C" void func_003E6448(void* dst, int c, int n);

struct sFpSlot_F228 {
    int id;
    char data[0xAC];
    int fB0;
};

extern "C" void func_0026F228(void* self)
{
    char* s = (char*)self;
    unsigned int st = *(int*)s - 14;
    bool b = !(st < 2);
    if (!b) return;
    func_0026F498(self);
    int i = 0;
    char* l0 = s + 0x3B0;
    char* l1 = s + 0x3BC;
    int none = -1;
    *(int*)(s + 0x4) = 15;
    func_0026F4A0(self, 10);
    *(int*)(s + 0x60C) = 0;
    *(int*)(s + 0x610) = 0;
    *(int*)(s + 0x614) = 0;
    *(int*)(s + 0x628) = 0;
    *(int*)(s + 0x62C) = 0;
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x608) = 0;
    *(int*)(s + 0x484) = 0;
    *(int*)(s + 0x3C8) = 0;
    *(int*)(s + 0x3CC) = 0;
    *(int*)(s + 0x488) = 0;
    *(int*)(s + 0x3D4) = 0;
    *(int*)(s + 0x3AC) = 0;
    *(int*)(s + 0x3D0) = 0;
    *(int*)(s + 0x1C) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x618) = 0;
    *(int*)(s + 0x61C) = 0;
    *(int*)(s + 0x620) = 0;
    *(int*)(s + 0x624) = 0;
    *(int*)(s + 0x63C) = 0;
    *(int*)(s + 0x650) = 0;
    *(int*)(s + 0x640) = 0;
    *(int*)(s + 0x644) = 0;
    *(int*)(s + 0x648) = 0;
    *(int*)(s + 0x638) = 0;
    *(int*)(s + 0x64C) = 0;
    *(int*)(s + 0x654) = 0;
    *(int*)(s + 0x658) = 0;
    *(int*)(s + 0x65C) = 0;
    *(int*)(s + 0x660) = 0;
    *(int*)(s + 0x664) = 0;
    *(int*)(s + 0x66C) = 0;
    *(int*)(s + 0x674) = 0;
    *(int*)(s + 0x678) = 0;
    *(int*)(s + 0x67C) = 0;
    *(int*)(s + 0x668) = 0;
    sFpSlot_F228* e = (sFpSlot_F228*)(s + 0x494);
    char* d = s + 0x498;
    void** pp = (void**)(s + 0x48C);
    do {
        if (*pp) func_0026D168(*pp);
        e->fB0 = 0;
        e->id = none;
        func_003E6448(d, 0, 0xAC);
        d += 0xB4;
        pp++;
        e->id = i;
        i++;
        e++;
    } while (i < 2);
    func_0026E5C0(l0);
    func_0026E5C0(l1);
    for (i = 0; i < *(int*)(s + 8); i++) {
        func_0026E5D0(l1, s + 0x2C + i * 0x38);
    }
    int three = 3;
    *(int*)(s + 0x630) = 0;
    *(int*)(s + 0x634) = 0;
    if (*(int*)(*(char**)(*(char**)(D_004A28A8 + 0x84) + 0xC) + 0x7C) == 1) {
        *(int*)(s + 0xC) = three;
        *(int*)(s + 0x10) = three;
    } else {
        *(int*)(s + 0xC) = 1;
        *(int*)(s + 0x10) = 0;
    }
}

//100%
void func_0026E5C0(void* self);

struct sFpEntry26F428 {
    char pad[0x38];
};

struct sFpOwner26F428 {
    char pad_0x00[0x8];
    int count;
    char pad_0x0C[0x20];
    sFpEntry26F428 entries[1];
};

extern "C" void func_0026F428(sFpOwner26F428* self)
{
    int i;
    for (i = 0; i < self->count; i++) {
        func_0026E968(&self->entries[i]);
    }
    func_0026E5C0((char*)self + 0x3B0);
    func_0026E5C0((char*)self + 0x3BC);
}

//100%
void func_0026F498(void* self)
{
}

//100%
void func_0026F4A0(void* self, int val)
{
    *(int*)((char*)self + 0x0) = val;
}

//100%
void func_0026F4A0(void* self, int state);
int func_00320C48(void* pad, int button);
extern char* D_004A28A8;
extern "C" void func_0026FB88(void* self, int a1);
extern "C" void func_0026FE50(char* self);
extern "C" void func_00270538(void* self);
extern "C" void func_00270628(void* self);
extern "C" void func_00270670(void* self);
extern "C" void func_00270E18(void* self);
extern "C" void func_0026F8A0(struct cReplayFramePtr_F8A0* self, void* a1, int a2, int a3);

struct sFrameDesc_F4A8 {
    short type;
    char a;
    char b;
};

extern "C" void* func_0026D760_F4A8(void* self, sFrameDesc_F4A8* desc) __asm__("func_0026D760");
// PORT: func_0026D740 is mangled with one parameter (__FPv) but is called with (self, block).
void func_0026D740_F4A8(void* self, void* block) __asm__("func_0026D740__FPv");

struct cReplayFramePtr_F4A8 {
    int state;          // 0x0
    char pad4[0x18 - 0x4];
    int keyEvery;       // 0x18
    char pad1C[0x20 - 0x1C];
    int f20;            // 0x20
    char pad24[0x28 - 0x24];
    int pad;            // 0x28
    char pad2C[0x3C8 - 0x2C];
    int frame;          // 0x3C8
    int count;          // 0x3CC
    void* block;        // 0x3D0
    void* f3D4;         // 0x3D4
    char pad3D8[0x484 - 0x3D8];
    int last;           // 0x484
    char pad488[0x604 - 0x488];
    int f604;           // 0x604
    int f608;           // 0x608
    int f60C;           // 0x60C
    int f610;           // 0x610
    int f614;           // 0x614
    int f618;           // 0x618
    int f61C;           // 0x61C
    int f620;           // 0x620
    int f624;           // 0x624
};

static inline void AddBlock_F4A8(cReplayFramePtr_F4A8* self, int type)
{
    sFrameDesc_F4A8 desc;
    desc.type = type;
    desc.a = 0;
    desc.b = 0;
    func_0026D740_F4A8(self, func_0026D760_F4A8(self, &desc));
}

extern "C" void func_0026F4A8(cReplayFramePtr_F4A8* self)
{
    int ok = !(self->state == 14 || self->state == 15);
    if (!ok)
        return;
    if (self->f614 > 0)
        self->f614--;
    self->f604 = 0;
    if (self->f618 == 7)
        func_0026F4A0(self, 3);
    if (!(self->state == 3 || self->state == 4))
        self->f20 = 0;
    switch (self->state) {
    case 11:
        func_0026F4A0(self, 12);
        break;
    case 2:
        if (self->last < self->frame - 1) {
            func_0026FB88(self, 0);
            func_0026FE50((char*)self);
            break;
        }
        func_00270670(self);
    case 0:
    case 12:
        func_0026F4A0(self, 0);
        self->block = 0;
        if (self->f60C != 0) {
            if (self->f608 == 0) {
                func_00270628(self);
                func_00270E18(self);
                func_00270538(self);
                AddBlock_F4A8(self, 1);
                func_0026F4A0(self, 13);
            }
        } else if (self->f624 != 0) {
            func_0026F8A0((cReplayFramePtr_F8A0*)self, self->f3D4, 1, 0);
            func_0026F4A0(self, 2);
            self->f624 = 0;
            self->f620 = 1;
        } else {
            if (self->f610 == 0) {
                if (self->frame % 60 == 0) {
                    func_00270538(self);
                    if (self->frame == 0 || (self->keyEvery != 0 && self->frame % self->keyEvery == 0))
                        AddBlock_F4A8(self, 1);
                    else
                        AddBlock_F4A8(self, 0);
                }
                if (self->f610 == 0)
                    self->count++;
            }
            self->frame++;
        }
        break;
    case 3: {
        void* p = *(void**)((self->pad << 2) + D_004A28A8 + 0xB0);
        if (p != 0 && func_00320C48(p, 0x6B))
            func_0026FB88(self, 0);
        func_0026FE50((char*)self);
        break;
    }
    case 9:
        func_0026F8A0((cReplayFramePtr_F8A0*)self, 0, 0, 1);
        func_0026F4A0(self, 1);
        self->f61C = 1;
        break;
    case 8:
        func_0026F8A0((cReplayFramePtr_F8A0*)self, 0, 0, 0);
    case 4:
    case 5:
    case 6:
    case 7:
        func_0026F4A0(self, 3);
        break;
    case 10:
    case 13:
        break;
    default:
        func_0026FE50((char*)self);
        break;
    }
}


//100%
void func_0026F4A0(void* self, int state);

extern "C" void func_0026F7B8(int* self)
{
    int s = *self;
    bool ok = !(s == 14 || s == 15);
    if (ok) {
        if (s == 10) {
            func_0026F4A0(self, 11);
        }
    }
}

//100%
struct sFrameDesc26F7F8 {
    short type;
    char a;
    char b;
};

extern "C" void* func_0026D760(void* self, sFrameDesc26F7F8* desc);
// PORT: func_0026D740 is mangled with one parameter (__FPv) but is called here
// with (self, block); bind the 2-arg form to the symbol.
void func_0026D740_2(void* self, void* block) __asm__("func_0026D740__FPv");

extern "C" void func_0026F7F8(void* self)
{
    if (*(void**)((char*)self + 0x3D0) == 0) {
        sFrameDesc26F7F8 desc;
        desc.type = 1;
        desc.a = 0;
        desc.b = 0;
        void* block = func_0026D760(self, &desc);
        *(void**)((char*)self + 0x3D0) = block;
        func_0026D740_2(self, block);
    }
}

//100%
extern "C" void func_0026DB88(void* self, void* p);
extern "C" void func_00270238(void* self, void* p);

extern "C" void func_0026F850(void* self)
{
    void* p = *(void**)((char*)self + 0x3D0);
    if (p != 0) {
        func_0026DB88(self, p);
        func_00270238(self, *(void**)((char*)self + 0x3D0));
        *(void**)((char*)self + 0x3D0) = 0;
    }
}

//100%
void func_0026F898(void* self, int val)
{
    *(int*)((char*)self + 0x28) = val;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_0026EE68(void* self);
extern "C" void func_0026EF30(void* self);
extern "C" void func_0026F7F8(void* self);
void func_0026F4A0(void* self, int state);
extern "C" void func_002702F8(void* self, void* a1);
extern "C" void func_002703F0(void* self, int a1);
extern "C" void* func_0028B180();
extern "C" void cSSXAudio_onReplayMenuOpen(void* self);

struct cReplayFramePtr_F8A0 {
    int state;              // 0x0
    char pad_0x4[0x604];
    int field_0x608;        // 0x608
    char pad_0x60c[0xC];
    int field_0x618;        // 0x618
    int field_0x61c;        // 0x61C
    int field_0x620;        // 0x620
};

extern "C" void func_0026F8A0(cReplayFramePtr_F8A0* self, void* a1, int a2, int a3)
{
    int ok = !(self->state == 14 || self->state == 15);
    if (ok) {
        if (self->field_0x608 == 0) {
            func_0026F7F8(self);
        }
        func_0026F4A0(self, 7);
        self->field_0x618 = 0;
        self->field_0x61c = 0;
        self->field_0x620 = a2;
        func_002702F8(self, a1);
        func_002703F0(self, 1);
        if (a2) {
            func_0026EF30(self);
        } else {
            func_0026EE68(self);
        }
        if (a2 == 0 && a3 == 0) {
            cSSXAudio_onReplayMenuOpen(func_0028B180());
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_0026EEA0(void* self);
extern "C" void func_0026EF80(void* self);
void func_0026F4A0(void* self, int state);
extern "C" void func_0026F850(void* self);
extern "C" void func_00270628(void* self);
extern "C" void* func_0028B180();
extern "C" void cSSXAudio_onReplayMenuClose(void* self);

struct cReplayFramePtr_F980 {
    int state;              // 0x0
    char pad_0x4[0x604];
    int field_0x608;        // 0x608
    int field_0x60c;        // 0x60C
    char pad_0x610[0xC];
    int field_0x61c;        // 0x61C
    int field_0x620;        // 0x620
    int field_0x624;        // 0x624
};

extern "C" void func_0026F980(cReplayFramePtr_F980* self)
{
    int ok = !(self->state == 14 || self->state == 15);
    if (ok) {
        func_00270628(self);
        if (self->field_0x61c == 0 && self->field_0x620 == 0) {
            cSSXAudio_onReplayMenuClose(func_0028B180());
        }
        self->field_0x61c = 0;
        self->field_0x620 = 0;
        self->field_0x624 = 0;
        if (self->field_0x608 == 0) {
            func_0026F850(self);
            if (self->field_0x620) {
                func_0026EF80(self);
            } else {
                func_0026EEA0(self);
            }
            if (self->field_0x60c) {
                func_0026F4A0(self, 13);
            } else {
                func_0026F4A0(self, 0);
            }
        }
    }
}

//100%
extern "C" void func_0026FA50(void* self)
{
    int s = *(int*)((char*)self + 0x0);
    bool ok = !(s == 0xE || s == 0xF);
    if (ok) {
        *(int*)((char*)self + 0x60C) = 1;
    }
}

//100%
extern char* D_004A28A8;
extern int D_00445438[];
int func_00320C48(void* pad, int button);
// PORT: func_00320BF0 returns the input axis value as a float ($f0).
extern "C" float func_00320BF0(void* pad, int axis);
extern "C" void cGameViewMan_updateAll(void* list);

static inline bool isStateFA78(int* self, int s)
{
    return *self == s;
}

extern "C" void func_0026FA78(int* self)
{
    if (!isStateFA78(self, 3)) {
        return;
    }
    void* pad = *(void**)(D_004A28A8 + (self[0x28 / 4] << 2) + 0xB0);
    if (func_00320C48(pad, 0x6C) != 0) {
        cGameViewMan_updateAll(*(void**)(*(char**)(D_004A28A8 + 0x84) + 0x84));
    }
    if (D_00445438[self[0x630 / 4]] != 0xB) {
        return;
    }
    if (func_00320BF0(pad, 0x31) != 0.0f || func_00320BF0(pad, 0x30) != 0.0f ||
        func_00320BF0(pad, 0x32) != 0.0f || func_00320BF0(pad, 0x33) != 0.0f) {
        cGameViewMan_updateAll(*(void**)(*(char**)(D_004A28A8 + 0x84) + 0x84));
    }
}

//100%
extern char D_004A5A58;
extern "C" void func_002305C8(void* self);

struct sFpViewVEntry_FB88 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sFpView_FB88 {
    sFpViewVEntry_FB88* vt;
};

static inline bool isStateFB88(char* s, int st)
{
    return *(int*)s == st;
}

static inline bool isActiveFB88(char* s)
{
    int st = *(int*)s;
    return st != 0 && st < 10;
}

static inline bool isIdleFB88(char* s)
{
    bool r = false;
    if (isActiveFB88(s)) r = *(int*)(s + 0x484) == *(int*)(s + 0x3CC);
    return r;
}

static inline bool isIdleNoCamFB88(char* s)
{
    bool r = false;
    if (isActiveFB88(s)) r = *(int*)(s + 0x484) == 0;
    return r;
}

// PORT: returns whether a menu action was queued; the unit declares it
// void earlier, so the definition goes through an asm label.
extern "C" int func_0026FB88_impl(void* self, int a1) __asm__("func_0026FB88");
extern "C" int func_0026FB88_impl(void* self, int a1)
{
    char* s = (char*)self;
    char* g = D_004A28A8;
    sFpView_FB88* v = (sFpView_FB88*)&D_004A5A58;
    sFpView_FB88* cur = *(sFpView_FB88**)(*(char**)(*(char**)(g + 0x84) + 0x48) + 0x14);
    if (cur != 0) v = cur;
    if (*(int*)(s + 0x618) != 0) return 0;
    int r = 0;
    void* pad = *(void**)(g + (*(int*)(s + 0x28) << 2) + 0xB0);
    if (*(int*)(s + 0x61C) == 0 && *(int*)(s + 0x620) == 0) {
        if (func_00320C48(pad, 0x6A)) {
            *(int*)(s + 0x1C) = 10;
            *(int*)(s + 0x20) = 0;
            if (!isStateFB88(s, 3)) r = 7;
            else r = isIdleFB88(s) ? 0 : 5;
        } else if (func_00320C48(pad, 0x6B)) {
            if (*(int*)(s + 0x1C) > 0) *(int*)(s + 0x1C) -= 1;
            *(int*)(s + 0x20) ^= 1;
            if (*(int*)(s + 0x1C) <= 0 && *(int*)(s + 0x20) == 0) {
                if (!isStateFB88(s, 3)) r = 7;
                else r = isIdleFB88(s) ? 0 : 5;
            }
        } else if (func_00320C48(pad, 0x67)) {
            if (!isStateFB88(s, 3)) r = 7;
            else r = isIdleFB88(s) ? 0 : 6;
        } else if (func_00320C48(pad, 0x66)) {
            if (a1) {
                func_002305C8(*(void**)(D_004A28A8 + 0x84));
                *(int*)(s + 0x618) = 8;
            } else if (!isStateFB88(s, 3)) {
                *(int*)(s + 0x618) = 7;
            }
            return 0;
        } else if (func_00320C48(pad, 0x68)) {
            if (!isStateFB88(s, 3)) r = 7;
            else if (!isIdleFB88(s)) {
                v->vt[2].fn((char*)v + v->vt[2].delta, 2);
                r = 4;
            } else {
                v->vt[2].fn((char*)v + v->vt[2].delta, 4);
            }
        } else if (func_00320C48(pad, 0x69)) {
            if (isStateFB88(s, 3)) {
                if (!isIdleNoCamFB88(s)) {
                    v->vt[2].fn((char*)v + v->vt[2].delta, 2);
                    r = 3;
                } else {
                    v->vt[2].fn((char*)v + v->vt[2].delta, 4);
                }
            } else {
                r = 7;
            }
        } else if (func_00320C48(pad, 0x6C)) {
            v->vt[2].fn((char*)v + v->vt[2].delta, 2);
            func_0026ED98(self);
        }
    }
    *(int*)(s + 0x618) = r;
    return r != 0;
}

//100%
extern char* D_004A28A8;
void func_0026F4A0(void* self, int state);
extern "C" void func_002702F8(void* self, void* a1);
extern "C" void func_002703F0(void* self, int a1);
extern "C" void func_00270378(void* self);
void* func_0026E448_FE50(void* self, int idx) __asm__("func_0026E448__FPv");
extern "C" void func_0026E528(void* self);
extern "C" void func_0026E568(void* self);
extern "C" void func_001620D0(void* self);
extern "C" void cGameViewMan_updateAll(void* list);

struct sVE_FE50 {
    short delta;
    short index;
    void (*fn)(void*);
};

extern "C" void func_0026FE50(char* self)
{
    int changed = 0;
    switch (*(int*)(self + 0x618)) {
    case 1:
        func_002702F8(self, 0);
        changed = 1;
        func_002703F0(self, 1);
        if (*(int*)(self + 0x484) == 0) {
            func_0026F4A0(self, 6);
        } else {
            func_0026F4A0(self, 5);
        }
        break;
    case 2:
        func_00270378(self);
        changed = 1;
        func_002703F0(self, 1);
        if (*(int*)(self + 0x484) == 0) {
            func_0026F4A0(self, 6);
        } else {
            func_0026F4A0(self, 5);
        }
        break;
    case 3: {
        changed = 1;
        char* p = (char*)func_0026E448_FE50(self, *(int*)(self + 0x484));
        *(char**)(self + 0x488) = p;
        if (*(int*)(self + 0x484) == *(int*)(p + 0x30)) {
            func_0026E568(self);
        } else {
            char* q = *(char**)(p + 0x14);
            if (q != 0 && *(int*)(q + 0x30) == *(int*)(self + 0x484)) {
                func_0026E568(self);
            }
        }
        func_002703F0(self, 1);
        if (*(int*)(self + 0x484) == 0) {
            func_0026F4A0(self, 6);
        } else {
            func_0026F4A0(self, 5);
        }
        break;
    }
    case 4:
        changed = 1;
        if (*(int*)(*(char**)(self + 0x488) + 0x14) != 0) {
            func_0026E528(self);
            func_002703F0(self, 1);
            func_0026F4A0(self, 5);
        }
        break;
    case 5:
        func_002703F0(self, 0);
        func_0026F4A0(self, 4);
        break;
    case 6:
        if (*(int*)self == 3) {
            func_0026F4A0(self, 1);
        } else {
            func_0026F4A0(self, 3);
        }
        break;
    case 7:
        func_0026F4A0(self, 3);
        break;
    case 8:
        break;
    default:
        if (*(int*)self != 3) {
            *(int*)(self + 0x604) = 1;
            func_002703F0(self, 0);
        }
        break;
    }
    *(int*)(self + 0x618) = 0;
    if (changed) {
        char* gm = *(char**)(*(char**)(D_004A28A8 + 0x84) + 0x84);
        char* v = *(char**)(*(char**)(gm + 4) + 0xA8);
        func_001620D0(v);
        sVE_FE50* vt = *(sVE_FE50**)(v + 0x14);
        vt[4].fn(v + vt[4].delta);
        cGameViewMan_updateAll(gm);
    }
}

