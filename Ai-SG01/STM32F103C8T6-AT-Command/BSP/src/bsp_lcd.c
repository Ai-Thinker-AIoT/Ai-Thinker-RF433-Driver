/**
  ******************************************************************************
  * 文件名 ：   bsp_lcd.c
  * 作者   ：   PAN312x RF Team
  * 版本   ：   V1.0.0
  * 时间   ：   
  * 文件描述：

*******************************************************************************/
#include "bsp.h"
#include "lcdfont.h"

/*
    开发板lcd资源分配：       
    LCD_BL  ---> PA2
    LCD_RST	---> PA3
    LCD_CS  ---> PA4(SPI1_NSS)
    LCD_SCK ---> PA5(SPI1_SCK)
    LCD_DC  ---> PA6(SPI1_MISO)
    LCD_MOSI---> PA7(SPI1_MOSI)
*/


#define LCD_SPIx				        SPI1
#define LCD_SPIx_CLK_ENABLE()	        __HAL_RCC_SPI1_CLK_ENABLE()

#define LCD_SPIx_SCK_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define LCD_SPIx_SCK_GPIO				GPIOA
#define LCD_SPIx_SCK_PIN				GPIO_PIN_5
#define LCD_SPIx_SCK_AF					GPIO_AF5_SPI1

#define LCD_SPIx_MOSI_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define LCD_SPIx_MOSI_GPIO				GPIOA
#define LCD_SPIx_MOSI_PIN 				GPIO_PIN_7
#define LCD_SPIx_MOSI_AF				GPIO_AF5_SPI1

#define LCD_SPIx_CSN_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define LCD_SPIx_CSN_GPIO				GPIOA
#define LCD_SPIx_CSN_PIN				GPIO_PIN_4

#define LCD_CSN_0()					    LCD_SPIx_CSN_GPIO->BSRR = ((uint32_t)LCD_SPIx_CSN_PIN << 16U) 
#define LCD_CSN_1()					    LCD_SPIx_CSN_GPIO->BSRR = (uint32_t)LCD_SPIx_CSN_PIN


#define LCD_DC_CLK_ENABLE()		        __HAL_RCC_GPIOA_CLK_ENABLE()
#define LCD_DC_GPIO				        GPIOA
#define LCD_DC_PIN 				        GPIO_PIN_6

#define LCD_DC_0()					    LCD_DC_GPIO->BSRR = ((uint32_t)LCD_DC_PIN << 16U) 
#define LCD_DC_1()					    LCD_DC_GPIO->BSRR = (uint32_t)LCD_DC_PIN

#define LCD_BL_CLK_ENABLE()		        __HAL_RCC_GPIOA_CLK_ENABLE()
#define LCD_BL_GPIO				        GPIOA
#define LCD_BL_PIN				        GPIO_PIN_2

#define LCD_BL_0()					    LCD_BL_GPIO->BSRR = ((uint32_t)LCD_BL_PIN << 16U) 
#define LCD_BL_1()					    LCD_BL_GPIO->BSRR = (uint32_t)LCD_BL_PIN

#define LCD_RST_CLK_ENABLE()		    __HAL_RCC_GPIOA_CLK_ENABLE()
#define LCD_RST_GPIO				    GPIOA
#define LCD_RST_PIN				        GPIO_PIN_3


#define LCD_RST_0()					    LCD_RST_GPIO->BSRR = ((uint32_t)LCD_RST_PIN << 16U) 
#define LCD_RST_1()					    LCD_RST_GPIO->BSRR = (uint32_t)LCD_RST_PIN


static SPI_HandleTypeDef lcd_hspi = {0};

