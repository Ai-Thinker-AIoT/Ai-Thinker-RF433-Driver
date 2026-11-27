# Ai-SG01(PAN3120) on STM32F103C8T6 —— AT 指令固件

[![English](https://img.shields.io/badge/English-README-green)](README.md)

安信可 Ai-SG01 模组的出厂式 AT 指令固件：串口收 AT 指令，在线改频点、速率、功率、收发模式，可做定频配置、功耗测试、拉距测试、可靠性测试、GPIO 测试。

- 模组：Ai-SG01（PAN3120，磐启微 Sub-1G 收发器，无射频前端）
- MCU：STM32F103C8T6，HSE 8 MHz → PLL ×9 → 72 MHz
- 工程：STM32CubeMX 生成 + Keil uVision5（`ARM-ADS` 工具链），`MDK-ARM/Ai-SG01.uvprojx`
- 调试串口：USART1 = PA9(TX) / PA10(RX)，115200-8-N-1
- 固件版本：`V4.18_P1.1.2`

---

## 1. 目录结构

```
STM32F103C8T6-AT-Command/
├── Ai-SG01.ioc / .mxproject   # CubeMX 工程描述
├── MDK-ARM/                   # Keil 工程、启动文件、EventRecorder 桩
├── Core/
│   ├── Src/at_command_firmware.c          # AT 指令固件主体（收发链路、配置、Flash 存取）
│   ├── Src/pull_distance_test_firmware.c  # 拉距测试固件源码，未加入工程编译
│   └── Src/stm32f1xx_hal_msp.c / stm32f1xx_it.c / system_stm32f1xx.c
├── BSP/                       # bsp_uart / bsp_timer / bsp_led / bsp_key / bsp_lcd / bsp_flash / bsp_dwt / bsp_queue
├── PAN312x/                   # PAN312x 驱动、HAL 适配、RF CTK 寄存器表
├── Drivers/                   # STM32F1 HAL + CMSIS
└── (AT 手册在仓库根 [`docs/Ai-SG01-AT-Commands.docx`](../../Docs/Ai-SG01-AT-Commands.docx))
```

## 2. 引脚

| PAN312x 信号 | STM32F103C8T6 | 说明 |
|--------------|---------------|------|
| CSN | PA4 | 软件片选 |
| SCK | PA5 | SPI1_SCK |
| MISO | PA6 | SPI1_MISO |
| MOSI | PA7 | SPI1_MOSI |
| nRST | PB0 | 复位，低有效 |
| DIO8 / IRQ | PB1 | 中断输入 |
| 其余 DIO / GPIO | PB10、PB11、PA11、PA12、PB14 | 由 AT+GPIOMODE / AT+GPIOWRITE / AT+GPIOREAD 读写 |

USART1：PA9 / PA10。完整对照表见仓库根目录 [`docs/wiring.zh-CN.md`](../../Docs/wiring.zh-CN.md)。

## 3. 默认射频参数

| 项目 | 默认值 |
|------|--------|
| 频率 | `490300000` Hz（490.3 MHz） |
| 调制 | 2FSK |
| 速率 | 50 kbps |
| 频偏 | TX / RX 均 25 kHz |
| 功率档 | `POWER_LDO_0402` + `POWER_20dBm` |
| 发包模式 | `tx_mode = 2`，周期 50 ms |
| 配置存储 | Flash `0x0800FC00`（最后一页），带 CRC 校验 |

改参数后 `AT+CONFIGSAVE` 写入 Flash，`AT+CONFIGRESET` 恢复出厂。

## 4. AT 指令

`AT+HELP` 可打印全表。常用项：

- 收发：`AT+RFMODE`（TX/RX）、`AT+TXMODE`、`AT+TXSTART` / `AT+TXSTOP`、`AT+TXPERIOD`
- 射频：`AT+FREQUENCYBASE`、`AT+DATARATE`、`AT+POWERDBM`、`AT+POWERSELECT`
- 测试：`AT+ENTERCARRIER`（单载波）、`AT+FTMASTER` / `AT+FTSLAVE`（产测主从）、`AT+CLEARCNT`
- 系统：`AT+SLEEPMODE` / `AT+WAKEUP`、`AT+RESET`、`AT+GPIOMODE` / `AT+GPIOWRITE` / `AT+GPIOREAD`、`AT+CONFIGSAVE` / `AT+CONFIGRESET`

逐条说明见仓库根目录 [`docs/Ai-SG01-AT-Commands.docx`](../../Docs/Ai-SG01-AT-Commands.docx)。

## 5. 编译与烧录

1. Keil uVision5 打开 `MDK-ARM/Ai-SG01.uvprojx`（Device = `STM32F103C8`，Define 含 `USE_HAL_DRIVER,STM32F103xB`）。
2. Rebuild，已勾选 Create HEX File，产物为 [`MDK-ARM/`](MDK-ARM/) 下的 hex（OutputName `at_command_firmware`）。
3. ST-LINK 烧录：3V3 / SWCLK / SWDIO / GND，与 LoRa-Kit 底板 pin2pin 连接。
4. 上电后串口 115200 打印启动信息，发送 `AT` 或 `AT+HELP` 确认链路。

## 6. 备注

- 本工程是 Ai-SG01 与 Ai-SG01-P 共用的 AT 框架来源；P 版固件见 [`../../Ai-SG01-P/STM32F103C8T6-AT-Command/`](../../Ai-SG01-P/STM32F103C8T6-AT-Command/)，差异在 GC1131 前端与功率口径。
- 底板为 LoRa-Kit V1.0.0 + Ai-SG01 转接板，pin2pin 连接。
- `pull_distance_test_firmware.c` 只是留档参考，不参与编译；做拉距测试时自行替换 `at_command_firmware.c` 入工程。
