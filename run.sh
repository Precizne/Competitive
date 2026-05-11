#!/usr/bin/env bash
set -e

# Choose Debug or Release (default: Release)
BUILD_TYPE=${1:-Release}
BUILD_DIR="build/$BUILD_TYPE"

# Step 1: Refresh Conan profile
conan profile detect --force

# Step 2: Install dependencies
conan install . --output-folder="$BUILD_DIR" --build=missing -s build_type="$BUILD_TYPE"

# Step 3: Configure with CMake
cmake -S . -B "$BUILD_DIR" -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$BUILD_DIR/conan_toolchain.cmake" \
  -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
  -DSANITIZER_SET=default

# Step 4: Build
cmake --build "$BUILD_DIR"

# Step 5: Run
timeout 3s "$BUILD_DIR/main"
