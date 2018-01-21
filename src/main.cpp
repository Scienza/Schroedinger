#include <iostream>
#include "Schroedinger.h"
#include "test.h"
#include "gtest/gtest.h"

double potential(double);

int main() {
    int nbox = 1000;
    double step = 0.01, norm;
    double *wavefunction = new double[nbox];
    std::string mode = "TEST";


    if (mode == "TEST") {
      // wavefunction = box_wf(2,nbox);
      // wavefunction = finite_well_wf(2, nbox, 3., 10.);
      wavefunction = harmonic_wf(2,nbox, 1.);

    }else{
      wavefunction[0] = 0.;
      wavefunction[1] = 0.2; //later on it gets renormalized, so is just a conventional number
      solve_Numerov(0., 2., step, nbox, &potential, wavefunction);
    }
    //wavefunction initialization

    return 0;
}

/* potential function defines the potential in function of position */
double potential(double x) {
    double value = x * x;
    return value;
} // end of function to evaluate
