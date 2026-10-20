#include "common.h"

//100%
extern "C" int cDirtysock_tag_TagFieldSetString(char* buf, int size, const char* key, const char* value);

// PORT: the unit declares value as int (callers pass a string pointer in it).
extern "C" int cDirtysock_tag_TagFieldSetUnk(char* buf, int size, const char* key, int value)
{
    char temp[256];
    int r;
    if (*(const char*)value == '\'') {
        temp[0] = '`';
        strcpy(temp + 1, (const char*)value);
        r = cDirtysock_tag_TagFieldSetString(buf, size, key, temp);
    } else {
        r = cDirtysock_tag_TagFieldSetString(buf, size, key, (const char*)value);
    }
    return r;
}

//100%
extern "C" char* strcpy(char* dst, const char* src);
extern "C" int cDirtysock_tag_TagFieldGetString(const char* tag, char* buf, int size);

// PORT: variable-length array (GNU extension in C++).
extern "C" void cDirtysock_tag_TagFieldGetUnk(const char* tag, char* dst, int size)
{
    char buf[size + 1];
    cDirtysock_tag_TagFieldGetString(tag, buf, size + 1);
    if (buf[0] == '`')
        strcpy(dst, buf + 1);
    else
        strcpy(dst, buf);
}

//100%
void LobbyMan_NullLobbyCallback(void* self)
{
}

extern "C" void* func_0041AA88(void*, void*);

//100%
void* LobbyMan_CompareUserNames(void* self, int a1, void* a2, void* a3)
{
    return func_0041AA88((char*)a2 + 0x1c, (char*)a3 + 0x1c);
}

//100%
void* LobbyMan_CompareRoomNames(void* self, int a1, void* a2, void* a3)
{
    return func_0041AA88((char*)a2 + 0x8, (char*)a3 + 0x8);
}

extern "C" int func_002593D8(void* a, void* b, int* entry)
{
    return ((entry[1] >> 21) ^ 1) & 1;
}

// Sort comparison: descending by the first word
extern "C" int func_002593F0(void* a, void* b, int* x, int* y)
{
    return *y - *x;
}

extern char D_004A2F30[];
extern "C" int cDirtysock_tag_TagFieldGetStructure(const char* tag, void* data, int len, const char* fmt);

// Sort comparison: descending by the first word of each entry's tag structure.
extern "C" int func_00259400(void* a, void* b, char* x, char* y)
{
    int sx[2];
    int sy[2];
    cDirtysock_tag_TagFieldGetStructure(x + 0x28, sx, 8, D_004A2F30);
    cDirtysock_tag_TagFieldGetStructure(y + 0x28, sy, 8, D_004A2F30);
    return sy[0] - sx[0];
}

// Sort comparison: ascending by the first word of each entry's tag structure.
extern "C" int func_00259468(void* a, void* b, char* x, char* y)
{
    int sx[2];
    int sy[2];
    cDirtysock_tag_TagFieldGetStructure(x + 0x28, sx, 8, D_004A2F30);
    cDirtysock_tag_TagFieldGetStructure(y + 0x28, sy, 8, D_004A2F30);
    return sx[0] - sy[0];
}

//100%
struct cBXString2;
cBXString2* cBXString_cBXString(cBXString2* self);
extern "C" void* cBXString_cBXString2(void* self, const char* s);
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void func_00260F10(void* self);
// The shared empty-string pointer is read as const so one load serves several string inits.
extern void* const D_004A3E90_94D0 __asm__("D_004A3E90");
extern char D_004807D8[];
extern char D_004804A8[];

struct sBXStr_94D0 {
    void* str;
};

struct sListNode_94D0 {
    sListNode_94D0* next;
    sListNode_94D0* prev;
    void* data;
};

struct sList_94D0 {
    int f0;
    sListNode_94D0* head;           // 0x4
    int f8;
    int fC;
    int f10;
    int f14;
};

extern "C" void* LobbyMan_ctor(void* self_)
{
    char* self = (char*)self_;
    // An unused 16-byte local is needed to reproduce the 0x40-byte frame.
    int unused[4];
    *(int*)(self + 0x0) = 0;
    *(int*)(self + 0x4) = 0;
    *(int*)(self + 0x8) = 0;
    *(int*)(self + 0xC) = 0;
    *(int*)(self + 0x10) = 0;
    *(int*)(self + 0x14) = 0;
    *(int*)(self + 0x18) = 0;
    *(int*)(self + 0x44) = 0;
    *(void**)(self + 0x48) = D_004A3E90_94D0;
    *(void**)(self + 0x4C) = D_004A3E90_94D0;
    *(int*)(self + 0x54) = 0;
    *(int*)(self + 0x58) = 0;
    *(int*)(self + 0x5C) = 0;
    *(int*)(self + 0x60) = 0;
    *(int*)(self + 0x64) = 0;
    *(int*)(self + 0x6C) = 0;
    sBXStr_94D0* p = (sBXStr_94D0*)(self + 0x70);
    for (int i = 3; i != -1; i--, p++) {
        p->str = D_004A3E90_94D0;
    }
    *(void**)(self + 0x80) = D_004A3E90_94D0;
    *(void**)(self + 0x84) = D_004A3E90_94D0;
    *(void**)(self + 0x88) = D_004A3E90_94D0;
    *(void**)(self + 0x8C) = D_004A3E90_94D0;
    *(void**)(self + 0x90) = D_004A3E90_94D0;
    *(void**)(self + 0x94) = D_004A3E90_94D0;
    *(void**)(self + 0x98) = D_004A3E90_94D0;
    *(void**)(self + 0x9C) = D_004A3E90_94D0;
    cBXString_cBXString2(self + 0xE8, D_004807D8);
    sList_94D0* lst = (sList_94D0*)(self + 0xEC);
    *(sListNode_94D0**)(self + 0xF0) = (sListNode_94D0*)cMemMan_alloc(0xC, D_004804A8, 0x20000000, 0);
    lst->head->next = *(sListNode_94D0**)(self + 0xF0);
    lst->head->prev = *(sListNode_94D0**)(self + 0xF0);
    *(int*)(self + 0xF4) = 0;
    *(int*)(self + 0xF8) = 0;
    *(int*)(self + 0xFC) = 0;
    *(int*)(self + 0x100) = 0;
    cBXString_cBXString((cBXString2*)(self + 0x260));
    cBXString_cBXString((cBXString2*)(self + 0x2B0));
    for (int i = 0x1C; i >= 0; i--)
        ((int*)(self + 0x1EC))[i] = 0;
    func_00260F10(self);
    return self;
}

//100%
extern "C" void cBXString__cBXString(void* self, int flags);
extern "C" void func_001DB718(void* self);
extern "C" void func_0025B800(void* self);
void operator_delete(int*);

static inline void dtorSub_9628(char* sub)
{
    if (sub + 0x14 != 0) {
        char* p = sub + 0x14 + 0x10;
        while (sub + 0x14 != p) {
            p -= 4;
            cBXString__cBXString(p, 0);
        }
    }
    cBXString__cBXString(sub + 0x10, 2);
    cBXString__cBXString(sub + 0xC, 2);
    cBXString__cBXString(sub + 0x8, 2);
    cBXString__cBXString(sub + 0x4, 2);
    cBXString__cBXString(sub, 2);
}

static inline void dtor4_9628(char* p)
{
    cBXString__cBXString(p + 0xC, 2);
    cBXString__cBXString(p + 0x8, 2);
    cBXString__cBXString(p + 0x4, 2);
    cBXString__cBXString(p, 2);
}

static inline void dtorList_9628(char* lst)
{
    func_001DB718(lst);
    operator_delete(*(int**)(lst + 4));
}

extern "C" void func_00259628(void* self_, int flags)
{
    char* self = (char*)self_;
    func_0025B800(self);
    dtorSub_9628(self + 0x2B0);
    dtorSub_9628(self + 0x260);
    dtorList_9628(self + 0xEC);
    cBXString__cBXString(self + 0xE8, 2);
    cBXString__cBXString(self + 0x9C, 2);
    cBXString__cBXString(self + 0x98, 2);
    dtor4_9628(self + 0x88);
    cBXString__cBXString(self + 0x84, 2);
    cBXString__cBXString(self + 0x80, 2);
    if (self + 0x70 != 0) {
        char* p = self + 0x70 + 0x10;
        while (self + 0x70 != p) {
            p -= 4;
            cBXString__cBXString(p, 0);
        }
    }
    cBXString__cBXString(self + 0x4C, 2);
    cBXString__cBXString(self + 0x48, 2);
    if (flags & 1)
        operator_delete((int*)self);
}

extern "C" void* func_003E8FD0(int);

//100%
void* LobbyMan_OnRecvDebug(void* self)
{
    return func_003E8FD0(*(int*)((char*)self + 0x54));
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern "C" int* func_002591D0();
extern "C" void func_00263BA8(void* p, int arg);

struct sMsgListNodeK2 {
    sMsgListNodeK2* next;
    sMsgListNodeK2* prev;
    void* data;
};

struct sMsgListIterK2 {
    sMsgListNodeK2* node;
    sMsgListIterK2(sMsgListNodeK2* x) : node(x) {}
    sMsgListIterK2(const sMsgListIterK2& x) : node(x.node) {}
};

static inline sMsgListIterK2 sMsgListK2_insert(sMsgListIterK2 pos, void* const& x)
{
    sMsgListNodeK2* tmp = (sMsgListNodeK2*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void LobbyMan_OnDisconnect(char* self, int* msg)
{
    if (msg[1] == 0x64697363) {
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0x115;
        *(void***)((char*)m + 0x4) = D_004812B0;
        void* mp = m;
        sMsgListK2_insert(*(sMsgListNodeK2**)(self + 0xF0), mp);
        *(int*)(self + 0x10) = 1;
        if (*func_002591D0() != 0)
            func_00263BA8(func_002591D0(), 2);
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];

struct sMsgListNodeK2b {
    sMsgListNodeK2b* next;
    sMsgListNodeK2b* prev;
    void* data;
};

struct sMsgListIterK2b {
    sMsgListNodeK2b* node;
    sMsgListIterK2b(sMsgListNodeK2b* x) : node(x) {}
    sMsgListIterK2b(const sMsgListIterK2b& x) : node(x.node) {}
};

static inline sMsgListIterK2b sMsgListK2b_insert(sMsgListIterK2b pos, void* const& x)
{
    sMsgListNodeK2b* tmp = (sMsgListNodeK2b*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void LobbyMan_OnRoomListChanged(char* self)
{
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = 0xE0;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListK2b_insert(*(sMsgListNodeK2b**)(self + 0xF0), mp);
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];

struct sMsgListNodeK2c {
    sMsgListNodeK2c* next;
    sMsgListNodeK2c* prev;
    void* data;
};

struct sMsgListIterK2c {
    sMsgListNodeK2c* node;
    sMsgListIterK2c(sMsgListNodeK2c* x) : node(x) {}
    sMsgListIterK2c(const sMsgListIterK2c& x) : node(x.node) {}
};

static inline sMsgListIterK2c sMsgListK2c_insert(sMsgListIterK2c pos, void* const& x)
{
    sMsgListNodeK2c* tmp = (sMsgListNodeK2c*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void LobbyMan_OnRankListChanged(char* self, int unused)
{
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = 0xE1;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListK2c_insert(*(sMsgListNodeK2c**)(self + 0xF0), mp);
}

INCLUDE_ASM("dirtysock/tagsunk", LobbyMan_OnMessage);

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" const char* cDirtysock_tag_TagFieldFind(const char* record, const char* name);
// PORT: TagFieldGetString really takes a 4th (default value) argument; the unit declares 3.
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");
extern "C" int cDirtysock_tag_TagFieldGetNumber(const char* tag, int defval);
extern "C" int cDirtysock_tag_TagFieldGetTime(const char* tag, int defval);
extern "C" int cDirtysock_tag_TagFieldGetAddr(const char* tag, int defval);
extern "C" void* cBXString_cBXString4(void* self, const char* str);
extern "C" int LobbyMan_LookupPeerAddr(void* self, const char* key, int def);
extern "C" int func_004165A8(void*, void*);
extern "C" int* func_002591D0();
extern "C" void func_00263BA8(void* p, int arg);
extern "C" void LobbyMan_SetupNetRace(void* p, int a, int b);
extern "C" unsigned int strlen(const char*);
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void cBENewRaceInterface_setGameMode(void* self, int mode);
extern "C" void cBENewRaceInterface_setGameEvent(void* self, int ev);
extern "C" void cBENewRaceInterface_setNumberAI(void* self, int n);
extern char D_004A2F40[];
extern char D_004A2F58[];
extern char D_004A2F60[];
extern char D_004A2F68[];
extern char D_004A2F70[];
extern char D_004A2F78[];
extern char D_004A2F80[];
extern char D_004A2F88[];
extern char D_004A2F90[];
extern char D_004A2F98[];
extern char D_004A2FA0[];
extern char D_004A2FA8[];
extern int D_00535C08[];
extern int D_004A11B8;
extern void* D_004A28A8;
extern int D_00534B34[];
extern char D_005308B8[];
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];

struct sMsgListNodeA1D0 {
    sMsgListNodeA1D0* next;
    sMsgListNodeA1D0* prev;
    void* data;
};

struct sMsgListIterA1D0 {
    sMsgListNodeA1D0* node;
    sMsgListIterA1D0(sMsgListNodeA1D0* x) : node(x) {}
    sMsgListIterA1D0(const sMsgListIterA1D0& x) : node(x.node) {}
};

static inline sMsgListIterA1D0 sMsgListA1D0_insert(sMsgListIterA1D0 pos, void* const& x)
{
    sMsgListNodeA1D0* tmp = (sMsgListNodeA1D0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_A1D0(char* self, void* msg)
{
    void* mp = msg;
    sMsgListA1D0_insert(*(sMsgListNodeA1D0**)(self + 0xF0), mp);
}

struct sAppA1D0 { char pad[0x78]; void* mBE; };

struct sVEntryA1D0 { short delta; short index; int (*fn)(void*); };

extern "C" void LobbyMan_OnGameStart(char* self, char* msg)
{
    char name[0x100];
    char b1[0x100];
    char b2[0x100];
    char b3[0x100];
    char b4[0x100];
    char b5[0x100];
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F58), name, 0x100, D_004A2F40);
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F60), b1, 0x100, D_004A2F40);
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F68), b2, 0x100, D_004A2F40);
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F70), b3, 0x100, D_004A2F40);
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F78), b4, 0x100, D_004A2F40);
    *(int*)(self + 0xA0) = cDirtysock_tag_TagFieldGetTime(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F80), 0);
    int ev = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F88), -1);
    int kind = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F90), -1);
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F88), b5, 0x100, D_004A2F40);
    *(int*)(self + 0xA8) = LobbyMan_LookupPeerAddr(self, b2, cDirtysock_tag_TagFieldGetAddr(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F98), 0));
    *(int*)(self + 0xAC) = LobbyMan_LookupPeerAddr(self, b3, cDirtysock_tag_TagFieldGetAddr(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2FA0), 0));
    cBXString_cBXString4(self + 0x88, name);
    cBXString_cBXString4(self + 0x90, b2);
    cBXString_cBXString4(self + 0x94, b3);
    cBXString_cBXString4(self + 0x9C, b4);
    int same = func_004165A8(b1, b2) == 0;
    *(int*)(self + 0xB4) = same;
    cBXString_cBXString4(self + 0x98, same ? b3 : b2);
    *(int*)(self + 0xB0) = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2FA8), 0);
    if (*(int*)self != 0x18 && *(int*)self != 0x14)
    {
        *(int*)self = 0x19;
        func_00263BA8(func_002591D0(), 0);
        return;
    }
    *(int*)self = 0x19;
    if (strlen(b5))
    {
        char* ri = (char*)cBE_getInterface_Fv(cBE_getBE(), 0);
        int mode = 0;
        switch (kind)
        {
        case 0:
            if (ev >= 14 && ev <= 16)
            {
                mode = 5;
                kind = 4;
            }
            else
                mode = 0;
            break;
        case 1:
            if (ev >= 14 && ev <= 16)
            {
                mode = 6;
                kind = 5;
            }
            else
                mode = 1;
            break;
        case 2:
            mode = 3;
            break;
        case 3:
            mode = 2;
            break;
        }
        cBENewRaceInterface_setGameMode(ri, mode);
        cBENewRaceInterface_setGameEvent(ri, kind);
        D_00535C08[0] = ev;
        D_004A11B8 = 1;
        cBE_getInterface_Fv(((sAppA1D0*)D_004A28A8)->mBE, 7);
        if (D_00534B34[0] != 0)
        {
            char* cfg = D_005308B8;
            *(int*)(cfg + 0x18) |= 0x1C0;
            cBENewRaceInterface_setNumberAI(ri, 0);
            sVEntryA1D0* vt = *(sVEntryA1D0**)(ri + 0xC);
            vt[1].fn(ri + vt[1].delta);
        }
    }
    int type = 0xEF;
    LobbyMan_SetupNetRace(func_002591D0(), *(int*)(self + 0xA4), 0);
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    post_A1D0(self, m);
}

//100%
extern "C" char* func_003E8A70(void* p, int tag);
extern "C" void* NetGameUtilCreate();
extern "C" void NetGameUtilAdvert(void* h, char* fmt, char* arg);
extern char D_004813A0[];

extern "C" void LobbyMan_CreatePeerTable(char* self)
{
    if (*(int*)(self + 0xC) == 0)
        return;
    if (*(void**)(self + 0xF4) != 0)
        return;
    if (func_003E8A70(*(void**)(self + 0x54), 0x70657273) == 0)
        return;
    if (*func_003E8A70(*(void**)(self + 0x54), 0x70657273) == 0)
        return;
    *(void**)(self + 0xF4) = NetGameUtilCreate();
    if (*(void**)(self + 0xF4) == 0)
        return;
    NetGameUtilAdvert(*(void**)(self + 0xF4), D_004813A0, func_003E8A70(*(void**)(self + 0x54), 0x70657273));
}

//100%
extern "C" void NetGameUtilDestroy(void*);

extern "C" void LobbyMan_DestroyPeerTable(void* self)
{
    void* p = *(void**)((char*)self + 0xF4);
    if (p != 0) {
        NetGameUtilDestroy(p);
        *(void**)((char*)self + 0xF4) = 0;
    }
}

//100%
extern char D_004813A0[];
extern "C" int NetGameUtilLocate(void* tags, const char* key, const char* def);

extern "C" int LobbyMan_LookupPeerAddr(void* self, const char* key, int def)
{
    void* tags = *(void**)((char*)self + 0xF4);
    if (tags != 0) {
        int r = NetGameUtilLocate(tags, D_004813A0, key);
        if (r != 0) {
            def = r;
        }
    }
    return def;
}

//100%
extern "C" void* func_003E85B0(void* mgr, int idx, void* cb, void* user);
extern "C" void func_003EE5A0(void* h, int a, int b, void* cb);
extern "C" void LobbyMan_OnUserListChanged_Thunk(void* self, void* a1, int a2);
extern "C" void LobbyMan_OnRoomListChanged_Thunk(void* self, void* a1, int a2);
extern "C" void LobbyMan_OnRankListChanged_Thunk(void* self, void* a1, int a2);

struct sDsSessK2 {
    char pad_0x00[0x54];
    void* mgr;                   // 0x54
    char pad_0x58[4];
    void* chan[3];               // 0x5C
    char pad_0x68[0x104 - 0x68];
    unsigned int slotA[29];      // 0x104
    unsigned int slotB[29];      // 0x178
};

extern "C" void LobbyMan_CreateLists(sDsSessK2* self)
{
    int i;
    self->chan[0] = func_003E85B0(self->mgr, 0, (void*)LobbyMan_OnUserListChanged_Thunk, self);
    func_003EE5A0(self->chan[0], 0, 0, (void*)LobbyMan_CompareUserNames);
    self->chan[1] = func_003E85B0(self->mgr, 1, (void*)LobbyMan_OnRoomListChanged_Thunk, self);
    func_003EE5A0(self->chan[1], 0, 0, (void*)LobbyMan_CompareRoomNames);
    self->chan[2] = func_003E85B0(self->mgr, 2, (void*)LobbyMan_OnRankListChanged_Thunk, self);
    for (i = 0; i < 29; i++) {
        self->slotA[i] = 0xFFFFFFFF;
        self->slotB[i] = 0xFFFFFFFF;
    }
}

//100%
extern "C" void func_003E8688(void* ctx, int kind, void* p);

