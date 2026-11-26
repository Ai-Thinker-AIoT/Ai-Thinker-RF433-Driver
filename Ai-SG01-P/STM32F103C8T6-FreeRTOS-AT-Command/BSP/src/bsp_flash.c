/**
  ******************************************************************************
  * @file    bsp_flash.c
  * @brief   Internal Flash read/write driver (StdPeriph) for STM32F103C8T6.
  *
  * @note    Ported from the original Ai-SG01 bsp_flash.c. The ST HAL FLASH API
  *          is replaced by the StdPeriph FLASH driver (FLASH_Unlock / ErasePage
  *          / ProgramHalfWord ...). All data is stored as 16-bit halfwords.
  *
  *          The storage region is placed at the TOP of the 128 KB Flash
  *          (pages 124..127) instead of the original 0x0800F000, because the
  *          firmware image plus FreeRTOS is far larger than 60 KB on the C8T6.
  *          See bsp_flash.h (FLASH_USER_START_ADDR / FLASH_USER_END_ADDR) and
  *          at_command_firmware.c (CONFIG_FLASH_ADDR).
  ******************************************************************************
  */
#include "bsp_flash.h"

HAL_StatusTypeDef Flash_Init(void)
{
    /* 72 MHz 下需要 2 个等待周期；启动代码通常已设置，这里再确保一次 */
    FLASH->ACR = 0x12u;   /* PRFTBE(0x10) | LATENCY_2(0x02) */

    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP |
                    FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    return HAL_OK;
}

HAL_StatusTypeDef Flash_Erase_Page(uint32_t page_address)
{
    FLASH_Status status;

    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP |
                    FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    status = FLASH_ErasePage(page_address);
    FLASH_Lock();

    return (status == FLASH_COMPLETE) ? HAL_OK : HAL_ERROR;
}

HAL_StatusTypeDef Flash_Write(uint32_t address, uint16_t *data, uint32_t size)
{
    FLASH_Status status;
    uint32_t i;

    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP |
                    FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

    for (i = 0u; i < size; i++)
    {
        status = FLASH_ProgramHalfWord(address + i * 2u, data[i]);
        if (status != FLASH_COMPLETE)
        {
            FLASH_Lock();
            return HAL_ERROR;
        }
    }

    FLASH_Lock();
    return HAL_OK;
}

void Flash_Read(uint32_t address, uint16_t *data, uint32_t size)
{
    uint32_t i;
    for (i = 0u; i < size; i++)
    {
        data[i] = *(volatile uint16_t *)(address + i * 2u);
    }
}

HAL_StatusTypeDef Flash_Write_Data(uint32_t address, void *data, uint32_t size)
{
    uint32_t halfwords = (size + 1u) / 2u;   /* 按字节计 -> 半字计 */
    return Flash_Write(address, (uint16_t *)data, halfwords);
}

void Flash_Read_Data(uint32_t address, void *data, uint32_t size)
{
    uint32_t halfwords = (size + 1u) / 2u;
    Flash_Read(address, (uint16_t *)data, halfwords);
}

bool Flash_Is_Empty(uint32_t address, uint32_t size)
{
    uint32_t halfwords = (size + 1u) / 2u;
    uint32_t i;
    for (i = 0u; i < halfwords; i++)
    {
        if (*(volatile uint16_t *)(address + i * 2u) != 0xFFFFu)
        {
            return false;
        }
    }
    return true;
}

/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
