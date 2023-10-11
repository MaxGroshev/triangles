#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>
#include "triangle.hpp"
#include <algorithm>
#include "octree.hpp"

//-----------------------------------------------------------------------------------------

namespace triangle_ui {

using namespace geom_figures;
using triangle_vect = typename std::vector<triangle_t>;

size_t               get_count_of_input_triangles(std::istream & in_strm = std::cin);
my_tree::object_vect get_user_triangles(const size_t count_of_triangles,
                                        my_tree::octant_t& init_oct,
                                        std::istream & in_strm = std::cin);

std::vector<size_t> get_and_test_user_data(std::istream & in_strm = std::cin);
std::vector<size_t> start_tests(size_t count_of_triangles, triangle_vect user_triangles);
void print_triangles(triangle_vect triangles, size_t count_of_triangle);
};



