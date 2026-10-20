#ifndef INTERSECT_SPACEHASH_H
#define INTERSECT_SPACEHASH_H

#include "common.h"
#include "intersect/spheretree.h"
#include "intersect/aifwddiff.h"
#include "intersect/worldquery.h"

// World spatial hash (cSpaceHash, returned by 0x002D1BE0): eight sparse
// octrees, one per octant of world space (picked by the sign bits of the cell
// x/y/z), each with a root cell that grows upward as items are inserted. A
// cell at level L is 2^L units wide (padded by 0.2 cell on each side when
// testing a box; level 11 is the smallest). Every octree node holds three
// intrusive lists: world instances, terrain patches and other objects (rails,
// lights). Items sit at the head of their list. Pads are unknown, not unused.

// Octree cell key (cSpaceHash_computeCell).
struct sSpaceHashCell {
    int mLevel;                 // 0x0 cell size is 2^mLevel
    int mX;                     // 0x4
    int mY;                     // 0x8
    int mZ;                     // 0xC
};

// Query box (two vec4, min first; e.g. the rider query bounds at +0x400).
struct sSpaceHashBox {
    sSphereVec4 mMin;           // 0x00
    sSphereVec4 mMax;           // 0x10
};

// List link at the start of every item.
struct sSpaceHashItem {
    sSpaceHashItem* mNext;      // 0x0
    sSpaceHashItem* mPrev;      // 0x4 0 at the list head
};

struct sSpaceHashList {
    sSpaceHashItem* mHead;      // 0x0

    sSpaceHashList() : mHead(0) {}
    void push(sSpaceHashItem* it)
    {
        if (mHead) mHead->mPrev = it;
        it->mNext = mHead;
        it->mPrev = 0;
        mHead = it;
    }
    void remove(sSpaceHashItem* it)
    {
        if (it->mNext) it->mNext->mPrev = it->mPrev;
        if (it->mPrev) {
            it->mPrev->mNext = it->mNext;
        } else {
            mHead = it->mNext;
        }
    }
};

enum {
    SPACEHASH_INSTANCES = 0,    // sWorldInstance
    SPACEHASH_PATCHES = 1,      // sTerrainPatch
    SPACEHASH_OBJECTS = 2       // sSpaceHashObject
};

// Octree node (0x2C bytes, tag D_004A3FC0). Child [x][y][z] covers the
// half-cell (2 * cell + x, 2 * cell + y, 2 * cell + z) one level down.
struct cSpaceHashNode {
    cSpaceHashNode* mChild[2][2][2]; // 0x00
    sSpaceHashList mLists[3];        // 0x20 SPACEHASH_INSTANCES / _PATCHES / _OBJECTS

    int empty()
    {
        if (mChild[0][0][0] || mChild[0][0][1] || mChild[0][1][0] || mChild[0][1][1] || mChild[1][0][0] ||
            mChild[1][0][1] || mChild[1][1][0] || mChild[1][1][1]) {
            return 0;
        }
        for (int i = 0; i < 3; i++) {
            if (mLists[i].mHead) return 0;
        }
        return 1;
    }
};

typedef char cSpaceHashNode_size_check[sizeof(cSpaceHashNode) == 0x2C ? 1 : -1];

// One octant's octree.
struct sSpaceHashRoot {
    sSpaceHashCell mCell;       // 0x00 cell covered by mNode
    cSpaceHashNode* mNode;      // 0x10 0 while empty
};

typedef char sSpaceHashRoot_size_check[sizeof(sSpaceHashRoot) == 0x14 ? 1 : -1];

struct cSpaceHash {
    sSpaceHashRoot mRoots[2][2][2]; // 0x00 [x < 0][y < 0][z < 0] of the item's cell
    int mVersion;               // 0x0A0 change counter (item removal bumps it); cOverlapList keeps the value it was built at
    cAIFwdDiffCache* mFwdDiff;  // 0x0A4 terrain patch cache (40 entries)
};

