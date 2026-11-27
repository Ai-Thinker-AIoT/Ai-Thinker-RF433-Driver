# Ai-SG01 (PAN3120) on STM32F103C8T6 + FreeRTOS — PING/PONG Two-Board Test

[![中文](https://img.shields.io/badge/中文-README-blue)](README.zh-CN.md)

FreeRTOS plus the AT firmware, with a built-in automatic PING/PONG test: at power-up the board starts transmitting or receiving by role instead of waiting for UART commands. One PING board and one PONG board are enough to exercise the link.

- Module: Ai-SG01 (PAN3120, plain pinout: nRST = PB0, no GC1131 front-end driver)
- MCU: STM32F103C8T6, 72 MHz
- Project: Keil MDK, `Project.uvprojx`, Device `STM32F103C8`
- UART: USART1 = PA9 / PA10, 115200-8-N-1

---

## 1. Layout

```
STM32F103C8T6-FreeRTOS-Demo/
├── Project.uvprojx
├── build.cmd                  # one-shot PING / PONG build (uses gcc/build.ps1)
├── Start/ Library/ hal_compat/
├── BSP/ PAN312x/ FreeRTOS/
├── User/
│   ├── main.c
│   ├── pingpong_config.h      # the only role switch you need to touch
│   └── at_command_firmware.c  # firmware core (PINGPONG state machine, AT+PINGPONG)
└── Objects/
    ├── Project_PING.hex       # prebuilt: PING (sender)
    ├── Project_PONG.hex       # prebuilt: PONG (receiver)
    └── Project.hex
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

## 3. Role configuration

[`User/pingpong_config.h`](User/pingpong_config.h) has a single setting:

```c
#define PINGPONG_ROLE   1    // 0 = PING sender, 1 = PONG receiver
```

- Default is **1 = PONG**. Flash one board with 0 and the other with 1.
- To avoid touching the source, flash `Objects/Project_PING.hex` / `Project_PONG.hex` directly.
- At runtime `AT+PINGPONG 0|1` switches the role and `AT+PINGPONG?` queries the role and running state.

## 4. Task and parameters

| Item | Value |
|------|-------|
| Task | `AiSG01` (Firmware_Task), 1024-word stack, priority 2 |
| Heap | `configTOTAL_HEAP_SIZE = 12 * 1024` |
| RF | 490.3 MHz, 2FSK, 50 kbps, ±25 kHz, `POWER_LDO_0402` + `POWER_20dBm` |
| TX period | 50 ms (`tx_period`) |

## 5. Build and flash

1. Open `Project.uvprojx` in Keil and build two images by `PINGPONG_ROLE`, or flash the prebuilt hex files.
2. `build.cmd` is the GCC command-line script (`build.cmd 0` / `build.cmd 1`), but it calls `gcc/build.ps1` and **this project does not ship a `gcc/` directory**; to build from the command line, copy it from [`../STM32F103C8T6-FreeRTOS-AT-Command/gcc/`](../STM32F103C8T6-FreeRTOS-AT-Command/gcc/) first.
3. After ST-LINK download watch the counters: PING transmits, PONG replies, and matched growth means the link is healthy.

## 6. Measured log

One board flashed with PONG and one with PING start automatically: `Demo auto-start, role=PONG` / `role=PING`, then `PING Tx` and `PONG Rx` increment packet by packet with `Err: 0`.

![STM32 FreeRTOS Demo test](../../Assets/3.png)

- The `[DBG]` lines are packet-level debug output (mask, FIFO pointer, IRQ state, tries) and are enabled only during debugging.
- The two counters stay in step over a long run with no skipped packets, which indicates a stable link.

## 7. Notes

- This project uses the plain Ai-SG01 pinout and does not include the GC1131 front-end driver; for P-variant hardware use [`../STM32F103C8T6-AT-Command/`](../STM32F103C8T6-AT-Command/).
- CW testing: [`../STM32F103C8T6-FreeRTOS-Single-Carrier/`](../STM32F103C8T6-FreeRTOS-Single-Carrier/); pure AT version: [`../STM32F103C8T6-FreeRTOS-AT-Command/`](../STM32F103C8T6-FreeRTOS-AT-Command/).
