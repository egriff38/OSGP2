#include <iostream>
#include <list>
#include <thread>
#include "Loader.h"
#include "Log.h"
#include "PCB.h"
#include "MMU.h"
#include "Scheduler.h"
#include "Dispatcher.h"
#include "Mutex_queues.cpp"
#include "CPU.h"
#include "Block_manager.h"

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
    auto main_log = new Log(0);

    // Loader calls init();
    loader->init(*mmu, *pcbs);

    // Dispatcher threads begin
    for (int i = 0; i < CPU_NUM; i++) {
        std::thread(Dispatcher::start, mmu, ready_queue, blocked_queue, done_queue, i, main_log).detach();
    }


    //Blocking thread begins
    std::thread(Block_manager::start, mmu, readyish_queue, blocked_queue).detach();


    // Scheduling process starts in main thread
    // Loop begins for scheduler. Continues while there are still jobs to be done
  while(done_queue->getSize() < 30) {
      scheduler->schedule();
  }
    main_log->publish();
    std::cout << done_queue->getSize() << " Finish";
    mmu->dumpDisk();

    return 0;
}

