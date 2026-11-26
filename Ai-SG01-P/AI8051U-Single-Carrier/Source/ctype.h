/* ============================================================================
 * ctype.h — 长缨-I(C351) 32位 字符分类/转换垫片
 * C351 未提供 <ctype.h>，固件用到 toupper/strcasecmp 等，此处以 static 实现。
 * ========================================================================== */
#ifndef __CTYPE_H_SHIM__
#define __CTYPE_H_SHIM__

static int isdigit(int c) { return (c >= '0' && c <= '9'); }
static int isxdigit(int c) { return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
static int isspace(int c) { return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'); }
static int isupper(int c) { return (c >= 'A' && c <= 'Z'); }
static int islower(int c) { return (c >= 'a' && c <= 'z'); }
static int isalpha(int c) { return isupper(c) || islower(c); }
static int isalnum(int c) { return isalpha(c) || isdigit(c); }
static int isprint(int c) { return (c >= 0x20 && c <= 0x7e); }
static int iscntrl(int c) { return (c < 0x20 || c == 0x7f); }
static int toupper(int c) { return (c >= 'a' && c <= 'z') ? (c - 32) : c; }
static int tolower(int c) { return (c >= 'A' && c <= 'Z') ? (c + 32) : c; }

#endif /* __CTYPE_H_SHIM__ */
