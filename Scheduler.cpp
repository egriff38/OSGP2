//
// Created by Charlie McDermitt on 10/10/2017.
#include <vector>
#include "Scheduler.h"
#include "Log.h"
#include <algorithm>
#include "Mutex_queues.h"

// Initalizes the Scheduler and gives it the job list, disk, ram, and dispatcher
Scheduler::Scheduler(M_priority_queue<PCB*> &pcb_list, M_priority_queue<PCB*> &ready_queue, M_queue<PCB*> &done_queue, MMU &mmu){
    pcbs = &pcb_list;
    this->ready_queue = &ready_queue;
    this->done_queue = &done_queue;
    this->mmu = &mmu;
    ram_space = std::list<free_ram>();
    ram_space.push_front(free_ram(0,true));
}


// Long Term Scheduler
void Scheduler::schedule(bool *still_has_work) {
    PCB *temp;
    // Continues until no more jobs can be loaded or there are no more jobs

    while (true) {
        temp = lt_get_next_pcb(*pcbs);
        if (temp == nullptr) {
            *still_has_work = false;
            break;
        }
        clean_ram_space(*done_queue);
        if (!get_ram_start(temp)) {
            break;
        }
        load_pcb(temp);
        temp->state = PCB::READY;
        ready_queue->push(temp);
        jobsAllocated++;
        std::cout << jobsAllocated << "\n";

    }
}


//returns pointer to next PCB, returns null pointer if no next PCB
PCB* Scheduler::lt_get_next_pcb(M_priority_queue<PCB *> &pcbs) {
    PCB *temp;
    if(pcbs.getSize() == 0)
        return nullptr;
    else
    {
        temp = pcbs.pop();
        return temp;
    }
}


//sets p->job_ram_address to start location
//if there's no room, p->job_ram_address will stay unset
bool Scheduler::get_ram_start(PCB *p) {


    bool is_space = false;
    std::list<free_ram>::iterator it = ram_space.begin();
    int next_pos = 0;
    int current_pos = 0;


    while (it != ram_space.end() && !is_space) { //while we haven't found anything and we aren't at the end of ram_space
        if (it->is_free) //if it is a free space
        {
            current_pos = it->position; //store current position


            if (std::next(it) == ram_space.end()) { //if we're at the end of the ram space list

                if (MMU::RAM_SIZE - it->position ==
                    p->total_size) //if the free space at the end is exactly the size of the PCB
                {
                    //set the address and that the space is used, then return
                    p->job_ram_address = it->position;
                    it->is_free = false;
                    is_space = true;
                    return is_space;

                } else if ((MMU::RAM_SIZE - it->position) >
                           p->job_size) { //if we're at the end of the list and there's more than enough space

                    //set address, insert new space, and return
                    p->job_ram_address = current_pos;
                    is_space = true;
                    it->is_free = false;
                    free_ram *to_be_added = new free_ram(current_pos + p->total_size, true); //new space starts in address after end of p
                    to_be_added->position = current_pos + p->total_size;
                    to_be_added->is_free = true;
                    ram_space.insert(std::next(it), *to_be_added);
                    is_space = true;
                }

                    // There is not enough space at the end of RAM, so return false
                else {
                    return is_space;
                }

            } else { //if we aren't at the end of the list

                next_pos = std::next(it)->position; //store position of next space (current_pos initialized at top)

                if (next_pos - current_pos == p->total_size) {//if there's exactly enough room before the next process
                    //set is_free and address, then return
                    it->is_free = false;
                    p->job_ram_address = current_pos;
                    is_space = true;
                    return is_space;

                } else if (next_pos - current_pos > p->total_size) { //if there's more than enough room
                    //set is_free and address, create and insert new space, and return
                    p->job_ram_address = current_pos;
                    it->is_free = false;
                    free_ram *to_be_added = new free_ram(current_pos + p->total_size + 1, true); //new space starts in address after end of p
                    to_be_added->is_free = true;
                    to_be_added->position = current_pos + p->total_size;
                    ram_space.insert(std::next(it), *to_be_added);
                    is_space = true;
                    return is_space;
                } //if we can't fit in this space, we loop again since we aren't at the end yet
            }
        }
        ++it;
    }
    //  std::cout << "Current Position:\t" << ram_space[0].position << "\nCurrent Offset\t" << ram_space[0].offset << std::endl;
    return is_space;
}

void Scheduler::load_pcb(PCB *p) { //puts PCB in RAM and ready_queue deal with sorting later
    int ram_start = p->job_ram_address;
    int disk_start = p->job_disk_address;
    // Put on ram
    for (int i = 0; i < p->total_size; i++) { // may need to be <=
        mmu->ram_memory(ram_start + i,mmu->disk_memory(disk_start + i));
    }
}

void Scheduler::clean_ram_space(M_queue<PCB *> &done_queue){
    PCB *temp;
    free_ram *f;
    while(done_queue.getSize() != 0){
     temp = done_queue.pop();
        std::list<free_ram>::iterator it = ram_space.begin();
        while (it != ram_space.end()) {
            if (it->position == temp->job_ram_address)
                it->is_free = true;
            it++;
                }

        }
    std::list<free_ram>::iterator it = ram_space.begin();
    while (it != ram_space.end()) {
        if (it->is_free)
            while (std::next(it) != ram_space.end() && std::next(it)->is_free) {
                ram_space.erase(std::next(it));

            }
        it++;
    }
}

//returns true if p1 has lower priority than p2 - used for sorting
bool comp_fifo(PCB *p1, PCB *p2)
{
    return true;
}

bool comp_priority(PCB *p1, PCB *p2) {
    return p1->job_pri > p2->job_pri;
}

bool comp_sjf(PCB *p1, PCB *p2)
{
    return p1->job_size > p2->job_size;
}
