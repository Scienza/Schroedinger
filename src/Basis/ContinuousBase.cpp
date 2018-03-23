#include "Base.h"

Base::ContinuousBase::ContinuousBase(double start, double end, double mesh)
{
    if( end - start == 0){
        std::invalid_argument("CountinousBase starting-end = 0");
    }
    //constant mesh
    unsigned int nbox = unsigned int( (end-start)/mesh );

    this-> start = start;
    this-> end   = end;
    this-> mesh  = mesh;
    this-> nbox  = nbox;

    this->coord.reserve(nbox);
    for(std::vector<double>::size_type i = 0; i < coord.size(); i++)
        this->coord[i] = start + mesh * i;

}


Base::ContinuousBase::ContinuousBase(double start, double end, unsigned int nbox)
{
    if( end - start == 0){
        std::invalid_argument("CountinousBase starting-end = 0");
    }
    //constant mesh
    double mesh = (end-start)/nbox;

    this-> start = start;
    this-> end   = end;
    this-> mesh  = mesh;
    this-> nbox  = nbox;

    this->coord.reserve(nbox);
    for(std::vector<double>::size_type i = 0; i < coord.size(); i++)
        this->coord[i] = start + mesh * i;

}

