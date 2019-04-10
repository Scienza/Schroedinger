file(GLOB_RECURSE LIB_SOURCES
                  ${CMAKE_CURRENT_SOURCE_DIR}/Basis/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/Potential/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/Solver/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/World/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/States/*.cpp)

add_library(schroedinger STATIC ${LIB_SOURCES})
target_include_directories(schroedinger
                           PUBLIC ${PROJECT_SOURCE_DIR}/src/
                                  ${PROJECT_SOURCE_DIR}/src/Basis
                                  ${PROJECT_SOURCE_DIR}/src/Potential
                                  ${PROJECT_SOURCE_DIR}/src/Solver
                                  ${PROJECT_SOURCE_DIR}/src/World
                                  ${PROJECT_SOURCE_DIR}/src/States
                                  ${PROJECT_SOURCE_DIR}/external)

add_executable(schroedinger-cli main.cpp)
target_link_libraries(schroedinger-cli PRIVATE schroedinger)
