#include "common.h"

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" int get_float_2510(unsigned char **pp, float *out) __asm__("get_float");
extern "C" int get_float_2510(unsigned char **pp, float *out) {
    unsigned char *p = *pp;
    union { unsigned int u; float f; } x;
    x.u = (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
    *out = x.f;
    *pp += 4;
    return 4;
}

//100%
extern "C" int get_uint(unsigned char **pp, unsigned int *out) {
    unsigned char *p = *pp;
    *out = (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
    *pp += 4;
    return 4;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct t3Vector_25A0 { float x, y, z; };
extern "C" int get_float_25A0(void*, void*) __asm__("get_float");
extern "C" int get_t3Vector(void *src, t3Vector_25A0 *out) {
    t3Vector_25A0 v;
    int total = 0;
    int i;
    float *p = &v.x;
    for (i = 0; i < 3; i++) {
        total += get_float_25A0(src, p);
        p++;
    }
    *out = v;
    return total;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int get_float(int, int);

extern "C" int func_002D2628(int arg0, int arg1) {
    int temp_2;
    int var_16;
    int var_17;
    int var_18;

    var_16 = arg1;
    var_17 = 3;
    var_18 = 0;
    do {
        temp_2 = get_float(arg0, var_16);
        var_16 += 4;
        var_17 -= 1;
        var_18 += temp_2;
    } while (var_17 >= 0);
    return var_18;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int get_float(int, int);

extern "C" int func_002D2690(int arg0, int arg1) {
    int temp_2;
    int var_16;
    int var_17;
    int var_18;

    var_16 = arg1;
    var_17 = 0xF;
    var_18 = 0;
    do {
        temp_2 = get_float(arg0, var_16);
        var_16 += 4;
        var_17 -= 1;
        var_18 += temp_2;
    } while (var_17 >= 0);
    return var_18;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
struct V4_26F8 { float x, y, z, w; } __attribute__((aligned(16)));
extern "C" int get_float_26F8(void*, void*) __asm__("get_float");
extern "C" int func_002D26F8(void *src, V4_26F8 *out) {
    float a, b, c, d;
    V4_26F8 v;
    int total;
    total = get_float_26F8(src, &a);
    total += get_float_26F8(src, &b);
    total += get_float_26F8(src, &c);
    total += get_float_26F8(src, &d);
    v.w = a;
    v.x = b;
    v.y = c;
    v.z = d;
    *out = v;
    return total;
}

//100%
extern "C" int func_002D2790(unsigned char **arg0, unsigned char *arg1) {
    *arg1 = **arg0;
    *arg0 += 1;
    return 1;
}

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag_27B0(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" int func_002D2790_27B0(unsigned char **, unsigned char *) __asm__("func_002D2790");
extern "C" char *strcpy(char *, const char *);
extern char D_004D49B8[];
extern char D_00486768[];
extern "C" int get_string(unsigned char **src, char **out) {
    int n = 0;
    char c = 1;
    do {
        n += func_002D2790_27B0(src, (unsigned char*)&c);
        D_004D49B8[n - 1] = c;
    } while (c != 0 && n < 1000);
    if (n == 1000) D_004D49B8[999] = 0;
    char *p = (char*)operator_new_tag_27B0(n, D_00486768, 0x100, 0);
    *out = p;
    strcpy(p, D_004D49B8);
    return n;
}

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag_2868(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" void* cMemMan_alloc_2868(int, const char*, int, int) __asm__("cMemMan_alloc");
extern "C" int func_002D2790_2868(unsigned char **, unsigned char *) __asm__("func_002D2790");
extern "C" int get_uint_2868(unsigned char **, void *) __asm__("get_uint");
extern char D_00486778[];
extern char D_00486788[];
struct Data_2868 { unsigned int n; unsigned char *data; };
extern "C" int get_data(unsigned char **src, Data_2868 **out) {
    unsigned int i = 0;
    Data_2868 *d = (Data_2868*)cMemMan_alloc_2868(8, D_00486778, 0x100, 0);
    d->n = 0;
    d->data = 0;
    *out = d;
    int total = get_uint_2868(src, d);
    Data_2868 *e = *out;
    e->data = (unsigned char*)operator_new_tag_2868(e->n, D_00486788, 0x100, 0);
    Data_2868 *t = *out;
    for (i = 0; i < t->n; i++) {
        total += func_002D2790_2868(src, t->data + i);
        t = *out;
    }
    return total;
}

//100%
extern "C" int func_002D2948(int self, ...) {
    return self;
}

INCLUDE_ASM("seg/seg_1D3510", func_002D2988);

//100%
void operator_delete(int *);
extern void* D_004871E8[];
extern "C" void func_002D3788(void ***self, int flags) {
    *self = D_004871E8;
    if (flags & 1) operator_delete((int*)self);
}

//100%
extern "C" int func_002D37B8(void) {
    return 1;
}

extern "C" void func_002D37C0(void) {
}

extern "C" void func_002D37C8(void) {
}

//100%
extern "C" int func_002D37D0(void) {
    return 0;
}

//100%
extern "C" int func_002D37D8(void *arg0) {
    return (*(int *)((char*)(arg0) + (0xC)));
}

//100%
struct VEnt_37E0 { short delta; short idx; int (*fn)(void*, int); };
extern "C" void cPS2MemCard_v49(void *arg0) {
    VEnt_37E0 *e = (VEnt_37E0*)(*(char **)arg0 + 0x180);
    e->fn((char*)arg0 + e->delta, *(int *)((char*)arg0 + 0xC));
}

//100%
struct VEnt_3810 { short delta; short idx; int (*fn)(void*, int); };
extern "C" void cPS2MemCard_v53(void *arg0) {
    VEnt_3810 *e = (VEnt_3810*)(*(char **)arg0 + 0x1A0);
    e->fn((char*)arg0 + e->delta, *(int *)((char*)arg0 + 0xC));
}

//100%
struct Obj_3840 {
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
  virtual int v48();
  virtual void v49();
  virtual int v50(int);
  virtual void v51();
  virtual int v52(int);
  virtual void v53();
  virtual void v54();
  virtual void v55();
  virtual int v56(int);
};
extern "C" int cPS2MemCard_v54(Obj_3840 *o, int x) {
    int ok = 0;
    if (!o->v48() && !o->v50(x) && o->v56(x)) {
        ok = o->v52(x) != 0;
    }
    return ok;
}

//100%
struct VEnt_38F0 { short delta; short idx; int (*fn)(void*, int); };
extern "C" void cPS2MemCard_v55(void *arg0) {
    VEnt_38F0 *e = (VEnt_38F0*)(*(char **)arg0 + 0x1C0);
    e->fn((char*)arg0 + e->delta, *(int *)((char*)arg0 + 0xC));
}

//100%
extern "C" int func_002D3920(void) {
    return 0;
}

//100%
extern "C" int func_002D3928(void) {
    return 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_002C53C8_3930(void*, int) __asm__("func_002C53C8");
extern "C" void cPS2MemCard_v63(void *arg0) {
    func_002C53C8_3930(arg0, (*(int *)((char*)(arg0) + (0xC))));
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_002C53E0_3950(void*, int, int) __asm__("func_002C53E0");
extern "C" void cPS2MemCard_v64(void *arg0, int arg1) {
    func_002C53E0_3950(arg0, (*(int *)((char*)(arg0) + (0xC))), arg1);
}

//100%
extern "C" int func_002D3970(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x14)));
}

//100%
extern "C" int func_002D3978(void) {
    return 2;
}

//100%
struct VEnt_3980 { short delta; short idx; void (*fn)(void*, int, int, int); };
extern "C" void cPS2MemCard_v71(void *arg0, int a1, int a2, int a3) {
    VEnt_3980 *e = (VEnt_3980*)(*(char **)arg0 + 0x230);
    e->fn((char*)arg0 + e->delta, a1, a2, a3);
}

//100%
extern "C" int func_002D39A8(void) {
    return 0;
}

//100%
extern "C" int func_002D39B0(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x3C)));
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void func_002C51D0_39B8(void*, int) __asm__("func_002C51D0");
extern "C" void func_002D39B8(void *arg0) {
    func_002C51D0_39B8(arg0, (*(int *)((char*)(arg0) + (0xC))));
}

//100%
extern "C" int func_002D39D8(void *arg0) {
    return (*(int *)((char*)(arg0) + (4)));
}

extern "C" void func_002D39E0(void) {
}

//100%
extern "C" int func_002D39E8(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x54)));
}

//100%
extern int D_004A3940;

extern "C" int func_002D39F0(void) {
    return D_004A3940;
}

extern "C" void func_002D39F8(void) {
}

//100%
extern "C" void func_002D3A00(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (8))) = arg1;
}

