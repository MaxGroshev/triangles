#include "./unteraction_with_user.hpp"

//-----------------------------------------------------------------------------------------

triangle_t* get_user_data(std::istream & in_strm) {
    size_t count_of_triangles  = get_count_of_triangles(in_strm);
    return get_users_triangles(count_of_triangles);
}

size_t get_count_of_triangles(std::istream & in_strm) {
    ASSERT (!in_strm.eof ());

    int count_of_triangles = 0;
    in_strm >> count_of_triangles;
    if (!in_strm.good ()) {
        std::cout << "\nWrong input of count of triangles\n";
        exit(-1);
    }

    LOG_DEBUG (count_of_triangles, '\n');
    return count_of_triangles;
}

triangle_t* get_users_triangles(const size_t count_of_triangles,  std::istream & in_strm) {
    triangle_t* triangles = new triangle_t [count_of_triangles];
    ASSERT(triangles != nullptr);

    point_t p1;
    point_t p2;
    point_t p3;
    for (int i = 0; i < count_of_triangles; i++) {
        in_strm >> p1.x >> p1.y >> p1.z;
        in_strm >> p2.x >> p2.y >> p2.z;
        in_strm >> p3.x >> p3.y >> p3.z;
        if (!in_strm.good ()) {
            std::cout << "\nWrong input of coordinates of triangles\n";
            exit(-1);
        }
        triangles[i].set (p1, p2, p3);
    }

    return triangles;
}

//double
