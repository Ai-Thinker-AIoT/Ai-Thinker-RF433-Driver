/* ============================================================================
 * bsp_led.c — AI8051U-34K64 状态 LED 驱动
 * 引脚：GREEN_LED -> P2.0，BLUE_LED -> P2.1，高电平点亮（与 STM32 极性一致）。
 * ========================================================================== */
#include "bsp.h"

/* LED 引脚（sbit） */
sbit LED_GREEN = P2^0;
sbit LED_BLUE  = P2^1;

/* LED 端口模式：推挽输出（P2.0 / P2.1） */
#define LED_GPIO_M0    0x03    /* P2.0,P2.1 */
#define LED_GPIO_M1    0x00

void bsp_InitLed(void)
{
    /* 端口模式：推挽输出 */
    P2M1 &= ~LED_GPIO_M0;
    P2M0 |=  LED_GPIO_M0;

    /* 初始熄灭（低电平） */
    bsp_LedOff(GREEN_LED);
    bsp_LedOff(BLUE_LED);
}

void bsp_LedOn(uint8_t _no)
{
    if (_no == GREEN_LED)
        LED_GREEN = 1;
    else if (_no == BLUE_LED)
        LED_BLUE = 1;
}

void bsp_LedOff(uint8_t _no)
{
    if (_no == GREEN_LED)
        LED_GREEN = 0;
    else if (_no == BLUE_LED)
        LED_BLUE = 0;
}

void bsp_LedToggle(uint8_t _no)
{
    if (_no == GREEN_LED)
        LED_GREEN = !LED_GREEN;
    else if (_no == BLUE_LED)
        LED_BLUE = !LED_BLUE;
}

uint8_t bsp_IsLedOn(uint8_t _no)
{
    if (_no == GREEN_LED)
        return (LED_GREEN != 0) ? 1 : 0;
    else if (_no == BLUE_LED)
        return (LED_BLUE != 0) ? 1 : 0;

    return 0;
}
