#include "common.h"

//100%
// PORT: operator_new__FUi really takes (size, tag, flags, d), like cMemMan_alloc.
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" void func_003E6448(void* dst, unsigned int value, int size);
extern char D_0048DD00[];

extern "C" void cInputMap_init(void* self, int count)
{
    *(int*)((char*)self + 0x0) = count;
    *(void**)((char*)self + 0x4) = operator_new_tag(count * 4, D_0048DD00, 0, 0);
    func_003E6448(*(void**)((char*)self + 0x4), 0xFFFFFFFF, *(int*)((char*)self + 0x0) * 4);
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0xC) = 0;
    *(int*)((char*)self + 0x10) = 0;
}

//100%
void cMemMan_free(void* p);

extern "C" void func_00320D08(void* self)
{
    if (*(void**)((char*)self + 0x4) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x4));
    }
    if (*(void**)((char*)self + 0x14) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x14));
    }
}

//100%
extern "C" unsigned char* func_003E1A10(const char* name, int* size, int flags);
extern "C" void cInputMap_loadMapFile(void* self, void* a1, void* a2);

extern "C" void func_00320D50(void* self, const char* name)
{
    int size;
    unsigned char* buf = func_003E1A10(name, &size, 0x100);
    cInputMap_loadMapFile(self, buf, (void*)size);
    if (buf != 0) {
        cMemMan_free(buf);
    }
}

//100%
extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cInputMapParser_ctor(void* self, void* a1, void* a2);
extern char D_0048DD10[];

extern "C" void cInputMap_loadMapFile(void* self, void* a1, void* a2)
{
    *(void**)((char*)self + 0x8) = cInputMapParser_ctor(cMemMan_alloc(0x109EC, D_0048DD10, 0x100, 0), a1, a2);
}

//100%
void cMemMan_free(void* p);
extern "C" void func_003E6574(void* dst, void* src, int size);
// PORT: operator_new__FUi really takes (size, tag, flags, d); bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
extern "C" int cInputMapParser_compileStatement(void* parser, char* src, int* dst, int room, int a4);
extern char D_0048DD20[];

struct sInputMap_0E18 {
    int f0;
    int* offsets;   // 0x4
    void* parser;   // 0x8
    int cap;        // 0xC
    int used;       // 0x10
    int* code;      // 0x14
};

extern "C" void cInputMap_compileMap(sInputMap_0E18* self, int idx, char* src)
{
    if (self->cap - self->used < 0x100) {
        int newCap = self->cap + 0x400;
        int* buf = (int*)operator_new_tag(newCap * 4, D_0048DD20, 0x100, 0);
        if (self->code != 0) {
            func_003E6574(buf, self->code, self->cap * 4);
            if (self->code != 0) {
                cMemMan_free(self->code);
            }
        }
        self->code = buf;
        self->cap = newCap;
    }
    self->offsets[idx] = self->used;
    self->used += cInputMapParser_compileStatement(self->parser, src, self->code + self->used, self->cap - self->used, 5);
}

//100%
// PORT: operator new with tag args bound by asm label
void* operator_new_tag(unsigned int size, const char* tag, int flags, int d) __asm__("operator_new__FUi");
void operator_delete(int* p);
void cMemMan_free(void* p);
extern "C" void func_003E6574(void* dst, void* src, int size);
extern char D_0048DD30[];

extern "C" void cInputMap_purgeMapFile(void* self)
{
    if (*(int**)((char*)self + 0x8) != 0) {
        operator_delete(*(int**)((char*)self + 0x8));
    }
    *(int**)((char*)self + 0x8) = 0;
    void* p = operator_new_tag(*(int*)((char*)self + 0x10) << 2, D_0048DD30, 0, 0);
    func_003E6574(p, *(void**)((char*)self + 0x14), *(int*)((char*)self + 0x10) << 2);
    if (*(void**)((char*)self + 0x14) != 0) {
        cMemMan_free(*(void**)((char*)self + 0x14));
    }
    *(void**)((char*)self + 0x14) = p;
    *(int*)((char*)self + 0xC) = *(int*)((char*)self + 0x10);
}

//100%
void* func_00325250(void* self);
extern "C" float func_00325450(void* parser, void* a1, void* a2);

extern "C" float func_00320FA8(void* self, void* a1, int a2)
{
    char parser[0x190];
    func_00325250(parser);
    return func_00325450(parser, a1, (char*)*(void**)((char*)self + 0x14) + ((*(int**)((char*)self + 0x4))[a2] << 2));
}

