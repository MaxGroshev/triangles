cmake_minimum_required (VERSION 3.21)

#-----------------------------------------------------------------------------------------

project (tests)

#-----------------------------------------------------------------------------------------

find_package(GTest REQUIRED)
# find_package(Python 2.7 REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#-----------------------------------------------------------------------------------------

#Unit_tests
set (UNIT_TESTS
    ./unit_tests/main.cpp)

# End_to_end_tests
set (E2E_TESTS
    ./end_to_end_tests/e2e_test.py)

#Debug
set (DEBUG_UTILS
    ../debug_utils/error_control/error_control.cpp)

#-----------------------------------------------------------------------------------------

include_directories(unit_tests PRIVATE ../src/figures/include/)

add_executable            (unit_tests ${UNIT_TESTS} ${HEADERS} ${DEBUG_UTILS})
target_include_directories(unit_tests PRIVATE${GTEST_INCLUDE_DIRS} ../debug_utils)
target_link_libraries     (unit_tests ${GTEST_BOTH_LIBRARIES} figures)

enable_testing()
add_test(NAME unit_testst COMMAND ./unit_tests) #do not know how to use

