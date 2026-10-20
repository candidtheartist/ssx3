#ifndef ANIMATION_MDFARCHIVE_H
#define ANIMATION_MDFARCHIVE_H

#include "common.h"

// Model-part archive (cMdfArchive): a 0x10-byte view over a loaded .mdf
// data block. cRider_addEquippedModelParts keeps one on the stack (four
// words) and cMdfArchive_close clears all four. cMdfArchive_bind points the
// tables at the block; only the block in mOwnedData is freed by close.
// Pads are unknown, not unused.

// Archive data header (start of the data block).
struct cMdfHeader {
    char pad0[0x4];
    short mNumParts;                  // 0x4 number of part headers
    short mPartsOffset;               // 0x6 offset of the part header table
    int mDataOffset;                  // 0x8 offset of the part data area
};

// Part header (0x60 bytes). cMdfArchive_getModelPartByIndex returns a copy
// of it followed by the part's data, so the offsets below that
// cAnimModel_addModelPartLOD reads are relative to header + 0x60.
struct cMdfPartHeader {
    char mName[0x10];                 // 0x00 part name (hasModelPart/getModelPart key)
    int mDataOffset;                  // 0x10 part data, relative to cMdfArchive::mData
    int mDataSize;                    // 0x14 bytes of part data copied after the header
    int mBoneNamesOffset;             // 0x18 bone name table (0x50-byte entries); model part +0x38
    int mOffset1C;                    // 0x1C offset into the part data; model part +0x3C
    char pad20[0xC];
    int mOffset2C;                    // 0x2C offset into the part data; model part +0x40
    char pad30[0x1A];
    short mNumBones;                  // 0x4A entries in the bone name table; model part +0x44
    char pad4C[0x2];
    short mCount4E;                   // 0x4E copied to model part +0x48
    short mCount50;                   // 0x50 copied to model part +0x4C
    signed char mPartId;              // 0x52 model part id (cAnimModel part match key)
    char pad53[0xD];
};

typedef char cMdfPartHeader_size_check[sizeof(cMdfPartHeader) == 0x60 ? 1 : -1];

struct cMdfArchive {
    char* mOwnedData;                 // 0x0 block freed by close (load/adoptData); 0 for attachData
    cMdfHeader* mHeader;              // 0x4 start of the data block
    cMdfPartHeader* mParts;           // 0x8 data + mHeader->mPartsOffset
    char* mData;                      // 0xC data + mHeader->mDataOffset
};

typedef char cMdfArchive_size_check[sizeof(cMdfArchive) == 0x10 ? 1 : -1];

#endif /* ANIMATION_MDFARCHIVE_H */
