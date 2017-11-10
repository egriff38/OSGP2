//
// Created by conrad on 11/9/17.
//

#include "Mutex_queues.h"

template <class T>
M_queue<T>::M_queue() {
    data = std::queue<T>();
}

template <class T>
T M_queue<T>::pop() {
    mutex.lock();
    T t = data.front();
    data.pop();
    mutex.unlock();
    return t;

}

template <class T>
void M_queue<T>::push(T input) {
    mutex.lock();
    data.push(input);
    mutex.unlock();
}

template <class T>
M_priority_queue<T>::M_priority_queue() {
    data = std::priority_queue<T>();
}
template <class T>
T M_priority_queue<T>::pop() {
    mutex.lock();
    T t = data.top();
    data.pop();
    mutex.unlock();
    return t;
}

template <class T>
void M_priority_queue<T>::push(T input){
    mutex.lock();
    data.push(input);
    mutex.unlock(); 
}