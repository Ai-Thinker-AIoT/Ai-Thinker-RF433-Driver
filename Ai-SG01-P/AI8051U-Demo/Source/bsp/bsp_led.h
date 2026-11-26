/* ============================================================================
 * bsp_led.h — AI8051U-34K64 状态 LED 驱动（替代 STM32 的 HAL_GPIO 控制）
 * 引脚分配（AI8051U-AISG01 模组）：
 *   P2.0  GREEN_LED  (推挽输出，高电平点亮)
 *   P2.1  BLUE_LED   (推挽输出，高电平点亮)
 * ========================================================================== */
#ifndef __BSP_LED_H
#define __BSP_LED_H

typedef enum {
    GREEN_LED = 0,
    BLUE_LED
} COLOUR_LED;

/* 外部使用的函数 */
void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no);
uint8_t bsp_IsLedOn(uint8_t _no);

#endif /* __BSP_LED_H */
