/**
  ******************************************************************************
  * 文件名 ：   PAN312x_Driver.c
  * 作者   ：   PAN312x RF Team
  * 版本   ：   V1.0.0
  * 时间   ：   
  * 文件描述：
*******************************************************************************/


//#include "PAN312x_RFregsetting.h"
#include "bsp.h"
/*
  注意，本文件的函数实现了从RF的驱动与MCU的兼容

*/
#define DEV_FIFO_SIZE 		128

uint8_t RF_Version;
uint16_t Receive_PC;

volatile uint8_t vcol_cal_code;
volatile uint8_t tp_auto_code;
volatile uint8_t rc_code;

uint8_t TcxoControlByGpio = 0;
//-------------------------------------------------//
//PAN312x power
//--------------------------------------------------------------//
#define PAN31XX_LDO_POWER_GET_VDD_PA_TRIM(v)        (((v) >> 11) & 0x1f)
#define PAN31XX_LDO_POWER_GET_PA_2ND_RAMP(v)        (((v) >> 5) & 0x3f)
#define PAN31XX_LDO_POWER_GET_PA_BIAS_TRIM(v)       (((v) >> 1) & 0xf)
#define PAN31XX_LDO_POWER_GET_LP_EN(v)              ((v) & 1)
#define PAN31XX_LDO_POWER_MAKE(VDD_PA_TRIM, PA_2ND_RAMP, PA_BIAS_TRIM, lp_en) \
    (((VDD_PA_TRIM) << 11) | ((PA_2ND_RAMP) << 5) | ((PA_BIAS_TRIM) << 1) | (lp_en))
    
    
const uint16_t pan31xx_ldo_power_0603_420_445mhz[41] = {
    PAN31XX_LDO_POWER_MAKE(0x00, 0x0e, 0x0, 1),         //-20dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x11, 0x0, 1),         //-19dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x05, 0x1, 1),         //-18dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x06, 0x1, 1),         //-17dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x17, 0x0, 1),         //-16dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x01, 0x3, 1),         //-15dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0x5, 1),         //-14dBm
    PAN31XX_LDO_POWER_MAKE(0x0e, 0x00, 0x5, 1),         //-13dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x00, 0x8, 1),         //-12dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x00, 0x9, 1),         //-11dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x00, 0xc, 1),         //-10dBm
    PAN31XX_LDO_POWER_MAKE(0x08, 0x00, 0xc, 1),         //-9dBm
    PAN31XX_LDO_POWER_MAKE(0x10, 0x00, 0xc, 1),         //-8dBm
    PAN31XX_LDO_POWER_MAKE(0x19, 0x00, 0xc, 1),         //-7dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xe, 1),         //-6dBm
    PAN31XX_LDO_POWER_MAKE(0x02, 0x01, 0xc, 1),         //-5dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x01, 0xc, 1),         //-4dBm
    PAN31XX_LDO_POWER_MAKE(0x0d, 0x01, 0xc, 1),         //-3dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x02, 0xc, 1),         //-2dBm
    PAN31XX_LDO_POWER_MAKE(0x08, 0x02, 0xc, 1),         //-1dBm
    PAN31XX_LDO_POWER_MAKE(0x0f, 0x02, 0xc, 1),         //0dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x02, 0xc, 1),         //1dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x02, 0xc, 1),         //2dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x03, 0xc, 1),         //3dBm
    PAN31XX_LDO_POWER_MAKE(0x15, 0x04, 0xc, 1),         //4dBm
    PAN31XX_LDO_POWER_MAKE(0x15, 0x05, 0xc, 1),         //5dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x06, 0xc, 1),         //6dBm
    PAN31XX_LDO_POWER_MAKE(0x19, 0x07, 0xc, 1),         //7dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x0a, 0xc, 1),         //8dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x0a, 0xc, 1),         //9dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x0d, 0xc, 1),         //10dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x12, 0xc, 1),         //11dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x1c, 0xc, 1),         //12dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x3f, 0xc, 1),         //13dBm
    PAN31XX_LDO_POWER_MAKE(0x02, 0x3c, 0xc, 0),         //14dBm
    PAN31XX_LDO_POWER_MAKE(0x05, 0x3c, 0xc, 0),         //15dBm
    PAN31XX_LDO_POWER_MAKE(0x09, 0x3c, 0xc, 0),         //16dBm
    PAN31XX_LDO_POWER_MAKE(0x0d, 0x3c, 0xc, 0),         //17dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x3c, 0xc, 0),         //18dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x3c, 0xc, 0),         //19dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x3c, 0xc, 0)          //20dBm
};                                                      

const uint16_t pan31xx_ldo_power_0603_470_510mhz[41] = {
    PAN31XX_LDO_POWER_MAKE(0x00, 0x0e, 0x0, 1),         //-20dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x11, 0x0, 1),         //-19dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x05, 0x1, 1),         //-18dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x06, 0x1, 1),         //-17dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x17, 0x0, 1),         //-16dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x01, 0x3, 1),         //-15dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0x5, 1),         //-14dBm
    PAN31XX_LDO_POWER_MAKE(0x0e, 0x00, 0x5, 1),         //-13dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x00, 0x8, 1),         //-12dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x00, 0x9, 1),         //-11dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x00, 0xc, 1),         //-10dBm
    PAN31XX_LDO_POWER_MAKE(0x08, 0x00, 0xc, 1),         //-9dBm
    PAN31XX_LDO_POWER_MAKE(0x10, 0x00, 0xc, 1),         //-8dBm
    PAN31XX_LDO_POWER_MAKE(0x19, 0x00, 0xc, 1),         //-7dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xe, 1),         //-6dBm
    PAN31XX_LDO_POWER_MAKE(0x02, 0x01, 0xc, 1),         //-5dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x01, 0xc, 1),         //-4dBm
    PAN31XX_LDO_POWER_MAKE(0x0d, 0x01, 0xc, 1),         //-3dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x02, 0xc, 1),         //-2dBm
    PAN31XX_LDO_POWER_MAKE(0x08, 0x02, 0xc, 1),         //-1dBm
    PAN31XX_LDO_POWER_MAKE(0x0f, 0x02, 0xc, 1),         //0dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x02, 0xc, 1),         //1dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x02, 0xc, 1),         //2dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x03, 0xc, 1),         //3dBm
    PAN31XX_LDO_POWER_MAKE(0x15, 0x04, 0xc, 1),         //4dBm
    PAN31XX_LDO_POWER_MAKE(0x15, 0x05, 0xc, 1),         //5dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x06, 0xc, 1),         //6dBm
    PAN31XX_LDO_POWER_MAKE(0x19, 0x07, 0xc, 1),         //7dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x0a, 0xc, 1),         //8dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x0a, 0xc, 1),         //9dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x0d, 0xc, 1),         //10dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x12, 0xc, 1),         //11dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x1c, 0xc, 1),         //12dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x3f, 0xc, 1),         //13dBm
    PAN31XX_LDO_POWER_MAKE(0x02, 0x3c, 0xc, 0),         //14dBm
    PAN31XX_LDO_POWER_MAKE(0x05, 0x3c, 0xc, 0),         //15dBm
    PAN31XX_LDO_POWER_MAKE(0x09, 0x3c, 0xc, 0),         //16dBm
    PAN31XX_LDO_POWER_MAKE(0x0d, 0x3c, 0xc, 0),         //17dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x3c, 0xc, 0),         //18dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x3c, 0xc, 0),         //19dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x3c, 0xc, 0)          //20dBm
};

const uint16_t pan31xx_ldo_power_0603_860_870mhz[41] = {
    PAN31XX_LDO_POWER_MAKE(0x00, 0x0e, 0x0, 1),         //-20dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x11, 0x0, 1),         //-19dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x05, 0x1, 1),         //-18dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x06, 0x1, 1),         //-17dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x17, 0x0, 1),         //-16dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0x5, 1),         //-15dBm
    PAN31XX_LDO_POWER_MAKE(0x0e, 0x00, 0x5, 1),         //-14dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x00, 0x8, 1),         //-13dBm
    PAN31XX_LDO_POWER_MAKE(0x05, 0x00, 0x9, 1),         //-12dBm
    PAN31XX_LDO_POWER_MAKE(0x05, 0x00, 0xc, 1),         //-11dBm
    PAN31XX_LDO_POWER_MAKE(0x0b, 0x00, 0xc, 1),         //-10dBm
    PAN31XX_LDO_POWER_MAKE(0x13, 0x00, 0xc, 1),         //-9dBm
    PAN31XX_LDO_POWER_MAKE(0x1c, 0x00, 0xc, 1),         //-8dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xe, 1),         //-7dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x01, 0xc, 1),         //-6dBm
    PAN31XX_LDO_POWER_MAKE(0x0b, 0x01, 0xc, 1),         //-5dBm
    PAN31XX_LDO_POWER_MAKE(0x10, 0x01, 0xc, 1),         //-4dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x02, 0xc, 1),         //-3dBm
    PAN31XX_LDO_POWER_MAKE(0x0b, 0x02, 0xc, 1),         //-2dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x02, 0xc, 1),         //-1dBm
    PAN31XX_LDO_POWER_MAKE(0x19, 0x02, 0xc, 1),         //0dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x02, 0xf, 1),         //1dBm
    PAN31XX_LDO_POWER_MAKE(0x1b, 0x03, 0xc, 1),         //2dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x04, 0xc, 1),         //3dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x05, 0xc, 1),         //4dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x06, 0xc, 1),         //5dBm
    PAN31XX_LDO_POWER_MAKE(0x1c, 0x07, 0xc, 1),         //6dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x0a, 0xc, 1),         //7dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x2c, 0xc, 1),         //8dBm
    PAN31XX_LDO_POWER_MAKE(0x0d, 0x2c, 0xc, 1),         //9dBm
    PAN31XX_LDO_POWER_MAKE(0x13, 0x2c, 0xc, 1),         //10dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x2c, 0xc, 1),         //11dBm
    PAN31XX_LDO_POWER_MAKE(0x1c, 0x2c, 0xc, 1),         //12dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x3f, 0xc, 1),         //13dBm
    PAN31XX_LDO_POWER_MAKE(0x02, 0x3c, 0xc, 0),         //14dBm
    PAN31XX_LDO_POWER_MAKE(0x05, 0x3c, 0xc, 0),         //15dBm
    PAN31XX_LDO_POWER_MAKE(0x09, 0x3c, 0xc, 0),         //16dBm
    PAN31XX_LDO_POWER_MAKE(0x0d, 0x3c, 0xc, 0),         //17dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x3c, 0xc, 0),         //18dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x3c, 0xc, 0),         //19dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x3c, 0xc, 0)          //20dBm    
};


const uint16_t pan31xx_ldo_power_0603_902_928mhz[41] = {
    PAN31XX_LDO_POWER_MAKE(0x00, 0x06, 0x1, 1),         //-20dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x07, 0x1, 1),         //-19dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x08, 0x1, 1),         //-18dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x09, 0x1, 1),         //-17dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x0a, 0x1, 1),         //-16dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x04, 0x2, 1),         //-15dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x05, 0x2, 1),         //-14dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x00, 0x8, 1),         //-13dBm
    PAN31XX_LDO_POWER_MAKE(0x08, 0x00, 0x9, 1),         //-12dBm
    PAN31XX_LDO_POWER_MAKE(0x05, 0x00, 0xc, 1),         //-11dBm
    PAN31XX_LDO_POWER_MAKE(0x0b, 0x00, 0xc, 1),         //-10dBm
    PAN31XX_LDO_POWER_MAKE(0x13, 0x00, 0xc, 1),         //-9dBm
    PAN31XX_LDO_POWER_MAKE(0x1c, 0x00, 0xc, 1),         //-8dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xe, 1),         //-7dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x01, 0xc, 1),         //-6dBm
    PAN31XX_LDO_POWER_MAKE(0x0b, 0x01, 0xc, 1),         //-5dBm
    PAN31XX_LDO_POWER_MAKE(0x10, 0x01, 0xc, 1),         //-4dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x02, 0xc, 1),         //-3dBm
    PAN31XX_LDO_POWER_MAKE(0x0b, 0x02, 0xc, 1),         //-2dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x02, 0xc, 1),         //-1dBm
    PAN31XX_LDO_POWER_MAKE(0x19, 0x02, 0xc, 1),         //0dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x02, 0xf, 1),         //1dBm
    PAN31XX_LDO_POWER_MAKE(0x1b, 0x03, 0xc, 1),         //2dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x04, 0xc, 1),         //3dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x05, 0xc, 1),         //4dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x06, 0xc, 1),         //5dBm
    PAN31XX_LDO_POWER_MAKE(0x1c, 0x07, 0xc, 1),         //6dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x0a, 0xc, 1),         //7dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x2c, 0xc, 1),         //8dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x2c, 0xc, 1),         //9dBm
    PAN31XX_LDO_POWER_MAKE(0x10, 0x2c, 0xc, 1),         //10dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x2c, 0xc, 1),         //11dBm
    PAN31XX_LDO_POWER_MAKE(0x1b, 0x2c, 0xc, 1),         //12dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x3f, 0xc, 1),         //13dBm
    PAN31XX_LDO_POWER_MAKE(0x02, 0x3c, 0xc, 0),         //14dBm
    PAN31XX_LDO_POWER_MAKE(0x05, 0x3c, 0xc, 0),         //15dBm
    PAN31XX_LDO_POWER_MAKE(0x09, 0x3c, 0xc, 0),         //16dBm
    PAN31XX_LDO_POWER_MAKE(0x0d, 0x3c, 0xc, 0),         //17dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x3c, 0xc, 0),         //18dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x3c, 0xc, 0),         //19dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x3c, 0xc, 0)          //20dBm
}; 

const uint16_t pan31xx_ldo_power_0402_420_445mhz[41] = {
    PAN31XX_LDO_POWER_MAKE(0x00, 0x05, 0x1, 1),         //-20dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x13, 0x0, 1),         //-19dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x06, 0x1, 1),         //-18dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x07, 0x1, 1),         //-17dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x08, 0x1, 1),         //-16dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0x8, 1),         //-15dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0xb, 1),         //-14dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x00, 0xc, 1),         //-13dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x00, 0xc, 1),         //-12dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x00, 0xc, 1),         //-11dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xc, 1),         //-10dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xf, 1),         //-9dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x01, 0xc, 1),         //-8dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x01, 0xc, 1),         //-7dBm
    PAN31XX_LDO_POWER_MAKE(0x0e, 0x01, 0xc, 1),         //-6dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x02, 0xc, 1),         //-5dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x02, 0xc, 1),         //-4dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x03, 0xc, 1),         //-3dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x03, 0xc, 1),         //-2dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x04, 0xc, 1),         //-1dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x05, 0xc, 1),         //0dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x07, 0xc, 1),         //1dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x07, 0xc, 1),         //2dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x07, 0xc, 1),         //3dBm
    PAN31XX_LDO_POWER_MAKE(0x11, 0x07, 0xc, 1),         //4dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x07, 0xc, 1),         //5dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x07, 0xc, 1),         //6dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x09, 0xc, 1),         //7dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x0b, 0xc, 1),         //8dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x0d, 0xc, 1),         //9dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x11, 0xc, 1),         //10dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x16, 0xc, 1),         //11dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x1f, 0xc, 1),         //12dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x30, 0xc, 1),         //13dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x0f, 0xc, 0),         //14dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x12, 0xc, 0),         //15dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x15, 0xc, 0),         //16dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x1a, 0xc, 0),         //17dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x20, 0xc, 0),         //18dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x2b, 0xc, 0),         //19dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x3f, 0xc, 0)          //20dBm
};

const uint16_t pan31xx_ldo_power_0402_470_510mhz[41] = {
    PAN31XX_LDO_POWER_MAKE(0x00, 0x05, 0x1, 1),         //-20dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x13, 0x0, 1),         //-19dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x06, 0x1, 1),         //-18dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x07, 0x1, 1),         //-17dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x08, 0x1, 1),         //-16dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0x8, 1),         //-15dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0xb, 1),         //-14dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x00, 0xc, 1),         //-13dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x00, 0xc, 1),         //-12dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x00, 0xc, 1),         //-11dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xc, 1),         //-10dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xf, 1),         //-9dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x01, 0xc, 1),         //-8dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x01, 0xc, 1),         //-7dBm
    PAN31XX_LDO_POWER_MAKE(0x0e, 0x01, 0xc, 1),         //-6dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x02, 0xc, 1),         //-5dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x02, 0xc, 1),         //-4dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x03, 0xc, 1),         //-3dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x03, 0xc, 1),         //-2dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x04, 0xc, 1),         //-1dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x05, 0xc, 1),         //0dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x07, 0xc, 1),         //1dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x07, 0xc, 1),         //2dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x07, 0xc, 1),         //3dBm
    PAN31XX_LDO_POWER_MAKE(0x11, 0x07, 0xc, 1),         //4dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x07, 0xc, 1),         //5dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x07, 0xc, 1),         //6dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x09, 0xc, 1),         //7dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x0b, 0xc, 1),         //8dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x0d, 0xc, 1),         //9dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x11, 0xc, 1),         //10dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x16, 0xc, 1),         //11dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x1f, 0xc, 1),         //12dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x30, 0xc, 1),         //13dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x0f, 0xc, 0),         //14dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x12, 0xc, 0),         //15dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x15, 0xc, 0),         //16dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x1a, 0xc, 0),         //17dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x20, 0xc, 0),         //18dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x2b, 0xc, 0),         //19dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x3f, 0xc, 0)          //20dBm
};

const uint16_t pan31xx_ldo_power_0402_860_870mhz[41] = {
    PAN31XX_LDO_POWER_MAKE(0x00, 0x05, 0x1, 1),        //-20dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x13, 0x0, 1),        //-19dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x06, 0x1, 1),        //-18dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x07, 0x1, 1),        //-17dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x08, 0x1, 1),        //-16dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0x8, 1),        //-15dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0xb, 1),        //-14dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x00, 0xc, 1),        //-13dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x00, 0xc, 1),        //-12dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x00, 0xc, 1),        //-11dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xc, 1),        //-10dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xf, 1),        //-9dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x01, 0xc, 1),        //-8dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x01, 0xc, 1),        //-7dBm
    PAN31XX_LDO_POWER_MAKE(0x0e, 0x01, 0xc, 1),        //-6dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x02, 0xc, 1),        //-5dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x02, 0xc, 1),        //-4dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x03, 0xc, 1),        //-3dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x03, 0xc, 1),        //-2dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x04, 0xc, 1),        //-1dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x05, 0xc, 1),        //0dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x07, 0xc, 1),        //1dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x07, 0xc, 1),        //2dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x07, 0xc, 1),        //3dBm
    PAN31XX_LDO_POWER_MAKE(0x11, 0x07, 0xc, 1),        //4dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x07, 0xc, 1),        //5dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x07, 0xc, 1),        //6dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x09, 0xc, 1),        //7dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x2c, 0xc, 1),        //8dBm
    PAN31XX_LDO_POWER_MAKE(0x0b, 0x2c, 0xc, 1),        //9dBm
    PAN31XX_LDO_POWER_MAKE(0x10, 0x2c, 0xc, 1),        //10dBm
    PAN31XX_LDO_POWER_MAKE(0x15, 0x2c, 0xc, 1),        //11dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x2c, 0xc, 1),        //12dBm
    PAN31XX_LDO_POWER_MAKE(0x1b, 0x3f, 0xc, 1),        //13dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x3c, 0xc, 0),        //14dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x3c, 0xc, 0),        //15dBm
    PAN31XX_LDO_POWER_MAKE(0x08, 0x3c, 0xc, 0),        //16dBm
    PAN31XX_LDO_POWER_MAKE(0x0c, 0x3c, 0xc, 0),        //17dBm
    PAN31XX_LDO_POWER_MAKE(0x11, 0x3c, 0xc, 0),        //18dBm
    PAN31XX_LDO_POWER_MAKE(0x16, 0x3c, 0xc, 0),        //19dBm
    PAN31XX_LDO_POWER_MAKE(0x1c, 0x3c, 0xc, 0)         //20dBm 
};

const uint16_t pan31xx_ldo_power_0402_902_928mhz[41] = {
    PAN31XX_LDO_POWER_MAKE(0x00, 0x05, 0x1, 1),        //-20dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x13, 0x0, 1),        //-19dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x06, 0x1, 1),        //-18dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x07, 0x1, 1),        //-17dBm
    PAN31XX_LDO_POWER_MAKE(0x18, 0x08, 0x1, 1),        //-16dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0x8, 1),        //-15dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x00, 0xb, 1),        //-14dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x00, 0xc, 1),        //-13dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x00, 0xc, 1),        //-12dBm
    PAN31XX_LDO_POWER_MAKE(0x12, 0x00, 0xc, 1),        //-11dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xc, 1),        //-10dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x00, 0xf, 1),        //-9dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x01, 0xc, 1),        //-8dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x01, 0xc, 1),        //-7dBm
    PAN31XX_LDO_POWER_MAKE(0x0e, 0x01, 0xc, 1),        //-6dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x02, 0xc, 1),        //-5dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x02, 0xc, 1),        //-4dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x03, 0xc, 1),        //-3dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x03, 0xc, 1),        //-2dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x04, 0xc, 1),        //-1dBm
    PAN31XX_LDO_POWER_MAKE(0x03, 0x05, 0xc, 1),        //0dBm
    PAN31XX_LDO_POWER_MAKE(0x00, 0x07, 0xc, 1),        //1dBm
    PAN31XX_LDO_POWER_MAKE(0x06, 0x07, 0xc, 1),        //2dBm
    PAN31XX_LDO_POWER_MAKE(0x0a, 0x07, 0xc, 1),        //3dBm
    PAN31XX_LDO_POWER_MAKE(0x11, 0x07, 0xc, 1),        //4dBm
    PAN31XX_LDO_POWER_MAKE(0x17, 0x07, 0xc, 1),        //5dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x07, 0xc, 1),        //6dBm
    PAN31XX_LDO_POWER_MAKE(0x1f, 0x09, 0xc, 1),        //7dBm
    PAN31XX_LDO_POWER_MAKE(0x07, 0x2c, 0xc, 1),        //8dBm
    PAN31XX_LDO_POWER_MAKE(0x0b, 0x2c, 0xc, 1),        //9dBm
    PAN31XX_LDO_POWER_MAKE(0x10, 0x2c, 0xc, 1),        //10dBm
    PAN31XX_LDO_POWER_MAKE(0x15, 0x2c, 0xc, 1),        //11dBm
    PAN31XX_LDO_POWER_MAKE(0x1a, 0x2c, 0xc, 1),        //12dBm
    PAN31XX_LDO_POWER_MAKE(0x1b, 0x3f, 0xc, 1),        //13dBm
    PAN31XX_LDO_POWER_MAKE(0x01, 0x3c, 0xc, 0),        //14dBm
    PAN31XX_LDO_POWER_MAKE(0x04, 0x3c, 0xc, 0),        //15dBm
    PAN31XX_LDO_POWER_MAKE(0x08, 0x3c, 0xc, 0),        //16dBm
    PAN31XX_LDO_POWER_MAKE(0x0c, 0x3c, 0xc, 0),        //17dBm
    PAN31XX_LDO_POWER_MAKE(0x11, 0x3c, 0xc, 0),        //18dBm
    PAN31XX_LDO_POWER_MAKE(0x16, 0x3c, 0xc, 0),        //19dBm
    PAN31XX_LDO_POWER_MAKE(0x1c, 0x3c, 0xc, 0)         //20dBm
};

#define PAN31XX_DCDC_POWER_GET_VDD_PA_TRIM(v)       (((v) >> 11) & 0x1f)
#define PAN31XX_DCDC_POWER_GET_PA_2ND_RAMP(v)       (((v) >> 5) & 0x3f)
#define PAN31XX_DCDC_POWER_GET_PA_BIAS_TRIM(v)      (((v) >> 1) & 0xf)
#define PAN31XX_DCDC_POWER_GET_LP_EN(v)             ((v) & 1)
#define PAN31XX_DCDC_POWER_GET_DCDC_EN(v)           (((v) >> 21) & 1)
#define PAN31XX_DCDC_POWER_GET_DCDC_VOUT_TRIM(v)    (((v) >> 16) & 0x1f)
#define PAN31XX_DCDC_POWER_MAKE(VDD_PA_TRIM, PA_2ND_RAMP, PA_BIAS_TRIM, lp_en, DCDC_EN, DCDC_VOUT_TRIM) \
    (((VDD_PA_TRIM) << 11) | ((PA_2ND_RAMP) << 5) | ((PA_BIAS_TRIM) << 1) | (lp_en) | ((DCDC_EN) << 21) | ((DCDC_VOUT_TRIM) << 16))

const uint32_t pan31xx_dcdc_power_0603_420_445mhz[34] = {
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x0e, 0x0, 1, 1, 0x0d),       //-20dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x11, 0x0, 1, 1, 0x0d),       //-19dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x05, 0x1, 1, 1, 0x0d),       //-18dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x06, 0x1, 1, 1, 0x0d),       //-17dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x17, 0x0, 1, 1, 0x0d),       //-16dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x01, 0x3, 1, 1, 0x0d),       //-15dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0x5, 1, 1, 0x0d),       //-14dBm
    PAN31XX_DCDC_POWER_MAKE(0x0e, 0x00, 0x5, 1, 1, 0x0d),       //-13dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x00, 0x8, 1, 1, 0x0d),       //-12dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x00, 0x9, 1, 1, 0x0d),       //-11dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x00, 0xc, 1, 1, 0x0d),       //-10dBm
    PAN31XX_DCDC_POWER_MAKE(0x08, 0x00, 0xc, 1, 1, 0x0d),       //-9dBm
    PAN31XX_DCDC_POWER_MAKE(0x10, 0x00, 0xc, 1, 1, 0x0d),       //-8dBm
    PAN31XX_DCDC_POWER_MAKE(0x19, 0x00, 0xc, 1, 1, 0x0d),       //-7dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xe, 1, 1, 0x0d),       //-6dBm
    PAN31XX_DCDC_POWER_MAKE(0x02, 0x01, 0xc, 1, 1, 0x0d),       //-5dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x01, 0xc, 1, 1, 0x0d),       //-4dBm
    PAN31XX_DCDC_POWER_MAKE(0x0d, 0x01, 0xc, 1, 1, 0x0d),       //-3dBm
    PAN31XX_DCDC_POWER_MAKE(0x04, 0x02, 0xc, 1, 1, 0x0d),       //-2dBm
    PAN31XX_DCDC_POWER_MAKE(0x08, 0x02, 0xc, 1, 1, 0x0d),       //-1dBm
    PAN31XX_DCDC_POWER_MAKE(0x0f, 0x02, 0xc, 1, 1, 0x0d),       //0dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x02, 0xc, 1, 1, 0x0d),       //1dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x02, 0xc, 1, 1, 0x0d),       //2dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x03, 0xc, 1, 1, 0x0d),       //3dBm
    PAN31XX_DCDC_POWER_MAKE(0x15, 0x04, 0xc, 1, 1, 0x0d),       //4dBm
    PAN31XX_DCDC_POWER_MAKE(0x15, 0x05, 0xc, 1, 1, 0x0d),       //5dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x06, 0xc, 1, 1, 0x0d),       //6dBm
    PAN31XX_DCDC_POWER_MAKE(0x19, 0x07, 0xc, 1, 1, 0x0d),       //7dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x0a, 0xc, 1, 1, 0x0d),       //8dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x0a, 0xc, 1, 1, 0x0d),       //9dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x0d, 0xc, 1, 1, 0x0d),       //10dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x12, 0xc, 1, 1, 0x0d),       //11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x1c, 0xc, 1, 1, 0x0d),       //12dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x3f, 0xc, 1, 1, 0x13)        //13dBm
};

const uint32_t pan31xx_dcdc_power_0603_470_510mhz[34] = {
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x0e, 0x0, 1, 1, 0x0f),       //-20dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x11, 0x0, 1, 1, 0x0f),       //-19dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x05, 0x1, 1, 1, 0x0f),       //-18dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x06, 0x1, 1, 1, 0x0f),       //-17dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x17, 0x0, 1, 1, 0x0f),       //-16dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x01, 0x3, 1, 1, 0x0f),       //-15dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0x5, 1, 1, 0x0f),       //-14dBm
    PAN31XX_DCDC_POWER_MAKE(0x0e, 0x00, 0x5, 1, 1, 0x0f),       //-13dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x00, 0x8, 1, 1, 0x0f),       //-12dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x00, 0x9, 1, 1, 0x0f),       //-11dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x00, 0xc, 1, 1, 0x0f),       //-10dBm
    PAN31XX_DCDC_POWER_MAKE(0x08, 0x00, 0xc, 1, 1, 0x0f),       //-9dBm
    PAN31XX_DCDC_POWER_MAKE(0x10, 0x00, 0xc, 1, 1, 0x0f),       //-8dBm
    PAN31XX_DCDC_POWER_MAKE(0x19, 0x00, 0xc, 1, 1, 0x0f),       //-7dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xe, 1, 1, 0x0f),       //-6dBm
    PAN31XX_DCDC_POWER_MAKE(0x02, 0x01, 0xc, 1, 1, 0x0f),       //-5dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x01, 0xc, 1, 1, 0x0f),       //-4dBm
    PAN31XX_DCDC_POWER_MAKE(0x0d, 0x01, 0xc, 1, 1, 0x0f),       //-3dBm
    PAN31XX_DCDC_POWER_MAKE(0x04, 0x02, 0xc, 1, 1, 0x0f),       //-2dBm
    PAN31XX_DCDC_POWER_MAKE(0x08, 0x02, 0xc, 1, 1, 0x0f),       //-1dBm
    PAN31XX_DCDC_POWER_MAKE(0x0f, 0x02, 0xc, 1, 1, 0x0f),       //0dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x02, 0xc, 1, 1, 0x0f),       //1dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x02, 0xc, 1, 1, 0x0f),       //2dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x03, 0xc, 1, 1, 0x0f),       //3dBm
    PAN31XX_DCDC_POWER_MAKE(0x15, 0x04, 0xc, 1, 1, 0x0f),       //4dBm
    PAN31XX_DCDC_POWER_MAKE(0x15, 0x05, 0xc, 1, 1, 0x0f),       //5dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x06, 0xc, 1, 1, 0x0f),       //6dBm
    PAN31XX_DCDC_POWER_MAKE(0x19, 0x07, 0xc, 1, 1, 0x0f),       //7dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x0a, 0xc, 1, 1, 0x0f),       //8dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x0a, 0xc, 1, 1, 0x0f),       //9dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x0d, 0xc, 1, 1, 0x0f),       //10dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x12, 0xc, 1, 1, 0x0f),       //11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x1c, 0xc, 1, 1, 0x0f),       //12dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x3f, 0xc, 1, 1, 0x13)        //13dBm
};


