#include <DiscreteBase.h>

DiscreteBase::DiscreteBase() {}
DiscreteBase::DiscreteBase(std::vector< DiscreteDimension > dim)
{
	for (std::vector<DiscreteDimension>::iterator d = dim.begin(); d != dim.end(); ++d) {
		this->properties.insert(std::pair(*d, evaluateCoord(*d)));
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
