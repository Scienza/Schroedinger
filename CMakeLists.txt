cmake_minimum_required(VERSION 3.5)
project(Schroedinger)

# Force C++17 standard
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_FLAGS -D_EMULATE_GLIBC=0)
set(CMAKE_CXX_FLAGS "--std=c++17") 

# Require git to download submodules
find_package(Git REQUIRED)
find_package(Threads REQUIRED)

# Download submodules
execute_process(
    COMMAND git submodule update --init
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# Main directories
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(GOOGLETEST_DIR external/googletest/googletest)
set(GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_DIR}/src/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_DIR}/src/gtest_main.cc
)

include_directories(
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_DIR}
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/Basis
        ${PROJECT_SOURCE_DIR}/src/Potential
        ${PROJECT_SOURCE_DIR}/src/Solver
		${PROJECT_SOURCE_DIR}/src/World

)

# Fetch all sources, creating ${SOURCES}
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

# Create ${TESTS}, using test's main.cpp instead of ${SOURCE}'s one
set(TESTS ${SOURCES} src/Basis/Initializer.cpp src/Basis/Initializer.h)
list(REMOVE_ITEM TESTS ${SOURCE_DIR}/main.cpp)
list(APPEND TESTS
        ${TEST_DIR}/main.cpp
        ${TEST_DIR}/test.cpp
        ${TEST_DIR}/test.h
)

# Google test things
foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})

# Main executable
add_executable (
    Schroedinger 
    ${SOURCES})

# Test executable
add_executable(
        unit_tests
        ${TESTS})

add_dependencies(unit_tests googletest)
if (WIN32)
    target_link_libraries(
        unit_tests
        googletest
    )
    else()
    target_link_libraries(
        unit_tests
        googletest
        pthread
    )
endif()
