#ifndef DISCRETEBASE_H
#define DISCRETEBASE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>

class DiscreteBase 
{
private:
	int start, end, step;
	unsigned int base_value;
	std::vector<int> coords;
	std::vector <int> evaluate();
public:
	std::vector<int> getCoords();
	DiscreteBase();
	DiscreteBase(int, int, int);
};

#endif