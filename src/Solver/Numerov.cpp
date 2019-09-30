#include "Numerov.h"
#include "LogManager.h"

#include <utility>

Numerov::Numerov(Potential potential, int nbox) : Solver(std::move(potential)) {}

void Numerov::initialize() {
    double nbox = this->potential.getBase().getContinuous().at(0).getNbox();
    this->solutionEnergy = 0;
    this->probability    = std::vector<double>(nbox + 1);
    this->wavefunction   = std::vector<double>(nbox + 1);
    switch (this->boundary) {
        case Base::boundaryCondition::ZEROEDGE:
            this->wavefunction.at(0) = 0;
            this->wavefunction.at(1) = 0.1;
            this->wfAtBoundary       = 0;
            break;
        default:
            throw std::invalid_argument(
                "Wrong boundary condition initialization or condition not implemented!");
    }
}
/*!
    Numerov Algorithm solves f''(x) + v(x)f(x) = 0,
    by considering
    \left( 1+ \frac{h^2}{12} v(x+h) \right) f(x+h) = 2 \left( 1 - \frac{5h^2}{12} v(x) \right) f(x)
   - \left( 1 + \frac{h^2}{12} v(x-h) \right) f(x-h). for the Shroedinger equation v(x) = V(x) - E,
   where V(x) is the potential and E the eigenenergy
*/
void Numerov::functionSolve(double energy, int potential_index) { 
    std::vector<double> pot = this->potential.getValues().at(potential_index);
    double mesh = this->potential.getBase().getContinuous().at(potential_index).getMesh();
    double nbox = this->potential.getBase().getContinuous().at(potential_index).getNbox();
    double c = (2.0 * mass / hbar / hbar) * (mesh * mesh / 12.0);
    try {
        // Build Numerov f(x) solution from left.
        for (int i = 2; i <= nbox; i++) {
            double &value = this->wavefunction.at(i);
            double &pot_1 = pot.at(i - 1);
            double &pot_2 = pot.at(i - 2);
            double &pot_a = pot.at(i);

            double &wave_1 = this->wavefunction.at(i - 1);
            double &wave_2 = this->wavefunction.at(i - 2);

            value = 2 * (1.0 - (5 * c) * (energy - pot_1)) * wave_1 -
                    (1.0 + (c) * (energy - pot_2)) * wave_2;
            value /= (1.0 + (c) * (energy - pot_a));
        }
    } catch (const std::out_of_range &ex) {
        S_ERROR("Out of range exception caught, {}", ex.what());
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
    int sign = 1;
    std::vector<std::vector<double>> temp;
    std::vector<State> states;

    for (int potential_index = 0; potential_index < this->potential.getValues().size(); potential_index++) {
        initialize();
        temp.clear();
        double mesh = this->potential.getBase().getContinuous().at(potential_index).getMesh();
        double nbox = this->potential.getBase().getContinuous().at(potential_index).getNbox();

        // scan energies to find when the Numerov solution is = 0 at the right extreme of the box.
        for (int n = 0; n < (e_max - e_min) / e_step; n++) {
            double energy = e_min + n * e_step;
            this->functionSolve(energy, potential_index);
            double &last_wavefunction_value = this->wavefunction.at(nbox);

            if (fabs(last_wavefunction_value - this->wfAtBoundary) < err_thres) {
                S_INFO("Solution found {}", last_wavefunction_value);
                this->solutionEnergy = energy;
                break;
            }

            if (n == 0) {
                sign = (last_wavefunction_value - this->wfAtBoundary > 0) ? 1 : -1;
            }

            // when the sign changes, means that the solution for f[nbox]=0 is in in the middle, thus
            // calls bisection rule.
            if (sign * (last_wavefunction_value - this->wfAtBoundary) < 0) {
                S_INFO("Bisection {}", last_wavefunction_value);
                this->solutionEnergy = this->bisection(energy - e_step, energy + e_step, potential_index);
                break;
            }
        }

        // Evaluation of the probability
        for (int i = 0; i <= nbox; i++) {
            double &value      = this->wavefunction[i];
            double &prob_value = this->probability[i];
            prob_value         = value * value;
        }

        // Evaluation of the norm
        double norm = trapezoidalRule(0, nbox, mesh, this->probability);

		// Normalize wavefunction and probabiliy
        auto norm_fun = [norm](double val) { return val / sqrt(norm); };
        std::transform(wavefunction.begin(), wavefunction.end(), wavefunction.begin(), norm_fun);
        std::transform(probability.begin(), probability.end(), probability.begin(), norm_fun);

        temp.push_back(this->potential.getValues().at(potential_index));
        const std::vector<double>& coords = this->potential.getBase().getContinuous().at(potential_index).getCoords(); 

        states.emplace_back(State{this->wavefunction, this->probability, temp, this->solutionEnergy, Base(coords)});

    }

    return makeStateFromVector(states);
}

/*! Applies a bisection algorith to the numerov method to find
the energy that gives the non-trivial (non-exponential) solution
with the correct boundary conditions (@param wavefunction[0] == @param wavefunction[@param nbox] ==
0)
*/
double Numerov::bisection(double e_min, double e_max, int potential_index) {
    double nbox = this->potential.getBase().getContinuous().at(potential_index).getNbox();

    double energy_middle = 0, fx1, fb, fa;
    std::cout.precision(17);

    // The number of iterations that the bisection routine needs can be evaluated in advance
    int itmax = static_cast<int>(ceil(log2(e_max - e_min) - log2(err_thres)) - 1);

    for (int i = 0; i < itmax; i++) {
        energy_middle = (e_max + e_min) / 2.0;

        this->functionSolve(energy_middle, potential_index);
        fx1 = this->wavefunction.at(nbox) - this->wfAtBoundary;

        this->functionSolve(e_max, potential_index);
        fb = this->wavefunction.at(nbox) - this->wfAtBoundary;

        if (std::abs(fx1) < err_thres) {
            return energy_middle;
        }

        if (fb * fx1 < 0.) {
            e_min = energy_middle;
        } else {
            this->functionSolve(e_min, potential_index);
            fa = this->wavefunction.at(nbox) - this->wfAtBoundary;

            if (fa * fx1 < 0.) {
                e_max = energy_middle;
            }
        }
    }

    S_WARN("Failed to find solution using bisection method, {} > {}", wavefunction.at(nbox),
         err_thres);
    return energy_middle;
}
