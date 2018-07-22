#ifndef DIMENSION_H
#define DIMENSION_H
#include <stdexcept>

class Dimension {
private:
	int id;
	void setId();

public:
	Dimension();
	const int& getId() const{
		return this->id;
	}

	// Overloading < operator due to "id" comparison used in std::map (ContinuousBase / DiscreteBase)
	friend bool Dimension::operator<(const Dimension& b1, const Dimension& b2) {
		if (b1.getId() == b2.getId())
			return false;
		else return true;
	}

};

class DiscreteDimension : public Dimension
{
public:
	int start, end, step;
	unsigned int base_value;
	DiscreteDimension(int, int, int);
};

class ContinuousDimension : public Dimension
{
public:
	double start, end, mesh, nbox;
	ContinuousDimension(double, unsigned int);
	ContinuousDimension(double, double, double);
	ContinuousDimension(double, double, unsigned int);
};

#endif