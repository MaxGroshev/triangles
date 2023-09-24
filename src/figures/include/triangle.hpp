#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

//-----------------------------------------------------------------------------------------

#include <array>

#include "./plane.hpp"

//-----------------------------------------------------------------------------------------

const int coun_of_triangle_vertices = 3;

//-----------------------------------------------------------------------------------------

class triangle_t {
    private:
        std::array<point_t, coun_of_triangle_vertices> vertices;
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
        virtual ~triangle_t() {};

        int  set(const point_t& point1, const point_t& point2, const point_t& point3);
        bool point_in_triangle(const point_t& point) const;
        bool is_intersected() const {return intersected;};
        void set_intersect_status(bool val) {intersected = val;};
        bool crosses_in_same_plane(const triangle_t& trian) const;
        bool intersect(const triangle_t& trian) const;
        void print();

};

#endif
