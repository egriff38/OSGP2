//
// Created by Eshin Griffith on 9/26/17.
//
#include <vector>
#include "Ram.h"
#include <mutex>
#include <cstdlib>
#include <iostream>


std::string Ram::read(int address) {
    std::string rd = ram_data[address];
    return rd;
}

void Ram::write(int address, std::string data) {
    if (address >= SIZE || address < 0)
        std::cout << "Using Ram INcorretly " << address<< "\n ";
        ram_data[address] = data;
}

void Ram::write(int address, std::vector<std::string> data) {
    if (data[0] == "0")
        ram_used -= data.size();
    else
        ram_used += data.size();
    for (int i = 0; i < data.size(); i++) {
        this->ram_data[i + address] = data[i];
    }
}

Ram::Ram() {
    for (int i = 0; i < SIZE; i++)
        ram_data[i] = "0";
    ram_used = 0;
}

Ram::~Ram() {

}