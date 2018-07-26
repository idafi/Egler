clang++ \
    -target x86_64-pc-windows-gnu \
    -g -gcodeview \
    -O0 \
    -std=c++17 \
    -Wall \
    -I"/mingw64/include/SDL2/" \
    -o"bin/Egler.exe" \
    "src/Egler/Egler.cpp" \
    -lOpenGL32 -lglew32 `sdl2-config --libs`