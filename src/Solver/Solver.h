#ifndef SOLVER_H
#define SOLVER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Potential.h"
#include "State.h"

constexpr double pi   = 3.14159265358979323846;
constexpr double pi_2 = 1.57079632679489661923;
constexpr double hbar = 1;
constexpr double mass = 1;
constexpr double dx   = 0.01;

constexpr double err_thres = 10E-10;

static_assert(std::numeric_limits<double>::is_iec559,
              "Floating-point representation not supported");

class Solver {
  public:
    Solver(Potential, int);
    virtual State solve(double, double, double) = 0;

  protected:
    Potential potential;
    int nbox;
    double solutionEnergy;
    double wfAtBoundary;
    std::vector<double> wavefunction;
    std::vector<double> probability;
    Base::boundaryCondition boundary;
};

#endif
