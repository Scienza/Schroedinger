#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#ifndef SCHROEDINGER
#define SCHROEDINGER

#define dx 0.01
#define err 1E-12

#define pi 3.14159265359
#define hbar 1
#define mass 1

#include <cmath>
#include <iostream>

double trap_array(int, int, double, double *);
void fsol_Numerov(double, int, double (*pot)(double), double *);
void solve_Numerov(double, double, double, int, double (*pot)(double), double *);
double bisec_Numer(double, double, int, double (*pot)(double), double *);
#endif
