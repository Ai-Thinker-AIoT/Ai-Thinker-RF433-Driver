# Ai-SG01-P(PAN3120 + GC1131) on STM32F103C8T6 —— AT 指令固件

[![English](https://img.shields.io/badge/English-README-green)](README.md)

Ai-SG01-P 模组的 AT 指令固件。AT 框架与 Ai-SG01 版相同，额外驱动 GC1131 射频前端（PA/LNA），并把功率上报口径换算到前端输出端。

- 模组：Ai-SG01-P（PAN3120 + GC1131）
- MCU：STM32F103C8T6，HSE 8 MHz → PLL ×9 → 72 MHz
- 工程：STM32CubeMX 生成 + Keil uVision5（`ARM-ADS`），`MDK-ARM/Ai-SG01-P.uvprojx`
- 调试串口：USART1 = PA9 / PA10，115200-8-N-1
- 固件版本：`V4.18_P1.1.2`

---

## 1. 目录结构

```
STM32F103C8T6-AT-Command/
├── Ai-SG01-P.ioc / .mxproject
├── MDK-ARM/                   # Ai-SG01-P.uvprojx、startup_stm32f103xb.s
├── Core/Src/
│   ├── at_command_firmware.c  # AT 固件主体，启动时调 bsp_InitGC1131()
│   └── stm32f1xx_hal_msp.c / stm32f1xx_it.c / system_stm32f1xx.c
├── BSP/                       # 含 bsp_gc1131.c/.h（GC1131 模式控制）
├── PAN312x/                   # PAN312x 驱动 + HAL 适配（P 版 GPIO 重映射）
├── Drivers/
└── (AT 手册在仓库根 [`docs/Ai-SG01-P-AT-Commands.docx`](../../Docs/Ai-SG01-P-AT-Commands.docx))
```

## 2. 引脚

| 信号 | STM32F103C8T6 | 说明 |
|------|---------------|------|
| CSN | PA4 | PAN3120 片选 |
| SCK / MISO / MOSI | PA5 / PA6 / PA7 | SPI1 |
| nRST | PB14 | P 版复位脚（普通版为 PB0） |
| DIO8 / IRQ | PB1 | 中断输入 |
| GC1131 CPS | PB0 | 省电/旁路控制 |
| GC1131 CSD | PB11 | 前端使能 |
| GC1131 CTX | PA11（GPIO2） | 收发切换 |
| DIO0 / DIO2 / DIO10 | — | P 版不再使用 |

USART1：PA9 / PA10。GC1131 四种模式：`SHUTDOWN` / `RECEIVE` / `TRANSMIT_BYPASS` / `TRANSMIT`，由 `bsp_gc1131.c` 按收发状态切换。

## 3. 与 Ai-SG01 版的差异

| 项目 | Ai-SG01 | Ai-SG01-P |
|------|---------|-----------|
| 射频前端 | 无 | GC1131（PA/LNA） |
| 功率上报 | 芯片设定值 | 叠加 `POWER_OFFSET 27` dB 后打印 `+POWERDBM` |
| `+POWERSELECT` | 只切电感档 | 同时约束功率档，非法组合返回 `+POWERDBM:4` |
| 启动 | `bsp_Init()` | `bsp_Init()` + `bsp_InitGC1131()` |
| 复位脚 | PB0 | PB14 |

## 4. 默认射频参数

| 项目 | 默认值 |
|------|--------|
| 频率 | 490.3 MHz（`490300000` Hz） |
| 调制 | 2FSK |
| 速率 | 50 kbps |
| 频偏 | 25 kHz |
| 功率档 | `POWER_LDO_0402` + `POWER_20dBm` |
| 配置存储 | Flash `0x0800FC00`，带 CRC |

AT 指令集与 Ai-SG01 版一致（`AT+RFMODE`、`AT+FREQUENCYBASE`、`AT+DATARATE`、`AT+POWERDBM`、`AT+POWERSELECT`、`AT+ENTERCARRIER`、`AT+FTMASTER/FTSLAVE`、`AT+CONFIGSAVE` 等），详见仓库根目录 [`docs/Ai-SG01-P-AT-Commands.docx`](../../Docs/Ai-SG01-P-AT-Commands.docx)。

## 5. 编译与烧录

1. Keil 打开 `MDK-ARM/Ai-SG01-P.uvprojx`，Device `STM32F103C8`，`USE_HAL_DRIVER,STM32F103xB`。
2. Rebuild（OutputName `Ai-SG01-P`，已勾选 Create HEX File）。
3. ST-LINK 烧录，3V3 / SWCLK / SWDIO / GND。
4. 上电串口应能看到固件版本与 GC1131 初始化结果，再发 `AT+HELP` 验证。

## 6. 备注

- **不要**把本固件烧到普通 Ai-SG01：它会去驱动不存在的 CPS/CSD/CTX 引脚，前端状态无法确认。
- 功率读数 = 芯片设定 + 27 dB 偏移，只用于同型号横向比较，不是校准后的绝对功率；认证测试须用频谱仪实测。
- 无前端版工程见 [`../../Ai-SG01/STM32F103C8T6-AT-Command/`](../../Ai-SG01/STM32F103C8T6-AT-Command/)。
