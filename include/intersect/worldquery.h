#ifndef INTERSECT_WORLDQUERY_H
#define INTERSECT_WORLDQUERY_H

#include "common.h"
#include "intersect/spheretree.h"
#include "intersect/riderspheretree.h"

// World collision queries. A query shape (line, rider body, sphere, sphere
// tree) is wrapped in one of the cWorldIntType classes below and handed to the
// world collectors, which call it through the vtable at +0x50 (GCC2 entries
// {short delta, short index, fn}; slot 1 transform(mtx, scale), 2 restore,
// 3 getRadius, 4 testTriangle, 5 testTriangleTwoSided, 6 testSphereTree,
// 7 testBox, 8 refinePatch, 9 overlapsBox, 10 deleting destructor). Class names
// other than cWorldSphTree are inferred from the unit names. Pads are unknown,
// not unused.

// Contact packet written by the queries (0x80 bytes; collectors take arrays of
// these with a capacity).
struct sWorldHit {
    sSphereVec4 mPos;           // 0x00 contact point
    sSphereVec4 mNormal;        // 0x10 push direction (normalised by the cWorld* wrappers)
    sSphereVec4 mSurfaceVel;    // 0x20 surface velocity (reset to D_004FF120)
    sSphereVec4 mVec30;         // 0x30 reset to D_004FF120
    float mDepth;               // 0x40 depth / distance / ray fraction; -1 none
    int mType;                  // 0x44 2 after a reset
    void* mCollider;            // 0x48 hit node's prebuilt collider
    int mSurface;               // 0x4C surface id, -1 none
    void* mInstance;            // 0x50 instance, 0 for terrain
    void* mPatch;               // 0x54 terrain patch
    int mUnk58;                 // 0x58 reset to 0
    int mUnk5C;                 // 0x5C reset to -1
    int mTriangle;              // 0x60 triangle index in a mesh, -1 none
    int mUnk64;                 // 0x64 reset to -1
    float mUnk68;               // 0x68 reset to 0
    float mU;                   // 0x6C patch u
    float mV;                   // 0x70 patch v
    char pad74[0xC];
};

typedef char sWorldHit_size_check[sizeof(sWorldHit) == 0x80 ? 1 : -1];

// Shared base.
struct cWorldIntType {
    int mKind;                  // 0x00 0: no preferred depth (getRadius returns -1); line: its kind arg
    int mTransformed;           // 0x04 1 while moved into node-local space (transform/restore)
    int mUseNormalFilter;       // 0x08 skip triangles whose normal . mFilterDir > 0.8
    char pad0C[0x4];
    sSphereVec4 mFilterDir;     // 0x10 filter direction (the ground normal)
    sSphereVec4 mMax;           // 0x20 AABB max (w = 1)
    sSphereVec4 mMin;           // 0x30 AABB min (w = 1)
    sSphereVec4 mBoxCentre;     // 0x40 AABB centre
    void* mVtable;              // 0x50
    char pad54[0xC];
};

typedef char cWorldIntType_size_check[sizeof(cWorldIntType) == 0x60 ? 1 : -1];

// Segment p0 .. p0 + dir (vtable D_0048E6A8).
struct cWorldLine : cWorldIntType {
    sSphereVec4 mP0;            // 0x60 start (current space)
    sSphereVec4 mDir;           // 0x70 p1 - p0 (current space)
    sSphereVec4 mP0Saved;       // 0x80 world-space start
    sSphereVec4 mDirSaved;      // 0x90 world-space direction
    float mRadius;              // 0xA0 radius / preferred fraction (getRadius)
};

// Rider body (vtable D_0048E590). 0x320 bytes: 0x70 + an embedded 0x2B0 tree.
struct cWorldRider : cWorldIntType {
    cRiderSphereTree* mTree;     // 0x60 current body (mLocalTree while transformed)
    cRiderSphereTree* mOrigTree; // 0x64 caller's body
    char pad68[0x8];
    cRiderSphereTree mLocalTree; // 0x70 transformed copy
};

typedef char cWorldRider_size_check[sizeof(cWorldRider) == 0x320 ? 1 : -1];

// Sphere (vtable D_0048E650).
struct cWorldSphere : cWorldIntType {
    sSphereVec4 mCentre;        // 0x60 current space
    float mRadius;              // 0x70 current space
    char pad74[0xC];
    sSphereVec4 mCentreSaved;   // 0x80 world space
    float mRadiusSaved;         // 0x90 world space
};

// Sphere tree (vtable D_0048E5F0).
struct cWorldSphTree : cWorldIntType {
    cSphereTree* mTree;         // 0x60 current tree (mScratch while transformed)
    cSphereTree* mOrigTree;     // 0x64 caller's tree
    cSphereTree* mScratch;      // 0x68 owned copy (0x140, "SphereTree")
};

#endif /* INTERSECT_WORLDQUERY_H */
