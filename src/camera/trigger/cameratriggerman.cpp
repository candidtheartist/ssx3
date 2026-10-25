#include "common.h"

//100%
struct cActiveTriggerList;
struct cCameraTriggerList;
struct cCameraTriggerStack;
void cCameraTriggerStack_init(cCameraTriggerStack* self);
void cActiveTriggerList_purge(cActiveTriggerList* self);
void cCameraTriggerList_init(cCameraTriggerList* self);
extern "C" void cCameraTriggerMan_purge(void* self);
extern "C" void cCamera_resetChaseControllerSwitches();

extern "C" void cCameraTriggerMan_cleanupOnExit(void* self)
{
    cActiveTriggerList_purge((cActiveTriggerList*)((char*)self + 0x14));
    cActiveTriggerList_purge((cActiveTriggerList*)((char*)self + 0x18));
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)self + 0x1C));
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)self + 0x3C));
    cCameraTriggerMan_purge(self);
    cCameraTriggerList_init((cCameraTriggerList*)self);
    cCamera_resetChaseControllerSwitches();
}

extern "C" void func_0016CA08()
{
}

//100%
void func_0016CA10(void* self)
{
}

void operator_delete(int*);
extern void* D_004A28A8;

struct sCtVec4_CF48 {
    float x, y, z, w;
} __attribute__((aligned(16)));
struct sCtBox_CF48 {
    sCtVec4_CF48 min;
    sCtVec4_CF48 max;
};
struct sCtCell_CF48 {
    int level;
    int x, y, z;
};
struct sCtNode_CF48 {
    sCtNode_CF48* child[2][2][2];   // 0x00
    void* lists[3];                 // 0x20
    int empty()
    {
        if (child[0][0][0] || child[0][0][1] || child[0][1][0] || child[0][1][1] || child[1][0][0] ||
            child[1][0][1] || child[1][1][0] || child[1][1][1]) {
            return 0;
        }
        for (int i = 0; i < 3; i++) {
            if (lists[i]) return 0;
        }
        return 1;
    }
};
struct sCtRoot_CF48 {
    sCtCell_CF48 cell;              // 0x00
    sCtNode_CF48* node;             // 0x10
};

extern "C" void func_00328F28(void* out, const void* box);
extern "C" void func_003284B8(void* node, int idx, void* item, const void* target, const void* cur);
extern "C" void func_00328C20(void* root, int idx, void* item, const void* target);

class cCtShape_CF48 {
public:
    char pad[0x24];
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual sCtBox_CF48 bounds();
};

struct sCtTrig_CF48 {
    int f0;
    unsigned int mask;              // 0x4
    cCtShape_CF48* shape;           // 0x8
    char padC[0x8];
    char item[0xC];                 // 0x14
    sCtTrig_CF48* reg;              // 0x20
};

struct sCtMan_CF48 {
    sCtTrig_CF48** trigs;           // 0x0
    int count;                      // 0x4
};

static inline sCtRoot_CF48* findRoot_CF48(char* w, int x, int y, int z)
{
    sCtRoot_CF48* r = (sCtRoot_CF48*)w;
    sCtRoot_CF48* rx = x >= 0 ? r : r + 4;
    sCtRoot_CF48* ry = y >= 0 ? rx : rx + 2;
    sCtRoot_CF48* rz = z >= 0 ? ry : ry + 1;
    return rz;
}

static inline void remove_CF48(char* w, void* item, const sCtBox_CF48* box)
{
    (*(int*)(w + 0xA0))++;
    sCtCell_CF48 c;
    func_00328F28(&c, box);
    sCtRoot_CF48* r = findRoot_CF48(w, c.x, c.y, c.z);
    func_003284B8(r->node, 2, item, &c, &r->cell);
    if (r->node->empty()) {
        operator_delete((int*)r->node);
        r->node = 0;
    }
}

static inline void insert_CF48(char* w, void* item, const sCtBox_CF48* box)
{
    sCtCell_CF48 c;
    func_00328F28(&c, box);
    func_00328C20(findRoot_CF48(w, c.x, c.y, c.z), 2, item, &c);
}

