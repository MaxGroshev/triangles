#ifndef VECTOR_HPP
#define VECTOR_HPP

//-----------------------------------------------------------------------------------------

#include "./point.hpp"
#include "../../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

struct vector_t {
    //Fields
    double a = NAN;
    double b = NAN;
    double c = NAN;

    //Methods
    //Constructor & destructor
    explicit vector_t() {};
    inline explicit vector_t(const point_t& point1, const point_t& point2);
    virtual ~vector_t() {};

    inline int      set_vector(const point_t& point1, const point_t& point2);
    inline double   find_angle(const vector_t& vector) const;
    inline vector_t cross_product(const vector_t& vector) const;
    inline double   dot_product(const vector_t& vector) const;
    inline double   squared_len() const {return (a * a + b * b + c * c);};
    inline void     print() const {
    std::cout << "Vector: "<< "(" << a << ';' << b << ';' << c << ")\n";}
};

//-----------------------------------------------------------------------------------------
//
// (a; b; c) - coordinates of vector
//
//-----------------------------------------------------------------------------------------

vector_t::vector_t(const point_t& point1, const point_t& point2) {
    ASSERT (point1.is_valid() && point2.is_valid());

    a = point2.x - point1.x;
    b = point2.y - point1.y;
    c = point2.z - point1.z;
}

int vector_t::set_vector(const point_t& point1, const point_t& point2) {
    ASSERT (point1.is_valid() && point2.is_valid());

    a = point2.x - point1.x;
    b = point2.y - point1.y;
    c = point2.z - point1.z;

    return 0;
}

vector_t vector_t::cross_product(const vector_t& vector) const {
    vector_t res;
    res.a =   (b * vector.c) - (c * vector.b);
    res.b = -((a * vector.c) - (c * vector.b));
    res.c =   (a * vector.b) - (b * vector.a);

    return res;
}

double vector_t::dot_product(const vector_t& vector) const {
    return (a * vector.a + b* vector.b + c * vector.c);
}

double vector_t::find_angle(const vector_t& vector) const {
    double abs_dot = my_abs(dot_product(vector));
    double squred_len_this  = squared_len();
    double squared_len_vect = vector.squared_len();

    return (abs_dot / (sqrt(squred_len_this) * sqrt(squared_len_vect)));
}

#endif
