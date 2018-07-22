#ifndef CONTINUOUSBASE_H
#define CONTINUOUSBASE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>
#include <Dimension.h>

class ContinuousBase 
{
private:
	std::map< ContinuousDimension, std::vector<double>> properties;
	std::vector<double> evaluateCoord(ContinuousDimension);
public:
	ContinuousBase();
	ContinuousBase(std::vector< ContinuousDimension >);
};

#endif