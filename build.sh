#!/usr/bin/env sh
# Configure and build BitChess into ./build, then print how to run it.
# Usage: ./build.sh          (build)
#        ./build.sh run      (build, then launch the game)
set -e

cd "$(dirname "$0")"

cmake -B build
cmake --build build -j

if [ "$1" = "run" ]; then
    ./build/bit_chess
else
    echo
    echo "Build complete. Run the game with:  ./build/bit_chess"
fi
