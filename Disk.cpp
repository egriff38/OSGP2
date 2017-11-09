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
        throw std::invalid_argument("Disk write is out of bounds");
    return disk_data[address];
}

// Construct Disk and set size to global variable SIZE
Disk::Disk() {
    for (int i = 0; i < SIZE; i++)
        disk_data[i] = "";
}

Disk::~Disk() {}