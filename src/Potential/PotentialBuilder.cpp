#include "Potential.h"

Potential::Builder::Builder(std::vector<double> x_new)
{
    this->x = x_new;
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

Potential::Builder Potential::Builder::setType(std::string type)
{
    if (!type.empty()) {
        this->type = type;
        return *this;
    }
    else throw std::invalid_argument("Empty type given as parameter.");
}

Potential Potential::Builder::build(){
    try {
        return Potential(this->x,this->type,this->k,this->width,this->height);
    }
    catch(const std::invalid_argument& e){
        throw;
    }
}

// Potential::Builder Potential::Builder::setBase(Base b)
// {
//     this->base = b;
// }
