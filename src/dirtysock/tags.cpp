#include "common.h"

//100%
char* cDirtysock_tag__TagFieldSetupAppend(char* buf, char* dst, char* name)
{
    if (name == 0) {
        *buf = 0;
    } else {
        while (*name != 0) {
            *dst++ = *name++;
        }
        *dst++ = '=';
    }
    return dst;
}

extern char D_004A4A70;
extern unsigned char D_004964C0[];
extern "C" int func_00415FC8(const void* a, const void* b, unsigned int n);
extern "C" void* func_0041610C(void* dst, const void* src, unsigned int n);
extern "C" void* func_0041605C(void* dst, const void* src, unsigned int n);

// Adds or replaces the "name=value" term temp in the record. Names compare
// through the D_004964C0 class table; "~..." terms are appended at the end.
extern "C" int cDirtysock_tag__TagFieldSetupTerm(char* record, int len, char* temp)
{
    unsigned char* rec = (unsigned char*)record;
    unsigned char* p;
    unsigned char* start;
    unsigned char* end;
    int n;
    int d;
    unsigned int a;
    unsigned int b;
    if (rec == 0) return -1;
    if (temp == 0 || (unsigned char)*temp <= ' ') return -1;
    if (*temp == '~') {
        p = rec;
        while (*p != 0) p++;
        if (p != rec && p[-1] >= 0x20 && p[-1] != D_004A4A70 && p < rec + len - 1) {
            *p++ = D_004A4A70;
            *p = 0;
        }
        end = p;
        start = p;
    } else {
        p = rec;
        for (;;) {
            if (*p == 0) {
                if (p != rec && p[-1] >= 0x20 && p[-1] != D_004A4A70 && p < rec + len - 1) {
                    *p++ = D_004A4A70;
                    *p = 0;
                }
                end = p;
                start = p;
                break;
            }
            if (*p <= ' ') {
                p++;
                continue;
            }
            if (D_004964C0[*p] == 1) {
                end = p;
                start = p;
                break;
            }
            a = D_004964C0[*p];
            b = D_004964C0[*temp];
            n = 0;
            while (a == b && a >= 2) {
                n++;
                a = D_004964C0[p[n]];
                b = D_004964C0[temp[n]];
            }
            if (a + b == 2) {
                end = p;
                start = p;
                while (*end >= 0x20) end++;
                if (*end != 0) end++;
                goto found;
            }
            p++;
            while (*p >= 0x20) p++;
        }
    }
found:
    int old = end - p;
    n = 0;
    while (temp[n] >= 0x20) n++;
    p = end;
    n++;
    d = n - old;
    while (*p != 0) p++;
    p++;
    if (d > 0 && rec + len - p < d) return -1;
    if (d == 0 && func_00415FC8(start, temp, n) == 0) return 0;
    if (d > 0) func_0041610C(end + d, end, p - end);
    if (d < 0) func_0041610C(start, start - d, p - (start - d));
    func_0041605C(start, temp, n);
    if (start[n] == 0 && D_004A4A70 != '\n')
        start[n - 1] = 0;
    else
        start[n - 1] = D_004A4A70;
    return n - 1;
}

//100%
// Sets the byte flag at D_004A4A70 and returns its old value.
extern char D_004A4A70;

extern "C" int func_003EB578(int v)
{
    char old = D_004A4A70;
    D_004A4A70 = v;
    return old;
}

// Normalizes a record in place: header control runs become `sep` (stopping at the first
// key line), a trailing sep becomes a newline (or the end), then each control run in the
// body becomes one '\n' (a run of the same char stays separate lines).
extern "C" void func_003EB588(unsigned char* d, unsigned char sep)
{
    unsigned char* buf = d;
    unsigned char* s = d;
    if (*s != 0) {
        do {
            if (*s < 0x20) {
                *d++ = sep;
                while (*s != 0 && *s < 0x20)
                    s++;
                if ((*s == '=' || *s == ':') && s[1] < 0x20)
                    break;
            } else {
                *d++ = *s++;
            }
        } while (*s != 0);
    }
    if (d != buf && d[-1] == sep)
        d[-1] = (sep == '\n' || *s != 0) ? '\n' : 0;
    while (*s != 0) {
        if (*s < 0x20) {
            *d++ = '\n';
            unsigned char c = *s++;
            while (*s != 0 && *s < 0x20 && *s != c)
                s++;
        } else {
            *d++ = *s++;
        }
    }
    *d = 0;
}

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldFind);

//100%
// Finds field prefix+name in record; either part may be null.
extern "C" char* cDirtysock_tag_TagFieldFind_B840(char* record, const char* name) __asm__("cDirtysock_tag_TagFieldFind");
extern "C" char* strcpy(char* d, const char* s);
extern "C" char* func_004162D0(char* d, const char* s);

