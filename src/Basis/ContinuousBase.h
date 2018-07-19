#ifndef CONTINUOUSBASE_H
#define CONTINUOUSBASE_H

#include <vector>
#include <stdexcept>
#include <iostream>

class ContinuousBase {
private:
	double start;
	double end;
	double mesh;
	unsigned int nbox;
public:
	ContinuousBase();
	ContinuousBase(double, unsigned int);
	ContinuousBase(double, double, double);
	ContinuousBase(double, double, unsigned int);

	std::vector<double> coord;
};

#endif