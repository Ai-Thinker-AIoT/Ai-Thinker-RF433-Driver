/**
  ******************************************************************************
  * �ļ��� ��   PAN312x_HAL.c
  * ����   ��   PAN312x RF Team
  * �汾   ��   V1.0.0
  * ʱ��   ��   
  * �ļ�������
  *     ���ļ�ΪPAN312xģ���Ӳ���㣬����MCU��PAN312xģ���SPI���ã�GPIO�ڳ�ʼ������
  *������PAN312x�Ĵ�����FIFO��д������
  *    �ͻ���ʹ��ģ��ʱ����Ҫ��ֲ���ļ�����֤�����������������ββ���������
  *�����Լ���MCUƽ̨�޸ĺ������ݣ�ʹ�������ܿ��������С�Ӳ����ռ����Դ���£�
	*
  *SPI��������ʹ��STM32L1��SPI3������PAN312xģ��ͨ�š�
  *GPIO�ڣ�������ʹ�õ�GPIO���������£�

  *        PA4  ---> CSN						PA4  ---> CSN
  *        PA5  ---> SCK						PA5  ---> SCK
  *        PA6  ---> MISO						PA6  ---> MISO
	*				 PA7  ---> MOSI						PA7  ---> MOSI
	*        PB0  ---> GPIO3(nRST)		PB14 ---> GPIO3(nRST)
  *        PB1  ---> GPIO8(IRQ)			PB1  ---> GPIO8(IRQ)
  *        PB10 ---> GPIO0					PA11 ---> GPIO0
  *        PB11 ---> GPIO1					PB0  ---> GPIO1
  *        PA11 ---> GPIO2					PA0  ---> GPIO2
  *        PA12 ---> GPIO9					NULL
  *        PB14 ---> GPIO10					PA12 ---> GPIO10

*******************************************************************************/
#include "bsp.h"

/* SPI peripheral selection */
#define PAN312x_SPIx                SPI1

/* SPI clock enable macros */
#define PAN312x_SPIx_CLK_ENABLE()    __HAL_RCC_SPI1_CLK_ENABLE()
#define PAN312x_SPIx_CLK_DISABLE()   __HAL_RCC_SPI1_CLK_DISABLE()

/* DMA clock enable */
#define DMAx_CLK_ENABLE()            __HAL_RCC_DMA1_CLK_ENABLE()

//#define SPIx_FORCE_RESET()			__HAL_RCC_SPI1_FORCE_RESET()
//#define SPIx_RELEASE_RESET()		__HAL_RCC_SPI1_RELEASE_RESET()


/* GPIO Configuration for STM32F103C8T6 */
/* SPI pins */
#define PAN312x_SPIx_SCK_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define PAN312x_SPIx_SCK_GPIO            GPIOA
#define PAN312x_SPIx_SCK_PIN             GPIO_PIN_5

#define PAN312x_SPIx_MISO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define PAN312x_SPIx_MISO_GPIO           GPIOA
#define PAN312x_SPIx_MISO_PIN            GPIO_PIN_6

#define PAN312x_SPIx_MOSI_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define PAN312x_SPIx_MOSI_GPIO           GPIOA
#define PAN312x_SPIx_MOSI_PIN            GPIO_PIN_7

#define PAN312x_SPIx_CSN_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define PAN312x_SPIx_CSN_GPIO            GPIOA
#define PAN312x_SPIx_CSN_PIN             GPIO_PIN_4

#define PAN312x_CSN_0()                  PAN312x_SPIx_CSN_GPIO->BRR  = PAN312x_SPIx_CSN_PIN
#define PAN312x_CSN_1()                  PAN312x_SPIx_CSN_GPIO->BSRR = PAN312x_SPIx_CSN_PIN

#if 0
/* IRQ Pin (DIO8) - matches MOD Connect interface */
#define PAN312x_DIO8_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_DIO8_GPIO                GPIOB
#define PAN312x_DIO8_PIN                 GPIO_PIN_1


