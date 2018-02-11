#include "../include/Potential.h"

std::vector<double> Potential::get_v() {
    return this->v;
}


Potential::Potential(std::vector<double> coord) : Potential(coord, "harmonic oscillator", 0.5) {}
Potential::Potential(std::vector<double> coord, std::string name){

    if(name.compare("finite well potential") == 0 || name.compare("well") == 0|| name.compare("2") == 0 )
        Potential(coord, name, 10., 5.);
    else
        Potential(coord, name, 0.5);
  }

Potential::Potential(std::vector<double> coord, std::string name, double k)
{
    std::cout << name << " " << coord.size() << std::endl;

    this->x = coord;
    this->v = x;
    this->pot_name = name;

    std::transform(name.begin(), name.end(), name.begin(),::tolower); //make pot_name lowercase
    if(name.compare("box potential") == 0 || name.compare("box") == 0 || name.compare("0") == 0)
        this->box_potential();
    else if(name.compare("harmonic oscillator") == 0 || name.compare("ho") == 0 ||  name.compare("1") == 0)
        this->ho_potential(k);
    else if(name.compare("finite well potential") == 0 || name.compare("well") == 0|| name.compare("2") == 0 ) {
        //        this->finite_well_potential();
        std::cerr << "! ERROR: wrong initialization !\n"
                << "! finite well potential needs two variables, not one! " << std::endl;
        exit(8);
    }
    else{
        std::cerr << "! ERROR: wrong potential name!\n! Potential" << name << "not known!" << std::endl;
        exit(8);
    }
}

Potential::Potential(std::vector<double> coord, std::string name, double height, double width){
    std::cout << name << " ?" << coord.size() << std::endl;

    this->x = coord;
    this->v = x;
    this->pot_name = name;

    if(name.compare("finite well potential") || name.compare("well") || name.compare("2") ){
      this->finite_well_potential(height, width);
    }
    else{
        std::cerr << "! ERROR: wrong potential name!\n! Potential" << name << "not known!\n"
                  << "! or initialization with two variables meaningless" << std::endl;
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
