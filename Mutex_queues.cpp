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

template <class T>
class M_queue {
public:
    M_queue<T>()
    {
        data = std::queue<T>();
    }
    void push(T input)
    {
        mutex.lock();
        data.push(input);
        mutex.unlock();
    }
    T pop(){
        mutex.lock();
        T t = data.front();
        data.pop();
        mutex.unlock();
        return t;
    }
    int getSize()
    {
        mutex.lock();
        int size = data.size();
        mutex.unlock();
        return size;
    }

private:
    std::queue<T> data;
    std::mutex mutex;
};

template <class U>
class M_priority_queue {
public:
    M_priority_queue<U>(){
        data = std::priority_queue<U>();
    }
    void push(U input){
        mutex.lock();
        data.push(input);
        mutex.unlock();
    }
    U pop(){
        mutex.lock();
        U t = data.top();
        data.pop();
        mutex.unlock();
        return t;
    }
    int getSize(){
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





