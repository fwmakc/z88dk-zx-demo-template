@echo off

cd %~dp0
if errorlevel 1 exit /B 1

call compile.cmd
if errorlevel 1 exit /B 1

tools\speccy\speccy bin\demo.sna
if errorlevel 1 exit /B 1