//100%
// As func_00320FA8 with the user word and eight float inputs set in the parser.
extern "C" float func_00321010(void* self, void* a1, int a2, int user, float v0, float v1, float v2, float v3, float v4, float v5, float v6, float v7)
{
    char parser[0x190];
    func_00325250(parser);
    *(int*)parser = user;
    *(float*)(parser + 0x10C) = v0;
    *(float*)(parser + 0x110) = v1;
    *(float*)(parser + 0x114) = v2;
    *(float*)(parser + 0x118) = v3;
    *(float*)(parser + 0x11C) = v4;
    *(float*)(parser + 0x120) = v5;
    *(float*)(parser + 0x124) = v6;
    *(float*)(parser + 0x128) = v7;
    return func_00325450(parser, a1, (char*)*(void**)((char*)self + 0x14) + ((*(int**)((char*)self + 0x4))[a2] << 2));
}

//100%
void* func_00325250(void* self);
extern "C" float func_00325450(void* parser, void* a1, void* a2);

extern "C" int func_00321108(void* self, void* a1, int a2)
{
    char parser[0x190];
    func_00325250(parser);
    return func_00325450(parser, a1, (char*)*(void**)((char*)self + 0x14) + ((*(int**)((char*)self + 0x4))[a2] << 2)) != 0.0f;
}

//100%
// As func_00320FA8 with the user word and eight float inputs set in the parser.
extern "C" int func_00321188(void* self, void* a1, int a2, int user, float v0, float v1, float v2, float v3, float v4, float v5, float v6, float v7)
{
    char parser[0x190];
    func_00325250(parser);
    *(int*)parser = user;
    *(float*)(parser + 0x10C) = v0;
    *(float*)(parser + 0x110) = v1;
    *(float*)(parser + 0x114) = v2;
    *(float*)(parser + 0x118) = v3;
    *(float*)(parser + 0x11C) = v4;
    *(float*)(parser + 0x120) = v5;
    *(float*)(parser + 0x124) = v6;
    *(float*)(parser + 0x128) = v7;
    return func_00325450(parser, a1, (char*)*(void**)((char*)self + 0x14) + ((*(int**)((char*)self + 0x4))[a2] << 2)) != 0.0f;
}

//100%
struct sBtn_00321298 {
    float value;    // 0x00
    int pressed;    // 0x04
    int released;   // 0x08
    int down;       // 0x0C
    int repeat;     // 0x10
    int timer;      // 0x14
    int settle;     // 0x18
};
struct sBtnSet_00321298 {
    int count;
    sBtn_00321298 b[1];
};

extern "C" void func_00321298(sBtnSet_00321298* self, int n, float* vals)
{
    if (self->count < n) {
        func_003E6448(&self->b[self->count], 0, (n - self->count) * sizeof(sBtn_00321298));
    }
    self->count = n;
    for (int i = 0; i < n; i++) {
        self->b[i].value = vals[i];
        if (self->b[i].settle < 3) {
            self->b[i].pressed = 0;
            self->b[i].settle++;
            self->b[i].released = 0;
        } else {
            int on = self->b[i].value > 0.0f;
            if (on == self->b[i].down) {
                self->b[i].pressed = 0;
                self->b[i].released = 0;
            } else {
                self->b[i].down = on;
                if (on) {
                    self->b[i].pressed = 1;
                    self->b[i].released = 0;
                } else {
                    self->b[i].pressed = 0;
                    self->b[i].released = 1;
                }
                self->b[i].settle = 0;
            }
        }
        if (self->b[i].down) {
            if (self->b[i].timer == 0) {
                self->b[i].repeat = 1;
                self->b[i].timer = 0x18;
            } else {
                self->b[i].timer--;
                if (self->b[i].timer <= 0) {
                    self->b[i].repeat = 1;
                    self->b[i].timer = 0xC;
                } else {
                    self->b[i].repeat = 0;
                }
            }
        } else {
            self->b[i].repeat = 0;
            self->b[i].timer = 0;
        }
    }
}

//100%
struct sParseNode_1428 {
    int f0;
    sParseNode_1428* next;      // 0x4
    int f8;
    int fC;
};

struct sParser_1428 {
    char* src;                  // 0x0
    int len;                    // 0x4
    char* cur;                  // 0x8
    char tok[0x80];             // 0xC
    int line;                   // 0x8C
    int col;                    // 0x90
    int err;                    // 0x94
    char pad_0x98[0x48];
    sParseNode_1428* freeNodes; // 0xE0
    sParseNode_1428 nodes[0x800];   // 0xE4
    int f80E4;                  // 0x80E4
    char pad_0x80E8[0x108EC - 0x80E8];
    int freeRegs[63];           // 0x108EC
    int numFree;                // 0x109E8
};

