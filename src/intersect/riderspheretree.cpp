#include "common.h"
#include "intersect/spheretree.h"
#include "intersect/riderspheretree.h"
#include "intersect/worldquery.h"

// R5900 128-bit GPR quadword, for functions that copy a 16-byte block via a
// single lq/sq pair instead of word-by-word.
typedef int cQuad128 __attribute__((mode(TI)));

//100%
inline void* operator new[](unsigned int, void* p) { return p; }

INCLUDE_ASM("intersect/riderspheretree", cRiderSphereTree_cRiderSphereTree__FP16cRiderSphereTree);
cRiderSphereTree* cRiderSphereTree_cRiderSphereTree(cRiderSphereTree* self);

INCLUDE_ASM("intersect/riderspheretree", cRiderSphereTree_cRiderSphereTreeCopy);

//100%
void operator_delete(int* ptr);

extern "C" void cRiderSphereTree_destroy(void* self, int flags)
{
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

extern "C" void cRiderSphereTree_initSingleSphere(char* self, float f)
{
    cRiderSphereTree* t = (cRiderSphereTree*)self;
    t->mRadius = f;
    t->mCentreBone = -1;
    t->mActiveMask = 0xFFFFFFFF;
    t->mCount = 1;
    t->mSpheres[0].mRadius = f;
    t->mSpheres[0].mBone = -1;
    t->mBones = 0;
}

//100%
extern "C" void cRiderSphereTree_setupBones(cRiderSphereTree* s, sRiderSphereBone* bones, int n, int* ids, float* radii,
                              int centreBone, float radius)
{
    s->mActiveMask = 0xFFFFFFFF;
    s->mCount = n;
    for (int i = 0; i < s->mCount; i++) {
        s->mSpheres[i].mBone = ids[i];
        s->mSpheres[i].mRadius = radii[i];
    }
    s->mBones = bones;
    s->mRadius = radius;
    s->mCentreBone = centreBone;
}

//100%
extern "C" void func_003E6574(void* dst, void* src, int size);

extern "C" cRiderSphereTree* cRiderSphereTree_assign(cRiderSphereTree* self, cRiderSphereTree* src)
{
    self->mBones = src->mBones;
    self->mRadius = src->mRadius;
    self->mCentre = src->mCentre;
    self->mCentreBone = src->mCentreBone;
    self->mCount = src->mCount;
    self->mActiveMask = src->mActiveMask;
    func_003E6574(self->mSpheres, src->mSpheres, self->mCount << 5);
    return self;
}

//100%
extern "C" void cRiderSphereTree_setSpheres(cRiderSphereTree* s, int n, sSphereVec4* pos, float* radii,
                              sSphereVec4* center, float radius)
{
    s->mCount = n;
    for (int i = 0; i < s->mCount; i++) {
        s->mSpheres[i].mPos = pos[i];
        s->mSpheres[i].mRadius = radii[i];
    }
    s->mCentre = *center;
    s->mRadius = radius;
}

//100%
extern "C" void cRiderSphereTree_updateFromBones(cRiderSphereTree* s)
{
    for (int i = 0; i < s->mCount; i++) {
        s->mSpheres[i].mPos = s->mBones[s->mSpheres[i].mBone].mPos;
    }
    s->mCentre = s->mBones[s->mCentreBone].mPos;
}

//100%
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float adds).
static inline void sphereVecAdd(sSphereVec4* dst, sSphereVec4* v)
{
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        ".set pop\n"
        : "=m"(*dst)
        : "m"(*dst), "m"(*v));
}

// self->mCentre += *v, then every child's mPos += *v
extern "C" void cRiderSphereTree_translate(cRiderSphereTree* s, sSphereVec4* v)
{
    sphereVecAdd(&s->mCentre, v);
    for (int i = 0; i < s->mCount; i++) {
        sphereVecAdd(&s->mSpheres[i].mPos, v);
    }
}

INCLUDE_ASM("intersect/riderspheretree", cRiderSphereTree_transform);

//100%
struct sSphBox_9CE0 {
    sSphereVec4 min;
    sSphereVec4 max;
};

extern "C" void cRiderSphereTree_getBounds(cRiderSphereTree* self, sSphBox_9CE0* box)
{
    box->min = box->max = self->mCentre;
    for (int i = 0; i < self->mCount; i++) {
        sRiderSphere* k = &self->mSpheres[i];
        float r = k->mRadius;
        float v;
        v = k->mPos.x - r;
        if (v < box->min.x) box->min.x = v;
        v = k->mPos.y - r;
        if (v < box->min.y) box->min.y = v;
        v = k->mPos.z - r;
        if (v < box->min.z) box->min.z = v;
        v = k->mPos.x + r;
        if (box->max.x < v) box->max.x = v;
        v = k->mPos.y + r;
        if (box->max.y < v) box->max.y = v;
        v = k->mPos.z + r;
        if (box->max.z < v) box->max.z = v;
    }
}


