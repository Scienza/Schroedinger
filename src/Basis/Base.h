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

    std::vector<double> get_continuous(){
      return this->x.coord;
    }

    int get_dim(){
      return dimNum;
    }

    // avoid copy; public for better error handling
    Base(const Base&)            = delete;
    void operator= (const Base&) = delete;

protected:
    // private Constructor, called just once
    Base(int dimNum = 1) {
        double start=-5., end=5., mesh=0.01;
        baseType t = baseType::Cartesian; //TODO: Improve baseType to allow choice in input
        this->dimNum = dimNum;

        switch(t){
          case 0  : std::cout << "Initializing Cartesian Basis" << std::endl;
                    break;
          case 1  : std::cout << "Initializing Spherical Basis" << std::endl;
                    break;
          case 2  : std::cout << "Initializing Cylindrical Basis" << std::endl;
                    break;
          default : throw std::invalid_argument("Wrong basis type or initialization meaningless!");
        }
        ContinuousBase coord(start,end,mesh);
        this->x = coord;
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
