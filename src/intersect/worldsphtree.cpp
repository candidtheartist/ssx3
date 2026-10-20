#include "common.h"
#include "intersect/worldquery.h"
#include "intersect/overlaplist.h"

//100%
extern void* D_0048E5F0[];
extern char D_0048E550[];
extern "C" void* cSphereTree_cSphereTree(void* p);
extern "C" float cSphereTree_getRadius(void* self);
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

extern "C" void* cWorldSphTree_cWorldSphTree(void* self, void* a1, int a2)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    cSphereTree* tree = (cSphereTree*)a1;
    t->mVtable = D_0048E5F0;
    t->mUseNormalFilter = 0;
    t->mTransformed = 0;
    if (a2 != 0) {
        t->mKind = 0;
    } else {
        t->mKind = 1;
    }
    t->mOrigTree = tree;
    t->mTree = tree;
    sSphereVec4 c = tree->mCentre;
    float r = cSphereTree_getRadius(a1);
    sSphereVec4 v;
    t->mBoxCentre = c;
    v.x = c.x + r;
    v.y = c.y + r;
    v.z = c.z + r;
    v.w = 1.0f;
    t->mMax = v;
    v.x = c.x - r;
    v.y = c.y - r;
    v.z = c.z - r;
    v.w = 1.0f;
    t->mMin = v;
    void* p = cMemMan_alloc(0x140, D_0048E550, 0, 0);
    cSphereTree_cSphereTree(p);
    t->mScratch = (cSphereTree*)p;
    return self;
}

//100%
void operator_delete(int* ptr);
extern void* D_0048E5F0[];

extern "C" void cWorldSphTree_destroy(void* self, int flags)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    t->mVtable = D_0048E5F0;
    operator_delete((int*)t->mScratch);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
// PORT: PS2-only VU0 inline asm (vector add).
static inline sSphereVec4 add_330540(const sSphereVec4& a, const sSphereVec4& b)
{
    sSphereVec4 r;
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

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sSphereVec4 sub_330540(const sSphereVec4& a, const sSphereVec4& b)
{
    sSphereVec4 r;
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

extern "C" float cSphereTree_getRadius(void* self);

extern "C" int cWorldSphTree_overlapsBox(void* self, float* lo, float* hi)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    sSphereVec4 ext;
    float rx = cSphereTree_getRadius(t->mTree);
    float ry = cSphereTree_getRadius(t->mTree);
    float rz = cSphereTree_getRadius(t->mTree);
    ext.x = rx;
    ext.y = ry;
    ext.z = rz;
    ext.w = 0.0f;
    sSphereVec4 mx = add_330540(t->mTree->mCentre, ext);
    sSphereVec4 mn = sub_330540(t->mTree->mCentre, ext);
    float lx = lo[0];
    float tx = mx.x;
    if (tx < lx && mn.x < lx) return 0;
    if (hi[0] < tx && hi[0] < mn.x) return 0;
    float ly = lo[1];
    float ty = mx.y;
    if (ty < ly && mn.y < ly) return 0;
    if (hi[1] < ty && hi[1] < mn.y) return 0;
    float lz = lo[2];
    float tz = mx.z;
    if (tz < lz && mn.z < lz) return 0;
    if (!(hi[2] < tz) || !(hi[2] < mn.z)) return 1;
    return 0;
}

//100%
extern "C" float cSphereTree_getRadius(void* self);

extern "C" float cWorldSphTree_getRadius(void* self)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    float r;
    if (t->mKind != 0) {
        r = cSphereTree_getRadius(t->mTree) * 2.0f;
    } else {
        r = -1.0f;
    }
    return r;
}

//100%
extern "C" void* cSphereTree_assign(void* self, void* src);
extern "C" void cSphereTree_transform(void* p, void* a, float f);

extern "C" void cWorldSphTree_transform(void* self, void* a1, float f)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    cSphereTree_assign(t->mScratch, t->mTree);
    t->mTree = t->mScratch;
    cSphereTree_transform(t->mTree, a1, f);
    t->mTransformed = 1;
}

//100%
int cWorldSphTree_restore__FPv(void* self)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    int t0 = *(int*)&t->mOrigTree;
    t->mTransformed = 0;
    *(int*)&t->mTree = t0;
    return t0;
}

//100%
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float wsLength_330788(const sSphereVec4& v)
{
    float r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vsqrt     Q, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni   %0, $vi22\n"
        : "=r"(r)
        : "m"(v));
    return r;
}

// PORT: PS2-only VU0 inline asm (v / s).
static inline sSphereVec4 wsDiv_330788(const sSphereVec4& v, float s)
{
    sSphereVec4 r;
    int t;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "mfc1      %1, %3\n"
        "qmtc2.ni  %1, $vf3\n"
        "vdiv      Q, $vf0w, $vf3x\n"
        "lqc2      $vf4, %2\n"
        "vwaitq\n"
        "vmulq.xyzw $vf4, $vf4, Q\n"
        "sqc2      $vf4, %0\n"
        ".set pop\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

extern "C" int cSphereTree_testTriangle(void* tree, int a1, int a2, int a3, int a4, sSphereVec4* out, int a6);

extern "C" int cWorldSphTree_testTriangle(void* self, int a1, int a2, int a3, int a4, int a5, sSphereVec4* outDir, float* outLen)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    sSphereVec4 v;
    int r = cSphereTree_testTriangle(t->mTree, a1, a2, a3, a4, &v, a5);
    if (r != 0) {
        float len = wsLength_330788(v);
        *outLen = len;
        *outDir = wsDiv_330788(v, len);
    }
    return r;
}

//100%
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float wsLength_330828(const sSphereVec4& v)
{
    float r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vsqrt     Q, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni   %0, $vi22\n"
        : "=r"(r)
        : "m"(v));
    return r;
}

// PORT: PS2-only VU0 inline asm (v / s).
static inline sSphereVec4 wsDiv_330828(const sSphereVec4& v, float s)
{
    sSphereVec4 r;
    int t;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "mfc1      %1, %3\n"
        "qmtc2.ni  %1, $vf3\n"
        "vdiv      Q, $vf0w, $vf3x\n"
        "lqc2      $vf4, %2\n"
        "vwaitq\n"
        "vmulq.xyzw $vf4, $vf4, Q\n"
        "sqc2      $vf4, %0\n"
        ".set pop\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

extern "C" int cSphereTree_testTriangleTwoSided(void* tree, int a1, int a2, int a3, int a4, sSphereVec4* out, int a6);

extern "C" int cWorldSphTree_testTriangleTwoSided(void* self, int a1, int a2, int a3, int a4, int a5, sSphereVec4* outDir, float* outLen)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    sSphereVec4 v;
    int r = cSphereTree_testTriangleTwoSided(t->mTree, a1, a2, a3, a4, &v, a5);
    if (r != 0) {
        float len = wsLength_330828(v);
        *outLen = len;
        *outDir = wsDiv_330828(v, len);
    }
    return r;
}

//100%
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float wsLength_3308C8(const sSphereVec4& v)
{
    float r;
    int t;
    __asm__(
        "lqc2      $vf3, %2\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vsqrt     Q, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni   %1, $vi22\n"
        "mtc1      %1, %0\n"
        : "=f"(r), "=&r"(t)
        : "m"(v));
    return r;
}

// PORT: PS2-only VU0 inline asm (in-place vector divided by scalar).
static inline void wsDivEq_3308C8(sSphereVec4& v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vdiv      Q, $vf0w, $vf3x\n"
        "lqc2      $vf4, %0\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf4, Q\n"
        "sqc2      $vf5, %0\n"
        : "+m"(v), "=&r"(t)
        : "f"(s)
        : "memory");
}

extern "C" int cSphereTree_testSphereTree(void* self, void* other, void* a2, void* a3);

extern "C" int cWorldSphTree_testSphereTree(void* self, void* a1, sWorldHit* hit)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    if (cSphereTree_testSphereTree(t->mTree, a1, &hit->mNormal, hit) != 0) {
        float len = wsLength_3308C8(hit->mNormal);
        hit->mDepth = len;
        wsDivEq_3308C8(hit->mNormal, len);
        return 1;
    }
    return 0;
}

//100%
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float wsLength_330950(const sSphereVec4& v)
{
    float r;
    int t;
    __asm__(
        "lqc2      $vf3, %2\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vsqrt     Q, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni   %1, $vi22\n"
        "mtc1      %1, %0\n"
        : "=f"(r), "=&r"(t)
        : "m"(v));
    return r;
}

// PORT: PS2-only VU0 inline asm (in-place vector divided by scalar).
static inline void wsDivEq_330950(sSphereVec4& v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vdiv      Q, $vf0w, $vf3x\n"
        "lqc2      $vf4, %0\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf4, Q\n"
        "sqc2      $vf5, %0\n"
        : "+m"(v), "=&r"(t)
        : "f"(s)
        : "memory");
}

extern "C" int cSphereTree_testBox(void* self, void* a1, void* a2, void* a3, void* a4);

extern "C" int cWorldSphTree_testBox(void* self, void* a1, void* a2, sWorldHit* hit)
{
    cWorldSphTree* t = (cWorldSphTree*)self;
    if (cSphereTree_testBox(t->mTree, a1, a2, &hit->mNormal, hit) != 0) {
        float len = wsLength_330950(hit->mNormal);
        hit->mDepth = len;
        wsDivEq_330950(hit->mNormal, len);
        return 1;
    }
    return 0;
}

//100%
typedef int (*Test_3309D8)(void*);
typedef sSpaceHashBox* (*GetBox_3309D8)(void*);

static inline int overlapNode_3309D8(const sSpaceHashBox* b, const sWorldInstance* n)
{
    int r = 0;
    if (b->mMin.x <= n->mMax[0] && b->mMax.x >= n->mMin[0] &&
        b->mMin.y <= n->mMax[1] && b->mMax.y >= n->mMin[1] &&
        b->mMin.z <= n->mMax[2] && b->mMax.z >= n->mMin[2]) {
        r = 1;
    }
    return r;
}

static inline int overlapBox_3309D8(const sSpaceHashBox* b, const sSpaceHashBox* o)
{
    int r = 0;
    if (b->mMin.x <= o->mMax.x && b->mMax.x >= o->mMin.x &&
        b->mMin.y <= o->mMax.y && b->mMax.y >= o->mMin.y &&
        b->mMin.z <= o->mMax.z && b->mMax.z >= o->mMin.z) {
        r = 1;
    }
    return r;
}

