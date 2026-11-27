# Ai-SG01-P (PAN3120 + GC1131) on AI8051U — AT Firmware + PING/PONG Test

[![中文](https://img.shields.io/badge/中文-README-blue)](README.zh-CN.md)

The AT command firmware ported to AI8051U, with a built-in PING/PONG two-board test: after power-up the boards transmit and receive by role, no AT commands needed.

- Module: Ai-SG01-P (PAN3120 + GC1131)
- MCU: AI8051U-34K64, 33.1776 MHz, Keil C51 (C351 compiler, Device `STC8051U-8Bit Series`)
- Project: `AI8051U-AISG01.uvproj`
- Debug UART: UART1 = P3.7 (TX) / P3.6 (RX), 115200-8-N-1 (33177600/9/32, TH1 = 0xF7, zero error)

---

## 1. Layout

```
AI8051U-Demo/
├── AI8051U-AISG01.uvproj      # Keil C51 project
├── Source/
│   ├── main.c                 # entry, only calls Firmware_App()
│   ├── firmware/at_command_firmware.c  # AT firmware core (PINGPONG state machine and AT+PINGPONG)
│   ├── bsp/                   # bsp.c, bsp_uart, bsp_timer, bsp_led, bsp_flash
│   ├── pan312x/               # PAN312x driver, HAL adaptation, RF CTK tables
│   ├── hal_compat/            # maps STM32 HAL calls onto 8051 ports
│   └── XSFR_STC8051U_8Bit.H   # register / port definitions
├── Listings/                  # build intermediates
├── Objects/AI8051U-AISG01.hex # prebuilt firmware
└── README.md
```

## 2. Pins

| Signal | AI8051U | Note |
|--------|---------|------|
| CSN | P1.4 | software chip select (SPI group S0=0/S1=0) |
| MOSI | P1.5 | push-pull output |
| MISO | P1.6 | high-impedance input |
| SCLK | P1.7 | software SPI clock |
| nRST | P3.5 | reset, active low |
| DIO8 / IRQ | P3.2 | interrupt input |
| second GPIO | P3.3 | callback placeholder (token = GPIO_PIN_5) |
| UART1 TX / RX | P3.7 / P3.6 | 115200-8-N-1 |
| GREEN_LED / BLUE_LED | P2.0 / P2.1 | active high |

## 3. Role configuration (PING / PONG)

`g_pingpong_role` defaults to **1 = PONG (receiver)**, set by `PINGPONG_ROLE_DEFAULT` in [`Source/firmware/at_command_firmware.c`](Source/firmware/at_command_firmware.c):

```c
#define PINGPONG_ROLE_DEFAULT 1   // 0 = PING sender, 1 = PONG receiver
```

- Flash two boards, one with 0 and one with 1; they start testing automatically: PING sends and waits for a reply, PONG answers, and the loop continues.
- At runtime `AT+PINGPONG 0|1` switches the role and `AT+PINGPONG?` queries the role and running state.
- The UART prints TX/RX counters so you can judge link stability.

## 4. RF settings

Same defaults as the STM32 version: 490.3 MHz, 2FSK, 50 kbps, 25 kHz deviation, `POWER_LDO_0402` + `POWER_20dBm`, 50 ms TX period; the config is stored in the last Flash page and applied by `AT+CONFIGSAVE` / `AT+CONFIGRESET`. `AT+HELP` prints the full AT table.

## 5. Build and flash

1. Open `AI8051U-AISG01.uvproj` in Keil C51 (with the C351 compiler), Device `STC8051U-8Bit Series`.
2. Rebuild; the output is `Objects/AI8051U-AISG01.hex` (a copy is included in the repo).
3. Download with STC-ISP; AI8051U needs a cold start / power cycle as prompted.
4. Flash the two boards with roles 0 / 1 and watch the test counters over UART.

## 6. Measured log

Two AI8051U boards (`COM10` / `COM26`) flashed with PONG / PING start testing automatically: `PONG Rx` and `PING Tx` counters grow together, `Err: 0`, RSSI about -71 dBm.

![AI8051U Demo test](../../Assets/4.png)

- Several hundred packets ran without a non-zero `Err`, so the 8051 software SPI plus interrupt callback does not drop interrupts in bidirectional traffic.
- The counter difference stays within 1, which is a normal packet in flight.

## 7. Notes

- If you only need AT commands without the automatic test, the role logic does not get in the way; for CW testing use [`../AI8051U-Single-Carrier/`](../AI8051U-Single-Carrier/).
- The equivalent test on STM32 is in [`../STM32F103C8T6-FreeRTOS-Demo/`](../STM32F103C8T6-FreeRTOS-Demo/).
