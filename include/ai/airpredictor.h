#ifndef AI_AIRPREDICTOR_H
#define AI_AIRPREDICTOR_H

#include "common.h"

// Air (landing) predictor, reached as cRider::mAirPredictor (rider+0x788).
// When a rider leaves the ground, cAirPredictor_startLaunchIntoAir seeds it
// from the rider's position and velocity; each tick cAirPredictor_update
// extends the predicted flight until it hits something, and integrates the
// actual flight in fixed 1/60 s steps. The object is 0xB0 bytes (the size
// saveState/loadState copy).

struct sAirVec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

// mStatus values.
#define AIRPRED_EXTENDING 0     // predicting, no hit yet
#define AIRPRED_LANDED    1     // landing found; mHit* are valid
#define AIRPRED_RESTARTED 2     // flight ran past 60 s; predicting again
#define AIRPRED_GAVE_UP   3     // second time past 60 s; mHit* set to defaults

struct cAirPredictor {
    sAirVec4 mHitPos;           // 0x00 predicted landing position (not touched by reset)
    sAirVec4 mHitHeading;       // 0x10 predicted landing heading
    sAirVec4 mHitNormal;        // 0x20 predicted landing normal (world up when given up)
    int mHitSurface;            // 0x30 word +0x150 of the hit object, -1 none
    float mHitParam[2];         // 0x34 two floats from the hit query
    char pad3C[0x4];
    sAirVec4 mApexPos;          // 0x40 written with mApexTime
    sAirVec4 mPredPos;          // 0x50 predicted-state position
    sAirVec4 mPredVel;          // 0x60 predicted-state velocity
    sAirVec4 mCurPos;           // 0x70 integrated actual position (fixed-step cache)
    sAirVec4 mCurVel;           // 0x80 integrated actual velocity
    int mHitType;               // 0x90 kind of hit; 0xD when given up, -1 after reset
    short mHitObjectId;         // 0x94 halfword +0xA of the hit object, -1 none
    char pad96[0x2];
    float mPredTime;            // 0x98 time of the predicted state
    float mApexTime;            // 0x9C time of the apex
    float mElapsed;             // 0xA0 elapsed air time
    float mStepTime;            // 0xA4 air time already covered by the fixed-step cache
    float mSpeedCap;            // 0xA8 speed cap for integration (3333.33 cm/s)
    int mStatus;                // 0xAC AIRPRED_*
};

typedef char cAirPredictor_size_check[sizeof(cAirPredictor) == 0xB0 ? 1 : -1];

#endif /* AI_AIRPREDICTOR_H */