extern "C" void func_00323098(void* self);

// Sets up the expression parser over src: free register list 63..1 and the node free list.
extern "C" void* cInputMapParser_ctor(void* selfp, void* srcp, void* lenp)
{
    sParser_1428* self = (sParser_1428*)selfp;
    char* src = (char*)srcp;
    int len = (int)lenp;
    self->len = len;
    self->src = src;
    self->cur = src;
    self->f80E4 = 0;
    self->line = 1;
    self->col = 1;
    self->tok[0] = 0;
    self->err = 0;
    self->numFree = 0;
    for (int i = 0x3F; i > 0; i--) {
        self->freeRegs[self->numFree++] = i;
    }
    self->freeNodes = self->nodes;
    // Link the node free list (walks the next fields 16 bytes at a time).
    sParseNode_1428** pn = &self->nodes[0].next;
    sParseNode_1428* m = self->nodes + 1;
    for (int j = 0x7FE; j >= 0; j--) {
        *pn = m;
        pn += 4;
        m++;
    }
    self->nodes[0x7FF].next = 0;
    func_00323098(self);
    return self;
}

//100%
// PORT: hand-rolled EE EABI va_start (gcc 2.95 va-mips.h form); use <stdarg.h> off-PS2.
typedef char* func_00321500_va_list;
#define func_00321500_va_start(ap)                                       \
    (ap = (char*)__builtin_next_arg()                                    \
          - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))

extern "C" int sprintf(char* dst, const char* fmt, ...);
extern "C" int func_004186C8(char* dst, const char* fmt, char* ap);
extern char D_0048DD40[];

extern "C" void func_00321500(void* self, const char* fmt, ...)
{
    char buf[0x400];
    func_00321500_va_list ap;
    func_00321500_va_start(ap);
    func_004186C8(buf + sprintf(buf, D_0048DD40, (char*)self + 0xC, *(int*)((char*)self + 0x8C)), fmt, ap);
    *(int*)((char*)self + 0x94) = 1;
}

//100%
extern "C" void cInputMapParser_readToken(void* self);

extern "C" void func_00321590(void* self)
{
    while (*(int*)((char*)self + 0x98) != 5 && *(int*)((char*)self + 0x98) != 0) {
        cInputMapParser_readToken(self);
    }
    cInputMapParser_readToken(self);
}

//100%
extern "C" void* func_00416210(void* dst, int c, int n);

extern "C" void* func_003215F8(void* self)
{
    void* p = *(void**)((char*)self + 0xE0);
    *(void**)((char*)self + 0xE0) = *(void**)((char*)p + 4);
    func_00416210(p, 0, 0x10);
    return p;
}

//100%
extern "C" void func_00321638(char* self, int* node)
{
    if (node == 0)
        return;
    switch (node[0]) {
    case 18: case 19: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32: case 33:
        func_00321638(self, (int*)node[1]);
        break;
    case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 20: case 21:
        func_00321638(self, (int*)node[1]);
        func_00321638(self, (int*)node[2]);
        break;
    case 5:
        func_00321638(self, (int*)node[1]);
        func_00321638(self, (int*)node[2]);
        func_00321638(self, (int*)node[3]);
        break;
    case 0: case 1: case 2: case 3: case 4: case 22: case 23:
        break;
    }
    node[1] = *(int*)(self + 0xE0);
    *(int**)(self + 0xE0) = node;
}

//100%
extern "C" int strncasecmp(const char* a, const char* b, int n);
extern char D_004A3EF0[];

extern "C" int func_003216E8(void* self, char* name)
{
    if (strncasecmp(name, D_004A3EF0, 6) != 0) {
        return -1;
    }
    int d = name[6] - '0';
    if ((unsigned char)d >= 10) {
        return -1;
    }
    int n = d;
    char* p = name + 7;
    while ((unsigned)(*p - '0') < 10) {
        n = n * 10 + (*p++ - '0');
    }
    int alpha = 0;
    if ((unsigned)(*p - 'a') < 26 || (unsigned)(*p - 'A') < 26) {
        alpha = 1;
    }
    if (alpha) {
        return -1;
    }
    if (*p != '_' && n < 0x39C) {
        return n;
    }
    return -1;
}

