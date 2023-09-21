#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>
#include "../figures/triangle.hpp"

//-----------------------------------------------------------------------------------------

triangle_t* get_user_data(std::istream & in_strm = std::cin);
size_t      get_count_of_triangles(std::istream & in_strm = std::cin);
triangle_t* get_users_triangles(const size_t count_of_triangles,
                                std::istream & in_strm = std::cin);

void print_triangles(triangle_t* triangle, size_t count_of_triangle);
