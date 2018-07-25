#ifndef BASE_H
#define BASE_H

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
#include <DiscreteBase.h>
#include <ContinuousBase.h>

class Base
{
public:
	enum BaseType { Cartesian = 0, Spherical = 1, Cylindrical = 2 };
	Base(BaseType, int, std::vector< ContinuousBase >, std::vector< DiscreteBase >);

	int getDim();
	std::vector<ContinuousBase> getContinuous();
	std::vector<DiscreteBase> getDiscrete();

private:
	std::vector< DiscreteBase > discrete;
	std::vector< ContinuousBase > continuous;
	int dimensions;
};

#endif