extern "C" void LobbyMan_ReleaseSnapshotLists(void* self)
{
    int i;
    void** arr = (void**)((char*)self + 0x1EC);
    for (i = 0; i < 29; i++) {
        if (arr[i] != 0) {
            func_003E8688(*(void**)((char*)self + 0x54), 4, arr[i]);
            arr[i] = 0;
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
struct sTagsUnkCallbackObj {
    char pad[0xC];
    void (*fn)(sTagsUnkCallbackObj* self);
};

extern "C" void LobbyMan_DestroyLists(void* self)
{
    if (*(void**)((char*)self + 0x5C) != 0) {
        func_003E8688(*(void**)((char*)self + 0x54), 0, *(void**)((char*)self + 0x5C));
        *(void**)((char*)self + 0x5C) = 0;
    }
    if (*(void**)((char*)self + 0x60) != 0) {
        func_003E8688(*(void**)((char*)self + 0x54), 1, *(void**)((char*)self + 0x60));
        *(void**)((char*)self + 0x60) = 0;
    }
    if (*(void**)((char*)self + 0x64) != 0) {
        func_003E8688(*(void**)((char*)self + 0x54), 2, *(void**)((char*)self + 0x64));
        *(void**)((char*)self + 0x64) = 0;
    }
    LobbyMan_ReleaseSnapshotLists(self);
    sTagsUnkCallbackObj* obj = *(sTagsUnkCallbackObj**)((char*)self + 0x58);
    if (obj != 0) {
        obj->fn(obj);
        *(void**)((char*)self + 0x58) = 0;
    }
}

//100%
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void* LobbyApi_Create(const char* tag, int a, void* cb);
extern "C" void func_003E8248(void* mgr, int idx, void* cb, void* user);
extern "C" const char* LobbyMan_GetLanguage();
extern "C" void LobbyMan_OnRecvDebug_Thunk(void* self, void* a1, int a2);
extern "C" void LobbyMan_OnMessage_Thunk(void* self, void* a1, int a2);
extern "C" void LobbyMan_OnDisconnect_Thunk(void* self, void* a1, int a2);
extern "C" void LobbyMan_OnGameStart_Thunk(void* self, void* a1, int a2);
extern char D_004A2FC8[];
extern char D_004A2FD0[];
extern char D_004A2FD8[];
extern char D_004A2FE0[];
extern char D_004A2FE8[];
extern char D_004813A0[];
extern char D_004813B0[];
extern char D_00481390[];
extern char D_00480818[];
extern char D_00480828[];

extern "C" void func_0025A948(void* self_)
{
    char* self = (char*)self_;
    char buf[0x40];
    char tag[0x100];
    tag[0] = 0;
    cDirtysock_tag_TagFieldSetString(tag, 0x100, D_004A2FC8, D_004813A0);
    sprintf(buf, D_00480818, D_004A2FD0, D_004813B0, D_00480828);
    cDirtysock_tag_TagFieldSetString(tag, 0x100, D_004A2FD8, buf);
    const char* key = D_004A2FE0;
    cDirtysock_tag_TagFieldSetString(tag, 0x100, key, LobbyMan_GetLanguage());
    cDirtysock_tag_TagFieldSetString(tag, 0x100, D_004A2FE8, D_00481390);
    void* mgr = LobbyApi_Create(tag, 0, (void*)LobbyMan_NullLobbyCallback);
    *(void**)(self + 0x54) = mgr;
    func_003E8248(mgr, 0, (void*)LobbyMan_OnRecvDebug_Thunk, self);
    func_003E8248(*(void**)(self + 0x54), 1, (void*)LobbyMan_OnMessage_Thunk, self);
    func_003E8248(*(void**)(self + 0x54), 3, (void*)LobbyMan_OnDisconnect_Thunk, self);
    func_003E8248(*(void**)(self + 0x54), 4, (void*)LobbyMan_OnGameStart_Thunk, self);
    LobbyMan_CreateLists((sDsSessK2*)self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void LobbyMan_DestroyLists(void* self);
extern "C" void func_003E80C0(void* p);
extern "C" void LobbyApi_Destroy(void* p);

extern "C" void func_0025AA98(void* self)
{
    LobbyMan_DestroyLists(self);
    if (*(void**)((char*)self + 0x54) != 0) {
        func_003E80C0(*(void**)((char*)self + 0x54));
        LobbyApi_Destroy(*(void**)((char*)self + 0x54));
        *(void**)((char*)self + 0x54) = 0;
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A3010[];
extern "C" int cDirtysock_tag_TagFieldSetUnk(char* buf, int size, const char* key, int value);
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);

extern "C" void func_0025AAE0(void* self, int value)
{
    char buf[0x200];
    if (*(int*)self != 0) {
        buf[0] = 0;
        cDirtysock_tag_TagFieldSetUnk(buf, 0x200, D_004A3010, value);
        func_003E8B10(*(void**)((char*)self + 0x54), 0x6D657367, buf, 0, 0);
    }
}

//100%
extern char D_00480498[];
extern char D_004804A8[];
extern void* D_00481230[];
extern "C" void cBXString__cBXString(void* self, int flags);
extern "C" void* cBXString_cBXString1(void* self, void* other);
extern "C" void* cBXString_cBXString2(void* self, const char* s);

struct sMsgListNodeAB40 {
    sMsgListNodeAB40* next;
    sMsgListNodeAB40* prev;
    void* data;
};

struct sMsgListIterAB40 {
    sMsgListNodeAB40* node;
    sMsgListIterAB40(sMsgListNodeAB40* x) : node(x) {}
    sMsgListIterAB40(const sMsgListIterAB40& x) : node(x.node) {}
};

static inline sMsgListIterAB40 sMsgListAB40_insert(sMsgListIterAB40 pos, void* const& x)
{
    sMsgListNodeAB40* tmp = (sMsgListNodeAB40*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

// cBXString temporary (one pointer; non-POD, so it gets its own 16-byte stack slot).
struct cBXStrAB40 {
    char* str;
    cBXStrAB40() {}
    cBXStrAB40(const cBXStrAB40& o) : str(o.str) {}
};

extern "C" void LobbyMan_PostChatEvent(char* self, const char* a, const char* b)
{
    int* m = (int*)operator new(0x10, D_00480498, 0x20000000, 0);
    cBXStrAB40 sa;
    cBXString_cBXString2(&sa, a);
    cBXStrAB40 sb;
    cBXString_cBXString2(&sb, b);
    m[0] = 0xDE;
    *(void***)((char*)m + 0x4) = D_00481230;
    cBXString_cBXString1((char*)m + 0x8, &sa);
    cBXString_cBXString1((char*)m + 0xC, &sb);
    cBXString__cBXString(&sa, 2);
    cBXString__cBXString(&sb, 2);
    void* mp = m;
    sMsgListAB40_insert(*(sMsgListNodeAB40**)(self + 0xF0), mp);
}

INCLUDE_ASM("dirtysock/tagsunk", func_0025AC50);

//100%
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);

extern "C" void LobbyMan_SendRequest(void* self, int a1, int tag, void* cb, int a4, float f)
{
    *(int*)self = a1;
    *(float*)((char*)self + 0xE0) = f;
    *(int*)((char*)self + 0x40) = func_003E8B10(*(void**)((char*)self + 0x54), tag, cb, a4, self);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_00480838[];
extern void* D_004A3028;
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* LobbyMan_ctor(void* self);

extern "C" void func_0025B650(void)
{
    D_004A3028 = LobbyMan_ctor(cMemMan_alloc(0x300, D_00480838, 0x20000000, 0));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern void* D_004A3028;
extern void* D_004A2EEC;
extern "C" void func_0025B800(void* self);
extern "C" void func_00259628(void* self, int flags);
extern "C" void func_00256C50(void);

extern "C" void func_0025B688(void)
{
    if (D_004A3028 != 0) {
        func_0025B800(D_004A3028);
        if (D_004A3028 != 0) {
            func_00259628(D_004A3028, 3);
        }
        D_004A3028 = 0;
    }
    if (D_004A2EEC != 0) {
        func_00256C50();
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern int D_004A3018;
extern "C" void func_0025A948(void* self);
extern "C" void LobbyApi_Connect(void* p, int a, int timeout, void* cb, void* user);
extern "C" int func_003F3A98(void* p, int a);
extern "C" void LobbyMan_OnConnectReply_Thunk(void* self, void* a1, int a2);

struct sMsgListNodeB6D8 {
    sMsgListNodeB6D8* next;
    sMsgListNodeB6D8* prev;
    void* data;
};

struct sMsgListIterB6D8 {
    sMsgListNodeB6D8* node;
    sMsgListIterB6D8(sMsgListNodeB6D8* x) : node(x) {}
    sMsgListIterB6D8(const sMsgListIterB6D8& x) : node(x.node) {}
};

static inline sMsgListIterB6D8 sMsgListB6D8_insert(sMsgListIterB6D8 pos, void* const& x)
{
    sMsgListNodeB6D8* tmp = (sMsgListNodeB6D8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025B6D8(char* self, int conn)
{
    if (*(void**)(self + 0x54) == 0)
        func_0025A948(self);
    *(int*)(self + 0x14) = conn;
    if (conn != 0) {
        int g = D_004A3018;
        *(int*)self = 3;
        *(float*)(self + 0xE0) = 30.0f;
        *(int*)(self + 0x4) = g;
        // PORT: function pointer passed as a callback argument.
        LobbyApi_Connect(*(void**)(self + 0x54), g, 0x2AF8, (void*)LobbyMan_OnConnectReply_Thunk, self);
    } else {
        *(int*)self = 2;
        *(int*)(self + 0x58) = func_003F3A98(*(void**)(self + 0xE8), 0);
    }
    int type = 0xC8;
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListB6D8_insert(*(sMsgListNodeB6D8**)(self + 0xF0), mp);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void LobbyMan_DestroyPeerTable(void* self);
extern "C" void func_0025AA98(void* self);

extern "C" void func_0025B800(void* self)
{
    LobbyMan_DestroyPeerTable(self);
    if (*(void**)((char*)self + 0x54) != 0) {
        func_0025AA98(self);
    }
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0xC) = 0;
    *(int*)((char*)self + 0x0) = 0;
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];
extern char D_00480848[];
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeB848 {
    sMsgListNodeB848* next;
    sMsgListNodeB848* prev;
    void* data;
};

struct sMsgListIterB848 {
    sMsgListNodeB848* node;
    sMsgListIterB848(sMsgListNodeB848* x) : node(x) {}
    sMsgListIterB848(const sMsgListIterB848& x) : node(x.node) {}
};

static inline sMsgListIterB848 sMsgListB848_insert(sMsgListIterB848 pos, void* const& x)
{
    sMsgListNodeB848* tmp = (sMsgListNodeB848*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_B848(char* self, void* msg)
{
    void* mp = msg;
    sMsgListB848_insert(*(sMsgListNodeB848**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnConnectReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        func_003E8B10(*(void**)(self + 0x54), 0x73656C65, D_00480848, 0, 0);
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0xC9;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_B848(self, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_B848(self, m);
        *(int*)(self + 0x10) = 1;
    }
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_00480870[];
extern char D_004A2F58[];
extern char D_004A2FE0[];
extern char D_004A3030[];
extern char D_004A3038[];
extern char D_004A3040[];
extern char D_004A3048[];
extern char D_004A3050[];
extern char D_004A3058[];
extern char D_004A3060[];
extern char D_004A3068[];
extern char D_004A3070[];
extern char D_004A3078[];
extern char D_004A3080[];
extern "C" void LobbyMan_OnCreateAccountReply_Thunk(void* self, void* a1, int a2);
extern "C" int cDirtysock_tag_TagFieldSetNumber(char* buf, int size, const char* key, int value);
extern "C" const char* LobbyMan_GetLanguage();

struct sMsgListNodeB9C8 {
    sMsgListNodeB9C8* next;
    sMsgListNodeB9C8* prev;
    void* data;
};

struct sMsgListIterB9C8 {
    sMsgListNodeB9C8* node;
    sMsgListIterB9C8(sMsgListNodeB9C8* x) : node(x) {}
    sMsgListIterB9C8(const sMsgListIterB9C8& x) : node(x.node) {}
};

static inline sMsgListIterB9C8 sMsgListB9C8_insert(sMsgListIterB9C8 pos, void* const& x)
{
    sMsgListNodeB9C8* tmp = (sMsgListNodeB9C8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025B9C8(char* self, char* msg)
{
    char buf[0x200];
    char yn[16];
    char mf[16];
    char ver[16];
    sprintf(yn, D_004A3030, *(int*)(msg + 0x38) ? 'Y' : 'N', *(int*)(msg + 0x3C) ? 'Y' : 'N');
    sprintf(mf, D_004A3038, *(int*)(msg + 0x34) ? 'F' : 'M');
    sprintf(ver, D_00480870, *(int*)(msg + 0x30), *(int*)(msg + 0x28), *(int*)(msg + 0x2C));
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A2F58, *(const char**)(msg + 0x0));
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3040, *(const char**)(msg + 0x4));
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3048, yn);
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3050, *(const char**)(msg + 0xC));
    const char* email = *(const char**)(msg + 0x10);
    // PORT: string length read from the header before the characters.
    if (*(int*)((int)email - 8) != 0)
        cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3058, email);
    int type = 0xCA;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3060, mf);
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3068, ver);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x200, D_004A3070, 0);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x200, D_004A3078, 4);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x200, D_004A3080, 0xD);
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A2FE0, LobbyMan_GetLanguage());
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 4, 0x61636374, buf, (int)LobbyMan_OnCreateAccountReply_Thunk, 20.0f);
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListB9C8_insert(*(sMsgListNodeB9C8**)(self + 0xF0), mp);
}

//100%
extern char D_004A2F40[];
extern char D_004A3090[];
extern "C" const char* cDirtysock_tag_TagFieldFind(const char* record, const char* name);
// PORT: TagFieldGetString really takes a 4th (default value) argument; the unit declares 3.
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");
extern "C" void* cBXString_cBXString4(void* self, const char* str);

struct sDsNameListK2 {
    char pad_0x00[0x274];
    char* names[4];   // 0x274 (cBXString)
    int count;        // 0x284
};

// Splits a comma-separated tag field into up to 4 strings.
extern "C" void LobbyMan_ParseNameSuggestions(sDsNameListK2* self, char* msg)
{
    char buf[256];
    char* p;
    char* start;
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3090), buf, 256, D_004A2F40);
    self->count = 0;
    p = buf;
    while ((*p != 0) && (self->count < 4)) {
        start = p;
        while ((*p != 0) && (*p != ','))
            p++;
        if (*p != 0)
            *p++ = 0;
        cBXString_cBXString4(&self->names[self->count++], start);
    }
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004811F0[];
extern void* D_004812B0[];
extern void* D_00481290[];
extern char D_004A3098[];
extern "C" int cDirtysock_tag_TagFieldGetNumber(const char* tag, int defval);
struct sDsNameListK2;
extern "C" void LobbyMan_ParseNameSuggestions(sDsNameListK2* self, char* msg);

struct sMsgListNodeBD30 {
    sMsgListNodeBD30* next;
    sMsgListNodeBD30* prev;
    void* data;
};

struct sMsgListIterBD30 {
    sMsgListNodeBD30* node;
    sMsgListIterBD30(sMsgListNodeBD30* x) : node(x) {}
    sMsgListIterBD30(const sMsgListIterBD30& x) : node(x.node) {}
};

static inline sMsgListIterBD30 sMsgListBD30_insert(sMsgListIterBD30 pos, void* const& x)
{
    sMsgListNodeBD30* tmp = (sMsgListNodeBD30*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_BD30(char* self, void* msg)
{
    void* mp = msg;
    sMsgListBD30_insert(*(sMsgListNodeBD30**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnCreateAccountReply(char* self, char* msg)
{
    *(int*)self = 1;
    int err = *(int*)(msg + 0x8);
    if (err == 0) {
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0xCB;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_BD30(self, m);
    } else if (err == 0x746F6F79) {
        int n = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3098), 0);
        int* m = (int*)operator new(0x10, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        m[2] = err;
        *(void***)((char*)m + 0x4) = D_004811F0;
        m[3] = n;
        post_BD30(self, m);
    } else {
        if (err == 0x6475706C)
            LobbyMan_ParseNameSuggestions((sDsNameListK2*)self, msg);
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_BD30(self, m);
    }
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_004A2F58[];
extern char D_004A3030[];
extern char D_004A3040[];
extern char D_004A3048[];
extern char D_004A3050[];
extern char D_004A30A0[];
extern "C" void LobbyMan_OnEditAccountReply_Thunk(void* self, void* a1, int a2);

struct sMsgListNodeBF18 {
    sMsgListNodeBF18* next;
    sMsgListNodeBF18* prev;
    void* data;
};

struct sMsgListIterBF18 {
    sMsgListNodeBF18* node;
    sMsgListIterBF18(sMsgListNodeBF18* x) : node(x) {}
    sMsgListIterBF18(const sMsgListIterBF18& x) : node(x.node) {}
};

static inline sMsgListIterBF18 sMsgListBF18_insert(sMsgListIterBF18 pos, void* const& x)
{
    sMsgListNodeBF18* tmp = (sMsgListNodeBF18*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025BF18(char* self, char* msg)
{
    char buf[0x200];
    char tmp[16];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A2F58, *(const char**)(self + 0x48));
    if (*(int*)(msg + 0x44) != 0) {
        cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3040, *(const char**)(self + 0x4C));
        cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A30A0, *(const char**)(msg + 0x4));
    }
    if (*(int*)(msg + 0x48) != 0) {
        sprintf(tmp, D_004A3030, *(int*)(msg + 0x38) ? 'Y' : 'N', *(int*)(msg + 0x3C) ? 'Y' : 'N');
        cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3048, tmp);
    }
    if (*(int*)(msg + 0x4C) != 0) {
        cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3050, *(const char**)(msg + 0xC));
    }
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 5, 0x65646974, buf, (int)LobbyMan_OnEditAccountReply_Thunk, 20.0f);
    int type = 0xCD;
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListBF18_insert(*(sMsgListNodeBF18**)(self + 0xF0), mp);
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeC0C0 {
    sMsgListNodeC0C0* next;
    sMsgListNodeC0C0* prev;
    void* data;
};

struct sMsgListIterC0C0 {
    sMsgListNodeC0C0* node;
    sMsgListIterC0C0(sMsgListNodeC0C0* x) : node(x) {}
    sMsgListIterC0C0(const sMsgListIterC0C0& x) : node(x.node) {}
};

static inline sMsgListIterC0C0 sMsgListC0C0_insert(sMsgListIterC0C0 pos, void* const& x)
{
    sMsgListNodeC0C0* tmp = (sMsgListNodeC0C0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_C0C0(char* self, void* msg)
{
    void* mp = msg;
    sMsgListC0C0_insert(*(sMsgListNodeC0C0**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnEditAccountReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0xCE;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_C0C0(self, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_C0C0(self, m);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_004A3050[];
extern "C" void LobbyMan_OnLostByEmailReply_Thunk(void* self, void* a1, int a2);

struct sMsgListNodeC1E0 {
    sMsgListNodeC1E0* next;
    sMsgListNodeC1E0* prev;
    void* data;
};

struct sMsgListIterC1E0 {
    sMsgListNodeC1E0* node;
    sMsgListIterC1E0(sMsgListNodeC1E0* x) : node(x) {}
    sMsgListIterC1E0(const sMsgListIterC1E0& x) : node(x.node) {}
};

static inline sMsgListIterC1E0 sMsgListC1E0_insert(sMsgListIterC1E0 pos, void* const& x)
{
    sMsgListNodeC1E0* tmp = (sMsgListNodeC1E0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025C1E0(char* self, const char* value)
{
    char buf[0x200];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3050, value);
    int type = 0xD1;
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 6, 0x6C6F7374, buf, (int)LobbyMan_OnLostByEmailReply_Thunk, 20.0f);
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListC1E0_insert(*(sMsgListNodeC1E0**)(self + 0xF0), mp);
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeC2D8 {
    sMsgListNodeC2D8* next;
    sMsgListNodeC2D8* prev;
    void* data;
};

struct sMsgListIterC2D8 {
    sMsgListNodeC2D8* node;
    sMsgListIterC2D8(sMsgListNodeC2D8* x) : node(x) {}
    sMsgListIterC2D8(const sMsgListIterC2D8& x) : node(x.node) {}
};

static inline sMsgListIterC2D8 sMsgListC2D8_insert(sMsgListIterC2D8 pos, void* const& x)
{
    sMsgListNodeC2D8* tmp = (sMsgListNodeC2D8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_C2D8(char* self, void* msg)
{
    void* mp = msg;
    sMsgListC2D8_insert(*(sMsgListNodeC2D8**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnLostByEmailReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0xCF;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_C2D8(self, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_C2D8(self, m);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_004A2F58[];
extern "C" void LobbyMan_OnLostByNameReply_Thunk(void* self, void* a1, int a2);

struct sMsgListNodeC3F8 {
    sMsgListNodeC3F8* next;
    sMsgListNodeC3F8* prev;
    void* data;
};

struct sMsgListIterC3F8 {
    sMsgListNodeC3F8* node;
    sMsgListIterC3F8(sMsgListNodeC3F8* x) : node(x) {}
    sMsgListIterC3F8(const sMsgListIterC3F8& x) : node(x.node) {}
};

static inline sMsgListIterC3F8 sMsgListC3F8_insert(sMsgListIterC3F8 pos, void* const& x)
{
    sMsgListNodeC3F8* tmp = (sMsgListNodeC3F8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025C3F8(char* self, const char* value)
{
    char buf[0x200];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A2F58, value);
    int type = 0xD0;
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 7, 0x6C6F7374, buf, (int)LobbyMan_OnLostByNameReply_Thunk, 20.0f);
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListC3F8_insert(*(sMsgListNodeC3F8**)(self + 0xF0), mp);
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeC4F0 {
    sMsgListNodeC4F0* next;
    sMsgListNodeC4F0* prev;
    void* data;
};

struct sMsgListIterC4F0 {
    sMsgListNodeC4F0* node;
    sMsgListIterC4F0(sMsgListNodeC4F0* x) : node(x) {}
    sMsgListIterC4F0(const sMsgListIterC4F0& x) : node(x.node) {}
};

static inline sMsgListIterC4F0 sMsgListC4F0_insert(sMsgListIterC4F0 pos, void* const& x)
{
    sMsgListNodeC4F0* tmp = (sMsgListNodeC4F0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_C4F0(char* self, void* msg)
{
    void* mp = msg;
    sMsgListC4F0_insert(*(sMsgListNodeC4F0**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnLostByNameReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0xD2;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_C4F0(self, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_C4F0(self, m);
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_004813A0[];
extern char D_004A2F58[];
extern char D_004A3040[];
extern char D_004A30C0[];
extern char D_004A30C8[];
extern char D_004A30D0[];
extern char D_004A30D8[];
extern char D_004A30E0[];
extern void* D_004A2EB8;
extern void* D_004A33F0;
extern void* D_004A33F4;
extern "C" void LobbyMan_OnLoginReply_Thunk();
extern "C" int cDirtysock_tag_TagFieldSetNumber(char* buf, int size, const char* key, int value);
extern "C" const char* func_003F3F78();
void* func_00266F38(void* self);

struct sMsgListNodeC610 {
    sMsgListNodeC610* next;
    sMsgListNodeC610* prev;
    void* data;
};

struct sMsgListIterC610 {
    sMsgListNodeC610* node;
    sMsgListIterC610(sMsgListNodeC610* x) : node(x) {}
    sMsgListIterC610(const sMsgListIterC610& x) : node(x.node) {}
};

static inline sMsgListIterC610 sMsgListC610_insert(sMsgListIterC610 pos, void* const& x)
{
    sMsgListNodeC610* tmp = (sMsgListNodeC610*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_C610(char* lst, void* msg)
{
    void* mp = msg;
    sMsgListC610_insert(*(sMsgListNodeC610**)(lst + 4), mp);
}

struct sDsSlotC610 {
    char pad[0x88];
    int flags;
};

extern "C" void func_0025C610(char* self)
{
    char buf[0x200];
    int flags = 0;
    int caps = 0;
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A2F58, *(const char**)(self + 0x48));
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3040, *(const char**)(self + 0x4C));
    cDirtysock_tag_TagFieldSetNumber(buf, 0x200, D_004A30C0, 1);
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A30C8, func_003F3F78());
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A30D0, D_004813A0);
    int v = *(int*)((char*)D_004A2EB8 + 0x30);
    if (v != 1) {
        flags = v & 4;
        caps = 0x10024;
        if (v & 0x10)
            flags |= 0x10000;
        if (v & 8)
            flags |= 0x20;
    }
    caps |= 0x800;
    int i = 0;
    void* conn = D_004A33F4;

    for (; i < 8; i++) {
        if (((sDsSlotC610*)D_004A33F0)[i].flags & 1) {
            flags |= 0x800;
            break;
        }
    }
    caps |= 0x100;
    if ((int)func_00266F38(conn) & 0x10)
        flags |= 0x100;
    cDirtysock_tag_TagFieldSetNumber(buf, 0x200, D_004A30D8, flags);
    int type = 0xD3;
    cDirtysock_tag_TagFieldSetNumber(buf, 0x200, D_004A30E0, caps);
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 8, 0x61757468, buf, (int)LobbyMan_OnLoginReply_Thunk, 20.0f);
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    post_C610(self + 0xEC, m);
}

extern "C" void func_003E8D70(void* p, int a);

extern "C" void func_0025C878(char* self)
{
    if (*(int*)self == 8)
        func_003E8D70(*(void**)(self + 0x54), *(int*)(self + 0x40));
}

INCLUDE_ASM("dirtysock/tagsunk", LobbyMan_OnLoginReply);

extern "C" void* func_0025CD50(void*, int);

//100%
void* func_0025CD28(void* self, int a1)
{
    return func_0025CD50(self, *(int*)((char*)((char*)self + a1 * 4) + 0x70));
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];
extern char D_004A3108[];
extern char D_004A30C8[];
extern char D_004A30D0[];
extern char D_004A3110[];
extern char D_004813A0[];
extern "C" const char* func_003F3F78();
extern "C" void* cBXString_cBXString4(void* self, const char* str);
extern "C" void LobbyMan_SendRequest(void* self, int a1, int tag, void* cb, int a4, float f);
extern "C" void LobbyMan_OnSelectPersonaReply_Thunk(void* self, void* a1, int a2);
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeCD50 {
    sMsgListNodeCD50* next;
    sMsgListNodeCD50* prev;
    void* data;
};

struct sMsgListIterCD50 {
    sMsgListNodeCD50* node;
    sMsgListIterCD50(sMsgListNodeCD50* x) : node(x) {}
    sMsgListIterCD50(const sMsgListIterCD50& x) : node(x.node) {}
};

static inline sMsgListIterCD50 sMsgListCD50_insert(sMsgListIterCD50 pos, void* const& x)
{
    sMsgListNodeCD50* tmp = (sMsgListNodeCD50*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

// PORT: the unit declares func_0025CD50 as void* (void*, int) (a caller tail-calls it); the body takes (self, name).
extern "C" void func_0025CD50_impl(char* self, const char* name) __asm__("func_0025CD50");

extern "C" void func_0025CD50_impl(char* self, const char* name)
{
    cBXString_cBXString4(self + 0x80, name);
    char buf[0x200];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3108, name);
    const char* key = D_004A30C8;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, key, func_003F3F78());
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A30D0, D_004813A0);
    if (*(int*)(self + 0x18) != 0)
        cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3110, self + 0x1C);
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 9, 0x70657273, buf, (int)LobbyMan_OnSelectPersonaReply_Thunk, 20.0f);
    int type = 0xD9;
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListCD50_insert(*(sMsgListNodeCD50**)(self + 0xF0), mp);
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481290[];
extern "C" void LobbyMan_QueryOwnStats(void* self);

struct sMsgListNodeCEB0 {
    sMsgListNodeCEB0* next;
    sMsgListNodeCEB0* prev;
    void* data;
};

struct sMsgListIterCEB0 {
    sMsgListNodeCEB0* node;
    sMsgListIterCEB0(sMsgListNodeCEB0* x) : node(x) {}
    sMsgListIterCEB0(const sMsgListIterCEB0& x) : node(x.node) {}
};

static inline sMsgListIterCEB0 sMsgListCEB0_insert(sMsgListIterCEB0 pos, void* const& x)
{
    sMsgListNodeCEB0* tmp = (sMsgListNodeCEB0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_CEB0(char* self, void* msg)
{
    void* mp = msg;
    sMsgListCEB0_insert(*(sMsgListNodeCEB0**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnSelectPersonaReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        LobbyMan_QueryOwnStats(self);
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0xDA;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_CEB0(self, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_CEB0(self, m);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A3108[];
extern "C" int cDirtysock_tag_TagFieldSetString(char* buf, int size, const char* key, const char* value);
extern "C" void LobbyMan_SendRequest(void* self, int a1, int tag, void* cb, int a4, float f);
extern "C" void LobbyMan_OnOwnStatsReply_Thunk(void* self, void* a1, int a2);

extern "C" void LobbyMan_QueryOwnStats(void* self)
{
    char buf[0x200];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3108, *(const char**)((char*)self + 0x80));
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 0x1B, 0x6F6E6C6E, buf, (int)LobbyMan_OnOwnStatsReply_Thunk, 20.0f);
}

//100%
extern "C" int cDirtysock_tag_TagFieldGetStructure(const char* tag, void* data, int len, const char* fmt);
extern "C" int cDirtysock_tag_TagFieldGetNumber(const char* tag, int defval);
extern "C" const char* cDirtysock_tag_TagFieldFind(const char* record, const char* name);
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];
extern char D_004A3128[];
extern char D_004A3130[];
extern char D_004A2F40[];
extern char D_004A2F30[];
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");
extern "C" void func_0025E0C8(void* self, int value);
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeD048 {
    sMsgListNodeD048* next;
    sMsgListNodeD048* prev;
    void* data;
};

struct sMsgListIterD048 {
    sMsgListNodeD048* node;
    sMsgListIterD048(sMsgListNodeD048* x) : node(x) {}
    sMsgListIterD048(const sMsgListIterD048& x) : node(x.node) {}
};

static inline sMsgListIterD048 sMsgListD048_insert(sMsgListIterD048 pos, void* const& x)
{
    sMsgListNodeD048* tmp = (sMsgListNodeD048*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_D048(char* self, void* msg)
{
    void* mp = msg;
    sMsgListD048_insert(*(sMsgListNodeD048**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnOwnStatsReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        char buf[0x100];
        int st[16];
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3128), buf, 0x100, D_004A2F40);
        cDirtysock_tag_TagFieldGetStructure(buf, st, 0x40, D_004A2F30);
        *(int*)(self + 0xBC) = st[2];
        *(int*)(self + 0xC0) = st[2] + st[3] + st[4];
        *(int*)(self + 0xC4) = st[6];
        *(int*)(self + 0xB8) = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3130), 0);
        *(int*)(self + 0xC8) = -1;
        func_0025E0C8(self, 0);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_D048(self, m);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_004A3108[];
extern "C" void* cBXString_cBXString4(void* self, const char* str);
extern "C" void LobbyMan_OnCreatePersonaReply_Thunk(void* self, void* a1, int a2);

struct sMsgListNodeD1B8 {
    sMsgListNodeD1B8* next;
    sMsgListNodeD1B8* prev;
    void* data;
};

struct sMsgListIterD1B8 {
    sMsgListNodeD1B8* node;
    sMsgListIterD1B8(sMsgListNodeD1B8* x) : node(x) {}
    sMsgListIterD1B8(const sMsgListIterD1B8& x) : node(x.node) {}
};

static inline sMsgListIterD1B8 sMsgListD1B8_insert(sMsgListIterD1B8 pos, void* const& x)
{
    sMsgListNodeD1B8* tmp = (sMsgListNodeD1B8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

struct sDsNamesD1B8 {
    char pad_0x00[0x6C];
    int count;          // 0x6C
    char* names[8];     // 0x70 (cBXString)
};

extern "C" void func_0025D1B8(char* self, const char* name)
{
    if (*(int*)self != 0) {
        char buf[0x200];
        buf[0] = 0;
        cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3108, name);
        int type = 0xD5;
        // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
        LobbyMan_SendRequest(self, 0xA, 0x63706572, buf, (int)LobbyMan_OnCreatePersonaReply_Thunk, 20.0f);
        sDsNamesD1B8* s = (sDsNamesD1B8*)self;
        cBXString_cBXString4(&s->names[s->count], name);
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = type;
        *(void***)((char*)m + 0x4) = D_004812B0;
        void* mp = m;
        sMsgListD1B8_insert(*(sMsgListNodeD1B8**)(self + 0xF0), mp);
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];

extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeD2D8 {
    sMsgListNodeD2D8* next;
    sMsgListNodeD2D8* prev;
    void* data;
};

struct sMsgListIterD2D8 {
    sMsgListNodeD2D8* node;
    sMsgListIterD2D8(sMsgListNodeD2D8* x) : node(x) {}
    sMsgListIterD2D8(const sMsgListIterD2D8& x) : node(x.node) {}
};

static inline sMsgListIterD2D8 sMsgListD2D8_insert(sMsgListIterD2D8 pos, void* const& x)
{
    sMsgListNodeD2D8* tmp = (sMsgListNodeD2D8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_D2D8(char* self, void* msg)
{
    void* mp = msg;
    sMsgListD2D8_insert(*(sMsgListNodeD2D8**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnCreatePersonaReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        (*(int*)(self + 0x6C))++;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0xD6;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_D2D8(self, m);
    } else {
        if (*(int*)(msg + 0x8) == 0x6475706C)
            LobbyMan_ParseNameSuggestions((sDsNameListK2*)self, msg);
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_D2D8(self, m);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_004A3108[];
extern "C" void LobbyMan_OnDeletePersonaReply_Thunk(void* self, void* a1, int a2);

struct sMsgListNodeD428 {
    sMsgListNodeD428* next;
    sMsgListNodeD428* prev;
    void* data;
};

struct sMsgListIterD428 {
    sMsgListNodeD428* node;
    sMsgListIterD428(sMsgListNodeD428* x) : node(x) {}
    sMsgListIterD428(const sMsgListIterD428& x) : node(x.node) {}
};

static inline sMsgListIterD428 sMsgListD428_insert(sMsgListIterD428 pos, void* const& x)
{
    sMsgListNodeD428* tmp = (sMsgListNodeD428*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025D428(char* self, int idx)
{
    if (*(int*)self != 0) {
        char buf[0x200];
        buf[0] = 0;
        cDirtysock_tag_TagFieldSetString(buf, 0x200, D_004A3108, *(const char**)(self + 0x70 + (idx << 2)));
        int type = 0xD7;
        // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
        LobbyMan_SendRequest(self, 0xB, 0x64706572, buf, (int)LobbyMan_OnDeletePersonaReply_Thunk, 20.0f);
        *(int*)(self + 0x50) = idx;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = type;
        *(void***)((char*)m + 0x4) = D_004812B0;
        void* mp = m;
        sMsgListD428_insert(*(sMsgListNodeD428**)(self + 0xF0), mp);
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];
extern "C" void* cBXString_operatorE(void* self, void* other);
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeD538 {
    sMsgListNodeD538* next;
    sMsgListNodeD538* prev;
    void* data;
};

struct sMsgListIterD538 {
    sMsgListNodeD538* node;
    sMsgListIterD538(sMsgListNodeD538* x) : node(x) {}
    sMsgListIterD538(const sMsgListIterD538& x) : node(x.node) {}
};

static inline sMsgListIterD538 sMsgListD538_insert(sMsgListIterD538 pos, void* const& x)
{
    sMsgListNodeD538* tmp = (sMsgListNodeD538*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_D538(char* lst, void* msg)
{
    void* mp = msg;
    sMsgListD538_insert(*(sMsgListNodeD538**)(lst + 4), mp);
}

struct sDsNamesD538 {
    char pad_0x00[0x50];
    int index;          // 0x50
    char pad_0x54[0x6C - 0x54];
    int count;          // 0x6C
    char* names[8];     // 0x70 (cBXString)
};

extern "C" void LobbyMan_OnDeletePersonaReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        sDsNamesD538* s = (sDsNamesD538*)self;
        char* lst = self + 0xEC;
        s->count--;
        for (int i = s->index; i < s->count; i++)
            cBXString_operatorE(&s->names[i], &s->names[i + 1]);
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        *(void***)((char*)m + 0x4) = D_004812B0;
        m[0] = 0xD8;
        post_D538(lst, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_D538(self + 0xEC, m);
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];

struct sMsgListNodeK6c0 {
    sMsgListNodeK6c0* next;
    sMsgListNodeK6c0* prev;
    void* data;
};

struct sMsgListIterK6c0 {
    sMsgListNodeK6c0* node;
    sMsgListIterK6c0(sMsgListNodeK6c0* x) : node(x) {}
    sMsgListIterK6c0(const sMsgListIterK6c0& x) : node(x.node) {}
};

static inline sMsgListIterK6c0 sMsgListK6c0_insert(sMsgListIterK6c0 pos, void* const& x)
{
    sMsgListNodeK6c0* tmp = (sMsgListNodeK6c0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void LobbyMan_OnUserListChanged(char* self)
{
    int* m = (int*)cMemMan_alloc(8, D_00480488, 0x20000000, 0);
    sMsgListNodeK6c0* list = *(sMsgListNodeK6c0**)(self + 0xF0);
    m[0] = 0xDF;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgListK6c0_insert(list, mp);
}

//100%
extern char D_004A2F40[];
extern char D_004A2F58[];
extern "C" void* func_0025F150(void* self);

extern "C" void func_0025D770(void* self, int idx)
{
    char buf[256];
    if (*(int*)self != 0) {
        const char* key = D_004A2F58;
        const char* name;
        buf[0] = 0;
        if (idx != -1) {
            name = (const char*)func_0025F150(self);
        } else {
            name = D_004A2F40;
        }
        cDirtysock_tag_TagFieldSetString(buf, 0x100, key, name);
        func_003E8B10(*(void**)((char*)self + 0x54), 0x7065656B, buf, 0, 0);
    }
}

//100%
extern char D_004A2F40[];
extern "C" void* func_0025F150(void* self);
extern "C" void func_0025D860(void* self, void* name, int a2);

extern "C" void func_0025D800(void* self, int idx, int a2)
{
    void* name;
    if (idx != -1) {
        name = func_0025F150(self);
    } else {
        name = D_004A2F40;
    }
    func_0025D860(self, name, a2);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A2F58[];
extern char D_004A3040[];
extern "C" void LobbyMan_OnMoveToRoomReply_Thunk(void* self, void* a1, int a2);

// PORT: the unit declares a2 as int; it carries an optional string pointer.
extern "C" void func_0025D860(void* self, void* name, int a2)
{
    if (*(int*)self != 0) {
        char buf[0x100];
        buf[0] = 0;
        cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A2F58, (const char*)name);
        if (a2 != 0) {
            cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3040, (const char*)a2);
        }
        // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
        LobbyMan_SendRequest(self, 0xC, 0x6D6F7665, buf, (int)LobbyMan_OnMoveToRoomReply_Thunk, 20.0f);
    }
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481290[];
extern char D_004A2F40[];
extern char D_004A2F58[];
extern "C" void cBXString_Reset(void* self);
// PORT: TagFieldGetString really takes a 4th (default value) argument; the unit declares 3.
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");

struct sMsgListNodeD8F8 {
    sMsgListNodeD8F8* next;
    sMsgListNodeD8F8* prev;
    void* data;
};

struct sMsgListIterD8F8 {
    sMsgListNodeD8F8* node;
    sMsgListIterD8F8(sMsgListNodeD8F8* x) : node(x) {}
    sMsgListIterD8F8(const sMsgListIterD8F8& x) : node(x.node) {}
};

static inline sMsgListIterD8F8 sMsgListD8F8_insert(sMsgListIterD8F8 pos, void* const& x)
{
    sMsgListNodeD8F8* tmp = (sMsgListNodeD8F8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_D8F8(char* self, void* msg)
{
    void* mp = msg;
    sMsgListD8F8_insert(*(sMsgListNodeD8F8**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnMoveToRoomReply(char* self, char* msg)
{
    *(int*)self = 1;
    if (*(int*)(msg + 0x8) == 0) {
        char buf[0x100];
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F58), buf, 0x100, D_004A2F40);
        cBXString_cBXString4(self + 0x84, buf);
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0xDC;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_D8F8(self, m);
    } else {
        cBXString_Reset(self + 0x84);
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = *(int*)(msg + 0x8);
        post_D8F8(self, m);
    }
}

//100%
extern "C" char* func_0025DA90(void* self)
{
    char* s;
    if (*(int*)((char*)self + 0x54) == 0) {
        return 0;
    }
    s = *(char**)((char*)self + 0x84);
    if (s != 0) {
        if (*s != 0) {
            return s;
        }
    }
    return 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A2F58[];
extern char D_004A3040[];
extern char D_004A3150[];
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void LobbyMan_OnCreateRoomReply_Thunk(void* self, void* a1, int a2);

extern "C" void func_0025DAC0(void* self, int a1, int a2, const char* a3)
{
    if (*(int*)self != 0) {
        char buf[0x100];
        char name[0x100];
        sprintf(name, D_004A3150, a1, a2);
        buf[0] = 0;
        cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A2F58, name);
        if (a3 != 0) {
            cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3040, a3);
        }
        // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
        LobbyMan_SendRequest(self, 0x11, 0x726F6F6D, buf, (int)LobbyMan_OnCreateRoomReply_Thunk, 20.0f);
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];
extern char D_004A2F58[];
extern char D_004A2F40[];
extern "C" const char* cDirtysock_tag_TagFieldFind(const char* record, const char* name);
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");
extern "C" void* cBXString_cBXString4(void* self, const char* str);
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeDB80 {
    sMsgListNodeDB80* next;
    sMsgListNodeDB80* prev;
    void* data;
};

struct sMsgListIterDB80 {
    sMsgListNodeDB80* node;
    sMsgListIterDB80(sMsgListNodeDB80* x) : node(x) {}
    sMsgListIterDB80(const sMsgListIterDB80& x) : node(x.node) {}
};

static inline sMsgListIterDB80 sMsgListDB80_insert(sMsgListIterDB80 pos, void* const& x)
{
    sMsgListNodeDB80* tmp = (sMsgListNodeDB80*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_DB80(char* self, void* msg)
{
    void* mp = msg;
    sMsgListDB80_insert(*(sMsgListNodeDB80**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnCreateRoomReply(char* self, char* msg)
{
    *(int*)self = 1;
    int v = *(int*)(msg + 0x8);
    if (v == 0) {
        int type = 0xE4;
        char buf[0x100];
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F58), buf, 0x100, D_004A2F40);
        cBXString_cBXString4(self + 0x84, buf);
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = type;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_DB80(self, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = v;
        post_DB80(self, m);
    }
}

//100%
extern "C" int LobbyMan_LookupPeerAddr(void* self, const char* key, int def);
extern "C" void LobbyMan_OnPingReply_Thunk(void* self, void* a1, int a2);
extern "C" int func_003E8DC0(void* p, const char* key, int value, int timeout, void* cb, void* user);

extern "C" void func_0025DD08(void* self, const char* key, int def)
{
    if (*(int*)self != 0) {
        func_003E8DC0(*(void**)((char*)self + 0x54), key, LobbyMan_LookupPeerAddr(self, key, def), 0x1388, (void*)LobbyMan_OnPingReply_Thunk, self);
    }
}

//100%
// Like func_0025DD08, but takes the key and default from the current entry of the list at 0x60.
extern "C" void* func_003EE560(void*);

extern "C" void func_0025DD68(void* self)
{
    if (*(int*)self != 0) {
        char* e = (char*)func_003EE560(*(void**)((char*)self + 0x60));
        if (e != 0) {
            const char* key = e + 8;
            func_003E8DC0(*(void**)((char*)self + 0x54), key, LobbyMan_LookupPeerAddr(self, key, *(int*)(e + 0x30)), 0x1388, (void*)LobbyMan_OnPingReply_Thunk, self);
        }
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481170[];
extern char D_004A2F58[];
extern char D_004A2F40[];
extern char D_004A3168[];
extern "C" int cDirtysock_tag_TagFieldGetNumber(const char* tag, int defval);
extern "C" void* cBXString_cBXString2(void* self, const char* s);

struct sMsgListNodeDDE0 {
    sMsgListNodeDDE0* next;
    sMsgListNodeDDE0* prev;
    void* data;
};

struct sMsgListIterDDE0 {
    sMsgListNodeDDE0* node;
    sMsgListIterDDE0(sMsgListNodeDDE0* x) : node(x) {}
    sMsgListIterDDE0(const sMsgListIterDDE0& x) : node(x.node) {}
};

static inline sMsgListIterDDE0 sMsgListDDE0_insert(sMsgListIterDDE0 pos, void* const& x)
{
    sMsgListNodeDDE0* tmp = (sMsgListNodeDDE0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void LobbyMan_OnPingReply(char* self, char* msg)
{
    char name[0x20];
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F58), name, 0x20, D_004A2F40);
    int v;
    if (*(int*)(msg + 0x8) != 0)
        v = 0x7F90;
    else
        v = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3168), 0);
    int* m = (int*)operator new(0x10, D_00480488, 0x20000000, 0);
    m[0] = 0xE5;
    *(void***)((char*)m + 0x4) = D_00481170;
    cBXString_cBXString2((char*)m + 0x8, name);
    m[3] = v;
    void* mp = m;
    sMsgListDDE0_insert(*(sMsgListNodeDDE0**)(self + 0xF0), mp);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A3108[];
extern char D_004A2FE0[];
extern "C" const char* LobbyMan_GetLanguage();
extern "C" void LobbyMan_OnReportUserReply_Thunk(void* self, void* a1, int a2);

extern "C" void func_0025DF00(void* self, const char* name)
{
    if (*(int*)self != 0) {
        char buf[0x100];
        buf[0] = 0;
        cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3108, name);
        const char* key = D_004A2FE0;
        cDirtysock_tag_TagFieldSetString(buf, 0x100, key, LobbyMan_GetLanguage());
        // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
        LobbyMan_SendRequest(self, 0x10, 0x72657074, buf, (int)LobbyMan_OnReportUserReply_Thunk, 20.0f);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeDF98 {
    sMsgListNodeDF98* next;
    sMsgListNodeDF98* prev;
    void* data;
};

struct sMsgListIterDF98 {
    sMsgListNodeDF98* node;
    sMsgListIterDF98(sMsgListNodeDF98* x) : node(x) {}
    sMsgListIterDF98(const sMsgListIterDF98& x) : node(x.node) {}
};

static inline sMsgListIterDF98 sMsgListDF98_insert(sMsgListIterDF98 pos, void* const& x)
{
    sMsgListNodeDF98* tmp = (sMsgListNodeDF98*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_DF98(char* self, void* msg)
{
    void* mp = msg;
    sMsgListDF98_insert(*(sMsgListNodeDF98**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnReportUserReply(char* self, char* msg)
{
    *(int*)self = 1;
    int v = *(int*)(msg + 0x8);
    if (v == 0) {
        int type = 0xE8;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = type;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_DF98(self, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = v;
        post_DF98(self, m);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A2F58[];
extern "C" int cDirtysock_tag_TagFieldSetNumber(char* buf, int size, const char* key, int value);
extern "C" void LobbyMan_SendRequest(void* self, int a1, int tag, void* cb, int a4, float f);
extern "C" void LobbyMan_OnNewsReply_Thunk(void* self, void* a1, int a2);

extern "C" void func_0025E0C8(void* self, int value)
{
    if (*(int*)self != 0) {
        char buf[0x100];
        buf[0] = 0;
        cDirtysock_tag_TagFieldSetNumber(buf, 0x100, D_004A2F58, value);
        // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
        LobbyMan_SendRequest(self, 0xE, 0x6E657773, buf, (int)LobbyMan_OnNewsReply_Thunk, 20.0f);
    }
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_00481210[];
extern void* D_004812B0[];
extern char D_00480890[];
extern char D_004808A0[];
extern char D_004808B0[];
extern char D_004808C0[];
extern char D_004813A0[];
extern char D_004A2F40[];
extern void* D_004A3328;
// PORT: TagFieldGetString really takes a 4th (default value) argument; the unit declares 3.
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");
extern "C" int cDirtysock_tag_TagFieldGetNumber(const char* tag, int defval);
extern "C" void* cBXString_cBXString2(void* self, const char* s);
extern "C" int func_00261460(void* p);
extern "C" void BuddyMan_Connect(void* self, void* self2, int idx, void* a, void* b, int c);

struct sStateE138 {
    int active;     // 0x0
    int f4;
    int f8;
    int busy;       // 0xC
};

struct sNetMgrE138 {
    char pad[0xA4];
    int timeout;    // 0xA4
};

struct sMsgListNodeE138 {
    sMsgListNodeE138* next;
    sMsgListNodeE138* prev;
    void* data;
};

struct sMsgListIterE138 {
    sMsgListNodeE138* node;
    sMsgListIterE138(sMsgListNodeE138* x) : node(x) {}
    sMsgListIterE138(const sMsgListIterE138& x) : node(x.node) {}
};

static inline sMsgListIterE138 sMsgListE138_insert(sMsgListIterE138 pos, void* const& x)
{
    sMsgListNodeE138* tmp = (sMsgListNodeE138*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_E138(char* self, void* msg)
{
    void* mp = msg;
    sMsgListE138_insert(*(sMsgListNodeE138**)(self + 0xF0), mp);
}

extern "C" void LobbyMan_OnNewsReply(char* self, char* msg)
{
    sStateE138* st = (sStateE138*)self;
    st->active = 1;
    int type = *(int*)(msg + 0x8);
    if (type == 0x6E657731) {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0xE2;
        *(void***)((char*)m + 0x4) = D_00481210;
        cBXString_cBXString2(m + 2, *(char**)(msg + 0xC));
        post_E138(self, m);
    } else if (type == 0x6E657730) {
        st->busy = 1;
        if (func_00261460(D_004A3328) == 0) {
            char host[0x100];
            char name[0x100];
            cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_00480890), host, 0x100, D_004A2F40);
            int port = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004808A0), 0x34C1);
            cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004808B0), name, 0x100, D_004813A0);
            ((sNetMgrE138*)D_004A3328)->timeout = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004808C0), 0xD2F00);
            // PORT: a pointer passed through BuddyMan_Connect's int parameter.
            BuddyMan_Connect(D_004A3328, host, port, *(void**)(self + 0x80), *(void**)(self + 0x4C), (int)name);
        }
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = 0x111;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_E138(self, m);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void* func_003E8F08(void* ctx, int tag);
extern "C" unsigned int func_0025F338(void* self);
extern "C" void LobbyMan_SendSnapshot(void* self, int a1, int a2, int a3);
extern "C" void LobbyMan_OnRankListChanged(char* self, int unused);

struct sDsSlotSessK2 {
    int active;                  // 0x0
    char pad_0x04[0x50];
    void* ctx;                   // 0x54
    char pad_0x58[0xF8 - 0x58];
    int slot;                    // 0xF8
    int pad_0xFC;
    void* slotTag;               // 0x100
    unsigned int limit[58];      // 0x104
    void* handles[29];           // 0x1EC
};

extern "C" void func_0025E348(sDsSlotSessK2* self, int slot)
{
    if (self->active != 0) {
        int old = self->slot;
        self->slot = slot;
        self->slotTag = func_003E8F08(self->ctx, 0x736C6F74);
        if (func_0025F338(self) < self->limit[slot]) {
            if (self->handles[self->slot] != 0) {
                func_003E8688(self->ctx, 4, self->handles[self->slot]);
                self->handles[self->slot] = 0;
            }
            LobbyMan_SendSnapshot(self, 0, 100, old);
        } else {
            LobbyMan_OnRankListChanged((char*)self, 0);
        }
    }
}

//100%
extern "C" int cDirtysock_tag_TagFieldSetNumber(char* buf, int size, const char* key, int value);
extern "C" void LobbyMan_SendRequest(void* self, int a1, int tag, void* cb, int a4, float f);
extern "C" void* func_003E85B0(void* mgr, int idx, void* cb, void* user);
extern "C" void func_003E8D70(void* p, int a);
extern "C" void LobbyMan_OnRankListChanged_Thunk(void* self, void* a1, int a2);
extern "C" void LobbyMan_OnSnapshotReply_Thunk(void* self, void* a1, int a2);
extern int D_004A3180;
extern char D_004A3188[];
extern char D_004A3190[];
extern char D_004A3198[];
extern char D_004A31A0[];
extern char D_004A31A8[];

struct sDsSlotSessE420 {
    int active;                  // 0x0
    char pad_0x04[0x3C];
    int f40;                     // 0x40
    char pad_0x44[0x10];
    void* ctx;                   // 0x54
    char pad_0x58[0xF8 - 0x58];
    int slot;                    // 0xF8
    int pad_0xFC;
    void* slotTag;               // 0x100
    unsigned int limitA[29];     // 0x104
    unsigned int limitB[29];     // 0x178
    void* handles[29];           // 0x1EC
};

extern "C" void LobbyMan_SendSnapshot(void* self_, int a1, int a2, int a3)
{
    sDsSlotSessE420* self = (sDsSlotSessE420*)self_;
    if (self->active == 0)
        return;
    if (self->handles[self->slot] == 0)
        self->handles[self->slot] = func_003E85B0(self->ctx, 4, (void*)LobbyMan_OnRankListChanged_Thunk, self);
    char buf[0x100];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetNumber(buf, 0x100, D_004A3188, self->slot);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x100, D_004A3190, D_004A3180 + 4);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x100, D_004A3198, a1);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x100, D_004A31A0, a2);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x100, D_004A31A8, self->slot);
    func_003E8D70(self->ctx, self->limitB[a3]);
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, self->active, 0x736E6170, buf, (int)LobbyMan_OnSnapshotReply_Thunk, 20.0f);
    self->limitB[self->slot] = self->f40;
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481290[];
extern char D_004A3198[];
extern char D_004A31A8[];
extern char D_004A31A0[];
extern "C" int cDirtysock_tag_TagFieldGetNumber(const char* tag, int defval);

struct sMsgListNodeE590 {
    sMsgListNodeE590* next;
    sMsgListNodeE590* prev;
    void* data;
};

struct sMsgListIterE590 {
    sMsgListNodeE590* node;
    sMsgListIterE590(sMsgListNodeE590* x) : node(x) {}
    sMsgListIterE590(const sMsgListIterE590& x) : node(x.node) {}
};

static inline sMsgListIterE590 sMsgListE590_insert(sMsgListIterE590 pos, void* const& x)
{
    sMsgListNodeE590* tmp = (sMsgListNodeE590*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void LobbyMan_OnSnapshotReply(char* self, char* msg)
{
    int v = *(int*)(msg + 0x8);
    if (v == 0) {
        int a = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3198), 0);
        int idx = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31A8), 0);
        int b = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31A0), 0);
        *(int*)(self + (idx << 2) + 0x104) = a + b;
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = v;
        void* mp = m;
        sMsgListE590_insert(*(sMsgListNodeE590**)(self + 0xF0), mp);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_004A3108[];
extern "C" void LobbyMan_OnLookupUserReply_Thunk(void* self, void* a1, int a2);

struct sMsgListNodeE6D0 {
    sMsgListNodeE6D0* next;
    sMsgListNodeE6D0* prev;
    void* data;
};

struct sMsgListIterE6D0 {
    sMsgListNodeE6D0* node;
    sMsgListIterE6D0(sMsgListNodeE6D0* x) : node(x) {}
    sMsgListIterE6D0(const sMsgListIterE6D0& x) : node(x.node) {}
};

static inline sMsgListIterE6D0 sMsgListE6D0_insert(sMsgListIterE6D0 pos, void* const& x)
{
    sMsgListNodeE6D0* tmp = (sMsgListNodeE6D0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025E6D0(char* self, const char* name)
{
    if (*(int*)self != 0) {
        if (func_0041AA88(*(void**)(self + 0x80), (void*)name) == 0) {
            int type = 0x10E;
            int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
            m[0] = type;
            *(void***)((char*)m + 0x4) = D_004812B0;
            void* mp = m;
            sMsgListE6D0_insert(*(sMsgListNodeE6D0**)(self + 0xF0), mp);
        } else {
            char buf[0x100];
            buf[0] = 0;
            cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3108, name);
            *(int*)(self + 0x44) = 1;
            // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
            LobbyMan_SendRequest(self, *(int*)self, 0x75736572, buf, (int)LobbyMan_OnLookupUserReply_Thunk, 20.0f);
        }
    }
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" int cDirtysock_tag_TagFieldGetStructure(const char* tag, void* data, int len, const char* fmt);
extern "C" int cDirtysock_tag_TagFieldGetNumber(const char* tag, int defval);
extern "C" const char* cDirtysock_tag_TagFieldFind(const char* record, const char* name);
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern char D_004A2F30[];
extern char D_004A2F40[];
extern char D_004A2FA0[];
extern char D_004A3108[];
extern char D_004A3128[];
extern char D_004A31C0[];
extern char D_004A31C8[];
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");
extern "C" void* cBXString_cBXString2(void* self, const char* s);
extern void* D_00481190[];
extern void* D_00481290[];

struct sMsgListNodeE7F0 {
    sMsgListNodeE7F0* next;
    sMsgListNodeE7F0* prev;
    void* data;
};

struct sMsgListIterE7F0 {
    sMsgListNodeE7F0* node;
    sMsgListIterE7F0(sMsgListNodeE7F0* x) : node(x) {}
    sMsgListIterE7F0(const sMsgListIterE7F0& x) : node(x.node) {}
};

static inline sMsgListIterE7F0 sMsgListE7F0_insert(sMsgListIterE7F0 pos, void* const& x)
{
    sMsgListNodeE7F0* tmp = (sMsgListNodeE7F0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_E7F0(char* self, void* msg)
{
    void* mp = msg;
    sMsgListE7F0_insert(*(sMsgListNodeE7F0**)(self + 0xF0), mp);
}

struct sRecE7F0 {
    int id;
    int start;
    int end;
    int len;
    int extra;
};

struct sMsgE7F0 {
    int type;
    void** vt;
    char name[4];       // 0x8 cBXString
    char text[4];       // 0xC cBXString
    int on;             // 0x10
    int count;          // 0x14
    sRecE7F0 rec;       // 0x18
};

extern "C" void LobbyMan_OnLookupUserReply(char* self, char* msg)
{
    *(int*)(self + 0x44) = 0;
    int err = *(int*)(msg + 0x8);
    if (err == 0) {
        char name[0x100];
        char text[0x100];
        sRecE7F0 rec;
        char buf[0x100];
        int st[16];
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3108), name, 0x100, D_004A2F40);
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3128), buf, 0x100, D_004A2F40);
        cDirtysock_tag_TagFieldGetStructure(buf, st, 0x40, D_004A2F30);
        rec.start = st[2];
        rec.end = st[2] + st[3] + st[4];
        rec.len = st[6];
        rec.id = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31C0), -1);
        rec.extra = -1;
        int count = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2FA0), 0);
        int on = count > 0;
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31C8), text, 0x100, D_004A2F40);
        sMsgE7F0* m = (sMsgE7F0*)operator new(0x2C, D_00480488, 0x20000000, 0);
        m->type = 0xE3;
        m->vt = D_00481190;
        cBXString_cBXString2(m->name, name);
        cBXString_cBXString2(m->text, text);
        m->on = on;
        m->count = count;
        m->rec = rec;
        post_E7F0(self, m);
    } else {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = err;
        post_E7F0(self, m);
    }
}

extern char D_004A3108[];
extern "C" void LobbyMan_OnUserStatsReply_Thunk(void* self, void* a1, int a2);

// Sends an 'onln' message with value under key D_004A3108; LobbyMan_OnUserStatsReply_Thunk handles the reply.
extern "C" void func_0025EAA0(void* self, const char* value)
{
    char buf[0x100];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3108, value);
    func_003E8B10(*(void**)((char*)self + 0x54), 0x6F6E6C6E, buf, (int)LobbyMan_OnUserStatsReply_Thunk, self);
}

//100%
// Handles a user record: with no type code it parses the record's name fields, counts and
// stats into a 0x10D message; any type other than 'uusr' becomes a 0x102 message.
extern char D_004A31D8[];
extern char D_004A2F38[];
extern char D_004A31E0[];
extern char D_004A31E8[];
extern char D_004A31F0[];
extern char D_004A31F8[];
extern char D_004A3130[];
extern void* D_00481110[];

struct sMsgListNode_25EB00 {
    sMsgListNode_25EB00* next;
    sMsgListNode_25EB00* prev;
    void* data;
};

struct sMsgListIter_25EB00 {
    sMsgListNode_25EB00* node;
    sMsgListIter_25EB00(sMsgListNode_25EB00* x) : node(x) {}
    sMsgListIter_25EB00(const sMsgListIter_25EB00& x) : node(x.node) {}
};

struct sMsgList_25EB00 {
    sMsgListNode_25EB00* head;
    sMsgListIter_25EB00 end() { return head; }
    sMsgListIter_25EB00 insert(sMsgListIter_25EB00 pos, void* const& x)
    {
        sMsgListNode_25EB00* tmp = (sMsgListNode_25EB00*)operator new(0xC, D_004804A8, 0x20000000, 0);
        void** data = &tmp->data;
        if (data != 0)
            *data = x;
        tmp->next = pos.node;
        tmp->prev = pos.node->prev;
        pos.node->prev->next = tmp;
        pos.node->prev = tmp;
        return tmp;
    }
};

struct sUserStats_25EB00 { int a, b, c, d, e; };

struct sUserMsg_25EB00 {
    int kind;
    void** vt;
    char name[0x20];
    char s2[0x20];
    char s3[0x100];
    int n2;                     // 0x148
    int n1;                     // 0x14C
    sUserStats_25EB00 stats;    // 0x150
};

extern "C" void LobbyMan_OnUserStatsReply(char* self, char* msg)
{
    int type = *(int*)(msg + 0x8);
    if (type == 0) {
        char name[0x100];
        char s2[0x100];
        char s3[0x100];
        char raw[0x20];
        int st[0x10];
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31D8), name, 0x100, D_004A2F40);
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A2F38), s2, 0x100, D_004A2F40);
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31E0), s3, 0x100, D_004A2F40);
        int n1 = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31E8), -1);
        int n2 = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31F0), -1);
        cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A31F8), raw, 0x14, D_004A2F40);
        int n3 = cDirtysock_tag_TagFieldGetNumber(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3130), 0);
        cDirtysock_tag_TagFieldGetStructure(raw, st, 0x40, D_004A2F30);
        sUserStats_25EB00 info;
        info.a = n3;
        info.b = st[2];
        info.c = st[2] + st[3] + st[4];
        info.d = st[6];
        info.e = n1;
        sUserMsg_25EB00* m = (sUserMsg_25EB00*)operator new(0x164, D_00480488, 0x20000000, 0);
        m->kind = 0x10D;
        m->vt = D_00481110;
        m->n2 = n2;
        m->n1 = n1;
        strcpy(m->name, name);
        strcpy(m->s2, s2);
        strcpy(m->s3, s3);
        m->stats = info;
        sMsgList_25EB00* l = (sMsgList_25EB00*)(self + 0xF0);
        void* mp = m;
        l->insert(l->end(), mp);
    } else if (type != 0x75757372) {
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = type;
        sMsgList_25EB00* l = (sMsgList_25EB00*)(self + 0xF0);
        void* mp = m;
        l->insert(l->end(), mp);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A3200[];
extern char D_004A3208[];
extern char D_004808D0[];
extern char D_004A2F30[];
extern "C" int cDirtysock_tag_TagFieldSetStructure(char* buf, int size, const char* key, const void* data, int len, const char* fmt);
extern "C" void func_00268E78(void* self, void* a1, int a2);

extern "C" void func_0025EE20(void* self, const void* data, int a2)
{
    int st = *(int*)self;
    if (st != 0) {
        bool on = (st == 1);
        if (on) {
            char buf[0x100];
            *(int*)((char*)self + 0xA4) = a2;
            buf[0] = 0;
            cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3200, D_004808D0);
            cDirtysock_tag_TagFieldSetStructure(buf, 0x100, D_004A3208, data, 0x14, D_004A2F30);
            // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
            LobbyMan_SendRequest(self, 0x12, 0x7175696B, buf, (int)func_00268E78, 20.0f);
        }
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];
extern char D_004A3200[];
extern char D_004A3218[];
extern "C" int* func_002591D0();
extern "C" void func_00263BA8(void* p, int arg);
extern "C" void func_00268E78(void* self, void* a1, int a2);
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNodeEED8 {
    sMsgListNodeEED8* next;
    sMsgListNodeEED8* prev;
    void* data;
};

struct sMsgListIterEED8 {
    sMsgListNodeEED8* node;
    sMsgListIterEED8(sMsgListNodeEED8* x) : node(x) {}
    sMsgListIterEED8(const sMsgListIterEED8& x) : node(x.node) {}
};

static inline sMsgListIterEED8 sMsgListEED8_insert(sMsgListIterEED8 pos, void* const& x)
{
    sMsgListNodeEED8* tmp = (sMsgListNodeEED8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_EED8(char* self, void* msg)
{
    void* mp = msg;
    sMsgListEED8_insert(*(sMsgListNodeEED8**)(self + 0xF0), mp);
}

extern "C" void func_0025EED8(char* self)
{
    int st = *(int*)self;
    if (st == 0)
        return;
    if (st == 0x19) {
        if (*func_002591D0() != 0)
            func_00263BA8(func_002591D0(), 2);
    } else if (st != 1) {
        char buf[0x100];
        buf[0] = 0;
        cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3200, D_004A3218);
        *(float*)(self + 0xE0) = 20.0f;
        // PORT: function pointer passed through func_003E8B10's int parameter.
        *(int*)(self + 0x40) = func_003E8B10(*(void**)(self + 0x54), 0x7175696B, buf, (int)func_00268E78, self);
    }
    *(int*)self = 1;
    int type = 0xE7;
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = type;
    *(void***)((char*)m + 0x4) = D_004812B0;
    post_EED8(self, m);
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];

struct sMsgListNodeK2e {
    sMsgListNodeK2e* next;
    sMsgListNodeK2e* prev;
    void* data;
};

struct sMsgListIterK2e {
    sMsgListNodeK2e* node;
    sMsgListIterK2e(sMsgListNodeK2e* x) : node(x) {}
    sMsgListIterK2e(const sMsgListIterK2e& x) : node(x.node) {}
};

static inline sMsgListIterK2e sMsgListK2e_insert(sMsgListIterK2e pos, void* const& x)
{
    sMsgListNodeK2e* tmp = (sMsgListNodeK2e*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern void* D_00481290[];

extern "C" void func_0025F030(char* self, char* msg)
{
    if (*(int*)(msg + 0x8) == 0) {
        if (*(int*)self == 0x12)
            *(int*)self = 0x14;
    } else {
        *(int*)self = 1;
        int v = *(int*)(msg + 0x8);
        int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = v;
        void* mp = m;
        sMsgListK2e_insert(*(sMsgListNodeK2e**)(self + 0xF0), mp);
    }
}

//100%
extern "C" int func_003EE558(void*);

extern "C" int func_0025F120(void* self)
{
    if (*(int*)self == 0) {
        return 0;
    }
    return func_003EE558(*(void**)((char*)self + 0x5C));
}

//100%
extern "C" void* func_003EE560(void*);

extern "C" void* func_0025F150(void* self)
{
    if (*(int*)self == 0) {
        return 0;
    }
    return (char*)func_003EE560(*(void**)((char*)self + 0x5C)) + 0x1C;
}

//100%
extern "C" void* func_003EE560(void*);

static inline short getFlags(void* p)
{
    return *(short*)((char*)p + 0xA);
}

extern "C" int func_0025F180(void* self)
{
    if (*(int*)self == 0) {
        return 0;
    }
    return getFlags(func_003EE560(*(void**)((char*)self + 0x5C))) & 1;
}

//100%
extern "C" int func_003EE558(void*);

extern "C" int func_0025F1B0(void* self)
{
    if (*(int*)self == 0) {
        return 0;
    }
    return func_003EE558(*(void**)((char*)self + 0x60));
}

//100%
extern char D_004A2ED0[];
// PORT: the unit declares func_003EE560 with one parameter; this caller passes (list, index).
void* func_003EE560_2(void* list, int idx) __asm__("func_003EE560");

extern "C" char* func_0025F1E0(void* self, int idx, int* outFlag)
{
    if (*(int*)self == 0) {
        return 0;
    }
    char* p = (char*)func_003EE560_2(*(void**)((char*)self + 0x60), idx);
    if (p != 0) {
        if (outFlag != 0) {
            *outFlag = (*(int*)(p + 0x4) >> 21) & 1;
        }
        return p + 8;
    }
    return D_004A2ED0;
}

//100%
extern "C" int func_0025F248(void* self)
{
    void* p;
    if (*(int*)self == 0) {
        return 0;
    }
    p = func_003EE560(*(void**)((char*)self + 0x60));
    if (p != 0) {
        return (*(int*)((char*)p + 0x4) >> 21) & 1;
    }
    return 0;
}

//100%
extern char D_004A2F30[];
extern "C" void* func_003EE560(void*);
extern "C" int atoi(const char* s);
extern "C" int cDirtysock_tag_TagFieldGetStructure(const char* tag, void* data, int len, const char* fmt);

struct sDsPeerK2 {
    char pad_0x00[0x28];
    char name[0xC];      // 0x28
    int addr;            // 0x34
    char record[1];      // 0x38
};

struct sDsPeerInfoK2 {
    int addr;            // 0x0
    int a;               // 0x4
    int total;           // 0x8
    int b;               // 0xC
    int nameLen;         // 0x10
};

extern "C" void func_0025F288(void* self, int a1, sDsPeerInfoK2* out)
{
    if (*(int*)self != 0) {
        int st[16];
        const char* rec;
        sDsPeerK2* e = (sDsPeerK2*)func_003EE560(*(void**)((char*)self + 0x60));
        if (e != 0 && e->record != 0) {
            rec = e->record;
            out->addr = e->addr;
            out->nameLen = atoi(e->name);
        } else {
            out->addr = 0;
            rec = 0;
            out->nameLen = 0;
        }
        cDirtysock_tag_TagFieldGetStructure(rec, st, 0x40, D_004A2F30);
        out->a = st[2];
        out->total = st[2] + st[3] + st[4];
        out->b = st[6];
    }
}

INCLUDE_ASM("dirtysock/tagsunk", func_0025F338);

//100%
extern char D_004A2F30[];
extern "C" void* func_003EE560(void*);
extern "C" int cDirtysock_tag_TagFieldGetStructure(const char* tag, void* data, int len, const char* fmt);

struct sDsSlotSessK2b {
    int active;                  // 0x0
    char pad_0x04[0xF8 - 0x4];
    int slot;                    // 0xF8
    char pad_0xFC[0x1EC - 0xFC];
    void* handles[29];           // 0x1EC
};

extern "C" void* func_0025F388(sDsSlotSessK2b* self, int a1, int* outA, int* outB)
{
    if (self->active == 0)
        return 0;
    char* e = (char*)func_003EE560(self->handles[self->slot]);
    if (e != 0) {
        int st[2];
        cDirtysock_tag_TagFieldGetStructure(e + 0x28, st, 8, D_004A2F30);
        *outB = st[1];
        if (self->slot != 0)
            *outA = st[0];
        else
            *outA = *(int*)e;
    }
    return e;
}

//100%
extern "C" char* func_003E8A70(void* p, int tag);
extern "C" bool LobbyMan_IsInRoom(void* self)
{
    char* s;
    if (*(int*)self == 0) {
        return false;
    }
    s = func_003E8A70(*(void**)((char*)self + 0x54), 0x726F6F6D);
    return s != 0 && *s != 0;
}

extern "C" int func_0025F4C0(void* self, char* entry, int a);

extern "C" int LobbyMan_ChallengeRoomUser(void* self, int idx, int a)
{
    return func_0025F4C0(self, func_0025F1E0(self, idx, 0), a);
}

INCLUDE_ASM("dirtysock/tagsunk", func_0025F4C0);

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern "C" void func_003E8D70(void* p, int a);
extern "C" void LobbyMan_ResetChalState(void* self);
extern "C" void func_0025F740(void* self, int type);
void* LobbyMan_SendAbortChal(void* self);

struct sMsgListNodeF628 {
    sMsgListNodeF628* next;
    sMsgListNodeF628* prev;
    void* data;
};

struct sMsgListIterF628 {
    sMsgListNodeF628* node;
    sMsgListIterF628(sMsgListNodeF628* x) : node(x) {}
    sMsgListIterF628(const sMsgListIterF628& x) : node(x.node) {}
};

static inline sMsgListIterF628 sMsgListF628_insert(sMsgListIterF628 pos, void* const& x)
{
    sMsgListNodeF628* tmp = (sMsgListNodeF628*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025F628(void* selfp, int notify, int flag)
{
    char* self = (char*)selfp;
    int st = *(int*)self;
    if (st != 0) {
        if (st == 0x15 || st == 0x16 || st == 0x18) {
            if (flag)
                LobbyMan_SendAbortChal(self);
            func_003E8D70(*(void**)(self + 0x54), *(int*)(self + 0x40));
            LobbyMan_ResetChalState(self);
        } else if (st == 0x19) {
            func_0025F740(self, 0);
        }
        if (notify) {
            int type = 0xEE;
            int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
            m[0] = type;
            *(void***)((char*)m + 0x4) = D_004812B0;
            void* mp = m;
            sMsgListF628_insert(*(sMsgListNodeF628**)(self + 0xF0), mp);
        }
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_004A3108[];
extern char D_004A3218[];

struct sMsgListNodeF740 {
    sMsgListNodeF740* next;
    sMsgListNodeF740* prev;
    void* data;
};

struct sMsgListIterF740 {
    sMsgListNodeF740* node;
    sMsgListIterF740(sMsgListNodeF740* x) : node(x) {}
    sMsgListIterF740(const sMsgListIterF740& x) : node(x.node) {}
};

static inline sMsgListIterF740 sMsgListF740_insert(sMsgListIterF740 pos, void* const& x)
{
    sMsgListNodeF740* tmp = (sMsgListNodeF740*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_0025F740(void* selfp, int type)
{
    char* self = (char*)selfp;
    if (*(int*)self != 0) {
        if (*(int*)self == 0x19) {
            char buf[0x100];
            *(float*)(self + 0xE0) = 20.0f;
            buf[0] = 0;
            cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3108, D_004A3218);
            func_003E8B10(*(void**)(self + 0x54), 0x6368616C, buf, 0, 0);
            *(int*)self = 1;
        }
        if (type != 0) {
            int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
            m[0] = type;
            *(void***)((char*)m + 0x4) = D_004812B0;
            void* mp = m;
            sMsgListF740_insert(*(sMsgListNodeF740**)(self + 0xF0), mp);
        }
    }
}

//100%
extern char D_004A2F40[];
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);

extern "C" void LobbyMan_ResetChalState(void* self)
{
    func_003E8B10(*(void**)((char*)self + 0x54), 0x6368616C, D_004A2F40, 0, 0);
    *(int*)self = 1;
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_00481290[];
extern char D_004A2F40[];
extern char D_004A3220[];
extern char D_004A3228[];
extern char D_004A3230[];
extern char D_004A3238[];
extern float D_004A5154;
// PORT: TagFieldGetString really takes a 4th (default value) argument; the unit declares 3.
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");
void* LobbyMan_SendAbortChal(void* self);
extern "C" void LobbyMan_SendLockChal(void* self, int a1, int a2);
extern "C" int func_004165A8(void*, void*);

struct sMsgListNodeF8A0 {
    sMsgListNodeF8A0* next;
    sMsgListNodeF8A0* prev;
    void* data;
};

struct sMsgListIterF8A0 {
    sMsgListNodeF8A0* node;
    sMsgListIterF8A0(sMsgListNodeF8A0* x) : node(x) {}
    sMsgListIterF8A0(const sMsgListIterF8A0& x) : node(x.node) {}
};

static inline sMsgListIterF8A0 sMsgListF8A0_insert(sMsgListIterF8A0 pos, void* const& x)
{
    sMsgListNodeF8A0* tmp = (sMsgListNodeF8A0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void LobbyMan_OnChalReply(char* self, char* msg)
{
    char buf[16];
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3220), buf, 0x10, D_004A2F40);
    if (*(int*)(msg + 0x8) != 0) {
        if (*(int*)self == 0x15) {
            *(int*)self = 1;
            LobbyMan_SendAbortChal(self);
            int* m = (int*)operator new(0xC, D_00480488, 0x20000000, 0);
            m[0] = 0x102;
            *(void***)((char*)m + 0x4) = D_00481290;
            m[2] = *(int*)(msg + 0x8);
            void* mp = m;
            sMsgListF8A0_insert(*(sMsgListNodeF8A0**)(self + 0xF0), mp);
        }
    } else if (func_004165A8(buf, D_004A3228) == 0) {
        if (*(int*)self == 0x15)
            LobbyMan_SendLockChal(self, *(int*)(self + 0x98), 0x18);
    } else if (func_004165A8(buf, D_004A3230) == 0) {
    } else if (func_004165A8(buf, D_004A3238) == 0) {
        if (*(int*)self == 0x15) {
            *(int*)self = 0x18;
            *(float*)(self + 0xE0) = 20.0f;
            D_004A5154 = 20.0f;
        }
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A3108[];
extern char D_004A2F68[];
extern char D_004A3240[];
extern "C" void func_00268EA0(void* self, void* a1, int a2);

extern "C" void LobbyMan_ChalRequestHost(void* self, const char* name)
{
    char buf[0x100];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3108, name);
    cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A2F68, D_004A3240);
    *(int*)self = 1;
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 0x15, 0x6368616C, buf, (int)func_00268EA0, 20.0f);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern char D_004A3108[];
extern char D_004A2F68[];
extern char D_004A3250[];
extern "C" void func_00268EA0(void* self, void* a1, int a2);

extern "C" void LobbyMan_ChalRequestJoin(void* self, const char* name)
{
    char buf[0x100];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3108, name);
    cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A2F68, D_004A3250);
    *(int*)self = 1;
    // PORT: function pointer passed through LobbyMan_SendRequest's int parameter.
    LobbyMan_SendRequest(self, 0x18, 0x6368616C, buf, (int)func_00268EA0, 20.0f);
}

//100%
extern "C" void LobbyMan_SendLockChal(void* self, int a1, int a2);

extern "C" void func_0025FB58(void* self, int a1, int a2)
{
    if (*(int*)self != 0) {
        *(int*)((char*)self + 0xA4) = a2;
        LobbyMan_SendLockChal(self, a1, 0x17);
    }
}

//100%
extern char D_004A3258[];
extern char D_004A3010[];
extern char D_004A3260[];
extern "C" int cDirtysock_tag_TagFieldSetFlags(char* record, int len, const char* name, int value);
extern "C" void func_00268EC8(void* self, void* a1, int a2);

// PORT: a1 carries a string pointer in an int (the unit's declaration).
extern "C" void* LobbyMan_SendPrivateMessage(void* self, int a1, void* a2)
{
    char buf[0x100];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3258, (const char*)a1);
    cDirtysock_tag_TagFieldSetString(buf, 0x100, D_004A3010, (const char*)a2);
    cDirtysock_tag_TagFieldSetFlags(buf, 0x100, D_004A3260, 0x40004000);
    // PORT: function pointer passed through func_003E8B10's int parameter.
    return (void*)func_003E8B10(*(void**)((char*)self + 0x54), 0x6D657367, buf, (int)func_00268EC8, self);
}

//100%
void LobbyMan_OnMesgReply(void* self)
{
}

extern void* D_004A3270[];
extern "C" void* LobbyMan_SendPrivateMessage(void*, int, void*);

//100%
void* LobbyMan_SendDecline(void* self, int a1)
{
    return LobbyMan_SendPrivateMessage(self, a1, (void*)D_004A3270);
}

extern void* D_004807F8[];
extern "C" void* LobbyMan_SendPrivateMessage(void*, int, void*);

//100%
void* LobbyMan_SendAbortChal(void* self)
{
    return LobbyMan_SendPrivateMessage(self, *(int*)((char*)self + 0x98), (void*)D_004807F8);
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_00480910[];
extern float D_004A5154;

struct sMsgListNode_0025FC70 {
    sMsgListNode_0025FC70* next;
    sMsgListNode_0025FC70* prev;
    void* data;
};

struct sMsgListIter_0025FC70 {
    sMsgListNode_0025FC70* node;
    sMsgListIter_0025FC70(sMsgListNode_0025FC70* x) : node(x) {}
    sMsgListIter_0025FC70(const sMsgListIter_0025FC70& x) : node(x.node) {}
};

static inline sMsgListIter_0025FC70 sMsgList_0025FC70_insert(sMsgListIter_0025FC70 pos, void* const& x)
{
    sMsgListNode_0025FC70* tmp = (sMsgListNode_0025FC70*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void LobbyMan_SendLockChal(void* self, int a1, int a2)
{
    LobbyMan_SendPrivateMessage(self, a1, D_00480910);
    int kind = 0x110;
    *(int*)self = a2;
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    m[0] = kind;
    *(void***)((char*)m + 0x4) = D_004812B0;
    void* mp = m;
    sMsgList_0025FC70_insert(*(sMsgListNode_0025FC70**)((char*)self + 0xF0), mp);
    *(float*)((char*)self + 0xE0) = 20.0f;
    D_004A5154 = 21.0f;
}

INCLUDE_ASM("dirtysock/tagsunk", func_0025FD50);

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern void* D_004A28A8;
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_00481290[];
extern int D_00534B34[];

struct sMsgListNode0C68 {
    sMsgListNode0C68* next;
    sMsgListNode0C68* prev;
    void* data;
};

struct sMsgListIter0C68 {
    sMsgListNode0C68* node;
    sMsgListIter0C68(sMsgListNode0C68* x) : node(x) {}
    sMsgListIter0C68(const sMsgListIter0C68& x) : node(x.node) {}
};

static inline sMsgListIter0C68 sMsgList0C68_insert(sMsgListIter0C68 pos, void* const& x)
{
    sMsgListNode0C68* tmp = (sMsgListNode0C68*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_0C68(char* lst, void* msg)
{
    void* mp = msg;
    sMsgList0C68_insert(*(sMsgListNode0C68**)(lst + 4), mp);
}

extern "C" void func_00260C68(char* self, char* msg)
{
    cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
    if (*(int*)(msg + 0x8) == 0 || (*(int*)(msg + 0x8) == 0x72616E6B && D_00534B34[0] == 0)) {
        int type = 0x101;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = type;
        *(void***)((char*)m + 0x4) = D_004812B0;
        post_0C68(self + 0xEC, m);
    } else {
        int err = *(int*)(msg + 0x8);
        char* lst = self + 0xEC;
        int* m = (int*)cMemMan_alloc(0xC, D_00480488, 0x20000000, 0);
        m[0] = 0x102;
        *(void***)((char*)m + 0x4) = D_004812B0;
        *(void***)((char*)m + 0x4) = D_00481290;
        m[2] = err;
        post_0C68(lst, m);
        int type = 0x101;
        int* m2 = (int*)cMemMan_alloc(8, D_00480488, 0x20000000, 0);
        *(void***)((char*)m2 + 0x4) = D_004812B0;
        m2[0] = type;
        post_0C68(lst, m2);
    }
}

//100%
extern "C" void cBXString__cBXString(void* self, int flags);
extern "C" void* cBXString_cBXString1(void* self, void* other);
extern "C" void* cBXString_cBXString2(void* self, const char* s);
extern "C" void func_003194A8(void* str, const char* fmt, ...);
extern void* D_004A3E90;
extern char D_00480E10[];
extern char D_004A3320[];
extern char D_00480E20[];

struct sBXStr_00260E50 {
    char* p;
};

// Builds the display name of a 4-character tag.
extern "C" void* LobbyMan_GetErrorString(void* ret, void* self, unsigned int tag)
{
    switch (tag)
    {
    case 0x6475706C:
        cBXString_cBXString2(ret, D_00480E10);
        break;
    case 0x74696D65:
        cBXString_cBXString2(ret, D_004A3320);
        break;
    default:
    {
        sBXStr_00260E50 s;
        s.p = (char*)D_004A3E90;
        func_003194A8(&s, D_00480E20, tag, tag >> 24, (tag >> 16) & 0xFF, (tag >> 8) & 0xFF, tag & 0xFF);
        cBXString_cBXString1(ret, &s);
        cBXString__cBXString(&s, 2);
        break;
    }
    }
    return ret;
}

//100%
extern "C" void cBXString_Reset(void* self);

extern "C" void func_00260F10(void* self)
{
    cBXString_Reset((char*)self + 0x260);
    cBXString_Reset((char*)self + 0x264);
    cBXString_Reset((char*)self + 0x268);
    cBXString_Reset((char*)self + 0x26C);
    cBXString_Reset((char*)self + 0x270);
    *(int*)((char*)self + 0x298) = 1;
    *(int*)((char*)self + 0x29C) = 1;
    *(int*)((char*)self + 0x288) = 1;
    *(int*)((char*)self + 0x294) = 0;
    *(int*)((char*)self + 0x28C) = 1;
    *(int*)((char*)self + 0x290) = 0x7C1;
    *(int*)((char*)self + 0x2A0) = 0;
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480E48[];
extern void* D_004A3E90;
extern void* D_004A3328;

// Creates the memory-card manager singleton (D_004A3328).
extern "C" void func_00260F80(void)
{
    // An unused 32-byte local is needed to reproduce the 0x30-byte frame.
    int unused[8];
    char* m = (char*)operator new(0xF0, D_00480E48, 0x20000000, 0);
    *(int*)(m + 0x40) = -1;
    *(int*)(m + 0xA4) = 0x15180;
    *(void**)(m + 0xEC) = D_004A3E90;
    *(int*)(m + 0xAC) = 0;
    *(int*)(m + 0xB0) = 0;
    *(int*)(m + 0xB4) = 0;
    *(int*)(m + 0xBC) = 0;
    *(int*)(m + 0xC0) = 0;
    *(int*)(m + 0xC4) = 0;
    *(int*)(m + 0xC8) = 0;
    *(int*)(m + 0xCC) = 0;
    *(int*)(m + 0xD0) = 0;
    *(int*)(m + 0xD8) = 0;
    *(int*)(m + 0xDC) = 0;
    *(int*)(m + 0xE0) = 0;
    *(int*)(m + 0xE4) = 0;
    *(int*)(m + 0xE8) = 0;
    D_004A3328 = m;
}

//100%
extern void* D_004A3328;
void func_00261058(void* self);
struct sVec261070;
extern "C" void func_00261070(sVec261070* self);
extern "C" void func_00261408(void* self);
extern "C" void BuddyMan_dtor(void* self, int flags);

extern "C" void func_00261008(void)
{
    if (D_004A3328 != 0) {
        func_00261058(D_004A3328);
        func_00261070((sVec261070*)D_004A3328);
        func_00261408(D_004A3328);
        if (D_004A3328 != 0) {
            BuddyMan_dtor(D_004A3328, 3);
        }
        D_004A3328 = 0;
    }
}

//100%
void func_00261058(void* self)
{
    *(char*)self = 0;
    *(int*)((char*)self + 0x40) = -1;
    *(char*)((char*)self + 0x44) = 0;
    *(char*)((char*)self + 0x64) = 0;
}

//100%
struct sVE261070 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sObj261070 {
    char pad[0xC];
    sVE261070* vt;
};

struct sVec261070 {
    char pad[0xAC];
    sObj261070** begin;
    sObj261070** end;
};

extern "C" void func_00261070(sVec261070* self)
{
    while (self->begin != self->end) {
        sObj261070* p = self->end[-1];
        self->end--;
        if (p != 0) {
            p->vt[1].fn((char*)p + p->vt[1].delta, 3);
        }
    }
}

//100%
extern void* D_004A3328;
extern void* D_004A3028;
extern "C" void func_00260F80(void);
extern "C" int func_00261460(void* p);
extern "C" void func_002613C8(void* p);
extern "C" void func_0025B800(void* self);
extern "C" int func_00262938(void* self);
extern "C" void* func_00263630(void* self, unsigned int i);
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
extern "C" void func_00261EF8(void* self, int a1, int a2, void* out);

static inline void* Mgr_2610D0()
{
    if (D_004A3328 == 0)
        func_00260F80();
    if (func_00261460(D_004A3328) == 0)
        func_002613C8(D_004A3328);
    if (D_004A3328 == 0)
        func_0025B800(D_004A3028);
    return D_004A3328;
}

extern "C" void BuddyMan_AddMessageSendersToRoster()
{
    for (int i = 0; i < func_00262938(Mgr_2610D0()); i++)
    {
        int* e = (int*)func_00263630(Mgr_2610D0(), i);
        if (BuddyMan_FindRosterEntry(Mgr_2610D0(), *e) < 0)
        {
            int out;
            func_00261EF8(Mgr_2610D0(), *e, 2, &out);
        }
    }
}

//100%
extern "C" void cBXString__cBXString(void* self, int flags);
extern "C" void* cBXString_cBXString4(void* self, const char* str);
extern "C" void* cBXString_Concat(void* self, const char* str);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" const char* LobbyMan_GetLanguage();
extern "C" void func_002614E8(void* self, void* a1);
extern "C" void func_003F0818(void* p, const char* a1, int tag, const char* a3, int a4);
extern "C" void func_003F08E8(void* p, const char* name, int a2, int a3, const char* s1, const char* s2, void* cb, void* user);
extern "C" void func_00268F18(void* self, void* a1, int a2);
extern void* D_004A3E90;
extern char D_004A3330[];
extern char D_004A3338[];

struct sDsGame_261248 {
    char name[0x40];        // 0x0
    int idx;                // 0x40
    char a[0x20];           // 0x44
    char b[0x64];           // 0x64
    void* ctx;              // 0xC8
    int fCC;
    int fD0;                // 0xD0
    float fD4;              // 0xD4
    int fD8;                // 0xD8
    int fDC;                // 0xDC
    int fE0;                // 0xE0
};

struct sBXStr_261248 {
    char* p;
    sBXStr_261248() : p((char*)D_004A3E90) {}
    sBXStr_261248(const sBXStr_261248& o) : p(o.p) {}
};

// PORT: the unit declares (void*, void*, int, void*, void*, int); the last int is really a string pointer.
extern "C" void BuddyMan_Connect(void* self_, void* name_, int a2, void* a3_, void* a4_, int a5_)
{
    char* self = (char*)self_;
    const char* name = (const char*)name_;
    const char* a3 = (const char*)a3_;
    const char* a4 = (const char*)a4_;
    const char* a5 = (const char*)a5_;
    if (*(void**)(self + 0xC8) == 0)
    {
        func_002614E8(self, (void*)a5);
        func_003F0818(*(void**)(self + 0xC8), a5, 0x73737833, LobbyMan_GetLanguage(), 0);
    }
    strcpy(self, name);
    *(int*)(self + 0x40) = a2;
    strcpy(self + 0x44, a3);
    strcpy(self + 0x64, a4);
    sDsGame_261248* g = (sDsGame_261248*)self;
    g->fD0 = 0;
    g->fD4 = 30.0f;
    g->fD8 = 1;
    g->fDC = 0;
    g->fE0 = 0;
    sBXStr_261248 s1;
    cBXString_cBXString4(&s1, a3);
    cBXString_Concat(&s1, D_004A3330);
    cBXString_Concat(&s1, a4);
    sBXStr_261248 s2;
    cBXString_cBXString4(&s2, D_004A3338);
    cBXString_Concat(&s2, a5);
    cBXString_cBXString4(self + 0xEC, a5);
    func_003F08E8(*(void**)(self + 0xC8), name, a2, 0x1E, s1.p, s2.p, (void*)func_00268F18, self);
    cBXString__cBXString(&s2, 2);
    cBXString__cBXString(&s1, 2);
}

//100%
extern "C" void BuddyMan_Connect(void* self, void* self2, int idx, void* a, void* b, int c);
extern "C" void func_002613C8(void* self)
{
    int idx = *(int*)((char*)self + 0x40);
    if (idx >= 0) {
        bool ok = !*(bool*)((char*)self + 0xD8);
        if (ok) {
            BuddyMan_Connect(self, self, idx, (char*)self + 0x44, (char*)self + 0x64, *(int*)((char*)self + 0xEC));
        }
    }
}

//100%
extern "C" void func_00262768(void* self, int a1, int a2, int a3, int a4, int a5);
extern "C" void BuddyMan_DestroyApi(void* self);

extern "C" void func_00261408(void* self)
{
    func_00262768(self, 0, 1, 0, 0, 0);
    BuddyMan_DestroyApi(self);
    *(int*)((char*)self + 0xD8) = 0;
    *(int*)((char*)self + 0xD0) = 0;
    *(int*)((char*)self + 0xDC) = 0;
    *(int*)((char*)self + 0xE0) = 0;
    *(int*)((char*)self + 0xE8) = 0;
}

INCLUDE_ASM("dirtysock/tagsunk", func_00261460);

//100%
extern "C" void func_003F17D8(void* p);
extern "C" void func_00261408(void* self);

extern "C" void BuddyMan_Update(void* self)
{
    void* p = *(void**)((char*)self + 0xC8);
    if (p != 0) {
        func_003F17D8(p);
        if (*(int*)((char*)self + 0xDC) != 0) {
            func_00261408(self);
            *(int*)((char*)self + 0xDC) = 0;
        }
    }
}

extern "C" void func_002614E0()
{
}

//100%
extern char D_00480E58[];
extern "C" void func_00268F40(void* self);
extern "C" void* func_003F0710(void* a, const char* name);
extern "C" void func_003F17C8(void* h, void (*cb)(void*), void* user);

extern "C" void func_002614E8(void* self, void* a1)
{
    void* h = func_003F0710(a1, D_00480E58);
    *(void**)((char*)self + 0xC8) = h;
    func_003F17C8(h, func_00268F40, self);
}

//100%
extern void* D_004A3028;
// PORT: callee defined as returning void* in this unit; called here as void.
void LobbyMan_SendDecline_v(void* self, int a1) __asm__("LobbyMan_SendDecline__FPvi");
extern "C" void func_003F0BE0(void* p);
extern "C" void func_003F07A0(void* p);

struct sVE261530 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sObj261530 {
    int id;
    char pad[0x38];
    sVE261530* vt;
};

struct sMgr261530 {
    char pad[0xBC];
    sObj261530** begin;
    sObj261530** end;
    char pad2[4];
    void* h;
    int cc;
};

extern "C" void BuddyMan_DestroyApi(void* vself)
{
    sMgr261530* self = (sMgr261530*)vself;
    if (self->h != 0) {
        while (self->begin != self->end) {
            sObj261530* p = self->end[-1];
            LobbyMan_SendDecline_v(D_004A3028, p->id);
            self->end--;
            if (p != 0) {
                p->vt[1].fn((char*)p + p->vt[1].delta, 3);
            }
        }
        func_003F0BE0(self->h);
        func_003F07A0(self->h);
        self->h = 0;
        self->cc = 0;
    }
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_004A3028;
extern "C" void* func_003F0C90(void* h, void* cb, void* user);
extern "C" void func_003EE5A0(void* h, int a, int b, void* cb);
extern "C" void func_00262768(void* self, int a1, int a2, int a3, int a4, int a5);
extern "C" void func_00268F68(void);
extern "C" int BuddyMan_RosterCompare(void* self, int a1, void* a, void* b);

struct sMsgListNode15C8 {
    sMsgListNode15C8* next;
    sMsgListNode15C8* prev;
    void* data;
};

struct sMsgListIter15C8 {
    sMsgListNode15C8* node;
    sMsgListIter15C8(sMsgListNode15C8* x) : node(x) {}
    sMsgListIter15C8(const sMsgListIter15C8& x) : node(x.node) {}
};

static inline sMsgListIter15C8 sMsgList15C8_insert(sMsgListIter15C8 pos, void* const& x)
{
    sMsgListNode15C8* tmp = (sMsgListNode15C8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_15C8(char* owner, void* msg)
{
    void* mp = msg;
    sMsgList15C8_insert(*(sMsgListNode15C8**)(owner + 0xF0), mp);
}

extern "C" void func_002615C8(char* self, int* msg)
{
    switch (msg[0]) {
    case 0x636F6E6E:
        {
            int s = msg[1];
            if (s == 2) {
                *(int*)(self + 0xDC) = 1;
                if (*(int*)(self + 0xD0) == 0)
                    *(int*)(self + 0xD0) = 1;
            } else if (s == 6) {
                *(int*)(self + 0xE8) = 0;
                *(int*)(self + 0xDC) = 1;
                if (*(int*)(self + 0xD0) == 0)
                    *(int*)(self + 0xD0) = 1;
            } else if (s == 4) {
                *(int*)(self + 0xDC) = 1;
                if (*(int*)(self + 0xD0) == 0)
                    *(int*)(self + 0xD0) = 1;
            } else if (s == 3) {
                *(int*)(self + 0xDC) = 1;
                if (*(int*)(self + 0xD0) == 0)
                    *(int*)(self + 0xD0) = 1;
            }
        }
        break;
    case 0x61757468:
        if (msg[2] == 0) {
            // PORT: function pointers passed as callbacks.
            *(void**)(self + 0xCC) = func_003F0C90(*(void**)(self + 0xC8), (void*)func_00268F68, self);
            func_003EE5A0(*(void**)(self + 0xCC), 0, 0, (void*)BuddyMan_RosterCompare);
            func_00262768(self, 1, 0, 0, 0, 0);
            *(int*)(self + 0xD8) = 0;
            *(int*)(self + 0xE0) = 1;
        } else {
            char* owner = (char*)D_004A3028;
            int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
            *(void***)((char*)m + 0x4) = D_004812B0;
            m[0] = 0x104;
            post_15C8(owner, m);
            int r = msg[2];
            *(int*)(self + 0xDC) = 1;
            *(int*)(self + 0xD0) = r;
        }
        break;
    }
}

INCLUDE_ASM("dirtysock/tagsunk", func_00261770);

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_004A3028;

struct sMsgListNode_002618C0 {
    sMsgListNode_002618C0* next;
    sMsgListNode_002618C0* prev;
    void* data;
};

struct sMsgListIter_002618C0 {
    sMsgListNode_002618C0* node;
    sMsgListIter_002618C0(sMsgListNode_002618C0* x) : node(x) {}
    sMsgListIter_002618C0(const sMsgListIter_002618C0& x) : node(x.node) {}
};

static inline sMsgListIter_002618C0 sMsgList_002618C0_insert(sMsgListIter_002618C0 pos, void* const& x)
{
    sMsgListNode_002618C0* tmp = (sMsgListNode_002618C0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void BuddyMan_OnRosterAddReply(int unused)
{
    char* g = (char*)D_004A3028;
    int* m = (int*)cMemMan_alloc(8, D_00480488, 0x20000000, 0);
    *(void***)((char*)m + 0x4) = D_004812B0;
    m[0] = 0x10A;
    void* mp = m;
    sMsgList_002618C0_insert(*(sMsgListNode_002618C0**)(g + 0xF0), mp);
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_004A3028;

struct sMsgListNode_00261970 {
    sMsgListNode_00261970* next;
    sMsgListNode_00261970* prev;
    void* data;
};

struct sMsgListIter_00261970 {
    sMsgListNode_00261970* node;
    sMsgListIter_00261970(sMsgListNode_00261970* x) : node(x) {}
    sMsgListIter_00261970(const sMsgListIter_00261970& x) : node(x.node) {}
};

static inline sMsgListIter_00261970 sMsgList_00261970_insert(sMsgListIter_00261970 pos, void* const& x)
{
    sMsgListNode_00261970* tmp = (sMsgListNode_00261970*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

struct sMsg_00261970 {
    int kind;
    void** vt;
};

extern "C" void BuddyMan_OnRosterRemoveReply(int unused)
{
    char* g = (char*)D_004A3028;
    sMsg_00261970* m = (sMsg_00261970*)cMemMan_alloc(8, D_00480488, 0x20000000, 0);
    m->vt = D_004812B0;
    m->kind = 0x10B;
    void* mp = m;
    sMsgList_00261970_insert(*(sMsgListNode_00261970**)(g + 0xF0), mp);
}

//100%
void BuddyMan_OnSendMessageReply(void* self)
{
}

//100%
// PORT: TagFieldGetUnk is called here with a 4th (default) argument left in $a3.
extern "C" void cDirtysock_tag_TagFieldGetUnk4(const char* tag, char* dst, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetUnk");
extern "C" int func_002623B0(void* self, int name);
extern "C" void BuddyMan_AddMessage(char* self, char* name, char* text, char* date);
extern "C" int BuddyMan_CountMessagesFrom(void* self, int name);
extern "C" void func_002635A8(void* self, int i);
extern "C" int func_003EDD70(const char* data, int* year, int* month, int* day, int* hour, int* min, int* sec, int offset);
extern "C" char* func_004162D0(char* d, const char* s);
extern char D_004A3358[];
extern char D_004A3360[];
extern char D_004A3368[];
extern char D_004A3370[];
extern char D_004A3378[];
extern char D_00480E68[];
extern char D_00480E78[];
extern char D_004A2ED0[];

struct sMsgListNode_00261A28 {
    sMsgListNode_00261A28* next;
    sMsgListNode_00261A28* prev;
    void* data;
};

struct sMsgListIter_00261A28 {
    sMsgListNode_00261A28* node;
    sMsgListIter_00261A28(sMsgListNode_00261A28* x) : node(x) {}
    sMsgListIter_00261A28(const sMsgListIter_00261A28& x) : node(x.node) {}
};

static inline sMsgListIter_00261A28 sMsgList_00261A28_insert(sMsgListIter_00261A28 pos, void* x)
{
    sMsgListNode_00261A28* tmp = (sMsgListNode_00261A28*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void sTagVec_00261A28_remove(char* self, char* name)
{
    for (unsigned int i = 0; i < (unsigned int)((*(int*)(self + 0xB0) - *(int*)(self + 0xAC)) >> 2); i++) {
        void* e = func_00263630(self, i);
        if (e != 0 && func_004165A8(*(void**)e, name) == 0) {
            func_002635A8(self, i);
            return;
        }
    }
}

struct sMsg_00261A28 {
    int kind;
    void** vt;
    sMsg_00261A28(int k) : kind(k), vt(D_004812B0) {}
};

extern "C" void BuddyMan_OnMessageReceived(char* self, char* msg)
{
    char raw[0x800];
    char text[0x8D0];
    char name[0x40];
    char date[0x40];
    char flag[0x10];
    int t0, t1, t2, t3, t4, t5;

    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3358), flag, 2, D_00480E68);
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3360), name, 0x40, D_00480E68);
    if (func_002623B0(self, (int)name))
        return;
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3368), text, 0x8CF, D_004A2ED0);
    cDirtysock_tag_TagFieldGetUnk4(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3370), raw, 0x800, D_00480E68);
    func_004162D0(text, raw);
    func_003EDD70(cDirtysock_tag_TagFieldFind(*(char**)(msg + 0xC), D_004A3378), &t0, &t1, &t2, &t3, &t4, &t5, 0);
    sprintf(date, D_00480E78, t1, t2, t0, t3, t4);
    BuddyMan_AddMessage(self, name, text, date);
    if (BuddyMan_CountMessagesFrom(self, (int)name) >= 0x1F) {
        sTagVec_00261A28_remove(self, name);
    }
    int kind = 0x109;
    char* g = (char*)D_004A3028;
    sMsg_00261A28* m = new (D_00480488, 0x20000000, 0) sMsg_00261A28(kind);
    sMsgList_00261A28_insert(*(sMsgListNode_00261A28**)(g + 0xF0), m);
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern char D_00480E98[];
extern void* D_0046D8C0[];
extern void* D_004A3028;
extern "C" int BuddyMan_IsBuddy(void* self, int a1);
extern "C" int func_002623B0(void* self, int a1);
extern "C" int func_00262438(void* self, int a1);
extern "C" int func_00262400(void* self, int a1);
extern "C" int func_00262598(void* self);
extern "C" void BuddyMan_RemoveTempEntryAt(char* self, int idx);
extern "C" int BuddyMan_AddRosterEntry(char* self, char* name, int kind, int* err, char* other);
struct sPtrVec7128;
extern "C" void BuddyMan_MessageVectorInsert(sPtrVec7128* self, void** pos, void* const& x);

struct sPtrVec1CD0 {
    void* alloc;
    void** start;
    void** finish;
    void** eos;
};

struct sOwner1CD0 {
    char pad[0xA8];
    sPtrVec1CD0 vec;    // 0xA8
};

static inline void sPtrVec1CD0_construct(void** p, void* const& v)
{
    if (p != 0)
        *p = v;
}

static inline void sOwner1CD0_push_back(sOwner1CD0* s, void* const& x)
{
    sPtrVec1CD0* v = &s->vec;
    if (s->vec.finish != s->vec.eos) {
        sPtrVec1CD0_construct(v->finish, x);
        ++s->vec.finish;
    } else {
        BuddyMan_MessageVectorInsert((sPtrVec7128*)v, s->vec.finish, x);
    }
}

struct sMsgListNode1CD0 {
    sMsgListNode1CD0* next;
    sMsgListNode1CD0* prev;
    void* data;
};

struct sMsgListIter1CD0 {
    sMsgListNode1CD0* node;
    sMsgListIter1CD0(sMsgListNode1CD0* x) : node(x) {}
    sMsgListIter1CD0(const sMsgListIter1CD0& x) : node(x.node) {}
};

static inline sMsgListIter1CD0 sMsgList1CD0_insert(sMsgListIter1CD0 pos, void* const& x)
{
    sMsgListNode1CD0* tmp = (sMsgListNode1CD0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_1CD0(char* owner, void* msg)
{
    void* mp = msg;
    sMsgList1CD0_insert(*(sMsgListNode1CD0**)(owner + 0xF0), mp);
}

// PORT: name pointers passed through int parameters of some callees.
extern "C" void BuddyMan_AddMessage(char* self, char* name, char* a2, char* a3)
{
    if (BuddyMan_IsBuddy(self, (int)name) == 0
        && func_002623B0(self, (int)name) == 0
        && func_00262438(self, (int)name) == 0) {
        int err;
        BuddyMan_AddRosterEntry(self, name, 2, &err, 0);
        if (err == 2) {
            for (int i = 0; i < func_00262598(self); i++) {
                if (func_00262400(self, i)) {
                    BuddyMan_RemoveTempEntryAt(self, i);
                    break;
                }
            }
            BuddyMan_AddRosterEntry(self, name, 2, &err, 0);
            int type = 0x108;
            char* owner = (char*)D_004A3028;
            int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
            m[0] = type;
            *(void***)((char*)m + 0x4) = D_004812B0;
            post_1CD0(owner, m);
        }
    }
    char* obj = (char*)cMemMan_alloc(0x10, D_00480E98, 0x20000000, 0);
    *(void***)(obj + 0xC) = D_0046D8C0;
    cBXString_cBXString2(obj, name);
    cBXString_cBXString2(obj + 4, a2);
    cBXString_cBXString2(obj + 8, a3);
    void* o = obj;
    sOwner1CD0_push_back((sOwner1CD0*)self, o);
}

//100%
extern "C" void* func_003F14D8(void* h);
extern "C" int BuddyMan_AddRosterEntry(char* self, char* name, int kind, int* err, char* other);
extern "C" void func_00263018(void* self, void* name);
extern "C" int func_00263128(char* self, char* name);
extern "C" void func_003F11F8(void* h, void* e, void* cb, void* user, int timeout);
extern "C" void func_00268F90(void* self, void* a1, int a2);

// PORT: the unit declares (void*, int, int, void*); a1 carries the name pointer.
extern "C" void func_00261EF8(void* self_, int a1, int kind, void* out)
{
    char* self = (char*)self_;
    char* name = (char*)a1;
    int* err = (int*)out;
    char* e = (char*)func_003F14D8(*(void**)(self + 0xC8));
    if (e == 0) {
        BuddyMan_AddRosterEntry(self, name, kind, err, 0);
        if (*err == 0)
            *err = 0;
        return;
    }
    int flags = *(int*)(e + 0xA8);
    // PORT: function pointer passed as a callback argument.
    func_003F11F8(*(void**)(self + 0xC8), e, (void*)func_00268F90, self, 600);
    int has = func_00263128(self, name);
    switch (kind) {
    case 0:
        if (!(flags & 4)) {
            BuddyMan_AddRosterEntry(self, name, 0, err, e);
            if (*err != 0) {
                if (flags & 0x100000) {
                    int tmp;
                    BuddyMan_AddRosterEntry(self, name, 2, &tmp, e);
                }
                return;
            }
            if (flags & 0x100000)
                has = 0;
        }
        break;
    case 1:
        if (flags & 0x200)
            goto do2;
        BuddyMan_AddRosterEntry(self, name, 1, err, e);
        if (*err != 0) {
            if (has)
                func_00263018(self, name);
            return;
        }
        break;
    case 2:
        if (!(flags & 0x100000)) {
        do2:
            BuddyMan_AddRosterEntry(self, name, 2, err, e);
            if (*err != 0)
                return;
        }
        break;
    }
    if (has)
        func_00263018(self, name);
    *err = 0;
}

//100%
extern void* D_004A3028;
extern "C" int BuddyMan_CountPermanentEntries(void* self);
extern "C" int BuddyMan_CountTempEntries(void* self);
extern "C" int func_003F0E38(void* h, void* rec, void* cb, void* user, int timeout);
extern "C" void func_00268FB8(void* self, void* a1, int a2);

struct sTagsUnkReq20D8 {
    char name[0x20];   // 0x00
    char x20[0x20];    // 0x20
    char x40[0x68];    // 0x40
    int flags;         // 0xA8
    char pad[0x14];
};

extern "C" int BuddyMan_AddRosterEntry(char* self, char* name, int kind, int* err, char* other)
{
    sTagsUnkReq20D8 rec;
    if (func_0041AA88(*(void**)((char*)D_004A3028 + 0x80), name) == 0) {
        *err = 3;
        return 0;
    }
    int a = 0;
    int b = 0;
    if (other == 0) {
        a = 1;
        b = 1;
    } else if (*(int*)(other + 0xA8) & 0x100000) {
        a = 1;
    } else {
        b = 1;
    }
    strcpy(rec.name, name);
    strcpy(rec.x40, *(char**)(self + 0xEC));
    rec.x20[0] = 0;
    switch (kind) {
    case 0:
        if (BuddyMan_CountPermanentEntries(self) + a >= 0x29) {
            *err = 1;
            return 0;
        }
        rec.flags |= 4;
        break;
    case 1:
        if (BuddyMan_CountPermanentEntries(self) + a >= 0x29) {
            *err = 1;
            return 0;
        }
        rec.flags |= 0x200;
        break;
    case 2:
        if (BuddyMan_CountTempEntries(self) + b >= 0xB) {
            *err = 2;
            return 0;
        }
        rec.flags |= 0x100000;
        rec.flags |= 0x800000;
        break;
    }
    *err = 0;
    // PORT: function pointer passed as a callback argument.
    return func_003F0E38(*(void**)(self + 0xC8), &rec, (void*)func_00268FB8, self, 600);
}

//100%
extern "C" int func_00262400(void* self, int a1);
extern "C" int func_00262598(void* self);

extern "C" int BuddyMan_CountPermanentEntries(void* self)
{
    int n = 0;
    for (int i = 0; i < func_00262598(self); i++) {
        if (func_00262400(self, i) == 0)
            n++;
    }
    return n;
}

//100%
extern "C" int func_00262400(void* self, int a1);
extern "C" int func_00262598(void* self);

extern "C" int BuddyMan_CountTempEntries(void* self)
{
    int n = 0;
    for (int i = 0; i < func_00262598(self); i++) {
        if (func_00262400(self, i) != 0)
            n++;
    }
    return n;
}

//100%
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
// PORT: the unit declares BuddyMan_IsBuddyAt as `int (void*)`; this caller passes a
// second argument (it reaches BuddyMan_GetBuddyAt's callee in $a1). Bound by asm label.
int BuddyMan_IsBuddyAt_2(void* self, int a1) __asm__("BuddyMan_IsBuddyAt__FPv");

extern "C" int BuddyMan_IsBuddy(void* self, int a1)
{
    return BuddyMan_IsBuddyAt_2(self, BuddyMan_FindRosterEntry(self, a1));
}

extern "C" void* BuddyMan_GetBuddyAt(void* self);

//100%
int BuddyMan_IsBuddyAt(void* self)
{
    return (BuddyMan_GetBuddyAt(self) != 0);
}

//100%
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
// PORT: the unit declares BuddyMan_IsBlockedAt as `int (void*)`; this caller passes a
// second argument (it reaches BuddyMan_GetBlockedAt's callee in $a1). Bound by asm label.
int BuddyMan_IsBlockedAt_2(void* self, int a1) __asm__("BuddyMan_IsBlockedAt__FPv");

extern "C" int func_002623B0(void* self, int a1)
{
    return BuddyMan_IsBlockedAt_2(self, BuddyMan_FindRosterEntry(self, a1));
}

extern "C" void* BuddyMan_GetBlockedAt(void* self);

//100%
int BuddyMan_IsBlockedAt(void* self)
{
    return (BuddyMan_GetBlockedAt(self) != 0);
}

//100%
extern "C" void* func_002625C8(void* self, int idx);

extern "C" int func_00262400(void* self, int a1)
{
    void* p = func_002625C8(self, a1);
    if (p != 0) {
        return (*(int*)((char*)p + 0xA8) >> 20) & 1;
    }
    return 0;
}

//100%
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
extern "C" int func_00262400(void* self, int a1);

extern "C" int func_00262438(void* self, int a1)
{
    return func_00262400(self, BuddyMan_FindRosterEntry(self, a1));
}

//100%
extern "C" int func_004165A8(void*, void*);
extern "C" void* func_002625C8(void* self, int idx);

// PORT: a1 carries a name pointer in an int (the unit's declaration).
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1)
{
    int i;
    int n = func_00262598(self);
    for (i = 0; i < n; i++) {
        void* e = func_002625C8(self, i);
        if (e != 0 && func_004165A8(e, (void*)a1) == 0) {
            return i;
        }
    }
    return -1;
}

//100%
extern "C" void* func_002625C8(void* self, int idx);

extern "C" int func_002624F8(void* self, void** key)
{
    int i;
    int n;
    if (key == 0) {
        return -1;
    }
    n = func_00262598(self);
    for (i = 0; i < n; i++) {
        void* e = func_002625C8(self, i);
        if (e != 0 && func_0041AA88(*key, e) == 0) {
            return i;
        }
    }
    return -1;
}

//100%
extern "C" int func_003EE550(void*);

extern "C" int func_00262598(void* self)
{
    void* p = *(void**)((char*)self + 0xCC);
    if (p == 0) {
        return 0;
    }
    return func_003EE550(p);
}

//100%
extern "C" int func_00262598(void* self);
// PORT: the unit declares func_003EE560 with one parameter; this caller passes (list, index).
void* func_003EE560_2(void* list, int idx) __asm__("func_003EE560");

extern "C" void* func_002625C8(void* self, int idx)
{
    void* r;
    if (idx < 0 || func_00262598(self) < idx) {
        r = 0;
    } else {
        r = func_003EE560_2(*(void**)((char*)self + 0xCC), idx);
    }
    return r;
}

//100%
extern "C" void* func_002625C8(void* self, int idx);
// PORT: the unit declares BuddyMan_GetBuddyAt as `void* (void*)`; the body passes a second
// argument through to func_002625C8 in $a1. Bound by asm label.
void* BuddyMan_GetBuddyAt_2(void* self, int idx) __asm__("BuddyMan_GetBuddyAt");

void* BuddyMan_GetBuddyAt_2(void* self, int idx)
{
    void* p = func_002625C8(self, idx);
    if ((p != 0) && (*(int*)((char*)p + 0xA8) & 0x4)) {
        return p;
    }
    return 0;
}

//100%
extern "C" void* func_002625C8(void* self, int idx);
// PORT: the unit declares BuddyMan_GetBlockedAt as `void* (void*)`; the body passes a second
// argument through to func_002625C8 in $a1. Bound by asm label.
void* BuddyMan_GetBlockedAt_2(void* self, int idx) __asm__("BuddyMan_GetBlockedAt");

void* BuddyMan_GetBlockedAt_2(void* self, int idx)
{
    void* p = func_002625C8(self, idx);
    if ((p != 0) && (*(int*)((char*)p + 0xA8) & 0x200)) {
        return p;
    }
    return 0;
}

//100%
extern char D_004A2F40[];
extern char D_004A3358[];
extern char D_004A3360[];
extern char D_004A3368[];
extern char D_004A3370[];
extern char D_004A3390[];
extern char D_004A3398[];
extern "C" void func_00268FE0(void* self, void* a1, int a2);
extern "C" void func_003F16D8(void* ctx, char* buf, void* cb, void* user, int a4);

extern "C" void func_00262690(char* self, const char* name, int a2)
{
    char buf[0x1000];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x1000, D_004A3358, D_004A3390);
    cDirtysock_tag_TagFieldSetString(buf, 0x1000, D_004A3368, D_004A2F40);
    cDirtysock_tag_TagFieldSetString(buf, 0x1000, D_004A3360, name);
    cDirtysock_tag_TagFieldSetUnk(buf, 0x1000, D_004A3370, a2);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x1000, D_004A3398, *(int*)(self + 0xA4));
    func_003F16D8(*(void**)(self + 0xC8), buf, (void*)func_00268FE0, self, *(int*)(self + 0xA4));
}

//100%
extern "C" int cDirtysock_tag_TagFieldSetNumber(char* buf, int size, const char* key, int value);
extern "C" int cDirtysock_tag_TagFieldSetString(char* buf, int size, const char* key, const char* value);
extern "C" int BuddyMan_MapPresenceState(void* self, int sel);
extern "C" void func_003F1538(void* p);
extern "C" void func_003F1548(void* p, char* buf);
extern "C" void func_003F1578(void* p, const char* a, const char* b);
extern "C" void func_003F15C8(void* p, const char* name, int a2, int a3);
extern char D_004A31F8[];
extern char D_004A33A8[];
extern char D_004A33B0[];
extern char D_004A33B8[];
extern char D_004A33C0[];
extern char D_004A33C8[];
extern char D_00480EA8[];
extern char D_004A2F18[];

// PORT: the unit declares every argument as int; a3..a5 are really string pointers.
extern "C" void func_00262768(void* self_, int a1, int a2, int a3, int a4, int a5)
{
    char* self = (char*)self_;
    if (*(void**)(self + 0xC8) == 0)
        return;
    char buf[0x50];
    buf[0] = 0;
    cDirtysock_tag_TagFieldSetString(buf, 0x50, D_004A31F8, *(const char**)(self + 0xEC));
    cDirtysock_tag_TagFieldSetNumber(buf, 0x50, D_004A33A8, 3);
    cDirtysock_tag_TagFieldSetNumber(buf, 0x50, D_004A33B0, a2);
    if (a3 != 0)
    {
        cDirtysock_tag_TagFieldSetString(buf, 0x50, D_004A33B8, (const char*)a3);
        if (a4 != 0)
        {
            cDirtysock_tag_TagFieldSetString(buf, 0x50, D_004A33C0, (const char*)a4);
            if (a5 != 0)
                cDirtysock_tag_TagFieldSetString(buf, 0x50, D_004A33C8, (const char*)a5);
        }
    }
    func_003F1538(*(void**)(self + 0xC8));
    func_003F1548(*(void**)(self + 0xC8), buf);
    func_003F1578(*(void**)(self + 0xC8), D_00480EA8, D_004A2F18);
    const char* name = *(const char**)(self + 0xEC);
    func_003F15C8(*(void**)(self + 0xC8), name, BuddyMan_MapPresenceState(self, a1), 0x7D0);
}

//100%
extern "C" int BuddyMan_MapPresenceState(void* self, int sel)
{
    if (*(int*)((char*)self + 0xC8) == 0) {
        return -1;
    }
    switch (sel) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    }
    return -1;
}

//100%
extern "C" int func_00262938(void* self)
{
    return (*(int*)((char*)self + 0xb0) - *(int*)((char*)self + 0xac)) >> 2;
}

//100%
extern "C" void* func_00263630(void* self, unsigned int i);
extern "C" int func_004165A8(void*, void*);

static inline unsigned int sDsListK2_size(void* self)
{
    return *(void***)((char*)self + 0xB0) - *(void***)((char*)self + 0xAC);
}

// Counts the entries whose name matches entry `idx`'s name.
extern "C" int BuddyMan_CountMessagesFromAt(void* self, int idx)
{
    void* key = func_002625C8(self, idx);
    if (key == 0)
        return -1;
    int count = 0;
    unsigned int i;
    for (i = 0; i < sDsListK2_size(self); i++) {
        void** e = (void**)func_00263630(self, i);
        if (e != 0) {
            if (func_004165A8(*e, key) == 0)
                count++;
        }
    }
    return count;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
extern "C" int BuddyMan_CountMessagesFromAt(void* self, int a1);

extern "C" int BuddyMan_CountMessagesFrom(void* self, int a1)
{
    return BuddyMan_CountMessagesFromAt(self, BuddyMan_FindRosterEntry(self, a1));
}

//100%
extern "C" int func_004165A8(void*, void*);

extern "C" int func_00262A38(void* self, void* name)
{
    for (void*** it = *(void****)((char*)self + 0xAC); it != *(void****)((char*)self + 0xB0); it++) {
        if (func_004165A8(**it, name) == 0)
            return 1;
    }
    return 0;
}

extern "C" int func_004165A8(void*, void*);

extern "C" int func_00262AB0(void* self, void** key)
{
    void*** p = *(void****)((char*)self + 0xAC);
    if (p != *(void****)((char*)self + 0xB0)) {
        func_004165A8(**p, *key);
        return 1;
    }
    return 0;
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cBXString_cBXString2(void* self, const char* s);
extern "C" int BuddyMan_AddRosterEntry(char* self, char* name, int kind, int* err, char* other);
int BuddyMan_IsBlockedAt_2(void* self, int a1) __asm__("BuddyMan_IsBlockedAt__FPv");
extern "C" int func_00262400(void* self, int a1);
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
extern "C" int func_00262598(void* self);
extern "C" void BuddyMan_RemoveTempEntryAt(char* self, int idx);
extern "C" void func_00263018(void* self, void* name);
extern "C" int func_00263128(char* self, char* name);
extern "C" void* func_0041AA88(void*, void*);
struct sPtrVec72C8;
extern "C" void BuddyMan_ChallengerVectorInsert(sPtrVec72C8* self, void** pos, void* const& x);
extern char D_00480488[];
extern char D_004804A8[];
extern char D_00480EC0[];
extern char D_004810E0[];
extern void* D_004812B0[];
extern void* D_004A3028;

struct sMsgListNode_262AF0 {
    sMsgListNode_262AF0* next;
    sMsgListNode_262AF0* prev;
    void* data;
};

struct sMsgListIter_262AF0 {
    sMsgListNode_262AF0* node;
    sMsgListIter_262AF0(sMsgListNode_262AF0* x) : node(x) {}
    sMsgListIter_262AF0(const sMsgListIter_262AF0& x) : node(x.node) {}
};

static inline sMsgListIter_262AF0 sMsgList_262AF0_insert(sMsgListIter_262AF0 pos, void* const& x)
{
    sMsgListNode_262AF0* tmp = (sMsgListNode_262AF0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_262AF0(char* owner, void* msg)
{
    void* mp = msg;
    sMsgList_262AF0_insert(*(sMsgListNode_262AF0**)(owner + 0xF0), mp);
}

struct sObjVec_262AF0 {
    void* alloc;
    void** start;
    void** finish;
    void** eos;
};

static inline void construct_262AF0(void** p, void* const& x)
{
    if (p != 0)
        *p = x;
}

static inline void push_back_262AF0(char* o, sObjVec_262AF0* v, void* const& x)
{
    if (*(void***)(o + 0xC0) != *(void***)(o + 0xC4))
    {
        construct_262AF0(v->finish, x);
        ++*(void***)(o + 0xC0);
    }
    else
    {
        BuddyMan_ChallengerVectorInsert((sPtrVec72C8*)v, *(void***)(o + 0xC0), x);
    }
}

extern "C" void BuddyMan_OnChallengeReceived(char* self, char* name, int a2, int a3, int a4, int a5, int a6, int a7,
                              int s0, int s1, char* s2, int s3, int s4, int s5, int s6)
{
    if (func_0041AA88(*(void**)((char*)D_004A3028 + 0x80), name) == 0)
        return;
    while (func_00263128(self, name))
        func_00263018(self, name);
    int idx = BuddyMan_FindRosterEntry(self, (int)name);
    if (idx < 0)
    {
        int err;
        BuddyMan_AddRosterEntry(self, name, 2, &err, 0);
        if (err == 2)
        {
            int i;
            for (i = 0; i < func_00262598(self); i++)
            {
                if (func_00262400(self, i))
                {
                    BuddyMan_RemoveTempEntryAt(self, i);
                    break;
                }
            }
            int type = 0x108;
            BuddyMan_AddRosterEntry(self, name, 2, &err, 0);
            char* g = (char*)D_004A3028;
            int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
            m[0] = type;
            *(void***)((char*)m + 0x4) = D_004812B0;
            post_262AF0(g, m);
        }
    }
    else if (BuddyMan_IsBlockedAt_2(self, idx))
    {
        return;
    }
    char* obj = (char*)operator new(0x40, D_00480EC0, 0x20000000, 0);
    *(char**)(obj + 0x3C) = D_004810E0;
    cBXString_cBXString2(obj, name);
    cBXString_cBXString2(obj + 4, s2);
    *(int*)(obj + 0x8) = a2;
    *(int*)(obj + 0xC) = a3;
    *(int*)(obj + 0x10) = a4;
    *(int*)(obj + 0x14) = a5;
    *(int*)(obj + 0x18) = a6;
    *(int*)(obj + 0x1C) = a7;
    *(int*)(obj + 0x20) = s0;
    *(int*)(obj + 0x24) = s1;
    *(int*)(obj + 0x2C) = s3;
    *(int*)(obj + 0x30) = s4;
    *(int*)(obj + 0x34) = s5;
    *(int*)(obj + 0x28) = s6;
    void* op = obj;
    push_back_262AF0(self, (sObjVec_262AF0*)(self + 0xB8), op);
    char* g = (char*)D_004A3028;
    int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
    *(void***)((char*)m + 0x4) = D_004812B0;
    m[0] = 0xEC;
    post_262AF0(g, m);
}

//100%
static inline unsigned int BuddyMan_FindChallengerIndex_count(void* self)
{
    return *(void***)((char*)self + 0xC0) - *(void***)((char*)self + 0xBC);
}

static inline void** BuddyMan_FindChallengerIndex_at(void* self, unsigned int i)
{
    return *(void***)((char*)*(void***)((char*)self + 0xBC) + (i << 2));
}

extern "C" int BuddyMan_FindChallengerIndex(void* self, void* name)
{
    for (unsigned int i = 0; i < BuddyMan_FindChallengerIndex_count(self); i++) {
        void** e = BuddyMan_FindChallengerIndex_at(self, i);
        if (e != 0 && func_0041AA88(*e, name) == 0) {
            return i;
        }
    }
    return -1;
}

//100%
extern void* D_004A3028;
// PORT: callee defined as returning void* in this unit; called here as void.
void LobbyMan_SendDecline_v(void* self, int a1) __asm__("LobbyMan_SendDecline__FPvi");
extern "C" void cBXString__cBXString(void* self, int flags);
extern "C" void* cBXString_cBXString2(void* self, const char* s);
extern "C" int func_00262400(void* self, int a1);
extern "C" void* func_002625C8(void* self, int idx);
extern "C" int func_00262938(void* self);
extern "C" int func_00262A38(void* self, void* name);
extern "C" int BuddyMan_FindChallengerIndex(void* self, void* name);
extern "C" int func_00263128(char* self, char* name);
extern "C" void func_002635A8(void* self, int i);
extern "C" void* func_00263630(void* self, unsigned int i);
extern "C" void func_003F11F8(void* h, void* e, void* cb, void* user, int timeout);
extern "C" void* func_0041610C(void* dst, const void* src, unsigned int n);
extern "C" void* func_0041AA88(void*, void*);
extern "C" void func_00268F90(void* self, void* a1, int a2);

struct sBXStr_262EC0 {
    char* p;
};

struct sObjVec_262EC0 {
    void* alloc;
    void** mStart;
    void** mFinish;
};

static inline void** sObjVec_262EC0_copy(void** first, void** last, void** result)
{
    func_0041610C(result, first, (last - first) * sizeof(void*));
    return result + (last - first);
}

extern "C" void BuddyMan_RemoveTempEntryAt(char* self, int idx)
{
    if (func_00262400(self, idx) == 0)
        return;
    char* name = (char*)func_002625C8(self, idx);
    if (name == 0)
        return;
    sBXStr_262EC0 s;
    cBXString_cBXString2(&s, name);
    func_003F11F8(*(void**)(self + 0xC8), name, (void*)func_00268F90, self, 600);
    if (func_00262A38(self, s.p))
    {
        for (int i = func_00262938(self) - 1; i >= 0; i--)
        {
            void** e = (void**)func_00263630(self, i);
            if (e != 0 && func_0041AA88(*e, s.p) == 0)
                func_002635A8(self, i);
        }
    }
    if (func_00263128(self, s.p))
    {
        // PORT: the name is passed through an int parameter.
        LobbyMan_SendDecline_v(D_004A3028, (int)s.p);
        int k = BuddyMan_FindChallengerIndex(self, s.p);
        sObjVec_262EC0* v = (sObjVec_262EC0*)(self + 0xB8);
        // PORT: pointer arithmetic through int.
        void** pos = (void**)(k * 4 + (int)*(void***)(self + 0xBC));
        if (pos + 1 != *(void***)(self + 0xC0))
            sObjVec_262EC0_copy(pos + 1, v->mFinish, pos);
        --*(void***)(self + 0xC0);
    }
    cBXString__cBXString(&s, 2);
}

//100%
extern void* D_004A3028;
// PORT: callee defined as returning void* in this unit; called here as void.
void LobbyMan_SendDecline_v(void* self, int a1) __asm__("LobbyMan_SendDecline__FPvi");
extern "C" void* func_0041610C(void* dst, const void* src, unsigned int n);
extern "C" int func_00262438(void* self, int a1);
extern "C" int func_00262A38(void* self, void* name);
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
extern "C" void* func_002625C8(void* self, int idx);
extern "C" void func_003F11F8(void* h, void* e, void* cb, void* user, int timeout);
extern "C" void func_00268F90(void* self, void* a1, int a2);

struct sTagsUnkVEntry18 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sTagsUnkObjVec18 {
    void* alloc;
    void** mStart;
    void** mFinish;
};

static inline void** sTagsUnkObjVec18_copy(void** first, void** last, void** result)
{
    func_0041610C(result, first, (last - first) * sizeof(void*));
    return result + (last - first);
}

// PORT: the name is passed through int parameters of some callees.
extern "C" void func_00263018(void* self, void* name)
{
    int idx = BuddyMan_FindChallengerIndex(self, name);
    if (idx >= 0) {
        LobbyMan_SendDecline_v(D_004A3028, (int)name);
        sTagsUnkObjVec18* v = (sTagsUnkObjVec18*)((char*)self + 0xB8);
        void** pos = *(void***)((char*)self + 0xBC) + idx;
        char* obj = (char*)*pos;
        if (pos + 1 != *(void***)((char*)self + 0xC0)) {
            sTagsUnkObjVec18_copy(pos + 1, v->mFinish, pos);
        }
        --*(void***)((char*)self + 0xC0);
        if (obj != 0) {
            sTagsUnkVEntry18* vt = *(sTagsUnkVEntry18**)(obj + 0x3C);
            vt[1].fn(obj + vt[1].delta, 3);
        }
        if (func_00262438(self, (int)name)) {
            if (func_00262A38(self, name) == 0) {
                void* e = func_002625C8(self, BuddyMan_FindRosterEntry(self, (int)name));
                if (e != 0) {
                    // PORT: function pointer passed as a callback argument.
                    func_003F11F8(*(void**)((char*)self + 0xC8), e, (void*)func_00268F90, self, 600);
                }
            }
        }
    }
}

//100%
extern "C" void cBXString__cBXString(void* self, int flags);
extern "C" void* cBXString_cBXString2(void* self, const char* s);
extern "C" int func_004165A8(void*, void*);

// Returns 1 if any entry's name equals `name`.
extern "C" int func_00263128(char* self, char* name)
{
    if ((*(void****)(self + 0xC0) - *(void****)(self + 0xBC)) == 0)
        return 0;
    for (void*** it = *(void****)(self + 0xBC); it != *(void****)(self + 0xC0); it++) {
        void** e = *it;
        char* tmp;
        cBXString_cBXString2(&tmp, name);
        if (func_004165A8(*e, name) == 0) {
            cBXString__cBXString(&tmp, 2);
            return 1;
        }
        cBXString__cBXString(&tmp, 2);
    }
    return 0;
}

//100%
// Returns whether any string in the pointer list at 0xBC..0xC0 equals *key.
extern "C" int func_002631E0(char* self, char** key)
{
    char*** end = *(char****)(self + 0xC0);
    char*** begin = *(char****)(self + 0xBC);
    if (end - begin == 0)
        return 0;
    for (char*** it = begin; it != *(char****)(self + 0xC0); ++it)
    {
        if (func_004165A8(**it, *key) == 0)
            return 1;
    }
    return 0;
}

//100%
extern "C" void* func_00263270(void* self, void* name)
{
    if ((unsigned int)(*(void***)((char*)self + 0xC0) - *(void***)((char*)self + 0xBC)) == 0) {
        return 0;
    }
    for (void** it = *(void***)((char*)self + 0xBC); it != *(void***)((char*)self + 0xC0); it++) {
        void* e = *it;
        if (func_004165A8(*(void**)e, name) == 0) {
            return e;
        }
    }
    return 0;
}

//100%
extern "C" void* func_00263308(void* self, unsigned int i)
{
    void** begin = *(void***)((char*)self + 0xBC);
    void** end = *(void***)((char*)self + 0xC0);
    if (i >= (unsigned int)(end - begin)) {
        return 0;
    }
    return *(void**)((char*)begin + (i << 2));
}

//100%
// PORT: the target calls func_00262598 without setting $4 (self is still there from entry);
// bound here with a no-arg prototype.
extern "C" int func_00262598_noarg() __asm__("func_00262598");

extern "C" int func_00263338(void* self, int idx)
{
    if (idx < 0) {
        return 0;
    }
    if (func_00262598_noarg() < idx) {
        return 0;
    }
    char* e = (char*)func_002625C8(self, idx);
    if (e == 0) {
        return 0;
    }
    int r = 0;
    if ((*(unsigned char*)(e + 0xA7) & 1) || (*(unsigned int*)(e + 0xA8) & 0x100000)) {
        r = 1;
    }
    return r;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
extern "C" int func_00263338(void* self, int a1);

extern "C" int func_002633C8(void* self, int a1)
{
    return func_00263338(self, BuddyMan_FindRosterEntry(self, a1));
}

//100%
extern char D_004A2F40[];
extern char D_004A31F8[];
extern "C" const char* cDirtysock_tag_TagFieldFind(const char* record, const char* name);
// PORT: the target calls func_00262598 without setting $4 (self is still there from entry);
// bound here with a no-arg prototype.
extern "C" int func_00262598_noarg() __asm__("func_00262598");
// PORT: TagFieldGetString really takes a 4th (default value) argument; the unit declares 3.
extern "C" int cDirtysock_tag_TagFieldGetString4(const char* tag, char* buf, int size, const char* defval) __asm__("cDirtysock_tag_TagFieldGetString");

extern "C" int func_002633F8(void* self, int idx)
{
    if (idx < 0) {
        return 0;
    }
    if (func_00262598_noarg() < idx) {
        return 0;
    }
    char* e = (char*)func_002625C8(self, idx);
    if (e == 0) {
        return 0;
    }
    char buf[16];
    cDirtysock_tag_TagFieldGetString4(cDirtysock_tag_TagFieldFind(e + 0x54, D_004A31F8), buf, 0x10, D_004A2F40);
    return func_004165A8(*(void**)((char*)self + 0xEC), buf) == 0;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int BuddyMan_FindRosterEntry(void* self, int a1);
extern "C" int func_002633F8(void* self, int a1);

extern "C" int BuddyMan_IsSameProduct(void* self, int a1)
{
    return func_002633F8(self, BuddyMan_FindRosterEntry(self, a1));
}

//100%
extern "C" int BuddyMan_RosterCompare(void* self, int a1, void* a, void* b)
{
    if (a == 0) {
        return b != 0;
    }
    if (b == 0) {
        return -1;
    }
    // PORT: func_0041AA88 (strcmp-like) is declared void* in this unit but returns int
    return (int)func_0041AA88(a, b);
}

//100%
// Removes obj from the pointer vector at 0xA8 and deletes it. The search walks back from
// mFinish itself (not mFinish - 1) and stops before mStart, as the retail code does.
struct sVEntry_263500 {
    short delta;
    short index;
    void (*fn)(void*, int);
};

extern "C" void BuddyMan_DeleteMessage(char* self, void* obj)
{
    void** p = *(void***)(self + 0xB0);
    if (p == *(void***)(self + 0xAC))
        return;
    do {
        void* x = *p;
        if (x == obj) {
            sObjVec_262EC0* v = (sObjVec_262EC0*)(self + 0xA8);
            if (p + 1 != *(void***)(self + 0xB0))
                sObjVec_262EC0_copy(p + 1, v->mFinish, p);
            --*(void***)(self + 0xB0);
            if (x != 0) {
                sVEntry_263500* vt = *(sVEntry_263500**)((char*)x + 0xC);
                vt[1].fn((char*)x + vt[1].delta, 3);
            }
            return;
        }
        p--;
    } while (p != *(void***)(self + 0xAC));
}

//100%
extern "C" void* func_0041610C(void* dst, const void* src, unsigned int n);

struct sTagsUnkVEntry {
    short delta;
    short index;
    void (*fn)(void*, int);
};

struct sTagsUnkObjVec {
    void* alloc;
    void** mStart;
    void** mFinish;
};

static inline void** sTagsUnkObjVec_copy(void** first, void** last, void** result)
{
    func_0041610C(result, first, (last - first) * sizeof(void*));
    return result + (last - first);
}

extern "C" void func_002635A8(void* self, int idx)
{
    sTagsUnkObjVec* v = (sTagsUnkObjVec*)((char*)self + 0xA8);
    void** pos = *(void***)((char*)self + 0xAC) + idx;
    char* obj = (char*)*pos;
    if (pos + 1 != *(void***)((char*)self + 0xB0)) {
        sTagsUnkObjVec_copy(pos + 1, v->mFinish, pos);
    }
    --*(void***)((char*)self + 0xB0);
    if (obj != 0) {
        sTagsUnkVEntry* vt = *(sTagsUnkVEntry**)(obj + 0xC);
        vt[1].fn(obj + vt[1].delta, 3);
    }
}

//100%
extern "C" void* func_00263630(void* self, unsigned int i)
{
    void** begin = *(void***)((char*)self + 0xAC);
    void** end = *(void***)((char*)self + 0xB0);
    if (i >= (unsigned int)(end - begin)) {
        return 0;
    }
    return *(void**)((char*)begin + (i << 2));
}

extern void* D_004810C8[];

//100%
void* func_00263660(void* self)
{
    *(int*)self = 0;
    *(int*)((char*)self + 0x8) = (int)(void*)D_004810C8;
    return self;
}

//100%
extern void* D_004810C8[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void func_00263678(void* self, int flags)
{
    *(void***)((char*)self + 0x8) = D_004810C8;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern void* D_004A2EB8;
extern float D_004A2F0C;
extern float D_004A2F10;
extern "C" void func_00255F50(void* p);

extern "C" void func_002636A8(void* self)
{
    func_00255F50(D_004A2EB8);
    float v;
    if (*(int*)((char*)D_004A2EB8 + 0x2C) != 0) {
        v = D_004A2F0C;
    } else {
        v = D_004A2F10;
    }
    *(float*)((char*)self + 0x4) = v;
    *(int*)self = 1;
}

//100%
extern char D_004804A8[];
extern char D_00480ED0[];
extern void* D_00481250[];
extern void* D_004A3328;
extern void* D_004A3028;
extern void* D_004A2EB8;
extern "C" void func_00260F80(void);
extern "C" int func_00261460(void* p);
extern "C" void func_002613C8(void* p);
extern "C" void func_0025B800(void* self);
extern "C" void func_00261408(void* p);
extern "C" void func_00255FA0(void* p);
struct sMsgListNode36F0 {
    sMsgListNode36F0* next;
    sMsgListNode36F0* prev;
    void* data;
};

struct sMsgListIter36F0 {
    sMsgListNode36F0* node;
    sMsgListIter36F0(sMsgListNode36F0* x) : node(x) {}
    sMsgListIter36F0(const sMsgListIter36F0& x) : node(x.node) {}
};

static inline sMsgListIter36F0 sMsgList36F0_insert(sMsgListIter36F0 pos, void* const& x)
{
    sMsgListNode36F0* tmp = (sMsgListNode36F0*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline bool isState_36F0(int st)
{
    return *(int*)((char*)D_004A2EB8 + 0x20) == st;
}

extern "C" void func_002636F0(int* out, int val)
{
    if (D_004A3328 == 0)
        func_00260F80();
    if (func_00261460(D_004A3328) == 0)
        func_002613C8(D_004A3328);
    if (D_004A3328 == 0)
        func_0025B800(D_004A3028);
    func_00261408(D_004A3328);
    func_0025B800(D_004A3028);
    if (!isState_36F0(1)) {
        func_00255FA0(D_004A2EB8);
        if (val != 0) {
            char* g = (char*)D_004A3028;
            int* m = (int*)operator new(0xC, D_00480ED0, 0x20000000, 0);
            m[0] = 0x116;
            *(void***)((char*)m + 0x4) = D_00481250;
            m[2] = val;
            void* mp = m;
            sMsgList36F0_insert(*(sMsgListNode36F0**)(g + 0xF0), mp);
        }
        *out = 0;
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004A3028;
extern void* D_004A2EB8;
extern void* D_004A28A8;
extern "C" void func_002636F0(int* out, int val);

static inline bool isState_3828(int st)
{
    return *(int*)((char*)D_004A2EB8 + 0x20) == st;
}
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNode3828 {
    sMsgListNode3828* next;
    sMsgListNode3828* prev;
    void* data;
};

struct sMsgListIter3828 {
    sMsgListNode3828* node;
    sMsgListIter3828(sMsgListNode3828* x) : node(x) {}
    sMsgListIter3828(const sMsgListIter3828& x) : node(x.node) {}
};

static inline sMsgListIter3828 sMsgList3828_insert(sMsgListIter3828 pos, void* const& x)
{
    sMsgListNode3828* tmp = (sMsgListNode3828*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_3828(char* self, void* msg)
{
    void* mp = msg;
    sMsgList3828_insert(*(sMsgListNode3828**)(self + 0xF0), mp);
}

struct sDsTimer_263828 {
    int state;
    float timer;
};

extern "C" void func_00263828(int* self)
{
    sDsTimer_263828* t = (sDsTimer_263828*)self;
    switch (t->state)
    {
    case 0:
        break;
    case 1:
        if (isState_3828(5)) {
            t->state = 2;
            char* g = (char*)D_004A3028;
            int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
            *(void***)((char*)m + 0x4) = D_004812B0;
            m[0] = 0x105;
            post_3828(g, m);
        } else if (isState_3828(6)) {
            func_002636F0(self, *(int*)((char*)D_004A2EB8 + 0x28));
        } else {
            int expired = t->timer < 0.0f;
            if (expired)
                func_002636F0(self, 0x2D3F3F3F);
            else
                t->timer -= *(float*)((char*)D_004A28A8 + 0x14);
        }
        break;
    case 2:
        if (isState_3828(6))
            func_002636F0(self, *(int*)((char*)D_004A2EB8 + 0x28));
        break;
    }
}

extern void* D_004810B0[];

//100%
void* func_00263998(void* self)
{
    *(int*)self = 0;
    *(int*)((char*)self + 0x14) = (int)(void*)D_004810B0;
    return self;
}

//100%
extern void* D_004810B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void func_002639B0(void* self, int flags)
{
    *(void***)((char*)self + 0x14) = D_004810B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
void cBENewRaceInterface_setNumberHumans(void* self, int n);
extern "C" void func_001472C8(void* self, int a1, int a2);
extern "C" int cCommSystem_openDSockChannel(void* comm, const char* addr, unsigned short port, int a3);
extern "C" void cVoipMan_Start(void* self, void* ip);
extern "C" void cVoipMan_Activate(void* self);
extern void* D_004A28A8;
extern void* D_004A2EB8;
extern void* D_004A33F4;
extern float D_004A2F14;
extern int D_00535610[];
extern char D_00480EE0[];

struct sVE_002639E0 {
    short delta;
    short index;
    void (*fn)(void*);
};

struct sIf_002639E0 {
    char pad[0xC];
    sVE_002639E0* vt;
};

struct sNetCfg_002639E0 {
    int active;     // 0x0
    int f4;         // 0x4
    int chan;       // 0x8
    int port;       // 0xC
    float rate;     // 0x10
};

extern sNetCfg_002639E0 D_00534B30_002639E0[] __asm__("D_00534B30");

extern "C" void Net_StartGameSetup(int* self, unsigned int ip, int chan, int a3, int a4)
{
    char buf[256];
    int one = 1;
    self[3] = a4;
    sIf_002639E0* p = (sIf_002639E0*)cBE_getInterface_Fv(cBE_getBE(), 1);
    sIf_002639E0* q = (sIf_002639E0*)cBE_getInterface_Fv(cBE_getBE(), 0);
    cBENewRaceInterface_setNumberHumans(q, 2);
    q->vt[1].fn((char*)q + q->vt[1].delta);
    func_001472C8(p, 0, a3);
    func_001472C8(p, 1, 0);
    p->vt[1].fn((char*)p + p->vt[1].delta);
    sIf_002639E0* r = (sIf_002639E0*)cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
    D_00534B30_002639E0[0].active = one;
    D_00534B30_002639E0[0].rate = 0.01666666753590107f;
    D_00534B30_002639E0[0].port = 0xE4A;
    D_00534B30_002639E0[0].chan = chan;
    r->vt[1].fn((char*)r + r->vt[1].delta);
    r->vt[1].fn((char*)r + r->vt[1].delta);
    self[2] = chan;
    sprintf(buf, D_00480EE0, ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
    self[1] = cCommSystem_openDSockChannel(D_004A2EB8, buf, D_00534B30_002639E0[0].port, chan);
    cBE_getInterface_Fv(cBE_getBE(), 4);
    if ((D_00535610[0] >> 18) & 1) {
        cVoipMan_Start(D_004A33F4, (void*)ip);
        cVoipMan_Activate(D_004A33F4);
    }
    *(float*)&self[4] = D_004A2F14;
    self[0] = one;
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" int func_003E8B10(void* p, int tag, void* cb, int a3, void* user);
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004A3028;
extern void* D_004A2EB8;
extern void* D_004A33CC;
extern void* D_004A33F4;
extern "C" int func_00255D38(void* comm, int chan);
extern "C" void func_00255CC8(void* comm, int chan);
extern "C" void cSetupMan_Destroy(void);
extern "C" void func_00266DF8(void* self);
extern "C" void func_00266E88(void* self);
extern "C" void func_0025F740(void* self, int type);
extern void* D_004812B0[];
extern void* D_00481290[];

struct sMsgListNode3BA8 {
    sMsgListNode3BA8* next;
    sMsgListNode3BA8* prev;
    void* data;
};

struct sMsgListIter3BA8 {
    sMsgListNode3BA8* node;
    sMsgListIter3BA8(sMsgListNode3BA8* x) : node(x) {}
    sMsgListIter3BA8(const sMsgListIter3BA8& x) : node(x.node) {}
};

static inline sMsgListIter3BA8 sMsgList3BA8_insert(sMsgListIter3BA8 pos, void* const& x)
{
    sMsgListNode3BA8* tmp = (sMsgListNode3BA8*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

static inline void post_3BA8(char* self, void* msg)
{
    void* mp = msg;
    sMsgList3BA8_insert(*(sMsgListNode3BA8**)(self + 0xF0), mp);
}

extern "C" void func_00263BA8(void* p, int arg)
{
    int* self = (int*)p;
    if (self[0] != 0 && func_00255D38(D_004A2EB8, self[1]) != 0)
    {
        func_00255CC8(D_004A2EB8, self[1]);
        func_00266E88(D_004A33F4);
        func_00266DF8(D_004A33F4);
    }
    if (D_004A33CC != 0)
        cSetupMan_Destroy();
    func_0025F740(D_004A3028, 0);
    self[0] = 0;
    if (arg == 1) {
        char* g = (char*)D_004A3028;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        *(void***)((char*)m + 0x4) = D_004812B0;
        m[0] = 0x10C;
        post_3BA8(g, m);
    } else if (arg == 0) {
        char* g = (char*)D_004A3028;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        *(void***)((char*)m + 0x4) = D_004812B0;
        m[0] = 0x112;
        post_3BA8(g, m);
    }
}

//100%
struct cAppMan;
void cAppMan_setNextModule(cAppMan* self, unsigned int module);
void* func_00232720(void* self);
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void cBENewPlayerInterface_setRiderCharID(void* iface, int rider, int ch);
extern "C" void cGameComm_construct(int a, int b);
extern "C" void func_0014EBF8(void* self, int a);
extern "C" int cCommSystem_IsChannelConnected(void* comm, int chan);
extern "C" int func_00255E40(void* comm, int chan);
extern "C" void func_00256C50(void);
extern "C" void func_0025B800(void* self);
extern "C" void func_00260F80(void);
extern "C" void func_002613C8(void* p);
extern "C" int func_00261460(void* p);
extern "C" void func_00262768(void* self, int a1, int a2, int a3, int a4, int a5);
extern "C" void func_00263BA8(void* p, int arg);
extern "C" void func_00264030(int a1, int a2, int a3);
extern "C" void cSetupMan_Destroy(void);
extern "C" void cSetupMan_Update(void* self);
// PORT: cSetupMan_SendHello is defined with one parameter; this caller passes a second in $a1.
extern "C" void cSetupMan_SendHello_2(void* self, int a) __asm__("cSetupMan_SendHello");
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern void* D_004A28A8;
extern void* D_004A2EB8;
extern void* D_004A2EEC;
extern void* D_004A3028;
extern void* D_004A3328;
extern void* D_004A33CC;
extern int D_004A19C4;
extern int D_00534B34[];
extern int D_00534E58[];
extern char D_00480EF0[];

struct sVEntry_263CF0 { short delta; short index; void (*fn)(void*); };

static inline bool tsTimedOut_263CF0(int* self)
{
    return *(float*)(self + 4) < 0.0f;
}

static inline bool tsIsState_263CF0(int st)
{
    return *(int*)D_004A33CC == st;
}

static inline void* Mgr_263CF0()
{
    if (D_004A3328 == 0)
        func_00260F80();
    if (func_00261460(D_004A3328) == 0)
        func_002613C8(D_004A3328);
    if (D_004A3328 == 0)
        func_0025B800(D_004A3028);
    return D_004A3328;
}

extern "C" void func_00263CF0(int* self)
{
    switch (self[0])
    {
    case 0:
        break;
    case 1:
        if (cCommSystem_IsChannelConnected(D_004A2EB8, self[1]))
        {
            if (self[3] != 0)
            {
                func_00263BA8(self, 1);
                return;
            }
            cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
            func_00264030(self[1], self[2], D_00534B34[0]);
            cSetupMan_SendHello_2(D_004A33CC, *(int*)((char*)D_004A3028 + 0x8C));
            self[0] = 2;
            return;
        }
        if (func_00255E40(D_004A2EB8, self[1]) || tsTimedOut_263CF0(self))
        {
            func_00263BA8(self, 0);
            return;
        }
        *(float*)(self + 4) = *(float*)(self + 4) - *(float*)((char*)D_004A28A8 + 0x14);
        return;
    case 2:
        if (func_00255E40(D_004A2EB8, self[1]))
        {
            if (!tsIsState_263CF0(0xB))
            {
                char* g = (char*)D_004A3028;
                int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
                *(void***)((char*)m + 0x4) = D_004812B0;
                m[0] = 0x113;
                post_3BA8(g, m);
            }
            func_00263BA8(self, 2);
            return;
        }
        {
            cSetupMan_Update(D_004A33CC);
            int go = 0;
            int st = *(int*)D_004A33CC;
            if (st == 0xD)
                go = 1;
            else if (st == 0xB)
                func_00263BA8(self, 2);
            if (go == 0)
                return;
            cSetupMan_Destroy();
            func_0025B800(D_004A3028);
            D_004A19C4 = 0x34;
            func_00262768(Mgr_263CF0(), 1, 9, *(int*)((char*)D_004A3028 + 0x98), 0, 0);
            void* bi7 = cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
            char* bi1 = (char*)cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 1);
            cBENewPlayerInterface_setRiderCharID(bi1, 0, D_00534E58[0]);
            sVEntry_263CF0* vt = *(sVEntry_263CF0**)(bi1 + 0xC);
            vt[1].fn(bi1 + vt[1].delta);
            func_0014EBF8(bi7, 0);
            if (D_004A2EEC != 0)
                func_00256C50();
            cGameComm_construct(self[1], self[2]);
            cAppMan_setNextModule((cAppMan*)D_004A28A8, (unsigned int)func_00232720(cMemMan_alloc(8, D_00480EF0, 0x100, 0)));
            self[0] = 0;
        }
        return;
    }
}

//100%
extern char D_00480F08[];
extern void* D_004A33CC;
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cSetupMan_ctor(void* self, int a1, int a2, int a3);

extern "C" void func_00264030(int a1, int a2, int a3)
{
    D_004A33CC = cSetupMan_ctor(cMemMan_alloc(0x12C, D_00480F08, 0x20000000, 0), a1, a2, a3);
}

//100%
extern void* D_004A33CC;
extern "C" void cSetupMan_dtor(void* self, int flags);

extern "C" void cSetupMan_Destroy(void)
{
    if (D_004A33CC != 0) {
        cSetupMan_dtor(D_004A33CC, 3);
        D_004A33CC = 0;
    }
}

//100%
extern "C" void* func_003E6448(void* dst, int value, int size);

extern "C" void* cSetupMan_ctor(void* self, int a1, int a2, int a3)
{
    *(int*)((char*)self + 0x0) = 1;
    *(int*)((char*)self + 0x120) = a1;
    *(int*)((char*)self + 0x124) = a2;
    *(int*)((char*)self + 0x4) = 0;
    *(int*)((char*)self + 0x118) = 0;
    *(int*)((char*)self + 0x11C) = 0;
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0xC) = 0;
    *(int*)((char*)self + 0x128) = a3;
    func_003E6448((char*)self + 0x10, 0, 0x80);
    *(int*)((char*)self + 0x90) = 0;
    *(int*)((char*)self + 0x94) = 0;
    func_003E6448((char*)self + 0x98, 0, 0x80);
    return self;
}

//100%
void operator_delete(int* ptr);
extern "C" void cSetupMan_FreePacket(void* self, int* p);

struct sRing_264138
{
    int end;
    int head;
    int* q[32];
};

struct sRingOwner_264138
{
    int f0;
    int* f4;
    sRing_264138 a;     // 0x8
    sRing_264138 b;     // 0x90
};

static inline int* PeekA_264138(sRingOwner_264138* o)
{
    if (o->a.head < o->a.end)
        return o->a.q[o->a.head % 32];
    return 0;
}

static inline int* PopA_264138(sRingOwner_264138* o)
{
    int h = o->a.head++;
    return o->a.q[h % 32];
}

static inline int* PeekB_264138(sRingOwner_264138* o)
{
    if (o->b.head < o->b.end)
        return o->b.q[o->b.head % 32];
    return 0;
}

static inline int* PopB_264138(sRingOwner_264138* o)
{
    int h = o->b.head++;
    return o->b.q[h % 32];
}

extern "C" void cSetupMan_dtor(void* self_, int flags)
{
    sRingOwner_264138* self = (sRingOwner_264138*)self_;
    if (self->f4 != 0)
        cSetupMan_FreePacket(self, self->f4);
    while (PeekA_264138(self) != 0)
        cSetupMan_FreePacket(self, PopA_264138(self));
    while (PeekB_264138(self) != 0)
        cSetupMan_FreePacket(self, PopB_264138(self));
    self->f0 = 1;
    if (flags & 1)
        operator_delete((int*)self);
}

INCLUDE_ASM("dirtysock/tagsunk", cSetupMan_Update);

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern const char D_004805A8[];

extern "C" void* func_00264960(void)
{
    return cMemMan_alloc(0xF0, D_004805A8, 0x20000000, 0);
}

void operator_delete(int*);

//100%
extern "C" void cSetupMan_FreePacket(void* self, int* p)
{
    operator_delete(p);
}

//100%
extern "C" void cSetupMan_ReceivePackets(void* self);
extern "C" void* func_003E6574(void* dst, const void* src, int n);

struct sDsPacketK2 {
    unsigned short kind;   // 0x0
    unsigned short size;   // 0x2 (including this 4-byte header)
    char data[1];          // 0x4
};

struct sDsPacketQueueK2 {
    int pad_0x0[2];
    int tail;                    // 0x8
    int head;                    // 0xC
    sDsPacketK2* slots[32];      // 0x10
};

// Pops the oldest queued packet into `dst`; returns its payload size (0 if empty).
extern "C" int cSetupMan_PopPacket(sDsPacketQueueK2* self, void* dst)
{
    cSetupMan_ReceivePackets(self);
    int head = self->head;
    if (head != self->tail) {
        self->head = head + 1;
        sDsPacketK2* p = self->slots[head % 32];
        int len = p->size - 4;
        func_003E6574(dst, p->data, len);
        cSetupMan_FreePacket(self, (int*)p);
        return len;
    }
    return 0;
}

//100%
extern void* D_004A2EB8;
extern "C" int func_00255DC0(void* mgr, int idx, void* buf, int len);
// PORT: func_00264960 is defined as f(void); this caller passes self in $a0.
void* func_00264960_self(void* self) __asm__("func_00264960");

struct sDsRecvQueue_00264A58 {
    int f0;                     // 0x0
    void* cur;                  // 0x4
    int tail;                   // 0x8
    int head;                   // 0xC
    void* slots[32];            // 0x10
    char pad_0x90[0x120 - 0x90];
    int chan;                   // 0x120
};

// Fills the 32-entry receive queue until it is full or no packet is pending.
extern "C" void cSetupMan_ReceivePackets(void* p)
{
    sDsRecvQueue_00264A58* self = (sDsRecvQueue_00264A58*)p;
    void* buf;
    while (self->cur != 0
           || (buf = func_00264960_self(self), self->cur = buf,
               func_00255DC0(D_004A2EB8, self->chan, buf, 0xF0) != 0))
    {
        bool full = self->tail - self->head >= 0x1F;
        if (full)
            return;
        self->slots[self->tail++ % 32] = self->cur;
        self->cur = 0;
    }
    operator_delete((int*)self->cur);
    self->cur = 0;
}

//100%
extern void* D_004A2EB8;
extern "C" int func_00255E00(void* mgr, int idx, void* buf, int len);

struct sDsPacket_00264B20 {
    unsigned short kind;   // 0x0
    unsigned short size;   // 0x2 (including this 4-byte header)
};

struct sDsSendQueue_00264B20 {
    char pad_0x00[0x90];
    int tail;                          // 0x90
    int head;                          // 0x94
    sDsPacket_00264B20* slots[32];     // 0x98
    char pad_0x118[0x120 - 0x118];
    int chan;                          // 0x120
};

// Sends queued packets until the queue is empty or the channel refuses one.
extern "C" void cSetupMan_FlushSendQueue(void* p)
{
    sDsSendQueue_00264B20* self = (sDsSendQueue_00264B20*)p;
    while (self->head != self->tail)
    {
        sDsPacket_00264B20* pkt;
        int head = self->head;
        if (head < self->tail)
            pkt = self->slots[head % 32];
        else
            pkt = 0;
        if (func_00255E00(D_004A2EB8, self->chan, pkt, pkt->size) == 0)
            return;
        self->head++;
        cSetupMan_FreePacket(self, (int*)pkt);
    }
}

//100%
extern void* D_004A2EB8;
extern "C" int func_00255E00(void* mgr, int idx, void* buf, int len);
extern "C" void cSetupMan_FlushSendQueue(void* p);
// PORT: func_00264960 is defined as f(void); this caller passes self in $a0.
void* func_00264960_self(void* self) __asm__("func_00264960");

struct sDsOutPacket_00264BE8 {
    unsigned char kind;     // 0x0
    unsigned char flags;    // 0x1
    unsigned short size;    // 0x2 (including this 4-byte header)
    char data[0xEC];        // 0x4
};

struct sDsSendQueue_00264BE8 {
    char pad_0x00[0x90];
    int tail;                          // 0x90
    int head;                          // 0x94
    void* slots[32];                   // 0x98
    char pad_0x118[0x120 - 0x118];
    int chan;                          // 0x120
};

// PORT: the unit declares cSetupMan_SendPacket as returning void (callers ignore the result); the body
// returns 1, so it is bound by asm label.
int cSetupMan_SendPacket_impl(void* p, const void* src, int len) __asm__("cSetupMan_SendPacket");

// Flushes the send queue, then sends `len` bytes now or queues a copy for later.
int cSetupMan_SendPacket_impl(void* p, const void* src, int len)
{
    sDsSendQueue_00264BE8* self = (sDsSendQueue_00264BE8*)p;
    cSetupMan_FlushSendQueue(self);
    sDsOutPacket_00264BE8 pkt;
    pkt.kind = 0;
    pkt.flags = 0;
    pkt.size = len + 4;
    func_003E6574(pkt.data, src, len);
    if (func_00255E00(D_004A2EB8, self->chan, &pkt, pkt.size) != 0)
        return 1;
    void* buf = func_00264960_self(self);
    func_003E6574(buf, &pkt, pkt.size);
    self->slots[self->tail++ % 32] = buf;
    return 1;
}

//100%
extern void* D_004A3028;
extern "C" void cSetupMan_SendPacket(void* self, void* msg, int size);

struct sTagMsg264CB8 {
    int type;          // 0x0
    int state;         // 0x4
    unsigned int id;   // 0x8
    int pad[2];
};

extern "C" void cSetupMan_SendHello(void* self)
{
    sTagMsg264CB8 msg;
    msg.state = *(int*)((char*)D_004A3028 + 0xB8);
    msg.type = 16;
    msg.id = 0;
    cSetupMan_SendPacket(self, &msg, sizeof(msg));
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_00147448(void* self, int a1, int charID);
extern void* D_004A28A8;
extern int D_00534E58[];

struct sVE264CF0 {
    short delta;
    short index;
    void (*fn)(void*);
};

struct sIf264CF0 {
    char pad[0xC];
    sVE264CF0* vt;
};

extern "C" void cSetupMan_SetLocalCharacter(void* self, int charID)
{
    sIf264CF0* p = (sIf264CF0*)cBE_getInterface_Fv(cBE_getBE(), 1);
    func_00147448(p, 0, charID);
    p->vt[1].fn((char*)p + p->vt[1].delta);
    sIf264CF0* q = (sIf264CF0*)cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
    D_00534E58[0] = charID;
    q->vt[1].fn((char*)q + q->vt[1].delta);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_00147448(void* self, int a1, int charID);
extern void* D_004A28A8;

struct sVE_00264D80 {
    short delta;
    short index;
    void (*fn)(void*);
};

struct sIf_00264D80 {
    char pad[0xC];
    sVE_00264D80* vt;
};

struct sName7_00264D80 {
    char c[7];
};

struct sNetState_00264D80 {
    char pad_0x000[0x32C];
    int charID;                     // 0x32C
    char pad_0x330[0x4A8 - 0x330];
    sName7_00264D80 name;           // 0x4A8
};

extern sNetState_00264D80 D_00534B30_00264D80[] __asm__("D_00534B30");

extern "C" void cSetupMan_SetRemoteCharacter(void* self, int charID, sName7_00264D80* name)
{
    sIf_00264D80* p = (sIf_00264D80*)cBE_getInterface_Fv(cBE_getBE(), 1);
    func_00147448(p, 1, charID);
    p->vt[1].fn((char*)p + p->vt[1].delta);
    sIf_00264D80* q = (sIf_00264D80*)cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
    D_00534B30_00264D80[0].charID = charID;
    if (name != 0)
        D_00534B30_00264D80[0].name = *name;
    q->vt[1].fn((char*)q + q->vt[1].delta);
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void cSetupMan_SendPacket(void* self, void* msg, int size);
extern "C" int func_00148BC8(void* iface, int a, int rider);
extern "C" int func_00148C68(void* iface, int a, int rider);
extern "C" int func_00148B78(void* iface, int a, int rider);
extern "C" int func_00148CB8(void* iface, int a, int rider);
extern "C" int func_00148D58(void* iface, int a, int rider);
extern "C" int func_00148D08(void* iface, int a, int rider);
extern "C" int func_00148C18(void* iface, int a, int rider);
extern void* D_004A28A8;

struct sTagMsg264E50 {
    int type;                   // 0x0
    int rider;                  // 0x4
    int state;                  // 0x8
    unsigned char stats[7];     // 0xC
};

extern "C" void cSetupMan_SendCharacterMsg(void* self, int type, int rider, int state)
{
    sTagMsg264E50 msg;
    msg.type = type;
    msg.state = state;
    msg.rider = rider;
    void* iface = cBE_getInterface_Fv(cBE_getBE(), 3);
    cBE_getInterface_Fv(*(void**)((char*)D_004A28A8 + 0x78), 7);
    if (*(int*)((char*)self + 0x128) != 0) {
        int i;
        for (i = 0; i < 7; i++)
            msg.stats[i] = 40;
    } else {
        msg.stats[0] = func_00148BC8(iface, 0, rider);
        msg.stats[1] = func_00148C68(iface, 0, rider);
        msg.stats[2] = func_00148B78(iface, 0, rider);
        msg.stats[3] = func_00148CB8(iface, 0, rider);
        msg.stats[4] = func_00148D58(iface, 0, rider);
        msg.stats[5] = func_00148D08(iface, 0, rider);
        msg.stats[6] = func_00148C18(iface, 0, rider);
    }
    cSetupMan_SendPacket(self, &msg, sizeof(msg));
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSetupMan_SetLocalCharacter(void* self, int a1);
extern "C" void cSetupMan_SendCharacterMsg(void* self, int event, int a2, int state);

extern "C" void func_00264F88(void* self, int a1)
{
    int state = *(int*)self;
    if (state == 0xC) {
        return;
    }
    if (*(int*)((char*)self + 0x124) != 0) {
        if (state == 1) {
            *(int*)self = 2;
        }
        cSetupMan_SetLocalCharacter(self, a1);
        cSetupMan_SendCharacterMsg(self, 0, a1, *(int*)self);
    } else {
        cSetupMan_SendCharacterMsg(self, 1, a1, 0);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_004A3028;
extern "C" void cSetupMan_SetLocalCharacter(void* self, int charID);
extern "C" void cSetupMan_SendCharacterMsg(void* self, int type, int rider, int state);

struct sMsgListNode5018 {
    sMsgListNode5018* next;
    sMsgListNode5018* prev;
    void* data;
};

struct sMsgListIter5018 {
    sMsgListNode5018* node;
    sMsgListIter5018(sMsgListNode5018* x) : node(x) {}
    sMsgListIter5018(const sMsgListIter5018& x) : node(x.node) {}
};

static inline sMsgListIter5018 sMsgList5018_insert(sMsgListIter5018 pos, void* const& x)
{
    sMsgListNode5018* tmp = (sMsgListNode5018*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void func_00265018(void* self, int rider)
{
    if (*(int*)((char*)self + 0x124) != 0) {
        int st = *(int*)self;
        if (st > 0) {
            if (st < 3)
                *(int*)self = 4;
            else if (st == 3)
                *(int*)self = 5;
        }
        cSetupMan_SetLocalCharacter(self, rider);
        int type = 0xF4;
        cSetupMan_SendCharacterMsg(self, 2, rider, *(int*)self);
        char* g = (char*)D_004A3028;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = type;
        *(void***)((char*)m + 0x4) = D_004812B0;
        void* mp = m;
        sMsgList5018_insert(*(sMsgListNode5018**)(g + 0xF0), mp);
    } else {
        cSetupMan_SendCharacterMsg(self, 3, rider, *(int*)self);
    }
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" void cSetupMan_SendCharacterMsg(void* self, int event, int a2, int state);

extern "C" void func_00265140(int* self)
{
    int event;
    if (*self != 0xC) {
        if (*(int*)((char*)self + 0x124) != 0) {
            if (*self == 4) {
                *self = 2;
            }
            event = 4;
        } else {
            event = 5;
        }
        cSetupMan_SendCharacterMsg(self, event, -1, *self);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_004A3028;
struct sName7_00264D80;
extern "C" void cSetupMan_SetRemoteCharacter(void* self, int charID, sName7_00264D80* name);
extern "C" void cSetupMan_SendCharacterMsg(void* self, int type, int rider, int state);

struct sMsgListNode5190 {
    sMsgListNode5190* next;
    sMsgListNode5190* prev;
    void* data;
};

struct sMsgListIter5190 {
    sMsgListNode5190* node;
    sMsgListIter5190(sMsgListNode5190* x) : node(x) {}
    sMsgListIter5190(const sMsgListIter5190& x) : node(x.node) {}
};

static inline sMsgListIter5190 sMsgList5190_insert(sMsgListIter5190 pos, void* const& x)
{
    sMsgListNode5190* tmp = (sMsgListNode5190*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void cSetupMan_HostRecvSelect(void* self, int rider, sName7_00264D80* name)
{
    int st = *(int*)self;
    if (st != 2) {
        if (st < 3) {
            if (st == 1)
                *(int*)self = 2;
        }
    }
    cSetupMan_SetRemoteCharacter(self, rider, name);
    int type = 0xF3;
    cSetupMan_SendCharacterMsg(self, 1, rider, *(int*)self);
    {
        char* g = (char*)D_004A3028;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = type;
        *(void***)((char*)m + 0x4) = D_004812B0;
        void* mp = m;
        sMsgList5190_insert(*(sMsgListNode5190**)(g + 0xF0), mp);
    }
}

//100%
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_004A3028;
struct sName7_00264D80;
extern "C" void cSetupMan_SetRemoteCharacter(void* self, int charID, sName7_00264D80* name);
extern "C" void cSetupMan_SendCharacterMsg(void* self, int type, int rider, int state);

struct sMsgListNode5290 {
    sMsgListNode5290* next;
    sMsgListNode5290* prev;
    void* data;
};

struct sMsgListIter5290 {
    sMsgListNode5290* node;
    sMsgListIter5290(sMsgListNode5290* x) : node(x) {}
    sMsgListIter5290(const sMsgListIter5290& x) : node(x.node) {}
};

static inline sMsgListIter5290 sMsgList5290_insert(sMsgListIter5290 pos, void* const& x)
{
    sMsgListNode5290* tmp = (sMsgListNode5290*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

extern "C" void cSetupMan_HostRecvConfirm(void* self, int rider)
{
    int st = *(int*)self;
    if (st > 0) {
        if (st < 3)
            *(int*)self = 3;
        else if (st == 4)
            *(int*)self = 5;
    }
    int type = 0xF5;
    cSetupMan_SetRemoteCharacter(self, rider, 0);
    cSetupMan_SendCharacterMsg(self, 3, rider, *(int*)self);
    {
        char* g = (char*)D_004A3028;
        int* m = (int*)operator new(8, D_00480488, 0x20000000, 0);
        m[0] = type;
        *(void***)((char*)m + 0x4) = D_004812B0;
        void* mp = m;
        sMsgList5290_insert(*(sMsgListNode5290**)(g + 0xF0), mp);
    }
}

//100%
// PORT: cMemMan_alloc called as the game's operator new(size, tag, flags, align): gcc then treats the
// result as malloc-like (no aliasing), as the target shows. On PC use a real operator new.
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern char D_00480488[];
extern char D_004804A8[];
extern void* D_004812B0[];
extern void* D_004A3028;

struct sMsgListNode_00265398 {
    sMsgListNode_00265398* next;
    sMsgListNode_00265398* prev;
    void* data;
};

struct sMsgListIter_00265398 {
    sMsgListNode_00265398* node;
    sMsgListIter_00265398(sMsgListNode_00265398* x) : node(x) {}
    sMsgListIter_00265398(const sMsgListIter_00265398& x) : node(x.node) {}
};

static inline sMsgListIter_00265398 sMsgList_00265398_insert(sMsgListIter_00265398 pos, void* const& x)
{
    sMsgListNode_00265398* tmp = (sMsgListNode_00265398*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

struct sMsg_00265398 {
    int kind;
    void** vt;
};

extern "C" void cSetupMan_HostRecvCancel(int* self)
{
    if (*self == 3)
        *self = 2;
    char* g = (char*)D_004A3028;
    sMsg_00265398* m = (sMsg_00265398*)cMemMan_alloc(8, D_00480488, 0x20000000, 0);
    m->vt = D_004812B0;
    m->kind = 0xF7;
    void* mp = m;
    sMsgList_00265398_insert(*(sMsgListNode_00265398**)(g + 0xF0), mp);
}

//100%
extern char D_004804A8[];
extern char D_00480F18[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern void* D_004A3028;
extern "C" void cSetupMan_SendPacket(void* self, void* msg, int size);
extern void* D_00481150[];

struct sMsgListNode5458 {
    sMsgListNode5458* next;
    sMsgListNode5458* prev;
    void* data;
};

struct sMsgListIter5458 {
    sMsgListNode5458* node;
    sMsgListIter5458(sMsgListNode5458* x) : node(x) {}
    sMsgListIter5458(const sMsgListIter5458& x) : node(x.node) {}
};

static inline sMsgListIter5458 sMsgList5458_insert(sMsgListIter5458 pos, void* const& x)
{
    sMsgListNode5458* tmp = (sMsgListNode5458*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

struct sTagMsg5458 {
    int type;   // 0x0
    int id;     // 0x4
    int state;  // 0x8
    int pad[2];
};

struct sNetMsg5458 {
    int type;       // 0x0
    void** vt;      // 0x4
    int flag;       // 0x8
    int v0;         // 0xC
    int v1;         // 0x10
};

extern "C" void func_00265458(void* self, int id)
{
    int st = *(int*)self;
    if (st != 12) {
        int type;
        if (*(int*)((char*)self + 0x124) != 0) {
            if (st >= 5) {
                if (st < 7)
                    *(int*)self = 7;
            }
            type = 6;
        } else
            type = 7;
        sTagMsg5458 msg;
        msg.type = type;
        msg.state = *(int*)self;
        msg.id = id;
        cSetupMan_SendPacket(self, &msg, sizeof(msg));
        sNetMsg5458* m = (sNetMsg5458*)cMemMan_alloc(0x10, D_00480F18, 0x20000000, 0);
        m->type = 0xFB;
        m->vt = D_00481150;
        m->v0 = id;
        m->flag = 0;
        void* mp = m;
        sMsgList5458_insert(*(sMsgListNode5458**)((char*)D_004A3028 + 0xF0), mp);
    }
}

//100%
extern char D_004804A8[];
extern char D_00480F18[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern void* D_004A3028;
extern "C" void cSetupMan_SendPacket(void* self, void* msg, int size);
extern void* D_00481130[];

struct sMsgListNode5568 {
    sMsgListNode5568* next;
    sMsgListNode5568* prev;
    void* data;
};

struct sMsgListIter5568 {
    sMsgListNode5568* node;
    sMsgListIter5568(sMsgListNode5568* x) : node(x) {}
    sMsgListIter5568(const sMsgListIter5568& x) : node(x.node) {}
};

static inline sMsgListIter5568 sMsgList5568_insert(sMsgListIter5568 pos, void* const& x)
{
    sMsgListNode5568* tmp = (sMsgListNode5568*)operator new(0xC, D_004804A8, 0x20000000, 0);
    void** data = &tmp->data;
    if (data != 0)
        *data = x;
    tmp->next = pos.node;
    tmp->prev = pos.node->prev;
    pos.node->prev->next = tmp;
    pos.node->prev = tmp;
    return tmp;
}

struct sTagMsg5568 {
    int type;   // 0x0
    int a;      // 0x4
    int b;      // 0x8
    int pad[2];
};

struct sNetMsg5568 {
    int type;       // 0x0
    void** vt;      // 0x4
    int flag;       // 0x8
    int v0;         // 0xC
    int v1;         // 0x10
};

extern "C" void func_00265568(void* self, int a, int b)
{
    int st = *(int*)self;
    if (st != 12) {
        int type;
        if (*(int*)((char*)self + 0x124) != 0) {
            if (st >= 5) {
                if (st < 7)
                    *(int*)self = 7;
            }
            type = 8;
        } else
            type = 9;
        sTagMsg5568 msg;
        msg.type = type;
        msg.a = a;
        msg.b = b;
        cSetupMan_SendPacket(self, &msg, sizeof(msg));
        sNetMsg5568* m = (sNetMsg5568*)cMemMan_alloc(0x14, D_00480F18, 0x20000000, 0);
        m->type = 0xFC;
        m->vt = D_00481130;
        m->v0 = a;
        m->v1 = b;
        m->flag = 0;
        void* mp = m;
        sMsgList5568_insert(*(sMsgListNode5568**)((char*)D_004A3028 + 0xF0), mp);
    }
}

//100%
// PORT: really returns int (the unit declares it void); the int return keeps the target's store scheduling.
extern "C" int cSetupMan_SendPacket_5688(void* self, void* msg, int size) __asm__("cSetupMan_SendPacket");
struct sMsg_5688 {
    int code;
    int state;
    unsigned int arg;
    int pad[2];
};

// Advances the connection state (5..7 -> 9, 8 -> 10) and posts a status message.
extern "C" void func_00265688(int* self)
{
    sMsg_5688 m;
    int code = 0xB;
    if (self[0x124 / 4] != 0) {
        code = 0xA;
        int st = self[0];
        if (st >= 5) {
            int nst;
            if (st < 8)
                nst = 9;
            else if (st == 8)
                nst = 10;
            else
                goto send;
            self[0] = nst;
            code = 0xA;
        }
    }
send:
    m.code = code;
    m.state = self[0];
    m.arg = 0xFFFFFFFF;
    cSetupMan_SendPacket_5688(self, &m, 0x14);
}

//100%
struct sTagMsg265700 {
    int type;          // 0x0
    int state;         // 0x4
    unsigned int id;   // 0x8
    int pad[2];
};

extern "C" void cSetupMan_SendPacket(void* self, void* msg, int size);

extern "C" void cSetupMan_SendBragMsg12(void* self)
{
    sTagMsg265700 msg;
    int type;
    int state = *(int*)self;
    if (state == 12)
        return;
    if (*(int*)((char*)self + 0x124) != 0) {
        if (state == 9)
            *(int*)self = 7;
        type = 12;
    } else {
        type = 13;
    }
    msg.type = type;
    msg.state = *(int*)self;
    msg.id = 0xFFFFFFFF;
    cSetupMan_SendPacket(self, &msg, sizeof(msg));
}

INCLUDE_ASM("dirtysock/tagsunk", func_00265768);

//100%
extern char D_00480F30[];
extern void* D_004A33D0;
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cSharedLoginMan_ctor(void* self);

extern "C" void func_00265880(void)
{
    D_004A33D0 = cSharedLoginMan_ctor(cMemMan_alloc(8, D_00480F30, 0x20000000, 0));
}

//100%
extern void* D_004A33D0;
extern "C" void cSharedLoginMan_dtor(void* self, int flags);

extern "C" void func_002658B8(void)
{
    if (D_004A33D0 != 0) {
        cSharedLoginMan_dtor(D_004A33D0, 3);
        D_004A33D0 = 0;
    }
}

//100%
extern "C" void cSharedLoginMan_Init(void* self);

extern "C" void* cSharedLoginMan_ctor(void* self)
{
    cSharedLoginMan_Init(self);
    return self;
}

//100%
extern "C" void cSharedLoginMan_Shutdown(void* self);
void operator_delete(int*);

extern "C" void cSharedLoginMan_dtor(void* self, int flags)
{
    cSharedLoginMan_Shutdown(self);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
// Constructor of the 8-byte singleton made by func_00265880: resets its state and the module globals.
struct sDsHandler265950 { void* vtable; int f4; };
extern sDsHandler265950 D_004A5B48;
extern char D_00442A18[];
extern int D_004A33D4;
extern int D_004A33DC;
extern int D_004A33E0;
extern int D_004A33E4;
extern void* D_004A33D8;
extern char D_00537190[];
extern "C" void func_003F7EE0(void* handler);
extern "C" void* func_003E6448(void* dst, int c, int n);
extern "C" void* func_002C22C8(void);

extern "C" void cSharedLoginMan_Init(void* self)
{
    ((int*)self)[0] = 1;
    D_004A33D4 = 0;
    ((int*)self)[1] = 0;
    D_004A5B48.vtable = D_00442A18;
    D_004A33E0 = 0;
    D_004A33DC = 0;
    D_004A33E4 = 0;
    D_004A5B48.f4 = 0;
    func_003F7EE0(&D_004A5B48);
    func_003E6448(D_00537190, 0, 0x40);
    D_004A33D8 = func_002C22C8();
}

//100%
extern void* D_004A33D8;
extern "C" void func_003F7F18();
extern "C" void func_002C2300(void* h);

extern "C" void cSharedLoginMan_Shutdown(void* self)
{
    *(int*)self = 0;
    func_003F7F18();
    func_002C2300(D_004A33D8);
}

//100%
struct cDsObj2659E8 {
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05(int a);
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual int v11();
};

extern void* D_004A33D8;
extern int D_004A33DC;

extern "C" void func_002659E8(void* self)
{
    if (((cDsObj2659E8*)D_004A33D8)->v11() == 0) {
        ((cDsObj2659E8*)D_004A33D8)->v05(D_004A33DC);
    }
}

//100%
struct cDsObj265A38 {
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual int v20();
};

extern void* D_004A33D8;

extern "C" int func_00265A38(void* self)
{
    return ((cDsObj265A38*)D_004A33D8)->v20();
}

//100%
struct cDsObj265A68 {
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05(int a);
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual int v11();
};

extern void* D_004A33D8;
extern int D_004A3940;
extern "C" int func_003F80E0(int* status);
extern "C" void cSharedLoginMan_DoLoad(void* self);
extern "C" void cSharedLoginMan_DoUpdate(void* self);
extern "C" void cSharedLoginMan_DoCreate(void* self);
extern "C" void cSharedLoginMan_DoDelete(void* self);
extern "C" void func_00265F00(void* self);

extern "C" void func_00265A68(int* self)
{
    int status;
    ((cDsObj265A68*)D_004A33D8)->v03();
    status = 0;
    switch (self[0]) {
    case 0:
    case 1:
    case 5:
    case 9:
    case 13:
    case 17:
    case 22:
        break;
    case 2:
        if (((cDsObj265A68*)D_004A33D8)->v11() == 0) {
            cSharedLoginMan_DoLoad(self);
        }
        break;
    case 6:
        if (((cDsObj265A68*)D_004A33D8)->v11() == 0) {
            cSharedLoginMan_DoUpdate(self);
        }
        break;
    case 10:
        if (((cDsObj265A68*)D_004A33D8)->v11() == 0) {
            cSharedLoginMan_DoCreate(self);
        }
        break;
    case 14:
        if (((cDsObj265A68*)D_004A33D8)->v11() == 0) {
            cSharedLoginMan_DoDelete(self);
        }
        break;
    case 18:
        if (((cDsObj265A68*)D_004A33D8)->v11() == 0) {
            func_00265F00(self);
        }
        break;
    case 3:
    case 7:
    case 11:
    case 15: {
        int r = func_003F80E0(&status);
        self[1] = r;
        if (r == 0) {
            if (status == 2) {
                self[0] += 1;
            }
        } else {
            self[0] += 2;
        }
        break;
    }
    case 4:
    case 8:
    case 12:
    case 16:
    case 21:
        if (((cDsObj265A68*)D_004A33D8)->v11() == 0) {
            ((cDsObj265A68*)D_004A33D8)->v05(0);
        }
        break;
    case 19:
        if (((cDsObj265A68*)D_004A33D8)->v11() == 0) {
            ((cDsObj265A68*)D_004A33D8)->v08();
            self[0] = 20;
        }
        break;
    case 20:
        if (((cDsObj265A68*)D_004A33D8)->v11() == 0) {
            if (D_004A3940) {
                self[0] = 22;
            } else {
                self[0] = 21;
            }
        }
        break;
    }
}

//100%
struct cDsObj265CB0 {
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual bool v53();
    virtual void v54();
    virtual bool v55();
};

extern void* D_004A33D8;

extern "C" int func_00265CB0(void* self)
{
    if (((cDsObj265CB0*)D_004A33D8)->v53() != 0) {
        return !((cDsObj265CB0*)D_004A33D8)->v55();
    }
    return 0;
}

//100%
struct cDsObj265D08 {
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
};

extern void* D_004A33D8;

extern "C" void func_00265D08(void* self)
{
    ((cDsObj265D08*)D_004A33D8)->v47();
}

//100%
struct cDsObj265D38 {
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual int v63();
};

extern void* D_004A33D8;

extern "C" int func_00265D38(void* self)
{
    return ((cDsObj265D38*)D_004A33D8)->v63();
}

//100%
struct cDsObj265D68 {
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual bool v53();
};

extern void* D_004A33D8;

extern "C" int func_00265D68(void* self)
{
    return !((cDsObj265D68*)D_004A33D8)->v53();
}

//100%
extern char D_00536760[0x11];
extern int D_004A33E0;
extern "C" void* func_003E6448(void* dst, int value, int size);
extern "C" int func_003F8000(void* p);

extern "C" void cSharedLoginMan_DoLoad(void* self)
{
    *(int*)((char*)self + 0x4) = 0;
    D_004A33E0 = 0;
    func_003E6448(D_00536760, 0, 0x24);
    func_003F8000(D_00536760);
    *(int*)self = 3;
}

//100%
void func_00265DF0(void* self)
{
    *(int*)self = 2;
}

//100%
void func_00265E00(void* self)
{
    *(int*)self = 6;
}

//100%
void func_00265E10(void* self)
{
    *(int*)self = 10;
}

//100%
void func_00265E20(void* self)
{
    *(int*)self = 14;
}

//100%
void func_00265E30(void* self)
{
    *(int*)self = 18;
}

//100%
extern char D_00536760[0x11];
extern int D_004A33E0;
extern "C" int func_003F8048(void* p);

extern "C" void cSharedLoginMan_DoUpdate(void* self)
{
    *(int*)((char*)self + 0x4) = 0;
    D_004A33E0 = 0;
    func_003F8048(D_00536760);
    *(int*)self = 7;
}

//100%
extern char D_00536760[0x11];
extern char D_00442A60[];
extern int D_004A33E0;
extern "C" int func_003F7F48(void* a, void* b);

extern "C" void cSharedLoginMan_DoCreate(void* self)
{
    *(int*)((char*)self + 0x4) = 0;
    D_004A33E0 = 0;
    func_003F7F48(D_00442A60, D_00536760);
    *(int*)self = 0xB;
}

//100%
extern int D_004A33E0;
extern "C" int func_003F80C0();

extern "C" void cSharedLoginMan_DoDelete(void* self)
{
    *(int*)((char*)self + 0x4) = 0;
    D_004A33E0 = 0;
    func_003F80C0();
    *(int*)self = 0xF;
}

//100%
extern int D_004A33E0;

extern "C" void func_00265F00(void* self)
{
    *(int*)((char*)self + 0x4) = 0;
    D_004A33E0 = 0;
    *(int*)self = 0x13;
}

//100%
extern char D_00536760[0x11];
extern "C" void* func_003E6448(void* dst, int value, int size);
extern "C" char* strcpy(char* dst, const char* src);

extern "C" void func_00265F18(const char* name)
{
    func_003E6448(D_00536760, 0, 0x11);
    strcpy(D_00536760, name);
}

//100%
extern char D_00536771[0x11];
extern "C" void* func_003E6448(void* dst, int value, int size);
extern "C" char* strcpy(char* dst, const char* src);

extern "C" void func_00265F68(const char* name)
{
    func_003E6448(D_00536771, 0, 0x11);
    strcpy(D_00536771, name);
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
extern char D_00537190[];
extern "C" void* func_003E6448(void* dst, int value, int size);
extern "C" int func_003FA1D0(int code, void* out);
extern "C" void func_002C6810(void* obj, void* a1);

struct sDsErr265FB8 {
    char a;
    char b;
};

extern "C" void cSharedLoginMan_McListDir(void* arg, int code)
{
    sDsErr265FB8 err;
    func_003FA1D0(code, &err);
    func_003E6448(D_00537190, 0, 0x40);
    func_002C6810(D_004A33D8, arg);
    D_004A33D4 = 2;
}

//100%
extern int D_004A33D4;
extern "C" int func_003FA1D0(int code, void* out);

struct sDsErr266010 {
    char a;
    char b;
};

extern "C" void func_00266010(int code)
{
    sDsErr266010 err;
    func_003FA1D0(code, &err);
    D_004A33D4 = 9;
}

//100%
extern int D_004A33D4;
extern "C" int func_003FA1D0(int code, void* out);

struct sDsErr266038 {
    char a;
    char b;
};

extern "C" void func_00266038(int code)
{
    sDsErr266038 err;
    func_003FA1D0(code, &err);
    D_004A33D4 = 0xA;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
extern int D_004A33DC;
extern int D_004A33E4;
extern "C" int func_003FA1D0(int code, void* out);
void func_002C67E8(void* self, int a1);

struct sDsErr266060 {
    unsigned char a;
    unsigned char b;
};

extern "C" void cSharedLoginMan_McGetInfo(int code)
{
    sDsErr266060 err;
    func_003FA1D0(code, &err);
    D_004A33DC = err.a;
    D_004A33E4 = 9;
    func_002C67E8(D_004A33D8, D_004A33DC);
    D_004A33D4 = 1;
}

//100%
extern int D_004A33D4;
extern "C" int func_003FA1D0(int code, void* out);

struct sDsErr2660A0 {
    char a;
    char b;
};

extern "C" void func_002660A0(int code)
{
    sDsErr2660A0 err;
    func_003FA1D0(code, &err);
    D_004A33D4 = 0x3;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
extern char D_004A33E8[];
extern "C" int func_003FA1D0(int code, void* out);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void func_002C6968(void* obj, char* str, int a2);

struct sDsErr2660C8 {
    unsigned char a;
    unsigned char b;
};

extern "C" void cSharedLoginMan_McOpen(const char* a0, const char* a1, int code, int a3)
{
    sDsErr2660C8 err;
    char buf[80];
    func_003FA1D0(code, &err);
    sprintf(buf, D_004A33E8, a0, a1);
    func_002C6968(D_004A33D8, buf, a3);
    D_004A33D4 = 4;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
void func_002C6A08(void* obj);

extern "C" void cSharedLoginMan_McClose(void)
{
    func_002C6A08(D_004A33D8);
    D_004A33D4 = 8;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
extern "C" int func_003FA1D0(int code, void* out);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" void func_002C6C50(void* obj, char* str, int a2);

struct sDsErr266170 {
    unsigned char a;
    unsigned char b;
};

extern "C" void cSharedLoginMan_McMkdir(const char* name, int a1, int code)
{
    sDsErr266170 err;
    char buf[80];
    func_003FA1D0(code, &err);
    strcpy(buf, name);
    func_002C6C50(D_004A33D8, buf, a1);
    D_004A33D4 = 0xB;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
extern char D_004A33E8[];
extern "C" int func_003FA1D0(int code, void* out);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern "C" void func_002C6CE0(void* obj, char* str);

struct sDsErr2661D8 {
    unsigned char a;
    unsigned char b;
};

extern "C" void cSharedLoginMan_McDeleteFile(const char* a0, const char* a1, int code)
{
    sDsErr2661D8 err;
    char buf[80];
    func_003FA1D0(code, &err);
    sprintf(buf, D_004A33E8, a0, a1);
    func_002C6CE0(D_004A33D8, buf);
    D_004A33D4 = 0xC;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
extern "C" int func_003FA1D0(int code, void* out);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" void func_002C6CE0(void* obj, char* str);

struct sDsErr266240 {
    unsigned char a;
    unsigned char b;
};

extern "C" void cSharedLoginMan_McDeletePath(const char* name, int code)
{
    sDsErr266240 err;
    char buf[80];
    func_003FA1D0(code, &err);
    strcpy(buf, name);
    func_002C6CE0(D_004A33D8, buf);
    D_004A33D4 = 0xD;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
void func_002C6B50(void* obj, int a1, int a2);

extern "C" void cSharedLoginMan_McRead(int a0, int a1, int a2)
{
    func_002C6B50(D_004A33D8, a1, a2);
    D_004A33D4 = 6;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
void func_002C6BD0(void* obj, int a1, int a2);

extern "C" void cSharedLoginMan_McWrite(int a0, int a1, int a2)
{
    func_002C6BD0(D_004A33D8, a1, a2);
    D_004A33D4 = 0xE;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
void func_002C6A60(void* obj, int a1, int a2);

extern "C" void cSharedLoginMan_McSeek(int a0, int a1, int a2)
{
    int r = 0;
    if (a2 != 0) {
        r = (a2 == 1);
    }
    func_002C6A60(D_004A33D8, a1, r);
    D_004A33D4 = 5;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
void func_002C6AE0(void* obj);

extern "C" void cSharedLoginMan_McFlush(void)
{
    func_002C6AE0(D_004A33D8);
    D_004A33D4 = 7;
}

//100%
extern int D_004A33D4;

extern "C" void cSharedLoginMan_McCb_State0F(void)
{
    D_004A33D4 = 0xF;
}

//100%
extern void* D_004A33D8;
extern int D_004A33D4;
extern int D_004A33DC;
extern int D_004A33E0;
extern int D_004A33E4;
extern int D_004A3940;
extern char D_00537190[];
extern "C" int func_002C51D0(void* obj, int a1);
extern "C" int cSharedLoginMan_McMapError(int a0);
void func_002C67E8(void* self, int a1);
extern "C" void func_002C68C8(void* obj, int idx, char* out);
extern "C" int func_003FA360(char* str);

struct sVE_266358 {
    short delta;
    short index;
    int (*fn)(void*);
};

extern "C" int cSharedLoginMan_McPoll(int* status, int* out)
{
    *out = 0;
    switch (D_004A33D4) {
    case 3:
    case 15:
    case 16:
        *status = 2;
        return 0;
    case 10:
        *status = 2;
        *out = 0x800;
        return 0;
    }
    {
        char* obj = (char*)D_004A33D8;
        sVE_266358* vt = *(sVE_266358**)obj;
        if (vt[11].fn(obj + vt[11].delta) != 0) {
            *status = 1;
            return 0;
        }
    }
    *status = 2;
    if (func_002C51D0(D_004A33D8, *(int*)((char*)D_004A33D8 + 0xC)) != 0) {
        return cSharedLoginMan_McMapError(func_002C51D0(D_004A33D8, *(int*)((char*)D_004A33D8 + 0xC)));
    }
    switch (D_004A33D4) {
    case 1:
        if (D_004A33E4 > 0) {
            *status = 1;
            D_004A33E4--;
            func_002C67E8(D_004A33D8, D_004A33DC);
            return 0;
        }
        D_004A33E0 = 1;
        break;
    case 2: {
        int i;
        if (*(int*)((char*)D_004A33D8 + 0x54) <= 0) {
            *out = 0;
            break;
        }
        for (i = 0; i < *(int*)((char*)D_004A33D8 + 0x54); i++) {
            func_002C68C8(D_004A33D8, i, D_00537190);
            if (func_003FA360(D_00537190) != 0) {
                *out = 1;
                return 0;
            }
        }
        *out = 0;
        break;
    }
    case 5:
        *out = D_004A3940;
        break;
    case 6:
        *out = D_004A3940;
        break;
    case 14:
        *out = D_004A3940;
        break;
    case 9: {
        char* obj = (char*)D_004A33D8;
        sVE_266358* vt = *(sVE_266358**)obj;
        *out = vt[20].fn(obj + vt[20].delta) << 10;
        break;
    }
    case 0:
    case 4:
        break;
    }
    return 0;
}

//100%
extern int D_004A33D4;
extern char D_00537190[];
extern "C" char* strcpy(char* dst, const char* src);

extern "C" void func_00266550(char* dst)
{
    strcpy(dst, D_00537190);
    D_004A33D4 = 0x10;
}

// Maps a login error code to a UI message id for the current connection state.
extern "C" int cSharedLoginMan_McMapError(int err)
{
    switch (D_004A33D4) {
    case 2:
        switch (err) {
        case -2: return 9;
        case -4: return 4;
        }
        break;
    case 9:
        switch (err) {
        case -2: return 17;
        }
        break;
    case 4:
        switch (err) {
        case -2: return 9;
        case -3: return 13;
        case -4: return 4;
        case -5: return 13;
        case -7: return 13;
        }
        break;
    case 8:
        switch (err) {
        case -2: return 9;
        case -4: return 4;
        default: return 17;
        }
        break;
    case 5:
        switch (err) {
        case -2: return 9;
        case -3: return 14;
        case -4: return 4;
        case -5: return 13;
        case -8: return 13;
        }
        break;
    case 7:
        switch (err) {
        case -2: return 9;
        case -4: return 4;
        }
        break;
    case 6:
        switch (err) {
        case -2: return 9;
        case -4: return 4;
        case -5: return 13;
        }
        break;
    case 14:
        switch (err) {
        case -2: return 9;
        case -3: return 14;
        case -4: return 4;
        case -5: return 13;
        case -8: return 13;
        }
        break;
    case 11:
        switch (err) {
        case -2: return 9;
        case -3: return 14;
        case -4: return 8;
        }
        break;
    case 12:
    case 13:
        switch (err) {
        case -2: return 9;
        case -4: return 4;
        case -5: return 5;
        case -6: return 6;
        }
        break;
    case 1:
    case 3:
    case 10:
        break;
    }
    return 3;
}

//100%
extern char D_00481080[];
// PORT: operator_new really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");

extern "C" void* func_00266728(void* self, int size, int kind)
{
    int flags = 0x20000000;
    if (kind == 0x20) {
        flags = 0x23000000;
    }
    return operator_new_tag(size + 0x400, D_00481080, flags, 0);
}

//100%
void* cMemMan_free(void* ptr);

extern "C" void TibExtMemFree(void* self, void* ptr)
{
    if (ptr != 0) {
        cMemMan_free(ptr);
    }
}

//100%
extern char D_00481090[];
extern void* D_004A33F0;
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cUsbKeyboard_ctor(void* self);

extern "C" void func_00266788(void)
{
    D_004A33F0 = cUsbKeyboard_ctor(cMemMan_alloc(0x464, D_00481090, 0x20000000, 0));
}

extern void* D_004A33F0;
extern "C" void cUsbKeyboard_dtor(void* p, int a);

extern "C" void cUsbKeyboard_Destroy()
{
    if (D_004A33F0) {
        cUsbKeyboard_dtor(D_004A33F0, 3);
        D_004A33F0 = 0;
    }
}

//100%
extern char D_005371D0[];
extern "C" void cUsbKeyboard_OnConnect(void* self);
extern "C" int func_003F61D0(int a0, int a1, void* name, void* cb, int a4);
extern "C" void* func_003E6448(void* dst, int value, int size);

extern "C" void* cUsbKeyboard_ctor(void* self)
{
    *(int*)((char*)self + 0x460) = 0;
    if (func_003F61D0(0, 0, D_005371D0, (void*)cUsbKeyboard_OnConnect, 0) >= 0) {
        *(int*)((char*)self + 0x460) = 1;
    }
    func_003E6448(self, 0, 0x460);
    return self;
}

extern "C" void func_003F62F8(void* self);
void operator_delete(int*);

// Destructor: releases the table at +0x460 if one is held.
extern "C" void cUsbKeyboard_dtor(void* self, int flags)
{
    if (*(int*)((char*)self + 0x460) != 0) {
        func_003F62F8(self);
        *(int*)((char*)self + 0x460) = 0;
    }
    if (flags & 1)
        operator_delete((int*)self);
}

//100%
extern "C" void func_003F6358(void* self);
extern "C" void func_0040C7C0(void* self, int a1);
extern "C" void func_0040D430(void* self, int a1);

extern "C" void cUsbKeyboard_OnConnect(void* self)
{
    func_003F6358(self);
    func_0040C7C0(self, 0);
    func_0040D430(self, 0);
}

//100%
extern "C" void func_003F63F0();
extern "C" int func_003F6520(int idx);
extern "C" int func_003F6348();
extern "C" void* func_003F64E0(int idx);
extern "C" unsigned char* func_003F68F0(void* conn, int a1, int idx);
extern "C" int func_003F6838(void* conn, int a1, int a2, int a3);

struct sSlotFlags_668E8 {
    unsigned active : 1;
    unsigned b1 : 1;
    unsigned b2 : 1;
    unsigned b3 : 1;
    unsigned b4 : 1;
};

struct sSlot_668E8 {
    int count;                  // 0x0
    int start;                  // 0x4
    unsigned char buf[64][2];   // 0x8
    sSlotFlags_668E8 flags;     // 0x88
};

struct sSlots_668E8 {
    sSlot_668E8 slot[8];        // 0x0
    int enabled;                // 0x460
};

struct sConn_668E8 {
    unsigned on : 1;            // 0x0
    int f4;
    int count;                  // 0x8
};

static inline int ringIdx_668E8(int w)
{
    return w % 64;
}

extern "C" void cUsbKeyboard_Update(sSlots_668E8* self)
{
    if (self->enabled == 0)
        return;
    func_003F63F0();
    for (int i = 0; i < 8; i++) {
        sSlot_668E8* s = &self->slot[i];
        s->flags.active = func_003F6520(i) == 1;
        if (!s->flags.active)
            *(int*)&s->flags = 0;
    }
    int n = func_003F6348();
    for (int j = 0; j < n; j++) {
        if (self->slot[j].flags.active) {
            sConn_668E8* c = (sConn_668E8*)func_003F64E0(j);
            if (c != 0) {
                for (int k = 0; k < c->count; k++) {
                    unsigned char* e = func_003F68F0(c, 0, k);
                    if (e[0] != 0 || e[1] != 0) {
                        int w = self->slot[j].count;
                        int idx = ringIdx_668E8(w);
                        int r = self->slot[j].start;
                        if (w - r >= 0x40)
                            self->slot[j].start = r + 1;
                        self->slot[j].buf[idx][0] = e[0];
                        self->slot[j].buf[idx][1] = e[1];
                        self->slot[j].count++;
                    }
                }
                if (func_003F6838(c, 0, 0, 0x10))
                    self->slot[j].flags.b4 = 1;
                else
                    self->slot[j].flags.b4 = 0;
                self->slot[j].flags.b2 = c->on;
                self->slot[j].flags.b3 = c->on;
                self->slot[j].flags.b1 = c->on;
            }
        }
    }
}

//100%
struct sEnt8C {
    int a;
    int b;
    char pad[0x84];
};

struct sEntTable {
    sEnt8C ents[8];
    int active;
};

extern "C" void func_00266B80(sEntTable* self, int idx)
{
    if (self->active != 0) {
        self->ents[idx].b = 0;
        self->ents[idx].a = 0;
    }
}

//100%
// Pops the next byte pair from slot idx's ring; a zero byte leaves its output at -1.
extern "C" int cUsbKeyboard_GetKey(sSlots_668E8* self, int idx, int* a, int* b)
{
    *a = -1;
    *b = -1;
    if (self->enabled != 0 && idx < func_003F6348()) {
        if (self->slot[idx].start < self->slot[idx].count) {
            int k = ringIdx_668E8(self->slot[idx].start);
            if (self->slot[idx].buf[k][0] != 0)
                *a = self->slot[idx].buf[k][0];
            if (self->slot[idx].buf[k][1] != 0)
                *b = self->slot[idx].buf[k][1];
            self->slot[idx].start++;
            return 1;
        }
    }
    return 0;
}

//100%
extern char D_004810A0[];
extern void* D_004A33F4;
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
void* cVoipMan_ctor(void* self);

extern "C" void func_00266CA0(void)
{
    D_004A33F4 = cVoipMan_ctor(cMemMan_alloc(8, D_004810A0, 0x20000000, 0));
}

//100%
extern void* D_004A33F4;
extern "C" void cVoipMan_dtor(void* self, int flags);

extern "C" void func_00266CD8(void)
{
    if (D_004A33F4 != 0) {
        cVoipMan_dtor(D_004A33F4, 3);
        D_004A33F4 = 0;
    }
}

//100%
void* cVoipMan_ctor(void* self)
{
    int t0 = 0;
    *(int*)self = t0;
    *(int*)((char*)self + 0x4) = t0;
    return self;
}

//100%
extern "C" void func_00266DF8(void* self);
void operator_delete(int*);

extern "C" void cVoipMan_dtor(void* self, int flags)
{
    func_00266DF8(self);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
// PORT: PS2-only inline asm; needs a C fallback off-PS2.
extern int D_004A33F8;
extern int D_00535610[];
extern "C" void* cBE_getBE();
void* cBE_getInterface_Fv(void* be, int kind) __asm__("cBE_getInterface__Fv");
extern "C" void func_003F6AB8(void* a0, int a1, int a2);
extern "C" void func_003F6C10(int a0, int a1);
extern "C" void func_00266E88(void* self);
extern "C" void cVoipMan_Activate(void* self);

extern "C" void cVoipMan_Start(void* self, void* a1)
{
    if (*(int*)self == 0) {
        func_003F6AB8(a1, 6000, 6000);
        int n = D_004A33F8;
        *(int*)self = 1;
        func_003F6C10(n, 0x55);
        if (D_004A33F8 < 10) {
            func_00266E88(self);
        } else {
            cBE_getInterface_Fv(cBE_getBE(), 4);
            if ((D_00535610[0] >> 18) & 1) {
                cVoipMan_Activate(self);
            }
        }
    }
}

//100%
extern "C" void func_003F6AF0(void* self);

extern "C" void func_00266DF8(void* self)
{
    if (*(void**)self != 0) {
        func_003F6AF0(self);
        *(void**)self = 0;
    }
}

//100%
extern int D_004A33F8;
extern "C" void func_003F6B20();

extern "C" void cVoipMan_Activate(void* self)
{
    if (*(int*)self != 0 && *(int*)((char*)self + 0x4) == 0 && D_004A33F8 >= 10) {
        func_003F6B20();
        *(int*)((char*)self + 0x4) = 1;
    }
}

//100%
extern "C" void func_003F6B50(void* self);

extern "C" void func_00266E88(void* self)
{
    if (*(int*)self != 0 && *(int*)((char*)self + 0x4) != 0) {
        func_003F6B50(self);
        *(int*)((char*)self + 0x4) = 0;
    }
}

extern "C" void* func_003F6C40(void* self);

extern "C" void func_00266E88(void* self);
extern "C" void cVoipMan_Activate(void* self);

extern "C" void func_00266ED0(void* self)
{
    if (*(int*)((char*)self + 0x4))
        func_00266E88(self);
    else
        cVoipMan_Activate(self);
}

extern "C" int func_003F6B80(void* p);

extern "C" int func_00266F08(void* self)
{
    if (*(int*)self != 0)
        return func_003F6B80(self);
    return 0;
}

//100%
void* func_00266F38(void* self)
{
    return func_003F6C40(self);
}

//100%
extern int D_004A33F8;
extern "C" void func_003F6C10(int a0, int a1);

extern "C" void cVoipMan_SetVolume(void* self, int a1, int a2)
{
    if (*(int*)self != 0) {
        func_003F6C10(a1, a2);
    }
    D_004A33F8 = a1;
}

//100%
extern "C" void func_003F6BA0(void* a, void* b);

extern "C" void cVoipMan_GetStatus(void* self, void* a, void* b)
{
    if (*(int*)self != 0) {
        func_003F6BA0(a, b);
    }
}

extern "C" void* func_00266FC0(void* p, ...)
{
    return p;
}

//100%
// Lexicographic less-than of the char ranges [a, aend) and [b, bend).
extern "C" int func_00267000(const signed char* a, const signed char* aend, const signed char* b, const signed char* bend)
{
    for (; a != aend && b != bend; ++a, ++b)
    {
        if (*a < *b)
            return 1;
        if (*b < *a)
            return 0;
    }
    return a == aend && b != bend;
}

//100%
// Three-way lexicographic compare of the char ranges [a, aend) and [b, bend): -1, 0 or 1.
extern "C" int func_00267068(const signed char* a, const signed char* aend, const signed char* b, const signed char* bend)
{
    while (a != aend && b != bend)
    {
        if (*a < *b)
            return -1;
        if (*b < *a)
            return 1;
        ++a;
        ++b;
    }
    if (b == bend)
        return a != aend;
    return -1;
}

struct sDsListNode670C8 {
    sDsListNode670C8* next;
    sDsListNode670C8* prev;
};
void operator_delete(int*);

// Frees every node of the circular list whose sentinel is at +4, leaving it empty.
extern "C" void func_002670C8(void* self)
{
    sDsListNode670C8* n = (*(sDsListNode670C8**)((char*)self + 4))->next;
    while (n != *(sDsListNode670C8**)((char*)self + 4)) {
        sDsListNode670C8* next = n->next;
        operator_delete((int*)n);
        n = next;
    }
    (*(sDsListNode670C8**)((char*)self + 4))->next = *(sDsListNode670C8**)((char*)self + 4);
    (*(sDsListNode670C8**)((char*)self + 4))->prev = *(sDsListNode670C8**)((char*)self + 4);
}

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_0041610C(void* dst, const void* src, unsigned int n);
void* cMemMan_free(void* ptr);
void operator_delete(int*);
extern char D_004804A8[];

struct sPtrVec7128 {
    void* alloc;
    void** start;
    void** finish;
    void** eos;
};

static inline void** sPtrVec7128_allocate(unsigned int n)
{
    if (n == 1)
        return (void**)cMemMan_alloc(4, D_004804A8, 0x20000000, 0);
    return (void**)operator_new_tag(n * 4, D_004804A8, 0x20000000, 0);
}

static inline void sPtrVec7128_deallocate(void** p, unsigned int n)
{
    if (p != 0) {
        if (n == 1)
            operator_delete((int*)p);
        else
            cMemMan_free(p);
    }
}

static inline void** sPtrVec7128_copy(void** first, void** last, void** result)
{
    func_0041610C(result, first, (last - first) * sizeof(void*));
    return result + (last - first);
}

static inline void** sPtrVec7128_ucopy(void** first, void** last, void** result)
{
    return sPtrVec7128_copy(first, last, result);
}

static inline void sPtrVec7128_construct(void** p, void* const& v)
{
    if (p != 0)
        *p = v;
}

static inline void** sPtrVec7128_copy_backward(void** first, void** last, void** result)
{
    int n = last - first;
    func_0041610C(result - n, first, n * sizeof(void*));
    return result - n;
}

extern "C" void BuddyMan_MessageVectorInsert(sPtrVec7128* self, void** pos, void* const& x)
{
    if (self->finish != self->eos) {
        if (self->finish != 0)
            *self->finish = self->finish[-1];
        ++self->finish;
        void* x_copy = x;
        sPtrVec7128_copy_backward(pos, self->finish - 2, self->finish - 1);
        *pos = x_copy;
    } else {
        unsigned int old_size = self->finish - self->start;
        unsigned int len = old_size != 0 ? 2 * old_size : 1;
        void** new_start = sPtrVec7128_allocate(len);
        void** new_finish = new_start;
        new_finish = sPtrVec7128_ucopy(self->start, pos, new_start);
        sPtrVec7128_construct(new_finish, x);
        ++new_finish;
        new_finish = sPtrVec7128_ucopy(pos, self->finish, new_finish);
        sPtrVec7128_deallocate(self->start, self->eos - self->start);
        self->start = new_start;
        self->finish = new_finish;
        self->eos = new_start + len;
    }
}

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* func_0041610C(void* dst, const void* src, unsigned int n);
void* cMemMan_free(void* ptr);
void operator_delete(int*);
extern char D_004804A8[];

struct sPtrVec72C8 {
    void* alloc;
    void** start;
    void** finish;
    void** eos;
};

static inline void** sPtrVec72C8_allocate(unsigned int n)
{
    if (n == 1)
        return (void**)cMemMan_alloc(4, D_004804A8, 0x20000000, 0);
    return (void**)operator_new_tag(n * 4, D_004804A8, 0x20000000, 0);
}

static inline void sPtrVec72C8_deallocate(void** p, unsigned int n)
{
    if (p != 0) {
        if (n == 1)
            operator_delete((int*)p);
        else
            cMemMan_free(p);
    }
}

static inline void** sPtrVec72C8_copy(void** first, void** last, void** result)
{
    func_0041610C(result, first, (last - first) * sizeof(void*));
    return result + (last - first);
}

static inline void** sPtrVec72C8_ucopy(void** first, void** last, void** result)
{
    return sPtrVec72C8_copy(first, last, result);
}

static inline void sPtrVec72C8_construct(void** p, void* const& v)
{
    if (p != 0)
        *p = v;
}

static inline void** sPtrVec72C8_copy_backward(void** first, void** last, void** result)
{
    int n = last - first;
    func_0041610C(result - n, first, n * sizeof(void*));
    return result - n;
}

extern "C" void BuddyMan_ChallengerVectorInsert(sPtrVec72C8* self, void** pos, void* const& x)
{
    if (self->finish != self->eos) {
        if (self->finish != 0)
            *self->finish = self->finish[-1];
        ++self->finish;
        void* x_copy = x;
        sPtrVec72C8_copy_backward(pos, self->finish - 2, self->finish - 1);
        *pos = x_copy;
    } else {
        unsigned int old_size = self->finish - self->start;
        unsigned int len = old_size != 0 ? 2 * old_size : 1;
        void** new_start = sPtrVec72C8_allocate(len);
        void** new_finish = new_start;
        new_finish = sPtrVec72C8_ucopy(self->start, pos, new_start);
        sPtrVec72C8_construct(new_finish, x);
        ++new_finish;
        new_finish = sPtrVec72C8_ucopy(pos, self->finish, new_finish);
        sPtrVec72C8_deallocate(self->start, self->eos - self->start);
        self->start = new_start;
        self->finish = new_finish;
        self->eos = new_start + len;
    }
}

INCLUDE_ASM("dirtysock/tagsunk", LobbyMan_StaticInit);

extern "C" void* cDSockChannel_ResetState(void* self);

extern "C" int func_00267D88(void* self)
{
    return *(int*)((char*)self + 0x0);
}

extern "C" void func_00267D90(void* self)
{
    *(int*)((char*)self + 0x4) = 0x1;
}

extern "C" int func_00267DA0(void* self)
{
    return *(int*)((char*)self + 0x4);
}

//100%
void* cDSockChannel_Base_Disconnect(void* self)
{
    return cDSockChannel_ResetState(self);
}

//100%
void cDSockChannel_Base_Update(void* self)
{
}

//100%
int cDSockChannel_Base_IsConnected(void* self)
{
    return 0;
}

//100%
extern "C" float cDSockChannel_Base_v05(void)
{
    return 0.01666666753590107f;
}

//100%
int cDSockChannel_Base_v06(void* self)
{
    return 0;
}

//100%
int cDSockChannel_Base_Recv(void* self)
{
    return 0;
}

//100%
int cDSockChannel_Base_Send(void* self)
{
    return 0;
}

//100%
extern "C" int cDSockChannel_IsConnected(void* self)
{
    return *(int*)((char*)self + 0xc) == 2;
}

//100%
int cDSockChannel_v06(void* self)
{
    return 0x1;
}

//100%
extern void* D_004812B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void NetEvent_dtor(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern char D_00480488[];
extern void* D_004812B0[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

extern "C" void* NetEvent_Clone(int* self)
{
    int* p = (int*)cMemMan_alloc(8, D_00480488, 0x20000000, 0);
    int v = *self;
    *(void***)((char*)p + 0x4) = D_004812B0;
    p[0] = v;
    return p;
}

//100%
extern void* D_004812B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void NetEvent102_dtor(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern char D_00480488[];
extern void* D_00481290[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

extern "C" void* NetEvent102_Clone(void* self)
{
    int* p = (int*)cMemMan_alloc(0xC, D_00480488, 0x20000000, 0);
    int v = *(int*)((char*)self + 0x8);
    p[0] = 0x102;
    *(void***)((char*)p + 0x4) = D_00481290;
    p[2] = v;
    return p;
}

//100%
extern void* D_004812B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void func_00267F28(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern char D_00480488[];
extern void* D_00481290[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

extern "C" void* func_00267F58(void* self)
{
    int* p = (int*)cMemMan_alloc(0xC, D_00480488, 0x20000000, 0);
    int v = *(int*)((char*)self + 0x8);
    p[0] = 0x102;
    *(void***)((char*)p + 0x4) = D_00481290;
    p[2] = v;
    return p;
}

//100%
extern void* D_004812B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void NetErrorEvent_dtor(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern char D_00480488[];
extern void* D_00481250[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

extern "C" void* NetErrorEvent_Clone(void* self)
{
    int* p = (int*)cMemMan_alloc(0xC, D_00480488, 0x20000000, 0);
    int v = *(int*)((char*)self + 0x8);
    p[0] = 0x116;
    *(void***)((char*)p + 0x4) = D_00481250;
    p[2] = v;
    return p;
}

//100%
extern void* D_004812B0[];
extern "C" void cBXString__cBXString(void* self, int flags);
void operator_delete(int*);

extern "C" void func_00268048(void* self, int flags)
{
    cBXString__cBXString((char*)self + 0xC, 2);
    cBXString__cBXString((char*)self + 0x8, 2);
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern "C" void cBXString__cBXString(void* self, int flags);
extern "C" void* cBXString_cBXString1(void* self, void* other);
extern char D_00480498[];
extern void* D_00481230[];

// Stand-in for cBXString (defined elsewhere): a class with a non-trivial copy constructor,
// which g++ keeps in memory (BLKmode, 16-byte stack slots).
struct sBXStrK2 {
    char* s;
    sBXStrK2() {}
    sBXStrK2(const sBXStrK2& o);
};

// Clone of a two-string message (type 0xDE).
extern "C" void* func_002680A8(char* self)
{
    char* p = (char*)cMemMan_alloc(0x10, D_00480498, 0x20000000, 0);
    sBXStrK2 a;
    sBXStrK2 b;
    cBXString_cBXString1(&a, self + 0x8);
    cBXString_cBXString1(&b, self + 0xC);
    *(void***)(p + 0x4) = D_00481230;
    *(int*)p = 0xDE;
    cBXString_cBXString1(p + 0x8, &a);
    cBXString_cBXString1(p + 0xC, &b);
    cBXString__cBXString(&a, 2);
    cBXString__cBXString(&b, 2);
    return p;
}

//100%
extern void* D_004812B0[];
extern "C" void cBXString__cBXString(void* self, int flags);
void operator_delete(int*);

extern "C" void func_00268158(void* self, int flags)
{
    cBXString__cBXString((char*)self + 0x8, 2);
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern char D_00480488[];
extern void* D_00481210[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cBXString_cBXString2(void* self, const char* s);

extern "C" void* func_002681B0(void* self)
{
    int* p = (int*)cMemMan_alloc(0xC, D_00480488, 0x20000000, 0);
    const char* s = *(const char**)((char*)self + 0x8);
    *(void***)((char*)p + 0x4) = D_00481210;
    p[0] = 0xE2;
    cBXString_cBXString2((char*)p + 0x8, s);
    return p;
}

//100%
extern void* D_004812B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void NetEvent102Tooy_dtor(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern char D_00480488[];
extern void* D_004811F0[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

extern "C" void* NetEvent102Tooy_Clone(void* self)
{
    int* p = (int*)cMemMan_alloc(0x10, D_00480488, 0x20000000, 0);
    int b = *(int*)((char*)self + 0xC);
    p[0] = 0x102;
    p[2] = 0x746F6F79;
    *(void***)((char*)p + 0x4) = D_004811F0;
    p[3] = b;
    return p;
}

//100%
extern void* D_004812B0[];
extern "C" void cBXString__cBXString(void* self, int flags);
void operator_delete(int*);

extern "C" void NetEvent102Lock_dtor(void* self, int flags)
{
    cBXString__cBXString((char*)self + 0x10, 2);
    cBXString__cBXString((char*)self + 0xC, 2);
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
void* operator new(unsigned int size, const char* tag, unsigned int flags, int d) __asm__("cMemMan_alloc");
extern "C" void* cBXString_cBXString2(void* self, const char* s);
extern char D_00480488[];
extern char D_004811D0[];

struct sLockMsg268308 {
    int type;       // 0x00
    char* name;     // 0x04
    int tag;        // 0x08
    char a[4];      // 0x0C
    char b[4];      // 0x10
};

static inline void Init268308(sLockMsg268308* m, const char* a, const char* b)
{
    m->type = 0x102;
    m->tag = 0x6C6F636B;
    m->name = D_004811D0;
    cBXString_cBXString2(m->a, a);
    cBXString_cBXString2(m->b, b);
}

// Builds a "lock" message carrying the two name strings of this request.
extern "C" void* NetEvent102Lock_Clone(char* self)
{
    sLockMsg268308* m = (sLockMsg268308*)operator new(0x14, D_00480488, 0x20000000, 0);
    Init268308(m, *(const char**)(self + 0xC), *(const char**)(self + 0x10));
    return m;
}

//100%
extern void* D_004812B0[];
extern "C" void cBXString__cBXString(void* self, int flags);
void operator_delete(int*);

extern "C" void NetEvent102Down_dtor(void* self, int flags)
{
    cBXString__cBXString((char*)self + 0xC, 2);
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern void* D_004811B0[];

extern "C" void* NetEvent102Down_Clone(void* self)
{
    int* p = (int*)cMemMan_alloc(0x10, D_00480488, 0x20000000, 0);
    const char* s = *(const char**)((char*)self + 0xC);
    p[2] = 0x646F776E;
    *(void***)((char*)p + 0x4) = D_004811B0;
    p[0] = 0x102;
    cBXString_cBXString2((char*)p + 0xC, s);
    return p;
}

//100%
extern void* D_004812B0[];
extern "C" void cBXString__cBXString(void* self, int flags);
void operator_delete(int*);

extern "C" void func_00268460(void* self, int flags)
{
    cBXString__cBXString((char*)self + 0xC, 2);
    cBXString__cBXString((char*)self + 0x8, 2);
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
// Clones an 0xE3 message (sMsgE7F0).
struct sMsgE3_2684C0 : sMsgE7F0 {
    sMsgE3_2684C0(const char* n, const char* t, int o, int c, const sRecE7F0& r)
    {
        vt = D_00481190;
        type = 0xE3;
        cBXString_cBXString2(name, n);
        cBXString_cBXString2(text, t);
        on = o;
        count = c;
        rec = r;
    }
};

extern "C" void* func_002684C0(void* self)
{
    sMsgE7F0* src = (sMsgE7F0*)self;
    return new (D_00480488, 0x20000000, 0) sMsgE3_2684C0(*(const char**)src->name, *(const char**)src->text, src->on, src->count, src->rec);
}

//100%
extern void* D_004812B0[];
extern "C" void cBXString__cBXString(void* self, int flags);
void operator_delete(int*);

extern "C" void func_00268588(void* self, int flags)
{
    cBXString__cBXString((char*)self + 0x8, 2);
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern void* D_00481170[];

extern "C" void* func_002685E0(void* self)
{
    int* p = (int*)cMemMan_alloc(0x10, D_00480488, 0x20000000, 0);
    int b = *(int*)((char*)self + 0xC);
    const char* s = *(const char**)((char*)self + 0x8);
    *(void***)((char*)p + 0x4) = D_00481170;
    p[0] = 0xE5;
    cBXString_cBXString2((char*)p + 0x8, s);
    p[3] = b;
    return p;
}

//100%
extern void* D_004812B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void func_00268658(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern char D_00480488[];
extern void* D_00481150[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

extern "C" void* func_00268688(void* self)
{
    int* p = (int*)cMemMan_alloc(0x10, D_00480488, 0x20000000, 0);
    int a = *(int*)((char*)self + 0x8);
    int b = *(int*)((char*)self + 0xC);
    p[0] = 0xFB;
    *(void***)((char*)p + 0x4) = D_00481150;
    p[2] = a;
    p[3] = b;
    return p;
}

//100%
extern void* D_004812B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void func_002686F0(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern void* D_00481130[];

extern "C" void* func_00268720(void* self)
{
    int* p = (int*)cMemMan_alloc(0x14, D_00480488, 0x20000000, 0);
    int a = *(int*)((char*)self + 0x8);
    int b = *(int*)((char*)self + 0xC);
    int c = *(int*)((char*)self + 0x10);
    p[0] = 0xFC;
    *(void***)((char*)p + 0x4) = D_00481130;
    p[2] = a;
    p[3] = b;
    p[4] = c;
    return p;
}

//100%
extern void* D_004812B0[];
void operator_delete(int*);

// deleting destructor: reset the vtable, free when bit 0 of flags is set
extern "C" void func_00268790(void* self, int flags)
{
    *(void***)((char*)self + 0x4) = D_004812B0;
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
extern char D_00480488[];
extern void* D_00481110[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" char* strcpy(char* dst, const char* src);

struct sDsBlob14K2b {
    int v[5];
};

// Clone of a message of type 0x10D (three names, two ints, a 20-byte blob).
extern "C" void* func_002687C0(char* self)
{
    char* p = (char*)cMemMan_alloc(0x164, D_00480488, 0x20000000, 0);
    const char* b = self + 0x28;
    int x = *(int*)(self + 0x148);
    int y = *(int*)(self + 0x14C);
    const char* c;
    *(void***)(p + 0x4) = D_00481110;
    *(int*)p = 0x10D;
    c = self + 0x48;
    *(int*)(p + 0x148) = x;
    *(int*)(p + 0x14C) = y;
    strcpy(p + 0x8, self + 0x8);
    strcpy(p + 0x28, b);
    strcpy(p + 0x48, c);
    *(sDsBlob14K2b*)(p + 0x150) = *(sDsBlob14K2b*)(self + 0x150);
    return p;
}

