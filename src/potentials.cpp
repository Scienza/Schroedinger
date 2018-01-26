/* potential function defines the potential in function of position */
double potential(double x) {
  double value = x * x;
  return value;
} // end of function to evaluate

double ho_potential(double x) {
  return x*x;
} // end of function to evaluate

double box_potential(double x) {
  return 0.;
}

double finite_well_potential(double x) {
  double width = 3., height = 10.;

  if(x < -width){
    return height;
  }else if(x > - width && x < width){
    return 0.;
  }else{
    return height;
  }
}
