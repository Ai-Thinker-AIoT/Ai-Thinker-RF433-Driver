/* ============================================================================
 * ai8051_port.h
 * ---------------------------------------------------------------------------
 * AI8051U-34K64 平台适配层（替代 C351 之外的类型/中断宏）。
 * 说明：
 *   - C351 无 <stdint.h>/<stdbool.h>，本目录提供等价 shim（stdint.h / stdbool.h）。
 *   - 全局中断用 EA=0/EA=1 替代 Cortex-M 的 __disable_irq/__enable_irq。
 *   - 主频由 STC-ISP 下载时设定（33.1776MHz），程序内仅放开取指/XDATA 等待。
 * ========================================================================== */
#ifndef __AI8051_PORT_H__
#define __AI8051_PORT_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <inttypes.h>

/* XSFR（扩展 SFR：SPI / IAP / 端口中断 / P_SW2 等）——
   提供 EA / EAXSFR() / P_SW1 / SPCTL / SPDAT / P3IE / P3INTF 等。 */
#include "XSFR_STC8051U_8Bit.H"

/* ---- 开/关总中断（替代 Cortex-M __disable_irq/__enable_irq） ---- */
#define PORT_DISABLE_IRQ()      (EA = 0)
#define PORT_ENABLE_IRQ()       (EA = 1)

/* ---- 主频常量：33.1776MHz（须与 STC-ISP 下载频率一致） ---- */
#define AI8051_SYS_CLK_HZ       33177600UL

#endif /* __AI8051_PORT_H__ */
