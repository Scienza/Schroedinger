#include <State.h>

State::State(std::vector<double> wavefunction, std::vector<double> probability, double energy, Base base) {
    this->wavefunction = wavefunction;
    this->probability  = probability;
    this->energy       = energy;
    this->base         = base;
}

const std::vector<double>& State::getWavefunction() {
    return this->wavefunction;
}
const std::vector<double>& State::getProbability(){
    return this->probability;
}
const double& State::getEnergy(){
    return this->energy;
}

void State::printToFile() {
    std::ofstream wavefunctionfile ("wavefunction.dat");
    std::ofstream probabilityfile ("probability.dat");

    if (wavefunctionfile.is_open() && probabilityfile.is_open()){
        std::vector<double> base_coords = this->base.getCoords();

        for(int i = 0; i < base_coords.size(); i++) {

            // Printing wavefunction
            wavefunctionfile << base_coords[i] << " " << this->wavefunction[i] << std::endl ;

            // Printing probability
            probabilityfile << base_coords[i] << " " << this->probability[i] << std::endl;

        }
        wavefunctionfile.close();
        probabilityfile.close();
    }
}
