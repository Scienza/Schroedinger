#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include "ContinuousBase.h"
#include "DiscreteBase.h"

class Base {
  public:
    enum basePreset { Custom = 0, Cartesian = 1, Spherical = 2, Cylindrical = 3 };
    enum baseType { Radial = 0, Momentum = 1, Other = 2 };
    enum boundaryCondition { ZEROEDGE = 0, PERIODIC = 1 };

    Base() = default;
    Base(basePreset, int, std::vector<ContinuousBase>, std::vector<DiscreteBase>);
    Base(const std::vector<double>& coords);

    int getDim() const noexcept { return this->dimensions; };
    boundaryCondition getBoundary() const noexcept { return this->boundary; };
    const std::vector<ContinuousBase>& getContinuous() const noexcept { return this->continuous; };
    const std::vector<DiscreteBase>& getDiscrete() const noexcept { return this->discrete; };
    std::vector<double> getCoords() const;
    friend const Base operator+(const Base& base1, const Base& base2);
    std::string toString() const;

    Base& operator+=(const Base& base2);

  private:
    int dimensions             = 0;
    boundaryCondition boundary = ZEROEDGE;

    std::vector<DiscreteBase> discrete{};
    std::vector<ContinuousBase> continuous{};
};

#endif
