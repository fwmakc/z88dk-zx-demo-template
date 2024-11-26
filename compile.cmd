@echo off
setlocal

set PATH=%~dp0tools\z88dk\bin;%PATH%
set ZCCCFG=%~dp0tools\z88dk\lib\config

cd %~dp0
if errorlevel 1 exit /B 1

zcc +zx -vn -clib=sdcc_iy -startup=31 --list --opt-code-size -Cz"--sna" @game.lst -o bin\game -create-app
if errorlevel 1 exit /B 1
