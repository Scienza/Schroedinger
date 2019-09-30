add_executable(unit_tests main.cpp basis.cpp potentials.cpp solvers.cpp)

target_link_libraries(unit_tests PRIVATE gtest schroedinger_core g_options g_warnings)

target_include_directories(
  unit_tests
  PRIVATE ${PROJECT_SOURCE_DIR}/external/googletest/include)

add_test(NAME unit_testing
         COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests)
