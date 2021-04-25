cmake_minimum_required(VERSION 3.17)
project(laba7)

set(CMAKE_CXX_STANDARD 14)

add_executable(laba7 main.cpp AVL_Tree.h Binary_Tree.h RedBlack_Tree.h Relation.h)
add_executable(task3 task_3.cpp)
add_executable(task4 task4.cpp)