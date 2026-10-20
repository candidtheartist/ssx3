#include "common.h"
#include "intersect/aifwddiff.h"
#include "intersect/spheretree.h"
#include "intersect/riderspheretree.h"
#include "intersect/spacehash.h"

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" void cAIFwdDiffEntry_cAIFwdDiffEntry(void* self);
extern char D_0048E4F8[];
extern char D_0048E508[];


extern "C" void cAIFwdDiffCache_Init(cAIFwdDiffCache* self, int n)
{
    cAIFwdDiffEntry* mem = (cAIFwdDiffEntry*)operator_new_tag(n * sizeof(cAIFwdDiffEntry), D_0048E4F8, 0, 0);
    cAIFwdDiffEntry* p = mem;
    for (int k = n - 1; k != -1; k--, p++) {
        cAIFwdDiffEntry_cAIFwdDiffEntry(p);
    }
    self->mEntries = mem;
    for (int i = 0; i < n; i++) {
        self->mEntries[i].mLruNext = &self->mEntries[i] + 1;
        self->mEntries[i].mLruPrev = &self->mEntries[i] - 1;
        self->mEntries[i].mKey = 0xFFFFFFFF;
    }
    self->mEntries[0].mLruPrev = self->mEntries + n - 1;
    self->mEntries[n - 1].mLruNext = self->mEntries;
    self->mBucketCount = n * 2 + 13;
    self->mLru = self->mEntries;
    self->mBuckets = (cAIFwdDiffEntry**)operator_new_tag(self->mBucketCount * 4, D_0048E508, 0x80000000, 0);
}

//100%
extern "C" void cAIFwdDiffCache_touch(cAIFwdDiffCache* list, cAIFwdDiffEntry* n);
extern "C" void cAIFwdDiffCache_unhash(void* self, void* node);
extern "C" void cAIFwdDiffCache_hash(cAIFwdDiffCache* table, cAIFwdDiffEntry* node);
extern "C" void cAIFwdDiffCache_evaluatePatch(void* self, void* src, void* node);



static inline int cAIFwdDiffCache_lookup_less(unsigned int a, unsigned int b) { return a < b; }

extern "C" void cAIFwdDiffCache_lookup(cAIFwdDiffCache* self, void* src, cAIFwdDiffEntry** out)
{
    unsigned int key = *(unsigned int*)((char*)src + 0x150);
    cAIFwdDiffEntry* n = self->mBuckets[key % self->mBucketCount];
    while (n != 0 && !cAIFwdDiffCache_lookup_less(key, n->mKey)) {
        if (n->mKey == key) {
            cAIFwdDiffCache_touch(self, n);
            *out = n;
            return;
        }
        n = n->mHashNext;
    }
    n = self->mLru;
    cAIFwdDiffCache_unhash(self, n);
    n->mKey = key;
    cAIFwdDiffCache_hash(self, n);
    self->mLru = n->mLruNext;
    cAIFwdDiffCache_evaluatePatch(self, src, n);
    *out = n;
}

//100%


extern "C" void cAIFwdDiffCache_touch(cAIFwdDiffCache* list, cAIFwdDiffEntry* n)
{
    if (list->mLru == n) {
        list->mLru = n->mLruNext;
        return;
    }
    if (list->mLru->mLruPrev == n) {
        return;
    }
    n->mLruPrev->mLruNext = n->mLruNext;
    n->mLruNext->mLruPrev = n->mLruPrev;
    n->mLruPrev = list->mLru->mLruPrev;
    n->mLruNext = list->mLru;
    list->mLru->mLruPrev->mLruNext = n;
    list->mLru->mLruPrev = n;
}

INCLUDE_ASM("intersect/aifwddiff", cAIFwdDiffCache_unhash);

//100%


extern "C" void cAIFwdDiffCache_hash(cAIFwdDiffCache* table, cAIFwdDiffEntry* node)
{
    unsigned int key = node->mKey;
    cAIFwdDiffEntry** link = &table->mBuckets[key % table->mBucketCount];
    for (;;) {
        cAIFwdDiffEntry* cur = *link;
        if (cur == 0 || key < cur->mKey) {
            *link = node;
            node->mHashNext = cur;
            return;
        }
        link = &cur->mHashNext;
    }
}