extern "C" void cOverlapList_collectNodeInstances(sOverlapSink* ctx, void* tree)
{
    cSpaceHashNode* t = (cSpaceHashNode*)tree;
    for (sWorldInstance* p = (sWorldInstance*)t->mLists[SPACEHASH_INSTANCES].mHead; p != 0; p = (sWorldInstance*)p->mLink.mNext) {
        int flags = p->mFlags;
        if (flags & 0x20) {
            if (overlapNode_3309D8(ctx->mBox, p)) {
                unsigned int* cnt = ctx->mCount;
                int n = *cnt;
                ctx->mItems[n] = p;
                *cnt = n + 1;
            }
        } else if (flags & 0x40) {
            sWorldVEntry* vt = p->mEntity->mVtable;
            if (((Test_3309D8)vt[44].mFn)((char*)p->mEntity + vt[44].mDelta)) {
                sWorldVEntry* vt2 = p->mEntity->mVtable;
                sSpaceHashBox* b = ((GetBox_3309D8)vt2[45].mFn)((char*)p->mEntity + vt2[45].mDelta);
                if (overlapBox_3309D8(ctx->mBox, b)) {
                    unsigned int* cnt = ctx->mCount;
                    int n = *cnt;
                    ctx->mItems[n] = p;
                    *cnt = n + 1;
                }
            }
        }
    }
}

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_buildInstances);

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_buildObjects);

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_buildInstancesPatches);

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_build);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern sSphereVec4 D_004FF120[];

typedef int (*Test_333EF8)(void*);
typedef sSpaceHashBox* (*GetBox_333EF8)(void*);

extern "C" void cAIFwdDiffCache_lookup(void* cache, void* src, void** out);
extern "C" int cWorldIntType_testPatch(void* q, void* obj, void* node, sSphereVec4* pos, sSphereVec4* nrm, float* dist, sSphereVec4* uv, int arg);
extern "C" int cWorldIntType_testInstance(void* q, void* node, void* buf, int cap, int mode);

static inline int overlapTri_333EF8(const cWorldIntType* q, const sTerrainPatch* n)
{
    int r = 0;
    if (q->mMax.x > n->mMin[0] && q->mMin.x < n->mMax[0] &&
        q->mMax.y > n->mMin[1] && q->mMin.y < n->mMax[1] &&
        q->mMax.z > n->mMin[2] && q->mMin.z < n->mMax[2]) {
        r = 1;
    }
    return r;
}

static inline int overlapNode_333EF8(const cWorldIntType* q, const sWorldInstance* n)
{
    int r = 0;
    if (q->mMax.x > n->mMin[0] && q->mMin.x < n->mMax[0] &&
        q->mMax.y > n->mMin[1] && q->mMin.y < n->mMax[1] &&
        q->mMax.z > n->mMin[2] && q->mMin.z < n->mMax[2]) {
        r = 1;
    }
    return r;
}

static inline int overlapBox_333EF8(const cWorldIntType* q, const sSpaceHashBox* o)
{
    int r = 0;
    if (q->mMax.x > o->mMin.x && q->mMin.x < o->mMax.x &&
        q->mMax.y > o->mMin.y && q->mMin.y < o->mMax.y &&
        q->mMax.z > o->mMin.z && o->mMax.z > q->mMin.z) {
        r = 1;
    }
    return r;
}

static inline void reset_333EF8(sWorldHit* h)
{
    h->mType = 2;
    h->mPatch = 0;
    h->mInstance = 0;
    h->mUnk58 = 0;
    h->mUnk5C = -1;
    h->mTriangle = -1;
    h->mUnk64 = -1;
    h->mSurface = -1;
    h->mSurfaceVel = *D_004FF120;
    h->mVec30 = *D_004FF120;
    h->mUnk68 = 0;
    h->mU = 0;
    h->mV = 0;
}

extern "C" int cOverlapList_collectHits(void* self, void* vq, sWorldHit* hits, int cap, int arg)
{
    cOverlapList* t = (cOverlapList*)self;
    cWorldIntType* q = (cWorldIntType*)vq;
    int n = 0;
    for (unsigned int i = 0; i < t->mPatchCount; i++) {
        sTerrainPatch* obj = t->mPatches[i];
        if ((obj->mFlags & 0x41) != 0x41) {
            continue;
        }
        if (!overlapTri_333EF8(q, obj)) {
            continue;
        }
        sSphereVec4 uv;
        sSphereVec4 pos;
        sSphereVec4 nrm;
        void* node;
        float dist;
        cAIFwdDiffCache_lookup(t->mHash->mFwdDiff, obj, &node);
        if (!cWorldIntType_testPatch(q, obj, node, &pos, &nrm, &dist, &uv, arg)) {
            continue;
        }
        reset_333EF8(&hits[n]);
        hits[n].mPos = pos;
        hits[n].mNormal = nrm;
        hits[n].mSurface = obj->mSurface;
        hits[n].mPatch = obj;
        hits[n].mDepth = dist;
        hits[n].mU = uv.x;
        hits[n].mV = uv.y;
        n++;
    }
    for (unsigned int j = 0; j < t->mInstanceCount; j++) {
        sWorldInstance* node = t->mInstances[j];
        if (node->mCollision == 0) {
            continue;
        }
        int flags = node->mFlags;
        if (flags & 0x20) {
            if (overlapNode_333EF8(q, node)) {
                n += cWorldIntType_testInstance(q, node, &hits[n], cap - n, 2);
            }
        } else if (flags & 0x40) {
            if (node->mEntity == 0) {
                continue;
            }
            sWorldVEntry* vt = node->mEntity->mVtable;
            if (((Test_333EF8)vt[44].mFn)((char*)node->mEntity + vt[44].mDelta)) {
                sWorldVEntry* vt2 = node->mEntity->mVtable;
                sSpaceHashBox* b = ((GetBox_333EF8)vt2[45].mFn)((char*)node->mEntity + vt2[45].mDelta);
                if (overlapBox_333EF8(q, b)) {
                    n += cWorldIntType_testInstance(q, node, &hits[n], cap - n, 2);
                }
            }
        }
    }
    return n;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_003342D0(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

static inline int isBetter_003342D0(sWorldHit* a, sWorldHit* b)
{
    if (a->mInstance != 0) {
        if (b->mInstance == 0) {
            return 1;
        }
        return ((sWorldInstance*)a->mInstance)->mResId < ((sWorldInstance*)b->mInstance)->mResId;
    }
    if (b->mInstance != 0) {
        return 0;
    }
    return ((sTerrainPatch*)a->mPatch)->mKey < ((sTerrainPatch*)b->mPatch)->mKey;
}

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_queryNearest);
extern "C" float cOverlapList_queryNearest(void* self, char* q, sWorldHit* out, int a3);

//100%
typedef int (*Test_334458)(void*);
typedef sSpaceHashBox* (*GetBox_334458)(void*);

extern "C" int cWorldIntType_testInstance(void* q, void* node, void* buf, int cap, int mode);

static inline int overlapNode_334458(const cWorldIntType* q, const sWorldInstance* n)
{
    int r = 0;
    if (q->mMax.x > n->mMin[0] && q->mMin.x < n->mMax[0] &&
        q->mMax.y > n->mMin[1] && q->mMin.y < n->mMax[1] &&
        q->mMax.z > n->mMin[2] && q->mMin.z < n->mMax[2]) {
        r = 1;
    }
    return r;
}

static inline int overlapBox_334458(const cWorldIntType* q, const sSpaceHashBox* o)
{
    int r = 0;
    if (q->mMax.x > o->mMin.x && q->mMin.x < o->mMax.x &&
        q->mMax.y > o->mMin.y && q->mMin.y < o->mMax.y &&
        q->mMax.z > o->mMin.z && o->mMax.z > q->mMin.z) {
        r = 1;
    }
    return r;
}

extern "C" int cOverlapList_collectInstanceHits(cOverlapList* self, cWorldIntType* q, sWorldHit* buf, int cap, int full)
{
    int mode = 1;
    if (full) mode = 2;
    int n = 0;
    for (unsigned int i = 0; i < self->mInstanceCount; i++) {
        sWorldInstance* node = self->mInstances[i];
        int flags = node->mFlags;
        if (flags & 0x20) {
            if (overlapNode_334458(q, node)) {
                n += cWorldIntType_testInstance(q, node, &buf[n], cap - n, mode);
            }
        } else if (flags & 0x40) {
            sWorldVEntry* vt = node->mEntity->mVtable;
            if (((Test_334458)vt[44].mFn)((char*)node->mEntity + vt[44].mDelta)) {
                sWorldVEntry* vt2 = node->mEntity->mVtable;
                sSpaceHashBox* b = ((GetBox_334458)vt2[45].mFn)((char*)node->mEntity + vt2[45].mDelta);
                if (overlapBox_334458(q, b)) {
                    n += cWorldIntType_testInstance(q, node, &buf[n], cap - n, mode);
                }
            }
        }
    }
    return n;
}

//100%
extern "C" void func_0035C698(void* a0, sSpaceHashBox* box, sSpaceHashBox* box2, sSphereVec4* pos, int mask, int* cnt, float* dist, int a7);
extern "C" void func_00348290(void* a0, sSpaceHashBox* box, sSpaceHashBox* box2, sSphereVec4* pos, int mask, int* cnt, float* dist, int a7);
extern "C" void cRailSegment_findClosestPoint(void* obj, sSpaceHashBox* box, sSphereVec4* pos, int* cnt, float* dist, int a5);

// PORT: PS2-only VU0 inline asm (in-place vector subtract).
static inline void wsSubEq_334680(sSphereVec4& a, const sSphereVec4& b)
{
    __asm__(
        "lqc2      $vf3, %0\n"
        "lqc2      $vf4, %1\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "+m"(a)
        : "m"(b)
        : "memory");
}

// PORT: PS2-only VU0 inline asm (in-place vector add).
static inline void wsAddEq_334680(sSphereVec4& a, const sSphereVec4& b)
{
    __asm__(
        "lqc2      $vf3, %0\n"
        "lqc2      $vf4, %1\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "+m"(a)
        : "m"(b)
        : "memory");
}

extern "C" int cOverlapList_findNearestRail(char* self, sSphereVec4* pos, int a2, int mask, float r)
{
    cOverlapList* t = (cOverlapList*)self;
    sSpaceHashBox box;
    sSphereVec4 ext;
    int cnt;
    float dist;
    float zero = 0.0f;
    cnt = 0;
    dist = zero;
    box.mMin = *pos;
    box.mMax = *pos;
    ext.x = r;
    ext.y = r;
    ext.z = r;
    ext.w = zero;
    wsSubEq_334680(box.mMin, ext);
    wsAddEq_334680(box.mMax, ext);
    for (unsigned int i = 0; i < t->mObjectCount; i++) {
        sSpaceHashObject* o = t->mObjects[i];
        int type = o->mType;
        if (type == 2) {
            func_0035C698(o->mObject, &box, &box, pos, mask, &cnt, &dist, a2);
        } else if (type == 3) {
            func_00348290(o->mObject, &box, &box, pos, mask, &cnt, &dist, a2);
        } else if (type == 1) {
            if (((sRailSegment*)o)->mSpline->mFlags & mask) {
                cRailSegment_findClosestPoint(o, &box, pos, &cnt, &dist, a2);
            }
        }
    }
    return cnt;
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
void* AIFwdDiffCache_ctor(void* self);
extern "C" void cAIFwdDiffCache_Init(void* cache, int n);
extern char D_0048E4F8[];

extern "C" void cSpaceHash_createFwdDiffCache(void* self)
{
    cSpaceHash* t = (cSpaceHash*)self;
    void* c = AIFwdDiffCache_ctor(cMemMan_alloc(0x10, D_0048E4F8, 0, 0));
    t->mFwdDiff = (cAIFwdDiffCache*)c;
    cAIFwdDiffCache_Init(c, 0x28);
}

//100%
extern "C" void func_00327828(void* p, int flags);

extern "C" void cSpaceHash_destroyFwdDiffCache(void* self)
{
    cSpaceHash* t = (cSpaceHash*)self;
    cAIFwdDiffCache* p = t->mFwdDiff;
    if (p != 0) {
        func_00327828(p, 3);
    }
    t->mFwdDiff = 0;
}

INCLUDE_ASM("intersect/worldsphtree", cWorldIntType_testInstance);

INCLUDE_ASM("intersect/worldsphtree", cRailSegment_findClosestPoint);

//100%
extern "C" void cAIFwdDiffCache_lookup(void* cache, void* src, void** out);
extern "C" int cWorldIntType_testPatch(void* q, void* obj, void* node, sSphereVec4* pos, sSphereVec4* nrm, float* dist, sSphereVec4* uv, int arg);

static inline int overlap_335960(const cWorldIntType* q, const sTerrainPatch* n)
{
    int r = 0;
    if (q->mMax.x > n->mMin[0] && q->mMin.x < n->mMax[0] &&
        q->mMax.y > n->mMin[1] && q->mMin.y < n->mMax[1] &&
        q->mMax.z > n->mMin[2] && q->mMin.z < n->mMax[2]) {
        r = 1;
    }
    return r;
}

static inline void reset_335960(sWorldHit* h)
{
    h->mType = 2;
    h->mPatch = 0;
    h->mInstance = 0;
    h->mUnk58 = 0;
    h->mUnk5C = -1;
    h->mTriangle = -1;
    h->mUnk64 = -1;
    h->mSurface = -1;
    h->mSurfaceVel = *D_004FF120;
    h->mVec30 = *D_004FF120;
    h->mUnk68 = 0;
    h->mU = 0;
    h->mV = 0;
}

extern "C" void cSpaceHash_collectPatchHit(void* vctx, void* vobj)
{
    sSpaceHashCollect* ctx = (sSpaceHashCollect*)vctx;
    sTerrainPatch* obj = (sTerrainPatch*)vobj;
    sSphereVec4 pos;
    sSphereVec4 nrm;
    sSphereVec4 uv;
    void* node;
    float dist;
    if ((obj->mFlags & 0x41) != 0x41) return;
    if (!overlap_335960(ctx->mQuery, obj)) return;
    cAIFwdDiffCache_lookup(ctx->mFwdDiff, obj, &node);
    if (!cWorldIntType_testPatch(ctx->mQuery, obj, node, &pos, &nrm, &dist, &uv, ctx->mArg)) return;
    reset_335960(&ctx->mHits[*ctx->mCount]);
    ctx->mHits[*ctx->mCount].mPos = pos;
    ctx->mHits[*ctx->mCount].mNormal = nrm;
    ctx->mHits[*ctx->mCount].mSurface = obj->mSurface;
    ctx->mHits[*ctx->mCount].mPatch = obj;
    ctx->mHits[*ctx->mCount].mDepth = dist;
    ctx->mHits[*ctx->mCount].mU = uv.x;
    ctx->mHits[*ctx->mCount].mV = uv.y;
    (*ctx->mCount)++;
}

//100%
typedef int (*Test_335B90)(void*);
typedef sSpaceHashBox* (*GetBox_335B90)(void*);

extern "C" int cWorldIntType_testInstance(void* q, void* node, void* buf, int cap, int mode);

static inline int overlapNode_335B90(const cWorldIntType* q, const sWorldInstance* n)
{
    int r = 0;
    if (q->mMax.x > n->mMin[0] && q->mMin.x < n->mMax[0] &&
        q->mMax.y > n->mMin[1] && q->mMin.y < n->mMax[1] &&
        q->mMax.z > n->mMin[2] && q->mMin.z < n->mMax[2]) {
        r = 1;
    }
    return r;
}

static inline int overlapBox_335B90(const cWorldIntType* q, const sSpaceHashBox* o)
{
    int r = 0;
    if (q->mMax.x > o->mMin.x && q->mMin.x < o->mMax.x &&
        q->mMax.y > o->mMin.y && q->mMin.y < o->mMax.y &&
        q->mMax.z > o->mMin.z && q->mMin.z < o->mMax.z) {
        r = 1;
    }
    return r;
}

static inline void collect_335B90(sSpaceHashCollect* ctx, sWorldInstance* node)
{
    int n = *ctx->mCount;
    *ctx->mCount += cWorldIntType_testInstance(ctx->mQuery, node, &ctx->mHits[n], ctx->mCapacity - n, 2);
}

extern "C" void cSpaceHash_collectInstanceHit(void* vctx, void* vnode)
{
    sSpaceHashCollect* ctx = (sSpaceHashCollect*)vctx;
    sWorldInstance* node = (sWorldInstance*)vnode;
    if (node->mCollision == 0) return;
    int flags = node->mFlags;
    if (flags & 0x20) {
        if (overlapNode_335B90(ctx->mQuery, node)) {
            collect_335B90(ctx, node);
        }
    } else if (flags & 0x40) {
        if (node->mEntity == 0) return;
        sWorldVEntry* vt = node->mEntity->mVtable;
        if (((Test_335B90)vt[44].mFn)((char*)node->mEntity + vt[44].mDelta)) {
            sWorldVEntry* vt2 = node->mEntity->mVtable;
            sSpaceHashBox* b = ((GetBox_335B90)vt2[45].mFn)((char*)node->mEntity + vt2[45].mDelta);
            if (overlapBox_335B90(ctx->mQuery, b)) {
                collect_335B90(ctx, node);
            }
        }
    }
}

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_collectHits);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cSpaceHash_collectHits(void* self, void* q, sWorldHit* hits, int max, int a4);

// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_00336850(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

static inline int isBetter_00336850(sWorldHit* a, sWorldHit* b)
{
    if (a->mInstance != 0) {
        if (b->mInstance == 0) {
            return 1;
        }
        return ((sWorldInstance*)a->mInstance)->mResId < ((sWorldInstance*)b->mInstance)->mResId;
    }
    if (b->mInstance != 0) {
        return 0;
    }
    return ((sTerrainPatch*)a->mPatch)->mKey < ((sTerrainPatch*)b->mPatch)->mKey;
}

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_queryNearest);
extern "C" float cSpaceHash_queryNearest(void* self, char* q, sWorldHit* out, int a3);

