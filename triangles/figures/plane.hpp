#ifndef PLANE_HPP
#define PLANE_HPP

//-----------------------------------------------------------------------------------------

#include "./vector.hpp"
#include "./line.hpp"
#include "../../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

enum pos_of_the_planes {
    PLANES_PARALLEL   = 0,
    PLANES_COINCIDE   = 1,
    PLANES_CROSSES    = 2,
};

struct plane_t {
    //Fields
    vector_t norm_vector;
    double D = NAN;

    //Methods
    //Constructor & destructor
    inline explicit plane_t() {};
    inline explicit plane_t(const point_t& point1, const point_t& point2,
                                                   const point_t& point3);
    inline virtual ~plane_t() {};

    inline int  set_plane(const point_t& point1, const point_t& point2,
                                                 const point_t& point3);
    inline int  def_pos_of_planes(const plane_t& plane) const;

    inline point_t find_point_of_intersection(const line_t& line) const;

    inline friend double find_det(const vector_t& vec1, const vector_t& vec2,
                                                        const vector_t& vec3);
    inline void print() const ;
};

//-----------------------------------------------------------------------------------------
//
// Ax + By + Cz + D = 0 - equation of plane
// (a, b, c) - normal vector of plane
//
//-----------------------------------------------------------------------------------------

plane_t::plane_t(const point_t& point1, const point_t& point2,
                                        const point_t& point3) {
    ASSERT (point1.is_valid() && point2.is_valid() && point3.is_valid());

    vector_t vec_v(point1, point2);
    vector_t vec_w(point1, point3);

    norm_vector.a =  (vec_v.b * vec_w.c) - (vec_w.b * vec_v.c);
    norm_vector.b = -((vec_v.a * vec_w.c) - (vec_w.a * vec_v.c));
    norm_vector.c =  (vec_v.a * vec_w.b) - (vec_w.a * vec_v.b);
    D = norm_vector.a * (-point1.x) +
        norm_vector.b * (-point1.y) +
        norm_vector.c * (-point1.z);
}

int plane_t::set_plane(const point_t& point1, const point_t& point2,
                                              const point_t& point3) {
    ASSERT (point1.is_valid() && point2.is_valid() && point3.is_valid());

    vector_t vec_v(point1, point2);
    vector_t vec_w(point1, point3);

    norm_vector.a =  (vec_v.b * vec_w.c) - (vec_w.b * vec_v.c);
    norm_vector.b = -((vec_v.a * vec_w.c) - (vec_w.a * vec_v.c));
    norm_vector.c =  (vec_v.a * vec_w.b) - (vec_w.a * vec_v.b);
    D = norm_vector.a * (-point1.x) +
        norm_vector.b * (-point1.y) +
        norm_vector.c * (-point1.z);

    return 0;
}

//-----------------------------------------------------------------------------------------

int plane_t::def_pos_of_planes(const plane_t& plane) const {
    double angle_between = norm_vector.find_angle(plane.norm_vector);
    if (my_abs(angle_between - 1) < calculation_error) {
        if (D == plane.D) {
            return PLANES_COINCIDE;
        }
        return PLANES_PARALLEL;
    }
    return PLANES_CROSSES;
}

//-----------------------------------------------------------------------------------------
//
// find param to solve system of equations
// param /= (n , dir_vect) = 0 - case line in plane
//
//-----------------------------------------------------------------------------------------

point_t plane_t::find_point_of_intersection(const line_t& line) const {
    double param = -((norm_vector.a * line.point_on_line.x) +
                     (norm_vector.b * line.point_on_line.y) +
                     (norm_vector.c * line.point_on_line.z) + D);
    double dot   = norm_vector.dot_product(line.dir_vector);
    if (dot == 0) {
        point_t point {};
        return point;
    }
    param /=  dot;

    point_t point (line.dir_vector.a * param + line.point_on_line.x,
                   line.dir_vector.b * param + line.point_on_line.y,
                   line.dir_vector.c * param + line.point_on_line.z);

    return point;
}

//-----------------------------------------------------------------------------------------

void plane_t::print() const {
    std::cout << '(' << norm_vector.a << ';'
                     << norm_vector.b << ';'
                     << norm_vector.c << ") - normal vector of plane\n";
    std::cout << "D = " << D  << '\n';
}

//-----------------------------------------------------------------------------------------

double find_det(const vector_t& vec1, const vector_t& vec2, const vector_t& vec3) {
    double det1 = vec1.a * ((vec2.b * vec3.c) - (vec3.b * vec2.c));
    double det2 = vec2.a * ((vec1.b * vec3.c) - (vec3.b * vec1.c));
    double det3 = vec3.a * ((vec1.b * vec2.c) - (vec2.b * vec1.c));

    return (det1 - det2 + det3);
}

#endif
