//
// Created by charlie on 11/16/17.
//

#include "Block_manager.h"
#include <thread>
#include <chrono>

void Block_manager::start(MMU *mmu, M_queue<PCB*> *readyish_queue, M_queue<PCB*> *blocked_queue, M_queue<PCB*> *pf_queue) {
    bool this_is_true;
    int count = 0;
    PCB *temp;
    using namespace std::chrono_literals;

    while(this_is_true) {
        if (blocked_queue->getSize() != 0) {
        temp = blocked_queue->pop();
           if (temp->state == PCB::PROCESS_STATUS::PAGE_FAULT)
                clear_pf(mmu, temp);
           else if (temp->state == PCB::PROCESS_STATUS::IO_BLOCKED)
                clear_io(mmu, temp);
           else
               std::cout << "Block_manager error: received non-blocked PCB " + temp->job_id << std::endl;
           readyish_queue->push(temp);
        }

        std::this_thread::sleep_for(2ns);
    }

}

void Block_manager::clear_io(MMU *mmu, PCB *p) {

}

void Block_manager::clear_pf(MMU *mmu, PCB *p) {

}
