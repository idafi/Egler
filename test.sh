echo "Building..."
./build.sh

if [ $? -eq 0 ]; then
    echo "Done."
    ./bin/Egler.Test.exe
fi