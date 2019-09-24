#include "Solver.h"

#include <utility>

Solver::Solver(Potential potential, int nbox) {
    this->potential      = std::move(potential);
    this->nbox           = nbox;
    this->boundary       = this->potential.getBase().getBoundary();
}
