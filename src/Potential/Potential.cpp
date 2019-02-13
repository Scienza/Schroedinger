#include "Potential.h"

Potential::Potential() {
    throw std::invalid_argument("Can't initialize a potential without specifying parameters");
}

Potential::Potential(Base base, PotentialType type, double k, double width, double height, bool separable)
{
    this->base      = base; 
    this->k         = k;
    this->width     = width;
    this->height    = height;
    this->type      = type;
    this->separable = separable;
    
    // If is not separable, evaluate it 
    if (!this->separable) {
        switch(type) {
            case BOX_POTENTIAL:
                this->box_potential();
                break;
            case HARMONIC_OSCILLATOR:
                this->ho_potential();
                break;
            case FINITE_WELL_POTENTIAL:
                this->finite_well_potential();
                break;
            default:
                throw std::invalid_argument("Wrong potential type or initialization meaningless!");
        }
    }

    // If the potential is separable, then n potentials (one for each base's representation)
    else {
        for (ContinuousBase this_base : base.getContinuous()) {

            std::vector<ContinuousBase> c_base;
            std::vector<DiscreteBase> d_base;

            // Extract continuous representation from the main base
            c_base.push_back(this_base);

            // Create new base object with the extracted representation
            Base monodimensional = Base(Base::basePreset::Custom, 1, c_base, d_base);

            // Create new potential with the new base
            Potential separated_potential = Potential(monodimensional, this->type, this->k, this->width, this->height, false);

            // Add the new Potential to the separated potenial vector associated to the main potential
            this->separated_potentials.push_back(separated_potential);
        }

        for (DiscreteBase this_base : base.getDiscrete()) {
            std::vector<ContinuousBase> c_base;
            std::vector<DiscreteBase> d_base;

            // Extract discrete representation from the main base
            d_base.push_back(this_base);

            // Create new base object with the extracted representation
            Base monodimensional = Base(Base::basePreset::Custom, 1, c_base, d_base);

            // Create new potential with the new base
            Potential separated_potential = Potential(monodimensional, this->type, this->k, this->width, this->height, false);

            // Add the new Potential to the separated potenial vector associated to the main potential
            this->separated_potentials.push_back(separated_potential);
        }
    }
            this->printToFile();

}

void Potential::ho_potential()
{
    std::vector<double> x = this->getCoordsFromBase();
    for(double value : x)
            this->v.push_back(value * value * this->k);
}

void Potential::box_potential()
{
    this->v = this->getCoordsFromBase();
    std::fill(this->v.begin(), this->v.end(), 0.0);
}

void Potential::finite_well_potential()
{
    std::vector<double> x = this->getCoordsFromBase();
    for(double value : x) 
        this->v.push_back((value > -this->width/2.0 && value < this->width/2.0) ? 0.0 : this->height);
}

std::vector<double> Potential::getValues()
{
    this->printToFile();
    return this->v;
}

std::vector<double> Potential::getCoordsFromBase() 
{
    if (this->base.getContinuous().size() == 1)
        return this->base.getContinuous().at(0).getCoords();
 
    else if (this->base.getDiscrete().size() == 1) {
        // In DiscreteBase we have int, so this is a way to return a vector of double
        std::vector<int> original_coords = this->base.getDiscrete().at(0).getCoords();
        return std::vector<double>(original_coords.begin(), original_coords.end());
    }
}

bool Potential::isSeparated() {
    return this->separable;
}

std::vector<Potential> Potential::getSeparatedPotentials() {
    if (this->separable == true && this->separated_potentials.size() > 0)
        return this->separated_potentials;
}

void Potential::printToFile() {
    std::ofstream myfile ("potential.dat");
    int size = 0;
    
    if (this->isSeparated()) {
        int coords_size = this->separated_potentials.at(0).getValues().size();

        if (myfile.is_open()) {
            for (int i = 0; i < coords_size; i++) {
                for (Potential &pot : this->separated_potentials) {
                    myfile << pot.getCoordsFromBase().at(i);
                    myfile << " ";
                    myfile << pot.getValues().at(i);
                    myfile << " ";                   
                }   
                myfile << std::endl ;
            }
            myfile.close();
        }

    }
    else {
        if (myfile.is_open()) {
            for (int i = 0; i < this->getValues().size(); i++) {
                    myfile << this->getCoordsFromBase().at(i);
                    myfile << " ";
                    myfile << this->getValues().at(i);
                    myfile << " ";   
                    myfile << std::endl; 
                }   
            myfile.close();
        }
    }
}
