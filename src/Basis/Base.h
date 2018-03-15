#ifndef BASE_H
#define BASE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include "Potential.h"

class Base {
private:

    class DiscreteBase {
    private:
        int start;
        int end;
        int step;
    public:
        DiscreteBase(int, int, int);
        std::vector<int> quantum_numbers;
    };

    class ContinuousBase {
    private:
        double starting;
        double end;
        std::vector<double> mesh;
        unsigned int nbox;
    public:
        ContinuousBase(double, double, std::vector<double>, unsigned int);
        std::vector<double> coord;
    };

public:
    Base() {};
    ~Base() = default;
    void combine() = 0;
    void change(base_type t) = 0;

    std::vector<DiscreteBase> quantumNumbers;
    std::vector<ContinuousBase> coords;
};

#endif
