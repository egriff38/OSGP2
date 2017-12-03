//
// Created by conrad on 11/7/17.
//
#ifndef PHASE_2_MMU_H
#define PHASE_2_MMU_H

/* The MMU manages both the RAM and the Disk. No one besides the MMU is allowed to alter or read
 * from the RAM or Disk!
 * disk_frame_map: A page table map for the disk.
 * ram_frame_map: A page table map for the Ram
 * disk: The disk that the MMU manages
 * ram: The RAM that the MMU manages
 * MMU(): Creates a basic MMU class
 * ~MMU(): Deletes an MMU class
 * ram_mutex, disk_mutex: Protect the read/write for disk and RAM respectively.
 * disk_memory: An address integer and a string s is passed in. If s is NULL, then a read is done,
 * and the read at the proper address is returned. If s is not NULL, the function writes the
 * string s to the specified location. This function will fail if the address is out of bounds.
 * add_page_to_ram: Does the exact same task as disk except it works with the RAM; see above.
 * get_page_from_ram: This function takes a frame_num as an integer and returns a pointer array containing
 * the page at that frame_num in ram.
 */

#include <iostream>
#include <map>
#include <mutex>
#include "Disk.h"
#include "Ram.h"
#include "PCB.h"
#include "Mutex_queues.cpp"

class MMU {
private:
    std::map<int, bool> *disk_frame_map;
    std::map<int, bool> *ram_frame_map;
    Disk *disk;
    Ram *ram;
    std::mutex ram_mutex;
    std::mutex disk_mutex;


public:
    MMU();

    ~MMU();

    std::string disk_memory(int address, std::string s = "NULL");

    std::string ram_memory(int address, std::string s = "NULL");

    bool add_page_to_disk(std::vector<std::string> page, int frame_num);

    int* add_page_to_ram(std::vector<std::string> page, int frame = -1);

    bool remove_page_from_ram(int frame_num);

    std::vector<std::string> read_page_from_ram(int frame_num);

    std::vector<std::string> read_page_from_disk(int frame_num);

    static int get_ram_frame(int page_num, const PCB *p);
    static int get_disk_frame(int page_num, const PCB *p);

    static const int RAM_SIZE = 1024;
    static const int DISK_SIZE = 2048;
    void print_disk_map(bool s = true);
    M_queue<int*> *free_ram_frames;
    int usedFrames;
    void dumpDisk();
};

struct blocking_info { //stored here because all classes that use it have MMU access
    PCB* pcb;
    int page_num;
    std::vector<std::string> data;
};




#endif //PHASE_2_MMU_H
