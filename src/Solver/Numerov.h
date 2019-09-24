#ifndef NUMEROV_H
#define NUMEROV_H

#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef _MSC_VER
#    if __STDCPP_MATH_SPEC_FUNCS__ < 201003L
#        error \
            "Special mathematical functions are not available \
        in this cmath implementation. Cannot continue."
#    endif
#elif _MSC_VER < 1914
#    error \
        "Special mathematical functions are not available \
in this MSVC version (need at least 19.14). Cannot continue."
#endif

#include "Potential.h"
#include "Solver.h"
#include "State.h"

class Numerov : public Solver {
  public:
    Numerov(Potential potential, int nbox);
    State solve(double, double, double);

  private:
    void functionSolve(double energy, std::vector<double> potential_values, std::vector<double> &wavefunction);
    double bisection(double e_min, double e_max, std::vector<double> potential_values, std::vector<double> &wavefunction,  double wfAtBoundary);
};

#endif
