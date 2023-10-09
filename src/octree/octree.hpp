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

    count_of_octants   = 8,  //remove
};

struct octant_t {
    using p_oct_array = typename  std::array<octant_t*, int(oct_name::count_of_octants)>;

    point_t top_left_front_;
    point_t bottom_right_back_;

    inline octant_t(point_t top_left_front, point_t bottom_right_back) :
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back) {};
};

using object_vect = typename std::vector<std::pair<triangle_t, size_t>>;

class octree_t {
    const int min_size = 1;

    private:
        //octree_t* top;

        point_t top_left_front_;
        point_t bottom_right_back_; //may be change to octant but line is too long
        object_vect triangles_;
        std::vector<octree_t*> children_ {8, nullptr};
        octree_t* parent;
    public:
        inline octree_t() {};
        inline octree_t(point_t top_right_front,
                        point_t bottom_left_back);
        inline octree_t(object_vect triangles,
                        point_t top_right_front,
                        point_t bottom_left_back);
        inline ~octree_t();
        inline void destroy_tree();

        inline void build_tree();
        inline void print() const;

        inline oct_name define_pos_in_octant(const triangle_t& triangle,
                                             const point_t& oct_center) const;
        inline oct_name define_pos_in_octant(const point_t& point,
                                             const point_t& oct_center) const;

        inline octant_t::p_oct_array create_oct_array(const point_t& oct_center);
        inline octree_t* create_node(octant_t* octant, object_vect triangles); //bad
        inline bool      limit_of_oct_size() const
        {return (fabs((top_left_front_.x - bottom_right_back_.x)) <= 1);}; //probably make int size with size 2^n

        inline point_t             find_octant_center() const; //remove to struct octant
        inline std::vector<size_t> find_intersections(object_vect parent_triangles);
        inline void find_intersection_in_oct     (object_vect& parent_triangles,
                                                  std::vector<size_t>& intersect_triangles);
        inline void find_intersection_with_parent(object_vect& parent_triangles,
                                                  std::vector<size_t>& intersect_triangles);
};

//-----------------------------------------------------------------------------------------

octree_t::octree_t(object_vect triangles, point_t top_left_front,
                                          point_t bottom_right_back) :
    triangles_(triangles),
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back)
    {children_.reserve(size_t(oct_name::count_of_octants));
}

octree_t::octree_t(point_t top_left_front, point_t bottom_right_back) :
    top_left_front_(top_left_front),
    bottom_right_back_(bottom_right_back)
    {children_.reserve(size_t(oct_name::count_of_octants));
};

octree_t::~octree_t() {
    //if (parent != this)
    //std::cout << "Destructor\n";
    // for (int i = 0; i < 8; i++) {
    //     delete children_[i];
    // }
    destroy_tree();
    // delete this;
    // delete this;
}

void octree_t::destroy_tree() {
    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
        if (children_[i] != nullptr) {
            children_[i]->destroy_tree();
        }
        delete children_[i];

    }
}

//-----------------------------------------------------------------------------------------

void octree_t::build_tree() {
    if      (triangles_.size() <= 1) return;
    else if (limit_of_oct_size())    return;

    point_t oct_center = find_octant_center();
    //oct_center.print();
    octant_t::p_oct_array octants = create_oct_array(oct_center);

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

    // std::cout << "------------------------------------\n";
    // std::cout << oct_data[0].size() << '\n';
    // std::cout << oct_data[1].size() << '\n';
    // std::cout << oct_data[2].size() << '\n';
    // std::cout << oct_data[3].size() << '\n';
    // std::cout << oct_data[4].size() << '\n';
    // std::cout << oct_data[5].size() << '\n';
    // std::cout << oct_data[6].size() << '\n';
    // std::cout << oct_data[7].size() << '\n';
    // std::cout << "------------------------------------\n";


    for (int i = 0; i < del_vect.size(); i++) {
        triangles_.erase(del_vect[i]);
    }

    for (int i = 0; i < int(oct_name::count_of_octants); i++)
	{
		if (oct_data[i].size() != 0)
		{
            children_[i] = create_node(octants[i], oct_data[i]);
            // m_activeNodes |= (byte)(1 << a);
            children_[i]->build_tree();
		}
        else if (oct_data[i].size() == 0){
            children_[i] = nullptr;
        }
        delete octants[i];
	}
}

//-----------------------------------------------------------------------------------------

octree_t* octree_t::create_node(octant_t* octant, object_vect triangles) {
    ASSERT(octant != nullptr);

    octree_t* ret_node = new octree_t{octant->top_left_front_, octant->bottom_right_back_};
    ASSERT(ret_node != nullptr);
    ret_node->parent = this;
    ret_node->triangles_ = triangles;

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
    octants[int(oct_name::bottom_right_back)] = new octant_t(oct_center, bottom_right_back_);

    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
        ASSERT(octants[i] != nullptr);
    }

    return octants;
}


//-----------------------------------------------------------------------------------------

std::vector<size_t> octree_t::find_intersections(object_vect parent_triangles) {

    std::vector<size_t> intersect_triangles;

    find_intersection_with_parent(parent_triangles, intersect_triangles);
    find_intersection_in_oct     (parent_triangles,intersect_triangles);

    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
        if (children_[i] != nullptr) {
            std::vector<size_t> intersected_children = children_[i]->find_intersections(parent_triangles);
            intersect_triangles.insert(intersect_triangles.end(),
                                       intersected_children.begin(),
                                       intersected_children.end());
        }
    }
    return intersect_triangles;
}

void octree_t::find_intersection_in_oct(object_vect& parent_triangles,
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

void octree_t::find_intersection_with_parent(object_vect& parent_triangles,
                                             std::vector<size_t>& intersect_triangles) {
    for (int i = 0; i < triangles_.size(); i++) {
        for (int j = 0; j < parent_triangles.size(); j++) {
            if (triangles_[i].first.intersect(parent_triangles[j].first)) {
                LOG_DEBUG("INTERSECTION: (", i, ";", j, ")\n")
                if (!triangles_[i].first.intersect_status()) {
                    intersect_triangles.push_back(triangles_[i].second);
                    triangles_[i].first.set_intersect_status(true);                }
                if (!parent_triangles[j].first.intersect_status()) {
                    intersect_triangles.push_back(parent_triangles[j].second);
                    parent_triangles[j].first.set_intersect_status(true);
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------------------

oct_name octree_t::define_pos_in_octant(const triangle_t& triangle,
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

//-----------------------------------------------------------------------------------------

void octree_t::print() const {
    static int level = 0;
    if (triangles_.size() != 0) {
        std::cout << "Level of print: " << level << '\n';
        top_left_front_.print();
        bottom_right_back_.print();
        for (auto const& elem : triangles_) {
            std::cout << "Number " << elem.second << '\n';
            elem.first.print();
        }
    }

    for (int i = 0; i < int(oct_name::count_of_octants); i++) {
        if (children_[i] != nullptr) {
            children_[i]->print();
            level++;
        }
    }
}
}
