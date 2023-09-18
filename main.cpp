#include "./figures/triangle.hpp"
// #include "point.hpp"
// #include "line.hpp"

int main() {
    point_t p1 (0, 0, 0);
    point_t p2 (0, 1, 0);
    point_t p3 (1, 0, 0);

    std::cout << "Hello\n";
    for (int i = 0; i < 6; i++) {

    }
    triangle_t trian (p1, p2, p3);
    trian.print();

    return 0;
}


