#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

//-----------------------------------------------------------------------------------------

#include <array>

#include "./plane.hpp"
#include "../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

const int coun_of_triangle_vertices = 3;

//-----------------------------------------------------------------------------------------

class triangle_t {
    private:
        std::array<point_t, coun_of_triangle_vertices> vertices;

        line_t  side_a;
        line_t  side_b;
        line_t  side_c;
        plane_t plane;
    public:
        //Constructor & destructor
        explicit triangle_t() {};
        inline explicit triangle_t(const point_t& point1, const point_t& point2,
                                                   const point_t& point3);
        virtual ~triangle_t() {};

        inline int  set(const point_t& point1, const point_t& point2, const point_t& point3);
        inline bool point_in_triangle(const point_t& point) const;
        inline bool crosses_in_same_plane(const triangle_t& trian) const;
        inline bool intersect  (const triangle_t& trian) const;
        inline void print();

};

//-----------------------------------------------------------------------------------------
//
// vertices - array of vertices of triangle
// plane    - the plane in which triangle lies
//
//-----------------------------------------------------------------------------------------

triangle_t::triangle_t(const point_t& point1, const point_t& point2,
                                              const point_t& point3) {
    ASSERT (point1.is_valid() && point2.is_valid() && point3.is_valid());

    vertices = {point1, point2, point3};

    side_a.set_line(point1, point2);
    side_b.set_line(point2, point3);
    side_c.set_line(point1, point3);

    plane.set_plane(point1, point2, point3);
}

int triangle_t::set(const point_t& point1, const point_t& point2, const point_t& point3) {
    ASSERT (point1.is_valid() && point2.is_valid() && point3.is_valid());

    vertices = {point1, point2, point3};

    side_a.set_line(point1, point2);
    side_b.set_line(point2, point3);
    side_c.set_line(point1, point3);

    plane.set_plane(point1, point2, point3);

    return 0;
}

//-----------------------------------------------------------------------------------------

bool triangle_t::intersect(const triangle_t& trian) const {
    std::array<point_t, coun_of_triangle_vertices> intersect_points;
    int pos_type = plane.def_pos_of_planes(trian.plane);

    if (pos_type == PLANES_PARALLEL) {
        return false;
    }
    else if (pos_type == PLANES_COINCIDE) {
        return crosses_in_same_plane(trian);
    }

    intersect_points[0] = plane.find_point_of_intersection(trian.side_a);
    intersect_points[1] = plane.find_point_of_intersection(trian.side_b);
    intersect_points[2] = plane.find_point_of_intersection(trian.side_c);

    for (int i = 0; i < coun_of_triangle_vertices; i++) {
        if (intersect_points[i].is_valid()) {
            if (point_in_triangle(intersect_points[i])) {
                return true;
            }
        }
    }

    return false;
}

bool triangle_t::crosses_in_same_plane(const triangle_t& trian) const { //TODO more general
    for (int i = 0; i < coun_of_triangle_vertices; i++) {
        if (trian.vertices[i].is_valid()) {
            bool in_triangle = point_in_triangle(trian.vertices[i]);
           // std::cout << in_triangle;
            if (in_triangle) {
                return true;
            }
        }
    }
    return false;
}

bool triangle_t::point_in_triangle(const point_t& point) const {
    vector_t p_vect(vertices[0], point);

    double dot_cc = side_c.dir_vector.dot_product(side_c.dir_vector);
    double dot_ac = side_a.dir_vector.dot_product(side_c.dir_vector);
    double dot_cp = side_c.dir_vector.dot_product(p_vect);
    double dot_aa = side_a.dir_vector.dot_product(side_a.dir_vector);
    double dot_ap = side_a.dir_vector.dot_product(p_vect);

    double divider = 1 / (dot_cc * dot_aa - dot_ac * dot_ac);
    double s = (dot_aa * dot_cp - dot_ac * dot_ap) * divider;
    double t = (dot_cc * dot_ap - dot_ac * dot_cp) * divider;

    std::cout << "S: " << s << " T: " << t << '\n';

    return ((s >= 0) && (t >= 0) && (s + t <= 1));
}

//-----------------------------------------------------------------------------------------

void triangle_t::print() {
    std::cout << "---------------------------\n";
    std::cout << "Print of triangle vertices:\n";
    for (int i = 0; i < vertices.size (); i++) {
        vertices[i].print();
    }
    std::cout << "Print of triangle plane:\n";
    plane.print();
    std::cout << "---------------------------\n";
}

#endif
