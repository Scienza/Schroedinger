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
	this-> bases.push_back(b);
}

std::vector<Base> BasisManager::getBasisList() {
	return this->bases;
}

std::vector<Base> BasisManager::getBasisList(Source s) {
	switch (s) {
		case MEMORY:
			return this->bases;
			break;

		case FILE:
			//TODO: read from default basis file
			break;
	}
	return this->bases;
}

Base BasisManager::Builder::build(Base::BaseType b, int dimension) {
	//TODO: Eventually add controls...
	return Base(b, dimension, c_base, d_base);
}
BasisManager::Builder BasisManager::Builder::addDiscrete(int start, int end, int step) {
	//TODO: Eventually add controls...
	d_base.push_back(DiscreteBase(start, end, step));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuous(double mesh, unsigned int nbox) {
	//TODO: Eventually add controls...
	c_base.push_back(ContinuousBase(mesh, nbox));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuous(double start, double end, double mesh) {
	//TODO: Eventually add controls...
	c_base.push_back(ContinuousBase(start, end, mesh));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuous(double start, double end, unsigned int nbox) {
	//TODO: Eventually add controls...
	c_base.push_back(ContinuousBase(start, end, nbox));
	return *this;
}
