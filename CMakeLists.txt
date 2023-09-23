cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(triangles_intersect)

#-----------------------------------------------------------------------------------------

enable_testing()
set(TESTING_ENABLED ON CACHE BOOL [FORCE])

#-----------------------------------------------------------------------------------------

set(CMAKE_BUILD_TYPE "Release")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(MY_DEBUG)
    message("Debug_version")
endif ()

#-----------------------------------------------------------------------------------------


if (TESTING_ENABLED)
    add_subdirectory(./tests/)
endif()


# add_test (NAME e2e_test
#     COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/end_to_end_tests/e2e_test.py# Or just COMMAND pytest
#     # WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )
# set_tests_properties(python-tests
#     PROPERTIES ENVIRONMENT "PYTHONPATH=${PROJECT_SOURCE_DIR}/src/mypyspace:$ENV{PYTHONPATH}")


add_subdirectory(triangles/ )

unset(TESTING_ENABLED CACHE)

