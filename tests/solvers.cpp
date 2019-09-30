#include <gtest/gtest.h>
#include "BasisManager.h"
#include "Numerov.h"
#include "Potential.h"
#include "State.h"

#include "analytical.h"

void testWavefunction(unsigned int nbox, Potential::PotentialType potType, double k, double width,
                      double height, Base base, std::vector<double> &pot,
                      std::vector<double> &numerov_Wf, std::vector<double> &an_wavefunciton) {

    double e_min  = 0.0;
    double e_max  = 2.0;
    double e_step = 0.01;

    Potential::Builder b(base);
    Potential V = b.setType(potType).setK(k).setHeight(height).setWidth(width).build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    numerov_Wf  = state.getWavefunction();

    Potential p      = state.getPotential();
    pot              = p.getValues().at(0);
    double E_numerov = state.getEnergy();

	std::pair<std::vector<double>, double> result;

    switch (potType) {
        case Potential::PotentialType::BOX_POTENTIAL:
            result = box_wf(1, nbox);
            break;
        case Potential::PotentialType::HARMONIC_OSCILLATOR:
            result = harmonic_wf(0, nbox, sqrt(2.0 * k));
            break;
        case Potential::PotentialType::FINITE_WELL_POTENTIAL: 
            result = finite_well_wf(1, nbox, width, height);
            break;
        default:
            std::cerr << "ERROR: Wrong potential type!";
            exit(8);
    }

	auto [anal_wf, anal_energy] = result;
    an_wavefunciton             = anal_wf;

    for (int i = 0; i < anal_wf.size(); i++) {
        ASSERT_NEAR(numerov_Wf.at(i), anal_wf.at(i), 1e-2);  // improve error definition
    }

    ASSERT_NEAR(E_numerov, anal_energy, 1e-3);

    // std::cout << std::fixed << std::setprecision(2);
    // std::cout << "Test completed" << std::endl;
    // std::cout << "Energies: " << E_numerov << " " << E_analytic << std:: endl;
    // std::cout << "num wf: " << numerov_Wf.at(0) << " " << numerov_Wf.at(numerov_Wf.size()/2)
    //           << " " << numerov_Wf.at(numerov_Wf.size() - 1) << " " << std::endl;
    // std::cout << "ana wf: " << analytic_Wf.at(0) << " " << analytic_Wf.at(analytic_Wf.size()/2)
    //           << " " << analytic_Wf.at(analytic_Wf.size()-1) << std::endl;
}

TEST(Wavefunction_and_energy, Numerov_HarmonicOscillator) {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    int dimension     = 1;

    std::vector<double> numerov_Wf;
    std::vector<double> analytic_Wf;
    std::vector<double> pot;

    BasisManager::Builder b;
    Base base = b.addContinuous(mesh, nbox).build(dimension);

    testWavefunction(nbox, Potential::PotentialType::HARMONIC_OSCILLATOR, 0.500, 0.0, 0.0, base,
                     pot, numerov_Wf, analytic_Wf);

    if (HasFailure()) {
        for (int i = 0; i < nbox; i++)
            std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " " << pot[i] << " "
                      << analytic_Wf[i] - numerov_Wf[i] << '\n';
    }
}

TEST(Wavefunction_and_energy, Numerov_HarmonicOscillator2) {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    std::vector<double> numerov_Wf;
    std::vector<double> analytic_Wf;
    std::vector<double> pot;

    BasisManager::Builder b;
    Base base = b.build(Base::basePreset::Cartesian, 1, mesh, nbox);

    testWavefunction(nbox, Potential::PotentialType::HARMONIC_OSCILLATOR, 1.0, 0.0, 0.0, base, pot,
                     numerov_Wf, analytic_Wf);

    // if (HasFailure()) {
    //     for (int i = 0; i < nbox; i++)
    //         std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " " << pot[i] << " "
    //                   << analytic_Wf[i] - numerov_Wf[i] << '\n';
    // }
}

TEST(Wavefunction_and_energy, Numerov_HarmonicOscillator3) {
    unsigned int nbox = 100;
    double mesh       = 0.1;
    std::vector<double> numerov_Wf;
    std::vector<double> analytic_Wf;
    std::vector<double> pot;

    BasisManager::Builder b;
    Base base = b.build(Base::basePreset::Cartesian, 1, mesh, nbox);

    testWavefunction(nbox, Potential::PotentialType::HARMONIC_OSCILLATOR, 1.0, 0.0, 0.0, base, pot,
                     numerov_Wf, analytic_Wf);

    if (HasFailure()) {
        for (int i = 0; i < nbox; i++)
            std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " " << pot[i] << " "
                      << analytic_Wf[i] - numerov_Wf[i] << '\n';
    }
}


TEST(Wavefunction_and_energy, Numerov_Box) {
    double mesh       = 0.01;
    unsigned int nbox = 1000;
    int dimension     = 1;

    std::vector<double> numerov_Wf;
    std::vector<double> analytic_Wf;
    std::vector<double> pot;

    BasisManager::Builder b;
    Base base = b.addContinuous(mesh, nbox).build(dimension);

    testWavefunction(nbox, Potential::PotentialType::BOX_POTENTIAL, 0.0, 0.0, 0.0, base, pot,
                     numerov_Wf, analytic_Wf);

    if (HasFailure()) {
        for (int i = 0; i < nbox; i++)
            std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " " << pot[i] << " "
                      << analytic_Wf[i] - numerov_Wf[i] << '\n';
    }
}

