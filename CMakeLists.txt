cmake_minimum_required (VERSION 3.5)

#-----------------------------------------------------------------------------------------

# project (trian)
# project (not_trian)
set (BUILD_TYPE  "DEBUG")

#-----------------------------------------------------------------------------------------

set (GCC_COMPILE_FLAGS      "-Wshadow -std=c++17 -Wall")
set (GCC_OPTIMIZATION_FLAGS "-O2 -DNDEBUG")
#add_compile_options(...) #Better way of adding flags?

set (CMAKE_CXX_FLAGS  "${GCC_COMPILE_FLAGS}")
if  (BUILD_TYPE STREQUAL "RELEASE")
    set (CMAKE_CXX_FLAGS  "${GCC_OPTIMIZATION_FLAGS}")
endif ()

#-----------------------------------------------------------------------------------------

#Root dir src
set (SOURCE
    main.cpp)

set (SOURCE1
    file.cpp)

add_executable (trian ${SOURCE})
add_executable (not_trian ${SOURCE1})