//100%
extern "C" void func_00391418(void* t, void* a);
extern "C" void cAIFwdDiffCache_resetCells(void* self, void* a);
extern "C" void func_003914F8(void* t);
extern "C" void func_00391480(void* t, void* a);
struct sGp2930 { int a, b; };
extern sGp2930 D_004A5A20; // placeholder: target is a raw $gp+0x2930 reference

extern "C" void cAIFwdDiffCache_evaluatePatch(void* self, void* a1, void* a2)
{
    sGp2930* t = &D_004A5A20;
    func_00391418(t, (char*)a1 + 0x40);
    cAIFwdDiffCache_resetCells(self, a2);
    func_003914F8(t);
    func_00391480(t, ((cAIFwdDiffEntry*)a2)->mGrid);
}

//100%
extern "C" void cAIFwdDiffCache_resetCells(void* self, void* a)
{
    cAIFwdDiffEntry* e = (cAIFwdDiffEntry*)a;
    float* p = (float*)e->mCells;
    int n = 0x50;
    do {
        p[0] = 10000000000.0f;
        p[4] = 10000000000.0f;
        p[8] = 10000000000.0f;
        p += 16;
    } while (n-- > 0);
    p = (float*)e->mRow;
    n = 8;
    do {
        p[0] = 10000000000.0f;
        p[4] = 10000000000.0f;
        p[8] = 10000000000.0f;
        p += 16;
    } while (n-- > 0);
}

//100%
extern "C" cSphereTree* cSphereTree_assign(cSphereTree* self, cSphereTree* src)
{
    int i;
    for (i = 0; i < 8; i++) {
        self->mDirs[i] = src->mDirs[i];
    }
    self->mCentre = src->mCentre;
    self->mHeaderData = src->mHeaderData;
    self->mHeader = &self->mHeaderData;
    return self;
}

//100%
extern "C" void func_003E6574(void* dst, void* src, int n);

extern "C" int cSphereTree_load(cSphereTree* self, char* buf, int a2)
{
    if (buf == 0) {
        return 0;
    }
    self->mHeaderData.mKey = a2;
    self->mHeaderData.mCacheSlot = 0;
    self->mHeader = &self->mHeaderData;
    self->mHeaderData.mUnk10 = 1;
    int len0;
    int len1;
    func_003E6574(&len0, buf, 4);
    func_003E6574(&len1, buf + 4, 4);
    func_003E6574(&self->mHeader->mPacked, buf + 0x8, 4);
    func_003E6574(&self->mHeader->mDepth, buf + 0xC, 4);
    func_003E6574(self->mHeader->mRootCentre, buf + 0x10, 0xC);
    func_003E6574(self->mHeader->mMassCentre, buf + 0x1C, 0xC);
    func_003E6574(self->mHeader->mInertia, buf + 0x28, 0x24);
    func_003E6574(self->mHeader->mInvInertia, buf + 0x4C, 0x24);
    char* p = buf + 0x70;
    *(char**)&self->mHeader->mLevels = p;
    p += (self->mHeader->mDepth + 1) * 0xC;
    *(char**)&self->mHeader->mPackedMasks = p;
    p += len1;
    p += len0;
    sSphereTreeHeader* b = self->mHeader;
    if (b->mPacked != 0) {
        b->mMasks = 0;
    } else {
        b->mMasks = (unsigned char*)b->mPackedMasks;
    }
    sSphereVec4 v;
    sSphereTreeHeader* c = self->mHeader;
    v.x = c->mRootCentre[0];
    v.y = c->mRootCentre[1];
    v.z = c->mRootCentre[2];
    v.w = 1.0f;
    self->mCentre = v;
    return p - buf;
}

//100%
extern "C" int cSphereTree_getMasks(void* self);
extern "C" int cSphereTree_testSphereNode(void* self, void* pos, void* out, int a3, int a4, int a5, int a6, float radius);


