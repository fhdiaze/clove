@echo off

setlocal enabledelayedexpansion

REM Captured now because "shift" (used below during argument parsing) can end up
REM shifting %0 too once all positional args are consumed, which would corrupt %~dp0.
set "ScriptDir=%~dp0"

set "BuildMode=debug"
set "Architecture=x64"
set "ModuleName=http"
set "MainFileName=http"
set "MainFilePath=./%MainFileName%.c"
set "Outdir=./bin/%ModuleName%"
set "Datadir=./data/%ModuleName%"
set "OutMainFilePath=%Outdir%/%MainFileName%.exe"
set "FlagsFile=%ScriptDir%..\..\compile_flags.txt"
set "DebugFlags=-g -gcodeview -O0 -DDEBUG -Wl,/DEBUG:FULL -fms-runtime-lib=static_dbg"
set "ReleaseFlags=-O3 -DNDEBUG -flto -fms-runtime-lib=static"
set "Flags=-Wl,/MAP:%Outdir%/%MainFileName%.map,/MAPINFO:EXPORTS -Wl,/PDB:%Outdir%/%MainFileName%.pdb"

:parse_args

if "%~1"=="" goto :done_args
if /i "%~1"=="/m" (
    if "%~2"=="" (
        echo Error: /m requires a value. & exit /b 1
    )
    set "BuildMode=%~2" & shift & shift & goto :parse_args
)
if /i "%~1"=="/a" (
    if "%~2"=="" (
        echo Error: /a requires a value. & exit /b 1
    )
    set "Architecture=%~2" & shift & shift & goto :parse_args
)
echo Error: Unknown argument "%~1".
exit /b 1

:done_args

if /i not "%BuildMode%"=="debug" if /i not "%BuildMode%"=="release" (
    echo Error: Invalid build mode "%BuildMode%". Must be "debug" or "release".
    exit /b 1
)

if /i not "%Architecture%"=="x86" if /i not "%Architecture%"=="x64" (
    echo Error: Invalid architecture "%Architecture%". Must be "x86" or "x64".
    exit /b 1
)


if not exist "%Outdir%" (
    echo Creating %Outdir%...
    mkdir "%Outdir%"
) else (
    echo Cleaning %Outdir%...
    del /s /q "%Outdir%\*" 2>nul
)

if not exist "%Datadir%" (
    echo Creating %Datadir%...
    mkdir "%Datadir%"
) else (
    echo Cleaning %Datadir%...
    del /q "%Datadir%\log.txt" 2>nul
)

REM Read flags from file (path is relative to this script's location, not the caller's cwd)
for /f "usebackq tokens=*" %%A in ("%FlagsFile%") do (
    set "line=%%A"
    set "line=!line: =!"
    if not "!line!"=="" if not "!line:~0,2!"=="//" (
        set "Flags=!Flags! %%A"
    )
)

if "%Architecture%"=="x86" (
    set "Flags=!Flags! -m32"
    echo Building for 32-bit ^(x86^)...
) else (
    set "Flags=!Flags! -m64"
    echo Building for 64-bit ^(x64^)...
)

if "%BuildMode%"=="debug" (
    set "Flags=!Flags! %DebugFlags%"
    echo Building in DEBUG mode...
) else (
    set "Flags=!Flags! %ReleaseFlags%"
    echo Building in RELEASE mode...
)

echo Building %OutMainFilePath% ...
echo.
echo clang !Flags! %MainFilePath% -o %OutMainFilePath%
echo.

clang !Flags! %MainFilePath% -o %OutMainFilePath%

if errorlevel 1 (
    echo Building %MainFileName% failed!
    exit /b %errorlevel%
)

echo.
echo Building %MainFileName% succeeded!
echo.
