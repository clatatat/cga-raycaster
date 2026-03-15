@echo off
REM BUILD.BAT - Build CGA text-mode raycaster
REM Requires: Microsoft QuickC 2.5 (QCL) and MASM 5.1
REM Memory model: Small (/AS) - near code, near data
REM Language extensions: On (/Ze) - enables 'far', 'near', 'interrupt'
REM Optimization: Maximum (/Ox)
REM
REM Usage: BUILD           (build all)
REM        BUILD clean     (delete .OBJ and .EXE files)

if "%1"=="clean" goto clean

echo ---- Assembling RCFIXED.ASM ----
MASM /Mx RCFIXED.ASM;
if errorlevel 1 goto fail

echo ---- Compiling C sources ----
QCL /AS /Ze /Ox /c RAYCAST.C RCMATH.C RCCAST.C RCDRAW.C RCTEX.C
if errorlevel 1 goto fail
QCL /AS /Ze /Ox /c RCLCD.C RCINPUT.C RCMAP.C RCMENU.C RCENT.C
if errorlevel 1 goto fail

echo ---- Linking ----
echo RAYCAST.OBJ RCMATH.OBJ RCCAST.OBJ RCDRAW.OBJ+ > LINK.RSP
echo RCTEX.OBJ RCLCD.OBJ RCINPUT.OBJ RCMAP.OBJ+ >> LINK.RSP
echo RCMENU.OBJ RCENT.OBJ RCFIXED.OBJ >> LINK.RSP
echo RAYCAST.EXE; >> LINK.RSP
LINK @LINK.RSP
if errorlevel 1 goto fail

echo.
echo ==== Build successful: RAYCAST.EXE ====
goto end

:clean
echo Cleaning build artifacts...
if exist *.OBJ del *.OBJ
if exist RAYCAST.EXE del RAYCAST.EXE
if exist RAYCAST.MAP del RAYCAST.MAP
echo Done.
goto end

:fail
echo.
echo ==== BUILD FAILED ====

:end
