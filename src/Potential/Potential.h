#ifndef POTENTIAL_H
#define POTENTIAL_H

#include <stdbool.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Base.h"

/*! Class Potential contains the potential used in the Schroedinger equation.
 * takes the necessary input: std::vector x at definition Builder(x),
 * it is as vector of position (or base states) to initialize the corresponding calculation.
 * The initialization uses the Builder design pattern. So after creating Potential::Builder object,
 * you can set the attributes and building using Potential V =
 * object.setType("...").setK(0.).build()
 *
 * Other inputs:
 * - string::type, setType(string), sets the potential type that define a certain shape of the
 * potential
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

  public:
    enum PotentialType {
        BOX_POTENTIAL         = 0,
        HARMONIC_OSCILLATOR   = 1,
        FINITE_WELL_POTENTIAL = 2,
    };

    Potential();
    Potential(Base base, std::vector<double> potentialValues);
    Potential(Base, PotentialType, double, double, double, bool);

    const std::vector<double>& getValues() { return this->v; }

    std::vector<Potential> getSeparatedPotentials();

    Base getBase();
    void printToFile();
    bool isSeparated();
    friend std::ostream& operator<<(std::ostream& stream, Potential& potential);

    class Builder {
      private:
        Base base;
        PotentialType type = PotentialType::BOX_POTENTIAL;
        double k           = 0.5;
        double width       = 5.0;
        double height      = 10.0;
        bool separable     = false;
        bool fromFile      = false;
        std::vector<Potential> separated_potentials;
        std::vector<double> potentialValues;

      public:
        Builder(Base b);
        Builder(const std::string& filename);
        Builder setK(double k_new);
        Builder setWidth(double width_new);
        Builder setHeight(double height_new);
        Builder setType(PotentialType type);
        Builder setBase(Base b);
        Builder setSeparable(bool separable);
        Potential build();
    };

  private:
    Base base;
    std::vector<double> v;
    PotentialType type;

    double k;
    double width;
    double height;
    bool separable;
    std::vector<Potential> separated_potentials;

    void ho_potential();
    void box_potential();
    void finite_well_potential();
};

#endif
