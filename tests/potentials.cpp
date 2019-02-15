#include <gtest/gtest.h>
#include <Potential.h>

TEST(Potentials, widthMustBePositive) {
    Base b;
    try {
        Potential p = Potential::Builder(b).setWidth(-1).build();
        FAIL();
    }
    catch (std::invalid_argument e) {}
}