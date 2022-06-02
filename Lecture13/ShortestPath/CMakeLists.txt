cmake_minimum_required(VERSION 3.20)
project(ShortestPath)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ShortestPath
        DiEdge.h
        DiGraph.h
        IndexPQ.h
        ShortestPath.h
        test.cpp)
