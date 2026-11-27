# Ai-SG01 (PAN3120) on STM32F103C8T6 + FreeRTOS — Single-Carrier (CW) Test

[![中文](https://img.shields.io/badge/中文-README-blue)](README.zh-CN.md)

FreeRTOS plus the AT firmware with `CARRIER_AUTO_ON_BOOT` enabled: **on power-up it enters an unmodulated single carrier** (the same state as `AT+ENTERCARRIER`, held indefinitely) for carrier power, frequency tolerance and spurious measurements. The scheduler keeps running, which demonstrates that the RF state is not rewritten when an RTOS is present.

- Module: Ai-SG01 (PAN3120, plain pinout: nRST = PB0, no GC1131 front-end driver)
- MCU: STM32F103C8T6, 72 MHz
- Project: Keil MDK, `Project.uvprojx`, ARM-GNU toolchain
- UART: USART1 = PA9 / PA10, 115200-8-N-1

---

## 1. Layout

```
STM32F103C8T6-FreeRTOS-Single-Carrier/
├── Project.uvprojx
├── build.cmd                  # one-shot GCC build (clean rebuilds all)
├── gcc/                       # startup file, linker script, syscalls, build.ps1
├── Start/ Library/ hal_compat/
├── BSP/ PAN312x/ FreeRTOS/
├── User/
│   ├── main.c
│   ├── carrier_config.h       # CARRIER_AUTO_ON_BOOT (default 1)
│   ├── pingpong_config.h      # Demo role kept, inactive in CW mode
│   ├── at_command_firmware.c  # firmware core + Carrier_Enter_*
│   └── stm32f10x_it.c / stm32f10x_conf.h
└── Objects/
```

## 2. Pins

| Signal | STM32F103C8T6 |
|--------|---------------|
| CSN / SCK / MISO / MOSI | PA4 / PA5 / PA6 / PA7 |
| nRST | PB0 |
| DIO8 / IRQ | PB1 |
| other DIO / GPIO | PB10, PB11, PA11, PA12, PB14 |
| GREEN_LED / BLUE_LED | PA8 / PB15 |
| USART1 | PA9 / PA10 |

## 3. Carrier configuration

[`User/carrier_config.h`](User/carrier_config.h):

```c
#define CARRIER_AUTO_ON_BOOT   1   // 1 = enter CW at boot; 0 = back to the Demo auto test
```

At startup `Carrier_Enter_Default()` stops Timer1 / Timer2, shuts down the PINGPONG state machine, clears the wake-up flag, then calls `Carrier_Enter_Now()` and sets `g_carrier_active`, after which no other mechanism may rewrite the RF state.

| Item | Value |
|------|-------|
| Frequency | 490.3 MHz (`FrequencyBase = 490300000`) |
| Modulation | 2FSK (no modulation data loaded in CW) |
| Data rate / deviation | 50 kbps / 25 kHz (not visible in CW) |
| Power | `POWER_LDO_0402` + `POWER_20dBm` |
| Config | Flash `0x0800FC00`, CRC protected |

## 4. Task structure

| Item | Value |
|------|-------|
| Task | `AiSG01` (Firmware_Task), 1024-word stack, priority 2 |
| Heap | `configTOTAL_HEAP_SIZE = 12 * 1024` |
| UART | 115200-8-N-1; AT queries still work, but the RF state is locked in carrier mode |

## 5. Build and flash

1. Open `Project.uvprojx` in Keil and Rebuild; or from the command line:

```powershell
.\build.cmd          # build
.\build.cmd clean    # full rebuild
```

2. Output `gcc/build/Project.elf` / `Project.hex` (Keil builds put them in `Objects/`).
3. Download with ST-LINK; the carrier starts at power-up. Connect a spectrum analyser to check frequency, power and spurious emissions.

## 6. Spectrum measurement (narrow-span sweep)

Keysight swept spectrum analyser, Ref 30 dBm / 10 dB/div / 40 dB attenuation, centre 490.30 MHz, span 25 kHz, RBW = VBW 240 Hz; marker `Mkr1 490.297778 MHz`, peak **24.73 dBm**.

![STM32 single carrier, 490.30 MHz / 24.73 dBm](../../Assets/4.jpg)

- A single line with no modulation sidebands, as expected for CW; OBW must be measured separately with continuous modulated transmission.
- About 1.2 dB higher than the AI8051U single-carrier project; compare on the same board, antenna and power tier.
- The measured frequency is about 2.4 kHz below the setting, within crystal tolerance; use the measured value in the report.

## 7. Notes

- An unmodulated carrier is a single line and **cannot** be used for occupied bandwidth; OBW needs continuous modulated transmission, which this project does not provide.
- Boards that already saved a Flash config read back the old frequency/power; run `AT+CONFIGRESET` or change the `DeviceConfig_Init()` defaults before flashing.
- This project uses the plain Ai-SG01 pinout and does not include the GC1131 front-end driver; for P-variant hardware use [`../STM32F103C8T6-AT-Command/`](../STM32F103C8T6-AT-Command/).
