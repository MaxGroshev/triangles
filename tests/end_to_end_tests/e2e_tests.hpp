#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>

#include "../../debug_utils/console_colors.hpp"
#include "../../figures/triangle.hpp"
#include "../../debug_utils/error_control.h"
#include "../../interactio_with_user/unteraction_with_user.hpp"

//-----------------------------------------------------------------------------------------

namespace tests {
};

using vector_ss = typename std::vector<std::pair<size_t, size_t>>;

int run_e2e_tests();
vector_ss start_tests(size_t count_of_triangles, triangle_t* triangles);
vector_ss get_correct_res(std::istream & in_strm = std::cin);

