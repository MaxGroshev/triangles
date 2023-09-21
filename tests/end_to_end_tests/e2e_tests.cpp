#include "./e2e_tests.hpp"

//-----------------------------------------------------------------------------------------

using namespace tests;

int run_e2e_tests() {
    std::ifstream input_file;
    input_file.open("../end_to_end_tests//e2e_tests.txt");
	ASSERT(input_file.is_open());

    size_t count_of_triangles = get_count_of_triangles(input_file);
    std::cout << count_of_triangles;
    triangle_t* triangles     = get_users_triangles(count_of_triangles, input_file);

    print_triangles(triangles, count_of_triangles);

    vector_ss intersect_triangles = start_tests(count_of_triangles, triangles);
    vector_ss correct_res         = get_correct_res(input_file);

    input_file.close();
    delete [] triangles;

    return 0;
}

vector_ss start_tests(size_t count_of_triangles, triangle_t* triangles) {
    vector_ss intersect_triangles;

    for (int i = 0; i < count_of_triangles; i++) {
        for (int j = i + 1; j <  count_of_triangles; j++) {
            if (triangles[i].intersect(triangles[i])) {
                intersect_triangles.push_back(std::make_pair(i, j));
            }
        }
    }

    return intersect_triangles;
}

//-----------------------------------------------------------------------------------------

vector_ss get_correct_res(std::istream & in_strm) {
    vector_ss res;
    size_t count_of_trian = 0;
    in_strm >> count_of_trian;
    ASSERT(in_strm.good ());

    int num_of_intersected = 0;
    int num_of_intersect   = 0;
    for (int i = 0; i < count_of_trian; i++) {
        in_strm >> num_of_intersected >> num_of_intersect;
        res.push_back(std::make_pair(num_of_intersected, num_of_intersect));
    }

    return res;
}
