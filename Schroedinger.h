#ifndef SCHROEDINGER
#define SCHROEDINGER

#include <cmath>
#include <iostream>

#define dx 0.01
#define err 1E-12

double trap_array(int, int, double, double *);
void fsol_Numerov(double, int, double (*pot)(double), double *);
void solve_Numerov(double, double, double, int, double (*pot)(double), double *);
double bisec_Numer(double, double, int, double (*pot)(double), double *);
#endif
