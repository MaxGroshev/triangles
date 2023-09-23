#pragma once

//-----------------------------------------------------------------------------------------

TEST(point_test, point_constructor) {
    point_t p1(0, -2.89, 1000);

    EXPECT_DOUBLE_EQ(p1.x, 0);
    EXPECT_DOUBLE_EQ(p1.y, -2.89);
    EXPECT_DOUBLE_EQ(p1.z, 1000);
}

TEST(vector_test, vector_constructor) {
    point_t p1(0, -2.89, 1000);
    point_t p2(-999, 999, 0);
    vector_t vector(p1, p2);

    EXPECT_DOUBLE_EQ(vector.a, -999);
    EXPECT_DOUBLE_EQ(vector.b, 1001.89);
    EXPECT_DOUBLE_EQ(vector.c, -1000);
}

//-----------------------------------------------------------------------------------------
