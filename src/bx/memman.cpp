#include "common.h"

extern unsigned int D_004A3E84;
extern const char D_004A3E88[];
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);

//100%
void* operator_new1(int size)
{
    return cMemMan_alloc(size, D_004A3E88, D_004A3E84, 0);
}

//100%
void* operator_new2(int size)
{
    return cMemMan_alloc(size, D_004A3E88, D_004A3E84, 0);
}

INCLUDE_ASM("bx/memman", cMemMan_alloc);

//100%
// PORT: the target calls the 4-arg cMemMan_alloc with only $a0 set (a1..a3 left as-is).
void* cMemMan_alloc1(unsigned int size) __asm__("cMemMan_alloc");

void* operator_new(unsigned int size)
{
    return cMemMan_alloc1(size);
}

extern void* gMemMutex[16];
extern "C" void MUTEX_lock(void* mutex);
extern "C" void MUTEX_unlock(void* mutex);
extern "C" void cMemMan_internalFree(void* ptr);

//100%
void operator_delete(int* ptr)
{
    MUTEX_lock(gMemMutex);
    cMemMan_internalFree(ptr);
    MUTEX_unlock(gMemMutex);
}

//100%
void cMemMan_free(void* ptr)
{
    MUTEX_lock(gMemMutex);
    cMemMan_internalFree(ptr);
    MUTEX_unlock(gMemMutex);
}

//100%
// Locks and immediately unlocks the memory manager mutex.
extern "C" void func_00317EE0()
{
    MUTEX_lock(gMemMutex);
    MUTEX_unlock(gMemMutex);
}

extern "C" void cMemMan_purge();

extern "C" void func_00317F18()
{
    cMemMan_purge();
}
