#!/bin/bash
set -e

cd /workspaces/autonomous-driving-demo

rm -rf build
mkdir -p build
mkdir -p logs

LOG_FILE="logs/build.log"

{
    echo "===== Build started: $(date) ====="
    echo ""

    cd build

    echo "===== CMake ====="
    cmake ..

    echo ""
    echo "===== Make ====="
    make

    echo ""
    echo "===== Tests ====="
    ctest --test-dir build -N
    # ctest --output-on-failure

    echo ""
    echo "===== Application ====="
    ./autonomous_demo

    echo ""
    echo "===== Build finished: $(date) ====="
} 2>&1 | tee "$LOG_FILE"

echo ""
echo "===== SUCCESS ====="
echo "Log: $LOG_FILE"