//100%
extern "C" void* cWorldLine_cWorldLine(void* seg, const sSphereVec4& a, const sSphereVec4& b, int n, float r);
// Ground probe handed down cSpaceHash_walkColumn (x/y column through the
// octree at the probe position).
struct sGroundProbe {
    float* mPos;            // 0x0
    char mFlags[8];         // 0x4
};

struct sTrav_369D8 {
    int count;              // 0x0
    sGroundProbe ctx;       // 0x4
};

extern "C" void cSpaceHash_walkColumn(char* flag, sSpaceHashCollect* q, sSpaceHashCollect* q2, sGroundProbe* ctx, cSpaceHashNode* node, sSpaceHashCell* cell);

// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_003369D8(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

// PORT: g++ `<?` (min) operator.
static inline float clamp_003369D8(float v, float lo, float hi)
{
    if (v >= lo) return v <? hi;
    return lo;
}

static inline int isBetter_003369D8(sWorldHit* a, sWorldHit* b)
{
    if (a->mInstance != 0) {
        if (b->mInstance == 0) {
            return 1;
        }
        return ((sWorldInstance*)a->mInstance)->mResId < ((sWorldInstance*)b->mInstance)->mResId;
    }
    if (b->mInstance != 0) {
        return 0;
    }
    return ((sTerrainPatch*)a->mPatch)->mKey < ((sTerrainPatch*)b->mPatch)->mKey;
}

static inline void visit_003369D8(sSpaceHashRoot* c, char* flag, sSpaceHashCollect* q, sGroundProbe* p)
{
    cSpaceHash_walkColumn(flag, q, q, p, c->mNode, &c->mCell);
}

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_queryGround);
extern "C" int cSpaceHash_queryGround(sSpaceHashRoot* self, float* pos, sSphereVec4* outP, sSphereVec4* outN);

//100%
typedef int (*Test_336D40)(void*);
typedef sSpaceHashBox* (*GetBox_336D40)(void*);

extern "C" int cWorldIntType_testInstance(void* q, void* node, void* buf, int cap, int mode);

static inline int overlapNode_336D40(const cWorldIntType* q, const sWorldInstance* n)
{
    int r = 0;
    if (q->mMax.x > n->mMin[0] && q->mMin.x < n->mMax[0] &&
        q->mMax.y > n->mMin[1] && q->mMin.y < n->mMax[1] &&
        q->mMax.z > n->mMin[2] && q->mMin.z < n->mMax[2]) {
        r = 1;
    }
    return r;
}

static inline int overlapBox_336D40(const cWorldIntType* q, const sSpaceHashBox* o)
{
    int r = 0;
    if (q->mMax.x > o->mMin.x && q->mMin.x < o->mMax.x &&
        q->mMax.y > o->mMin.y && q->mMin.y < o->mMax.y &&
        q->mMax.z > o->mMin.z && q->mMin.z < o->mMax.z) {
        r = 1;
    }
    return r;
}

static inline void collect_336D40(sSpaceHashCollect* ctx, sWorldInstance* node, int mode)
{
    int n = *ctx->mCount;
    *ctx->mCount += cWorldIntType_testInstance(ctx->mQuery, node, &ctx->mHits[n], ctx->mCapacity - n, mode);
}

extern "C" void cSpaceHash_collectSceneryHit(void* vctx, void* vnode)
{
    sSpaceHashCollect* ctx = (sSpaceHashCollect*)vctx;
    sWorldInstance* node = (sWorldInstance*)vnode;
    int mode = ctx->mArg ? 3 : 1;
    int flags = node->mFlags;
    if (flags & 0x20) {
        if (overlapNode_336D40(ctx->mQuery, node)) {
            collect_336D40(ctx, node, mode);
        }
    } else if (flags & 0x40) {
        sWorldVEntry* vt = node->mEntity->mVtable;
        if (((Test_336D40)vt[44].mFn)((char*)node->mEntity + vt[44].mDelta)) {
            sWorldVEntry* vt2 = node->mEntity->mVtable;
            sSpaceHashBox* b = ((GetBox_336D40)vt2[45].mFn)((char*)node->mEntity + vt2[45].mDelta);
            if (overlapBox_336D40(ctx->mQuery, b)) {
                collect_336D40(ctx, node, mode);
            }
        }
    }
}

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_collectSceneryHits);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cSpaceHash_collectSceneryHits(void* self, void* q, sWorldHit* hits, int max, int a4);

// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_003378C0(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

static inline int isBetter_003378C0(sWorldHit* a, sWorldHit* b)
{
    if (a->mInstance != 0) {
        if (b->mInstance == 0) {
            return 1;
        }
        return ((sWorldInstance*)a->mInstance)->mResId < ((sWorldInstance*)b->mInstance)->mResId;
    }
    if (b->mInstance != 0) {
        return 0;
    }
    return ((sTerrainPatch*)a->mPatch)->mKey < ((sTerrainPatch*)b->mPatch)->mKey;
}

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_queryNearestScenery);
extern "C" float cSpaceHash_queryNearestScenery(void* self, char* q, sWorldHit* out, int a3);

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_findNearestRail);

extern "C" void* func_003388E0(void* p, ...)
{
    return p;
}

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_walkInstances);

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_walkObjects);

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_walkInstancesPatches);

INCLUDE_ASM("intersect/worldsphtree", cOverlapList_walkAll);

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_walkHits);

//100%
extern "C" void cSpaceHash_collectPatchHit(void* ctx, void* obj);
extern "C" void cSpaceHash_collectInstanceHit(void* ctx, void* obj);
extern "C" void cSpaceHash_collectSubtreeHits(void* self, void* ctx);

static inline int Classify_DBE8(sGroundProbe* ctx, sSpaceHashCell* c)
{
    int bits = (c->mLevel + 0x7F) << 23;
    float s = *(float*)&bits;
    float* p = ctx->mPos;
    if (p[0] < ((float)c->mX - 0.2f) * s) {
        return 1;
    }
    if (((float)(c->mX + 1) + 0.2f) * s < p[0]) {
        return 1;
    }
    if (p[1] < ((float)c->mY - 0.2f) * s) {
        return 1;
    }
    if (((float)(c->mY + 1) + 0.2f) * s < p[1]) {
        return 1;
    }
    return 2;
}

extern "C" void cSpaceHash_walkColumn(char* flag, sSpaceHashCollect* q, sSpaceHashCollect* q2, sGroundProbe* vctx, cSpaceHashNode* node, sSpaceHashCell* cell)
{
    int r = Classify_DBE8(vctx, cell);
    if (r == 0) {
        sSpaceHashItem* o;
        for (o = node->mLists[SPACEHASH_PATCHES].mHead; o != 0; o = o->mNext) {
            cSpaceHash_collectPatchHit(q2, o);
        }
        for (o = node->mLists[SPACEHASH_INSTANCES].mHead; o != 0; o = o->mNext) {
            cSpaceHash_collectInstanceHit(q2, o);
        }
        if (node->mChild[0][0][0]) {
            cSpaceHash_collectSubtreeHits(node->mChild[0][0][0], q2);
        }
        if (node->mChild[0][0][1]) {
            cSpaceHash_collectSubtreeHits(node->mChild[0][0][1], q2);
        }
        if (node->mChild[0][1][0]) {
            cSpaceHash_collectSubtreeHits(node->mChild[0][1][0], q2);
        }
        if (node->mChild[0][1][1]) {
            cSpaceHash_collectSubtreeHits(node->mChild[0][1][1], q2);
        }
        if (node->mChild[1][0][0]) {
            cSpaceHash_collectSubtreeHits(node->mChild[1][0][0], q2);
        }
        if (node->mChild[1][0][1]) {
            cSpaceHash_collectSubtreeHits(node->mChild[1][0][1], q2);
        }
        if (node->mChild[1][1][0]) {
            cSpaceHash_collectSubtreeHits(node->mChild[1][1][0], q2);
        }
        if (node->mChild[1][1][1]) {
            cSpaceHash_collectSubtreeHits(node->mChild[1][1][1], q2);
        }
    } else if (r == 2) {
        sSpaceHashItem* o;
        for (o = node->mLists[SPACEHASH_PATCHES].mHead; o != 0; o = o->mNext) {
            cSpaceHash_collectPatchHit(q, o);
        }
        for (o = node->mLists[SPACEHASH_INSTANCES].mHead; o != 0; o = o->mNext) {
            cSpaceHash_collectInstanceHit(q, o);
        }
        if (cell->mLevel == 11) {
            return;
        }
        sSpaceHashCell sub;
        sub.mLevel = cell->mLevel - 1;
        sub.mX = cell->mX * 2;
        sub.mY = cell->mY * 2;
        sub.mZ = cell->mZ * 2;
        if (node->mChild[0][0][0]) {
            cSpaceHash_walkColumn(flag, q, q2, vctx, node->mChild[0][0][0], &sub);
        }
        sub.mX++;
        if (node->mChild[1][0][0]) {
            cSpaceHash_walkColumn(flag, q, q2, vctx, node->mChild[1][0][0], &sub);
        }
        sub.mY++;
        if (node->mChild[1][1][0]) {
            cSpaceHash_walkColumn(flag, q, q2, vctx, node->mChild[1][1][0], &sub);
        }
        sub.mX--;
        if (node->mChild[0][1][0]) {
            cSpaceHash_walkColumn(flag, q, q2, vctx, node->mChild[0][1][0], &sub);
        }
        sub.mZ++;
        if (node->mChild[0][1][1]) {
            cSpaceHash_walkColumn(flag, q, q2, vctx, node->mChild[0][1][1], &sub);
        }
        sub.mX++;
        if (node->mChild[1][1][1]) {
            cSpaceHash_walkColumn(flag, q, q2, vctx, node->mChild[1][1][1], &sub);
        }
        sub.mY--;
        if (node->mChild[1][0][1]) {
            cSpaceHash_walkColumn(flag, q, q2, vctx, node->mChild[1][0][1], &sub);
        }
        sub.mX--;
        if (node->mChild[0][0][1]) {
            cSpaceHash_walkColumn(flag, q, q2, vctx, node->mChild[0][0][1], &sub);
        }
    }
}

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_walkSceneryHits);

INCLUDE_ASM("intersect/worldsphtree", cSpaceHash_walkRails);

INCLUDE_ASM("intersect/worldsphtree", __sti__worldsphtree_cpp);

INCLUDE_ASM("intersect/worldsphtree", cAIFwdDiffEntry_cAIFwdDiffEntry);

//100%
void cWorldIntType_refinePatch__FPv(void* self)
{
}

//100%
float cWorldLine_getRadius__FPv(void* self)
{
    cWorldLine* t = (cWorldLine*)self;
    return t->mRadius;
}

//100%
extern "C" float cWorldSphere_getRadius(void* self)
{
    cWorldSphere* t = (cWorldSphere*)self;
    if (t->mKind == 0) {
        return -1.0f;
    }
    return t->mRadius * 2.0f;
}

//100%
// Visits node and every descendant with cOverlapList_collectNodeInstances.
extern "C" void cOverlapList_collectSubtreeInstances(cSpaceHashNode* self, sOverlapSink* ctx)
{
    cOverlapList_collectNodeInstances(ctx, self);
    if (self->mChild[0][0][0] != 0) {
        cOverlapList_collectSubtreeInstances(self->mChild[0][0][0], ctx);
    }
    if (self->mChild[0][0][1] != 0) {
        cOverlapList_collectSubtreeInstances(self->mChild[0][0][1], ctx);
    }
    if (self->mChild[0][1][0] != 0) {
        cOverlapList_collectSubtreeInstances(self->mChild[0][1][0], ctx);
    }
    if (self->mChild[0][1][1] != 0) {
        cOverlapList_collectSubtreeInstances(self->mChild[0][1][1], ctx);
    }
    if (self->mChild[1][0][0] != 0) {
        cOverlapList_collectSubtreeInstances(self->mChild[1][0][0], ctx);
    }
    if (self->mChild[1][0][1] != 0) {
        cOverlapList_collectSubtreeInstances(self->mChild[1][0][1], ctx);
    }
    if (self->mChild[1][1][0] != 0) {
        cOverlapList_collectSubtreeInstances(self->mChild[1][1][0], ctx);
    }
    if (self->mChild[1][1][1] != 0) {
        cOverlapList_collectSubtreeInstances(self->mChild[1][1][1], ctx);
    }
}

//100%
extern "C" void cOverlapList_collectSubtreeObjects(void* self, sOverlapSink* out)
{
    cSpaceHashNode* t = (cSpaceHashNode*)self;
    sSpaceHashItem* p;
    for (p = t->mLists[SPACEHASH_OBJECTS].mHead; p != 0; p = p->mNext) {
        out->mItems[(*out->mCount)++] = p;
    }
    if (t->mChild[0][0][0]) cOverlapList_collectSubtreeObjects(t->mChild[0][0][0], out);
    if (t->mChild[0][0][1]) cOverlapList_collectSubtreeObjects(t->mChild[0][0][1], out);
    if (t->mChild[0][1][0]) cOverlapList_collectSubtreeObjects(t->mChild[0][1][0], out);
    if (t->mChild[0][1][1]) cOverlapList_collectSubtreeObjects(t->mChild[0][1][1], out);
    if (t->mChild[1][0][0]) cOverlapList_collectSubtreeObjects(t->mChild[1][0][0], out);
    if (t->mChild[1][0][1]) cOverlapList_collectSubtreeObjects(t->mChild[1][0][1], out);
    if (t->mChild[1][1][0]) cOverlapList_collectSubtreeObjects(t->mChild[1][1][0], out);
    if (t->mChild[1][1][1]) cOverlapList_collectSubtreeObjects(t->mChild[1][1][1], out);
}

//100%
extern "C" void cOverlapList_collectNodeInstances(sOverlapSink* ctx, void* tree);

static inline void add_340C20(sOverlapSink* s, void* p)
{
    unsigned int* cnt = s->mCount;
    int n = *cnt;
    s->mItems[n] = p;
    *cnt = n + 1;
}

static inline int overlap_340C20(const sSpaceHashBox* b, const sTerrainPatch* n)
{
    int r = 0;
    if (b->mMin.x <= n->mMax[0] && b->mMax.x >= n->mMin[0] &&
        b->mMin.y <= n->mMax[1] && b->mMax.y >= n->mMin[1] &&
        b->mMin.z <= n->mMax[2] && b->mMax.z >= n->mMin[2]) {
        r = 1;
    }
    return r;
}

