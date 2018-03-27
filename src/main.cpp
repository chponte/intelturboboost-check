#include <iostream>
#include "ThreadSpawner.h"


int main(int argc, const char **argv) {
    if (argc < 2) {
        std::cout << "Error" << std::endl;
        return 0;
    }

    constexpr unsigned freq_update_time = 10000;
    const std::string cmd("cat /proc/cpuinfo | grep MHz");

    const unsigned num_cores = (unsigned int) std::stoul(argv[1]);
    ThreadSpawner spawner;
    for (int i = 0; i < num_cores; i++) {
        spawner.spawn(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(freq_update_time));
        system(cmd.c_str());
    }

    return 0;
}