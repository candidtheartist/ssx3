#include "common.h"

//100%
extern "C" void cBXString__cBXString(void* self, int flags);
void cAppMan__cAppMan(void* self, int flags);

extern "C" void cSSXApp__cSSXApp(void* self, int flags)
{
    cBXString__cBXString((char*)self + 0xCC, 2);
    cBXString__cBXString((char*)self + 0xC8, 2);
    cBXString__cBXString((char*)self + 0xC4, 2);
    cAppMan__cAppMan(self, flags);
}

extern "C" int func_00243950(void* self)
{
    return *(int*)((char*)self + 0x78);
}

extern "C" int func_00243958(void* self)
{
    return *(int*)((char*)self + 0x7C);
}

extern "C" int func_00243960(void* self)
{
    return *(int*)((char*)self + 0x80);
}

extern "C" int func_00243968(void* self)
{
    return *(int*)((char*)self + 0x84);
}

extern "C" int func_00243970(void* self)
{
    return *(int*)((char*)self + 0x88);
}

extern "C" int func_00243978(void* self)
{
    return *(int*)((char*)self + 0x8C);
}

struct sfunc_00243980 {
    char pad[0xB0];
    int values[1];
};

extern "C" int func_00243980(sfunc_00243980* self, int i)
{
    return self->values[i];
}

struct sfunc_00243990 {
    char pad[0xB8];
    int values[1];
};

extern "C" int func_00243990(sfunc_00243990* self, int i)
{
    return self->values[i];
}

extern "C" int func_002439A0(void* self)
{
    return *(int*)((char*)self + 0xC0);
}

extern "C" void* func_002439A8(void* self)
{
    return (char*)self + 0xC4;
}

extern "C" void* func_002439B0(void* self)
{
    return (char*)self + 0xC8;
}

extern "C" int func_002439B8(void* self)
{
    return *(int*)((char*)self + 0xD0);
}

extern "C" int func_002439C0(void* self)
{
    return *(int*)((char*)self + 0x9C);
}

extern "C" int func_002439C8(void* self)
{
    return *(int*)((char*)self + 0xA4);
}

extern "C" int func_002439D0()
{
    return 0x2;
}

extern "C" int func_002439D8(void* self)
{
    return *(int*)((char*)self + 0xA0);
}

extern "C" void func_002439E0(void* self, int value)
{
    *(int*)((char*)self + 0xA0) = value;
}

extern "C" void func_002439E8(void* self)
{
    *(int*)((char*)self + 0x7C) = 0;
    *(int*)((char*)self + 0x80) = 0;
}

extern "C" void func_002439F8(void* self)
{
    *(int*)((char*)self + 0x84) = 0;
}

extern "C" int func_00243A00(void* self)
{
    return *(int*)((char*)self + 0x84) != 0;
}

extern "C" int func_00243A10(void* self)
{
    return *(int*)((char*)self + 0x7C) || *(int*)((char*)self + 0x80);
}

extern "C" int func_00243A38(void* self)
{
    return *(int*)((char*)self + 0x11C);
}

//100%
void operator_delete(int* ptr);
extern char D_0046D970[];

