#ifndef POTENTIAL
#define POTENTIAL

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

/*! Class Potential contains the potential used in the Schroedinger equation.
 * takes the necessary input: std::vector x at definition Builder(x),
 * it is as vector of position (or base states) to initialize the corresponding calculation.
 * The initialization uses the Builder design pattern. So after creating Potential::Builder object, you can set the
 * attributes and building using Potential V = object.setType("...").setK(0.).build()
 *
 * Other inputs:
 * - string::type, setType(string), sets the potential type that define a certain shape of the potential
 *   ("box", "finite well", "harmonic oscillator")
 * - double k, setK(double), sets the harmonic oscillator strength parameter
 * - double width, setWidth(double), sets the finite well width.
 * - double height, setHeight(double), set the finite well depth.
 *
 * Outputs:
 * - v, the std::vector of output, the value of the potential for every value of x.
 *
 * Eventually it throws invalid_argument exception if given parameters are wrong.
 */

class Potential {
private:
    std::vector<double> x;
    std::vector<double> v;
    std::string type;
    double k;
    double width;
    double height;

    void ho_potential();
    void box_potential();
    void finite_well_potential();

public:
    Potential(std::vector<double>, std::string, double, double, double);
    std::vector<double> get_v();

    class Builder{
        private:
            std::vector<double> x;
            std::string type     = "box";
            double k             = 0.5;
            double width         = 5.0;
            double height        = 10.0;

        public:
            Builder(std::vector<double> x_new) {
                this->x = x_new;
            }

            Builder setK(double k_new){
                this->k = k_new;
                return *this;
            }

            Builder setWidth(double width_new){
                if (width_new >= 0) {
                    this->width = width_new;
                    return *this;
                }
                else throw std::invalid_argument("Width parameter cannot be negative.");
            }

            Builder setHeight(double height_new){
                this->height = height_new;
                return *this;
            }

            Builder setType(std::string type){
                if (!type.empty()) {
                    this->type = type;
                    return *this;
                }
                else throw std::invalid_argument("Empty type given as parameter.");
            }

            Potential build(){
                try {
                    return Potential(this->x,this->type,this->k,this->width,this->height);
                }
                catch(const std::invalid_argument& e){
                    throw;
                }
            }
    };
};


#endif