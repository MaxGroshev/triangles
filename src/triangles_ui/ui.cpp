#include "ui.hpp"

//-----------------------------------------------------------------------------------------

namespace triangle_ui {

std::vector<size_t> get_and_test_user_data(std::istream & in_strm) {
    using namespace my_tree;

    size_t count_of_triangles  = get_count_of_input_triangles(in_strm);
    object_vect user_triangles = get_user_triangles(count_of_triangles);
    octree_t octree(user_triangles, point_t{128, 0, 128}, point_t{0, 128, 0});
    octree.root->build_tree();

    //octree.print();
    object_vect parent_triangles;
    return octree.root->find_intersections(parent_triangles);
}

size_t get_count_of_input_triangles(std::istream & in_strm) {

    ASSERT (!in_strm.eof ());

    int count_of_triangles = 0;
    in_strm >> count_of_triangles;
    if (!in_strm.good()) {
        std::cout << "\nWrong input of count of triangles\n";
        exit(-1);
    }

    return count_of_triangles;
}

my_tree::object_vect get_user_triangles(const size_t count_of_triangles, std::istream & in_strm) {

    my_tree::object_vect user_triangles;
    point_t p1;
    point_t p2;
    point_t p3;
    triangle_t tmp_trian {};
    for (int i = 0; i < count_of_triangles; i++) {
        in_strm >> p1.x >> p1.y >> p1.z;
        in_strm >> p2.x >> p2.y >> p2.z;
        in_strm >> p3.x >> p3.y >> p3.z;
        if (!in_strm.good() && !in_strm.eof()) {
            std::cout << "\nWrong input of coordinates of triangles\n";
            exit(-1);
        }
        tmp_trian.set(p1, p2, p3);
       // tmp_trian.print();
        user_triangles.push_back(std::make_pair(tmp_trian, i));
    }

    return user_triangles;
}

//-----------------------------------------------------------------------------------------

void print_triangles(triangle_vect triangles, size_t count_of_triangle) {
    for (int i = 0; i < count_of_triangle; i++) {
        triangles[i].print();
    }
}

}
