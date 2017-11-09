//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_DISK_H
#define PHASE_2_DISK_H


/* This class is used by the MMU and
 * only the MMU. It can be read and
 * written to, but any sort of frame
 * management is done by the MMU
 * SIZE is the maximum size that a disk can have
 * disk_data contains all the information in the disk
 * write allows for information to be written or overwritten to a certain index on the array
 * read allows to get data from the disk_data at a specific index
 * read and write must have the address inputs be between 0 and SIZE - 1
 * An error will be thrown reading "Disk read / write out of range if this is violated
 * Disk() initializes the disk_data array to contain the size
 * ~Disk() just destroys the object
 * getSize const returns the value of SIZE */

#include <iostream>

const static int SIZE = 2048;
class Disk {
private:
    std::string disk_data[SIZE];
public:

    std::string read(int address);
    void write(int address, std::string data);
    int getSize() const;
    Disk();
    ~Disk();
    static void testDisk();
};



#endif //PHASE_2_DISK_H
