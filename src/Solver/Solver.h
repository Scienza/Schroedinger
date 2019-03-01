#ifndef SOLVER_H
#define SOLVER_H

#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#define dx 0.01
#define err 1E-10

#define pi 3.14159265359
#define hbar 1
#define mass 1

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <fstream> 

#include "Potential.h"
#include "State.h"

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
