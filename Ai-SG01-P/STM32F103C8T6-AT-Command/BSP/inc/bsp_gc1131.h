#ifndef __BSP_GC1131_H
#define __BSP_GC1131_H

#include "bsp.h"

//GC1131模式控制
typedef enum {
    GC1131_MODE_SHUTDOWN = 0,
    GC1131_MODE_RECEIVE,
    GC1131_MODE_TRANSMIT_BYPASS,
    GC1131_MODE_TRANSMIT
} GC1131_ModeTypeDef;

/* 供外部调用的函数声明 */
void bsp_InitGC1131(void);
#if 0
void GC1131_CPS_On(void);
void GC1131_CPS_Off(void);
void GC1131_CTX_On(void);
void GC1131_CTX_Off(void);
uint8_t Get_CPS_Level(void);
#endif

void PAN312x_GC1131_Set_Mode(GC1131_ModeTypeDef mode);

#endif
