#ifndef AI_MOTIONOWNER_H
#define AI_MOTIONOWNER_H

#include "common.h"

// Motion owner (cMotionOwner), reached as cRider::mMotion (rider+0x77C).
// It holds one receiver per motion mode, the control objects, the input
// provider and the rider FX components. The ground motion receiver is the
// owner itself (offset 0). cPlayer (human) and cComputer (computer) extend
// it past 0xDEC; the computer extension at 0xDF0 is 0x150 bytes.
// Receiver and control offsets come from the cMotionOwner_* dispatch
// functions; the FX components and scalars from
// docs/notes/structs/rider-components.md ("Motion owner and rider FX
// container"). Each component array runs to the next known
// offset; the true extents are not known, so never take sizeof(cMotionOwner).

// mMotionMode values, in the order of the game's motion name table
// (D_00459D70).
#define MOTION_GROUND    0
#define MOTION_AIR       1
#define MOTION_WIPEOUT   2
#define MOTION_STATIC    3
#define MOTION_RAILSLIDE 4
#define MOTION_HANDPLANT 5

// mControlState values, in the order of the game's control name table
// (D_00459DC8).
#define CONTROL_CRUISE      0
#define CONTROL_BOARDPRESS  1
#define CONTROL_PREWIND     2
#define CONTROL_BUMP        3
#define CONTROL_NATURALAIR  4
#define CONTROL_SPIN        5
#define CONTROL_GATE        6
#define CONTROL_RAILSLIDE   7
#define CONTROL_WIPEOUT     8
#define CONTROL_RESET       9
#define CONTROL_FINISHLINE  10
#define CONTROL_HANDPLANT   11
#define CONTROL_UBERGRIND   12
#define CONTROL_VOID        13

struct cMotionOwner {
    char pad000[0x10];
    int mGroundFocusTick;             // 0x010 tick at which the ground gained focus
    int mTakeoffTick;                 // 0x014 -1 after a passive takeoff; stamped when ground motion ends
    char* mRider;                     // 0x018 owning cRider
    char pad01C[0x4];
    char mAirMotion[0x10];            // 0x020 MOTION_AIR receiver
    char mWipeoutMotion[0x70];        // 0x030 MOTION_WIPEOUT receiver; first word: 0 sliding, else airborne
    char mStaticMotion[0x10];         // 0x0A0 MOTION_STATIC receiver
    char mRailSlideMotion[0x60];      // 0x0B0 MOTION_RAILSLIDE receiver
    char mHandplantMotion[0xB0];      // 0x110 MOTION_HANDPLANT receiver
    char mCruiseControl[0x10];        // 0x1C0 CONTROL_CRUISE object
    char mBoardPressControl[0x20];    // 0x1D0 CONTROL_BOARDPRESS object
    char mPrewindControl[0x10];       // 0x1F0 CONTROL_PREWIND object
    char mBumpControl[0x10];          // 0x200 CONTROL_BUMP object
    char mNaturalAirControl[0x20];    // 0x210 CONTROL_NATURALAIR object (passive air)
    char mSpinControl[0x60];          // 0x230 CONTROL_SPIN object (air tricks)
    char mGateControl[0x20];          // 0x290 CONTROL_GATE object
    char mRailSlideControl[0x10];     // 0x2B0 CONTROL_RAILSLIDE object
    char mWipeoutControl[0x90];       // 0x2C0 CONTROL_WIPEOUT object
    char mResetControl[0x10];         // 0x350 CONTROL_RESET object
    char mFinishLineControl[0x10];    // 0x360 CONTROL_FINISHLINE object
    char mHandplantControl[0x20];     // 0x370 CONTROL_HANDPLANT object
    char mUberGrindControl[0x20];     // 0x390 CONTROL_UBERGRIND object; +0x4 held rail Uber 0..3
    char mWakeFx[0xC0];               // 0x3B0 wake rings
    char mBoardSparksFx[0xB0];        // 0x470 sparks, glints, grind chunks
    char mBoardTrackFx[0xF0];         // 0x520 board track
    char mBoostFx[0x3B0];             // 0x610 boost
    char mAuraFx[0x110];              // 0x9C0 power-up aura
    char mStreamersFx[0x20];          // 0xAD0 air streamers
    char mRivalIcon[0x10];            // 0xAF0 rival relationship icon
    char mRivalBeam[0x40];            // 0xB00 rival locator beam
    char mSnowFx[0x130];              // 0xB40 snow, body snow and breath
    char mFistSparkleFx[0xB0];        // 0xC70 attack fist sparkle
    char padD20[0x10];
    char mLights[0xB0];               // 0xD30 light list: ambient plus directional pairs
    int mMotionMode;                  // 0xDE0 MOTION_*
    int mControlState;                // 0xDE4 CONTROL_*
    void* mInput;                     // 0xDE8 input provider interface
};

#endif /* AI_MOTIONOWNER_H */
