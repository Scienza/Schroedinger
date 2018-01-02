#include <iostream>
#include <cmath>

#define dx 0.01
#define err 1E-12

using namespace std;

double trap_array(int a, int b, double stepx, double *func);
double potential(double x);
void fsol_Numerov(double, int, double (*pot)(double), double *);
void solve_Numerov(double, double, double, int, double (*pot)(double), double *);
double bisec_Numer(double, double, int, double (*pot)(double), double *);

int main() {
    int nbox = 1000;
    double step = 0.01, norm;
    double *fsol = new double[nbox];
    fsol[0] = 0.;
    fsol[1] = 0.2;
    solve_Numerov(0., 2., step, nbox, &potential, fsol);
    return 0;
}

// Integrate with the trapezoidal rule method, from a to b position in a function array
double trap_array(int a, int b, double stepx, double *func) {
    double trapez_sum = 0.;

    for (int j = a + 1; j < b; j++) {
        trapez_sum += func[j];
    }
    trapez_sum += (func[a] + func[b]) / 2.;
    trapez_sum = (trapez_sum) * stepx;
    return trapez_sum;
}

//  this function defines the potential in function of position
double potential(double x) {
    double value = x * x;
    return value;
} // end of function to evaluate

//Numerov Algorithm solves
// f''(x) + v(x)f(x) = 0,
// by considering
//\left( 1+ \frac{h^2}{12} v(x+h) \right) f(x+h) = 2 \left( 1 - \frac{5h^2}{12} v(x) \right) f(x) - \left( 1 + \frac{h^2}{12} v(x-h) \right) f(x-h).
//for the Shroedinger equation v(x) = V(x) - E, where V(x) is the potential and E the eigenenergy
void fsol_Numerov(double En, int nbox, double (*pot)(double), double *fsol) {
    double c, x;
    c = dx * dx / 12.;
    //Build Numerov f(x) solution from left.
    for (int i = 2; i <= nbox; i++) {
        x = (-nbox / 2 + i) * dx;

        fsol[i] = 2 * (1. - (5 * c) * (En - (*pot)(x - dx))) * fsol[i - 1]
                  - (1. + (c) * (En - (*pot)(x - 2 * dx))) * fsol[i - 2];
        fsol[i] /= (1. + (c) * (En - (*pot)(x)));
    }

    /* //right solution

    norm = fsol[nbox/2];
    fsol[nbox-1] = first_step;
    for(int i=nbox-2;i>=nbox/2;i--){
      x = (i-nbox/2)*dx;
      fsol[i] = -   ( 1. + (  c)*(- En + (*pot)(x+2*step)) ) *  fsol[i+2]
                + 2*( 1. - (5*c)*(- En + (*pot)(x+step))   ) * fsol[i+1] ;

      fsol[i]/= ( 1. + (  c)*(- En + (*pot)(x)) );
    }*/

    return;
}

// solve_Numerov solves the pointed potential using the Numerov algorithm and
// renormalizing the output wavefunction to 1
void solve_Numerov(double Emin, double Emax, double dE,
                   int nbox, double (*pot)(double), double *fsol) {

    double c, x, first_step, norm, En, Ex;
    int n, sign;

    double *probab = new double[nbox];

    // scan energies to find when the Numerov solution is =0 at the right extreme of the box.
    for (n = 0; n < (Emax - Emin) / dE; n++) {
        En = Emin + n * dE;
        // fsol[1] = first_step;

        fsol_Numerov(En, nbox, *pot, fsol);
        cout << "# En = " << En << "  " << fsol[nbox] << endl;

        if (abs(fsol[nbox]) < err) {
            Ex = En;
            break;
        }

        if (n == 0)
            if (fsol[nbox] > 0) { sign = 1; } else { sign = -1; }

        if (sign * fsol[nbox] <
            0) { // when the sign changes, means that the solution for f[nbox] =0 is in in the middle, thus calls bisection rule.
            Ex = bisec_Numer(En - dE, En + dE, nbox, *pot, fsol);
            break;
        }
    }

    cout << "# iteration " << n << "  En = " << Ex << endl;

    for (int i = 0; i <= nbox; i++)
        probab[i] = fsol[i] * fsol[i];

    norm = trap_array(0., nbox, dx, probab);
    cout << "# norm=" << norm << endl;

    for (int i = 0; i <= nbox; i++)
        fsol[i] = fsol[i] / sqrt(norm);
    for (int i = 0; i <= nbox; i++)
        cout << (-nbox / 2 + i) * dx << "  " << fsol[i] << " " << (*pot)((-nbox / 2 + i) * dx) << endl;
    return;
}

//Applies bisection routine to Numerov function. (to be improved)
double bisec_Numer(double a, double b, int nbox, double (*pot)(double), double *fsol) {
    double x1, fx1, fb, fa;
    cout.precision(17);
    x1 = (b + a) / 2.;

    if (abs(x1 - a) > err) {
        fsol_Numerov(x1, nbox, *pot, fsol);
        fx1 = fsol[nbox];
        fsol_Numerov(b, nbox, *pot, fsol);
        fb = fsol[nbox];

        if (abs(fx1) < err) {
            return x1;
        }

        if (fb * fx1 < 0.) {
            a = x1;
        } else {
            fsol_Numerov(a, nbox, *pot, fsol);
            fa = fsol[nbox];

            if (fa * fx1 < 0.)
                b = x1;
        }
        bisec_Numer(a, b, nbox, *pot, fsol);
    }
    return x1;
}
