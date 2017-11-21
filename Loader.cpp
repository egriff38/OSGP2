//
// Created by Eshin Griffith on 9/26/17.
//

#include "Loader.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Log.h"
#include "Hex_Util.h"


Loader::Loader() {
    current_data = std::vector<std::string>(4);
}

void Loader::init(MMU &mmu, M_priority_queue<PCB *> &pcbs) {
    std::vector<std::string> page = std::vector<std::string>(4);
    int current_MMU_page = 0;
    int current_pcb_page = 0;
    int word_count = 0;
    std::ifstream input("../Program.txt");
    std::string temp = "";
    PCB *pcb;
  //  pcb = new PCB();

    while (getline(input, temp)) {
        if (temp.length() != 0) {
            // For MetaData
            if (temp.at(0) == '/' && temp != "// END" && temp != "//END") {
                pcb = strip_meta_data(temp, pcb);
            } else if (temp.at(0) == '0') {
                updatePCBData(&mmu, pcb, current_MMU_page, current_pcb_page, word_count, temp);
            } else {
                addPCB(&mmu,pcbs,pcb, current_MMU_page, current_pcb_page, word_count);
            }
        }
    }
    mmu.print_disk_map(false);
}

PCB* Loader::strip_meta_data(std::string temp_data, PCB *pcb) {
   PCB *p;
    if (temp_data.at(3) == 'J') {
        p = new PCB();
        strip_job_meta_data(p, temp_data);
    } else {
        strip_data_meta_data(pcb, temp_data);
        p = pcb;
    }
    return p;
}

PCB* Loader::strip_job_meta_data(PCB *pcb, std::string temp_data) {
    std::string buildString = "";
    temp_data = temp_data.substr(7, std::string::npos);
    std::vector<int> data = Hex_Util::parseIntsFromString(temp_data);
    pcb->job_id = data[0];
    pcb->job_size = data[1];
    pcb->job_pri = data[2];
    return pcb;
}

PCB* Loader::strip_data_meta_data(PCB *pcb, std::string temp_data) {
    std::string buildString = "";
    temp_data = temp_data.substr(7, std::string::npos);
    std::vector<int> data = Hex_Util::parseIntsFromString(temp_data);
    pcb->in_buf_size = data[0];
    pcb->out_buf_size = data[1];
    pcb->temp_buf_size = data[2];
    pcb->total_size = pcb->job_size + pcb->in_buf_size + pcb->out_buf_size + pcb->temp_buf_size;
    return pcb;
}

void Loader::updatePCBData(MMU *mmu, PCB *pcb, int &current_MMU_page, int &current_pcb_page, int &word_count, std::string temp_data) {
   int b = current_pcb_page;
    temp_data = temp_data.substr(2, std::string::npos);
    if(word_count == 4){
        pcb->page_table[current_pcb_page] = (std::make_tuple(current_MMU_page,-1,false));
        mmu->add_page_to_disk(current_data,current_MMU_page);
        current_MMU_page++;
        current_pcb_page++;
        for(int i = 0; i < 4; i++)
            current_data[i] = "";
        word_count = 0;
    }
    current_data[word_count] = temp_data;
    word_count++;
}

void Loader::addPCB(MMU *mmu ,M_priority_queue<PCB *> &pcbs, PCB *pcb, int &current_MMU_page, int &current_pcb_page, int &word_count) {
    if(word_count != 0){
        mmu->add_page_to_disk(current_data,current_MMU_page);
        pcb->page_table[current_pcb_page] = (std::make_tuple(current_MMU_page,-1,false));
        current_MMU_page++;
        current_pcb_page++;//ds
    }
    current_pcb_page = 0;
    word_count = 0;
    pcbs.push(pcb);
}


//void Loader::init(MMU &mmu, M_priority_queue<PCB *> &pcbs) {
//
//    // Variables for init function
//    int data[10];
//    std::vector<std::string> page = std::vector<std::string>(4);
//    int wordCount = 0;
//    int currentPagesForJob= 0;
//    int currentMMUPage = 0;
//    std::ifstream input("../Program.txt");
//    std::string temp;
//    std::string store;
//    std::string build_string = "";
//    int counter = 0;
//    int current_position = 0;
//    int lines = 0;
//    PCB *p = new PCB();
//    // Read the file
//    while (getline(input, temp)) {
//        lines++;
//        build_string = "";
//        if (temp.length() == 0)
//            break;
//        if (temp.at(0) == '/' && temp != "// END" && temp != "//END") { // If the line is PCB Data
//            if (temp.at(3) == 'J') {// Do this if the line is a PCB Job line
//                //create new PCB with registers and address initialized
//
//
//
//                temp = temp.substr(7, std::string::npos);//drop the characters before index 7
//
//                //store the values from the line in data
//                for (int i = 0; i < temp.length(); i++) {
//                    if (temp.at(i) != ' ')
//                        build_string += temp.at(i);
//                    else {
//                        if (build_string.length() != 0) {
//                            data[counter] = Hex_Util::hex_to_decimal(build_string);
//                            counter++;
//                            build_string = "";
//                        }
//                    }
//                }
//
//                // Last build string must be added
//                data[counter] = Hex_Util::hex_to_decimal(build_string);
//                counter++;
//                build_string = "";
//
//            } else { //if the line is a data info line
//                int innerIterations = 0;
//
//                temp = temp.substr(8, std::string::npos);
//
//                //store the values from the line in data
//                for (int i = 0; i < temp.length(); i++) {
//                    innerIterations++;
//                    if (temp.at(i) != ' ')
//                        build_string += temp.at(i);
//                    else {
//                        // Last buildstring must be added
//                        data[counter] = Hex_Util::hex_to_decimal(build_string);
//                        counter++;
//                        build_string = "";
//                    }
//                }
//
//                data[counter] = Hex_Util::hex_to_decimal(build_string);
//                counter++;
//                build_string = "";
//
//                // Once a PCB Data Line information is recorded, store that into a pcb
//                p->job_id = data[0];
//                p->job_size = data[1];
//                p->job_pri = data[2];
//                p->in_buf_size = data[3];
//                p->out_buf_size = data[4];
//                p->temp_buf_size = data[5];
//                p->total_size = p->job_size + p->in_buf_size + p->out_buf_size + p->temp_buf_size;
//                p->state = PCB::PROCESS_STATUS::NEW;
//                p->prgm_counter = 0;
//
//                mmu.add_page_to_disk(page, currentMMUPage);
//                p->page_table[currentPagesForJob] = std::make_tuple(currentMMUPage,-1,true,false);
//                currentPagesForJob = 0;
//                currentMMUPage++;
//                wordCount = 0;
//                for(int j = 0; j < 4; j++)
//                    page[j] = "";
//
//                p = new PCB();
//                for (int &j : p->registers) {
//                    j = -1;
//                }
//
//                pcbs.push(p);
//                counter = 0;
//
//            }
//        }
//            // If the data is just raw hexcode, strip off the first few characters and store it as a string
//        else if (temp.at(0) != '/') {
//            temp = temp.substr(2, std::string::npos);
//            if(wordCount == 4)
//            {
//                mmu.add_page_to_disk(page, currentMMUPage);
//                wordCount = 0;
//                p->page_table[currentPagesForJob] = std::make_tuple(currentMMUPage,-1,true,false);
//                currentPagesForJob++;
//                currentMMUPage++;
//                for(int j = 0; j < 4; j++)
//                    page[j] = "";
//            }
//            page[wordCount] = temp; //xdf
//            wordCount++;
//        }
//    }
//    input.close();
//    }