const uint32_t pan31xx_dcdc_power_0603_860_870mhz[34] = {
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x0e, 0x0, 1, 1, 0x0f),       //-20dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x11, 0x0, 1, 1, 0x0f),       //-19dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x05, 0x1, 1, 1, 0x0f),       //-18dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x06, 0x1, 1, 1, 0x0f),       //-17dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x17, 0x0, 1, 1, 0x0f),       //-16dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0x5, 1, 1, 0x0f),       //-15dBm
    PAN31XX_DCDC_POWER_MAKE(0x0e, 0x00, 0x5, 1, 1, 0x0f),       //-14dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x00, 0x8, 1, 1, 0x0f),       //-13dBm
    PAN31XX_DCDC_POWER_MAKE(0x05, 0x00, 0x9, 1, 1, 0x0f),       //-12dBm
    PAN31XX_DCDC_POWER_MAKE(0x05, 0x00, 0xc, 1, 1, 0x0f),       //-11dBm
    PAN31XX_DCDC_POWER_MAKE(0x0b, 0x00, 0xc, 1, 1, 0x0f),       //-10dBm
    PAN31XX_DCDC_POWER_MAKE(0x13, 0x00, 0xc, 1, 1, 0x0f),       //-9dBm
    PAN31XX_DCDC_POWER_MAKE(0x1c, 0x00, 0xc, 1, 1, 0x0f),       //-8dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xe, 1, 1, 0x0f),       //-7dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x01, 0xc, 1, 1, 0x0f),       //-6dBm
    PAN31XX_DCDC_POWER_MAKE(0x0b, 0x01, 0xc, 1, 1, 0x0f),       //-5dBm
    PAN31XX_DCDC_POWER_MAKE(0x10, 0x01, 0xc, 1, 1, 0x0f),       //-4dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x02, 0xc, 1, 1, 0x0f),       //-3dBm
    PAN31XX_DCDC_POWER_MAKE(0x0b, 0x02, 0xc, 1, 1, 0x0f),       //-2dBm
    PAN31XX_DCDC_POWER_MAKE(0x12, 0x02, 0xc, 1, 1, 0x0f),       //-1dBm
    PAN31XX_DCDC_POWER_MAKE(0x19, 0x02, 0xc, 1, 1, 0x0f),       //0dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x02, 0xf, 1, 1, 0x0f),       //1dBm
    PAN31XX_DCDC_POWER_MAKE(0x1b, 0x03, 0xc, 1, 1, 0x0f),       //2dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x04, 0xc, 1, 1, 0x0f),       //3dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x05, 0xc, 1, 1, 0x0f),       //4dBm
    PAN31XX_DCDC_POWER_MAKE(0x1a, 0x06, 0xc, 1, 1, 0x0f),       //5dBm
    PAN31XX_DCDC_POWER_MAKE(0x1c, 0x07, 0xc, 1, 1, 0x0f),       //6dBm
    PAN31XX_DCDC_POWER_MAKE(0x1a, 0x0a, 0xc, 1, 1, 0x0f),       //7dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x2c, 0xc, 1, 1, 0x0f),       //8dBm
    PAN31XX_DCDC_POWER_MAKE(0x0d, 0x2c, 0xc, 1, 1, 0x0f),       //9dBm
    PAN31XX_DCDC_POWER_MAKE(0x13, 0x2c, 0xc, 1, 1, 0x13),       //10dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x2c, 0xc, 1, 1, 0x13),       //11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1c, 0x2c, 0xc, 1, 1, 0x13),       //12dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x3f, 0xc, 1, 1, 0x17)        //13dBm
};

const uint32_t pan31xx_dcdc_power_0603_902_928mhz[34] = {
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x06, 0x1, 1, 1, 0x0f),      //-20dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x07, 0x1, 1, 1, 0x0f),      //-19dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x08, 0x1, 1, 1, 0x0f),      //-18dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x09, 0x1, 1, 1, 0x0f),      //-17dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x0a, 0x1, 1, 1, 0x0f),      //-16dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x04, 0x2, 1, 1, 0x0f),      //-15dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x05, 0x2, 1, 1, 0x0f),      //-14dBm
    PAN31XX_DCDC_POWER_MAKE(0x04, 0x00, 0x8, 1, 1, 0x0f),      //-13dBm
    PAN31XX_DCDC_POWER_MAKE(0x08, 0x00, 0x9, 1, 1, 0x0f),      //-12dBm
    PAN31XX_DCDC_POWER_MAKE(0x05, 0x00, 0xc, 1, 1, 0x0f),      //-11dBm
    PAN31XX_DCDC_POWER_MAKE(0x0b, 0x00, 0xc, 1, 1, 0x0f),      //-10dBm
    PAN31XX_DCDC_POWER_MAKE(0x13, 0x00, 0xc, 1, 1, 0x0f),      //-9dBm
    PAN31XX_DCDC_POWER_MAKE(0x1c, 0x00, 0xc, 1, 1, 0x0f),      //-8dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xe, 1, 1, 0x0f),      //-7dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x01, 0xc, 1, 1, 0x0f),      //-6dBm
    PAN31XX_DCDC_POWER_MAKE(0x0b, 0x01, 0xc, 1, 1, 0x0f),      //-5dBm
    PAN31XX_DCDC_POWER_MAKE(0x10, 0x01, 0xc, 1, 1, 0x0f),      //-4dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x02, 0xc, 1, 1, 0x0f),      //-3dBm
    PAN31XX_DCDC_POWER_MAKE(0x0b, 0x02, 0xc, 1, 1, 0x0f),      //-2dBm
    PAN31XX_DCDC_POWER_MAKE(0x12, 0x02, 0xc, 1, 1, 0x0f),      //-1dBm
    PAN31XX_DCDC_POWER_MAKE(0x19, 0x02, 0xc, 1, 1, 0x0f),      //0dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x02, 0xf, 1, 1, 0x0f),      //1dBm
    PAN31XX_DCDC_POWER_MAKE(0x1b, 0x03, 0xc, 1, 1, 0x0f),      //2dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x04, 0xc, 1, 1, 0x0f),      //3dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x05, 0xc, 1, 1, 0x0f),      //4dBm
    PAN31XX_DCDC_POWER_MAKE(0x1a, 0x06, 0xc, 1, 1, 0x0f),      //5dBm
    PAN31XX_DCDC_POWER_MAKE(0x1c, 0x07, 0xc, 1, 1, 0x0f),      //6dBm
    PAN31XX_DCDC_POWER_MAKE(0x1a, 0x0a, 0xc, 1, 1, 0x0f),      //7dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x2c, 0xc, 1, 1, 0x0f),      //8dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x2c, 0xc, 1, 1, 0x0f),      //9dBm
    PAN31XX_DCDC_POWER_MAKE(0x10, 0x2c, 0xc, 1, 1, 0x13),      //10dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x2c, 0xc, 1, 1, 0x13),      //11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1b, 0x2c, 0xc, 1, 1, 0x13),      //12dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x3f, 0xc, 1, 1, 0x17)       //13dBm 
};

const uint32_t pan31xx_dcdc_power_0402_420_445mhz[34] = {
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x05, 0x1, 1, 1, 0x0d),      //-20dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x13, 0x0, 1, 1, 0x0d),      //-19dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x06, 0x1, 1, 1, 0x0d),      //-18dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x07, 0x1, 1, 1, 0x0d),      //-17dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x08, 0x1, 1, 1, 0x0d),      //-16dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0x8, 1, 1, 0x0d),      //-15dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0xb, 1, 1, 0x0d),      //-14dBm
    PAN31XX_DCDC_POWER_MAKE(0x04, 0x00, 0xc, 1, 1, 0x0d),      //-13dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x00, 0xc, 1, 1, 0x0d),      //-12dBm
    PAN31XX_DCDC_POWER_MAKE(0x12, 0x00, 0xc, 1, 1, 0x0d),      //-11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xc, 1, 1, 0x0d),      //-10dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xf, 1, 1, 0x0d),      //-9dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x01, 0xc, 1, 1, 0x0d),      //-8dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x01, 0xc, 1, 1, 0x0d),      //-7dBm
    PAN31XX_DCDC_POWER_MAKE(0x0e, 0x01, 0xc, 1, 1, 0x0d),      //-6dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x02, 0xc, 1, 1, 0x0d),      //-5dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x02, 0xc, 1, 1, 0x0d),      //-4dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x03, 0xc, 1, 1, 0x0d),      //-3dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x03, 0xc, 1, 1, 0x0d),      //-2dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x04, 0xc, 1, 1, 0x0d),      //-1dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x05, 0xc, 1, 1, 0x0d),      //0dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x07, 0xc, 1, 1, 0x0d),      //1dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x07, 0xc, 1, 1, 0x0d),      //2dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x07, 0xc, 1, 1, 0x0d),      //3dBm
    PAN31XX_DCDC_POWER_MAKE(0x11, 0x07, 0xc, 1, 1, 0x0d),      //4dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x07, 0xc, 1, 1, 0x0d),      //5dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x07, 0xc, 1, 1, 0x0d),      //6dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x09, 0xc, 1, 1, 0x0d),      //7dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x0b, 0xc, 1, 1, 0x0d),      //8dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x0d, 0xc, 1, 1, 0x10),      //9dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x11, 0xc, 1, 1, 0x10),      //10dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x16, 0xc, 1, 1, 0x10),      //11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x1f, 0xc, 1, 1, 0x13),      //12dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x30, 0xc, 1, 1, 0x13)       //13dBm
};

const uint32_t pan31xx_dcdc_power_0402_470_510mhz[34] = {
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x05, 0x1, 1, 1, 0x0d),       //-20dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x13, 0x0, 1, 1, 0x0d),       //-19dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x06, 0x1, 1, 1, 0x0d),       //-18dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x07, 0x1, 1, 1, 0x0d),       //-17dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x08, 0x1, 1, 1, 0x0d),       //-16dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0x8, 1, 1, 0x0d),       //-15dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0xb, 1, 1, 0x0d),       //-14dBm
    PAN31XX_DCDC_POWER_MAKE(0x04, 0x00, 0xc, 1, 1, 0x0d),       //-13dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x00, 0xc, 1, 1, 0x0d),       //-12dBm
    PAN31XX_DCDC_POWER_MAKE(0x12, 0x00, 0xc, 1, 1, 0x0d),       //-11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xc, 1, 1, 0x0d),       //-10dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xf, 1, 1, 0x0d),       //-9dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x01, 0xc, 1, 1, 0x0d),       //-8dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x01, 0xc, 1, 1, 0x0d),       //-7dBm
    PAN31XX_DCDC_POWER_MAKE(0x0e, 0x01, 0xc, 1, 1, 0x0d),       //-6dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x02, 0xc, 1, 1, 0x0d),       //-5dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x02, 0xc, 1, 1, 0x0d),       //-4dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x03, 0xc, 1, 1, 0x0d),       //-3dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x03, 0xc, 1, 1, 0x0d),       //-2dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x04, 0xc, 1, 1, 0x0d),       //-1dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x05, 0xc, 1, 1, 0x0d),       //0dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x07, 0xc, 1, 1, 0x0d),       //1dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x07, 0xc, 1, 1, 0x0d),       //2dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x07, 0xc, 1, 1, 0x0d),       //3dBm
    PAN31XX_DCDC_POWER_MAKE(0x11, 0x07, 0xc, 1, 1, 0x0d),       //4dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x07, 0xc, 1, 1, 0x0d),       //5dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x07, 0xc, 1, 1, 0x0d),       //6dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x09, 0xc, 1, 1, 0x0d),       //7dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x0b, 0xc, 1, 1, 0x0d),       //8dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x0d, 0xc, 1, 1, 0x10),       //9dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x11, 0xc, 1, 1, 0x10),       //10dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x16, 0xc, 1, 1, 0x10),       //11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x1f, 0xc, 1, 1, 0x13),       //12dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x30, 0xc, 1, 1, 0x13)        //13dBm
};

const uint32_t pan31xx_dcdc_power_0402_860_870mhz[34] = {
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x05, 0x1, 1, 1, 0x10),       //-20dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x13, 0x0, 1, 1, 0x10),       //-19dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x06, 0x1, 1, 1, 0x10),       //-18dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x07, 0x1, 1, 1, 0x10),       //-17dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x08, 0x1, 1, 1, 0x10),       //-16dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0x8, 1, 1, 0x10),       //-15dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0xb, 1, 1, 0x10),       //-14dBm
    PAN31XX_DCDC_POWER_MAKE(0x04, 0x00, 0xc, 1, 1, 0x10),       //-13dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x00, 0xc, 1, 1, 0x10),       //-12dBm
    PAN31XX_DCDC_POWER_MAKE(0x12, 0x00, 0xc, 1, 1, 0x10),       //-11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xc, 1, 1, 0x10),       //-10dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xf, 1, 1, 0x10),       //-9dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x01, 0xc, 1, 1, 0x10),       //-8dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x01, 0xc, 1, 1, 0x10),       //-7dBm
    PAN31XX_DCDC_POWER_MAKE(0x0e, 0x01, 0xc, 1, 1, 0x10),       //-6dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x02, 0xc, 1, 1, 0x10),       //-5dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x02, 0xc, 1, 1, 0x10),       //-4dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x03, 0xc, 1, 1, 0x10),       //-3dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x03, 0xc, 1, 1, 0x10),       //-2dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x04, 0xc, 1, 1, 0x10),       //-1dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x05, 0xc, 1, 1, 0x10),       //0dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x07, 0xc, 1, 1, 0x10),       //1dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x07, 0xc, 1, 1, 0x10),       //2dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x07, 0xc, 1, 1, 0x10),       //3dBm
    PAN31XX_DCDC_POWER_MAKE(0x11, 0x07, 0xc, 1, 1, 0x10),       //4dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x07, 0xc, 1, 1, 0x10),       //5dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x07, 0xc, 1, 1, 0x10),       //6dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x09, 0xc, 1, 1, 0x10),       //7dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x2c, 0xc, 1, 1, 0x0f),       //8dBm
    PAN31XX_DCDC_POWER_MAKE(0x0b, 0x2c, 0xc, 1, 1, 0x0f),       //9dBm
    PAN31XX_DCDC_POWER_MAKE(0x10, 0x2c, 0xc, 1, 1, 0x13),       //10dBm
    PAN31XX_DCDC_POWER_MAKE(0x15, 0x2c, 0xc, 1, 1, 0x13),       //11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1a, 0x2c, 0xc, 1, 1, 0x15),       //12dBm
    PAN31XX_DCDC_POWER_MAKE(0x1b, 0x3f, 0xc, 1, 1, 0x19)        //13dBm
};

const uint32_t pan31xx_dcdc_power_0402_902_928mhz[34] = {
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x05, 0x1, 1, 1, 0x10),      //-20dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x13, 0x0, 1, 1, 0x10),      //-19dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x06, 0x1, 1, 1, 0x10),      //-18dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x07, 0x1, 1, 1, 0x10),      //-17dBm
    PAN31XX_DCDC_POWER_MAKE(0x18, 0x08, 0x1, 1, 1, 0x10),      //-16dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0x8, 1, 1, 0x10),      //-15dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x00, 0xb, 1, 1, 0x10),      //-14dBm
    PAN31XX_DCDC_POWER_MAKE(0x04, 0x00, 0xc, 1, 1, 0x10),      //-13dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x00, 0xc, 1, 1, 0x10),      //-12dBm
    PAN31XX_DCDC_POWER_MAKE(0x12, 0x00, 0xc, 1, 1, 0x10),      //-11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xc, 1, 1, 0x10),      //-10dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x00, 0xf, 1, 1, 0x10),      //-9dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x01, 0xc, 1, 1, 0x10),      //-8dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x01, 0xc, 1, 1, 0x10),      //-7dBm
    PAN31XX_DCDC_POWER_MAKE(0x0e, 0x01, 0xc, 1, 1, 0x10),      //-6dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x02, 0xc, 1, 1, 0x10),      //-5dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x02, 0xc, 1, 1, 0x10),      //-4dBm
    PAN31XX_DCDC_POWER_MAKE(0x01, 0x03, 0xc, 1, 1, 0x10),      //-3dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x03, 0xc, 1, 1, 0x10),      //-2dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x04, 0xc, 1, 1, 0x10),      //-1dBm
    PAN31XX_DCDC_POWER_MAKE(0x03, 0x05, 0xc, 1, 1, 0x10),      //0dBm
    PAN31XX_DCDC_POWER_MAKE(0x00, 0x07, 0xc, 1, 1, 0x10),      //1dBm
    PAN31XX_DCDC_POWER_MAKE(0x06, 0x07, 0xc, 1, 1, 0x10),      //2dBm
    PAN31XX_DCDC_POWER_MAKE(0x0a, 0x07, 0xc, 1, 1, 0x10),      //3dBm
    PAN31XX_DCDC_POWER_MAKE(0x11, 0x07, 0xc, 1, 1, 0x10),      //4dBm
    PAN31XX_DCDC_POWER_MAKE(0x17, 0x07, 0xc, 1, 1, 0x10),      //5dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x07, 0xc, 1, 1, 0x10),      //6dBm
    PAN31XX_DCDC_POWER_MAKE(0x1f, 0x09, 0xc, 1, 1, 0x10),      //7dBm
    PAN31XX_DCDC_POWER_MAKE(0x07, 0x2c, 0xc, 1, 1, 0x0f),      //8dBm
    PAN31XX_DCDC_POWER_MAKE(0x0b, 0x2c, 0xc, 1, 1, 0x0f),      //9dBm
    PAN31XX_DCDC_POWER_MAKE(0x10, 0x2c, 0xc, 1, 1, 0x13),      //10dBm
    PAN31XX_DCDC_POWER_MAKE(0x15, 0x2c, 0xc, 1, 1, 0x13),      //11dBm
    PAN31XX_DCDC_POWER_MAKE(0x1a, 0x2c, 0xc, 1, 1, 0x15),      //12dBm
    PAN31XX_DCDC_POWER_MAKE(0x1b, 0x3f, 0xc, 1, 1, 0x1a)       //13dBm
};


//-------------------------PAN312x api接口------------------------//
//该部分函数为MCU对PAN312x模块接口函数
//--------------------------------------------------------------//
static int __PAN312xCmd_Write__(const void* wbuf, int wlen);
static int __PAN312xCmd_Write(const void* wbuf, int wlen);
static int __PAN312xCmd_WriteRead(const void* wbuf, int wlen, void* rbuf, int rlen);
#if PAN312x_INTERFACE == PAN312x_IF_SPI
    #define PAN312x_DataBeginWrite()         PAN312x_DataBegin()
    #define PAN312x_DataBeginRead()          /* nothing to do */
    #define PAN312x_DataReadNonLast(B, L)    PAN312x_DataRead((B), (L))
    #define PAN312x_DataReadLast(B, L)       PAN312x_DataRead((B), (L))
    #define PAN312xReg_Waddr(adr)               (((adr) << 1) | 1)
    #define PAN312xReg_Raddr(adr)               (((adr) << 1) | 0)
    
#elif PAN312x_INTERFACE == PAN312x_IF_3SPI
    #define PAN312x_DataBeginWrite()         PAN312x_DataBegin()
    #define PAN312x_DataBeginRead()          /* nothing to do */
    #define PAN312x_DataReadNonLast(B, L)    PAN312x_DataRead((B), (L))
    #define PAN312x_DataReadLast(B, L)       PAN312x_DataRead((B), (L))
    #define PAN312xReg_Waddr(adr)               (((adr) << 1) | 1)
    #define PAN312xReg_Raddr(adr)               (((adr) << 1) | 0)
#elif PAN312x_INTERFACE == PAN312x_IF_I2C
    #define PAN312x_DataBeginWrite()         PAN312x_DataBegin()
    #define PAN312x_DataBeginRead()          PAN312x_DataReadBegin()/* nothing to do */
    #define PAN312x_DataReadNonLast(B, L)    PAN312x_DataRead((B), (L))
    #define PAN312x_DataReadLast(B, L)       PAN312x_DataRead((B), (L))
    #define PAN312xReg_Waddr(adr)               (((adr) << 1) | 0)
    #define PAN312xReg_Raddr(adr)               (((adr) << 1) | 1)
#endif //PAN312x_INTERFACE

int PAN312x_Trigger()
{
    while(1){
        uint8_t temp = PAN312xReg_ReadB1(R000);
        if(temp & R000_OTP_LOAD_DONE_Msk) break;
    }  
    PAN312xReg_WriteB1(R004, 0x1C);
    int ret;
    uint8_t cmd = 0x44, cts;
    do{
        PAN312x_DataBeginWrite();
        ret = PAN312x_DataWrite(&cmd, 1);
        if(ret == 1) {
            PAN312x_DataBeginRead();
            ret = PAN312x_DataReadLast(&cts, 1);
        }
        PAN312x_DataEnd();
        if(ret == 1){
            if((cts & 0xC0u) == 0x40u){
                ret = PAN312x_OK;
                break;
            }
        }
    } while(ret == 1);
    return ret;
}
//--------------------------------------------------------------------------------------------------
int PAN312xRaw_Write(const void* buf, int len){
    PAN312x_Lock();
    PAN312x_DataBeginWrite();
    int ret = PAN312x_DataWrite(buf, len);
    PAN312x_DataEnd();
    PAN312x_Unlock();
    return ret;
}

int PAN312xRaw_WriteAddr(uint8_t adr, const void* buf, int len){
    int ret;
    PAN312x_Lock();
    PAN312x_DataBeginWrite();
    
    ret = PAN312x_DataWrite(&adr, 1);
    if(ret == 1){
        ret = PAN312x_DataWrite(buf, len);
    }
    PAN312x_DataEnd();
    PAN312x_Unlock();
    return ret;
}
int PAN312xRaw_WriteAddrB1(uint8_t adr, uint8_t val){
    int ret = PAN312xRaw_WriteAddr(adr, &val, 1);
    return ret == 1 ? 0 : ret;
}
int PAN312xRaw_WriteAddrB2(uint8_t adr, uint16_t val){
    int ret = PAN312xRaw_WriteAddr(adr, &val, 2);
    return ret == 2 ? 0 : ret;
}
int PAN312xRaw_WriteAddrB3(uint8_t adr, uint32_t val){
    int ret = PAN312xRaw_WriteAddr(adr, &val, 3);
    return ret == 3 ? 0 : ret;
}
int PAN312xRaw_WriteAddrB4(uint8_t adr, uint32_t val){
    int ret = PAN312xRaw_WriteAddr(adr, &val, 4);
    return ret == 4 ? 0 : ret;
}
int PAN312xRaw_ReadAddr(uint8_t adr, void* buf, int len){
    int ret;
    PAN312x_Lock();
    PAN312x_DataBeginWrite();
    ret = PAN312x_DataWrite(&adr, 1);
    if(ret == 1){
        PAN312x_DataBeginRead();
        ret = PAN312x_DataReadLast(buf, len);
    }
    PAN312x_DataEnd();
    PAN312x_Unlock();
    return ret;
}
int PAN312xRaw_ReadAddrB1(uint8_t adr){
    uint8_t val;
    int ret = PAN312xRaw_ReadAddr(adr, &val, 1);
    return ret == 1 ? val : ret;
}
int PAN312xRaw_ReadAddrB2(uint8_t adr){
    uint16_t val;
    int ret = PAN312xRaw_ReadAddr(adr, &val, 2);
    return ret == 2 ? val : ret;
}
int PAN312xRaw_ReadAddrB3(uint8_t adr){
    uint32_t val = 0;
    int ret = PAN312xRaw_ReadAddr(adr, &val, 3);
    return ret == 3 ? val : ret;
}
uint32_t PAN312xRaw_ReadAddrB4(uint8_t adr){
    uint32_t val;
    int ret = PAN312xRaw_ReadAddr(adr, &val, 4);
    return val;
}
//--------------------------------------------------------------------------------------------------
int PAN312xReg_Write(uint8_t reg, const void* buf, int len){
    return PAN312xRaw_WriteAddr(PAN312xReg_Waddr(reg), buf, len);
}
int PAN312xReg_WriteB1(uint8_t reg, uint8_t val){
    int ret = PAN312xReg_Write(reg, &val, 1);
    return ret == 1 ? PAN312x_OK : ret;
}
int PAN312xReg_WriteB2(uint8_t reg, uint16_t val){
    int ret = PAN312xReg_Write(reg, &val, 2);
    return ret == 2 ? PAN312x_OK : ret;
}
int PAN312xReg_WriteB3(uint8_t reg, uint32_t val){
    int ret = PAN312xReg_Write(reg, &val, 3);
    return ret == 3 ? PAN312x_OK : ret;
}
int PAN312xReg_WriteB4(uint8_t reg, uint32_t val){
    int ret = PAN312xReg_Write(reg, &val, 4);
    return ret == 4 ? PAN312x_OK : ret;
}
int PAN312xReg_Read(uint8_t reg, void* buf, int len){
    return PAN312xRaw_ReadAddr(PAN312xReg_Raddr(reg), buf, len);
}
int PAN312xReg_ReadB1(uint8_t reg){
    uint8_t val;
    int ret = PAN312xReg_Read(reg, &val, 1);
    return ret == 1 ? val : ret;
}
int PAN312xReg_ReadB2(uint8_t reg){
    uint16_t val;
    int ret = PAN312xReg_Read(reg, &val, 2);
    return ret == 2 ? val : ret;
}
int PAN312xReg_ReadB3(uint8_t reg){
    uint32_t val = 0;
    int ret = PAN312xReg_Read(reg, &val, 3);
    return ret == 3 ? val : ret;
}
uint32_t PAN312xReg_ReadB4(uint8_t reg){
    uint32_t val;
    int ret = PAN312xReg_Read(reg, &val, 4);
    return val;
}
//--------------------------------------------------------------------------------------------------
static int __PAN312xCmd_WaitCts__()
{
    int ret;
    uint8_t cmd = 0x44, cts;
    do{
        PAN312x_DataBeginWrite();
        ret = PAN312x_DataWrite(&cmd, 1);
        if(ret == 1) {
            PAN312x_DataBeginRead();
            ret = PAN312x_DataReadLast(&cts, 1);
        }
        PAN312x_DataEnd();
        if(ret == 1){
            if(!(cts & 0x40)) ret = PAN312x_CTS_ERROR;
            else if(!(cts & 0x80)) ret = PAN312x_OK;
        }
    } while(ret == 1);
    return ret;
}
static int __PAN312xCmd_Write__(const void* wbuf, int wlen){
    PAN312x_DataBeginWrite();
    int ret = PAN312x_DataWrite(wbuf, wlen);
    PAN312x_DataEnd();
    if(ret == wlen){
        int _ret = __PAN312xCmd_WaitCts__();
        if(_ret != PAN312x_OK) ret = _ret;
    }
    return ret;
}
static int __PAN312xCmd_Write(const void* wbuf, int wlen){
    PAN312x_Lock();
    int ret = __PAN312xCmd_Write__(wbuf, wlen);
    PAN312x_Unlock();
    return ret;
}
static int __PAN312xCmd_WriteRead(const void* wbuf, int wlen, void* rbuf, int rlen)
{
    PAN312x_Lock();
    int ret = __PAN312xCmd_Write__(wbuf, wlen);
    if(ret == wlen){
        uint8_t temp = 0x44;
        PAN312x_DataBeginWrite();
        ret = PAN312x_DataWrite(&temp, 1);
        if(ret == 1){
            PAN312x_DataBeginRead();
            ret = PAN312x_DataReadNonLast(&temp, 1); //skip CTS
            if(ret == 1){
                ret = PAN312x_DataReadLast(rbuf, rlen);
            }
        }
        PAN312x_DataEnd();
    }
    PAN312x_Unlock();
    return ret;
}

void PAN312x_WaitReady(void)
{
    int ret;
    uint8_t cmd = 0x44, cts;
    do{
        PAN312x_DataBeginWrite();
        ret = PAN312x_DataWrite(&cmd, 1);
        if(ret == 1) {
            PAN312x_DataBeginRead();
            ret = PAN312x_DataReadLast(&cts, 1);
        }
        PAN312x_DataEnd();
        if(ret == 1){
            if((cts & 0xC0u) == 0x40u){
                ret = PAN312x_OK;
                break;
            }
        }
    }while(ret == 1);
}

void PAN312x_WaitCtsOk(void)
{
    int ret;
    uint8_t cmd = 0x44, cts;
    do{
        PAN312x_DataBeginWrite();
        ret = PAN312x_DataWrite(&cmd, 1);
        if(ret == 1) {
            PAN312x_DataBeginRead();
            ret = PAN312x_DataReadLast(&cts, 1);
        }
        PAN312x_DataEnd();
        if(ret == 1){
            if((cts & 0xC0u) == 0x40u){
                ret = PAN312x_OK;
                break;
            }
        }
    }while(ret == 1);
}

void PAN312x_ReadInvalidData(void)
{
    uint8_t tmpBuffer[33];
    PAN312xReg_Read(0x22, tmpBuffer, sizeof(tmpBuffer));
}

//-------------------------PAN312x 寄存器------------------------//
//该部分函数为MCU对PAN312x模块寄存器进行读写及FIFO的读写
//--------------------------------------------------------------//

/**
  * @简介：向寄存器地址写1字节数据
  * @参数：addr - 寄存器地址
  *        data - 数据
  * @返回值：无
  */
void PAN312x_Write( uint8_t addr, uint8_t data )
{
	PAN312xReg_WriteB1(addr, data); 
    
}
/**
  * @简介：向寄存器地址读1字节数据
  * @参数：addr - 寄存器地址
  *        data - 读数据存储地址
  * @返回值：无
  */
void PAN312x_Read( uint8_t addr, uint8_t *data )
{
	PAN312xReg_Read(addr, data, 1);
}
/**
  * @简介：等待PAN312x Ready
  * @参数：无
  * @返回值：
  */
int PAN312x_Wait_Ready(void)
{
	uint8_t tmp;
	uint16_t time_out;
	while(1){
		PAN312xRaw_ReadAddr(0x44, &tmp, 1);
		if((tmp & (3 << 6)) == (1 << 6)) {
			break;
		}
		if(1000 == time_out++){
			return PAN312x_TIMEOUT;
		}
	}
	return PAN312x_OK;
}




void PAN312x_Set_OP_Reg(uint16_t addr, uint8_t num_value, const uint8_t *value)
{
	PAN312x_SetXdatas(addr, value, num_value);
}

void PAN312x_Get_OP_Reg(uint16_t addr, uint8_t num_value, uint8_t *value)
{
	PAN312x_GetXdatas(addr, value, num_value);
}


/**
  * @简介：通过PAD复位PAN312x(低电平有效)
  * @参数：无
  * @返回值：无
  */
void PAN312x_Reset(void)
{
	PAN312x_Reset_Init();
    PAN312x_Reset_Low();
    HAL_Delay(20);
    PAN312x_Reset_High();
    HAL_Delay(20);
}
/**
  * @简介：PAN312x  IO初始化及配置
  * @参数：无
  * @返回值：无
  */
void PAN312x_InitIo(void)
{
    PAN312x_DIO8_INPUT();
}

