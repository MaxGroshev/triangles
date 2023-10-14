#pragma once

//-----------------------------------------------------------------------------------------

#include "octant.hpp"

//-----------------------------------------------------------------------------------------

namespace my_tree {

using object_vect = typename std::list<std::pair<triangle_t, size_t>>;

struct node_t {

    octant_t octant_;
    //node_t* parent;
    object_vect triangles_;
    std::vector<node_t*> children_ {count_of_octants, nullptr};

    inline node_t(point_t top_right_front, point_t bottom_left_back);
    inline node_t(octant_t* octant, object_vect triangles);
    inline node_t(object_vect triangles,
                  point_t top_right_front,
                  point_t bottom_left_back);

    inline ~node_t();

    inline void build_tree();
    inline void insert(std::pair<triangle_t, size_t> triangle);
    inline void print() const;

    inline oct_name define_pos_in_octant(const triangle_t& triangle,
                                         const point_t& oct_center) const;
    inline oct_name define_pos_in_octant(const point_t& point,
                                         const point_t& oct_center) const;

    inline std::vector<size_t> find_intersections(object_vect parent_triangles);
    inline void find_intersection_in_oct (object_vect& parent_triangles,
                                         std::vector<size_t>& intersect_triangles);
    inline void find_intersection_with_parent(object_vect& parent_triangles,
                                              std::vector<size_t>& intersect_triangles);
};

//-----------------------------------------------------------------------------------------

node_t::node_t(object_vect triangles, point_t top_left_front,
                                      point_t bottom_right_back) :
    triangles_(triangles),
    octant_(top_left_front, bottom_right_back)
    {}

node_t::node_t(point_t top_left_front, point_t bottom_right_back) :
    octant_(top_left_front, bottom_right_back)
    {}

node_t::node_t(octant_t* octant, object_vect triangles) :
    triangles_(triangles),
    octant_ {octant->top_left_front_, octant->bottom_right_back_}
    {/*parent = this;*/};

node_t::~node_t() {
    // for (int i = 0; i < count_of_octants; i++) {
    //     delete children_[i];
    // }
}

void node_t::insert(std::pair<triangle_t, size_t> triangle) {

    point_t oct_center = octant_.find_octant_center();
    oct_name pos = define_pos_in_octant(triangle.first, oct_center);

    if (!(pos >= top_right_front && pos <= bottom_right_back) || octant_.limit_of_oct_size()) {//remove r condition
        triangles_.push_back(triangle);
        return;
    }
    else {
        if (children_[pos] == nullptr) {
            octant_t octant = octant_t(octant, oct_center, pos);
            children_[pos] = new node_t {octant.top_left_front_, octant.bottom_right_back_};
            children_[pos]->triangles_.push_back(triangle);
        }
        else {
            children_[pos]->insert(triangle);
            // //std::cout << "Here\n";
            // //children_[pos]->insert(triangle);
            // children_[pos]->triangles_.push_back(triangle);
        }
    }

}


//-----------------------------------------------------------------------------------------

void node_t::build_tree() {
    if      (triangles_.size() <= 1)      return;
    else if (octant_.limit_of_oct_size()) return;

   // return;
    point_t oct_center = octant_.find_octant_center();
    //oct_center.print();
    octant_t::p_oct_array octants = octant_.create_oct_array(oct_center);//change

    std::array<object_vect, count_of_octants> oct_data;
    std::vector<object_vect::iterator> del_vect;
    for (auto cur = triangles_.begin(); cur != triangles_.end(); cur = std::next(cur)) {
        oct_name pos = define_pos_in_octant(cur->first, oct_center);
        if (pos >= top_right_front) {
            del_vect.push_back(cur);
            oct_data[pos].push_back(*cur);
            counter--;
        }
    }

    for (int i = 0; i < del_vect.size(); i++) {
        triangles_.erase(del_vect[i]);
    }

    for (int i = 0; i < count_of_octants; i++)
	{
		if (oct_data[i].size() != 0)
		{
            children_[i] = new node_t {octants[i], oct_data[i]};
            ASSERT(ret_node != nullptr);
            children_[i]->build_tree();
		}
        else if (oct_data[i].size() == 0) {
            children_[i] = nullptr;
        }
        delete octants[i];
	}
}

//-----------------------------------------------------------------------------------------

std::vector<size_t> node_t::find_intersections(object_vect parent_triangles) {
    std::vector<size_t> intersect_triangles;

    find_intersection_with_parent(parent_triangles, intersect_triangles);
    find_intersection_in_oct     (parent_triangles,intersect_triangles);

    for (int i = 0; i < count_of_octants; i++) {
        if (children_[i] != nullptr) {
            std::vector<size_t> intersected_children =
                                        children_[i]->find_intersections(parent_triangles);
            intersect_triangles.insert(intersect_triangles.end(),
                                       intersected_children.begin(),
                                       intersected_children.end());
        }
    }
    return intersect_triangles;
}

void node_t::find_intersection_in_oct(object_vect& parent_triangles,
                                      std::vector<size_t>& intersect_triangles) {

    for (auto child1 = triangles_.begin(); child1 != triangles_.end(); child1 =std::next(child1)) {
        // auto child2 = std::next(child1);
        for (auto child2 = std::next(child1); child2 != triangles_.end(); child2 = std::next(child2)) {
            if (child1->first.intersect(child2->first)) {
                if (!child1->first.intersect_status()) {
                    intersect_triangles.push_back(child1->second);
                    child1->first.set_intersect_status(true);
                }
                if (!child2->first.intersect_status()) {
                    intersect_triangles.push_back(child2->second);
                    child2->first.set_intersect_status(true);
                }
            }
        }
        parent_triangles.push_back(*child1);
    }
}

void node_t::find_intersection_with_parent(object_vect& parent_triangles,
                                           std::vector<size_t>& intersect_triangles) {
    for (auto& child : triangles_) {
        for (auto& parent : parent_triangles) {
            if (child.first.intersect(parent.first)) {
                if (!child.first.intersect_status()) {
                    intersect_triangles.push_back(child.second);
                    child.first.set_intersect_status(true);
                }
                if (!parent.first.intersect_status()) {
                    intersect_triangles.push_back(parent.second);
                    parent.first.set_intersect_status(true);
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------------------

oct_name node_t::define_pos_in_octant(const triangle_t& triangle,
                                      const point_t& oct_center) const {
    std::array<oct_name, count_of_triangle_vertices> verticies_pos;
    for (int i = 0; i < count_of_triangle_vertices; i++) {
        verticies_pos[i] = define_pos_in_octant(triangle.vertices[i], oct_center);
    }
    if (verticies_pos[0] == verticies_pos[1] && verticies_pos[1] == verticies_pos[2]) {
        return verticies_pos[1];
    }

    return oct_name::intersection;
}

oct_name node_t::define_pos_in_octant(const point_t& point,
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

//-----------------------------------------------------------------------------------------

}
