#include "../include/potentials.h"

class potential {
public:
  // attributes
  std::vector<double> x;
  std::vector<double> v;
  std::string pot_name;

  // methods
  potential(std::vector<double> coord);
//  potential(std::vector<double> coord, std::string name);
  potential(std::vector<double> coord, std::string name, double k);

/* potential function defines the potential in function of position */
//double potential(double x) {
//  double value = x * x;
//  return value;
//} // end of function to evaluate
};

//initialize the default potential (ho, 0.5 strength)
potential::potential(std::vector<double> coord){
  potential(coord, "ho", 0.5);
}

potential::potential(std::vector<double> coord, std::string name, double k){
  std::transform(name.begin(), name.end(), name.begin(),::tolower); //make pot_name lowercase
  pot_name = name;
  x = coord;
  v = x; //

  if (pot_name == "harmonic oscillator" || pot_name == "ho" || pot_name == "1"){
    for(std::vector<int>::size_type i = 0; i < x.size(); i++) {
      v[i] = x[i]*x[i]*k;
    }
  }

}

double ho_potential(double x) {
  return x*x/2.;
}

double box_potential(double x) {
  return 0.0;
}

double finite_well_potential(double x) {
  const  double width = 5.0;
  const  double height = 10.0;
  return (x > -width/2. && x < width/2.) ? 0.0 : height;
}
