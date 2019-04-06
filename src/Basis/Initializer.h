#ifndef SCHROEDINGER_INITIALIZER_H
#define SCHROEDINGER_INITIALIZER_H

#include <iostream>
#include <stdexcept>
#include <vector>

class Initializer {
  public:
    Initializer(){};
};

class DiscreteInitializer : public Initializer {
  public:
    int min, max, step;
    unsigned int base_value;
    DiscreteInitializer() = default;
    DiscreteInitializer(int, int, int);
};

class ContinuousInitializer : public Initializer {
  public:
    double start, end, mesh;
    unsigned int nbox;

    ContinuousInitializer() = default;
    ContinuousInitializer(double, unsigned int);
    ContinuousInitializer(double, double, double);
    ContinuousInitializer(double, double, unsigned int);
};

class SphericalInitializer : public virtual ContinuousInitializer {
  public:
    int Lmin  = 0;
    int Lmax  = 0;
    int Lstep = 1;
    int spin  = 0;

    // todo: check start = 0, end > 0... might be needed new set of constructors :(
    SphericalInitializer(...){};
};

#endif  // SCHROEDINGER_INITIALIZER_H
