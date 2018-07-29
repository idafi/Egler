@ECHO off

clang++ ^
    -target x86_64-windows-unknown ^
    -g -gcodeview ^
    -O0 ^
    -std=c++17 ^
    -Wall -Wno-pragma-pack ^
    -I%SDL2_INC% -I%GLEW_INC% -I%GLEW_LIB% -I %FBX_INC% ^
    -o%OUT%\Egler.exe ^
    "%SRC%\Egler\Egler.cpp" ^
    -L%OUT% -llib\Egler.Core ^
    -L%SDL2_LIB% -L%GLEW_LIB% -L%FBX_LIB% ^
    -lSDL2main.lib -lSDL2.lib -lOpenGL32.lib -lglew32s.lib -lglew32.lib -llibfbxsdk-mt.lib ^
    -Xclang -flto-visibility-public-std ^
    -Xlinker /SUBSYSTEM:windows