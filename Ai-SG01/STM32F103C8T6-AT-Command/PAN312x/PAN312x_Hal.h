/**
  ******************************************************************************
  * 文件名 ：   PAN312x_Hal.h
  * 作者   ：   PAN312x RF Team
  * 版本   ：   V1.0.0
  * 时间   ：   
  * 文件描述：

*******************************************************************************/

#ifndef __PAN312x_HAL_H__
#define __PAN312x_HAL_H__
#include "bsp.h"	


#define PAN312x_IF_SPI          1

#define PAN312x_IF_I2C          0

#define PAN312x_IF_3SPI         0

//配置接口类型
#define PAN312x_INTERFACE       PAN312x_IF_SPI

//===================================SPI函数声明===================================================
void PAN312x_Set_AllGPIO_Analog(void);
void PAN312x_DIO8_INPUT(void);
void PAN312x_DIO8_INTENABLE(void);
void PAN312x_DIO8_INTDISABLE(void);
GPIO_PinState PAN312x_DIO8_GetState(void);
void PAN312x_Reset_Init(void);
void PAN312x_Reset_High(void);
void PAN312x_Reset_Low(void);
void PAN312x_SPIGPIO_Init(void);
void PAN312x_SPI_Init(void);
void PAN312x_SPI_DeInit(void);

void PAN312x_Lock(void);
void PAN312x_Unlock(void);
void PAN312x_SPI3Wire_Test(void);


#if PAN312x_INTERFACE == PAN312x_IF_SPI
void PAN312x_DataBegin(void);
void PAN312x_DataEnd(void);
int PAN312x_DataWrite(const void* buf, int len);
int PAN312x_DataRead(void* buf, int len);

#elif PAN312x_INTERFACE == PAN312x_IF_3SPI

void PAN312x_DataBegin(void);
void PAN312x_DataEnd(void);
int PAN312x_DataWrite(const void* buf, int len);
int PAN312x_DataRead(void* buf, int len);

#elif PAN312x_INTERFACE == PAN312x_IF_I2C

#define PAN312x_I2C_SLAVE_ADDR  (0x73 << 1)

void PAN312x_DataBegin(void);
void PAN312x_DataReadBegin(void);
void PAN312x_DataEnd(void);
int PAN312x_DataWrite(const void* buf, int len);
int PAN312x_DataRead(void* buf, int len);

#endif //PAN312x_INTERFACE

#endif //__PAN312x_HAL_H__


/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
