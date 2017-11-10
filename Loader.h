// Created by Eshin Griffith on 11/3/17.
//

/* The Loader class is used only at the beginning of main. Its only purpose is to call init()
 * init(): Takes an mmu and a list of pcbs both by reference, and reads from the ProgramFile to
 * fill those pcbs with proper information.
 * Loader(): Creates a loader class
 * ~Loader(): Deletes a loader class
 * PROGRAM_FILE: The string containing the relative path to the ProgramFile
 */

#ifndef PHASE_2_LOADER_H
#define PHASE_2_LOADER_H

#include "Disk.h"
#include "PCB.h"
#include "Log.h"
#include "MMU.h"
#include "Mutex_queues.cpp"

class Loader {
public:
    void init(MMU &mmu, M_priority_queue<PCB *> &pcbs);
    Loader();
    ~Loader();
private:
    const std::string PROGRAM_FILE;
};

#endif //PHASE_2_LOADER_H
