/*
 * Schroedinger - Scienza (c) 2019
 * Released under the GNU LGPL2.1
 * See the included LICENSE for details
 */
#include "Solver.h"

#include <utility>

Solver::Solver(Potential i_potential) : potential(std::move(i_potential)), solutionEnergy(0) {
    double first_nbox  = potential.getBase().getContinuous().at(0).getNbox();
    this->probability  = std::vector<double>(first_nbox + 1);
    this->wavefunction = std::vector<double>(first_nbox + 1);
    this->boundary     = potential.getBase().getBoundary();
}
