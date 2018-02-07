#include "Schroedinger.h"

/*! Integrate with the trapezoidal rule method, from a to b position in a function array
*/
double trap_array(int a, int b, double stepx, double *func) {
    double trapez_sum = 0.;

    for (int j = a + 1; j < b; j++) {
        trapez_sum += func[j];
    }
    trapez_sum += (func[a] + func[b]) / 2.;
    trapez_sum = (trapez_sum) * stepx;
    return trapez_sum;
}

/*! Numerov Algorithm solves
f''(x) + v(x)f(x) = 0,
by considering
\left( 1+ \frac{h^2}{12} v(x+h) \right) f(x+h) = 2 \left( 1 - \frac{5h^2}{12} v(x) \right) f(x) - \left( 1 + \frac{h^2}{12} v(x-h) \right) f(x-h).
for the Shroedinger equation v(x) = V(x) - E, where V(x) is the potential and E the eigenenergy
*/
void fsol_Numerov(double Energy, int nbox, double (*potential)(double), double *wavefunction) {
    double c, x;
    c = (2. * mass / hbar / hbar) * (dx * dx / 12.);
    //Build Numerov f(x) solution from left.
    for (int i = 2; i <= nbox; i++) {
        x = (-nbox / 2 + i) * dx;

        wavefunction[i] = 2 * (1. - (5 * c) * (Energy - (*potential)(x - dx))) * wavefunction[i - 1]
                  - (1. + (c) * (Energy - (*potential)(x - 2 * dx))) * wavefunction[i - 2];
        wavefunction[i] /= (1. + (c) * (Energy - (*potential)(x)));
    }

    /* //right solution

    norm = wavefunction[nbox/2];
    wavefunction[nbox-1] = first_step;
    for(int i=nbox-2;i>=nbox/2;i--){
      x = (i-nbox/2)*dx;
      wavefunction[i] = -   ( 1. + (  c)*(- Energy + (*potential)(x+2*step)) ) *  wavefunction[i+2]
                + 2*( 1. - (5*c)*(- Energy + (*potential)(x+step))   ) * wavefunction[i+1] ;

      wavefunction[i]/= ( 1. + (  c)*(- Energy + (*potential)(x)) );
    }*/
}

/*! \brief a solver of differential equation using Numerov algorithm and selecting non-trivial solutions.
@param (*potential) is the pointer to the potential function, takes function of 1 variable as input
@param wavefunction, takes array of @param nbox size as input (for preconditioning)
  and gives the output the normalizedwf solution

solve_Numerov solves the pointed potential using the Numerov algorithm and
renormalizing the output wavefunction to 1. To do this it must try the solutions
for different energies. The natural solution to the second degree differential equation
is the exponential. But my boundary conditions impose 0 at both beginning and end
of the wavefunction, so you have to try until you find such solution by finding
 where the exponential solution changes sign.
*/
double solve_Numerov(double Emin, double Emax, double Estep,
                   int nbox, double (*potential)(double), double *wavefunction) {

    double c, x, first_step, norm, Energy, Solution_Energy;
    int n, sign;

    double *probab = new double[nbox];

    // scan energies to find when the Numerov solution is =0 at the right extreme of the box.
    for (n = 0; n < (Emax - Emin) / Estep; n++) {
        Energy = Emin + n * Estep;
        // wavefunction[1] = first_step;

        fsol_Numerov(Energy, nbox, *potential, wavefunction);
        // std::coutS << "# Energy = " << Energy << "  " << wavefunction[nbox] << std::endl;

        if (fabs(wavefunction[nbox]) < err) {
          std::cout << "#solution found" << wavefunction[nbox] << std::endl;
            Solution_Energy = Energy;
            break;
        }

        if (n == 0)
            sign = (wavefunction[nbox] > 0) ? 1 : -1;

        // when the sign changes, means that the solution for f[nbox]=0 is in in the middle, thus calls bisection rule.
        if (sign * wavefunction[nbox] < 0) {
          std::cout << "#bisection " << wavefunction[nbox] << std::endl;
          Solution_Energy = bisec_Numer(Energy - Estep, Energy + Estep, nbox, *potential, wavefunction);
            break;
        }
    }

    std::cout << "# iteration " << n << "  Energy = " << Solution_Energy << std::endl;

    for (int i = 0; i <= nbox; i++)
        probab[i] = wavefunction[i] * wavefunction[i];

    norm = trap_array(0., nbox, dx, probab);
    std::cout << "# norm=" << norm << std::endl;

    for (int i = 0; i <= nbox; i++)
        wavefunction[i] = wavefunction[i] / sqrt(norm);
    // for (int i = 0; i <= nbox; i++)
    //     std::cout << (-nbox / 2 + i) * dx << "  " << wavefunction[i] << " " << (*potential)((-nbox / 2 + i) * dx) << std::endl;
    return Solution_Energy;
}

/*! Applies a bisection algorith to the numerov method to find
the energy that gives the non-trivial (non-exponential) solution
with the correct boundary conditions (@param wavefunction[0] == @param wavefunction[@param nbox] == 0)
*/
double bisec_Numer(double Emin, double Emax, int nbox, double (*potential)(double), double *wavefunction) {
    double Emiddle, fx1, fb, fa;
    std::cout.precision(17);

    // The number of iterations that the bisection routine needs can be evaluated in advance
    int itmax = ceil(log2(Emax - Emin) - log2(err)) - 1;

    std::cout << "#itmax=" << itmax << std::endl;
    for (int i = 0; i < itmax; i++) {
        Emiddle = (Emax + Emin) / 2.;
        fsol_Numerov(Emiddle, nbox, *potential, wavefunction);
        fx1 = wavefunction[nbox];
        fsol_Numerov(Emax, nbox, *potential, wavefunction);
        fb = wavefunction[nbox];

        if (std::abs(fx1) < err) {
            std::cout << "#Numerov E=" << Emiddle << "f(nbox=" << nbox << ") = " << fx1 << " " << wavefunction[nbox] << std::endl;
            return Emiddle;
        }

        if (fb * fx1 < 0.) {
            Emin = Emiddle;
        } else {
            fsol_Numerov(Emin, nbox, *potential, wavefunction);
            fa = wavefunction[nbox];

            if (fa * fx1 < 0.)
                Emax = Emiddle;
        }
    }

    std::cerr<< "ERROR: Solution not found in bisec_Numer " << wavefunction[nbox] << " > " << err << std::endl;
//    exit(9);
    return Emiddle;
}
