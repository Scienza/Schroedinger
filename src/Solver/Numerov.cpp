#include "Numerov.h"
#include "LogManager.h"

#include <utility>

Numerov::Numerov(Potential potential, int nbox) : Solver(std::move(potential), nbox) {

}

/*!
    Numerov Algorithm solves f''(x) + v(x)f(x) = 0,
    by considering
    \left( 1+ \frac{h^2}{12} v(x+h) \right) f(x+h) = 2 \left( 1 - \frac{5h^2}{12} v(x) \right) f(x)
   - \left( 1 + \frac{h^2}{12} v(x-h) \right) f(x-h). for the Shroedinger equation v(x) = V(x) - E,
   where V(x) is the potential and E the eigenenergy
*/
void Numerov::functionSolve(double energy, std::vector<double> potential_values, std::vector<double> &wavefunction) {
    std::vector<double> pot = this->potential.getValues();

    double c = (2.0 * mass / hbar / hbar) * (dx * dx / 12.0);
    try {
        // Build Numerov f(x) solution from left.
        for (int i = 2; i <= this->nbox; i++) {
            double &value = wavefunction.at(i);
            double &pot_1 = pot.at(i - 1);
            double &pot_2 = pot.at(i - 2);
            double &pot_a = pot.at(i);

            double &wave_1 = wavefunction.at(i - 1);
            double &wave_2 = wavefunction.at(i - 2);

            value = 2 * (1.0 - (5 * c) * (energy - pot_1)) * wave_1 -
                    (1.0 + (c) * (energy - pot_2)) * wave_2;
            value /= (1.0 + (c) * (energy - pot_a));
        }
    } catch (const std::out_of_range &ex) {
        ERROR("Out of range exception caught, {}", ex.what());
    }
}

/*!
    \brief a solver of differential equation using Numerov algorithm and selecting non-trivial
   solutions.
    @param (*potential) is the pointer to the potential function, takes function of 1 variable as
   input
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
    double norm, energy = 0.0;
    int n, sign;
    std::vector<Potential> potentials;
    std::vector<State> states;

    if (this->potential.isSeparated()) {
            potentials = this->potential.getSeparatedPotentials();
    } else {
        potentials.push_back(this->potential); 
    }

    for (Potential local_potential : potentials) {

        double solutionEnergy = 0.0;
        double wfAtBoundary;
        std::vector<double> wavefunction = std::vector<double>(nbox + 1);
        std::vector<double> probability = std::vector<double>(nbox + 1);
        
        // Initialization of wavefunction
        switch (this->boundary) {
            case Base::boundaryCondition::ZEROEDGE:
                wavefunction.at(0) = 0;
                wavefunction.at(1) = 0.1;
                wfAtBoundary       = 0;
                break;
            default:
                throw std::invalid_argument(
                    "Wrong boundary condition initialization or condition not implemented!");
        }

        // scan energies to find when the Numerov solution is = 0 at the right extreme of the box.
        for (n = 0; n < (e_max - e_min) / e_step; n++) {
            energy = e_min + n * e_step;
            this->functionSolve(energy, local_potential.getValues(), wavefunction);
            double &last_wavefunction_value = wavefunction.at(this->nbox);

            if (fabs(last_wavefunction_value - wfAtBoundary) < err_thres) {
                INFO("Solution found {}", last_wavefunction_value);
                solutionEnergy = energy;
                break;
            }

            if (n == 0) {
                sign = (last_wavefunction_value - wfAtBoundary > 0) ? 1 : -1;
            }

            // when the sign changes, means that the solution for f[nbox]=0 is in in the middle, thus
            // calls bisection rule.
            if (sign * (last_wavefunction_value - wfAtBoundary) < 0) {
                INFO("Bisection {}", last_wavefunction_value);
                solutionEnergy = this->bisection(energy - e_step, energy + e_step, local_potential.getValues(), wavefunction, wfAtBoundary);
                break;
            }
        }

        // Evaluation of the probability
        for (int i = 0; i <= nbox; i++) {
            double &value      = wavefunction[i];
            double &prob_value = probability[i];
            prob_value         = value * value;
        }

        // Evaluation of the norm
        norm = trapezoidalRule(0, this->nbox, dx, probability);

        // Normalization of the wavefunction
        for (int i = 0; i <= nbox; i++) {
            double &value = wavefunction[i];
            value /= sqrt(norm);
        }

        // Normalization of the potential
        for (int i = 0; i <= nbox; i++) {
            double &value = probability[i];
            value /= norm;
        }

        states.push_back(State(wavefunction, probability, solutionEnergy,
                    local_potential.getBase()));
    }

    // Get the resulting state

    return states.at(0);
}

/*! Applies a bisection algorith to the numerov method to find
the energy that gives the non-trivial (non-exponential) solution
with the correct boundary conditions (@param wavefunction[0] == @param wavefunction[@param nbox] ==
0)
*/
double Numerov::bisection(double e_min, double e_max, std::vector<double> potential_values, std::vector<double> &wavefunction,  double wfAtBoundary) {
    double energy_middle = 0, fx1, fb, fa;
    std::cout.precision(17);

    // The number of iterations that the bisection routine needs can be evaluated in advance
    int itmax = static_cast<int>(ceil(log2(e_max - e_min) - log2(err_thres)) - 1);

    for (int i = 0; i < itmax; i++) {
        energy_middle = (e_max + e_min) / 2.0;

        this->functionSolve(energy_middle, potential_values, wavefunction);
        fx1 = wavefunction.at(this->nbox) - wfAtBoundary;

        this->functionSolve(e_max, potential_values, wavefunction);
        fb = wavefunction.at(this->nbox) - wfAtBoundary;

        if (std::abs(fx1) < err_thres) {
            return energy_middle;
        }

        if (fb * fx1 < 0.) {
            e_min = energy_middle;
        } else {
            this->functionSolve(e_min, potential_values, wavefunction);
            fa = wavefunction.at(this->nbox) - wfAtBoundary;

            if (fa * fx1 < 0.) {
                e_max = energy_middle;
            }
        }
    }

    WARN("Failed to find solution using bisection method, {} > {}", wavefunction.at(nbox),
         err_thres);
    return energy_middle;
}