/**
  * @简介：DIO8中断开启使能
  * @参数：无
  * @返回值：无
  */
void DIO8_EnableInterrupt(void)
{
    PAN312x_DIO8_INTENABLE();
}
/**
  * @简介：DIO8中断关闭使能
  * @参数：无
  * @返回值：无
  */
void DIO8_DisableInterrupt(void)
{
    PAN312x_DIO8_INTDISABLE();
}
/**
  * @简介：DIO8引脚状态获取
  * @参数：无
  * @返回值：State表示DIO0获取的电平，高电平"1",低电平"0"
  */
GPIO_PinState DIO8_GetState(void)
{
    GPIO_PinState State;
    State = PAN312x_DIO8_GetState();
    return State;
}

/**
  * @简介：PAN312x  FSK初始化
  * @参数：无
  * @返回值：无
  */
uint16_t fwid_test;
void PAN312x_Fsk_Init(void)
{
    PAN312x_InitIo();                // PAIO口初始化
    PAN312x_SPI_Init();              // SPI初始化
    
	#if 1
		//otp 芯片
		PAN312x_Reset();                 // 复位RF
	#else
		//ram 芯片
		uint8_t tmp = PAN312xReg_ReadB1(R000);
		tmp &= 0xf0;
		tmp |= 0x0b;
	    PAN312xReg_WriteB1(R000, tmp);
	#endif
    
    #if PAN312x_INTERFACE == PAN312x_IF_3SPI
    
        PAN312x_SPI3wire_Enable();
        
    #endif
    

    
    if(TcxoControlByGpio == 0x01){
        PAN312x_TCXO_ControlByGpio(PAN312x_GPIO_PIN_9, 1); /* 使能TCXO, 高电平有效 */  
    }
    
    
	PAN312x_Trigger();
    
	
    
    //修改寄存器默认值
    PAN312x_RegMap_Init();
   
	//RC校准
    PAN312x_RC_Calibration();
}
/**
  * @简介：PAN312x寄存器RegMap初始化
  * @参数：无
  * @返回值：无
  */
void PAN312x_RegMap_Init(void)
{
    uint8_t tmp;
    uint8_t tmpBuffer[37] = {0x06, 0x5f, 0x05, 0x35, 0x66, 0x23, 0x05, 0x05,
                             0x54, 0x23, 0x05, 0x05, 0x54, 0x23, 0x05, 0x05,
                             0x54, 0x23, 0x05, 0x05, 0x54, 0x23, 0x05, 0x05,
                             0x54, 0x37, 0x05, 0x18, 0x3c, 0x3f, 0x05, 0x25,
                             0x30, 0x5f, 0x05, 0x35, 0x0c};
    //[0x70][0x3e][0x13e]: 0x80 
    //[8]:adc_clk相位选择；
    //0:不取反；1:取反
    tmp = 0x80;
    PAN312x_Set_OP_Reg(R13E, 1, &tmp);					 
			
    
    //AGC&RSSI相关
    //[0x72][0x06 ~ 0x1d]
    PAN312x_Set_OP_Reg(R206, 24, tmpBuffer);
    //[0x72][0x1e ~ 0x2a]
    PAN312x_Set_OP_Reg(R21E, 13, &tmpBuffer[24]);
    //[0x72][0x31]
    tmp = 0x81;
    PAN312x_Set_OP_Reg(R231, 1, &tmp);
    
    //[0x73][0x3e]修改PLL_VCO_ISEL, 优化相噪
    tmp = 0x2e;//v1.0:0x28,v1.1:0x2e
    PAN312x_Set_OP_Reg(R2BE, 1, &tmp); 
    //[0x73][0x41]修改XTH_HYS_EN，优化相噪
    tmp = 0x00;
    PAN312x_Set_OP_Reg(R2C1, 1, &tmp);
    
    //[0x73][0x53]修改PLL_CP_ISEL，PSHIFT,优化相噪
    tmp = 0x7d;
    PAN312x_Set_OP_Reg(R2D3, 1, &tmp);
    
    //[0x73][0x54]修改PLL_VCO_IBGSEL，IPTATSEL,优化相噪
    tmp = 0xfd;//v1.0:0x7d,v1.1:0xfd
    PAN312x_Set_OP_Reg(R2D4, 1, &tmp);

    //[0x73][0x57]:PA模拟模式 ramp时间常数调节
    //PA_RAMP_RC_TRIM[3:1]
    PAN312x_Get_OP_Reg(R2D7, 1, &tmp);
    tmp &= ~R2D7_PA_RAMP_RC_TRIM_Msk;
    tmp |= (0x06 << 1);
    PAN312x_Set_OP_Reg(R2D7, 1, &tmp);
    
    //[0x73][0x5c],默认值修改
    tmp = 0xff;
    PAN312x_Set_OP_Reg(R2DC, 1, &tmp);
    
    //[0x74][0x16] AGC输入使能
    PAN312x_Get_OP_Reg(R316, 1, &tmp);
    tmp |= R316_REG_AGC_IN_MODE_Msk | (R316_REG_DC_CAL_TRIG_Msk);
    PAN312x_Set_OP_Reg(R316, 1, &tmp);
    
    
    //新增的V1.1
    //[0x72][0x38]
    tmp = 0x71;
    PAN312x_Set_OP_Reg(R238, 1, &tmp);
    
    //[0x72][0x40]
    tmp = 0x86;
    PAN312x_Set_OP_Reg(R240, 1, &tmp);
    
    //DCDC_CAL_EN: [0x73][0x45][5:3] =111b dcdc充电限流控制
    PAN312x_Get_OP_Reg(R2C5, 1, &tmp);
    tmp &= ~R2C5_DCDC_IMAX_Msk;
    tmp |= (0x07 << R2C5_DCDC_IMAX_Pos);
    PAN312x_Set_OP_Reg(R2C5, 1, &tmp);
    
    
    //[0x73][0x44]
    PAN312x_Get_OP_Reg(R2C4, 1, &tmp);
    //DCDC_BUFSEL:[0x73][0x44][7:5] = 000b
    tmp &= ~R2C4_DCDC_BUFSEL_Msk;
    //DCDC_RESSEL:[0x73][0x44][4:2] = 010b
    tmp &= ~R2C4_DCDC_RESSEL_Msk;
    tmp |= (0x02 << R2C4_DCDC_RESSEL_Pos);
    PAN312x_Set_OP_Reg(R2C4, 1, &tmp);
    
    //[0x73][0x48]
    //XTH_AMP_SEL[7]=0,优化DCDC杂散，32M spur，功耗
    PAN312x_Get_OP_Reg(R2C8, 1, &tmp);
    tmp &= ~R2C8_XTH_AMP_SEL_Msk;
    PAN312x_Set_OP_Reg(R2C8, 1, &tmp);
    
    //20250928  tx_setting and rx_setting  time
		//[0x74][0x40],??è??μDT??
//    tmp = 0x02;
//    PAN312x_Set_OP_Reg(R340, 1, &tmp);
//		//[0x74][0x41],??è??μDT??
//    tmp = 0x08;
//    PAN312x_Set_OP_Reg(R341, 1, &tmp);

//		//[0x74][0x43],??è??μDT??
//    tmp = 0x10;
//    PAN312x_Set_OP_Reg(R343, 1, &tmp);
//		//[0x74][0x44],??è??μDT?? 03 to 02,128us to 64us
//    tmp = 0x02;
//    PAN312x_Set_OP_Reg(R344, 1, &tmp);
//		//[0x74][0x45],??è??μDT??
//    tmp = 0x02;
//    PAN312x_Set_OP_Reg(R345, 1, &tmp);
    
}

/**
  * @简介：获取PAN312x的FirwareId
  * @参数：fwid - 固件ID缓冲区
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Get_FwId(uint16_t *fwid)
{
	uint8_t cmd = COMMAND_GET_FWID;
    int ret = __PAN312xCmd_WriteRead(&cmd, 1, fwid, 2);
    return ret == 2 ? PAN312x_OK : ret;
}
/**
  * @简介：寄存器操作
  * @参数：op_reg_flag - 操作标志，参考PAN312x_OpRegFlag_t
  *        addr - 寄存器地址
  *        buf - 寄存器值缓冲区
  *        len - 缓冲区长度
  * @返回值：0-成功，非0-失败
  */
int PAN312x_OpRegister(uint8_t op_reg_flag, uint16_t addr, void* buf, int len)
{
	int ret;
    if(op_reg_flag & OP_REG_FLAG_READ_INFO){
        uint8_t txbuf[3] = {COMMAND_OP_REGISTER, OP_REG_FLAG_READ_INFO, addr};
        ret = __PAN312xCmd_WriteRead(txbuf, 3, buf, 2);
        if(ret == 1) ret = PAN312x_OK;
    } else if(op_reg_flag & OP_REG_FLAG_WRITE){
        uint8_t txbuf[33];
        txbuf[0] = COMMAND_OP_REGISTER;
        txbuf[1] = (op_reg_flag & 0xf0) | ((addr >> 8) & 0x07);
        txbuf[2] = addr;
        memcpy(txbuf + 3, buf, len);
        ret = __PAN312xCmd_Write(txbuf, len + 3);
        if(ret == len + 3) ret = PAN312x_OK;
    } else {
        uint8_t txbuf[4] = {COMMAND_OP_REGISTER, (op_reg_flag & 0xf0) | ((addr >> 8) & 0x07), addr, len};
        ret = __PAN312xCmd_WriteRead(txbuf, 4, buf, len);
        if(ret == len) ret = PAN312x_OK;
    }
    return ret;
}
/**
  * @简介：设置sfr/data值，地址自增
  * @参数：addr - sfr/data地址
  *        buff - 数据缓冲区
  *        len - 数据长度
  * @返回值：实际设置的数据量
  */
int PAN312x_SetDatas(uint8_t addr, const void* buff, int len)
{
	int count = len;
    uint8_t* ptr = (uint8_t*)buff;
    uint8_t adr = addr;
    while(len > 0){
        int tx = len > 30 ? 30 : len;
        int ret = PAN312x_OpRegister(OP_REG_FLAG_INC_ADDR | OP_REG_FLAG_WRITE, adr, ptr, tx);
        if(ret != PAN312x_OK) return ret;
        adr += tx;
        ptr += tx;
        len -= tx;
    }
    return count;
}
/**
  * @简介：设置单个sfr/data数据
  * @参数：addr - sfr/data地址
  *        value - sfr/data数据
  * @返回值：0-成功，非0-失败
  */
int PAN312x_SetData(uint8_t addr, uint8_t value)
{
	int ret = PAN312x_SetDatas(addr, &value, 1);
    return ret == 1 ? PAN312x_OK : ret;
}
/**
  * @简介：获取sfr/data数据，地址自增
  * @参数：addr - sfr/data地址
  *        buff - 数据缓冲区
  *        len - 数据长度
  * @返回值：实际设置的数据量
  */
int PAN312x_GetDatas(uint8_t addr, void* buff, int len)
{
	int count = len;
    uint8_t* ptr = (uint8_t*)buff;
    uint8_t adr = addr;
    while(len > 0){
        int rx = len > 30 ? 30 : len;
        int ret = PAN312x_OpRegister(OP_REG_FLAG_INC_ADDR, adr, ptr, rx);
        if(ret != PAN312x_OK) return ret;
        adr += rx;
        ptr += rx;
        len -= rx;
    }
    return count;
}
/**
  * @简介：获取单个sfr/data数据
  * @参数：addr - sfr/data地址
  * @返回值：成功返回数据值，失败返回负数
  */
int PAN312x_GetData(uint8_t addr)
{
	uint8_t value;
    if(PAN312x_GetDatas(addr, &value, 1) == 1){
        return value;
    }
    return -1;
}
/**
  * @简介：设置xdata数据，地址自增
  * @参数：addr - xdata地址
  *        buff - 数据缓冲区
  *        len - 数据长度
  * @返回值：实际设置的数据量
  */
int PAN312x_SetXdatas(uint16_t addr, const void* buff, int len)
{
	int count = len;
    uint8_t* ptr = (uint8_t*)buff;
    uint16_t adr = addr;
    while(len > 0){
        int tx = len > 30 ? 30 : len;
        int ret = PAN312x_OpRegister(OP_REG_FLAG_INC_ADDR | OP_REG_FLAG_XDATA | OP_REG_FLAG_WRITE, adr, ptr, tx);
        if(ret != PAN312x_OK) return ret;
        adr += tx;
        ptr += tx;
        len -= tx;
    }
    return count;
}
/**
  * @简介：设置单个xdata数据
  * @参数：addr - xdata地址
  *        value - xdata数据
  * @返回值：实际设置的数据量
  */
int PAN312x_SetXdata(uint16_t addr, uint8_t value)
{
	int ret = PAN312x_SetXdatas(addr, &value, 1);
    return ret == 1 ? PAN312x_OK : ret;
}
/**
  * @简介：获取xdata数据，地址自增
  * @参数：addr - xdata地址
  *        buff - 数据缓冲区
  *        len - 缓冲区长度
  * @返回值：实际获取的数据量
  */
int PAN312x_GetXdatas(uint16_t addr, void* buff, int len)
{
	int count = len;
    uint8_t* ptr = (uint8_t*)buff;
    uint16_t adr = addr;
    while(len > 0){
        int rx = len > 30 ? 30 : len;
        int ret = PAN312x_OpRegister(OP_REG_FLAG_INC_ADDR | OP_REG_FLAG_XDATA, adr, ptr, rx);
        if(ret != PAN312x_OK) return ret;
        adr += rx;
        ptr += rx;
        len -= rx;
    }
    return count;
}
/**
  * @简介：获取单个xdata数据
  * @参数：addr - xdata地址
  * @返回值：成功返回数据，失败返回负数
  */
int PAN312x_GetXdata(uint16_t addr)
{
	uint8_t value;
    if(PAN312x_GetXdatas(addr, &value, 1) == 1){
        return value;
    }
    return -1;
}

int PAN312x_GetInfoDatas(uint8_t addr, void* buff, int len)
{
    int count = len;
    uint8_t* ptr = (uint8_t*)buff;
    while(len > 0){
        int ret = PAN312x_OpRegister(OP_REG_FLAG_READ_INFO, addr, ptr, 2);
        if(ret != PAN312x_OK) return ret;
        addr += 1;
        ptr += 2;
        len -= 2;
    }
    return count;
}
int PAN312x_GetInfoData(uint8_t addr)
{
	uint16_t value;
    if(PAN312x_GetInfoDatas(addr, &value, 2) == 2){
        return value;
    }
    return -1;
}
/**
  * @简介：设置PAN312x进入Tx
  * @参数：channel：  信道
  *        condition: 条件标志，参考PAN312xStartCond
  *        tx_len:    发送数据长度
   
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Enter_Tx(uint16_t channel, uint8_t condition, uint16_t tx_len)
{
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R2C4, 1, &tmp);
    tmp &= ~R2C4_TRX_COMATCH_EN_Msk;
    PAN312x_Set_OP_Reg(R2C4, 1, &tmp);
    
	uint8_t txbuf[6] = {
        COMMAND_START_TX,
        channel, channel >> 8,
        condition,
        tx_len, (tx_len >> 8) & 0x1f
    };
    int ret = __PAN312xCmd_Write(txbuf, 6);
    return ret == 6 ? PAN312x_OK : ret;
}

/**
  * @简介：设置PAN312x进入Rx
  * @参数：channel：  信道
  *        condition: 条件标志，参考PAN312xStartCond
  *         rx_len:   接收数据长度
  *                   注意：可变包长帧结构时，该参数设置为0x00
  *                         固定包长帧结构时，该参数需要与发端的数据长度一致
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Enter_Rx(uint16_t channel, uint8_t condition, uint16_t rx_len)
{
	uint8_t txbuf[6] = {
        COMMAND_START_RX,
        channel, channel >> 8,
        condition,
        rx_len, (rx_len >> 8) & 0x1f
    };
    int ret = __PAN312xCmd_Write(txbuf, 6);
    return ret == 6 ? PAN312x_OK : ret;
}
/**
  * @简介：PAN312x发送ACK
  * @参数：无
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Tx_Ack(void)
{
    uint8_t cmd = COMMAND_TX_ACK;
    int ret = __PAN312xCmd_Write(&cmd, 1);
    return ret == 1 ? PAN312x_OK : ret;
}
/**
  * @简介：设置PAN312x进入sleep状态
  * @参数：sleep_mode - 休眠模式，参考PAN312x_SleepMode_t
  *        wake_up_state - 唤醒后进入状态(仅NormalSleep有效)，参考PAN312x_WakeUpState_t
  * @返回值：无
  */
int PAN312x_Enter_Sleep(PAN312xSleepMode sleep_mode, PAN312xWakeUpState wake_up_state)
{
	uint8_t txbuf[2] = {
        COMMAND_GO_SLEEP,
        (sleep_mode == DEEP_SLEEP_MODE ? 0x08 : 0x00) | (wake_up_state & 0x03)
    };
    int ret = PAN312xRaw_Write(txbuf, 2);
    return ret == 2 ? PAN312x_OK : ret;
}
/**
  * @简介：强制进入READY状态，非休眠状态下有效
  * @参数：无
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Enter_Ready(void)
{
	uint8_t cmd = COMMAND_GO_READY;
    int ret = __PAN312xCmd_Write(&cmd, 1);
    return ret == 1 ? PAN312x_OK : ret;
}
/**
  * @简介：设置属性寄存器
  * @参数：group- 寄存器地址
  *        num_value - 缓冲区长度
  *        value - 寄存器值缓冲区
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Set_Property(uint16_t group, uint8_t num_value, const void* value)
{
	uint8_t txbuf[33];
    txbuf[0] = COMMAND_SET_PROPERTY;
    txbuf[1] = group >> 8;
    txbuf[2] = group;
    memcpy(txbuf + 3, value, num_value);
    int ret = __PAN312xCmd_Write(txbuf, num_value + 3);
    return ret == num_value + 3 ? PAN312x_OK : ret;
}
/**
  * @简介：设置1个字节的属性寄存器值
  * @参数：group- 寄存器地址
  *        value - 值
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Set_PropertyB1(uint16_t group, uint8_t value)
{
	int ret = PAN312x_Set_Property(group, 1, &value);
    return ret == 1 ? PAN312x_OK : ret;
}
/**
  * @简介：设置2个字节的属性寄存器值
  * @参数：group- 寄存器地址
  *        value - 值
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Set_PropertyB2(uint16_t group, uint16_t value)
{
	int ret = PAN312x_Set_Property(group, 2, &value);
    return ret == 2 ? PAN312x_OK : ret;
}
/**
  * @简介：设置3个字节的属性寄存器值
  * @参数：group- 寄存器地址
  *        value - 值
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Set_PropertyB3(uint16_t group, uint32_t value)
{
	int ret = PAN312x_Set_Property(group, 3, &value);
    return ret == 2 ? PAN312x_OK : ret;
}
/**
  * @简介：设置4个字节的属性寄存器值
  * @参数：group- 寄存器地址
  *        value - 值
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Set_PropertyB4(uint16_t group, uint32_t value)
{
	int ret = PAN312x_Set_Property(group, 4, &value);
    return ret == 2 ? PAN312x_OK : ret;
}
/**
  * @简介：获取属性寄存器
  * @参数：group- 寄存器地址
  *        num_value - 缓冲区长度
  *        value - 寄存器值缓冲区
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Get_Property(uint16_t group, uint8_t num_value, void *value)
{
	uint8_t txbuf[4] = {
        COMMAND_GET_PROPERTY,
        num_value, group >> 8, group
    };
    int ret = __PAN312xCmd_WriteRead(txbuf, 4, value, num_value);
    return ret == num_value ? PAN312x_OK : ret;
}
/**
  * @简介：获取1个字节的属性寄存器值
  * @参数：group- 寄存器地址
  *        value - 值
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Get_PropertyB1(uint16_t group)
{
	uint8_t value;
    int ret = PAN312x_Get_Property(group, 1, &value);
    return ret == PAN312x_OK ? value : ret;
}
/**
  * @简介：获取2个字节的属性寄存器值
  * @参数：group- 寄存器地址
  *        value - 值
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Get_PropertyB2(uint16_t group)
{
	uint16_t value = 0;
    int ret = PAN312x_Get_Property(group, 2, &value);
    return ret == PAN312x_OK ? value : ret;
}
/**
  * @简介：获取3个字节的属性寄存器值
  * @参数：group- 寄存器地址
  *        value - 值
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Get_PropertyB3(uint16_t group)
{
	uint32_t value = 0;
    int ret = PAN312x_Get_Property(group, 3, &value);
    return ret == PAN312x_OK ? value : ret;
}
/**
  * @简介：获取4个字节的属性寄存器值
  * @参数：group- 寄存器地址
  *        value - 值
  * @返回值：返回寄存器值，注意该函数无法区分是否发生错误
  */
uint32_t PAN312x_Get_PropertyB4(uint16_t group)
{
	uint32_t value;
    PAN312x_Get_Property(group, 4, &value);
    return value;
}

uint8_t PAN312x_Get_ChipState(void)
{
    uint32_t status;
	
	uint8_t cmd = COMMAND_GET_STATUS;
    int ret = __PAN312xCmd_WriteRead(&cmd, 1, &status, 4);
   
    //memcpy(pIrqStatus, &status, 4);
    
    return (uint8_t)((status >> 8) & 0x07);
}
/**
  * @简介：启动DutyCycle
  * @参数：sleep_now: 
            0x00：启动DutyCycle时，发送一包报数据，然后休眠
            0x01：启动DutyCycle时，立即休眠(Sleep)
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Enter_DutyCycle(uint8_t sleep_now)
{
	uint8_t txbuf[2] = {
        COMMAND_DUTY_CYCLE,
        sleep_now ? 0x08 : 0x00
    };
    int ret = sleep_now ? PAN312xRaw_Write(txbuf, 2) : __PAN312xCmd_Write(txbuf, 2);
    return ret == 2 ? PAN312x_OK : ret;
}
/**
  * @简介：退出DutyCycle
  * @参数：无
  * @返回值：无
  */
void PAN312x_Exit_DutyCycle(void)
{
    PAN312x_WaitCtsOk();
    PAN312x_Enter_Ready();
    PAN312x_Flush_TxFifo();
    PAN312x_Reset_Modem();
    PAN312x_WutDisable();
}

/**
  * @简介：获取PAN312x的irq的状态
  * @参数：pIrqStatus：参考PAN312xIrqs;  
  * @返回值：无
  */
int PAN312x_Irq_Get_Status(PAN312xIrqs* pIrqStatus)
{
	uint32_t status;
	
	uint8_t cmd = COMMAND_GET_STATUS;
    int ret = __PAN312xCmd_WriteRead(&cmd, 1, &status, 4);
   
    memcpy(pIrqStatus, &status, 4);
	
	return ret == 4 ? PAN312x_OK : ret;
}
/**
  * @简介：清除PAN312x的所有irq的状态
  * @参数：无; 
  * @返回值：无
  */
int PAN312x_Irq_Clear_AllStatus(void)
{
    uint32_t status = 0xffffffff;
    uint8_t txbuf[5];
    txbuf[0] = COMMAND_CLEAR_STATUS;
    memcpy(txbuf + 1, &status, 4);
    int ret = __PAN312xCmd_Write(txbuf, 5);
    return ret == 5 ? PAN312x_OK : ret;
}
/**
  * @简介：清除PAN312x的irq的状态
  * @参数：pIrqStatus：参考PAN312xIrqs; 
  * @返回值：无
  */
int PAN312x_Irq_Clear_Status(PAN312xIrqs pIrqStatus)
{
	uint32_t status;
    memcpy(&status, &pIrqStatus, 4);
	status &= ~(IRQ_STATUS_FW_STATE | IRQ_STATUS_DUTYCYCLE_FLAG);
    uint8_t txbuf[5];
    txbuf[0] = COMMAND_CLEAR_STATUS;
    memcpy(txbuf + 1, &status, 4);
    int ret = __PAN312xCmd_Write(txbuf, 5);
    return ret == 5 ? PAN312x_OK : ret;
}
/**
  * @简介：清除PAN312x的tx fifo的状态
  * @参数：pIrqStatus：参考PAN312xIrqs; 
  * @返回值：无
  */

#if 0
int PAN312x_Irq_Clear_TxFifo_Status(void)
{
	uint32_t status = IRQ_STATUS_TX_FIFO;
	
	status &= ~(IRQ_STATUS_FW_STATE | IRQ_STATUS_DUTYCYCLE_FLAG);
    uint8_t txbuf[5];
    txbuf[0] = COMMAND_CLEAR_STATUS;
    memcpy(txbuf + 1, &status, 4);
    int ret = __PAN312xCmd_Write(txbuf, 5);
    return ret == 5 ? PAN312x_OK : ret;
}
#else

int PAN312x_Irq_Clear_TxFifo_Status(PAN312xIrqs pIrqStatus)
{
	uint32_t status;
    memcpy(&status, &pIrqStatus, 4);
	
	status &= ~(IRQ_STATUS_FW_STATE | IRQ_STATUS_DUTYCYCLE_FLAG);
    uint8_t txbuf[5];
    txbuf[0] = COMMAND_CLEAR_STATUS;
    memcpy(txbuf + 1, &status, 4);
    int ret = __PAN312xCmd_Write(txbuf, 5);
    return ret == 5 ? PAN312x_OK : ret;
}
#endif
/**
  * @简介：清除PAN312x的rx fifo的状态
  * @参数：无; 
  * @返回值：无
  */
int PAN312x_Irq_Clear_RxFifo_Status(void)
{
	uint32_t status = IRQ_STATUS_RX_FIFO;
	
	status &= ~(IRQ_STATUS_FW_STATE | IRQ_STATUS_DUTYCYCLE_FLAG);
    uint8_t txbuf[5];
    txbuf[0] = COMMAND_CLEAR_STATUS;
    memcpy(txbuf + 1, &status, 4);
    int ret = __PAN312xCmd_Write(txbuf, 5);
    return ret == 5 ? PAN312x_OK : ret;
}
/**
  * @简介：清除PAN312x的rx done的状态
  * @参数：无
  * @返回值：无
  */
int PAN312x_Irq_Clear_RxDone_Status(void)
{
	uint32_t status = IRQ_STATUS_RX_DONE | IRQ_STATUS_RX_FIFO;
	
	status &= ~(IRQ_STATUS_FW_STATE | IRQ_STATUS_DUTYCYCLE_FLAG);
    uint8_t txbuf[5];
    txbuf[0] = COMMAND_CLEAR_STATUS;
    memcpy(txbuf + 1, &status, 4);
    int ret = __PAN312xCmd_Write(txbuf, 5);
    return ret == 5 ? PAN312x_OK : ret;
}
/**
  * @简介：清除PAN312x的rx crc error的状态
  * @参数：无
  * @返回值：无
  */
int PAN312x_Irq_Clear_RxCrcError_Status(void)
{
	uint32_t status = IRQ_STATUS_CRC_ERROR;
	
	status &= ~(IRQ_STATUS_FW_STATE | IRQ_STATUS_DUTYCYCLE_FLAG);
    uint8_t txbuf[5];
    txbuf[0] = COMMAND_CLEAR_STATUS;
    memcpy(txbuf + 1, &status, 4);
    int ret = __PAN312xCmd_Write(txbuf, 5);
    return ret == 5 ? PAN312x_OK : ret;
}
/**
  * @简介：获取PAN312x的GpioIrq 使能的状态
  * @参数：无        
  * @返回值：GpioIrq 使能的状态值
  */
uint32_t PAN312x_Get_GpioIrq_EnableStatus(void)
{
	return PAN312x_Get_PropertyB3(PROPERTY_ADDR_IRQ_ENABLE);
}
/**
  * @简介：使能or失能某个中断映射到Gpio引脚上
  * @参数：status:    
  * @返回值：无
  */
void PAN312x_GpioIrq_EnableStatus(uint32_t status)
{
	PAN312x_Set_PropertyB3(PROPERTY_ADDR_IRQ_ENABLE, status);
}
/**
  * @简介：将PAN312x的中断映射到PAN312x的irq(GPIO8)引脚上
  * @参数：pIrqStatus：参考PAN312xIrqList;
  *         xNewState: 0:enable
  *                    1:disable         
  * @返回值：无
  */
void PAN312x_GpioIrq_Config(PAN312xIrqList xIrq, SFunctionalState xNewState)
{
	uint32_t status = PAN312x_Get_GpioIrq_EnableStatus();
    uint32_t newsts = xNewState ? (status | xIrq) : (status & (~xIrq));
    if(status != newsts){
        PAN312x_GpioIrq_EnableStatus(newsts);
    }
}
/**
  * @简介：设置PAN312x的包过滤控制
  * @参数：epat1: 0: 
  *               1: 
  *        epat2: 0: 
  *               1: 
  *        epat3: 0: 
  *               1: 
  *        inten: 0: 失能node id中断
  *               1: 使能node id中断
  *        reset: 0：node id不匹配时，不丢弃数据，继续接收
                  1：node id不匹配时，丢弃已接收的数据，继续接收
  * @返回值：无
  */
void PAN312x_Set_PacketFilter_Ctrl(uint8_t epat1, uint8_t epat2, uint8_t epat3,uint8_t inten, uint8_t reset)
{
	uint8_t tmp = 0x00;
	tmp |= (inten << 7) | (epat3 << 6) | (epat2 << 5) | (epat1 << 4) | (reset << 3);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_PACKET_FILTER_CTRL, tmp);
}

/**
  * @简介：设置PAN312x的包过滤掩码
  * @参数：pat_mask:
  * @返回值：无
  */
void PAN312x_Set_PacketFilter_Mask(uint32_t pat_mask)
{
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_PACKET_FILTER_MASK, pat_mask);
}
/**
  * @简介：设置PAN312x的包过滤pat1_value
  * @参数： pat1_value:
  * @返回值：无
  */
void PAN312x_Set_PacketFiter_Pat1Value(uint32_t pat1_value)
{
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_PACKET_FILTER_PAT1, pat1_value);
}
/**
  * @简介：设置PAN312x的包过滤pat2_value
  * @参数： pat2_value:
  * @返回值：无
  */
void PAN312x_Set_PacketFiter_Pat2Value(uint32_t pat2_value)
{
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_PACKET_FILTER_PAT2, pat2_value);
}
/**
  * @简介：设置PAN312x的包过滤pat3_value
  * @参数： pat3_value:
  * @返回值：无
  */
void PAN312x_Set_PacketFiter_Pat3Value(uint32_t pat3_value)
{
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_PACKET_FILTER_PAT3, pat3_value);
}
/**
  * @简介：设置PAN312x的NodeId
  * @参数： nodeid_length ： nodeid的长度(最大4bytes)
  *         nodeid_position: 0 nodeid before length
  *                          1 nodeid after length(只针对rx有效)
  * @返回值：无
  */
