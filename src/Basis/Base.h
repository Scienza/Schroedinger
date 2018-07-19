#ifndef BASE_H
#define BASE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <DiscreteBase.h>
#include <ContinuousBase.h>

class Base;

class Base
{
public:
	enum baseType { Cartesian = 0, Spherical = 1, Cylindrical = 2 };
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


private:
    int dimNum;
    ContinuousBase x;
};

#endif
