cmake_minimum_required(VERSION 3.5)
project(Schroedinger)

# Build options ###
option(ENABLE_TESTS "Enables unit testing" ON)

# Force C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to Release unless another option was set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release"
      CACHE STRING "Build type (Release/Debug/RelWithDebInfo/MinSizeRel)"
      FORCE)
endif()

# Dependencies ###
find_package(Threads REQUIRED)

if(ENABLE_TESTS)
  message(STATUS "Using bundled GTest")
  add_subdirectory(external/googletest EXCLUDE_FROM_ALL)
else()
  message(STATUS "Unit testing was disabled")
endif()

find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(NOT CLANG_FORMAT_EXE)
  message(STATUS "Could not find clang-format")
else()
  message(STATUS "Found clang-format: ${CLANG_FORMAT_EXE}")
endif()

# Project settings ###
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Targets ###
add_subdirectory(src)
if(ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(CLANG_FORMAT_EXE)
  file(GLOB_RECURSE TO_FORMAT
                    "src/*.cpp"
                    "src/*.h"
                    "tests/*.cpp"
                    "tests/*.h")

  add_custom_target(format
                    COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${TO_FORMAT}
                    COMMENT "Formatting source files...")
endif()
