/**
  ******************************************************************************
  * @file    hal_compat.c
  * @brief   Implementation of the minimal HAL-compatibility shim.
  *
  * @see     hal_compat.h for the design rationale. GPIO and SPI are programmed
  *          via registers; TIM / USART / RCC use the StdPeriph helpers that do
  *          not clash with the HAL type names.
  ******************************************************************************
  */

#include "hal_compat.h"

/* DWT 周期计数器延时支持 ---------------------------------------------------
 * 本工程 Start\core_cm3.h 定义了 CoreDebug 但未定义 DWT / DWT_Type /
 * DWT_CTRL_CYCCNTENA_Msk（较旧 CMSIS）。此处按 ARM 内存映射补齐，并用 #ifndef
 * 守卫避免与未来升级的 CMSIS 冲突。CoreDebug 已由 hal_compat.h -> stm32f10x.h 提供。 */
#ifndef DWT_BASE
#define DWT_BASE                0xE0001000UL
#define DWT_CTRL_CYCCNTENA_Msk  (1UL << 0)
typedef struct {
    volatile uint32_t CTRL;     /* 0x00 Control Register */
    volatile uint32_t CYCCNT;   /* 0x04 Cycle Count Register */
} DWT_Type;
#define DWT                     ((DWT_Type *)DWT_BASE)
#endif

/* ===========================================================================
   GPIO
=========================================================================== */

static void gpio_config_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t cnf, uint8_t mode)
{
  uint8_t  shift = (pin & 7u) * 4u;
  __IO uint32_t *cr = (pin < 8u) ? &GPIOx->CRL : &GPIOx->CRH;
  uint32_t val = *cr;
  val &= ~(0xFu << shift);
  val |= (((uint32_t)cnf << 2) | (uint32_t)mode) << shift;
  *cr = val;
}

void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t pins = GPIO_Init->Pin;
  uint8_t  cnf, mode;

  if (GPIO_Init->Mode & 0x00030000U)            /* interrupt input */
  {
    mode = 0; cnf = 2;                          /* input, pull-up/down */
  }
  else if (GPIO_Init->Mode == GPIO_MODE_ANALOG)
  {
    mode = 0; cnf = 0;
  }
  else if (GPIO_Init->Mode == GPIO_MODE_INPUT)
  {
    mode = 0; cnf = (GPIO_Init->Pull != GPIO_NOPULL) ? 2 : 1;
  }
  else                                          /* output / alternate */
  {
    mode = (GPIO_Init->Speed == GPIO_SPEED_FREQ_LOW) ? 1 : 3;  /* 10 MHz or 50 MHz */
    if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP)       cnf = 0;
    else if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD)  cnf = 1;
    else if (GPIO_Init->Mode == GPIO_MODE_AF_PP)      cnf = 2;
    else if (GPIO_Init->Mode == GPIO_MODE_AF_OD)      cnf = 3;
    else { cnf = 0; mode = 3; }
  }

  for (uint8_t i = 0u; i < 16u; i++)
  {
    if ((pins & ((uint32_t)1u << i)) == 0u)
      continue;

    gpio_config_pin(GPIOx, i, cnf, mode);

    /* Set pull direction through ODR for pull-up / pull-down inputs and IT pins */
    if ((mode == 0) && (cnf == 2))
    {
      if (GPIO_Init->Pull == GPIO_PULLUP)
        GPIOx->ODR |= ((uint32_t)1u << i);
      else if (GPIO_Init->Pull == GPIO_PULLDOWN)
        GPIOx->ODR &= ~((uint32_t)1u << i);
      else
        GPIOx->ODR &= ~((uint32_t)1u << i);     /* IT pins default to pull-down */
    }

    /* Interrupt configuration */
    if (GPIO_Init->Mode & 0x00030000U)
    {
      __HAL_RCC_AFIO_CLK_ENABLE();
      uint8_t port = (GPIOx == GPIOA) ? 0 : (GPIOx == GPIOB) ? 1 : (GPIOx == GPIOC) ? 2 : 0;
      uint8_t idx  = i / 4u;
      uint8_t off  = (i % 4u) * 4u;
      AFIO->EXTICR[idx] &= ~(0xFu << off);
      AFIO->EXTICR[idx] |= ((uint32_t)port << off);

      EXTI->IMR |= ((uint32_t)1u << i);
      if (GPIO_Init->Mode & 0x00010000U)        /* rising */
        EXTI->RTSR |= ((uint32_t)1u << i);
      else if (GPIO_Init->Mode & 0x00020000U)   /* falling */
        EXTI->FTSR |= ((uint32_t)1u << i);
      else                                      /* both */
      {
        EXTI->RTSR |= ((uint32_t)1u << i);
        EXTI->FTSR |= ((uint32_t)1u << i);
      }
      EXTI->PR = ((uint32_t)1u << i);
    }
  }
}

void HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  for (uint8_t i = 0u; i < 16u; i++)
  {
    if ((GPIO_Pin & ((uint32_t)1u << i)) == 0u)
      continue;
    gpio_config_pin(GPIOx, i, 1, 0);            /* floating input */
  }
}

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  if (PinState == GPIO_PIN_SET)
    GPIOx->BSRR = GPIO_Pin;
  else
    GPIOx->BRR = GPIO_Pin;
}

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  return ((GPIOx->IDR & GPIO_Pin) != 0u) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  GPIOx->ODR ^= GPIO_Pin;
}

void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
  if ((EXTI->PR & GPIO_Pin) != 0u)
  {
    EXTI->PR = GPIO_Pin;
    HAL_GPIO_EXTI_Callback(GPIO_Pin);
  }
}

/* ===========================================================================
   NVIC
=========================================================================== */

void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
  (void)SubPriority;
  NVIC_SetPriority((IRQn_Type)IRQn, (uint32_t)PreemptPriority);
}

void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
  NVIC_EnableIRQ((IRQn_Type)IRQn);
}

void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
  NVIC_DisableIRQ((IRQn_Type)IRQn);
}

void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  NVIC_SetPriorityGrouping((uint32_t)PriorityGroup);
}

void HAL_NVIC_SystemReset(void)
{
  NVIC_SystemReset();
}

/* ===========================================================================
   SPI  (register programmed; the StdPeriph SPI_Init typedef conflicts)
=========================================================================== */

HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
  SPI_TypeDef *SPIx = hspi->Instance;

  uint16_t cr1 = 0;
  cr1 |= SPI_CR1_MSTR;                         /* master                       */
  cr1 |= SPI_CR1_SSM | SPI_CR1_SSI;             /* software NSS (NSS = SOFT)    */
  if (hspi->Init.CLKPolarity != 0u) cr1 |= SPI_CR1_CPOL;
  if (hspi->Init.CLKPhase    != 0u) cr1 |= SPI_CR1_CPHA;
  cr1 |= (uint16_t)((hspi->Init.BaudRatePrescaler & 7u) << 3);
  if (hspi->Init.FirstBit == SPI_FIRSTBIT_LSB) cr1 |= SPI_CR1_LSBFIRST;

  SPIx->CR1 = cr1;
  SPIx->CR2 = 0u;
  SPIx->CR1 |= SPI_CR1_SPE;                     /* enable peripheral           */

  return HAL_OK;
}

static inline void spi_wait_tx(SPI_TypeDef *s) { while ((s->SR & SPI_SR_TXE) == 0u); }
static inline void spi_wait_rx(SPI_TypeDef *s) { while ((s->SR & SPI_SR_RXNE) == 0u); }

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  SPI_TypeDef *SPIx = hspi->Instance;
  (void)Timeout;
  for (uint16_t i = 0u; i < Size; i++)
  {
    spi_wait_tx(SPIx);
    SPIx->DR = pData[i];
    spi_wait_rx(SPIx);
    (void)SPIx->DR;                             /* flush RX to avoid overrun   */
  }
  while ((SPIx->SR & SPI_SR_BSY) != 0u);
  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  SPI_TypeDef *SPIx = hspi->Instance;
  (void)Timeout;
  for (uint16_t i = 0u; i < Size; i++)
  {
    spi_wait_tx(SPIx);
    SPIx->DR = 0xFFu;                            /* dummy write                 */
    spi_wait_rx(SPIx);
    pData[i] = (uint8_t)SPIx->DR;
  }
  while ((SPIx->SR & SPI_SR_BSY) != 0u);
  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  SPI_TypeDef *SPIx = hspi->Instance;
  (void)Timeout;
  for (uint16_t i = 0u; i < Size; i++)
  {
    spi_wait_tx(SPIx);
    SPIx->DR = pTxData[i];
    spi_wait_rx(SPIx);
    pRxData[i] = (uint8_t)SPIx->DR;
  }
  while ((SPIx->SR & SPI_SR_BSY) != 0u);
  return HAL_OK;
}

