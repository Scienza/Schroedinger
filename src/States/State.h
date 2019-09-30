#ifndef STATE_H
#define STATE_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include <spdlog/fmt/ostr.h>
#include "Base.h"
#include "Potential.h"

class State {
  public:
    State(std::vector<double> wavefunction, std::vector<double> probability,
          std::vector<std::vector<double>> potential, double energy, Base base, int nbox);
    State(std::vector<double> i_wavefunction, std::vector<double> i_probability,
          Potential i_potential, double i_energy, Base i_base, int i_nbox);

    const std::vector<double>& getWavefunction() const noexcept { return this->wavefunction; }
    const std::vector<double>& getProbability() const noexcept { return this->probability; }
    const Potential& getPotential() const noexcept { return this->potential; }

    double getEnergy() const noexcept { return energy; }
    const Base& getBase() const noexcept { return base; };

    void printToFile();

    friend std::ostream& operator<<(std::ostream& stream, const State& state);

  private:
    int nbox{};
    double energy{};

    Base base;
    Potential potential;
    std::vector<double> wavefunction;
    std::vector<double> probability;
};

State makeStateFromVector(std::vector<State> states);

#endif