//100%
extern "C" int func_002D3A08(void *arg0) {
    return (*(int *)((char*)(arg0) + (8)));
}

//100%
extern "C" void func_002D3A10(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0xC))) = arg1;
}

//100%
extern "C" int func_002D3A18(void *arg0) {
    return (*(int *)((char*)(arg0) + (0xC)));
}

//100%
extern "C" int func_002D3A20(int *arg0) {
    return *arg0;
}

//100%
extern "C" int func_002D3A28(char *arg0, int arg1) {
    return *(int *)(arg0 + (arg1 << 2) + 0xC);
}

//100%
extern "C" int func_002D3A38(int *arg0) {
    return *arg0;
}

//100%
extern "C" int func_002D3A40(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x124)));
}

//100%
extern "C" int func_002D3A48(void *arg0) {
    return (*(int *)((char*)((*(void **)((char*)(arg0) + (0x124)))) + (0x58)));
}

//100%
extern "C" int func_002D3A58(void **arg0) {
    return (*(int *)((char*)((*(void **)((char*)(*arg0) + (0x124)))) + (0x58)));
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3A68(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3A88(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x20))) = arg1;
}

//100%
extern "C" void func_002D3A90(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3A98(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3AB8(void *arg0, int arg1, int arg2) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
    (*(int *)((char*)(arg0) + (0x1C))) = arg2;
}

//100%
extern "C" void func_002D3AC8(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x20))) = arg1;
}

