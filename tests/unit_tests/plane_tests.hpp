#pragma once

using namespace geom_figures;

//-----------------------------------------------------------------------------------------

class plane_test : public ::testing::Test {
    protected:
        void SetUp() {
            //if static SetUpTestSuit this will be created once
        }
        point_t compl_p1 {-2.75, 3.17, 3};
        point_t compl_p2 {-2.22, 2.98, 0};
        point_t compl_p3 {3.34, -3.98, 0};

        point_t simpl_p1 {0, 0, 1};
        point_t simpl_p2 {-1, 1, 0};
        point_t simpl_p3 {-1, -1, 0};

        plane_t complicated_plane {compl_p1, compl_p2, compl_p3};
        plane_t simple_plane {simpl_p1, simpl_p2, simpl_p3};
};

//-----------------------------------------------------------------------------------------

TEST_F(plane_test, intersection_of_line_and_plane) {

    point_t line_p1(0, 0, 0);
    point_t line_p2(3, 0, 0);
    line_t inter_line(line_p1, line_p2);
    point_t inter_point = complicated_plane.find_point_of_intersection(inter_line);

    EXPECT_TRUE(inter_point.x - 0.16 < calculation_error);
    EXPECT_DOUBLE_EQ(inter_point.y, 0);
    EXPECT_DOUBLE_EQ(inter_point.z, 0);
}

TEST_F(plane_test, define_pos_of_planes) {

    point_t t_p1(0, 0, 2);
    point_t t_p2(-1, 1, 1);
    point_t t_p3(-1, -1, 1);
    plane_t test_plane {t_p1, t_p2, t_p3};

    ASSERT_TRUE(
        simple_plane.def_pos_of_planes(complicated_plane) == pos_of_the_planes::CROSSES);
    ASSERT_TRUE(
        simple_plane.def_pos_of_planes(simple_plane)      == pos_of_the_planes::COINCIDE);
    ASSERT_TRUE(
        simple_plane.def_pos_of_planes(test_plane)        == pos_of_the_planes::PARALLEL);
}

TEST_F(plane_test, define_point_is_in_plane) {

    point_t point_in_plane(-1, 0, 0);
    point_t point_out_plane(1, 1, 1);

    ASSERT_TRUE(simple_plane.is_point_in_plane(point_in_plane));
    ASSERT_FALSE(simple_plane.is_point_in_plane(point_out_plane));
}

//-----------------------------------------------------------------------------------------
