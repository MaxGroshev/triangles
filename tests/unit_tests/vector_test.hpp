#pragma once

using namespace geom_figures;

//-----------------------------------------------------------------------------------------

class vector_test : public ::testing::Test {
    protected:
        void SetUp() {

        }
        point_t v1_begin {13, 2, 6};
        point_t v1_end   {-1, 1, 99};

        point_t v2_begin {-1, -1, 0};
        point_t v2_end   {0, 5, 6};

        vector_t vector_1 {v1_begin, v1_end};
        vector_t vector_2 {v2_begin, v2_end};
};

//-----------------------------------------------------------------------------------------

TEST_F(vector_test, vector_constructor) {

    point_t p1(0, -2.89, 1000);
    point_t p2(-999, 999, 0);
    vector_t vector(p1, p2);

    EXPECT_DOUBLE_EQ(vector.a, -999);
    EXPECT_DOUBLE_EQ(vector.b, 1001.89);
    EXPECT_DOUBLE_EQ(vector.c, -1000);
}

TEST_F(vector_test, find_angle) {

    ASSERT_TRUE(my_abs(vector_1.find_angle(vector_2) - 0.67) < calculation_error);
}

TEST_F(vector_test, dot_product) {

    ASSERT_TRUE(vector_1.dot_product(vector_2) == 538);
}

// TEST_F(vector_test, point_on_triangle) {
//
//     point_t t_p1(0, 0, 0);
//     point_t t_p2(0, 1, 0);
//     point_t t_p3(1, 0, 0);
//     point_t t_p7(0.5, 0.5, 0);
//
//     ASSERT_TRUE(triangle_1.point_in_triangle(t_p1));
//     ASSERT_TRUE(triangle_1.point_in_triangle(t_p2));
//     ASSERT_TRUE(triangle_1.point_in_triangle(t_p3));
//     EXPECT_TRUE(triangle_1.point_in_triangle(t_p7));
// }

//-----------------------------------------------------------------------------------------

