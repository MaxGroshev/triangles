#pragma once

//-----------------------------------------------------------------------------------------

class plane_test : public ::testing::Test {
    protected:
        void SetUp() {
            //if static SetUpTestSuit this will be created once
        }
        point_t p1 {-2.75, 3.17, 3}; //probably make static
        point_t p2 {-2.22, 2.98, 0};
        point_t p3 {3.34, -3.98, 0};

        plane_t plane {p1, p2, p3};
};

//-----------------------------------------------------------------------------------------

TEST_F(plane_test, intersection_of_line_and_plane) {
    point_t line_p1(0, 0, 0);
    point_t line_p2(3, 0, 0);
    line_t inter_line(line_p1, line_p2);
    point_t inter_point = plane.find_point_of_intersection(inter_line);

    EXPECT_TRUE(inter_point.x - 0.16 < calculation_error);
    EXPECT_DOUBLE_EQ(inter_point.y, 0);
    EXPECT_DOUBLE_EQ(inter_point.z, 0);
}

//-----------------------------------------------------------------------------------------
