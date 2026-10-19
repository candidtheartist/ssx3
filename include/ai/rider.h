#ifndef AI_RIDER_H
#define AI_RIDER_H

#include "common.h"

// Partial layout of the rider object (cRider), from docs/notes/structs/rider.md.
// Only fields whose meaning was checked are named; the pads are unknown, not
// unused. The size of the object is not known, so never take sizeof(cRider).

struct sRiderVec4 {
    float x, y, z, w;
};

// One of the 19 filtered values at 0x1F0..0x2D3: each tick current moves
// toward target by rate.
struct sRiderFilter {
    float current;
    float rate;
    float target;
};

struct cRider {
    char pad000[0x110];
    sRiderVec4 mPosition;               // 0x110 physical position (cm, Z-up)
    sRiderVec4 mOrientation;            // 0x120 physical orientation quaternion (XYZW)
    char pad130[0x70];
    sRiderVec4 mRight;                  // 0x1A0 physical right axis
    sRiderVec4 mForward;                // 0x1B0 physical forward axis
    sRiderVec4 mUp;                     // 0x1C0 physical up axis
    char pad1D0[0x10];
    sRiderVec4 mVelocity;               // 0x1E0 cm/s, Z-up
    sRiderFilter mTurn;                 // 0x1F0 physical (effective) turn
    sRiderFilter mAnimTurn;             // 0x1FC animation turn (ground cycle blend)
    sRiderFilter mExtraLean;            // 0x208
    sRiderFilter mBrake;                // 0x214
    sRiderFilter mCrouch;               // 0x220 crouch / jump charge
    sRiderFilter mRailSteer;            // 0x22C
    sRiderFilter mRailBalance;          // 0x238
    sRiderFilter mPipeBalance;          // 0x244 half-pipe / handplant balance
    sRiderFilter mPresentationRoll;     // 0x250
    sRiderFilter mRailAttach;           // 0x25C rail attach tolerance
    sRiderFilter mBoardPress;           // 0x268 board-press depth 0..1
    sRiderFilter mFilter274;            // 0x274 meaning unresolved
    sRiderFilter mBoardPivot;           // 0x280 -1..1, times pi is the angle
    sRiderFilter mAirAdjust;            // 0x28C
    sRiderFilter mAirAdjust2;           // 0x298
    sRiderFilter mPrewind;              // 0x2A4
    sRiderFilter mPrewind2;             // 0x2B0
    sRiderFilter mBoardAlign;           // 0x2BC board-alignment weight
    sRiderFilter mPresentationLift;     // 0x2C8 body-root lift
    unsigned int mPatchFlags;           // 0x2D4 runtime flags of the contacted terrain patch
    char pad2D8[0xC];
    float mSpeedLimit;                  // 0x2E4 3333.33 in normal motion
    float mBoostPickupTime;             // 0x2E8
    float mBoostCounter;                // 0x2EC
    float mTrickyTime;                  // 0x2F0 Tricky / Super Uber timer (s)
    int mUberTier;                      // 0x2F4 0..10, 10 = Super Uber
    float mBoostMeter;                  // 0x2F8 stored boost meter 0..1
    float mBoostAmount;                 // 0x2FC 0 / 0.25 / 0.625 / 1
    float mTimeScale;                   // 0x300 rubber band: dt = timeScale / 60
    int mBoostPolicy;                   // 0x304 0 full, 1 normal decay, 2 fast decay, 3 no awards
    char pad308[0x10];
    float mLegIKWeight;                 // 0x318
    char pad31C[0x4];
    int mSwitchStance;                  // 0x320 toggled by stance flips
    int mDefaultStance;                 // 0x324
    int mGrindStyle;                    // 0x328 0 none, 1 50-50, 2 backward, 3 frontside, 4 backside
    char pad32C[0x4];
    int mPressStyle;                    // 0x330 board press: 0 none, 1 nose, 2 tail
    char pad334[0x20];
    int mReactionTick;                  // 0x354 logic tick a pending reaction is due
    int mReactionKind;                  // 0x358 pending reaction kind
    char pad35C[0x14];
    sRiderVec4 mContactNormal;          // 0x370
    sRiderVec4 mPrevContactNormal;      // 0x380
    char pad390[0x70];
    sRiderVec4 mBoundsMin;              // 0x400 query bounds (body AABB)
    sRiderVec4 mBoundsMax;              // 0x410
    char pad420[0x18];
    int mSurfaceId;                     // 0x438 current surface id
    char pad43C[0x34];
    float mFinishTimer;                 // 0x470 < 0 unfinished, then +1/60 per tick
    char pad474[0x4];
    int mFinishTicks;                   // 0x478 race ticks at the finish + penaltyTicks
    int mPenaltyTicks;                  // 0x47C
    int mDidNotFinish;                  // 0x480 time limit or Give Up
    char pad484[0x40];
    float mRouteDistance;               // 0x4C4 distance along the retained route path
    char pad4C8[0x8];
    float mRemainingDistance;           // 0x4D0 cm to the finish
    char pad4D4[0x1EC];
    void* mInterfaceVtbl;               // 0x6C0 interface subobject vtable (human 0x004583A8, computer 0x00458660)
    char pad6C4[0xB8];
    void* mMotion;                      // 0x77C motion owner and rider FX container (+0xDE0 motion mode)
    void* mGeometry;                    // 0x780 model / rig (bones at +0x2C)
    void* mAnimator;                    // 0x784 cRiderAnimBase
    void* mAirPredictor;                // 0x788 cAirPredictor
    char pad78C[0x4];
    void* mRiderMetrix;                 // 0x790 cRiderMetrix: trick score object (0x1CC bytes)
    void* mLights[8];                   // 0x794 selected local lights
    char pad7B4[0xAC];
    void* mQueryScope;                  // 0x860 nearby-object cache, rebuilt from boundsMin/Max
    void* mGroundCache;                 // 0x864 coarse ground contact cache
    void* mBodyCache;                   // 0x868 body collision cache
    int mSlot;                          // 0x86C grid / roster slot (0 human, 1..5 computer); meaning not fully settled
    int mPlayerIndex;                   // 0x870 controller / player index, -1 for computer riders
    int mIsHuman;                       // 0x874 local player flag
    char pad878[0x4];
    int mControllerEnabled;             // 0x87C
    int mActorState;                    // 0x880 pair records are enabled only when 7
    char pad884[0x18];
    int mRootBone;                      // 0x89C root / hips bone index
    int mBoardRootBone;                 // 0x8A0
    int mBoardBone;                     // 0x8A4
    int mHeadBone;                      // 0x8A8
    char pad8AC[0x1F4];
    void* mCollisionBody;               // 0xAA0
    char padAA4[0x88];
    unsigned int mAbilityFlags;         // 0xB2C bit 0 Uber selection, bit 1 rail Uber
    char padB30[0x4];
    int mStatLevel;                     // 0xB34 11 = maxed stats
};

#endif /* AI_RIDER_H */
