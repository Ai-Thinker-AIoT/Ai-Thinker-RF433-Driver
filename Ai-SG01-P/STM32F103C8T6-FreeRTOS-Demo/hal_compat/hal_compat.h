/**
  ******************************************************************************
  * @file    hal_compat.h
  * @brief   Minimal HAL-compatibility shim for the Ai-SG01 PAN312x firmware.
  *
  * @note    The original Ai-SG01 firmware (PAN312x_Driver.c / PAN312x_Hal.c /
  *          at_command_firmware.c) is written against ST's HAL/CubeMX layer. The
  *          FreeRTOS porting package is StdPeriph-based. Rather than rewrite the
  *          (large) RF/AT source, this header + hal_compat.c provide the small
  *          subset of HAL symbols those files actually use, implemented on top
  *          of the StdPeriph register structs already available from stm32f10x.h.
  *
  *          To let the two "GPIO_InitTypeDef / SPI_InitTypeDef" names coexist in
  *          the same translation unit, the StdPeriph typedefs are renamed while
  *          stm32f10x.h (which pulls in the StdPeriph peripheral headers) is
  *          included; afterwards the HAL-compatible definitions are introduced.
  ******************************************************************************
  */

#ifndef HAL_COMPAT_H
#define HAL_COMPAT_H

#include <stdint.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------------
   Rename the two StdPeriph typedefs that collide with our HAL names, then pull
   in the device/CMSIS headers (which transitively include the StdPeriph
   peripheral headers through stm32f10x_conf.h). After this, the redirect is
   undone and our own HAL-compatible types are defined below.
--------------------------------------------------------------------------- */
#define GPIO_InitTypeDef  HALC_STD_GPIO_InitTypeDef
#define SPI_InitTypeDef   HALC_STD_SPI_InitTypeDef
#include "stm32f10x.h"            /* device registers, CMSIS, StdPeriph conf   */
#undef GPIO_InitTypeDef
#undef SPI_InitTypeDef

#ifdef __cplusplus
extern "C" {
#endif

/* ============================== HAL status ============================== */
typedef enum
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

#define HAL_MAX_DELAY      0xFFFFFFFFU

extern uint32_t SystemCoreClock;  /* provided by system_stm32f10x.c            */

/* ============================== GPIO ================================== */
typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET   = 1
} GPIO_PinState;

/* HAL pin macros map 1:1 onto StdPeriph GPIO_Pin_x bit masks */
#define GPIO_PIN_0   ((uint16_t)0x0001)
#define GPIO_PIN_1   ((uint16_t)0x0002)
#define GPIO_PIN_2   ((uint16_t)0x0004)
#define GPIO_PIN_3   ((uint16_t)0x0008)
#define GPIO_PIN_4   ((uint16_t)0x0010)
#define GPIO_PIN_5   ((uint16_t)0x0020)
#define GPIO_PIN_6   ((uint16_t)0x0040)
#define GPIO_PIN_7   ((uint16_t)0x0080)
#define GPIO_PIN_8   ((uint16_t)0x0100)
#define GPIO_PIN_9   ((uint16_t)0x0200)
#define GPIO_PIN_10  ((uint16_t)0x0400)
#define GPIO_PIN_11  ((uint16_t)0x0800)
#define GPIO_PIN_12  ((uint16_t)0x1000)
#define GPIO_PIN_13  ((uint16_t)0x2000)
#define GPIO_PIN_14  ((uint16_t)0x4000)
#define GPIO_PIN_15  ((uint16_t)0x8000)
#define GPIO_PIN_All ((uint16_t)0xFFFF)

/* HAL GPIO mode codes (private to this shim) */
#define  GPIO_MODE_INPUT               0x00000000U
#define  GPIO_MODE_OUTPUT_PP           0x00000001U
#define  GPIO_MODE_OUTPUT_OD           0x00000002U
#define  GPIO_MODE_AF_PP               0x00000003U
#define  GPIO_MODE_AF_OD               0x00000004U
#define  GPIO_MODE_ANALOG              0x00000005U
#define  GPIO_MODE_IT_RISING           0x00010000U
#define  GPIO_MODE_IT_FALLING          0x00020000U
#define  GPIO_MODE_IT_RISING_FALLING   0x00030000U

