#pragma once

//-----------------------------------------------------------------------------------------

class triangle_test : public ::testing::Test {
    protected:
        void SetUp() {
            //if static SetUpTestSuit this will be created once
        }
        point_t p1 {0, 0, 0}; //probably make static
        point_t p2 {0, 1, 0};
        point_t p3 {1, 0, 0};

        triangle_t triangle {p1, p2, p3};
};

//-----------------------------------------------------------------------------------------

TEST_F(triangle_test, point_in_triangle) {
    point_t t_p4(0.5, 0.4, 0);
    point_t t_p5(0.5, 0.3, 0);
    point_t t_p6(7e-06, 0.1, 0);

    ASSERT_TRUE(triangle.point_in_triangle(t_p4));
    ASSERT_TRUE(triangle.point_in_triangle(t_p5));
    ASSERT_TRUE(triangle.point_in_triangle(t_p6));
}

TEST_F(triangle_test, point_out_triangle) {
    point_t t_p4(2, 0.4, 0);
    point_t t_p5(0.7, 0.7, 0);
    point_t t_p6(-900, 3e+06, 0);

    ASSERT_FALSE(triangle.point_in_triangle(t_p4));
    ASSERT_FALSE(triangle.point_in_triangle(t_p5));
    ASSERT_FALSE(triangle.point_in_triangle(t_p6));
}

TEST_F(triangle_test, point_on_triangle) {
    point_t t_p4(0, 0, 0);
    point_t t_p5(0, 1, 0);
    point_t t_p6(1, 0, 0);
    point_t t_p7(0.5, 0.5, 0);

    ASSERT_TRUE(triangle.point_in_triangle(t_p4));
    ASSERT_TRUE(triangle.point_in_triangle(t_p5));
    ASSERT_TRUE(triangle.point_in_triangle(t_p6));
    EXPECT_TRUE(triangle.point_in_triangle(t_p7));
}

// TEST(triangle_test, point_on_triangle) {
//     point_t p1(-2.75, 0, 0);
//     point_t t_p(0, 1, 0);
//     point_t t_p(1, 0, 0);
//     point_t t_p(0.5, 0.5, 0);
//
//     ASSERT_TRUE(triangle.point_in_triangle(t_p4));
//     ASSERT_TRUE(triangle.point_in_triangle(t_p5));
//     ASSERT_TRUE(triangle.point_in_triangle(t_p6));
//     EXPECT_TRUE(triangle.point_in_triangle(t_p7));
// }

//-----------------------------------------------------------------------------------------
