//
// Created by conrad on 11/7/17.
//
#include "CPU.h"
#include "MMU.h"
#include <thread>
#include <chrono>
#include "Mutex_queues.cpp"
#include "Dispatcher.h"

namespace Dispatcher{
 static void start(MMU *mmu, M_priority_queue<PCB *> *ready_queue, M_queue<PCB *> *io_queue,
                       M_queue<PCB *> *pf_queue, M_queue<PCB *> *done_queue) {
     using namespace std::chrono_literals;
     CPU *cpu = new CPU(new Ram(), production);
     PCB *current;
     while (done_queue->getSize() != 30) {

         current = ready_queue->pop();
         if (current != nullptr) {
             current->state = PCB::RUNNING;
             cpu->load_pcb(current);
             while (cpu->state.state == PCB::RUNNING)
                 cpu->Operate();
             cpu->store_pcb();
             done_queue->push(current);
         }

         std::this_thread::sleep_for(2ns);
     }

 }
};
