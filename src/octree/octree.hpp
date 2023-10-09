#pragma once

//-----------------------------------------------------------------------------------------

#include "node.hpp"

//-----------------------------------------------------------------------------------------

namespace my_tree {

class octree_t {
    public:
        node_t* root;
    public:
        inline octree_t(object_vect triangles,
                        point_t top_right_front,
                        point_t bottom_left_back);
        inline ~octree_t();
};

//-----------------------------------------------------------------------------------------

octree_t::octree_t(object_vect triangles, point_t top_left_front,
                                          point_t bottom_right_back) {
    root = new node_t {triangles, top_left_front, bottom_right_back};
}

octree_t::~octree_t() {
    delete root;
}

//-----------------------------------------------------------------------------------------

}
