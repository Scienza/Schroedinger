#ifndef NUMEROV_H
#define NUMEROV_H

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
#include <Solver.h>
#include <Potential.h>
#include <State.h>

class Numerov : public Solver {
        public:
                Numerov(Potential potential, int nbox);
                State solve(double, double, double);

                /*! Integrate with the trapezoidal rule method, from a to b position in a function array*/
                static double trapezoidalRule(int a, int b, double stepx, std::vector<double> function) {
                        double sum = 0.0;
                        for (int j = a + 1; j < b; j++) 
                                sum += function.at(j);
                        sum += (function.at(a) + function.at(b)) / 2.0;
                        sum = (sum) * stepx;
                        return sum;
                }
                
        private:
                void functionSolve(double energy);
                double bisection(double, double);
};

#endif
