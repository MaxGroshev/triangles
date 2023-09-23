cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(trian)

#-----------------------------------------------------------------------------------------

#Root dir src
set(SOURCE
    ./main.cpp
    ./triangles_ui/ui.cpp
    ./my_math/my_math_func.cpp)

#Debug
set(DEBUG_UTILS
    ../debug_utils/error_control.cpp)

#Headers
set(FIGURES
    figures/point.hpp
    figures/vector.hpp
    figures/line.hpp
    figures/plane.hpp
    figures/triangle.hpp
    ./my_math/my_math_func.hpp
    ../debug_utils/error_control.h
    ./triangles_ui/ui.hpp)

#-----------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${FIGURES} ${SOURCE} ${DEBUG_UTILS})




