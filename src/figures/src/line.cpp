#include "line.hpp"

using namespace geom_figures;

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
