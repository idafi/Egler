@ECHO off

clang++ ^
    -shared ^
    -target x86_64-windows-msvc ^
    -g -gcodeview ^
    -O0 ^
    -std=c++17 ^
    -Wall -Wno-pragma-pack -Wno-null-dereference ^
    -I%SDL2_INC% -I%GLEW_INC% -I%FBX_INC% ^
    -o%OUT%\Egler.FBX.dll ^
    "%SRC%\Egler.FBX\*.cpp" ^
    -llib\Egler.Core ^
    -L%FBX_LIB% ^
    -llibfbxsdk-mt.lib ^
    -Xclang -flto-visibility-public-std ^
    -Xlinker /IMPLIB:"lib\Egler.FBX.lib"