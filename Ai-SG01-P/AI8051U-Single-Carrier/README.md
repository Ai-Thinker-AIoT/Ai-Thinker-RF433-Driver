# Ai-SG01-P(PAN3120 + GC1131) on AI8051U —— 单载波（CW）测试

同一套 AI8051U AT 固件，打开 `CARRIER_AUTO_ON_BOOT` 后**上电直接进入未调制单载波**，效果等同 `AT+ENTERCARRIER`，用于载波功率、频率容限、杂散测试。

- 模组：Ai-SG01-P（PAN3120 + GC1131）
- MCU：AI8051U-34K64，33.1776 MHz，Keil C51（C351，Device `STC8051U-8Bit Series`）
- 工程：`AI8051U-AISG01.uvproj`
- 调试串口：P3.7 / P3.6，115200-8-N-1

---

## 1. 目录结构

```
AI8051U-Single-Carrier/
├── AI8051U-AISG01.uvproj
├── Source/
│   ├── main.c
│   ├── firmware/
│   │   ├── at_command_firmware.c   # AT 固件 + 单载波入口
│   │   └── carrier_config.h        # CARRIER_AUTO_ON_BOOT（默认 1）
│   └── bsp/ pan312x/ hal_compat/   # 同 Demo 工程
├── Listings/
└── README.md
```

## 2. 引脚

与 [`../AI8051U-Demo/`](../AI8051U-Demo/) 完全相同：CSN P1.4、MOSI P1.5、MISO P1.6、SCLK P1.7、nRST P3.5、IRQ P3.2、GPIO P3.3、UART P3.7/P3.6、LED P2.0/P2.1。

## 3. 载波配置

[`Source/firmware/carrier_config.h`](Source/firmware/carrier_config.h)：

```c
#define CARRIER_AUTO_ON_BOOT   1   // 1 = 上电即进 CW；0 = 回到 Demo 自动对测
```

开启后启动流程会停掉两个定时器、关闭 Demo 状态机并锁住 RF 工作状态，避免运行中被改写。载波频率/功率取当前 `device_config` 默认值：

| 项目 | 值 |
|------|-----|
| 频率 | 490.3 MHz（`FrequencyBase = 490300000`） |
| 调制 | 2FSK（CW 时不加载调制数据） |
| 速率 / 频偏 | 50 kbps / 25 kHz（CW 下不体现） |
| 功率 | `POWER_LDO_0402` + `POWER_20dBm` |

要换频点或功率，先改 `DeviceConfig_Init()` 的默认值再编译；已存过 Flash 配置的板子会读回旧配置。

## 4. 运行行为

- 上电初始化板级外设 → 进入单载波 → 串口保持 AT 可用（但 RF 状态已冻结）。
- 载波是**未调制**的，频谱上只有一根谱线；测占用带宽（OBW）必须改用调制连续发射，本工程不提供。
- 测完直接断电。

## 5. 编译与烧录

1. Keil C51 打开 `AI8051U-AISG01.uvproj`，Rebuild。
2. STC-ISP 下载 hex，冷启动/重新上电。
3. 板子接频谱仪验证载波：先看频率是否落在设定值 ±晶振误差内，再看功率与杂散。

## 6. 频谱实测（窄带扫频）

Keysight 扫频式频谱仪，Ref 30 dBm / 10 dB/div / 衰减 40 dB，中心 490.30 MHz、Span 25 kHz、RBW = VBW 240 Hz；标记 `Mkr1 490.297585 MHz`，峰值 **23.52 dBm**。

![AI8051U 单载波，490.30 MHz / 23.52 dBm](../../Assets/3.jpg)

- 25 kHz 内只有一根谱线，符合未调制载波预期；占用带宽仅几十 kHz，**不能**用它论证 OBW。
- 实测频点比设定低约 2.4 kHz，属于晶振误差范围，认证报告按实测值记录。

## 7. 备注

- 需要正常收发或双板对测时，把 `CARRIER_AUTO_ON_BOOT` 改 0，或用 [`../AI8051U-Demo/`](../AI8051U-Demo/)。
- STM32 + FreeRTOS 的同类固件见 [`../STM32F103C8T6-FreeRTOS-Single-Carrier/`](../STM32F103C8T6-FreeRTOS-Single-Carrier/)。
