cmake_minimum_required (VERSION 3.21)

#-----------------------------------------------------------------------------------------

project (tests)

#-----------------------------------------------------------------------------------------

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


#-----------------------------------------------------------------------------------------

#Test src
set (SOURCE
    main.cpp)

#-----------------------------------------------------------------------------------------

add_executable            (${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE${GTEST_INCLUDE_DIRS})
target_link_libraries     (${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
