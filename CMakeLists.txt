cmake_minimum_required(VERSION 3.9)
project(Schroedinger)

set(CMAKE_CXX_STANDARD 11)

add_executable(Schroedinger
        src/Basis/Base.h
        src/Basis/ContinuousBase.cpp
        src/Basis/DiscreteBase.cpp
        src/Potential/Potential.cpp
        src/Potential/Potential.h
        src/Potential/PotentialBuilder.cpp
        src/Schroedinger/Schroedinger.cpp
        src/Schroedinger/Schroedinger.h
        src/main.cpp
        tests/main.cpp
        tests/test.cpp
        tests/test.h
        CMakeLists.txt
        CONTRIBUTING.md
        LICENSE
        README.md)
