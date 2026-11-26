/**
  ******************************************************************************
  * 文件名 ：   bsp_led.h
  * 作者   ：   PAN312x RF Team
  * 版本   ：   V1.0.0
  * 时间   ：   
  * 文件描述：

*******************************************************************************/
#include "bsp.h"

/*
        开发板LED口线分配：
		GREEN    : PA8    (高电平点亮，低电平熄灭)
		BLUE     : PB15   (高电平点亮，低电平熄灭)
*/

/* LED口对应的RCC时钟 */
#define LED_GPIO_CLK_ALLENABLE() {	    \
		__HAL_RCC_GPIOA_CLK_ENABLE();	\
		__HAL_RCC_GPIOB_CLK_ENABLE(); \
	};

#define GPIO_PORT_LED1  GPIOA
#define GPIO_PIN_LED1	GPIO_PIN_11
   

#define GPIO_PORT_LED2  GPIOA
#define GPIO_PIN_LED2	GPIO_PIN_12

#define GPIO_PORT_LED3  GPIOA
#define GPIO_PIN_LED3	GPIO_PIN_8

// LED引脚定义
#define GREEN_LED_GPIO_PORT 	GPIOA
#define GREEN_LED_GPIO_PIN 		GPIO_PIN_8
	
#define BLUE_LED_GPIO_PORT 		GPIOB
#define BLUE_LED_GPIO_PIN 		GPIO_PIN_15


/*
*********************************************************************************************************
*	函 数 名: bsp_InitLed
*	功能说明: 配置LED指示灯相关的GPIO,  该函数被 bsp_Init() 调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitLed(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/* 打开GPIO时钟 */
	LED_GPIO_CLK_ALLENABLE();
	
	/*
		配置所有的LED指示灯GPIO为推挽输出模式
		由于将GPIO设置为输出时，GPIO输出寄存器的值缺省是0，因此会驱动LED点亮.
		这是我不希望的，因此在改变GPIO为输出前，先关闭LED指示灯
	*/
	bsp_LedOff(GREEN_LED);
	bsp_LedOff(BLUE_LED);

	// 配置Green LED引脚 (PA8)
	GPIO_InitStruct.Pin = GREEN_LED_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GREEN_LED_GPIO_PORT, &GPIO_InitStruct);
	
	// 配置Blue LED引脚 (PB15)
	GPIO_InitStruct.Pin = BLUE_LED_GPIO_PIN;
	HAL_GPIO_Init(BLUE_LED_GPIO_PORT, &GPIO_InitStruct);
	
}

// 点亮Green LED
void Green_LED_On(void)
{
    HAL_GPIO_WritePin(GREEN_LED_GPIO_PORT, GREEN_LED_GPIO_PIN, GPIO_PIN_SET);
}

// 关闭Green LED
void Green_LED_Off(void)
{
    HAL_GPIO_WritePin(GREEN_LED_GPIO_PORT, GREEN_LED_GPIO_PIN, GPIO_PIN_RESET);
}

// 切换Green LED状态
void Green_LED_Toggle(void)
{
    HAL_GPIO_TogglePin(GREEN_LED_GPIO_PORT, GREEN_LED_GPIO_PIN);
}

// 点亮Blue LED
void Blue_LED_On(void)
{
    HAL_GPIO_WritePin(BLUE_LED_GPIO_PORT, BLUE_LED_GPIO_PIN, GPIO_PIN_SET);
}

// 关闭Blue LED
void Blue_LED_Off(void)
{
    HAL_GPIO_WritePin(BLUE_LED_GPIO_PORT, BLUE_LED_GPIO_PIN, GPIO_PIN_RESET);
}

// 切换Blue LED状态
void Blue_LED_Toggle(void)
{
    HAL_GPIO_TogglePin(BLUE_LED_GPIO_PORT, BLUE_LED_GPIO_PIN);
}

/*
*********************************************************************************************************
*	函 数 名: bsp_LedOn
*	功能说明: 点亮指定的LED指示灯。
*	形    参:  _no : 指示灯序号
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_LedOn(uint8_t _no)
{
	if (_no == GREEN_LED)
	{
		HAL_GPIO_WritePin(GREEN_LED_GPIO_PORT, GREEN_LED_GPIO_PIN, GPIO_PIN_SET);
	}
	else if (_no == BLUE_LED)
	{
		HAL_GPIO_WritePin(BLUE_LED_GPIO_PORT, BLUE_LED_GPIO_PIN, GPIO_PIN_SET);
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_LedOff
*	功能说明: 熄灭指定的LED指示灯。
*	形    参:  _no : 指示灯序号
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_LedOff(uint8_t _no)
{
	if (_no == GREEN_LED)
	{
		HAL_GPIO_WritePin(GREEN_LED_GPIO_PORT, GREEN_LED_GPIO_PIN, GPIO_PIN_RESET);
	}
	else if (_no == BLUE_LED)
	{
		HAL_GPIO_WritePin(BLUE_LED_GPIO_PORT, BLUE_LED_GPIO_PIN, GPIO_PIN_RESET);
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_LedToggle
*	功能说明: 翻转指定的LED指示灯。
*	形    参:  _no : 指示灯序号
*	返 回 值: 按键代码
*********************************************************************************************************
*/
void bsp_LedToggle(uint8_t _no)
{
	if (_no == GREEN_LED)
	{
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_PORT, GREEN_LED_GPIO_PIN);
	}
	else if (_no == BLUE_LED)
	{
		HAL_GPIO_TogglePin(BLUE_LED_GPIO_PORT, BLUE_LED_GPIO_PIN);
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_IsLedOn
*	功能说明: 判断LED指示灯是否已经点亮。
*	形    参:  _no : 指示灯序号
*	返 回 值: 1表示已经点亮，0表示未点亮
*********************************************************************************************************
*/
uint8_t bsp_IsLedOn(uint8_t _no)
{
	if (_no == GREEN_LED)
	{
		if (HAL_GPIO_ReadPin(GREEN_LED_GPIO_PORT, GREEN_LED_GPIO_PIN) == GPIO_PIN_SET)
		{
			return GPIO_PIN_SET;
		}
		return GPIO_PIN_RESET;
	}
	else if (_no == BLUE_LED)
	{
		if (HAL_GPIO_ReadPin(BLUE_LED_GPIO_PORT, BLUE_LED_GPIO_PIN) == GPIO_PIN_SET)
		{
			return GPIO_PIN_SET;
		}
		return GPIO_PIN_RESET;
	}

	return 0;
}
/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
