#ifndef ANIMATION_ANIMSEQUENCE_H
#define ANIMATION_ANIMSEQUENCE_H

#include "common.h"
#include "animation/animmodel.h"

// Animation playback sequence (cAnimSequence) and the per-channel list that
// holds them (cAnimSequencer). cRiderAnimBase::mSequencers points at six
// cAnimSequencers, one per channel. A sequence is a 0xD0-byte block
// (cAnimSequencer_newSequence allocates 0xD0 and runs
// cAnimSequence_cAnimSequence on it) with three playback slots, a blend
// weight that fades towards a target, and a list of trigger nodes.
// Pads are unknown, not unused.

// Trigger node (0x10 bytes, allocated by addTrigger/addEndTrigger, saved
// and loaded whole). Kept in a singly linked list at cAnimSequence::mTriggers.
struct cAnimSequenceTrigger {
    int mKey;                         // 0x00 trigger id
    int mIsEndTrigger;                // 0x04 1 = end trigger (addEndTrigger), 0 = point trigger
    float mPoint;                     // 0x08 point trigger: value given to addTrigger; 0 for end triggers
    cAnimSequenceTrigger* mNext;      // 0x0C next trigger
};

// Playback slot; three per sequence, stride 0x1C. Slot 0 is the primary.
struct cAnimSequenceSlot {
    int mClip;                        // 0x00 packed clip id: low 8 bits bank, rest animation index
    float mTime;                      // 0x04 clock (seconds)
    float mRate;                      // 0x08 slot playback rate
    float mLength;                    // 0x0C duration = (frames - 1) / 30
    float mWeight;                    // 0x10 slot weight
    int mEnabled;                     // 0x14 nonzero while the slot plays
    int mLoop;                        // 0x18 loop flag
};

struct cAnimSequence {
    int mSemantic;                    // 0x00 semantic state id (constructor argument; hasAnim/findAnim key)
    cAnimSequenceSlot mSlots[3];      // 0x04 playback slots
    char pad58[0x8];
    sAnimVec4 mRootPos;               // 0x60 per-sequence root translation
    sAnimVec4 mRootRot;               // 0x70 per-sequence root quaternion
    int mMirror;                      // 0x80 mirror flag
    int mPriority;                    // 0x84 channel priority
    ulong mBoneMask;                  // 0x88 64-bit on ee-gcc; bone mask, -1 = all
    float mRate;                      // 0x90 sequence playback rate
    float mWeight;                    // 0x94 current blend weight
    float mTargetWeight;              // 0x98 weight being faded towards
    float mFadeTime;                  // 0x9C fade time remaining
    int mRemoveWhenFaded;             // 0xA0 drop the sequence once the fade ends
    float mFadeOutTime;               // 0xA4 slot weight ramps down over the last this many seconds
    float mFadeInTime;                // 0xA8 slot weight ramps up over the first this many seconds
    cAnimSequenceTrigger* mTriggers;  // 0xAC trigger list head
    ulong mLatchedFlags;              // 0xB0 latched event flags
    ulong mNewFlags;                  // 0xB8 newly raised event flags
    int mCompleted;                   // 0xC0 completion flag
    int mSeekPending;                 // 0xC4 set when a slot clip or time is changed
    cAnimSequence* mNext;             // 0xC8 next sequence in the channel list
    char padCC[0x4];
};

typedef char cAnimSequenceSlot_size_check[sizeof(cAnimSequenceSlot) == 0x1C ? 1 : -1];
typedef char cAnimSequence_size_check[sizeof(cAnimSequence) == 0xD0 ? 1 : -1];

// One channel's sequence list (8 bytes).
struct cAnimSequencer {
    int mCount;                       // 0x0 number of sequences in the list
    cAnimSequence* mFirstSequence;    // 0x4 list head, linked through mNext
};

typedef char cAnimSequencer_size_check[sizeof(cAnimSequencer) == 0x8 ? 1 : -1];

#endif /* ANIMATION_ANIMSEQUENCE_H */
