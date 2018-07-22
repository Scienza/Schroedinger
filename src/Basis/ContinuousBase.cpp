#include <ContinuousBase.h>

ContinuousDimension::ContinuousDimension(double mesh, unsigned int nbox)
{
	if (end - start <= 0) {
		std::invalid_argument("CountinousBase starting-end = 0");
	}

	this->start = -(nbox / 2.) * mesh;
	this->end   = (nbox / 2.) * mesh;
	this->mesh  = mesh;
	this->nbox  = nbox;
}

ContinuousDimension::ContinuousDimension(double start, double end, double mesh)
{
	if (end - start <= 0) {
		std::invalid_argument("CountinousBase starting-end = 0");
	}

	this->start = start;
	this->end = end;
	this->mesh = mesh;
	this->nbox = (unsigned int)((end - start) / mesh);
}

ContinuousDimension::ContinuousDimension(double start, double end, unsigned int nbox)
{
	if (end - start <= 0) {
		std::invalid_argument("CountinousBase starting-end = 0");
	}
	
	this->start = start;
	this->end = end;
	this->mesh = (end - start) / nbox;
	this->nbox = nbox;
}

// To construct a DiscreteBase of generic dimensions (specified with the vector dim), 
// we fill the map properties with the pair <dimension's properties, evalued coords>
ContinuousBase::ContinuousBase(std::vector< ContinuousDimension > dim)
{
	for (auto &d : dim) {
		this->properties.insert(std::make_pair(d, evaluateCoord(d)));
	}
}

std::vector<double> ContinuousBase::evaluateCoord(ContinuousDimension dim)
{
	std::vector<double> coord;
	coord.reserve(dim.nbox);
	for (std::vector<double>::size_type i = 0; i < dim.nbox; i++)
		coord.push_back(dim.start + dim.mesh * i);
	return coord;
}
