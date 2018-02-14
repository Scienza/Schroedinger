#include "../include/Potential.h"

std::vector<double> Potential::get_v() {
    return this->v;
}

Potential::Potential(std::vector<double> coord, std::string name, double k, double width, double height){
//    std::cout << this->pot_name << " ?" << this->x.size() << std::endl;
    this->x = coord;
    this->v = x;
    this->k = k;
    this->width = width;
    this->height = height;
    this->pot_name = name;

    if(name.compare("box potential") == 0 || name.compare("box") == 0 || name.compare("0") == 0)
        this->box_potential();
    else if(name.compare("harmonic oscillator") == 0 || name.compare("ho") == 0 ||  name.compare("1") == 0)
        this->ho_potential(k);
    else if(name.compare("finite well potential") || name.compare("well") || name.compare("2") ){
      this->finite_well_potential(this->height, this->width);
    }
    else{
        std::cerr << "! ERROR: wrong potential name!\n! Potential" << name << "not known!\n"
                  << "! or initialization meaningless" << std::endl;
        exit(8);
    }
}

void Potential::ho_potential(double k)
{
    for(std::vector<int>::size_type i = 0; i < x.size(); i++)
        this->v[i] = this->x[i] * this->x[i] * k;
}

void Potential::box_potential()
{
    std::fill(this->v.begin(), this->v.end(), 0.);
}

void Potential::finite_well_potential(double height, double width)
{
    for(std::vector<int>::size_type i = 0; i < x.size(); i++) {
        this->v[i] = (this->x[i] > -width/2. && this->x[i] < width/2.) ? 0.0 : height;
    }
}
