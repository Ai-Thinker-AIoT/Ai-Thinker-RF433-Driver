/**
  ******************************************************************************
  * 文件名 ：   bsp_lcd.h
  * 作者   ：   PAN312x RF Team
  * 版本   ：   V1.0.0
  * 时间   ：   
  * 文件描述：

*******************************************************************************/

#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "bsp.h"

#define USE_HORIZONTAL 3  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
    #define LCD_W 128
    #define LCD_H 160

#else
    #define LCD_W 160
    #define LCD_H 128
#endif


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

void bsp_InitLcd(void);
void bsp_InitLcdGpio(void);
void bsp_InitLcdSpi(void);
void bsp_InitLcdReg(void);
void bsp_LcdReset(void);
void bsp_LcdBackLightOn(void);
void bsp_LcdBackLightOff(void);


void bsp_LcdFill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void bsp_LcdWriteByte(uint8_t byte);
void bsp_LcdWriteData8(uint8_t data);
void bsp_LcdWriteData16(uint16_t data);
void bsp_LcdWriteReg(uint8_t data);
void bsp_LcdAddressSet(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void bsp_LcdDrawPoint(uint16_t x,uint16_t y,uint16_t color);
void bsp_LcdDrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);

void bsp_LcdDrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void bsp_LcdDrawCircle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);
void bsp_LcdShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void bsp_LcdShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void bsp_LcdShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void bsp_LcdShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void bsp_LcdShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void bsp_LcdShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void bsp_LcdShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
uint32_t mypow(uint8_t m,uint8_t n);
void bsp_LcdShowIntNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void bsp_LcdShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void bsp_LcdShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);
void bsp_LcdShowFloat(uint16_t x, uint16_t y, float num, uint8_t decimals);



#endif

/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/

