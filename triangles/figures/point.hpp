#ifndef POINT_HPP
#define POINT_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>

#include "../my_math/my_math_func.hpp"
#include "../../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

const int count_of_dementions = 3;
const double calculation_error = 0.02;

//-----------------------------------------------------------------------------------------

struct point_t {
    //Fields
    double x = NAN;
    double y = NAN;
    double z = NAN;

    //Methods
    //Constructor & destructor
    explicit point_t() {};
    explicit point_t(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};
    virtual ~point_t() {};

    inline void set_point (double x_, double y_, double z_) {x = x_; y = y_; z = z_;};
    inline bool is_valid() const {return !(x != x || y != y || z != z);};
    inline void print()    const
    {std::cout << "Point:  " << "(" << x << ';' << y << ';' << z << ")\n";};
};

#endif
