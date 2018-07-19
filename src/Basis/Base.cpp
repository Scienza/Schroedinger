#include "Base.h"
//TODO: instead of having an integer parameter, use the enum baseType
Base::Base(int dimNum) {
	double start = -5., end = 5., mesh = 0.01;
	baseType t = baseType::Cartesian; //TODO: Improve baseType to allow choice in input
	this->dimNum = dimNum;

	switch (t) {
	case 0: std::cout << "Initializing Cartesian Basis" << std::endl;
		break;
	case 1: std::cout << "Initializing Spherical Basis" << std::endl;
		break;
	case 2: std::cout << "Initializing Cylindrical Basis" << std::endl;
		break;
	default: throw std::invalid_argument("Wrong basis type or initialization meaningless!");
	}
	ContinuousBase coord(start, end, mesh);
	this->x = coord;
};