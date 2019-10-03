#include "Numerov.h"
#include "LogManager.h"

#include <utility>

Numerov::Numerov(Potential potential, int nbox) : Solver(std::move(potential)) {}

void Numerov::initialize() {
    double nbox          = this->potential.getBase().getContinuous().at(0).getNbox();
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
    double c    = (2.0 * mass / hbar / hbar) * (mesh * mesh / 12.0);
    try {
        // Build Numerov f(x) solution from left.
        for (int i = 2; i <= nbox; i++) {
            this->wavefunction.at(i) =
                (2 * (1.0 - (5 * c) * (energy - pot.at(i - 1))) * this->wavefunction.at(i - 1) -
                 (1.0 + (c) * (energy - pot.at(i - 2))) * this->wavefunction.at(i - 2)) /
                (1.0 + (c) * (energy - pot.at(i)));
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

    for (int potential_index = 0; potential_index < this->potential.getValues().size();
         potential_index++) {
        initialize();
        temp.clear();
        double mesh = this->potential.getBase().getContinuous().at(potential_index).getMesh();
        double nbox = this->potential.getBase().getContinuous().at(potential_index).getNbox();

        // scan energies to find when the Numerov solution is = 0 at the right extreme of the box.
        for (int n = 0; n < (e_max - e_min) / e_step; n++) {
            double energy = e_min + n * e_step;
            this->functionSolve(energy, potential_index);

            // Update the sign at the first iteration
            if (n == 0) {
                sign = (this->wavefunction.at(nbox) - this->wfAtBoundary > 0) ? 1 : -1;
            }

            if (fabs(this->wavefunction.at(nbox) - this->wfAtBoundary) < err_thres) {
                S_INFO("Solution found {}", this->wavefunction.at(nbox));
                this->solutionEnergy = energy;
                break;
            }

            // when the sign changes, means that the solution for f[nbox]=0 is in in the middle,
            // thus calls bisection rule.
            if (sign * (this->wavefunction.at(nbox) - this->wfAtBoundary) < 0) {
                S_INFO("Bisection {}", this->wavefunction.at(nbox));
                this->solutionEnergy =
                    this->bisection(energy - e_step, energy + e_step, potential_index);
                break;
            }
        }

        normalize(potential_index);

        temp.push_back(this->potential.getValues().at(potential_index));
        states.emplace_back(
            State{this->wavefunction, this->probability, temp, this->solutionEnergy,
                  Base(this->potential.getBase().getContinuous().at(potential_index).getCoords())});
    }

    return makeStateFromVector(states);
}

void Numerov::normalize(int potential_index) {
    double mesh = this->potential.getBase().getContinuous().at(potential_index).getMesh();
    double nbox = this->potential.getBase().getContinuous().at(potential_index).getNbox();

    // Evaluation of the probability
    auto prob_fun = [](double val) { return val * val; };
    std::transform(this->wavefunction.begin(), this->wavefunction.end(), this->probability.begin(),
                   prob_fun);

    // Evaluation of the norm
    double norm = trapezoidalRule(0, nbox, mesh, this->probability);

    // Normalize wavefunction and probabiliy
    auto norm_fun = [norm](double val) { return val / sqrt(norm); };
    std::transform(wavefunction.begin(), wavefunction.end(), wavefunction.begin(), norm_fun);
    std::transform(probability.begin(), probability.end(), probability.begin(), norm_fun);
}

/*! Applies a bisection algorith to the numerov method to find
the energy that gives the non-trivial (non-exponential) solution
with the correct boundary conditions (@param wavefunction[0] == @param wavefunction[@param nbox] ==
0)
*/
double Numerov::bisection(double e_min, double e_max, int potential_index) {
    double nbox = this->potential.getBase().getContinuous().at(potential_index).getNbox();

    double energy_middle                  = 0, fx1;
    std::vector<double> temp_wavefunction = this->wavefunction;
    this->functionSolve(e_max, potential_index);
    double fb = this->wavefunction.at(nbox) - this->wfAtBoundary;
    this->functionSolve(e_min, potential_index);
    double fa = this->wavefunction.at(nbox) - this->wfAtBoundary;
    this->functionSolve(energy_middle, potential_index);
    fx1 = this->wavefunction.at(nbox) - this->wfAtBoundary;
    std::cout.precision(17);
    this->wavefunction = temp_wavefunction;

    int wavefunction_print_count = 0;
    bool should_dump             = LogManager::getInstance().WavefunctionDumpEnabled();

    if (fa * fb > 0) {
        S_WARN("[Bisection method] f(a) * f(b) > 0! ( f(a):{}, f(b):{})", fa, fb);
    }

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

        if (fb * fx1 < 0.0) {
            e_min = energy_middle;
        } else {
            this->functionSolve(e_min, potential_index);
            fa = this->wavefunction.at(nbox) - this->wfAtBoundary;

            if (fa * fx1 < 0.0) {
                e_max = energy_middle;
            }
        }

        normalize(potential_index);
        S_WF(wavefunction);

    }

    S_WARN("Failed to find solution using bisection method, {} > {}", wavefunction.at(nbox),
           err_thres);
    return energy_middle;
}
