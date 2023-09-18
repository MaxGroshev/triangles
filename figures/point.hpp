#ifndef POINT_HPP
#define POINT_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>

#include "../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

const int count_of_dementions = 3;

//-----------------------------------------------------------------------------------------

struct point_t {
    //Fields
    double x = NAN;
    double y = NAN;
    double z = NAN;

    //Methods
    //Constructor & destructor
    explicit point_t() {};
    explicit point_t(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {
        std::cout << "Hello from point constructor\n";
    };
    virtual ~point_t() {};

    inline bool is_valid() const {return !(x != x || y != y || z != z);};
    inline void print()    const
    {std::cout << "Point:  " << "(" << x << ';' << y << ';' << z << ")\n";};
};

#endif
