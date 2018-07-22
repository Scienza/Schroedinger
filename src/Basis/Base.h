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
	enum baseType { Cartesian = 0, Spherical = 1, Cylindrical = 2 };
	Base(baseType, int, std::vector< ContinuousDimension >, std::vector< DiscreteDimension >);

	int get_dim() {
		return this->dimensions;
	}
	/*
	ContinuousBase get_continuous() {
		return continuous;
	}
	DiscreteBase get_discrete() {
		return discrete;
	}
	*/

private:
    ContinuousBase continuous;
	DiscreteBase discrete;
	int dimensions;
};

#endif
