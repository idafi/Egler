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
    -L"bin" -lEgler.Core \
    -lgtest_main -lgmock_main -lgtest -lgmock

if [ $? -eq 0 ]; then
    echo "Done."
    ./bin/Egler.Test.exe
fi