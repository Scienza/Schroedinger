#include <iostream>
#include <string>
#include "test.h"
#include "Schroedinger.h"
#include "potentials.h"

int main(int argc, char **argv) {
    int nbox = 1000;
    double step = 0.01, norm;
    double *wavefunction = new double[nbox];

    wavefunction[0] = 0.;
    wavefunction[1] = 0.2; //later on it gets renormalized, so is just a conventional number
    solve_Numerov(0., 2., step, nbox, &potential, wavefunction);

   return 0;
}
