cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(trian)

#-----------------------------------------------------------------------------------------

#Root dir src
set(SOURCE
    ./main.cpp
    ./triangles_ui/ui.cpp
    ./my_math/my_math_func.cpp)

#Figures
set(FIGURES_SRC
    ./figures/src/line.cpp
    ./figures/src/plane.cpp
    ./figures/src/triangle.cpp
    ./figures/src/vector.cpp)

#Debug
set(DEBUG_UTILS
    ../debug_utils/error_control.cpp)

#Headers
include_directories(./figures/include)

#-----------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${FIGURES_SRC} ${SOURCE} ${DEBUG_UTILS})




