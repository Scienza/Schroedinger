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
    std::string pot_name;

    void ho_potential(double);
    void box_potential();
    void finite_well_potential(double, double);

    class Builder{

    public:
        std::vector<double> x;
        std::vector<double> v;
        double k = 0.5;
        double width = 5.;
        double height = 10;
        std::string pot_name;

        Builder(std::vector<double> x) {
            this->x = x;
        }

        Builder addK(double k){
            this->k = k;
        }

        Builder addWidth(double width){
            this->width = width;
        }

        Builder addHeight(double height){
            this->height = height;
        }

        Builder addName(std::string name){
            this->pot_name = name;
        }

        Potential build(){
            return new Potential(this);
        }

    };

    Potential(Builder);

//    Potential(std::vector<double>);
//    Potential(std::vector<double>, std::string);
//    Potential(std::vector<double>, std::string, double);


    std::vector<double> get_v();
};


#endif