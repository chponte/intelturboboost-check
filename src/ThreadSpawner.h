//
// Created by christian on 27/03/18.
//

#ifndef INTELTURBOBOOST_TEST_THREADSPAWNER_H
#define INTELTURBOBOOST_TEST_THREADSPAWNER_H

#include <thread>
#include <vector>


class ThreadSpawner {
public:
    ~ThreadSpawner();

    void spawn(const int &core);

private:
    void infinite_workload();

    std::vector<pthread_t> threads;
};

#endif //INTELTURBOBOOST_TEST_THREADSPAWNER_H