shopt -s globstar

echo "Building main code..."

./build.sh
if [ $? -eq 0 ]; then
    echo "Done."
fi

echo "Building tests..."

clang++ \
    -target x86_64-pc-windows-gnu \
    -g \
    -O0 \
    -std=c++17 \
    -Wall \
    -o"bin/Egler.Test.exe" \
    `ls src/Egler.Test/**/*.cpp` \
    -lgtest_main -lgtest -lgmock \
    -L"bin" -lEgler.Core

if [ $? -eq 0 ]; then
    echo "Done."
    ./bin/Egler.Test.exe
fi