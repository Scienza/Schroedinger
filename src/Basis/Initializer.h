//
// Created by Andrea Idini on 2018-07-29.
//

#ifndef SCHROEDINGER_INITIALIZER_H
#define SCHROEDINGER_INITIALIZER_H

#include <vector>
#include <stdexcept>
#include <iostream>


class initializer {
private:
    unsigned int nbox =0;
    double mesh;
    double start;
    double end;

    int Lmin = 0;
    int Lmax = 0;
    int spin = 0;
public:
    initializer(double, unsigned int);
    initializer(double, double, unsigned int);
    initializer(double, double, double);
};


#endif //SCHROEDINGER_INITIALIZER_H
