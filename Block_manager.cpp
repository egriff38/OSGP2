//
// Created by charlie on 11/16/17.
//

#include "Block_manager.h"
#include <thread>
#include <chrono>

void Block_manager::start(MMU *mmu, M_queue<PCB *> *readyish_queue, M_queue<blocking_info*> *blocked_queue) {
    bool this_is_true;
    int count = 0;
    blocking_info *temp;
    using namespace std::chrono_literals; //for ns in sleep_for()

    while (this_is_true) {
        if (blocked_queue->getSize() != 0) {
            temp = blocked_queue->pop();
            if (temp->pcb->state == PCB::PROCESS_STATUS::PAGE_FAULT) {
                clear_pf(mmu, temp);
            } else if (temp->pcb->state == PCB::PROCESS_STATUS::IO_BLOCKED) {
                clear_io(mmu, temp);
            } else
                std::cout << "Block_manager error: received non-blocked PCB " + temp->pcb->job_id << std::endl;
        }
        readyish_queue->push(temp->pcb);
    }

    std::this_thread::sleep_for(2ns);
}

void Block_manager::clear_io(MMU *mmu, blocking_info *b) {
    if (b->data.size() == 0) { //read
        mmu->get_disk_frame(b->page_num, b->pcb);
    } else if (b->data.size() == 4) { //write
        mmu->add_page_to_disk(b->data, std::get<0>(b->pcb->page_table.at(b->page_num)));
    } else { //wrong size
        std::cout << "Block_manager error: data is blocking_info->data is the wrong size" << std::endl;
    }
}

void Block_manager::clear_pf(MMU *mmu, blocking_info *b) {
    mmu->add_page_to_ram(mmu->read_page_from_disk(mmu->get_disk_frame(b->page_num, b->pcb)), std::get<0>(b->pcb->page_table.at(b->page_num)));
}
