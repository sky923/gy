@echo off
IF NOT EXIST "build" mkdir build
cd build
cmake ../
IF %ERRORLEVEL% EQU 9009 (ECHO error - cmake)
cd ..

