cmake_minimum_required(VERSION 3.8)
project(project2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Customer.cpp Customer.h Cashier.cpp Cashier.h Barista.cpp Barista.h)
add_executable(project2 ${SOURCE_FILES})