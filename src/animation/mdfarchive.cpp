#include "common.h"
#include "animation/mdfarchive.h"
#include "animation/gameanimmap.h"

//100%
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void func_003E6574(void*, void*, int);
extern "C" void func_003B47F8(void* src, void* dst);
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern const char D_0048A5D0[];

extern "C" void* cMdfArchive_getModelPartByIndex(cMdfArchive* self, int i)
{
    char name[0x40];
    sprintf(name, D_0048A5D0, &self->mParts[i]);
    char* p = (char*)operator_new_tag(self->mParts[i].mDataSize + 0x60, name, 0x3000000, 0);
    func_003E6574(p, &self->mParts[i], 0x60);
    if (self->mParts[i].mDataSize)
    {
        func_003B47F8(self->mData + self->mParts[i].mDataOffset, p + 0x60);
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
// Destructor: clears the map singleton D_004A3E7C, then frees self when flags bit 0 is set.
extern int D_004A3E7C;
void operator_delete(int* p);

extern "C" void cGameAnimMap__cGameAnimMap(cGameAnimMap* self, int flags)
{
    D_004A3E7C = 0;
    if (flags & 1)
        operator_delete((int*)self);
}

//100%
int GetHashValue32(char* str);
extern char* D_0048CFC0[];
extern unsigned int* D_004A3E78;
extern "C" int cGameAnimMap_compareHash(int* a, int* b);
extern "C" void func_00418EF8(void* base, int n, int size, int (*cmp)(int*, int*));
extern "C" void* func_00416210(void* dst, int c, int n);

extern "C" void cGameAnimMap_init(cGameAnimMap* self)
{
    for (int i = 0; i < 0x206; i++)
    {
        int h = GetHashValue32(D_0048CFC0[i]);
        self->mSortedOrder[i] = i;
        self->mNameHashes[i] = h;
    }
    D_004A3E78 = self->mNameHashes;
    func_00418EF8(self->mSortedOrder, 0x206, 4, cGameAnimMap_compareHash);
    D_004A3E78 = 0;
    func_00416210(self->mClips, -1, 0x818);
}

//100%
// Binary search for `hash`; returns its entry index, or -1.
extern "C" int cGameAnimMap_findAnim(cGameAnimMap* self, unsigned int hash)
{
    int lo = 0;
    int hi = 0x206;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        int idx = self->mSortedOrder[mid];
        unsigned int h = self->mNameHashes[idx];
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
extern "C" void cGameAnimMap_setClip(cGameAnimMap* self, unsigned int hash, void* value)
{
    int i = cGameAnimMap_findAnim(self, hash);
    if (i >= 0)
    {
        *(void**)&self->mClips[i] = value;
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
void cGameAnimMap_setClip_handle(cGameAnimMap* self, unsigned int hash, sMdfHandle_00314F30 value) __asm__("cGameAnimMap_setClip");

extern "C" void cGameAnimMap_addBank(cGameAnimMap* self, int kind, char* list)
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

extern "C" void cGameAnimMap_removeBank(cGameAnimMap* self, char* list)
{
    for (int i = 0; i < *(short*)(*(char**)(list + 4) + 2); i++)
    {
        cGameAnimMap_setClip(self, *(unsigned int*)(i * 0x14 + *(int*)(list + 8)), D_004A5950);
    }
}


//100%
// Finds the id whose clip handle is key and returns its name from D_0048CFC0, or D_0048A4C0.
extern char D_0048A4C0[];

extern "C" char* cGameAnimMap_getAnimName(cGameAnimMap* self, int key)
{
    int* hashes = self->mClips;
    for (int i = 0; i < 0x206; i++)
    {
        if (key == hashes[i])
            return D_0048CFC0[i];
    }
    return D_0048A4C0;
}
