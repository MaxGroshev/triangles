#ifndef PLANE_HPP
#define PLANE_HPP

//-----------------------------------------------------------------------------------------

#include "./vector.hpp"
#include "./line.hpp"
#include "./linear_algebra.hpp"
#include "../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

enum pos_of_the_planes {
    PLANES_PARALLEL   = 0,
    PLANES_COINCIDE   = 1,
    PLANES_CROSSES    = 2,
};

struct plane_t {
    //Fields
    double A = NAN;
    double B = NAN;
    double C = NAN;
    double D = NAN;

    //Methods
    //Constructor & destructor
    explicit plane_t() {};
    explicit plane_t(const point_t& point1, const point_t& point2, const point_t& point3);
    virtual ~plane_t() {};

    int  set_plane(const point_t& point1, const point_t& point2, const point_t& point3);
    int  def_pos_of_planes(const plane_t& plane) const;

    point_t find_point_of_intersection(const line_t& line) const;

    friend double find_det(const vector_t& vec1, const vector_t& vec2, const vector_t& vec3);
    void print();
};

//-----------------------------------------------------------------------------------------
//
// Ax + By + Cz + D = 0 - equation of plane
//
//-----------------------------------------------------------------------------------------

plane_t::plane_t(const point_t& point1, const point_t& point2,
                                        const point_t& point3) {
    ASSERT (point1.is_valid() && point2.is_valid() && point3.is_valid());

    vector_t vec_v(point1, point2);
    vector_t vec_w(point1, point3);

    A =  (vec_v.b * vec_w.c) - (vec_w.b * vec_v.c);
    B = -((vec_v.a * vec_w.c) - (vec_w.a * vec_v.c));
    C =  (vec_v.a * vec_w.b) - (vec_w.a * vec_v.b);
    D = A * (-point1.x) + B * (-point1.y) + C * (-point1.z);
}

int plane_t::set_plane(const point_t& point1, const point_t& point2,
                                              const point_t& point3) {
    ASSERT (point1.is_valid() && point2.is_valid() && point3.is_valid());

    vector_t vec_v(point1, point2);
    vector_t vec_w(point1, point3);

    A =   (vec_v.b * vec_w.c) - (vec_w.b * vec_v.c);
    B = -((vec_v.a * vec_w.c) - (vec_w.a * vec_v.c));
    C =   (vec_v.a * vec_w.b) - (vec_w.a * vec_v.b);
    D = A * (-point1.x) + B * (-point1.y) + C * (-point1.z);

    return 0;
}

//-----------------------------------------------------------------------------------------

int plane_t::def_pos_of_planes(const plane_t& plane) const {
    double coef_A = A / plane.A;
    double coef_B = B / plane.B;
    double coef_C = C / plane.C;

    if (coef_A == coef_B && coef_B == coef_C) {
        if (D / plane.D) {
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
    double param = -((A * line.point_on_line.x) +
                     (D * line.point_on_line.y) +
                     (C * line.point_on_line.y) + D);

    param /= ((A * line.dir_vector.a) +
              (B * line.dir_vector.b) +
              (C * line.dir_vector.c));

    point_t point (line.dir_vector.a * param + line.point_on_line.x,
                   line.dir_vector.b * param + line.point_on_line.y,
                   line.dir_vector.c * param + line.point_on_line.z);

    return point;
}

//-----------------------------------------------------------------------------------------

void plane_t::print() {
    std::cout << '(' << A << ';' << B << ';' << C << ") - normal vector of plane\n";
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
