#include "State.h"

#include <functional>
#include <numeric>
#include <utility>
#include <vector>
#include <spdlog/fmt/bundled/format.h>

State makeStateFromVector(std::vector<State> states) {
    std::vector<Base> bases;
    std::vector<Potential> potentials;
    std::vector<double> energies;
    std::vector<std::vector<double>> wavefunctions;
    std::vector<std::vector<double>> probabilities;

    for (State &local_state : states) {
        bases.push_back(std::move(local_state.getBase()));
        wavefunctions.push_back(std::move(local_state.getWavefunction()));
        potentials.push_back(std::move(local_state.getPotential()));
        probabilities.push_back(std::move(local_state.getProbability()));
        energies.push_back(std::move(local_state.getEnergy()));
    }

    Base b = std::accumulate(std::next(bases.begin()), bases.end(), bases.at(0));
    Potential p =
        std::accumulate(std::next(potentials.begin()), potentials.end(), potentials.at(0));
    double en = std::accumulate(energies.begin(), energies.end(), 0.0);

    // Save W(a, ..., z) = W(a) * ... * W(z)
    size_t n = wavefunctions.size();
    std::vector<size_t> indices(n, 0);

    std::vector<double> wavefunction;
    std::vector<double> probability;

    while (1) {

        // print current combination
        double sum = 1.0;
        for (int i = 0; i < n; i++) {
            sum *= wavefunctions[i][indices[i]];
        }

        wavefunction.push_back(sum);

        int next = n - 1;
        while (next >= 0 && (indices[next] + 1 >= wavefunctions[next].size())) next--;

        if (next < 0) break;

        indices[next]++;
        for (int i = next + 1; i < n; i++) indices[i] = 0;
    }

    // Maybe we should check probability here
    probability = probabilities.at(0);

    return {wavefunction, probability, p, en, b};
}

State::State(std::vector<double> i_wavefunction, std::vector<double> i_probability,
             std::vector<std::vector<double>> i_potential, double i_energy, Base i_base)
    : potential(std::move(Potential(base, i_potential))),
      probability(std::move(i_probability)),
      wavefunction(std::move(i_wavefunction)),
      base(std::move(i_base)),
      energy(i_energy) {}

State::State(std::vector<double> i_wavefunction, std::vector<double> i_probability,
             Potential i_potential, double i_energy, Base i_base)
    : potential(i_potential),
      probability(std::move(i_probability)),
      wavefunction(std::move(i_wavefunction)),
      base(std::move(i_base)),
      energy(i_energy) {}

void State::printToFile() {
    std::ofstream basefile("base.dat");
    std::ofstream wavefunctionfile("wavefunction.dat");
    std::ofstream probabilityfile("probability.dat");
    std::ofstream potentialfile("potential.dat");

    if (wavefunctionfile.is_open() && probabilityfile.is_open() && basefile.is_open() && potentialfile.is_open()) {
        fmt::memory_buffer writer;

        std::for_each(wavefunction.begin(), wavefunction.end(),
                      [&writer](const auto value) { format_to(writer, "{}\n", value); });
        wavefunctionfile << to_string(writer);

		writer.clear();

        std::for_each(probability.begin(), probability.end(),
                      [&writer](const auto value) { format_to(writer, "{}\n", value); });
        probabilityfile << to_string(writer);

        basefile << base.toString();
        potentialfile << potential.toString();

        basefile.close();
        wavefunctionfile.close();
        probabilityfile.close();
        potentialfile.close();
    }

}

std::ostream &operator<<(std::ostream &stream, const State &st) {
    std::vector<double> base_coords = st.getBase().getCoords();

    stream << std::setw(20) << std::right << "Basis coordinates";
    stream << std::setw(20) << std::right << "Wavefunction";
    stream << std::setw(20) << std::right << "Probability" << '\n';

    for (int i = 0; i < base_coords.size(); i++) {

        // Printing coord
        stream << st.getBase().toString();

        // Printing wavefunction
        stream << std::setprecision(3) << std::setw(20) << std::right << st.wavefunction[i];

        // Printing probability
        stream << std::setprecision(3) << std::setw(20) << std::right << st.probability[i] << '\n';
    }

    return stream;
}
