#ifndef BASE_H
#define BASE_H

#include <vector>
#include <stdexcept>
#include <iostream>

class Base {
public:

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
        double start;
        double end;
        double mesh;
        unsigned int nbox;
    public:
        ContinuousBase(double, double, double);
        ContinuousBase(double, double, unsigned int);

        std::vector<double> coord;
    };

public:
    Base() {};
    ~Base() = default;
};

#endif
