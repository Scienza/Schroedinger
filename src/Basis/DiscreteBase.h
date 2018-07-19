#ifndef DISCRETEBASE_H
#define DISCRETEBASE_H

#include <vector>
#include <stdexcept>
#include <iostream>

class DiscreteBase {
private:
	int start;
	int end;
	int step;
public:
	DiscreteBase(int, int, int);
	std::vector<int> quantum_numbers;
};

#endif