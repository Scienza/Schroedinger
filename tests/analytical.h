#include "Numerov.h"

/*! Calculates the analytical wavefunction of a particle in a box
allowed energy levels :   $E_n = n^2 \pi^2 \hbar^2 / (2 m L)$
wavefcuntion: $A*sin(n \pi/L * x)$
Analytically exact
nlevel > 0,
*/
double box_wf(int nlevel, int nbox, std::vector<double> &wavefunction) {
    wavefunction = std::vector<double>(nbox + 1);

    double boxLength = (nbox)*dx;
    double E_n       = nlevel * nlevel * pi * pi * hbar * hbar / 2. / mass / boxLength / boxLength;
    double norm      = sqrt(2 / boxLength);

    for (int i = 0; i < wavefunction.size(); i++) {
        double x                   = i * dx;
        double &wavefunction_value = wavefunction.at(i);
        wavefunction_value         = norm * sin(nlevel * pi * x / boxLength);
        // remember to translate by half box length, eventually
        // std::cout << x - boxLength/2. << " " << wavefunction.at(i) << std::endl;
    }
    return E_n;
}

/*! Calculates the analytical wavefunction of a particle in a finite potential
allowed energy levels : $E_n = n^2 \pi^2 \hbar^2 / (2 m L)$
wavefcuntion: $A*sin(n \pi/L * x)$
This will not correspond exactly to a numerical solution in a box, since the
box is a finite overlay on top of the finite well, instead of an exact contiuum.
Check by expanding the box, and/or deepening the potential.
nlevel > 1
*/
double finite_well_wf(int nlevel, int nbox, double pot_width, double pot_height,
                      std::vector<double> &wavefunction) {
    // double boxLength = nbox * dx;
    wavefunction = std::vector<double>(nbox + 1);

    std::cout << "width: " << pot_width << " height: " << pot_height << '\n';
    double xi = pot_width / 2. * sqrt(2. * mass * pot_height / hbar / hbar);

    double k, G, H, A, B, E_n;
    double eta_old, eta;
    double tolerance = 1e-10;
    int counter      = 0;

    eta_old = 1. + pi_2 * (nlevel - 1);
    // std::cout << "#" << eta_old << std::endl;
    do {
        counter++;
        eta = eta_old;

        if (nlevel % 2 == 0) {  // looking for solution has n even, thus is odd parity
            eta_old = atan(sqrt(xi * xi / eta / eta - 1) + pi_2) + pi_2 * (nlevel - 1);
        } else {  // looking for has n odd, thus is even parity
            eta_old = atan(sqrt(xi * xi / eta / eta - 1)) - pi_2 * (nlevel - 1);
        }
        //    std::cout << "#" << eta << " - " << eta_old << '\n';
    } while (fabs((eta_old - eta) / eta) > tolerance && counter < 100);

    if (counter == 100) {
        std::cerr << "transcendent equation in finite_well_wf() not converging" << '\n';
        exit(-1);
    } else {
        E_n = 2. * hbar * hbar * eta * eta / pot_width / pot_width / mass;
        std::cout << "#" << nlevel << " solution for eta = " << eta << "  E_n =" << E_n
                  << '\n';
    }

    if (nlevel % 2 == 0) {  // looking for solution has n even, thus is antisymmetric
        k        = sqrt(2. * mass * (pot_height - E_n)) / hbar;
        double x = pot_width / 2.;
        A        = 1.;
        B        = 0.;
        H        = A * sin(sqrt(2. * mass * E_n) * x) * exp(k * x);
        G        = -H;
        // std::cout << A * sin (sqrt(2. * mass * E_n) * x) << " "
        // << H*exp( -k * x ) << std::endl;
    } else {  // looking for has n odd, thus is symmetric
        k        = sqrt(2. * mass * (pot_height - E_n)) / hbar;
        double x = -pot_width / 2.;

        A = 0.;
        B = 1.;
        H = B * cos(sqrt(2. * mass * E_n) * x) * exp(-k * x);
        G = H;
    }

    for (int i = 0; i < nbox; i++) {
        double x                   = (-nbox / 2 + i) * dx;
        double &wavefunction_value = wavefunction.at(i);

        if (x <= -pot_width / 2.) {
            k                  = sqrt(2. * mass * (pot_height - E_n)) / hbar;
            wavefunction_value = G * exp(k * x);
        } else if (x > -pot_width / 2. && x < pot_width / 2.) {
            k                  = sqrt(2. * mass * E_n) / hbar;
            wavefunction_value = A * sin(k * x) + B * cos(k * x);
        } else {
            k = sqrt(2. * mass * (pot_height - E_n)) / hbar;
            // std::cout << k << " " << H << " " << exp( -k * x ) << std::endl;
            wavefunction_value = H * exp(-k * x);
        }
    }

    // Final Normalization
    std::vector<double> probability = std::vector<double>(nbox + 1);
    for (int i = 0; i <= nbox; i++) {
        double &probab             = probability.at(i);
        double &wavefunction_value = wavefunction.at(i);
        probab                     = wavefunction_value * wavefunction_value;
    }
    double norm = Numerov::trapezoidalRule(0, nbox, dx, probability);
    for (int i = 0; i < wavefunction.size(); i++) {
        double &wavefunction_value = wavefunction.at(i);
        wavefunction_value /= sqrt(norm);
    }
    return E_n;
}

inline int factorial(int x, int result = 1) {
    if (x == 1 || x == 0)
        return result;
    else
        return factorial(x - 1, x * result);
}

double harmonic_wf(int nlevel, int nbox, double omega, std::vector<double> &wavefunction) {
    wavefunction = std::vector<double>(nbox + 1);
    double c     = mass * omega / hbar;
    double E_n   = hbar * omega * (nlevel + 0.5);

    for (int i = 0; i < nbox; i++) {
        double &wavefunction_value = wavefunction.at(i);
        double x                   = (-nbox / 2 + i) * dx;
        wavefunction_value         = sqrt(1 / pow(2, nlevel) / factorial(nlevel) * sqrt(c / pi)) *
                             exp(-c / 2. * x * x) * std::hermite(nlevel, sqrt(c) * x);
    }
    return E_n;
}
