cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(trian)

#-----------------------------------------------------------------------------------------

set(TESTING_ENABLED OFF CACHE BOOL [FORCE])

#-----------------------------------------------------------------------------------------

set(CMAKE_BUILD_TYPE "Debug")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(MY_DEBUG)
    message("Debug_version")
endif ()

#-----------------------------------------------------------------------------------------

#Root dir src
set(SOURCE
    interactio_with_user/unteraction_with_user.cpp
    main.cpp)

#Debug
set(DEBUG_UTILS
    ./debug_utils/error_control.cpp)

#Headers
set(FIGURES
    figures/point.hpp
    figures/vector.hpp
    figures/line.hpp
    figures/plane.hpp
    figures/triangle.hpp
    debug_utils/error_control.h
    interactio_with_user/unteraction_with_user.hpp)

#-----------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${FIGURES} ${SOURCE} ${LIN_ALGEBRA} ${DEBUG_UTILS})

if (TESTING_ENABLED)
    add_subdirectory(./tests/)
endif()

unset(TESTING_ENABLED CACHE)

