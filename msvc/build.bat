@ECHO off

ECHO setting up for build...

CD /D %~dp0

SET SRC=..\src
SET DATA=..\data
SET OUT=bin
IF NOT EXIST %OUT% (MKDIR %OUT%)

SET SDL2=lib\SDL2-2.0.8
SET GLEW=lib\glew-2.1.0
SET FBX=lib\FBX-SDK\2019.0

SET SDL2_INC=%SDL2%\include
SET SDL2_LIB=%SDL2%\lib\x64
SET SDL2_BIN=%SDL2_LIB%
SET GLEW_INC=%GLEW%\include
SET GLEW_LIB=%GLEW%\lib\Release\x64
SET GLEW_BIN=%GLEW%\bin\Release\x64
SET FBX_INC=%FBX%\include
SET FBX_LIB=%FBX%\lib\vs2015\x64\release

ECHO ...building Egler.Core...

CALL build_core.bat
IF ERRORLEVEL 1 GOTO :EOF

ECHO ...building Egler...

CALL build_exe.bat
IF ERRORLEVEL 1 GOTO :EOF

ECHO ...copying dependencies...

XCOPY /Q /Y %SDL2_BIN%\SDL2.dll %OUT%
XCOPY /Q /Y %GLEW_BIN%\glew32.dll %OUT%
XCOPY /Q /Y /E %DATA% %OUT%\data\

ECHO ...done.