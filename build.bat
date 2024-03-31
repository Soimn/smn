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

set "ignored_warnings=-Wno-unused-parameter -Wno-gnu-statement-expression-from-macro-expansion"
set "ignored_warnings=%ignored_warnings% -Wno-strict-prototypes -Wno-gnu-zero-variadic-macro-arguments"
set "ignored_warnings=%ignored_warnings% -Wno-missing-prototypes -Wno-declaration-after-statement"
set "ignored_warnings=%ignored_warnings% -Wno-language-extension-token -Wno-cast-qual -Wno-gnu-pointer-arith"

set "opt_options= /Zo /Z7 /Od /Oi"

set "link_options= /subsystem:console /opt:icf /opt:ref /incremental:no /pdb:test.pdb /out:test.exe"
set "link_options=%link_options% clang_rt.builtins-x86_64.lib /out:test.exe /pdb:test.pdb /debug:full"

set "sanitizers= -fsanitize=address,undefined"

clang-cl %opt_options% %warnings% %ignored_warnings% %sanitizers% ..\test.c /link %link_options%

:end
endlocal
