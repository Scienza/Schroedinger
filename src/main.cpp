#include <iostream>
#include <string>
#include "test.h"
#include "Schroedinger.h"


/* potential function defines the potential in function of position */
double potential(double x) {
  double value = x * x;
  return value;
} // end of function to evaluate


double ho_potential(double x) {
  return x*x;
} // end of function to evaluate

double box_potential(double x) {
  return 0.;
}

double finite_well_potential(double x) {
  double width = 3., height = 10.;

  if(x < -width){
    return height;
  }else if(x > - width && x < width){
    return 0.;
  }else{
    return height;
  }
}

int main(int argc, char **argv) {
    int nbox = 1000;
    double step = 0.01, norm;
    double *wavefunction = new double[nbox];
    
    wavefunction[0] = 0.;
    wavefunction[1] = 0.2; //later on it gets renormalized, so is just a conventional number
    solve_Numerov(0., 2., step, nbox, &potential, wavefunction);

   return 0;
}