cmake_minimum_required(VERSION 3.1.3)
project(IntelTurboBoost-Check)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

find_package(Threads REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(src)