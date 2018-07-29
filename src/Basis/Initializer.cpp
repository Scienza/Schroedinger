//
// Created by Andrea Idini on 2018-07-29.
//

#include "Initializer.h"


initializer::initializer(double mesh, unsigned int nbox)
{
    if (end - start <= 0) {
        std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->start  = -(nbox / 2.) * mesh;
    this->end	 = (nbox / 2.) * mesh;
    this->mesh   = mesh;
    this->nbox   = nbox;
}


initializer::initializer(double start, double end, unsigned int nbox)
{
    if (end - start <= 0) {
        std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->start = start;
    this->end = end;
    this->mesh = (end - start) / nbox;
    this->nbox = nbox;
}


initializer::initializer(double start, double end, double mesh)
{
    if (end - start <= 0) {
        std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->start = start;
    this->end = end;
    this->mesh = mesh;
    this->nbox = (unsigned int)((end - start) / mesh);
}
