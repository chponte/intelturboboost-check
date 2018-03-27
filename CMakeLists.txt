cmake_minimum_required(VERSION 3.9)
project(intelturboboost_test)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

add_executable(intelturboboost_test src/main.cpp src/ThreadSpawner.cpp src/ThreadSpawner.h)
target_link_libraries(intelturboboost_test "${CMAKE_THREAD_LIBS_INIT}")
