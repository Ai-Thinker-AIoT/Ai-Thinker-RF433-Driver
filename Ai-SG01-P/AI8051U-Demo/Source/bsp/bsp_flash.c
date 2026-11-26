/* ============================================================================
 * bsp_flash.c — AI8051U-34K64 EEPROM(IAP) 读写实现
 *   命令码：1=读 2=写(编程) 3=擦除扇区
 *   触发：IAP_TRIG 依次写 0x5A、0xA5（CPU 在 IAP 期间自动停顿，无需轮询完成）
 *   地址：EEPROM 4KB，扇区 512B；固件地址 &0x0FFF 取偏移。
 * ========================================================================== */
#include "bsp_flash.h"

/* IAP 命令 / 控制位 */
#define IAP_EN          0x80    /* IAP_CONTR 使能位 */
#define IAP_CMD_READ    0x01
#define IAP_CMD_PROG    0x02
#define IAP_CMD_ERASE   0x03

#define EEPROM_MASK     0x0FFFU /* EEPROM 偏移取低 12 位（4KB） */
#define SECTOR_SIZE     0x0200U /* 512 字节/扇区 */

/* 开启 IAP 并设置等待时序（按主频 MHz 配置 IAP_TPS） */
static void IAP_Enable(void)
{
    EAXSFR();                       /* 确保可访问扩展 SFR（IAP_TPS 在扩展区） */
    IAP_TPS   = (uint8_t)(AI8051_SYS_CLK_HZ / 1000000UL);
    IAP_CONTR |= IAP_EN;
}

static void IAP_Disable(void)
{
    IAP_CONTR &= ~IAP_EN;
}

/* 固件地址 -> EEPROM 16 位偏移 */
static uint16_t eep_of(uint32_t address)
{
    return (uint16_t)(address & EEPROM_MASK);
}

HAL_StatusTypeDef Flash_Init(void)
{
    /* 实际使能在每次操作中完成；此处仅占位返回 OK */
    return HAL_OK;
}

HAL_StatusTypeDef Flash_Erase_Page(uint32_t page_address)
{
    uint16_t sec = eep_of(page_address) & (uint16_t)(~(SECTOR_SIZE - 1U));

    IAP_Enable();
    IAP_ADDRH = (uint8_t)(sec >> 8);
    IAP_ADDRL = (uint8_t)(sec & 0xFF);
    IAP_CMD   = IAP_CMD_ERASE;
    IAP_TRIG  = 0x5A;
    IAP_TRIG  = 0xA5;
    IAP_Disable();

    return HAL_OK;
}

HAL_StatusTypeDef Flash_Write(uint32_t address, uint16_t *dat, uint32_t size)
{
    uint16_t eep = eep_of(address);
    uint32_t i;

    IAP_Enable();
    for (i = 0; i < size; i++)
    {
        uint16_t w = dat[i];

        /* 低字节 */
        IAP_ADDRH = (uint8_t)(eep >> 8);
        IAP_ADDRL = (uint8_t)(eep & 0xFF);
        IAP_DATA  = (uint8_t)(w & 0xFF);
        IAP_CMD   = IAP_CMD_PROG;
        IAP_TRIG  = 0x5A;
        IAP_TRIG  = 0xA5;
        eep++;

        /* 高字节 */
        IAP_ADDRH = (uint8_t)(eep >> 8);
        IAP_ADDRL = (uint8_t)(eep & 0xFF);
        IAP_DATA  = (uint8_t)(w >> 8);
        IAP_CMD   = IAP_CMD_PROG;
        IAP_TRIG  = 0x5A;
        IAP_TRIG  = 0xA5;
        eep++;
    }
    IAP_Disable();

    return HAL_OK;
}

void Flash_Read(uint32_t address, uint16_t *dat, uint32_t size)
{
    uint16_t eep = eep_of(address);
    uint32_t i;

    IAP_Enable();
    for (i = 0; i < size; i++)
    {
        IAP_ADDRH = (uint8_t)(eep >> 8);
        IAP_ADDRL = (uint8_t)(eep & 0xFF);
        IAP_CMD   = IAP_CMD_READ;
        IAP_TRIG  = 0x5A;
        IAP_TRIG  = 0xA5;
        dat[i]   = IAP_DATA;
        eep++;

        IAP_ADDRH = (uint8_t)(eep >> 8);
        IAP_ADDRL = (uint8_t)(eep & 0xFF);
        IAP_CMD   = IAP_CMD_READ;
        IAP_TRIG  = 0x5A;
        IAP_TRIG  = 0xA5;
        dat[i]  |= (uint16_t)((uint16_t)IAP_DATA << 8);
        eep++;
    }
    IAP_Disable();
}

HAL_StatusTypeDef Flash_Write_Data(uint32_t address, void *dat, uint32_t size)
{
    if (size % 2 != 0)
        return HAL_ERROR;

    return Flash_Write(address, (uint16_t *)dat, size / 2);
}

void Flash_Read_Data(uint32_t address, void *dat, uint32_t size)
{
    if (size % 2 != 0)
        return;

    Flash_Read(address, (uint16_t *)dat, size / 2);
}

bool Flash_Is_Empty(uint32_t address, uint32_t size)
{
    uint16_t eep = eep_of(address);
    uint32_t i;
    uint8_t  b;

    IAP_Enable();
    for (i = 0; i < size; i++)
    {
        IAP_ADDRH = (uint8_t)(eep >> 8);
        IAP_ADDRL = (uint8_t)(eep & 0xFF);
        IAP_CMD   = IAP_CMD_READ;
        IAP_TRIG  = 0x5A;
        IAP_TRIG  = 0xA5;
        b = IAP_DATA;
        if (b != 0xFF)
        {
            IAP_Disable();
            return false;
        }
        eep++;
    }
    IAP_Disable();

    return true;
}
