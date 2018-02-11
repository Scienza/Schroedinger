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

    Potential(std::vector<double> x) {
        this->x = x;
    }

    Potential addK(double k){
        this->k = k;
    }

    Potential addWidth(double width){
        this->width = width;
    }

    Potential addHeight(double height){
        this->height = height;
    }

    Potential addName(std::string name){
        this->pot_name = name;
    }

//    Potential(std::vector<double>);
//    Potential(std::vector<double>, std::string);
//    Potential(std::vector<double>, std::string, double);

public:
    std::vector<double> get_v();
    Potential(Builder);

};

class Builder{

public:
    virtual ~Builder();

    Potential* getPotential(){
        return pot;
    };

    std::vector<double> x;
    std::vector<double> v;
    double k = 0.5;
    double width = 5.;
    double height = 10;
    std::string pot_name;



};
#endif