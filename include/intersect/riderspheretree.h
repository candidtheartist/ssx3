#ifndef INTERSECT_RIDERSPHERETREE_H
#define INTERSECT_RIDERSPHERETREE_H

#include "common.h"
#include "intersect/spheretree.h"

// Rider collision body (cRiderSphereTree, tags "RiderSphereTree" at rider+0xAA0
// and "BoardSphereTree" in the wipeout motion): a broad sphere plus up to 20
// bone-attached child spheres. 0x2B0 bytes (both allocations; cWorldRider
// embeds one at +0x70). Pads are unknown, not unused.

// Bone pose record the spheres follow (32 bytes; position first).
struct sRiderSphereBone {
    sSphereVec4 mPos;           // 0x00
    char pad10[0x10];
};

struct sRiderSphere {
    sSphereVec4 mPos;           // 0x00 centre
    float mRadius;              // 0x10
    int mBone;                  // 0x14 bone index into mBones (-1 none)
    char pad18[0x8];
};

struct cRiderSphereTree {
    sRiderSphereBone* mBones;   // 0x000 bone pose table (0 for a single sphere)
    char pad004[0xC];
    sSphereVec4 mCentre;        // 0x010 broad sphere centre
    float mRadius;              // 0x020 broad sphere radius
    int mCentreBone;            // 0x024 bone the broad centre follows (-1 none)
    unsigned int mActiveMask;   // 0x028 enabled child spheres; 0 = broad sphere only
    int mCount;                 // 0x02C child sphere count
    sRiderSphere mSpheres[20];  // 0x030 (the constructor loops 20 times)
};

typedef char cRiderSphereTree_size_check[sizeof(cRiderSphereTree) == 0x2B0 ? 1 : -1];

#endif /* INTERSECT_RIDERSPHERETREE_H */
