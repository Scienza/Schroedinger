#include <utility>

#include "LogManager.h"
#include "Potential.h"

Potential::Builder::Builder(Base b) { this->base = std::move(b); }

Potential::Builder::Builder(const std::string& filename) {
    this->fromFile = true;

    std::string row;
    std::ifstream potentialfile(filename);
    try {
        std::vector<double> baseCoords;
        std::vector<double> potentialValues;
        double singleBaseCoord, singlePotentialValue;

        while (std::getline(potentialfile, row)) {
            std::istringstream rowStreamer(row);
            rowStreamer >> singleBaseCoord >> singlePotentialValue;

            baseCoords.push_back(singleBaseCoord);
            this->potentialValues.push_back(singlePotentialValue);
        }

        this->base = Base(baseCoords);
    } catch (const std::ifstream::failure& e) {
        ERROR("Exception opening/reading file: {}", e.what());
    }
}

Potential::Builder Potential::Builder::setK(double k_new) {
    if (this->fromFile) {
        throw std::invalid_argument("Cannot read options from file");
    }

    this->k = k_new;
    return *this;
}

Potential::Builder Potential::Builder::setWidth(double width_new) {
    if (this->fromFile) {
        throw std::invalid_argument("Cannot read options from file");
    }

    if (width_new >= 0) {
        this->width = width_new;
        return *this;
    } else {
        throw std::invalid_argument("Width parameter cannot be negative.");
    }
}

Potential::Builder Potential::Builder::setHeight(double height_new) {
    if (this->fromFile) {
        throw std::invalid_argument("Cannot read options from file");
    }

    this->height = height_new;
    return *this;
}

Potential::Builder Potential::Builder::setType(PotentialType type) {
    if (this->fromFile) {
        throw std::invalid_argument("Cannot read options from file");
    }

    this->type = type;
    return *this;
}

Potential::Builder Potential::Builder::setSeparable(bool separable) {
    if (this->fromFile) {
        throw std::invalid_argument("Cannot read options from file");
    }

    this->separable = separable;
    return *this;
}

Potential::Builder Potential::Builder::setBase(Base b) {
    if (this->fromFile) {
        throw std::invalid_argument("Cannot read options from file");
    }

    this->base = std::move(b);
    return *this;
}

Potential Potential::Builder::build() {
    if (!this->fromFile) {
        return Potential(this->base, this->type, this->k, this->width, this->height,
                         this->separable);
    }

    return Potential(this->base, this->potentialValues);
}
