#include <gtest/gtest.h>
#include "BasisManager.h"
#include "Numerov.h"
#include "Potential.h"
#include "State.h"

#include "analytical.h"

void testWavefunction(unsigned int nbox, Potential::PotentialType potType, double k, double width,
                      double height, Base base, std::vector<double> &pot,
                      std::vector<double> &numerov_Wf, std::vector<double> &analytic_Wf) {

    double e_min      = 0.0;
    double e_max      = 2.0;
    double e_step     = 0.01;

    Potential::Builder b(base);
    Potential V = b.setType(potType).setK(k).setHeight(height).setWidth(width).build();

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    numerov_Wf  = state.getWavefunction();
    analytic_Wf = numerov_Wf;

    Potential p = state.getPotential();
    pot = p.getValues().at(0);
    double E_numerov = state.getEnergy();
    double E_analytic;

    switch (potType) {
        case Potential::PotentialType::BOX_POTENTIAL:
            E_analytic = box_wf(1, nbox, analytic_Wf);
            break;
        case Potential::PotentialType::HARMONIC_OSCILLATOR:
            E_analytic = harmonic_wf(0, nbox, sqrt(2. * k), analytic_Wf);
            break;
        case Potential::PotentialType::FINITE_WELL_POTENTIAL:
            E_analytic = finite_well_wf(1, nbox, width, height, analytic_Wf);
            break;
        default:
            std::cerr << "ERROR: Wrong potential type!";
            exit(8);
    }

    //if (analytic_Wf.size() == numerov_Wf.size()) {
        for (int i = 0; i < analytic_Wf.size(); i++)
            ASSERT_NEAR(numerov_Wf.at(i), analytic_Wf.at(i), 1e-2);  // improve error definition
    //} //else
    //    FAIL() << "Analytic wavefunction and Numerov wavefunction haven't the same size "
    //           << analytic_Wf.size() << " " << numerov_Wf.size();

    ASSERT_NEAR(E_numerov, E_analytic, 1e-3);

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
