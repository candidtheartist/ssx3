#include "common.h"
#include "animation/animsequence.h"
#include "animation/mdfarchive.h"

//100%
void cAnimSequence_fadeWeight(cAnimSequence* self, float target, float time)
{
    self->mTargetWeight = target;
    self->mFadeTime = time;
    self->mRemoveWhenFaded = 0;
}

//100%
extern "C" void cAnimSequence_fadeOut(void* self_, float time)
{
    cAnimSequence* self = (cAnimSequence*)self_;
    if (self->mTargetWeight != 0.0f || self->mFadeTime == 0.0f || time < self->mFadeTime)
    {
        self->mFadeTime = time;
    }
    self->mTargetWeight = 0.0f;
    self->mRemoveWhenFaded = 1;
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0048A5B0[];

extern "C" void cAnimSequence_addTrigger(void* self, int key, float weight)
{
    cAnimSequence* seq = (cAnimSequence*)self;
    cAnimSequenceTrigger* n = (cAnimSequenceTrigger*)cMemMan_alloc(0x10, D_0048A5B0, 0x20000000, 0);
    cAnimSequenceTrigger* old = seq->mTriggers;
    seq->mTriggers = n;
    n->mKey = key;
    n->mPoint = weight;
    n->mNext = old;
    n->mIsEndTrigger = 0;
}

//100%
extern "C" void cAnimSequence_addEndTrigger(void* self, int key)
{
    cAnimSequence* seq = (cAnimSequence*)self;
    cAnimSequenceTrigger* n = (cAnimSequenceTrigger*)cMemMan_alloc(0x10, D_0048A5B0, 0x20000000, 0);
    cAnimSequenceTrigger* old = seq->mTriggers;
    seq->mTriggers = n;
    n->mKey = key;
    n->mIsEndTrigger = 1;
    n->mNext = old;
    n->mPoint = 0;
}

//100%
void operator_delete(int* ptr);

// Removes the first point trigger matching key and value.
extern "C" void cAnimSequence_removeTrigger(void* self, int key, float weight)
{
    cAnimSequenceTrigger** link = &((cAnimSequence*)self)->mTriggers;
    for (; *link != 0; link = &(*link)->mNext)
    {
        cAnimSequenceTrigger* n = *link;
        if (n->mKey == key && n->mPoint == weight && n->mIsEndTrigger == 0)
        {
            *link = n->mNext;
            operator_delete((int*)n);
            return;
        }
    }
}

//100%
extern "C" void cAnimSequence_removeEndTrigger(void* self, int key)
{
    cAnimSequenceTrigger** pp;
    for (pp = &((cAnimSequence*)self)->mTriggers; *pp != 0; pp = &(*pp)->mNext)
    {
        if ((*pp)->mKey == key)
        {
            cAnimSequenceTrigger* n = *pp;
            if (n->mIsEndTrigger != 0)
            {
                *pp = n->mNext;
                operator_delete((int*)n);
                return;
            }
        }
    }
}

//100%
extern "C" void cAnimSequence_deleteTriggers(char* self)
{
    cAnimSequence* seq = (cAnimSequence*)self;
    while (seq->mTriggers != 0)
    {
        cAnimSequenceTrigger* node = seq->mTriggers;
        seq->mTriggers = node->mNext;
        operator_delete((int*)node);
    }
}

//100%
extern void** D_004A3DF8;

extern "C" void cAnimSequence_setSlotClip(void* self, int i, int anim)
{
    cAnimSequence* s = (cAnimSequence*)self;
    (s->mSlots + i)->mClip = anim;
    char* clip = *(char**)((char*)D_004A3DF8 + ((anim & 0xFF) << 2));
    char* q = (char*)(((unsigned)anim >> 8) * 0x14 + *(int*)(clip + 0x8));
    s->mSlots[i].mLength = (*(unsigned short*)(q + 0xC) - 1) * 0.03333333507180214f;
    if (s->mSlots[i].mEnabled == 0)
    {
        s->mSlots[i].mTime = 0;
        s->mSlots[i].mRate = 1.0f;
        s->mSlots[i].mWeight = 1.0f;
        s->mSlots[i].mEnabled = 1;
        s->mSlots[i].mLoop = 0;
        s->mSeekPending = 1;
    }
}

//100%
extern "C" void cAnimSequence_setSlotTime(void* self, int a1, float val)
{
    cAnimSequence* seq = (cAnimSequence*)self;
    seq->mSlots[a1].mTime = val;
    seq->mSeekPending = 1;
}

extern "C" void cAnimSequence_setSlotRate(char* self, int i, float value)
{
    ((cAnimSequence*)self)->mSlots[i].mRate = value;
}

//100%
extern "C" void cAnimSequence_setSlotWeight(void* self, int a1, float val)
{
    ((cAnimSequence*)self)->mSlots[a1].mWeight = val;
}

//100%
extern "C" void cAnimSequence_setSlotLoop(void* self, int a1, int val)
{
    ((cAnimSequence*)self)->mSlots[a1].mLoop = val;
}

extern "C" void cAnimSequence_disableSlot(char* self, int i)
{
    ((cAnimSequence*)self)->mSlots[i].mEnabled = 0;
}

//100%
// Slot weight: sequence weight x slot weight, ramped in over mFadeInTime and
// out over the last mFadeOutTime seconds of the slot.
// PORT: g++ <? (min) operator, removed in GCC 4.3.
extern "C" float cAnimSequence_getSlotWeight(cAnimSequence* self, int i)
{
    float time = self->mSlots[i].mTime;
    float w = self->mWeight * self->mSlots[i].mWeight;
    float end = self->mSlots[i].mLength;
    if (time < self->mFadeInTime)
    {
        w = (time / self->mFadeInTime) <? w;
    }
    float rem = end - time;
    if (rem < self->mFadeOutTime)
    {
        w = (rem / self->mFadeOutTime) <? w;
    }
    return w;
}

//100%
struct sVEntry_313DD0 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

static inline void Ser_313DD0(char* s, void* p, int n)
{
    sVEntry_313DD0* e = &(*(sVEntry_313DD0**)s)[1];
    e->fn(s + e->delta, p, n);
}

class cAsStream;

extern "C" void cAnimSequence_save(void* node, cAsStream* stream)
{
    cAnimSequence* self = (cAnimSequence*)node;
    char* s = (char*)stream;
    Ser_313DD0(s, &self->mSemantic, 0x4);
    Ser_313DD0(s, self->mSlots, 0x54);
    Ser_313DD0(s, &self->mRootPos, 0x20);
    Ser_313DD0(s, &self->mMirror, 0x4);
    Ser_313DD0(s, &self->mPriority, 0x4);
    Ser_313DD0(s, &self->mBoneMask, 0x8);
    Ser_313DD0(s, &self->mRate, 0x4);
    Ser_313DD0(s, &self->mWeight, 0x4);
    Ser_313DD0(s, &self->mTargetWeight, 0x4);
    Ser_313DD0(s, &self->mFadeTime, 0x4);
    Ser_313DD0(s, &self->mRemoveWhenFaded, 0x4);
    Ser_313DD0(s, &self->mFadeOutTime, 0x4);
    Ser_313DD0(s, &self->mFadeInTime, 0x4);
    Ser_313DD0(s, &self->mLatchedFlags, 0x10);
    Ser_313DD0(s, &self->mCompleted, 0x4);
    Ser_313DD0(s, &self->mSeekPending, 0x4);
    int n = 0;
    cAnimSequenceTrigger* p = self->mTriggers;
    if (p != 0) {
        int c = 0;
        do {
            p = p->mNext;
            c++;
        } while (p != 0);
        n = c;
    }
    Ser_313DD0(s, &n, 4);
    for (p = self->mTriggers; p; p = p->mNext) {
        Ser_313DD0(s, p, 0x10);
    }
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0048A5B0[];

struct sVEntry_314050 {
    short delta;
    short index;
    void (*fn)(void*, void*, int);
};

static inline void Read_314050(char* s, void* p, int n)
{
    sVEntry_314050* e = &(*(sVEntry_314050**)s)[2];
    e->fn(s + e->delta, p, n);
}

extern "C" void cAnimSequence_load(void* node, void* stream)
{
    cAnimSequence* self = (cAnimSequence*)node;
    char* s = (char*)stream;
    Read_314050(s, &self->mSemantic, 0x4);
    Read_314050(s, self->mSlots, 0x54);
    Read_314050(s, &self->mRootPos, 0x20);
    Read_314050(s, &self->mMirror, 0x4);
    Read_314050(s, &self->mPriority, 0x4);
    Read_314050(s, &self->mBoneMask, 0x8);
    Read_314050(s, &self->mRate, 0x4);
    Read_314050(s, &self->mWeight, 0x4);
    Read_314050(s, &self->mTargetWeight, 0x4);
    Read_314050(s, &self->mFadeTime, 0x4);
    Read_314050(s, &self->mRemoveWhenFaded, 0x4);
    Read_314050(s, &self->mFadeOutTime, 0x4);
    Read_314050(s, &self->mFadeInTime, 0x4);
    Read_314050(s, &self->mLatchedFlags, 0x10);
    Read_314050(s, &self->mCompleted, 0x4);
    Read_314050(s, &self->mSeekPending, 0x4);
    int n;
    Read_314050(s, &n, 4);
    cAnimSequenceTrigger* tail = self->mTriggers;
    for (int i = 0; i < n; i++) {
        cAnimSequenceTrigger* p = (cAnimSequenceTrigger*)cMemMan_alloc(0x10, D_0048A5B0, 0x20000000, 0);
        Read_314050(s, p, 0x10);
        if (self->mTriggers != 0) {
            tail->mNext = p;
        } else {
            self->mTriggers = p;
        }
        tail = p;
    }
}

//100%
void cAnimSequencer_cAnimSequencer(void* self)
{
    cAnimSequencer* sq = (cAnimSequencer*)self;
    sq->mCount = 0;
    sq->mFirstSequence = 0;
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_0048A5C0[];

extern "C" void* cAnimSequence_cAnimSequence(void* mem, int arg);

extern "C" void* cAnimSequencer_newSequence(void* seq, int arg)
{
    cAnimSequencer* self = (cAnimSequencer*)seq;
    cAnimSequence* node = (cAnimSequence*)cAnimSequence_cAnimSequence(cMemMan_alloc(sizeof(cAnimSequence), D_0048A5C0, 0x20000000, 0), arg);
    node->mNext = self->mFirstSequence;
    self->mFirstSequence = node;
    self->mCount++;
    return node;
}

//100%
extern "C" void cAnimSequencer_appendSequence(cAnimSequencer* self, cAnimSequence* node)
{
    if (self->mFirstSequence != 0)
    {
        cAnimSequence* p = self->mFirstSequence;
        while (p->mNext != 0)
        {
            p = p->mNext;
        }
        p->mNext = node;
    }
    else
    {
        self->mFirstSequence = node;
    }
    node->mNext = 0;
    self->mCount++;
}

//100%
extern "C" void cAnimSequencer_unlinkSequence(cAnimSequencer* self, cAnimSequence* node)
{
    if (self->mFirstSequence == node) {
        self->mFirstSequence = node->mNext;
    } else {
        cAnimSequence* nxt = node->mNext;
        cAnimSequence* cur;
        for (cur = self->mFirstSequence; cur != 0; cur = cur->mNext) {
            if (cur->mNext == node)
                break;
        }
        cur->mNext = nxt;
    }
    node->mNext = 0;
    self->mCount--;
}

//100%
// One sampling descriptor per enabled slot, read by the model sampler.
struct sSeqState_314418
{
    int id;             // 0x00 slot clip
    float time;         // 0x04 slot time
    int d;              // 0x08 sequence priority
    float weight;       // 0x0C slot weight (cAnimSequence_getSlotWeight)
    long e;             // 0x10 sequence bone mask
    char pad18[0x8];
    sAnimVec4 a;        // 0x20 sequence root translation
    sAnimVec4 b;        // 0x30 sequence root quaternion
    int c;              // 0x40 sequence mirror flag
    char pad44[0xC];
};

// PORT: `long` field is 64-bit (ld/sd).
extern "C" int cAnimSequencer_getSampleStates(void* self, sSeqState_314418* out)
{
    int count = 0;
    cAnimSequence* n = ((cAnimSequencer*)self)->mFirstSequence;
    while (n != 0)
    {
        for (int j = 0; j < 3; j++)
        {
            if (n->mSlots[j].mEnabled != 0)
            {
                sSeqState_314418* o = &out[count];
                o->id = n->mSlots[j].mClip;
                o->time = n->mSlots[j].mTime;
                o->a = n->mRootPos;
                o->b = n->mRootRot;
                o->c = n->mMirror;
                o->d = n->mPriority;
                o->weight = cAnimSequence_getSlotWeight(n, j);
                o->e = n->mBoneMask;
                count++;
            }
        }
        n = n->mNext;
    }
    return count;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* cAnimSequencer_newSequence(void* seq, int arg);
extern "C" void cAnimSequence_setSlotClip(void* self, int i, int anim);

extern "C" void* cAnimSequencer_addSequence(void* self, int arg, int anim, float val)
{
    void* node = cAnimSequencer_newSequence(self, arg);
    cAnimSequence_setSlotClip(node, 0, anim);
    cAnimSequence_setSlotTime(node, 0, val);
    cAnimSequence_setSlotLoop(node, 0, 0);
    return node;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* cAnimSequencer_addLoopingSequence(void* self, int arg, int anim, float val)
{
    void* node = cAnimSequencer_newSequence(self, arg);
    cAnimSequence_setSlotClip(node, 0, anim);
    cAnimSequence_setSlotTime(node, 0, val);
    cAnimSequence_setSlotLoop(node, 0, 1);
    return node;
}

//100%
extern "C" void cAnimSequencer_removeSequence(cAnimSequencer* self, cAnimSequence* node)
{
    cAnimSequence** pp;
    for (pp = &self->mFirstSequence; *pp != 0; pp = &(*pp)->mNext)
    {
        cAnimSequence* n = *pp;
        if (n == node)
        {
            *pp = n->mNext;
            if (n != 0)
            {
                cAnimSequence_deleteTriggers((char*)n);
                operator_delete((int*)n);
            }
            self->mCount--;
            return;
        }
    }
}

//100%
extern "C" void cAnimSequencer_removeAll(cAnimSequencer* self)
{
    while (self->mFirstSequence != 0)
    {
        cAnimSequence* n = self->mFirstSequence;
        self->mFirstSequence = n->mNext;
        if (n != 0)
        {
            cAnimSequence_deleteTriggers((char*)n);
            operator_delete((int*)n);
        }
        self->mCount--;
    }
}

//100%
extern "C" void cAnimSequencer_fadeOutAll(void* self, float v)
{
    for (cAnimSequence* node = ((cAnimSequencer*)self)->mFirstSequence; node != 0; node = node->mNext)
    {
        cAnimSequence_fadeOut(node, v);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cAnimSequencer_removeEndTriggers(void* self, int v)
{
    for (cAnimSequence* node = ((cAnimSequencer*)self)->mFirstSequence; node != 0; node = node->mNext)
    {
        cAnimSequence_removeEndTrigger(node, v);
    }
}

//100%
cAnimSequence* cAnimSequencer_getSequence(cAnimSequencer* self, int index)
{
    cAnimSequence* cur = self->mFirstSequence;
    while (cur != 0 && index-- > 0) {
        cur = cur->mNext;
    }
    return cur;
}

// Whether a sequence with the given semantic is in the list
extern "C" int cAnimSequencer_hasAnim(char* self, int id)
{
    cAnimSequence* p;
    for (p = ((cAnimSequencer*)self)->mFirstSequence; p; p = p->mNext) {
        if (p->mSemantic == id)
            return 1;
    }
    return 0;
}

// Index of the sequence with the given semantic, or -1
extern "C" int cAnimSequencer_findAnim(char* self, int id)
{
    cAnimSequence* p;
    int i = 0;
    for (p = ((cAnimSequencer*)self)->mFirstSequence; p; p = p->mNext) {
        if (p->mSemantic == id)
            return i;
        i++;
    }
    return -1;
}

//100% - objdiff report; single-function view differs only in a relocation name
class cAsStream {
public:
    virtual void serialize(void* data, int size);
};

extern "C" void cAnimSequencer_save(cAnimSequencer* self, cAsStream* s)
{
    s->serialize(self, 4);
    cAnimSequence* n = self->mFirstSequence;
    for (int i = 0; i < self->mCount; i++)
    {
        cAnimSequence_save(n, s);
        n = n->mNext;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
// PORT: cMemMan_alloc is the game's tagged operator new(size, tag, flags, d); bound by asm label.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" void func_003E6448(void* dst, int value, int size);
extern "C" void cAnimSequence_load(void* node, void* stream);
extern const char D_0048A5C0[];

struct sStreamVE_314880 { short delta; short index; void (*fn)(void*, void*, int); };

struct sSeqTrack_314880
{
    char pad[0x1C];
    sSeqTrack_314880() {}
};

struct sSeqNode_314880
{
    sSeqTrack_314880 tracks[3];
    char pad54[0xD0 - 0x54];
    sSeqNode_314880() {}
};

INCLUDE_ASM("animation/animsequencer", cAnimSequencer_load);
extern "C" void cAnimSequencer_load(void* self, void* stream);

//100%
void* cMdfArchive_cMdfArchive(void* self)
{
    cMdfArchive* arc = (cMdfArchive*)self;
    arc->mOwnedData = 0;
    return self;
}

//100%
void operator_delete(int* ptr);
extern "C" void cMdfArchive_close(cMdfArchive* self);

extern "C" void cMdfArchive__cMdfArchive(cMdfArchive* self, int flags)
{
    cMdfArchive_close(self);
    if (flags & 1)
    {
        operator_delete((int*)self);
    }
}

//100%
void cMemMan_free(void* ptr);

extern "C" void cMdfArchive_close(cMdfArchive* self)
{
    if (self->mOwnedData != 0)
    {
        cMemMan_free(self->mOwnedData);
    }
    self->mOwnedData = 0;
    self->mHeader = 0;
    self->mParts = 0;
    self->mData = 0;
}

extern "C" void* cMdfArchive_bind(void*);

//100%
// PORT: asm label (same binding the unit uses for cMdfArchive_bind's two-argument body).
void cMdfArchive_bind_impl(void* self, char* data) __asm__("cMdfArchive_bind");

void cMdfArchive_adoptData(void* self, int a1)
{
    cMdfArchive* arc = (cMdfArchive*)self;
    arc->mOwnedData = (char*)a1;
    cMdfArchive_bind_impl(self, (char*)a1);
}

//100%
void* cMdfArchive_attachData(void* self)
{
    cMdfArchive* arc = (cMdfArchive*)self;
    arc->mOwnedData = 0;
    return cMdfArchive_bind(self);
}

//100%
// Loads the archive named name with func_003E22F0, stores it and points self at its tables.
extern "C" char* func_003E22F0(const char* name, int flags);

extern "C" void cMdfArchive_load(cMdfArchive* self, const char* name, int flags)
{
    char* data = func_003E22F0(name, flags);
    self->mOwnedData = data;
    cMdfArchive_bind_impl(self, data);
}

//100%
// The original had the same mismatch: callers (cMdfArchive_adoptData/cMdfArchive_attachData, the
// latter already 100%) see the one-argument declaration above and leave $5 as-is,
// while the definition takes two. The asm label binds this two-argument body to
// the symbol without changing the callers' prototype.
// PORT: asm labels are GCC/Clang-only; the port should give callers the real signature.
void cMdfArchive_bind_impl(void* self, char* data) __asm__("cMdfArchive_bind");
void cMdfArchive_bind_impl(void* self, char* data)
{
    cMdfArchive* arc = (cMdfArchive*)self;
    arc->mHeader = (cMdfHeader*)data;
    arc->mParts = (cMdfPartHeader*)(data + ((cMdfHeader*)data)->mPartsOffset);
    arc->mData = data + ((cMdfHeader*)data)->mDataOffset;
}

extern "C" int cMdfArchive_getNumModelParts(cMdfArchive* self)
{
    cMdfHeader* p = self->mHeader;
    if (p)
        return p->mNumParts;
    return 0;
}

//100%
// Returns 1 when the archive has a part called name.
extern "C" int func_0041AA88(const char* a, const char* b);

extern "C" int cMdfArchive_hasModelPart(cMdfArchive* self, const char* name)
{
    for (int i = 0; i < self->mHeader->mNumParts; i++)
    {
        if (func_0041AA88(name, self->mParts[i].mName) == 0)
            return 1;
    }
    return 0;
}

//100%
// Returns the part called name, or null.
extern "C" cMdfPartHeader* cMdfArchive_findModelPartHeader(cMdfArchive* self, const char* name)
{
    for (int i = 0; i < self->mHeader->mNumParts; i++)
    {
        if (func_0041AA88(name, self->mParts[i].mName) == 0)
            return &self->mParts[i];
    }
    return 0;
}

//100%
extern "C" void* cMdfArchive_getModelPartByIndex(cMdfArchive* self, int index);

extern "C" void* cMdfArchive_getModelPart(cMdfArchive* self, const char* name)
{
    for (int i = 0; i < self->mHeader->mNumParts; i++)
    {
        if (func_0041AA88(name, self->mParts[i].mName) == 0)
            return cMdfArchive_getModelPartByIndex(self, i);
    }
    return 0;
}


extern "C" cMdfPartHeader* cMdfArchive_getModelPartHeader(cMdfArchive* self, int i)
{
    return &self->mParts[i];
}