TEST(Wavefunction_and_energy, Numerov_Box2) {
    double mesh       = 0.01;
    unsigned int nbox = 500;
    int dimension     = 1;

    std::vector<double> numerov_Wf;
    std::vector<double> analytic_Wf;
    std::vector<double> pot;

    BasisManager::Builder b;
    Base base = b.addContinuous(mesh, nbox).build(dimension);

    testWavefunction(nbox, Potential::PotentialType::BOX_POTENTIAL, 0.0, 0.0, 0.0, base, pot,
                     numerov_Wf, analytic_Wf);

    if (HasFailure()) {
        for (int i = 0; i < nbox; i++)
            std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " " << pot[i] << " "
                      << analytic_Wf[i] - numerov_Wf[i] << '\n';
    }
}

TEST(Wavefunction_and_energy, Numerov_FiniteWell1) {
    unsigned int nbox = 2000;
    double mesh       = dx;
    double width      = 10.0;
    double height     = 3.0;
    std::vector<double> numerov_Wf;
    std::vector<double> analytic_Wf;
    std::vector<double> pot;

    ContinuousInitializer x_ini(mesh, nbox);
    BasisManager::Builder b;
    Base base = b.build(x_ini);
    testWavefunction(nbox, Potential::PotentialType::FINITE_WELL_POTENTIAL, 0.0, width, height,
                     base, pot, numerov_Wf, analytic_Wf);

    if (HasFailure()) {
        for (int i = 0; i < nbox; i++)
            std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " " << pot[i] << " "
                      << analytic_Wf[i] - numerov_Wf[i] << '\n';
    }
}

TEST(Wavefunction_and_energy, Numerov_FiniteWell2) {
    unsigned int nbox = 1000;
    double mesh       = dx;
    BasisManager::Builder b;
    Base base = b.build(Base::basePreset::Cartesian, 1, mesh, nbox);

    double width = 7.0, height = 5.0;
    std::vector<double> numerov_Wf;
    std::vector<double> analytic_Wf;
    std::vector<double> pot;

    testWavefunction(nbox, Potential::PotentialType::FINITE_WELL_POTENTIAL, 0.0, width, height,
                     base, pot, numerov_Wf, analytic_Wf);

    if (HasFailure()) {
        for (int i = 0; i < nbox; i++)
            std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " " << pot[i] << " "
                      << analytic_Wf[i] - numerov_Wf[i] << '\n';
    }
}

TEST(NDimensional, harmonic_oscillator_2D) {
    unsigned int nbox = 200;
    double mesh       = 0.05;
    double k          = 1.0;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;

    BasisManager::Builder baseBuilder;
    Base base = baseBuilder.build(Base::basePreset::Cartesian, 2, mesh, nbox);

    Potential::Builder potentialBuilder(base);
    Potential V =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();

    Numerov solver(V, nbox);
    State state = solver.solve(e_min, e_max, e_step);

    std::vector<double> wavefunction = state.getWavefunction();
    energy                           = state.getEnergy();

    auto [anal_wf, anal_energy] = harmonic_wf(0, nbox, sqrt(2.0 * k));

    int ii = 0;
    for (int i = 0; i < anal_wf.size(); i++){
        for (int j = 0; j < anal_wf.size(); j++){
            ASSERT_NEAR(wavefunction.at(ii), anal_wf.at(i)*anal_wf.at(j), 1e-2);  // improve error definition
            ii++;
        }
    }

    ASSERT_NEAR(energy, 2.0 * anal_energy, 1e-3);
}

TEST(NDimensional, harmonic_oscillator_3D) {
    unsigned int nbox = 100;
    double mesh       = 0.1;
    double k          = 1.0;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;

    std::vector<double> wavefunction;

    BasisManager::Builder baseBuilder;
    Base base = baseBuilder.build(Base::basePreset::Cartesian, 3, mesh, nbox);

    Potential::Builder potentialBuilder(base);
    Potential V =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction = state.getWavefunction();
    energy       = state.getEnergy();

    auto [anal_wf, anal_energy]     = harmonic_wf(0, nbox, sqrt(2.0 * k));

    int ii = 0;
    for (int i = 0; i < anal_wf.size(); i++){
        for (int j = 0; j < anal_wf.size(); j++){
            for (int l = 0; l < anal_wf.size(); l++){
                ASSERT_NEAR(wavefunction.at(ii), anal_wf.at(i)*anal_wf.at(j)*anal_wf.at(l), 1e-2);  // improve error definition
                ii++;
            }
        }
    }

    ASSERT_NEAR(energy, 3.0 * anal_energy, 1e-3);
}


TEST(NDimensional, FiniteWell_2D) {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    double energy     = 0.0;
    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;

    BasisManager::Builder b;
    Base base = b.build(Base::basePreset::Cartesian, 2, mesh, nbox);

    double width = 8.0, height = 10.0;

    std::vector<double> numerov_Wf;
    std::vector<double> analytic_Wf;

    Potential::Builder potentialBuilder(base);
    Potential V =
        potentialBuilder.setType(Potential::PotentialType::FINITE_WELL_POTENTIAL).setHeight(height).setWidth(width).build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    numerov_Wf     = state.getWavefunction();
    energy         = state.getEnergy();

    auto [anal_wf, anal_energy]     = finite_well_wf(1, nbox, width, height);

    int ii = 0;
    for (int i = 0; i < anal_wf.size(); i++){
        for (int j = 0; j < anal_wf.size(); j++){
            ASSERT_NEAR(numerov_Wf.at(ii), anal_wf.at(i)*anal_wf.at(j), 1e-2);  // improve error definition
            ii++;
        }
    }

    ASSERT_NEAR(energy, 2.0 * anal_energy, 1e-3);

}
