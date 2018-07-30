shopt -s globstar
cd "$(dirname ${BASH_SOURCE[0]})"

echo "rebuilding main libraries..."

./build.sh

if [ $? -ne 0 ]; then
    exit
fi

echo "building Egler.Test..."

clang++ \
    -target x86_64-pc-windows-gnu \
    -g \
    -O0 \
    -std=c++17 \
    -Wall \
    -o"bin/Egler.Test.exe" \
    -L"bin" -lEgler.Core \
    `ls ../src/Egler.Test/**/*.cpp` \
    -lgtest_main -lgtest -lgmock

if [ $? -ne 0 ]; then
    exit
fi

echo "...done."
./bin/Egler.Test.exe