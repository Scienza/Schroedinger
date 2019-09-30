#include <utility>

#include "LogManager.h"
#include "Potential.h"

Potential::Builder::Builder(Base b) : base(std::move(b)) {}

Potential::Builder::Builder(const std::string& filename, Base base) {
    this->fromFile = true;

    std::string row;
    std::ifstream potentialfile(filename);
    try {
        std::vector<double> potentialValues;
        double singlePotentialValue;

        while (std::getline(potentialfile, row)) {
            std::istringstream rowStreamer(row);
            rowStreamer >> singlePotentialValue;
            potentialValues.push_back(singlePotentialValue);
        }
        this->values.push_back(potentialValues);
        this->base = base;
    } catch (const std::ifstream::failure& e) {
        S_ERROR("Exception opening/reading file: {}", e.what());
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

Potential::Builder Potential::Builder::setBase(Base b) {
    if (this->fromFile) {
        throw std::invalid_argument("Cannot read options from file");
    }

    this->base = std::move(b);
    return *this;
}

Potential Potential::Builder::build() {
    if (!this->fromFile) {
        return Potential(this->base, this->type, this->k, this->width, this->height);
    }

    return Potential(this->base, this->values);
}
