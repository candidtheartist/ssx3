#ifndef AI_RIDERMETRIX_H
#define AI_RIDERMETRIX_H

#include "common.h"

// Trick score object (cRiderMetrix), reached as cRider::mRiderMetrix
// (rider+0x790). Layout from docs/notes/structs/rider-components.md
// ("Score object"); only fields whose meaning was checked are named, and the
// pads are unknown, not unused. Rewards are kept in units of 10000 points
// until they are paid out.

struct cRiderMetrix {
    int mStance;                    // 0x000 set at landing to rider mSwitchStance != mDefaultStance
    int mAltTable;                  // 0x004 alternate trick table (steep landing / ramp takeoff)
    int mMultiTrick;                // 0x008 nonzero skips repeat matching and insertion
    int mStyle;                     // 0x00C style value
    int mPressStyle;                // 0x010 rider mPressStyle copied at landing
    float mReward;                  // 0x014 pending trick reward, points / 10000 before multipliers
    float mMultiplier;              // 0x018 raised by multiplier icon pickups
    float mInvertedReward;          // 0x01C inverted / stall reward (INVERTED! message)
    int mTrickStyle;                // 0x020 nonzero skips repeat history
    float mRailDistance;            // 0x024 grind distance (cm), -1 inactive
    int mSpecial;                   // 0x028 special record flag; nonzero skips repeat history
    float mManualTime;              // 0x02C manual timer, -1 inactive
    float mAirTime;                 // 0x030 air time (s)
    float mSpin;                    // 0x034 spin of the current trick
    float mFlip;                    // 0x038 flip of the current trick
    float mHoldRate;                // 0x03C added to mReward each held tick
    float mHoldTime;                // 0x040 current hold (s), -1 inactive
    float mTotalHoldTime;           // 0x044
    float mLongestHold;             // 0x048
    int mNormalCount;               // 0x04C normal tricks (score ids below 19)
    int mTweakCount;                // 0x050 tweaks (score ids 19..34)
    int mUberCount;                 // 0x054 Ubers this air (score ids 35+)
    int mSuperUberCount;            // 0x058
    int mActiveUber;                // 0x05C set while an Uber is being done
    int mGrabs[3];                  // 0x060 grab ids of the current trick
    float mActiveTime;              // 0x06C active timer, negative = inactive
    int mActive;                    // 0x070 nonzero skips repeat history
    int mUberCount2;                // 0x074 counted together with mUberCount
    char pad078[0x4];
    int mIdentity;                  // 0x07C nonzero skips repeat history
    char pad080[0x4];
    int mBonusPoints;               // 0x084 hold / distance threshold bonuses
    int mBonusStep[5];              // 0x088 next threshold per bonus kind; [1] is the hold one
    int mComboCount;                // 0x09C combo multiplier = clamp((count + 10) * 0.05, 0.5, 2)
    int mComboPoints;               // 0x0A0
    float mComboClock;              // 0x0A4 combo timeout, -1 suspended
    int mRepeatHistory[20];         // 0x0A8 10 trick ids of 8 bytes
    int mRepeatCursor;              // 0x0F8 mod 10
    char pad0FC[0x14];
    int mRunTrickCount;             // 0x110 run statistics (+0xFC..+0x1A8) start here
    int mRunUberCount;              // 0x114 drives Uber tier progression
    int mRunSuperUberCount;         // 0x118
    int mRunUberGrindCount;         // 0x11C
    int mRunResetCount;             // 0x120
    char pad124[0x4];
    int mRunKnockouts;              // 0x128
    char pad12C[0x4];
    int mRunMultiplierPickups;      // 0x130
    int mRunComboTricks;            // 0x134
    char pad138[0x14];
    float mRunAirStat;              // 0x14C StayInAir personal best
    char pad150[0x4];
    float mRunRailStat;             // 0x154 StayOnRail personal best
    float mRunHandplantStat;        // 0x158 HoldHandplant personal best
    char pad15C[0x28];
    int mBestCombo[2];              // 0x184
    int mBestTrick;                 // 0x18C
    char pad190[0x8];
    int mTotalScore;                // 0x198
    char pad19C[0x4];
    int mLostPoints[2];             // 0x1A0
    char pad1A8[0x4];
    char* mRider;                   // 0x1AC owning cRider
    char* mMsgSlots;                // 0x1B0 HUD message bank, 44 slots of 0x9C bytes; null without HUD
    char pad1B4[0x4];
    int mRenderMask;                // 0x1B8
    char pad1BC[0x8];
    float mScoreMult;               // 0x1C4 1 after construction
    int mStartingScore;             // 0x1C8 set by cRiderMetrix_setStartingScore; mTotalScore restarts from it
};

typedef char cRiderMetrix_size_check[sizeof(cRiderMetrix) == 0x1CC ? 1 : -1];

#endif /* AI_RIDERMETRIX_H */
