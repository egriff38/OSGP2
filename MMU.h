//
// Created by conrad on 11/7/17.
//
#ifndef PHASE_2_MMU_H
#define PHASE_2_MMU_H

/*
 *
 */

#include <iostream>
#include <map>
#include <mutex>
#include "Disk.h"
#include "Ram.h"

class MMU
{
private:
    std::map disk_frame_map<int, bool>;
    std::map ram_frame_map<int, bool>;
    Disk *disk;
    // Ram *ram;

public:
    std::string disk_memory(int address, std::string = NULL);
    std::string ram_memory(int address, std::string = NULL);
    bool add_page_to_disk(std::string word[],int frame_num);
    bool add_page_to_ram();

};
#endif //PHASE_2_MMU_H
