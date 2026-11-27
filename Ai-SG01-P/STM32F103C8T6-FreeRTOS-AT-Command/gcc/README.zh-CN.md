# 方案 B：不装回 AC5，用 Arm GNU Toolchain 让 Keil 继续编译

[![English](https://img.shields.io/badge/English-README-green)](README.md)

本目录是 `Ai-SG01-P/STM32F103C8T6-FreeRTOS-AT` 工程从 **ARM Compiler 5.06u7 (armcc)**
迁移到 **Arm GNU Toolchain 15.3.1 (arm-none-eabi-gcc)** 的全部新增文件。
**已在本机实测通过**：μVision 5.40 批处理构建 `0 Error(s)`，生成 `Objects/Project.hex`。

## 现在怎么编译

- **Keil 里**：直接打开 `Project.uvprojx`，点 `Project → Rebuild`（F7 或魔法棒旁边的 Build）。
  输出仍是 `.\Objects\Project.elf` / `Project.hex`，调试、下载、Flash 算法配置都不变。
- **命令行（可复现/做合规留痕）**：在工程根目录执行
  ```powershell
  powershell -ExecutionPolicy Bypass -File .\gcc\build.ps1
  ```
  产物在 `gcc\build\Project.elf`、`Project.hex`。加 `-Clean` 可全量重编。

两条路用的是同一套源码和同一个编译器，只是入口不同。

## 改了哪些文件

| 文件 | 说明 |
|---|---|
| `Project.uvprojx` | 工具集 `ARM-ADS → ARM-GNU`；填入 GNU 模式的宏/头文件路径/编译链接选项；启动文件指向 `gcc/startup_stm32f10x_md.s`；输出目录与 Create HEX 恢复；`pCCUsed` 中残留的 `V5.06 update 7` 字样清掉，避免资产扫描误判。所有 `-Wno-*` 屏蔽项最终都已移除，改为真正修好源码 |
| `gcc/startup_stm32f10x_md.s` | **新建**。把原 `Start/startup_stm32f10x_md.s`（armasm 语法）翻成 GNU as 语法，中断向量表顺序完全一致；`Reset_Handler` 设栈、复制 `.data`、清 `.bss`、调 `SystemInit` 与 `main` |
| `gcc/stm32f103c8.ld` | **新建**。替代 armlink 分散加载文件：FLASH 0x08000000/64K，RAM 0x20000000/20K，`_estack = 0x20005000` |
| `gcc/syscalls.c` | **新建**。newlib 最小系统调用层，`_write()` 把 `printf` 接到 USART1（详见下方"printf 重定向"），并消除 6 条 libnosys 链接警告 |
| `FreeRTOS/port/port.c`、`portmacro.h` | **替换为 FreeRTOS-Kernel V11.1.0 官方 `portable/GCC/ARM_CM3`**。原来那份是 RVDS/armcc 版，用了 `__asm void vPortSVCHandler` 与 `__weak`，GCC 不认 |
| `FreeRTOS/FreeRTOSConfig.h` | 显式设 `configCHECK_HANDLER_INSTALLATION = 0`（详见下方说明） |
| `Start/core_cm3.c` | 3 处 `__STREXB/__STREXH/__STREXW` 内联汇编的输出约束改成 `"=&r"`。CMSIS V1.30 老写法会让 GCC 15 的汇编器报 `registers may not be the same` |
| `gcc/libs/*.a` | 从工具链拷出的 `libgcc / libc_nano / libm / libnosys`（v7-m/nofp）。因为 Keil 装在含中文的路径 `E:\腾讯电脑管家软件搬家\...`，直接让 ld 去那里取库会失败，统一放到纯 ASCII 路径 |
| `gcc/backup/` | **改动前的原始文件备份**：`Project.uvprojx.orig`、`port.c.orig`、`portmacro.h.orig`、`startup_stm32f10x_md.s.orig`、`TOOLS.INI.orig`；以及修复后的快照 `PAN312x_Driver.c.fixed`、`at_command_firmware.c.fixed`、`FreeRTOSConfig.h.fixed` |

`TOOLS.INI` 里 `[ARM] PATH1` 已指向 `C:\Users\Ai\AppData\Local\Keil_v5\ARM\ARMCC\`，
`TOOLPREFIX=arm-none-eabi-` 保持不变（原先 PATH1 指向一个已不存在的 GCC 9 目录）。

### 启动弹窗 `Registered ARM Compiler Version not found in path: '.\ARMCC'`

μVision 每次启动会校验 `[ARMADS]` 段登记的**每一个**编译器版本是否真实存在。
原先还留着一条

```
ARMCCPATH1=".\ARMCC"  ("V5.06 update 7 (build 960)")
```

而 `.\ARMCC` 目录现在装的是 **GNU 工具链**（里面是 `arm-none-eabi-gcc.exe`，没有 `armcc.exe`），
所以每次打开都弹这个警告。它只是校验告警，不影响编译，但会挡住自动化构建。

**处理方式**：删除 `[ARMADS]` 段里那条无效的 `ARMCCPATH1`，保留仍在使用的
`ARMCCPATH0="ARMCLANG" ("V6.22")`（AC6 还装着）。同时把工程 `.uvprojx` 里的
`<pCCUsed>` 改成 `0::Arm GNU Toolchain 15.3.1::GNU`，避免工程侧再指向 AC5。

注意 `[ARM] PATH1="...\ARM\ARMCC\"` 是 **GNU 工具链的安装路径**，不是编译器登记，
必须保留；删了它 μVision 就找不到 `arm-none-eabi-gcc` 了。
本机 `C:\Users\Ai\AppData\Local\Keil_v5\TOOLS.INI` 与
`E:\腾讯电脑管家软件搬家\软件搬家\Keil μVision4\TOOLS.INI` 是同一文件的两个路径
（硬链接/搬家映射），改一处即可，但建议核对两份 md5 一致。
删除前的备份在 `gcc/backup/TOOLS.INI.before-<时间戳>` 与 `TOOLS.INI.E-drive.before-<时间戳>`。

## 关键配置值（GUI 里对照用）

- Target → **C/C++ (GNU)** Define：`USE_STDPERIPH_DRIVER,STM32F10X_MD`
- Include Paths：`.\Start;.\Library;.\User;.\FreeRTOS\inc;.\FreeRTOS\port;.\FreeRTOS\src;.\FreeRTOS;.\BSP\inc;.\PAN312x;.\hal_compat`
- C/C++ Misc：`-mcpu=cortex-m3 -mthumb -std=gnu99 -ffunction-sections -fdata-sections`（已移除早期的 `-Wno-*`，改为真正修好代码）
- Linker → Linker Script File：`.\gcc\stm32f103c8.ld`，**不要**再在 Misc 里写 `-T`（μVision 会自己加，重复会报错）
- Linker Misc：`-mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles -Wl,--gc-sections -L./gcc/libs -lgcc -lc_nano -lm -lgcc`
  （路径一律用正斜杠，μVision 会吞掉反斜杠；`--gc-sections` 必须带 `-Wl,`，否则 FLASH 会溢出约 15 KB。
  **不要加 `-lnosys`**：它的 `_write` 是强符号，会和 `gcc/syscalls.c` 里的真实实现冲突）
- `FreeRTOSConfig.h` 里已有的三行映射保持不动：
  `#define xPortPendSVHandler PendSV_Handler` / `vPortSVCHandler SVC_Handler` / `xPortSysTickHandler SysTick_Handler`

## 实测结果

| 构建方式 | text | data | bss | 结果 |
|---|---|---|---|---|
| μVision Rebuild | 44676 | 152 | 16368 | **0 Error，0 Warning**，`UV4 exit=0`，生成 `Objects/Project.hex` |
| `gcc/build.ps1` | 41256 | 152 | 16360 | **0 Error，0 Warning**，生成 `gcc/build/Project.hex` |

两者都远小于 64 KB FLASH / 20 KB RAM，且**没有任何 `-Wno-*` 屏蔽项**。向量表校验：
`g_pfnVectors = 0x08000000`、`_estack = 0x20005000`、Reset_Handler `0x08001014`、
SVCall/PendSV/SysTick 槽位分别指向 `0x08007481 / 0x080074d1 / 0x08007589`（均带 Thumb 位），
说明迁移后的中断向量接线正确。

## 顺带修掉的真实 bug（迁移后 GCC 把它们暴露出来）

原来的 armcc 对这几处不报警，GCC 报出来后逐个核实并修正：

| 位置 | 问题 | 影响 |
|---|---|---|
| **printf 输出通道** | `BSP/src/bsp_uart.c` 的 `fputc` 是 armcc 时代的重定向方式；**GCC + newlib 的 printf 走 `_write`，不走 `fputc`**。链接 `-lnosys` 时由空桩接管，日志里报 6 条 `_close/_fstat/_isatty/_lseek/_read/_write is not implemented and will always fail` | **所有 `printf` 的 AT 回显被静默丢弃，串口一个字符都不输出**。这不是无害噪音，是功能性缺陷 |
| `User/at_command_firmware.c` | `tx_cnt/rx_cnt/rx_error_cnt` 是 `uint32_t`，却用 `PRIu16` 打印 | **AT 指令回显的计数值被截断成 16 位**，计数超过 65535 后回显错误 |
| `User/at_command_firmware.c` | `FrequencyBase/DataRate/TxDeviation/RxDeviation`（`uint32_t`）用 `%u` 打印 | 64 位平台下格式不匹配（本平台无害，但不可移植） |
| `PAN312x_Driver.c` `PAN312x_Wait_Ready` | `time_out` 未初始化 | 首次判断即为随机值，等待逻辑不可靠 |
| `PAN312x_Driver.c` `PAN312x_Set_Crc` | `CrcPolynomial` 未初始化，`switch` 的 `default` 分支不赋值 | **传入非法 CRC 索引时会把随机多项式写进芯片** |
| `PAN312x_Driver.c` `PAN312x_Set_Rx_Deviation` | `data_rate` 未初始化，且速率表只覆盖到 500kbps | 1M/2Mbps 下用随机值算频偏 |
| `PAN312x_Driver.c` `PAN312x_Set_Frequency` / `_b` | `base_frequency_tmp`、`mid_frequency_tmp`、`tmp_freq` 未初始化，频段 if/else 无兜底 | **频率超出支持范围时用垃圾值配置射频** |
| `PAN312x_Driver.c` `PAN312x_Set_Symbol_RateB` | `symbol_rate_b` 未初始化，速率表无兜底 | 不支持的速率会写入非法符号率 |
| `PAN312x_Driver.c` `PAN312x_CTK_Set_Power` | `PowerSelect` 未初始化，封装/供电组合无兜底 | 非法组合下按随机供电模式配置 |
| `PAN312x_Driver.c` `PAN312x_Set_CrcByteSwap` | 参数类型是 `PAN312xCrcByteSwap`，却和 `CRC_BIT_ORDER_*`（位序枚举）比较，触发 `-Wenum-compare` | 两个枚举数值恰好都是 0/1，**当前功能碰巧等价**，但类型用错且语义误导；已改为 `CRC_BYTE_MSB_FIRST/CRC_BYTE_LSB_FIRST` |
| `PAN312x_Driver.c` `PAN312xRaw_ReadAddrB4` / `PAN312xReg_ReadB4` / `PAN312x_Get_ChipState` | 读取失败时忽略返回值，返回未初始化的数据 | **SPI 读失败时返回随机值**（原 armcc 同样不报） |
| `PAN312x_Driver.c` 两点校准函数 | `tx_dev`/`ref_diff`/`data_rate_index` 未初始化 | 校准参数可能为随机值 |

### printf 重定向（0 Warning 的关键一步）

新增 `gcc/syscalls.c`，提供 newlib 需要的最小系统调用层：

- `_write()`：逐字节调用 `BSP/src/bsp_uart.c` 里已有的 `fputc()`（USART1 阻塞发送），
  **返回实际写入的字节数**；返回 0 会让 newlib 认为写出错并丢弃后续输出。
  这样既复用了原有串口驱动，又让 `printf` 真正走通。
- 其余 `_read/_close/_fstat/_isatty/_lseek/_getpid/_kill/_exit/_sbrk` 为裸机环境的最小桩；
  `_sbrk` 从链接脚本的 `end` 向上增长，留出 `_Min_Stack_Size`（2 KB）给栈。
- 同时从链接行**移除 `-lnosys`**（它的 `_write` 是强符号，会与我们的实现冲突），
  6 条 `not implemented and will always fail` 警告随之消失。
- 已挂到 `Project.uvprojx` 的 `Start` 组和 `gcc/build.ps1` 的源文件列表，两条构建路径都会编译它。

验证：`arm-none-eabi-nm Objects/Project.elf` 中 `_write` 等均为 `T` 强符号且 `printf` 已链接，
ELF 中不再引用 libnosys。上板后串口 115200 应能看到 `+CLEARCNT` 等 AT 回显。

另：`PAN312x_Hal.c` 两个 DMA 句柄（`pan312x_hdma_tx/rx`）只在注释掉的代码块里被引用，
加 `__attribute__((unused))` 明确标记"有意保留"，而不是删掉或靠 `-Wno-unused-variable` 压制。

修复原则：**不是简单加初始化了事**。凡是"某分支不赋值就往下走"的地方，都补了
`else { return; }` 兜底，让非法输入直接退出而不是带着垃圾值继续写芯片。

### 关于中断向量接线与运行期自检

迁移后最需要确认的是"向量表是否真的指向 FreeRTOS 的 handler"。已用
`arm-none-eabi-nm` / `objdump` 对最终 `Project.elf` 静态核对：

- `g_pfnVectors = 0x08000000`，`_estack = 0x20005000`
- 槽位 11 (SVCall) → `0x08007501` = `SVC_Handler` (`0x08007500` + Thumb 位)
- 槽位 14 (PendSV) → `0x08007551` = `PendSV_Handler`
- 槽位 15 (SysTick) → `0x08007625` = `SysTick_Handler`

`FreeRTOSConfig.h` 里保留了原有的三行 `#define`，把移植层的
`vPortSVCHandler/xPortPendSVHandler/xPortSysTickHandler` 映射到这些符号，接线正确。

**为什么不启用运行期自检**：`FreeRTOS.h` 里 `configCHECK_HANDLER_INSTALLATION` 默认是 1，
且会要求同时定义 `configASSERT()`；而一旦定义 `configASSERT()`，
`configASSERT_DEFINED` 就变成 1，会连带启用 `vPortValidateInterruptPriority()` 等
**全部** FreeRTOS 内部断言。这份固件尚未在硬件上回归，擅自启用可能让原本能跑的
中断路径直接卡在断言里。因此显式设为 0，用上面的静态核对替代。
若要在硬件上做一次带自检的验证，把该宏改成 1 并补上 `configASSERT()` 即可。

### 关于 `-Wno-*`

工程里曾临时加过 `-Wno-maybe-uninitialized -Wno-unused-variable` 来压掉告警，
**现已全部移除**，改为真正修好代码。当前是 **0 Error / 0 Warning**，且没有任何告警被屏蔽。


## 合规收尾建议

1. 本次**没有**装回 ARM Compiler 5.06u7；构建全程只用 Arm GNU Toolchain 15.3.1（开源、无需 license 服务器）。
2. `TOOLS.INI` 的 `[ARMADS]` 段里那条无效的 `ARMCCPATH1=".\ARMCC" ("V5.06 update 7 (build 960)")`
   已删除（μVision 每次启动弹 "Registered ARM Compiler Version not found in path: '.\ARMCC'" 的根因），
   两个工程的 `<pCCUsed>` 也已改成 `0::Arm GNU Toolchain 15.3.1::GNU`。
   若"应用和功能"里仍残留 AC5 的卸载项，按台账要求清理。
3. 建议后续把工具链从 `...\Keil_v5\ARM\ARMCC` 挪到独立目录（如 `C:\arm-gnu-toolchain`），
   然后同步改 `TOOLS.INI` 的 `[ARM] PATH1` 和 `build.ps1` 的 `-ToolchainBin`，避免被资产扫描按路径误判。
4. 台账登记替代版本 `Arm GNU Toolchain 15.3.1`，附 `arm-none-eabi-gcc --version` 输出；
   μVision IDE 本身仍是商业软件（本机为 MDK-Pro 授权），用 GCC 编译不替代 Keil 的 IDE 授权。

## 回退（若要恢复原状）

把 `gcc/backup/` 里 5 个 `.orig` 文件按原名拷回原位，并在 μVision 里
`Project → Manage → Project Items → Folders/Extensions` 取消 **Use GNU Compiler**
（工具集切回 ARM-ADS）。注意：回退后若 AC5 二进制仍缺失，工程依旧无法编译——
那正是本次迁移要解决的问题。
