#pragma once

//-----------------------------------------------------------------------------------------

#include "octant.hpp"

//-----------------------------------------------------------------------------------------

namespace my_tree {

using object_vect = typename std::vector<std::pair<triangle_t, size_t>>;

struct node_t {

    octant_t octant_;

    object_vect triangles_;
    std::vector<node_t*> children_ {8, nullptr};

    inline node_t(point_t top_right_front, point_t bottom_left_back);
    // inline node_t(octant_t* octant, object_vect triangles);
    inline node_t(object_vect triangles,
                  point_t top_right_front,
                  point_t bottom_left_back);

    inline ~node_t();

    inline void build_tree();
    inline void print() const;

    inline oct_name define_pos_in_octant(const triangle_t& triangle,
                                            const point_t& oct_center) const;
    inline oct_name define_pos_in_octant(const point_t& point,
                                            const point_t& oct_center) const;

    inline std::vector<size_t> find_intersections(object_vect parent_triangles);
    inline void find_intersection_in_oct     (object_vect& parent_triangles,
                                              std::vector<size_t>& intersect_triangles);
    inline void find_intersection_with_parent(object_vect& parent_triangles,
                                              std::vector<size_t>& intersect_triangles);
};

//-----------------------------------------------------------------------------------------

node_t::node_t(object_vect triangles, point_t top_left_front,
                                      point_t bottom_right_back) :
    triangles_(triangles),
    octant_(top_left_front, bottom_right_back)
    {children_.reserve(size_t(oct_name::count_of_octants));
}

node_t::node_t(point_t top_left_front, point_t bottom_right_back) :
    octant_(top_left_front, bottom_right_back)
    {children_.reserve(size_t(oct_name::count_of_octants));
}

// node_t::node_t(octant_t* octant, object_vect triangles) {
//     ASSERT(octant != nullptr);
//     node_t ret_node {triangles, octant->top_left_front_, octant->bottom_right_back_};
// }

node_t::~node_t() {
    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
        delete children_[i];
    }
}

//-----------------------------------------------------------------------------------------

void node_t::build_tree() {
    if      (triangles_.size() <= 1) return;
    else if (octant_.limit_of_oct_size())    return;

    point_t oct_center = octant_.find_octant_center();
    //oct_center.print();
    octant_t::p_oct_array octants = octant_.create_oct_array(oct_center);//change

    std::array<object_vect, int(oct_name::count_of_octants)> oct_data;
    std::vector<object_vect::iterator> del_vect;

    int counter = 0;
    for (auto const& elem : triangles_) {
        oct_name pos = define_pos_in_octant(elem.first, oct_center);
        for (int oct_name = 0; oct_name < int(oct_name::count_of_octants); oct_name++) {
            if (int(pos) == oct_name) {
                del_vect.push_back(triangles_.begin() + counter);
                oct_data[oct_name].push_back(elem);
                counter--;
                break;
            }
        }
        counter++;
    }

    for (int i = 0; i < del_vect.size(); i++) {
        triangles_.erase(del_vect[i]);
    }

    for (int i = 0; i < int(oct_name::count_of_octants); i++)
	{
		if (oct_data[i].size() != 0)
		{
            children_[i] = new node_t {oct_data[i], octants[i]->top_left_front_, octants[i]->bottom_right_back_};
            ASSERT(ret_node != nullptr);

            children_[i]->build_tree();
		}
        else if (oct_data[i].size() == 0){
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

    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
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
    for (int i = 0; i < triangles_.size(); i++) {
        for (int j = i + 1; j < triangles_.size(); j++) {
            if (triangles_[i].first.intersect(triangles_[j].first)) {
                LOG_DEBUG("INTERSECTION: (", i, ";", j, ")\n")
                if (!triangles_[i].first.intersect_status()) {
                    intersect_triangles.push_back(triangles_[i].second);
                    triangles_[i].first.set_intersect_status(true);
                }
                if (!triangles_[j].first.intersect_status()) {
                    intersect_triangles.push_back(triangles_[j].second);
                    triangles_[j].first.set_intersect_status(true);
                }
            }
        }
        parent_triangles.push_back(triangles_[i]);
    }
}

void node_t::find_intersection_with_parent(object_vect& parent_triangles,
                                             std::vector<size_t>& intersect_triangles) {
    for (int i = 0; i < triangles_.size(); i++) {
        for (int j = 0; j < parent_triangles.size(); j++) {
            if (triangles_[i].first.intersect(parent_triangles[j].first)) {
                LOG_DEBUG("INTERSECTION: (", i, ";", j, ")\n")
                if (!triangles_[i].first.intersect_status()) {
                    intersect_triangles.push_back(triangles_[i].second);
                    triangles_[i].first.set_intersect_status(true);
                }
                if (!parent_triangles[j].first.intersect_status()) {
                    intersect_triangles.push_back(parent_triangles[j].second);
                    parent_triangles[j].first.set_intersect_status(true);
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
