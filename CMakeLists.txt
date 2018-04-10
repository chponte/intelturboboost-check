cmake_minimum_required(VERSION 3.1.3)
project(IntelTurboBoost-Check)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

add_executable(intelturboboost_test src/main.cpp src/ThreadSpawner.cpp src/ThreadSpawner.h src/FrequencyReader.h src/CPUInfoFrequencyReader.cpp src/CPUInfoFrequencyReader.h src/PCMFrequencyReader.cpp src/PCMFrequencyReader.h)
target_link_libraries(intelturboboost_test "${CMAKE_THREAD_LIBS_INIT}")
