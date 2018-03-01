#include "DiscreteBase.h"

DiscreteBase::DiscreteBase(std::vector< std::vector<int> > dimensions, Potential potential)
{
    if (dimensions.size() == 0)
        throw std::invalid_argument("Empty dimensions vector given.");

    // Due to the fact that Basis->coords is vector<double>
    // here's the conversion from vector<int> to vector<double>
    this->coords.reserve(dimensions.size());
    for(auto&& dimension : dimensions) {
        this->coords.emplace_back(dimension.begin(), dimension.end());
    }
    this->potential = &potential;
}