extern "C" void cOverlapList_collectSubtreeInstancesPatches(cSpaceHashNode* self, sOverlapBuild* ctx)
{
    cOverlapList_collectNodeInstances(&ctx->mInstances, self);
    sOverlapSink* s = &ctx->mPatches;
    for (sTerrainPatch* p = (sTerrainPatch*)self->mLists[SPACEHASH_PATCHES].mHead; p != 0; p = (sTerrainPatch*)p->mLink.mNext) {
        if (overlap_340C20(s->mBox, p)) {
            add_340C20(s, p);
        }
    }
    if (self->mChild[0][0][0]) cOverlapList_collectSubtreeInstancesPatches(self->mChild[0][0][0], ctx);
    if (self->mChild[0][0][1]) cOverlapList_collectSubtreeInstancesPatches(self->mChild[0][0][1], ctx);
    if (self->mChild[0][1][0]) cOverlapList_collectSubtreeInstancesPatches(self->mChild[0][1][0], ctx);
    if (self->mChild[0][1][1]) cOverlapList_collectSubtreeInstancesPatches(self->mChild[0][1][1], ctx);
    if (self->mChild[1][0][0]) cOverlapList_collectSubtreeInstancesPatches(self->mChild[1][0][0], ctx);
    if (self->mChild[1][0][1]) cOverlapList_collectSubtreeInstancesPatches(self->mChild[1][0][1], ctx);
    if (self->mChild[1][1][0]) cOverlapList_collectSubtreeInstancesPatches(self->mChild[1][1][0], ctx);
    if (self->mChild[1][1][1]) cOverlapList_collectSubtreeInstancesPatches(self->mChild[1][1][1], ctx);
}

//100%
extern "C" void cOverlapList_collectNodeInstances(sOverlapSink* ctx, void* tree);

static inline void add_340DC0(sOverlapSink* s, void* p)
{
    unsigned int* cnt = s->mCount;
    int n = *cnt;
    s->mItems[n] = p;
    *cnt = n + 1;
}

static inline int overlap_340DC0(const sSpaceHashBox* b, const sTerrainPatch* n)
{
    int r = 0;
    if (b->mMin.x <= n->mMax[0] && b->mMax.x >= n->mMin[0] &&
        b->mMin.y <= n->mMax[1] && b->mMax.y >= n->mMin[1] &&
        b->mMin.z <= n->mMax[2] && b->mMax.z >= n->mMin[2]) {
        r = 1;
    }
    return r;
}