#define  GPIO_NOPULL        0x00000000U
#define  GPIO_PULLUP        0x00000001U
#define  GPIO_PULLDOWN      0x00000002U

#define  GPIO_SPEED_FREQ_LOW        0x00000000U
#define  GPIO_SPEED_FREQ_MEDIUM     0x00000001U
#define  GPIO_SPEED_FREQ_HIGH       0x00000002U
#define  GPIO_SPEED_FREQ_VERY_HIGH  0x00000003U

typedef struct
{
  uint32_t Pin;
  uint32_t Mode;
  uint32_t Pull;
  uint32_t Speed;
  uint32_t Alternate;
} GPIO_InitTypeDef;

void     HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void     HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);
void     HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void     HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void     HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void     HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);   /* provided by application */

/* ============================ RCC clock enables ======================== */
#define __HAL_RCC_GPIOA_CLK_ENABLE()  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN
#define __HAL_RCC_GPIOB_CLK_ENABLE()  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN
#define __HAL_RCC_GPIOC_CLK_ENABLE()  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN
#define __HAL_RCC_AFIO_CLK_ENABLE()   RCC->APB2ENR |= RCC_APB2ENR_AFIOEN
#define __HAL_RCC_SPI1_CLK_ENABLE()   RCC->APB2ENR |= RCC_APB2ENR_SPI1EN
#define __HAL_RCC_SPI1_CLK_DISABLE()  RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN
#define __HAL_RCC_USART1_CLK_ENABLE() RCC->APB2ENR |= RCC_APB2ENR_USART1EN
#define __HAL_RCC_USART1_CLK_DISABLE()RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN
#define __HAL_RCC_TIM2_CLK_ENABLE()   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN
#define __HAL_RCC_TIM2_CLK_DISABLE()  RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN
#define __HAL_RCC_TIM3_CLK_ENABLE()   RCC->APB1ENR |= RCC_APB1ENR_TIM3EN
#define __HAL_RCC_DMA1_CLK_ENABLE()   RCC->AHBENR  |= RCC_AHBENR_DMA1EN

/* Public (single-underscore) RCC aliases expected by the PAN312x driver and
   the Ai-SG01 firmware. The CubeMX/HAL layer exposes these names; we bridge
   them onto the __HAL_RCC_* macros above. */
#define HAL_RCC_SPI1_CLK_ENABLE()    __HAL_RCC_SPI1_CLK_ENABLE()
#define HAL_RCC_SPI1_CLK_DISABLE()   __HAL_RCC_SPI1_CLK_DISABLE()
#define HAL_RCC_SPI1_FORCE_RESET()   do { RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST; } while (0)
#define HAL_RCC_SPI1_RELEASE_RESET() do { RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST; } while (0)
#define HAL_RCC_TIM2_CLK_ENABLE()    __HAL_RCC_TIM2_CLK_ENABLE()
#define HAL_RCC_TIM2_CLK_DISABLE()   __HAL_RCC_TIM2_CLK_DISABLE()
#define HAL_RCC_DMA1_CLK_ENABLE()    __HAL_RCC_DMA1_CLK_ENABLE()

#define __HAL_GPIO_EXTI_CLEAR_IT(__PIN__)  do { EXTI->PR = (__PIN__); } while (0)

/* ============================== NVIC ================================== */
#define NVIC_PRIORITYGROUP_4   0x00000003UL   /* 4 bits preemption, 0 subpriority (PRIGROUP=3) */

void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SystemReset(void);

/* ============================== SPI =================================== */
#define HAL_SPI_STATE_RESET       0x00U
#define HAL_SPI_STATE_READY       0x01U
#define HAL_SPI_STATE_BUSY        0x02U
#define HAL_SPI_STATE_BUSY_TX     0x03U
#define HAL_SPI_STATE_BUSY_RX     0x04U
#define HAL_SPI_STATE_BUSY_TX_RX  0x05U
#define HAL_SPI_STATE_ERROR       0x06U

