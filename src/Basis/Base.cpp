#include "Base.h"
Base::Base(BaseType t, int n_dimension, std::vector<ContinuousDimension> c_dim, std::vector<DiscreteDimension> d_dim) {

	switch (t) {
		case Cartesian: std::cout << "Initializing Cartesian Basis" << std::endl;
			//TODO: add here, for each base type, a control for dimensions 
			break;
		case Spherical: std::cout << "Initializing Spherical Basis" << std::endl;
			break;
		case Cylindrical: std::cout << "Initializing Cylindrical Basis" << std::endl;
			break;
		default: throw std::invalid_argument("Wrong basis type or initialization meaningless!");
			break;
	}

	this->dimensions = n_dimension;
	this->continuous = ContinuousBase(c_dim);
	this->discrete   = DiscreteBase(d_dim);
};