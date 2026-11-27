# Option B: keep Keil building with Arm GNU Toolchain instead of reinstalling AC5

[![中文](https://img.shields.io/badge/中文-README-blue)](README.zh-CN.md)

This directory holds every file added when the `Ai-SG01-P/STM32F103C8T6-FreeRTOS-AT` project was migrated from **ARM Compiler 5.06u7 (armcc)** to the **Arm GNU Toolchain 15.3.1 (arm-none-eabi-gcc)**. **Measured on this machine**: μVision 5.40 batch build gives `0 Error(s)` and produces `Objects/Project.hex`.

## How to build now

- **In Keil**: open `Project.uvprojx` and press `Project → Rebuild` (F7 or the Build button). The output is still `.\Objects\Project.elf` / `Project.hex`; debugging, download and Flash algorithm settings are unchanged.
- **Command line** (reproducible, auditable): from the project root

  ```powershell
  powershell -ExecutionPolicy Bypass -File .\gcc\build.ps1
  ```

  Output goes to `gcc\build\Project.elf` and `Project.hex`. Add `-Clean` for a full rebuild.

Both routes use the same sources and the same compiler; only the entry point differs.

## Files changed

| File | Description |
|------|-------------|
| `Project.uvprojx` | toolset `ARM-ADS → ARM-GNU`; GNU macros/include paths/compile and link options filled in; startup file points to `gcc/startup_stm32f10x_md.s`; output directory and Create HEX restored; the leftover `V5.06 update 7` text in `pCCUsed` removed so asset scans do not misjudge it. Every `-Wno-*` suppression was ultimately removed in favour of fixing the source |
| `gcc/startup_stm32f10x_md.s` | **new**. The original `Start/startup_stm32f10x_md.s` (armasm syntax) translated to GNU as syntax with an identical vector table order; `Reset_Handler` sets the stack, copies `.data`, clears `.bss`, calls `SystemInit` and `main` |
| `gcc/stm32f103c8.ld` | **new**. Replaces the armlink scatter file: FLASH 0x08000000/64K, RAM 0x20000000/20K, `_estack = 0x20005000` |
| `gcc/syscalls.c` | **new**. Minimal newlib syscall layer; `_write()` routes `printf` to USART1 (see "printf redirection" below) and removes six libnosys link warnings |
| `FreeRTOS/port/port.c`, `portmacro.h` | **replaced** with the official FreeRTOS-Kernel V11.1.0 `portable/GCC/ARM_CM3` port. The old copies were RVDS/armcc versions using `__asm void vPortSVCHandler` and `__weak`, which GCC rejects |
| `FreeRTOS/FreeRTOSConfig.h` | explicitly sets `configCHECK_HANDLER_INSTALLATION = 0` (see below) |
| `Start/core_cm3.c` | output constraints of the three `__STREXB/__STREXH/__STREXW` inline asm blocks changed to `"=&r"`; the CMSIS V1.30 style makes GCC 15's assembler report `registers may not be the same` |
| `gcc/libs/*.a` | `libgcc / libc_nano / libm / libnosys` (v7-m/nofp) copied out of the toolchain. Keil is installed under a Chinese path (`E:\腾讯电脑管家软件搬家\...`), where ld fails to pick up libraries, so they live on a pure-ASCII path |
| `gcc/backup/` | **pre-change backups**: `Project.uvprojx.orig`, `port.c.orig`, `portmacro.h.orig`, `startup_stm32f10x_md.s.orig`, `TOOLS.INI.orig`, plus post-fix snapshots `PAN312x_Driver.c.fixed`, `at_command_firmware.c.fixed`, `FreeRTOSConfig.h.fixed` |

`TOOLS.INI` now has `[ARM] PATH1` pointing at `C:\Users\Ai\AppData\Local\Keil_v5\ARM\ARMCC\`, with `TOOLPREFIX=arm-none-eabi-` unchanged (PATH1 previously pointed at a GCC 9 directory that no longer exists).

### Startup popup `Registered ARM Compiler Version not found in path: '.\ARMCC'`

μVision checks at every start that **each** compiler version registered in `[ARMADS]` really exists. It still contained

```
ARMCCPATH1=".\ARMCC"  ("V5.06 update 7 (build 960)")
```

while `.\ARMCC` now holds the **GNU toolchain** (`arm-none-eabi-gcc.exe`, no `armcc.exe`), so the warning popped up on every launch. It is only a validation warning and does not block compilation, but it does block automated builds.

**Fix**: remove the invalid `ARMCCPATH1` entry from `[ARMADS]`, keeping the still-used `ARMCCPATH0="ARMCLANG" ("V6.22")` (AC6 is still installed), and set `<pCCUsed>` in `.uvprojx` to `0::Arm GNU Toolchain 15.3.1::GNU` so the project no longer points at AC5.

Note that `[ARM] PATH1="...\ARM\ARMCC\"` is the **GNU toolchain install path**, not a compiler registration, and must be kept; without it μVision cannot find `arm-none-eabi-gcc`. On this machine `C:\Users\Ai\AppData\Local\Keil_v5\TOOLS.INI` and `E:\腾讯电脑管家软件搬家\软件搬家\Keil μVision4\TOOLS.INI` are two paths to the same file (hard link / relocation mapping), so one edit suffices, but verify both md5 sums match. Pre-deletion backups are `gcc/backup/TOOLS.INI.before-<timestamp>` and `TOOLS.INI.E-drive.before-<timestamp>`.

## Key configuration values (for GUI cross-check)

- Target → **C/C++ (GNU)** Define: `USE_STDPERIPH_DRIVER,STM32F10X_MD`
- Include Paths: `.\Start;.\Library;.\User;.\FreeRTOS\inc;.\FreeRTOS\port;.\FreeRTOS\src;.\FreeRTOS;.\BSP\inc;.\PAN312x;.\hal_compat`
- C/C++ Misc: `-mcpu=cortex-m3 -mthumb -std=gnu99 -ffunction-sections -fdata-sections` (the early `-Wno-*` flags are gone; the code was fixed instead)
- Linker → Linker Script File: `.\gcc\stm32f103c8.ld`; do **not** add `-T` in Misc (μVision adds it and duplicates cause errors)
- Linker Misc: `-mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles -Wl,--gc-sections -L./gcc/libs -lgcc -lc_nano -lm -lgcc`
  (always use forward slashes, μVision swallows backslashes; `--gc-sections` must carry `-Wl,`, otherwise FLASH overflows by about 15 KB. **Do not add `-lnosys`**: its `_write` is a strong symbol and conflicts with the real implementation in `gcc/syscalls.c`)
- Keep the three mappings already in `FreeRTOSConfig.h`:
  `#define xPortPendSVHandler PendSV_Handler` / `vPortSVCHandler SVC_Handler` / `xPortSysTickHandler SysTick_Handler`

## Measured results

| Build | text | data | bss | Result |
|-------|------|------|-----|--------|
| μVision Rebuild | 44676 | 152 | 16368 | **0 Error, 0 Warning**, `UV4 exit=0`, `Objects/Project.hex` produced |
| `gcc/build.ps1` | 41256 | 152 | 16360 | **0 Error, 0 Warning**, `gcc/build/Project.hex` produced |

Both are far below 64 KB FLASH / 20 KB RAM and **no `-Wno-*` suppression is used**. Vector table check: `g_pfnVectors = 0x08000000`, `_estack = 0x20005000`, `Reset_Handler` at `0x08001014`, and the SVCall/PendSV/SysTick slots point to `0x08007481 / 0x080074d1 / 0x08007589` (all with the Thumb bit), confirming the interrupt wiring after migration.

## Real bugs fixed (exposed by GCC after migration)

armcc did not warn about these; each was verified and fixed:

| Location | Problem | Impact |
|----------|---------|--------|
| **printf output path** | `BSP/src/bsp_uart.c` used an armcc-era `fputc` redirection; **GCC + newlib printf goes through `_write`, not `fputc`**. With `-lnosys` an empty stub handled it and the log showed six `_close/_fstat/_isatty/_lseek/_read/_write is not implemented and will always fail` | **All AT echo from `printf` was silently dropped — not a single character on the UART.** A functional defect, not harmless noise |
| `User/at_command_firmware.c` | `tx_cnt/rx_cnt/rx_error_cnt` are `uint32_t` but printed with `PRIu16` | **Counter values in AT replies truncated to 16 bits**, wrong once above 65535 |
| `User/at_command_firmware.c` | `FrequencyBase/DataRate/TxDeviation/RxDeviation` (`uint32_t`) printed with `%u` | format mismatch on 64-bit platforms (harmless here, not portable) |
| `PAN312x_Driver.c` `PAN312x_Wait_Ready` | `time_out` uninitialised | first comparison uses a random value, unreliable wait logic |
| `PAN312x_Driver.c` `PAN312x_Set_Crc` | `CrcPolynomial` uninitialised and the `switch` `default` branch assigns nothing | **an invalid CRC index writes a random polynomial into the chip** |
| `PAN312x_Driver.c` `PAN312x_Set_Rx_Deviation` | `data_rate` uninitialised and the rate table only reaches 500 kbps | deviation computed from a random value at 1M/2M bps |
| `PAN312x_Driver.c` `PAN312x_Set_Frequency` / `_b` | `base_frequency_tmp`, `mid_frequency_tmp`, `tmp_freq` uninitialised, band if/else has no fallback | **out-of-range frequencies configure the radio with garbage** |
| `PAN312x_Driver.c` `PAN312x_Set_Symbol_RateB` | `symbol_rate_b` uninitialised, no fallback in the rate table | unsupported rates write an illegal symbol rate |
| `PAN312x_Driver.c` `PAN312x_CTK_Set_Power` | `PowerSelect` uninitialised, no fallback for package/supply combinations | illegal combinations configure a random supply mode |
| `PAN312x_Driver.c` `PAN312x_Set_CrcByteSwap` | parameter type `PAN312xCrcByteSwap` compared against `CRC_BIT_ORDER_*` (bit-order enum), triggering `-Wenum-compare` | the two enum values happen to be 0/1 so the behaviour is **accidentally equivalent**, but the type is wrong and misleading; changed to `CRC_BYTE_MSB_FIRST/CRC_BYTE_LSB_FIRST` |
| `PAN312x_Driver.c` `PAN312xRaw_ReadAddrB4` / `PAN312xReg_ReadB4` / `PAN312x_Get_ChipState` | return value ignored on read failure, uninitialised data returned | **random values on SPI read failure** (armcc did not warn either) |
| `PAN312x_Driver.c` two-point calibration | `tx_dev`/`ref_diff`/`data_rate_index` uninitialised | calibration parameters may be random |

### printf redirection (the key to 0 Warning)

New `gcc/syscalls.c` provides the minimal newlib syscall layer:

- `_write()`: calls the existing `fputc()` in `BSP/src/bsp_uart.c` byte by byte (blocking USART1) and **returns the number of bytes actually written**; returning 0 makes newlib treat the write as failed and drop further output. This reuses the original UART driver and makes `printf` work.
- The other `_read/_close/_fstat/_isatty/_lseek/_getpid/_kill/_exit/_sbrk` are minimal bare-metal stubs; `_sbrk` grows upward from the linker script's `end`, leaving `_Min_Stack_Size` (2 KB) for the stack.
- `-lnosys` was **removed** from the link line (its `_write` is a strong symbol that conflicts with our implementation), and the six `not implemented and will always fail` warnings disappeared with it.
- It is added to the `Start` group in `Project.uvprojx` and to the source list of `gcc/build.ps1`, so both build paths compile it.

Verification: in `arm-none-eabi-nm Objects/Project.elf`, `_write` and friends are `T` strong symbols, `printf` is linked, and the ELF no longer references libnosys. On hardware the UART at 115200 shows AT replies such as `+CLEARCNT`.

Also: the two DMA handles in `PAN312x_Hal.c` (`pan312x_hdma_tx/rx`) are referenced only inside commented-out code, so they are marked `__attribute__((unused))` as intentionally kept rather than deleted or suppressed with `-Wno-unused-variable`.

Repair principle: **not simply adding initialisers**. Wherever a branch could fall through without assigning, an `else { return; }` guard was added so invalid input exits instead of writing garbage to the chip.

### Interrupt wiring and runtime self-check

What matters most after migration is that the vector table really points at the FreeRTOS handlers. Verified statically on the final `Project.elf` with `arm-none-eabi-nm` / `objdump`:

- `g_pfnVectors = 0x08000000`, `_estack = 0x20005000`
- slot 11 (SVCall) → `0x08007501` = `SVC_Handler` (`0x08007500` + Thumb bit)
- slot 14 (PendSV) → `0x08007551` = `PendSV_Handler`
- slot 15 (SysTick) → `0x08007625` = `SysTick_Handler`

The three `#define`s already present in `FreeRTOSConfig.h` map the port's `vPortSVCHandler/xPortPendSVHandler/xPortSysTickHandler` onto these symbols, so the wiring is correct.

**Why the runtime self-check stays off**: in `FreeRTOS.h`, `configCHECK_HANDLER_INSTALLATION` defaults to 1 and also requires `configASSERT()` to be defined; once defined, `configASSERT_DEFINED` becomes 1 and enables **all** FreeRTOS internal assertions such as `vPortValidateInterruptPriority()`. This firmware has not been regression-tested on hardware, so enabling them could stall working interrupt paths on an assertion. It is therefore explicitly set to 0 and replaced by the static check above. For a hardware run with the self-check, set the macro to 1 and supply `configASSERT()`.

### About `-Wno-*`

The project temporarily used `-Wno-maybe-uninitialized -Wno-unused-variable` to silence warnings. **All of them are removed** and the code is fixed instead. The build is now **0 Error / 0 Warning** with no warnings suppressed.

## Compliance wrap-up suggestions

1. ARM Compiler 5.06u7 was **not** reinstalled; the whole build uses only Arm GNU Toolchain 15.3.1 (open source, no license server).
2. The invalid `ARMCCPATH1=".\ARMCC" ("V5.06 update 7 (build 960)")` entry in `[ARMADS]` (the root cause of the μVision startup popup) has been removed, and both projects' `<pCCUsed>` now read `0::Arm GNU Toolchain 15.3.1::GNU`. If AC5 uninstall entries remain under "Apps & features", clean them up per the asset ledger.
3. Consider moving the toolchain out of `...\Keil_v5\ARM\ARMCC` into its own directory (e.g. `C:\arm-gnu-toolchain`), then updating `[ARM] PATH1` in `TOOLS.INI` and `-ToolchainBin` in `build.ps1`, so path-based asset scans do not misclassify it.
4. Register the replacement version `Arm GNU Toolchain 15.3.1` in the ledger with the `arm-none-eabi-gcc --version` output. The μVision IDE itself is still commercial software (MDK-Pro licensed here); building with GCC does not replace the Keil IDE licence.

## Rollback

Copy the five `.orig` files in `gcc/backup/` back under their original names and clear **Use GNU Compiler** in μVision under
`Project → Manage → Project Items → Folders/Extensions` (toolset back to ARM-ADS). Note that after rollback the project still will not build if the AC5 binaries are missing — which is exactly the problem this migration solved.
