#ifndef DISCRETEBASE_H
#define DISCRETEBASE_H

#include <vector>
#include <stdexcept>
#include <iostream>

class DiscreteDimension : Dimension{
public:
	int start, end, step;
	unsigned int base_value;
	DiscreteDimension(int, int, int);
};

class DiscreteBase {
private:
	std::map < DiscreteDimension , std::vector<int> > properties;
	std::vector<int> evaluateCoord( DiscreteDimension);
public:
	DiscreteBase();
	DiscreteBase(std::vector< DiscreteDimension >);
};

#endif