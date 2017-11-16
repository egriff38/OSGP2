//
// Created by charlie on 11/16/17.
//

#ifndef PHASE_2_BLOCK_MANAGER_H
#define PHASE_2_BLOCK_MANAGER_H

#include "MMU.h"
#include "Mutex_queues.cpp"

namespace Block_manager {
    void start(MMU *mmu, M_queue<PCB*> *readyish_queue, M_queue<PCB*> *io_queue, M_queue<PCB*> *pf_queue);
    void clear_io(MMU *mmu, PCB *p);
    void clear_pf(MMU *mmu, PCB *p);
};

#endif //PHASE_2_BLOCK_MANAGER_H
