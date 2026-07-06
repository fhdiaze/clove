@echo off

cd /d "%~dp0"

clang -g main.c -nostdlib -Wl,/subsystem:windows -o main.exe
