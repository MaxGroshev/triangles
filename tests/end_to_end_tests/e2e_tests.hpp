#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>

#include "../../debug_utils/console_colors.hpp"
#include "../../figures/triangle.hpp"
#include "../../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

int run_e2e_tests();
std::vector<std::pair<size_t, size_t>> start_tests(size_t count_of_triangles,
                                                   triangle_t* triangles);