void bsp_InitLcdGpio()
{
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
	LCD_SPIx_SCK_CLK_ENABLE();
	LCD_SPIx_MOSI_CLK_ENABLE();
    LCD_SPIx_CSN_CLK_ENABLE();
    
    
    LCD_BL_CLK_ENABLE();
    LCD_RST_CLK_ENABLE();
    
    LCD_DC_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /*##-2- Configure peripheral GPIO ##########################################*/  
    /* SPI SCK GPIO pin configuration  */
    GPIO_InitStruct.Pin       = LCD_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLDOWN;		/* ?? */
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_MEDIUM;
    GPIO_InitStruct.Alternate = LCD_SPIx_SCK_AF;
    HAL_GPIO_Init(LCD_SPIx_SCK_GPIO, &GPIO_InitStruct);

    /* SPI MOSI GPIO pin configuration  */
    GPIO_InitStruct.Pin = LCD_SPIx_MOSI_PIN;
    GPIO_InitStruct.Alternate = LCD_SPIx_MOSI_AF;
    HAL_GPIO_Init(LCD_SPIx_MOSI_GPIO, &GPIO_InitStruct);
    
    /* Configure the LCD_CSN pin */
    GPIO_InitStruct.Pin = LCD_SPIx_CSN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    //GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LCD_SPIx_CSN_GPIO, &GPIO_InitStruct);
    
    /* Configure the LCD_RST pin */
    GPIO_InitStruct.Pin = LCD_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    //GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LCD_RST_GPIO, &GPIO_InitStruct);
    
    
    /* Configure the LCD_DC pin */
    GPIO_InitStruct.Pin = LCD_DC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    //GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LCD_DC_GPIO, &GPIO_InitStruct);
    
    
    /* Configure the LCD_BL pin */
    GPIO_InitStruct.Pin = LCD_BL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    //GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LCD_BL_GPIO, &GPIO_InitStruct);
}
/**
  * @简介：该函数用于MCU对SPI配置初始化；
  * @参数：无
  * @返回值：无
  */
void bsp_InitLcdSpi(void)
{
    /* Enable SPI1 clock */
    LCD_SPIx_CLK_ENABLE();
    
    lcd_hspi.Instance               = LCD_SPIx;
    lcd_hspi.Init.Mode 			    = SPI_MODE_MASTER;
	lcd_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
//	lcd_hspi.Init.Direction         = SPI_DIRECTION_1LINES;
//	lcd_hspi.Init.CLKPhase          = SPI_PHASE_2EDGE;
//	lcd_hspi.Init.CLKPolarity       = SPI_POLARITY_HIGH;
    lcd_hspi.Init.Direction         = SPI_DIRECTION_1LINE;//SPI_DIRECTION_2LINES;
	lcd_hspi.Init.CLKPhase          = SPI_PHASE_1EDGE;
	lcd_hspi.Init.CLKPolarity       = SPI_POLARITY_LOW;
    lcd_hspi.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	lcd_hspi.Init.CRCPolynomial     = 7;
	lcd_hspi.Init.DataSize          = SPI_DATASIZE_8BIT;
	lcd_hspi.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    lcd_hspi.Init.NSS               = SPI_NSS_SOFT;
	lcd_hspi.Init.TIMode            = SPI_TIMODE_DISABLE;

    if(HAL_SPI_Init(&lcd_hspi) != HAL_OK)

    {
        while(1);
    }
}


void bsp_LcdWriteByte(uint8_t byte)
{
    LCD_CSN_0();
    HAL_SPI_Transmit(&lcd_hspi, &byte, 1, 1000);
    LCD_CSN_1();
}


