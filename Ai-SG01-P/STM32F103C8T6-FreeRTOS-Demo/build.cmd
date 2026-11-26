@echo off
REM ===== 一键编译 STM32F103C8T6-FREERTOS-AISG01 =====
REM 用法:  build.cmd        编 PING 板 (Role 0, 默认)
REM        build.cmd 1      编 PONG 板 (Role 1)
REM        build.cmd 0 clean  全量重编
REM 产物:  gcc\build\Project_r0.hex / Project_r1.hex
setlocal
cd /d "%~dp0"

set ROLE=%1
if "%ROLE%"=="" set ROLE=0

set CLEANARG=
if /i "%2"=="clean" set CLEANARG=-Clean

echo.
echo == Building Role %ROLE% %CLEANARG% ==
powershell -NoProfile -ExecutionPolicy Bypass -File ".\gcc\build.ps1" -Role %ROLE% %CLEANARG%
if errorlevel 1 (
  echo.
  echo ** BUILD FAILED **
  exit /b 1
)

echo.
echo ** BUILD OK -> gcc\build\Project_r%ROLE%.hex **
endlocal
