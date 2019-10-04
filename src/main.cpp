#include <iostream>
#include <string>

#include "Base.h"
#include "BasisManager.h"
#include "LogManager.h"
#include "Numerov.h"
#include "Potential.h"
#include "State.h"
#include "../tests/analytical.h"

void box_potential_example() {
    unsigned int nbox = 500;
    double mesh       = 0.01;
    double k          = 0.0;
    double height     = 0.0;
    double width      = 0.0;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;
    int dimension     = 1;
    std::vector<double> wavefunction;

    // Initialize the base using preset and parameters
    BasisManager::Builder baseBuilder;
    Base base = baseBuilder.addContinuous(mesh, nbox).build(dimension);

    Potential::Builder potentialBuilder(base);

    // No need to setup Box_potential, is just 0 and the above defined cartesian basis sets up the
    // box. With zero-edge boundary conditions this correspond to infinite well potential with the
    // width of the cartesian basis
    Potential V = potentialBuilder.setType(Potential::PotentialType::BOX_POTENTIAL).build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction = state.getWavefunction();
    energy       = state.getEnergy();

    S_INFO("Energy {}", energy);
    S_INFO("Printing state");

    // This is find being output to console
    std::cout << state;

    // Save to file wavefunction and probability
    state.printToFile();
}

void finite_well_example() {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    double height     = 5.0;
    double width      = 7.0;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;
    std::vector<double> wavefunction;

    // double anal_energy;
    // std::vector<double> anal_wf;

    // Initialize the base using a ContinuousInitializer
    ContinuousInitializer x_ini(mesh, nbox);
    BasisManager::Builder b;
    Base base = b.build(x_ini);

    Potential::Builder potentialBuilder(base);
    Potential V = potentialBuilder.setType(Potential::PotentialType::FINITE_WELL_POTENTIAL)
                      .setHeight(height)
                      .setWidth(width)
                      .build();

    std::ofstream basefile("base.dat");
    std::ofstream potentialfile("potential.dat");
    basefile << base.toString();
    potentialfile << V.toString();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction = state.getWavefunction();
    energy       = state.getEnergy();

    // std::cout << std::endl << energy << std::endl;
    auto [anal_wf, anal_energy] = finite_well_wf(1, nbox, width, height, mesh);

    std::ofstream myfile("analitical.dat");

    for (std::vector<int>::size_type i = 0; i < anal_wf.size(); i++) 
	    myfile << anal_wf.at(i) << '\n';
    myfile << std::endl;

    S_INFO("Energy {}", energy, anal_energy);
    S_INFO("Printing state");

    // Save to file wavefunction and probability
    state.printToFile();
    V.printToFile();

}

void harmonic_oscillator_example() {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    double k          = 1.0;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;
    int dimension     = 1;
    std::vector<double> wavefunction;

    BasisManager::Builder baseBuilder;
    Base base = baseBuilder.addContinuous(mesh, nbox).build(dimension);

    Potential::Builder potentialBuilder(base);
    Potential V =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction = state.getWavefunction();
    energy       = state.getEnergy();

    S_INFO("Energy {}", energy);
    S_INFO("Printing state");

    std::cout << state;

    // Save to file wavefunction and probability
    state.printToFile();
}

void harmonic_oscillator_2D_example() {
    unsigned int nbox = 100;
    double mesh       = 0.03;
    double k          = 1.0;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;

    std::vector<double> wavefunction;

    BasisManager::Builder baseBuilder;
    Base base = baseBuilder.build(Base::basePreset::Cartesian, 2, mesh, nbox);

    Potential::Builder potentialBuilder(base);
    Potential V =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction = state.getWavefunction();
    energy       = state.getEnergy();

    S_INFO("Energy {}", energy);

    // Save to file wavefunction and probability
    state.printToFile();
    V.printToFile();
}

void finite_well_2D_example() {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    double height     = 5.0;
    double width      = 7.0;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;

    BasisManager::Builder b;
    Base base = b.build(Base::basePreset::Cartesian, 2, mesh, nbox);

    Potential::Builder potentialBuilder(base);
    Potential V = potentialBuilder.setType(Potential::PotentialType::FINITE_WELL_POTENTIAL)
                      .setHeight(height)
                      .setWidth(width)
                      .build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    std::vector<double> wavefunction = state.getWavefunction();
    energy       = state.getEnergy();

    S_INFO("Energy {}", energy);

    // Save to file wavefunction and probability
    state.printToFile();
    V.printToFile();
}

void box_2D_example() {
    unsigned int nbox = 500;
    double mesh       = 0.01;
    double k          = 0.0;
    double height     = 0.0;
    double width      = 0.0;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;

    BasisManager::Builder b;
    Base base = b.build(Base::basePreset::Cartesian, 2, mesh, nbox);

    Potential::Builder potentialBuilder(base);
    Potential V = potentialBuilder.setType(Potential::PotentialType::BOX_POTENTIAL) 
                    .setK(k)
                    .setHeight(height)
                    .setWidth(width).build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    std::vector<double> wavefunction = state.getWavefunction();
    energy       = state.getEnergy();

    S_INFO("Energy {}", energy);

    // Save to file wavefunction and probability
    state.printToFile();
    V.printToFile();
}

void custom_workflow() {
    BasisManager::Builder builder = BasisManager::Builder();
    BasisManager *manager         = BasisManager::getInstance();
    Base base;
    std::vector<Base> basis;

    // Setup the properties of a new base, using the basis builder
    int dimension = 2;

    // Specify parameters of first dimension
    double start_1 = 0;
    double end_1   = 1000;
    double mesh_1  = 2;

    // Specify parameters of second dimension
    double start_2 = 0;
    double end_2   = 1000;
    double mesh_2  = 2;

    // Add the continuous representation to the base, using the basis builder
    builder.addContinuous(start_1, end_2, mesh_2);
    builder.addContinuous(start_2, end_2, mesh_2);

    // Getting a base object, building with the previous specified parameters in the basis builder.
    // (Specify that the base is Cartesian, passing also the dimension)
    base = builder.build(Base::basePreset::Cartesian, dimension);

    // Add the base in the basis list, using the basis manager
    manager->addBase(base);

    // Get a list of basis from the basis list (Not mandatory)
    basis = manager->getBasisList();

    // Print basis values for each dimension
    std::cout << base.toString();
}

int main(int argc, char **argv) {
    bool debug = true;

    LogManager::getInstance().Init(debug);

    int c = 0;
    std::cout << "Choose: " << '\n';
    std::cout << "1) 1D Hamonic oscillator (example)" << '\n';
    std::cout << "2) 1D Box (example)" << '\n';
    std::cout << "3) 1D Finite well (example)" << '\n';
    std::cout << "4) 2D Harmonic oscillator (example)" << '\n';
    std::cout << "5) 2D Box (example)" << '\n';
    std::cout << "6) 2D Finite well (example)" << '\n';

    std::cout << "\nInsert: ";
    std::cin >> c;

    switch (c) {
        case 1:
            harmonic_oscillator_example();
            break;
        case 2:
            box_potential_example();
            break;
        case 3:
            finite_well_example();
            break;
        case 4:
            harmonic_oscillator_2D_example();
            break;
        case 5:
            box_2D_example();
            break;
        case 6:
            finite_well_2D_example();
            break;
            
        default:
            S_ERROR("Not a valid option");
            break;
    }

    return 0;
}
