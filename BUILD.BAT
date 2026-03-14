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

echo ---- Compiling and linking ----
QCL /AS /Ze /Ox /FeRAYCAST.EXE RAYCAST.C RCMATH.C RCCAST.C RCDRAW.C RCTEX.C RCLCD.C RCINPUT.C RCMAP.C RCMENU.C RCFIXED.OBJ
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
