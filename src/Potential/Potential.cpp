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
    this->v         = std::vector<double>();

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
        this->separated_potentials = std::vector<Potential>();

        for (int i = 0; i < base.getContinuous().size(); i++) {
            // Extract continuous representation from the main base
            std::vector<ContinuousBase> c_base = std::vector<ContinuousBase>(1);
            c_base.push_back(base.getContinuous().at(i));

            // Create new base object with the extracted representation
            Base monodimensional = Base(Base::basePreset::Custom, 1, c_base, std::vector<DiscreteBase>());

            // Create new potential with the new base
            Potential separated_potential = Potential(monodimensional, this->type, this->k, this->width, this->height, false);

            // Add the new Potential to the separated potenial vector associated to the main potential
            this->separated_potentials.push_back(separated_potential);
        }

        for (int i = 0; i < base.getDiscrete().size(); i++) {
            // Extract discrete representation from the main base
            std::vector<DiscreteBase> d_base = std::vector<DiscreteBase>(1);
            d_base.push_back(base.getDiscrete().at(i));

            // Create new base object with the extracted representation
            Base monodimensional = Base(Base::basePreset::Custom, 1, std::vector<ContinuousBase>(), d_base);

            // Create new potential with the new base
            Potential separated_potential = Potential(monodimensional, this->type, this->k, this->width, this->height, false);

            // Add the new Potential to the separated potenial vector associated to the main potential
            this->separated_potentials.push_back(separated_potential);
        }
    }
}

void Potential::ho_potential()
{
    std::vector<double> x = this->getCoordsFromBase();
    this->v.reserve(x.size());
    for(std::vector<int>::size_type i = 0; i < x.size(); i++)
            this->v.push_back(x.at(i) * x.at(i) * this->k);
}

void Potential::box_potential()
{
    this->v = this->getCoordsFromBase();
    std::fill(this->v.begin(), this->v.end(), 0.0);
}

void Potential::finite_well_potential()
{
    std::vector<double> x = this->getCoordsFromBase();
    this->v.reserve(x.size());
    for(std::vector<int>::size_type i = 0; i < x.size(); i++) {
        double value = (x.at(i) > -this->width/2.0 && x.at(i) < this->width/2.0) ? 0.0 : this->height;
        this->v.push_back(value);
    }
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
        // tricky conversion taking each std::vector<int> value and returning a final std::vector<double> 
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
  if (myfile.is_open())
  {

    for(int i = 0; i < this->v.size(); i ++){
        myfile << i <<" " << this->v.at(i)<< std::endl ;
    }
    myfile.close();
  }
}


