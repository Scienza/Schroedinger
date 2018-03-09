#ifndef BASE_H
#define BASE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include "Potential.h"

// Just an example of base type for basis change
enum base_type { discrete, continuous };

class Base {
protected:

    // About coords: maybe should not exist in this manner. It's better to evaluate at run-time.
    // Instead of a vector of coords it's better to have a vector of Dimensions, where Dimensions are structs
    // with parameters related to basis type.

public:
    Potential *potential;
    Base() {};
    virtual ~Base() = default;
    virtual void combine() = 0;
    virtual void change(base_type t) = 0;

    class DiscreteBase {
    private:
        DiscreteBase(int, int, int);

        std::vector<int> quantum_numbers;
    };

    class ContinuousBase {
    public:
        ContinuousBase(double, double, std::vector<double>, unsigned int);

        std::vector<double> coord;
    };



    std::vector<DiscreteBase> quantumNumbers;
    std::vector<ContinuousBase> coords;
};

#endif