//100%
// Unregisters every trigger from the world hash, then resets the stacks and the trigger list.
extern "C" void func_0016BF40(void* self);
void cCameraTriggerStack_init(cCameraTriggerStack* self);

extern "C" void cCameraTriggerMan_RemoveTriggerRegions(void* vself)
{
    sCtMan_CF48* self = (sCtMan_CF48*)vself;
    for (int i = 0; i < self->count; i++) {
        sCtTrig_CF48* t = self->trigs[i];
        char* w = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x20);
        sCtBox_CF48 box = t->shape->bounds();
        remove_CF48(w, t->item, &box);
    }
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)vself + 0x1C));
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)vself + 0x3C));
    func_0016BF40(vself);
    cCamera_resetChaseControllerSwitches();
}

//100%
// Unregisters every trigger from the world hash, then resets the stacks and active lists.
void cActiveTriggerList_purge(cActiveTriggerList* self);
void cCameraTriggerStack_init(cCameraTriggerStack* self);
extern "C" void func_0016C098(void* self);

extern "C" void cCameraTriggerMan_purge(void* vself)
{
    sCtMan_CF48* self = (sCtMan_CF48*)vself;
    for (int i = 0; i < self->count; i++) {
        sCtTrig_CF48* t = self->trigs[i];
        if (t->reg != 0) {
            char* w = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x20);
            sCtBox_CF48 box = t->shape->bounds();
            remove_CF48(w, t->item, &box);
        }
    }
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)vself + 0x1C));
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)vself + 0x3C));
    func_0016C098(vself);
    cActiveTriggerList_purge((cActiveTriggerList*)((char*)vself + 0x14));
    cActiveTriggerList_purge((cActiveTriggerList*)((char*)vself + 0x18));
    cCamera_resetChaseControllerSwitches();
}

//100%
struct sCamTrigMan {
    char** triggers; // 0x0
    int count;       // 0x4
};

extern "C" int cCameraTriggerList_loadFromFile(void* self, const char* file);

extern "C" int cCameraTriggerMan_loadTriggers(sCamTrigMan* self, const char* file)
{
    int err = cCameraTriggerList_loadFromFile(self, file);
    if (err != 0)
        return err;
    for (int i = 0; i < self->count; i++)
        *(int*)(self->triggers[i] + 0x20) = 0;
    return 0;
}

//100%
struct sCamTrigManB {
    char** triggers; // 0x0
    int count;       // 0x4
};

extern "C" int cCameraTriggerList_loadFromBuffer(void* self, void* buf);
void cCameraTriggerMan_setInGameTriggers(void* self);

extern "C" void cCameraTriggerMan_streamIn(void* self, void* stream)
{
    cCameraTriggerMan_cleanupOnExit(self);
    cCameraTriggerList_loadFromBuffer(self, stream);
    sCamTrigManB* m = (sCamTrigManB*)self;
    for (int i = 0; i < m->count; i++)
        *(int*)(m->triggers[i] + 0x20) = 0;
    cCameraTriggerMan_setInGameTriggers(self);
}

extern void* D_004C5830[];
extern "C" void* cCameraTriggerMan_streamInIf(void*, void*, int);

//100%
// Forwards to cCameraTriggerMan_RemoveTriggerRegions.
extern "C" void cCameraTriggerMan_RemoveTriggerRegions(void* self);

extern "C" void func_0016CEA8(void* self)
{
    cCameraTriggerMan_RemoveTriggerRegions(self);
}

