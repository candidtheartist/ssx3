#ifndef ANIMATION_GAMEANIMMAP_H
#define ANIMATION_GAMEANIMMAP_H

#include "common.h"

// Game animation map (cGameAnimMap): resolves the game's animation ids (the
// 0x206 names in D_0048CFC0) to loaded clips. One instance, 0x1848 bytes
// (cSSXApp_initload allocates it), is kept in D_004A3E7C. addBank/removeBank
// fill and clear mClips from the clip banks; cRiderAnimBase and the
// controllers read mClips[id] directly. Id 0x207 means "no animation".

#define GAMEANIM_COUNT 0x206

struct cGameAnimMap {
    unsigned int mNameHashes[GAMEANIM_COUNT]; // 0x0000 GetHashValue32 of each name
    int mSortedOrder[GAMEANIM_COUNT];         // 0x0818 ids sorted by hash, for findAnim's binary search
    int mClips[GAMEANIM_COUNT];               // 0x1030 clip handle per id: low 8 bits bank, rest clip index; -1 after init
};

typedef char cGameAnimMap_size_check[sizeof(cGameAnimMap) == 0x1848 ? 1 : -1];

#endif /* ANIMATION_GAMEANIMMAP_H */
