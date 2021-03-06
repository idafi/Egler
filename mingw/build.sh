shopt -s globstar
cd "$(dirname ${BASH_SOURCE[0]})"

if [ ! -d "bin" ]; then
	mkdir "bin"
fi

echo "building Egler.Core..."

clang++ \
    -shared \
    -target x86_64-pc-windows-gnu \
    -g \
    -O0 \
    -std=c++17 \
    -Wall \
    -o"bin/Egler.Core.dll" \
    `ls ../src/Egler.Core/**/*.cpp` \
    -lOpenGL32 -lglew32 -lmingw32 -lSDL2main -lSDL2

if [ $? -ne 0 ]; then
    exit
fi

echo "...done."