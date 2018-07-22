#ifndef DIMENSION_H
#define DIMENSION_H

class DiscreteDimension 
{
public:
	int start, end, step;
	unsigned int base_value;
	DiscreteDimension(int, int, int);
};

class ContinuousDimension 
{
public:
	double start, end, mesh, nbox;
	ContinuousDimension(double, unsigned int);
	ContinuousDimension(double, double, double);
	ContinuousDimension(double, double, unsigned int);
};


#endif