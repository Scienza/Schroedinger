#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#include <gtest/gtest.h>
#include <Numerov.h>
#include <BasisManager.h>
#include <Potential.h>
#include "test.h"
double H3(double x) { return 8 * std::pow(x, 3) - 12 * x; }

double H4(double x) { return 16 * std::pow(x, 4) - 48 * x * x + 12; }

void testWf(unsigned int nbox, Potential::PotentialType potType, double k, 
            double width, double height, Base base, std::vector<double> &pot, std::vector<double> &numerov_Wf, 
            std::vector<double> &analytic_Wf) {
    
    Potential::Builder b(base);
    Potential V = b.setType(potType)
                    .setK(k)
                    .setHeight(height)
                    .setWidth(width)
                    .build();
    

    Numerov solver = Numerov(V, nbox);
    solver.solve(0.0, 2.0, 0.01);

    numerov_Wf  = solver.getWavefunction();
    analytic_Wf = std::vector<double>(numerov_Wf.size());

    double E_numerov = solver.getSolutionEnergy();
    double E_analytic;
    
    switch(potType) {
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
                std::cerr <<"ERROR: Wrong potential type!";
                exit(8);
    }

    if (analytic_Wf.size() == numerov_Wf.size())
        for (int i = 0; i < analytic_Wf.size(); i++) {
            EXPECT_NEAR(numerov_Wf.at(i), analytic_Wf.at(i), 1e-2); //improve error definition
        }
    else   
        FAIL() << "Analytic wavefunction and Numerov wavefunction haven't the same size " << analytic_Wf.size() << " " << numerov_Wf.size();

    ASSERT_NEAR(E_numerov, E_analytic, 1e-3);
}

namespace {
    TEST(NumTest, Hermite) {
        ASSERT_NEAR(std::hermite(3, 10.), H3(10.), err);
        ASSERT_NEAR(std::hermite(4, 4.3), H4(4.3), err);
    }

    TEST(Basis, IsSingleton) {
        BasisManager *m1 = BasisManager::getInstance();
        BasisManager *m2 = BasisManager::getInstance();
        ASSERT_EQ(m1, m2);
    }

    TEST(Potential, widthMustBePositive) {
        Base b;
        try {
            Potential p = Potential::Builder(b).setWidth(-1).build();
            FAIL();
        }
        catch (std::invalid_argument e) {}
    }

    TEST(Basis, Constructor) {
        unsigned int nbox = 1000;
        double mesh = 0.1;
        int dimension = 1;
        std::vector<double> x(nbox);

        // Building Basis
        BasisManager::Builder b = BasisManager::Builder();
        BasisManager *manager = BasisManager::getInstance();

        // With this we save a new base, created with the Builder object b.
        manager->addBase(b.addContinuous(mesh, nbox).build(dimension));

        // This is to get a list of available basis
        std::vector<Base> bases = manager->getBasisList();

        // getContinuous() returns a vector of continuousbasis, even if there's only one dimension!
        // So in this test we select the first base and its first continuousbase
        ContinuousBase firstContinuousBase = bases.at(0).getContinuous().at(0);
        std::vector<double> firstDimensionCoords = firstContinuousBase.getCoords();

        for (std::vector<int>::size_type i = 0; i < x.size(); i++) {
            x[i] = mesh * (int) (i - nbox / 2);
            ASSERT_NEAR(x[i], firstDimensionCoords[i], err);
        }
    }

    TEST(WfTest, HarmonicOscillator) {
        unsigned int nbox = 1000;
        double mesh = 0.01;

        BasisManager::Builder b;
        Base base = b.build(Base::basePreset::Cartesian, 1, mesh, nbox);

        
        std::vector<double> numerov_Wf;
        std::vector<double> analytic_Wf;        
        std::vector<double> pot;

        testWf(nbox, Potential::PotentialType::HARMONIC_OSCILLATOR, 0.500, 0.0, 0.0, base,  pot, numerov_Wf, analytic_Wf);

        if (HasFailure()) {
            for (int i = 0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }

    TEST(WfTest, HarmonicOscillator2) {
        unsigned int nbox = 1000;
        double mesh = dx;
        BasisManager::Builder b;
        Base base = b.build(Base::basePreset::Cartesian, 1, mesh, nbox);

        std::vector<double> numerov_Wf;
        std::vector<double> analytic_Wf;
        std::vector<double> pot;

        testWf(nbox, Potential::PotentialType::HARMONIC_OSCILLATOR, 1.0, 0.0, 0.0, base, pot, numerov_Wf, analytic_Wf);

        if (HasFailure()) {
            for (int i = 0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }


    TEST(WfTest, Box) {
        unsigned int nbox = 500;
        double mesh = dx;
        BasisManager::Builder b;
        Base base = b.build(Base::basePreset::Cartesian, 1, mesh, nbox);

        std::vector<double> numerov_Wf;
        std::vector<double> analytic_Wf;        
        std::vector<double> pot;

        testWf(nbox, Potential::PotentialType::BOX_POTENTIAL, 0.0, 0.0, 0.0, base, pot, numerov_Wf, analytic_Wf);

        if (HasFailure()) {
            for (int i = 0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }

    TEST(WfTest, Box2) {
        unsigned int nbox = 1000;
        double mesh = dx;
        BasisManager::Builder b;
        Base base = b.build(Base::basePreset::Cartesian, 1, mesh, nbox);

        std::vector<double> numerov_Wf;
        std::vector<double> analytic_Wf;        
        std::vector<double> pot;

        testWf(nbox, Potential::PotentialType::BOX_POTENTIAL, 0.0, 0.0, 0.0, base, pot, numerov_Wf, analytic_Wf);

        if (HasFailure()) {
            for (int i = 0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }

    TEST(WfTest, FiniteWell1) {
        unsigned int nbox = 2000;
        double mesh = dx;
        ContinuousInitializer x_ini(mesh,nbox);
        BasisManager::Builder b;
        Base base = b.build(x_ini);

        double width = 10.0, height = 3.0;
        std::vector<double> numerov_Wf;
        std::vector<double> analytic_Wf;        
        std::vector<double> pot;

        testWf(nbox, Potential::PotentialType::FINITE_WELL_POTENTIAL, 0.0, width, height, base, pot, numerov_Wf, analytic_Wf);

        if (HasFailure()) {
            for (int i = 0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }

    TEST(WfTest, FiniteWell2) {
        unsigned int nbox = 1000;
        double mesh = dx;
        BasisManager::Builder b;
        Base base = b.build(Base::basePreset::Cartesian, 1, mesh, nbox);

        double width = 7.0, height = 5.0;
        std::vector<double> numerov_Wf;
        std::vector<double> analytic_Wf;        
        std::vector<double> pot;

        testWf(nbox, Potential::PotentialType::FINITE_WELL_POTENTIAL, 0.0, width, height, base, pot, numerov_Wf, analytic_Wf);

        if (HasFailure()) {
            for (int i = 0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
