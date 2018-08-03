#ifndef CONTINUOUSBASE_H
#define CONTINUOUSBASE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>

class ContinuousBase 
{
private:
	double start, end, mesh, nbox;
	std::vector<double> coords;
	std::vector<double> evaluate();
public:
	std::vector<double> getCoords();
	ContinuousBase();	
	ContinuousBase(double, unsigned int);
	ContinuousBase(double, double, double);
	ContinuousBase(double, double, unsigned int);
};

#endif