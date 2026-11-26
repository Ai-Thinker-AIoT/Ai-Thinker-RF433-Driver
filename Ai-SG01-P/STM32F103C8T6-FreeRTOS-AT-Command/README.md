# Ai-SG01(PAN3120) on STM32F103C8T6 + FreeRTOS —— AT 指令固件

把 Ai-SG01 的 AT 固件原封不动搬进 FreeRTOS 任务里跑：`bsp_Init()` 后创建任务，任务内调用原固件入口 `Firmware_App()`。AT 行为与裸机版一致，用来验证调度器、串口、中断和射频驱动共存。

- 模组：Ai-SG01（PAN3120，按普通版引脚定义：nRST = PB0，不含 GC1131 前端驱动）
- MCU：STM32F103C8T6，HSE 8 MHz → PLL ×9 → 72 MHz
- 工程：Keil MDK（**ARM-GNU / arm-none-eabi-gcc** 工具链），`Project.uvprojx`，Device `STM32F103C8`
- 调试串口：USART1 = PA9 / PA10，115200-8-N-1

---

## 1. 目录结构

```
STM32F103C8T6-FreeRTOS-AT-Command/
├── Project.uvprojx            # Keil 工程（ARM-GNU）
├── gcc/                       # startup_stm32f10x_md.s、stm32f103c8.ld、syscalls.c、build.ps1
├── Start/                     # core_cm3、system_stm32f10x
├── Library/                   # STM32F10x 标准外设库
├── hal_compat/                # 把 HAL 调用适配到标准外设库
├── BSP/                       # bsp_uart / bsp_led / bsp_timer / bsp_flash
├── PAN312x/                   # PAN312x 驱动 + HAL 适配（nRST PB0）
├── FreeRTOS/                  # 内核 + FreeRTOSConfig.h（heap 12 KB）
├── User/
│   ├── main.c                 # bsp_Init() → 建任务 → 启动调度器
│   ├── at_command_firmware.c  # 原固件，main 已改名 Firmware_App()
│   └── stm32f10x_it.c / stm32f10x_conf.h
└── Objects/                   # 编译产物
```

## 2. 引脚

| 信号 | STM32F103C8T6 |
|------|---------------|
| CSN / SCK / MISO / MOSI | PA4 / PA5 / PA6 / PA7 |
| nRST | PB0 |
| DIO8 / IRQ | PB1 |
| 其余 DIO / GPIO | PB10、PB11、PA11、PA12、PB14 |
| GREEN_LED / BLUE_LED | PA8 / PB15 |
| USART1 | PA9 / PA10 |

## 3. 任务结构

| 任务 | 栈（字） | 优先级 | 行为 |
|------|----------|--------|------|
| `AiSG01`（Firmware_Task） | 1536 | 2 | 调 `Firmware_App()`，正常不返回 |

- `main()` 先 `bsp_Init()`，再打印 `bsp_Init OK` 并翻转 GREEN LED，然后 `xTaskCreate`、`vTaskStartScheduler()`。
- 任务创建失败会打印 `xTaskCreate FAILED (heap?)` 并点亮 BLUE LED。
- `configTOTAL_HEAP_SIZE = 12 * 1024`；栈从 1024 调到 1536，避免原固件深调用链溢出。

## 4. 固件行为

- 射频默认：490.3 MHz、2FSK、50 kbps、±25 kHz 频偏、`POWER_LDO_0402` + `POWER_20dBm`，配置存 Flash `0x0800FC00`。
- AT 指令集与裸机版相同：`AT+RFMODE`、`AT+FREQUENCYBASE`、`AT+DATARATE`、`AT+TXSTART/TXSTOP`、`AT+ENTERCARRIER`、`AT+FTMASTER/FTSLAVE`、`AT+CONFIGSAVE/RESET` 等。
- 本工程**没有** PINGPONG 自动对测，也没有开机自动单载波；需要时用同目录的 [`../STM32F103C8T6-FreeRTOS-Demo/`](../STM32F103C8T6-FreeRTOS-Demo/)、[`../STM32F103C8T6-FreeRTOS-Single-Carrier/`](../STM32F103C8T6-FreeRTOS-Single-Carrier/)。

## 5. 编译与烧录

1. Keil 打开 `Project.uvprojx`（已配置 ARM-GNU 工具链，启动文件与链接脚本都在 [`gcc/`](gcc/)）。
2. 命令行可复现构建：

```powershell
powershell -ExecutionPolicy Bypass -File .\gcc\build.ps1
```

3. 产物 `Objects/Project.elf` / `Project.hex`；ST-LINK 下载后先看串口 `bsp_Init OK`。
4. 更多 GCC 构建细节见 [`gcc/README.md`](gcc/README.md)。

## 6. 实测日志

双板各跑一份固件，上电从 Flash 读回配置（`FrequencyBase 490300000`、`DataRate 50000`、TX/RX 频偏 25000 Hz、`PowerSelect 0x00`、`Power 20 dBm`、TX Mode 2、RF Mode 2），随后持续输出收发计数。

![FreeRTOS AT 固件串口日志](../../Assets/2.png)

- 配置区打印说明 `DeviceConfig_Load()` 正常，Flash 里的 CRC `0x049B` 与结构体匹配。
- 左右两侧 `Cnt` 连续增长、`Err_Cnt` 保持 0，说明 FreeRTOS 任务里跑 AT 固件时串口与射频都没被调度打断。

## 7. 备注

- 本工程按**普通 Ai-SG01** 引脚（nRST PB0）定义，未包含 GC1131 前端驱动；烧到 Ai-SG01-P 时前端不会被初始化，收发功率与旁路状态都不可控。
- 中断向量由 [`gcc/startup_stm32f10x_md.s`](gcc/startup_stm32f10x_md.s) 与 FreeRTOS 端口接管，不要在 `stm32f10x_it.c` 里重复实现 `SVC/PendSV/SysTick`。