extern "C" int cSphereTree_testRiderSphereTree(void* self, cRiderSphereTree* shape, int a2, int a3)
{
    cSphereTree* t = (cSphereTree*)self;
    sSphereTreeHeader* m = t->mHeader;
    if (m->mPacked != 0) {
        *(int*)&t->mHeader->mMasks = cSphereTree_getMasks(m);
    }
    if (cSphereTree_testSphereNode(self, &shape->mCentre, &t->mCentre, 0, 0, a2, a3, shape->mRadius) == 0) {
        return 0;
    }
    if (shape->mCount == 0) {
        return 1;
    }
    for (int i = 0; i < shape->mCount; i++) {
        if (cSphereTree_testSphereNode(self, &shape->mSpheres[i].mPos, &t->mCentre, 0, 0, a2, a3, shape->mSpheres[i].mRadius) != 0) {
            return 1;
        }
    }
    return 0;
}

//100%
extern "C" float cSphereTree_getRadius(void* self);
extern "C" int cSphereTree_testTriangle(void* self, void* a1, void* a2, void* a3, void* v, void* a5, void* a6);

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sSphereVec4 vu0Sub_28030(const sSphereVec4& a, const sSphereVec4& b)
{
    sSphereVec4 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0Dot_28030(const sSphereVec4& a, const sSphereVec4& b)
{
    float r;
    int t;
    __asm__(
        "lqc2      $vf3, %2\n"
        "lqc2      $vf5, %3\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf5\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "qmfc2.ni  %1, $vf4\n"
        "mtc1      %1, %0\n"
        : "=f"(r), "=&r"(t)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sSphereVec4 vu0Scale_28030(const sSphereVec4& v, float s)
{
    sSphereVec4 r;
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s));
    return r;
}

extern "C" int cSphereTree_testTriangleTwoSided(void* self, sSphereVec4* p, void* a2, void* a3, sSphereVec4* dir, void* a5, void* a6)
{
    float dot;
    {
        cSphereTree* t = (cSphereTree*)self;
        sSphereVec4 d = vu0Sub_28030(t->mCentre, *p);
        dot = vu0Dot_28030(*dir, d);
    }
    if (cSphereTree_getRadius(self) < __builtin_fabsf(dot)) {
        return 0;
    }
    if (dot < 0.0f) {
        sSphereVec4 nd = vu0Scale_28030(*dir, -1.0f);
        return cSphereTree_testTriangle(self, p, a2, a3, &nd, a5, a6);
    }
    return cSphereTree_testTriangle(self, p, a2, a3, dir, a5, a6);
}

//100%
extern "C" void cSphereTree_debugDrawNode(void* self, int a1, void* a2, int a3, int a4);

extern "C" void cSphereTree_debugDraw(void* self)
{
    cSphereTree* t = (cSphereTree*)self;
    sSphereTreeHeader* m = t->mHeader;
    if (m->mPacked != 0) {
        *(int*)&t->mHeader->mMasks = cSphereTree_getMasks(m);
    }
    cSphereTree_debugDrawNode(self, t->mHeader->mDepth, &t->mCentre, 0, 0);
}

INCLUDE_ASM("intersect/aifwddiff", cSphereTree_debugDrawNode);

//100%
extern "C" int cSpaceHash_classifyCell(sSpaceHashCell* c, sSpaceHashBox* b)
{
    union {
        int i;
        float f;
    } s;
    s.i = (c->mLevel + 0x7F) << 23;
    float scale = s.f;
    float x0 = ((float)c->mX - 0.2f) * scale;
    if (b->mMax.x < x0) {
        return 1;
    }
    float y0 = ((float)c->mY - 0.2f) * scale;
    if (b->mMax.y < y0) {
        return 1;
    }
    float z0 = ((float)c->mZ - 0.2f) * scale;
    if (b->mMax.z < z0) {
        return 1;
    }
    float x1 = ((float)(c->mX + 1) + 0.2f) * scale;
    if (x1 < b->mMin.x) {
        return 1;
    }
    float y1 = ((float)(c->mY + 1) + 0.2f) * scale;
    if (y1 < b->mMin.y) {
        return 1;
    }
    float z1 = ((float)(c->mZ + 1) + 0.2f) * scale;
    if (z1 < b->mMin.z) {
        return 1;
    }
    if (x1 < b->mMax.x) {
        return 2;
    }
    if (y1 < b->mMax.y) {
        return 2;
    }
    if (z1 < b->mMax.z) {
        return 2;
    }
    if (b->mMin.x < x1) {
        return 2;
    }
    if (b->mMin.y < y1) {
        return 2;
    }
    if (b->mMin.y < y1) {
        return 2;
    }
    return 0;
}

//100%
void operator_delete(int* p);

extern "C" void func_003284B8(cSpaceHashNode* node, int idx, sSpaceHashItem* item, const sSpaceHashCell* target,
                              const sSpaceHashCell* cur)
{
    int lv = cur->mLevel;
    if (target->mLevel == lv) {
        node->mLists[idx].remove(item);
        return;
    }
    int sh = lv - target->mLevel - 1;
    int dx = (target->mX >> sh) - cur->mX * 2;
    int dy = (target->mY >> sh) - cur->mY * 2;
    int dz = (target->mZ >> sh) - cur->mZ * 2;
    sSpaceHashCell c;
    c.mX = cur->mX * 2 + dx;
    c.mLevel = --lv;
    c.mY = cur->mY * 2 + dy;
    c.mZ = cur->mZ * 2 + dz;
    cSpaceHashNode** ch = &node->mChild[dx][dy][dz];
    func_003284B8(*ch, idx, item, target, &c);
    if ((*ch)->empty()) {
        operator_delete((int*)*ch);
        *ch = 0;
    }
}

//100%
// PORT: cMemMan_alloc is the game's operator new(size, tag, flags, align).
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" void func_003E6448(void* p, int v, int n);
extern char D_004A3FC0[];

// cSpaceHashNode with the constructor cSpaceHash_insertItemAt inlines.
struct sNewNode_00328660 : cSpaceHashNode {
    sNewNode_00328660() { func_003E6448(mChild, 0, sizeof(mChild)); }
};

extern "C" void cSpaceHash_insertItemAt(cSpaceHashNode* node, int idx, sSpaceHashItem* item, sSpaceHashCell* target, const sSpaceHashCell* at)
{
    sSpaceHashCell cur = *at;
    while (cur.mLevel != target->mLevel) {
        int sh = cur.mLevel - target->mLevel - 1;
        cur.mLevel--;
        int dx = (target->mX >> sh) - cur.mX * 2;
        int dy = (target->mY >> sh) - cur.mY * 2;
        int dz = (target->mZ >> sh) - cur.mZ * 2;
        cur.mX = cur.mX * 2 + dx;
        cur.mY = cur.mY * 2 + dy;
        cur.mZ = cur.mZ * 2 + dz;
        cSpaceHashNode** c = &node->mChild[dx][dy][dz];
        if (*c == 0) {
            *c = new (D_004A3FC0, 0x20000000, 0) sNewNode_00328660;
        }
        node = *c;
    }
    node->mLists[idx].push(item);
}

INCLUDE_ASM("intersect/aifwddiff", cSpaceHash_moveItemInNode);

//100%
// cSpaceHashNode with the constructors func_00328C20 inlines (a new root, and
// a parent wrapping the old root).
struct sNewNode_8C20 : cSpaceHashNode {
    sNewNode_8C20() {}
    sNewNode_8C20(cSpaceHashNode* c, const sSpaceHashCell& cc, const sSpaceHashCell& pc)
    {
        int dx = cc.mX - pc.mX * 2;
        int dy = cc.mY - pc.mY * 2;
        int dz = cc.mZ - pc.mZ * 2;
        func_003E6448(mChild, 0, sizeof(mChild));
        mChild[dx][dy][dz] = c;
    }
};

static inline int Contains_8C20(const sSpaceHashCell& a, const sSpaceHashCell& b)
{
    int d = a.mLevel - b.mLevel;
    if (d < 0) {
        return 0;
    }
    if (d == 0) {
        return b.mX == a.mX && b.mY == a.mY && b.mZ == a.mZ;
    }
    return (b.mX >> d) == a.mX && (b.mY >> d) == a.mY && (b.mZ >> d) == a.mZ;
}

static inline sSpaceHashCell Parent_8C20(const sSpaceHashCell& c)
{
    sSpaceHashCell r;
    r.mLevel = c.mLevel + 1;
    r.mX = c.mX >> 1;
    r.mY = c.mY >> 1;
    r.mZ = c.mZ >> 1;
    return r;
}

extern "C" void func_00328C20(sSpaceHashRoot* root, int idx, sSpaceHashItem* item, sSpaceHashCell* cell)
{
    cSpaceHashNode** pn = &root->mNode;
    if (root->mNode == 0) {
        root->mCell = *cell;
        sNewNode_8C20* n = new (D_004A3FC0, 0x20000000, 0) sNewNode_8C20;
        func_003E6448(n->mChild, 0, sizeof(n->mChild));
        *pn = n;
        root->mNode->mLists[idx].push(item);
        return;
    }
    while (!Contains_8C20(root->mCell, *cell)) {
        sSpaceHashCell nc = Parent_8C20(root->mCell);
        sNewNode_8C20* n = new (D_004A3FC0, 0x20000000, 0) sNewNode_8C20(root->mNode, root->mCell, nc);
        root->mCell = nc;
        root->mNode = n;
    }
    cSpaceHash_insertItemAt(root->mNode, idx, item, cell, &root->mCell);
}

//100%
// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sSphereVec4 vu0Sub_8F28(const sSphereVec4& a, const sSphereVec4& b)
{
    sSphereVec4 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector add).
static inline sSphereVec4 vu0Add_8F28(const sSphereVec4& a, const sSphereVec4& b)
{
    sSphereVec4 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sSphereVec4 vu0Scale_8F28(const sSphereVec4& v, float s)
{
    sSphereVec4 r;
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s));
    return r;
}

