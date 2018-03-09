#ifndef DISCRETEBASE_H
#define DISCRETEBASE_H

#include "Base.h"

class DiscreteBase : public Base {
private:
    DiscreteBase(int, int, int);
    std::vector<int> quantum_numbers;


    void combine() {} // @TODO implement
    void change(base_type t) {} // @TODO implement
    void set_potential() {} // @TODO implement

    class Builder {
//    private:
//        std::vector<int> quantum_numbers;
    public:
        Builder addQuantumNumbers(int min_value, int max_value, int step);
        DiscreteBase build();
    };
};

#endif
