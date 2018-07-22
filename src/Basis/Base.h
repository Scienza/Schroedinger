#ifndef BASE_H
#define BASE_H

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

#include <Dimension.h>
#include <DiscreteBase.h>
#include <ContinuousBase.h>

class Base
{
public:
	enum BaseType { Cartesian = 0, Spherical = 1, Cylindrical = 2 };
	Base(BaseType, int, std::vector< ContinuousDimension >, std::vector< DiscreteDimension >);

	int get_dim() {
		return this->dimensions;
	}
	
	const ContinuousBase& get_continuous() const {
		return continuous;
	}
	const DiscreteBase& get_discrete() const {
		return discrete;
	}
	

private:
    ContinuousBase continuous;
	DiscreteBase discrete;
	int dimensions;
};

#endif
