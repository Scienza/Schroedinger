#include "Initializer.h"

// ContinuousInitializer //
ContinuousInitializer::ContinuousInitializer(double mesh, unsigned int nbox) {
    if (end - start <= 0) {
        std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->start = -(nbox / 2.) * mesh;
    this->end   = (nbox / 2.) * mesh;
    this->mesh  = mesh;
    this->nbox  = nbox;
}

ContinuousInitializer::ContinuousInitializer(double start, double end, unsigned int nbox) {
    if (end - start <= 0) {
        std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->start = start;
    this->end   = end;
    this->mesh  = (end - start) / nbox;
    this->nbox  = nbox;
}

ContinuousInitializer::ContinuousInitializer(double start, double end, double mesh) {
    if (end - start <= 0) {
        std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->start = start;
    this->end   = end;
    this->mesh  = mesh;
    this->nbox  = static_cast<unsigned int>((end - start) / mesh);
}

// DiscreteInitializer //
DiscreteInitializer::DiscreteInitializer(int start, int end, int step) {
    if ((end - start) / step % 1 != 0) {
        throw std::invalid_argument("invalid discrete basis given (check interval and step).");
    }

    if ((end - start) / step < 1) {
        throw std::invalid_argument("invalid discrete basis given (check interval and step).");
    }

    if ((end - start) / step == 0) {
        throw std::invalid_argument("Empty dimensions basis given.");
    }

    this->base_value = (end - start) / step;
    this->min        = start;
    this->max        = end;
    this->step       = step;
}