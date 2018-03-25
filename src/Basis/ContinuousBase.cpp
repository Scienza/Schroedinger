#include "Base.h"

Base::ContinuousBase::ContinuousBase(double mesh, unsigned int nbox)
{
    //constant mesh, symmetrical box
    this-> start = - (nbox/2.) * mesh;
    this-> end   =   (nbox/2.) * mesh;
    this-> mesh  = mesh;
    this-> nbox  = nbox;

    if( end - start <= 0){
        std::invalid_argument("CountinousBase starting-end = 0");
    }

    this->coord.reserve(nbox);
    for(std::vector<double>::size_type i = 0; i < nbox; i++)
        this->coord.push_back(start + mesh * i);
}


Base::ContinuousBase::ContinuousBase(double start, double end, double mesh)
{

    if( end - start <= 0){
        std::invalid_argument("CountinousBase end - starting < 0");
    }

    //constant mesh
    unsigned int nbox = (unsigned int)( (end-start)/mesh );

    this-> start = start;
    this-> end   = end;
    this-> mesh  = mesh;
    this-> nbox  = nbox;

    this->coord.reserve(nbox);
    for(std::vector<double>::size_type i = 0; i < nbox; i++)
        this->coord.push_back(start + mesh * i);
}


Base::ContinuousBase::ContinuousBase(double start, double end, unsigned int nbox)
{
    if( end - start <= 0){
        std::invalid_argument("CountinousBase starting-end = 0");
    }
    //constant mesh
    double mesh = (end-start)/nbox;

    this-> start = start;
    this-> end   = end;
    this-> mesh  = mesh;
    this-> nbox  = nbox;

    this->coord.reserve(nbox);
    for(std::vector<double>::size_type i = 0; i < nbox; i++)
        this->coord.push_back(start + mesh * i);
}