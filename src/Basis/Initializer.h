//
// Created by Andrea Idini on 2018-07-29.
//

#ifndef SCHROEDINGER_INITIALIZER_H
#define SCHROEDINGER_INITIALIZER_H

#include <vector>
#include <stdexcept>
#include <iostream>

class Initializer {
private:
    int id;

    virtual void setId();

public:
    Initializer();

    virtual const int &getId() const {
        return this->id;
    }

    // Overloading < operator due to "id" comparison used in std::map (ContinuousBase / DiscreteBase)
    friend bool operator<(const Initializer &b1, const Initializer &b2) {
        if (b1.getId() == b2.getId())
            return false;
        else return true;
    }
};

class DiscreteInitializer : public Initializer {
public:
    int min, max, step;
    unsigned int base_value;

    DiscreteInitializer() = default;
    DiscreteInitializer(int, int, int);
};

class ContinuousInizializer : public Initializer {
public:
    double start, end, mesh;
    unsigned int nbox;

    ContinuousInizializer() = default;
    ContinuousInizializer(double, unsigned int);
    ContinuousInizializer(double, double, double);
    ContinuousInizializer(double, double, unsigned int);
};

class SphericalInitializer : public virtual ContinuousInizializer {
public:
    int Lmin = 0;
    int Lmax = 0;
    int Lstep = 1;

    int spin = 0;

    // todo: check start = 0, end > 0... might be needed new set of constructors :(
    SphericalInitializer(...){};
};

#endif //SCHROEDINGER_INITIALIZER_H
