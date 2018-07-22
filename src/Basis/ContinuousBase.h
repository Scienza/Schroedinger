#ifndef CONTINUOUSBASE_H
#define CONTINUOUSBASE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>

class ContinuousDimension : public Dimension 
{
public:
	double start, end, mesh, nbox;
	ContinuousDimension(double, unsigned int);
	ContinuousDimension(double, double, double);
	ContinuousDimension(double, double, unsigned int);
};

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