/* Reset Pin (GPIO3/nRST) - matches MOD Connect interface */
#define PAN312x_RESET_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_RESET_GPIO               GPIOB
#define PAN312x_RESET_PIN                GPIO_PIN_0


/* Other GPIOs - matches MOD Connect interface */
#define PAN312x_DIO0_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_DIO0_GPIO                GPIOB
#define PAN312x_DIO0_PIN                 GPIO_PIN_10


#define PAN312x_DIO1_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_DIO1_GPIO                GPIOB
#define PAN312x_DIO1_PIN                 GPIO_PIN_11


#define PAN312x_DIO2_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define PAN312x_DIO2_GPIO                GPIOA
#define PAN312x_DIO2_PIN                 GPIO_PIN_11


#define PAN312x_DIO9_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define PAN312x_DIO9_GPIO                GPIOA
#define PAN312x_DIO9_PIN                 GPIO_PIN_12

#define PAN312x_DIO10_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_DIO10_GPIO               GPIOB
#define PAN312x_DIO10_PIN                GPIO_PIN_14
#else
/* IRQ Pin (DIO8) - matches MOD Connect interface */
#define PAN312x_DIO8_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_DIO8_GPIO                GPIOB
#define PAN312x_DIO8_PIN                 GPIO_PIN_1


/* Reset Pin (GPIO3/nRST) - matches MOD Connect interface */
#define PAN312x_RESET_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_RESET_GPIO               GPIOB
#define PAN312x_RESET_PIN                GPIO_PIN_14


/* Other GPIOs - matches MOD Connect interface */
#define PAN312x_DIO0_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_DIO0_GPIO                GPIOA
#define PAN312x_DIO0_PIN                 GPIO_PIN_11


#define PAN312x_DIO1_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_DIO1_GPIO                GPIOB
#define PAN312x_DIO1_PIN                 GPIO_PIN_0


#define PAN312x_DIO2_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define PAN312x_DIO2_GPIO                GPIOA
#define PAN312x_DIO2_PIN                 GPIO_PIN_0


//#define PAN312x_DIO9_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
//#define PAN312x_DIO9_GPIO                GPIOA
//#define PAN312x_DIO9_PIN                 GPIO_PIN_12

#define PAN312x_DIO10_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define PAN312x_DIO10_GPIO               GPIOA
#define PAN312x_DIO10_PIN                GPIO_PIN_12

#endif

static SPI_HandleTypeDef pan312x_hspi = {0};
/* DMA handles are only referenced by the commented-out DMA setup below; keep them for future use. */
static DMA_HandleTypeDef pan312x_hdma_tx __attribute__((unused));
static DMA_HandleTypeDef pan312x_hdma_rx __attribute__((unused));

#define WAIT_FOR_SPI_TC()               {while(!__HAL_DMA_GET_FLAG(pan312x_hspi.hdmarx, __HAL_DMA_GET_TC_FLAG_INDEX(pan312x_hspi.hdmarx)));\
                                          do{HAL_DMA_IRQHandler(pan312x_hspi.hdmarx);\
                                          HAL_DMA_IRQHandler(pan312x_hspi.hdmatx);\
                                          }while(HAL_SPI_GetState(&pan312x_hspi) != HAL_SPI_STATE_READY);}

//-----------------------------GPIO-----------------------------//
//�ò��ֺ���Ϊϵͳ�õ���GPIO�ĳ�ʼ���������û������Լ���ƽ̨��Ӧ�޸�
//--------------------------------------------------------------//
/**
  * @��飺��������PAN312x���ӵ�gpio��������Ϊģ��̬
  * @��������
  * @����ֵ����
  */
