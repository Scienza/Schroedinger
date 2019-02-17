#include "Potential.h"

Potential::Builder::Builder(Base b)
{
    this->base = b;
}

Potential::Builder::Builder(std::string filename) 
{
    this->fromFile = true;

    std::string row;
    std::ifstream potentialfile(filename);
    try {
        std::vector<double> baseCoords;
        std::vector<double> potentialValues;
        double singleBaseCoord, singlePotentialValue;

        while(std::getline(potentialfile, row)) {
            std::istringstream rowStreamer(row);
            rowStreamer >> singleBaseCoord >> singlePotentialValue;
        
            baseCoords.push_back(singleBaseCoord);
            this->potentialValues.push_back(singlePotentialValue);
        }

        this->base = Base(baseCoords);
    }
    catch (const std::ifstream::failure& e) {
        std::cout << "Exception opening/reading file";
    }
}

Potential::Builder Potential::Builder::setK(double k_new)
{
    if (!this->fromFile) {
        this->k = k_new;
        return *this;
    }
}

Potential::Builder Potential::Builder::setWidth(double width_new)
{
    if (!this->fromFile) {
        if (width_new >= 0) {
            this->width = width_new;
            return *this;
        }
        else throw std::invalid_argument("Width parameter cannot be negative.");
    }
}

Potential::Builder Potential::Builder::setHeight(double height_new)
{
    if (!this->fromFile) {
        this->height = height_new;
        return *this;
    }
}

Potential::Builder Potential::Builder::setType(PotentialType type)
{   
    if (!this->fromFile) {
        this->type = type;
        return *this;
    }
}

Potential::Builder Potential::Builder::setSeparable(bool separable)
{
    if (!this->fromFile) {
        this->separable = separable;
        return *this;
    }
}


Potential::Builder Potential::Builder::setBase(Base b) {
    if (!this->fromFile) {
        this->base = b;
        return *this;
    }
 }
 
Potential Potential::Builder::build(){
    if (!this->fromFile) {
        return Potential(this->base,this->type,this->k,this->width,this->height, this->separable);
    }
    else {
        return Potential(this->base, this->potentialValues);
    }
}
