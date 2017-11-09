#include <iostream>
#include "MMU.h"
int main() {
MMU *m = new MMU();
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