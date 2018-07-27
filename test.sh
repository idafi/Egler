shopt -s globstar

echo "Building..."

clang++ \
    -target x86_64-pc-windows-gnu \
    -g \
    -O0 \
    -std=c++17 \
    -Wall \
    -I"/mingw64/include/SDL2/" \
    -o"bin/Egler.Test.exe" \
    `ls src/Egler/**/*.cpp` \
    `ls src/Egler.Test/**/*.cpp` \
    -lOpenGL32 -lglew32 -lmingw32 -lSDL2main -lSDL2 \
    -lgtest_main -lgmock_main -lgtest -lgmock

if [ $? -eq 0 ]; then
    echo "Done."
    ./bin/Egler.Test.exe
fi