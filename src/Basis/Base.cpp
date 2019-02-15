#include <Base.h>
#include "BasisManager.h"

Base::Base(basePreset t, int n_dimension, std::vector< ContinuousBase > c_base, std::vector< DiscreteBase > d_base) {

	switch (t) {
		//TODO: add here, for each base type, a control for dimensions
		case Custom: std::cout << "Initializing Custom Basis" << std::endl;
			break;
		case Cartesian: std::cout << "Initializing Cartesian Basis" << std::endl;
			break;
		case Spherical: std::cout << "Initializing Spherical Basis" << std::endl;
			break;
		case Cylindrical: std::cout << "Initializing Cylindrical Basis" << std::endl;
			break;
		default: throw std::invalid_argument("Wrong basis type or initialization meaningless!");
			break;
	}

	this->dimensions = n_dimension;
	this->continuous.insert(continuous.end(), c_base.begin(), c_base.end());
	this->discrete.insert(discrete.end(), d_base.begin(), d_base.end());

	BasisManager::getInstance()->selectBase(*this);
};


int Base::getDim() {
	return this->dimensions;
}
std::vector<ContinuousBase> Base::getContinuous() {
	return this->continuous;
}
std::vector<DiscreteBase> Base::getDiscrete() {
	return this->discrete;
}

std::ostream& operator<<(std::ostream& stream, Base& base) {

	// Print continuous dimension values (if present)
	if (base.getContinuous().size() > 0)
		for (int i = 0; i < base.getContinuous().size(); i++) {
			for (int coord_counter = 0; coord_counter < base.getContinuous().at(i).getCoords().size(); coord_counter++)
				stream << base.getContinuous().at(i).getCoords().at(coord_counter) << "; ";
		}

	stream << "\n\n";

	// Print discrete dimension values (if present)
	if (base.getDiscrete().size() > 0)
		for (int i = 0; i < base.getContinuous().size(); i++) {
			for (int coord_counter = 0; coord_counter < base.getDiscrete().at(i).getCoords().size(); coord_counter++)
				stream << base.getDiscrete().at(i).getCoords().at(coord_counter) << "; ";
		}

    return stream;
 }

// This method let you get basis coords when it has only one dimension
std::vector<double> Base::getCoords() 
{
    if (this->getContinuous().size() == 1) {
		std::vector<double> toreturn = this->getContinuous().at(0).getCoords();
		return toreturn;
	}
         
 
    else if (this->getDiscrete().size() == 1) {
        // tricky conversion taking each std::vector<int> value and returning a final std::vector<double> 
        std::vector<int> original_coords = this->getDiscrete().at(0).getCoords();
		std::vector<double> toreturn = std::vector<double>(original_coords.begin(), original_coords.end());
        return toreturn;
    }
	else throw std::runtime_error("Can't get coords from multidimensional basis using this method. ");
}