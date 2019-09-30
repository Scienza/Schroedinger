#include "Solver.h"

#include <utility>

Solver::Solver(Potential i_potential, int i_nbox) :
	potential(std::move(i_potential)), nbox(i_nbox), solutionEnergy(0) {
    this->probability    = std::vector<double>(nbox + 1);
    this->wavefunction   = std::vector<double>(nbox + 1);
    this->boundary       = potential.getBase().getBoundary();
}
