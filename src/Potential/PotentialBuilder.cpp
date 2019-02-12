#include "Potential.h"

Potential::Builder::Builder(Base b)
{
    this->base = b;
}

Potential::Builder Potential::Builder::setK(double k_new)
{
    this->k = k_new;
    return *this;
}

Potential::Builder Potential::Builder::setWidth(double width_new)
{
    if (width_new >= 0) {
        this->width = width_new;
        return *this;
    }
    else throw std::invalid_argument("Width parameter cannot be negative.");
}

Potential::Builder Potential::Builder::setHeight(double height_new)
{
    this->height = height_new;
    return *this;
}

Potential::Builder Potential::Builder::setType(PotentialType type)
{   
    this->type = type;
    return *this;
}

Potential::Builder Potential::Builder::setSeparable(bool separable)
{
    this->separable = separable;

}

Potential Potential::Builder::build(){
    try {
        return Potential(this->base,this->type,this->k,this->width,this->height, this->separable);
    }
    catch(const std::invalid_argument& e){
        throw;
    }
}

Potential::Builder Potential::Builder::setBase(Base b) {
     this->base = b;
 }
