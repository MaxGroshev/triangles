cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(triangles_intersect)

#-----------------------------------------------------------------------------------------

set(TESTING_ENABLED ON CACHE BOOL [FORCE])

#-----------------------------------------------------------------------------------------

set(CMAKE_BUILD_TYPE "Release")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(MY_DEBUG)
    message("Debug_version")
endif ()

#-----------------------------------------------------------------------------------------

include_directories(${PROJECT_NAME} PRIVATE
                    ./debug_utils
                    ./src/triangles_ui/)

add_subdirectory(src/)

if (TESTING_ENABLED)
    add_subdirectory(./tests/)
endif()

unset(TESTING_ENABLED CACHE)