//80.0%
//100%
// PORT: the unit declares cCameraTriggerMan_streamInIf as returning void*; this caller treats it as void.
void cCameraTriggerMan_streamInIf_CEC8(void*, void*, int) __asm__("cCameraTriggerMan_streamInIf");
void func_0016CEC8(void* self, int a1)
{
    cCameraTriggerMan_streamInIf_CEC8((void*)D_004C5830, self, a1);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cCameraTriggerMan_streamIn(void* self, void* stream);

// PORT: the unit declares cCameraTriggerMan_streamInIf as returning void*, but the body returns nothing.
void cCameraTriggerMan_streamInIf_impl(void* self, void* unused, void* stream) __asm__("cCameraTriggerMan_streamInIf");
void cCameraTriggerMan_streamInIf_impl(void* self, void* unused, void* stream)
{
    if (stream != 0) {
        cCameraTriggerMan_streamIn(self, stream);
    }
}

//100%
// PORT: func_0016CF40__FPv is mangled as (void*), but this caller passes two args.
void func_0016CF40_2(void* mgr, void* self) __asm__("func_0016CF40__FPv");

extern "C" void func_0016CF18(void* self)
{
    func_0016CF40_2((void*)D_004C5830, self);
}

//100%
void func_0016CF40(void* self)
{
}

//100%
// PORT: the unit declares func_0016CF48 as returning void*; it returns nothing.
extern "C" void func_0016CF48_impl(void* vself, int mask) __asm__("func_0016CF48");

extern "C" void func_0016CF48_impl(void* vself, int mask)
{
    sCtMan_CF48* self = (sCtMan_CF48*)vself;
    for (int i = 0; i < self->count; i++) {
        sCtTrig_CF48* t = self->trigs[i];
        if (t->mask & mask) {
            if (t->reg == 0) {
                t->reg = t;
                char* w = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x20);
                sCtBox_CF48 box = t->shape->bounds();
                insert_CF48(w, t->item, &box);
            }
        } else if (t->reg != 0) {
            char* w = *(char**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x20);
            sCtBox_CF48 box = t->shape->bounds();
            remove_CF48(w, t->item, &box);
            t->reg = 0;
        }
    }
}

extern "C" void* func_0016CF48(void* self, int type);

//100%
void cCameraTriggerMan_setInGameTriggers(void* self)
{
    func_0016CF48(self, 2);
}

//99.29%
void* func_0016D1D8(void* self)
{
    return func_0016CF48(self, 1);
}

struct cCameraTriggerStack {
    int field_0x0;
    int field_0x4;
};

extern "C" int func_0016D1F8(int a0)
{
    return a0;
}

//100%
void cCameraTriggerStack_init(cCameraTriggerStack* self)
{
    self->field_0x0 = 0;
    self->field_0x4 = 0;
}

//100%
void cCameraTriggerStack_init(cCameraTriggerStack* self);

extern "C" cCameraTriggerStack* func_0016D210(cCameraTriggerStack* self)
{
    cCameraTriggerStack_init(self);
    return self;
}

//100%
void func_0016D238(void* self, int a1)
{
    *(int*)((char*)self + (*(int*)self << 2) + 0x8) = a1;
    *(int*)((char*)self + 0x4) = a1;
    *(int*)self = *(int*)self + 1;
}

//100%
struct sCamTrigStack {
    unsigned int count; // 0x0
    int top; // 0x4
    int items[1]; // 0x8
};

extern "C" int func_0016D260(sCamTrigStack* self, int key, int* changed, int* out)
{
    unsigned int i;
    for (i = 0; i < self->count; i++) {
        if (self->items[i] == key) {
            unsigned int j;
            for (j = i + 1; j < self->count; j++) {
                self->items[j - 1] = self->items[j];
            }
            self->count--;
            break;
        }
    }
    if (self->count != 0) {
        int t = self->items[self->count - 1];
        if (t == self->top) {
            *changed = 0;
        } else {
            *changed = 1;
            *out = t;
        }
        return 0;
    }
    *changed = 0;
    return 1;
}

INCLUDE_ASM("camera/trigger/cameratriggerman", func_0016D320);

//100%
extern void* D_004A28A8;
extern "C" void func_00162060(void* self, int mode, int arg, float blend);

struct sCamEvt_E1D8 {
    int type;
    int pad4;
    unsigned int id;
    float dur;
};

struct sCams_E1D8 {
    int count;
    char* cam[1];
};

