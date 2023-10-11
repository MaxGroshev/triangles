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
const int count_of_octants = 8;

enum oct_name {
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
};

struct octant_t {
    const double min_size = 1;

    using p_oct_array = typename  std::array<octant_t*, count_of_octants>;

    point_t top_left_front_;
    point_t bottom_right_back_;

    inline octant_t(point_t top_left_front, point_t bottom_right_back) :
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back) {};

    inline octant_t(octant_t octant, point_t oct_center, int oct_name);

    inline void expand_oct(const std::vector<point_t>& points);
    inline octant_t::p_oct_array create_oct_array(const point_t& oct_center);
    inline bool limit_of_oct_size() const {
                return (fabs((top_left_front_.x - bottom_right_back_.x)) <= min_size);};

    inline point_t find_octant_center() const;
};

//-----------------------------------------------------------------------------------------

octant_t::octant_t(octant_t octant, point_t oct_center, int oct_name) {
    switch (oct_name) {
        case top_right_front:
            octant_t {
                point_t {top_left_front_.x, oct_center.y, top_left_front_.z},
                point_t {oct_center.x, bottom_right_back_.y, oct_center.z}
            };
            break;
        case top_left_front:
            octant_t(top_left_front_, oct_center);
            break;
        case bottom_left_front:
            octant_t {
                point_t {top_left_front_.x, top_left_front_.y, oct_center.z},
                point_t {oct_center.x, oct_center.y, bottom_right_back_.z}
            };
            break;
        case bottom_right_front:
            octant_t {
                point_t {top_left_front_.x, oct_center.y, oct_center.z},
                point_t {oct_center.x, bottom_right_back_.y, bottom_right_back_.z}
            };
            break;
        case top_right_back:
            octant_t {
                point_t {oct_center.x, oct_center.y, top_left_front_.z},
                point_t {bottom_right_back_.x, bottom_right_back_.y, oct_center.z}
            };
            break;
        case top_left_back:
            octant_t {
                point_t {oct_center.x, top_left_front_.y, top_left_front_.z},
                point_t {bottom_right_back_.x, oct_center.y, oct_center.z}
            };
            break;
        case bottom_left_back:
            octant_t {
                point_t {oct_center.x, top_left_front_.y, oct_center.z},
                point_t {bottom_right_back_.x, oct_center.y, bottom_right_back_.z}
            };
            break;
        case bottom_right_back:
            octant_t(oct_center, bottom_right_back_);
            break;
    }
};

octant_t::p_oct_array octant_t::create_oct_array(const point_t& oct_center) {
    octant_t::p_oct_array octants;

    octants[top_left_front]  = new octant_t(top_left_front_, oct_center);
    octants[top_right_front] = new octant_t {
        point_t {top_left_front_.x, oct_center.y, top_left_front_.z},
        point_t {oct_center.x, bottom_right_back_.y, oct_center.z}
    };
    octants[bottom_left_front] = new octant_t {
        point_t {top_left_front_.x, top_left_front_.y, oct_center.z},
        point_t {oct_center.x, oct_center.y, bottom_right_back_.z}
    };
    octants[bottom_right_front] = new octant_t {
        point_t {top_left_front_.x, oct_center.y, oct_center.z},
        point_t {oct_center.x, bottom_right_back_.y, bottom_right_back_.z}
    };
    octants[top_left_back] = new octant_t {
        point_t {oct_center.x, top_left_front_.y, top_left_front_.z},
        point_t {bottom_right_back_.x, oct_center.y, oct_center.z}
    };
    octants[top_right_back] = new octant_t {
        point_t {oct_center.x, oct_center.y, top_left_front_.z},
        point_t {bottom_right_back_.x, bottom_right_back_.y, oct_center.z}
    };
    octants[bottom_left_back] = new octant_t {
        point_t {oct_center.x, top_left_front_.y, oct_center.z},
        point_t {bottom_right_back_.x, oct_center.y, bottom_right_back_.z}
    };
    octants[bottom_right_back] = new octant_t(oct_center, bottom_right_back_);

    for (int i = 0; i < count_of_octants; i++) {
        ASSERT(octants[i] != nullptr);
    }

    return octants;
}

//-----------------------------------------------------------------------------------------

void octant_t::expand_oct(const std::vector<point_t>& points) {
    for (auto const& point : points) {
        if (top_left_front_.x < point.x)
            top_left_front_.x = point.x;
        if (top_left_front_.y < point.y)
            top_left_front_.y = point.y;
        if (top_left_front_.z < point.z)
            top_left_front_.z = point.z;

        if (bottom_right_back_.x > point.x)
            bottom_right_back_.x = point.x;
        if (bottom_right_back_.y > point.y)
            bottom_right_back_.y = point.y;
        if (bottom_right_back_.z > point.z)
            bottom_right_back_.z = point.z;
    }
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
