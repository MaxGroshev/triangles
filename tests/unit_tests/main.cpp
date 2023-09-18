#include "./unit_tests.hpp"

//-----------------------------------------------------------------------------------------

TEST(point_test, point_constructor) {
    ASSERT_FALSE(1 == 1);
}

int main (int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
