//
// Created by conrad on 11/7/17.
//

#ifndef PHASE_2_DISPATCHER_CPP
#define PHASE_2_DISPATCHER_CPP

#include "CPU.h"
#include "MMU.h"
#include <thread>
#include <chrono>
#include <atomic>
#include "Mutex_queues.cpp"
#include "Dispatcher.h"


namespace Dispatcher {

    static void start(MMU *mmu, M_priority_queue<PCB *> *ready_queue, M_queue<blocking_info*> *blocked_queue,
                      M_queue<PCB *> *done_queue, int i) {
        using namespace std::chrono_literals;
        CPU *cpu = new CPU(mmu, production);
        PCB *current;
        bool itstrue  = true;
        while (itstrue) {
            current = ready_queue->pop();
            if (current != nullptr) {
                Dispatcher::lock_talk.lock();
                std::cout << "PCB NUM " << current->job_id << "\n";
                std::cout << "Using CPU " << i << "\n";
                Dispatcher::lock_talk.unlock();
                current->state = PCB::RUNNING;
                   cpu->load_pcb(current);
                 while (cpu->state->state == PCB::RUNNING)
                     cpu->Operate();
                  cpu->store_pcb();
                current->state = PCB::COMPLETED;
                done_queue->push(current);
                /*Dispatcher::lock_talk.lock();
                std::cout << "Jobs Completed " << done_queue->getPopped() << "\n\n";
                Dispatcher::lock_talk.unlock();*/
            } else {
                /*Dispatcher::lock_talk.lock();
                std::cout << "Current = nullptr \n";
                Dispatcher::lock_talk.unlock();*/
            }

            std::this_thread::sleep_for(2ns);
        }

    }
};
#endif