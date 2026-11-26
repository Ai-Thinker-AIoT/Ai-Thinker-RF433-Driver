/* ============================================================================
 * string.h — 长缨-I(C351) 32位 字符串/内存操作垫片
 * C351_STRING.H 仅声明 strlen/strcpy/strcat/strcmp；下列为固件用到但 C351 未声明
 * 的函数，以 static 实现，保证链接通过且不污染全局符号（避免与 C351 库冲突）。
 * ========================================================================== */
#ifndef __STRING_H_SHIM__
#define __STRING_H_SHIM__

#include "..\Toolchain\INC\C351_STRING.H"    /* strlen / strcpy / strcat / strcmp */

static void *memcpy(void *dest, const void *src, unsigned int n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) *d++ = *s++;
    return dest;
}

static void *memset(void *s, int c, unsigned int n)
{
    unsigned char *p = (unsigned char *)s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

static int memcmp(const void *s1, const void *s2, unsigned int n)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    while (n--)
    {
        if (*p1 != *p2) return (int)*p1 - (int)*p2;
        p1++; p2++;
    }
    return 0;
}

static char *strncpy(char *dest, const char *src, unsigned int n)
{
    unsigned int i = 0;
    while (i < n && src[i]) { dest[i] = src[i]; i++; }
    while (i < n) { dest[i] = '\0'; i++; }
    return dest;
}

static int strncmp(const char *s1, const char *s2, unsigned int n)
{
    unsigned int i = 0;
    while (i < n && s1[i] && s2[i])
    {
        if (s1[i] != s2[i]) return (int)(unsigned char)s1[i] - (int)(unsigned char)s2[i];
        i++;
    }
    if (i == n) return 0;
    return (int)(unsigned char)s1[i] - (int)(unsigned char)s2[i];
}

static int strcasecmp(const char *s1, const char *s2)
{
    int c1, c2;
    do
    {
        c1 = *s1; if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        c2 = *s2; if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) return c1 - c2;
        s1++; s2++;
    } while (c1 != '\0');
    return 0;
}

static int strncasecmp(const char *s1, const char *s2, unsigned int n)
{
    unsigned int i = 0; int c1, c2;
    while (i < n && *s1 && *s2)
    {
        c1 = *s1; if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        c2 = *s2; if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) return c1 - c2;
        s1++; s2++; i++;
    }
    if (i == n) return 0;
    c1 = (i < n) ? *s1 : 0;
    c2 = (i < n) ? *s2 : 0;
    if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
    if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
    return c1 - c2;
}

#endif /* __STRING_H_SHIM__ */