extern "C" char* func_003EB840(char* record, const char* prefix, const char* name)
{
    char buf[256];
    char* r;
    if (prefix == 0)
    {
        r = cDirtysock_tag_TagFieldFind_B840(record, name);
    }
    else if (name == 0)
    {
        r = cDirtysock_tag_TagFieldFind_B840(record, prefix);
    }
    else
    {
        strcpy(buf, prefix);
        func_004162D0(buf, name);
        r = cDirtysock_tag_TagFieldFind_B840(record, buf);
    }
    return r;
}

extern char D_004A4A78[];

// Finds the D_004A4A78 field and skips leading blanks; null if the value is empty.
extern "C" unsigned char* func_003EB8B8(char* record)
{
    unsigned char* p = (unsigned char*)cDirtysock_tag_TagFieldFind_B840(record, D_004A4A78);
    if (p != 0) {
        while (*p != 0 && *p <= ' ')
            p++;
        if (*p == 0)
            p = 0;
    }
    return p;
}

//100%
extern "C" unsigned char* cDirtysock_tag_TagFieldFind(char* record, char* name);

extern "C" int cDirtysock_tag_TagFieldDelete(unsigned char* record, char* name)
{
    unsigned char* p = cDirtysock_tag_TagFieldFind((char*)record, name);
    unsigned char* dst;
    unsigned char* src;
    if (p == 0) {
        return -1;
    }
    dst = p;
    while (dst != record && dst[-1] > ' ') {
        dst--;
    }
    src = p;
    while (*src >= ' ') {
        src++;
    }
    while ((unsigned int)(*src - 1) < 0x1FU) {
        src++;
    }
    int c = *src;
    if (c != 0) {
        do {
            *dst = c;
            src++;
            c = *src;
            dst++;
        } while (c != 0);
    }
    *dst = 0;
    return 0;
}

extern "C" int strlen(const char* s);

// Renames field `name` in the record to `newname`, shifting the rest of the record;
// -1 if the field is missing or the longer name does not fit.
extern "C" int func_003EB9E8(unsigned char* rec, int size, const char* name, const char* newname)
{
    unsigned char* p = (unsigned char*)cDirtysock_tag_TagFieldFind_B840((char*)rec, name);
    unsigned char* q;
    unsigned char* e;
    int d;
    if (p == 0)
        return -1;
    if (p[-1] == ' ')
        p--;
    q = p - 1;
    p = q;
    while (q != rec && q[-1] > 0x20)
        q--;
    d = strlen(newname) - (p - q);
    if (d < 0) {
        while (*p != 0)
            p[d] = *p;
        *p = 0;
    }
    if (d > 0) {
        e = p;
        while (*e != 0)
            e++;
        if (e - rec < size - d)
            return -1;
        while (e != p) {
            e[d] = *e;
            e--;
        }
    }
    while (*newname != 0)
        *q++ = *newname++;
    return 0;
}

//100%
extern "C" int cDirtysock_tag_TagFieldDupl(char* dst, int len, const char* src)
{
    int left = len;
    while (left > 1 && *src != 0) {
        *dst++ = *src++;
        left--;
    }
    if (left > 0) {
        *dst = 0;
    }
    return len - left;
}

//100%
extern "C" int func_003EBBA8(const unsigned char* rec, char* buf, int len)
{
    int n = 0;
    if (len > 0)
        *buf = 0;
    if (rec == 0 || *rec == 0)
        return 0;
    for (const unsigned char* p = rec; *p != 0; p++) {
        if (*p != '=' && *p != ':')
            continue;
        if (p[1] < 0x20 && p[-1] <= 0x20)
            break;
        const unsigned char* s = p;
        while (s != rec && s[-1] > 0x20)
            s--;
        while (s != p && n + 1 < len)
            buf[n++] = *s++;
        buf[n] = 0;
        break;
    }
    return n;
}

//100%
// Cuts the record at its first "=" or ":" that ends a line, then appends "=\n" and val if they fit (-1 when fewer than 5 bytes remain).
extern "C" int func_003EBCB0(unsigned char* buf, int size, const char* val)
{
    unsigned char* p = buf;
    unsigned char* end;
    while (*p != 0) {
        if ((*p == '=' || *p == ':') && p[1] < 0x20)
            break;
        p++;
    }
    *p = 0;
    if (val == 0)
        return 0;
    end = buf + size - 1;
    if (end - p < 5)
        return -1;
    *p++ = '=';
    *p++ = '\n';
    while (*val != 0 && p != end)
        *p++ = *val++;
    *p = 0;
    return 0;
}

extern char D_004A4A80[];

