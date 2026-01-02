@echo off
echo ================================================
echo Compilando Aplicacion Iglesia Poblado
echo ================================================
echo.

REM Intentar con Visual Studio Build Tools
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    echo Buscando Visual Studio...
    for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set VSPATH=%%i
    )
    if defined VSPATH (
        if exist "!VSPATH!\VC\Auxiliary\Build\vcvars64.bat" (
            echo Configurando Visual Studio...
            call "!VSPATH!\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
            echo Compilando con Visual Studio...
            cl /nologo /EHsc /Fe:IglesiaPoblado.exe src\main.cpp user32.lib gdi32.lib comctl32.lib /link /SUBSYSTEM:WINDOWS >nul 2>&1
            if exist "IglesiaPoblado.exe" (
                echo.
                echo [OK] Compilacion exitosa!
                echo Ejecuta: IglesiaPoblado.exe
                pause
                exit /b 0
            )
        )
    )
)

REM Buscar g++ (MinGW o MSYS2)
where g++ >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Compilando con MinGW...
    g++ -o IglesiaPoblado.exe src\main.cpp -mwindows -luser32 -lgdi32 -lcomctl32 2>nul
    if exist "IglesiaPoblado.exe" (
        echo.
        echo [OK] Compilacion exitosa!
        echo Ejecuta: IglesiaPoblado.exe
        pause
        exit /b 0
    )
)

REM Buscar cl.exe directamente
where cl >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Compilando con cl.exe...
    cl /nologo /EHsc /Fe:IglesiaPoblado.exe src\main.cpp user32.lib gdi32.lib comctl32.lib /link /SUBSYSTEM:WINDOWS >nul 2>&1
    if exist "IglesiaPoblado.exe" (
        echo.
        echo [OK] Compilacion exitosa!
        echo Ejecuta: IglesiaPoblado.exe
        pause
        exit /b 0
    )
)

echo.
echo [ERROR] No se encontro ningun compilador de C++
echo.
echo Opciones para instalar:
echo 1. Visual Studio Community: https://visualstudio.microsoft.com/es/downloads/
echo 2. MinGW: https://sourceforge.net/projects/mingw-w64/
echo 3. O ejecuta: winget install Microsoft.VisualStudio.2022.BuildTools
echo.
pause
exit /b 1
