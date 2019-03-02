#include "State.h"

State::State(std::vector<double> wavefunction, std::vector<double> probability, double energy, Base base)
{
    this->wavefunction = wavefunction;
    this->probability = probability;
    this->energy = energy;
    this->base = base;
}

const std::vector<double> &State::getWavefunction()
{
    return this->wavefunction;
}
const std::vector<double> &State::getProbability()
{
    return this->probability;
}
const double &State::getEnergy()
{
    return this->energy;
}

void State::printToFile()
{
    std::ofstream wavefunctionfile("wavefunction.dat");
    std::ofstream probabilityfile("probability.dat");

    if (wavefunctionfile.is_open() && probabilityfile.is_open()) {
        std::vector<double> base_coords = this->base.getCoords();

        for (int i = 0; i < base_coords.size(); i++) {

            // Printing wavefunction
            wavefunctionfile << base_coords[i] << " " << this->wavefunction[i] << std::endl;

            // Printing probability
            probabilityfile << base_coords[i] << " " << this->probability[i] << std::endl;
        }
        wavefunctionfile.close();
        probabilityfile.close();
    }
}

Base State::getBase() {
    return this->base;
}

std::ostream &operator<<(std::ostream &stream, State &st)
{
    std::vector<double> base_coords = st.getBase().getCoords();

    stream << std::endl << std::endl;
    stream  << std::setw(20) << std::right << "Coord from basis";
    stream  << std::setw(20) << std::right << "Wavefunction";
    stream  << std::setw(20) << std::right << "Probability" << std::endl;
    
    for (int i = 0; i < base_coords.size(); i++) {

        // Printing coord
        stream << std::setprecision(3) << std::setw(20) << std::right << base_coords[i]; 

        // Printing wavefunction
        stream << std::setprecision(3) << std::setw(20) << std::right << st.wavefunction[i];

        // Printing probability
        stream << std::setprecision(3) << std::setw(20) << std::right << st.probability[i] << std::endl;

    }   

    return stream;
}

// TODO: implement the overload to get the resulting state W(x,y) = W(x)^W(y)
std::ostream& operator^ (const State& state_1, const State& state_2) {

}
