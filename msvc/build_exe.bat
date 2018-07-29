@ECHO off

clang++ ^
    -target x86_64-windows-msvc ^
    -g -gcodeview ^
    -O0 ^
    -std=c++17 ^
    -Wall -Wno-pragma-pack ^
    -I%SDL2_INC% -I%GLEW_INC% -I%FBX_INC% ^
    -o%OUT%\Egler.exe ^
    "%SRC%\Egler\Egler.cpp" ^
    -llib\Egler.Core -llib\Egler.FBX ^
    -L%SDL2_LIB% -lSDL2main.lib -lSDL2.lib ^
    -L%FBX_LIB% -llibfbxsdk-mt.lib ^
    -Xclang -flto-visibility-public-std ^
    -Xlinker /SUBSYSTEM:windows