void PAN312x_Set_NodeId_Config(uint8_t nodeid_length, uint8_t nodeid_position)
{
    uint8_t tmp = (nodeid_length << 2) | (nodeid_position << 1);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_NODE_ID_CONF, tmp);
}
/**
  * @简介：设置PAN312x的NodeId的值
  * @参数： nodeid_value ： nodeid_value的值
  * @返回值：无
  * 备注：
  * 这个只支持如下帧结构：
  * preamble + syncword + node_id + length + data + crc
  */
void PAN312x_Set_Tx_NodeId_Value(uint32_t nodeid_value)
{
    PAN312x_Set_PropertyB4(PROPERTY_ADDR_R11C_REG_NODE_ID_L1, nodeid_value);
}
/**
  * @简介：获取PAN312x接收的NodeId的值
  * @参数： nodeid_value ： nodeid_value的值
  * @返回值：无
  * 备注：
  * 这个只支持如下帧结构：
  * preamble + syncword + node_id + length + data + crc
  */
uint32_t PAN312x_Get_Rx_NodeId_Value(void)
{
    return PAN312x_Get_PropertyB4(PROPERTY_ADDR_RX_NODE_ID);
}

/**
  * @简介：设置PAN312x的TxPacket
  * @参数：crc_state：  0 失能crc
  *                     1 使能crc
  *        packet_type: 0 固定包长
  *                     1 可变包长
  * @返回值：无
  */

#if 0
void PAN312x_Set_TxPacket_Config(uint8_t crc_state, uint8_t packet_type)
{
	uint8_t tmp = (crc_state << 5)  | (packet_type);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_TXPKT_CONF, tmp);
}
#else
void PAN312x_Set_TxPacket_Config(PAN312xTxPacketConfig TxPacketConfig)
{
	
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_TXPKT_CONF, TxPacketConfig);
}
#endif
/**
  * @简介：设置PAN312x的TxPacket Number
  * @参数：number: 
  * @返回值：无
  */
void PAN312x_Set_TxPacket_ExtraNumber(uint8_t number)
{
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_TX_REPEAT_TIMES, number);
}
/**
  * @简介：设置PAN312x的TxPacket Gap
  * @参数：gap:(单位：1us))
  * @返回值：无
  */
void PAN312x_Set_TxPacket_Gap(uint16_t gap)
{
	PAN312x_Set_PropertyB2(PROPERTY_ADDR_TX_PACKET_GAP, gap);
}
/**
  * @简介：设置PAN312x的退出当前状态后的状态
  * @参数：cond：参考 PAN312x_ExitStateCond_t
  *        state：参考 PAN312x_State_t
  * @返回值：无
  */
void PAN312x_Set_ExitState(PAN312xExitStateCond cond, PAN312xState state)
{
	PAN312x_Set_PropertyB1(cond, state & 0x03);
}
/**
  * @简介：获取PAN312x的退出当前状态后的状态
  * @参数：cond：参考 PAN312x_ExitStateCond_t
  * @返回值：获取到的状态
  */
PAN312xState PAN312x_Get_ExitState(PAN312xExitStateCond cond)
{
	return (PAN312xState)PAN312x_Get_PropertyB1(cond);
}
/**
  * @简介：PAN312x Tx Ok后，rf的退出状态
  * @参数：state：参考PAN312x_State_t
  * @返回值：无
  */
void PAN312x_Set_TxOk_ExitState(PAN312xState state)
{
	PAN312x_Set_ExitState(EXIT_STATE_COND_TX_OK, state);
}
/**
  * @简介：设置PAN312x的RxPacket
  * @参数：crc_host:            0: 由mcu来自己计算crc
  *                             1: 由PAN312x固件来计算crc，同时需要使能crc，失能硬件计算crc
  *        crc_hardware:        0: 失能硬件计算crc
  *                             1: 使能引荐计算crc，同时需要使能crc
  *        crc_state:           0: 失能crc
  *                             1: 使能crc
  *        read_pl_by_cmd:
  *        length_in_payload:
  *        rx_packet_type:      0:固定包长 
  *                             1:可变包长 
  *                 
  * @返回值：接收的数据长度
  */
#if 0
void PAN312x_Set_RxPacket_Config(uint8_t crc_host, uint8_t crc_hardware, uint8_t crc_state, uint8_t read_pl_by_cmd, uint8_t length_in_payload, uint8_t rx_packet_type)
{
	uint8_t tmp = (crc_host << 7) | (crc_hardware << 6) | (crc_state << 5) | (read_pl_by_cmd << 4) | (length_in_payload << 1) | (rx_packet_type);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_RXPKT_CONF, tmp);
}
#else
void PAN312x_Set_RxPacket_Config(PAN312xRxPacketConfig RxPacketConfig)
{
	
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_RXPKT_CONF, RxPacketConfig);
}

#endif
/**
  * @简介：设置PAN312x Rx Timeout时间
  * @参数：rx_time_out：单位(us)
  * @返回值：无
  */
void PAN312x_Set_RxTimeOut(uint32_t rx_time_out)
{
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_RX_TIMEOUT, rx_time_out);
}
/**
  * @简介：PAN312x Rx Timeout后，从rx退出后的状态
  * @参数：state：参考PAN312x_State_t
  * @返回值：无
  */
void PAN312x_Set_RxTimeout_ExitState(PAN312xState state)
{
	PAN312x_Set_ExitState(EXIT_STATE_COND_RX_TIMEOUT, state);
}
/**
  * @简介：PAN312x Rx Invalid(CRC ERROR)后，rf的退出状态
  * @参数：state：参考PAN312x_State_t
  * @返回值：无
  */
void PAN312x_Set_RxInvalid_ExitState(PAN312xState state)
{
    PAN312x_Set_ExitState(EXIT_STATE_COND_RX_INVALID, state);
}
/**
  * @简介：PAN312x Rx Valid(RX DONE)后，rf的退出状态
  * @参数：state：参考PAN312x_State_t
  * @返回值：无
  */
void PAN312x_Set_RxValid_ExitState(PAN312xState state)
{
    PAN312x_Set_ExitState(EXIT_STATE_COND_RX_VALID, state);
}
/**
  * @简介：设置PAN312x Ack Timeout时间
  * @参数：ack_time_out: 单位(us)
  * @返回值：无
  */
void PAN312x_Set_AckTimeOut(uint32_t ack_time_out)
{
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_ACK_TIMEOUT, ack_time_out);
}
/**
  * @简介：PAN312x Ack Valid后，rf的退出状态
  * @参数：state：参考PAN312x_State_t
  * @返回值：无
  * 备注：tx端发送完数据，转为rx，如果一直未接收到ack，直至AckTimeout后，rf退出后的状态
  */
void PAN312x_Set_AckTimeout_ExitState(PAN312xState state)
{
    PAN312x_Set_ExitState(EXIT_STATE_COND_ACK_TIMEOUT, state);
}
/**
  * @简介：单位：10us
  * @参数：state：参考PAN312x_State_t
  * @返回值：无
  * 备注：
  */
void PAN312x_Set_AckTxDelay1(uint8_t delay1)
{
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_ACK_TX_DELAY1, delay1);
}
/**
  * @简介：单位：1us
  * @参数：delay2
  * @返回值：无
  * 备注：
  */
void PAN312x_Set_AckTxDelay2(uint8_t delay2)
{
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_ACK_TX_DELAY2, delay2);
}
/**
  * @简介：设置DutyCycle基准时间
  * @参数：BaseTime
  * @返回值：无
  * 备注：最小时间62.5us
  */
void PAN312x_Set_BaseDutyCycleTime(uint32_t BaseTime)
{
    PAN312x_Set_PropertyB3(PROPERTY_ADDR_DUTY_CYCLE_BASE, BaseTime);
}

/**
  * @简介：设置PAN312x 系统控制
  * @参数：ctrl：参考PAN312x_SysCtrl_t
  * @返回值：无
  */
void PAN312x_System_Ctrl(PAN312xSysCtrl ctrl)
{
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_SYS_CTRL0, ctrl);
}
/**
  * @简介：获取PAN312x的接收数据长度
  * @参数：无
  * @返回值：接收的数据长度
  */
uint16_t PAN312x_Get_Rx_Length(void)
{	
	return PAN312x_Get_PropertyB2(PROPERTY_ADDR_RX_LENGTH_IN_PACKET);
	
}
uint16_t PAN312x_Get_RxLengthInPacket(void)
{
    return PAN312x_Get_PropertyB2(PROPERTY_ADDR_RX_LENGTH_IN_PACKET);
}
uint16_t PAN312x_Get_RxLengthInFifo(void)
{
    return PAN312x_Get_PropertyB2(PROPERTY_ADDR_RX_LENGTH_IN_FIFO);
}
/**
  * @简介：PAN312x  向FIFO写数据
  * @参数：uint8_t *buffer,数组指针 uint8_t size长度
  * @返回值：无
  */
void PAN312x_Write_Fifo(const void *buffer, uint8_t size )
{
	if(size == 0){
		return;
	}
	PAN312xReg_Write(0x01, buffer, size);
}
/**
  * @简介：PAN312x  向FIFO读数据
  * @参数：uint8_t *buffer,数组指针 uint8_t size长度
  * @返回值：uint8_t *buffer 存储读取内容
  */
void PAN312x_Read_Fifo( uint8_t *buffer, uint8_t size )
{
    if(size == 0){
        return;
    }
    PAN312xReg_Read(0x01, buffer, size);
}
/**
  * @简介：PAN312x通过命令获取SPI接收数据，固件计算CRC时必须使用该接口
  * @参数：ubuf - 数据缓冲区
  *        len - 缓冲区长度
  * @返回值：0-成功，非0-失败
  */
int PAN312x_Get_RxDataByCmd(void *data, uint8_t length)
{
    uint8_t cmd = COMMAND_GET_RXDATA;
    int ret = __PAN312xCmd_WriteRead(&cmd, 1, data, length);
    return ret == length ? PAN312x_OK : ret;
}

/**
  * @简介：设置PAN312x的可变包长length为几个bytes
  * @参数：number_byte:
  *         0: 1 bytes
  *         1: 2 bytes
  * @返回值: 无
  */
void PAN312x_SetLengthFiled(uint8_t number_byte)
{
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R11B, 1, &tmp);
    
    tmp &= ~R11B_REG_VIA_LENGTH_LEN_Msk;
    tmp |= (number_byte << 7);
    PAN312x_Set_OP_Reg(R11B, 1, &tmp);
}
/**
  * @简介：设置PAN312x的可变包长lengthField的大小端
  * @参数：number_byte:
  *         0: 小端
  *         1: 大端
  * @返回值: 无
  */
void PAN312x_SetLengthFiledEndian(uint8_t endian)
{
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R12B, 1, &tmp);
    
    tmp &= ~R12B_REG_VIA_LEN_ENDIAN_Msk;
    tmp |= (endian << 5);
    PAN312x_Set_OP_Reg(R12B, 1, &tmp);
}

/**
  * @简介：设置PAN312x的Payload Manchester mode
  * @参数：mode:参考PAN312x_MANCHESTER_Mode_t
  * @返回值：无
  */
void PAN312x_Set_PayloadManchesterMode(PAN312xManchesterMode mode)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R11A);
	tmp &= ~PROPERTY_MSK_R11A_REG_PL_MAN_MODE;
	tmp |= (mode << 4);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R11A, tmp);
}
/**
  * @简介：使能PAN312x的Payload Manchester
  * @参数：无
  * @返回值：无
  */
void PAN312x_PayloadManchesterEnable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	tmp |= PROPERTY_MSK_R12E_FIELD1_MAN_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
}
/**
  * @简介：失能PAN312x的Payload Manchester
  * @参数：无
  * @返回值：无
  */
void PAN312x_PayloadManchesterDisable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	tmp &= ~PROPERTY_MSK_R12E_FIELD1_MAN_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
}
/**
  * @简介：设置PAN312x的Payload Msb First
  * @参数：无
  * @返回值：无
  */
void PAN312x_Set_Payload_MsbFirst(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	tmp &= ~PROPERTY_MSK_R10D_REG_PAYLOAD_ENDIAN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
	
}
/**
  * @简介：设置PAN312x的Payload Lsb First
  * @参数：无
  * @返回值：无
  */
void PAN312x_Set_Payload_LsbFirst(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	tmp |= PROPERTY_MSK_R10D_REG_PAYLOAD_ENDIAN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
}
/**
  * @简介：使能PAN312x的Whitening
  * @参数：无
  * @返回值：无
  */
void PAN312x_Whitening_Enable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	tmp |= PROPERTY_MSK_R12E_FIELD1_WHITE_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
	
}
/**
  * @简介：失能PAN312x的Whitening
  * @参数：无
  * @返回值：无
  */
void PAN312x_Whitening_Disable(void)
{	
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	tmp &= ~PROPERTY_MSK_R12E_FIELD1_WHITE_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
}
/**
  * @简介：使能PAN312x的PN9IBM扰码模式
  * @参数：无
  * @返回值：无
  */
void PAN312x_Whitening_PN9IBM_Enable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12B);
	tmp |= PROPERTY_MSK_R12B_REG_WHITEN_PN9_SEL;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12B, tmp);
}
/**
  * @简介：失能PAN312x的PN9IBM扰码模式
  * @参数：无
  * @返回值：无
  */
void PAN312x_Whitening_PN9IBM_Disable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12B);
	tmp &= ~PROPERTY_MSK_R12B_REG_WHITEN_PN9_SEL;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12B, tmp);
}
/**
  * @简介：设置PAN312x的白化计算复位
  * @参数：无
  * @返回值：无
  */
void PAN312x_Whitening_Cal_Reset(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	tmp |= PROPERTY_MSK_R12E_FIELD1_WHITE_SET;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
}
/**
  * @简介：设置PAN312x的白化计算不复位
  * @参数：无
  * @返回值：无
  */
void PAN312x_Whitening_Cal_NoReset(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	tmp &= ~PROPERTY_MSK_R12E_FIELD1_WHITE_SET;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
}
/**
  * @简介：设置PAN312x的白化多项式长度
  * @参数：length
  * @返回值：无
  */
void PAN312x_Set_Whitening_Length(uint8_t length)
{
    uint8_t tmp;
    if(length > 15){
        return;
    }
	
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R11A);
	tmp &= ~PROPERTY_MSK_R11A_REG_WHITEN_LENGTH;
	tmp |= (length & 0x0f);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R11A, tmp);
}
/**
  * @简介：设置PAN312x的白化输出序列模式
  * @参数：mode:
  *        0:白化输出序列从第一个序列开始
  *        1:白化输出序列从第二个序列开始
  * @返回值：无
  */
void PAN312x_Set_Whitening_Mode(uint8_t mode)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R116);
	tmp &= ~PROPERTY_MSK_R116_REG_WHITEN_SEL;
	tmp |= (mode << 3);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R116, tmp);
}
/**
  * @简介：设置PAN312x的白化初始值
  * @参数：seed：白化初始值
  * @返回值：无
  */
void PAN312x_Set_Whitening_Seed(uint16_t seed)
{
	PAN312x_Set_PropertyB2(PROPERTY_ADDR_R118, seed);
}
/**
  * @简介：设置PAN312x的白化与或输入bit和输出bit
  * @参数：xor1_bit:
  *        xor2_bit:
  *        output_bit
  *        example：
  *             xor1_bit  |  xor2_bit  | output_bit
  *         PN6:     2    |      1     |    6
  * @返回值：无
  */
void PAN312x_Set_Whitening_BitSel(uint8_t xor1_bit, uint8_t xor2_bit, uint8_t output_bit)
{
    uint8_t tmp;
	if((xor1_bit > 15) || (xor2_bit > 15) || (output_bit > 15)){
		return;
	}
	tmp = xor1_bit | (xor2_bit << 4);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R117, tmp);
	
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R116);
	tmp &= ~PROPERTY_MSK_R116_REG_WHITEN_OUT_SEL;
	tmp |= (output_bit << 4);
	
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R116, tmp);
}
/**
  * @简介：设置PAN312x的payload 的白化类型
  * @参数：WhiteningPattern
  *         typedef enum{
  *             WHITENING_DISABLE      = 0,
  *             WHITENING_PN6          = 1,
  *             WHITENING_PN7          = 2,
  *             WHITENING_PN9          = 3,
  *             WHITENING_PN9_IBM      = 4,
  *             WHITENING_IEEE_802154g = 5,
  *             WHITENING_PN9_CCITT    = 6,
  *             WHITENING_PN11         = 7,
  *             WHITENING_PN13         = 8,
  *             WHITENING_PN15         = 9
  *         }PAN312xWhiteningPattern;
  * @返回值：无
  */
void PAN312x_Set_Payload_Whitening_Pattern(PAN312xWhiteningPattern WhiteningPattern)
{
    if(WhiteningPattern == WHITENING_DISABLE){
        PAN312x_Whitening_Disable();
        PAN312x_Whitening_PN9IBM_Disable();
        return;
    }else{
        PAN312x_Whitening_Enable();
    }
    PAN312x_Whitening_Cal_Reset();
    PAN312x_Set_Whitening_Mode(0);
    
    if(WhiteningPattern == WHITENING_PN6){
        PAN312x_Set_Whitening_Length(6);
        PAN312x_Set_Whitening_BitSel(2,1,6);
        PAN312x_Set_Whitening_Mode(0);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Disable();
    }else if(WhiteningPattern == WHITENING_PN7){
        PAN312x_Set_Whitening_Length(7);
        PAN312x_Set_Whitening_BitSel(5,1,1);
        PAN312x_Set_Whitening_Mode(0);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Disable();
    }else if(WhiteningPattern == WHITENING_PN9){
        PAN312x_Set_Whitening_Length(9);
        PAN312x_Set_Whitening_BitSel(6,1,9);
        PAN312x_Set_Whitening_Mode(0);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Disable();
    }else if(WhiteningPattern == WHITENING_PN9_IBM){
        PAN312x_Set_Whitening_Length(9);
        PAN312x_Set_Whitening_BitSel(6,1,9);
        PAN312x_Set_Whitening_Mode(1);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Enable();
    }else if(WhiteningPattern == WHITENING_IEEE_802154g){
        PAN312x_Set_Whitening_Length(9);
        PAN312x_Set_Whitening_BitSel(6,1,9);
        PAN312x_Set_Whitening_Mode(1);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Disable();
    }else if(WhiteningPattern == WHITENING_PN9_CCITT){
        PAN312x_Set_Whitening_Length(9);
        PAN312x_Set_Whitening_BitSel(6,1,1);
        PAN312x_Set_Whitening_Mode(0);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Disable();
    }else if(WhiteningPattern == WHITENING_PN11){ 
        PAN312x_Set_Whitening_Length(11);
        PAN312x_Set_Whitening_BitSel(3,1,11);
        PAN312x_Set_Whitening_Mode(0);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Disable();
    }else if(WhiteningPattern == WHITENING_PN13){
        uint8_t tmp;
        PAN312x_Get_OP_Reg(R11A, 1, &tmp);
        tmp &= ~R11A_REG_WHITEN_PN13_SEL_Msk;
        tmp |= R11A_REG_WHITEN_PN13_SEL_Msk;
        PAN312x_Set_OP_Reg(R11A, 1, &tmp);
        PAN312x_Set_Whitening_Length(13);
        PAN312x_Set_Whitening_BitSel(4,5,13);
        PAN312x_Set_Whitening_Mode(0);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Disable();
    }else if(WhiteningPattern == WHITENING_PN15){
        PAN312x_Set_Whitening_Length(15);
        PAN312x_Set_Whitening_BitSel(2,1,15);
        PAN312x_Set_Whitening_Mode(0);
        PAN312x_Set_Whitening_Seed(0xffff);
        PAN312x_Whitening_PN9IBM_Disable();
    }
}
/**
  * @简介：设置PAN312x的CrcMode
  * @参数：CrcMode
  *        0: crc-8
  *        1: crc-16
  *        2: crc-24
  *        3: crc-32 
  * @返回值：无
  */
void PAN312x_Set_CrcMode(PAN312xCrcMode CrcMode)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R116);
	tmp &= ~PROPERTY_MSK_R116_REG_CRC_MODE;
    tmp |= CrcMode;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R116, tmp);
}
/**
  * @简介：设置PAN312x的CrcSeed
  * @参数：CrcSeed
  * @返回值：无
  */
void PAN312x_Set_CrcSeed(uint32_t CrcSeed)
{
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_R112, CrcSeed);
}
/**
  * @简介：设置PAN312x的crc多项式
  * @参数：CrcPolynomial
  * @返回值：无
  */
void PAN312x_Set_CrcPolynomial(uint32_t CrcPolynomial)
{
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_R10E, CrcPolynomial);
}
/**
  * @简介：设置PAN312x的crc invert(CRC结果是否取反)
  * @参数：xNewState
  *        0: 不取反
  *        1: 取反
  * @返回值：无
  */
void PAN312x_Set_CrcInvert(SFunctionalState xNewState)
{
	uint8_t tmp;
	
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R116);
	
	if(xNewState == S_ENABLE) {
		tmp |= PROPERTY_MSK_R116_REG_CRC_NOT_SEL;
	}
	else{
		tmp &= ~PROPERTY_MSK_R116_REG_CRC_NOT_SEL;
	}
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R116, tmp);
		
}
/**
  * @简介：设置PAN312x的大小端
  * @参数：xNewState
  * @返回值：无
  */
//uint8_t tmp_test;
void PAN312x_Set_CrcEndian(SFunctionalState xNewState)
{
	uint8_t tmp;
	
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	
	if(xNewState == S_ENABLE) {
		tmp |= PROPERTY_MSK_R10D_REG_CRC_ENDIAN;
	}
	else{
		tmp &= ~PROPERTY_MSK_R10D_REG_CRC_ENDIAN;
	}
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
	
//	tmp_test = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
//	
//	PAN312x_Get_OP_Reg(R10D, 1, &tmp_test);	
}
/**
  * @简介：使能PAN312x的crc
  * @参数：无
  * @返回值：无
  */
void PAN312x_Crc_Enable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	tmp |= PROPERTY_MSK_R12E_FIELD1_CRC_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
}
/**
  * @简介：失能PAN312x的crc
  * @参数：无
  * @返回值：无
  */
void PAN312x_Crc_Disable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	tmp &= ~PROPERTY_MSK_R12E_FIELD1_CRC_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
}
/**
  * @简介：设置PAN312x的crc
  * @参数：xNewState
  *         0：帧结构中没有crc字段
  *         1：帧结构中插入crc字段
  * @返回值：无
  */
void PAN312x_CrcInsertSelect(SFunctionalState xNewState)
{
	uint8_t tmp;
	
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12E);
	
	if(xNewState == S_ENABLE) {
		tmp |= PROPERTY_MSK_R12E_FIELD1_CRC_IN;
	}
	else{
		tmp &= ~PROPERTY_MSK_R12E_FIELD1_CRC_IN;
	}
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12E, tmp);
}
/**
  * @简介：将整个CRC部分的高低顺序倒过来
  * @参数：CrcBitOrder:参考PAN312xCrcBitOrder
  * @返回值：无
  */
void PAN312x_Set_CrcBitOrder(PAN312xCrcBitOrder CrcBitOrder)
{
	uint8_t tmp;
	
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	
	if(CrcBitOrder == CRC_BIT_ORDER_MSB_FIRST) {
		tmp &= ~PROPERTY_MSK_R10D_REG_CRC_ENDIAN;
		
	}else if(CrcBitOrder == CRC_BIT_ORDER_LSB_FIRST){
		tmp |= PROPERTY_MSK_R10D_REG_CRC_ENDIAN;
	}
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
}
/**
  * @简介：将整个CRC将两个Byte的位置倒过来，但是不改变每个Byte里面的Bit的顺序
  * @参数：CrcByteSwap:参考PAN312xCrcByteSwap
  * @返回值：无
  */
void PAN312x_Set_CrcByteSwap(PAN312xCrcByteSwap CrcByteSwap)
{
	uint8_t tmp;
	
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R12B);
	
	if(CrcByteSwap == CRC_BIT_ORDER_MSB_FIRST) {
		tmp &= ~PROPERTY_MSK_R12B_CRC_BYTE_ENDIAN;
		
	}else if(CrcByteSwap == CRC_BIT_ORDER_LSB_FIRST){
		tmp |= PROPERTY_MSK_R12B_CRC_BYTE_ENDIAN;
	}
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R12B, tmp);
}
/**
  * @简介：设置PAN312x的crc
  * @参数：CrcIndex
  *        CrcSeed
  *        0: CRC8：X8+X2+X+1 (poly:0x07)
  *        1: CRC16：X16+X14+X12+X11+X9+X8+X7+X4+X+1 (poly:0x5b93)
  *        2: CRC16：X16+X15+X12+X7+X6+X4+X3+1 (poly:0x90d9)
  *        3: CRC16：X16+X15+X2+1 (poly:0x8005)
  *        4: CRC16：X16+X12+X5+1 (poly:0x1021) 802.15.4g
  *        5: CRC16：X16+X13+X12+X11+X10+X8+X6+X5+X2+1 (poly:0x3d65)
  *        6: CRC24：X24+X23+X18+X17+X14+X11+X10+X7+X6+X5+X4+X3+X+1 (poly 0x864cfa)
  *        7: CRC32：X32+X30+X29+X28+X26+X20+X19+X17+X16+X15+X11+X10+X7+X6+X4+X2+X1+1 (poly 0x741b8cd7)
  *        8: CRC32：X32+X26+X23+X22+X16+X12+X11+X10+X8+X7+X5+X4+X2+X1+1 (poly 0x04c11db7) 802.15.4g
  *        9: CRC32：X32+X28+X27+X26+X25+X23+X22+X20+X19+X18+X14+X13+X11+X10+X9+X8+X6+1 (poly 0x1edc6f41)
  * @返回值：无
  */
void PAN312x_Set_Crc(uint8_t CrcIndex, uint32_t CrcSeed)
{
	uint32_t CrcPolynomial;
	//帧结构中插入crc字段
    PAN312x_CrcInsertSelect(S_ENABLE);
	//crc 使能
	PAN312x_Crc_Enable();

	//CrcSeed
	PAN312x_Set_CrcSeed(CrcSeed);
	
	//crc endian: big endian
	PAN312x_Set_CrcEndian(S_DISABLE);
	//crc invert：crc结果是否取反
	PAN312x_Set_CrcInvert(S_DISABLE);


	
	switch(CrcIndex){
		case 0x00:
			PAN312x_Set_CrcMode(CRC_MODE_8_BIT);
			CrcPolynomial = 0x00000007;
			break;
		case 0x01:
			PAN312x_Set_CrcMode(CRC_MODE_16_BIT);
			CrcPolynomial = 0x00005b93;
			break;
		case 0x02:
			PAN312x_Set_CrcMode(CRC_MODE_16_BIT);
			CrcPolynomial = 0x000090d9;
			break;
		case 0x03:
			PAN312x_Set_CrcMode(CRC_MODE_16_BIT);
			CrcPolynomial = 0x00008005;
			break;
		case 0x04:
			PAN312x_Set_CrcMode(CRC_MODE_16_BIT);
			CrcPolynomial = 0x00001021;
			break;
		case 0x05:
			PAN312x_Set_CrcMode(CRC_MODE_16_BIT);
			CrcPolynomial = 0x00003d65;
			break;
		case 0x06:
			PAN312x_Set_CrcMode(CRC_MODE_24_BIT);
			CrcPolynomial = 0x00864cfa;
			break;
		case 0x07:
			PAN312x_Set_CrcMode(CRC_MODE_32_BIT);
			CrcPolynomial = 0x741b8cd7;
			break;
		case 0x08:
			PAN312x_Set_CrcMode(CRC_MODE_32_BIT);
			CrcPolynomial = 0x04c11db7;
			break;
		case 0x09:
			PAN312x_Set_CrcMode(CRC_MODE_32_BIT);
			CrcPolynomial = 0x1edc6f41;
			break;
		default:
			break;		
	}
	PAN312x_Set_CrcPolynomial(CrcPolynomial);
}
/**
  * @简介：设置PAN312x的SyncWord Pattern
  * @参数：Syncwords
  *        SyncLength
  * @返回值：无
  */
void PAN312x_Set_SyncWordPattern(uint32_t Syncwords, uint8_t SyncWordLength)
{
	uint8_t tmp;
	
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	tmp &= ~PROPERTY_MSK_R10D_REG_SYNC_LEN;
	tmp |= (SyncWordLength << 0);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
    
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_R189, Syncwords);
}
/**
  * @简介：设置PAN312x的SyncWord Length
  * @参数：SyncWordLength
  * @返回值：无
  */
void PAN312x_Set_SyncWordLength(uint8_t SyncWordLength)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	tmp &= ~PROPERTY_MSK_R10D_REG_SYNC_LEN;
	tmp |= (SyncWordLength << 0);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
}
/**
  * @简介：设置PAN312x的Syncword Manchester编码
  * @参数：PreambleManchesterMode：
  *        0: 0->01 
  *        1: 0->10
  * @返回值：无
  */
void PAN312x_Set_SyncwordManchesterMode(PAN312xManchesterMode SyncwordManchesterMode)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	tmp &= ~PROPERTY_MSK_R10D_REG_SYNC_MAN_MODE;
	tmp |= (SyncwordManchesterMode << 4);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
}
/**
  * @简介：使能PAN312x的Syncword Manchester编码
  * @参数：无
  * @返回值：无
  */
void PAN312x_SyncwordManchesterEnable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	tmp |= PROPERTY_MSK_R10D_REG_SYNC_MAN_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
}
/**
  * @简介：使能PAN312x的Syncword Manchester编码
  * @参数：无
  * @返回值：无
  */
void PAN312x_SyncwordManchesterDisable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10D);
	tmp &= ~PROPERTY_MSK_R10D_REG_SYNC_MAN_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10D, tmp);
}
/**
  * @简介：设置PAN312x的Preamble Manchester编码
  * @参数：PreambleManchesterMode：
  *        0: 0->01 
  *        1: 0->10
  * @返回值：无
  */
void PAN312x_Set_PreambleManchesterMode(PAN312xManchesterMode PreambleManchesterMode)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp &=  ~PROPERTY_MSK_R107_REG_PRE_MAN_MODE;
	tmp |= (PreambleManchesterMode << 1);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：使能PAN312x的Preamble Manchester编码
  * @参数：无
  * @返回值：无
  */
void PAN312x_PreambleManchesterEnable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp |= PROPERTY_MSK_R107_REG_PRE_MAN_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
		
}
/**
  * @简介：失能PAN312x的Preamble Manchester编码
  * @参数：无
  * @返回值：无
  */
void PAN312x_PreambleManchesterDisable(void)
{	
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp &= ~PROPERTY_MSK_R107_REG_PRE_MAN_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
		
}
/**
  * @简介：设置PAN312x的Preamble Pattern
  * @参数：PreamblePattern
  *        0: non standard 
  *        1: 0101
  *        2: 1010(default)
  * @返回值：无
  */
