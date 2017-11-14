//
// Created by conrad on 11/9/17.
//

//
// Created by Charlie McDermitt on 11/8/17.
//

#ifndef PHASE_2_MUTEX_QUEUES_H
#define PHASE_2_MUTEX_QUEUES_H

#include <mutex>
#include <queue>
#include <functional>
#include <iostream>

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
    //  typename compare = std::less<U>;
    M_priority_queue<U>() {
        data = std::priority_queue<U>();
    }

    void push(U input) {
        mutex.lock();
        data.push(input);
        mutex.unlock();
    }

    U pop() {
        mutex.lock();
        if (data.size() == 0) {
            mutex.unlock();
            return nullptr;
        }
        U u = data.top();
        data.pop();
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
    std::priority_queue<U> data;
    std::mutex mutex;

};

#endif //PHASE_2_MUTEX_QUEUES_H





