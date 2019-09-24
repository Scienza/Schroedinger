#include "State.h"

#include <utility>

State::State(std::vector<double> wavefunction, Potential potential, double energy, Base base, int nbox) {

        double norm = 0.0;
        this->potential = potential;
        this->nbox = nbox;

        this->probability = std::vector<double>(nbox + 1);

        // Evaluation of the probability
        for (int i = 0; i <= nbox; i++) {
            double &value      = wavefunction[i];
            double &prob_value = probability[i];
            prob_value         = value * value;
        }

        // Evaluation of the norm
        norm = trapezoidalRule(0, nbox, dx, probability);

        // Normalization of the wavefunction
        for (int i = 0; i <= nbox; i++) {
            double &value = wavefunction[i];
            value /= sqrt(norm);
        }

        // Normalization of the potential
        for (int i = 0; i <= nbox; i++) {
            double &value = probability[i];
            value /= norm;
        }
    this->wavefunction = std::move(wavefunction);
    this->probability  = std::move(probability);
    this->base         = std::move(base);
    this->energy       = energy;
}

const std::vector<double> &State::getWavefunction() { return this->wavefunction; }
const std::vector<double> &State::getProbability() { return this->probability; }
const double &State::getEnergy() { return this->energy; }

void State::printToFile() {
    std::ofstream basefile("base.dat");
    std::ofstream wavefunctionfile("wavefunction.dat");
    std::ofstream probabilityfile("probability.dat");

    if (wavefunctionfile.is_open() && probabilityfile.is_open() && basefile.is_open()) {
        std::vector<double> base_coords = this->base.getCoords();

        for (double wavefunction_element : wavefunction)
            wavefunctionfile << wavefunction_element << std::endl;
        
        for (double probability_element : probability)
            probabilityfile << probability_element << std::endl;

        basefile << base;

        wavefunctionfile.close();
        probabilityfile.close();
        basefile.close();
    }
}

std::ostream &operator<<(std::ostream &stream, const State &st) {
    std::vector<double> base_coords = st.getBase().getCoords();

    stream << std::setw(20) << std::right << "Basis coordinates";
    stream << std::setw(20) << std::right << "Wavefunction";
    stream << std::setw(20) << std::right << "Probability" << std::endl;

    for (int i = 0; i < base_coords.size(); i++) {

        // Printing coord
        stream << std::setprecision(3) << std::setw(20) << std::right << base_coords[i];

        // Printing wavefunction
        stream << std::setprecision(3) << std::setw(20) << std::right << st.wavefunction[i];

        // Printing probability
        stream << std::setprecision(3) << std::setw(20) << std::right << st.probability[i]
               << std::endl;
    }

    return stream;
}

State operator^ (State& state_1, State& state_2) {
        Base base_1 = state_1.getBase();
        Base base_2 = state_2.getBase();
        Base base = base_1 + base_2;

        std::vector<double> wavefunction = std::vector<double>(
                                                state_1.wavefunction.size() * state_2.wavefunction.size()
                                            );

        std::vector<double> potential = std::vector<double>(
                                                state_1.potential.getValues().size() * state_2.potential.getValues().size()
        );
        
        for (int i = 0; i < state_1.wavefunction.size(); i++)
            for (int j = 0; j < state_2.wavefunction.size(); j++)
                wavefunction.push_back(state_1.wavefunction.at(i) * state_2.wavefunction.at(j));

        for (int i = 0; i < state_1.potential.getValues().size(); i++)
            for (int j = 0; j < state_2.potential.getValues().size(); j++)
                potential.push_back(state_1.potential.getValues().at(i) + state_2.potential.getValues().at(j));

        double energy = state_1.getEnergy() + state_2.getEnergy();
        
        Potential final_potential = Potential(base, potential);
        return State(wavefunction, final_potential, energy, base, state_1.nbox);
};