void PAN312x_Set_PreamblePattern(uint8_t PreamblePattern)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp &=  ~PROPERTY_MSK_R107_REG_PRE_SEL;
	tmp |= (PreamblePattern << 2);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：设置PAN312x的Preamble Endian
  * @参数：PreambleEndian
  *        0: big endian
  *        1: little endian
  * @返回值：无
  */
void PAN312x_Set_PreambleEndian(uint8_t PreambleEndian)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp &=  ~PROPERTY_MSK_R107_REG_PRE_BIT_MODE;
	tmp |= (PreambleEndian << 4);
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：设置PAN312x的Preamble 长度
  * @参数：PreambleLength:preamble的长度
  * @返回值：无
  */
void PAN312x_Set_PreambleLength(uint8_t PreambleLength)
{
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R10C, PreambleLength);
}
/**
  * @简介：获取PAN312x的Preamble长度
  * @参数：无
  * @返回值：Preamble的长度
  */
uint8_t PAN312x_Get_PreambleLength(void)
{
	return PAN312x_Get_PropertyB1(PROPERTY_ADDR_R10C);
}
/**
  * @简介：设置PAN312x的非标准Preamble Pattern
  * @参数：PreamblePattern：
  *        PreambleLength：
  * @返回值：无
  */
void PAN312x_Set_NonStandardPreamblePattern(uint32_t PreamblePattern)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp &= PROPERTY_MSK_R107_REG_PRE_SEL;
	if(tmp != 0x00){
		return;
	}
	PAN312x_Set_PropertyB4(PROPERTY_ADDR_R108, PreamblePattern);
}
/**
  * @简介：获取PAN312x的非标准Preamble Pattern
  * @参数：无
  * @返回值：非标准Preamble Pattern值
  */
uint32_t PAN312x_Get_NonStandardPreamblePattern(void)
{
	return PAN312x_Get_PropertyB4(PROPERTY_ADDR_R108);
}

/**
  * @简介：设置PAN312x的tx deviation
  * @参数：tx_deviation：(单位hz)
  * @返回值：无
  */
void PAN312x_Set_Tx_Deviation(uint32_t tx_deviation)
{
    int tmp;


    if(tx_deviation == 1000000){ 
        tmp = 255;
        PAN312x_Set_PropertyB1(PROPERTY_ADDR_R142, tmp);
        tmp = 128;
        PAN312x_Set_PropertyB2(PROPERTY_ADDR_R15A, tmp);
    }else if((tx_deviation > 2400) &&(tx_deviation <= 500000)){
        tmp = 0x80;
        PAN312x_Set_PropertyB1(PROPERTY_ADDR_R142, tmp);
        tmp = (int)(tx_deviation * 256.0 / 500000);
        if(tmp > 511){
            tmp = 511;
        }
        PAN312x_Set_PropertyB2(PROPERTY_ADDR_R15A, tmp);
    }else if((tx_deviation >= 2400) &&(tx_deviation <= 500)){
        //[0x70][0x42]配置fsk_dev,当deviation小于2.4k以后，此时需要按比例修改fsk_dev配置
        tmp = tx_deviation * 128 / 2400;
        PAN312x_Set_PropertyB1(PROPERTY_ADDR_R142,tmp);
        tmp = 1;
        PAN312x_Set_PropertyB2(PROPERTY_ADDR_R15A,tmp);
    }
}
/**
  * @简介：设置PAN312x的rx deviation h 小于或等于1的配置
  * @参数：rx_dev
  * @返回值：无
  */
void PAN312x_Set_Rx_Deviation_H_BelowOne(uint16_t rx_deviation_tmp)
{
    uint8_t tmp;
    uint8_t tmpBuffer[2];
    //[0x70][0x46]: reg_rx_tr_dev_outer_l
    //[0x70][0x47][3:0]: reg_rx_tr_dev_outer_h
    tmpBuffer[0] = (uint8_t)rx_deviation_tmp;
    tmpBuffer[1] = (uint8_t)((rx_deviation_tmp >> 8) & R147_REG_RX_TR_DEV_OUTER_H_Msk);
    PAN312x_Set_OP_Reg(R146, 2, tmpBuffer);
    
    
    //[0x70][0x3d][7:0]:reg_fltr_dev_l
    //[0x70][0x3e][0]: reg_fltr_dev_h
    tmpBuffer[0] = 0x00;
    PAN312x_Get_OP_Reg(R13E, 1, &tmp);
    tmp &= ~R13E_REG_FLTR_DEV_H_Msk;
    tmpBuffer[1] = tmp;
    PAN312x_Set_OP_Reg(R13D, 2, tmpBuffer);
    
    
    //[0x70][0x4b][6]:high_dev_decimat_en
    PAN312x_Get_OP_Reg(R14B, 1, &tmp);
    tmp &= ~R14B_HIGH_DEV_DECIMAT_EN_Msk;
    PAN312x_Set_OP_Reg(R14B, 1, &tmp);
    
    //[0x72][0x52][6]:decimat_last_manu_en
    PAN312x_Get_OP_Reg(R252, 1, &tmp);
    tmp &= ~R252_DECIMAT_LAST_MANU_EN_Msk;
    PAN312x_Set_OP_Reg(R252, 1, &tmp);
    
    
}
/**
  * @简介：设置PAN312x的rx deviation h 大于1的配置
  * @参数：rx_dev
  * @返回值：无
  */
void PAN312x_Set_Rx_Deviation_H_HighOne(uint16_t rx_deviation_tmp, uint32_t rx_deviation, uint32_t data_rate)
{
    uint8_t tmp;
    uint8_t tmpBuffer[3];
    uint16_t fltr_dev;
    uint32_t symbrate_rbw;
    uint8_t chf_sel;
    uint8_t a, b;
    double high_dev_decimat_num;
    int decimat_last_manu_num;
    
    
    
    //[0x70][0x46]: reg_rx_tr_dev_outer_l
    //[0x70][0x47][3:0]: reg_rx_tr_dev_outer_h
    tmpBuffer[0] = (uint8_t)rx_deviation_tmp;
    tmpBuffer[1] = (uint8_t)((rx_deviation_tmp >> 8) & R147_REG_RX_TR_DEV_OUTER_H_Msk);
    PAN312x_Set_OP_Reg(R146, 2, tmpBuffer);
    
    
    //[0x70][0x3d][7:0]:reg_fltr_dev_l
    //[0x70][0x3e][0]: reg_fltr_dev_h
    fltr_dev = (int)rx_deviation * 1.0 / 100;
    tmpBuffer[0] = (uint8_t)fltr_dev;
    PAN312x_Get_OP_Reg(R13E, 1, &tmp);
    tmp |= (uint8_t)((fltr_dev >> 8) & R13E_REG_FLTR_DEV_H_Msk);
    tmpBuffer[1] = tmp;
    PAN312x_Set_OP_Reg(R13D, 2, tmpBuffer);
	
	
	symbrate_rbw = 2 * rx_deviation;
    
    
    //[0x70][0x50][7:4]:reg_chf_sel
    if(symbrate_rbw > 1000000){
        chf_sel = 0;
    }else if(symbrate_rbw > 500000){
        chf_sel = 1;
    }else if(symbrate_rbw > 400000){
        chf_sel = 2;
    }else if(symbrate_rbw > 250000){
        chf_sel = 3;
    }else if(symbrate_rbw > 200000){
        chf_sel = 4;
    }else if(symbrate_rbw > 125000){
        chf_sel = 5;
    }else if(symbrate_rbw > 100000){
        chf_sel = 6;
    }else if(symbrate_rbw > 80000){
        chf_sel = 7;
    }else if(symbrate_rbw > 62500){
        chf_sel = 8;
    }else if(symbrate_rbw > 50000){
        chf_sel = 9;
    }else if(symbrate_rbw > 40000){
        chf_sel = 10;
    }else if(symbrate_rbw == 40000){
        chf_sel = 11;
    }else if(symbrate_rbw > 10000){
        chf_sel = 12;
    }else{
        chf_sel = 13;
    }
    PAN312x_Get_OP_Reg(R150, 1, &tmp);
    tmp &= ~R150_REG_CHF_SEL_Msk;
    tmp |= (chf_sel << 4);
    PAN312x_Set_OP_Reg(R150, 1, &tmp);
    
    //[0x70][0x4b][6]:high_dev_decimat_en
    PAN312x_Get_OP_Reg(R14B, 1, &tmp);
    if(symbrate_rbw <= data_rate){
        tmp &= ~R14B_HIGH_DEV_DECIMAT_EN_Msk;
    }else{
        tmp |= R14B_HIGH_DEV_DECIMAT_EN_Msk;
    }
    PAN312x_Set_OP_Reg(R14B, 1, &tmp);
    //[0x72][0x52][6]:decimat_last_manu_en
    PAN312x_Get_OP_Reg(R252, 1, &tmp);
    if(symbrate_rbw <= data_rate){
        tmp &= ~R252_DECIMAT_LAST_MANU_EN_Msk;
    }else{
        tmp |= R252_DECIMAT_LAST_MANU_EN_Msk;
    }
    PAN312x_Set_OP_Reg(R252, 1, &tmp);
    
    if(symbrate_rbw >= 10000){
        a = 8;
    }else{
        a = 16;
    }
    
    if(data_rate >= 10000){
        b = 8;
    }else{
        b = 16;
    }
    //high_dev_decimat_num = (int)1.0 * a * symbrate_rbw / b / data_rate;
    high_dev_decimat_num = round(1.0 * a * symbrate_rbw / b / data_rate * 10000) / 10000.0;
    decimat_last_manu_num = (int)1.0 * 320000 / high_dev_decimat_num;
    
    //[0x72][0x50][7:0]:decimat_last_manu_num_l1
    //[0x72][0x51][7:0]:decimat_last_manu_num_l2
    //[0x72][0x52][2:0]:decimat_last_manu_num_h
    tmpBuffer[0] = (uint8_t)decimat_last_manu_num;
    tmpBuffer[1] = (uint8_t)(decimat_last_manu_num >> 8);
    PAN312x_Get_OP_Reg(R252, 1, &tmp);
    tmp |= (uint8_t)((decimat_last_manu_num >> 16) & 0x07);
    tmpBuffer[2] = tmp;
    PAN312x_Set_OP_Reg(R250, 3, tmpBuffer);
    
}
/**
  * @简介：设置PAN312x的rx deviation
  * @参数：rx_deviation：(单位hz)
  * @返回值：无
  */
void PAN312x_Set_Rx_Deviation(uint32_t rx_deviation)
{
    uint8_t tmp;
    uint8_t rate_tmp;
    uint32_t data_rate;
    int rx_dev_tmp;
    float h;
    //[0x71][0x06]
    PAN312x_Get_OP_Reg(R186, 1, &rate_tmp);
    if((rate_tmp & R186_REG_SYMB_AB_SEL_Msk) == R186_REG_SYMB_AB_SEL_Msk){
        //data rate >= 50kbps
        rate_tmp = (rate_tmp & R186_REG_SYMBRATE_B_Msk) >> 4; 
        if(rate_tmp == 0x00){
            //50kbps
            data_rate = 50000;
        }else if(rate_tmp == 0x01){
            //62.5kbps
            data_rate = 62500;
        }else if(rate_tmp == 0x02){
            //80kbps
            data_rate = 80000;
        }else if(rate_tmp == 0x03){
            //100kbps
            data_rate = 100000;
        }else if(rate_tmp == 0x04){
            //125kbps
            data_rate = 125000;
        }else if(rate_tmp == 0x05){
            //200kbps
            data_rate = 200000;            
        }else if(rate_tmp == 0x06){
            //250kbps
            data_rate = 250000;
        }else if(rate_tmp == 0x07){
            //400kbps
            data_rate = 400000;
        }else if(rate_tmp == 0x08){
            //500kbps
            data_rate = 500000;
        }
    }else{
        //data rate <= 40kbps
        PAN312x_Get_OP_Reg(R187, 1, &tmp);
        data_rate = tmp;
        PAN312x_Get_OP_Reg(R188, 1, &tmp);
        data_rate |= ((tmp & R188_REG_SYMBRATE_A_H_Msk) << 8);
        data_rate *= 100;
    }
    h = 2.0f * rx_deviation / data_rate;
    
    
    if((h >= 0.5) && (h <= 1.0)){
        rx_dev_tmp = (int)rx_deviation * 1.0 * (1 << 14) / data_rate / 8 / 2;
        PAN312x_Set_Rx_Deviation_H_BelowOne(rx_dev_tmp);
    }else if((h > 1.0) && (h <= 20)){
        rx_dev_tmp = 1024;
        PAN312x_Set_Rx_Deviation_H_HighOne(rx_dev_tmp, rx_deviation, data_rate);
    }else{
        return;
    }
}

/**
  * @简介：使能PAN312x的GPIO Direct Tx
  * @参数：无
  * @返回值: 无
  */
void PAN312x_GPIO_Direct_Tx_Enable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp |= PROPERTY_MSK_R107_REG_DIRECT_TX_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：失能PAN312x的GPIO Direct Tx
  * @参数：无
  * @返回值: 无
  */
void PAN312x_GPIO_Direct_Tx_Disable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp &= ~PROPERTY_MSK_R107_REG_DIRECT_TX_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：使能PAN312x的GPIO Direct Rx
  * @参数：无
  * @返回值: 无
  */
void PAN312x_GPIO_Direct_Rx_Enable(void)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp |= PROPERTY_MSK_R107_REG_DIRECT_RX_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：失能PAN312x的GPIO Direct Rx
  * @参数：无
  * @返回值: 无
  */
void PAN312x_GPIO_Direct_Rx_Disable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp &= ~PROPERTY_MSK_R107_REG_DIRECT_RX_EN;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：设置PAN312x的GPIO Direct 异步模式
  * @参数：无
  * @返回值: 无
  */
void PAN312x_Gpio_Direct_Asynchronous_Mode(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp &= ~PROPERTY_MSK_R107_REG_DIRECT_MODE;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：设置PAN312x的GPIO Direct 同步模式
  * @参数：无
  * @返回值: 无
  */
void PAN312x_Gpio_Direct_Synchronous_Mode(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R107);
	tmp |= PROPERTY_MSK_R107_REG_DIRECT_MODE;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R107, tmp);
}
/**
  * @简介：设置PAN312x的EncodingHaming模式
  * @参数：无
  * @返回值: 无
  */
void PAN312x_Set_FecHamingEncoding(PAN312xFecEncoding HamingEncoding)
{
	uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R106);
	if(HamingEncoding == FEC_HAMING_DISABLE){
		tmp &= ~PROPERTY_MSK_R106_REG_HAMMING_EN;
	}else if(HamingEncoding == FEC_HAMING_X3_X_1){
		tmp |= PROPERTY_MSK_R106_REG_HAMMING_EN;
		tmp &= ~PROPERTY_MSK_R106_REG_HAMMING_MODE;
	}else if(HamingEncoding == FEC_HAMING_X3_X2_1){
		tmp |= (PROPERTY_MSK_R106_REG_HAMMING_EN | PROPERTY_MSK_R106_REG_HAMMING_MODE);
	}
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R106, tmp);
}

void PAN312x_MaxPayloadLimitDisable(void)
{
	uint8_t tmp;
	PAN312x_Get_OP_Reg(R31C, 1, &tmp);
	tmp &= ~R31C_REG_MAX_VLD_Msk;
	PAN312x_Set_OP_Reg(R31C, 1, &tmp);
}
/**
  * @简介：设置PAN312x的
  * @参数：base_frequency(hz):
  *        frequency_step(hz):
  *        channel_number
  * @返回值：无
  */
void PAN312x_Set_ModulationType(PAN312xModulationSelect ModType)
{
    //uint8_t tmp;
//	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R186);
//    tmp &= ~PROPERTY_MSK_R186_REG_MODTYPE;
//    tmp |= (ModType << PROPERTY_POS_R186_REG_MODTYPE);
//    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R186, tmp);
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R186, 1, &tmp);
    tmp &= ~R186_REG_MODTYPE_Msk;
    tmp |= (ModType << R186_REG_MODTYPE_Pos);
    PAN312x_Set_OP_Reg(R186, 1, &tmp);
}

/**
  * @简介：设置PAN312x的Base Frequency
  * @参数：base_frequency(hz):
  *        frequency_step(hz):
  *        channel_number
  * @返回值：无
  */

#if 0
void PAN312x_Set_Frequency(uint32_t base_frequency, uint32_t frequency_step, uint16_t channel_number)
{
    uint8_t tmp;
    uint8_t tmpBuffer[4];
	int base_frequency_tmp;
	float frequency_step_tmp;
	int carrier_frequency;
	uint32_t carrier_frequency_tmp;
	int freq_step_integer;
	float freq_step_fraction;
	float mid_frequency_tmp;
    uint32_t ref_freq = 32000000; 
    uint32_t mid_frequency = 500000;
    
    
    //1、配置lo
    PAN312x_Get_OP_Reg(R1B3, 1, &tmp);
    tmp &= 0xf8;
//    if((base_frequency >= 130000000) && (base_frequency <= 187000000)){
//        //配置lo为12
//        tmp |= 0x04;
//        base_frequency_tmp = base_frequency * 12.0 / ref_freq * (1 << 24);
//        frequency_step_tmp = frequency_step * 12.0 / ref_freq * (1 << 24);
//        mid_frequency_tmp = mid_frequency * 12.0 / ref_freq * (1 << 24); 
//        
//    }else if((base_frequency >= 190000000) && (base_frequency < 280000000)){
//        //配置lo为8
//        tmp |= 0x03;
//        base_frequency_tmp = base_frequency * 8.0 / ref_freq * (1 << 24);
//        frequency_step_tmp = frequency_step * 8.0 / ref_freq * (1 << 24);
//        mid_frequency_tmp = mid_frequency * 8.0 / ref_freq * (1 << 24);         
//    }else 
    if((base_frequency >= 253000000) && (base_frequency < 380000000)){
        //配置lo为6
        tmp |= 0x02;
        base_frequency_tmp = base_frequency * 6.0 / ref_freq * (1 << 24);
        frequency_step_tmp = frequency_step * 6.0 / ref_freq * (1 << 24);        
        mid_frequency_tmp = mid_frequency * 6.0 / ref_freq * (1 << 24); 
    }else if((base_frequency >= 380000000) && (base_frequency <= 550000000)){
        //配置lo为4
        tmp |= 0x01;
        base_frequency_tmp = base_frequency * 4.0 / ref_freq * (1 << 24);
        frequency_step_tmp = frequency_step * 4.0  / ref_freq * (1 << 24);
		mid_frequency_tmp = mid_frequency * 4.0 / ref_freq * (1 << 24);
               
    }else if((base_frequency >= 760000000) && (base_frequency <= 1110000000)){
        //配置lo为2
        base_frequency_tmp = base_frequency * 2.0 / ref_freq * (1 << 24);
        frequency_step_tmp = frequency_step * 2.0 / ref_freq * (1 << 24);
        mid_frequency_tmp = mid_frequency * 2.0 / ref_freq * (1 << 24); 
    }
    PAN312x_Set_OP_Reg(R1B3, 1, &tmp);
	
	//频率补偿值
	freq_step_fraction = frequency_step_tmp - (int)frequency_step_tmp;
	
    base_frequency_tmp += round(freq_step_fraction * channel_number);
   
    //2、vco输出频率调节
    PAN312x_Get_OP_Reg(R2D2, 1, &tmp);
    tmp &= 0xc7;
    //280Mhz~380Mhz
    if((base_frequency >= 300000000) && (base_frequency < 327000000)){
        tmp |= (0x05 << 3);
    }else if((base_frequency >= 327000000) && (base_frequency < 380000000)){
        tmp |= (0x06 << 3);
    }
    //380Mhz~550Mhz
    if((base_frequency >= 380000000) && (base_frequency < 400000000)){
        tmp |= (0x0 << 3);
    }else if((base_frequency >= 400000000) && (base_frequency < 412000000)){
        tmp |= (0x1 << 3);
    }else if((base_frequency >= 412000000) && (base_frequency < 430000000)){
        tmp |= (0x2 << 3);
    }else if((base_frequency >= 430000000) && (base_frequency < 445000000)){
        tmp |= (0x3 << 3);
    }else if((base_frequency >= 445000000) && (base_frequency < 470000000)){
        tmp |= (0x4 << 3);
    }else if((base_frequency >= 470000000) && (base_frequency < 490000000)){
        tmp |= (0x5 << 3);
    }else if((base_frequency >= 490000000) && (base_frequency <= 510000000)){
        tmp |= (0x6 << 3);
    }else if((base_frequency >= 510000000) && (base_frequency < 550000000)){
        tmp |= (0x07 << 3);
    }
    
    PAN312x_Set_OP_Reg(R2D2, 1, &tmp);
    
    //3、[0x71][0x15]、[0x71][0x16]、[0x71][0x17]、[0x71][0x18]配置base frequency
    tmpBuffer[0] = (uint8_t)base_frequency_tmp;
    tmpBuffer[1] = (uint8_t)((uint32_t)base_frequency_tmp >> 8);
    tmpBuffer[2] = (uint8_t)(((uint32_t)base_frequency_tmp >> 16));
    tmpBuffer[3] = (uint8_t)(((uint32_t)base_frequency_tmp >> 24));
    PAN312x_Set_OP_Reg(R195, 4, tmpBuffer);
    
    //4、[0x71][0x11]、[0x71][0x12]配置frequency step
    tmpBuffer[0] = (uint8_t)frequency_step_tmp;
    tmpBuffer[1] = (uint8_t)((uint32_t)frequency_step_tmp >> 8);
    PAN312x_Set_OP_Reg(R191, 2, tmpBuffer);
    
    //5、[0x71][0x13]、[0x71][0x14]配置channel number
    tmpBuffer[0] = (uint8_t)channel_number;
    tmpBuffer[1] = (uint8_t)(channel_number >> 8);
    PAN312x_Set_OP_Reg(R193, 2, tmpBuffer);
    
    //6、[0x72][0x36][3]:配置为高本振
    PAN312x_Get_OP_Reg(R236, 1, &tmp);
    tmp |= R236_HI_LO_SET_Msk;
    PAN312x_Set_OP_Reg(R236, 1, &tmp);    
    
    //7、[0x71][0x19]、[0x71][0x1a]、[0x71][0x1b]设置中频(当前版本配置中频为:500khz)
    tmpBuffer[0] = (uint8_t)mid_frequency_tmp;
    tmpBuffer[1] = (uint8_t)((uint32_t)mid_frequency_tmp >> 8);
    tmpBuffer[2] = (uint8_t)(((uint32_t)mid_frequency_tmp >> 16));
    PAN312x_Set_OP_Reg(R199, 3, tmpBuffer);
    
    
    //8、如果使能reg_ppm_enable([74][0x22][6]),则需要配置载波频率
    PAN312x_Get_OP_Reg(R322, 1, &tmp);
    if((tmp & 0x40) == 0x40){
        carrier_frequency_tmp = base_frequency + channel_number * frequency_step;
        carrier_frequency = (int)(ref_freq * 1.0f * (1 << 10) / carrier_frequency_tmp);
        tmpBuffer[0] = (carrier_frequency & 0xff);
        PAN312x_Get_OP_Reg(R14B, 1, &tmpBuffer[1]);
        tmpBuffer[1] |= ((carrier_frequency >> 8) & 0xff);
        
        PAN312x_Set_OP_Reg(R14A, 2, tmpBuffer);
    }
}
#else
float frequency_step_tmp = 0.0;
void PAN312x_Set_Frequency(uint32_t base_frequency, uint32_t frequency_step, uint16_t channel_number)
{
    uint8_t tmp;
    uint8_t vco_tmp;
    uint8_t vco_vd_sw_tmp;
    uint8_t tmpBuffer[4];
	int base_frequency_tmp;
	
	int carrier_frequency;
	uint32_t carrier_frequency_tmp;
//	int freq_step_integer;
	float freq_step_fraction;
	float mid_frequency_tmp;
    uint32_t ref_freq = 32000000; 
    uint32_t mid_frequency = 500000;
    
    uint8_t freq_tmp;
    
    //base_frequency += frequency_step * channel_number;
    //1、配置lo
    PAN312x_Get_OP_Reg(R1B3, 1, &tmp);
    tmp &= 0xf8;
    
    //2、vco输出频率调节
    PAN312x_Get_OP_Reg(R2D2, 1, &vco_tmp);
    PAN312x_Get_OP_Reg(R2D4, 1, &vco_vd_sw_tmp);
    vco_vd_sw_tmp &= ~R2D4_PLL_VCO_VD_SW_Msk;
    vco_tmp &= 0xc7;
    if((base_frequency >= 253000000) && (base_frequency <= 367000000)){
        //配置lo为6
        tmp |= 0x02;
        base_frequency_tmp = base_frequency * 6.0 / ref_freq * (1 << 24);
        frequency_step_tmp = frequency_step * 6.0 / ref_freq * (1 << 24);        
        mid_frequency_tmp = mid_frequency * 6.0 / ref_freq * (1 << 24); 
        
        
        
         //253Mhz~367Mhz
        if((base_frequency >= 253000000) && (base_frequency < 260000000)){
            vco_tmp |= (0x0 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 260000000) && (base_frequency < 270000000)){
            vco_tmp |= (0x1 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 270000000) && (base_frequency < 280000000)){
            vco_tmp |= (0x2 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 280000000) && (base_frequency < 293000000)){
            vco_tmp |= (0x3 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 293000000) && (base_frequency < 307000000)){
            vco_tmp |= (0x4 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 307000000) && (base_frequency < 323000000)){
            vco_tmp |= (0x5 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 323000000) && (base_frequency < 340000000)){
            vco_tmp |= (0x6 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 340000000) && (base_frequency <= 367000000)){
            vco_tmp |= (0x07 << 3);
            vco_vd_sw_tmp |= 0x01;
        }
        
        
        PAN312x_Get_OP_Reg(R2C4, 1, &freq_tmp);
        freq_tmp &= ~R2C4_TRX_COMATCH_EN_Msk;
        PAN312x_Set_OP_Reg(R2C4, 1, &freq_tmp);
        
        PAN312x_Get_OP_Reg(R2D9, 1, &freq_tmp);
        freq_tmp &= ~R2D9_RX_LNA2_ICORE_Msk;
        freq_tmp |= (0x04 << R2D9_RX_LNA2_ICORE_Pos);
        PAN312x_Set_OP_Reg(R2D9, 1, &freq_tmp);
        
    }else if((base_frequency >= 380000000) && (base_frequency <= 550000000)){
        //配置lo为4
        tmp |= 0x01;
        base_frequency_tmp = base_frequency * 4.0 / ref_freq * (1 << 24);
        frequency_step_tmp = frequency_step * 4.0  / ref_freq * (1 << 24);
		mid_frequency_tmp = mid_frequency * 4.0 / ref_freq * (1 << 24);
        
        //380Mhz~550Mhz
        if((base_frequency >= 380000000) && (base_frequency < 390000000)){
            vco_tmp |= (0x0 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 390000000) && (base_frequency < 405000000)){
            vco_tmp |= (0x1 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 405000000) && (base_frequency < 420000000)){
            vco_tmp |= (0x2 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 420000000) && (base_frequency < 440000000)){
            vco_tmp |= (0x3 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 440000000) && (base_frequency < 460000000)){
            vco_tmp |= (0x4 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 460000000) && (base_frequency < 485000000)){
            vco_tmp |= (0x5 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 485000000) && (base_frequency < 510000000)){
            vco_tmp |= (0x6 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 510000000) && (base_frequency <= 550000000)){
            vco_tmp |= (0x07 << 3);
            vco_vd_sw_tmp |= 0x01;
        }
        
        PAN312x_Get_OP_Reg(R2C4, 1, &freq_tmp);
        freq_tmp &= ~R2C4_TRX_COMATCH_EN_Msk;
        PAN312x_Set_OP_Reg(R2C4, 1, &freq_tmp);
        
        PAN312x_Get_OP_Reg(R2D9, 1, &freq_tmp);
        freq_tmp &= ~R2D9_RX_LNA2_ICORE_Msk;
        freq_tmp |= (0x04 << R2D9_RX_LNA2_ICORE_Pos);
        PAN312x_Set_OP_Reg(R2D9, 1, &freq_tmp);
               
    }else if((base_frequency >= 760000000) && (base_frequency <= 1100000000)){
        //配置lo为2
        base_frequency_tmp = base_frequency * 2.0 / ref_freq * (1 << 24);
        frequency_step_tmp = frequency_step * 2.0 / ref_freq * (1 << 24);
        mid_frequency_tmp = mid_frequency * 2.0 / ref_freq * (1 << 24); 
        
        //760Mhz~1100Mhz
        if((base_frequency >= 760000000) && (base_frequency < 780000000)){
            vco_tmp |= (0x0 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 780000000) && (base_frequency < 810000000)){
            vco_tmp |= (0x1 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 810000000) && (base_frequency < 840000000)){
            vco_tmp |= (0x2 << 3);
            vco_vd_sw_tmp |= 0x02;
        }else if((base_frequency >= 840000000) && (base_frequency < 880000000)){
            vco_tmp |= (0x3 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 880000000) && (base_frequency < 920000000)){
            vco_tmp |= (0x4 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 920000000) && (base_frequency < 970000000)){
            vco_tmp |= (0x5 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 970000000) && (base_frequency < 1020000000)){
            vco_tmp |= (0x6 << 3);
            vco_vd_sw_tmp |= 0x01;
        }else if((base_frequency >= 1020000000) && (base_frequency <= 1100000000)){
            vco_tmp |= (0x07 << 3);
            vco_vd_sw_tmp |= 0x01;
        }
        
        PAN312x_Get_OP_Reg(R2C4, 1, &freq_tmp);
        freq_tmp |= R2C4_TRX_COMATCH_EN_Msk;
        PAN312x_Set_OP_Reg(R2C4, 1, &freq_tmp);
        
        PAN312x_Get_OP_Reg(R2D9, 1, &freq_tmp);
        freq_tmp &= ~R2D9_RX_LNA2_ICORE_Msk;
        freq_tmp |= (0x0a << R2D9_RX_LNA2_ICORE_Pos);
        PAN312x_Set_OP_Reg(R2D9, 1, &freq_tmp);
    }
    PAN312x_Set_OP_Reg(R1B3, 1, &tmp);
    
    PAN312x_Set_OP_Reg(R2D2, 1, &vco_tmp);
    
	PAN312x_Set_OP_Reg(R2D4, 1, &vco_vd_sw_tmp);
	//频率补偿值
	freq_step_fraction = frequency_step_tmp - (int)frequency_step_tmp;
	
    base_frequency_tmp += round(freq_step_fraction * channel_number);
    
    
    //3、[0x71][0x15]、[0x71][0x16]、[0x71][0x17]、[0x71][0x18]配置base frequency
    tmpBuffer[0] = (uint8_t)base_frequency_tmp;
    tmpBuffer[1] = (uint8_t)((uint32_t)base_frequency_tmp >> 8);
    tmpBuffer[2] = (uint8_t)(((uint32_t)base_frequency_tmp >> 16));
    tmpBuffer[3] = (uint8_t)(((uint32_t)base_frequency_tmp >> 24));
    PAN312x_Set_OP_Reg(R195, 4, tmpBuffer);
    
    //4、[0x71][0x11]、[0x71][0x12]配置frequency step
    tmpBuffer[0] = (uint8_t)frequency_step_tmp;
    tmpBuffer[1] = (uint8_t)((uint32_t)frequency_step_tmp >> 8);
    PAN312x_Set_OP_Reg(R191, 2, tmpBuffer);
    
    //5、[0x71][0x13]、[0x71][0x14]配置channel number
    tmpBuffer[0] = (uint8_t)channel_number;
    tmpBuffer[1] = (uint8_t)(channel_number >> 8);
    PAN312x_Set_OP_Reg(R193, 2, tmpBuffer);
    
    //6、[0x72][0x36][3]:配置为高本振
    PAN312x_Get_OP_Reg(R236, 1, &tmp);
    tmp |= R236_HI_LO_SET_Msk;
    PAN312x_Set_OP_Reg(R236, 1, &tmp);    
    
    //7、[0x71][0x19]、[0x71][0x1a]、[0x71][0x1b]设置中频(当前版本配置中频为:500khz)
    tmpBuffer[0] = (uint8_t)mid_frequency_tmp;
    tmpBuffer[1] = (uint8_t)((uint32_t)mid_frequency_tmp >> 8);
    tmpBuffer[2] = (uint8_t)(((uint32_t)mid_frequency_tmp >> 16));
    PAN312x_Set_OP_Reg(R199, 3, tmpBuffer);
    
    
    //8、如果使能reg_ppm_enable([74][0x22][6]),则需要配置载波频率
    PAN312x_Get_OP_Reg(R322, 1, &tmp);
    if((tmp & 0x40) == 0x40){
        carrier_frequency_tmp = base_frequency + channel_number * frequency_step;
        carrier_frequency = (int)(ref_freq * 1.0f * (1 << 10) / carrier_frequency_tmp);
        tmpBuffer[0] = (carrier_frequency & 0xff);
        PAN312x_Get_OP_Reg(R14B, 1, &tmpBuffer[1]);
        tmpBuffer[1] |= ((carrier_frequency >> 8) & 0xff);
        
        PAN312x_Set_OP_Reg(R14A, 2, tmpBuffer);
    }
}

