#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

//-----------------------------------------------------------------------------------------

#include <array>

#include "./plane.hpp"

//-----------------------------------------------------------------------------------------

namespace geom_figures {

const int count_of_triangle_vertices = 3;

//-----------------------------------------------------------------------------------------

class triangle_t {
    public:
        std::array<point_t, count_of_triangle_vertices> vertices;
        bool intersected = false;

        line_t  side_a;
        line_t  side_b;
        line_t  side_c;
        plane_t plane;
    public:
        //Constructor & destructor
        explicit triangle_t() {};
        explicit triangle_t(const point_t& point1, const point_t& point2,
                                                          const point_t& point3);

        int  set(const point_t& point1, const point_t& point2, const point_t& point3);
        bool point_in_triangle(const point_t& point) const;
        bool intersect_status() const {return intersected;};
        void set_intersect_status(bool val) {intersected = val;};
        bool intersect_in_same_plane(const triangle_t& trian) const;
        bool intersect(const triangle_t& trian) const;
        void print() const;
};

}
#endif