void PAN312x_Set_AllGPIO_Analog(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
   
	#if 0
	// ʹ��GPIOA��GPIOBʱ��
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// ���������������Ϊģ��ģʽ
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	// ֻ����GPIOA����Ҫ����������
	GPIO_InitStruct.Pin = PAN312x_SPIx_CSN_PIN | PAN312x_SPIx_SCK_PIN |
												 PAN312x_SPIx_MISO_PIN | PAN312x_SPIx_MOSI_PIN |
												 PAN312x_DIO2_PIN | PAN312x_DIO9_PIN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// ֻ����GPIOB����Ҫ����������
	GPIO_InitStruct.Pin = PAN312x_RESET_PIN | PAN312x_DIO8_PIN |
												 PAN312x_DIO0_PIN | PAN312x_DIO1_PIN |
												 PAN312x_DIO10_PIN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	#else
	// ʹ��GPIOA��GPIOBʱ��
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// ���������������Ϊģ��ģʽ
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	// ֻ����GPIOA����Ҫ����������
	GPIO_InitStruct.Pin = PAN312x_SPIx_CSN_PIN | PAN312x_SPIx_SCK_PIN |
												 PAN312x_SPIx_MISO_PIN | PAN312x_SPIx_MOSI_PIN |
												 PAN312x_DIO0_PIN | PAN312x_DIO2_PIN |
												 PAN312x_DIO10_PIN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// ֻ����GPIOB����Ҫ����������
	GPIO_InitStruct.Pin = PAN312x_RESET_PIN | PAN312x_DIO8_PIN |
												 PAN312x_DIO1_PIN ;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	#endif
	
}
/**
  * @��飺�ú���ΪGPIO8�����ʼ�����жϡ����ȼ����ã�
  * @��������
  * @����ֵ����
  */
void PAN312x_DIO8_INPUT()
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		
		PAN312x_DIO8_CLK_ENABLE();
		
		GPIO_InitStruct.Pin = PAN312x_DIO8_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(PAN312x_DIO8_GPIO, &GPIO_InitStruct);
		
		// Configure EXTI interrupt for PB1 (DIO8)
		HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 1);
		HAL_NVIC_EnableIRQ(EXTI1_IRQn);
		__HAL_GPIO_EXTI_CLEAR_IT(PAN312x_DIO8_PIN);
}
/**
  * @��飺�ú���ΪGPIO8�����жϿ���ʹ�ܣ�
  * @��������
  * @����ֵ����
  */
void PAN312x_DIO8_INTENABLE()
{
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    
}
/**
  * @��飺�ú���ΪDIO8�����жϹر�ʹ�ܣ�
  * @��������
  * @����ֵ����
  */
void PAN312x_DIO8_INTDISABLE()
{
    HAL_NVIC_DisableIRQ(EXTI1_IRQn);
}
/**
  * @��飺�ú���ΪDIO8����״̬��ȡ��
  * @��������
  * @����ֵ��DIO8״̬"1"or"0"
  */
GPIO_PinState PAN312x_DIO8_GetState()
{
    GPIO_PinState State;
    State = HAL_GPIO_ReadPin(PAN312x_DIO8_GPIO, PAN312x_DIO8_PIN);
    return State;
}


void PAN312x_Reset_OUTPUT(GPIO_PinState PinState)
{
    HAL_GPIO_WritePin(PAN312x_RESET_GPIO, PAN312x_RESET_PIN, PinState);
}
/**
  * @��飺Reset���ų�ʼ����
  * @������void��
  * @����ֵ����
  */
void PAN312x_Reset_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		
    PAN312x_RESET_CLK_ENABLE();
		
    GPIO_InitStruct.Pin = PAN312x_RESET_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PAN312x_RESET_GPIO, &GPIO_InitStruct);
}
/**
  * @��飺��Reset�������ߣ�
  * @������void��
  * @����ֵ����
  */
void PAN312x_Reset_High(void)
{
	
    PAN312x_RESET_GPIO->BSRR = (uint32_t)PAN312x_RESET_PIN;
}
/**
  * @��飺��Reset�������ͣ�
  * @������void��
  * @����ֵ����
  */
void PAN312x_Reset_Low(void)
{
		PAN312x_RESET_GPIO->BRR = PAN312x_RESET_PIN;
}

/**
  * @��飺��������SDK������
  * @��������
  * @����ֵ����
  */
void PAN312x_Lock(void)
{
	__disable_irq();
}
/**
  * @��飺��������SDK������
  * @��������
  * @����ֵ����
  */
