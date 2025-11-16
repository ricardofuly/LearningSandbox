@echo off
setlocal enabledelayedexpansion

FOR %%F IN (*.uproject) DO (
 set UPROJECT=%%F
 goto compile
)

:compile
echo Project: %UPROJECT%
for /f "delims=" %%A in (' powershell -Command "(Get-Content %UPROJECT% | ConvertFrom-Json).EngineAssociation" ') do set ENGINE_ASSOCIATION=%%A
echo Associated Engine: %ENGINE_ASSOCIATION%

set "ENGINE_ASSOCIATION_AUX=%ENGINE_ASSOCIATION%"
set "ENGINE_STR_LENGTH=0"

:loopStrLen
if not "!ENGINE_ASSOCIATION_AUX!"=="" (
    set "ENGINE_ASSOCIATION_AUX=!ENGINE_ASSOCIATION_AUX:~1!"
    set /a ENGINE_STR_LENGTH+=1
    goto loopStrLen
)

if %ENGINE_STR_LENGTH% gtr 8 (
goto FindSourceEngine
) else (
goto FindLauncherEngine
)

:FindSourceEngine
setlocal ENABLEEXTENSIONS
set KEY_NAME="HKEY_CURRENT_USER\SOFTWARE\Epic Games\Unreal Engine\Builds"
FOR /F "usebackq skip=2 tokens=1-2*" %%A IN (`REG QUERY %KEY_NAME% /v %ENGINE_ASSOCIATION% 2^>nul`) DO (
    set ENGINE_DIRECTORY=%%C
)
goto build
@REM end of FindSourceEngine

:FindLauncherEngine
setlocal ENABLEEXTENSIONS
set KEY_NAME="HKLM\SOFTWARE\EpicGames\Unreal Engine\%ENGINE_ASSOCIATION%"
FOR /F "usebackq skip=2 tokens=1-2*" %%A IN (`REG QUERY %KEY_NAME% /v "InstalledDirectory" 2^>nul`) DO (
    set ENGINE_DIRECTORY=%%C
)
goto build
@REM end of FindSourceEngine

:build
if NOT defined ENGINE_DIRECTORY (
    echo.
    echo.
	echo Unable to find Unreal Engine directory.
	goto end
)
echo Associated Engine Directory: %ENGINE_DIRECTORY%
set "TARGET_NAME=%UPROJECT:.uproject=%Editor"
echo Target Name: %TARGET_NAME%
echo.
echo.
echo ====== BUILDING PROJECT ======
echo.
echo.
call "%ENGINE_DIRECTORY%\Engine\Build\BatchFiles\Build.bat" %TARGET_NAME% Win64 Development "%cd%/%UPROJECT%" -Quiet -WaitMutex -FromMsBuild
echo.
echo.

:end
pause
