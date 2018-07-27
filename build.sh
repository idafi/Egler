shopt -s globstar

clang++ \
    -shared \
    -target x86_64-pc-windows-gnu \
    -g \
    -O0 \
    -std=c++17 \
    -Wall \
    -I"/mingw64/include/SDL2/" \
    -o"bin/Egler.dll" \
    `ls src/Egler/**/*.cpp` \
    -lOpenGL32 -lglew32 -lmingw32 -lSDL2main -lSDL2