add_executable(intelturboboost_test main.cpp ThreadSpawner.cpp ThreadSpawner.h FrequencyReader.h CPUInfoFrequencyReader.cpp CPUInfoFrequencyReader.h PCMFrequencyReader.cpp PCMFrequencyReader.h)
target_link_libraries(intelturboboost_test "${CMAKE_THREAD_LIBS_INIT}")
