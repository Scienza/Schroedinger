#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#include <gtest/gtest.h>
#include <cmath>
#include "Numerov.h"

double H3(double x) { return 8 * std::pow(x, 3) - 12 * x; }
double H4(double x) { return 16 * std::pow(x, 4) - 48 * x * x + 12; }

namespace {
TEST(NumTest, Hermite) {
    ASSERT_NEAR(std::hermite(3, 10.), H3(10.), err_thres);
    ASSERT_NEAR(std::hermite(4, 4.3), H4(4.3), err_thres);
}
}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout.rdbuf(NULL);
    std::cerr.rdbuf(NULL);
    return RUN_ALL_TESTS();
}
