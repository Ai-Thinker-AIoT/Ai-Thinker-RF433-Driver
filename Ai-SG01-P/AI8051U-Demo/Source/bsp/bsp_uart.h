/* ============================================================================
 * bsp_uart.h — AI8051U-34K64 UART1 调试串口（替代 STM32 的 huart1 / HAL_UART）
 *   波特率 115200-8-N-1，默认引脚 P3.6(RXD) / P3.7(TXD)（不切换 P_SW1）。
 *   接收采用环形缓冲，USART1_ReceiveData() 供主循环轮询读取。
 *   printf 经本文件 putchar() 重定向到 UART1 TXD。
 * ========================================================================== */
#ifndef __BSP_UART_H
#define __BSP_UART_H

#define USART_RX_BUF_SIZE  256

/* 接收环形缓冲（供中断与主循环共享） */
extern uint8_t  uart1_rxBuf[USART_RX_BUF_SIZE];
extern volatile uint16_t uart1_rxHead;
extern volatile uint16_t uart1_rxTail;

void    bsp_InitUart(void);
uint16_t USART1_ReceiveData(uint8_t *buffer, uint16_t max_len);
uint16_t USART1_GetRxCount(void);
void    USART1_ClearRxBuffer(void);

/* C351 printf 字符输出重定向（printf/sprintf 经此从 UART1 发出）。
   说明：C351_STDIO.H 已将 putchar 声明为 void putchar(char)，其定义见 bsp_uart.c，
   此处不再重复声明，避免与库原型冲突（C231 _putchar redefinition）。 */

#endif /* __BSP_UART_H */
