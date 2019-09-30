# Schroedinger (c) 2019 Licensed under the GNU LGPL 2.1
# See the included LICENSE for details
cmake_minimum_required(VERSION 3.12)
project(Schroedinger)

add_library(g_options INTERFACE)
add_library(g_warnings INTERFACE)

# Default to Release if build type wasn't specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE STRING "Build type (Release/Debug/RelWithDebInfo/MinSizeRel)" FORCE)
endif()

message(STATUS "Will build in ${CMAKE_BUILD_TYPE} mode")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Build options
option(ENABLE_ASAN "Enable address sanitizer" OFF)
option(ENABLE_TESTS "Enable unit testing" ON)
option(LIBCPP "Use libc++" OFF)

# Use ccache if present on the system
find_program(CCACHE ccache)
if(CCACHE)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

# Set the standard to c++17
target_compile_features(g_options INTERFACE cxx_std_17)

if(MSVC)
  target_compile_options(g_options
                         INTERFACE /Zc:strictStrings-
                                   -DNOMINMAX
                                   -D_CRT_SECURE_NO_DEPRECATE
                                   -D_CRT_NONSTDC_NO_DEPRECATE
                                   -D_CRT_SECURE_NO_WARNINGS)
  if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Release")
    target_compile_options(g_warnings
                           INTERFACE /W3 "/permissive-")
	target_compile_options(g_options INTERFACE /MTd)
  else()
	target_compile_options(g_options INTERFACE /MT)
  endif()
else()
  if(ENABLE_ASAN)
    target_compile_options(g_options INTERFACE -fsanitize=address)
    target_link_libraries(g_options INTERFACE -fsanitize=address)
  endif()

  if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Release")
    target_compile_options(g_warnings
                           INTERFACE -Wall
                                     -Wextra
                                     -Wshadow
                                     -Wunused
                                     -Wold-style-cast
                                     -Woverloaded-virtual
                                     -Wcast-align
                                     -Wnull-dereference)
  endif()

  if(LIBCPP)
    target_compile_options(g_options INTERFACE -stdlib=libc++)
  endif()
endif()


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

# Targets
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
