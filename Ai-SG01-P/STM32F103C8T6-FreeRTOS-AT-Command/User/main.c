/**
  ******************************************************************************
  * @file    main.c
  * @brief   FreeRTOS entry point for the Ai-SG01 PAN312x AT firmware on
  *          STM32F103C8T6.
  *
  * @note    The original firmware's main() has been renamed to Firmware_App()
  *          (see at_command_firmware.c). Here we bring up the board with
  *          bsp_Init() and then run the firmware inside a FreeRTOS task.
  *
  *          The system clock (HSE 8 MHz * PLL9 = 72 MHz) and SysTick (FreeRTOS
  *          tick) are configured by the startup file and the FreeRTOS port
  *          respectively; this file owns neither.
  ******************************************************************************
  */
#include "bsp.h"
#include "FreeRTOS.h"
#include "task.h"

/* 原固件逻辑（at_command_firmware.c 中已将 main 重命名为 Firmware_App） */
extern int Firmware_App(void);

static TaskHandle_t g_firmwareTask = NULL;

/* 固件任务：运行 Ai-SG01 的 AT 指令固件 */
static void Firmware_Task(void *pvParameters)
{
    (void)pvParameters;

    Firmware_App();   /* 正常不会返回；若返回则删除任务 */

    vTaskDelete(NULL);
}

int main(void)
{
    /* 注意：系统时钟已在启动文件 system_stm32f10x.c 中配置为 72MHz，
       bsp_Init 内不再重复配置。 */
    bsp_Init();

    /* 最早的心跳：证明启动/时钟/串口都正常。若串口完全看不到这句，
     * 说明故障发生在 bsp_Init 之前（启动/时钟/链接）或串口本身未就绪 */
    printf("bsp_Init OK\r\n");
    bsp_LedToggle(0);   /* GREEN LED 闪一下 */

    /* 创建固件任务并启动调度器 */
    if (xTaskCreate(Firmware_Task,
                   "AiSG01",
                   1536,       /* 任务栈深度（单位：字）。原 1024 偏小、2048 又把 12KB 堆挤爆，取折中 */
                   NULL,
                   2,
                   &g_firmwareTask) != pdPASS)
    {
        printf("xTaskCreate FAILED (heap?)\r\n");
        bsp_LedOn(1);   /* BLUE LED 常亮 = 任务创建失败 */
    }

    vTaskStartScheduler();

    /* 调度器启动失败才会执行到这里 */
    for (;;)
    {
    }
}
