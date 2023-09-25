#include "./triangles_ui/ui.hpp"
#include "./figures/include/triangle.hpp"

//-----------------------------------------------------------------------------------------

int main() {
    std::vector<size_t> intersect_triangles = triangle_ui::get_and_test_user_data(std::cin);

    LOG_DEBUG("\nRESULT:\n");
    for (int i = 0; i < intersect_triangles.size(); i++) {
        std::cout << intersect_triangles[i] << " \n";
    }

    return 0;
}
