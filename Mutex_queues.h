//
// Created by Charlie McDermitt on 11/8/17.
//

#ifndef PHASE_2_MUTEX_QUEUES_H
#define PHASE_2_MUTEX_QUEUES_H

#include <queue>

template <class T>
class M_queue {
public:
    M_queue();
    void push(T input);
    T pop();
private:
    std::queue<T> data;
};

template <class T>
class M_priority_queue {
public:
    M_queue();
    void push(T input);
    T pop();
private:
    std::priority_queue<T> data;
};

#endif //PHASE_2_MUTEX_QUEUES_H
