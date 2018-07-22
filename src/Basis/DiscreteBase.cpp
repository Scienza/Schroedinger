#include "Base.h"

DiscreteDimension::DiscreteDimension(int start, int end, int step) {
	if ((end - start) / step % 1 != 0)
		throw std::invalid_argument("invalid discrete basis given (check interval and step).");
	if ((end - start) / step < 1)
		throw std::invalid_argument("invalid discrete basis given (check interval and step).");
    if ((end - start) / step == 0)
        throw std::invalid_argument("Empty dimensions basis given.");

	this-> base_value = (end - start) / step;
    this-> start	  = start;
    this-> end		  = end;
    this-> step		  = step;
}

DiscreteBase::DiscreteBase(std::vector< DiscreteDimension > dim)
{
	for (auto &d : dim) {
		this->properties.insert(std::pair(d, evaluateCoord(d)));
	}
}

std::vector<int> DiscreteBase::evaluateCoord(DiscreteDimension dim)
{
	std::vector<int> quantum_numbers;
	quantum_numbers.reserve(dim.base_value);
	int j = 0;
	for (int i = dim.start; i < dim.end; i += dim.step) {
		quantum_numbers[j] = i;
		j++;
	}
	return quantum_numbers;
}
