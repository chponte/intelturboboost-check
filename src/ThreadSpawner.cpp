//
// Created by christian on 27/03/18.
//

#include <vector>
#include <iostream>
#include "ThreadSpawner.h"


ThreadSpawner::~ThreadSpawner() {
    while (!threads.empty()) {
        pthread_cancel(threads.back());
        threads.pop_back();
    }
}

void ThreadSpawner::spawn(const int &core) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset);

    std::thread t(&ThreadSpawner::infinite_workload, this);
    threads.push_back(t.native_handle());
    pthread_setaffinity_np(t.native_handle(), sizeof(cpu_set_t), &cpuset);
    t.detach();
}

void ThreadSpawner::infinite_workload() {
    double sum = 0;
    while (true) {
        sum += 1 / sum;
    }
}
