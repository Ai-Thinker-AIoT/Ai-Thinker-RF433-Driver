#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

#include "bsp.h"

// Flash存储区域定义（使用最后4KB作为数据存储）
#define FLASH_USER_START_ADDR  0x0800F000  // 第60页起始地址
#define FLASH_USER_END_ADDR    0x0800FFFF  // 第63页结束地址
//#define FLASH_PAGE_SIZE        1024        // 1KB页大小

// 函数声明
HAL_StatusTypeDef Flash_Init(void);
HAL_StatusTypeDef Flash_Erase_Page(uint32_t page_address);
HAL_StatusTypeDef Flash_Write(uint32_t address, uint16_t *data, uint32_t size);
void Flash_Read(uint32_t address, uint16_t *data, uint32_t size);
HAL_StatusTypeDef Flash_Write_Data(uint32_t address, void *data, uint32_t size);
void Flash_Read_Data(uint32_t address, void *data, uint32_t size);
bool Flash_Is_Empty(uint32_t address, uint32_t size);

#endif /* __BSP_FLASH_H */
