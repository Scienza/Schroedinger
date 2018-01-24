cmake_minimum_required(VERSION 3.0)
project(Schroedinger)

find_package(Threads REQUIRED)
# Add all sources file
file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories (include)

set(GOOGLETEST_ROOT external/googletest/googletest)

include_directories(
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
)

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})

add_executable (Schroedinger ${SOURCES})
add_executable(
    unit_tests
    tests/main.cpp
)
add_dependencies(unit_tests googletest)

target_link_libraries(
    unit_tests
    googletest
    pthread
)

include(CTest)
enable_testing()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
