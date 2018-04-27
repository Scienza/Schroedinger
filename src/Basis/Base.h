#ifndef BASE_H
#define BASE_H

#include <vector>
#include <stdexcept>
#include <iostream>

class Base
{
public:
    static Base& get_instance(){
      static Base instance;
      return instance;
    }

    enum baseType {Spherical,Cylindrical,Cartesian};
    int dimNum;

    // avoid copy; public for better error handling
    Base(const Base&)       = delete;
    void operator= (const Base&) = delete;

protected:
    // private Constructor
    Base() {};

    class DiscreteBase {
    private:
        int start;
        int end;
        int step;
    public:
        DiscreteBase(int, int, int);
        std::vector<int> quantum_numbers;
    };

    class ContinuousBase {
    private:
        double start;
        double end;
        double mesh;
        unsigned int nbox;
    public:
        ContinuousBase(double, unsigned int);
        ContinuousBase(double, double, double);
        ContinuousBase(double, double, unsigned int);

        std::vector<double> coord;
    };

};

#endif
