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

        vector_t side_a;
        vector_t side_b;
        vector_t side_c;
        plane_t  plane; // with help of Ax+By+Cz+D = 0 ?
    public:
        //Constructor & destructor
        explicit triangle_t(const point_t& point1, const point_t& point2,
                                                   const point_t& point3);
        virtual ~triangle_t() {};

        bool is_point_in(const point_t& point) const;
        void print();

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

    side_a.set_vector(point1, point2);
    side_b.set_vector(point2, point3);
    side_c.set_vector(point3, point1);

    plane.set_plane(point1, point2, point3);
}

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

bool triangle_t::is_point_in(const point_t& point) const {

}

#endif