extern "C" void cOverlapList_collectSubtreeAll(cSpaceHashNode* self, sOverlapBuild* ctx)
{
    cOverlapList_collectNodeInstances(&ctx->mInstances, self);
    sOverlapSink* s = &ctx->mPatches;
    for (sTerrainPatch* p = (sTerrainPatch*)self->mLists[SPACEHASH_PATCHES].mHead; p != 0; p = (sTerrainPatch*)p->mLink.mNext) {
        if (overlap_340DC0(s->mBox, p)) {
            add_340DC0(s, p);
        }
    }
    s = &ctx->mObjects;
    for (sSpaceHashItem* q = self->mLists[SPACEHASH_OBJECTS].mHead; q != 0; q = q->mNext) {
        add_340DC0(s, q);
    }
    if (self->mChild[0][0][0]) cOverlapList_collectSubtreeAll(self->mChild[0][0][0], ctx);
    if (self->mChild[0][0][1]) cOverlapList_collectSubtreeAll(self->mChild[0][0][1], ctx);
    if (self->mChild[0][1][0]) cOverlapList_collectSubtreeAll(self->mChild[0][1][0], ctx);
    if (self->mChild[0][1][1]) cOverlapList_collectSubtreeAll(self->mChild[0][1][1], ctx);
    if (self->mChild[1][0][0]) cOverlapList_collectSubtreeAll(self->mChild[1][0][0], ctx);
    if (self->mChild[1][0][1]) cOverlapList_collectSubtreeAll(self->mChild[1][0][1], ctx);
    if (self->mChild[1][1][0]) cOverlapList_collectSubtreeAll(self->mChild[1][1][0], ctx);
    if (self->mChild[1][1][1]) cOverlapList_collectSubtreeAll(self->mChild[1][1][1], ctx);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSpaceHash_collectPatchHit(void* ctx, void* obj);
extern "C" void cSpaceHash_collectInstanceHit(void* ctx, void* obj);

extern "C" void cSpaceHash_collectSubtreeHits(void* self, void* ctx)
{
    cSpaceHashNode* t = (cSpaceHashNode*)self;
    sSpaceHashItem* p;
    for (p = t->mLists[SPACEHASH_PATCHES].mHead; p != 0; p = p->mNext) {
        cSpaceHash_collectPatchHit(ctx, p);
    }
    for (p = t->mLists[SPACEHASH_INSTANCES].mHead; p != 0; p = p->mNext) {
        cSpaceHash_collectInstanceHit(ctx, p);
    }
    if (t->mChild[0][0][0]) cSpaceHash_collectSubtreeHits(t->mChild[0][0][0], ctx);
    if (t->mChild[0][0][1]) cSpaceHash_collectSubtreeHits(t->mChild[0][0][1], ctx);
    if (t->mChild[0][1][0]) cSpaceHash_collectSubtreeHits(t->mChild[0][1][0], ctx);
    if (t->mChild[0][1][1]) cSpaceHash_collectSubtreeHits(t->mChild[0][1][1], ctx);
    if (t->mChild[1][0][0]) cSpaceHash_collectSubtreeHits(t->mChild[1][0][0], ctx);
    if (t->mChild[1][0][1]) cSpaceHash_collectSubtreeHits(t->mChild[1][0][1], ctx);
    if (t->mChild[1][1][0]) cSpaceHash_collectSubtreeHits(t->mChild[1][1][0], ctx);
    if (t->mChild[1][1][1]) cSpaceHash_collectSubtreeHits(t->mChild[1][1][1], ctx);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSpaceHash_collectSceneryHit(void* ctx, void* obj);

extern "C" void cSpaceHash_collectSubtreeSceneryHits(void* self, void* ctx)
{
    cSpaceHashNode* t = (cSpaceHashNode*)self;
    sSpaceHashItem* p;
    for (p = t->mLists[SPACEHASH_INSTANCES].mHead; p != 0; p = p->mNext) {
        cSpaceHash_collectSceneryHit(ctx, p);
    }
    if (t->mChild[0][0][0]) cSpaceHash_collectSubtreeSceneryHits(t->mChild[0][0][0], ctx);
    if (t->mChild[0][0][1]) cSpaceHash_collectSubtreeSceneryHits(t->mChild[0][0][1], ctx);
    if (t->mChild[0][1][0]) cSpaceHash_collectSubtreeSceneryHits(t->mChild[0][1][0], ctx);
    if (t->mChild[0][1][1]) cSpaceHash_collectSubtreeSceneryHits(t->mChild[0][1][1], ctx);
    if (t->mChild[1][0][0]) cSpaceHash_collectSubtreeSceneryHits(t->mChild[1][0][0], ctx);
    if (t->mChild[1][0][1]) cSpaceHash_collectSubtreeSceneryHits(t->mChild[1][0][1], ctx);
    if (t->mChild[1][1][0]) cSpaceHash_collectSubtreeSceneryHits(t->mChild[1][1][0], ctx);
    if (t->mChild[1][1][1]) cSpaceHash_collectSubtreeSceneryHits(t->mChild[1][1][1], ctx);
}

extern "C" void* __sti__worldsphtree_cpp(int, int);

//100%
struct sCtx_3411B8 {
    sSphereVec4* pos;           // 0x00
    int a2;                     // 0x04
    int mask;                   // 0x08
    int* cnt;                   // 0x0C
    float* dist;                // 0x10
    sSpaceHashBox* box;         // 0x14
};

extern "C" void cSpaceHash_collectSubtreeRails(void* self, sCtx_3411B8* ctx)
{
    cSpaceHashNode* t = (cSpaceHashNode*)self;
    for (sSpaceHashObject* o = (sSpaceHashObject*)t->mLists[SPACEHASH_OBJECTS].mHead; o != 0; o = (sSpaceHashObject*)o->mLink.mNext) {
        int type = o->mType;
        if (type == 2) {
            func_0035C698(o->mObject, ctx->box, ctx->box, ctx->pos, ctx->mask, ctx->cnt, ctx->dist, ctx->a2);
        } else if (type == 3) {
            func_00348290(o->mObject, ctx->box, ctx->box, ctx->pos, ctx->mask, ctx->cnt, ctx->dist, ctx->a2);
        } else if (type == 1) {
            if (((sRailSegment*)o)->mSpline->mFlags & ctx->mask) {
                cRailSegment_findClosestPoint(o, ctx->box, ctx->pos, ctx->cnt, ctx->dist, ctx->a2);
            }
        }
    }
    if (t->mChild[0][0][0]) cSpaceHash_collectSubtreeRails(t->mChild[0][0][0], ctx);
    if (t->mChild[0][0][1]) cSpaceHash_collectSubtreeRails(t->mChild[0][0][1], ctx);
    if (t->mChild[0][1][0]) cSpaceHash_collectSubtreeRails(t->mChild[0][1][0], ctx);
    if (t->mChild[0][1][1]) cSpaceHash_collectSubtreeRails(t->mChild[0][1][1], ctx);
    if (t->mChild[1][0][0]) cSpaceHash_collectSubtreeRails(t->mChild[1][0][0], ctx);
    if (t->mChild[1][0][1]) cSpaceHash_collectSubtreeRails(t->mChild[1][0][1], ctx);
    if (t->mChild[1][1][0]) cSpaceHash_collectSubtreeRails(t->mChild[1][1][0], ctx);
    if (t->mChild[1][1][1]) cSpaceHash_collectSubtreeRails(t->mChild[1][1][1], ctx);
}

//99.38%
void* worldsphtreeStaticInit__FPv(void* self)
{
    return __sti__worldsphtree_cpp(1, 0xffff);
}

//100%
struct sVec4_341388 {
    float x, y, z, w;
    sVec4_341388() {}
    sVec4_341388(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

struct sDef_341388 {
    int f00;
    short type;
    short pad06;
    float time;
    float f0C;
    float f10;
    float x, y, z;
};

struct sObj_341388 {
    int pad00[3];
    void** vt;
    int pad10[2];
    char* mtx;
    int pad1C;
    sVec4_341388 pos;
    float speed;
    float f34;
    int t38;
    int t3C;
    int type;
};

extern void* D_004914E0[];
extern char* D_004A5B64;
extern sVec4_341388 D_004FF120_341388[] __asm__("D_004FF120");
extern sVec4_341388 D_004FF150_341388[] __asm__("D_004FF150");
extern "C" void* func_0034FB00(void* self, void* a1, int type, void* a3);

// PORT: PS2-only VU0 inline asm (v / |v|).
static inline sVec4_341388 vu0Normalize_341388(const sVec4_341388& v)
{
    sVec4_341388 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vrsqrt    Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf3, Q\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(v)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (v * s).
static inline sVec4_341388 vu0Scale_341388(const sVec4_341388& v, float s)
{
    sVec4_341388 r;
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (matrix * vector).
static inline sVec4_341388 vu0Xform_341388(const sVec4_341388& v, const char* m)
{
    sVec4_341388 r;
    __asm__(
        "lqc2      $vf8, %2\n"
        "lqc2      $vf4, 0x0(%1)\n"
        "lqc2      $vf5, 0x10(%1)\n"
        "lqc2      $vf6, 0x20(%1)\n"
        "lqc2      $vf7, 0x30(%1)\n"
        "vmulax.xyzw ACC, $vf4, $vf8x\n"
        "vmadday.xyzw ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf12, $vf7, $vf8w\n"
        "sqc2      $vf12, %0\n"
        : "=m"(r)
        : "r"(m), "m"(v)
        : "memory");
    return r;
}

extern "C" sObj_341388* cBoostNode_construct(sObj_341388* self, void* a1, int a2, void* a3, sDef_341388* def)
{
    func_0034FB00(self, a1, a2, a3);
    self->vt = D_004914E0;
    int type = def->type;
    self->type = type;
    self->t38 = (int)(def->time * (float)*(int*)(D_004A5B64 + 0x10));
    if (def->x == 0.0f && def->y == 0.0f && def->z == 0.0f) {
        if (type == 2) {
            self->pos = *D_004FF150_341388;
        } else {
            self->pos = *D_004FF120_341388;
        }
    } else {
        self->pos = vu0Normalize_341388(sVec4_341388(def->x, def->y, def->z, 0.0f));
    }
    self->speed = def->f10 * 27.77777862548828f;
    self->f34 = def->f0C;
    self->t3C = self->type ? self->t38 : 0;
    if (self->type == 2) {
        char* m = self->mtx + 0x10;
        self->pos = vu0Xform_341388(vu0Scale_341388(self->pos, -1.0f), m);
        self->speed = -self->speed;
    }
    return self;
}

//100%
extern "C" void* cInstanceNode_cInstanceNode(void* self, void* a1, void* stream);
extern void* D_004914E0[];
struct sVEntry_func_00341548 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void* func_00341548(void* self, void* a1, void* stream)
{
    cInstanceNode_cInstanceNode(self, a1, stream);
    *(void***)((char*)self + 0xC) = D_004914E0;
    sVEntry_func_00341548* vt = *(sVEntry_func_00341548**)stream;
    vt[2].fn((char*)stream + vt[2].delta, (char*)self + 0x20, 0x30);
    return self;
}

extern void* D_004914E0[];
extern "C" void* func_0034FBF0(void*);

//100%
void* cBoostNode_destroy__FPv(void* self)
{
    *(int*)((char*)self + 0xc) = (int)(void*)D_004914E0;
    return func_0034FBF0(self);
}

//100%
extern "C" int World_GetRiderCount();
extern "C" void** World_GetRider(int i);

struct sVEnt_003415D0 { short delta; short index; void* fn; };
typedef void (*Fn0_003415D0)(void*);
typedef void (*Fn1_003415D0)(void*, void*);
typedef void (*FnI_003415D0)(void*, int);
typedef int (*Test0_003415D0)(void*);
typedef int (*Test_003415D0)(void*, int);

struct sNode_003415D0 {
    int pad00[3];
    sVEnt_003415D0* vt;
    int pad10[2];
    int a18;
    int pad1C[6];
    float f34;
    int pad38;
    int t3C;
    int type;
};

extern "C" void cBoostNode_update(sNode_003415D0* self)
{
    int hit = 0;
    if (self->type != 1) {
        hit = 1;
    }
    int t = self->t3C;
    if (t > 0) {
        int n = t - 1;
        self->t3C = n;
        if (n > 0) {
            hit = 1;
        }
    }
    sVEnt_003415D0* vt = self->vt;
    ((Fn0_003415D0)vt[49].fn)((char*)self + vt[49].delta);
    if (self->type == 1 || self->t3C <= 0) {
        for (int i = 0; i < World_GetRiderCount(); i++) {
            void** obj = World_GetRider(i);
            if (self->type == 2) {
                sVEnt_003415D0* ovt = (sVEnt_003415D0*)*obj;
                if (((Test0_003415D0)ovt[9].fn)((char*)obj + ovt[9].delta) != 0) continue;
            }
            sVEnt_003415D0* ovt = (sVEnt_003415D0*)*obj;
            if (((Test_003415D0)ovt[3].fn)((char*)obj + ovt[3].delta, self->a18) != 0) {
                hit = 1;
                if (self->f34 < 0.0f) {
                    sVEnt_003415D0* v = self->vt;
                    ((Fn1_003415D0)v[48].fn)((char*)self + v[48].delta, obj);
                } else {
                    sVEnt_003415D0* v = self->vt;
                    ((Fn1_003415D0)v[47].fn)((char*)self + v[47].delta, obj);
                }
            }
        }
    }
    sVEnt_003415D0* v2 = self->vt;
    ((Fn0_003415D0)v2[50].fn)((char*)self + v2[50].delta);
    if (hit == 0) {
        sVEnt_003415D0* v3 = self->vt;
        ((FnI_003415D0)v3[34].fn)((char*)self + v3[34].delta, 1);
    }
}

//100%
struct sVec4_341770 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_341770 vu0Scale_341770(const sVec4_341770& v, float s)
{
    sVec4_341770 r;
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

class cMover_341770 {
public:
    virtual void v01();
    virtual sVec4_341770* getVelocity();
    virtual void v03();
    virtual void setVelocity(sVec4_341770* v);
};

extern "C" float World_GetSecondsPerTick();

extern "C" void cBoostNode_scaleVelocity(void* self, cMover_341770* obj)
{
    sVec4_341770 u = vu0Scale_341770(vu0Scale_341770(*obj->getVelocity(), *(float*)((char*)self + 0x34) + 1.0f), World_GetSecondsPerTick());
    obj->setVelocity(&u);
}

//100%
struct sVec4_341818 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (v / |v|).
static inline sVec4_341818 vu0Normalize_341818(const sVec4_341818& v)
{
    sVec4_341818 r;
    __asm__(
        "lqc2      $vf3, %1\n"
        "vaddw.x   $vf6, $vf0, $vf0w\n"
        "vmul.xyzw $vf4, $vf3, $vf3\n"
        "vadday.x  ACC, $vf4, $vf4y\n"
        "vmaddaz.x ACC, $vf6, $vf4z\n"
        "vmaddw.x  $vf4, $vf6, $vf4w\n"
        "vrsqrt    Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf5, $vf3, Q\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(v)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0Dot_341818(const sVec4_341818& a, const sVec4_341818& b)
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
static inline sVec4_341818 vu0Scale_341818(const sVec4_341818& v, float s)
{
    sVec4_341818 r;
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

class cMover_341818 {
public:
    virtual void v01();
    virtual sVec4_341818* getVelocity();
    virtual void v03();
    virtual void setVelocity(sVec4_341818* v);
};

extern "C" float World_GetSecondsPerTick();

struct sParams_341818 {
    sVec4_341818 dir;
    float speed;
    float scale;
};

struct sSph_341818 {
    char pad00[0x20];
    sParams_341818 params;
    int type;
};

static inline void push_341818(sParams_341818* p, cMover_341818* obj, const sVec4_341818& dir, float amount)
{
    sVec4_341818 u = vu0Scale_341818(vu0Scale_341818(vu0Scale_341818(dir, amount), p->scale), World_GetSecondsPerTick());
    obj->setVelocity(&u);
}

extern "C" void cBoostNode_pushVelocity(sSph_341818* self, cMover_341818* obj)
{
    sVec4_341818 vel = *obj->getVelocity();
    sVec4_341818 dir = self->params.dir;
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f) {
        dir = vu0Normalize_341818(vel);
    }
    float d = vu0Dot_341818(vel, dir);
    float diff = self->params.speed - d;
    sParams_341818* p = &self->params;
    if (self->type == 2) {
        if (d >= 0.0f) {
            sVec4_341818 u = vu0Scale_341818(vu0Scale_341818(vu0Scale_341818(dir, p->speed), p->scale), World_GetSecondsPerTick());
            obj->setVelocity(&u);
        }
    } else if (diff > 0.0f) {
        sVec4_341818 u = vu0Scale_341818(vu0Scale_341818(vu0Scale_341818(dir, diff), p->scale), World_GetSecondsPerTick());
        obj->setVelocity(&u);
    }
}

//100%
extern "C" void cBoostNode_onMessage(void* self, int a1)
{
    if (a1 == 1) {
        *(int*)((char*)self + 0x3c) = *(int*)((char*)self + 0x38);
    }
}

//100%
struct sSerVEntry_00341A50 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void func_0034FE90(void* self, void* stream);

extern "C" void cBoostNode_writeToReplayFrame(void* self, void* stream)
{
    func_0034FE90(self, stream);
    sSerVEntry_00341A50* vt = *(sSerVEntry_00341A50**)stream;
    vt[1].fn((char*)stream + vt[1].delta, (char*)self + 0x20, 0x30);
}

//100%
extern char* D_004A5B64;
extern void* D_00490B10[];
extern "C" void func_0034D9B0(void* p, int a1, int a2, void* obj, int a4);
extern "C" float func_00351508(void* inst);
float AIrandf(float lo, float hi);
float func_00317890(float a, float b);

struct sSphFloat_1AA0 {
    unsigned short id;  // 0x00
    char pad02[0x2];
    int active;         // 0x04
    int atLimit;        // 0x08
    int fC;             // 0x0C
    float speed;        // 0x10
    float min;          // 0x14
    float max;          // 0x18
    float value;        // 0x1C
    float start;        // 0x20
    char pad24[0x18];
    void** vt;          // 0x3C
    char pad40[0x2];
    unsigned short flags; // 0x42
    char pad44[0x20];
    void* inst;         // 0x64
};

struct sSphFloatDef_1AA0 {
    int f0;
    unsigned short id;  // 0x04
    char pad06[0x2];
    int dir;            // 0x08
    float min;          // 0x0C
    float max;          // 0x10
    float speed;        // 0x14
    float speedVar;     // 0x18
    float value;        // 0x1C
    int random;         // 0x20
    int f24;            // 0x24
};

struct sFloat_1AA0 {
    float v;
};

static inline void setRate_1AA0(sFloat_1AA0* dst, float v, float dflt)
{
    float r;
    if (v >= 0.0f) {
        r = v * 0.03333333507180214f;
    } else {
        r = dflt;
    }
    dst->v = r;
}

static inline void setRateMax_1AA0(sFloat_1AA0* dst, float v, char* info)
{
    float r;
    if (v < 0.0f) {
        r = *(float*)(info + 0x14);
    } else {
        r = v * 0.03333333507180214f;
    }
    dst->v = r;
}

// Animated float constructor: range and start value (frames -> seconds), optional random start and speed.
extern "C" void* cAnimObjectNode_construct(sSphFloat_1AA0* self, int a1, int a2, char* obj, sSphFloatDef_1AA0* def)
{
    func_0034D9B0((char*)self + 0x1C, a1, a2, obj, def->f24 != 0);
    self->vt = D_00490B10;
    float v = 0.0f;
    char* info = *(char**)(obj + 0x80);
    if (self->inst != 0) {
        v = func_00351508(self->inst);
    }
    self->id = def->id;
    setRate_1AA0((sFloat_1AA0*)&self->min, def->min, v);
    setRateMax_1AA0((sFloat_1AA0*)&self->max, def->max, info);
    v = def->value;
    if (v < 0.0f) {
        v = self->min;
    } else {
        v *= 0.03333333507180214f;
    }
    if (v < self->min) {
        v = self->min;
    }
    if (self->max < v) {
        v = self->max;
    }
    if (def->random != 0) {
        v = AIrandf(self->min, self->max);
    }
    self->value = v;
    if (def->speedVar != 0.0f) {
        self->speed = func_00317890(def->speed * 0.03333333507180214f, def->speedVar * 0.03333333507180214f) / (float)*(int*)(D_004A5B64 + 0x10);
    } else {
        self->speed = def->speed * 0.03333333507180214f / (float)*(int*)(D_004A5B64 + 0x10);
    }
    if (def->dir == 1) {
        self->speed = -self->speed;
    }
    self->start = self->value;
    self->active = 1;
    self->flags |= 1;
    self->fC = 0;
    self->atLimit = 0;
    return self;
}

//100%
struct sVEntry00341C80 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void* func_0034DAC8(void* p, int a1, void* stream);
extern void* D_00490B10[];

extern "C" void* func_00341C80(void* self, int a1, sVEntry00341C80** stream)
{
    func_0034DAC8((char*)self + 0x1C, a1, stream);
    *(void***)((char*)self + 0x3C) = D_00490B10;
    (*stream)[2].fn((char*)stream + (*stream)[2].delta, self, 0x1C);
    *(unsigned short*)((char*)self + 0x42) |= 1;
    return self;
}

//100%
extern "C" void func_0034DBA8(void* p, int flags);
void operator_delete(int* ptr);
extern void* D_00490B10[];

extern "C" void cAnimObjectNode_destroy(void* self, int flags)
{
    *(void***)((char*)self + 0x3C) = D_00490B10;
    func_0034DBA8((char*)self + 0x1C, 0);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
struct sWrapFloat_1E48;
struct sBounceFloat_1EC0;
struct sClampFloat_1F38;
extern "C" void cAnimObjectNode_stepWrap(sWrapFloat_1E48* s);
extern "C" void cAnimObjectNode_stepPingPong(sBounceFloat_1EC0* s);
extern "C" void cAnimObjectNode_stepClamp(sClampFloat_1F38* s);
extern "C" int func_0034EBA0(void* p);

struct sVEntry_00341D48 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

extern "C" int cAnimObjectNode_update(void* self)
{
    *(float*)((char*)self + 0x24) = 10000000000.0f;
    *(float*)((char*)self + 0x28) = 10000000000.0f;
    if (*(int*)((char*)self + 0x8) != 0) {
        return 1;
    }
    if (*(int*)((char*)self + 0x4) != 0 && *(int*)((char*)self + 0xC) >= 0) {
        if (*(int*)((char*)self + 0xC) > 0) {
            *(int*)((char*)self + 0xC) -= 1;
        } else {
            *(float*)((char*)self + 0x24) = *(float*)((char*)self + 0x1C);
            switch (*(short*)self) {
            case 2:
                cAnimObjectNode_stepPingPong((sBounceFloat_1EC0*)self);
                break;
            case 1:
                cAnimObjectNode_stepWrap((sWrapFloat_1E48*)self);
                break;
            default:
                cAnimObjectNode_stepClamp((sClampFloat_1F38*)self);
                break;
            }
            if (func_0034EBA0((char*)self + 0x1C) == 0) {
                return 0;
            }
        }
    }
    char* obj = (char*)self + 0x30;
    *(unsigned short*)((char*)self + 0x42) |= 1;
    *(float*)((char*)self + 0x20) = *(float*)((char*)self + 0x1C);
    if (*(int*)((char*)self + 0x8) == 0) {
        return 1;
    }
    sVEntry_00341D48* vt = *(sVEntry_00341D48**)((char*)self + 0x3C);
    vt[0x22].fn(obj + vt[0x22].delta, 1);
    return 0;
}

//100%
struct sWrapFloat_1E48 {
    char pad_0x00[0x10];
    float speed;    // 0x10
    float min;      // 0x14
    float max;      // 0x18
    float value;    // 0x1C
    char pad_0x20[0x8];
    float last;     // 0x28
};

extern "C" void cAnimObjectNode_stepWrap(sWrapFloat_1E48* s)
{
    if (s->speed >= 0.0f) {
        s->value += s->speed;
        s->last = s->value;
        if (s->value > s->max) {
            s->value = s->min + (s->value - s->max);
        }
    } else {
        s->value += s->speed;
        s->last = s->value;
        if (s->value < s->min) {
            s->value = s->max - (s->min - s->value);
        }
    }
}

//100%
struct sBounceFloat_1EC0 {
    char pad_0x00[0x10];
    float speed;    // 0x10
    float min;      // 0x14
    float max;      // 0x18
    float value;    // 0x1C
    char pad_0x20[0x8];
    float last;     // 0x28
};

extern "C" void cAnimObjectNode_stepPingPong(sBounceFloat_1EC0* s)
{
    if (s->speed >= 0.0f) {
        s->value += s->speed;
        s->last = s->value;
        if (s->value > s->max) {
            s->speed = -s->speed;
            s->value = s->max - (s->value - s->max);
        }
    } else {
        s->value += s->speed;
        s->last = s->value;
        if (s->value < s->min) {
            s->speed = -s->speed;
            s->value = s->min + (s->min - s->value);
        }
    }
}

//100%
struct sClampFloat_1F38 {
    char pad_0x00[0x8];
    int atLimit;    // 0x08
    char pad_0x0C[0x4];
    float speed;    // 0x10
    float min;      // 0x14
    float max;      // 0x18
    float value;    // 0x1C
    char pad_0x20[0x8];
    float last;     // 0x28
};

extern "C" void cAnimObjectNode_stepClamp(sClampFloat_1F38* s)
{
    if (s->speed >= 0.0f) {
        if (s->value == s->max) {
            s->atLimit = 1;
        }
        s->value += s->speed;
        s->last = s->value;
        if (s->value > s->max) {
            s->value = s->max;
        }
    } else {
        if (s->value == s->min) {
            s->atLimit = 1;
        }
        s->value += s->speed;
        s->last = s->value;
        if (s->value < s->min) {
            s->value = s->min;
        }
    }
}

void func_0034FCC0(void*);

//100%
extern "C" void cAnimObjectNode_onFinished(void* self, int a1)
{
    if (a1 != 0) {
        func_0034FCC0((char*)self + 0x30);
    }
}

//100%
extern char* D_004A5B64;
extern "C" void cMoveNode_v36(void* p);

extern "C" void cAnimObjectNode_onMessage(sClampFloat_1F38* self, int msg, float v)
{
    if (msg == 0x64) {
        *(int*)((char*)self + 0xC) = (int)(v * (float)*(int*)(D_004A5B64 + 0x10));
    } else if (msg == 0x65) {
        v = v * 0.03333333507180214f;
        if (self->min <= v && v <= self->max) {
            self->value = v;
        }
    } else if (msg == 0x66) {
        v = v * 0.03333333507180214f;
        self->speed = v / (float)*(int*)(D_004A5B64 + 0x10);
    } else if (msg == 0x67) {
        v = v * 0.03333333507180214f;
        float lim = *(float*)(*(char**)(*(char**)((char*)self + 0x48) + 0x80) + 0x14);
        if (lim < v) {
            v = lim;
        }
        if (v < 0.0f) {
            v = 0.0f;
        }
        self->max = v;
        if (v < self->value) {
            self->value = v;
        }
    } else if (msg == 0x68) {
        v = v * 0.03333333507180214f;
        float lim = *(float*)(*(char**)(*(char**)((char*)self + 0x48) + 0x80) + 0x14);
        if (lim < v) {
            v = lim;
        }
        if (v < 0.0f) {
            v = 0.0f;
        }
        self->min = v;
        if (self->value < v) {
            self->value = v;
        }
    } else if (msg == 0x69) {
        *(short*)self = 0;
    } else {
        cMoveNode_v36((char*)self + 0x30);
    }
}

//100%
extern "C" void func_0034E3D8(void* p, void* stream);
struct sVEntry_func_00342150 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cAnimObjectNode_writeToReplayFrame(void* self, void* stream)
{
    func_0034E3D8((char*)self + 0x1C, stream);
    sVEntry_func_00342150* vt = *(sVEntry_func_00342150**)stream;
    vt[1].fn((char*)stream + vt[1].delta, self, 0x1C);
}

//100%
extern char* D_004A5B64;
extern void* D_004908F8[];
extern "C" void func_0034D9B0(void* p, int a1, int a2, void* obj, int a4);
extern "C" float func_00351508(void* inst);

struct sSphCtl_003421A0 {
    int f00;            // 0x00
    int f04;            // 0x04
    float f08;          // 0x08
    float f0C;          // 0x0C
    float f10;          // 0x10
    float f14;          // 0x14
    float f18;          // 0x18
    float f1C;          // 0x1C
    float f20;          // 0x20
    float f24;          // 0x24
    int f28;            // 0x28
    int f2C;            // 0x2C
    char pad30[0x20];
    void** vt;          // 0x50
    char pad54[2];
    unsigned short flags; // 0x56
    char pad58[0x20];
    void* inst;         // 0x78
};

struct sFloat_003421A0 {
    float v;
};

static inline void setRate_003421A0(sFloat_003421A0* dst, float v, float dflt)
{
    float r;
    if (v >= 0.0f) {
        r = v * 0.03333333507180214f;
    } else {
        r = dflt;
    }
    dst->v = r;
}

static inline void setRateMax_003421A0(sFloat_003421A0* dst, float v, char* info)
{
    float r;
    if (v < 0.0f) {
        r = *(float*)(info + 0x14);
    } else {
        r = v * 0.03333333507180214f;
    }
    dst->v = r;
}

extern "C" void* cAnimTeeterNode_construct(sSphCtl_003421A0* self, int a1, char* obj, char* def)
{
    func_0034D9B0((char*)self + 0x30, a1, 4, obj, 0);
    self->vt = D_004908F8;
    float t = 0.0f;
    char* info = *(char**)(obj + 0x80);
    if (self->inst != 0) {
        t = func_00351508(self->inst);
    }
    setRate_003421A0((sFloat_003421A0*)&self->f10, *(float*)(def + 0x20), t);
    setRateMax_003421A0((sFloat_003421A0*)&self->f14, *(float*)(def + 0x24), info);
    self->f0C = *(float*)(def + 0x8);
    self->f08 = *(float*)(def + 0x4) * 9.999999974752427e-07f;
    self->f18 = *(float*)(def + 0xC) * 0.03333333507180214f / (float)*(int*)(D_004A5B64 + 0x10);
    self->f2C = *(int*)(def + 0x1C);
    self->f24 = *(float*)(def + 0x14) * 0.03333333507180214f;
    self->f1C = *(float*)(def + 0x18);
    self->f20 = *(float*)(def + 0x10);
    self->flags |= 1;
    self->f00 = 0;
    self->f04 = 0;
    self->f28 = 0;
    return self;
}

//100%
struct sVEntry003422E8 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void* func_0034DAC8(void* p, int a1, void* stream);
extern void* D_004908F8[];

extern "C" void* func_003422E8(void* self, int a1, sVEntry003422E8** stream)
{
    func_0034DAC8((char*)self + 0x30, a1, stream);
    *(void***)((char*)self + 0x50) = D_004908F8;
    (*stream)[2].fn((char*)stream + (*stream)[2].delta, self, 0x30);
    *(unsigned short*)((char*)self + 0x56) |= 1;
    return self;
}

//100%
extern "C" float World_GetSecondsPerTick();
extern "C" int func_0034EBA0(void* p);

struct sSphCtl_00342358 {
    float force;        // 0x00
    float step;         // 0x04
    float gain;         // 0x08
    float bounce;       // 0x0C
    float min;          // 0x10
    float max;          // 0x14
    float maxStep;      // 0x18
    float damping;      // 0x1C
    float stiffness;    // 0x20
    float rest;         // 0x24
    float vel;          // 0x28
    int f2C;            // 0x2C
    float pos;          // 0x30
    float pos34;        // 0x34
    float prev;         // 0x38
    float pos3C;        // 0x3C
    char pad40[0x16];
    unsigned short flags; // 0x56
};

// PORT: PS2 FPU abs.s via inline asm; use fabsf off-PS2.
static inline float absf_00342358(float x)
{
    float r;
    __asm__("abs.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

extern "C" int cAnimTeeterNode_update(sSphCtl_00342358* s)
{
    s->prev = s->pos;
    float dt = World_GetSecondsPerTick();
    float force = s->gain * s->force;
    if (s->gain < 0.0f) {
        force = -force;
    }
    float vel = s->vel;
    float maxStep = s->maxStep;
    float step = vel * dt;
    float acc = -s->stiffness * (s->pos - s->rest);
    acc += force;
    acc += -s->damping * vel;
    s->step = step;
    if (maxStep < absf_00342358(step)) {
        if (step < 0.0f) {
            s->step = -maxStep;
        } else {
            s->step = maxStep;
        }
    }
    float pos = s->pos + s->step;
    float nv = s->vel + acc * dt;
    s->pos = pos;
    s->pos3C = pos;
    s->vel = nv;
    if (pos < s->min) {
        s->pos = s->min;
        if (absf_00342358(nv) > 0.1f) {
            s->vel = nv * s->bounce;
        } else {
            s->step = 0.0f;
            s->vel = 0.0f;
        }
    } else if (s->max < pos) {
        s->pos = s->max;
        if (absf_00342358(nv) > 0.1f) {
            s->vel = nv * s->bounce;
        } else {
            s->step = 0.0f;
            s->vel = 0.0f;
        }
    }
    s->force = 0.0f;
    s->pos34 = s->pos;
    if (func_0034EBA0(&s->pos) == 0) {
        return 0;
    }
    s->flags |= 1;
    return 1;
}

//100%
extern "C" float cAnimTeeterNode_getStep(void* self)
{
    if (*(float*)((char*)self + 0x30) <= *(float*)((char*)self + 0x10) && *(float*)((char*)self + 0x4) < 0.0f) {
        return 0.0f;
    }
    if (*(float*)((char*)self + 0x30) >= *(float*)((char*)self + 0x14) && *(float*)((char*)self + 0x4) > 0.0f) {
        return 0.0f;
    }
    return *(float*)((char*)self + 0x4);
}

INCLUDE_ASM("intersect/worldsphtree", cAnimTeeterNode_applyForce);

//100%
extern "C" void func_0034E3D8(void* p, void* stream);
struct sVEntry_func_00342718 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

extern "C" void cAnimTeeterNode_writeToReplayFrame(void* self, void* stream)
{
    func_0034E3D8((char*)self + 0x30, stream);
    sVEntry_func_00342718* vt = *(sVEntry_func_00342718**)stream;
    vt[1].fn((char*)stream + vt[1].delta, self, 0x30);
}

//100%
struct sVec4_342768 {
    float x, y, z, w;
} __attribute__((aligned(16)));
struct sSphDef_342768 {
    int f00;
    short type;
    short pad06;
    float time;
    float f0C;
    float f10;
    float x, y, z;
};
struct sSph_342768 {
    int refs;
    void** vt;
    int pad08[2];
    sVec4_342768 pos;
    float f20;
    float f24;
    int t28;
    int t2C;
    int type;
    int pad34[3];
    int a40;
};
extern void* D_00490898[];
extern char* D_004A5B64;

extern "C" void* cBoostModifier_construct(sSph_342768* self, sSphDef_342768* def, int a2)
{
    self->refs = 1;
    self->vt = D_00490898;
    self->a40 = a2;
    int type = def->type;
    self->type = type;
    int t = (int)(def->time * (float)*(int*)(D_004A5B64 + 0x10));
    self->t28 = t;
    sVec4_342768 v;
    v.x = def->x;
    v.y = def->y;
    v.z = def->z;
    v.w = 0.0f;
    self->pos = v;
    self->f20 = def->f10 * 100.0f;
    self->f24 = def->f0C;
    self->t2C = type == 1 ? t : 0;
    return self;
}

//100%
struct sVEntry00342808 {
    short delta;
    short index;
    void* fn;
};

typedef void (*ReadFn00342808)(void*, void*, int);
typedef int (*ReadIntFn00342808)(void*);

extern void* D_00490898[];

extern "C" void* cBoostModifier_cBoostModifier(void* self, sVEntry00342808** stream)
{
    *(int*)((char*)self + 0x0) = 1;
    *(void***)((char*)self + 0x4) = D_00490898;
    ((ReadFn00342808)(*stream)[2].fn)((char*)stream + (*stream)[2].delta, (char*)self + 0x10, 0x30);
    *(int*)((char*)self + 0x40) = ((ReadIntFn00342808)(*stream)[3].fn)((char*)stream + (*stream)[3].delta);
    return self;
}

//100%
extern "C" int World_GetRiderCount();
extern "C" void** World_GetRider(int i);

struct sVEnt_00342880 { short delta; short index; void* fn; };
typedef void (*Fn0_00342880)(void*);
typedef void (*Fn1_00342880)(void*, void*);
typedef int (*Test_00342880)(void*, int);

extern "C" void cBoostModifier_update(sSph_342768* self)
{
    self->refs = 0;
    if (self->type == 0) {
        self->refs = 1;
    }
    int t = self->t2C;
    if (t > 0) {
        t--;
        self->t2C = t;
        if (t > 0) {
            self->refs = 1;
        }
    }
    sVEnt_00342880* vt = (sVEnt_00342880*)self->vt;
    ((Fn0_00342880)vt[9].fn)((char*)self + vt[9].delta);
    if (self->type == 1 || self->t2C <= 0) {
        for (int i = 0; i < World_GetRiderCount(); i++) {
            void** obj = World_GetRider(i);
            sVEnt_00342880* ovt = (sVEnt_00342880*)*obj;
            if (((Test_00342880)ovt[3].fn)((char*)obj + ovt[3].delta, self->a40) != 0) {
                self->refs = 1;
                if (self->f24 < 0.0f) {
                    sVEnt_00342880* v = (sVEnt_00342880*)self->vt;
                    ((Fn1_00342880)v[8].fn)((char*)self + v[8].delta, obj);
                } else {
                    sVEnt_00342880* v = (sVEnt_00342880*)self->vt;
                    ((Fn1_00342880)v[7].fn)((char*)self + v[7].delta, obj);
                }
            }
        }
    }
    sVEnt_00342880* v2 = (sVEnt_00342880*)self->vt;
    ((Fn0_00342880)v2[10].fn)((char*)self + v2[10].delta);
}

//100%
struct sVec4_3429E0 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sVec4_3429E0 vu0Scale_3429E0(const sVec4_3429E0& v, float s)
{
    sVec4_3429E0 r;
    int t;
    __asm__(
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

class cMover_3429E0 {
public:
    virtual void v01();
    virtual sVec4_3429E0* getVelocity();
    virtual void v03();
    virtual void setVelocity(sVec4_3429E0* v);
};

extern "C" float World_GetSecondsPerTick();

extern "C" void cBoostModifier_scaleVelocity(void* self, cMover_3429E0* obj)
{
    sVec4_3429E0 u = vu0Scale_3429E0(vu0Scale_3429E0(*obj->getVelocity(), *(float*)((char*)self + 0x24) + 1.0f), World_GetSecondsPerTick());
    obj->setVelocity(&u);
}

INCLUDE_ASM("intersect/worldsphtree", cBoostModifier_pushVelocity);

//100%
extern "C" void cBoostModifier_onMessage(void* self, int a1)
{
    if (a1 == 0x258) {
        *(int*)((char*)self + 0x2c) = *(int*)((char*)self + 0x28);
    }
}

//100%
extern "C" void func_003584B8(void* self, void* stream);
struct sVEntry_func_00342BA0 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};
struct sVEntry1_func_00342BA0 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

extern "C" void cBoostModifier_writeToReplayFrame(void* self, void* stream)
{
    func_003584B8(self, stream);
    sVEntry_func_00342BA0* vt = *(sVEntry_func_00342BA0**)stream;
    vt[1].fn((char*)stream + vt[1].delta, (char*)self + 0x10, 0x30);
    sVEntry1_func_00342BA0* vt1 = *(sVEntry1_func_00342BA0**)stream;
    vt1[5].fn((char*)stream + vt1[5].delta, *(int*)((char*)self + 0x40));
}

//100%
extern "C" void* func_00355280(void* self, void* a1, int type, void* a3);
extern "C" void func_00355F10(void* self, void* a1);
extern void* D_004906F0[];

struct sNode_342C08 {
    int pad00[2];
    unsigned int flags;
};

struct sDef_342C08 {
    int f00;
    float time;
    int f08;
    int mode;
};

struct sSelf_342C08 {
    int pad00[3];
    void** vt;
    int pad10[2];
    sNode_342C08* node;
    int pad1C[4];
    int t2C;
    int t30;
};

extern "C" void* cDebounceNode_construct(sSelf_342C08* self, void* a1, void* a2, sDef_342C08* def, void* a4)
{
    func_00355280(self, a1, 0, a2);
    self->vt = D_004906F0;
    self->t2C = (int)(def->time * (float)*(int*)(D_004A5B64 + 0x10));
    self->t30 = def->f08;
    func_00355F10(self, a4);
    if (def->mode == 0) {
        self->node->flags &= 0xFFFFFFF0;
    } else if (def->mode == 1) {
        self->node->flags |= 1;
        self->node->flags = (self->node->flags & ~2u) | 4;
    } else {
        sNode_342C08* n = self->node;
        if ((n->flags & 3) == 3) {
            n->flags = (n->flags & ~2u) | 4;
        }
    }
    return self;
}

