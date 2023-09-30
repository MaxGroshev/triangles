#include "../include/triangle.hpp"

using namespace geom_figures;

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

    std::array<point_t, count_of_triangle_vertices> intersect_points;
    pos_of_the_planes pos = plane.def_pos_of_planes(trian.plane);

    if (pos == pos_of_the_planes::PARALLEL) {
        return false;
    }
    else if (pos == pos_of_the_planes::COINCIDE) {
        return intersect_in_same_plane(trian);
    }
    else {
        intersect_points[0] = plane.find_point_of_intersection(trian.side_a);
        intersect_points[1] = plane.find_point_of_intersection(trian.side_b);
        intersect_points[2] = plane.find_point_of_intersection(trian.side_c);

        for (int i = 0; i < count_of_triangle_vertices; i++) {
            if (intersect_points[i].is_valid()) {
                if (point_in_triangle(intersect_points[i]) &&
                    trian.point_in_triangle(intersect_points[i])) {
                    return true;
                }
            }
        }

        intersect_points[0] = trian.plane.find_point_of_intersection(side_a);
        intersect_points[1] = trian.plane.find_point_of_intersection(side_b);
        intersect_points[2] = trian.plane.find_point_of_intersection(side_c);

        for (int i = 0; i < count_of_triangle_vertices; i++) {
            if (intersect_points[i].is_valid()) {
                if (point_in_triangle(intersect_points[i]) &&
                    trian.point_in_triangle(intersect_points[i])) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool triangle_t::intersect_in_same_plane(const triangle_t& trian) const { //TODO more general

    for (int i = 0; i < count_of_triangle_vertices; i++) {
        bool trian_in_this = point_in_triangle(trian.vertices[i]);
        bool this_in_trian = trian.point_in_triangle(this->vertices[i]);
        if (trian_in_this || this_in_trian) {
            LOG_DEBUG("Point in triangle\n");
            return true;
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

    LOG_DEBUG ("S: ", s, " T: ", t, '\n');

    return ((s  >= -calculation_error) &&
            (t  >= -calculation_error) &&
            (s + t <= 1 + calculation_error));
}

//-----------------------------------------------------------------------------------------

void triangle_t::print() {

    std::cout << "---------------------------\n";
    std::cout << "Print of triangle vertices:\n";
    for (int i = 0; i < vertices.size (); i++) {
        vertices[i].print();
    }
    side_a.dir_vector.print();
    side_b.dir_vector.print();
    side_c.dir_vector.print();
    std::cout << "Print of triangle plane:\n";
    plane.print();
    std::cout << "---------------------------\n";
}
