#include "common.h"

INCLUDE_ASM("scripter/all_in_one_scripter", __sti__all_in_one_scripter_cpp);

extern "C" void func_002847A8(void) {
}

extern "C" void DataInstanceMan_OnDataRemoved(void) {
}

extern "C" void DataInstanceMan_v04(void) {
}

extern "C" void DataInstanceMan_v05(void) {
}

//100%
extern "C" int func_002847C8(int *arg0) {
    return *arg0;
}

//100%
extern "C" int func_002847D0(void *arg0) {
    return (*(int *)((char*)(arg0) + (4)));
}

//100%
extern "C" int func_002847D8(void *arg0) {
    return (*(int *)((char*)(arg0) + (8))) > 0;
}

extern "C" void ScriptEngine_SeqListenerOnAdvance(void) {
}

extern "C" void ScriptEngine_SeqListenerOnEnd(void) {
}

//100%
extern "C" int func_002847F8(void) {
    return 1;
}

extern "C" void ScriptEngine_SeqListener_v07(void) {
}

extern "C" void ScriptEngine_SeqListener_v08(void) {
}

//100%
extern "C" int ScriptEngine_SeqListener_v11(void) {
    return 1;
}

//100%
extern "C" int func_00284818(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x2B4)));
}

//100%
extern "C" int func_00284820(void) {
    return 0;
}

extern "C" void ScriptEngine_ScriptDbCancelBank(void) {
}

extern "C" void ScriptEngine_ScriptDbUnloadBank(void) {
}

extern "C" void ScriptEngine_ScriptDb_v10(void) {
}

extern "C" void ScriptEngine_ScriptDb_v11(void) {
}

extern "C" void ScriptEngine_ScriptDb_v12(void) {
}

//100%
extern "C" int func_00284850(void *arg0) {
    return (*(int *)((char*)(arg0) + (8)));
}

//100%
extern "C" int func_00284858(void *arg0) {
    return (*(int *)((char*)(arg0) + (4)));
}

//100%
extern "C" void func_00284860(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (4))) = arg1;
}

//100%
extern "C" void func_00284868(void *arg0) {
    (*(int *)((char*)(arg0) + (4))) = -1;
}

extern "C" void ScriptBinding_Apply(void) {
}

extern "C" void ScriptBinding_Tick(void) {
}

//100%
extern "C" int ScriptBinding_AcceptCommand(void) {
    return 1;
}

//100%
extern "C" void func_00284890(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x10))) = arg1;
}

//100%
extern "C" int func_00284898(void *arg0) {
    return (*(int *)((char*)(arg0) + (0xC)));
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_00283228_48A0(void *) __asm__("func_00283228");
extern char D_00482360[];
extern char D_00482398[];

extern "C" void ScriptViewObj_dtor(void *arg0) {
    *(char **)((char*)arg0 + 0x10) = D_00482360;
    *(char **)((char*)arg0 + 0xC) = D_00482398;
    func_00283228_48A0(arg0);
}

//100%
extern "C" int func_002848D0(void *arg0) {
    return (*(int *)((char*)(arg0) + (0xF8)));
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_00283228_48D8(void *, int) __asm__("func_00283228");
void operator_delete(int *);
extern char D_004822E0[];
extern char D_00482318[];

extern "C" void ScriptDummyObj_dtor(void *arg0, int arg1) {
    *(char **)((char*)arg0 + 0x18) = D_00482318;
    *(char **)((char*)arg0 + 0x0) = D_004822E0;
    func_00283228_48D8((char*)arg0 + 0xC, 0);
    if (arg1 & 1) {
        operator_delete((int *)arg0);
    }
}

//100%
extern "C" int ScriptDummyObj_GetBindingCount(void) {
    return 1;
}

//100%
extern "C" int func_00284948(int arg0) {
    return arg0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_00283228_4950(void *, int) __asm__("func_00283228");
void operator_delete(int *);
extern char D_00482260[];
extern char D_00482298[];

extern "C" void ScriptAudioObj_dtor(void *arg0, int arg1) {
    *(char **)((char*)arg0 + 0x18) = D_00482298;
    *(char **)((char*)arg0 + 0x0) = D_00482260;
    func_00283228_4950((char*)arg0 + 0xC, 0);
    if (arg1 & 1) {
        operator_delete((int *)arg0);
    }
}

//100%
extern "C" int ScriptAudioObj_GetBindingCount(void) {
    return 1;
}

//100%
extern "C" int ScriptAudioObj_GetBinding(int arg0) {
    return arg0;
}

//100%
extern "C" int func_002849C8(int *arg0) {
    return *arg0 != 0;
}

//100%
extern "C" int func_002849D8(void *arg0) {
    return (*(int *)((char*)(arg0) + (4)));
}

//100%
extern "C" int func_002849E0(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x550))) != 2;
}

