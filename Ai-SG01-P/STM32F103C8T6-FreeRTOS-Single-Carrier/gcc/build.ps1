# GCC (arm-none-eabi) build for STM32F103C8T6-FREERTOS-AISG01
# Run from anywhere:  powershell -ExecutionPolicy Bypass -File .\gcc\build.ps1
#
# The toolchain lives in the Keil installation's ARMCC folder on this machine;
# override it with -ToolchainBin if you move it elsewhere.

param(
    [string]$ToolchainBin = 'C:\Users\Ai\AppData\Local\Keil_v5\ARM\ARMCC\bin',
    [switch]$Clean
)

$ErrorActionPreference = 'Stop'
$Root = Split-Path -Parent $PSScriptRoot
$Out  = Join-Path $Root 'gcc\build'
$Elf  = Join-Path $Out 'Project.elf'
$Hex  = Join-Path $Out 'Project.hex'
$Map  = Join-Path $Out 'Project.map'

$cc = Join-Path $ToolchainBin 'arm-none-eabi-gcc.exe'
if (-not (Test-Path $cc)) { throw "Compiler not found: $cc  (use -ToolchainBin <dir>)" }

if ($Clean -and (Test-Path $Out)) { Remove-Item -Recurse -Force $Out }
New-Item -ItemType Directory -Force -Path $Out | Out-Null

# Copy the toolchain's v7-m libraries to an ASCII-safe path (the Keil install
# lives under a path containing Chinese characters that some tool steps fail on).
$ToolchainRoot = Split-Path -Parent $ToolchainBin
$LibDir = Join-Path $Root 'gcc\libs'
New-Item -ItemType Directory -Force -Path $LibDir | Out-Null
$libSources = @(
    (Join-Path $ToolchainRoot 'lib\gcc\arm-none-eabi\15.3.1\thumb\v7-m\nofp\libgcc.a'),
    (Join-Path $ToolchainRoot 'arm-none-eabi\lib\thumb\v7-m\nofp\libc_nano.a'),
    (Join-Path $ToolchainRoot 'arm-none-eabi\lib\thumb\v7-m\nofp\libm.a'),
    (Join-Path $ToolchainRoot 'arm-none-eabi\lib\thumb\v7-m\nofp\libnosys.a')
)
foreach ($lib in $libSources) {
    if (-not (Test-Path $lib)) { throw "Toolchain library missing: $lib" }
    Copy-Item $lib $LibDir -Force
}

$C = @(
    'Start\core_cm3.c', 'Start\system_stm32f10x.c',
    'Library\misc.c', 'Library\stm32f10x_adc.c', 'Library\stm32f10x_bkp.c',
    'Library\stm32f10x_can.c', 'Library\stm32f10x_cec.c', 'Library\stm32f10x_crc.c',
    'Library\stm32f10x_dac.c', 'Library\stm32f10x_dbgmcu.c', 'Library\stm32f10x_dma.c',
    'Library\stm32f10x_exti.c', 'Library\stm32f10x_flash.c', 'Library\stm32f10x_fsmc.c',
    'Library\stm32f10x_gpio.c', 'Library\stm32f10x_i2c.c', 'Library\stm32f10x_iwdg.c',
    'Library\stm32f10x_pwr.c', 'Library\stm32f10x_rcc.c', 'Library\stm32f10x_rtc.c',
    'Library\stm32f10x_sdio.c', 'Library\stm32f10x_spi.c', 'Library\stm32f10x_tim.c',
    'Library\stm32f10x_usart.c', 'Library\stm32f10x_wwdg.c',
    'BSP\src\bsp.c', 'BSP\src\bsp_uart.c', 'BSP\src\bsp_timer.c',
    'BSP\src\bsp_led.c', 'BSP\src\bsp_flash.c',
    'PAN312x\PAN312x_Driver.c', 'PAN312x\PAN312x_Hal.c', 'PAN312x\PAN312x_Rf_CTK_Setting.c',
    'hal_compat\hal_compat.c',
    'User\main.c', 'User\at_command_firmware.c', 'User\stm32f10x_it.c',
    'FreeRTOS\src\croutine.c', 'FreeRTOS\src\event_groups.c', 'FreeRTOS\src\list.c',
    'FreeRTOS\src\queue.c', 'FreeRTOS\src\stream_buffer.c', 'FreeRTOS\src\tasks.c',
    'FreeRTOS\src\timers.c',
    'FreeRTOS\port\heap_4.c', 'FreeRTOS\port\port.c'
)
$Startup = 'gcc\startup_stm32f10x_md.s'
$Syscalls = 'gcc\syscalls.c'   # newlib _write() -> USART1 (printf retarget)
$Ld      = 'gcc\stm32f103c8.ld'

$Inc = @('gcc','Start','Library','User','FreeRTOS\inc','FreeRTOS\port',
         'FreeRTOS\src','FreeRTOS','BSP\inc','PAN312x','hal_compat')

$Common = @(
    '-mcpu=cortex-m3', '-mthumb', '-Os', '-g', '-std=gnu99',
    '-ffunction-sections', '-fdata-sections', '-Wall',
    '-Wno-unused-parameter', '-Wno-sign-compare',
    '-DUSE_STDPERIPH_DRIVER', '-DSTM32F10X_MD'
)
foreach ($i in $Inc) { $Common += ('-I' + (Join-Path $Root $i)) }

$Objs = @()
foreach ($rel in ($C + @($Startup, $Syscalls))) {
    $src = Join-Path $Root $rel
    if (-not (Test-Path $src)) { throw "Missing source: $src" }
    $obj = Join-Path $Out (($rel -replace '[\\/]', '_') + '.o')
    $Objs += $obj
    $args = $Common + @('-c', $src, '-o', $obj)
    Write-Host "CC  $rel"
    $prevEAP = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'
    $compileOut = & $cc @args 2>&1
    $ErrorActionPreference = $prevEAP
    foreach ($line in ($compileOut | Out-String -Stream)) { Write-Host $line }
    if ($LASTEXITCODE -ne 0) { throw "Compile failed: $rel" }
}

$link = @(
    '-mcpu=cortex-m3', '-mthumb', '-Os',
    '-nostdlib', '-nostartfiles',
    '-T', (Join-Path $Root $Ld),
    '-Wl,--gc-sections',
    '-L', (Join-Path $Root 'gcc\libs'),
    '-o', $Elf
) + $Objs + @('-lgcc', '-lc_nano', '-lm', '-lgcc')
Write-Host 'LD  -> Project.elf'
$prevEAP = $ErrorActionPreference
$ErrorActionPreference = 'Continue'
$linkOut = & $cc @link 2>&1
$ErrorActionPreference = $prevEAP
foreach ($line in ($linkOut | Out-String -Stream)) { Write-Host $line }
if ($LASTEXITCODE -ne 0) { throw 'Link failed' }

$objcopy = Join-Path $ToolchainBin 'arm-none-eabi-objcopy.exe'
& $objcopy '-O' 'ihex' $Elf $Hex
if ($LASTEXITCODE -ne 0) { throw 'objcopy failed' }

$size = Join-Path $ToolchainBin 'arm-none-eabi-size.exe'
& $size $Elf

Write-Host ""
Write-Host "OK -> $Elf"
Write-Host "OK -> $Hex"
