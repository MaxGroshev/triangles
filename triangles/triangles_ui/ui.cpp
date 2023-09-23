#include "./ui.hpp"

using namespace triangle_ui;

//-----------------------------------------------------------------------------------------

std::vector<size_t> test_user_data(std::istream & in_strm) {
    size_t count_of_triangles    = get_count_of_triangles(in_strm);
    triangle_vect user_triangles = get_user_triangles(count_of_triangles);

    return start_tests(count_of_triangles, user_triangles);
}

size_t get_count_of_triangles(std::istream & in_strm) {
    ASSERT (!in_strm.eof ());

    int count_of_triangles = 0;
    in_strm >> count_of_triangles;
    if (!in_strm.good ()) {
        std::cout << "\nWrong input of count of triangles\n";
        exit(-1);
    }

    return count_of_triangles;
}

triangle_vect get_user_triangles(const size_t count_of_triangles, std::istream & in_strm) {
    triangle_vect user_triangles;

    point_t p1;
    point_t p2;
    point_t p3;
    triangle_t tmp_trian {};
    for (int i = 0; i < count_of_triangles; i++) {
        in_strm >> p1.x >> p1.y >> p1.z;
        in_strm >> p2.x >> p2.y >> p2.z;
        in_strm >> p3.x >> p3.y >> p3.z;
        if (!in_strm.good ()) {
            std::cout << "\nWrong input of coordinates of triangles\n";
            exit(-1);
        }
        tmp_trian.set (p1, p2, p3);
        //tmp_trian.print();
        user_triangles.push_back(tmp_trian);
    }

    return user_triangles;
}

std::vector<size_t> start_tests(size_t count_of_triangles, triangle_vect user_triangles) {
    std::vector<size_t> intersect_triangles;
    for (int i = 0; i < count_of_triangles; i++) {
        for (int j = i + 1; j < count_of_triangles; j++) {
            if (user_triangles[i].intersect(user_triangles[j])) {
                //std::cout << i << '\n';
                if (!user_triangles[i].is_intersected()) {
                    intersect_triangles.push_back(i + 1);
                }
                intersect_triangles.push_back(j + 1);
                user_triangles[i].set_intersect_status(true);
                user_triangles[j].set_intersect_status(true);
                break;
            }
        }
    }

    return intersect_triangles;
}

void print_triangles(triangle_t* triangle, size_t count_of_triangle) {
    for (int i = 0; i < count_of_triangle; i++) {
        triangle[i].print();
    }
}
