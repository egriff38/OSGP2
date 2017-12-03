//
// Created by Eshin Griffith on 9/26/17.
//

#include "Disk.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdexcept>

// Writes string data to the array address
void Disk::write(int address, std::string data) {
    if (address >= SIZE || address < 0)
        throw std::invalid_argument("Disk write is out of bounds");
    disk_data[address] = data;
}

// Reads string data from the array address
std::string Disk::read(int address) {
    if (address >= SIZE || address < 0)
        throw std::invalid_argument("Disk read is out of bounds " + std::to_string(address));
    return disk_data[address];
}


// Construct Disk and set size to global variable SIZE
Disk::Disk() {
    for (int i = 0; i < SIZE; i++)
        disk_data[i] = "";
}

// Dumps Disk Data to Hex File
void Disk::dumpDisk() {
    ostrm << "Disk Dump\n";
    for(int i = 0; i < 2048; i++){
        ostrm << disk_data[i] << "\n";
    }
    ostrm.close();
}

