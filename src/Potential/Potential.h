#ifndef POTENTIAL_H
#define POTENTIAL_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "../Basis/Base.h"

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
    Potential(std::vector<double>, std::string, double, double, double, Base *base);
    std::vector<double> get_v();
    Base get_x();

    class Builder{
        private:
            std::vector<double> x;
            std::string type     = "box";
            double k             = 0.5;
            double width         = 5.0;
            double height        = 10.0;
            Base *base;

        public:
            Builder(std::vector<double> x_new);
            Builder setK(double k_new);
            Builder setWidth(double width_new);
            Builder setHeight(double height_new);
            Builder setType(std::string type);
            Builder setBase(Base b);
            Potential build();
    };
};

#endif