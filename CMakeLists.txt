cmake_minimum_required(VERSION 2.8.12.2)
project(project2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Barista.cpp
    Barista.h
    Cashier.cpp
    Cashier.h
    Customer.cpp
    Customer.h
    main.cpp)

add_executable(project2 ${SOURCE_FILES})