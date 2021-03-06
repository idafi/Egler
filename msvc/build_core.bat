@ECHO off

clang++ ^
    -shared ^
    -target x86_64-windows-msvc ^
    -g -gcodeview ^
    -O0 ^
    -std=c++17 ^
    -Wall -Wno-pragma-pack ^
    -I%SDL2_INC% -I%GLEW_INC% ^
    -o%OUT%\Egler.Core.dll ^
    "%SRC%\Egler.Core\Core\*.cpp" "%SRC%\Egler.Core\IO\*.cpp" "%SRC%\Egler.Core\Logging\*.cpp" "%SRC%\Egler.Core\Video\*.cpp" ^
    -L%SDL2_LIB% -L%GLEW_LIB% ^
    -lSDL2.lib -lOpenGL32.lib -lglew32s.lib -lglew32.lib ^
    -Xclang -flto-visibility-public-std ^
    -Xlinker /IMPLIB:"lib\Egler.Core.lib"