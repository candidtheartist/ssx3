#include "common.h"

signed char cBELibrary_getCharacterID(int index);

struct sCharWeightEntry {
    char pad_0x00[0x40];
    int mWeight;
    char pad_0x44[0x88 - 0x40 - 4];
};
extern sCharWeightEntry D_00530970[];

//100%
INCLUDE_ASM("be/beintcharacter", cBECharacterInterface_getWeight__FPvi);
#ifdef SKIP_ASM
int cBECharacterInterface_getWeight(void* self, int riderIndex)
{
    return D_00530970[cBELibrary_getCharacterID(riderIndex)].mWeight;
}
#endif

//100%
INCLUDE_ASM("be/beintcharacter", func_0014EF70);
#ifdef SKIP_ASM
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
#endif

INCLUDE_ASM("be/beintcharacter", func_0014EFA8);

//100%
INCLUDE_ASM("be/beintcharacter", func_0014F100);
#ifdef SKIP_ASM
extern "C" void func_0014F100()
{
}
#endif

//100%
INCLUDE_ASM("be/beintcharacter", func_0014F108);
#ifdef SKIP_ASM
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
#endif

//100%
INCLUDE_ASM("be/beintcharacter", func_0014F138);
#ifdef SKIP_ASM
extern "C" bool func_0014F138(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].female != 0;
}
#endif

//100%
INCLUDE_ASM("be/beintcharacter", func_0014F170);
#ifdef SKIP_ASM
extern "C" int func_0014F170(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].age;
}
#endif

//100%
INCLUDE_ASM("be/beintcharacter", func_0014F1B0);
#ifdef SKIP_ASM
extern "C" char* func_0014F1B0(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].height;
}
#endif

//100%
INCLUDE_ASM("be/beintcharacter", func_0014F1E0);
#ifdef SKIP_ASM
extern "C" char* func_0014F1E0(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].nationality;
}
#endif

//100%
INCLUDE_ASM("be/beintcharacter", func_0014F210);
#ifdef SKIP_ASM
extern "C" int func_0014F210(void* self, int riderIndex)
{
    return gCharacterData[cBELibrary_getCharacterID(riderIndex)].unk84;
}
#endif
