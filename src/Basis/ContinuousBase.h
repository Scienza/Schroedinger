#ifndef CONTINUOUSBASE_H
#define CONTINUOUSBASE_H

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class ContinuousBase {
  private:
    double start, end, mesh, nbox;
    std::vector<double> coords;
    std::vector<double> evaluate();

  public:
    std::vector<double> getCoords();
    ContinuousBase();
    ContinuousBase(std::vector<double> coords);
    ContinuousBase(double, unsigned int);
    ContinuousBase(double, double, double);
    ContinuousBase(double, double, unsigned int);
};

#endif