// GCC2 virtual table entry.
struct sWorldVEntry {
    short mDelta;               // 0x0 this adjustment
    short mIndex;               // 0x2
    void* mFn;                  // 0x4
};

// Script / set-piece entity attached to a world instance.
struct sWorldEntity {
    char pad00[0xC];
    sWorldVEntry* mVtable;      // 0x0C slot 44 (+0x160) collidable predicate, slot 45 (+0x168) box getter
};

// Placed world instance (SPACEHASH_INSTANCES item).
struct sWorldInstance {
    sSpaceHashItem mLink;       // 0x00
    unsigned int mFlags;        // 0x08 runtime flags: 0x20 inline box (mMin/mMax), 0x40 entity box
    sWorldEntity* mEntity;      // 0x0C 0 when none
    float mMatrix[16];          // 0x10 world matrix (row 3 = translation)
    char pad50[0x10];
    float mMin[3];              // 0x60 bounds
    float mMax[3];              // 0x6C
    unsigned int mResId;        // 0x78 resource id (nearest-hit tie-break, lower first)
    char pad7C[0xC];
    void* mCollision;           // 0x88 kind-16 collision descriptor, 0 = no collision
};

// Terrain patch (SPACEHASH_PATCHES item).
struct sTerrainPatch {
    sSpaceHashItem mLink;       // 0x000
    short mSurface;             // 0x008 surface id
    unsigned short mFlags;      // 0x00A 0x1 collidable, 0x40 active; collision wants both
    char pad00C[0x144];
    unsigned int mKey;          // 0x150 resource id; cAIFwdDiffCache key and nearest-hit tie-break
    char pad154[0x4];
    float mMin[3];              // 0x158 bounds
    float mMax[3];              // 0x164
};

// Other object (SPACEHASH_OBJECTS item; 0x10 bytes as cFlexRailNode allocates
// it, except a static rail segment, which is its own item).
struct sSpaceHashObject {
    sSpaceHashItem mLink;       // 0x0
    int mType;                  // 0x8 1 static rail segment, 2 object rail, 3 flex rail, 6 light
    void* mObject;              // 0xC owner (types 2, 3, 6)
};

typedef char sSpaceHashObject_size_check[sizeof(sSpaceHashObject) == 0x10 ? 1 : -1];

// Static rail spline record header (48 bytes, followed by its segments).
struct sRailSpline {
    char pad00[0x1C];
    unsigned int mFlags;        // 0x1C rider mask bits (tested against the query mask)
};

// Static rail spline segment (0x90 bytes); a type-1 sSpaceHashObject.
struct sRailSegment {
    sSpaceHashItem mLink;       // 0x00
    int mType;                  // 0x08 1
    float mLength;              // 0x0C arc length
    sSphereVec4 mCubic[4];      // 0x10 t^3, t^2, t, 1 rows
    sSphereVec4 mArcCoef;       // 0x50 arc length to parameter cubic
    int mPrev;                  // 0x60 previous global segment (-1 at the start)
    int mNext;                  // 0x64
    sRailSpline* mSpline;       // 0x68 record header
    float mMin[3];              // 0x6C bounds
    float mMax[3];              // 0x78
    float mDist;                // 0x84 distance at t = 0
    char pad88[0x4];
    unsigned int mSegFlags;     // 0x8C
};

typedef char sRailSegment_size_check[sizeof(sRailSegment) == 0x90 ? 1 : -1];

// Collector context the space hash walks hand to the per-item collectors.
struct sSpaceHashCollect {
    cWorldIntType* mQuery;      // 0x00
    sWorldHit* mHits;           // 0x04
    int mCapacity;              // 0x08
    int* mCount;                // 0x0C
    int mArg;                   // 0x10 patch test argument; scenery: nonzero = mode 3
    cAIFwdDiffCache* mFwdDiff;  // 0x14 patch collectors only
};

#endif /* INTERSECT_SPACEHASH_H */
