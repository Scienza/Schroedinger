#include <iostream>
#include <string>
#include "test.h"
#include "Schroedinger.h"
#include "Potential.h"

int main(int argc, char **argv) {
    unsigned int nbox = 1000;
    double step = 0.01, norm;
    double *wavefunction = new double[nbox];
    std::vector<double> x(nbox);

    for(std::vector<int>::size_type i = 0; i < x.size(); i++)
        x[i] = dx*(i-nbox/2);

    Potential V(x);

    wavefunction[0] = 0.;
    wavefunction[1] = 0.2; //later on it gets renormalized, so is just a conventional number
    solve_Numerov(0., 2., step, nbox, V, wavefunction);

   return 0;
}
