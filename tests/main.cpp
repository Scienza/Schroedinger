#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#include <gtest/gtest.h>
#include <Numerov.h>
#include <Potential.h>
#include "basis.cpp"
#include "potentials.cpp"
#include "solvers.cpp"


double H3(double x) { return 8 * std::pow(x, 3) - 12 * x; }
double H4(double x) { return 16 * std::pow(x, 4) - 48 * x * x + 12; }

namespace {
    TEST(NumTest, Hermite) {
        ASSERT_NEAR(std::hermite(3, 10.), H3(10.), err);
        ASSERT_NEAR(std::hermite(4, 4.3), H4(4.3), err);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout.rdbuf(nullptr);
    std::cerr.rdbuf(nullptr);
    return RUN_ALL_TESTS();
}