void bsp_LcdWriteData8(uint8_t data)
{
	bsp_LcdWriteByte(data);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void bsp_LcdWriteData16(uint16_t data)
{
	bsp_LcdWriteByte(data>>8);
	bsp_LcdWriteByte(data);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void bsp_LcdWriteReg(uint8_t data)
{
	LCD_DC_0();//写命令
	bsp_LcdWriteByte(data);
	LCD_DC_1();//写数据
}

void bsp_LcdReset(void)
{
    LCD_RST_0();  //复位
	bsp_DelayMS(100);
	LCD_RST_1();
}


void bsp_LcdBackLightOn(void)
{
     LCD_BL_1();
}
void bsp_LcdBackLightOff(void)
{
    LCD_BL_0();
}


void bsp_InitLcdReg(void)
{
    //************* Start Initial Sequence **********//
	bsp_LcdWriteReg(0x11);  //Sleep out 
	bsp_DelayMS(120);              //Delay 120ms 
	//------------------------------------ST7735S Frame Rate-----------------------------------------// 
	bsp_LcdWriteReg(0xB1); 
	bsp_LcdWriteData8(0x05); 
	bsp_LcdWriteData8(0x3C); 
	bsp_LcdWriteData8(0x3C); 
	bsp_LcdWriteReg(0xB2); 
	bsp_LcdWriteData8(0x05);
	bsp_LcdWriteData8(0x3C); 
	bsp_LcdWriteData8(0x3C); 
	bsp_LcdWriteReg(0xB3); 
	bsp_LcdWriteData8(0x05); 
	bsp_LcdWriteData8(0x3C); 
	bsp_LcdWriteData8(0x3C); 
	bsp_LcdWriteData8(0x05); 
	bsp_LcdWriteData8(0x3C); 
	bsp_LcdWriteData8(0x3C); 
	//------------------------------------End ST7735S Frame Rate---------------------------------// 
	bsp_LcdWriteReg(0xB4); //Dot inversion 
	bsp_LcdWriteData8(0x03); 
	//------------------------------------ST7735S Power Sequence---------------------------------// 
	bsp_LcdWriteReg(0xC0); 
	bsp_LcdWriteData8(0x28); 
	bsp_LcdWriteData8(0x08); 
	bsp_LcdWriteData8(0x04); 
	bsp_LcdWriteReg(0xC1); 
	bsp_LcdWriteData8(0XC0); 
	bsp_LcdWriteReg(0xC2); 
	bsp_LcdWriteData8(0x0D); 
	bsp_LcdWriteData8(0x00); 
	bsp_LcdWriteReg(0xC3); 
	bsp_LcdWriteData8(0x8D); 
	bsp_LcdWriteData8(0x2A); 
	bsp_LcdWriteReg(0xC4); 
	bsp_LcdWriteData8(0x8D); 
	bsp_LcdWriteData8(0xEE); 
	//---------------------------------End ST7735S Power Sequence-------------------------------------// 
	bsp_LcdWriteReg(0xC5); //VCOM 
	bsp_LcdWriteData8(0x1A); 
	bsp_LcdWriteReg(0x36); //MX, MY, RGB mode 
	if(USE_HORIZONTAL == 0){
        bsp_LcdWriteData8(0x00);
    }else if(USE_HORIZONTAL == 1){
        bsp_LcdWriteData8(0xC0);
    }else if(USE_HORIZONTAL == 2){
        bsp_LcdWriteData8(0x70);
	}else {
        bsp_LcdWriteData8(0xA0); 
	}
    //------------------------------------ST7735S Gamma Sequence---------------------------------// 
	bsp_LcdWriteReg(0xE0); 
	bsp_LcdWriteData8(0x04); 
	bsp_LcdWriteData8(0x22); 
	bsp_LcdWriteData8(0x07); 
	bsp_LcdWriteData8(0x0A); 
	bsp_LcdWriteData8(0x2E); 
	bsp_LcdWriteData8(0x30); 
	bsp_LcdWriteData8(0x25); 
	bsp_LcdWriteData8(0x2A); 
	bsp_LcdWriteData8(0x28); 
	bsp_LcdWriteData8(0x26); 
	bsp_LcdWriteData8(0x2E); 
	bsp_LcdWriteData8(0x3A); 
	bsp_LcdWriteData8(0x00); 
	bsp_LcdWriteData8(0x01); 
	bsp_LcdWriteData8(0x03); 
	bsp_LcdWriteData8(0x13); 
	bsp_LcdWriteReg(0xE1); 
	bsp_LcdWriteData8(0x04); 
	bsp_LcdWriteData8(0x16); 
	bsp_LcdWriteData8(0x06); 
	bsp_LcdWriteData8(0x0D); 
	bsp_LcdWriteData8(0x2D); 
	bsp_LcdWriteData8(0x26); 
	bsp_LcdWriteData8(0x23); 
	bsp_LcdWriteData8(0x27); 
	bsp_LcdWriteData8(0x27); 
	bsp_LcdWriteData8(0x25); 
	bsp_LcdWriteData8(0x2D); 
	bsp_LcdWriteData8(0x3B); 
	bsp_LcdWriteData8(0x00); 
	bsp_LcdWriteData8(0x01); 
	bsp_LcdWriteData8(0x04); 
	bsp_LcdWriteData8(0x13); 
	//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
	bsp_LcdWriteReg(0x3A); //65k mode 
	bsp_LcdWriteData8(0x05); 
	bsp_LcdWriteReg(0x29); //Display on 
}

void bsp_InitLcd(void)
{
    bsp_InitLcdGpio();
    bsp_InitLcdSpi();
    bsp_LcdReset();
    
    bsp_LcdBackLightOn();
    
    bsp_DelayMS(100);
    bsp_InitLcdReg();
    
    bsp_LcdFill(0,0,LCD_W,LCD_H,WHITE);
    
}


/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void bsp_LcdFill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
	bsp_LcdAddressSet(xsta,ysta,xend-1,yend-1);//设置显示范围
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			bsp_LcdWriteData16(color);
		}
	} 					  	    
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void bsp_LcdAddressSet(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		bsp_LcdWriteReg(0x2a);//列地址设置
		bsp_LcdWriteData16(x1+2);
		bsp_LcdWriteData16(x2+2);
		bsp_LcdWriteReg(0x2b);//行地址设置
		bsp_LcdWriteData16(y1+1);
		bsp_LcdWriteData16(y2+1);
		bsp_LcdWriteReg(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		bsp_LcdWriteReg(0x2a);//列地址设置
		bsp_LcdWriteData16(x1+2);
		bsp_LcdWriteData16(x2+2);
		bsp_LcdWriteReg(0x2b);//行地址设置
		bsp_LcdWriteData16(y1+1);
		bsp_LcdWriteData16(y2+1);
		bsp_LcdWriteReg(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		bsp_LcdWriteReg(0x2a);//列地址设置
		bsp_LcdWriteData16(x1+1);
		bsp_LcdWriteData16(x2+1);
		bsp_LcdWriteReg(0x2b);//行地址设置
		bsp_LcdWriteData16(y1+2);
		bsp_LcdWriteData16(y2+2);
		bsp_LcdWriteReg(0x2c);//储存器写
	}
	else
	{
		bsp_LcdWriteReg(0x2a);//列地址设置
		bsp_LcdWriteData16(x1+1);
		bsp_LcdWriteData16(x2+1);
		bsp_LcdWriteReg(0x2b);//行地址设置
		bsp_LcdWriteData16(y1+2);
		bsp_LcdWriteData16(y2+2);
		bsp_LcdWriteReg(0x2c);//储存器写
	}
}


/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void bsp_LcdDrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	bsp_LcdAddressSet(x,y,x,y);//设置光标位置 
	bsp_LcdWriteData16(color);
} 


