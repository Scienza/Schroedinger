#include "ContinuousBase.h"

#include <utility>


ContinuousBase::ContinuousBase(std::vector<double> coords) { this->coords = std::move(coords); }

ContinuousBase::ContinuousBase(double mesh, unsigned int nbox) {
    this->start = -(nbox / 2.) * mesh;
    this->end   = (nbox / 2.) * mesh;

    if (end - start <= 0) {
        throw std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->mesh   = mesh;
    this->nbox   = nbox;
    this->coords = evaluate();
}

ContinuousBase::ContinuousBase(double start, double end, double mesh) {
    if (end - start <= 0) {
        throw std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->start  = start;
    this->end    = end;
    this->mesh   = mesh;
    this->nbox   = static_cast<unsigned int>((end - start) / mesh);
    this->coords = evaluate();
}

ContinuousBase::ContinuousBase(double start, double end, unsigned int nbox) {
    if (end - start <= 0) {
        throw std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->start  = start;
    this->end    = end;
    this->mesh   = (end - start) / nbox;
    this->nbox   = nbox;
    this->coords = evaluate();
}

std::vector<double> ContinuousBase::evaluate() {
    std::vector<double> coord;
    for (int i = 0; i <= this->nbox; i++) {
        coord.push_back(this->start + (this->mesh * i));
    }
    return coord;
}
