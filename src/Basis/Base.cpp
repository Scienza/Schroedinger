#include "Base.h"
#include "BasisManager.h"
#include "LogManager.h"

Base::Base(const std::vector<double>& coords) {
    this->dimensions = 1;
    this->continuous.emplace_back(coords);
    this->boundary = ZEROEDGE;
}

Base::Base(basePreset t, int n_dimension, std::vector<ContinuousBase> c_base,
           std::vector<DiscreteBase> d_base) {

    switch (t) {
        // TODO: add here, for each base type, a control for dimensions
        case Custom:
            INFO("Initializing custom basis");
            break;
        case Cartesian:
            INFO("Initializing cartesian basis");
            break;
        case Spherical:
            INFO("Initializing Spherical Basis");
            break;
        case Cylindrical:
            INFO("Initializing Cylindrical Basis");
            break;
        default:
            throw std::invalid_argument("Wrong basis type or initialization meaningless!");
            break;
    }

    this->dimensions = n_dimension;
    this->continuous.insert(continuous.end(), c_base.begin(), c_base.end());
    this->discrete.insert(discrete.end(), d_base.begin(), d_base.end());
    this->boundary = ZEROEDGE;

    BasisManager::getInstance()->selectBase(*this);
};

std::ostream& operator<<(std::ostream& stream, Base& base) {

    // Print continuous dimension values (if present)
    if (!base.getContinuous().empty()) {
        for (int i = 0; i < base.getContinuous().size(); i++) {
            for (int coord_counter = 0; coord_counter < base.getContinuous().at(i).getCoords().size(); coord_counter++) {
                stream << base.getContinuous().at(i).getCoords().at(coord_counter) << "; ";
            }
        }
    }

    stream << "\n\n";

    // Print discrete dimension values (if present)
    //if (!base.getDiscrete().empty()) {
    //    for (int i = 0; i < base.getContinuous().size(); i++) {
    //        for (int coord_counter = 0; coord_counter < base.getDiscrete().at(i).getCoords().size();
    //             coord_counter++) {
    //            stream << base.getDiscrete().at(i).getCoords().at(coord_counter) << "; ";
    //        }
    //    }
    //}

    return stream;
}

    const Base operator+(Base& base1, Base& base2) {
        std::vector<DiscreteBase> discrete_dimension = std::vector<DiscreteBase>();
        std::vector<ContinuousBase> continuous_dimension = std::vector<ContinuousBase>();
        
        for (int i = 0; i < base1.getDiscrete().size(); i++)
            discrete_dimension.push_back(base1.getDiscrete().at(i));

        for (int i = 0; i < base2.getDiscrete().size(); i++)
            discrete_dimension.push_back(base2.getDiscrete().at(i));

        for (int i = 0; i < base1.getContinuous().size(); i++)
            continuous_dimension.push_back(base1.getContinuous().at(i));

        for (int i = 0; i < base2.getContinuous().size(); i++)
            continuous_dimension.push_back(base2.getContinuous().at(i));

        const Base& base = Base(Base::basePreset::Custom, 
                        (base1.getDim() + base2.getDim()), 
                        continuous_dimension, 
                        discrete_dimension);
        return base;

    }

// This method let you get basis coords when it has only one dimension
std::vector<double> Base::getCoords() {
    if (this->getContinuous().size() == 1) {
        std::vector<double> toreturn = this->getContinuous().at(0).getCoords();
        return toreturn;
    } else if (this->getDiscrete().size() == 1) {
        // tricky conversion taking each std::vector<int> value and returning a final
        // std::vector<double>
        std::vector<int> original_coords = this->getDiscrete().at(0).getCoords();
        std::vector<double> toreturn =
            std::vector<double>(original_coords.begin(), original_coords.end());
        return toreturn;
    } else {
        throw std::runtime_error(
            "Can't get coords from multidimensional basis using this method. ");
    }
}