#pragma once

using namespace geom_figures;

//-----------------------------------------------------------------------------------------

class triangle_test : public ::testing::Test {
    protected:
        void SetUp() {
            //if static SetUpTestSuit this will be created once
        }
        point_t p1 {0, 0, 0}; //probably make static
        point_t p2 {0, 1, 0};
        point_t p3 {1, 0, 0};

        point_t p4 {-1, -1, 0};
        point_t p5 {0, 5, 0};
        point_t p6 {5, 0, 0};

        triangle_t triangle_1 {p1, p2, p3};
        triangle_t triangle_2 {p4, p5, p6};
};

//-----------------------------------------------------------------------------------------

TEST_F(triangle_test, point_in_triangle) {

    point_t t_p1(0.5, 0.4, 0);
    point_t t_p2(0.5, 0.3, 0);
    point_t t_p3(7e-06, 0.1, 0);

    ASSERT_TRUE(triangle_1.point_in_triangle(t_p1));
    ASSERT_TRUE(triangle_1.point_in_triangle(t_p2));
    ASSERT_TRUE(triangle_1.point_in_triangle(t_p3));
}

TEST_F(triangle_test, point_out_triangle) {

    point_t t_p1(2, 0.4, 0);
    point_t t_p2(0.7, 0.7, 0);
    point_t t_p3(-900, 3e+06, 0);

    ASSERT_FALSE(triangle_1.point_in_triangle(t_p1));
    ASSERT_FALSE(triangle_1.point_in_triangle(t_p2));
    ASSERT_FALSE(triangle_1.point_in_triangle(t_p3));
}

TEST_F(triangle_test, point_on_triangle) {

    point_t t_p1(0, 0, 0);
    point_t t_p2(0, 1, 0);
    point_t t_p3(1, 0, 0);
    point_t t_p7(0.5, 0.5, 0);

    ASSERT_TRUE(triangle_1.point_in_triangle(t_p1));
    ASSERT_TRUE(triangle_1.point_in_triangle(t_p2));
    ASSERT_TRUE(triangle_1.point_in_triangle(t_p3));
    EXPECT_TRUE(triangle_1.point_in_triangle(t_p7));
}

//-----------------------------------------------------------------------------------------

TEST_F(triangle_test, intersect_in_same_plane) {

    ASSERT_TRUE(triangle_1.intersect_in_same_plane(triangle_2));
    ASSERT_TRUE(triangle_2.intersect_in_same_plane(triangle_1));
}
