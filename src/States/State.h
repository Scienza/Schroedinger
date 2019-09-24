#ifndef STATE_H
#define STATE_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include <spdlog/fmt/ostr.h>
#include "Base.h"
#include "Potential.h"

constexpr double dx   = 0.01;

class State {
  public:

    State() {}
    State(std::vector<double> wavefunction, Potential potential, double energy, Base base, int nbox);

    const std::vector<double>& getWavefunction();
    const std::vector<double>& getProbability();
    const double& getEnergy();
    Base getBase() const { return base; };

    void printToFile();

    friend std::ostream& operator<<(std::ostream& stream, const State& state);
    friend State operator^ (State& state_1, State& state_2);


    /*! Integrate with the trapezoidal rule method, from a to b position in a function array*/
    static double trapezoidalRule(int a, int b, double stepx, std::vector<double> function) {
        double sum = 0.0;
        for (int j = a + 1; j < b; j++) sum += function.at(j);
        sum += (function.at(a) + function.at(b)) / 2.0;
        sum = (sum)*stepx;
        return sum;
    }

    int nbox;
    Base base;
    Potential potential;
    std::vector<double> wavefunction;
    std::vector<double> probability;
    double energy;
};

#endif