#endif
/**
  * @简介：设置PAN312x的Frequency_Channel_Number
  * @参数：channel_number:       
  * @返回值：无
  */
void PAN312x_Set_Frequency_Channel_Number(uint16_t channel_number)
{
	uint8_t tmpBuffer[2];
	tmpBuffer[0] = (channel_number & 0xff);
    tmpBuffer[1] = ((channel_number >> 8) & 0xff); 
	PAN312x_Set_OP_Reg(R193, 2, tmpBuffer);
}
#if 1
/**
  * @简介：设置PAN312x的频点
  * @参数：Frequency      
  * @返回值：无
  * example，如果需要设置频点433Mhz
  * rx时,需要配置为433500000;
  * tx时,需要配置为433000000;
  */
void PAN312x_Set_Frequency_b(uint32_t Frequency)
{
    uint8_t tmp;
    uint8_t tmpBuffer[3];
    float tmp_freq;
    uint32_t ref_freq = 32000000; 
    int freq_integer;
    float freq_fraction;
    int carrier_frequency;
    
    //1、配置lo
    PAN312x_Get_OP_Reg(R1B3, 1, &tmp);
    tmp &= 0xf8;
    if((Frequency >= 280000000) && (Frequency <= 380000000)){
        //配置lo为6
        tmp |= 0x02;
        tmp_freq = Frequency * 6.0 / ref_freq; 
    }else if((Frequency >= 380000000) && (Frequency <= 550000000)){
        //配置lo为4
        tmp |= 0x01;
        tmp_freq = Frequency * 4.0 / ref_freq;
    }else if((Frequency >= 800000000) && (Frequency <= 1050000000)){
        //配置lo为2
        tmp_freq = Frequency * 2.0 / ref_freq;
    }
    PAN312x_Set_OP_Reg(R1B3, 1, &tmp);
    
   
    //2、vco输出频率调节
    PAN312x_Get_OP_Reg(R2D2, 1, &tmp);
    tmp &= 0xc7;
    //280Mhz~380Mhz
    if((Frequency >= 300000000) && (Frequency < 327000000)){
        tmp |= (0x05 << 3);
    }else if((Frequency >= 327000000) && (Frequency < 380000000)){
        tmp |= (0x06 << 3);
    }
    //380Mhz~550Mhz
    if((Frequency >= 380000000) && (Frequency < 400000000)){
        tmp |= (0x0 << 3);
    }else if((Frequency >= 400000000) && (Frequency < 412000000)){
        tmp |= (0x1 << 3);
    }else if((Frequency >= 412000000) && (Frequency < 430000000)){
        tmp |= (0x2 << 3);
    }else if((Frequency >= 430000000) && (Frequency < 445000000)){
        tmp |= (0x3 << 3);
    }else if((Frequency >= 445000000) && (Frequency < 470000000)){
        tmp |= (0x4 << 3);
    }else if((Frequency >= 470000000) && (Frequency < 490000000)){
        tmp |= (0x5 << 3);
    }else if((Frequency >= 490000000) && (Frequency <= 510000000)){
        tmp |= (0x6 << 3);
    }else if((Frequency >= 510000000) && (Frequency < 550000000)){
        tmp |= (0x07 << 3);
    }
    
    PAN312x_Set_OP_Reg(R2D2, 1, &tmp);
    
    //3、配置整数部分
    freq_integer = (int)tmp_freq;
    tmpBuffer[0] = (uint8_t)freq_integer;
    tmpBuffer[1] = (uint8_t)(freq_integer >> 8);
    PAN312x_Set_OP_Reg(R242, 2, tmpBuffer);
    
    //4、配置小数部分
    freq_fraction = tmp_freq - freq_integer;
    freq_fraction = freq_fraction * (1 << 23);
    
    tmpBuffer[0] = (uint8_t)freq_fraction;
    tmpBuffer[1] = (uint8_t)((uint32_t)freq_fraction >> 8);
    tmpBuffer[2] = (uint8_t)(((uint32_t)freq_fraction >> 16) | 0x80);
    
    PAN312x_Set_OP_Reg(R244, 3, tmpBuffer);
    
    
    //5、如果使能reg_ppm_enable([74][0x22][6]),则需要配置载波频率

    PAN312x_Get_OP_Reg(R322, 1, &tmp);
    if((tmp & 0x40) == 0x40){
        carrier_frequency = (int)(ref_freq * 1.0f * (1 << 10) / Frequency);
        tmpBuffer[0] = (carrier_frequency & 0xff);
        PAN312x_Get_OP_Reg(R14B, 1, &tmpBuffer[1]);
        tmpBuffer[1] |= ((carrier_frequency >> 8) & 0xff);
        
        PAN312x_Set_OP_Reg(R14A, 2, tmpBuffer);
    }
    
}
#endif

/**
  * @简介：设置PAN312x的发射功率(dBm)
  * @参数：PAN312xPowerdBm:(-20dBm ~ 21dBm,step:1dBm)      
  * @返回值：无
  */
#if 0
volatile uint8_t page73_46;
void PAN312x_Set_Power(PAN312xPowerdBm PowerdBm)    
{
    int power;
    power = (int)(PowerdBm & 0xff) - 20;
    if((power > 21) || (power < -20)){
        return;
    }
    uint8_t tmp;
    uint8_t vdd_pa_trim = (uint8_t)(PowerdBm >> 24);
    uint8_t pa_2nd_ramp = (uint8_t)(PowerdBm >> 16);
    uint8_t pa_bias_trim = (uint8_t)(PowerdBm >> 8);
    
    if((power >= -20) && (power <= 12)){
        //lp en[0x73][0x46][7]
        PAN312x_Get_OP_Reg(R2C6, 1, &tmp);
        tmp |= 0x80;
        PAN312x_Set_OP_Reg(R2C6, 1, &tmp);
        //dcdc en[0x60][0x06][7]
        PAN312x_Get_OP_Reg(R006, 1, &tmp);
        tmp |= 0x80;
        PAN312x_Set_OP_Reg(R006, 1, &tmp);
        //dcdc vout trim[0x73][0x34][4:0]
        PAN312x_Get_OP_Reg(R2B4, 1, &tmp);
        tmp &= 0xe0;
        tmp |= 0x0b;
        PAN312x_Set_OP_Reg(R2B4, 1, &tmp);
    }else if((power == 13) || (power == 14)){
        //lp en[0x73][0x46][7]
        PAN312x_Get_OP_Reg(R2C6, 1, &tmp);
        page73_46 = tmp;
        tmp |= 0x80;
        PAN312x_Set_OP_Reg(R2C6, 1, &tmp);
        PAN312x_Get_OP_Reg(R2C6, 1, &tmp);
        
//        //dcdc en[0x60][0x06][7]
        PAN312x_Get_OP_Reg(R006, 1, &tmp);
        tmp |= 0x80;
        PAN312x_Set_OP_Reg(R006, 1, &tmp);
        //dcdc vout trim[0x73][0x34][4:0]
        PAN312x_Get_OP_Reg(R2B4, 1, &tmp);
        tmp &= 0xe0;
        tmp |= 0x10;
        PAN312x_Set_OP_Reg(R2B4, 1, &tmp);
    }else{
        //lp en[0x73][0x46][7]
        PAN312x_Get_OP_Reg(R2C6, 1, &tmp);
        tmp &= 0x7f;
        PAN312x_Set_OP_Reg(R2C6, 1, &tmp);
        //dcdc en[0x60][0x06][7]
        PAN312x_Get_OP_Reg(R006, 1, &tmp);
        tmp &= 0x7f;
        PAN312x_Set_OP_Reg(R006, 1, &tmp);
        //dcdc vout trim[0x73][0x34][4:0]
        PAN312x_Get_OP_Reg(R2B4, 1, &tmp);
        tmp &= 0xe0;
        tmp |= 0x10;
        PAN312x_Set_OP_Reg(R2B4, 1, &tmp);
    }

    //VDD_PA_TRIM[0x73][0x32][7:3]
    PAN312x_Get_OP_Reg(R2B2, 1, &tmp);
    tmp &= 0x07;
    tmp |= (vdd_pa_trim << 3);
    PAN312x_Set_OP_Reg(R2B2, 1, &tmp);
        
    //PA_2ND_RAMP[0x70][0x4e][5:0]
    PAN312x_Get_OP_Reg(R14E, 1, &tmp);
    tmp &= 0xc0;
    tmp |= pa_2nd_ramp;
    PAN312x_Set_OP_Reg(R14E, 1, &tmp);
    //PA_BIAS_TRIM[0x73][0x57][7:4]
    PAN312x_Get_OP_Reg(R2D7, 1, &tmp);
    tmp &= 0x0f;
    tmp |= (pa_bias_trim << 4);
    PAN312x_Set_OP_Reg(R2D7, 1, &tmp);

}
#else

void PAN312x_Set_Power_Ldo(uint16_t Power)
{
    uint8_t tmp;
    uint8_t vdd_pa_trim ;
    uint8_t pa_2nd_ramp ;
    uint8_t pa_bias_trim ;
    uint8_t lp_en;
    vdd_pa_trim = PAN31XX_LDO_POWER_GET_VDD_PA_TRIM(Power);
    pa_2nd_ramp = PAN31XX_LDO_POWER_GET_PA_2ND_RAMP(Power);
    pa_bias_trim = PAN31XX_LDO_POWER_GET_PA_BIAS_TRIM(Power);
    lp_en = PAN31XX_LDO_POWER_GET_LP_EN(Power);
    
    //VDD_PA_TRIM[0x73][0x32][7:3]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R2B2);
    tmp &= ~PROPERTY_MSK_R2B2_VDD_PA_TRIM;
    tmp |= (vdd_pa_trim << PROPERTY_POS_R2B2_VDD_PA_TRIM);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R2B2, tmp);
    
    //PA_2ND_RAMP[0x70][0x4e][5:0]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R14E);
    tmp &= ~PROPERTY_MSK_R14E_PA_2ND_RAMP;
    tmp |= (pa_2nd_ramp << PROPERTY_POS_R14E_PA_2ND_RAMP);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R14E, tmp);
    
    //PA_BIAS_TRIM[0x73][0x57][7:4]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R2D7);
    tmp &= ~PROPERTY_MSK_R2D7_PA_BIAS_TRIM;
    tmp |= (pa_bias_trim << PROPERTY_POS_R2D7_PA_BIAS_TRIM);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R2D7, tmp);
    
    
    //lp en[0x73][0x46][7]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R2C6);
    tmp &= ~PROPERTY_MSK_R2C6_PA_LP_SEL;
    tmp |= (lp_en << PROPERTY_POS_R2C6_PA_LP_SEL);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R2C6, tmp);
    
    
    
}

void PAN312x_Set_Power_Dcdc(uint32_t Power)
{
    uint8_t tmp;
    uint8_t vdd_pa_trim ;
    uint8_t pa_2nd_ramp ;
    uint8_t pa_bias_trim ;
    uint8_t lp_en;
    uint8_t dcdc_en;
    uint8_t dcdc_vout_trim;
    
    vdd_pa_trim = PAN31XX_DCDC_POWER_GET_VDD_PA_TRIM(Power);
    pa_2nd_ramp = PAN31XX_DCDC_POWER_GET_PA_2ND_RAMP(Power);
    pa_bias_trim = PAN31XX_DCDC_POWER_GET_PA_BIAS_TRIM(Power);
    lp_en = PAN31XX_DCDC_POWER_GET_LP_EN(Power);
    dcdc_en = PAN31XX_DCDC_POWER_GET_DCDC_EN(Power);
    dcdc_vout_trim = PAN31XX_DCDC_POWER_GET_DCDC_VOUT_TRIM(Power);
    
    //VDD_PA_TRIM[0x73][0x32][7:3]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R2B2);
    tmp &= ~PROPERTY_MSK_R2B2_VDD_PA_TRIM;
    tmp |= (vdd_pa_trim << PROPERTY_POS_R2B2_VDD_PA_TRIM);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R2B2, tmp);
    
    //PA_2ND_RAMP[0x70][0x4e][5:0]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R14E);
    tmp &= ~PROPERTY_MSK_R14E_PA_2ND_RAMP;
    tmp |= (pa_2nd_ramp << PROPERTY_POS_R14E_PA_2ND_RAMP);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R14E, tmp);
    
    //PA_BIAS_TRIM[0x73][0x57][7:4]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R2D7);
    tmp &= ~PROPERTY_MSK_R2D7_PA_BIAS_TRIM;
    tmp |= (pa_bias_trim << PROPERTY_POS_R2D7_PA_BIAS_TRIM);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R2D7, tmp);
    
    
    //lp en[0x73][0x46][7]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R2C6);
    tmp &= ~PROPERTY_MSK_R2C6_PA_LP_SEL;
    tmp |= (lp_en << PROPERTY_POS_R2C6_PA_LP_SEL);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R2C6, tmp);
    
    
    //dcdc en[0x60][0x06][7]
    PAN312x_Get_OP_Reg(R006, 1, &tmp);
    tmp &= ~R006_EN_DCDC_Msk;
    tmp |= (dcdc_en << R006_EN_DCDC_Pos);
    PAN312x_Set_OP_Reg(R006, 1, &tmp);
    
    //dcdc vout trim[0x73][0x34][4:0]
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R2B4);
    tmp &= ~PROPERTY_MSK_R2B4_DCDC_VOUT_TRIM;
    tmp |= (dcdc_vout_trim << PROPERTY_POS_R2B4_DCDC_VOUT_TRIM);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R2B4, tmp);
}
void PAN312x_Set_Power(uint32_t Frequency, uint32_t FrequencyStep, uint16_t ChannelNumber, PAN312xPowerSelect PowerSelect, PAN312xPowerdBm PowerdBm)
{
    int power;
    power = (int)(PowerdBm & 0xff) - 20;
    if((PowerSelect == POWER_LDO_0603) || (PowerSelect == POWER_LDO_0402)){
        if((power > 20) || (power < -20)){
            while(1);
        }
    }else if((PowerSelect == POWER_DCDC_0603) || (PowerSelect == POWER_DCDC_0402)){
        if((power > 13) || (power < -20)){
            while(1);
        }
    }
    uint32_t freq_tmp = Frequency + ChannelNumber * FrequencyStep;
    if(freq_tmp >= 420000000 && (freq_tmp <= 445000000)){
        if(PowerSelect == POWER_LDO_0603){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0603_420_445mhz[PowerdBm]);
        }else if(PowerSelect == POWER_LDO_0402){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0402_420_445mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0603){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0603_420_445mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0402){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0402_420_445mhz[PowerdBm]);
        }
    }else if(freq_tmp >= 470000000 && (freq_tmp <= 510000000)){
        if(PowerSelect == POWER_LDO_0603){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0603_470_510mhz[PowerdBm]);
        }else if(PowerSelect == POWER_LDO_0402){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0402_470_510mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0603){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0603_470_510mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0402){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0402_470_510mhz[PowerdBm]);
        }
    }else if(freq_tmp >= 860000000 && (freq_tmp <= 870000000)){
        if(PowerSelect == POWER_LDO_0603){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0603_860_870mhz[PowerdBm]);
        }else if(PowerSelect == POWER_LDO_0402){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0402_860_870mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0603){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0603_860_870mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0402){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0402_860_870mhz[PowerdBm]);
        }
    }else if(freq_tmp >= 902000000 && (freq_tmp <= 928000000)){
        if(PowerSelect == POWER_LDO_0603){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0603_902_928mhz[PowerdBm]);
        }else if(PowerSelect == POWER_LDO_0402){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0402_902_928mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0603){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0603_902_928mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0402){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0402_902_928mhz[PowerdBm]);
        }
    }
}    

#endif

/**
  * @简介：获取PAN312x的接收信号的RSSI值
  *        芯片收取到数据时，芯片内部逻辑会统计当前数据包的信号强度。
  * @参数：无
  * @返回值：RSSI值
  */
int PAN312x_GetRSSI(void)
{
    uint8_t tmp;
    uint8_t rate_tmp;
    uint16_t data_rate_a;
    uint8_t rssi_offset = 0;
    
    int cRssi;
    
    //[0x71][0x06]
    PAN312x_Get_OP_Reg(R186, 1, &rate_tmp);
    if((rate_tmp & R186_REG_SYMB_AB_SEL_Msk) == R186_REG_SYMB_AB_SEL_Msk){
        rate_tmp = (rate_tmp & R186_REG_SYMBRATE_B_Msk) >> 4; 
        if((rate_tmp == 0x00) || (rate_tmp == 0x03) || (rate_tmp == 0x05) || (rate_tmp == 0x07)){
            //50kbps、100kbps、200kbps、400kbps
            rssi_offset = 5;
        }else if(rate_tmp == 0x02){
            //80kbps
            rssi_offset = 3;
        }else{
            rssi_offset = 0;
        }
    }else{
        //data rate <= 40kbps
        PAN312x_Get_OP_Reg(R187, 1, &tmp);
        data_rate_a = tmp;
        PAN312x_Get_OP_Reg(R188, 1, &tmp);
        data_rate_a |= ((tmp & R188_REG_SYMBRATE_A_H_Msk) << 8);
        if(data_rate_a == 40){
            //40kbps
            rssi_offset = 3;
        }else{
            rssi_offset = 0;
        }
    }
    
    PAN312x_Get_OP_Reg(R1BC, 1, &tmp);  //[0x71][0x3c]
    
    cRssi = (int)tmp;
    if(cRssi > 0x7f){
        cRssi = (0x100 - cRssi - rssi_offset);
    }
    return cRssi;
}

int PAN312x_GetChannelCheckRssi(void)
{
    uint8_t tmp;
    int cRssi;
    
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1BF);

   cRssi = (int)tmp;
    
    if(cRssi > 0x7f){
        cRssi = (0x100 - cRssi);
    }
    return cRssi;
}
/**
  * @简介：获取PAN312x的Snr
  * @参数：无
  * @返回值：Snr值
  */
int PAN312x_GetSnr(void)
{
    //[0x71][0x34 ~ 0x37]
    return 0;
}
/**
  * @简介：PAN312x的两点式校准
  * @参数：symbol_rate：速率
  *        tx_deviation：发送 deviation
  *        ref_diff：参考值
  * @返回值：无
  * 备注：
  * 1、当速率大于等于200kbps时，需要进行两点式校准
  */
void PAN312x_Two_Point_Calibration(uint8_t symbol_rate, uint32_t tx_deviation, uint16_t ref_diff)
{
    uint8_t tmp;
    uint8_t tmpBuffer[2];
    
    //[0x70][0x59][4:3],设置0，表示使用第一组两点式校准code
    PAN312x_Get_OP_Reg(R159, 1, &tmp);
    tmp &= ~R159_TP_CODE_GROUP_SEL_Msk;
    PAN312x_Set_OP_Reg(R159, 1, &tmp);
    
    /*
     * 除2 780~1110： [0x73][0x42][1] 为0
     * 除4 380~550： [0x73][0x42][1] 为1
     * 除6 253~367： [0x73][0x42][1] 为1
     */
    //[0x73][0x42][1]
    uint8_t lo_tmp;
    PAN312x_Get_OP_Reg(R1B3, 1, &lo_tmp);
    lo_tmp &= R1B3_LO_MUX_SEL_Msk;
    PAN312x_Get_OP_Reg(R2C2, 1, &tmp);
    if(lo_tmp == 0x00){
        //除2
        tmp &= ~R2C2_DAC_SG_SEL_Msk;
    }else if(lo_tmp == 0x01){
        //除4
        tmp |= R2C2_DAC_SG_SEL_Msk;
    }else if(lo_tmp == 0x02){
        //除6
        tmp |= R2C2_DAC_SG_SEL_Msk;
    }
    PAN312x_Set_OP_Reg(R2C2, 1, &tmp);
    
    
    if(symbol_rate == 0x0a){
        //2M
        //[0x70][0x4d]
        PAN312x_Get_OP_Reg(R14D, 1, &tmp);
        tmp &= ~R14D_PLL_VCO_TXCTK_Msk;
        tmp |= 0x03;
        PAN312x_Set_OP_Reg(R14D, 1, &tmp);
        
        //[0x73][0x42]
        PAN312x_Get_OP_Reg(R2C2, 1, &tmp);
        tmp &= ~R2C2_DAC_SEL_SW_Msk;
        tmp |= (0x03 << 2);
        PAN312x_Set_OP_Reg(R2C2, 1, &tmp);
    }else{
        //[0x70][0x4d]
        PAN312x_Get_OP_Reg(R14D, 1, &tmp);
        tmp &= ~R14D_PLL_VCO_TXCTK_Msk;
        tmp |= 0x01;
        PAN312x_Set_OP_Reg(R14D, 1, &tmp);
        
        //[0x73][0x42]
        PAN312x_Get_OP_Reg(R2C2, 1, &tmp);
        tmp &= ~R2C2_DAC_SEL_SW_Msk;
        tmp |= (0x01 << 2);
        PAN312x_Set_OP_Reg(R2C2, 1, &tmp);
    }
    
    if((symbol_rate == 0x0a) || ((symbol_rate == 0x09) && tx_deviation == 500000)){
        //2M
        //1M & tx_deviation = 500000hz
        //[0x73][0x58]
        PAN312x_Get_OP_Reg(R2D8, 1, &tmp);
        tmp &= ~R2D8_DAC_ISEL_Msk;
        tmp |= (0x07 << 4);
        PAN312x_Set_OP_Reg(R2D8, 1, &tmp);
    }else{
        PAN312x_Get_OP_Reg(R2D8, 1, &tmp);
        tmp &= ~R2D8_DAC_ISEL_Msk;
        tmp |= (0x02 << 4);
        PAN312x_Set_OP_Reg(R2D8, 1, &tmp);
    }
    
    //[0x71][0x24]
    PAN312x_Get_OP_Reg(R1A4, 1, &tmp);
    tmp |= 0x01;
    PAN312x_Set_OP_Reg(R1A4, 1, &tmp);
    
    
    //enter tx
    
    tmp = 0x10;
    PAN312x_Set_OP_Reg(R003, 1, &tmp);
    tmp = 0x20;
    PAN312x_Set_OP_Reg(R003, 1, &tmp);
   
   
    
    bsp_DelayMS(200);
    
    //[0x70][0x63]
    PAN312x_Get_OP_Reg(R163, 1, &tmp);
    vcol_cal_code = (tmp & 0x3f);
    
    //[0x70][0x69]
    tmpBuffer[0] = (uint8_t)ref_diff;
    tmpBuffer[1] = (uint8_t)(ref_diff >> 8);
    PAN312x_Set_OP_Reg(R169, 2, tmpBuffer);

    
    //[0x73][0x4b]
    PAN312x_Get_OP_Reg(R2CB, 1, &tmp);
    tmp |= (0x01 << 2);
    PAN312x_Set_OP_Reg(R2CB, 1, &tmp);
    
    
    //[0x70][0x57]
    PAN312x_Get_OP_Reg(R157, 1, &tmp);
    tmp &= 0x7f;
    PAN312x_Set_OP_Reg(R157, 1, &tmp);
    
    //[70][0x64]
    PAN312x_Get_OP_Reg(R164, 1, &tmp);
    tmp |= (0x01 << 6);
    PAN312x_Set_OP_Reg(R164, 1, &tmp);
    bsp_DelayUS(200);
    
 
    
    tmp |= (0x01 << 7);
    PAN312x_Set_OP_Reg(R164, 1, &tmp);
    bsp_DelayUS(200);
    
    
    tmp |= (0x01 << 4);
    PAN312x_Set_OP_Reg(R164, 1, &tmp);
    bsp_DelayUS(200);
    
    
    tmp &= 0xef;
    PAN312x_Set_OP_Reg(R164, 1, &tmp);
    bsp_DelayMS(200);
    
    
    //[0x70][0x5e]
    PAN312x_Get_OP_Reg(R15E, 1, &tmp);
    tp_auto_code = tmp;
    //tp_auto_code = 0x77;
    
    //[0x70][0x64]
    PAN312x_Get_OP_Reg(R164, 1, &tmp);
    tmp |= 0x7f;
    PAN312x_Set_OP_Reg(R164, 1, &tmp);
    tmp &= 0xbf;
    PAN312x_Set_OP_Reg(R164, 1, &tmp);
    
    //[0x70][0x67]
    PAN312x_Get_OP_Reg(R167, 1, &tmp);
    tmp &= 0xe0;
    tmp |= (tp_auto_code & 0x1f);
    #if 0
        PAN312x_Set_OP_Reg(R167, 1, &tmp);
    #else
        PAN312x_Set_OP_Reg(R165, 1, &tmp);
        //PAN312x_Set_OP_Reg(R166, 1, &tmp);
        //PAN312x_Set_OP_Reg(R167, 1, &tmp);
        //PAN312x_Set_OP_Reg(R168, 1, &tmp);
    #endif
    //[0x73][0x4b]
    PAN312x_Get_OP_Reg(R2CB, 1, &tmp);
    tmp &= 0xfb;
    PAN312x_Set_OP_Reg(R2CB, 1, &tmp);
    
    //[0x71][0x24]
    PAN312x_Get_OP_Reg(R1A4, 1, &tmp);
    tmp &= 0xfe;
    PAN312x_Set_OP_Reg(R1A4, 1, &tmp);
    
    
    bsp_DelayUS(120);
    
    //[0x70][0x42]
    tmp = 0x80;
    PAN312x_Set_OP_Reg(R142, 1, &tmp);
    
    
    //7、进入ready转态
    

    tmp = 0x10;
    PAN312x_Set_OP_Reg(R003, 1, &tmp);

 
}
/**
  * @简介：PAN312x的RC校准
  * @参数：无
  * @返回值：无
  */
void PAN312x_RC_Calibration(void)
{
    uint8_t tmp;
    //1、进入rx
    tmp = 0x40;
    PAN312x_Set_OP_Reg(R003, 1, &tmp);
    
    //2、[0x73][0x59][3]写1，进入自动校准模式
    PAN312x_Get_OP_Reg(R2D9, 1, &tmp);
    tmp |= R2D9_EN_RX_RCCAL_Msk;
    PAN312x_Set_OP_Reg(R2D9, 1, &tmp);
    bsp_DelayUS(10);
    
    //3、[0x73][0x59][1]写1，释放校准电路的复位信号
    PAN312x_Get_OP_Reg(R2D9, 1, &tmp);
    tmp |= R2D9_RX_RCCAL_RST_Msk;
    PAN312x_Set_OP_Reg(R2D9, 1, &tmp);
    bsp_DelayUS(10);
    
    //4、等[0x73][0x4f][6]为1，表示校准完成
    do{
        PAN312x_Get_OP_Reg(R2CF, 1, &tmp);
    }while(!((tmp & R2CF_RCCAL_DONE_Msk) == R2CF_RCCAL_DONE_Msk));
    
    //5、读取校准值[0x73][0x4f][5:0]RCCAL_CAPTUNE, 将该校准值写到
    //   寄存器[0x70][0x4f][5:0]RX_ADC_CAPTUNE
    PAN312x_Get_OP_Reg(R2CF, 1, &tmp);
    tmp &= R2CF_RCCAL_CAPTUNE_Msk;
    rc_code = tmp;
    PAN312x_Set_OP_Reg(R14F, 1, &tmp);
    
    //6、[0x73][0x59][1]写0
    PAN312x_Get_OP_Reg(R2D9, 1, &tmp);
    tmp &= ~R2D9_RX_RCCAL_RST_Msk;
    PAN312x_Set_OP_Reg(R2D9, 1, &tmp);
    
    //7、进入ready转态
    tmp = 0x10;
    PAN312x_Set_OP_Reg(R003, 1, &tmp);
}


/**
  * @简介：使能PAN312x的DCDC
  * @参数：无
  * @返回值: 无
  * 备注：
  * 1、rx若需要用dcdc模式，需在初始化中调用该函数;
  * 2、tx若需要用dcdc模式，只需要配置功率就可以了(PAN312x_Set_Power)，
  *    因为在PAN312x_Set_Power中已经使能dcdc，需要注意tx如果使能dcdc，发射功率最大只支持到14dBm。
  */
