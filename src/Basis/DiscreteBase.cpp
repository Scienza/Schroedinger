#include "DiscreteBase.h"

DiscreteBase::DiscreteBase(int start, int end, int step) {
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
    this->start      = start;
    this->end        = end;
    this->step       = step;
    this->coords     = evaluate();
}

std::vector<int> DiscreteBase::evaluate() {
    std::vector<int> quantum_numbers;
    quantum_numbers.reserve(this->base_value);
    for (int i = this->start; i < this->end; i += this->step) {
        quantum_numbers.push_back(i);
    }
    return quantum_numbers;
}
