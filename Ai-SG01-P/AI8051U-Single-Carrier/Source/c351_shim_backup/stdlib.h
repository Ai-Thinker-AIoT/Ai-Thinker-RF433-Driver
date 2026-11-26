/* ============================================================================
 * stdlib.h — 长缨-I(C351) 32位 标准库垫片
 * C351 的整型/字符转换位于 C351_STDLIBI.H，浮点转换位于 C351_STDLIBF.H。
 * 固件主要通过 sscanf 解析，本垫片仅纳入这些模块以备 atoi/atol/stol 等调用。
 * ========================================================================== */
#ifndef __STDLIB_H_SHIM__
#define __STDLIB_H_SHIM__

#include "..\Toolchain\INC\C351_STDLIBI.H"   /* rand/srand/abs/labs/atoi/atol/stol/ltoa/itoa */
#include "..\Toolchain\INC\C351_STDLIBF.H"   /* atof/fabs/ftoa */

#endif /* __STDLIB_H_SHIM__ */
