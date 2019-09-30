file(GLOB_RECURSE SCH_SOURCES
                  ${CMAKE_CURRENT_SOURCE_DIR}/Basis/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/Potential/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/Solver/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/World/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/States/*.cpp)

add_library(schroedinger_core OBJECT ${SCH_SOURCES})
target_link_libraries(schroedinger_core PRIVATE g_options g_warnings)

target_include_directories(schroedinger_core
                           PUBLIC ${PROJECT_SOURCE_DIR}/src/
                                  ${PROJECT_SOURCE_DIR}/src/Basis
                                  ${PROJECT_SOURCE_DIR}/src/Potential
                                  ${PROJECT_SOURCE_DIR}/src/Solver
                                  ${PROJECT_SOURCE_DIR}/src/World
                                  ${PROJECT_SOURCE_DIR}/src/States
                                  ${PROJECT_SOURCE_DIR}/external)

add_executable(schroedinger-cli main.cpp)
target_link_libraries(schroedinger-cli PRIVATE schroedinger_core g_options g_warnings)