void PAN312x_DCDC_Enable(void)
{
    uint8_t tmp;
    //[0x60][06]
    PAN312x_Get_OP_Reg(R006, 1, &tmp);
    tmp |= R006_EN_DCDC_Msk;
    PAN312x_Set_OP_Reg(R006, 1, &tmp);
    //[0x73][0x44]
    ////放在regmap init中，tx rx公用
//    PAN312x_Get_OP_Reg(R2C4, 1, &tmp);
//    //DCDC_BUFSEL:[0x73][0x44][7:5] = 000b
//    tmp &= ~R2C4_DCDC_BUFSEL_Msk;
//    //DCDC_RESSEL:[0x73][0x44][4:2] = 010b
//    tmp &= ~R2C4_DCDC_RESSEL_Msk;
//    tmp |= (0x02 << R2C4_DCDC_RESSEL_Pos);
//    PAN312x_Set_OP_Reg(R2C4, 1, &tmp);
    //[0x73][0x45]
    PAN312x_Get_OP_Reg(R2C5, 1, &tmp);
    //DCDC_CAL_EN: [0x73][0x45][7:6] =00b dcdc自动校准关闭
    tmp &= ~R2C5_DCDC_CAL_EN_Msk;
    //DCDC_CAL_EN: [0x73][0x45][5:3] =111b dcdc充电限流控制
    //放在regmap init中，tx rx公用
//    tmp &= ~R2C5_DCDC_IMAX_Msk;
//    tmp |= (0x07 << R2C5_DCDC_IMAX_Pos);
    //test begin
    //tmp |= R2C5_DCDC_SSEN_Msk;
    //test end
    PAN312x_Set_OP_Reg(R2C5, 1, &tmp);
    
}


void PAN312x_DCDC_Disable(void)
{
    uint8_t tmp;
    //[0x60][06]
    PAN312x_Get_OP_Reg(R006, 1, &tmp);
    tmp &= ~R006_EN_DCDC_Msk;
    PAN312x_Set_OP_Reg(R006, 1, &tmp);
    
}


/**
  * @简介：PAN312x的GPIO Direct Tx初始化
  * @参数：无
  * @返回值: 无
  */

//同步模式
void PAN312x_SynchoronousMode_GpioDirectTxInit(void)
{
    //配置GPIO0为Gpio Direct Tx
    PAN312x_Iomux_Gpio(IOMUX_GPIO0_AS_DIRECT_TX);
    PAN312x_Set_Gpio_Mode(GPIO_PIN_0, GPIO_INPUT_MODE);
    
    //配置GPIO1输出数据速率
    PAN312x_Iomux_Gpio(IOMUX_GPIO1_AS_DIRECT_CLK);
    PAN312x_Set_Gpio_Mode(GPIO_PIN_1, GPIO_OUTPUT_MODE);
    
    //使能GPIO Direct Tx
    PAN312x_GPIO_Direct_Tx_Enable();
    
    //配置为同步模式
    PAN312x_Gpio_Direct_Synchronous_Mode();
    
}

void PAN312x_AsynchoronousMode_GpioDirectTxInit(void)
{   
    //使能GPIO Direct Tx
    PAN312x_GPIO_Direct_Tx_Enable();
    
    //配置为异步模式
    PAN312x_Gpio_Direct_Asynchronous_Mode();
    
}

/**
  * @简介：PAN312x的GPIO Direct Rx初始化
  * @参数：无
  * @返回值: 无
  */


void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
}

void PAN312x_Gpio_Direct_RxByPass_Enable(void)
{
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R30E, 1, &tmp);
    tmp |= R30E_DIRECT_BYPASS_MODE_Msk;
    PAN312x_Set_OP_Reg(R30E, 1, &tmp);
}

void PAN312x_Gpio_Direct_RxByPass_Disnable(void)
{
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R30E, 1, &tmp);
    tmp &= ~R30E_DIRECT_BYPASS_MODE_Msk;
    PAN312x_Set_OP_Reg(R30E, 1, &tmp);
}

//同步模式
void PAN312x_SynchoronousMode_GpioDirectRxInit(void)
{
	PAN312x_Enter_Ready();
	 GPIO_InitTypeDef GPIO_InitStruct;
    //GPIO0_Direct_Rx_Data: PB11
	__HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;//GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    //GPIO1 _Direct_Rx_Clk: PB5
   
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;//GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
    
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    
    //配置GPIO1为Gpio Direct Rx
    PAN312x_Iomux_Gpio(IOMUX_GPIO0_AS_DIRECT_RX);
    PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_0, GPIO_OUTPUT_MODE);
    
    //配置GPIO2输出数据速率
    PAN312x_Iomux_Gpio(IOMUX_GPIO1_AS_DIRECT_CLK);
    PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_1, GPIO_OUTPUT_MODE);
    
    //使能GPIO Direct Rx
    PAN312x_GPIO_Direct_Rx_Enable();
    
    //GPIO Direct Rx寄存器初始化
    PAN312x_Gpio_Direct_Rx_Regmap_Init();
    
    //配置为同步模式
    PAN312x_Gpio_Direct_Synchronous_Mode();
	
}

//异步模式
void PAN312x_AsynchoronousMode_GpioDirectRxInit(void)
{   
//    PAN312x_Iomux_Gpio(IOMUX_GPIO0_AS_DIRECT_RX);
//    PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_0, GPIO_OUTPUT_MODE);
//    
    PAN312x_Iomux_Gpio(IOMUX_GPIO1_AS_DIRECT_RX);
    PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_1, GPIO_OUTPUT_MODE);
    
//    PAN312x_Iomux_Gpio(IOMUX_GPIO2_AS_DIRECT_RX);
//    PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_2, GPIO_OUTPUT_MODE);
    
    //使能GPIO Direct Rx
    PAN312x_GPIO_Direct_Rx_Enable();
    
    //GPIO Direct Rx寄存器初始化
    PAN312x_Gpio_Direct_Rx_Regmap_Init();
	
	
	PAN312x_Gpio_Direct_Asynchronous_Mode();
    
    //agc_manu_en

//    PAN312x_Get_OP_Reg(R206, 1, &tmp);
//    tmp |= R206_REG_AGC_MANU_EN_Msk;
//    PAN312x_Set_OP_Reg(R206, 1, &tmp);
//    
//    //[0x74][0x16][1]:dagc_manu_en
//    PAN312x_Get_OP_Reg(R316, 1, &tmp);
//    tmp |= R316_REG_DAGC_MANU_EN_Msk;
//    PAN312x_Set_OP_Reg(R316, 1, &tmp);
    
    //[0x74][0x1a]
    
    //使能Direct rx bypass mode
    PAN312x_Gpio_Direct_RxByPass_Enable();
}

/**
  * @简介：PAN312x的GPIO Direct Rx寄存器初始化
  * @参数：无
  * @返回值: 无
  */
void PAN312x_Gpio_Direct_Rx_Regmap_Init(void)
{
    uint8_t tmp;
    
    //[0x74][0x0b]:盲同步纠频偏快慢阈值
    tmp = 0xcf;
    PAN312x_Set_OP_Reg(R30B, 1, &tmp);
    //[0x74][0x0c]:盲同步PPM计算快慢阈值
    tmp = 0x6b;
    PAN312x_Set_OP_Reg(R30C, 1, &tmp);
    //[0x74][0x0e]:打开盲同步使能，盲同步频偏计算使能
    tmp = 0x50;
    PAN312x_Set_OP_Reg(R30E, 1, &tmp);
    
    //[0x74][0x18]:配置dagc的alpha belta系数
    tmp = 0xa7;
    PAN312x_Set_OP_Reg(R318, 1, &tmp);
    
    
}    
/**
  * @简介：Iomux PAN312x的GPIO功能
  * @参数：IomuxGpio
  * @返回值: 无
  */
void PAN312x_Iomux_Gpio(uint32_t IomuxGpio)
{
	uint8_t tmp;
	uint16_t reg_addr;
	reg_addr = (uint16_t)(IomuxGpio & 0x7ff);

	PAN312x_Get_OP_Reg(reg_addr, 1, &tmp);
	
	tmp &= ~((uint8_t)(IomuxGpio >> 16));
	
	tmp |= ((uint8_t)(IomuxGpio >> 24));
    
    PAN312x_Set_OP_Reg(reg_addr, 1, &tmp);
}
/**
  * @简介：设置PAN312x的GPIO模式
  * @参数：GpioPin：
  *        Mode:
  *         0x01: 输出模式
  *         0x00: 输入模式
  * @返回值: 无
  */
void PAN312x_Set_Gpio_Mode(uint16_t GpioPin, uint8_t Mode)
{
	uint8_t tmp;
	uint8_t GpioPin0_2_11 = 0x00,GpioPin3_10 = 0x00;
	GpioPin0_2_11 = (uint8_t)GpioPin;
	GpioPin3_10 = (uint8_t)(GpioPin >> 8);
	
	if(GpioPin0_2_11 != 0x00){
        //[0x71][0x30]
        PAN312x_Get_OP_Reg(R1B0, 1, &tmp);
        
		if(Mode == GPIO_INPUT_MODE) {
            
            tmp &= ~(GpioPin0_2_11 << 4);
			tmp |= GpioPin0_2_11;
		}
		else if(Mode == GPIO_OUTPUT_MODE){
			tmp |= (GpioPin0_2_11 << 4);
		}
        PAN312x_Set_OP_Reg(R1B0, 1, &tmp);
		
	}
	
	if(GpioPin3_10 != 0x00){
        //[0x60][0x19]
		PAN312x_Get_OP_Reg(R019, 1, &tmp);
		if(Mode == GPIO_INPUT_MODE) {
			tmp &= ~GpioPin3_10;
			PAN312x_Set_OP_Reg(R019, 1, &tmp);
			
			PAN312x_Get_OP_Reg(R018, 1, &tmp);
			tmp |= GpioPin3_10;
			PAN312x_Set_OP_Reg(R018, 1, &tmp);
		}
		else if(Mode == GPIO_OUTPUT_MODE){
			tmp |= GpioPin3_10;
			PAN312x_Set_OP_Reg(R019, 1, &tmp);
		}	
	}
}

void PAN312x_Gpio_Write_Pin(uint16_t GpioPin, uint8_t PinState)
{
	uint8_t tmp;
	uint8_t GpioPin0_2_11 = 0x00,GpioPin3_10 = 0x00;
	GpioPin0_2_11 = (uint8_t)GpioPin;
	GpioPin3_10 = (uint8_t)(GpioPin >> 8);
	
	if(GpioPin0_2_11 != 0x00){
        PAN312x_Get_OP_Reg(R1B2, 1, &tmp);
		if(PinState == 0) {
			tmp &= ~GpioPin0_2_11;
		}
		else if(PinState == 1){
			tmp |= GpioPin0_2_11;
		}
		PAN312x_Set_OP_Reg(R1B2, 1, &tmp);
        
	}
	
	if(GpioPin3_10 != 0x00){
        PAN312x_Get_OP_Reg(R017, 1, &tmp);
		if(PinState == 0) {
			tmp &= ~GpioPin3_10;
		}
		else if(PinState == 1){
			tmp |= GpioPin3_10;
		}
        PAN312x_Set_OP_Reg(R017, 1, &tmp);
	}
}

uint8_t PAN312x_Gpio_Read_Pin(uint16_t GpioPin)
{
    uint8_t reg_value = 0;
    uint8_t pin_state = 0;

    //处理低8位引脚(GPI0，GPIO1.GPIO2)
    if(GpioPin& (PAN312x_GPIO_PIN_0 | PAN312x_GPIO_PIN_1 | PAN312x_GPIO_PIN_2)){
        //读取R1B2寄存号(GPIO状态寄存器)
        PAN312x_Get_OP_Reg(R1B2, 1, &reg_value);
        
        //检查每个引脚的状态
        if(GpioPin & PAN312x_GPIO_PIN_0){
            pin_state=(reg_value &(1 << 0)) ? 1 : 0;
        }else if(GpioPin & PAN312x_GPIO_PIN_1){
            pin_state = (reg_value & (1 << 1)) ? 1 : 0;
        }else if (GpioPin & PAN312x_GPIO_PIN_2){
            pin_state = (reg_value & (1 << 2)) ? 1 : 0;
        }
        
    }else if(GpioPin& (PAN312x_GPIO_PIN_9 | PAN312x_GPIO_PIN_10)){
        //读取R017寄存号(GPIO状态寄存器)
        PAN312x_Get_OP_Reg(R017, 1, &reg_value);
        
        //检查每个引脚的状态
        if(GpioPin & PAN312x_GPIO_PIN_9){
            pin_state = (reg_value &(1 << 6)) ? 1 : 0;
        }else if(GpioPin & PAN312x_GPIO_PIN_10){
            pin_state = (reg_value & (1 << 7)) ? 1 : 0;
        }
    }
    
    return pin_state;
}

void PAN312x_Gpio_DigitalInputEnable(uint16_t GpioPin)
{
    uint8_t tmp;
	uint8_t GpioPin0_2_11 = 0x00,GpioPin3_10 = 0x00;
	GpioPin0_2_11 = (uint8_t)GpioPin;
	GpioPin3_10 = (uint8_t)(GpioPin >> 8);
    
    if(GpioPin3_10 != 0x00){
        PAN312x_Get_OP_Reg(R018, 1, &tmp);
        tmp |= GpioPin3_10;
        PAN312x_Set_OP_Reg(R018, 1, &tmp);
	}
    
    
    if(GpioPin0_2_11 != 0x00){
        //[0x71][0x30]
        PAN312x_Get_OP_Reg(R1B0, 1, &tmp);
        tmp |= GpioPin0_2_11;
        PAN312x_Set_OP_Reg(R1B0, 1, &tmp);
		
	}
}
/**
  * @简介：设置PAN312x的gpio输出系统时钟
  * @参数：IomuxGpio：时钟输出的gpio(gpio0、gpio1、gpio2、gpio9、gpio10)
  *        OclkFrequency：
  *        0: 16Mhz
  *        1: 8Mhz
  *        2: 4Mhz
  *        3: 2Mhz
  *        4: 2Mhz
  *        5: 500Khz
  * @返回值：无
  */
void PAN312x_GpioOutputOclk(uint32_t IomuxGpio, PAN312xGpioOutputClk ClkFrequency)
{
    uint8_t clk_select,clk_set;
    clk_select = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R14D);
    clk_set = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R150);
    clk_set |= (PROPERTY_MSK_R150_OCLK_EN  | PROPERTY_MSK_R150_OCLK_SRC_SEL);
    if(ClkFrequency <4){
        //16Mhz、8Mhz、4Mhz、2Mhz
        clk_select &= ~PROPERTY_MSK_R14D_OCLK_500K_SEL;
        clk_set &= ~PROPERTY_MSK_R150_OCLK_DIV_SEL;
        clk_set |=(ClkFrequency << PROPERTY_POS_R150_OCLK_DIV_SEL);
    }else if(ClkFrequency == 4){
        //500Khzclk 
        clk_select |= PROPERTY_MSK_R14D_OCLK_500K_SEL;
    }
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R14D,clk_select);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R150,clk_set);
    PAN312x_Iomux_Gpio(IomuxGpio);
}
/**
  * @简介：设置PAN312x进入单载波模式
  * @参数：frequency：频点
  *        power：发射功率
  * @返回值：无
  */
void PAN312x_Enter_Carrier(uint32_t Frequency, uint32_t FrequencyStep, uint16_t ChannelNumber, PAN312xPowerSelect PowerSelect, PAN312xPowerdBm PowerdBm)
{
	uint8_t tmp;
    tmp = 0x10;
    PAN312x_Set_OP_Reg(R003, 1, &tmp);
	//1、进入tx模式
	tmp = 0x20;
	PAN312x_Set_OP_Reg(R003, 1, &tmp);
    
    //2、配置频点
    
    PAN312x_Set_Frequency(Frequency, FrequencyStep, ChannelNumber);

    //3、配置发射功率
    PAN312x_Set_Power(Frequency, FrequencyStep, ChannelNumber, PowerSelect, PowerdBm);
    
	//4、配置tx连续发送模式
	PAN312x_Get_OP_Reg(R153, 1, &tmp);
	tmp |= R153_REG_TX_CFG_MODE_Msk;
	PAN312x_Set_OP_Reg(R153, 1, &tmp);
    
    //5、发调制波形
    PAN312x_Get_OP_Reg(R1A4, 1, &tmp);
    tmp |= R1A4_REG_TX_FIFO_FULL_Msk;
	PAN312x_Set_OP_Reg(R1A4, 1, &tmp);
}






/**
  * @简介：通过spi命令唤醒PAN312x
  * @参数：无 
  * @返回值：无
  */
void PAN312x_WakeUp_BySpi(void)
{
    uint8_t tmp;
    //rch_en改为用状态机控制
    PAN312x_Read(R004, &tmp);
    tmp &= ~R004_REG_ENRCH_SEL_Msk;
    PAN312x_Write(R004, tmp);
    PAN312x_Write(R005, 0x60);
    PAN312x_Read(R007, &tmp);
    tmp |= (R007_SPI_WKEN_Msk | R007_SPI_WKTRIG_Msk);
    PAN312x_Write(R007, tmp);
    //至少延迟31.25us
    for(volatile uint32_t i = 0; i < 50; i++);
    tmp &= ~R007_SPI_WKTRIG_Msk;
    PAN312x_Write(R007, tmp);
    
    tmp = 0x00;
    PAN312x_Write(R005, tmp);  
}
/**
  * @简介：使能PAN312x的rcl时钟
  * @参数：无 
  * @返回值：无
  */
void PAN312x_ClkRcl_Enable(void)
{
    uint8_t tmp;
    PAN312x_Write(R005, 0x60);
    PAN312x_Read(R00E, &tmp);
    tmp |= R00E_EN_RCL_3V_Msk;
    PAN312x_Write(R00E, tmp);    
    PAN312x_Write(R005, 0x00);
}
/**
  * @简介：失能PAN312x的rcl时钟
  * @参数：无 
  * @返回值：无
  */
void PAN312x_ClkRcl_Disable(void)
{
    uint8_t tmp;
    PAN312x_Write(R005, 0x60);
    PAN312x_Read(R00E, &tmp);
    tmp &= ~R00E_EN_RCL_3V_Msk;
    PAN312x_Write(R00E, tmp);    
    PAN312x_Write(R005, 0x00);
}
/**
  * @简介：设置PAN312x 的SymbolRate(SymbolRate <= 40kbps)
  * @参数：symbol_rate_a:
  *        example:200(设置的值) 实际对应的速率 20kbps 
  * @返回值：无
  */
void PAN312x_Set_Symbol_RateA(uint16_t symbol_rate_a)
{
	uint8_t tmp, tmpBuffer[3];
    uint32_t IntermediateFrequency;
	
	//page71, 0x06
	PAN312x_Get_OP_Reg(R186, 1, &tmp);
	tmp &= ~R186_REG_SYMB_AB_SEL_Msk;
	PAN312x_Set_OP_Reg(R186, 1, &tmp);

	PAN312x_Get_OP_Reg(R187, 1, &tmp);
	tmp = symbol_rate_a;
	PAN312x_Set_OP_Reg(R187, 1, &tmp);
    

	PAN312x_Get_OP_Reg(R188, 1, &tmp);
	tmp &= ~R188_REG_SYMBRATE_A_H_Msk;
	tmp = (symbol_rate_a >> 8);
	tmp &= R188_REG_SYMBRATE_A_H_Msk;
	PAN312x_Set_OP_Reg(R188, 1, &tmp);

	//page70, 0x50 chf_sel

	PAN312x_Get_OP_Reg(R150, 1, &tmp);
	tmp &= ~R150_REG_CHF_SEL_Msk;
	
	if(symbol_rate_a == 400){
		//40k
		tmp |= (0x0b << 4);
		
	}else if(symbol_rate_a >= 100 && symbol_rate_a < 400){
		
		tmp |= (0x0c << 4);
		
	}else if(symbol_rate_a >= 20 && symbol_rate_a < 100){
		
		tmp |= (0x0d << 4);
		
	}
	PAN312x_Set_OP_Reg(R150, 1, &tmp);

	
	IntermediateFrequency = 0x004000;
	tmpBuffer[0] = (uint8_t)IntermediateFrequency;
	tmpBuffer[1] = (uint8_t)((uint32_t)IntermediateFrequency >> 8);
	
	PAN312x_Get_OP_Reg(R153, 1, &tmp);
	
	tmp |= (uint8_t)(((uint32_t)IntermediateFrequency >> 16) & 0x0f);
	tmpBuffer[2] = tmp;
	PAN312x_Set_OP_Reg(R151, 3, tmpBuffer);
    
    
    //[0x70][0x4d] ADC中频:±500Khz
    PAN312x_Get_OP_Reg(R14D, 1, &tmp);
    tmp &= ~R14D_RX_ADC_IFSEL_Msk;
    tmp |= (0x01 << 5);
    PAN312x_Set_OP_Reg(R14D, 1, &tmp);
    
    //[0x70][0x4e] ADC带宽选择：±500Khz
    PAN312x_Get_OP_Reg(R14E, 1, &tmp);
    tmp &= ~R14E_RX_ADC_BWSEL_Msk;
    tmp |= (0x02 << 6);
    PAN312x_Set_OP_Reg(R14E, 1, &tmp);
    
    //[0x73][0x46] TIA带宽选择: 1.5Mhz
    PAN312x_Get_OP_Reg(R2C6, 1, &tmp);
    tmp &= ~R2C6_RX_TIA_BWSEL_Msk;
    tmp |= (0x01 << 4);
    PAN312x_Set_OP_Reg(R2C6, 1, &tmp);
    
    PAN312x_Get_OP_Reg(R157, 1, &tmp);
    tmp |= R157_IB_ONLY_Msk;
    PAN312x_Set_OP_Reg(R157, 1, &tmp);
    
    //rc_code回写到寄存器[0x73][0x50][7:1],bit[7]不用管，用默认值1，[6:1]等于rc_code
    PAN312x_Get_OP_Reg(R2D0, 1, &tmp);
    tmp &= 0x81;
    tmp |= (rc_code << 1);
    PAN312x_Set_OP_Reg(R2D0, 1, &tmp);
    
}
/**
  * @简介：设置PAN312x 的SymbolRate(SymbolRate >= 50kbps)
  * @参数：symbol_rate_b:
  *          index  symbol_rate    fs
  *          0x00:      50k        4M
  *          0x01:      62.5k      4M
  *          0x02:      80k        6.4M
  *          0x03:      100k       6.4M
  *          0x04:      125k       8M
  *          0x05:      200k       16M
  *          0x06:      250k       16M
  *          0x07:      400k       16M
  *          0x08:      500k       16M
  *          0x09:      1M  
  *          0x0a:      2M
  *          IF = symbol_rate / fs *2^20 
  * @返回值：无
  */

void PAN312x_Set_Symbol_RateB(uint32_t DataRate, uint32_t TxDeviation)
{
	uint8_t tmp, tmpBuffer[4];
	uint32_t IntermediateFrequency;
    uint8_t symbol_rate_b;
    
    float h;
  
    h = 2.0f * TxDeviation / DataRate;

    if(DataRate == 50000){
        symbol_rate_b = 0x00;
    }else if(DataRate == 62500){
        symbol_rate_b = 0x01;
    }else if(DataRate == 80000){
        symbol_rate_b = 0x02;
    }else if(DataRate == 100000){
        symbol_rate_b = 0x03;
    }else if(DataRate == 125000){
        symbol_rate_b = 0x04;
    }else if(DataRate == 200000){
        symbol_rate_b = 0x05;
    }else if(DataRate == 250000){
        symbol_rate_b = 0x06;
    }else if(DataRate == 400000){
        symbol_rate_b = 0x07;
    }else if(DataRate == 500000){
        symbol_rate_b = 0x08;
    }else if(DataRate == 1000000){
        symbol_rate_b = 0x09;
    }else if(DataRate == 2000000){
        symbol_rate_b = 0x0a;
        //[0x73][0x4b][2] 
        PAN312x_Get_OP_Reg(R2CB, 1, &tmp);
        tmp |= (R2CB_EN_PLL_LPF_VCDN_Msk);
        PAN312x_Set_OP_Reg(R2CB, 1, &tmp);
        PAN312x_Get_OP_Reg(R2CB, 1, &tmp);
    }
	//Page71 0x06: 0x186  data_rate
	PAN312x_Get_OP_Reg(R186, 1, &tmp);
	tmp &= ~(R186_REG_SYMBRATE_B_Msk | R186_REG_SYMB_AB_SEL_Msk);
	tmp |= ((symbol_rate_b << 4) | (R186_REG_SYMB_AB_SEL_Msk));
	PAN312x_Set_OP_Reg(R186, 1, &tmp);

//	//page70, 0x50 chf_sel
	PAN312x_Get_OP_Reg(R150, 1, &tmp);
	tmp &= ~R150_REG_CHF_SEL_Msk;
	
	switch(symbol_rate_b){
		case 0x00:
			//50kbps
			tmp |= (0x0a << 4);
			break;
		case 0x01:
			//62.5kbps
			tmp |= (0x09 << 4);
			break;
		case 0x02:
			//80kbps
			tmp |= (0x08 << 4);
			break;
		case 0x03:
			//100kbps
			tmp |= (0x07 << 4);
			break;
		case 0x04:
			//125kbps
		    tmp |= (0x06 << 4);
			break;
		case 0x05:
			//200kbps
			tmp |= (0x05 << 4);
			break;
		case 0x06:
			//250kbps
			tmp |= (0x04 << 4);
			break;
		case 0x07:
			//400kbps
			tmp |= (0x03 << 4);
			break;
		case 0x08:
			//500kbps
			tmp |= (0x02 << 4);
			break;
        case 0x09:
            //1Mbps
            tmp |= (0x01 << 4);
            break;
        case 0x0a:
            //2Mbps
            tmp |= (0x00 << 4);
            break;
	}
	PAN312x_Set_OP_Reg(R150, 1, &tmp);
	

    //[0x70][0x51~0x53] 数字中频:500Khz
	
	IntermediateFrequency = 0x004000;

	
	tmpBuffer[0] = (uint8_t)IntermediateFrequency;
	tmpBuffer[1] = (uint8_t)((uint32_t)IntermediateFrequency >> 8);
	
	PAN312x_Get_OP_Reg(R153, 1, &tmp);
	
	tmp |= (uint8_t)(((uint32_t)IntermediateFrequency >> 16) & 0x0f);
	tmpBuffer[2] = tmp;

	PAN312x_Set_OP_Reg(R151, 3, tmpBuffer);
    
    
    //[0x70][0x4d] ADC中频:±500Khz
    PAN312x_Get_OP_Reg(R14D, 1, &tmp);
    tmp &= ~R14D_RX_ADC_IFSEL_Msk;
    tmp |= (0x01 << 5);
    PAN312x_Set_OP_Reg(R14D, 1, &tmp);
    
    //[0x70][0x4e] ADC带宽选择：±500Khz
    PAN312x_Get_OP_Reg(R14E, 1, &tmp);
    tmp &= ~R14E_RX_ADC_BWSEL_Msk;
    tmp |= (0x02 << 6);
    PAN312x_Set_OP_Reg(R14E, 1, &tmp);
    
    //[0x73][0x46] TIA带宽选择: 1.5Mhz
    PAN312x_Get_OP_Reg(R2C6, 1, &tmp);
    tmp &= ~R2C6_RX_TIA_BWSEL_Msk;
    tmp |= (0x01 << 4);
    PAN312x_Set_OP_Reg(R2C6, 1, &tmp);
    
    //rc_code回写到寄存器[0x73][0x50][7:1],
    //bit[7]不用管，用默认值1，[6:1]等于rc_code
    PAN312x_Get_OP_Reg(R2D0, 1, &tmp);
    tmp &= 0x81;
    tmp |= (rc_code << 1);
    PAN312x_Set_OP_Reg(R2D0, 1, &tmp);
    
    
    //diff
    if(symbol_rate_b >= 0x05){
        //大于200Khz
        //[0x70][0x57][8] 0:带内带外都有 1：单带内模式 
        PAN312x_Get_OP_Reg(R157, 1, &tmp);
        tmp &= ~R157_IB_ONLY_Msk;
        PAN312x_Set_OP_Reg(R157, 1, &tmp);
        
        uint32_t tx_dev;
        uint16_t ref_diff;
        uint8_t lo_tmp;
        PAN312x_Get_OP_Reg(R1B3, 1, &lo_tmp);
        lo_tmp &= R1B3_LO_MUX_SEL_Msk;
        if(((symbol_rate_b == 0x05) &&(h == 1.0)) || (((symbol_rate_b == 0x07) &&(h == 0.5)) )){
            //datarate = 200kbps deviation = 100khz, h = 1
            //datarate = 400kbps deviation = 100khz, h = 0.5
            tx_dev = 100000;
            if(lo_tmp == 0x00){
                //除2:频段760Mhz ~ 1110Mhz
                ref_diff = 205;
            }else if(lo_tmp == 0x01){
                //除4:频段380Mhz ~ 550Mhz
                ref_diff = 410;
            }else if(lo_tmp == 0x02){
                //除6:频段253Mhz ~ 380Mhz
                ref_diff = 614;
            }else if(lo_tmp == 0x03){
                //除8:频段190Mhz ~ 280Mhz
                ref_diff = 819;
            }else if(lo_tmp == 0x04){
                //除12:频段130Mhz ~ 187Mhz
                ref_diff = 1229;
            }
            
        }else if((symbol_rate_b == 0x05) &&(h == 0.5)){
            //datarate = 200kbps deviation = 50khz, h = 0.5
            tx_dev = 50000;
            if(lo_tmp == 0x00){
                //除2:频段760Mhz ~ 1110Mhz
                ref_diff = 102;
            }else if(lo_tmp == 0x01){
                //除4:频段380Mhz ~ 550Mhz
                ref_diff = 205;
            }else if(lo_tmp == 0x02){
                //除6:频段253Mhz ~ 380Mhz
                ref_diff = 307;
            }else if(lo_tmp == 0x03){
                //除8:频段190Mhz ~ 280Mhz
                ref_diff = 410;
            }else if(lo_tmp == 0x04){
                //除12:频段130Mhz ~ 187Mhz
                ref_diff = 614;
            }
        }
        else if((symbol_rate_b == 0x06) &&(h == 0.5)){
            //datarate = 250kbps deviation = 62.5khz, h = 0.5
            tx_dev = 62500;
            if(lo_tmp == 0x00){
                //除2:频段760Mhz ~ 1110Mhz
                ref_diff = 128;
            }else if(lo_tmp == 0x01){
                //除4:频段380Mhz ~ 550Mhz
                ref_diff = 256;
            }else if(lo_tmp == 0x02){
                //除6:频段253Mhz ~ 380Mhz
                ref_diff = 384;
            }else if(lo_tmp == 0x03){
                //除8:频段190Mhz ~ 280Mhz
                ref_diff = 512;
            }else if(lo_tmp == 0x04){
                //除12:频段130Mhz ~ 187Mhz
                ref_diff = 768;
            }
        }
        else if(((symbol_rate_b == 0x06) &&(h == 1.0)) || (((symbol_rate_b == 0x08) &&(h == 0.5)))){
            //250kbps 
            //datarate = 250kbps deviation = 125khz, h = 1
            //datarate = 500kbps deviation = 125khz, h = 0.5
            tx_dev = 125000;
            if(lo_tmp == 0x00){
                //除2:频段760Mhz ~ 1110Mhz
                ref_diff = 256;
            }else if(lo_tmp == 0x01){
                //除4:频段380Mhz ~ 550Mhz
                ref_diff = 512;
            }else if(lo_tmp == 0x02){
                //除6:频段253Mhz ~ 380Mhz
                ref_diff = 768;
            }else if(lo_tmp == 0x03){
                //除8:频段190Mhz ~ 280Mhz
                ref_diff = 1024;
            }else if(lo_tmp == 0x04){
                //除12:频段130Mhz ~ 187Mhz
                ref_diff = 1536;
            }
        }else if((symbol_rate_b == 0x07) &&(h == 1.0)){
            //400kbps
            //datarate = 400kbps deviation = 200khz, h = 1
            tx_dev = 200000;
            if(lo_tmp == 0x00){
                //除2:频段760Mhz ~ 1110Mhz
                ref_diff = 410;
            }else if(lo_tmp == 0x01){
                //除4:频段380Mhz ~ 550Mhz
                ref_diff = 819;
            }else if(lo_tmp == 0x02){
                //除6:频段253Mhz ~ 380Mhz
                ref_diff = 1229;
            }else if(lo_tmp == 0x03){
                //除8:频段190Mhz ~ 280Mhz
                ref_diff = 1638;
            }else if(lo_tmp == 0x04){
                //除12:频段130Mhz ~ 187Mhz
                ref_diff = 2458;
            }
        }else if(((symbol_rate_b == 0x08) &&(h == 1.0)) || ((symbol_rate_b == 0x09) && (h == 0.5))){
            //datarate = 500kbps deviation = 250khz, h = 1
            //datarate = 1Mbps deviation = 250khz, h = 0.5
            tx_dev = 250000;
            if(lo_tmp == 0x00){
                //除2:频段760Mhz ~ 1110Mhz
                ref_diff = 512;
            }else if(lo_tmp == 0x01){
                //除4:频段380Mhz ~ 550Mhz
                ref_diff = 1024;
            }else if(lo_tmp == 0x02){
                //除6:频段253Mhz ~ 380Mhz
                ref_diff = 1536;
            }else if(lo_tmp == 0x03){
                //除8:频段190Mhz ~ 280Mhz
                ref_diff = 2048;
            }else if(lo_tmp == 0x04){
                //除12:频段130Mhz ~ 187Mhz
                ref_diff = 3072;
            }
        }else if(((symbol_rate_b == 0x09) &&(h == 1.0)) || ((symbol_rate_b == 0x0a) && (h == 0.5))){
            //datarate = 1Mbps deviation = 500khz, h = 1
            //datarate = 2Mbps deviation = 500khz, h = 0.5
            tx_dev = 500000;
            if(lo_tmp == 0x00){
                //除2:频段760Mhz ~ 1110Mhz
                ref_diff = 1024;
            }else if(lo_tmp == 0x01){
                //除4:频段380Mhz ~ 550Mhz
                ref_diff = 2048;
            }else if(lo_tmp == 0x02){
                //除6:频段253Mhz ~ 380Mhz
                ref_diff = 3072;
            }else if(lo_tmp == 0x03){
                //除8:频段190Mhz ~ 280Mhz
                ref_diff = 4096;
            }
        }else if((symbol_rate_b == 0x0a) &&(h == 1.0)){
            //datarate = 2Mbps deviation = 1Mhz, h = 1
            tx_dev = 1000000;
            if(lo_tmp == 0x00){
                //除2:频段760Mhz ~ 1110Mhz
                ref_diff = 2048;
            }else if(lo_tmp == 0x01){
                //除4:频段380Mhz ~ 550Mhz
                ref_diff = 4096;
            }
        }
        PAN312x_Two_Point_Calibration(symbol_rate_b, tx_dev, ref_diff);
    }else{
        PAN312x_Get_OP_Reg(R157, 1, &tmp);
        tmp |= R157_IB_ONLY_Msk;
        PAN312x_Set_OP_Reg(R157, 1, &tmp);
    }
}

