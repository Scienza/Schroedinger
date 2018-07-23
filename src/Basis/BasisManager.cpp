#include <BasisManager.h>
BasisManager* BasisManager::instance = 0;
BasisManager* BasisManager::getInstance()
{
	if (!instance) {
		instance = new BasisManager();
		return instance;
	}
	else {
		return instance;
	}
};

void BasisManager::addBase(Base b) {
	this-> basis.push_back(b);
}

const std::vector<Base> &BasisManager::getBasisList() {
	return this->basis;
}

const std::vector<Base> &BasisManager::getBasisList(Source s) {
	switch (s) {
		case MEMORY:
			return this->basis;
			break;

		case FILE:
			//TODO: read from default basis file
			break;
	}
	return this->basis;
}

Base BasisManager::Builder::build(Base::BaseType b, int dimension) {
	//TODO: Eventually add controls...
	return Base(b, dimension, c_dim, d_dim);
}
BasisManager::Builder BasisManager::Builder::addDiscreteDimension(int start, int end, int step) {
	//TODO: Eventually add controls...
	d_dim.push_back(DiscreteDimension(start, end, step));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuousDimension(double mesh, unsigned int nbox) {
	//TODO: Eventually add controls...
	c_dim.push_back(ContinuousDimension(mesh, nbox));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuousDimension(double start, double end, double mesh) {
	//TODO: Eventually add controls...
	c_dim.push_back(ContinuousDimension(start, end, mesh));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuousDimension(double start, double end, unsigned int nbox) {
	//TODO: Eventually add controls...
	c_dim.push_back(ContinuousDimension(start, end, nbox));
	return *this;
}