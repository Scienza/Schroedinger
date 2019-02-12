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
#include <Potential.h>

class Numerov {
        public:
                Potential *potential;
                int nbox;

                Numerov(Potential, int);
                std::vector<double> getWavefunction();
                std::vector<double> getProbability();
                double getSolutionEnergy();
                double solve(double, double, double);
                void printToFile();
	        friend std::ostream& operator<< (std::ostream& stream, Numerov& solver);

                // Integrate with the trapezoidal rule method, from a to b position in a function array
                // This is static and public in order to be used by analytical functions outside of this class
                static double trapezoidalRule(int a, int b, double stepx, std::vector<double> function) {
                        double sum = 0.0;
                        for (int j = a + 1; j < b; j++) 
                                sum += function.at(j);
                        sum += (function.at(a) + function.at(b)) / 2.0;
                        sum = (sum) * stepx;
                        return sum;
                }
        private:
                double solutionEnergy;
                std::vector<double> wavefunction;
                std::vector<double> tempWavefunction;
                std::vector<double> probability;
                void findWavefunction(double, std::vector<double>&);
                void multiplyWavefunction();
                double bisection(double, double, std::vector<double>&);
                double findEnergy(double, double, double, std::vector<double>&);
                void normalize();
                std::vector<double> findProbability();

};

#endif
