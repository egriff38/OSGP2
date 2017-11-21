//
// Created by conrad on 11/7/17.
//


#include <iostream>
#include "PCB.h"
#include "Hex_Util.h"


PCB::PCB(){
    this->page_table = std::map<int,std::tuple<int,int,bool> >();
}

//Prints out the PCB information
void print_pcbs(std::list<PCB *> p)
{

    for(PCB *pcb : p)
    {
        std::cout << "ID\t" << pcb->job_id << std::endl;
        std::cout << "Job Size:\t" << pcb->job_size << std::endl;
        std::cout << "JobPri:\t" << pcb->job_pri << std::endl;
        std::cout << "InSize:\t" << pcb->in_buf_size << std::endl;
        std::cout << "OutSize:\t" << pcb->out_buf_size << std::endl;
        std::cout << "TempSize:\t" << pcb->temp_buf_size << std::endl;
        std::cout << "Total Size:\t" << pcb->total_size << std::endl;
        std::cout << "Start Point:\t" << pcb->job_disk_address << std::endl; 
        std::string s;
        switch((int)pcb->state)
        {
            case 0: {
                s = "RUNNING";
                break;
            }
            case 1: {
                s = "READY";
                break;
            }
            case 2: {
                s = "PAGE_FAULT";
                break;
            }
            case 3: {
                s = "IO_BLOCKED";
                break;
            }
            case 4: {
                s = "NEW";
                break;
            }
            case 5: {
                s = "COMPLETED";
                break;
            }
        }
        std::cout << "State:\t" << s << std::endl;
        std::cout << std::endl;
    }

    if (p.empty())
        std::cout << ("No PCBs to print.") << std::endl;

}


void PCB::printPageTable() {
   std::cout << "JOBID " << this->job_id << std::endl;
    for(int i = 0; i < page_table.size(); i++)
    {
        std::cout << "Disk Frame " << std::get<0>(page_table[i]) << "\n";
        std::cout << "Ram Frame " << std::get<1>(page_table[i]) << "\n";
        std::cout << "Ram Frame Exists " << Hex_Util::bool_to_string(std::get<2>(page_table[i])) << "\n";

    }

}

// static bool PCB::compare(const PCB *a, const PCB *b)const {
//    if(PCB::SORT == PCB::SORTING_METHOD::FIFO)
//        return true;
//    else if(PCB::SORT == PCB::SORTING_METHOD::PRIO)
//        return a->job_pri < b->job_pri;
//    else
//        return a->job_size < b->job_size;
//}