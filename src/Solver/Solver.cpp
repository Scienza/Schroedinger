#include "Solver.h"

#include <utility>

Solver::Solver(Potential potential, int nbox) {
    this->potential      = std::move(potential);
    this->nbox           = nbox;
    this->solutionEnergy = 0;
    this->probability    = std::vector<double>(nbox+1);
    this->wavefunction   = std::vector<double>(nbox+1);
    this->boundary = this->potential.getBase().getBoundary();
}
