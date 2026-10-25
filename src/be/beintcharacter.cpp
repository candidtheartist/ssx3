#include "common.h"

signed char cBELibrary_getCharacterID(int index);

struct sCharWeightEntry {
    char pad_0x00[0x40];
    int mWeight;
    char pad_0x44[0x88 - 0x40 - 4];
};
extern sCharWeightEntry D_00530970[];

//100%
int cBECharacterInterface_getWeight(void* self, int riderIndex)
{
    return D_00530970[cBELibrary_getCharacterID(riderIndex)].mWeight;
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
// sCharWeightEntry (declared above in the unit) has no field at 0x44 yet;
// this view of the same table binds to D_00530970.
struct sCharWeightEntryView {
    char pad_0x00[0x40];
    int mWeight;        // 0x40
    int field_0x44;     // 0x44
    char pad_0x48[0x88 - 0x48];
};
extern sCharWeightEntryView D_00530970_view[] __asm__("D_00530970");

extern "C" bool func_0014EF70(void* self, int riderIndex)
{
    int charID = cBELibrary_getCharacterID(riderIndex);
    return D_00530970_view[charID].field_0x44 != 0;
}

//100%
extern "C" int func_0014A0B0(int rider);
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
int cBENewPlayerInterface_isMissionMan(int rider);
extern signed char D_00535C11[];
struct sCharStatEntry_EFA8 {
    char pad_0x00[0x48];
    int stat;           // 0x48
    char pad_0x4C[0x88 - 0x4C];
};
extern sCharStatEntry_EFA8 D_00530970_EFA8[] __asm__("D_00530970");

extern "C" float cBECharacterInterface_GetRiderSizeScale(void* self, int rider)
{
    int charID = cBELibrary_getCharacterID(rider);
    int board = func_0014A0B0(rider);
    cBE_getInterface_Fv(cBE_getBE(), 0);
    if (board != 0 && (D_00535C11[0] != 0 || rider != 0)) {
        switch (board) {
        case 10:
            return 0.98f;
        case 11:
        case 14:
            return 0.85f;
        case 29:
            return 2.0f;
        case 28:
            return 0.7f;
        case 26:
            return 1.5f;
        case 20:
            return 1.2f;
        case 22:
        case 23:
            return 1.3f;
        case 15:
        case 17:
            return 0.75f;
        case 13:
        case 18:
        case 19:
        case 21:
            return 1.0f;
        default:
            return 0.9f;
        }
    }
    if (cBENewPlayerInterface_isMissionMan(rider))
        return 0.8f;
    return D_00530970_EFA8[charID].stat * 0.01f;
}


extern "C" void func_0014F100()
{
}

// One row of the character table (DATA/BE/CHARDB.DBL): 0x88 bytes per rider
struct sBECharacterData {
    char longName[0x20];
    char firstName[0x10];   // 0x20
    char nickname[0x10];    // 0x30
    int weight;             // 0x40
    int goofy;              // 0x44
    int modelSize;          // 0x48: model scale in percent
    char bloodType[0x10];   // 0x4C
    int female;             // 0x5C
    int age;                // 0x60
    char height[0x10];      // 0x64
    char nationality[0x10]; // 0x74
    int unk84;              // 0x84
};

extern sBECharacterData gCharacterData[10] __asm__("D_00530970");

extern "C" char* func_0014F108(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].bloodType;
}

extern "C" bool func_0014F138(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].female != 0;
}

extern "C" int func_0014F170(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].age;
}

extern "C" char* func_0014F1B0(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].height;
}

extern "C" char* func_0014F1E0(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].nationality;
}

extern "C" int func_0014F210(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].unk84;
}
