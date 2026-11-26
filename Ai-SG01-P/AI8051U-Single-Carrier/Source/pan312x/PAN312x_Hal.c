/**
  ******************************************************************************
  * 文件   ：   PAN312x_HAL.c
  * 平台   ：   AI8051U-34K64（STC 80251 内核，长缨-I / C351 32位编译器）
  * 工程   ：   AI8051U-AISG01（Ai-SG01 PAN312x 2.4GHz AT 指令固件的移植版）
  * 说明   ：   本文件替换原 STM32 HAL/CubeMX 的 PAN312x 硬件抽象层，将
  *             SPI / GPIO / 外部中断 调用映射到 AI8051U 外设：
  *               - 硬件 SPI1（引脚组 SPI_S1=0/SPI_S0=0 -> P1.4~P1.7，软件 NSS）
  *               - RESET(P3.5) / DIO8-IRQ(P3.2 端口中断) / 第二路GPIO(P3.3 端口中断)
  *               - BUSY(P3.4) 保留为输入（驱动未轮询）
  *
  * 引脚映射（AI8051U-AISG01 模组）：
  *   P1.4  NSS / CSN  软件片选，推挽输出，空闲高
  *   P1.5  MOSI       推挽输出
  *   P1.6  MISO       高阻输入
  *   P1.7  SCLK       推挽输出
  *   P3.5  RESET/nRST 推挽输出，空闲高 = 不复位（低有效）
  *   P3.2  DIO8/IRQ   输入，上升沿端口中断 -> EXTI1_IRQn(0)
  *   P3.3  第二路GPIO 输入，上升沿端口中断 -> EXTI9_5_IRQn(1)，回调 token=GPIO_PIN_5
  *   P3.4  BUSY       保留为输入（驱动未做 GPIO 轮询）
  *
  * 端口中断：AI8051U 端口中断号(40) > 31，借保留中断号 13（向量 0x006B）中转，
  *           port_int_vec.a51 在 P3 口中断向量 0x0143H 处放置 LJMP 0x006BH。
  *******************************************************************************/

#include "bsp.h"

/* ============================ 引脚映射（C351 sbit 位寻址） ============================ */
sbit PAN312x_NSS   = P1^4;   /* 软件片选 CSN */
sbit PAN312x_RESET = P3^5;   /* 模块复位（低有效） */
sbit PAN312x_DIO8  = P3^2;   /* IRQ 中断输入 */

/* DIO8 回调 token：固件 HAL_GPIO_EXTI_Callback 会重读 DIO8 电平判定，
   token 仅作占位传递，取值任意（不与 GPIO_PIN_5=0x0020 冲突即可）。 */
#define PAN312x_DIO8_PIN   ((uint16_t)0x0002U)

/* SPI 控制字：SSIG|SPEN|MSTR = 0xD0
   CPOL=0/CPHA=0 -> SPI 模式0；SPR1=0/SPR0=0 -> SYSCLK/4 = 33.1776MHz/4 = 8.29MHz。
   如需降速可改 SPR 位：01->/8(4.15M)、10->/16(2.07M)、11->/32(1.04M)。 */
#define PAN312x_SPCTL_INIT  (SSIG | SPEN | MSTR | SPR1)  /* /16 -> 2.07MHz, match STM32 prescaler 16 */


/* ============================ 内部：SPI 单字节全双工 ============================ */
static uint8_t SpiInOutByte(uint8_t out)
{
    /* STC SPI：写 SPDAT 启动传输；SPIF 置位表示 8bit 完成；写 1 清零 */
    SPDAT = out;
    while (!(SPSTAT & SPIF)) { /* 轮询传输完成，最高 8.29MHz 单字节极快 */ }
    SPSTAT = SPIF | WCOL;            /* 写1清除 SPIF / WCOL 标志 */
    return SPDAT;
}


/* ============================ GPIO：SPI 引脚 + 软件 NSS ============================ */
void PAN312x_SPIGPIO_Init(void)
{
    /* 选择 SPI 引脚组：SPI_S1=0 / SPI_S0=0 -> SS/P1.4, MOSI/P1.5, MISO/P1.6, SCLK/P1.7 */
    P_SW1 &= ~(SPI_S1 | SPI_S0);

    /* 端口模式：MOSI(P1.5)/SCLK(P1.7)/NSS(P1.4) 推挽输出；MISO(P1.6) 高阻输入。
       SSIG=1 时硬件 SS 被忽略，P1.4 可当普通 GPIO 作软件片选。 */
    P1M1 &= ~0xB0;     /* P1.4/5/7: M1=0 */
    P1M0 |=  0xB0;     /* P1.4/5/7: M0=1 推挽 */
    P1M1 |=  0x40;     /* P1.6: M1=1 */
    P1M0 &= ~0x40;     /* P1.6: M0=0 高阻输入 */

    PAN312x_NSS = 1;   /* 空闲片选拉高 */
}


/* ============================ SPI 初始化 ============================ */
void PAN312x_SPI_Init(void)
{
    PAN312x_SPIGPIO_Init();          /* 引脚 + NSS 配置 */

    SPSTAT = SPIF | WCOL;            /* 清可能残留的标志 */
    SPCTL  = PAN312x_SPCTL_INIT;     /* 模式0 主机，/4 分频 */

    PAN312x_NSS = 1;                 /* 空闲高 */
}

