#pragma once

using namespace geom_figures;

//-----------------------------------------------------------------------------------------

TEST(point_test, point_constructor) {
    point_t p1(0, -2.89, 1000);

    EXPECT_DOUBLE_EQ(p1.x, 0);
    EXPECT_DOUBLE_EQ(p1.y, -2.89);
    EXPECT_DOUBLE_EQ(p1.z, 1000);
}

//-----------------------------------------------------------------------------------------
