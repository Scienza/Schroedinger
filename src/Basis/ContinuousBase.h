#ifndef CONTINUOUSBASE_H
#define CONTINUOUSBASE_H

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class ContinuousBase {
  public:
    ContinuousBase(std::vector<double> coords);
    ContinuousBase(double, unsigned int);
    ContinuousBase(double, double, double);
    ContinuousBase(double, double, unsigned int);

    const std::vector<double>& getCoords() const { return this->coords; }
    double getMesh() const noexcept { return this->mesh; }
    double getNbox() const noexcept { return this->nbox; }

  private:
    double start, end, mesh, nbox;
    std::vector<double> coords;
    std::vector<double> evaluate();
};

#endif