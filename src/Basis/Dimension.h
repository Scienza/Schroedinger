// Dimension class (specified and implemented inside ContinuousBase and DiscreteBase)
// used to add arbitrary dimension to basis.
class Dimension {};

class DiscreteDimension : Dimension
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