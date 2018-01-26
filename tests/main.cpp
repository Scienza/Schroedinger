#include <gtest/gtest.h>
#include "../include/Schroedinger.h"
#include "../include/test.h"
#include "../include/potentials.h"

namespace {

    TEST(WfTest,HarmonicOscillator){
        int nbox = 1000;
        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];

        numerov_Wf[0] = 0.;
        numerov_Wf[1] = 0.2; //later on it gets renormalized, so is just a conventional number
        solve_Numerov(0., 2., 0.01, nbox, &ho_potential, numerov_Wf);

        analytic_Wf = harmonic_wf(1,nbox, 1.);
        for(int i; i < nbox; i++){
            ASSERT_FLOAT_EQ(numerov_Wf[i],analytic_Wf[i]);
        }
    }

    TEST(WfTest,Box){
        int nbox = 500;
        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];

        numerov_Wf[0] = 0.;
        numerov_Wf[1] = 0.2; //later on it gets renormalized, so is just a conventional number
        solve_Numerov(0., 2., 0.01, nbox, &box_potential, numerov_Wf);

        analytic_Wf = box_wf(1,nbox);
        for(int i; i < nbox; i++){
            ASSERT_FLOAT_EQ(numerov_Wf[i],analytic_Wf[i]);
        }
    }

    TEST(WfTest,FiniteWell){
        int nbox = 1000;
        double width = 3., height = 10.;
        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];

        numerov_Wf[0] = 0.;
        numerov_Wf[1] = 0.2; //later on it gets renormalized, so is just a conventional number
        solve_Numerov(0., 2., 0.01, nbox, &finite_well_potential, numerov_Wf);

        analytic_Wf = finite_well_wf(2, nbox, width, height);
        for(int i; i < nbox; i++){
            ASSERT_FLOAT_EQ(numerov_Wf[i],analytic_Wf[i]);
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
