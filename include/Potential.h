#ifndef POTENTIAL
#define POTENTIAL

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*! Class Potential contains the potential used in the Schroedinger equation.
 * takes the necessary input: std::vector x at definition Builder(x),
 * it is as vector of position (or base states) to initialize the corresponding calculation.
 * The initialization uses the Builder design pattern. So after creating Potential::Builder object, you can set the
 * attributes and building using Potential V = object.setType("...").setK(0.).build()
 * Other inputs:
 * - string::pot_name, setType(string), sets the potential type that define a certain shape of the potential
 *   ("box", "finite well", "harmonic oscillator")
 * - double k, setK(double), sets the harmonic oscillator strength parameter
 * - double width, setWidth(double), sets the finite well width.
 * - double height, setHeight(double), set the finite well depth.
 * Outputs:
 * - v, the std::vector of output, the value of the potential for every value of x.
 */

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