cmake_minimum_required(VERSION 3.20)
project(Project3TreeFiles)

set(CMAKE_C_STANDARD 14)

add_executable(Project3TreeFiles
        AVLTree.h
        BinarySearchTree.h
        SplayTree.h main.cpp)
