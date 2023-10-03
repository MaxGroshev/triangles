#include "ui.hpp"
#include "triangle.hpp"

//-----------------------------------------------------------------------------------------

int main() {
    std::vector<size_t> intersect_triangles = triangle_ui::get_and_test_user_data(std::cin);

    std::sort(intersect_triangles.begin(), intersect_triangles.end());
    LOG_DEBUG("\nRESULT:\n");
    for (auto const& intersected : intersect_triangles) {
        std::cout << intersected << " \n";
    }

    return 0;
}