void PAN312x_SPI_DeInit(void)
{
    /* 关闭 SPI 并将引脚置为输入（弱上拉），释放总线 */
    SPCTL &= ~SPEN;
    P1M1 |=  0xF0;                   /* P1.4~P1.7 高阻输入 */
    P1M0 &= ~0xF0;
    PAN312x_NSS = 1;
}


/* ============================ 所有 GPIO 置默认（占位） ============================ */
void PAN312x_Set_AllGPIO_Analog(void)
{
    /* AI8051U 没有 STM32 风格的 GPIO_MODE_ANALOG；相关功能脚由各 *_Init 单独配置，
       此处无需动作（默认端口已在 bsp_Init 的 PortInit 中设为准双向+输出高）。 */
}


/* ============================ DIO8（IRQ）输入 + 上升沿端口中断 ============================ */
void PAN312x_DIO8_INPUT(void)
{
    /* P3.2 保持默认准双向（可作输入读取），确保非推挽输出 */
    P3M1 &= ~0x04;
    P3M0 &= ~0x04;

    HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 1);   /* 占位（无真实优先级寄存器） */
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);           /* P3.2 上升沿触发并使能端口中断 */
    __HAL_GPIO_EXTI_CLEAR_IT(PAN312x_DIO8_PIN);
}

void PAN312x_DIO8_INTENABLE(void)
{
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void PAN312x_DIO8_INTDISABLE(void)
{
    HAL_NVIC_DisableIRQ(EXTI1_IRQn);
}

GPIO_PinState PAN312x_DIO8_GetState(void)
{
    return (PAN312x_DIO8) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}


/* ============================ RESET 引脚 ============================ */
void PAN312x_Reset_Init(void)
{
    P3M1 &= ~0x20;     /* P3.5 推挽输出 */
    P3M0 |=  0x20;
    PAN312x_RESET = 1; /* 空闲高（不复位） */
}

void PAN312x_Reset_High(void)
{
    PAN312x_RESET = 1;
}

void PAN312x_Reset_Low(void)
{
    PAN312x_RESET = 0;
}


/* ============================ 临界区（替代 __disable_irq/__enable_irq） ============================ */
static uint8_t radio_lock_depth = 0;
static uint8_t radio_saved_ea = 0;
void PAN312x_Lock(void)
{
    uint8_t saved = EA;
    EA = 0;
    if (radio_lock_depth == 0) radio_saved_ea = saved;
    radio_lock_depth++;
}

void PAN312x_Unlock(void)
{
    if (radio_lock_depth && --radio_lock_depth == 0) EA = radio_saved_ea;
}


/* ============================ SPI 数据收发 ============================ */
void PAN312x_DataBegin(void)
{
    PAN312x_NSS = 0;   /* 拉低片选，开始一帧 */
}

void PAN312x_DataEnd(void)
{
    PAN312x_NSS = 1;   /* 拉高片选，结束一帧 */
}

int PAN312x_DataWrite(const void* buf, int len)
{
    const uint8_t *p = (const uint8_t *)buf;
    int i;

    for (i = 0; i < len; i++)
        SpiInOutByte(p[i]);   /* 仅发，回读丢弃 */

    return len;
}

int PAN312x_DataRead(void* buf, int len)
{
    uint8_t *p = (uint8_t *)buf;
    int i;

    for (i = 0; i < len; i++)
        p[i] = SpiInOutByte(0x00);   /* 发哑元 0x00，读回数据 */

    return len;
}

/* 全双工（同时收发），保留接口以兼容原始 XIAOLAN 段 */
int PAN312x_DataWriteRead(const void* tx_buf, void* rx_buf, int len)
{
    const uint8_t *tx = (const uint8_t *)tx_buf;
    uint8_t *rx = (uint8_t *)rx_buf;
    int i;

    for (i = 0; i < len; i++)
        rx[i] = SpiInOutByte(tx[i]);

    return len;
}

void PAN312x_SPI3Wire_Test(void)
{
    /* 未使用，占位以满足 PAN312x_Hal.h 声明 */
}


/* ============================ 端口中断中转（P3 口 -> interrupt 13） ============================ */
/**
  * @brief  P3 端口中断服务程序（借保留中断号 13 入口）。
  *         DIO8(P3.2) 与第二路 PAN312x GPIO(P3.3) 共用 P3 端口中断，
  *         此处按 P3INTF 标志分发到对应回调。
  */
void Port3_ISR(void) interrupt 13
{
    uint8_t intf;

    EAXSFR();                       /* 允许访问 XSFR 端口中断寄存器 */
    intf = P3INTF;
    if (intf)
    {
        P3INTF = 0x00;              /* 写 0 清除端口中断标志（仿 Ra-05U 清 P1INTF） */

        if (intf & 0x04)            /* P3.2 = DIO8 上升沿 */
            HAL_GPIO_EXTI_IRQHandler(PAN312x_DIO8_PIN);

        if (intf & 0x08)            /* P3.3 = 第二路 PAN312x GPIO（回调 token = GPIO_PIN_5） */
            HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
    }
}


/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
