//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_PCB_H
#define PHASE_2_PCB_H

#include<list>
#include "Log.h"
#include <map>

//Process Control Block - Contains job information
struct PCB {
    //Job
    int job_id;
    int job_size;
    int job_pri;
    int in_buf_size;
    int out_buf_size;
    int temp_buf_size;
    int total_size;
    enum PROCESS_STATUS {RUNNING, READY, BLOCKED, NEW, COMPLETED};
    enum PROCESS_STATUS state;
    std::map<int,int> pageTable;
    int job_disk_address;
    int job_ram_address;
    int prgm_counter;
    int registers[16];
    Log* log;
    enum SORTING_METHOD{FIFO, PRIO, SJF};
   static const SORTING_METHOD SORT = SJF;
    //Data
    int data_disk_address;
  //  static bool compare(const PCB *a, const PCB *b) const;
};

void print_pcbs(std::list<PCB *> p);

#endif //PHASE_2_PCB_H
