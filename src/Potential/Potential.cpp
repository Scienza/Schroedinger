#include "Potential.h"

#include <utility>

Potential::Potential() = default;
Potential::Potential(Base base, std::vector<double> potentialValues)
{
    this->base = std::move(base);
    this->v = std::move(potentialValues);
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
    std::vector<double> x = this->base.getCoords();
    this->v = std::vector<double>(this->base.getCoords().size());
    std::fill(this->v.begin(), this->v.end(), 0.0);
    int i = 0;
    for(double value : x) {
            this->v[i] = (value * value * this->k);
            i++;
    }
}

void Potential::box_potential()
{
    this->v = this->base.getCoords();
    std::fill(this->v.begin(), this->v.end(), 0.0);
}

void Potential::finite_well_potential()
{
    std::vector<double> x = this->base.getCoords();
    this->v = x;
    std::fill(this->v.begin(), this->v.end(), 0.0);

    int i = 0;
    for(double value : x)  {
        this->v[i] = (value > -this->width/2.0 && value < this->width/2.0) ? 0.0 : this->height;
        i++;
    }
}

bool Potential::isSeparated() {
    return this->separable;
}

std::vector<Potential> Potential::getSeparatedPotentials() {
    if (separable == true && !separated_potentials.empty())
        return separated_potentials;

    // fixme: need to throw instead?
    return {};
}

void Potential::printToFile() {
  std::ofstream myfile ("potential.dat");
  if (myfile.is_open()) {
    std::vector<double> base_coords = this->base.getCoords();

    for(int i = 0; i < base_coords.size(); i ++)
        myfile << base_coords[i] <<" " << this->v.at(i)<< std::endl ;
    myfile.close();
  }
}

std::ostream& operator<<(std::ostream& stream, Potential& potential) {
	for (double val : potential.getValues())
        stream << val << std::endl;
    return stream;
 }

Base Potential::getBase() {
    return this->base;
}