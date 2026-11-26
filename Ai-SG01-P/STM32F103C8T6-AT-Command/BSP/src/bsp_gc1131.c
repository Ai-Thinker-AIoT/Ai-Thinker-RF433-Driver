#include "bsp_gc1131.h"

// CPS
#define PAN312x_CPS_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_CPS_GPIO  							 GPIOB
#define PAN312x_CPS_PIN	 								 GPIO_PIN_0

// CSD引脚定义
#define PAN312x_CSD_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_CSD_GPIO                 GPIOB
#define PAN312x_CSD_PIN                  GPIO_PIN_11

#define PAN312x_CTX_PIN                  PAN312x_GPIO_PIN_2
   
/*
*********************************************************************************************************
*	函 数 名: bsp_InitGC1131
*	功能说明: 配置GC1131指示灯相关的GPIO,  该函数被 bsp_Init() 调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitGC1131(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/* 打开GPIO时钟 */
	PAN312x_CPS_CLK_ENABLE();

	// 配置CPS、CSD引脚 (PB0|PB11)
	GPIO_InitStruct.Pin = PAN312x_CPS_PIN | PAN312x_CSD_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PAN312x_CPS_GPIO, &GPIO_InitStruct);
	
	PAN312x_Iomux_Gpio(IOMUX_GPIO2_AS_GPIO);
	PAN312x_Set_Gpio_Mode(PAN312x_CTX_PIN, GPIO_OUTPUT_MODE);

}

void PAN312x_GC1131_Set_Mode(GC1131_ModeTypeDef mode)
{
    switch (mode) {
        case GC1131_MODE_SHUTDOWN:
//						printf("GC1131_MODE_SHUTDOWN\r\n");
            // CSD=0, CTX=X, CPS=X
            HAL_GPIO_WritePin(PAN312x_CSD_GPIO, PAN312x_CSD_PIN, GPIO_PIN_RESET);
            // CTX 和 CPS 可以设为任意值，但建议CPS设为1，降低功耗
            HAL_GPIO_WritePin(PAN312x_CPS_GPIO, PAN312x_CPS_PIN, GPIO_PIN_SET);
						PAN312x_Gpio_Write_Pin(PAN312x_CTX_PIN, 0);
            break;
            
        case GC1131_MODE_RECEIVE:
//						printf("GC1131_MODE_RECEIVE\r\n");
            // CSD=1, CTX=0, CPS=X
            HAL_GPIO_WritePin(PAN312x_CSD_GPIO, PAN312x_CSD_PIN, GPIO_PIN_SET);
            // CPS 设为 0 以节省功耗
            HAL_GPIO_WritePin(PAN312x_CPS_GPIO, PAN312x_CPS_PIN, GPIO_PIN_RESET);
						PAN312x_Gpio_Write_Pin(PAN312x_CTX_PIN, 0);
            break;
            
        case GC1131_MODE_TRANSMIT_BYPASS:
//						printf("GC1131_MODE_TRANSMIT_BYPASS\r\n");
            // CSD=1, CTX=1, CPS=0
            HAL_GPIO_WritePin(PAN312x_CSD_GPIO, PAN312x_CSD_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(PAN312x_CPS_GPIO, PAN312x_CPS_PIN, GPIO_PIN_RESET);
						PAN312x_Gpio_Write_Pin(PAN312x_CTX_PIN, 1);
            break;
            
        case GC1131_MODE_TRANSMIT:
//						printf("GC1131_MODE_TRANSMIT\r\n");
            // CSD=1, CTX=1, CPS=1
            HAL_GPIO_WritePin(PAN312x_CSD_GPIO, PAN312x_CSD_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(PAN312x_CPS_GPIO, PAN312x_CPS_PIN, GPIO_PIN_SET);
						PAN312x_Gpio_Write_Pin(PAN312x_CTX_PIN, 1);
            break;
    }
    
    // 添加适当延时确保模式切换稳定
    HAL_Delay(1);
}

#if 0
// Control GC1131 CPS
void GC1131_CPS_On(void)
{
    HAL_GPIO_WritePin(GPIO_PORT_CPS, GPIO_PIN_CPS, GPIO_PIN_SET);
}

// Control GC1131 CPS
void GC1131_CPS_Off(void)
{
    HAL_GPIO_WritePin(GPIO_PORT_CPS, GPIO_PIN_CPS, GPIO_PIN_RESET);
}

// Control GC1131 CTX
void GC1131_CTX_On(void)
{
    PAN312x_Iomux_Gpio(IOMUX_GPIO2_AS_GPIO);
    PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_2, GPIO_OUTPUT_MODE);
		PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_2, 1);
}

// Control GC1131 CTX
void GC1131_CTX_Off(void)
{
    PAN312x_Iomux_Gpio(IOMUX_GPIO2_AS_GPIO);
    PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_2, GPIO_OUTPUT_MODE);
		PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_2, 0);
}

uint8_t Get_CPS_Level(void)
{
		return HAL_GPIO_ReadPin(GPIO_PORT_CPS, GPIO_PIN_CPS);
}
#endif
