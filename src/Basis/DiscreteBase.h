#ifndef DISCRETEBASE_H
#define DISCRETEBASE_H

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class DiscreteBase {
  public:
    DiscreteBase(int, int, int);

    const std::vector<int>& getCoords() const { return this->coords; }

  private:
    int start, end, step;
    unsigned int base_value;
    std::vector<int> coords;
    std::vector<int> evaluate();
};

#endif