cmake_minimum_required (VERSION 3.21)

#-----------------------------------------------------------------------------------------

project (tests)

set (CMAKE_BUILD_TYPE "Debug")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions (MY_DEBUG)
    message ("Debug_version")
endif ()

#-----------------------------------------------------------------------------------------


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


#-----------------------------------------------------------------------------------------

#Unit_tests
set (UNIT_TESTS
    ./unit_tests/main.cpp)

#End_to_end_tests
set (E2E_TESTS
    ../interactio_with_user/unteraction_with_user.cp)

#Headers of figures
set (HEADERS
    ../figures/point.hpp
    ../figures/vector.hpp
    ../figures/line.hpp
    ../figures/plane.hpp
    ../debug_utils/error_control.h
    ../figures/triangle.hpp
    ./end_to_end_tests/e2e_tests.hpp
    )

#Debug
set (DEBUG_UTILS
    ../debug_utils/error_control.cpp)

#-----------------------------------------------------------------------------------------

add_executable            (unit_tests ${UNIT_TESTS} ${HEADERS} ${DEBUG_UTILS})
target_include_directories(unit_tests PRIVATE${GTEST_INCLUDE_DIRS})
target_link_libraries     (unit_tests ${GTEST_BOTH_LIBRARIES})

add_executable            (e2e_tests ${E2E_TESTS} ${HEADERS} ${DEBUG_UTILS})
