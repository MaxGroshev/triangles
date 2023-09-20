#include "./e2e_tests.hpp"

//-----------------------------------------------------------------------------------------

int run_e2e_tests() {
    std::ifstream input_file;
    input_file.open("./e2e_tests.txt");
	ASSERT(input_file.is_open());

    size_t count_of_triangles = get_count_of_triangles();
    triangle_t* triangles     = get_users_triangles(count_of_triangles, input_file);

    std::vector<std::pair<size_t, size_t>> intersect_triangles =
                                            start_tests(count_of_triangles, triangles);

    input_file.close();
    delete [] triangles;
}

std::vector<std::pair<size_t, size_t>> start_tests(size_t count_of_triangles,
                                                   triangle_t* triangles) {
    std::vector<std::pair<size_t, size_t>>intersect_triangles;

    for (int i = 0; i < count_of_triangles; i++) {
        for (int j = i + 1; j <  count_of_triangles; j++) {
            if (triangles[i].intersect(triangles[i])) {
                intersect_triangles.push_back(i, j);
            }
        }
    }

    return intersect_triangles;
}
