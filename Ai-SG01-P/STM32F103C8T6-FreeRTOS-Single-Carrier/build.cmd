@echo off
REM One-click GCC build for STM32F103C8T6-FREERTOS-AISG01-CARRIER
REM Usage:  build.cmd          build
REM         build.cmd clean    full rebuild
REM Output: gcc\build\Project.elf / Project.hex
setlocal
cd /d "%~dp0"

set CLEANARG=
if /i "%1"=="clean" set CLEANARG=-Clean

set TOOLCHAINBIN=
if exist "D:\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe" set "TOOLCHAINBIN=D:\arm-gnu-toolchain\bin"
if "%TOOLCHAINBIN%"=="" if exist "C:\Users\Ai\AppData\Local\Keil_v5\ARM\ARMCC\bin\arm-none-eabi-gcc.exe" set "TOOLCHAINBIN=C:\Users\Ai\AppData\Local\Keil_v5\ARM\ARMCC\bin"
if "%TOOLCHAINBIN%"=="" (
  echo ** Toolchain not found. Set TOOLCHAINBIN to the folder holding arm-none-eabi-gcc.exe **
  exit /b 1
)

echo == Building %CLEANARG% with %TOOLCHAINBIN% ==
powershell -NoProfile -ExecutionPolicy Bypass -File ".\gcc\build.ps1" -ToolchainBin "%TOOLCHAINBIN%" %CLEANARG%
if errorlevel 1 (
  echo ** BUILD FAILED **
  exit /b 1
)
echo ** BUILD OK - gcc\build\Project.hex **
endlocal
