//
// Created by charlie on 11/16/17.
//

#include "Block_manager.h"
#include <thread>
#include <chrono>

void Block_manager::start(MMU *mmu, M_queue<PCB*> *readyish_queue, M_queue<PCB*> *io_queue, M_queue<PCB*> *pf_queue) {
    bool this_is_true;
    int count = 0;
    PCB *temp;
    using namespace std::chrono_literals;

    while(this_is_true) {
        if (count % 2 == 0)
        {
            if (io_queue->getSize() != 0) {
                temp = io_queue->pop();
                clear_io(mmu, temp);
                readyish_queue->push(temp);
            }
        } else {
            if (pf_queue->getSize() != 0) {
                temp = pf_queue->pop();
                clear_pf(mmu, temp);
                readyish_queue->push(temp);
            }
        }

        std::this_thread::sleep_for(2ns);
    }

}

void Block_manager::clear_io(MMU *mmu, PCB *p) {

}

void Block_manager::clear_pf(MMU *mmu, PCB *p) {

}