#define SPI_MODE_MASTER            0x00000001U
#define SPI_DIRECTION_2LINES       0x00000000U
#define SPI_DATASIZE_8BIT          0x00000000U
#define SPI_POLARITY_LOW           0x00000000U
#define SPI_POLARITY_HIGH          0x00000001U
#define SPI_PHASE_1EDGE            0x00000000U
#define SPI_PHASE_2EDGE            0x00000001U
#define SPI_NSS_SOFT               0x00000001U
#define SPI_NSS_HARD               0x00000000U
#define SPI_BAUDRATEPRESCALER_2    0x00000000U
#define SPI_BAUDRATEPRESCALER_4    0x00000001U
#define SPI_BAUDRATEPRESCALER_8    0x00000002U
#define SPI_BAUDRATEPRESCALER_16   0x00000003U
#define SPI_BAUDRATEPRESCALER_32   0x00000004U
#define SPI_BAUDRATEPRESCALER_64   0x00000005U
#define SPI_BAUDRATEPRESCALER_128  0x00000006U
#define SPI_BAUDRATEPRESCALER_256  0x00000007U
#define SPI_FIRSTBIT_MSB           0x00000000U
#define SPI_FIRSTBIT_LSB           0x00000001U
#define SPI_TIMODE_DISABLE         0x00000000U
#define SPI_TIMODE_ENABLE          0x00000001U
#define SPI_CRCCALCULATION_DISABLE 0x00000000U
#define SPI_CRCCALCULATION_ENABLE  0x00000001U

typedef struct
{
  SPI_TypeDef *Instance;
  struct
  {
    uint32_t Mode;
    uint32_t Direction;
    uint32_t DataSize;
    uint32_t CLKPolarity;
    uint32_t CLKPhase;
    uint32_t NSS;
    uint32_t BaudRatePrescaler;
    uint32_t FirstBit;
    uint32_t TIMode;
    uint32_t CRCCalculation;
    uint32_t CRCPolynomial;
  } Init;
  void    *hdmarx;   /* kept so PAN312x_Hal.c's (unused) DMA refs compile */
  void    *hdmatx;
} SPI_HandleTypeDef;

HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
uint32_t HAL_SPI_GetState(SPI_HandleTypeDef *hspi);

/* Minimal DMA handle placeholder (only declared statically in PAN312x_Hal.c) */
typedef struct
{
  void *Instance;
} DMA_HandleTypeDef;

/* ============================== TIM =================================== */
#define TIM_COUNTERMODE_UP        0x00000000U
#define TIM_COUNTERMODE_DOWN      0x00000001U
#define TIM_CLOCKDIVISION_DIV1    0x00000000U
#define TIM_CLOCKDIVISION_DIV2    0x00000001U
#define TIM_CLOCKDIVISION_DIV4    0x00000002U
#define TIM_CLOCKSOURCE_INTERNAL  0x00000000U
#define TIM_TRGO_RESET            0x00000000U
#define TIM_MASTERSLAVEMODE_DISABLE 0x00000000U
#define TIM_MASTERSLAVEMODE_ENABLE   0x00000001U
#define TIM_IT_UPDATE             ((uint16_t)0x0001)

typedef struct
{
  uint32_t Prescaler;
  uint32_t CounterMode;
  uint32_t Period;
  uint32_t ClockDivision;
  uint32_t RepetitionCounter;
} TIM_Base_InitTypeDef;

typedef struct
{
  uint32_t ClockSource;
} TIM_ClockConfigTypeDef;

typedef struct
{
  uint32_t MasterOutputTrigger;
  uint32_t MasterSlaveMode;
} TIM_MasterConfigTypeDef;

typedef struct
{
  TIM_TypeDef *Instance;
  TIM_Base_InitTypeDef Init;
} TIM_HandleTypeDef;

HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *sClockSourceConfig);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);

/* These callbacks are provided by the application (at_command_firmware.c). */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#define __HAL_TIM_CLEAR_IT(__HANDLE__, __INTERRUPT__)  TIM_ClearITPendingBit((__HANDLE__)->Instance, (__INTERRUPT__))

/* ============================ Time / delay ============================ */
void     HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
void     HAL_IncTick(void);

/* DWT-based microsecond delay (independent of SysTick, which FreeRTOS owns) */
void DWT_Init(void);
void DWT_DelayUS(uint32_t us);

/* Optional HAL entry used by some code paths; harmless stub here. */
HAL_StatusTypeDef HAL_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_COMPAT_H */
