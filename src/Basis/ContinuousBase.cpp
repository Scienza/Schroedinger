#include <ContinuousBase.h>

ContinuousBase::ContinuousBase() {}
ContinuousBase::ContinuousBase(std::vector< ContinuousDimension > dim)
{
	for (std::vector<ContinuousDimension>::iterator d = dim.begin(); d != dim.end(); ++d) {
		
		this->properties.insert(std::pair(*d, evaluateCoord(*d)));
	}
}

std::vector<double> ContinuousBase::evaluateCoord(ContinuousDimension dim)
{
	std::vector<double> coord;
	coord.reserve(dim.nbox);
	for (std::vector<double>::size_type i = 0; i < dim.nbox; i++)
		coord.push_back(dim.start + dim.mesh * i);
	return coord;
}