//100%
struct sSphereV4_9DC8 {
    float x, y, z, w;
    sSphereV4_9DC8() {}
    sSphereV4_9DC8(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
} __attribute__((aligned(16)));

// PORT: PS2-only VU0 inline asm (a - b).
static inline sSphereV4_9DC8 Sub_9DC8(const sSphereV4_9DC8& a, const sSphereV4_9DC8& b)
{
    sSphereV4_9DC8 r;
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
static inline sSphereV4_9DC8 Add_9DC8(const sSphereV4_9DC8& a, const sSphereV4_9DC8& b)
{
    sSphereV4_9DC8 r;
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

extern "C" void cRiderSphereTree_getActiveBounds(void* tree, sSphereVec4* mnp, sSphereVec4* mxp)
{
    cRiderSphereTree* node = (cRiderSphereTree*)tree;
    sSphereV4_9DC8* mn = (sSphereV4_9DC8*)mnp;
    sSphereV4_9DC8* mx = (sSphereV4_9DC8*)mxp;
    *mn = sSphereV4_9DC8(10000000000.0f, 10000000000.0f, 10000000000.0f, 1.0f);
    *mx = sSphereV4_9DC8(-10000000000.0f, -10000000000.0f, -10000000000.0f, 1.0f);
    if (node->mActiveMask == 0) {
        *mn = Sub_9DC8(*(sSphereV4_9DC8*)&node->mCentre, sSphereV4_9DC8(node->mRadius, node->mRadius, node->mRadius, 0.0f));
        *mx = Add_9DC8(*(sSphereV4_9DC8*)&node->mCentre, sSphereV4_9DC8(node->mRadius, node->mRadius, node->mRadius, 0.0f));
        return;
    }
    for (int i = 0; i < node->mCount; i++) {
        if (node->mActiveMask & (1 << i)) {
            sSphereV4_9DC8 r(node->mSpheres[i].mRadius, node->mSpheres[i].mRadius, node->mSpheres[i].mRadius, 1.0f);
            sSphereV4_9DC8 t = Sub_9DC8(*(sSphereV4_9DC8*)&node->mSpheres[i].mPos, r);
            if (t.x < mn->x) mn->x = t.x;
            if (t.y < mn->y) mn->y = t.y;
            if (t.z < mn->z) mn->z = t.z;
            t = Add_9DC8(*(sSphereV4_9DC8*)&node->mSpheres[i].mPos, r);
            if (t.x > mx->x) mx->x = t.x;
            if (t.y > mx->y) mx->y = t.y;
            if (t.z > mx->z) mx->z = t.z;
        }
    }
}

INCLUDE_ASM("intersect/riderspheretree", cRiderSphereTree_testRiderSphereTree);

INCLUDE_ASM("intersect/riderspheretree", cRiderSphereTree_testTriangle);

INCLUDE_ASM("intersect/riderspheretree", cRiderSphereTree_testTriangleTwoSided);

//100%
extern "C" int intersectSphereBox(void* a, void* b, void* center, void* box, void* boxMin, void* boxMax, float radius);

// PORT: PS2-only VU0 inline asm (v * s).
static inline sSphereVec4 Scale_B2B8(const sSphereVec4& v, float s)
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
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

extern "C" int cRiderSphereTree_testBox(void* tree, void* a, void* b, sSphereVec4* outPos, sWorldHit* hit)
{
    cRiderSphereTree* self = (cRiderSphereTree*)tree;
    sSphereVec4* outNormal = (sSphereVec4*)hit;
    sSphereVec4 normal;
    sSphereVec4 dir;
    float t;
    if (intersectSphereBox(a, b, &self->mCentre, &normal, &dir, &t, self->mRadius) == 0) {
        return 0;
    }
    if (self->mActiveMask == 0) {
        *outPos = Scale_B2B8(dir, t);
        *outNormal = normal;
        return 1;
    }
    float best = -1.0f;
    for (int i = 0; i < self->mCount; i++) {
        if (self->mActiveMask & (1 << i)) {
            if (intersectSphereBox(a, b, &self->mCentre, &normal, &dir, &t, self->mRadius) && best < t) {
                *outPos = Scale_B2B8(dir, t);
                *outNormal = normal;
                best = t;
            }
        }
    }
    return best != -1.0f;
}

extern "C" void func_0032B460()
{
}

INCLUDE_ASM("intersect/riderspheretree", packBitsEncode);

//100%
// Run-length decode (PackBits style) into dst: a negative count -n copies the next n bytes, a positive count n
// repeats the next byte n+1 times, 0 terminates. Returns the number of bytes written.
// PORT: the unit declares it later as void*(void*, void*); defined under its own name bound to the symbol.
extern "C" int packBitsDecode_impl(char* dst, signed char* src) __asm__("packBitsDecode");
extern "C" int packBitsDecode_impl(char* dst, signed char* src)
{
    if (src == 0)
        return 0;
    char* d = dst;
    int c;
    do {
        c = *src++;
        if (c < 0) {
            int n = -c;
            do {
                *d++ = *src++;
            } while (--n);
        } else {
            int n = c + 1;
            if (c == 0)
                break;
            do {
                *d++ = *src;
            } while (--n);
            src++;
        }
    } while (c != 0);
    return d - dst;
}

//100%
// VU0 microprogram entry (micro-memory address 0x6E0; resolved via undefined_syms_auto.txt)
extern char D_6E0[];

// Loads four vectors into vf10-vf13, runs the VU0 microprogram at D_6E0 and
// returns whether it left a nonzero result in vi2.
// PORT: PS2-only VU0 microprogram call (ctc2/vcallmsr/cfc2); the PC port needs a C version
// of the microprogram.
INCLUDE_ASM("intersect/riderspheretree", vu0PointInTriangle);
extern "C" int vu0PointInTriangle(sSphereVec4* a, sSphereVec4* b, sSphereVec4* c, sSphereVec4* d);

INCLUDE_ASM("intersect/riderspheretree", cWorldIntType_testPatch);

//100%
extern sSphereVec4 D_004FF120;

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vDot_C0F8(const sSphereVec4& a, const sSphereVec4& b)
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

struct sTriBox_C0F8 {
    float lo[3];
    float hi[3];
};

struct sTriMesh_C0F8 {
    unsigned short numTris;     // 0x0
    short pad2;
    unsigned char* indices;     // 0x4
    sTriBox_C0F8* boxes;        // 0x8
    sSphereVec4* verts;            // 0xC
    sSphereVec4* normals;          // 0x10
};

struct sVE_C0F8a {
    short delta;
    short index;
    int (*fn)(void*, sSphereVec4*, sSphereVec4*, sSphereVec4*, sSphereVec4*, sSphereVec4*, sSphereVec4*, float*);
};
struct sVE_C0F8b {
    short delta;
    short index;
    int (*fn)(void*, float*, float*);
};

static inline sVE_C0F8a* vt_C0F8(cWorldIntType* t)
{
    return (sVE_C0F8a*)t->mVtable;
}

extern "C" int cWorldIntType_testTriMesh(cWorldIntType* self, sTriMesh_C0F8* mesh, int flag, sWorldHit* out)
{
    sSphereVec4 pos;
    sSphereVec4 hn;
    float t;
    int n = 0;
    if (mesh->numTris < 11) {
        for (int i = 0; i < mesh->numTris; i++) {
            sSphereVec4* nrm = &mesh->normals[i];
            if (self->mUseNormalFilter != 0 && vDot_C0F8(*nrm, self->mFilterDir) > 0.8f) {
                continue;
            }
                        sSphereVec4* v = mesh->verts;
            sSphereVec4* p0 = &v[mesh->indices[i * 3]];
            sSphereVec4* p1 = &v[mesh->indices[i * 3 + 1]];
            sSphereVec4* p2 = &v[mesh->indices[i * 3 + 2]];
            int r;
            if (flag != 0) {
                r = vt_C0F8(self)[5].fn((char*)self + vt_C0F8(self)[5].delta, p0, p1, p2, nrm, &pos, &hn, &t);
            } else {
                r = vt_C0F8(self)[4].fn((char*)self + vt_C0F8(self)[4].delta, p0, p1, p2, nrm, &pos, &hn, &t);
            }
            if (r == 0) {
                continue;
            }
            sWorldHit* h = &out[n];
            h->mPatch = 0;
            h->mType = 2;
            h->mTriangle = -1;
            h->mInstance = 0;
            h->mUnk58 = 0;
            h->mUnk5C = -1;
            h->mUnk64 = -1;
            h->mSurface = -1;
            h->mSurfaceVel = D_004FF120;
            h->mVec30 = D_004FF120;
            h->mUnk68 = 0;
            h->mU = 0;
            h->mV = 0;
            h->mPos = pos;
            h->mNormal = hn;
            h->mDepth = t;
            h->mTriangle = i;
            h->mPatch = 0;
            n++;
        }
    } else {
        int nb = (mesh->numTris + 9) / 10;
        for (int b = 0; b < nb; b++) {
            sTriBox_C0F8* box = &mesh->boxes[b];
            sVE_C0F8b* vt = (sVE_C0F8b*)self->mVtable;
            if (!vt[9].fn((char*)self + vt[9].delta, box->lo, box->hi)) {
                continue;
            }
            int end = (b + 1) * 10 < mesh->numTris ? (b + 1) * 10 : mesh->numTris;
            for (int i = b * 10; i < end; i++) {
                sSphereVec4* nrm = &mesh->normals[i];
                if (self->mUseNormalFilter != 0 && vDot_C0F8(*nrm, self->mFilterDir) > 0.8f) {
                    continue;
                }
                                sSphereVec4* v = mesh->verts;
                sSphereVec4* p0 = &v[mesh->indices[i * 3]];
                sSphereVec4* p1 = &v[mesh->indices[i * 3 + 1]];
                sSphereVec4* p2 = &v[mesh->indices[i * 3 + 2]];
                int r;
                if (flag != 0) {
                    r = vt_C0F8(self)[5].fn((char*)self + vt_C0F8(self)[5].delta, p0, p1, p2, nrm, &pos, &hn, &t);
                } else {
                    r = vt_C0F8(self)[4].fn((char*)self + vt_C0F8(self)[4].delta, p0, p1, p2, nrm, &pos, &hn, &t);
                }
                if (r == 0) {
                    continue;
                }
                sWorldHit* h = &out[n];
                h->mPatch = 0;
                h->mType = 2;
                h->mTriangle = -1;
                h->mInstance = 0;
                h->mUnk58 = 0;
                h->mUnk5C = -1;
                h->mUnk64 = -1;
                h->mSurface = -1;
                h->mSurfaceVel = D_004FF120;
                h->mVec30 = D_004FF120;
                h->mUnk68 = 0;
                h->mU = 0;
                h->mV = 0;
                h->mPos = pos;
                h->mNormal = hn;
                h->mDepth = t;
                h->mTriangle = i;
                h->mPatch = 0;
                n++;
            }
        }
    }
    return n;
}

INCLUDE_ASM("intersect/riderspheretree", cSphereTree_cSphereTree);

//100%
extern sSphereVec4 D_004FF640[8];
extern sSphereVec4 D_004FF130;

extern "C" void cSphereTree_reset(void* self)
{
    cSphereTree* t = (cSphereTree*)self;
    for (int i = 0; i < 8; i++) {
        t->mDirs[i] = D_004FF640[i];
    }
    t->mCentre = D_004FF130;
    t->mScale = 1.0f;
}

//100%
extern "C" float cSphereTree_getRadius(void* self)
{
    cSphereTree* t = (cSphereTree*)self;
    sSphereTreeHeader* p = t->mHeader;
    sSphereTreeLevel* q = p->mLevels;
    return q->mRadius * t->mScale;
}

//100%
extern "C" float cSphereTree_getLeafHalfRadius(void* self)
{
    cSphereTree* t = (cSphereTree*)self;
    sSphereTreeHeader* p = t->mHeader;
    int idx = p->mDepth;
    sSphereTreeLevel* tab = p->mLevels;
    return tab[idx].mRadius * t->mScale * 0.5f;
}

INCLUDE_ASM("intersect/riderspheretree", cSphereTree_setPosition);

//100%
// self->(0x80) += *v  (4-wide VU0 add, macro mode)
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float adds).
INCLUDE_ASM("intersect/riderspheretree", cSphereTree_translate);
extern "C" void cSphereTree_translate(void* self, void* v);

INCLUDE_ASM("intersect/riderspheretree", cSphereTree_setTransform);

INCLUDE_ASM("intersect/riderspheretree", cSphereTree_transform);

//100%
extern "C" int cSphereTree_getMasks(void* self);
extern "C" int cSphereTree_testSphereNode(void* self, void* a1, float f, void* pos, int a4, int a5, void* a6, void* a7);

extern "C" int cSphereTree_testSphere(void* self, void* a1, float f, void* a2, void* a3)
{
    cSphereTree* st = (cSphereTree*)self;
    sSphereTreeHeader* h = st->mHeader;
    if (h->mPacked != 0) {
        *(int*)&st->mHeader->mMasks = cSphereTree_getMasks(h);
    }
    return cSphereTree_testSphereNode(self, a1, f, &st->mCentre, 0, 0, a2, a3);
}

//100%
extern "C" int cSphereTree_getMasks(void* self);
extern "C" int cSphereTree_testBoxNode(void* self, void* a1, void* a2, void* pos, int a4, int a5, void* a6, void* a7);

extern "C" int cSphereTree_testBox(void* self, void* a1, void* a2, void* a3, void* a4)
{
    cSphereTree* st = (cSphereTree*)self;
    sSphereTreeHeader* h = st->mHeader;
    if (h->mPacked != 0) {
        *(int*)&st->mHeader->mMasks = cSphereTree_getMasks(h);
    }
    return cSphereTree_testBoxNode(self, a1, a2, &st->mCentre, 0, 0, a3, a4);
}

//100%
extern "C" int cSphereTree_getMasks(void* self);
extern "C" void cSphereTree_sortChildren(void* self, void* v);
extern "C" int cSphereTree_testPlaneNode(void* self, void* a1, void* pos, int a3, int a4, void* a5, void* a6);

static inline sSphereVec4 flat_C9B8(sSphereVec4 p)
{
    p.w = 0.0f;
    return p;
}

extern "C" int cSphereTree_testPlane(void* self, sSphereVec4* a1, void* a2, void* a3)
{
    cSphereTree* st = (cSphereTree*)self;
    sSphereTreeHeader* h = st->mHeader;
    if (h->mPacked != 0) {
        *(int*)&st->mHeader->mMasks = cSphereTree_getMasks(h);
    }
    sSphereVec4 v = flat_C9B8(*a1);
    cSphereTree_sortChildren(self, &v);
    st->mBestDepth = 0.0f;
    cSphereTree_testPlaneNode(self, a1, &st->mCentre, 0, 0, a2, a3);
    if (st->mBestDepth < 0.0f) {
        return 1;
    }
    return 0;
}

//100%
extern "C" int cSphereTree_getMasks(void* self);
extern "C" void cSphereTree_sortChildren(void* self, void* v);
extern "C" int cSphereTree_testTriangleNode(void* self, void* a1, void* a2, void* a3, void* v, void* pos, int a6, int a7, void* a8, void* a9);

extern "C" int cSphereTree_testTriangle(void* self, void* a1, void* a2, void* a3, void* v, void* a5, void* a6)
{
    cSphereTree* st = (cSphereTree*)self;
    sSphereTreeHeader* h = st->mHeader;
    if (h->mPacked != 0) {
        *(int*)&st->mHeader->mMasks = cSphereTree_getMasks(h);
    }
    cSphereTree_sortChildren(self, v);
    st->mBestDepth = 0.0f;
    cSphereTree_testTriangleNode(self, a1, a2, a3, v, &st->mCentre, 0, 0, a5, a6);
    if (st->mBestDepth < 0.0f) {
        return 1;
    }
    return 0;
}

//100%
extern "C" int cSphereTree_getMasks(void* self);
extern "C" int cSphereTree_testSphereTreeNode(void* self, void* other, void* pos, int a3, int a4, void* a5, void* a6);

extern "C" int cSphereTree_testSphereTree(void* self, void* other, void* a2, void* a3)
{
    cSphereTree* st = (cSphereTree*)self;
    sSphereTreeHeader* h = st->mHeader;
    if (h->mPacked != 0) {
        *(int*)&st->mHeader->mMasks = cSphereTree_getMasks(h);
    }
    cSphereTree* ot = (cSphereTree*)other;
    h = ot->mHeader;
    if (h->mPacked != 0) {
        *(int*)&ot->mHeader->mMasks = cSphereTree_getMasks(h);
    }
    return cSphereTree_testSphereTreeNode(self, other, &st->mCentre, 0, 0, a2, a3);
}

//100%
extern "C" int cSphereTree_testSphereNode(void* self, void* a1, float f, void* pos, int a4, int a5, void* a6, void* a7);
extern "C" int cSphereTree_testSphereTreeNode(void* self, void* other, void* pos, int a3, int a4, void* a5, void* a6);


// PORT: PS2-only VU0 inline asm (v * s).
static inline sSphereVec4 Scale_CBF8(const sSphereVec4& v, float s)
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
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (a + b).
static inline sSphereVec4 Add_CBF8(const sSphereVec4& a, const sSphereVec4& b)
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

extern "C" int cSphereTree_testSphereTreeNode(void* selfp, void* other, void* posp, int depth, int base, void* a5, void* a6)
{
    cSphereTree* self = (cSphereTree*)selfp;
    sSphereVec4 p;
    unsigned char mask = self->mHeader->mMasks[base];
    if (depth < self->mHeader->mDepth) {
        if (depth >= 4) {
            return 1;
        }
        if (mask != 0) {
            float off = self->mHeader->mLevels[depth + 1].mOffset;
            for (int i = 0; i < 8; i++) {
                if ((mask >> i) & 1) {
                    p = Add_CBF8(*(sSphereVec4*)posp, Scale_CBF8(self->mDirs[i], off));
                    if (cSphereTree_testSphereNode(other, &p, self->mHeader->mLevels[depth].mRadius * self->mScale, &((cSphereTree*)other)->mCentre, 0, 0, a5, a6) &&
                        cSphereTree_testSphereTreeNode(self, other, &p, depth + 1, (i + 1) * self->mHeader->mLevels[depth].mStride + base, a5, a6)) {
                        return 1;
                    }
                }
            }
            return 0;
        }
    }
    return 1;
}

//100%

// PORT: PS2-only VU0 inline asm (v * s).
static inline sSphereVec4 Scale_CDB0(const sSphereVec4& v, float s)
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
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (a + b).
static inline sSphereVec4 Add_CDB0(const sSphereVec4& a, const sSphereVec4& b)
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

// PORT: PS2-only VU0 inline asm (a - b).
static inline sSphereVec4 Sub_CDB0(const sSphereVec4& a, const sSphereVec4& b)
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

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float Dot_CDB0(const sSphereVec4& a, const sSphereVec4& b)
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

// PORT: PS2-only VU0 inline asm (v / |v|).
static inline sSphereVec4 Normalize_CDB0(const sSphereVec4& v)
{
    sSphereVec4 r;
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

// PORT: sqrt.s (sqrtf without errno check)
static inline float Sqrt_CDB0(float v)
{
    float r;
    __asm__("sqrt.s %0, %1" : "=f"(r) : "f"(v));
    return r;
}

extern "C" int cSphereTree_testSphereNode(void* selfp, void* a1, float r, void* pos, int depth, int base, void* outA, void* outB)
{
    cSphereTree* self = (cSphereTree*)selfp;
    float sum = r + self->mHeader->mLevels[depth].mRadius * self->mScale;
    sSphereVec4 d = Sub_CDB0(*(sSphereVec4*)a1, *(sSphereVec4*)pos);
    float dd = Dot_CDB0(d, d);
    if (!(dd < sum * sum))
        return 0;
    float f;
    unsigned char mask = self->mHeader->mMasks[base];
    if (depth < self->mHeader->mDepth && mask != 0) {
        f = self->mHeader->mLevels[depth + 1].mOffset;
        for (int i = 0; i < 8; i++) {
            if ((mask >> i) & 1) {
                sSphereVec4 p = Add_CDB0(*(sSphereVec4*)pos, Scale_CDB0(self->mDirs[i], f));
                if (cSphereTree_testSphereNode(self, a1, r, &p, depth + 1, (i + 1) * self->mHeader->mLevels[depth].mStride + base, outA, outB))
                    return 1;
            }
        }
        return 0;
    }
    sSphereVec4 n = Normalize_CDB0(d);
    f = sum - Sqrt_CDB0(dd);
    *(sSphereVec4*)outA = Scale_CDB0(n, f);
    *(sSphereVec4*)outB = Sub_CDB0(*(sSphereVec4*)a1, Scale_CDB0(n, r - f));
    return 1;
}

//100%
extern "C" int intersectSphereBox(void* a, void* b, void* center, void* box, void* boxMin, void* boxMax, float radius);
extern "C" int cSphereTree_testBoxNode(void* self, void* a1, void* a2, void* pos, int a4, int a5, void* a6, void* a7);


// PORT: PS2-only VU0 inline asm (v * s).
static inline sSphereVec4 Scale_D028(const sSphereVec4& v, float s)
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
        : "m"(v), "f"(s)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm (a + b).
static inline sSphereVec4 Add_D028(const sSphereVec4& a, const sSphereVec4& b)
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

extern "C" int cSphereTree_testBoxNode(void* selfp, void* a1, void* a2, void* pos, int depth, int base, void* outPos, void* outNormal)
{
    cSphereTree* self = (cSphereTree*)selfp;
    sSphereVec4 normal;
    sSphereVec4 dir;
    float t;
    if (intersectSphereBox(a1, a2, pos, &normal, &dir, &t, self->mHeader->mLevels[depth].mRadius * self->mScale) == 0) {
        return 0;
    }
    unsigned char mask = self->mHeader->mMasks[base];
    if (depth < self->mHeader->mDepth && mask != 0) {
        float off = self->mHeader->mLevels[depth + 1].mOffset;
        for (int i = 0; i < 8; i++) {
            if ((mask >> i) & 1) {
                sSphereVec4 p = Add_D028(*(sSphereVec4*)pos, Scale_D028(self->mDirs[i], off));
                if (cSphereTree_testBoxNode(self, a1, a2, &p, depth + 1, (i + 1) * self->mHeader->mLevels[depth].mStride + base, outPos, outNormal)) {
                    return 1;
                }
            }
        }
        return 0;
    }
    *(sSphereVec4*)outNormal = normal;
    *(sSphereVec4*)outPos = Scale_D028(dir, t);
    return 1;
}

INCLUDE_ASM("intersect/riderspheretree", cSphereTree_testPlaneNode);

//100%
// PORT: this caller passes a tolerance in $f12 that the unit's 4-arg vu0PointInTriangle never reads;
// bind the 5-arg form to the same symbol.
extern "C" int vu0PointInTriangle_tol(sSphereVec4* a, sSphereVec4* b, sSphereVec4* c, sSphereVec4* d, float tol) __asm__("vu0PointInTriangle");

extern "C" int cSphereTree_pointInTriangle(void* self, sSphereVec4* a, sSphereVec4* b, sSphereVec4* c, sSphereVec4* d)
{
    return vu0PointInTriangle_tol(a, b, c, d, 9.999999747378752e-05f);
}

INCLUDE_ASM("intersect/riderspheretree", cSphereTree_testTriangleNode);

//100%
extern int D_0044AF98[];

// Shell sort of keys[] (descending) carrying vals[] along, gap table D_0044AF98.
extern "C" void shellSortDescending(int n, int* keys, int* vals)
{
    int k = 1;
    while (D_0044AF98[k] < n) {
        k++;
    }
    int gap;
    for (;;) {
        gap = D_0044AF98[--k];
        for (int i = gap; i < n; i++) {
            int key = keys[i];
            int val = vals[i];
            int j = i - gap;
            do {
                if (keys[j] >= key) {
                    break;
                }
                keys[j + gap] = keys[j];
                vals[j + gap] = vals[j];
                j -= gap;
            } while (j >= 0);
            keys[j + gap] = key;
            vals[j + gap] = val;
        }
        if (gap < 2) {
            break;
        }
    }
}

INCLUDE_ASM("intersect/riderspheretree", cSphereTree_sortChildren);

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label as a placement operator new[].
void* operator new[](unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern char D_0048E540[];
extern void** D_004A3FC8;
extern void* D_004A3FCC;
extern int D_004A3FD0;
extern int D_004A3FD4;
extern void** D_004A3FD8;
extern void* D_004A3FDC;
extern int D_004A3FE0;
extern int D_004A3FE4;
extern int D_004A3FE8;

// Allocates the two decompression caches; each buffer holds a full octree of the given depth
// (1 + 8 + 64 + ... nodes).
extern "C" void func_0032DC10(int nSmall, int smallDepth, int nBig, int threshold)
{
    int smallSize = 0;
    int bigSize = 0;
    int i;
    int k;
    D_004A3FE8 = threshold;
    k = 1;
    for (i = 0; i <= smallDepth; i++) {
        smallSize += k;
        k <<= 3;
    }
    k = 1;
    for (i = 0; i <= D_004A3FE8; i++) {
        bigSize += k;
        k <<= 3;
    }
    D_004A3FC8 = 0;
    D_004A3FCC = 0;
    D_004A3FD8 = 0;
    D_004A3FDC = 0;
    if (nSmall != 0) {
        D_004A3FC8 = new (D_0048E540, 0, 0) void*[nSmall];
        D_004A3FCC = new (D_0048E540, 0, 0) int[nSmall];
    }
    if (nBig != 0) {
        D_004A3FD8 = new (D_0048E540, 0, 0) void*[nBig];
        D_004A3FDC = new (D_0048E540, 0, 0) int[nBig];
    }
    for (i = 0; i < nSmall; i++) {
        D_004A3FC8[i] = new (D_0048E540, 0, 0) char[smallSize];
        ((int*)D_004A3FCC)[i] = -1;
    }
    for (i = 0; i < nBig; i++) {
        D_004A3FD8[i] = new (D_0048E540, 0, 0) char[bigSize];
        ((int*)D_004A3FDC)[i] = -1;
    }
    D_004A3FD0 = nSmall;
    D_004A3FE0 = nBig;
    D_004A3FD4 = 0;
    D_004A3FE4 = 0;
}

//100%
void cMemMan_free(void* p);
extern void** D_004A3FC8;
extern void* D_004A3FCC;
extern int D_004A3FD0;
extern void** D_004A3FD8;
extern void* D_004A3FDC;
extern int D_004A3FE0;

extern "C" void func_0032DE20(void)
{
    if (D_004A3FC8 != 0) {
        for (int i = 0; i < D_004A3FD0; i++) {
            if (D_004A3FC8[i] != 0) {
                cMemMan_free(D_004A3FC8[i]);
            }
        }
        if (D_004A3FC8 != 0) {
            cMemMan_free(D_004A3FC8);
        }
        D_004A3FC8 = 0;
    }
    if (D_004A3FCC != 0) {
        cMemMan_free(D_004A3FCC);
        D_004A3FCC = 0;
    }
    if (D_004A3FD8 != 0) {
        for (int i = 0; i < D_004A3FE0; i++) {
            if (D_004A3FD8[i] != 0) {
                cMemMan_free(D_004A3FD8[i]);
            }
        }
        if (D_004A3FD8 != 0) {
            cMemMan_free(D_004A3FD8);
        }
        D_004A3FD8 = 0;
    }
    if (D_004A3FDC != 0) {
        cMemMan_free(D_004A3FDC);
        D_004A3FDC = 0;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern void** D_004A3FC8;
extern void* D_004A3FCC;
extern int D_004A3FD0;
extern int D_004A3FD4;
extern void** D_004A3FD8;
extern void* D_004A3FDC;
extern int D_004A3FE0;
extern int D_004A3FE4;
extern int D_004A3FE8;
extern "C" void* packBitsDecode(void* dst, void* src);


// PORT: returns the cached buffer pointer as int (the unit declares it int-returning).
extern "C" int cSphereTree_getMasks(void* selfp)
{
    sSphereTreeHeader* self = (sSphereTreeHeader*)selfp;
    int key = self->mKey;
    int* pslot = &self->mCacheSlot;
    if (self->mDepth < D_004A3FE8) {
        if (((int*)D_004A3FCC)[*pslot] == key) {
            return (int)D_004A3FC8[*pslot];
        }
        for (int i = 0; i < D_004A3FD0; i++) {
            if (((int*)D_004A3FCC)[i] == key) {
                *pslot = i;
                return (int)D_004A3FC8[i];
            }
        }
        packBitsDecode(D_004A3FC8[D_004A3FD4], self->mPackedMasks);
        ((int*)D_004A3FCC)[D_004A3FD4] = key;
        *pslot = D_004A3FD4;
        D_004A3FD4++;
        D_004A3FD4 %= D_004A3FD0;
        return (int)D_004A3FC8[*pslot];
    } else {
        if (((int*)D_004A3FDC)[*pslot] == key) {
            return (int)D_004A3FD8[*pslot];
        }
        for (int i = 0; i < D_004A3FE0; i++) {
            if (((int*)D_004A3FDC)[i] == key) {
                *pslot = i;
                return (int)D_004A3FD8[i];
            }
        }
        packBitsDecode(D_004A3FD8[D_004A3FE4], self->mPackedMasks);
        ((int*)D_004A3FDC)[D_004A3FE4] = key;
        *pslot = D_004A3FE4;
        D_004A3FE4++;
        D_004A3FE4 %= D_004A3FE0;
        return (int)D_004A3FD8[*pslot];
    }
}

//100%
extern char D_0048E6A8[];

// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float subs).
static inline sSphereVec4 sphereCapsuleSub(sSphereVec4* a, sSphereVec4* b)
{
    sSphereVec4 r;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        ".set pop\n"
        : "=m"(r)
        : "m"(*a), "m"(*b)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float adds).
static inline sSphereVec4 sphereCapsuleAdd(sSphereVec4* a, sSphereVec4* b)
{
    sSphereVec4 r;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        ".set pop\n"
        : "=m"(r)
        : "m"(*a), "m"(*b)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (v / s).
static inline sSphereVec4 sphereCapsuleDiv(const sSphereVec4& v, float s)
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

struct sSphereV4_E100 : sSphereVec4 {
    sSphereV4_E100(float ax, float ay, float az, float aw)
    {
        x = ax;
        y = ay;
        z = az;
        w = aw;
    }
};


extern "C" cWorldLine* cWorldLine_cWorldLine(cWorldLine* self, sSphereVec4* p0, sSphereVec4* p1,
                                             int state, float r)
{
    self->mKind = state;
    self->mVtable = D_0048E6A8;
    self->mUseNormalFilter = 0;
    self->mTransformed = 0;
    self->mP0Saved = *p0;
    self->mP0 = self->mP0Saved;
    self->mDirSaved = sphereCapsuleSub(p1, p0);
    self->mDir = self->mDirSaved;
    self->mRadius = r;
    self->mMax = sSphereV4_E100(p0->x > p1->x ? p0->x : p1->x,
                               p0->y > p1->y ? p0->y : p1->y,
                               p0->z > p1->z ? p0->z : p1->z, 1.0f);
    self->mMin = sSphereV4_E100(p0->x < p1->x ? p0->x : p1->x,
                               p0->y < p1->y ? p0->y : p1->y,
                               p0->z < p1->z ? p0->z : p1->z, 1.0f);
    self->mBoxCentre = sphereCapsuleDiv(sphereCapsuleAdd(&self->mMin, &self->mMax), 2.0f);
    return self;
}

//100%
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float adds).
// segment self->mP0 .. mP0+mDir overlaps the box [mn, mx]?
extern "C" int cWorldLine_overlapsBox(cWorldLine* self, sSphereVec4* mn, sSphereVec4* mx)
{
    sSphereVec4 e = sphereCapsuleAdd(&self->mP0, &self->mDir);
    if ((self->mP0.x < mn->x && e.x < mn->x) || (mx->x < self->mP0.x && mx->x < e.x) ||
        (self->mP0.y < mn->y && e.y < mn->y) || (mx->y < self->mP0.y && mx->y < e.y) ||
        (self->mP0.z < mn->z && e.z < mn->z) || (mx->z < self->mP0.z && mx->z < e.z)) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("intersect/riderspheretree", cWorldLine_transform);

//100%
extern "C" void cWorldLine_restore(void* self)
{
    cWorldLine* t = (cWorldLine*)self;
    cQuad128 a = *(cQuad128*)&t->mP0Saved;
    cQuad128 b = *(cQuad128*)&t->mDirSaved;
    *(cQuad128*)&t->mP0 = a;
    *(cQuad128*)&t->mDir = b;
    t->mTransformed = 0;
}

//100%
// PORT: this caller passes a tolerance in $f12 that the unit's 4-arg vu0PointInTriangle never reads;
// bind the 5-arg form to the same symbol.
extern "C" int vu0PointInTriangle_tol(sSphereVec4* a, sSphereVec4* b, sSphereVec4* c, sSphereVec4* d, float tol) __asm__("vu0PointInTriangle");

// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float vu0Dot_E4D0(const sSphereVec4& a, const sSphereVec4& b)
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

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sSphereVec4 vu0Sub_E4D0(const sSphereVec4& a, const sSphereVec4& b)
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
static inline sSphereVec4 vu0Add_E4D0(const sSphereVec4& a, const sSphereVec4& b)
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
static inline sSphereVec4 vu0Scale_E4D0(const sSphereVec4& v, float s)
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

// segment mP0 + t*mDir against the plane through *p with normal *n
extern "C" int cWorldLine_testTriangle(void* self, sSphereVec4* p, sSphereVec4* b, sSphereVec4* c, sSphereVec4* n,
                             sSphereVec4* hit, sSphereVec4* outN, float* outT)
{
    cWorldLine* t0 = (cWorldLine*)self;
    sSphereVec4* origin = &t0->mP0;
    sSphereVec4* dir = &t0->mDir;
    float denom = vu0Dot_E4D0(*dir, *n);
    if (__builtin_fabsf(denom) < 1.000000013351432e-10f) {
        return 0;
    }
    float t;
    {
        sSphereVec4 d = vu0Sub_E4D0(*p, *origin);
        t = vu0Dot_E4D0(d, *n) / denom;
    }
    *outT = t;
    if (t < 0.0f || 1.0f < t) {
        return 0;
    }
    *hit = vu0Add_E4D0(*origin, vu0Scale_E4D0(*dir, t));
    *outN = *n;
    return vu0PointInTriangle_tol(p, b, c, hit, 9.999999747378752e-05f);
}

INCLUDE_ASM("intersect/riderspheretree", cWorldLine_testTriangleTwoSided);

//100%
int cWorldLine_testSphereTree__FPv(void* self)
{
    return 0;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern int D_004A5978;
extern sSphereVec4 D_004FF260[];
extern sSphereVec4 D_004FF120_E690[] __asm__("D_004FF120");


static inline void reset_E690(sWorldHit* h)
{
    h->mType = 2;
    h->mPatch = 0;
    h->mInstance = 0;
    h->mUnk58 = 0;
    h->mUnk5C = -1;
    h->mTriangle = -1;
    h->mUnk64 = -1;
    h->mSurface = -1;
    h->mSurfaceVel = *D_004FF120_E690;
    h->mVec30 = *D_004FF120_E690;
    h->mUnk68 = 0;
    h->mU = 0;
    h->mV = 0;
}


extern "C" int cWorldLine_testBox(cWorldLine* self, float* bmin, float* bmax, sWorldHit* hits)
{
    float tmin = -1.0f;
    float tmax = 2.0f;
    float* pd = &self->mDir.x;
    float* po = &self->mP0.x;
    int fmin = -1;
    int fmax = -1;
    for (int i = 0; i < 3; i++, bmin++, bmax++, pd++, po++) {
        float d = *pd;
        if (__builtin_fabsf(d) > 1.000000013351432e-10f) {
            float o = *po;
            float t1 = (*bmin - o) / d;
            float t2 = (*bmax - o) / d;
            int face = i * 2;
            if (t2 < t1) {
                float tt = t1;
                face++;
                t1 = t2;
                t2 = tt;
            }
            if (tmin < t1) {
                tmin = t1;
                fmin = face;
            }
            if (t2 < tmax) {
                tmax = t2;
                fmax = face ^ 1;
            }
            if (tmax < tmin)
                return 0;
            if (tmax < 0.0f)
                return 0;
            if (1.0f < tmin)
                return 0;
        }
    }
    if (D_004A5978 == 0) {
        D_004FF260[0].x = -1.0f;
        D_004FF260[0].y = 0.0f;
        D_004FF260[0].z = 0.0f;
        D_004FF260[0].w = 0.0f;
        D_004FF260[1].x = 1.0f;
        D_004FF260[1].y = 0.0f;
        D_004FF260[1].z = 0.0f;
        D_004FF260[1].w = 0.0f;
        D_004FF260[2].x = 0.0f;
        D_004FF260[2].y = -1.0f;
        D_004FF260[2].z = 0.0f;
        D_004FF260[2].w = 0.0f;
        D_004FF260[3].x = 0.0f;
        D_004FF260[3].y = 1.0f;
        D_004FF260[3].z = 0.0f;
        D_004FF260[3].w = 0.0f;
        D_004FF260[4].x = 0.0f;
        D_004FF260[4].y = 0.0f;
        D_004FF260[4].z = -1.0f;
        D_004FF260[4].w = 0.0f;
        D_004FF260[5].x = 0.0f;
        D_004FF260[5].y = 0.0f;
        D_004FF260[5].z = 1.0f;
        D_004FF260[5].w = 0.0f;
        D_004A5978 = 1;
    }
    int n = 0;
    if (0.0f <= tmin) {
        sWorldHit* h = &hits[0];
        reset_E690(h);
        h->mNormal = D_004FF260[fmin];
        h->mPos = vu0Add_E4D0(self->mP0, vu0Scale_E4D0(self->mDir, tmin));
        h->mDepth = tmin;
        n = 1;
    }
    if (tmax < 1.0f) {
        reset_E690(&hits[n]);
        hits[n].mNormal = D_004FF260[fmax];
        hits[n].mPos = vu0Add_E4D0(self->mP0, vu0Scale_E4D0(self->mDir, tmax));
        hits[n].mDepth = tmax;
        n++;
    }
    return n;
}

INCLUDE_ASM("intersect/riderspheretree", cWorldLine_refinePatch);

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float adds).
static inline sSphereVec4 vecAdd_2F650(sSphereVec4* a, sSphereVec4* b)
{
    sSphereVec4 r;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        ".set pop\n"
        : "=m"(r)
        : "m"(*a), "m"(*b)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (v * s).
static inline sSphereVec4 vecScale_2F650(const sSphereVec4& v, float s)
{
    sSphereVec4 r;
    int t;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "mfc1      %1, %3\n"
        "lqc2      $vf4, %2\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        ".set pop\n"
        : "=m"(r), "=&r"(t)
        : "m"(v), "f"(s)
        : "memory");
    return r;
}


extern "C" void cRiderSphereTree_getActiveBounds(void* tree, sSphereVec4* mn, sSphereVec4* mx);
extern void* D_0048E590[];

extern "C" cWorldRider* cWorldRider_cWorldRider(cWorldRider* self, void* tree, int flag)
{
    self->mUseNormalFilter = 0;
    self->mTransformed = 0;
    self->mVtable = D_0048E590;
    cRiderSphereTree_cRiderSphereTree(&self->mLocalTree);
    self->mOrigTree = (cRiderSphereTree*)tree;
    self->mTree = (cRiderSphereTree*)tree;
    self->mKind = flag == 0;
    cRiderSphereTree_getActiveBounds(tree, &self->mMin, &self->mMax);
    self->mBoxCentre = vecScale_2F650(vecAdd_2F650(&self->mMin, &self->mMax), 0.5f);
    return self;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cRiderSphereTree_destroy(void* p, int flags);
void operator_delete(int* ptr);
extern void* D_0048E590[];

extern "C" void cWorldRider_destroy(void* self, int flags)
{
    cWorldRider* t = (cWorldRider*)self;
    t->mVtable = D_0048E590;
    cRiderSphereTree_destroy(&t->mLocalTree, 2);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float subs).
static inline sSphereVec4 sphereVecSub(sSphereVec4* a, sSphereVec4* b)
{
    sSphereVec4 r;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        ".set pop\n"
        : "=m"(r)
        : "m"(*a), "m"(*b)
        : "memory");
    return r;
}

// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float adds).
static inline sSphereVec4 sphereVecAddR(sSphereVec4* a, sSphereVec4* b)
{
    sSphereVec4 r;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vadd.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        ".set pop\n"
        : "=m"(r)
        : "m"(*a), "m"(*b)
        : "memory");
    return r;
}

// broad sphere of mTree overlaps the box [mn, mx]?
extern "C" int cWorldRider_overlapsBox(void* self, sSphereVec4* mn, sSphereVec4* mx)
{
    cWorldRider* t = (cWorldRider*)self;
    sSphereVec4 rv;
    int r = 0;
    float rad = t->mTree->mRadius;
    rv.x = rad;
    rv.y = rad;
    rv.z = rad;
    rv.w = 0;
    sSphereVec4 lo = sphereVecSub(&t->mTree->mCentre, &rv);
    sSphereVec4 hi = sphereVecAddR(&t->mTree->mCentre, &rv);
    if (mx->x >= lo.x && mn->x <= hi.x && mx->y >= lo.y && mn->y <= hi.y &&
        lo.z <= mx->z && mn->z <= hi.z) {
        r = 1;
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sSphereMtx;
extern "C" void cRiderSphereTree_transform(cRiderSphereTree* s, sSphereMtx* m, float scale);

extern "C" void cWorldRider_transform(void* self, sSphereMtx* m, float scale)
{
    cWorldRider* t = (cWorldRider*)self;
    cRiderSphereTree* node = &t->mLocalTree;
    cRiderSphereTree_assign(node, t->mTree);
    t->mTree = node;
    cRiderSphereTree_transform(node, m, scale);
    t->mTransformed = 1;
}

//100%
int cWorldRider_restore__FPv(void* self)
{
    cWorldRider* t = (cWorldRider*)self;
    int t0 = *(int*)&t->mOrigTree;
    t->mTransformed = 0;
    *(int*)&t->mTree = t0;
    return t0;
}

//100%
extern "C" float cWorldRider_getRadius(void* self)
{
    cWorldRider* t = (cWorldRider*)self;
    if (t->mKind == 0) {
        return -1.0f;
    }
    cRiderSphereTree* sphere = t->mTree;
    return sphere->mRadius * 2.0f;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float sphereLength_32F8F0(const sSphereVec4& v)
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

extern "C" int cRiderSphereTree_testTriangle(void* tree, int a1, int a2, int a3, int a4, sSphereVec4* out, int a6);

extern "C" int cWorldRider_testTriangle(void* self, int a1, int a2, int a3, int a4, int a5, sSphereVec4* outDir, float* outLen)
{
    sSphereVec4 v;
    cWorldRider* t = (cWorldRider*)self;
    int r = cRiderSphereTree_testTriangle(t->mTree, a1, a2, a3, a4, &v, a5);
    if (r != 0) {
        float len = sphereLength_32F8F0(v);
        *outLen = len;
        *outDir = sphereCapsuleDiv(v, len);
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float sphereLength_32F990(const sSphereVec4& v)
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

extern "C" int cRiderSphereTree_testTriangleTwoSided(void* tree, int a1, int a2, int a3, int a4, sSphereVec4* out, int a6);

extern "C" int cWorldRider_testTriangleTwoSided(void* self, int a1, int a2, int a3, int a4, int a5, sSphereVec4* outDir, float* outLen)
{
    sSphereVec4 v;
    cWorldRider* t = (cWorldRider*)self;
    int r = cRiderSphereTree_testTriangleTwoSided(t->mTree, a1, a2, a3, a4, &v, a5);
    if (r != 0) {
        float len = sphereLength_32F990(v);
        *outLen = len;
        *outDir = sphereCapsuleDiv(v, len);
    }
    return r;
}

//100%
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float sphereLength_32FA30(const sSphereVec4& v)
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
static inline void sphereDivEq_32FA30(sSphereVec4& v, float s)
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


extern "C" int cSphereTree_testRiderSphereTree(void* a, void* tree, sSphereVec4* dir, sWorldHit* hit);

extern "C" int cWorldRider_testSphereTree(void* self, void* a1, sWorldHit* hit)
{
    cWorldRider* t = (cWorldRider*)self;
    if (cSphereTree_testRiderSphereTree(a1, t->mTree, &hit->mNormal, hit) != 0) {
        float len = sphereLength_32FA30(hit->mNormal);
        hit->mDepth = len;
        sphereDivEq_32FA30(hit->mNormal, len);
        return 1;
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float sphereLength_32FAC0(const sSphereVec4& v)
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
static inline void sphereDivEq_32FAC0(sSphereVec4& v, float s)
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


extern "C" int cRiderSphereTree_testBox(void* tree, void* a1, void* a2, sSphereVec4* dir, sWorldHit* hit);

extern "C" int cWorldRider_testBox(void* self, void* a1, void* a2, sWorldHit* hit)
{
    cWorldRider* t = (cWorldRider*)self;
    if (cRiderSphereTree_testBox(t->mTree, a1, a2, &hit->mNormal, hit) != 0) {
        float len = sphereLength_32FAC0(hit->mNormal);
        hit->mDepth = len;
        sphereDivEq_32FAC0(hit->mNormal, len);
        return 1;
    }
    return 0;
}

//100%
extern char D_0048E650[];


extern "C" cWorldSphere* cWorldSphere_cWorldSphere(cWorldSphere* self, sSphereVec4* p, int flag, float r)
{
    sSphereVec4 t;
    self->mVtable = D_0048E650;
    self->mUseNormalFilter = 0;
    self->mTransformed = 0;
    if (flag != 0) {
        self->mKind = 0;
    } else {
        self->mKind = 1;
    }
    self->mCentreSaved = *p;
    self->mCentre = self->mCentreSaved;
    self->mRadius = r;
    self->mRadiusSaved = r;
    t.x = p->x + r;
    t.y = p->y + r;
    t.z = p->z + r;
    t.w = 1.0f;
    self->mMax = t;
    t.x = p->x - r;
    t.y = p->y - r;
    t.z = p->z - r;
    self->mMin = t;
    self->mBoxCentre = *p;
    return self;
}

//100%
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float subs).
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4 float adds).
// sphere (mCentre, mRadius) overlaps the box [mn, mx]?
extern "C" int cWorldSphere_overlapsBox(void* self, sSphereVec4* mn, sSphereVec4* mx)
{
    cWorldSphere* t = (cWorldSphere*)self;
    sSphereVec4 rv;
    float rad = t->mRadius;
    rv.x = rad;
    rv.y = rad;
    rv.z = rad;
    rv.w = 0;
    sSphereVec4 hi = sphereCapsuleAdd(&t->mCentre, &rv);
    sSphereVec4 lo = sphereCapsuleSub(&t->mCentre, &rv);
    if ((mn->x > hi.x && lo.x < mn->x) || (mx->x < hi.x && mx->x < lo.x) ||
        (mn->y > hi.y && lo.y < mn->y) || (mx->y < hi.y && mx->y < lo.y) ||
        (mn->z > hi.z && lo.z < mn->z) || (mx->z < hi.z && mx->z < lo.z)) {
        return 0;
    }
    return 1;
}

//100%
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (4x4 matrix * vector).
static inline sSphereVec4 sphereMtxMulVec(sSphereVec4* m, sSphereVec4* v)
{
    sSphereVec4 r;
    __asm__(
        ".set push\n"
        ".set noreorder\n"
        "lqc2         $vf8, %1\n"
        "lqc2         $vf4, 0x0(%2)\n"
        "lqc2         $vf5, 0x10(%2)\n"
        "lqc2         $vf6, 0x20(%2)\n"
        "lqc2         $vf7, 0x30(%2)\n"
        "vmulax.xyzw  ACC, $vf4, $vf8x\n"
        "vmadday.xyzw ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw  $vf12, $vf7, $vf8w\n"
        "sqc2         $vf12, %0\n"
        ".set pop\n"
        : "=m"(r)
        : "m"(*v), "r"(m)
        : "memory");
    return r;
}

extern "C" void cWorldSphere_transform(void* self, sSphereVec4* m, float scale)
{
    cWorldSphere* t = (cWorldSphere*)self;
    sSphereVec4 p = sphereMtxMulVec(m, &t->mCentreSaved);
    t->mTransformed = 1;
    t->mCentre = p;
    t->mRadius = scale * t->mRadiusSaved;
}

//100%
extern "C" void cWorldSphere_restore(void* self)
{
    cWorldSphere* t = (cWorldSphere*)self;
    cQuad128 a = *(cQuad128*)&t->mCentreSaved;
    float f = t->mRadiusSaved;
    *(cQuad128*)&t->mCentre = a;
    t->mRadius = f;
    t->mTransformed = 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float sphereLength_32FDB0(const sSphereVec4& v)
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
static inline void sphereDivEq_32FDB0(sSphereVec4& v, float s)
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


extern "C" int cSphereTree_testSphere(void* self, void* a1, float f, void* a2, void* a3);

extern "C" int cWorldSphere_testSphereTree(void* self, void* a1, sWorldHit* hit)
{
    cWorldSphere* t = (cWorldSphere*)self;
    if (cSphereTree_testSphere(a1, &t->mCentre, t->mRadius, &hit->mNormal, hit) != 0) {
        float len = sphereLength_32FDB0(hit->mNormal);
        hit->mDepth = len;
        sphereDivEq_32FDB0(hit->mNormal, len);
        return 1;
    }
    return 0;
}

//100%
extern "C" int intersectSphereBox(void* a, void* b, void* center, void* box, void* boxMin, void* boxMax, float radius);

extern "C" int cWorldSphere_testBox(void* self, void* a, void* b, void* box)
{
    cWorldSphere* t = (cWorldSphere*)self;
    sWorldHit* h = (sWorldHit*)box;
    return intersectSphereBox(a, b, &t->mCentre, box, &h->mNormal, &h->mDepth, t->mRadius) != 0;
}

INCLUDE_ASM("intersect/riderspheretree", cWorldSphere_testTriangle);

//100%
extern "C" int cWorldSphere_planeDistance(void* self, sSphereVec4* plane, sSphereVec4* p, float* out);
extern "C" int cWorldSphere_touchesTriangleEdge(void* self, sSphereVec4* a, sSphereVec4* b, sSphereVec4* c);

// PORT: PS2-only VU0 inline asm (vector times scalar).
static inline sSphereVec4 sphereScale_32FFA0(const sSphereVec4& v, float s)
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

// PORT: PS2-only VU0 inline asm (in-place vector times scalar).
static inline void sphereScaleEq_32FFA0(sSphereVec4& v, float s)
{
    int t;
    __asm__(
        "mfc1      %1, %2\n"
        "lqc2      $vf4, %0\n"
        "qmtc2.ni  %1, $vf3\n"
        "vmulx.xyzw $vf5, $vf4, $vf3x\n"
        "sqc2      $vf5, %0\n"
        : "+m"(v), "=&r"(t)
        : "f"(s));
}

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sSphereVec4 sphereSub_32FFA0(const sSphereVec4& a, const sSphereVec4& b)
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

extern "C" int cWorldSphere_testTriangleTwoSided(void* self, sSphereVec4* a, sSphereVec4* b, sSphereVec4* c, sSphereVec4* plane,
                             sSphereVec4* outPos, sSphereVec4* outDir, float* outDist)
{
    sSphereVec4 d = *plane;
    float t;
    if (cWorldSphere_planeDistance(self, plane, a, &t) == 0) {
        return 0;
    }
    if (t < 0.0f) {
        t = -t;
        sphereScaleEq_32FFA0(d, -1.0f);
    }
    cWorldSphere* ws = (cWorldSphere*)self;
    sSphereVec4 p = sphereSub_32FFA0(ws->mCentre, sphereScale_32FFA0(d, t));
    *outPos = p;
    if (vu0PointInTriangle_tol(a, b, c, outPos, 9.999999747378752e-05f) != 0 || cWorldSphere_touchesTriangleEdge(self, a, b, c) != 0) {
        *outDir = d;
        *outDist = ws->mRadius - t;
        return 1;
    }
    return 0;
}

//100%
// Returns -dot(*a, *b) (4-component dot product on VU0, macro mode).
// PORT: PS2-only VU0 inline asm; the PC port needs a C fallback (-(ax*bx + ay*by + az*bz + aw*bw)).
INCLUDE_ASM("intersect/riderspheretree", vu0NegDot4);
extern "C" float vu0NegDot4(sSphereVec4* a, sSphereVec4* b);

//100%
// PORT: callers use this as a by-value struct return (hidden out pointer in $4).
sSphereVec4 closestPointOnSegment_def(sSphereVec4* a, sSphereVec4* b, sSphereVec4* p) __asm__("closestPointOnSegment");

sSphereVec4 closestPointOnSegment_def(sSphereVec4* a, sSphereVec4* b, sSphereVec4* p)
{
    sSphereVec4 d = Sub_CDB0(*p, *a);
    sSphereVec4 e = Sub_CDB0(*b, *a);
    sSphereVec4 n = Normalize_CDB0(e);
    float t = Dot_CDB0(n, d);
    float len = sphereLength_32FDB0(e);
    if (t <= 0.0f) {
        return *a;
    } else if (len <= t) {
        return *b;
    } else {
        sSphereVec4 r = Add_CDB0(*a, Scale_CDB0(n, t));
        return r;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: closestPointOnSegment is defined as (out, a, b, p) returning out; this caller uses it as a by-value
// struct return (hidden out pointer in $4), so bind that view to the same symbol.
sSphereVec4 closestPointOnSegment_v(sSphereVec4* a, sSphereVec4* b, sSphereVec4* p) __asm__("closestPointOnSegment");

// PORT: PS2-only VU0 inline asm (vector subtract).
static inline sSphereVec4 vu0Sub_30250(const sSphereVec4& a, const sSphereVec4& b)
{
    sSphereVec4 r;
    __asm__ __volatile__(
        "lqc2      $vf3, %1\n"
        "lqc2      $vf4, %2\n"
        "vsub.xyzw $vf5, $vf3, $vf4\n"
        "sqc2      $vf5, %0\n"
        : "=m"(r)
        : "m"(a), "m"(b));
    return r;
}

// PORT: PS2-only VU0 inline asm (4-component vector length).
static inline float vu0Length_30250(const sSphereVec4& v)
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

// does the sphere (mCentre, mRadius) touch any edge of triangle a,b,c?
extern "C" int cWorldSphere_touchesTriangleEdge(void* self, sSphereVec4* a, sSphereVec4* b, sSphereVec4* c)
{
    cWorldSphere* t = (cWorldSphere*)self;
    sSphereVec4 pt;
    sSphereVec4 tri[3];
    tri[0] = *a;
    tri[1] = *b;
    tri[2] = *c;
    for (int i = 0; i < 3; i++) {
        pt = closestPointOnSegment_v(&tri[i], &tri[(i + 1) % 3], &t->mCentre);
        float dist = vu0Length_30250(vu0Sub_30250(t->mCentre, pt));
        if (dist < t->mRadius) {
            return 1;
        }
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: PS2-only VU0 inline asm (4-component dot product).
static inline float sphereDot_330360(const sSphereVec4& a, const sSphereVec4& b)
{
    float d;
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
        : "=f"(d), "=&r"(t)
        : "m"(a), "m"(b));
    return d;
}

// PORT: PS2-only inline asm (float absolute value).
static inline float sphereAbs_330360(float x)
{
    float r;
    __asm__("abs.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

extern "C" int cWorldSphere_planeDistance(void* self, sSphereVec4* plane, sSphereVec4* p, float* out)
{
    cWorldSphere* t = (cWorldSphere*)self;
    float c = vu0NegDot4(plane, p);
    float d = sphereDot_330360(*plane, t->mCentre) + c;
    *out = d;
    return sphereAbs_330360(d) < t->mRadius;
}

