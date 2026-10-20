#ifndef INTERSECT_OVERLAPLIST_H
#define INTERSECT_OVERLAPLIST_H

#include "common.h"
#include "intersect/spacehash.h"

// Snapshot of the space hash items near a box (cOverlapList, tags
// "OverlapList" and "RTLOverlapList"). The rider keeps one at rider+0x860,
// rebuilt from its query bounds every third tick by cOverlapList_build; the
// rider queries then test only these lists instead of walking the octrees.
// The world light manager keeps eight (one per light cache slot) for its
// light candidates. 0xA14 bytes (cWorldLightMan_initLightCache allocates
// that).

struct cOverlapList {
    cSpaceHash* mHash;          // 0x000
    int mVersion;               // 0x004 mHash->mVersion at the last build (0 from the light manager)
    unsigned int mInstanceCount; // 0x008 (the light manager starts all three counts at -1)
    sWorldInstance* mInstances[64]; // 0x00C
    unsigned int mPatchCount;   // 0x10C
    sTerrainPatch* mPatches[64]; // 0x110
    unsigned int mObjectCount;  // 0x210 rails and lights
    sSpaceHashObject* mObjects[512]; // 0x214
};

typedef char cOverlapList_size_check[sizeof(cOverlapList) == 0xA14 ? 1 : -1];

// One output list of a build: the octree walk appends overlapping items.
struct sOverlapSink {
    void** mItems;              // 0x0 one of the cOverlapList arrays
    unsigned int* mCount;       // 0x4 its count
    int mCapacity;              // 0x8 64 or 512
    sSpaceHashBox* mBox;        // 0xC build box
};

// Build context: the instance, patch and object sinks (the walks that skip a
// list take a shorter prefix).
struct sOverlapBuild {
    sOverlapSink mInstances;    // 0x00
    sOverlapSink mPatches;      // 0x10
    sOverlapSink mObjects;      // 0x20
};

#endif /* INTERSECT_OVERLAPLIST_H */
