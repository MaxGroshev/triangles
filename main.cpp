#include "./figures/triangle.hpp"

int main() {

    point_t p1 (-2.75, 3.17, 3);
    point_t p2 (-2.22, 2.98, 3);
    point_t p3 (3.34, -3.38, 0);

    point_t p4 (0, 0, 0);
    point_t p5 (0, 1, 1);
    point_t p6 (0, 1, 0);

    triangle_t trian1 (p1, p2, p3);
    triangle_t trian2 (p4, p5, p6);
    bool res = trian1.intersect(trian2);
    if (res) std::cout << "Intersect\n";
    //trian1.print();

    return 0;
}


