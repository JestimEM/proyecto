cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

# Buscar GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Agregar el ejecutable
add_executable(untitled
        main.cpp
        MPointerGC.h
        MPointer.h
        DoublyLinkedList.h
        MPointer.tpp
        DoublyLinkedList.tpp)

# Enlazar con GoogleTest y pthread
target_link_libraries(untitled ${GTEST_LIBRARIES} pthread)
