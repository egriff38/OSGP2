//
// Created by Charlie McDermitt on 11/8/17.
//

#ifndef PHASE_2_MUTEX_QUEUES_H
#define PHASE_2_MUTEX_QUEUES_H

#include <mutex>
#include <queue>
#include <list>
#include <functional>
#include <iostream>
#include "PCB.h"

template<class T>
class M_queue {
public:
    M_queue<T>() {
        data = std::queue<T>();
        popped = 0;
    }

    void push(T input) {
        mutex.lock();
        data.push(input);
        mutex.unlock();
    }

    T pop() {
        mutex.lock();
        if (data.size() == 0) {
            mutex.unlock();
            return nullptr;
        }
        T t = data.front();
        data.pop();
        popped++;
        mutex.unlock();
        return t;
    }

    int getSize() {
        mutex.lock();
        int size = data.size();
        mutex.unlock();
        return size;
    }

    int getPopped() {
        mutex.lock();
        int s = popped;
        mutex.unlock();
        return popped;
    }

private:
    std::queue<T> data;
    std::mutex mutex;
    int popped;
};

template<class U>
class M_priority_queue {
public:
    static bool comp_priority(PCB *p1, PCB *p2) {
        return p1->job_pri > p2->job_pri;
    }

    static bool comp_sjf(PCB *p1, PCB *p2) {
        return p1->job_size > p2->job_size;
    }

    //  typename compare = std::less<U>;
    M_priority_queue<U>() {
        data = std::list<U>();
    }

    void push(U input) {
        mutex.lock();
        data.push_back(input);
        if (PCB::SORT == PCB::SORTING_METHOD::PRIO)
            data.sort(comp_priority);
        else if (PCB::SORT == PCB::SORTING_METHOD::SJF)
            data.sort(comp_sjf);
        mutex.unlock();
    }

    U pop() {
        mutex.lock();
        if (data.size() == 0) {
            mutex.unlock();
            return nullptr;
        }
        U u = data.front();
        data.pop_front();
        mutex.unlock();
        return u;
    }

    int getSize() {
        mutex.lock();
        int size = data.size();
        mutex.unlock();
        return size;
    }

private:
    std::list<U> data;
    std::mutex mutex;
};




#endif //PHASE_2_MUTEX_QUEUES_H





