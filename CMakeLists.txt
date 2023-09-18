cmake_minimum_required (VERSION 3.21)

#-----------------------------------------------------------------------------------------

# project (trian)
# project (not_trian)
set (CMAKE_BUILD_TYPE "Debug")
set (TESTING_ENABLED ON)

#-----------------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions (MY_DEBUG)
    message ("Debug_version")
endif ()

#-----------------------------------------------------------------------------------------

#Root dir src
set (SOURCE
    main.cpp)

#Debug
set (DEBUG_UTILS
    ./debug_utils/error_control.cpp)

#Headers
set (FIGURES
    figures/point.hpp
    figures/vector.hpp
    figures/line.hpp
    figures/plane.hpp
    figures/triangle.hpp)

#-----------------------------------------------------------------------------------------

add_executable   (trian ${FIGURES} ${SOURCE}  ${DEBUG_UTILS})

if (TESTING_ENABLED)
    add_subdirectory (./tests/unit_tests/)
endif ()
