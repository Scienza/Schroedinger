#ifndef BASE_H
#define BASE_H

#include <vector>
#include <stdexcept>
#include <iostream>

class Base;

class Base
{
public:
    static Base& get_instance(){
      static Base instance;
      return instance;
    }

    auto get_continuous(){
      return this->x;
    }

    int get_dim(){
      return dimNum;
    }

    // avoid copy; public for better error handling
    Base(const Base&)            = delete;
    void operator= (const Base&) = delete;

protected:
    // private Constructor, called just once
    // Base(int);
    Base(int dimNum = 1);

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
        ContinuousBase();
        ContinuousBase(double, unsigned int);
        ContinuousBase(double, double, double);
        ContinuousBase(double, double, unsigned int);

        std::vector<double> coord;
    };

private:
    enum baseType {Cartesian = 0, Spherical = 1, Cylindrical = 2};
    int dimNum;
    ContinuousBase x;
};

#endif
