//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_DISPATCHER_H
#define PHASE_2_DISPATCHER_H

#include <queue>
#include "CPU.h"
#include "MMU.h"
#include "PCB.h"
#include "Mutex_queues.cpp"
#include "Log.h"

#include <mutex>
#include <tuple>

/*
 * The Dispatcher namespace contains only the start function, which gets called from a thread with
 * all the necessary queues
 * start: A static function that must me given an mmu, ready_queue, io_queue, and done_queue
 * The function will be called in a thread as mentioned before, and its job is to run a cpu and pull
 * from the ready_queue. When the done_queue is full (at 30), the thread will end. 
 */

namespace Dispatcher {
    static std::mutex lock_talk;

    void start(MMU *mmu, M_priority_queue<PCB*> *ready_queue, M_queue<blocking_info*> *blocked_queue, M_queue<PCB*> *done_queue, int i, Log* m_log);


};

#endif //PHASE_2_DISPATCHER_H
