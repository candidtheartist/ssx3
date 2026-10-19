#include "common.h"

//100%
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void func_003E6574(void*, void*, int);
extern "C" void func_003B47F8(void* src, void* dst);
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern const char D_0048A5D0[];

struct sMdfPart_00314CB0
{
    char name[0x10];
    int dataOffset;
    int dataSize;
    char pad_0x18[0x48];
};

struct sMdfArchive_00314CB0
{
    int f0;
    int f4;
    sMdfPart_00314CB0* parts;
    char* data;
};

extern "C" void* cMdfArchive_getModelPartByIndex(sMdfArchive_00314CB0* self, int i)
{
    char name[0x40];
    sprintf(name, D_0048A5D0, &self->parts[i]);
    char* p = (char*)operator_new_tag(self->parts[i].dataSize + 0x60, name, 0x3000000, 0);
    func_003E6574(p, &self->parts[i], 0x60);
    if (self->parts[i].dataSize)
    {
        func_003B47F8(self->data + self->parts[i].dataOffset, p + 0x60);
    }
    return p;
}

//100%
extern unsigned int* D_004A3E78;

extern "C" int cGameAnimMap_compareHash(int* a, int* b)
{
    return D_004A3E78[*a] < D_004A3E78[*b] ? -1 : 1;
}

INCLUDE_ASM("animation/mdfarchive", cGameAnimMap_cGameAnimMap);

//100%
// Destructor: clears the current-archive global at D_004A3E7C, then frees self when flags bit 0 is set.
extern int D_004A3E7C;
void operator_delete(int* p);

extern "C" void cGameAnimMap__cGameAnimMap(int* self, int flags)
{
    D_004A3E7C = 0;
    if (flags & 1)
        operator_delete(self);
}

//100%
int GetHashValue32(char* str);
extern char* D_0048CFC0[];
extern unsigned int* D_004A3E78;
extern "C" int cGameAnimMap_compareHash(int* a, int* b);
extern "C" void func_00418EF8(void* base, int n, int size, int (*cmp)(int*, int*));
extern "C" void* func_00416210(void* dst, int c, int n);

struct sMdfHashTable_00314DD8
{
    unsigned int hash[0x206];
    int order[0x206];
    char map[0x818];
};

extern "C" void cGameAnimMap_init(sMdfHashTable_00314DD8* self)
{
    for (int i = 0; i < 0x206; i++)
    {
        int h = GetHashValue32(D_0048CFC0[i]);
        self->order[i] = i;
        self->hash[i] = h;
    }
    D_004A3E78 = self->hash;
    func_00418EF8(self->order, 0x206, 4, cGameAnimMap_compareHash);
    D_004A3E78 = 0;
    func_00416210(self->map, -1, 0x818);
}

//100%
struct sMdfIndex_00314E88
{
    unsigned int hashes[0x206]; // 0x000: sorted by order[]
    int order[0x206];           // 0x818
};

// Binary search for `hash`; returns its entry index, or -1.
extern "C" int cGameAnimMap_findAnim(sMdfIndex_00314E88* self, unsigned int hash)
{
    int lo = 0;
    int hi = 0x206;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        int idx = self->order[mid];
        unsigned int h = self->hashes[idx];
        if (hash == h)
        {
            return idx;
        }
        if (hash < h)
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return -1;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cGameAnimMap_setClip(sMdfIndex_00314E88* self, unsigned int hash, void* value)
{
    int i = cGameAnimMap_findAnim(self, hash);
    if (i >= 0)
    {
        ((void**)((char*)self + 0x1030))[i] = value;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sMdfHandle_00314F30
{
    unsigned int kind : 8;
    unsigned int index : 24;
};

static inline void SetKind_00314F30(sMdfHandle_00314F30* h, int v) { h->kind = v; }
static inline void SetIndex_00314F30(sMdfHandle_00314F30* h, int v) { h->index = v; }

// PORT: cGameAnimMap_setClip's value slot receives the handle struct by value here.
void cGameAnimMap_setClip_handle(sMdfIndex_00314E88* self, unsigned int hash, sMdfHandle_00314F30 value) __asm__("cGameAnimMap_setClip");

extern "C" void cGameAnimMap_addBank(sMdfIndex_00314E88* self, int kind, char* list)
{
    sMdfHandle_00314F30 h;
    for (int i = 0; i < *(short*)(*(char**)(list + 4) + 2); i++)
    {
        SetKind_00314F30(&h, kind);
        SetIndex_00314F30(&h, i);
        cGameAnimMap_setClip_handle(self, *(unsigned int*)(i * 0x14 + *(int*)(list + 8)), h);
    }
}

//100%
extern void* D_004A5950;

extern "C" void cGameAnimMap_removeBank(sMdfIndex_00314E88* self, char* list)
{
    for (int i = 0; i < *(short*)(*(char**)(list + 4) + 2); i++)
    {
        cGameAnimMap_setClip(self, *(unsigned int*)(i * 0x14 + *(int*)(list + 8)), D_004A5950);
    }
}


//100%
// Finds key among the 0x206 hashes at 0x1030 and returns the matching name from D_0048CFC0, or D_0048A4C0.
extern char D_0048A4C0[];

extern "C" char* cGameAnimMap_getAnimName(char* self, int key)
{
    int* hashes = (int*)(self + 0x1030);
    for (int i = 0; i < 0x206; i++)
    {
        if (key == hashes[i])
            return D_0048CFC0[i];
    }
    return D_0048A4C0;
}
