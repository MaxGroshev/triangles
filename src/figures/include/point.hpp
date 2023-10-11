#ifndef POINint_HPP
#define POINint_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>

#include "../../my_math/my_math_func.hpp"
#include "debug_utils.hpp"
#include "figures.hpp"

//-----------------------------------------------------------------------------------------

namespace geom_figures {

struct point_t {
    //Fields
    double x = NAN;
    double y = NAN;
    double z = NAN;

    //Methods
    //Constructor & destructor
    explicit point_t() {};
    explicit point_t(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};

    void set_point(double x_, double y_, double z_) {x = x_; y = y_; z = z_;};
    bool is_valid() const {return !(x != x || y != y || z != z);};
    void print()    const
    {std::cout << "Point:  " << "(" << x << ';' << y << ';' << z << ")\n";};
};

//repeating code: Use once in oct tree
struct oct_point_t {
    int x;
    int y;
    int z;

    explicit oct_point_t() {};
    explicit oct_point_t(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {};

    void set_point(int x_, int y_, int z_) {x = x_; y = y_; z = z_;};
    void print()    const
    {std::cout << "Point:  " << "(" << x << ';' << y << ';' << z << ")\n";};
};

}
#endif
