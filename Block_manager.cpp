//
// Created by charlie on 11/16/17.
//

#include "Block_manager.h"
#include <thread>
#include <chrono>

void Block_manager::start(MMU *mmu, M_queue<PCB *> *readyish_queue, M_queue<blocking_info*> *blocked_queue) {
    bool this_is_true;
    int count = 0;
    blocking_info *temp;
    using namespace std::chrono_literals; //for ns in sleep_for()

    while (this_is_true) {
        if (blocked_queue->getSize() != 0) {
            temp = blocked_queue->pop();
            if (temp->pcb->state == PCB::PROCESS_STATUS::PAGE_FAULT) {
                clear_pf(mmu, temp);
            } else if (temp->pcb->state == PCB::PROCESS_STATUS::IO_BLOCKED) {
                clear_io(mmu, temp);
            } else
                std::cout << "Block_manager error: received non-blocked PCB " + temp->pcb->job_id << std::endl;
        }
        readyish_queue->push(temp->pcb);
    }

    std::this_thread::sleep_for(2ns);
}

void Block_manager::clear_io(MMU *mmu, blocking_info *b) {
    //temp->
}

void Block_manager::clear_pf(MMU *mmu, blocking_info *b) {

}
