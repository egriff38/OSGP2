//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_DISPATCHER_H
#define PHASE_2_DISPATCHER_H

#include <queue>
#include "CPU.h"
#include "MMU.h"
#include "PCB.h"

/*
 * Dispatcher objects will be created in separate threads - one per CPU. The constructor takes
 * all the needed queues as parameters. When start() is called, the dispatcher will begin to
 * load jobs from the ready queue to the CPU. When the CPU is finished
 * with a job, the dispatcher will determine whether the job is finished or blocked
 * and place it on the appropriate queue, then get another job for the CPU if one is available.
 * If none is available, it will sleep temporarily. If all jobs are completed, it will exit.
 */

class Dispatcher {
public:
    Dispatcher(std::priority_queue<PCB> ready_queue, M_queue io_queue, M_queue pf_queue, M_queue done_queue);
    start();
private:
    MMU mmu;
    PCB pcb;
    CPU cpu;
};

#endif //PHASE_2_DISPATCHER_H
