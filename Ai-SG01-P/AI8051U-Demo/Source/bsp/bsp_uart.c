/* ============================================================================
 * bsp_uart.c — AI8051U-34K64 UART1 调试串口驱动
 *   115200-8-N-1 @33.1776MHz：T1 方式2(8位自动重载) + 1T(T1x12=1) + SMOD=0
 *   波特率 = 33177600 / 9 / 32 = 115200（精确无误差，TH1=0xF7）
 *   接收：中断 4 + 256 字节环形缓冲。
 * ========================================================================== */
#include "bsp.h"      /* 必须最先包含：提供 uint8_t 等基础类型；bsp.h 内部已含 bsp_uart.h（守卫防重入） */

/* 环形缓冲 */
uint8_t  uart1_rxBuf[USART_RX_BUF_SIZE];
volatile uint16_t uart1_rxHead = 0;
volatile uint16_t uart1_rxTail = 0;
static volatile uint8_t uart_tx_done = 0;

/* putchar 发送超时阈值（软件循环）：正常单字节约 87us，给 50ms 余量 */
#define PUTCHAR_TIMEOUT_LOOPS   (50UL * (AI8051_SYS_CLK_HZ / 1000UL) / 8UL)

/* UART1 初始化：115200，T1 1T 波特率源 */
void bsp_InitUart(void)
{
    uart1_rxHead = 0;
    uart1_rxTail = 0;

    SCON = 0x50;                /* 方式1(8位UART)，REN=1 允许接收 */

    /* UART1 映射到 P3.6(RxD) / P3.7(TxD)，与实际 CH340 接线一致 */
    P_SW1 |= 0x40;              /* UART1: 01 = P3.6/P3.7 */
    P3M1 &= ~0x40;              /* P3.6 RxD 准双向 */
    P3M0 &= ~0x40;
    P3M1 &= ~0x80;              /* P3.7 TxD 推挽输出 */
    P3M0 |=  0x80;

    /* 波特率源 = T1（方式2，8位自动重载，1T） */
    TMOD &= 0x0F;               /* 清 T1 模式位 */
    TMOD |= 0x20;               /* T1 方式2 */
    AUXR |= T1x12;              /* T1 1T 模式 */
    AUXR &= ~S1BRT;             /* 波特率源 = T1 */
    PCON &= ~SMOD;              /* SMOD=0 */
    TH1 = 0xF7;                 /* 115200 @33.1776MHz */
    TL1 = 0xF7;

    ES  = 1;                    /* 允许串口1接收中断 */
    TR1 = 1;                    /* 启动 T1 */
}

/* C351 printf 字符重定向：等价 STM32 的 HAL_UART_Transmit 单字节 */
char putchar(char c)
{
    uint32_t timeout = PUTCHAR_TIMEOUT_LOOPS;

    uart_tx_done = 0;
    TI = 0;
    SBUF = c;                   /* 启动发送 */
    while (!uart_tx_done && !TI)
    {
        if (--timeout == 0UL)   /* 软件超时，防止串口失效时卡死 */
        {
            TI = 0;
            return c;
        }
    }
    TI = 0;                     /* 清发送完成标志 */
    return c;
}

/* UART1 接收中断：写入环形缓冲（不回显，主循环解析） */
void Uart1_ISR(void) interrupt 4
{
    uint8_t uartData;

    if (TI) { TI = 0; uart_tx_done = 1; }
    if (RI)
    {
        RI = 0;
        uartData = SBUF;

        /* 写指针追上读指针（满）则丢弃新字节，防止覆盖未读数据 */
        if (((uart1_rxHead + 1) % USART_RX_BUF_SIZE) != uart1_rxTail)
        {
            uart1_rxBuf[uart1_rxHead] = uartData;
            uart1_rxHead = (uart1_rxHead + 1) % USART_RX_BUF_SIZE;
        }
    }
}

/* 从环形缓冲读取最多 max_len 字节，返回实际读取数 */
uint16_t USART1_ReceiveData(uint8_t *buffer, uint16_t max_len)
{
    uint16_t count = 0;

    while ((uart1_rxTail != uart1_rxHead) && (count < max_len))
    {
        buffer[count++] = uart1_rxBuf[uart1_rxTail];
        uart1_rxTail = (uart1_rxTail + 1) % USART_RX_BUF_SIZE;
    }

    return count;
}

uint16_t USART1_GetRxCount(void)
{
    if (uart1_rxHead >= uart1_rxTail)
        return (uint16_t)(uart1_rxHead - uart1_rxTail);
    else
        return (uint16_t)(USART_RX_BUF_SIZE - uart1_rxTail + uart1_rxHead);
}

void USART1_ClearRxBuffer(void)
{
    uart1_rxHead = 0;
    uart1_rxTail = 0;
}
