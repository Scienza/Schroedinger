 #ifndef POTENTIAL
#define POTENTIAL

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

 class Potential {
private:
    std::vector<double> x;
    std::vector<double> v;
    std::string pot_name;

    void ho_potential(double);
    void box_potential();
    void finite_well_potential();

public:
    Potential(std::vector<double>);
    Potential(std::vector<double>, std::string);
    Potential(std::vector<double>, std::string, double);
    Potential(std::vector<double>, std::string, double, double);

    std::vector<double> get_v();
};

#endif