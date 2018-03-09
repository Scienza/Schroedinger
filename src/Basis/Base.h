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
    std::vector< std::vector<double> > coords;

public:
    Base() {};
    virtual ~Base() = default;
    virtual void combine() = 0;
    virtual void change(base_type t) = 0;
    virtual void set_potential() = 0;
};

#endif
