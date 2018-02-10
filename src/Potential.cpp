#include "../include/Potential.h"


Potential::Potential(std::vector<double> coord) : Potential(coord, "harmonic oscillator", 0.5) {}
Potential::Potential(std::vector<double> coord, std::string name, double k)
{
    this->x = coord;
    std::transform(name.begin(), name.end(), name.begin(),::tolower); //make pot_name lowercase

    if(name.compare("harmonic oscillator") == 0 || name.compare("ho") == 0 ||  name.compare("1") == 0)
        this->ho_potential(k);
    else if(name.compare("box potential") == 0 )
        this->box_potential();
    else if(name.compare("finite well potential"))
        this->finite_well_potential();
}

std::vector<double> Potential::get_v() {
    return this->v;
}

void Potential::ho_potential(double k)
{
  for(std::vector<int>::size_type i = 0; i < x.size(); i++) {
      this->v[i] = this->x[i] * this->x[i] * k;
  }
}

void Potential::box_potential()
{
  std::fill(this->v.begin(), this->v.end(), 0);
}

void Potential::finite_well_potential()
{
    const  double width = 5.0;
    const  double height = 10.0;

    for(std::vector<int>::size_type i = 0; i < x.size(); i++) {
        this->v[i] = (this->x[i] > -width/2. && this->x[i] < width/2.) ? 0.0 : height;
    }
}
