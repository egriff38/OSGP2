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

    void start(MMU *mmu, M_priority_queue<PCB*> *ready_queue, M_queue<blocking_info*> *blocked_queue, M_queue<PCB*> *done_queue, int i) {
        using namespace std::chrono_literals;
        CPU *cpu = new CPU(mmu, production);
        PCB *current;
        bool itstrue  = true;
        int* temp_int_pointer;
        while (itstrue) {
            current = ready_queue->pop();
            if (current != nullptr) {
                Dispatcher::lock_talk.lock();
               // std::cout << "PCB NUM " << current->job_id << "\n";
                //std::cout << "Using CPU " << i << "\n";
                Dispatcher::lock_talk.unlock();
                current->state = PCB::RUNNING;
                cpu->load_pcb(current);
                while (cpu->state->state == PCB::RUNNING)
                    cpu->Operate();
                current = cpu->store_pcb();
                if(current->state==PCB::COMPLETED){
                    std::cout << "Finishing PCB " << cpu->state->job_id << "\n";
                    for(auto s : current->page_table)
                    {
                        if(std::get<2>(s.second)){
                            if(std::get<1>(s.second) == -1)
                                throw std::invalid_argument("-1 tried to add to page");
                           temp_int_pointer = new int(std::get<1>(s.second));

                            mmu->free_ram_frames->push(temp_int_pointer);
                        }
                    }
                    done_queue->push(current);

                }
                else if(current->state==PCB::IO_BLOCKED || current->state == PCB::PAGE_FAULT){
               //     std::cout << "Unloading job " << current->job_id << "\n";
                    auto a = new blocking_info();
                    a -> pcb = current;
                    a -> page_num = cpu->page_trip;

                    blocked_queue->push(a);

                }
                /*Dispatcher::lock_talk.lock();
                std::cout << "Jobs Completed " << done_queue->getPopped() << "\n\n";
                Dispatcher::lock_talk.unlock();*/
            } else {
               // std::cout << "OH NO A NULLPTR" << std::endl;
                /*Dispatcher::lock_talk.lock();
                std::cout << "Current = nullptr \n";
                Dispatcher::lock_talk.unlock();*/
            }

            std::this_thread::sleep_for(2ns);
        }

    }
};
#endif