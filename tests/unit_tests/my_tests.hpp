#pragma once

//-----------------------------------------------------------------------------------------

TEST(point_test, point_constructor) {
    point_t p1(0, -2.89, 1000);

    ASSERT_TRUE(p1.x == 0);
    ASSERT_TRUE(p1.y == -2.89);
    ASSERT_TRUE(p1.z == 1000);
}

TEST(vector_test, vector_constructor) {
    point_t p1(0, -2.89, 1000);
    point_t p2(-999, 999, 0);
    vector_t vector(p1, p2);

    ASSERT_TRUE(vector.a == -999);
    ASSERT_TRUE(vector.b == 1001.89);
    ASSERT_TRUE(vector.c == -1000);
}
