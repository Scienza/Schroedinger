#include "Numerov.h"

Numerov::Numerov(Potential potential, int nbox) : Solver(potential, nbox) {    
    switch(this->boundary) {
        case Base::boundaryCondition::ZEROEDGE:
            this->wavefunction.at(0) = 0;
            this->wavefunction.at(1) = 0.1;
            this->wfAtBoundary = 0;
            break;
        default:
            throw std::invalid_argument("Wrong boundary condition initialization or condition not implemented!");
    }
}

/*! 
    Numerov Algorithm solves f''(x) + v(x)f(x) = 0,
    by considering
    \left( 1+ \frac{h^2}{12} v(x+h) \right) f(x+h) = 2 \left( 1 - \frac{5h^2}{12} v(x) \right) f(x) - \left( 1 + \frac{h^2}{12} v(x-h) \right) f(x-h).
    for the Shroedinger equation v(x) = V(x) - E, where V(x) is the potential and E the eigenenergy
*/
void Numerov::functionSolve(double energy) {
    double c, x;
    std::vector<double> pot = this->potential.getValues();

    c = (2.0 * mass / hbar / hbar) * (dx * dx / 12.0);
    try{
        //Build Numerov f(x) solution from left. 
        for (int i = 2; i <= this->nbox; i++) {
            x = (-this->nbox / 2 + i) * dx;
            double &value = this->wavefunction.at(i);
            double &pot_1 = pot.at(i-1);
            double &pot_2 = pot.at(i-2);
            double &pot_a = pot.at(i);

            double &wave_1 = this->wavefunction.at(i-1);
            double &wave_2 = this->wavefunction.at(i-2);

            value = 2 * (1.0 - (5 * c) * (energy - pot_1 )) * wave_1 - (1.0 + (c) * (energy - pot_2)) * wave_2;
            value /= (1.0 + (c) * (energy - pot_a));  
        }
    }catch (const std::out_of_range & ex)
    {
        std::cout << "out_of_range Exception Caught :: " << ex.what() << std::endl;
    }
}

/*! 
    \brief a solver of differential equation using Numerov algorithm and selecting non-trivial solutions.
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

State Numerov::solve(double e_min, double e_max, double e_step) {
    double c, x, first_step, norm, energy = 0.0;
    int n, sign;

    // scan energies to find when the Numerov solution is = 0 at the right extreme of the box.
    for (n = 0; n < (e_max - e_min) / e_step; n++) {
        energy = e_min + n * e_step;
        this->functionSolve(energy);
        double &last_wavefunction_value = this->wavefunction.at(this->nbox);

        if ( fabs(last_wavefunction_value - this->wfAtBoundary) < err ) {
            std::cout << "Solution found" << last_wavefunction_value << std::endl;
            this->solutionEnergy = energy;
            break;
        }

        if (n == 0)
            sign = (last_wavefunction_value - this->wfAtBoundary > 0) ? 1 : -1;

        // when the sign changes, means that the solution for f[nbox]=0 is in in the middle, thus calls bisection rule.
        if (sign * (last_wavefunction_value - this->wfAtBoundary) < 0) {
            std::cout << "Bisection " << last_wavefunction_value << std::endl;
            this->solutionEnergy = this->bisection(energy - e_step, energy + e_step);
            break;
        }
    }

    // Evaluation of the probability
    for (int i = 0; i <= nbox; i++) {
        double &value      = this->wavefunction[i];
        double &prob_value = this->probability[i];
        prob_value = value*value;
    }

    // Evaluation of the norm
    norm = trapezoidalRule(0.0, this->nbox, dx, this->probability);

    // Normalization of the wavefunction
    for (int i = 0; i <= nbox; i++) {
        double &value = this->wavefunction[i];
        value /= sqrt(norm);
    }

    // Normalization of the potential
    for (int i = 0; i <= nbox; i++) {
        double &value = this->probability[i];
        value /= norm;
    }

    return State(this->wavefunction, this->probability, this->solutionEnergy, this->potential.getBase());
}

/*! Applies a bisection algorith to the numerov method to find
the energy that gives the non-trivial (non-exponential) solution
with the correct boundary conditions (@param wavefunction[0] == @param wavefunction[@param nbox] == 0)
*/
double Numerov::bisection(double e_min, double e_max) {
    double energy_middle, fx1, fb, fa;
    double solutionAt;
    std::cout.precision(17);

    // The number of iterations that the bisection routine needs can be evaluated in advance
    int itmax = ceil(log2(e_max - e_min) - log2(err)) - 1;

    for (int i = 0; i < itmax; i++) {
        energy_middle = (e_max + e_min) / 2.0;

        this->functionSolve(energy_middle);
        fx1 = this->wavefunction.at(this->nbox) - this->wfAtBoundary;
        
        this->functionSolve(e_max);
        fb = this->wavefunction.at(this->nbox) - this->wfAtBoundary;

        if (std::abs(fx1) < err) {
            return energy_middle;
        }

        if (fb * fx1 < 0.) {
            e_min = energy_middle;
        } else {
            this->functionSolve(e_min);
            fa = this->wavefunction.at(this->nbox) - this->wfAtBoundary;

            if (fa * fx1 < 0.)
                e_max = energy_middle;
        }
    }

    std::cerr << "WARNING: Solution not found at the set precision using the bisection method, " << this->wavefunction.at(this->nbox) << " > " << err << std::endl;
    return energy_middle;
}