//100%
extern "C" int func_002849F0(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x550)));
}

struct sE_49F8 { int a; int b; int c; int d; };
struct sS_49F8 { char pad[0x628]; sE_49F8 e[8]; };
extern "C" int func_002849F8(sS_49F8* self, int i)
{
    int r = 0;
    if (self->e[i].c == 0) {
        r = self->e[i].a == 0;
    }
    return r;
}

//100%
extern "C" void func_00283228();

extern "C" void func_00284A28(void) {
    func_00283228();
}

//100%
extern "C" int func_00284A48(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x14)));
}

//100%
extern "C" float func_00284A50(void *arg0) {
    return (*(float *)((char*)(arg0) + (0x18)));
}

//100%
extern "C" int func_00284A58(int arg0) {
    return arg0 + 0x30;
}

//100%
extern "C" float func_00284A60(void *arg0) {
    return (*(float *)((char*)(arg0) + (0x70)));
}

//100%
extern "C" float func_00284A68(void *arg0) {
    return (*(float *)((char*)(arg0) + (0x74)));
}

//100%
extern "C" float func_00284A70(void *arg0) {
    return (*(float *)((char*)(arg0) + (0x78)));
}

//100%
extern "C" int func_00284A78(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x7C)));
}

//100%
extern "C" int func_00284A80(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x10)));
}

//100%
extern "C" int ScriptObjCam_GetBindingCount(void) {
    return 0;
}

//100%
extern "C" int ScriptObjCam_GetBinding(void) {
    return 0;
}

//100%
extern "C" void func_00284A98(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x1C))) = arg1;
}

//100%
extern "C" int func_00284AA0(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x1C)));
}

//100%
extern "C" void func_00283228();

extern "C" void func_00284AA8(void) {
    func_00283228();
}

//100%
extern "C" int func_00284AC8(int arg0) {
    return arg0 + 0x18;
}

//100%
extern "C" int func_00284AD0(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x10)));
}

//100%
extern "C" int cTransitionMan_ScriptGetBindingCount(void) {
    return 0;
}

//100%
extern "C" int cTransitionMan_ScriptGetBinding(void) {
    return 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_00283228_4AE8(void *, int) __asm__("func_00283228");
void operator_delete(int *);
extern char D_00481FD8[];
extern char D_00482018[];

extern "C" void RiderScriptObj_dtor(void *arg0, int arg1) {
    *(char **)((char*)arg0 + 0x18) = D_00482018;
    *(char **)((char*)arg0 + 0x0) = D_00481FD8;
    func_00283228_4AE8((char*)arg0 + 0xC, 0);
    if (arg1 & 1) {
        operator_delete((int *)arg0);
    }
}

//100%
extern "C" int RiderScriptObj_GetBindingCount(void) {
    return 1;
}

//100%
extern "C" int RiderScriptObj_GetBinding(int arg0) {
    return arg0;
}

//100%
extern "C" int func_00284B60(int arg0) {
    return arg0 + 0x30;
}

//100%
extern "C" float func_00284B68(void *arg0) {
    return (*(float *)((char*)(arg0) + (0x70)));
}

//100%
extern "C" float func_00284B70(void *arg0) {
    return (*(float *)((char*)(arg0) + (0x74)));
}

//100%
extern "C" float func_00284B78(void *arg0) {
    return (*(float *)((char*)(arg0) + (0x78)));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void __sti__all_in_one_scripter_cpp(int, int);

extern "C" void ScriptEngine_GlobalCtors(void) {
    __sti__all_in_one_scripter_cpp(1, 0xFFFF);
}

//100%
extern "C" int func_00284BA0(int arg0) {
    return (arg0 != 0) ? 0 : 0x173;
}
