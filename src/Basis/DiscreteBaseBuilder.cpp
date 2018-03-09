#include "DiscreteBase.h"

DiscreteBase::Builder DiscreteBase::Builder::addDimension(int min_value, int max_value, int step)
{
    std::vector<int> dimension((max_value-min_value)/step);
    for(int i = min_value; i <= max_value; i++) {
        dimension.push_back(i);
    }
    dimensions.push_back(dimension);
    return *this;
}

DiscreteBase DiscreteBase::Builder::build()
{
    return DiscreteBase(this->dimensions);
}