void PAN312x_Unlock(void)
{
	__enable_irq();
}

//-----------------------------SPI-----------------------------//
//�ò��ֺ���ΪMCU��PAN312xģ��SPIͨ�Ų��֣�����SPI�ڼ����ó�ʼ��
//--------------------------------------------------------------//
#if PAN312x_INTERFACE == PAN312x_IF_SPI
/**
  * @��飺�ú�������MCU��SPI��ӦIO�ڳ�ʼ����
  * @��������
  * @����ֵ����
  */
void PAN312x_SPIGPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
		
		// Enable clocks
    PAN312x_SPIx_SCK_CLK_ENABLE();
    PAN312x_SPIx_MISO_CLK_ENABLE();
    PAN312x_SPIx_MOSI_CLK_ENABLE();
    PAN312x_SPIx_CSN_CLK_ENABLE();
    
    /*##-2- Configure peripheral GPIO ##########################################*/  
    /* SPI SCK GPIO pin configuration  */
    // SPI1 SCK (PA5)
    GPIO_InitStruct.Pin = PAN312x_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PAN312x_SPIx_SCK_GPIO, &GPIO_InitStruct);

    /* SPI MISO GPIO pin configuration  */
    // SPI1 MISO (PA6)
    GPIO_InitStruct.Pin = PAN312x_SPIx_MISO_PIN;
    HAL_GPIO_Init(PAN312x_SPIx_MISO_GPIO, &GPIO_InitStruct);

    /* SPI MOSI GPIO pin configuration  */
    GPIO_InitStruct.Pin = PAN312x_SPIx_MOSI_PIN;
    HAL_GPIO_Init(PAN312x_SPIx_MOSI_GPIO, &GPIO_InitStruct);
    
    /* Configure the PAN312x_CSN pin */
    // CSN (PA4)
    GPIO_InitStruct.Pin = PAN312x_SPIx_CSN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PAN312x_SPIx_CSN_GPIO, &GPIO_InitStruct);
}
/**
  * @��飺�ú�������MCU��SPI���ó�ʼ����
  * @��������
  * @����ֵ����
  */
void PAN312x_SPI_Init(void)
{
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
		PAN312x_SPIx_SCK_CLK_ENABLE();
    PAN312x_SPIx_MISO_CLK_ENABLE();
    PAN312x_SPIx_MOSI_CLK_ENABLE();
    PAN312x_SPIx_CSN_CLK_ENABLE();

    PAN312x_SPIGPIO_Init();
    
    /* Enable SPI1 clock */
    PAN312x_SPIx_CLK_ENABLE();
    
    pan312x_hspi.Instance = PAN312x_SPIx;
    pan312x_hspi.Init.Mode = SPI_MODE_MASTER;
    pan312x_hspi.Init.Direction = SPI_DIRECTION_2LINES;
    pan312x_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    pan312x_hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    pan312x_hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    pan312x_hspi.Init.NSS = SPI_NSS_SOFT;
    pan312x_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;//SPI_BAUDRATEPRESCALER_4;
    pan312x_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    pan312x_hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    pan312x_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    
    
    if(HAL_SPI_Init(&pan312x_hspi) != HAL_OK)
    {
        while(1);
    }
	
//    pan312x_hspi.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
//	pan312x_hspi.Init.CRCPolynomial     = 7;
//	pan312x_hspi.Init.FirstBit          = SPI_FIRSTBIT_MSB;
//	pan312x_hspi.Init.TIMode            = SPI_TIMODE_DISABLE;
	
	
//	pan312x_hspi.Instance = PAN312x_SPIx;
//	pan312x_hspi.Init.Mode = SPI_MODE_MASTER;
//	pan312x_hspi.Init.Direction = SPI_DIRECTION_2LINES;
//	pan312x_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
//	pan312x_hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
//	pan312x_hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
//	pan312x_hspi.Init.NSS = SPI_NSS_SOFT;
//	pan312x_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
//	pan312x_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
//	pan312x_hspi.Init.TIMode = SPI_TIMODE_DISABLE;
//	pan312x_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//	pan312x_hspi.Init.CRCPolynomial = 10;



//    __HAL_RCC_DMA1_CLK_ENABLE();

		// DMA configuration for STM32F103C8T6
    // TX DMA (SPI1_TX: DMA1 Channel3)
//    pan312x_hdma_tx.Instance = DMA1_Channel3;
//    pan312x_hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
//    pan312x_hdma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
//    pan312x_hdma_tx.Init.MemInc = DMA_MINC_ENABLE;
//    pan312x_hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//    pan312x_hdma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//    pan312x_hdma_tx.Init.Mode = DMA_NORMAL;
//    pan312x_hdma_tx.Init.Priority = DMA_PRIORITY_HIGH;
//    HAL_DMA_Init(&pan312x_hdma_tx);
//    __HAL_LINKDMA(&pan312x_hspi, hdmatx, pan312x_hdma_tx);
    
    
    
    
    // RXͨ����������ڴ棩
		// RX DMA (SPI1_RX: DMA1 Channel2)
//    pan312x_hdma_rx.Instance = DMA1_Channel2;
//    pan312x_hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
//    pan312x_hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
//    pan312x_hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
//    pan312x_hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//    pan312x_hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//    pan312x_hdma_rx.Init.Mode = DMA_NORMAL;
//    pan312x_hdma_rx.Init.Priority = DMA_PRIORITY_HIGH;
//    HAL_DMA_Init(&pan312x_hdma_rx);
//    __HAL_LINKDMA(&pan312x_hspi, hdmarx, pan312x_hdma_rx);

//    // DMA interrupt configuration
//    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);   
    
    PAN312x_CSN_1();
    
}


