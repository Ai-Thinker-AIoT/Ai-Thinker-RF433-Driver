#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

#include "bsp.h"

// Flash存储区域（使用最后4KB作为数据存储区，避免与固件镜像重叠）
// 注意：C8T6 仅有 128KB Flash，固件+FreeRTOS 镜像远大于原来的 60KB 边界，
// 故将数据区移到 Flash 顶部（第124~127页）。CONFIG 放在最后一页。
#define FLASH_USER_START_ADDR  0x0801F000  // 第124页起始地址
#define FLASH_USER_END_ADDR    0x0801FFFF  // 第127页结束地址
//#define FLASH_PAGE_SIZE        1024        // 1KB页大小

// 对外函数
HAL_StatusTypeDef Flash_Init(void);
HAL_StatusTypeDef Flash_Erase_Page(uint32_t page_address);
HAL_StatusTypeDef Flash_Write(uint32_t address, uint16_t *data, uint32_t size);
void Flash_Read(uint32_t address, uint16_t *data, uint32_t size);
HAL_StatusTypeDef Flash_Write_Data(uint32_t address, void *data, uint32_t size);
void Flash_Read_Data(uint32_t address, void *data, uint32_t size);
bool Flash_Is_Empty(uint32_t address, uint32_t size);

#endif /* __BSP_FLASH_H */
