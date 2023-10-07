#pragma once

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cmath>
#include <vector>
#include <array>

#include "debug_utils.hpp"
#include "figures.hpp"

//-----------------------------------------------------------------------------------------

namespace my_tree {

using namespace geom_figures;

enum class oct_name {
    undefined          = -1,

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

class octree_t {
    const int min_size = 1;
    private:
        point_t top_left_front_;
        point_t bottom_right_back_;
        std::vector<triangle_t> triangles_;
        std::vector<octree_t*> children_;
        octree_t* parent;
    public:
        inline octree_t() {};
        inline octree_t(point_t top_left_front,
                        point_t bottom_right_back);
        inline octree_t(std::vector<triangle_t> triangles,
                        point_t top_right_front,
                        point_t bottom_left_back);
        inline ~octree_t();

        inline octree_t* build_tree();
        inline void      insert(triangle_t triangle);

        inline oct_name define_pos_in_octant(const triangle_t& triangle,
                                                   const point_t& oct_center) const;
        inline oct_name define_pos_in_octant(const point_t& point,
                                                   const point_t& oct_center) const;

        inline void make_children(const point_t& oct_center);
        inline bool limit_of_oct_size() const
                                {return ((top_left_front_.x - bottom_right_back_.x) <= 1);}; //probably make int size with size 2^n
        inline point_t find_octant_center() const;
        // inline
};

//-----------------------------------------------------------------------------------------

octree_t::octree_t(std::vector<triangle_t> triangles, point_t top_left_front,
                                                      point_t bottom_right_back) :
    triangles_(triangles),
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back)
    {children_.reserve(size_t(oct_name::count_of_octants));
}

octree_t::octree_t(point_t top_left_front, point_t bottom_right_back) :
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back) {
}

octree_t::~octree_t(){

}

//-----------------------------------------------------------------------------------------

void octree_t::insert(triangle_t triangle) {
    if      (triangles_.size() <= 1) return;
    else if (limit_of_oct_size())    return;
    point_t oct_center = find_octant_center();
    oct_name pos = define_pos_in_octant(triangle, oct_center);

    make_children(oct_center);

    if (children_[int(pos)] == nullptr) {

    }
}

void octree_t::make_children(const point_t& oct_center) {
    parent = this;

    children_[int(oct_name::top_left_front)]  = new octree_t(top_left_front_, oct_center);
    children_[int(oct_name::top_right_front)] = new octree_t {
        point_t {top_left_front_.x, oct_center.y, top_left_front_.z},
        point_t {oct_center.x, bottom_right_back_.y, oct_center.z}
    };
    children_[int(oct_name::bottom_left_front)] = new octree_t {
        point_t {top_left_front_.x, top_left_front_.y, oct_center.z},
        point_t {oct_center.x, oct_center.y, bottom_right_back_.z}
    };
    children_[int(oct_name::bottom_right_front)] = new octree_t {
        point_t {top_left_front_.x, oct_center.y, oct_center.z},
        point_t {oct_center.x,  bottom_right_back_.y, bottom_right_back_.z}
    };
    children_[int(oct_name::top_left_back)] = new octree_t {
        point_t {oct_center.x, top_left_front_.y, top_left_front_.z},
        point_t {bottom_right_back_.x, oct_center.y, oct_center.z}
    };
    children_[int(oct_name::top_right_back)] = new octree_t {
        point_t {oct_center.x, oct_center.y, top_left_front_.z},
        point_t {bottom_right_back_.x, bottom_right_back_.y, oct_center.z}
    };
    children_[int(oct_name::bottom_left_back)] = new octree_t {
        point_t {oct_center.x, top_left_front_.y, oct_center.z},
        point_t {bottom_right_back_.x, oct_center.y, bottom_right_back_.z}
    };
    children_[int(oct_name::top_left_front)] = new octree_t(oct_center, bottom_right_back_);

}

//-----------------------------------------------------------------------------------------

oct_name octree_t::define_pos_in_octant(const triangle_t& triangle,
                                              const point_t& oct_center) const {
    oct_name pos = oct_name::undefined;

    std::array<oct_name, count_of_triangle_vertices> verticies_pos;
    for (int i = 0; i < count_of_triangle_vertices; i++) {
        verticies_pos[i] = define_pos_in_octant(triangle.vertices[i], oct_center);
    }
    //if ();

    return pos;
}

oct_name octree_t::define_pos_in_octant(const point_t& point,
                                              const point_t& oct_center) const {
    oct_name pos = oct_name::undefined;

    if (point.x <= oct_center.x) {
        if (point.y <= oct_center.y) {
            if (point.z <= oct_center.z)
                pos = oct_name::bottom_left_back;
            else
                pos = oct_name::top_left_back;
        }
        else {
            if (point.z <= oct_center.z)
                pos = oct_name::bottom_right_back;
            else
                pos = oct_name::top_right_back;
        }
    }
    else {
        if (point.y <= oct_center.y) {
            if (point.z <= oct_center.z)
                pos = oct_name::bottom_left_front;
            else
                pos = oct_name::top_left_front;
        }
        else {
            if (point.z <= oct_center.z)
                pos = oct_name::bottom_right_front;
            else
                pos = oct_name::top_right_front;
        }
    }

    return pos;
}

point_t octree_t::find_octant_center() const {
    point_t center;
    center.x = (top_left_front_.x + bottom_right_back_.x) / 2;
    center.y = (top_left_front_.y + bottom_right_back_.y) / 2;
    center.z = (top_left_front_.z + bottom_right_back_.z) / 2;

    return center;
}

}
