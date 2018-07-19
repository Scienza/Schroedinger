#include "Base.h"

DiscreteBase::DiscreteBase(int start, int end, int step)
{
    //if not integer division of the basis
    if( (end-start)/step % 1 != 0)
        throw std::invalid_argument("invalid discrete basis given (check interval and step).");

    if( (end-start)/step < 1)
        throw std::invalid_argument("invalid discrete basis given (check interval and step).");


    unsigned int base_value = (end-start)/step;
    if (base_value == 0)
        throw std::invalid_argument("Empty dimensions basis given.");

    this-> start = start;
    this-> end   = end;
    this-> step  = step;

    this-> quantum_numbers.reserve(base_value);
    int j=0;
    for(int i = start; i < end; i+=step ) {
        this->quantum_numbers[j] = i;
        j++;
    }
}