void PAN312x_SPI_DeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	PAN312x_SPIx_SCK_CLK_ENABLE();
	PAN312x_SPIx_MISO_CLK_ENABLE();
	PAN312x_SPIx_MOSI_CLK_ENABLE();
	PAN312x_SPIx_CSN_CLK_ENABLE();
	/* Configure the AF for MOSI, MISO and SCLK GPIO pins*/
	GPIO_InitStructure.Pin       = PAN312x_SPIx_SCK_PIN;
	GPIO_InitStructure.Mode      = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull      = GPIO_PULLUP;
	GPIO_InitStructure.Speed     = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PAN312x_SPIx_SCK_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = PAN312x_SPIx_MISO_PIN;
	HAL_GPIO_Init(PAN312x_SPIx_MISO_GPIO, &GPIO_InitStructure);
//	
	GPIO_InitStructure.Pin = PAN312x_SPIx_MOSI_PIN;
	HAL_GPIO_Init(PAN312x_SPIx_MOSI_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = PAN312x_SPIx_CSN_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(PAN312x_SPIx_CSN_GPIO, &GPIO_InitStructure);
	
	// ����SPI����ʱ���Խ�ʡ����
    PAN312x_SPIx_CLK_DISABLE();
}

/**
  * @��飺��ʼPAN312x�������շ�����SPI�ӿ�����CS
  * @��������
  * @����ֵ����
  */
void PAN312x_DataBegin(void)
{
	PAN312x_CSN_0();	
}
/**
  * @��飺����PAN312x�������շ�������ӿ�ΪSPI���ʾ����CS������ӿ�ΪI2C���ʾ���ͽ����ź�
  * @��������
  * @����ֵ����
  */
void PAN312x_DataEnd(void)
{
	PAN312x_CSN_1();
}
/**
  * @��飺��PAN312xд��һ�����ݣ�����ӿ�ΪSPI�򲻰���CS��������
  * @������buf - ���ݻ�����
  *        len - ���ݳ���
  * @����ֵ��д������ݳ��ȣ����ߴ���ֵ(����)
  */
