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
	enum BaseType { Custom = 0, Cartesian = 1, Spherical = 2, Cylindrical = 3 };
	Base(BaseType, int, std::vector< ContinuousBase >, std::vector< DiscreteBase >);
	Base() {}
	int getDim();
	std::vector<ContinuousBase> getContinuous();
	std::vector<DiscreteBase> getDiscrete();

private:
	std::vector< DiscreteBase > discrete;
	std::vector< ContinuousBase > continuous;
	int dimensions;
};

#endif