// Ends the record with the separator D_004A4A70 unless its last byte is a control
// char or already the separator, then appends D_004A4A80 if 4 more bytes fit.
extern "C" int func_003EBD70(unsigned char* buf, int size)
{
    const char* s = D_004A4A80;
    int ret = -1;
    int n = 0;
    while (buf[n] != 0)
        n++;
    if (n > 0 && buf[n - 1] >= 0x20 && buf[n - 1] != D_004A4A70 && n < size - 1) {
        buf[n] = D_004A4A70;
        n++;
        buf[n] = 0;
    }
    if (n + 4 < size) {
        while (*s != 0)
            buf[n++] = *s++;
        buf[n] = 0;
        ret = 0;
    }
    return ret;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cDirtysock_tag__TagFieldSetupTerm(char* record, int len, char* temp);

extern "C" int cDirtysock_tag_TagFieldSetNumber(char* record, int len, char* name, int value)
{
    char temp[256 + 32];
    unsigned char* num;
    char* data = cDirtysock_tag__TagFieldSetupAppend(record, temp, name);

    if (value < 0) {
        *data++ = '-';
        value = -value;
    }
    num = (unsigned char*)data + 31;
    *num = 0;
    while (value > 0) {
        *--num = '0' + (value % 10);
        value /= 10;
    }
    if (*num == 0)
        *--num = '0';
    do {
        *data++ = *num++;
    } while (*num != 0);
    *data = 0;
    return cDirtysock_tag__TagFieldSetupTerm(record, len, temp);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cDirtysock_tag__TagFieldSetupTerm(char* record, int len, char* temp);
extern char D_004965C0[];

extern "C" int cDirtysock_tag_TagFieldSetFlags(char* record, int len, char* name, int value)
{
    char temp[256 + 32];
    char* data = cDirtysock_tag__TagFieldSetupAppend(record, temp, name);
    const char* flags = D_004965C0;
    for (; (value != 0) && (*flags != 0); value >>= 1, flags++) {
        if (value & 1) {
            *data++ = *flags;
        }
    }
    *data = 0;
    return cDirtysock_tag__TagFieldSetupTerm(record, len, temp);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cDirtysock_tag__TagFieldSetupTerm(char* record, int len, char* temp);

extern "C" int cDirtysock_tag_TagFieldSetAddress(char* record, int len, char* name, unsigned int addr)
{
    int i;
    unsigned char bytes[4];
    char temp[256 + 32];
    char* data = cDirtysock_tag__TagFieldSetupAppend(record, temp, name);

    bytes[3] = (unsigned char)addr;
    addr >>= 8;
    bytes[2] = (unsigned char)addr;
    addr >>= 8;
    bytes[1] = (unsigned char)addr;
    addr >>= 8;
    bytes[0] = (unsigned char)addr;
    for (i = 0; i < 4; i++) {
        unsigned char c = bytes[i];
        if (i > 0)
            *data++ = '.';
        if (c >= 10) {
            if (c >= 100) {
                *data++ = '0' + c / 100;
                c %= 100;
            }
            *data++ = '0' + c / 10;
            c %= 10;
        }
        *data++ = '0' + c;
    }
    *data = 0;
    return cDirtysock_tag__TagFieldSetupTerm(record, len, temp);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cDirtysock_tag__TagFieldSetupTerm(char* record, int len, char* temp);

extern "C" int cDirtysock_tag_TagFieldSetFourCC(char* record, int len, char* name, int value)
{
    char temp[256 + 32];
    char* data = cDirtysock_tag__TagFieldSetupAppend(record, temp, name);
    for (; value != 0; value <<= 8) {
        if (value > 0x20FFFFFF) {
            *data++ = (char)(value >> 24);
        }
    }
    *data = 0;
    return cDirtysock_tag__TagFieldSetupTerm(record, len, temp);
}

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetString);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cDirtysock_tag__TagFieldSetupTerm(char* record, int len, char* temp);
extern unsigned char D_00495FC0[];
extern unsigned char D_004960C0[];

extern "C" int cDirtysock_tag_TagFieldSetBinary(char* record, int len, char* name, const void* value, int size)
{
    const unsigned char* src = (const unsigned char*)value;
    char temp[4096 + 256];
    char* data = cDirtysock_tag__TagFieldSetupAppend(record, temp, name);
    *data++ = '$';
    for (; size > 0; --size) {
        *data++ = D_00495FC0[*src];
        *data++ = D_004960C0[*src++];
    }
    *data = 0;
    return cDirtysock_tag__TagFieldSetupTerm(record, len, temp);
}

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetStructure);

INCLUDE_ASM("dirtysock/tags", cDirtysock_tag_TagFieldSetCrypt);

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cDirtysock_tag__TagFieldSetupTerm(char* record, int len, char* temp);
extern "C" int sprintf(char* buf, const char* fmt, ...);
extern char D_00496A40[];

struct sDsTmK2 {
    int tm_sec;   // 0x0
    int tm_min;   // 0x4
    int tm_hour;  // 0x8
    int tm_mday;  // 0xC
    int tm_mon;   // 0x10
    int tm_year;  // 0x14
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

// ds_timeinsecs / ds_secstotime
extern "C" unsigned int func_003EF088();
extern "C" sDsTmK2* func_003EAEB8(sDsTmK2* tm, unsigned long secs);

// PORT: epoch is widened to 64-bit `unsigned long` (zero-extended) for ds_secstotime.
extern "C" int cDirtysock_tag_TagFieldSetEpoch(char* record, int len, char* name, unsigned int epoch)
{
    sDsTmK2 tm;
    char temp[256 + 32];
    sDsTmK2* t;
    unsigned long secs = epoch;

    if (secs == 0)
        secs = func_003EF088();
    t = func_003EAEB8(&tm, secs);
    if (t == 0)
        return -1;
    char* data = cDirtysock_tag__TagFieldSetupAppend(record, temp, name);
    sprintf(data, D_00496A40, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return cDirtysock_tag__TagFieldSetupTerm(record, len, temp);
}

//100%
// TagFieldSetDate-style setter: converts calendar fields (minus offset seconds) to an epoch and stores it with TagFieldSetEpoch.
extern "C" void* func_00416210_C8B8(void* p, int c, int n) __asm__("func_00416210");
extern "C" long func_003EB090_C8B8(sDsTmK2* tm) __asm__("func_003EB090");

extern "C" int func_003EC8B8(char* record, int len, char* name, int year, int month, int day, int hour, int min, int sec, int offset)
{
    sDsTmK2 tm;
    int secs;
    func_00416210_C8B8(&tm, 0, sizeof(tm));
    tm.tm_isdst = -1;
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
    secs = func_003EB090_C8B8(&tm);
    return cDirtysock_tag_TagFieldSetEpoch(record, len, name, secs ? secs - offset : 0);
}

//100%
// Like func_003EC8B8, but takes the date (year << 16 | month << 8 | day) and time (hour << 16 | min << 8 | sec) packed.
extern "C" int func_003EC9A0(char* record, int len, char* name, int date, int time, int offset)
{
    sDsTmK2 tm;
    int secs;
    func_00416210_C8B8(&tm, 0, sizeof(tm));
    tm.tm_isdst = -1;
    tm.tm_year = ((date >> 16) & 0xFFFF) - 1900;
    tm.tm_mon = ((date >> 8) & 0xFF) - 1;
    tm.tm_mday = date & 0xFF;
    tm.tm_hour = (time >> 16) & 0xFF;
    tm.tm_min = (time >> 8) & 0xFF;
    tm.tm_sec = time & 0xFF;
    secs = func_003EB090_C8B8(&tm);
    return cDirtysock_tag_TagFieldSetEpoch(record, len, name, secs ? secs - offset : 0);
}

//100%
// Finds field name in src, steps back to the start of its token, and sets up record from there.
extern "C" char* cDirtysock_tag_TagFieldFind_CA88(char* record, const char* name) __asm__("cDirtysock_tag_TagFieldFind");

extern "C" int func_003ECA88(char* record, int len, const char* name, char* src)
{
    char* p = cDirtysock_tag_TagFieldFind_CA88(src, name);
    if (p == 0)
        return 0;
    while (p != src && (unsigned char)p[-1] >= 0x20)
        p--;
    return cDirtysock_tag__TagFieldSetupTerm(record, len, p);
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" int cDirtysock_tag__TagFieldSetupTerm(char* record, int len, char* temp);

// TagFieldMerge: apply every field of `data` to the record; returns how many were set.
extern "C" int func_003ECB00(char* record, int len, unsigned char* data)
{
    int count = 0;
    for (;;) {
        unsigned char c = *data;
        if (c == 0)
            break;
        // skip whitespace
        if (c <= ' ') {
            ++data;
            continue;
        }
        // stop at a separator
        if ((c == '=') || (c == ':'))
            break;
        // add the field
        if (cDirtysock_tag__TagFieldSetupTerm(record, len, (char*)data) > 0)
            ++count;
        // skip to the next field
        while (*data >= ' ')
            ++data;
    }
    return count;
}

//100%
// PORT: hand-rolled EE EABI va_start (gcc 2.95 va-mips.h form); use <stdarg.h> off-PS2.
typedef char* func_003ECBD8_va_list;
#define func_003ECBD8_va_start(ap)                                       \
    (ap = (char*)__builtin_next_arg()                                    \
          - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))
#define func_003ECBD8_va_arg(ap, T) (ap += 8, *(T*)(ap - 8))

extern "C" int cDirtysock_tag_TagFieldSetString(char* buf, int size, const char* key, const char* value);
extern char D_004A4A90[];

// TagFieldPrintf-style formatter: copies fmt into buf, turning whitespace runs into the
// field separator and %s/%d/%a/%f/%e/%r into tag fields from the arguments.
extern "C" int func_003ECBD8(char* buf, int len, const char* fmt, ...)
{
    func_003ECBD8_va_list args;
    func_003ECBD8_va_start(args);
    int size = len;
    unsigned char c = *fmt++;
    while (c != 0 && len >= 2) {
        if (c <= ' ') {
            *buf++ = D_004A4A70;
            len--;
            while (*fmt != 0 && *fmt <= ' ')
                fmt++;
        } else if (c != '%') {
            *buf++ = c;
            len--;
        } else if (*fmt != 0) {
            int n = 0;
            c = *fmt++;
            if (buf[-1] == '=') {
                buf--;
                len++;
            }
            *buf = 0;
            if (c == 's') {
                n = cDirtysock_tag_TagFieldSetString(buf, len, D_004A4A90, func_003ECBD8_va_arg(args, char*));
            } else if (c == 'd') {
                n = cDirtysock_tag_TagFieldSetNumber(buf, len, D_004A4A90, func_003ECBD8_va_arg(args, int));
            } else if (c == 'a') {
                n = cDirtysock_tag_TagFieldSetAddress(buf, len, D_004A4A90, func_003ECBD8_va_arg(args, unsigned int));
            } else if (c == 'f') {
                n = cDirtysock_tag_TagFieldSetFlags(buf, len, D_004A4A90, func_003ECBD8_va_arg(args, int));
            } else if (c == 'e') {
                n = cDirtysock_tag_TagFieldSetEpoch(buf, len, D_004A4A90, func_003ECBD8_va_arg(args, unsigned int));
            } else if (c == 'r') {
                const char* r = func_003ECBD8_va_arg(args, char*);
                while (*r != 0 && len > 0) {
                    *buf++ = *r++;
                    len--;
                }
            }
            if (n > 0) {
                buf += n;
                len -= n;
            }
        }
        c = *fmt++;
    }
    if (len > 0)
        *buf = 0;
    return size - len;
}

//100%
// Finds the next "=" or ":" field separator in p and copies the following value into out (or dflt when there is none); returns the value start or 0.
extern "C" unsigned char* func_003ECE38(unsigned char* src, int unused, char* out, int size, const char* dflt)
{
    int i;
    unsigned char* p = src;
    while (*p != 0) {
        if ((*p == '=' || *p == ':') && p[1] < 0x20) {
            if (p[1] == 0)
                break;
            p += 2;
            if (out != 0) {
                size--;
                for (i = 0; i < size && p[i] != 0; i++)
                    out[i] = p[i];
                out[i] = 0;
            }
            return p;
        }
        p++;
    }
    if (out != 0 && dflt != 0) {
        size--;
        for (i = 0; i < size && dflt[i] != 0; i++)
            out[i] = dflt[i];
        out[i] = 0;
    }
    return 0;
}

//100%
extern "C" int cDirtysock_tag_TagFieldGetNumber(const char* data, int defval)
{
    int sign;
    int value;
    if (data == 0) {
        return defval;
    }
    sign = 1;
    if (*data == '+') {
        ++data;
    } else if (*data == '-') {
        ++data;
        sign = -1;
    }
    for (value = 0; (*data >= '0') && (*data <= '9'); ) {
        value = (value * 10) + (*data++ & 15);
    }
    return sign * value;
}

//100%
extern int D_004965E0[];

extern "C" int cDirtysock_tag_TagFieldGetFlags(const char* data, int defval)
{
    if (data != 0) {
        int flags = 0;
        int f;
        while ((f = D_004965E0[*data]) != 0) {
            flags |= f;
            data++;
        }
        defval = flags;
    }
    return defval;
}

//100%
extern "C" unsigned int cDirtysock_tag_TagFieldGetAddr(const char* data, unsigned int defval)
{
    unsigned int addr = 0;
    if (data != 0) {
        for (;; data++) {
            if ((*data >= '0') && (*data <= '9')) {
                addr = (addr & 0xFFFFFF00) | (((addr & 0xFF) * 10) + (*data & 15));
            } else if (*data == '.') {
                addr <<= 8;
            } else {
                break;
            }
        }
        defval = addr;
    }
    return defval;
}

//100%
extern "C" int cDirtysock_tag_TagFieldGetFourCC(const char* data, int defval)
{
    int token;
    if ((data == 0) || (*data <= ' ') || (*data >= 127)) {
        return defval;
    }
    for (token = 0x20202020; (token < 0x20FFFFFF) && (*data > ' ') && (*data < 127); data++) {
        token = (token << 8) | *data;
    }
    return token;
}

//100%
extern "C" int strlen(const char* s);
extern unsigned char D_004961C0[];
extern unsigned char D_004962C0[];

// TagFieldGetString variant that first skips iIndex fields split by iDelim.
extern "C" int func_003ED0F8(const char* pData, char* pBuffer, int iLength, const char* pDefval, int iIndex, int iDelim)
{
    int iSize;
    unsigned char cQuote;
    const unsigned char* p;

    if (pData != 0) {
        if ((*pData == '"') || (*pData == '\'')) {
            cQuote = *pData++;
        } else {
            cQuote = 0;
        }
        for (; iIndex > 0; --iIndex) {
            for (;;) {
                char c = *pData;
                if ((c == cQuote) || (c < ' ') || (c == iDelim)) {
                    break;
                }
                ++pData;
            }
            if (*pData++ != iDelim) {
                pData = 0;
                break;
            }
        }
    }
    if (pData == 0) {
        if (pDefval == 0) {
            return -1;
        }
        if (pBuffer == 0) {
            return strlen(pDefval);
        }
        for (iSize = 1; (iSize < iLength) && (*pDefval != 0); ++iSize) {
            *pBuffer++ = *pDefval++;
        }
        *pBuffer = 0;
        return iSize - 1;
    }
    if (pBuffer == 0) {
        p = (const unsigned char*)pData;
        for (iSize = 0; (*p != cQuote) && (*p >= ' ') && (*p != iDelim); ++iSize) {
            if ((p[0] == '%') && (p[1] >= ' ') && (p[2] >= ' ')) {
                p += 2;
            }
            ++p;
        }
        return iSize;
    }
    if (iLength <= 0) {
        return -1;
    }
    p = (const unsigned char*)pData;
    for (iSize = 1; (iSize < iLength) && (*p != cQuote) && (*p >= ' ') && (*p != iDelim);) {
        if ((p[0] == '%') && (p[1] == '%')) {
            *pBuffer++ = '%';
            p += 2;
            ++iSize;
        } else if ((p[0] == '%') && (p[1] >= ' ') && (p[2] >= ' ')) {
            ++iSize;
            *pBuffer++ = D_004961C0[p[1]] | D_004962C0[p[2]];
            p += 3;
        } else {
            ++iSize;
            *pBuffer++ = *p++;
        }
    }
    *pBuffer = 0;
    return iSize - 1;
}

//100%
// Copies a tag field value (quoted or bare, with %xx decoding) into pBuffer, or the default.
extern "C" int cDirtysock_tag_TagFieldGetString(const char* pData, char* pBuffer, int iLength, const char* pDefval)
{
    int iSize;
    unsigned char cQuote;
    const unsigned char* p;

    if (pData == 0) {
        if (pDefval == 0) {
            return -1;
        }
        if (pBuffer == 0) {
            return strlen(pDefval);
        }
        for (iSize = 1; (iSize < iLength) && (*pDefval != 0); ++iSize) {
            *pBuffer++ = *pDefval++;
        }
        *pBuffer = 0;
        return iSize - 1;
    }
    if ((*pData == '"') || (*pData == '\'')) {
        cQuote = *pData++;
    } else {
        cQuote = 0;
    }
    if (pBuffer == 0) {
        p = (const unsigned char*)pData;
        for (iSize = 0; (*p != cQuote) && (*p >= ' '); ++iSize) {
            if ((p[0] == '%') && (p[1] >= ' ') && (p[2] >= ' ')) {
                p += 2;
            }
            ++p;
        }
        return iSize;
    }
    if (iLength <= 0) {
        return -1;
    }
    p = (const unsigned char*)pData;
    for (iSize = 1; (iSize < iLength) && (*p != cQuote) && (*p >= ' ');) {
        if ((p[0] == '%') && (p[1] == '%')) {
            *pBuffer++ = '%';
            p += 2;
            ++iSize;
        } else if ((p[0] == '%') && (p[1] >= ' ') && (p[2] >= ' ')) {
            ++iSize;
            *pBuffer++ = D_004961C0[p[1]] | D_004962C0[p[2]];
            p += 3;
        } else {
            ++iSize;
            *pBuffer++ = *p++;
        }
    }
    *pBuffer = 0;
    return iSize - 1;
}

//100%
extern unsigned char D_004961C0[];
extern unsigned char D_004962C0[];

extern "C" int cDirtysock_tag_TagFieldGetBinary(const char* data, void* buffer, int len)
{
    int count;
    const char* p;
    char* buf = (char*)buffer;

    if ((data == 0) || (*data != '$')) {
        return -1;
    }
    if (buf == 0) {
        for (count = 0, p = data + 1; ((unsigned char)p[0] >= '0') && ((unsigned char)p[1] >= '0'); count++) {
            p += 2;
        }
        return count;
    }
    p = data + 1;
    if (len <= 0) {
        return -1;
    }
    for (count = 0; (count < len) && ((unsigned char)p[0] >= '0') && ((unsigned char)p[1] >= '0'); count++) {
        *buf++ = D_004961C0[(unsigned char)p[0]] | D_004962C0[(unsigned char)p[1]];
        p += 2;
    }
    return count;
}

//100%
extern char D_004A4A90[];

extern "C" int cDirtysock_tag_TagFieldGetStructure(const char* data, void* buffer, int len, const char* tmpl)
{
    int count;
    int size;
    int sign;
    unsigned int value;
    char* buf = (char*)buffer;
    char* limit;
    char temp[1024];

    if (len < 0) {
        limit = buf + 65535;
    } else {
        limit = buf + len;
    }
    if (data == 0) {
        data = D_004A4A90;
    }
    if (buf == 0) {
        buf = (char*)(buffer = temp);
    }
    while (*tmpl != 0) {
        if (*tmpl == '#') {
            for (++tmpl; (*tmpl != 0) && (*tmpl++ != '='); ) {
            }
        }
        for (count = 0; (*tmpl >= '0') && (*tmpl <= '9'); ++tmpl) {
            count = (count * 10) + (*tmpl & 15);
        }
        if (*tmpl == 'a') {
            if (count != 0) {
                buf += count;
            } else {
                buf += 1;
            }
        }
        size = 0;
        if (*tmpl == 'b') {
            size = 2;
        }
        if (*tmpl == 'w') {
            size = 4;
        }
        if (*tmpl == 'l') {
            size = 8;
        }
        if (size > 0) {
            sign = *data;
            if (sign == '-') {
                ++data;
            }
            for (value = 0; (size > 0) && (*data >= '0'); --size) {
                value = (value << 4) | D_004962C0[*data++];
            }
            if ((size > 0) && (*data == ',')) {
                ++data;
            }
            if (sign == '-') {
                value = -value;
            }
            if (*tmpl == 'b') {
                *buf++ = value;
            }
            if (*tmpl == 'w') {
                *(short*)buf = value;
                buf += 2;
            }
            if (*tmpl == 'l') {
                *(int*)buf = value;
                buf += 4;
            }
        }
        if ((*tmpl == 's') && (count > 0)) {
            for (size = 0; ((*data >= '0') || (*data == '%')) && (size + 1 < count); ++size) {
                if (*data == '%') {
                    buf[size] = D_004961C0[data[1]] | D_004962C0[data[2]];
                    data += 3;
                } else {
                    buf[size] = *data++;
                }
            }
            for (; size < count; ++size) {
                buf[size] = 0;
            }
            if (*data == ',') {
                ++data;
            }
            buf += size;
        }
        if (buf >= limit) {
            break;
        }
        ++tmpl;
        if (*tmpl == '*') {
            --tmpl;
        }
    }
    return buf - (char*)buffer;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern unsigned char D_004961C0[];
extern unsigned char D_004962C0[];
extern char D_004A4A88[];
extern "C" int cDirtysock_tag_TagFieldGetString(const char* data, char* buf, int len, const char* defval);

extern "C" int cDirtysock_tag_TagFieldGetCrypt(const char* data, char* buf, int len, const unsigned char* key, const char* defval)
{
    int count;
    const char* p;
    const unsigned char* kbase = key;
    const unsigned char* k;
    int prev;
    if (data == 0) {
        return -1;
    }
    if (*data != '$') {
        return cDirtysock_tag_TagFieldGetString(data, buf, len, defval);
    }
    if (kbase == 0 || *kbase == 0) {
        kbase = (const unsigned char*)D_004A4A88;
    }
    if (buf == 0) {
        for (count = 0, p = data + 1; (unsigned char)p[0] >= '0' && (unsigned char)p[1] >= '0'; count++) {
            p += 2;
        }
        return count;
    }
    count = 1;
    if (len <= 0) {
        return -1;
    }
    p = data + 1;
    k = kbase;
    prev = 0;
    for (; count < len && (unsigned char)p[0] >= '0' && (unsigned char)p[1] >= '0'; count++) {
        unsigned int c = *k ^ (D_004961C0[(unsigned char)p[0]] | D_004962C0[(unsigned char)p[1]]);
        if (*++k == 0) {
            k = kbase;
        }
        *buf++ = ((c << 5) | (c >> 3)) ^ prev;
        int hi = D_004961C0[(unsigned char)p[0]];
        int lo = D_004962C0[(unsigned char)p[1]];
        prev = lo | hi;
        p += 2;
    }
    *buf = 0;
    return count - 1;
}

//100%
// _TagFieldParseNumber / memset / ds_tmtosecs
extern "C" char* func_003EAE68(const char* data, int* value);
extern "C" void* func_00416210(void* dst, int value, int size);
// PORT: ds_tmtosecs returns a 64-bit `unsigned long`.
extern "C" unsigned long func_003EB090(sDsTmK2* tm);

extern "C" unsigned int cDirtysock_tag_TagFieldGetTime(char* data, unsigned int defval)
{
    sDsTmK2 tm;
    int value;
    unsigned int result = 0;

    if (data != 0) {
        if (*data == '$') {
            for (++data; *data >= '0'; ++data) {
                result = (result << 4) | D_004962C0[*data];
            }
        } else if ((*data >= '0') && (*data <= '9')) {
            const char* p = func_003EAE68(data, &value);
            if (*p <= ' ') {
                result = value;
            } else if ((*data >= '0') && (*data <= '9')) {
                func_00416210(&tm, 0, sizeof(tm));
                tm.tm_isdst = -1;
                data = func_003EAE68(data, &tm.tm_year);
                if ((unsigned char)(*data - '-') <= 1) {
                    data++;
                }
                data = func_003EAE68(data, &tm.tm_mon);
                if ((unsigned char)(*data - '-') <= 1) {
                    data++;
                }
                data = func_003EAE68(data, &tm.tm_mday);
                if (*data == ' ') {
                    data++;
                }
                data = func_003EAE68(data, &tm.tm_hour);
                if (*data == ':') {
                    data++;
                }
                data = func_003EAE68(data, &tm.tm_min);
                if (*data == ':') {
                    data++;
                }
                data = func_003EAE68(data, &tm.tm_sec);
                if ((tm.tm_year < 1970) || (tm.tm_year > 2099) || (tm.tm_mon < 1) || (tm.tm_mon > 12) || (tm.tm_mday < 1) || (tm.tm_mday > 31)) {
                    tm.tm_year = 0;
                }
                if ((tm.tm_hour < 0) || (tm.tm_hour > 23) || (tm.tm_min < 0) || (tm.tm_min > 59) || (tm.tm_sec < 0) || (tm.tm_sec > 61)) {
                    tm.tm_year = 0;
                }
                if (tm.tm_year != 0) {
                    tm.tm_year -= 1900;
                    tm.tm_mon -= 1;
                    result = func_003EB090(&tm);
                }
            }
        }
    }
    if (result == 0) {
        result = defval;
        if (result == 0) {
            result = func_003EF088();
        }
    }
    return result;
}

//100% - objdiff report; single-function view differs only in a relocation name
extern "C" unsigned int cDirtysock_tag_TagFieldGetTime(char* data, unsigned int dflt);

// TagFieldGetDate-style accessor: split a time tag into calendar fields.
extern "C" int func_003EDD70(char* data, int* year, int* month, int* day, int* hour, int* min, int* sec, int offset)
{
    sDsTmK2 tm;
    sDsTmK2* t;
    unsigned int secs = cDirtysock_tag_TagFieldGetTime(data, 1);
    if (secs < 2)
        return -1;
    t = func_003EAEB8(&tm, secs + offset);
    if (t == 0)
        return -1;
    if (year)
        *year = t->tm_year + 1900;
    if (month)
        *month = t->tm_mon + 1;
    if (day)
        *day = t->tm_mday;
    if (hour)
        *hour = t->tm_hour;
    if (min)
        *min = t->tm_min;
    if (sec)
        *sec = t->tm_sec;
    return 0;
}


//100%
// TagFieldGetDate-style accessor: packs a time tag into date (year << 16 | month << 8 | day) and time (hour << 16 | min << 8 | sec).
extern "C" int func_003EDE80(char* data, int* date, int* time, int offset)
{
    sDsTmK2 tm;
    sDsTmK2* t;
    unsigned int secs = cDirtysock_tag_TagFieldGetTime(data, 1);
    if (secs < 2)
        return -1;
    t = func_003EAEB8(&tm, secs + offset);
    if (t == 0)
        return -1;
    if (date)
        *date = ((t->tm_year + 1900) << 16) | ((t->tm_mon + 1) << 8) | t->tm_mday;
    if (time)
        *time = (t->tm_hour << 16) | (t->tm_min << 8) | t->tm_sec;
    return 0;
}
