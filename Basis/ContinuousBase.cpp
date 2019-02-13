#include <ContinuousBase.h>

ContinuousBase::ContinuousBase() {}
ContinuousBase::ContinuousBase(double mesh, unsigned int nbox)
{
	if (end - start <= 0) {
		std::invalid_argument("CountinousBase starting-end = 0");
	}

	this->start  = -(nbox / 2.) * mesh;
	this->end	 = (nbox / 2.) * mesh;
	this->mesh   = mesh;
	this->nbox   = nbox;
	this->coords = evaluate();
}

ContinuousBase::ContinuousBase(double start, double end, double mesh)
{
	if (end - start <= 0) {
		std::invalid_argument("CountinousBase starting-end = 0");
	}

	this->start  = start;
	this->end    = end;
	this->mesh   = mesh;
	this->nbox   = (unsigned int)((end - start) / mesh);
	this->coords = evaluate();
}

ContinuousBase::ContinuousBase(double start, double end, unsigned int nbox)
{
	if (end - start <= 0) {
		std::invalid_argument("CountinousBase starting-end = 0");
	}

	this->start  = start;
	this->end    = end;
	this->mesh   = (end - start) / nbox;
	this->nbox   = nbox;
	this->coords = evaluate();
}

std::vector<double> ContinuousBase::evaluate()
{
	std::vector<double> coord;
	coord.reserve(this->nbox);
	for (std::vector<double>::size_type i = 0; i < this->nbox; i++)
		coord.push_back(this->start + this->mesh * i);
	return coord;
}

std::vector<double> ContinuousBase::getCoords() {
	return this->coords;
}
