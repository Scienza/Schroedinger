#include <iostream>
#include <string>
#include "../src/Potential/Potential.h"
#include "../src/Schroedinger/Schroedinger.h"

int main(int argc, char **argv) {
    unsigned int nbox = 1000;
    double step = 0.01, norm;
    /*
	ContinuousBase x(step, nbox);

    double *wavefunction = new double[nbox];

    Potential::Builder b(x.coord);

    Potential V = b.build();

    wavefunction[0] = 0.;
    wavefunction[1] = 0.2; //later on it gets renormalized, so is just a conventional number
    solve_Numerov(0., 2., 0.01, nbox, V, wavefunction);
	*/
    return 0;
}