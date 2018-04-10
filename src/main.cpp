#include "argh.h"
#include "FrequencyReaderBuilder.h"
#include "ThreadSpawner.h"
#include <iostream>

int main(int argc, const char **argv) {
    argh::parser args({"-u", "--update-time"});
    args.parse(argc, argv);

    if (args[0].empty()){
        std::cout << "Error" << std::endl;
        return 0;
    }

    // Read core IDs from positional args
    std::vector<unsigned short> cores;
    int i = 1;
    while (!args[i].empty()) {
        cores.push_back((unsigned short) std::stoi(args[i++]));
    }
    std::cout << cores.size() << std::endl;
    for (auto c : cores){
        std::cout << c << std::endl;
    }

    // Read frequency update time
    unsigned freq_update_time;
    args({"-u", "--update-time"}, 10000) >> freq_update_time;

    ThreadSpawner spawner;
    FrequencyReader *reader = FrequencyReaderBuilder::build(cores);

    auto frequencies = reader->get_frequencies();
    for (i = 0; i < cores.size(); i++) {
        std::cout << "Core " + std::to_string(cores[i]) + ": " + std::to_string(frequencies[i]) + " MHz" << std::endl;
    }

    for (unsigned short c : cores) {
        spawner.spawn(c);
        std::this_thread::sleep_for(std::chrono::milliseconds(freq_update_time));

        frequencies = reader->get_frequencies();
        for (i = 0; i < cores.size(); i++) {
            std::cout << "Core " + std::to_string(cores[i]) + ": " + std::to_string(frequencies[i]) + " MHz"
                      << std::endl;
        }
    }

    return 0;
}