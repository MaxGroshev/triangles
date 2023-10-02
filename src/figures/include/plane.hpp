#ifndef PLANE_HPP
#define PLANE_HPP

//-----------------------------------------------------------------------------------------

#include "vector.hpp"
#include "line.hpp"

//-----------------------------------------------------------------------------------------

namespace geom_figures {

enum class pos_of_the_planes {
    PARALLEL = 0,
    COINCIDE = 1,
    CROSSES  = 2,
};

struct plane_t {
    //Fields
    vector_t norm_vector;
    point_t  point_in_plane;
    double D = NAN;

    //Methods
    //Constructor & destructor
    explicit plane_t() {};
    explicit plane_t(const point_t& point1, const point_t& point2,
                                            const point_t& point3);
    int set_plane(const point_t& point1, const point_t& point2, const point_t& point3);

    pos_of_the_planes def_pos_of_planes(const plane_t& plane) const;
    bool is_point_in_plane(const point_t& point) const;
    point_t find_point_of_intersection(const line_t& line) const;

    friend double find_det(const vector_t& vec1, const vector_t& vec2,
                                                 const vector_t& vec3);
    void print() const ;
};


}
#endif
