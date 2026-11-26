/* ============================================================================
 * bsp.c — AI8051U-34K64 板级初始化（替代 STM32 的 HAL_Init / SystemClock_Config）
 *   入口 bsp_Init() 由固件 main() 调用，完成：
 *     1) 放开取指/XDATA 等待（WTST/CKCON）+ 允许 MOVX 访问扩展 SFR（EAXSFR）
 *     2) 端口默认模式设置
 *     3) UART1 初始化（115200）
 *     4) LED 初始化
 *     5) Timer0 1ms 节拍初始化
 *     6) 开总中断 EA
 *   SPI / 复位引脚由 PAN312x 驱动层在 Fsk_Init 路径内完成。
 * ========================================================================== */
#include "bsp.h"

/* 端口默认配置：全部准双向口，输出高（与复位态一致）。
   具体功能脚（SPI/NSS/RESET/LED）由各自子模块再配置。 */
static void PortInit(void)
{
    P0M1 = 0x00; P0M0 = 0x00;
    P1M1 = 0x00; P1M0 = 0x00;
    P2M1 = 0x00; P2M0 = 0x00;
    P3M1 = 0x00; P3M0 = 0x00;
    P4M1 = 0x00; P4M0 = 0x00;
    P5M1 = 0x00; P5M0 = 0x00;
    P6M1 = 0x00; P6M0 = 0x00;
    P7M1 = 0x00; P7M0 = 0x00;

    P0 = 0xFF; P1 = 0xFF; P2 = 0xFF; P3 = 0xFF;
    P4 = 0xFF; P5 = 0xFF; P6 = 0xFF; P7 = 0xFF;
}

void bsp_Init(void)
{
    /* 时钟/等待周期：主频由 STC-ISP 下载设定（33.1776MHz），程序内仅放开等待 */
    EAXSFR();                       /* 允许访问扩展 SFR（端口中断/IAP 等） */
    WTST  = 0;                      /* 取指零等待 */
    CKCON = 0;                      /* XDATA 零等待 */

    PortInit();
    bsp_InitUart();
    bsp_InitLed();
    bsp_InitTimer();                /* 配置并启动 Timer0 1ms 节拍 */

    EA = 1;                         /* 开总中断 */
}

/* 空闲钩子：阻塞延时段内调用，可在此喂独立看门狗 */
void bsp_Idle(void)
{
    /* 当前无操作 */
}

void Error_Handler(void)
{
    while (1);
}
