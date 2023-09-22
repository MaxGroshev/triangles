#include "./triangles_ui/ui.hpp"
#include "./figures/triangle.hpp"

//-----------------------------------------------------------------------------------------

using namespace triangle_ui;

int main() {
    std::vector<size_t> intersect_triangles = test_user_data(std::cin);

    //std::cout << intersect_triangles.size();
    for (int i = 0; i < intersect_triangles.size(); i++) {
        std::cout << intersect_triangles[i] << " \n";
    }

    return 0;
}
