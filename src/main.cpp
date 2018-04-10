#include "ThreadSpawner.h"
#include "FrequencyReader.h"
#include "CPUInfoFrequencyReader.h"
#include "PCMFrequencyReader.h"
#include <iostream>

int main(int argc, const char **argv) {
    if (argc < 2) {
        std::cout << "Error" << std::endl;
        return 0;
    }

    constexpr unsigned freq_update_time = 10000;

    const std::vector<unsigned short> cores{0};

    ThreadSpawner spawner;

    FrequencyReader *reader = new CPUInfoFrequencyReader(cores);
    //FrequencyReader *reader = new PCMFrequencyReader(cores);

    auto frequencies = reader->get_frequencies();
    for (int i = 0; i < cores.size(); i++) {
        std::cout << "Core " + std::to_string(cores[i]) + ": " + std::to_string(frequencies[i]) + " MHz" << std::endl;
    }

    for (unsigned short c : cores) {
        spawner.spawn(c);
        std::this_thread::sleep_for(std::chrono::milliseconds(freq_update_time));

        frequencies = reader->get_frequencies();
        for (int i = 0; i < cores.size(); i++) {
            std::cout << "Core " + std::to_string(cores[i]) + ": " + std::to_string(frequencies[i]) + " MHz"
                      << std::endl;
        }
    }

    return 0;
}