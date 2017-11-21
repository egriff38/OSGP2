#include <iostream>
#include <list>
#include <thread>
#include "Loader.h"
#include "PCB.h"
#include "MMU.h"
#include "Scheduler.h"
#include "Dispatcher.h"
#include "Mutex_queues.cpp"
#include "CPU.h"

int main() {
    const int CPU_NUM = 4;

// Loader, MMU, Dispatchers, scheduler, ready_queue (prio queue), io_queue, and done_queue
// and are declared and initialized.
    auto pcbs = new M_priority_queue<PCB *>();
    auto ready_queue = new M_priority_queue<PCB *>();
    auto readyish_queue = new M_queue<PCB *>;
    auto blocked_queue = new M_queue<blocking_info *>;
    auto done_queue = new M_queue<PCB *>();
    auto mmu = new MMU();
    auto still_has_work = new bool(true);
    auto loader = new Loader();
    auto scheduler = new Scheduler(*pcbs, *ready_queue, *readyish_queue, *done_queue, *mmu);
    auto threads = std::vector<std::thread>();
    // Loader calls init();
    loader->init(*mmu, *pcbs);

    // Dispatcher threads begin
//    for(int i = 0; i < CPU_NUM; i++) {
//
//        std::thread(Dispatcher::start,mmu,ready_queue,blocked_queue,done_queue,i).detach();
//    }

    //Blocking thread will start here

    // Scheduling process starts in main thread
    // Loop begins for scheduler. Continues while there are still jobs to be done
  while(*still_has_work || scheduler->getDone() != 30) {
      scheduler->schedule(still_has_work);
 }





    // Thread for page fault and io begins (later)
    std::cout << scheduler->getDone() << " Finish";

    return 0;
}

