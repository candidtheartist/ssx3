#include "common.h"

void operator_delete(int* ptr);

struct sTriggerNode {
    void* pad;
    sTriggerNode* next;
};

struct cActiveTriggerList {
    sTriggerNode* head;
};

//100%
void cActiveTriggerList_purge(cActiveTriggerList* self)
{
    sTriggerNode* node = self->head;
    if (node != 0) {
        do {
            sTriggerNode* next = node->next;
            operator_delete((int*)node);
            node = next;
        } while (node != 0);
    }
    self->head = 0;
}

//100%
extern "C" void func_0016C678(cActiveTriggerList* self)
{
    sTriggerNode* node = self->head;
    if (node != 0) {
        do {
            *(int*)((char*)node + 0xC) = 0;
            *(int*)((char*)node + 0x8) = 0;
            node = node->next;
        } while (node != 0);
    }
}

//100%
extern "C" sTriggerNode* func_0016C6B0(cActiveTriggerList* self, void* key)
{
    sTriggerNode* node = self->head;
    if (node != 0) {
        do {
            if (node->pad == key) {
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

//100%
extern "C" void* func_0016C6E0(cActiveTriggerList* self, void* key)
{
    sTriggerNode* node = self->head;
    if (node != 0) {
        do {
            void* item = node->pad;
            if (*(void**)item == key) {
                return item;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern char D_0045BF68[];

extern "C" void cActiveTriggerList_add(cActiveTriggerList* self, void* item)
{
    sTriggerNode* n = (sTriggerNode*)cMemMan_alloc(0x10, D_0045BF68, 0x20000000, 0);
    sTriggerNode* old = self->head;
    self->head = n;
    n->pad = item;
    n->next = old;
    *(int*)((char*)n + 0xC) = 1;
    *(int*)((char*)n + 0x8) = 1;
}

//100%
extern "C" sTriggerNode* func_0016C778(cActiveTriggerList* self, sTriggerNode* target)
{
    sTriggerNode* head = self->head;
    if (target == head) {
        sTriggerNode* next = target->next;
        operator_delete((int*)target);
        self->head = next;
        return next;
    }
    sTriggerNode* prev = head;
    for (sTriggerNode* node = prev->next; node != 0; node = node->next) {
        if (node == target) {
            prev->next = node->next;
            operator_delete((int*)node);
            return prev->next;
        }
        prev = node;
    }
    return 0;
}

//100%
void* func_0016BEE8(void* self);
void* func_0016C5D0(void* self);
extern "C" void* func_0016D210(void* self);

extern "C" void* cCameraTriggerMan_ctor(void* self)
{
    char* p;
    int i;
    func_0016BEE8(self);
    p = (char*)self + 0x14;
    for (i = 1; i != -1; i--, p += 4) {
        func_0016C5D0(p);
    }
    p = (char*)self + 0x1C;
    for (i = 1; i != -1; i--, p += 0x20) {
        func_0016D210(p);
    }
    return self;
}

//100%
extern "C" void cCameraTriggerMan_purge(void* self);
extern "C" void func_0016C5E0(void* self, int flags);
extern "C" void func_0016BEF8(void* self, int flags);

extern "C" void cCameraTriggerMan_dtor(void* self, int flags)
{
    cCameraTriggerMan_purge(self);
    if ((char*)self + 0x14 != 0) {
        char* p = (char*)self + 0x14 + 8;
        while ((char*)self + 0x14 != p) {
            p -= 4;
            func_0016C5E0(p, 0);
        }
    }
    func_0016BEF8(self, 2);
    if (flags & 1) {
        operator_delete((int*)self);
    }
}

//100%
struct cCameraTriggerList;
struct cCameraTriggerStack;
void cCameraTriggerList_init(cCameraTriggerList* self);
void cCameraTriggerStack_init(cCameraTriggerStack* self);
extern "C" void cCamera_resetChaseControllerSwitches(void);

extern "C" void func_0016C918(void* self)
{
    cCameraTriggerList_init((cCameraTriggerList*)self);
    cActiveTriggerList_purge((cActiveTriggerList*)((char*)self + 0x14));
    cActiveTriggerList_purge((cActiveTriggerList*)((char*)self + 0x18));
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)self + 0x1C));
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)self + 0x3C));
    cCamera_resetChaseControllerSwitches();
}

//100%
struct cCameraTriggerStack;
void cCameraTriggerStack_init(cCameraTriggerStack* self);
extern "C" void cCamera_resetChaseControllerSwitches(void);

extern "C" void cCameraTriggerMan_ResetActive(void* self)
{
    cActiveTriggerList_purge((cActiveTriggerList*)((char*)self + 0x14));
    cActiveTriggerList_purge((cActiveTriggerList*)((char*)self + 0x18));
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)self + 0x1C));
    cCameraTriggerStack_init((cCameraTriggerStack*)((char*)self + 0x3C));
    cCamera_resetChaseControllerSwitches();
}

