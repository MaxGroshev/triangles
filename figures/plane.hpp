#ifndef PLANE_HPP
#define PLANE_HPP

//-----------------------------------------------------------------------------------------

#include "./vector.hpp"
#include "./line.hpp"
#include "../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

struct plane_t {
    //Fields
    point_t  point_on_plane;
    vector_t vector_v;
    vector_t vector_w;

    //Methods
    //Constructor & destructor
    explicit plane_t() {};
    explicit plane_t(const point_t& point1, const point_t& point2,
                                            const point_t& point3);
    virtual ~plane_t() {};

    int set_plane(const point_t& point1, const point_t& point2,
                                         const point_t& point3);
    void print();
};

//-----------------------------------------------------------------------------------------
//
// point_on_plane     - coordinates of point on the line
// vector_v, vector_w - vectors defining the plane
//
//-----------------------------------------------------------------------------------------

plane_t::plane_t(const point_t& point1, const point_t& point2,
                                        const point_t& point3) {
    ASSERT (point1.is_valid() && point2.is_valid() && point3.is_valid());

    point_on_plane = point1;
    vector_v.set_vector(point1, point2);
    vector_w.set_vector(point1, point3);
}

int plane_t::set_plane(const point_t& point1, const point_t& point2,
                                              const point_t& point3) {
    ASSERT (point1.is_valid() && point2.is_valid() && point3.is_valid());

    point_on_plane = point1;
    vector_v.set_vector(point1, point2);
    vector_w.set_vector(point1, point3);

    return 0;
}

void plane_t::print() {
    point_on_plane.print ();
    vector_v.print();
    vector_w.print();
}

#endif
