#ifndef ANIMATION_RIDERANIMBASE_H
#define ANIMATION_RIDERANIMBASE_H

#include "common.h"
#include "animation/animmodel.h"

// Rider animator (cRiderAnimBase), reached as cRider::mAnimator
// (rider+0x784). The rider's is a 0x70-byte "RiderAnim" object whose
// vtable (0x00458458) replaces the base one; mRider and mAltActor exist
// only in that derived object. Each of the six channels has a sequencer
// (count, list head) in mSequencers. Pads are unknown, not unused.

// Channel numbers, in the order of the game's channel name table.
#define ANIMCH_GRAFT_CYCLE   0
#define ANIMCH_GRAFT         1
#define ANIMCH_BODY          2
#define ANIMCH_HEAD_REL2ND   3
#define ANIMCH_TORSO_REL2ND  4
#define ANIMCH_LEGS_REL2ND   5
#define ANIMCH_COUNT         6

struct cRiderAnimBase {
    int mRequestedAnim[6];            // 0x000 requested anim per channel; 438 after a reset
    int mMirror;                      // 0x018 copied to new sequences; rider stance after a flip
    float mPendingRate;               // 0x01C playback rate for new sequences
    ulong mBoneMask;                  // 0x020 64-bit on ee-gcc; bone mask for new sequences; -1 = all
    char pad028[0x8];
    sAnimVec4 mDefaultRootPos;        // 0x030 root translation for new sequences
    sAnimVec4 mDefaultRootRot;        // 0x040 root quaternion for new sequences
    char* mSequencers;                // 0x050 "Sequencers": six {count, head} pairs
    char* mModel;                     // 0x054 cAnimModel the sampler poses
    void* mVtable;                    // 0x058
    char pad05C[0x4];
    char* mRider;                     // 0x060 RiderAnim only: owning cRider
    char* mAltActor;                  // 0x064 RiderAnim only: front-end actor, preferred when set
    char pad068[0x8];
};

typedef char cRiderAnimBase_size_check[sizeof(cRiderAnimBase) == 0x70 ? 1 : -1];

#endif /* ANIMATION_RIDERANIMBASE_H */
