#include <iostream>
#include <list>
#include "Loader.h"
#include "PCB.h"
#include "MMU.h"
#include "Scheduler.h"
#include "Mutex_queues.h"
#include "Mutex_queues.cpp"

int main() {
M_priority_queue<PCB*> *pcbs = new M_priority_queue<PCB*>();
M_priority_queue<PCB*> *ready_queue = new M_priority_queue<PCB*>();
M_queue<PCB*> *done_queue = new M_queue<PCB*>();
bool temp = true;
bool *still_has_work = &temp;
MMU *m = new MMU();
Loader *loader = new Loader();
Scheduler *scheduler = new Scheduler(*pcbs,*ready_queue,*done_queue, *m);
    loader->init(*m,*pcbs);
    scheduler->schedule(still_has_work);

    // Loader, MMU, Dispatchers, scheduler, ready_queue (prio queue), io_queue, and done_queue
    // and page_fault_queue are declared and initialized.

    // Loader calls init();

    // Thread for page fault and io begins

    // Dispatcher threads begin

    // Scheduling process starts in main thread

    // Loop begins for scheduler. Continues while there are still jobs to be done

    // Calls lt_sched

    // Calls st_sched


    return 0;
}