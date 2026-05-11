cmake_minimum_required(VERSION 3.16)
project(cpp-kickstart LANGUAGES CXX)

# C++ config
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_EXTENSIONS ON)

# Default to Release build
if(NOT CMAKE_BUILD_TYPE)
  set(
    CMAKE_BUILD_TYPE Release
    CACHE STRING "Build type" FORCE
  )
endif()

# Default to default sanitizer set
if(NOT SANITIZER_SET)
  set(
    SANITIZER_SET "default"
    CACHE STRING "Sanitizer set (default|thread|memory|none)" FORCE
  )
endif()

# Tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Use ccache if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# Conan (optional)
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake OPTIONAL)

# Flags
add_compile_options(-Wall -Wextra)
add_link_options(-fuse-ld=lld)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
add_compile_options(-g -O0 -fno-omit-frame-pointer)
  if(SANITIZER_SET STREQUAL "default")
    add_compile_options(-fsanitize=address,undefined,leak)
    add_link_options(-fsanitize=address,undefined,leak)
  elseif(SANITIZER_SET STREQUAL "memory")
    add_compile_options(-fsanitize=memory -fsanitize-memory-track-origins)
    add_link_options(-fsanitize=memory -fsanitize-memory-track-origins)
  elseif(SANITIZER_SET STREQUAL "thread")
    add_compile_options(-fsanitize=thread)
    add_link_options(-fsanitize=thread)
  elseif(SANITIZER_SET STREQUAL "none")
    message(STATUS "No sanitizers enabled.")
  endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_compile_options(-O3 -ffast-math -march=native -DNDEBUG)
endif()

# Target
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE)
