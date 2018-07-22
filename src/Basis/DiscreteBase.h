#ifndef DISCRETEBASE_H
#define DISCRETEBASE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>
#include <Dimension.h>

class DiscreteBase 
{
private:
	std::map < DiscreteDimension , std::vector<int> > properties;
	std::vector <int> evaluateCoord( DiscreteDimension);
public:
	DiscreteBase();
	DiscreteBase(std::vector < DiscreteDimension >);
};

#endif