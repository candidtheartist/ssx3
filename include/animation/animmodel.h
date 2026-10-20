#ifndef ANIMATION_ANIMMODEL_H
#define ANIMATION_ANIMMODEL_H

#include "common.h"

// Animated, skinned model (cAnimModel). The rider's model is the one at
// cRider::mGeometry (rider+0x780): cRider_initStep allocates 0x160 bytes
// tagged "RiderModel" and compiles it from its model parts. Array names
// follow the allocation tags in cAnimModel_compile. Pads are unknown, not
// unused.

struct sAnimVec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct cAnimModel {
    int mPartCapacity;                // 0x000 parts allocated ("ModelRefs")
    int mNumVariants;                 // 0x004 variants per part ("ModelVariant")
    int mNumParts;                    // 0x008
    char* mParts;                     // 0x00C 0x58-byte part records
    int mNumBones;                    // 0x010 pose save/load size is mNumBones * 32
    int mMaxPartId;                   // 0x014 largest part id
    char pad018[0x4];
    int* mPartIndexById;              // 0x01C "PartModelOffset": part index per id, -1 none
    int* mBoneChannelOffset;          // 0x020 "BoneChannelOffset"
    char* mBoneOffsets;               // 0x024 "BoneOffset": local translations, float4 per bone
    char* mBoneQuats;                 // 0x028 "BoneQuaternion": local rotations
    char* mPoses;                     // 0x02C "SkelPoses": world transforms, 32 bytes per bone
    char* mBoneMatrices;              // 0x030 "SkelMatrices": world matrices, 64 bytes per bone
    char* mScaledBoneMatrices;        // 0x034 second "SkelMatrices": scaled by mScale
    char* mInvDefaultMats;            // 0x038 "InvDefaultMats": inverse bind matrices
    char* mMorphChannels;             // 0x03C "MorphChannels"
    char pad040[0x20];
    int mNumTexturePacks;             // 0x060
    void* mTexturePacks[50];          // 0x064 appended by 0x0030DB70; 50 fit before 0x12C
    int mNumTextureRefs;              // 0x12C
    char* mTextureRefs;               // 0x130 "TextureRefs": 12-byte entries
    char pad134[0xC];
    sAnimVec4 mScale;                 // 0x140 body scale (x, y, z, 1)
    ulong mActiveBoneMask;            // 0x150 64-bit on ee-gcc; bones of the visible parts
    ulong mReducedBoneMask;           // 0x158 used when the sampler asks for the reduced set
};

typedef char cAnimModel_size_check[sizeof(cAnimModel) == 0x160 ? 1 : -1];

#endif /* ANIMATION_ANIMMODEL_H */
