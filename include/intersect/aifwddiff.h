#ifndef INTERSECT_AIFWDDIFF_H
#define INTERSECT_AIFWDDIFF_H

#include "common.h"

// Cache of evaluated terrain patches (cAIFwdDiffCache, tag "AIFwdDiffCache"),
// reached from the space hash at +0xA4; cGame_loadTrack creates it with 40
// entries. Entries are kept on a circular LRU list and in a hash keyed by the
// patch's cache key (patch+0x150), each bucket chain sorted by key. A miss
// recycles the LRU head and re-evaluates the patch with forward differencing
// on VU0. Pads are unknown, not unused.

// 0x40-byte cell record; cAIFwdDiffCache_resetCells sets x of the first three
// vectors to 1e10 (empty).
struct sAIFwdDiffCell {
    float mData[16];            // 0x00
};

// One cached patch (0x1CD0 bytes, the stride cAIFwdDiffCache_Init allocates).
struct cAIFwdDiffEntry {
    unsigned int mKey;          // 0x0000 patch cache key, 0xFFFFFFFF free
    cAIFwdDiffEntry* mLruNext;  // 0x0004
    cAIFwdDiffEntry* mLruPrev;  // 0x0008
    cAIFwdDiffEntry* mHashNext; // 0x000C bucket chain (ascending keys)
    float mGrid[0x190];         // 0x0010 evaluated patch points from VU0 (100 float4)
    sAIFwdDiffCell mCells[81];  // 0x0650 9 x 9 cell records
    sAIFwdDiffCell mRow[9];     // 0x1A90 9 further records
};

typedef char cAIFwdDiffEntry_size_check[sizeof(cAIFwdDiffEntry) == 0x1CD0 ? 1 : -1];

struct cAIFwdDiffCache {
    cAIFwdDiffEntry* mEntries;  // 0x0 n entries
    cAIFwdDiffEntry* mLru;      // 0x4 least recently used entry (next to recycle)
    cAIFwdDiffEntry** mBuckets; // 0x8 "AIFwdDiffHash"
    unsigned int mBucketCount;  // 0xC 2n + 13
};

typedef char cAIFwdDiffCache_size_check[sizeof(cAIFwdDiffCache) == 0x10 ? 1 : -1];

#endif /* INTERSECT_AIFWDDIFF_H */
