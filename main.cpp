#include <iostream>
#include <list>
#include <thread>
#include "Loader.h"
#include "PCB.h"
#include "MMU.h"
#include "Scheduler.h"
#include "Dispatcher.cpp"
#include "Mutex_queues.cpp"

int main() {
const int CPU_NUM = 4;

// Loader, MMU, Dispatchers, scheduler, ready_queue (prio queue), io_queue, and done_queue
// and page_fault_queue are declared and initialized.
M_priority_queue<PCB*> *pcbs = new M_priority_queue<PCB*>();
M_priority_queue<PCB*> *ready_queue = new M_priority_queue<PCB*>();
M_queue<PCB*> *done_queue = new M_queue<PCB*>();
auto *still_has_work = new bool(true);
MMU *m = new MMU();
Loader *loader = new Loader();
Scheduler *scheduler = new Scheduler(*pcbs,*ready_queue,*done_queue, *m);
std::vector<std::thread> t = std::vector<std::thread>();
    // Loader calls init();
    loader->init(*m,*pcbs);

    // Dispatcher threads begin
    for(int i = 0; i < CPU_NUM; i++) {
        std::thread(Dispatcher::start,m,ready_queue,new M_queue<PCB*>(),new M_queue<PCB*>(),done_queue,i).detach();
    }


    // Scheduling process starts in main thread
    // Loop begins for scheduler. Continues while there are still jobs to be done
    while(*still_has_work || scheduler->getDone() != 30) {
        scheduler->schedule(still_has_work);
    }

    // Thread for page fault and io begins (later)


    return 0;
}