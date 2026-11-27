# Ai-SG01-P (PAN3120 + GC1131) on STM32F103C8T6 — AT Command Firmware

[![中文](https://img.shields.io/badge/中文-README-blue)](README.zh-CN.md)

AT command firmware for the Ai-SG01-P module. The AT framework is the same as the Ai-SG01 version, but it additionally drives the GC1131 RF front end (PA/LNA) and converts the reported power to the front-end output.

- Module: Ai-SG01-P (PAN3120 + GC1131)
- MCU: STM32F103C8T6, HSE 8 MHz → PLL ×9 → 72 MHz
- Project: STM32CubeMX + Keil uVision5 (`ARM-ADS`), `MDK-ARM/Ai-SG01-P.uvprojx`
- Debug UART: USART1 = PA9 / PA10, 115200-8-N-1
- Firmware version: `V4.18_P1.1.2`

---

## 1. Layout

```
STM32F103C8T6-AT-Command/
├── Ai-SG01-P.ioc / .mxproject
├── MDK-ARM/                   # Ai-SG01-P.uvprojx, startup_stm32f103xb.s
├── Core/Src/
│   ├── at_command_firmware.c  # AT firmware core, calls bsp_InitGC1131() at boot
│   └── stm32f1xx_hal_msp.c / stm32f1xx_it.c / system_stm32f1xx.c
├── BSP/                       # includes bsp_gc1131.c/.h (GC1131 mode control)
├── PAN312x/                   # PAN312x driver + HAL adaptation (P-variant GPIO remap)
├── Drivers/
└── (AT manual at repo root [`Docs/Ai-SG01-P-AT-Commands.docx`](../../Docs/Ai-SG01-P-AT-Commands.docx))
```

## 2. Pins

| Signal | STM32F103C8T6 | Note |
|--------|---------------|------|
| CSN | PA4 | PAN3120 chip select |
| SCK / MISO / MOSI | PA5 / PA6 / PA7 | SPI1 |
| nRST | PB14 | reset pin on the P variant (PB0 on the plain version) |
| DIO8 / IRQ | PB1 | interrupt input |
| GC1131 CPS | PB0 | power-save / bypass control |
| GC1131 CSD | PB11 | front-end enable |
| GC1131 CTX | PA11 (GPIO2) | TX/RX switch |
| DIO0 / DIO2 / DIO10 | — | unused on the P variant |

USART1: PA9 / PA10. GC1131 has four modes — `SHUTDOWN` / `RECEIVE` / `TRANSMIT_BYPASS` / `TRANSMIT` — switched by `bsp_gc1131.c` according to the TX/RX state.

## 3. Differences from the Ai-SG01 version

| Item | Ai-SG01 | Ai-SG01-P |
|------|---------|-----------|
| RF front end | none | GC1131 (PA/LNA) |
| Power reporting | chip setting | chip setting + `POWER_OFFSET 27` dB, printed by `+POWERDBM` |
| `+POWERSELECT` | inductor tier only | also constrains the power tier; illegal combinations return `+POWERDBM:4` |
| Startup | `bsp_Init()` | `bsp_Init()` + `bsp_InitGC1131()` |
| Reset pin | PB0 | PB14 |

## 4. Default RF settings

| Item | Default |
|------|---------|
| Frequency | 490.3 MHz (`490300000` Hz) |
| Modulation | 2FSK |
| Data rate | 50 kbps |
| Deviation | 25 kHz |
| Power tier | `POWER_LDO_0402` + `POWER_20dBm` |
| Config storage | Flash `0x0800FC00`, CRC protected |

The AT command set is identical to the Ai-SG01 version (`AT+RFMODE`, `AT+FREQUENCYBASE`, `AT+DATARATE`, `AT+POWERDBM`, `AT+POWERSELECT`, `AT+ENTERCARRIER`, `AT+FTMASTER/FTSLAVE`, `AT+CONFIGSAVE`, and so on); see [`Docs/Ai-SG01-P-AT-Commands.docx`](../../Docs/Ai-SG01-P-AT-Commands.docx).

## 5. Build and flash

1. Open `MDK-ARM/Ai-SG01-P.uvprojx` in Keil, Device `STM32F103C8`, defines `USE_HAL_DRIVER,STM32F103xB`.
2. Rebuild (OutputName `Ai-SG01-P`, Create HEX File enabled).
3. Flash with ST-LINK: 3V3 / SWCLK / SWDIO / GND.
4. On power-up the UART should print the firmware version and the GC1131 init result; send `AT+HELP` to verify.

## 6. Notes

- Do **not** flash this firmware onto a plain Ai-SG01: it drives CPS/CSD/CTX pins that do not exist there, so the front-end state cannot be confirmed.
- Power reading = chip setting + 27 dB offset. It is for side-by-side comparison within the same model, not a calibrated absolute value; certification measurements must be taken with a spectrum analyser.
- The version without the front end is in [`../../Ai-SG01/STM32F103C8T6-AT-Command/`](../../Ai-SG01/STM32F103C8T6-AT-Command/).