int PAN312x_DataWrite(const void* buf, int len)
{
		HAL_StatusTypeDef status;
		
		// ʹ������ʽ���䣬�ʺ�С������
		status = HAL_SPI_Transmit(&pan312x_hspi, (uint8_t*)buf, len, 1000);
		
		if(status != HAL_OK) {
				return -1; // �������
		}
		
		return len;

}
/**
  * @��飺ͨ��SPI��PAN312x��ȡһ������ 
  * @������buf - ���ݻ�����
  *        len - ���ݳ���
  * @����ֵ����ȡ�����ݳ���
  */
int PAN312x_DataRead(void* buf, int len)
{
    HAL_StatusTypeDef status;
    
    // ʹ������ʽ���գ��ʺ�С������
    status = HAL_SPI_Receive(&pan312x_hspi, (uint8_t*)buf, len, 1000);
    
    if(status != HAL_OK) {
        return -1; // ���մ���
    }
    
    return len;
}

#define XIAOLAN 1
#if XIAOLAN
/**
  * @��飺ͬʱд��Ͷ�ȡ���ݣ�ȫ˫��SPIͨ�ţ�
  * @������tx_buf - �������ݻ�����
  *        rx_buf - �������ݻ�����
  *        len - ���ݳ���
  * @����ֵ����������ݳ��ȣ������ֵ(����)
  */
int PAN312x_DataWriteRead(const void* tx_buf, void* rx_buf, int len)
{
    HAL_StatusTypeDef status;
    
    status = HAL_SPI_TransmitReceive(&pan312x_hspi, (uint8_t*)tx_buf, (uint8_t*)rx_buf, len, 1000);
    
    if(status != HAL_OK) {
        return -1; // �������
    }
    
    return len;
}

/**
  * @��飺ʹ��DMA��ʽд������
  * @������buf - ���ݻ�����
  *        len - ���ݳ���
  * @����ֵ��0��ʾ�ɹ���������ʾ����
  */
int PAN312x_DataWrite_DMA(const void* buf, int len)
{
    HAL_StatusTypeDef status;
    
    status = HAL_SPI_Transmit_DMA(&pan312x_hspi, (uint8_t*)buf, len);
    
    if(status != HAL_OK) {
        return -1; // ����DMA����ʧ��
    }
    
    return 0;
}

/**
  * @��飺ʹ��DMA��ʽ��ȡ����
  * @������buf - ���ݻ�����
  *        len - ���ݳ���
  * @����ֵ��0��ʾ�ɹ���������ʾ����
  */
int PAN312x_DataRead_DMA(void* buf, int len)
{
    HAL_StatusTypeDef status;
    
    status = HAL_SPI_Receive_DMA(&pan312x_hspi, (uint8_t*)buf, len);
    
    if(status != HAL_OK) {
        return -1; // ����DMA����ʧ��
    }
    
    return 0;
}

/**
  * @��飺���SPI�����Ƿ����
  * @��������
  * @����ֵ������״̬��HAL_SPI_STATE_READY��ʾ��ɣ�
  */
uint32_t PAN312x_SPI_GetState(void)
{
    return HAL_SPI_GetState(&pan312x_hspi);
}

/**
  * @��飺�ȴ�SPI�������
  * @������timeout - ��ʱʱ�䣨���룩
  * @����ֵ������״̬��HAL_OK��ʾ�ɹ���
  */
HAL_StatusTypeDef PAN312x_SPI_WaitForTransfer(uint32_t timeout)
{
    uint32_t tickstart = HAL_GetTick();
    
    while(HAL_SPI_GetState(&pan312x_hspi) != HAL_SPI_STATE_READY) {
        if((HAL_GetTick() - tickstart) > timeout) {
            return HAL_TIMEOUT;
        }
    }
    
    return HAL_OK;
}
#endif

#elif PAN312x_INTERFACE == PAN312x_IF_3SPI
      
#elif PAN312x_INTERFACE == PAN312x_IF_I2C


#endif //PAN312x_INTERFACE


// Interrupt handlers
void EXTI1_IRQHandler(void)
{
    //HAL_NVIC_DisableIRQ(EXTI0_IRQn);
    HAL_GPIO_EXTI_IRQHandler(PAN312x_DIO8_PIN);
    //HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}


/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
