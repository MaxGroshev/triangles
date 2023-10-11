#pragma once

//-----------------------------------------------------------------------------------------

#include "node.hpp"

//-----------------------------------------------------------------------------------------

namespace my_tree {

class octree_t {
    private:
        node_t* root;
    public:
        inline octree_t(object_vect triangles,
                        point_t top_right_front,
                        point_t bottom_left_back);
        inline octree_t(point_t top_right_front,
                        point_t bottom_left_back);
        inline ~octree_t();
        inline void build_tree();
        inline void insert(std::pair<triangle_t, size_t> triangle);
        inline std::vector<size_t> find_intersections();
};

//-----------------------------------------------------------------------------------------

octree_t::octree_t(object_vect triangles, point_t top_left_front,
                                          point_t bottom_right_back) {
    root = new node_t {triangles, top_left_front, bottom_right_back};
}

octree_t::octree_t(point_t top_left_front, point_t bottom_right_back) {
    root = new node_t {top_left_front, bottom_right_back};
}

octree_t::~octree_t() {
    delete root;
}


//-----------------------------------------------------------------------------------------

void octree_t::insert(std::pair<triangle_t, size_t> triangle) {
    root->insert(triangle);
}

void octree_t::build_tree() {
    root->build_tree();
}

std::vector<size_t> octree_t::find_intersections() {
    object_vect parent_triangles;
    return root->find_intersections(parent_triangles);
}

}