extern "C" void func_0016E1D8(sCamEvt_E1D8* evt, char* rider)
{
    sCams_E1D8* cams = *(sCams_E1D8**)(*(char**)((char*)D_004A28A8 + 0x84) + 0x84);
    void* cam = *(void**)(cams->cam[*(int*)(rider + 0x870)] + 0xA8);
    switch (evt->type) {
    case 2: {
        float rate;
        if (evt->dur != 0.0f)
            rate = 1.0f / evt->dur * 0.016666668f;
        else
            rate = 1.0f;
        func_00162060(cam, 0x5C, (int)evt, rate);
        break;
    }
    case 1: {
        float rate;
        if (evt->dur != 0.0f)
            rate = 1.0f / evt->dur * 0.016666668f;
        else
            rate = 1.0f;
        func_00162060(cam, 0x5B, (int)evt, rate);
        break;
    }
    case 0: {
        float rate = 0.0f;
        if (evt->dur == rate)
            rate = 1.0f;
        else
            rate = 1.0f / evt->dur * 0.016666668f;
        int mode;
        switch (evt->id) {
        case 3: mode = 4; break;
        case 7: mode = 3; break;
        case 1: mode = 2; break;
        case 2: mode = 1; break;
        case 4: mode = 7; break;
        case 5: mode = 5; break;
        case 6: mode = 6; break;
        case 8: mode = 8; break;
        case 10: mode = 9; break;
        case 9: mode = 10; break;
        case 11: mode = 11; break;
        case 12: mode = 12; break;
        case 13: mode = 13; break;
        case 14: mode = 14; break;
        case 15: mode = 15; break;
        case 16: mode = 16; break;
        case 17: mode = 17; break;
        case 18: mode = 18; break;
        case 19: mode = 19; break;
        case 20: mode = 20; break;
        case 21: mode = 21; break;
        case 22: mode = 22; break;
        case 23: mode = 23; break;
        case 24: mode = 24; break;
        case 25: mode = 25; break;
        case 26: mode = 26; break;
        case 27: mode = 27; break;
        case 28: mode = 28; break;
        case 29: mode = 29; break;
        case 30: mode = 30; break;
        case 31: mode = 31; break;
        case 32: mode = 32; break;
        case 33: mode = 0x29; break;
        case 34: case 35: case 36: case 37: case 38: case 39: case 40: case 41: mode = evt->id - 1; break;
        case 44: mode = 0x2A; break;
        case 45: mode = 0x2B; break;
        case 46: mode = 0x2C; break;
        case 47: mode = 0x2D; break;
        case 48: mode = 0x2E; break;
        case 49: mode = 0x2F; break;
        case 50: mode = 0x30; break;
        case 51: mode = 0x31; break;
        case 52: mode = 0x32; break;
        case 53: mode = 0x33; break;
        case 54: mode = 0x34; break;
        case 55: mode = 0x35; break;
        case 56: mode = 0x36; break;
        case 57: mode = 0x37; break;
        case 58: mode = 0x38; break;
        case 59: mode = 0x39; break;
        case 60: mode = 0x3A; break;
        case 61: mode = 0x3B; break;
        case 62: mode = 0x3C; break;
        case 63: mode = 0x3D; break;
        case 64: mode = 0x3E; break;
        case 65: mode = 0x3F; break;
        case 66: mode = 0x40; break;
        case 67: mode = 0x41; break;
        case 68: mode = 0x42; break;
        case 69: mode = 0x43; break;
        case 70: mode = 0x44; break;
        case 71: mode = 0x45; break;
        case 72: mode = 0x46; break;
        case 73: mode = 0x47; break;
        case 74: mode = 0x48; break;
        case 75: mode = 0x49; break;
        case 42: mode = 0x4C; break;
        case 0:
        case 43:
        default: mode = 0; break;
        }
        func_00162060(cam, mode, 0, rate);
        break;
    }
    }
}


INCLUDE_ASM("camera/trigger/cameratriggerman", cCTBoundObjEllipse_ClampPoint);

INCLUDE_ASM("camera/trigger/cameratriggerman", cCTBoundObjBox_ClampPoint);

INCLUDE_ASM("camera/trigger/cameratriggerman", cCTBoundObjLine_ClampPoint);

INCLUDE_ASM("camera/trigger/cameratriggerman", cCTBoundObjLine_GetWorldStart);

INCLUDE_ASM("camera/trigger/cameratriggerman", cCTBoundObjLine_GetWorldEnd);

INCLUDE_ASM("camera/trigger/cameratriggerman", cCTBoundObj_GetWorldPoint);