/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void bsp_LcdDrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		bsp_LcdDrawPoint(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}



/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   矩形的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	bsp_LcdDrawLine(x1,y1,x2,y1,color);
	bsp_LcdDrawLine(x1,y1,x1,y2,color);
	bsp_LcdDrawLine(x1,y2,x2,y2,color);
	bsp_LcdDrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
                color   圆的颜色
      返回值：  无
******************************************************************************/
void bsp_LcdDrawCircle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		bsp_LcdDrawPoint(x0-b,y0-a,color);             //3           
		bsp_LcdDrawPoint(x0+b,y0-a,color);             //0           
		bsp_LcdDrawPoint(x0-a,y0+b,color);             //1                
		bsp_LcdDrawPoint(x0-a,y0-b,color);             //2             
		bsp_LcdDrawPoint(x0+b,y0+a,color);             //4               
		bsp_LcdDrawPoint(x0+a,y0-b,color);             //5
		bsp_LcdDrawPoint(x0+a,y0+b,color);             //6 
		bsp_LcdDrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}

/******************************************************************************
      函数说明：显示汉字串
      入口数据：x,y显示坐标
                *s 要显示的汉字串
                fc 字的颜色
                bc 字的背景色
                sizey 字号 可选 16 24 32
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
//void bsp_LcdShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	while(*s!=0)
//	{
//		if(sizey == 12){
//            bsp_LcdShowChinese12x12(x,y,s,fc,bc,sizey,mode);
//		}else if(sizey == 16){
//            bsp_LcdShowChinese16x16(x,y,s,fc,bc,sizey,mode);
//		}else if(sizey == 24){
//            bsp_LcdShowChinese24x24(x,y,s,fc,bc,sizey,mode);
//        }else if(sizey==32){
//            bsp_LcdShowChinese32x32(x,y,s,fc,bc,sizey,mode);
//        }else{ 
//            return;
//        }
//		s+=2;
//		x+=sizey;
//	}
//}

/******************************************************************************
      函数说明：显示单个12x12汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
//void bsp_LcdShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//汉字数目
//	uint16_t TypefaceNum;//一个字符所占字节大小
//	uint16_t x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	                         
//	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
//		{ 	
//			bsp_LcdAddressSet(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont12[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
//						else LCD_WR_DATA(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont12[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
//} 

/******************************************************************************
      函数说明：显示单个16x16汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
//void bsp_LcdShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//汉字数目
//	uint16_t TypefaceNum;//一个字符所占字节大小
//	uint16_t x0=x;
//    TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont16[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
//						else LCD_WR_DATA(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont16[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
//} 


/******************************************************************************
      函数说明：显示单个24x24汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
//void bsp_LcdShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//汉字数目
//	uint16_t TypefaceNum;//一个字符所占字节大小
//	uint16_t x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont24[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
//						else LCD_WR_DATA(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont24[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
//} 

/******************************************************************************
      函数说明：显示单个32x32汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
//void bsp_LcdShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//汉字数目
//	uint16_t TypefaceNum;//一个字符所占字节大小
//	uint16_t x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont32[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
//						else LCD_WR_DATA(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont32[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
//}


/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void bsp_LcdShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//一个字符所占字节大小
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	bsp_LcdAddressSet(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey == 12){
            temp = ascii_1206[num][i];		 //调用6x12字体
		}else if(sizey == 16){
            temp = ascii_1608[num][i];		 //调用8x16字体
        }else if(sizey == 24){
            temp = ascii_2412[num][i];		 //调用12x24字体
        }else if(sizey == 32){
            temp = ascii_3216[num][i];		 //调用16x32字体
        }else {
            return;
        }
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t)){
                    bsp_LcdWriteData16(fc);
				}else {
                    bsp_LcdWriteData16(bc);
                }
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t)){
                    bsp_LcdDrawPoint(x,y,fc);//画一个点
				}
                x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void bsp_LcdShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		bsp_LcdShowChar(x,y,*p,fc,bc,sizey,mode);
		x += sizey / 2;
		p++;
	}  
}


/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void bsp_LcdShowIntNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow = 0;
	uint8_t sizex = sizey / 2;
	for(t = 0; t < len; t++){
		temp = (num/mypow(10,len-t-1))%10;
		if(enshow == 0 && t < (len-1)){
			if(temp == 0){
				bsp_LcdShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else{
                enshow=1; 
            }
		}
	 	bsp_LcdShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void bsp_LcdShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			bsp_LcdShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	bsp_LcdShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}


void bsp_LcdShowFloat(uint16_t x, uint16_t y, float num, uint8_t decimals)
{
    int integer = (int)num;
    float fraction = num - integer;
    
    // 显示整数部分
    bsp_LcdShowIntNum(x, y, integer, 3, RED, WHITE,16);
    
    // 显示小数点
    bsp_LcdShowChar(x + 8*sizeof(integer), y, '.', RED, WHITE, 16, 0);
    
    // 显示小数位
    for(uint8_t i=0; i<decimals; i++){
        fraction *= 10;
        int digit = (int)fraction;
        bsp_LcdShowIntNum(x + 8*(sizeof(integer)+1+i), y, digit, 3, RED, WHITE, 16);
        fraction -= digit;
    }
}

/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组    
      返回值：  无
******************************************************************************/
void bsp_LcdShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[])
{
	uint16_t i,j;
	uint32_t k=0;
	bsp_LcdAddressSet(x,y,x+length-1,y+width-1);
	for(i = 0; i < length; i++)
	{
		for(j = 0; j < width; j++)
		{
			bsp_LcdWriteData8(pic[k*2]);
			bsp_LcdWriteData8(pic[k*2+1]);
			k++;
		}
	}			
}

/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
