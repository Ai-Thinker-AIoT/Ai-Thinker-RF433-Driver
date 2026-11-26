/**
  ******************************************************************************
  * @file    bsp_uart.c
  * @brief   USART1 (PA9=TX, PA10=RX @115200, 8N1) driver for the StdPeriph port.
  *
  * @note    Ported from the original Ai-SG01 bsp_uart.c. The ST HAL UART handle
  *          and HAL_UART_* calls are replaced by direct StdPeriph register
  *          programming + a small receive ring buffer. The public API (ring
  *          buffer based) and the printf/fgetc retargeting are preserved exactly
  *          so the firmware keeps working unchanged.
  ******************************************************************************
  */
#include "bsp_uart.h"

/* USART1 clock is on APB2 (72 MHz on this board). */
#define USART1_BAUDRATE   115200u
#define USART1_PCLK       SystemCoreClock   /* APB2 = HCLK = 72 MHz */

static uint8_t  usart_rx_buf[USART_RX_BUF_SIZE];
static volatile uint16_t usart_rx_head = 0;
static volatile uint16_t usart_rx_tail = 0;

/* Redirect printf() to USART1 (polling). */
int fputc(int ch, FILE *f)
{
    (void)f;
    /* 等待上一次发送完成 */
    while ((USART1->SR & USART_SR_TXE) == 0u)
    {
    }
    USART1->DR = (uint8_t)ch;
    /* 等待发送完毕（TC），确保连续打印不丢字节 */
    while ((USART1->SR & USART_SR_TC) == 0u)
    {
    }
    return ch;
}

int fgetc(FILE *f)
{
    (void)f;
    /* 阻塞等待接收一个字节 */
    while ((USART1->SR & USART_SR_RXNE) == 0u)
    {
    }
    return (int)USART1->DR;
}

#if defined(__GNUC__)
/* ARM GNU Toolchain (newlib-nano) retarget: printf() -> _write_r -> _write().
 * Matches the working official Ai-SG01_ATCommandFirmware, which puts _write()
 * here next to the UART driver (not in syscalls.c). The official code calls
 * HAL_UART_Transmit; this StdPeriph port drives USART1 registers directly.
 * Return the byte count, otherwise newlib treats the write as failed. */
int _write(int fd, const void *buf, size_t len)
{
    const uint8_t *p = (const uint8_t *)buf;
    size_t i;

    (void)fd;
    for (i = 0; i < len; i++)
    {
        while ((USART1->SR & USART_SR_TXE) == 0u)
        {
        }
        USART1->DR = (uint8_t)p[i];
    }
    while ((USART1->SR & USART_SR_TC) == 0u)
    {
    }
    return (int)len;
}
#endif

void bsp_InitUart(void)
{
    /* 1. 打开时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

    /* 2. 配置 GPIO：PA9 = TX (AF_PP, 50MHz)，PA10 = RX (input floating) */
    /* CRL 只管 PA0..PA7；PA9/PA10 在 CRH。
     * PA9  -> CRH[7:4]  = MODE=11(50MHz), CNF=10(AF_PP) => 0xB
     * PA10 -> CRH[11:8] = MODE=00(input), CNF=01(floating) => 0x4
     * 写成 CRL 会让 PA9 保持复位默认的浮空输入，TX 脚完全没有输出。 */
    GPIOA->CRH &= ~(0xFu << 4);
    GPIOA->CRH |=  (0xBu << 4);
    GPIOA->CRH &= ~(0xFu << 8);
    GPIOA->CRH |=  (0x4u << 8);

    /* 3. 配置波特率：BRR = PCLK / baud */
    USART1->BRR = (uint16_t)(USART1_PCLK / USART1_BAUDRATE);

    /* 4. 使能 USART、发送、接收、接收中断 (TXE/TC 用轮询，RXNE 用中断) */
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    USART1->CR2 = 0u;
    USART1->CR3 = 0u;

    /* 5. 配置 NVIC */
    NVIC_SetPriority(USART1_IRQn, 5u);   /* 不调用 FreeRTOS API，任意优先级均可 */
    NVIC_EnableIRQ(USART1_IRQn);

    /* 6. 初始化环形缓冲区 */
    usart_rx_head = 0;
    usart_rx_tail = 0;
    memset(usart_rx_buf, 0, USART_RX_BUF_SIZE);
}

void USART1_Reinit(void)
{
    bsp_InitUart();
}

void USART1_EnterSleep(void)
{
    /* 仅关闭 USART1 外设时钟与中断；不要关 GPIOA 时钟，否则会波及 SPI/LED */
    NVIC_DisableIRQ(USART1_IRQn);
    USART1->CR1 &= ~(USART_CR1_UE | USART_CR1_RXNEIE);
    RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
}

void USART1_SendString(const char *str)
{
    USART1_SendData((uint8_t *)str, (uint16_t)strlen(str));
}

void USART1_SendData(uint8_t *data, uint16_t size)
{
    for (uint16_t i = 0u; i < size; i++)
    {
        while ((USART1->SR & USART_SR_TXE) == 0u)
        {
        }
        USART1->DR = data[i];
    }
    while ((USART1->SR & USART_SR_TC) == 0u)
    {
    }
}

uint16_t USART1_ReceiveData(uint8_t *buffer, uint16_t max_len)
{
    uint16_t count = 0u;

    while ((usart_rx_tail != usart_rx_head) && (count < max_len))
    {
        buffer[count++] = usart_rx_buf[usart_rx_tail];
        usart_rx_tail = (uint16_t)((usart_rx_tail + 1u) % USART_RX_BUF_SIZE);
    }
    return count;
}

uint16_t USART1_GetRxCount(void)
{
    if (usart_rx_head >= usart_rx_tail)
    {
        return (uint16_t)(usart_rx_head - usart_rx_tail);
    }
    return (uint16_t)(USART_RX_BUF_SIZE - usart_rx_tail + usart_rx_head);
}

void USART1_ClearRxBuffer(void)
{
    usart_rx_head = 0;
    usart_rx_tail = 0;
}

/* USART1 中断服务程序：仅处理 RXNE（环形缓冲） */
void USART1_IRQHandler(void)
{
    if ((USART1->SR & USART_SR_RXNE) != 0u)
    {
        uint8_t ch = (uint8_t)USART1->DR;

        usart_rx_buf[usart_rx_head] = ch;
        usart_rx_head = (uint16_t)((usart_rx_head + 1u) % USART_RX_BUF_SIZE);

        /* 缓冲溢出时丢弃最旧数据，移动 tail */
        if (usart_rx_head == usart_rx_tail)
        {
            usart_rx_tail = (uint16_t)((usart_rx_tail + 1u) % USART_RX_BUF_SIZE);
        }
    }
}

/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
