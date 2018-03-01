#ifndef DISCRETEBASE_H
#define DISCRETEBASE_H

#include "Base.h"

class DiscreteBase : public Base {
public:
    DiscreteBase(std::vector< std::vector<int> > dimensions, Potential potential);

    void combine() {} // @TODO implement
    void change(base_type t) {} // @TODO implement
    void set_potential() {} // @TODO implement

    class Builder {
    private:
        std::vector< std::vector<int> > dimensions;
        Potential potential;
    public:
        Builder addDimension(int min_value, int max_value, int step);
        Builder addPotential(Potential p);
        DiscreteBase build();
    };
};

#endif
