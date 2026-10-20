#ifndef INTERSECT_SPHERETREE_H
#define INTERSECT_SPHERETREE_H

#include "common.h"

// Sphere-tree collider (cSphereTree, allocation tag "SphereTree"). One is built
// per type-3 ("format 3") collision node, the crashbag modifier keeps one at
// +0xE0, and cWorldSphTree owns a scratch copy. The tree is an implicit octree:
// level d spheres have radius levels[d].mRadius * mScale, and the child i of a
// node sits at node + mDirs[i] * levels[d + 1].mOffset. Occupancy is one byte
// per node (bit i = child i), unpacked on demand by cSphereTree_getMasks. The
// object is 0x140 bytes (the size cWorldSphTree allocates). Pads are unknown,
// not unused.

struct sSphereVec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// One octree level (12 bytes; the loader skips (mDepth + 1) * 0xC bytes).
struct sSphereTreeLevel {
    float mRadius;              // 0x0 sphere radius at this level (tree space)
    float mOffset;              // 0x4 child centre offset along mDirs[i]
    int mStride;                // 0x8 child i's subtree starts at base + (i + 1) * stride
};

// Tree header, embedded at cSphereTree+0xC0 and filled by cSphereTree_load
// from the resource (file offsets in brackets). 0x80 bytes (cSphereTree_assign
// copies it as one block).
struct sSphereTreeHeader {
    int mKey;                   // 0x00 mask-cache key (load argument)
    int mCacheSlot;             // 0x04 last mask-cache slot that held this key (load sets 0)
    int mPacked;                // 0x08 [0x08] masks are PackBits-compressed; getMasks fills mMasks
    int mDepth;                 // 0x0C [0x0C] deepest level; also picks the shallow/deep mask cache
    int mUnk10;                 // 0x10 set to 1 by load; reader unknown
    float mRootCentre[3];       // 0x14 [0x10] root centre in tree space; load copies it to mCentre
    sSphereTreeLevel* mLevels;  // 0x20 [0x70] mDepth + 1 levels
    signed char* mPackedMasks;  // 0x24 PackBits stream after the levels
    unsigned char* mMasks;      // 0x28 occupancy byte per node (mPackedMasks when not packed)
    float mMassCentre[3];       // 0x2C [0x1C] centre of mass (crashbags)
    float mInertia[9];          // 0x38 [0x28] inertia tensor (crashbags)
    float mInvInertia[9];       // 0x5C [0x4C] inverse inertia tensor (crashbags)
};

typedef char sSphereTreeHeader_size_check[sizeof(sSphereTreeHeader) == 0x80 ? 1 : -1];

struct cSphereTree {
    sSphereVec4 mDirs[8];       // 0x000 octant directions (reset: D_004FF640; dirs[7 - i] = -dirs[i])
    sSphereVec4 mCentre;        // 0x080 root centre (world space once placed)
    float mScale;               // 0x090 instance scale applied to the level radii
    float mBestDepth;           // 0x094 plane/triangle walks: best signed depth, < 0 means hit
    sSphereTreeHeader* mHeader; // 0x098 normally &mHeaderData; 0 after construction
    int mOrder[8];              // 0x09C child visit order (cSphereTree_sortChildren)
    char pad0BC[0x4];
    sSphereTreeHeader mHeaderData; // 0x0C0
};

typedef char cSphereTree_size_check[sizeof(cSphereTree) == 0x140 ? 1 : -1];

#endif /* INTERSECT_SPHERETREE_H */
