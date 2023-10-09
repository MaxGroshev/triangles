#pragma once

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <iterator>

#include "debug_utils.hpp"
#include "figures.hpp"

//-----------------------------------------------------------------------------------------

namespace my_tree {

using namespace geom_figures;

enum class oct_name {
    undefined          = -2,
    intersection       = -1,

    top_right_front    = 0,  // (x+; y+; z+)
    top_left_front     = 1,  // (x+; y-; z+)
    bottom_left_front  = 2,  // (x+; y-; z-)
    bottom_right_front = 3,  // (x+; y+; z-)

    top_right_back     = 4,  // (x-; y+; z+)
    top_left_back      = 5,  // (x-; y-; z+)
    bottom_left_back   = 6,  // (x-; y-; z-)
    bottom_right_back  = 7,  // (x-; y+; z-)

    count_of_octants   = 8,
};

struct octant_t {
    const int min_size = 1;

    using p_oct_array = typename  std::array<octant_t*, int(oct_name::count_of_octants)>;

    point_t top_left_front_;
    point_t bottom_right_back_;

    inline octant_t(point_t top_left_front, point_t bottom_right_back) :
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back) {};

    inline octant_t::p_oct_array create_oct_array(const point_t& oct_center);
    inline bool limit_of_oct_size() const {
                return (fabs((top_left_front_.x - bottom_right_back_.x)) <= min_size);};

    inline point_t find_octant_center() const;
};

//-----------------------------------------------------------------------------------------

octant_t::p_oct_array octant_t::create_oct_array(const point_t& oct_center) {
    octant_t::p_oct_array octants;

    octants[int(oct_name::top_left_front)]  = new octant_t(top_left_front_, oct_center);
    octants[int(oct_name::top_right_front)] = new octant_t {
        point_t {top_left_front_.x, oct_center.y, top_left_front_.z},
        point_t {oct_center.x, bottom_right_back_.y, oct_center.z}
    };
    octants[int(oct_name::bottom_left_front)] = new octant_t {
        point_t {top_left_front_.x, top_left_front_.y, oct_center.z},
        point_t {oct_center.x, oct_center.y, bottom_right_back_.z}
    };
    octants[int(oct_name::bottom_right_front)] = new octant_t {
        point_t {top_left_front_.x, oct_center.y, oct_center.z},
        point_t {oct_center.x, bottom_right_back_.y, bottom_right_back_.z}
    };
    octants[int(oct_name::top_left_back)] = new octant_t {
        point_t {oct_center.x, top_left_front_.y, top_left_front_.z},
        point_t {bottom_right_back_.x, oct_center.y, oct_center.z}
    };
    octants[int(oct_name::top_right_back)] = new octant_t {
        point_t {oct_center.x, oct_center.y, top_left_front_.z},
        point_t {bottom_right_back_.x, bottom_right_back_.y, oct_center.z}
    };
    octants[int(oct_name::bottom_left_back)] = new octant_t {
        point_t {oct_center.x, top_left_front_.y, oct_center.z},
        point_t {bottom_right_back_.x, oct_center.y, bottom_right_back_.z}
    };
    octants[int(oct_name::bottom_right_back)] = new octant_t(oct_center, bottom_right_back_);

    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
        ASSERT(octants[i] != nullptr);
    }

    return octants;
}

//-----------------------------------------------------------------------------------------

point_t octant_t::find_octant_center() const {
    point_t center;
    center.x = (top_left_front_.x + bottom_right_back_.x) / 2;
    center.y = (top_left_front_.y + bottom_right_back_.y) / 2;
    center.z = (top_left_front_.z + bottom_right_back_.z) / 2;

    return center;
}

}
