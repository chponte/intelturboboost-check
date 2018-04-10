set(FREQ_READER_IMPLEMENTATION "cpuinfo" CACHE STRING "Select CPU frequency reader implementation")
set_property(CACHE FREQ_READER_IMPLEMENTATION PROPERTY STRINGS "cpuinfo" "PCM")

if (FREQ_READER_IMPLEMENTATION STREQUAL "cpuinfo")
    list(APPEND FREQ_READER_SOURCES CPUInfoFrequencyReader.cpp CPUInfoFrequencyReader.h)
elseif (FREQ_READER_IMPLEMENTATION STREQUAL "PCM")
    list(APPEND FREQ_READER_SOURCES PCMFrequencyReader.cpp PCMFrequencyReader.h)
    set(PCM_EXECUTABLE_PATH "/opt/cesga/sistemas/pcm/pcm.x" CACHE STRING "Path to PCM executable")
endif ()

configure_file(Definitions.h.in ${PROJECT_BINARY_DIR}/src/Definitions.h)

include_directories(${PROJECT_BINARY_DIR}/src/)
add_executable(itb-check main.cpp ThreadSpawner.cpp ThreadSpawner.h FrequencyReader.h FrequencyReaderBuilder.h ${FREQ_READER_SOURCES})
target_link_libraries(itb-check "${CMAKE_THREAD_LIBS_INIT}")