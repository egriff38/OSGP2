//
// Created by Charlie McDermitt on 11/8/17.
//

#ifndef PHASE_2_MUTEX_QUEUES_H
#define PHASE_2_MUTEX_QUEUES_H

#include <mutex>
#include <queue>

template <class T>
class M_queue {
public:
    M_queue<T>();
    void push(T input);
    T pop();
private:
    std::queue<T> data;
    std::mutex mutex;
};

template <class T>
class M_priority_queue {
public:
    M_priority_queue<T>();
    void push(T input);
    T pop();
private:
    std::priority_queue<T> data;
    std::mutex mutex;
};

#endif //PHASE_2_MUTEX_QUEUES_H
