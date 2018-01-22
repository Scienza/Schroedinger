#include <iostream>
#include "Schroedinger.h"
#include "test.h"
#include "gtest/gtest.h"

#include <string>

double potential(double);

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    int nbox = 1000;
    double step = 0.01, norm;
    double *wavefunction = new double[nbox];
    std::string mode = "TEST";

    if (mode == "TEST") {
      // wavefunction = box_wf(2,nbox);
      // wavefunction = finite_well_wf(2, nbox, 3., 10.);
      wavefunction = harmonic_wf(2,nbox, 1.);

    }else{
      wavefunction[0] = 0.;
      wavefunction[1] = 0.2; //later on it gets renormalized, so is just a conventional number
      solve_Numerov(0., 2., step, nbox, &potential, wavefunction);
    }
    //wavefunction initialization

   return RUN_ALL_TESTS();
}


namespace {

// Tests factorial of 0.
TEST(TrivialTest, one) {
  EXPECT_EQ(1, 1);
}

// TEST(ParameterTest, one) {
//   EXPECT_TRUE(nbox > 100);
// }

TEST(WfTest,HarmonicOscillator){
  int nbox = 1000;
  double *numerov_Wf = new double[nbox];
  double *analytic_Wf = new double[nbox];

  numerov_Wf[0] = 0.;
  numerov_Wf[1] = 0.2; //later on it gets renormalized, so is just a conventional number
  solve_Numerov(0., 2., 0.01, nbox, &potential, numerov_Wf);

  analytic_Wf = harmonic_wf(1,nbox, 1.);
  for(int i; i < nbox; i++){
    ASSERT_FLOAT_EQ(numerov_Wf[i],analytic_Wf[i]);
  }
}

}  // namespace

/* potential function defines the potential in function of position */
double potential(double x) {
    double value = x * x;
    return value;
} // end of function to evaluate
