#ifndef VECTOR_HPP
#define VECTOR_HPP

//-----------------------------------------------------------------------------------------

#include "./point.hpp"

//-----------------------------------------------------------------------------------------

namespace geom_figures {

struct vector_t {
    //Fields
    double a = NAN;
    double b = NAN;
    double c = NAN;

    //Methods
    //Constructor & destructor
    explicit vector_t() {};
    explicit vector_t(const point_t& point1, const point_t& point2);
    virtual ~vector_t() {};

    int      set_vector(const point_t& point1, const point_t& point2);
    double   find_angle(const vector_t& vector) const;
    vector_t cross_product(const vector_t& vector) const;
    double   dot_product(const vector_t& vector) const;
    double   squared_len() const {return (a * a + b * b + c * c);};
    void     print() const {
    std::cout << "Vector: "<< "(" << a << ';' << b << ';' << c << ")\n";}
};

}
#endif