// PORT: PS2 float->int->float round trip kept in the FPU (cvt.w.s / mfc1 / cvt.s.w).
static inline int Floor_8F28(float f)
{
    float t;
    int q;
    __asm__("cvt.w.s %0, %2\n\tmfc1 %1, %0\n\tcvt.s.w %0, %0" : "=&f"(t), "=r"(q) : "f"(f));
    if (f < t) {
        q--;
    }
    return q;
}

static inline sSpaceHashCell Parent_8F28(const sSpaceHashCell& c)
{
    sSpaceHashCell r;
    r.mLevel = c.mLevel + 1;
    r.mX = c.mX >> 1;
    r.mY = c.mY >> 1;
    r.mZ = c.mZ >> 1;
    return r;
}

extern "C" void func_00328F28(sSpaceHashCell* c, sSpaceHashBox* b)
{
    sSphereVec4 size = vu0Sub_8F28(b->mMax, b->mMin);
    sSphereVec4 center = vu0Add_8F28(b->mMin, vu0Scale_8F28(size, 0.5f));
    float m = size.x;
    if (m < size.y) {
        m = size.y;
    }
    if (m < size.z) {
        m = size.z;
    }
    union {
        float f;
        int i;
    } u;
    u.f = m * 0.7142857313156128f;
    c->mLevel = ((u.i >> 23) & 0xFF) - 0x7F;
    if (c->mLevel < 11) {
        c->mLevel = 11;
    }
    union {
        int i;
        float f;
    } s;
    s.i = (c->mLevel + 0x7F) << 23;
    float scale = s.f;
    c->mX = Floor_8F28(center.x / scale);
    c->mY = Floor_8F28(center.y / scale);
    c->mZ = Floor_8F28(center.z / scale);
    for (;;) {
        s.i = (c->mLevel + 0x7F) << 23;
        scale = s.f;
        int ok = 0;
        if (((float)c->mX - 0.2f) * scale <= b->mMin.x && ((float)c->mY - 0.2f) * scale <= b->mMin.y && ((float)c->mZ - 0.2f) * scale <= b->mMin.z
            && b->mMax.x <= ((float)(c->mX + 1) + 0.2f) * scale && b->mMax.y <= ((float)(c->mY + 1) + 0.2f) * scale && b->mMax.z <= ((float)(c->mZ + 1) + 0.2f) * scale) {
            ok = 1;
        }
        if (ok) {
            break;
        }
        *c = Parent_8F28(*c);
    }
}

INCLUDE_ASM("intersect/aifwddiff", cSpaceHash_moveItem);

INCLUDE_ASM("intersect/aifwddiff", intersectSphereBox);

