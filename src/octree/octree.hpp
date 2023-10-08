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

    count_of_octants   = 8,  //remove
};

struct octant_t {
    using p_oct_array = std::array<octant_t*, int(oct_name::count_of_octants)>;

    point_t top_left_front_;
    point_t bottom_right_back_;

    inline octant_t(point_t top_left_front, point_t bottom_right_back) :
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back) {};
};

class octree_t {
    const int min_size = 1;

    private:
        octree_t* top;

        bool no_elems = true;
        point_t top_left_front_;
        point_t bottom_right_back_; //may be change to octant but line is too long
        std::vector<triangle_t> triangles_;
        std::vector<octree_t*> children_;
        octree_t* parent;
    public:
        inline octree_t() {};
        inline octree_t(point_t top_right_front,
                        point_t bottom_left_back);
        inline octree_t(std::vector<triangle_t> triangles,
                        point_t top_right_front,
                        point_t bottom_left_back);
        inline ~octree_t();
        inline void destroy_tree();

        inline void build_tree();
        inline void insert(triangle_t triangle);

        inline oct_name define_pos_in_octant(const triangle_t& triangle,
                                             const point_t& oct_center) const;
        inline oct_name define_pos_in_octant(const point_t& point,
                                             const point_t& oct_center) const;

        inline octant_t::p_oct_array create_oct_array(const point_t& oct_center);
        inline octree_t* create_node(octant_t* octant, std::vector<triangle_t> triangles); //bad
        inline bool      limit_of_oct_size() const
        {return ((top_left_front_.x - bottom_right_back_.x) <= 1);}; //probably make int size with size 2^n

        inline point_t                 find_octant_center() const; //remove to struct octant
        inline std::vector<size_t> find_intersections(std::vector<triangle_t>
                                                      parent_triangles);
};

//-----------------------------------------------------------------------------------------

octree_t::octree_t(std::vector<triangle_t> triangles, point_t top_left_front,
                                                      point_t bottom_right_back) :
    triangles_(triangles),
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back),
    no_elems(false)
    {children_.reserve(size_t(oct_name::count_of_octants));
}

octree_t::octree_t(point_t top_left_front, point_t bottom_right_back) :
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back) {
};

octree_t::~octree_t() {
    destroy_tree();
}

void octree_t::destroy_tree() {
    if (!no_elems) {
        for (int i = 0; i < int(oct_name::count_of_octants); i++) {
            if (children_[i] != nullptr) {
                children_[i]->destroy_tree();
            }
            else {
                delete this;
            }
        }
    }
}

//-----------------------------------------------------------------------------------------

void octree_t::build_tree() {
    if      (triangles_.size() <= 1) return;
    else if (limit_of_oct_size())    return;

    point_t oct_center = find_octant_center();
    octant_t::p_oct_array octants = create_oct_array(oct_center);

    std::array<std::vector<triangle_t>, int(oct_name::count_of_octants)> oct_data;
    size_t counter = 0;
    for (auto const& elem : triangles_) { //seg_fault?
        oct_name pos = define_pos_in_octant(elem, oct_center);
        for (int oct_name = 0; oct_name < int(oct_name::count_of_octants); oct_name++) {
            if (int(pos) == oct_name) {
                triangles_.erase(triangles_.begin() + counter);
                oct_data[oct_name].push_back(elem);
                break;
            }
        }
        counter++;
    }

    for (int i = 0; i < int(oct_name::count_of_octants); i++)
	{
		if (oct_data[i].size() != 0)
		{
			children_[i] = create_node(octants[i], oct_data[i]);
			// m_activeNodes |= (byte)(1 << a);
			children_[i]->build_tree();
		}
        else {
            delete octants[i];
        }
	}
}

//-----------------------------------------------------------------------------------------

octree_t* octree_t::create_node(octant_t* octant, std::vector<triangle_t> triangles) {
    ASSERT(octant != nullptr);

    octree_t* ret_node = new octree_t{octant->top_left_front_, octant->bottom_right_back_};
    ret_node->parent = this;
    no_elems = false;

    return ret_node;
}

octant_t::p_oct_array octree_t::create_oct_array(const point_t& oct_center) {
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
    octants[int(oct_name::top_left_front)] = new octant_t(oct_center, bottom_right_back_);

    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
        ASSERT(octants[i] != nullptr);
    }

    return octants;
}


//-----------------------------------------------------------------------------------------

std::vector<size_t> octree_t::find_intersections(std::vector<triangle_t>
                                                 parent_triangles) {

    std::vector<size_t> intersect_triangles;

    for (int i = 0; i < triangles_.size(); i++) {
        for (int j = 0; j < parent_triangles.size(); j++) {
            if (triangles_[i].intersect(parent_triangles[j])) {
                LOG_DEBUG("INTERSECTION: (", i, ";", j, ")\n")
                if (!triangles_[i].is_intersected()) {
                    intersect_triangles.push_back(i);
                    triangles_[i].set_intersect_status(true);
                }
                if (!parent_triangles[j].is_intersected()) {
                    intersect_triangles.push_back(j);
                    parent_triangles[j].set_intersect_status(true);
                }
            }
        }

        for (int j = i + 1; j < triangles_.size(); j++) {
            if (triangles_[i].intersect(triangles_[j])) {
                LOG_DEBUG("INTERSECTION: (", i, ";", j, ")\n")
                if (!triangles_[i].is_intersected()) {
                    intersect_triangles.push_back(i);
                    triangles_[i].set_intersect_status(true);
                }
                if (!triangles_[j].is_intersected()) {
                    intersect_triangles.push_back(j);
                    triangles_[j].set_intersect_status(true);
                }
            }
        }
        parent_triangles.push_back(triangles_[i]);
    }

    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
        if (!children_[i]->no_elems) {
            std::vector<size_t> intersected_children = find_intersections(parent_triangles);
            intersect_triangles.insert(intersect_triangles.end(),
                                       intersected_children.begin(),
                                       intersected_children.end());
        }
    }

    return intersect_triangles;
}

//-----------------------------------------------------------------------------------------

oct_name octree_t::define_pos_in_octant(const triangle_t& triangle,
                                        const point_t& oct_center) const {
    std::array<oct_name, count_of_triangle_vertices> verticies_pos;
    for (int i = 0; i < count_of_triangle_vertices; i++) {
        verticies_pos[i] = define_pos_in_octant(triangle.vertices[i], oct_center);
    }

    if (verticies_pos[1] == verticies_pos[2] && verticies_pos[2] == verticies_pos[3]) {
        return verticies_pos[1];
    }

    return oct_name::intersection;
}

oct_name octree_t::define_pos_in_octant(const point_t& point,
                                        const point_t& oct_center) const {
    oct_name pos = oct_name::undefined;

    if (point.x <= oct_center.x) { //bad <=
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
