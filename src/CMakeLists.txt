cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(triangles)

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
    ../debug_utils/error_control/error_control.cpp)

#-----------------------------------------------------------------------------------------

add_library(figures ${FIGURES_SRC})

add_executable(${PROJECT_NAME} ${SOURCE} ${DEBUG_UTILS})

target_link_libraries(${PROJECT_NAME} figures)

target_include_directories(${PROJECT_NAME} PRIVATE
                            ./figures/include/
                            ../debug_utils
                            ./octree/
                            ./triangles_ui/)

target_include_directories(figures PRIVATE
                            ./figures/include/
                            ./octree/
                            ../debug_utils
                            ./triangles_ui/)





