cmake_minimum_required(VERSION 3.8)
project(GraphicsProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Shapes Lines Circles Curves Polygons Fillers utils)
add_executable(GraphicsProject ${SOURCE_FILES})