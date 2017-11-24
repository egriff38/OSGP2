//
// Created by charlie on 11/16/17.
//

#include "Block_manager.h"
#include "Hex_Util.h"
#include <thread>
#include <chrono>

void Block_manager::start(MMU *mmu, M_queue<PCB *> *readyish_queue, M_queue<blocking_info*> *blocked_queue) {
    bool this_is_true = true;
    int count = 0;
    blocking_info *temp;
    using namespace std::chrono_literals; //for ns in sleep_for()

    while (this_is_true) {
        temp = blocked_queue->pop();
        if (temp != nullptr) {
            if (temp->pcb->state == PCB::PROCESS_STATUS::PAGE_FAULT) {
                clear_pf(mmu, temp);
            } else if (temp->pcb->state == PCB::PROCESS_STATUS::IO_BLOCKED) {
                clear_io(mmu, temp);
            } else
                std::cout << "Block_manager error: received non-blocked PCB " + temp->pcb->job_id << std::endl;

            readyish_queue->push(temp->pcb);
        }

        std::this_thread::sleep_for(2ns);
    }


}

void Block_manager::clear_io(MMU *mmu, blocking_info *b) {
//    if (b->data.size() == 0) {
//        //read
//        auto frame = mmu->get_disk_frame(b->page_num, b->pcb);
//        auto page = mmu->read_page_from_disk(frame);
//        mmu->add_page_to_ram(page);
//    } else if (b->data.size() == 4) { //write
//        mmu->add_page_to_disk(b->data, std::get<0>(b->pcb->page_table.at(b->page_num)));
//    } else { //wrong size
//        std::cout << "Block_manager error: data is blocking_info->data is the wrong size" << std::endl;
//    }
//std::cout << "Register " << b->pcb->s1 << "\n";
if(b->pcb->read_IO){
   // std::string temp = mmu->ram_memory(b->pcb->address);
 //   int data = Hex_Util::hex_to_decimal(temp);
    b->pcb->registers[b->pcb->s1] = b->pcb->address;
}

else{
    mmu->ram_memory(b->pcb->address, Hex_Util::decimal_to_hex(b->pcb->s2));
}
    //b->pcb->prgm_counter++;
}

void Block_manager::clear_pf(MMU *mmu, blocking_info *b) {

    int* frame_num = mmu->add_page_to_ram(mmu->read_page_from_disk(mmu->get_disk_frame(b->page_num, b->pcb)));
   // if(frame_num == nullptr){
     //   throw std::invalid_argument(" FrameNum is null\nblocking_info\nPage_num " + std::to_string(b->page_num)
       // + "\nPCB Num " + std::to_string(b->pcb->job_id));
    //}
    if(frame_num != nullptr) {
        if(*frame_num == -1)
            throw std::invalid_argument("NO NO NO frame num cannot be -1");
        std::get<1>(b->pcb->page_table[b->page_num]) = *frame_num;
        std::get<2>(b->pcb->page_table[b->page_num]) = true;
    }
}
