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

class State {
  public:
    State() {}
    State(std::vector<double> wavefunction, std::vector<double> probability, double energy,
          Base base);

    const std::vector<double>& getWavefunction();
    const std::vector<double>& getProbability();
    const double& getEnergy();
    Base getBase() const { return base; };

    void printToFile();

    friend std::ostream& operator<<(std::ostream& stream, const State& state);
    // friend std::ostream& operator^ (const State& state_1, const State& state_2);

  private:
    Base base;
    std::vector<double> wavefunction;
    std::vector<double> probability;
    double energy;
};

#endif
