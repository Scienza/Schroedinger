/* potential function defines the potential in function of position */
double potential(double x) {
  double value = x * x;
  return value;
} // end of function to evaluate

double ho_potential(double x) {
  return x*x;
}

double box_potential(double x) {
  return 0.0;
}

double finite_well_potential(double x) {
  const  double width = 3.0;
  const  double height = 10.0;
  return (x > -width/2. && x < width/2.) ? 0.0 : height;
}
