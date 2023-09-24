#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>
#include "../figures/include/triangle.hpp"

//-----------------------------------------------------------------------------------------

namespace triangle_ui {
};

using triangle_vect = typename std::vector<triangle_t>;

size_t        get_count_of_triangles(std::istream & in_strm = std::cin);
triangle_vect get_user_triangles(const size_t count_of_triangles,
                                  std::istream & in_strm = std::cin);

std::vector<size_t> test_user_data(std::istream & in_strm = std::cin);
std::vector<size_t> start_tests(size_t count_of_triangles, triangle_vect user_triangles);
void print_triangles(triangle_t* triangle, size_t count_of_triangle);

