#include"ContinuousBase.h"

//TODO: convert the arguments in class private properties
ContinuousBase::ContinuousBase(double starting, double end, std::vector<double> mesh, unsigned int nbox)
{
    if (mesh.size() < 1 && nbox == 0)
        throw std::invalid_argument("Empty mesh given.");

//  TODO:correct in a way that you know at least one between mesh and nbox, and three defined arguments
//    if (starting = None)
//        throw std::invalid_argument("starting point not defined");
//    if(end-starting < 0.)
//        throw std::invalid_argument("Mesh boundaries not correctly specified");


    if (mesh.size() == 1){
        //constant mesh
        nbox = (unsigned int) (end-starting)/mesh[0];

    }else if(mesh.size() > 1){
        throw std::invalid_argument("non--constant mesh to be developed");
    }
//    else if(nbox != 0){
//
//    }

    // Due to the fact that Basis->coords is vector<double>
    // here's the conversion from vector<int> to vector<double>
    this->coords.reserve(nbox);
    for(std::vector<double>::size_type i = 0; i < coords.size(); i++)
        this->coords[i][0] = starting + mesh[0] * i;

}
