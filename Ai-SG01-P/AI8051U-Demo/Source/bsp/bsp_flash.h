/* ============================================================================
 * bsp_flash.h — AI8051U-34K64 数据存储器（替代 STM32 内部 Flash）
 *   使用芯片内置 4KB EEPROM（IAP 方式访问），扇区 512 字节。
 *   固件传入的 STM32 风格地址（如 0x0800FC00）经 &0x0FFF 映射到 EEPROM 偏移，
 *   无需改动固件侧地址常量。
 * ========================================================================== */
#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

#include "bsp.h"

/* 等效 STM32 Flash 用户区起始/结束（仅占位，实际映射到 EEPROM 偏移） */
#define FLASH_USER_START_ADDR  0x0800F000
#define FLASH_USER_END_ADDR    0x0800FFFF

HAL_StatusTypeDef Flash_Init(void);
HAL_StatusTypeDef Flash_Erase_Page(uint32_t page_address);
HAL_StatusTypeDef Flash_Write(uint32_t address, uint16_t *dat, uint32_t size);
void Flash_Read(uint32_t address, uint16_t *dat, uint32_t size);
HAL_StatusTypeDef Flash_Write_Data(uint32_t address, void *dat, uint32_t size);
void Flash_Read_Data(uint32_t address, void *dat, uint32_t size);
bool Flash_Is_Empty(uint32_t address, uint32_t size);

#endif /* __BSP_FLASH_H */
