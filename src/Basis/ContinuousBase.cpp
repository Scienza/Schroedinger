#include "Base.h"

Base::ContinuousBase::ContinuousBase(double starting, double end, std::vector<double> mesh, unsigned int nbox)
{
    if (mesh.size() < 1 && nbox == 0)
        throw std::invalid_argument("Empty mesh given.");

//  TODO:correct in a way that you know at least one between mesh and nbox, and three defined arguments
//    if (starting = None)
//        throw std::invalid_argument("starting point not defined");
//    if(end-starting < 0.)
//        throw std::invalid_argument("Mesh boundaries not correctly specified");

    //constant mesh
    if (mesh.size() == 1){
        nbox = (unsigned int) (end-starting)/mesh[0];
    }
    else if(mesh.size() > 1){
        throw std::invalid_argument("non--constant mesh to be developed");
    }
//    else if(nbox != 0){
//
//    }

    this-> starting = starting;
    this-> end      = end;
    this-> mesh     = mesh;
    this-> nbox     = nbox;

    this->coord.reserve(nbox);
    for(std::vector<double>::size_type i = 0; i < coord.size(); i++)
        this->coord[i] = starting + mesh[0] * i;

}
