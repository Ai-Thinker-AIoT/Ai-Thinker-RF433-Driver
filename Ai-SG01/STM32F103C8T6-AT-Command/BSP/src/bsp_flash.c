#include "bsp_flash.h"

// Flash初始化
HAL_StatusTypeDef Flash_Init(void)
{
    // 检查Flash是否已解锁
    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET) {
        // 解锁Flash
        HAL_FLASH_Unlock();
    }
    
    // 清除所有错误标志
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
    
    return HAL_OK;
}

// 擦除指定页
HAL_StatusTypeDef Flash_Erase_Page(uint32_t page_address)
{
    HAL_StatusTypeDef status;
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PageError = 0;
    
    // 检查地址是否在有效范围内
    if (page_address < FLASH_USER_START_ADDR || page_address > FLASH_USER_END_ADDR) {
        return HAL_ERROR;
    }
    
    // 解锁Flash
    HAL_FLASH_Unlock();
    
    // 配置擦除参数
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = page_address;
    EraseInitStruct.NbPages = 1; // 擦除1页
    
    // 执行擦除操作
    status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
    
    // 锁定Flash
    HAL_FLASH_Lock();
    
    return status;
}

// 写入数据（以半字为单位）
HAL_StatusTypeDef Flash_Write(uint32_t address, uint16_t *data, uint32_t size)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t i;
    
    // 检查地址是否在有效范围内
    if (address < FLASH_USER_START_ADDR || address + size * 2 > FLASH_USER_END_ADDR) {
        return HAL_ERROR;
    }
    
    // 解锁Flash
    HAL_FLASH_Unlock();
    
    // 写入数据
    for (i = 0; i < size; i++) {
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, data[i]);
        if (status != HAL_OK) {
            break;
        }
        address += 2; // 地址增加2字节
    }
    
    // 锁定Flash
    HAL_FLASH_Lock();
    
    return status;
}

// 读取数据（以半字为单位）
void Flash_Read(uint32_t address, uint16_t *data, uint32_t size)
{
    uint32_t i;
    
    for (i = 0; i < size; i++) {
        data[i] = *(__IO uint16_t*)(address);
        address += 2;
    }
}

// 写入任意类型数据
HAL_StatusTypeDef Flash_Write_Data(uint32_t address, void *data, uint32_t size)
{
	#if 1
    // 确保数据大小是2的倍数（半字对齐）
    if (size % 2 != 0) {
        return HAL_ERROR;
    }
    
    return Flash_Write(address, (uint16_t*)data, size / 2);
	#else
		HAL_StatusTypeDef status = HAL_OK;
		// 确保size是2的倍数（半字对齐）
    if (size % 2 != 0) {
        // 处理错误或调整大小
        size = (size + 1) & ~1; // 向上取整到2的倍数
    }
    
    // 写入数据
    HAL_FLASH_Unlock();
    for (uint32_t i = 0; i < size; i += 2) {
        uint16_t halfword = *((uint16_t*)((uint8_t*)data + i));
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address + i, halfword);
				if (status != HAL_OK) {
            break;
        }
    }
    HAL_FLASH_Lock();
		return status;
	#endif
}

// 读取任意类型数据
void Flash_Read_Data(uint32_t address, void *data, uint32_t size)
{
    // 确保数据大小是2的倍数（半字对齐）
    if (size % 2 != 0) {
        return;
    }
    
    Flash_Read(address, (uint16_t*)data, size / 2);
}

// 检查Flash区域是否为空（全为0xFF）
bool Flash_Is_Empty(uint32_t address, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++) {
        if (*(__IO uint8_t*)(address + i) != 0xFF) {
            return false;
        }
    }
    return true;
}