extern "C" void func_00243A40(int* self, int flags)
{
    *(void**)self = D_0046D970;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern "C" void func_00243A70(void* self)
{
    *(int*)((char*)self + 0x8) = 0x1;
}

//100%
void operator_delete(int* ptr);
extern char D_0046D970[];

extern "C" void func_00243A80(int* self, int flags)
{
    *(void**)self = D_0046D970;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void func_00243AB0(void* self)
{
}

extern char D_0047D8F0[];

extern "C" void* func_00243AB8(void* self)
{
    *(int*)((char*)self + 0x4) = 0;
    *(void**)self = D_0047D8F0;
    *(int*)((char*)self + 0x8) = 0;
    return self;
}

extern "C" void func_00243AD8(void* self)
{
    *(int*)((char*)self + 0x4) = 0x1;
}

//100%
void operator_delete(int* ptr);
extern char D_0046D970[];

extern "C" void func_00243AE8(int* self, int flags)
{
    *(void**)self = D_0046D970;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D818[];
extern "C" void func_00231CD0(void* self);

extern "C" void* func_00243B18(void* self)
{
    func_00231CD0(self);
    *(int*)((char*)self + 0xC) = 0;
    *(void**)self = D_0047D818;
    return self;
}

//100%
void operator_delete(int* ptr);
extern char D_0046D970[];

extern "C" void func_00243B50(int* self, int flags)
{
    *(void**)self = D_0046D970;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);
extern char D_0046D970[];

extern "C" void func_00243B80(int* self, int flags)
{
    *(void**)self = D_0046D970;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D788[];
extern "C" void func_00231CD0(void* self);

extern "C" void* cGameLoadScreen_ctor(void* self)
{
    func_00231CD0(self);
    *(int*)((char*)self + 0xC) = 0;
    *(void**)self = D_0047D788;
    *(int*)((char*)self + 0x10) = 0;
    *(int*)((char*)self + 0x14) = 0;
    return self;
}

struct sfunc_00243BF0 {
    char pad[0x10];
    int values[1];
};

extern "C" int func_00243BF0(sfunc_00243BF0* self, int i)
{
    return self->values[i];
}

//100%
void operator_delete(int* ptr);

extern char D_0046D970[];

extern "C" void func_00243C00(int* self, int flags)
{
    *(void**)self = D_0046D970;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D740[];
extern "C" void func_00231CD0(void* self);

extern "C" void* cFELoadScreen_ctor(void* self)
{
    func_00231CD0(self);
    *(int*)((char*)self + 0xC) = 0;
    *(void**)self = D_0047D740;
    *(int*)((char*)self + 0x10) = 0;
    *(int*)((char*)self + 0x14) = 0;
    return self;
}

struct sfunc_00243C70 {
    char pad[0x10];
    int values[1];
};

extern "C" int func_00243C70(sfunc_00243C70* self, int i)
{
    return self->values[i];
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameState_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void GameState_OverlayEnter(void* self)
{
}

//100%
void GameState_OverlayUpdate(void* self)
{
}

//100%
void GameState_OverlayExit(void* self)
{
}

//100%
void GameState_Enter(void* self)
{
}

//100%
void GameState_Update(void* self)
{
}

//100%
void GameState_Exit(void* self)
{
}

//100%
int func_00243CE0(void* self)
{
    return 0x1;
}

//100%
void GameState_v09(void* self)
{
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateQuit_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D690[];
extern int D_004A2C68;

extern "C" void* func_00243D20(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 8;
    *(void**)(self + 3) = D_0047D690;
    self[1] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateIdle_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateFinish_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void func_00243DB8(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D588[];
extern int D_004A2C68;

extern "C" void* func_00243DE8(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 10;
    *(void**)(self + 3) = D_0047D588;
    self[1] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStatePreRaceLoad_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void cGFGateState_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D4D8[];
extern int D_004A2C68;

extern "C" void* func_00243E80(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 4;
    *(void**)(self + 3) = D_0047D4D8;
    self[1] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateRace_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D480[];
extern int D_004A2C68;

extern "C" void* func_00243EE8(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 5;
    *(void**)(self + 3) = D_0047D480;
    self[1] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateReset_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateRestartRace_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D3D0[];
extern int D_004A2C68;

extern "C" void* func_00243F80(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    *(void**)(self + 3) = D_0047D3D0;
    self[0] = 1;
    self[1] = 3;
    self[5] = 0;
    self[6] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateWarpToEvent_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D378[];
extern int D_004A2C68;

extern "C" void* func_00243FF0(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 10;
    *(void**)(self + 3) = D_0047D378;
    self[1] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateEventSelect_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern "C" void func_00244058(void* self, int value)
{
    *(int*)((char*)self + 0x18) = value;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateEventSwitchLoad_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStatePreRaceMenu_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D270[];
extern int D_004A2C68;

extern "C" void* func_002440C0(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 3;
    *(void**)(self + 3) = D_0047D270;
    self[1] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateResults_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D218[];
extern int D_004A2C68;

extern "C" void* func_00244128(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 8;
    *(void**)(self + 3) = D_0047D218;
    self[1] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateFinishCinematic_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D1C0[];
extern int D_004A2C68;

extern "C" void* func_00244190(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 7;
    *(void**)(self + 3) = D_0047D1C0;
    self[1] = 0;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D6E8[];

extern "C" void GameStateReplayPlayback_dtor(int* self, int flags)
{
    *(void**)((char*)self + 0xC) = D_0047D6E8;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern char D_0047D6E8[];
extern char D_0047D168[];
extern int D_004A2C68;

extern "C" void* func_002441F8(int* self)
{
    self[0] = 0;
    *(void**)(self + 3) = D_0047D6E8;
    D_004A2C68 = 0;
    self[0] = 4;
    *(void**)(self + 3) = D_0047D168;
    self[1] = 0;
    return self;
}

extern "C" void func_00244230()
{
}

extern "C" void func_00244238()
{
}

//100%
extern int D_004428F0[];
extern int D_005366E8[];
extern int D_004A2A50;
extern int D_004A2A54;

extern "C" void func_00244240(int id)
{
    D_004A2A50 = D_004428F0[id];
    D_005366E8[D_004A2A54] = id;
}

extern "C" int func_00244278(void* self)
{
    return *(int*)((char*)self + 0x214);
}

extern "C" int func_00244280(void* self)
{
    return *(int*)((char*)self + 0x218);
}

extern "C" int func_00244288(void* self)
{
    return *(int*)((char*)self + 0x200);
}

extern "C" int func_00244290(void* self)
{
    return *(int*)((char*)self + 0x20);
}

extern "C" int func_00244298(void* self)
{
    return *(int*)((char*)self + 0x10);
}

extern "C" int func_002442A0(void* self)
{
    return *(int*)((char*)self + 0x24);
}

extern "C" int func_002442A8(void* self)
{
    return *(int*)((char*)self + 0xA4);
}

extern "C" int func_002442B0(void* self)
{
    return *(int*)((char*)self + 0xC);
}

extern "C" int func_002442B8(void* self)
{
    return *(int*)((char*)self + 0x48);
}

extern "C" int func_002442C0(void* self)
{
    return *(int*)((char*)self + 0x28);
}

extern "C" int func_002442C8(void* self)
{
    return *(int*)((char*)self + 0x2C);
}

extern "C" int func_002442D0(void* self)
{
    return *(int*)((char*)self + 0x44);
}

extern "C" int func_002442D8(void* self)
{
    return *(int*)((char*)self + 0x4C);
}

extern "C" int func_002442E0(void* self)
{
    return *(int*)((char*)self + 0x50);
}

extern "C" int func_002442E8(void* self)
{
    return *(int*)((char*)self + 0x54);
}

extern "C" int func_002442F0(void* self)
{
    return *(int*)((char*)self + 0x64);
}

extern "C" int func_002442F8(void* self)
{
    return *(int*)((char*)self + 0x70);
}

extern "C" int func_00244300(void* self)
{
    return *(int*)((char*)self + 0x74);
}

extern "C" int func_00244308(void* self)
{
    return *(int*)((char*)self + 0x34);
}

extern "C" int func_00244310(void* self)
{
    return *(int*)((char*)self + 0x78);
}

extern "C" int func_00244318(void* self)
{
    return *(int*)((char*)self + 0x7C);
}

extern "C" int func_00244320(void* self)
{
    return *(int*)((char*)self + 0x14);
}

extern "C" int func_00244328(void* self)
{
    return *(int*)((char*)self + 0x38);
}

extern "C" int func_00244330(void* self)
{
    return *(int*)((char*)self + 0x3C);
}

extern "C" int func_00244338(void* self)
{
    return *(int*)((char*)self + 0x40);
}

extern "C" int func_00244340(void* self)
{
    return *(int*)((char*)self + 0x88);
}

extern "C" int func_00244348(void* self)
{
    return *(int*)((char*)self + 0x8C);
}

extern "C" int func_00244350(void* self)
{
    return *(int*)((char*)self + 0x90);
}

extern "C" int func_00244358(void* self)
{
    return *(int*)((char*)self + 0x94);
}

extern "C" int func_00244360(void* self)
{
    return *(int*)((char*)self + 0x224);
}

extern "C" int func_00244368(void* self)
{
    return *(int*)((char*)self + 0x84);
}

// The list at +0x84
struct sAppList {
    int unk0;
    int items[4];   // 0x4
    int count;      // 0x14
};

extern "C" int func_00244370(void* self, int i)
{
    return (*(sAppList**)((char*)self + 0x84))->items[i];
}

extern "C" int func_00244388(void* self)
{
    return *(int*)(*(char**)((char*)self + 0x84) + 0x10);
}

extern "C" int func_00244398(void* self)
{
    sAppList* list = *(sAppList**)((char*)self + 0x84);
    return list->items[list->count];
}

extern "C" int func_002443B0(void* self)
{
    return *(int*)(*(char**)((char*)self + 0x84) + 0x14);
}

//100%
void operator_delete(int* ptr);

extern char D_0047DB28[];

extern "C" void GenericStreamPause_v01(int* self, int flags)
{
    *(void**)self = D_0047DB28;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
extern "C" void* func_002443F0(void* self, void* a1)
{
    return a1;
}

//100%
int GenericStreamPause_v03(void* self)
{
    return 0x1;
}

//100%
void func_00244400(void* self, int val)
{
    *(int*)((char*)self + 0x0) = val;
}

//100%
void func_00244408(void* self, int val)
{
    *(int*)((char*)self + 0x4) = val;
}

//100%
extern "C" void func_003546C8(void* self, int flags);
extern void* D_0047D070[];
struct sVEntry_func_00244410 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

extern "C" void VfxProcess_dtor(void* self, int flags)
{
    *(void***)((char*)self + 0xC) = D_0047D070;
    void* obj = *(void**)((char*)self + 0x10);
    if (obj != 0) {
        sVEntry_func_00244410* vt = *(sVEntry_func_00244410**)((char*)obj + 0x44);
        vt[1].fn((char*)obj + vt[1].delta, 3);
    }
    func_003546C8(self, flags);
}

//100%
class cAppDtorVirt44 {
public:
    char pad[0x44];
    // vptr lands at 0x44 (g++ 2.95 places it after the class's own data);
    // slot N lives at vtable offset N*8 (delta at +0, function at +4)
    virtual void v01();
    virtual void v02();
    virtual void v03();
};

extern "C" void VfxProcess_Update(void* self)
{
    (*(cAppDtorVirt44**)((char*)self + 0x10))->v02();
}

//100%
extern "C" void VfxProcess_Render(void* self)
{
    (*(cAppDtorVirt44**)((char*)self + 0x10))->v03();
}

extern char D_0047D008[];

extern "C" void* func_002444D8(void* self)
{
    *(void**)self = D_0047D008;
    return self;
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern int D_004A2C70;

extern "C" void func_00244520(int value)
{
    D_004A2C70 = value;
}

//100%
void GMHandler_Reset(void* self)
{
}

//100%
int GMHandler_v06(void* self)
{
    return 0x1;
}

//100%
void GMHandler_v07(void* self)
{
}

//100%
void GMHandler_OnRiderFinished(void* self)
{
}

//100%
int func_00244548(void* self)
{
    return 0;
}

//100%
void GMHandler_SaveState(void* self)
{
}

//100%
void GMHandler_LoadState(void* self)
{
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler0_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler1_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler8_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler9_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void GMHandler9_SaveState(void* self)
{
}

//100%
void GMHandler9_LoadState(void* self)
{
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler2_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler4_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler5_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler6_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void GMHandler7_dtor(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

//100%
void operator_delete(int* ptr);

extern char D_0047D008[];

extern "C" void func_00244720(int* self, int flags)
{
    *(void**)self = D_0047D008;
    if (flags & 1) {
        operator_delete(self);
    }
}

extern "C" int func_00244750(void* self)
{
    return *(int*)((char*)self + 0x434);
}

extern "C" int func_00244758(void* self)
{
    return *(int*)((char*)self + 0x130);
}

extern "C" int func_00244760(void* self)
{
    return *(int*)((char*)self + 0xBC);
}

extern "C" int func_00244768(void* self)
{
    return *(int*)((char*)self + 0xC0);
}

extern "C" void func_00244770(void* self)
{
    (*(void (**)(void*))((char*)self + 0x78))(self);
}

extern "C" int func_00244790(void* self)
{
    int r = 0;
    if (!*(int*)((char*)self + 0x440))
        r = *(int*)((char*)self + 0x43C) != 0;
    return r;
}

extern "C" int func_002447B0(void* self)
{
    return *(int*)((char*)self + 0x43C) != 0;
}

extern "C" int func_002447C0(void* self)
{
    return *(int*)((char*)self + 0x43C);
}

extern "C" void func_002447C8(void* self)
{
    *(int*)((char*)self + 0x440) = 0x1;
}

extern "C" int func_002447D8(void* self)
{
    return ((*(unsigned int*)((char*)self + 0x43C) >> 5) & 0xF) - 1;
}

extern "C" void func_002C2508(void* p);

extern "C" void func_002447F0(void* self)
{
    func_002C2508((char*)self + 0x276);
}

extern "C" void func_002C2540(void* p);

extern "C" void func_00244810(void* self)
{
    func_002C2540((char*)self + 0x276);
}

extern "C" void* func_00244830(void* self)
{
    return (char*)self + 0x276;
}

extern "C" void func_00244838(void* self, int value)
{
    *(int*)((char*)self + 0x11C) = value;
}

extern "C" void func_00244840(void* self, int value)
{
    *(int*)((char*)self + 0x120) = value;
}

extern "C" void func_00244848(void* self, int value)
{
    *(int*)((char*)self + 0x124) = value;
}

extern "C" void func_00244850(void* self, int value)
{
    *(int*)((char*)self + 0x128) = value;
}

extern "C" void func_00244858(void* self, int value)
{
    *(int*)((char*)self + 0x12C) = value;
}

//100%
void cMCOverlayManager_NullCallback(void* self)
{
}

//100%
int cMCOverlayManager_NullCallbackRet0(void* self)
{
    return 0;
}

//100%
int cMCOverlayManager_NullCallbackRet1(void* self)
{
    return 0x1;
}

//100%
int cMCOverlayManager_NullChunkCallback(void* self)
{
    return 0;
}

//100%
void func_00244880(void* self)
{
    *(int*)((char*)self + 0x40) = 0;
}

extern "C" void func_0022E8B8(void* p);
extern "C" int func_0022E920(void* p);

extern "C" int func_00244888(void* self)
{
    func_0022E8B8(*(void**)((char*)self + 0x84));
    if (*(int*)((char*)self + 0x9C) != 0) {
        return 0;
    }
    if (func_0022E920(*(void**)((char*)self + 0x84)) != 0) {
        return 1;
    }
    *(int*)((char*)self + 0x9C) = 1;
    *(int*)((char*)self + 0xA0) = 1;
    return 0;
}

//100%
extern "C" void func_003546C8(void* self, int flags);
extern void* D_0047CB60[];
struct sVEntry_func_002448E0 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

extern "C" void AIVfxProcess_dtor(void* self, int flags)
{
    *(void***)((char*)self + 0xC) = D_0047CB60;
    void* obj = *(void**)((char*)self + 0x10);
    if (obj != 0) {
        sVEntry_func_002448E0* vt = *(sVEntry_func_002448E0**)((char*)obj + 0x4);
        vt[1].fn((char*)obj + vt[1].delta, 3);
    }
    func_003546C8(self, flags);
}

//100%
class cAppDtorVirt04 {
public:
    int field_0x0;
    // vptr lands at 0x4 (g++ 2.95 places it after the class's own data);
    // slot N lives at vtable offset N*8 (delta at +0, function at +4)
    virtual void v01();
    virtual void v02();
    virtual void v03();
};

extern "C" void AIVfxProcess_Update(void* self)
{
    (*(cAppDtorVirt04**)((char*)self + 0x10))->v02();
}

//100%
extern "C" void AIVfxProcess_Render(void* self)
{
    (*(cAppDtorVirt04**)((char*)self + 0x10))->v03();
}

//100%
extern "C" void func_003546C8(void* self, int flags);
extern void* D_0047CAE8[];

extern "C" void StatsProcess_dtor(void* self, int flags)
{
    *(void***)((char*)self + 0xC) = D_0047CAE8;
    operator_delete(*(int**)((char*)self + 0x10));
    func_003546C8(self, flags);
}

void func_002D21B0(void*);

//100%
extern "C" void StatsProcess_Update(void* self)
{
    func_002D21B0(*(void**)((char*)self + 0x10));
}

void func_002D21B8(void*);

//100%
extern "C" void StatsProcess_Render(void* self)
{
    func_002D21B8(*(void**)((char*)self + 0x10));
}

extern "C" void* func_0039E390(void* self);

extern "C" void func_00244A38()
{
}

//100%
struct sGfxVEntry_44A40 {
    short delta;
    short index;
    void (*fn)(void*);
};

struct sGfx_44A40 {
    char pad_0x0[0x10D8];
    sGfxVEntry_44A40* vtable;   // 0x10D8
};

struct sView_44A40 {
    char pad_0x0[0x3D4];
    int paused;                 // 0x3D4
};

struct sViewRef_44A40 {
    sView_44A40* view;          // 0x0
};

struct sRace_44A40 {
    char pad_0x0[0x1D0];
    int over;                   // 0x1D0
};

struct sApp_44A40 {
    char pad_0x0[0x10];
    sViewRef_44A40* view;       // 0x10
    char pad_0x14[0x78 - 0x14];
    sRace_44A40* race;          // 0x78
    char pad_0x7C[0x84 - 0x7C];
    void* menu;                 // 0x84
    char pad_0x88[0x9C - 0x88];
    int f9C;                    // 0x9C
    int fA0;                    // 0xA0
};

void func_003A6928(void* p);
extern "C" void cGameViewMan_updateAll(void* list);
extern "C" void func_00230F40(void* self);
extern "C" void func_0022D8D8(void* p);
extern "C" void func_003A88A8(void* p);
extern sGfx_44A40* D_004A289C;

extern "C" int func_00244A40(sApp_44A40* self)
{
    if (func_0022E920(self->menu) == 0 || self->race->over == 0) {
        self->view->view->paused = 0;
        func_003A6928(self->view);
        cGameViewMan_updateAll(self->menu);
        if (self->race->over == 0) {
            func_00230F40(self);
            func_0022D8D8(self->race);
        }
        if (self->f9C == 0 && func_0022E920(self->menu) == 0) {
            self->fA0 = 1;
        }
        self->f9C = 1;
        if (self->fA0 != 0) {
            sGfx_44A40* g = D_004A289C;
            sGfxVEntry_44A40* e = &g->vtable[19];
            e->fn((char*)g + e->delta);
            func_0022E8B8(self->menu);
            func_003A88A8(self->view->view);
            self->fA0 = 0;
        }
        return 0;
    }
    self->view->view->paused = 1;
    self->f9C = 0;
    self->fA0 = 0;
    func_003A6928(self->view);
    func_0022D8D8(self->race);
    return 1;
}


INCLUDE_ASM("main/ssxappdtor", cGame_UpdatePauseAndUI);

struct sVE_4E60 {
    short delta;
    short index;
    void (*fn)(void*, ...);
};

extern "C" int InputSync_IsReady(void* p);
extern "C" int InputSync_ApplyInput(void* p);
extern "C" void func_00354C98(void* p, int n);
extern "C" void func_00354F98(void* p, int n);
extern "C" void func_00355028(void* p, int n);
extern "C" void func_0026F4A8(void* p);
extern "C" int Replay_IsPaused(void* p);
extern "C" int func_0026CE50(void* p);
extern "C" void func_00309270(void* p);
extern "C" void CrowdMan2d_Update(void* p);
extern "C" void CrowdMan3d_Update(void* p);
extern "C" void func_00357BF8(void* p);
extern "C" void func_002B7848(void* p, void* q, int i);
extern char D_004A5988[8];
extern void* D_004A28A4;

static inline char* GetSnd() { return D_004A5988; }
static inline bool IsRun(int st) { return st != 0 && st < 10; }
static inline bool Is3(int st) { return st == 3; }
#define F(o, t) (*(t*)((char*)self + (o)))

//100%
// App frame end: sound channel updates, view update and per-player loop.
// The unused label stops cse from reusing the loop test's self->0x84 load.
extern "C" void func_00244E60(char* self)
{
    int skip;
    if (F(0x7C, void*) == 0 || InputSync_IsReady(F(0x7C, void*)) != 0) {
        if (F(0x214, int) == 3) {
            func_00230F40(self);
            func_00354C98(GetSnd(), 1);
        } else {
            func_00230F40(self);
        }
        if ((D_004A2A50 & 1) == 0) func_0026F4A8(F(0x28, void*));
        if (Replay_IsPaused(F(0x28, void*)) == 0 && !(D_004A2A50 & 8)) {
            char* g = (char*)D_004A28A4;
            sVE_4E60* vt = *(sVE_4E60**)(g + 0x2A8);
            vt[5].fn(g + vt[5].delta);
        }
    }
    skip = 0;
    if ((D_004A2A50 & 1) || Replay_IsPaused(F(0x28, void*))) skip = 1;
    if (!skip) {
        if ((F(0x7C, void*) != 0 && InputSync_ApplyInput(F(0x7C, void*)) == 0) || func_0026CE50(F(0x34, void*))) skip = 1;
    }
    if (!skip) {
        if (!(D_004A2A50 & 2)) func_00354F98(GetSnd(), 1);
        func_00354F98(GetSnd(), 5);
        func_00354F98(GetSnd(), 6);
        if (!(D_004A2A50 & 2)) func_00355028(GetSnd(), 1);
        {
            char* o = F(0xC, char*);
            sVE_4E60* vt = *(sVE_4E60**)(o + 0xCC);
            vt[3].fn(o + vt[3].delta);
        }
        if (!(D_004A2A50 & 0x10)) func_00354F98(GetSnd(), 2);
        if (!(D_004A2A50 & 4)) func_00354F98(GetSnd(), 3);
        func_00309270(F(0x30, void*));
        CrowdMan2d_Update(F(0x38, void*));
        CrowdMan3d_Update(F(0x3C, void*));
        func_00357BF8(F(0x40, void*));
        func_00354C98(GetSnd(), 1);
    } else {
        func_00354F98(GetSnd(), 5);
        if (!(D_004A2A50 & 4)) func_00354F98(GetSnd(), 3);
    }
    func_00354F98(GetSnd(), 4);
    {
        int st = **(int**)(self + 0x28);
        if (!IsRun(st) || !Is3(st)) cGameViewMan_updateAll(F(0x84, void*));
    }
    F(0xAC, int)++;
    for (unsigned int i = 0; i < *(unsigned int*)(F(0x84, char*) + 0x10); i++) {
    top:
        func_002B7848(F(0x4C, void*), *(char**)(F(0x84, char*) + (i << 2) + 4) + 0x20, i);
    }
}
#undef F

extern void* D_004A2EEC;
extern "C" void func_002570D8(void* p);

extern "C" void cGameComm_UpdateIfActive()
{
    if (D_004A2EEC)
        func_002570D8(D_004A2EEC);
}

extern void* D_004A2EB8;
extern "C" void func_003F42A0();

extern "C" void NetConn_IdleIfActive()
{
    if (D_004A2EB8)
        func_003F42A0();
}

extern "C" void func_00231D18(void* self);
extern char* D_004A28A8;

extern "C" int func_00245168(void* self)
{
    func_00231D18(self);
    if (*(int*)(D_004A28A8 + 0x4) != 0) {
        *(int*)((char*)self + 0x8) = 1;
        return 0;
    }
    return 1;
}

typedef void (*fn_002451B0)(char*);

struct s002451B0_World {
    char pad[0x28];
    char* riders[20];
    int count;
};

struct s002451B0_App {
    char pad[0xC];
    s002451B0_World* world;
};

extern "C" void func_002451B0(s002451B0_App* self)
{
    int i = 0;
    if (self->world->count > 0) {
        do {
            char* obj = self->world->riders[i++];
            char* vt = *(char**)(obj + 0x6C0);
            ((fn_002451B0)*(void**)(vt + 0x9C))(obj + *(short*)(vt + 0x98));
        } while (i < self->world->count);
    }
}

//100%
void* cFEStateProgressive_dtor(void* self)
{
    return func_0039E390(self);
}

//100%
struct cUIText;
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void cUIScreen_playFrame(void* screen, int a1, int a2);
extern "C" void* cUIScreen_getObjectByHashName(void* self, int hash);
void cUIText_setAsciiString(cUIText* text, const char* str);
extern char D_004A2AD8[];
extern char D_004A2AC0[];
extern char D_0047B988[];

extern "C" void cFEStateProgressive_Init(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_004A2AD8), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
    cUIText* text = (cUIText*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2AC0));
    if (text != 0) {
        cUIText_setAsciiString(text, D_0047B988);
    }
}

//100%
// PORT: cMemMan_alloc bound as a placement operator new (gcc then treats the result as unaliased)
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" void func_0039E2A0(void* self, void* owner);
extern "C" void func_0039F400(void* list, void* item);
extern char D_0047B9C0[];
extern char D_004A2AC8[];
extern void* D_0047DA58[];

struct sUIObj_2452D8 {
    int f0;
    int f4;
    void** vt;
    char pad[0x3C];
    char flag48;
    char pad49[7];
};

struct sRVEntry_2452D8 {
    short delta;
    short index;
    void (*fn)(void*, int);
};
struct sRCtx_2452D8 {
    char pad[0x10D8];
    sRVEntry_2452D8* vt;
};
extern sRCtx_2452D8* D_004A5B80;

static inline int isHash_2452D8(int id, char* s)
{
    return id == GetHashValue32(s);
}

static inline sUIObj_2452D8* newUIObj_2452D8(void* owner, char flag)
{
    sUIObj_2452D8* o = new (D_0047B9C0, 0, 0) sUIObj_2452D8;
    func_0039E2A0(o, *(void**)((char*)owner + 0x10));
    o->vt = D_0047DA58;
    o->flag48 = flag;
    return o;
}

extern "C" void cFEStateProgressive_OnWidgetAction(void* self, char* msg, int type)
{
    if (msg == 0) {
        return;
    }
    if (type != 5) {
        return;
    }
    if (isHash_2452D8(*(int*)(msg + 0x38), D_004A2AC8)) {
        sUIObj_2452D8* o = newUIObj_2452D8(self, 0);
        func_0039F400(*(char**)((char*)self + 0x10) + 0x18, o);
        D_004A5B80->vt[8].fn((char*)D_004A5B80 + D_004A5B80->vt[8].delta, 1);
    } else {
        sUIObj_2452D8* o = newUIObj_2452D8(self, 1);
        func_0039F400(*(char**)((char*)self + 0x10) + 0x18, o);
    }
}

//100%
extern "C" int func_002453E0(void* self, int a1, int a2)
{
    return a2 == 6 ? 0x101 : 0;
}

//100%
extern void* D_0047C948[];
extern "C" void* func_0039E390(void* self);

extern "C" void* cGameLoadState_dtor(void* self)
{
    *(void**)((char*)self + 0x8) = D_0047C948;
    return func_0039E390(self);
}

//100%
int GetHashValue32(char* str);
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void cUIScreen_playFrame(void* screen, int a1, int a2);
extern "C" void func_00246CF8(void* self, int a1);
extern signed char D_00535C11[];
extern char D_0047BA28[];
extern char D_0047BA38[];

extern "C" void cGameLoadState_Init(void* self)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    if (D_00535C11[0] == 2) {
        void* engine = *(void**)((char*)self + 0x10);
        void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0047BA28), 0);
        *(void**)((char*)self + 0x40) = screen;
        if (screen != 0) {
            cUIScreen_playFrame(screen, 0, 0);
        }
    } else {
        void* engine = *(void**)((char*)self + 0x10);
        void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0047BA38), 0);
        *(void**)((char*)self + 0x40) = screen;
        if (screen != 0) {
            cUIScreen_playFrame(screen, 0, 0);
        }
    }
    func_00246CF8(self, 0);
    func_00246CF8(self, 1);
}

//100%
extern char D_004A2BC8[];
extern char D_004A2BD0[];
extern char* D_004A5B64;
extern "C" void func_002C27C0(char* dst, const char* fmt, ...);
extern "C" void func_003A0E90(void* text, void* p);

extern "C" int cGameLoadState_TransitionIn(void* self, int refresh)
{
    void* obj = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2BC8));
    if (obj != 0) {
        char buf[0xD0];
        func_002C27C0(buf, D_004A2BD0, (int)*(float*)(D_004A5B64 + 0x38));
        func_003A0E90(obj, buf);
    }
    if (refresh != 0) {
        func_00246CF8(self, 0);
        func_00246CF8(self, 1);
    }
    return 0;
}

//100%
extern "C" void* cBE_getBE();
// PORT: cBE_getInterface__Fv is called with (be, kind) here; bind the 2-arg form to that symbol.
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_002464E8(void* self, int a1);
extern "C" void func_00246278(void* self, int a1);
extern signed char D_00535C11[];

extern "C" void cGameLoadState_OnWidgetCreated(void* self, int a1)
{
    cBE_getInterface_Fv(cBE_getBE(), 0);
    bool ok = D_00535C11[0] != 2;
    if (ok) {
        func_002464E8(self, a1);
    } else {
        func_00246278(self, a1);
    }
}

//100%
extern void* D_0047C878[];
extern "C" void* func_0039E390(void* self);

extern "C" void* cGameLoadStateOutLodge_dtor(void* self)
{
    *(void**)((char*)self + 0x8) = D_0047C878;
    return func_0039E390(self);
}

//100%
int GetHashValue32(char* str);
extern "C" void* cUIEngine_addScreenByHashName(void* engine, void* owner, int hash, int a3);
extern "C" void cUIScreen_playFrame(void* screen, int a1, int a2);
extern char D_0047BCC8[];

extern "C" void cGameLoadStateOutLodge_Init(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* screen = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0047BCC8), 0);
    *(void**)((char*)self + 0x40) = screen;
    if (screen != 0) {
        cUIScreen_playFrame(screen, 0, 0);
    }
}

//100%
void cGameLoadStateOutLodge_OnWidgetCreated(void* self)
{
}

//100%
extern char D_004A2BC8[];
extern char D_004A2BD0[];
extern char* D_004A5B64;
extern "C" void func_002C27C0(char* dst, const char* fmt, ...);
extern "C" void func_003A0E90(void* text, void* p);

extern "C" int cGameLoadStateOutLodge_TransitionIn(void* self)
{
    void* obj = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2BC8));
    if (obj != 0) {
        char buf[0xD0];
        func_002C27C0(buf, D_004A2BD0, (int)*(float*)(D_004A5B64 + 0x38));
        func_003A0E90(obj, buf);
    }
    return 0;
}

//100%
extern void* D_0047C7A8[];
extern "C" void* func_0039E390(void* self);

extern "C" void* cGameLoadStateConquer_dtor(void* self)
{
    *(void**)((char*)self + 0x8) = D_0047C7A8;
    return func_0039E390(self);
}

//100%
// PORT: cBE_getInterface__Fv really takes (be, kind); bound by asm label
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void* cBE_getBE();
extern "C" int func_00147618(void* iface, int a1);
extern char D_0047BCD8[];
extern char D_0047BCE8[];
extern char D_0047BCF8[];
extern char D_0047BD08[];
extern char D_0047BD18[];

class cUIObj_245730 {
public:
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
    virtual void setVisible(int on);
};

extern "C" void cGameLoadStateConquer_Init(void* self)
{
    void* engine = *(void**)((char*)self + 0x10);
    void* scr = cUIEngine_addScreenByHashName(engine, self, GetHashValue32(D_0047BCD8), 0);
    *(void**)((char*)self + 0x40) = scr;
    if (scr != 0) {
        cUIScreen_playFrame(scr, 0, 0);
    }
    char* ctrlDefault = D_0047BCE8;
    char* ctrlPro = D_0047BCF8;
    int r = func_00147618(cBE_getInterface_Fv(cBE_getBE(), 1), 0);
    cUIObj_245730* o;
    o = (cUIObj_245730*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(ctrlDefault));
    if (o != 0) {
        o->setVisible(r == 0);
    }
    o = (cUIObj_245730*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_0047BD08));
    if (o != 0) {
        o->setVisible(r == 0);
    }
    o = (cUIObj_245730*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(ctrlPro));
    if (o != 0) {
        o->setVisible(r != 0);
    }
    o = (cUIObj_245730*)cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_0047BD18));
    if (o != 0) {
        o->setVisible(r != 0);
    }
}

//100%
void cGameLoadStateConquer_OnWidgetCreated(void* self)
{
}

//100%
extern char D_004A2BC8[];
extern char D_004A2BD0[];
extern char* D_004A5B64;
extern "C" void func_002C27C0(char* dst, const char* fmt, ...);
extern "C" void func_003A0E90(void* text, void* p);

extern "C" int cGameLoadStateConquer_TransitionIn(void* self)
{
    void* obj = cUIScreen_getObjectByHashName(*(void**)((char*)self + 0x40), GetHashValue32(D_004A2BC8));
    if (obj != 0) {
        char buf[0xD0];
        func_002C27C0(buf, D_004A2BD0, (int)*(float*)(D_004A5B64 + 0x38));
        func_003A0E90(obj, buf);
    }
    return 0;
}

//100%
extern void* D_0047C6D8[];
extern "C" void* func_0039E390(void* self);

extern "C" void* cFELoadHintState_dtor(void* self)
{
    *(void**)((char*)self + 0x8) = D_0047C6D8;
    return func_0039E390(self);
}

