@echo off
setlocal

if "%Platform%" neq "x64" (
    echo ERROR: Platform is not "x64" - please run this from the MSVC x64 native tools command prompt.
    exit /b 1
)

cd %~dp0
if not exist build mkdir build
cd build

if "%1" neq "" (
	echo Illegal number of arguments^, expected^: build
	goto end
)

set "warnings=-Wall -Wextra -Wshadow -Wconversion -Wnull-dereference -Wdouble-promotion -Wformat=2"

set "ignored_warnings=-Wno-unused-parameter"

clang %warnings% %ignored_warnings% -std=gnu11 -o test.exe ../test.c

:end
endlocal
