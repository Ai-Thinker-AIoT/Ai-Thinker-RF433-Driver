/* ============================================================================
 * stdio.h — 长缨-I(C351) 32位 标准输入输出垫片
 * 重定向到 C351 的 printf / sprintf / sscanf / putchar 实现模块。
 * 说明：C351 不提供标准 <stdio.h>，其打印/扫描功能位于 C351_STDIO.H 与
 *       C351_PRTSCN.H；本垫片将其纳入工程，使固件的 #include <stdio.h> 可用。
 *       用户必须在某处实现 putchar(char)（见 main.c / bsp_uart.c）。
 * ========================================================================== */
#ifndef __STDIO_H_SHIM__
#define __STDIO_H_SHIM__

#include "..\Toolchain\INC\C351_STDIO.H"     /* putchar / getchar / gets / puts */
#include "..\Toolchain\INC\C351_PRTSCN.H"    /* printf / sprintf / sscanf / scanf */

#endif /* __STDIO_H_SHIM__ */
