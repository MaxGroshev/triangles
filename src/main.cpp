#include "ui.hpp"
#include "triangle.hpp"

using namespace time_control;
//-----------------------------------------------------------------------------------------

int main() {
    auto start_time = chrono_cur_time ();

    std::vector<size_t> intersect_triangles = triangle_ui::get_and_test_user_data(std::cin);

    std::sort(intersect_triangles.begin(), intersect_triangles.end());
    LOG_DEBUG("\nRESULT:\n");
    for (auto const& intersected : intersect_triangles) {
        std::cout << intersected << " \n";
    }
    auto end_time = chrono_cur_time ();
    // std::cerr << "\n==============================\n";
    // std::cerr << "Run time: " <<(end_time - start_time) / 0.1ms  << '\n';
    return 0;
}
