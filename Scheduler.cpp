//
// Created by Charlie McDermitt on 10/10/2017.
#include <vector>
#include "Scheduler.h"
#include "Log.h"
#include <algorithm>
#include "Hex_Util.h"
#include <tuple>

// Initalizes the Scheduler and gives it the job list, disk, ram, and dispatcher.
Scheduler::Scheduler(M_priority_queue<PCB *> &pcb_list, M_priority_queue<PCB *> &ready_queue, M_queue<PCB*> &readyish_queue,
                     M_queue<PCB *> &done_queue, MMU &mmu) {
    pcbs = &pcb_list;
    this->ready_queue = &ready_queue;
    this->readyish_queue = &readyish_queue;
    this->done_queue = &done_queue;
    this->mmu = &mmu;
    ram_space = std::list<free_ram>();
    ram_space.push_front(free_ram(0, true));
    for (free_ram i : ram_space)
        std::cout << Hex_Util::bool_to_string(i.is_free) << std::endl;
    done = 0;
}


// Long Term Scheduler
void Scheduler::schedule(bool *still_has_work) {
    PCB *temp;
    // Continues until no more jobs can be loaded or there are no more jobs
        clean_ram_space();
        while (readyish_queue->getSize() > 0) {
            ready_queue->push(readyish_queue->pop());
        }

        if(*still_has_work){
            temp = lt_get_next_pcb(*pcbs);
            if (temp != nullptr) {
                *still_has_work = false;
                load_pcb(temp );
                temp->state = PCB::READY;
                ready_queue->push(temp);
                jobsAllocated++;
            }
            else
                *still_has_work  = false;
        }
}


//returns pointer to next PCB, returns null pointer if no next PCB
PCB *Scheduler::lt_get_next_pcb(M_priority_queue<PCB *> &pcbs) {
    PCB *temp;
    if (pcbs.getSize() == 0)
        return nullptr;
    else {
        temp = pcbs.pop();
        return temp;
    }
}


void Scheduler::load_pcb(PCB *p) { //puts PCB in RAM and ready_queue deal with sorting laternt ram_start = p->job_ram_address;
    for(int i = 0; i < INITIAL_NUM_OF_FRAMES; i++){

    }
}

void Scheduler::clean_ram_space() {
    /*Dispatcher::lock_talk.lock();
    //std::cout << "Cleaning Ram \n";
    Dispatcher::lock_talk.unlock();*/
    PCB *temp;
    free_ram *f;
    while (done_queue->getSize() != 0) {
        temp = done_queue->pop();
        done++;
        for(auto s : temp->page_table)
        {
            if(std::get<3>(s.second)){
                mmu->free_ram_frames->push(std::get<1>(s.second));
            }
        }
    }
}

int Scheduler::getDone() {
    int x = 2;
    return done;


}
