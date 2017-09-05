@echo off
IF NOT EXIST "build" mkdir build
cd build
del CMakeCache.txt
cmake ../ -G "Visual Studio 15 Win64"
IF %ERRORLEVEL% EQU 9009 (ECHO error - cmake)
cd ..

