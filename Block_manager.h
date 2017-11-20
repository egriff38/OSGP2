//
// Created by charlie on 11/16/17.
//

#ifndef PHASE_2_BLOCK_MANAGER_H
#define PHASE_2_BLOCK_MANAGER_H

#include "MMU.h"
#include "Mutex_queues.cpp"
#include <tuple>

namespace Block_manager {
    void start(MMU *mmu, M_queue<PCB*> *readyish_queue, M_queue<blocking_info*> *blocked_queue);
    void clear_io(MMU *mmu, blocking_info *b);
    void clear_pf(MMU *mmu, blocking_info *b);
};

#endif //PHASE_2_BLOCK_MANAGER_H
