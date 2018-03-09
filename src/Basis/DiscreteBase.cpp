#include "DiscreteBase.h"

DiscreteBase::DiscreteBase(int start, int end, int step)
{
    //if not integer division of the basis
    if((start-end)/step % 1 !=0)
        throw std::invalid_argument("invalid discrete basis given (check interval and step).");

    unsigned int base_value = (start-end)/step;
    if (base_value == 0)
        throw std::invalid_argument("Empty dimensions basis given.");

    this->quantum_numbers.reserve(base_value);

    int j=0;
    for(int i = start; i < end; i++ ) {
        this->quantum_numbers[j] = i;
        j++;
    }
}
