#include "Schroedinger.h"

/*! Calculates the analytical wavefunction of a particle in a box
allowed energy levels :   $E_n = n^2 \pi^2 \hbar^2 / (2 m L)$
wavefcuntion: $A*sin(n \pi/L * x)$
Analytically exact
nlevel > 0,
*/
double* box_wf(int nlevel, int nbox){
  double boxLength = nbox * dx;
  double Energy = nlevel * nlevel * pi * pi * hbar * hbar / 2. / mass / boxLength;
  double norm = sqrt(2/boxLength);
  double wavefunction [nbox];

  for(int i=0; i<nbox; i++){
    double x = i * dx;
    wavefunction[i] = norm * sin(nlevel * pi * x/boxLength);
    //remember to translate by half box length, eventually
    std::cout << x - boxLength/2. << " " << wavefunction[i] << std::endl;
  }

  return wavefunction;
  //
}

/*! Calculates the analytical wavefunction of a particle in a finite potential
allowed energy levels : $E_n = n^2 \pi^2 \hbar^2 / (2 m L)$
wavefcuntion: $A*sin(n \pi/L * x)$
This will not correspond exactly to a numerical solution in a box, since the
box is a finite overlay on top of the finite well, instead of an exact contiuum.
Check by expanding the box, and/or deepening the potential.
nlevel > 1
*/
double* finite_well_wf(int nlevel, int nbox, double pot_width, double pot_height){
  // double boxLength = nbox * dx;

  double xi = pot_width/2.*sqrt(2 * mass * pot_height / hbar / hbar);

  double k, alpha, G, H, A, B, E_n;
  double wavefunction [nbox];
  double eta_old, eta;
  double tolerance = 1e-10;
  int counter = 0;

  eta_old = 1. + pi/2. * (nlevel-1);
  // std::cout << "#" << eta_old << std::endl;
  do{
    counter++;
    eta = eta_old;

    if(nlevel % 2 == 0){ //looking for solution has n even, thus is odd parity
      eta_old = atan( sqrt(xi*xi/eta/eta - 1) + pi/2. ) + pi/2. * (nlevel-1);
    }else{             //looking for has n odd, thus is even parity
      eta_old = atan( sqrt(xi*xi/eta/eta - 1) ) + pi/2. * (nlevel-1);
    }
    // std::cout << "#" << eta << std::endl;
  } while ( fabs((eta_old - eta)/eta) > tolerance && counter < 100 );

  if(counter == 100){
    std::cerr << "transcendent equation in finite_well_wf() not converging" << std::endl;
    exit;
  }else{
    E_n = 2. / pot_width / pot_width * hbar * hbar / mass * eta * eta;
    // std::cout << "#" << nlevel << " solution for eta = " << eta << "  E_n =" << E_n << std::endl;
  }


  if(nlevel % 2 == 0){ //looking for solution has n even, thus is antisymmetric
    k = sqrt(2. * mass * (pot_height - E_n)) / hbar;
    double x = pot_width / 2.;
    A = 1.; B = 0.;
    H = A * sin (sqrt(2. * mass * E_n) * x) * exp( k * x );
    G = -H;
    // std::cout << A * sin (sqrt(2. * mass * E_n) * x) << " "
    // << H*exp( -k * x ) << std::endl;
  }else{             //looking for has n odd, thus is symmetric
    k = sqrt(2. * mass * (pot_height - E_n)) / hbar;
    double x = -pot_width / 2.;

    A = 0.; B = 1.;
    H = B * cos (sqrt(2. * mass * E_n) * x) * exp( -k * x);
    G = H;
  }

  for(int i=0; i<nbox; i++){
    double x = (- nbox/2 + i) * dx;

    if( x <= - pot_width/2.){
      k = sqrt(2. * mass * (pot_height - E_n)) / hbar;
      wavefunction[i] = G * exp( k*x );
    }else if( x > -pot_width/2. && x < pot_width/2.){
      k = sqrt(2. * mass * E_n) / hbar;
      wavefunction[i] = A * sin(k * x) + B * cos(k * x);
    }else{
      k = sqrt(2. * mass * (pot_height - E_n)) / hbar;
      // std::cout << k << " " << H << " " << exp( -k * x ) << std::endl;
      wavefunction[i] = H * exp( -k * x );
    }

    std::cout << x << " " << wavefunction[i] << std::endl;
  }


// Final Normalization
  double *probab = new double[nbox];

  for (int i = 0; i <= nbox; i++)
      probab[i] = wavefunction[i] * wavefunction[i];

  double norm = trap_array(0., nbox, dx, probab);
  for (int i = 0; i <= nbox; i++)
      wavefunction[i] = wavefunction[i] / sqrt(norm);

  return wavefunction;
  //
}

double H3(double x) { return 8*std::pow(x,3) - 12*x; }
double H4(double x) { return 16*std::pow(x,4)-48*x*x+12; }

inline int factorial(int x, int result = 1) {
  if (x == 1 || x == 0) return result; else return factorial(x - 1, x * result);
}

double* harmonic_wf(int nlevel, int nbox, double omega){
  double c = mass*omega/hbar;
  double wavefunction [nbox];
  double E_n = hbar * omega * (nlevel+0.5);

  //example of test
  if(fabs(std::hermite(3, 10.) - H3(10.)) + fabs(std::hermite(4, 4.3) - H4(4.3)) > 1e-10){
    std::cerr << "Hermite polynomials not correctly implemented: "
    << fabs(std::hermite(3, 10.) - H3(10.)) + fabs(std::hermite(4, 4.3) - H4(4.3)) <<std::endl;
    exit;
  }

  for(int i=0; i<nbox; i++){
    double x = (- nbox/2 + i) * dx;
    wavefunction[i] = sqrt(1/pow(2,nlevel) / factorial(nlevel) * sqrt(1/pi) )
                    * exp(-c/2. * x*x) * std::hermite(nlevel,sqrt(c)*x);
    //remember to translate by half box length, eventually
    std::cout << x << " " << wavefunction[i] << std::endl;
  }


}
