#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#include <gtest/gtest.h>

#include "../src/Schroedinger/Schroedinger.h"
#include "test.h"

double H3(double x) { return  8*std::pow(x,3) - 12*x; }
double H4(double x) { return 16*std::pow(x,4) - 48*x*x+12; }

void testWf(unsigned int nbox, std::string potType, double k, double width, double height,
            std::vector<double> x, std::vector<double>* pot,
            double* numerov_Wf, double* analytic_Wf){

    Potential::Builder b(x);
    Potential V = b.setType(potType)
                    .setK(k)
                    .setHeight(height)
                    .setWidth(width)
                    .build();

    *pot = V.get_v();

    numerov_Wf[0] = 0.0;
    numerov_Wf[1] = 0.2; //later on it gets renormalized, so is just a conventional number

    double E_numerov = solve_Numerov(0., 2., 0.01, nbox, V, numerov_Wf);
    double E_analytic;

    if(potType == "box") {
        E_analytic = box_wf(1, nbox, analytic_Wf);
    }
    else if(potType == "harmonic oscillator") {
        E_analytic = harmonic_wf(0,nbox, sqrt(2.*k), analytic_Wf);
    }
    else if(potType == "well") {
        E_analytic = finite_well_wf(1, nbox, width, height, analytic_Wf);
    }
    else {
        std::cerr << "ERROR! Wrong potential name in set" << std::endl;
        exit(8);
    }

    for(int i=0; i < nbox; i++) {
        EXPECT_NEAR(numerov_Wf[i], analytic_Wf[i], 1e-2 ); //improve error definition
     }

    ASSERT_NEAR(E_numerov, E_analytic, 1e-3 );
}

namespace {
    TEST(NumTest,Hermite){
        ASSERT_NEAR(std::hermite(3, 10.), H3(10.),err);
        ASSERT_NEAR(std::hermite(4, 4.3), H4(4.3),err);
    }

    TEST(Potential, widthMustBePositive) {
        std::vector<double> x;
        try {
            Potential p = Potential::Builder(x).setWidth(-1).build();
            FAIL();
        }
        catch(std::invalid_argument e) {}
    }

    TEST(Potential, typeCannotBeEmpty) {
        std::vector<double> x;
        try {
            Potential p = Potential::Builder(x).setType("").build();
            FAIL();
        }
        catch(std::invalid_argument e) {}
    }

    TEST(Potential, typeMustBeKnown) {
        std::vector<double> x;
        try {
            Potential p = Potential::Builder(x).setType("unknownType").build();
            FAIL();
        }
        catch(std::invalid_argument e) {}
    }

    TEST(WfTest,HarmonicOscillator){
        unsigned int nbox = 1000;
        std::string s = "harmonic oscillator";

        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];
        std::vector<double> x(nbox), pot(nbox);

        for(std::vector<int>::size_type i = 0; i < x.size(); i++)
            x[i] = dx * (int) (i - nbox / 2);

        testWf(nbox, s,  0.500, 0., 0., x, &pot, numerov_Wf, analytic_Wf);

        if(HasFailure()){
            for(int i=0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }

    TEST(WfTest,HarmonicOscillator2){
        unsigned int nbox = 1000;
        std::string s = "harmonic oscillator";

        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];
        std::vector<double> x(nbox), pot(nbox);

        for(std::vector<int>::size_type i = 0; i < x.size(); i++)
            x[i] = dx * (int) (i - nbox / 2);

        testWf(nbox, s,  1.0, 0.0, 0.0, x, &pot, numerov_Wf, analytic_Wf);

        if(HasFailure()){
            for(int i=0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }


    TEST(WfTest,Box){
        unsigned int nbox = 500;
        std::string s = "box";

        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];
        std::vector<double> x(nbox), pot(nbox);

        for(std::vector<int>::size_type i = 0; i < x.size(); i++)
            x[i] = dx * (int) (i - nbox / 2);

        testWf(nbox, s,  0.0, 0.0, 0.0, x, &pot, numerov_Wf, analytic_Wf);

        if(HasFailure()){
            for(int i=0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }

    TEST(WfTest,Box2){
        unsigned int nbox = 1000;
        std::string s = "box";

        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];
        std::vector<double> x(nbox), pot(nbox);

        for(std::vector<int>::size_type i = 0; i < x.size(); i++)
            x[i] = dx * (int) (i - nbox / 2);

        testWf(nbox, s,  0.0, 0.0, 0.0, x, &pot, numerov_Wf, analytic_Wf);

        if(HasFailure()){
            for(int i=0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }

    TEST(WfTest,FiniteWell1){
        unsigned int nbox = 2000;
        std::string s = "well";

        double width = 10., height = 3.;
        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];
        std::vector<double> x(nbox), pot(nbox);

        for(std::vector<int>::size_type i = 0; i < x.size(); i++)
            x[i] = dx * (int) (i - nbox / 2);

        testWf(nbox, s, 0., width, height, x, &pot, numerov_Wf, analytic_Wf);

        if(HasFailure()){
            for(int i=0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }

    TEST(WfTest,FiniteWell2){
        unsigned int nbox = 1000;
        std::string s = "well";

        double width = 7.0, height = 5.0;
        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];
        std::vector<double> x(nbox), pot(nbox);

        for(std::vector<int>::size_type i = 0; i < x.size(); i++)
            x[i] = dx * (int) (i - nbox / 2);

        testWf(nbox, s,  0.0, width, height, x, &pot, numerov_Wf, analytic_Wf);

        if(HasFailure()){
            for(int i=0; i < nbox; i++)
                std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " "
                          << pot[i] << " " << analytic_Wf[i] - numerov_Wf[i] << std::endl;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
