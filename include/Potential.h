#ifndef POTENTIAL
#define POTENTIAL

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Potential {
private:
    std::vector<double> x;
    std::vector<double> v;
    double k;
    double width;
    double height;
    std::string pot_name;

    void ho_potential(double);
    void box_potential();
    void finite_well_potential(double, double);

public: class Builder{

    private:
        std::vector<double> x;
        double k = 0.5;
        double width = 5.;
        double height = 10.;
        std::string pot_name = "box";

    public:
        Builder(std::vector<double> x_new) {
            this->x = x_new;
        }

        Builder setK(double k_new){
            this->k = k_new;
            return *this;
        }

        Builder setWidth(double width_new){
            this->width = width_new;
            return *this;
        }

        Builder setHeight(double height_new){
            this->height = height_new;
            return *this;
        }

        Builder setType(std::string name){
            this->pot_name = name;
            return *this;
        }

        Potential build(){
            return Potential(this->x,this->pot_name,this->k,this->width,this->height);
        }

    };

    Potential(std::vector<double>, std::string, double, double, double);

//    Potential(std::vector<double>);
//    Potential(std::vector<double>, std::string);
//    Potential(std::vector<double>, std::string, double);

public:
    std::vector<double> get_v();
};


#endif