//100%
extern "C" void func_002D3AD0(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" int func_002D3AD8(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x14)));
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3AE0(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3B00(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
extern "C" int func_002D3B08(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x18)));
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3B10(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3B30(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3B38(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3B58(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
extern "C" void func_002D3B60(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" int func_002D3B68(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x14)));
}

//100%
extern "C" void func_002D3B70(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x20))) = arg1;
}

//100%
extern "C" int func_002D3B78(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x20)));
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3B80(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3BA0(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" int func_002D3BA8(void *arg0) {
    return (*(int *)((char*)(arg0) + (0x14)));
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3BB0(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3BD0(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" void func_002D3BD8(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3BE0(void) {
    func_002CA280();
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3C00(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3C20(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
extern "C" void func_002D3C28(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3C30(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3C50(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
extern "C" void func_002D3C58(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3C60(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3C80(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
extern "C" void func_002D3C88(void *arg0, float fparg0, float fparg1) {
    (*(float *)((char*)(arg0) + (0x1C))) = fparg0;
    (*(float *)((char*)(arg0) + (0x20))) = fparg1;
}

//100%
extern "C" void func_002D3C98(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" void func_002D3CA0(void *arg0, float fparg0, float fparg1) {
    (*(float *)((char*)(arg0) + (0x24))) = fparg0;
    (*(float *)((char*)(arg0) + (0x28))) = fparg1;
}

//100%
extern "C" void func_002D3CB0(void *arg0, float fparg0) {
    *(*(float **)((char*)(arg0) + (0x18))) = fparg0;
}

//100%
extern "C" float func_002D3CC0(void *arg0) {
    return ((*(float *)((char*)(arg0) + (0x24))) * *(*(float **)((char*)(arg0) + (0x18)))) + (*(float *)((char*)(arg0) + (0x28)));
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3CE0(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3D00(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
extern "C" void func_002D3D08(void *arg0, float fparg0, float fparg1) {
    (*(float *)((char*)(arg0) + (0x1C))) = fparg0;
    (*(float *)((char*)(arg0) + (0x20))) = fparg1;
}

//100%
extern "C" void func_002D3D18(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3D20(void) {
    func_002CA280();
}

//100%
extern "C" int func_002D3D40(int arg0) {
    return arg0 + 0x18;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" int func_00416958_3D48(char*, int, int) __asm__("func_00416958");
extern "C" int func_002D3D48(char *arg0, int arg1) {
    char *p = arg0 + 0x18;
    *p = 0;
    return func_00416958_3D48(p, arg1, 0xF);
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3D70(void) {
    func_002CA280();
}

//100%
extern "C" void func_002CAA80();

extern "C" void func_002D3D90(void) {
    func_002CAA80();
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern void func_002CA280_3DB0(int, int) __asm__("func_002CA280");
extern "C" void func_002CAA80(int, int);

extern "C" void func_002D3DB0(int arg0, int arg1) {
    func_002CAA80(arg0 + 0x18, 2);
    func_002CA280_3DB0(arg0, arg1);
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3DF8(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3E18(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern void func_002CA280_3E20(int, int) __asm__("func_002CA280");
extern "C" void func_002CAA80(int, int);

extern "C" void func_002D3E20(int arg0, int arg1) {
    func_002CA280_3E20(arg0 + 0x640, 2);
    func_002CA280_3E20(arg0 + 0x61C, 2);
    func_002CA280_3E20(arg0 + 0x5F8, 2);
    func_002CA280_3E20(arg0 + 0x5D4, 2);
    func_002CA280_3E20(arg0 + 0x5B0, 2);
    func_002CAA80(arg0 + 0x18, 2);
    func_002CA280_3E20(arg0, arg1);
}

//100%
extern "C" void func_002D3EA0(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x658))) = arg1;
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3EA8(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3EC8(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x18))) = arg1;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern void func_002CA280_3ED0(int, int) __asm__("func_002CA280");
extern "C" void func_002CAA80(int, int);

extern "C" void func_002D3ED0(int arg0, int arg1) {
    func_002CA280_3ED0(arg0 + 0x654, 2);
    func_002CA280_3ED0(arg0 + 0x620, 2);
    func_002CA280_3ED0(arg0 + 0x5EC, 2);
    func_002CA280_3ED0(arg0 + 0x5B8, 2);
    func_002CAA80(arg0 + 0x18, 2);
    func_002CA280_3ED0(arg0, arg1);
}

//100%
extern "C" void func_002D3F48(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x66C))) = arg1;
}

//100%
extern "C" void func_002CA280();

extern "C" void func_002D3F50(void) {
    func_002CA280();
}

//100%
extern "C" void func_002D3F70(void *arg0, int arg1) {
    (*(int *)((char*)(arg0) + (0x14))) = arg1;
}

//100%
extern "C" void func_002CA280(int, int);
extern "C" void func_002CAA80(int, int);

extern "C" void func_002D3F78(int arg0, int arg1) {
    func_002CA280(arg0 + 0x164, 2);
    func_002CA280(arg0 + 0x14C, 2);
    func_002CA280(arg0 + 0x130, 2);
    func_002CAA80(arg0, arg1);
}

//100%
void operator_delete(int *);
extern void* D_00487480[];
extern "C" void cPS2ConsoleConfig_v01(char *self, int flags) {
    *(void***)(self + 0x34) = D_00487480;
    if (flags & 1) operator_delete((int*)self);
}

//100%
extern int (*D_004A54BC)(int, int);

extern "C" void func_002D4008(int *arg0, int *arg1) {
    D_004A54BC(*arg0, *arg1);
}

//100%
void operator_delete(int *);
extern void* D_00487480[];
extern "C" void func_002D4030(char *self, int flags) {
    *(void***)(self + 0x34) = D_00487480;
    if (flags & 1) operator_delete((int*)self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002D2988(int, int);

extern "C" void func_002D4060(void) {
    func_002D2988(1, 0xFFFF);
}

//100%
extern "C" int func_002D4080(int self, ...) {
    return self;
}

INCLUDE_ASM("seg/seg_1D3510", func_002D40C0);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void func_002D40C0(int, int);

extern "C" void func_002D48D0(void) {
    func_002D40C0(1, 0xFFFF);
}
