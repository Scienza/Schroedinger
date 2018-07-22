#ifndef DIMENSION_H
#define DIMENSION_H
class Dimension {
private:
	static int id;
public:
	Dimension() {
		id = id++;
	}
	const int& getId() const{
		return this->id;
	}

	// Overloading < operator due to "id" comparison used in std::map (ContinuousBase / DiscreteBase)
	friend bool operator<(const Dimension& b1, const Dimension& b2) {
		if (b1.getId() == b2.getId())
			return false;
		else return true;
	}

};

int Dimension::id = 0;

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