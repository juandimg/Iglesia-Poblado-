@echo off
echo ================================================
echo Compilando y Ejecutando Iglesia Poblado
echo ================================================
echo.

REM Buscar el compilador de C# que viene con Windows
set "CSC="
for /f "delims=" %%i in ('dir /b /s "%SystemRoot%\Microsoft.NET\Framework64\v4*\csc.exe" 2^>nul') do set "CSC=%%i"

if not defined CSC (
    for /f "delims=" %%i in ('dir /b /s "%SystemRoot%\Microsoft.NET\Framework\v4*\csc.exe" 2^>nul') do set "CSC=%%i"
)

if not defined CSC (
    echo [ERROR] No se encontro el compilador de C#
    echo Instalando .NET Framework...
    winget install Microsoft.DotNet.Framework.DeveloperPack_4
    pause
    exit /b 1
)

echo Compilador encontrado: %CSC%
echo Compilando aplicacion C#...
echo.

"%CSC%" /target:winexe /out:IglesiaPoblado.exe /r:System.Windows.Forms.dll /r:System.Drawing.dll src\IglesiaPoblado.cs /nologo /optimize+

if exist "IglesiaPoblado.exe" (
    echo.
    echo [OK] Compilacion exitosa!
    echo.
    echo Iniciando aplicacion...
    echo.
    start "" "IglesiaPoblado.exe"
    exit /b 0
) else (
    echo.
    echo [ERROR] No se pudo compilar la aplicacion
    pause
    exit /b 1
)
