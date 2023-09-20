#ifndef LINE_HPP
#define LINE_HPP

//-----------------------------------------------------------------------------------------

#include "./vector.hpp"
#include "../debug_utils/error_control.h"

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

//-----------------------------------------------------------------------------------------
//
// dir_vactor    - direction vector of line
// point_on_line - coordinates of point on the line
//
//-----------------------------------------------------------------------------------------

line_t::line_t(const point_t& point1, const point_t& point2) {
    ASSERT (point1.is_valid() && point2.is_valid());

    point_on_line = point1;
    dir_vector.set_vector (point1, point2);
}

int line_t::set_line(const point_t& point1, const point_t& point2) {
    ASSERT (point1.is_valid() && point2.is_valid());

    point_on_line = point1;
    dir_vector.set_vector (point1, point2);

    return 0;
}

#endif
