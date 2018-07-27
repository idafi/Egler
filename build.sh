shopt -s globstar

clang++ \
    -mwindows \
    -target x86_64-pc-windows-gnu \
    -g \
    -O0 \
    -std=c++17 \
    -Wall \
    -I"/mingw64/include/SDL2/" \
    -o"bin/Egler.exe" \
    `ls src/Egler/**/*.cpp` \
    -lOpenGL32 -lglew32 -lmingw32 -lSDL2main -lSDL2