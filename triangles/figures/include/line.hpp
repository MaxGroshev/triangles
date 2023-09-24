#ifndef LINE_HPP
#define LINE_HPP

//-----------------------------------------------------------------------------------------

#include "./vector.hpp"

//-----------------------------------------------------------------------------------------

struct line_t {
    //Fields
    vector_t dir_vector;
    point_t  point_on_line;

    //Methods
    //Constructor & destructor
    explicit line_t  () {};
    explicit line_t  (const point_t& point1, const point_t& point2);
    virtual ~line_t  () {};

    int set_line(const point_t& point1, const point_t& point2);
};

#endif
