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

    /*! Integrate with the trapezoidal rule method, from a to b position in a function array*/
    static double trapezoidalRule(int a, int b, double stepx, std::vector<double> function) {
        double sum = 0.0;
        for (int j = a + 1; j < b; j++) sum += function.at(j);
        sum += (function.at(a) + function.at(b)) / 2.0;
        sum = (sum)*stepx;
        return sum;
    }

  private:
    void functionSolve(double energy, int potential_index);
    double bisection(double, double, int potential_index);
    void initialize();
};

#endif
