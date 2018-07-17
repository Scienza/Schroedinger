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

    // avoid copy; public for better error handling
    Base(const Base&)       = delete;
    void operator= (const Base&) = delete;

protected:
    // private Constructor
    Base(int dimNum = 1) {
        double start=0, end=0, mesh=0.1;
        baseType t = Cartesian; //TODO: Improve baseType
        this->dimNum = dimNum;

        switch(t){
          case baseType::Cartesian  : std::cout << "Initializing Cartesian Basis" << std::endl;
          case baseType::Spherical  : std::cout << "Initializing Spherical Basis" << std::endl;
          case baseType::Cylindrical: std::cout << "Initializing Cartesian Basis" << std::endl;

          default                   : throw std::invalid_argument("Wrong basis type or initialization meaningless!");
        }
        ContinuousBase x(start,end,mesh);
    };

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
private:
    enum baseType {Cartesian = 0, Spherical = 1, Cylindrical = 2};
    int dimNum;

};

#endif
