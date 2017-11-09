//
// Created by Eshin Griffith on 11/3/17.
//

/*The Scheduler class is used in the main thread and contains the Long Term Scheduler and the Short Term Scheduler
 * free_ram is used to determine whether or not ______________ (May need to be updated after paging)
 * get_ram_start(PCB *p) sets *p->ramStartAddress to an open space in RAM
 * load_pcb(PCB *p) puts PCB in RAM
 * remove_pcb(PCB *p) removes PCB from RAM or puts on Ready Queue if not done
 * clean_ram_space() combines the free ram spaces
 * Scheduler(...) establishes the Scheduler and assigns it the pre-existing PCB list, Ready Queue, and MMU
 * lt_sched(*still_has_work) runs the Long Term Scheduler which loads the jobs from the disk into the PCB list
 * st_sched(*st_still_has_work) runs the Short Term Scheduler which loads jobs from the PCB list onto the Ready Queue
 * *lt_get_next_pcb(M_queue<PCB> &pcbs) retrieves the next pcb from the disk and puts it in the ram for the Ready Queue
 * comp_fifo returns true if p1 has a smaller job_id - used for sorting
 * comp_prio returns true if p1 has higher priority than p2 - used for sorting
 * comp_sjf returns true if p1 has higher job size than p2 - used for sorting
 */

#ifndef PHASE_2_SCHEDULER_H
#define PHASE_2_SCHEDULER_H

#include "MMU.h"
#include "PCB.h"
#include <list>
#include <vector>
#include <queue>
#include "Scheduler.h"
#include "Dispatcher.h"

struct free_ram {
    int position;
    bool is_free;

    free_ram(int pos, bool is_free) {
        position = pos;
        is_free = false;
    }
};

class Scheduler {
private:
    M_queue<PCB> &pcbs;
    MMU mmu;
    std::list<free_ram> ram_space;
    int jobsAllocated;
    int jobsCompleted;

    enum SCHEDULING_TYPE {FIFO, PRIORITY, SJF};
    const SCHEDULING_TYPE sched_type = SCHEDULING_TYPE::FIFO;

    bool get_ram_start(PCB *p);
    void load_pcb(PCB *p);
    void remove_pcb(PCB *p);
    void clean_ram_space();

public:
    Scheduler(M_queue<PCB> &pcb_list, M_prio_queue<PCB> &ready_queue, MMU &mmu);

    void lt_sched(bool *still_has_work);
    void st_sched(bool *st_still_has_work);

    PCB *lt_get_next_pcb(M_queue<PCB> &pcbs);
};

bool comp_fifo(PCB *p1, PCB *p2);

bool comp_priority(PCB *p1, PCB *p2);

bool comp_sjf(PCB *p1, PCB *p2);

#endif //PHASE_2_SCHEDULER_H
