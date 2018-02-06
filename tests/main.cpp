#include <gtest/gtest.h>
#include "../include/Schroedinger.h"
#include "../include/test.h"
#include "../include/potentials.h"

namespace {
//
    TEST(WfTest,HarmonicOscillator){
        int nbox = 1000;
        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];

        numerov_Wf[0] = 0.;
        numerov_Wf[1] = 0.2; //later on it gets renormalized, so is just a conventional number
        solve_Numerov(0., 2., 0.01, nbox, &ho_potential, numerov_Wf);

        harmonic_wf(0,nbox, 1., analytic_Wf);

        for(int i=0; i < nbox; i++){
//          std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << std::endl;
          ASSERT_TRUE(fabs(numerov_Wf[i] - analytic_Wf[i]) < 1e-5 );
        }
    }

    TEST(WfTest,Box){
        int nbox = 500;
        double *numerov_Wf = new double[nbox+1];
        double *analytic_Wf = new double[nbox+1];

        numerov_Wf[0] = 0.;
        numerov_Wf[1] = 0.2; //later on it gets renormalized, so is just a conventional number
        solve_Numerov(0., 2., 0.01, nbox, &box_potential, numerov_Wf);

        box_wf(1,nbox, analytic_Wf);
        for(int i=0; i <= nbox; i++){
            std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << std::endl;
          // Check that the box is of the same dimension for numerov and analytical
            ASSERT_TRUE(fabs(numerov_Wf[i] - analytic_Wf[i]) < err*10 );
        }
    }

    TEST(WfTest,FiniteWell){
        int nbox = 1000;
        double width = 5., height = 10.;
        double *numerov_Wf = new double[nbox];
        double *analytic_Wf = new double[nbox];

        numerov_Wf[0] = 0.;
        numerov_Wf[1] = 0.2; //later on it gets renormalized, so is just a conventional number
        solve_Numerov(0., 2., 0.01, nbox, &finite_well_potential, numerov_Wf);

        finite_well_wf(1, nbox, width, height, analytic_Wf);
        for(int i=0; i < nbox; i++){
//            std::cout << i << " " << numerov_Wf[i] << " " << analytic_Wf[i] << " " << finite_well_potential((-nbox/2 + i)*dx) << std::endl;
            ASSERT_TRUE(fabs(numerov_Wf[i] - analytic_Wf[i]) < 1e-2 );
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
