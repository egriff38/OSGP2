//
// Created by conrad on 11/9/17.
//

#include "MMU.h"
#include <tuple>
#include "Hex_Util.h"


// Constructor / Deconstructor

MMU::MMU() {
    disk = new Disk();
    ram = new Ram();
    disk_frame_map = new std::map<int, bool>();
    ram_frame_map = new std::map<int, bool>();
    for(int i = 0; i < 512; i++)
    {
        (*disk_frame_map)[i] = false;
        if(i < 256)
            (*ram_frame_map)[i] = false;
    }
}

MMU::~MMU(){}

// Memory Access ons

std::string MMU::disk_memory(int address, std::string s) {
    disk_mutex.lock();
    std::string a;
    if(s == "NULL"){
        a = disk->read(address);
        disk_mutex.unlock();
        return a;
    }
    else {
        disk->write(address, s);
        disk_mutex.unlock();
        return s;
    }
}

std::string MMU::ram_memory(int address, std::string s) {
    std::string a;
    ram_mutex.lock();
    if(s == "NULL") {
        a = ram->read(address);
        ram_mutex.unlock();
        return a;
    }
    else {
        ram->write(address, s);
        ram_mutex.unlock();
        return s;
    }
}

// Page memory access functions

bool MMU::add_page_to_disk(std::vector<std::string> page, int frame_num) {
    // Check if map location is free
    // If it is then add the word there, and set the location
    // in the map to be not free and return true
    disk_mutex.lock();
    if((*disk_frame_map).at(frame_num) == false)
    {
        (*disk_frame_map).at(frame_num) = true;
        for(int i = frame_num * 4; i < frame_num*4 + 4; i++)
            disk->write(i, page[i%4]);
        disk_mutex.unlock();
        return true;
    }
    else{
        disk_mutex.unlock();
        return false;
    }
}

bool MMU::add_page_to_ram(std::vector<std::string> page, int frame_num) {
    // Check if map location is free
    // If it is then add the word there, and set the location
    // in the map to be not free and return true
    ram_mutex.lock();
    if((*ram_frame_map)[frame_num] == false)
    {
        (*ram_frame_map)[frame_num] = true;
        for(int i = frame_num * 4; i < frame_num*4 + 4; i++)
            ram->write(i, page[i%4]);
        ram_mutex.unlock();
        return true;
    }
    else{
        ram_mutex.unlock();
        return false;
    }
}

std::vector<std::string> MMU::read_page_from_ram(int frame_num) {
    std::vector<std::string> output;
    ram_mutex.lock();
    for (int i = 0; i < 4; i++) {
        output[i] = ram->read(frame_num * 4 + i);
    }
    ram_mutex.unlock();
    return output;
}

std::vector<std::string> MMU::read_page_from_disk(int frame_num) {
    std::vector<std::string> output;
    disk_mutex.lock();
    for (int i = 0; i < 4; i++) {
        output[i] = disk->read(frame_num * 4 + i);
    }
    disk_mutex.unlock();
    return output;
}


int MMU::get_ram_frame(int page_num, const PCB *p) {
    return std::get<0>(p->page_table.at(page_num));
}

int MMU::get_disk_frame(int page_num, const PCB *p) {
    return std::get<1>(p->page_table.at(page_num));
}

void MMU::print_disk_map() {
    for(int i = 0; i < disk_frame_map->size(); i++)
    {
        std::cout << "PAGE #" << i << " " << Hex_Util::bool_to_string(disk_frame_map->at(i)) << "\n";
    }


}