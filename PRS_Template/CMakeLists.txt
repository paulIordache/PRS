cmake_minimum_required(VERSION 4.0)
project(lab_1)

set(CMAKE_CXX_STANDARD 20)


add_executable(lab_1 lab1.cpp
        core/src/Coordinates.cpp
        core/include/Coordinates.h
        core/src/Models.cpp
        core/include/Models.h)


find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(lab_1 ${OpenCV_LIBS})
