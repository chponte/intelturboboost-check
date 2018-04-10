#include "argh.h"
#include "FrequencyReaderBuilder.h"
#include "ThreadSpawner.h"
#include <iostream>

void print_frequencies(const std::vector<unsigned short> &cores, const std::vector<double> &frequencies,
                       const std::string &print_prefix) {
    for (int i = 0; i < cores.size(); i++) {
        std::cout << print_prefix << "Core " + std::to_string(cores[i]) + ": " + std::to_string(frequencies[i]) + " MHz\n";
    }
}

int main(int argc, const char **argv) {
    argh::parser args({"-u", "--update-time"});
    args.parse(argc, argv);

    // Check if there is any argument or asked to print help
    if (args[{"h", "--help"}] || args[1].empty()){
        if (args[{"h", "--help"}]){
            std::cout << "Usage:\n";
        } else {
            std::cout << "Missing arguments:\n";
        }
        std::cout << args[0] << " [--update-time <milliseconds>] <core1 id> [<core2 id> ...]" << std::endl;
        return 0;
    }

    // Read core IDs from positional args
    std::vector<unsigned short> cores;
    int i = 1;
    while (!args[i].empty()) {
        cores.push_back((unsigned short) std::stoi(args[i++]));
    }

    // Read frequency update time
    unsigned freq_update_time;
    args({"-u", "--update-time"}, 10000) >> freq_update_time;

    ThreadSpawner spawner;
    FrequencyReader *reader = FrequencyReaderBuilder::build(cores);

    std::cout << "Initial frequencies:\n";
    print_frequencies(cores, reader->get_frequencies(), "\t");
    for (unsigned short c : cores) {
        std::cout << "Stressing core " << c << " and sleeping for " << freq_update_time << " ms...\n";
        spawner.spawn(c);
        std::this_thread::sleep_for(std::chrono::milliseconds(freq_update_time));
        print_frequencies(cores, reader->get_frequencies(), "\t");
    }
    std::cout << "\nTest finished!" << std::endl;
    return 0;
}