void PAN312x_SyncwordLastByteIgnoreEnable(uint8_t SyncwordMask)
{
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1D5, SyncwordMask);  
}

void PAN312x_PreambleLastByteIgnoreEnable(uint8_t PreambleMask)
{
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1D6, PreambleMask);  
}

uint8_t PAN312x_GetRealSyncwordLastByte(void)
{
    return PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1D7);
}

uint8_t PAN312x_GetRealPreambleLastByte(void)
{
    return PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1D8);
}

void PAN312x_RxMaxPayloadLimitDisable(void)
{
	uint8_t tmp;
	PAN312x_Get_OP_Reg(R31C, 1, &tmp);
	tmp &= ~R31C_REG_MAX_VLD_Msk;
	PAN312x_Set_OP_Reg(R31C, 1, &tmp);
}

void PAN312x_RxMaxPayloadLimitEnable(void)
{
	uint8_t tmp;
	PAN312x_Get_OP_Reg(R31C, 1, &tmp);
	tmp |= R31C_REG_MAX_VLD_Msk;
	PAN312x_Set_OP_Reg(R31C, 1, &tmp);
}

void PAN312x_Reset_Modem(void)
{
    uint8_t tmp = 0;
    tmp |= R100_REG_SOFT_RST_Msk;
    PAN312x_Set_OP_Reg(R100, 1, &tmp);
    tmp &= ~R100_REG_SOFT_RST_Msk;
    PAN312x_Set_OP_Reg(R100, 1, &tmp);
}
void PAN312x_Flush_RxFifo(void)
{
    uint8_t tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1C1);
    tmp |= (PROPERTY_MSK_R1C1_FIFO1_WADDR_CLR | PROPERTY_MSK_R1C1_FIFO1_RADDR_CLR);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1C1, tmp);
    tmp &= ~(PROPERTY_MSK_R1C1_FIFO1_WADDR_CLR | PROPERTY_MSK_R1C1_FIFO1_RADDR_CLR);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1C1, tmp);
}

void PAN312x_Flush_TxFifo(void)
{
    uint8_t tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1C0);
    tmp |= (PROPERTY_MSK_R1C0_FIFO0_WADDR_CLR | PROPERTY_MSK_R1C0_FIFO0_RADDR_CLR);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1C0, tmp);
    tmp &= ~(PROPERTY_MSK_R1C0_FIFO0_WADDR_CLR | PROPERTY_MSK_R1C0_FIFO0_RADDR_CLR);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1C0, tmp);
}


void PAN312x_RadioInit(PAN312xRadioInit* pRadioInitStruct)
{
	//进入 ready 状态;
	PAN312x_Enter_Ready();
    PAN312x_Reset_Modem();
    PAN312x_Set_ModulationType(pRadioInitStruct->ModulationSelect);
    
	//设置频点
	PAN312x_Set_Frequency(pRadioInitStruct->FrequencyBase, pRadioInitStruct->FrequencyStep, pRadioInitStruct->FrequencyChannelNumber);
	//设置tx deviation
	PAN312x_Set_Tx_Deviation(pRadioInitStruct->TxDeviation);
    
    //设置速率
	if(pRadioInitStruct->DataRate > 40000){
        PAN312x_Set_Symbol_RateB(pRadioInitStruct->DataRate, pRadioInitStruct->TxDeviation);
	}else if(pRadioInitStruct->DataRate <= 40000){
		PAN312x_Set_Symbol_RateA(pRadioInitStruct->DataRate / 100);
	}
    
    
    //设置rx deviation
	PAN312x_Set_Rx_Deviation(pRadioInitStruct->RxDeviation);
	
	//设置发射功率
	PAN312x_Set_Power(pRadioInitStruct->FrequencyBase,pRadioInitStruct->FrequencyStep,pRadioInitStruct->FrequencyChannelNumber,pRadioInitStruct->PowerSelect,pRadioInitStruct->Power);
}

void PAN312x_PktInit(PAN321xPacketInit* pPktInitStruct)
{
	//设置Preamble length
	PAN312x_Set_PreambleLength(pPktInitStruct->PreambleLength);
	//设置Preamble pattern
	PAN312x_Set_PreamblePattern(pPktInitStruct->PreambleSeclect);
	//设置Preamble pattern为非标准时，设置相应的非标准的pattern
	if(pPktInitStruct->PreambleSeclect == PREAMBLE_NON_STANDARD){
		PAN312x_Set_NonStandardPreamblePattern(pPktInitStruct->NonStandardPreamblePattern);
	}
	
	//设置syncword pattern 和syncword length
	PAN312x_Set_SyncWordPattern(pPktInitStruct->SyncwordPattern, pPktInitStruct->SyncwordLength);
	
	//设置Preamble Manchester编码
	if(pPktInitStruct->PreambleManchester == S_ENABLE){
		PAN312x_PreambleManchesterEnable();
		PAN312x_Set_PreambleManchesterMode(pPktInitStruct->PreambleManchesterMode);
	}else if(pPktInitStruct->PreambleManchester == S_DISABLE){
		PAN312x_PreambleManchesterDisable();
	}
	
	//设置Syncword Manchester编码
	if(pPktInitStruct->SyncwordManchester == S_ENABLE){
		PAN312x_SyncwordManchesterEnable();
		PAN312x_Set_SyncwordManchesterMode(pPktInitStruct->SyncwordManchesterMode);
	}else if(pPktInitStruct->PreambleManchester == S_DISABLE){
		PAN312x_SyncwordManchesterDisable();
	}
	//设置Payload Manchester编码
	if(pPktInitStruct->PayloadManchester == S_ENABLE){
		PAN312x_PayloadManchesterEnable();
		PAN312x_Set_PayloadManchesterMode(pPktInitStruct->PayloadManchesterMode);
	}else if(pPktInitStruct->PreambleManchester == S_DISABLE){
		PAN312x_PayloadManchesterDisable();
	}
	//设置Haming编码
	PAN312x_Set_FecHamingEncoding(pPktInitStruct->FecEncoding);
	//设置白化
	PAN312x_Set_Payload_Whitening_Pattern(pPktInitStruct->WhiteningPattern);
	//配置direct模式
	if(pPktInitStruct->DataMode == DATA_MODE_DIRECT){
		
	}
}

void PAN312x_CrcInit(PAN312xCrcInit* pCrcInitStruct)
{
	//帧结构中插入crc字段
	PAN312x_CrcInsertSelect(S_ENABLE);
	
	if(pCrcInitStruct->CrcMode == CRC_MODE_8_BIT){
		PAN312x_Set_CrcMode(CRC_MODE_8_BIT);
	}else if(pCrcInitStruct->CrcMode == CRC_MODE_16_BIT){
		PAN312x_Set_CrcMode(CRC_MODE_16_BIT);
	}else if(pCrcInitStruct->CrcMode == CRC_MODE_24_BIT){
		PAN312x_Set_CrcMode(CRC_MODE_24_BIT);
	}else if(pCrcInitStruct->CrcMode == CRC_MODE_32_BIT){
		PAN312x_Set_CrcMode(CRC_MODE_32_BIT);
	}
	
	PAN312x_Set_CrcSeed(pCrcInitStruct->CrcSeed);
	PAN312x_Set_CrcPolynomial(pCrcInitStruct->CrcPolynomial);
	PAN312x_Set_CrcBitOrder(pCrcInitStruct->CrcBitOrder);
	PAN312x_Set_CrcByteSwap(pCrcInitStruct->CrcByteSwap);
	PAN312x_Set_CrcInvert(pCrcInitStruct->CrcBitInv);
    
}

/**
  * @简介：PAN312x的rx初始化
  * @参数：无
  * @返回值：无
  */
void PAN312x_Rx_Init(void)
{
    
    PAN312x_Enter_Ready();
    
    #if DCDC_ENABLE == 1
        PAN312x_DCDC_Enable();
    #endif
	
	
	//PAN312x_Set_RxPacket_Config(0, 0, 1, )
    
    
    PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE | IRQ_MASK_RX_CRC_ERROR), S_ENABLE);
    
    PAN312x_System_Ctrl(SYS_CTRL_AUTO_CLEAR_STATUS);
    
    
    PAN312x_Set_RxTimeOut(400000);      //400ms
    PAN312x_Set_RxTimeout_ExitState(STATE_RX);
    PAN312x_Set_RxInvalid_ExitState(STATE_RX);
    PAN312x_Set_RxValid_ExitState(STATE_RX);

    PAN312x_Enter_Rx(0, START_COND_ENABLE_TIMEOUT, 0);
}



/**
  * @简介：Iomux PAN312x的GPIO功能(只使用GPIO3 ~ GPIO10)
  * @参数：IomuxGpio:
  * @返回值: 无
  */
void PAN312x_Iomux_Gpio_BySpi(uint32_t IomuxGpio)
{
	uint8_t tmp;
	uint16_t reg_addr;
    PAN312x_Write(R005, 0x60);
	reg_addr = (uint16_t)(IomuxGpio & 0x7ff);
    
    tmp = PAN312xReg_ReadB1(reg_addr);
	
	tmp &= ~((uint8_t)(IomuxGpio >> 16));
	
	tmp |= ((uint8_t)(IomuxGpio >> 24));
    
    PAN312xReg_WriteB1(reg_addr, tmp);
    
    PAN312x_Write(R005, 0x00);
}
/**
  * @简介：设置PAN312x的GPIO模式(只使用GPIO3 ~ GPIO10)
  * @参数：GpioPin：
  *        Mode:
  *         0x01: 输出模式
  *         0x00: 输入模式
  * @返回值: 无
  */
void PAN312x_Set_Gpio_Mode_BySpi(uint16_t GpioPin, uint8_t Mode)
{
	uint8_t tmp;
	uint8_t GpioPin3_10 = 0x00;
	GpioPin3_10 = (uint8_t)(GpioPin >> 8);
    
    PAN312x_Write(R005, 0x60);
	
	if(GpioPin3_10 != 0x00){
        //[0x60][0x19]
		tmp = PAN312xReg_ReadB1(R019);
        
		if(Mode == GPIO_INPUT_MODE) {
			tmp &= ~GpioPin3_10;
			PAN312xReg_WriteB1(R019, tmp);
			
			tmp = PAN312xReg_ReadB1(R018);
			tmp |= GpioPin3_10;
			PAN312xReg_WriteB1(R018, tmp);
		}
		else if(Mode == GPIO_OUTPUT_MODE){
			tmp |= GpioPin3_10;
			PAN312xReg_WriteB1(R019, tmp);
		}	
	}
    PAN312x_Write(R005, 0x00);
}
/**
  * @简介：设置PAN312x的GPIO输出高低电平(只使用GPIO3 ~ GPIO10)
  * @参数：GpioPin：
  *        Mode:
  *         0x01: 高电平
  *         0x00: 低电平
  * @返回值: 无
  */
void PAN312x_Gpio_Write_Pin_BySpi(uint16_t GpioPin, uint8_t PinState)
{
	uint8_t tmp;
	uint8_t GpioPin3_10 = 0x00;
	GpioPin3_10 = (uint8_t)(GpioPin >> 8);
	
	PAN312x_Write(R005, 0x60);
	if(GpioPin3_10 != 0x00){
        tmp = PAN312xReg_ReadB1(R017);
		if(PinState == 0) {
			tmp &= ~GpioPin3_10;
		}
		else if(PinState == 1){
			tmp |= GpioPin3_10;
		}
        PAN312xReg_WriteB1(R017, tmp);
	}
    
    PAN312x_Write(R005, 0x00);
}

void PAN312x_Software_Reset(void)
{
    uint8_t tmp = 0;
    //tmp = PAN312xReg_ReadB1(R004);
    tmp |= (R004_REG_NRST_L_Msk | R004_REG_NRST_PIC_Msk);
    PAN312xReg_WriteB1(R004, tmp);
    tmp &= ~((R004_REG_NRST_L_Msk | R004_REG_NRST_PIC_Msk));
    PAN312xReg_WriteB1(R004, tmp);
}

//uint8_t tmp_test;
void PAN312x_SPI3wire_Enable(void)
{
    
    
    PAN312xReg_WriteB1(R005, 0x60);
    //使能3线spi
    PAN312xReg_WriteB1(R00E, 0x84);
    
//    tmp_test = PAN312xReg_ReadB1(R00E);
    PAN312xReg_WriteB1(R005, 0x00);
    
}


void PAN312x_PreambleCadIndEnable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1CB);
	tmp |= PROPERTY_MSK_R1CB_PRE_BUSY_MASK;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1CB, tmp);
}
void PAN312x_PreambleCadIndDisable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1CB);
	tmp &= ~PROPERTY_MSK_R1CB_PRE_BUSY_MASK;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1CB, tmp);
}
void PAN312x_SyncwordCadIndEnable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1CB);
	tmp |= PROPERTY_MSK_R1CB_SW_BUSY_MASK;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1CB, tmp);
}
void PAN312x_SyncwordCadIndDisable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1CB);
	tmp &= ~PROPERTY_MSK_R1CB_SW_BUSY_MASK;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1CB, tmp);
}
void PAN312x_RssiCadIndEnable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1CB);
	tmp |= PROPERTY_MSK_R1CB_RSSI_BUSY_MASK;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1CB, tmp);
}
void PAN312x_RssiCadIndDisable(void)
{
    uint8_t tmp;
	tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1CB);
	tmp &= ~PROPERTY_MSK_R1CB_RSSI_BUSY_MASK;
	PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1CB, tmp);
}


void PAN312x_SetRssiCadIndThreshold(uint8_t threshold)
{
    uint8_t tmp = threshold;
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1AC, tmp);
}



void PAN312x_GpioCmdTxEnable(void)
{
    uint8_t tmp;
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1A4);
    tmp |= PROPERTY_MSK_R1A4_REG_GPIO_TX_MODE;
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1A4, tmp);
}

void PAN312x_GpioCmdTxDisable(void)
{
    uint8_t tmp;
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1A4);
    tmp &= ~PROPERTY_MSK_R1A4_REG_GPIO_TX_MODE;
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1A4, tmp);
}

void PAN312x_GpioCmdRxEnable(void)
{
    uint8_t tmp;
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1A4);
    tmp |= PROPERTY_MSK_R1A4_REG_GPIO_RX_MODE;
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1A4, tmp);
}

void PAN312x_GpioCmdRxDisable(void)
{
    uint8_t tmp;
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1A4);
    tmp &= ~PROPERTY_MSK_R1A4_REG_GPIO_RX_MODE;
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R1A4, tmp);
}


void PAN312x_Set_XthCapTrim(uint8_t TrimCode)
{
    uint8_t tmp;
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R2C7);
    tmp &= ~PROPERTY_MSK_R2C7_XTH_CAP_TRIM;
    tmp |= (TrimCode << PROPERTY_POS_R2C7_XTH_CAP_TRIM);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R2C7, tmp);
}


void PAN312x_WutEnable(void)
{
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R02F, 1, &tmp);
    tmp |= R02F_WUT_EN_Msk;
    PAN312x_Set_OP_Reg(R02F, 1, &tmp);
    
}
void PAN312x_WutDisable(void)
{
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R02F, 1, &tmp);
    tmp &= ~R02F_WUT_EN_Msk;
    PAN312x_Set_OP_Reg(R02F, 1, &tmp);
}


void PAN312x_IomuxGpio3Rcl(void)
{
    uint8_t tmp;
    PAN312x_Get_OP_Reg(R00E, 1, &tmp);
    tmp &= ~R00E_GPIO3_MUX15_SEL_Msk;
    tmp |= (0x02 << R00E_GPIO3_MUX15_SEL_Pos);
    PAN312x_Set_OP_Reg(R00E, 1, &tmp);
    
    PAN312x_Iomux_Gpio(IOMUX_GPIO3_AS_BOD_LVR_RCL_XTL);
}

/**
  * @简介：设置802.15.4g数据包的头文件字段中fcs类型
  * @参数：FcsType：
  *         0x00: CRC32,多项式为0x04C011BB7
  *         0x01: CRC16,多项式为0x1021
  * @返回值: 无
  */
void PAN312x_Set_FcsType(uint8_t FcsType)
{
    uint8_t tmp;
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R11B);
    tmp &= ~PROPERTY_MSK_R11B_REG_M802_FCS;
    tmp |= (FcsType << PROPERTY_POS_R11B_REG_M802_FCS);
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R11B, tmp);
}


/**
  * @简介：通过PAN312x的gpio输出高电平到TCXO的使能引脚，以此来激活TCXO,
  * @参数：GpioPin:只支持GPIO9和GPIO10
  *        PinState:如果TCXO EN高电平有效, 则使能的话PinState = 1, 失能的话PinState = 0;
  *                 如果TCXO EN低电平有效, 则使能的话PinState = 0, 失能的话PinState = 1;
  * @返回值: 无
  * @备注：如果使用TCXO，并且需要PAN3120的GPIO来激活，则需要将此函数PAN312x_Trigger()前面执行；
  */
void PAN312x_TCXO_ControlByGpio(uint16_t GpioPin, uint8_t PinState)
{
    if(PAN312x_GPIO_PIN_9 == GpioPin){
        
        PAN312x_Iomux_Gpio_BySpi(IOMUX_GPIO9_AS_GPIO);
        PAN312x_Set_Gpio_Mode_BySpi(PAN312x_GPIO_PIN_9, GPIO_OUTPUT_MODE);
        PAN312x_Gpio_Write_Pin_BySpi(PAN312x_GPIO_PIN_9,PinState);
    }else if(PAN312x_GPIO_PIN_10 == GpioPin){
        PAN312x_Iomux_Gpio_BySpi(IOMUX_GPIO10_AS_GPIO);
        PAN312x_Set_Gpio_Mode_BySpi(PAN312x_GPIO_PIN_10, GPIO_OUTPUT_MODE);
        PAN312x_Gpio_Write_Pin_BySpi(PAN312x_GPIO_PIN_10,PinState);
    }
}

/**
  * @简介：初始化控制TRxSwitch的GPIO引脚
  * @参数：吴
  * @返回值: 无
  * @备注：TxSwitchEn：GPIO0;
  *        RxSwitchEn：GPIO10; 
  */
void PAN312x_TRxSwitchGpioInit(void)
{
    //配置GPIO0为TXEN  配置GPIO10为RXEN  
	PAN312x_Iomux_Gpio(IOMUX_GPIO10_AS_GPIO);
	PAN312x_Iomux_Gpio(IOMUX_GPIO0_AS_GPIO);
	PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_0|PAN312x_GPIO_PIN_10, GPIO_OUTPUT_MODE);	
}
/**
  * @简介：关闭TxSwitch
  * @参数：无
  * @返回值: 无
  */
void PAN312x_TxSwitchOn(void)
{
    PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_0, 1);
}
/**
  * @简介：关闭TxSwitch
  * @参数：无
  * @返回值: 无
  */
void PAN312x_TxSwitchOff(void)
{
    PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_0, 0);
}
/**
  * @简介：打开RxSwitch
  * @参数：无
  * @返回值: 无
  */
void PAN312x_RxSwitchOn(void)
{
    PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_10, 1);
}
/**
  * @简介：关闭RxSwitch
  * @参数：无
  * @返回值: 无
  */
void PAN312x_RxSwitchOff(void)
{
    PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_10, 0);
}

void PAN312x_Ctk_Two_Point_Calibration(uint32_t DataRate, uint32_t TxDeviation)
{
    uint32_t tx_dev; 
    uint16_t ref_diff;
    uint8_t data_rate_index;
    uint8_t lo_tmp, tmp;
    float h;
  
    h = 2.0f * TxDeviation / DataRate;
    
    //[0x70][0x57][8] 0:带内带外都有 1：单带内模式 
    tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R157);
    tmp &= ~PROPERTY_MSK_R157_IB_ONLY; 
    PAN312x_Set_PropertyB1(PROPERTY_ADDR_R157, tmp);
    
    lo_tmp = PAN312x_Get_PropertyB1(PROPERTY_ADDR_R1B3);
    lo_tmp &= PROPERTY_MSK_R1B3_LO_MUX_SEL;
    if(((DataRate == 200000)&&(h == 1.0))|| ((DataRate == 400000)&&(h == 0.5))){
        //datarate = 200kbps deviation = 100khz, h = 1
        //datarate = 400kbps deviation = 100khz, h = 0.5
        data_rate_index = 0x05;
         //200kbps
        tx_dev = 100000;
        if(lo_tmp == 0x00){
            //除2
            ref_diff = 205;
        }else if(lo_tmp == 0x01){
            //除4
            ref_diff = 410;
        }else if(lo_tmp == 0x02){
            //除6
            ref_diff = 614;
        }else if(lo_tmp == 0x03){
            //除8
            ref_diff = 819;
        }else if(lo_tmp == 0x04){
            //除12
            ref_diff = 1229;
        }
    }else if((DataRate == 200000) &&(h == 0.5)){
        //datarate = 200kbps deviation = 50khz, h = 0.5
        tx_dev = 50000;
        if(lo_tmp == 0x00){
            //除2
            ref_diff = 102;
        }else if(lo_tmp == 0x01){
            //除4
            ref_diff = 205;
        }else if(lo_tmp == 0x02){
            //除6
            ref_diff = 307;
        }else if(lo_tmp == 0x03){
            //除8
            ref_diff = 410;
        }else if(lo_tmp == 0x04){
            //除12
            ref_diff = 614;
        }
    }else if((DataRate == 250000) &&(h == 0.5)){
        //datarate = 250kbps deviation = 62.5khz, h = 0.5
        tx_dev = 62500;
        if(lo_tmp == 0x00){
            //除2
            ref_diff = 128;
        }else if(lo_tmp == 0x01){
            //除4
            ref_diff = 256;
        }else if(lo_tmp == 0x02){
            //除6
            ref_diff = 384;
        }else if(lo_tmp == 0x03){
            //除8
            ref_diff = 512;
        }else if(lo_tmp == 0x04){
            //除12
            ref_diff = 768;
        }
    }
    else if(((DataRate == 250000) &&(h == 1.0)) || (((DataRate == 500000) &&(h == 0.5)))){
        //250kbps 
        //datarate = 250kbps deviation = 125khz, h = 1
        //datarate = 500kbps deviation = 125khz, h = 0.5
        data_rate_index = 0x06;
        //250kbps
        tx_dev = 125000;
        if(lo_tmp == 0x00){
            //除2
            ref_diff = 256;
        }else if(lo_tmp == 0x01){
            //除4
            ref_diff = 512;
        }else if(lo_tmp == 0x02){
            //除6
            ref_diff = 768;
        }else if(lo_tmp == 0x03){
            //除8
            ref_diff = 1024;
        }else if(lo_tmp == 0x04){
            //除12
            ref_diff = 1536;
        }
    }else if((DataRate == 400000) &&(h == 1.0)){
        //400kbps
        //datarate = 400kbps deviation = 200khz, h = 1
        data_rate_index = 0x07;
        //400kbps
        tx_dev = 200000;
        if(lo_tmp == 0x00){
            //除2
            ref_diff = 410;
        }else if(lo_tmp == 0x01){
            //除4
            ref_diff = 819;
        }else if(lo_tmp == 0x02){
            //除6
            ref_diff = 1229;
        }else if(lo_tmp == 0x03){
            //除8
            ref_diff = 1638;
        }
    }else if((DataRate == 500000) &&(h == 1.0)){
         //datarate = 500kbps deviation = 250khz, h = 1
        data_rate_index = 0x08;
        //500kbps
        tx_dev = 250000;
        if(lo_tmp == 0x00){
            //除2
            ref_diff = 512;
        }else if(lo_tmp == 0x01){
            //除4
            ref_diff = 1024;
        }else if(lo_tmp == 0x02){
            //除6
            ref_diff = 1536;
        }else if(lo_tmp == 0x03){
            //除8
            ref_diff = 2048;
        }
    }
    PAN312x_Two_Point_Calibration(data_rate_index, tx_dev, ref_diff);
}


void PAN312x_CTK_Set_Power(uint32_t Frequency, uint8_t SupplyMode, uint32_t InductorPackage, int PowerdBm)
{
    PAN312xPowerSelect PowerSelect;
    
    if((InductorPackage == INDUCTOR_PACKAGE_SMD0603) && (SupplyMode == POWER_SUPPLY_MODE_LDO)){
        PowerSelect = POWER_LDO_0603;
    }else if ((InductorPackage == INDUCTOR_PACKAGE_SMD0402) && (SupplyMode == POWER_SUPPLY_MODE_LDO)){
        PowerSelect = POWER_LDO_0402;
    }else if ((InductorPackage == INDUCTOR_PACKAGE_SMD0603) && (SupplyMode == POWER_SUPPLY_MODE_DCDC)){
        PowerSelect = POWER_DCDC_0603;
    }else if ((InductorPackage == INDUCTOR_PACKAGE_SMD0402) && (SupplyMode == POWER_SUPPLY_MODE_DCDC)){
        PowerSelect = POWER_DCDC_0402;
    }
    
    if((PowerSelect == POWER_LDO_0603) || (PowerSelect == POWER_LDO_0402)){
        if((PowerdBm > 20) || (PowerdBm < -20)){
            while(1);
        }else {
            PowerdBm += 20;
        }
    }else if((PowerSelect == POWER_DCDC_0603) || (PowerSelect == POWER_DCDC_0402)){
        if((PowerdBm > 13) || (PowerdBm < -20)){
            while(1);
        }else {
            PowerdBm += 20;
        }
    }
    uint32_t freq_tmp = Frequency;
    if(freq_tmp >= 420000000 && (freq_tmp <= 445000000)){
        if(PowerSelect == POWER_LDO_0603){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0603_420_445mhz[PowerdBm]);
        }else if(PowerSelect == POWER_LDO_0402){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0402_420_445mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0603){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0603_420_445mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0402){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0402_420_445mhz[PowerdBm]);
        }
    }else if(freq_tmp >= 470000000 && (freq_tmp <= 510000000)){
        if(PowerSelect == POWER_LDO_0603){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0603_470_510mhz[PowerdBm]);
        }else if(PowerSelect == POWER_LDO_0402){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0402_470_510mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0603){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0603_470_510mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0402){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0402_470_510mhz[PowerdBm]);
        }
    }else if(freq_tmp >= 860000000 && (freq_tmp <= 870000000)){
        if(PowerSelect == POWER_LDO_0603){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0603_860_870mhz[PowerdBm]);
        }else if(PowerSelect == POWER_LDO_0402){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0402_860_870mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0603){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0603_860_870mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0402){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0402_860_870mhz[PowerdBm]);
        }
    }else if(freq_tmp >= 902000000 && (freq_tmp <= 928000000)){
        if(PowerSelect == POWER_LDO_0603){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0603_902_928mhz[PowerdBm]);
        }else if(PowerSelect == POWER_LDO_0402){
            PAN312x_Set_Power_Ldo(pan31xx_ldo_power_0402_902_928mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0603){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0603_902_928mhz[PowerdBm]);
        }else if(PowerSelect == POWER_DCDC_0402){
            PAN312x_Set_Power_Dcdc(pan31xx_dcdc_power_0402_902_928mhz[PowerdBm]);
        }
    }
}    


/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
