#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#ifndef SCHROEDINGER_H
#define SCHROEDINGER_H

#define dx 0.01
#define err 1E-10

#define pi 3.14159265359
#define hbar 1
#define mass 1

#include <cmath>
#include <iostream>
#include <vector>
#include <string>

#include "../Potential/Potential.h"


double trap_array(int, int, double, double *);
void fsol_Numerov(double, int, Potential, double *);
double solve_Numerov(double, double, double, int, Potential, double *);
double bisec_Numer(double, double, int, Potential, double *);

#endif
