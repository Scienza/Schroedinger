#include "Solver.h"

Solver::Solver(Potential potential, int nbox) {
    this->potential      = potential;
    this->nbox           = nbox;
    this->solutionEnergy = 0;
    this->probability    = std::vector<double>(nbox+1);
    this->wavefunction   = std::vector<double>(nbox+1);
    this->boundary = this->potential.getBase().getBoundary();
}