uint32_t HAL_SPI_GetState(SPI_HandleTypeDef *hspi)
{
  (void)hspi;
  return HAL_SPI_STATE_READY;
}

/* ---------------------------------------------------------------------------
   The PAN312x HAL layer compiles PAN312x_DataWrite_DMA / PAN312x_DataRead_DMA,
   but this port does not drive the STM32 DMA controller. Mapping the DMA
   variants onto the polling API keeps the driver self-consistent and avoids
   pulling in the DMA peripheral (and the void* hdmarx/hdmatx handles).
--------------------------------------------------------------------------- */
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  return HAL_SPI_Transmit(hspi, pData, Size, 0u);
}

HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  return HAL_SPI_Receive(hspi, pData, Size, 0u);
}

/* ===========================================================================
   TIM  (StdPeriph TIM_TimeBaseInit is type-safe and does not clash)
=========================================================================== */

HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)
{
  HAL_TIM_Base_MspInit(htim);                   /* enables clock + NVIC        */

  TIM_TimeBaseInitTypeDef tb;
  tb.TIM_Prescaler         = (uint16_t)htim->Init.Prescaler;
  tb.TIM_CounterMode       = (htim->Init.CounterMode == TIM_COUNTERMODE_DOWN)
                                 ? TIM_CounterMode_Down : TIM_CounterMode_Up;
  tb.TIM_Period            = htim->Init.Period;
  tb.TIM_ClockDivision     = (htim->Init.ClockDivision == TIM_CLOCKDIVISION_DIV2) ? TIM_CKD_DIV2
                             : (htim->Init.ClockDivision == TIM_CLOCKDIVISION_DIV4) ? TIM_CKD_DIV4
                             : TIM_CKD_DIV1;
  tb.TIM_RepetitionCounter = 0u;
  TIM_TimeBaseInit(htim->Instance, &tb);
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *sClockSourceConfig)
{
  (void)htim; (void)sClockSourceConfig;
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef *sMasterConfig)
{
  (void)htim; (void)sMasterConfig;
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim)
{
  TIM_ITConfig(htim->Instance, TIM_IT_Update, ENABLE);
  TIM_Cmd(htim->Instance, ENABLE);
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim)
{
  TIM_ITConfig(htim->Instance, TIM_IT_Update, DISABLE);
  TIM_Cmd(htim->Instance, DISABLE);
  return HAL_OK;
}

void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)
{
  if (TIM_GetITStatus(htim->Instance, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(htim->Instance, TIM_IT_Update);
    HAL_TIM_PeriodElapsedCallback(htim);
  }
}

/* ===========================================================================
   Time / delay
=========================================================================== */

static volatile uint32_t HAL_uwTick = 0u;

uint32_t HAL_GetTick(void)
{
  return HAL_uwTick;
}

void HAL_IncTick(void)
{
  HAL_uwTick++;
}

void DWT_Init(void)
{
  if ((CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk) == 0u)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0u;
}

void DWT_DelayUS(uint32_t us)
{
  uint32_t cycles = us * (SystemCoreClock / 1000000u);
  uint32_t start  = DWT->CYCCNT;
  while ((DWT->CYCCNT - start) < cycles);
}

void HAL_Delay(uint32_t Delay)
{
  DWT_DelayUS(Delay * 1000u);
}

HAL_StatusTypeDef HAL_Init(void)
{
  return HAL_OK;
}
