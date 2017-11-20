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
}

void Loader::init(MMU &mmu, M_priority_queue<PCB *> &pcbs) {

    // Variables for init function
    int data[10];
    std::vector<std::string> page = std::vector<std::string>(4);
    int wordCount = 0;
    int currentPagesForJob= 0;
    int currentMMUPage = 0;
    std::ifstream input("../Program.txt");
    std::string temp;
    std::string store;
    std::string build_string = "";
    int counter = 0;
    int current_position = 0;
    int lines = 0;
    PCB *p = new PCB();

    // Read the file
    while (getline(input, temp)) {
        lines++;
        build_string = "";
        if (temp.length() == 0)
            break;
        if (temp.at(0) == '/' && temp != "// END" && temp != "//END") { // If the line is PCB Data
            if (temp.at(3) == 'J') {// Do this if the line is a PCB Job line
                //create new PCB with registers and address initialized
                mmu.add_page_to_disk(page, currentMMUPage);
                currentPagesForJob = 0;
                currentMMUPage++;
                wordCount = 0;
                for(int j = 0; j < 4; j++)
                    page[j] = "";

                p = new PCB();
                for (int &j : p->registers) {
                    j = -1;
                }

                temp = temp.substr(7, std::string::npos);//drop the characters before index 7

                //store the values from the line in data
                for (int i = 0; i < temp.length(); i++) {
                    if (temp.at(i) != ' ')
                        build_string += temp.at(i);
                    else {
                        if (build_string.length() != 0) {
                            data[counter] = Hex_Util::hex_to_decimal(build_string);
                            counter++;
                            build_string = "";
                        }
                    }
                }

                // Last build string must be added
                data[counter] = Hex_Util::hex_to_decimal(build_string);
                counter++;
                build_string = "";

            } else { //if the line is a data info line
                int innerIterations = 0;

                temp = temp.substr(8, std::string::npos);

                //store the values from the line in data
                for (int i = 0; i < temp.length(); i++) {
                    innerIterations++;
                    if (temp.at(i) != ' ')
                        build_string += temp.at(i);
                    else {
                        // Last buildstring must be added
                        data[counter] = Hex_Util::hex_to_decimal(build_string);
                        counter++;
                        build_string = "";
                    }
                }

                data[counter] = Hex_Util::hex_to_decimal(build_string);
                counter++;
                build_string = "";

                // Once a PCB Data Line information is recorded, store that into a pcb
                p->job_id = data[0];
                p->job_size = data[1];
                p->job_pri = data[2];
                p->in_buf_size = data[3];
                p->out_buf_size = data[4];
                p->temp_buf_size = data[5];
                p->total_size = p->job_size + p->in_buf_size + p->out_buf_size + p->temp_buf_size;
                p->state = PCB::PROCESS_STATUS::NEW;
                p->prgm_counter = 0;
                pcbs.push(p);
                counter = 0;

            }
        }
            // If the data is just raw hexcode, strip off the first few characters and store it as a string
        else if (temp.at(0) != '/') {
            temp = temp.substr(2, std::string::npos);
            if(wordCount == 4)
            {
                mmu.add_page_to_disk(page, currentMMUPage);
                wordCount = 0;
                currentPagesForJob++;
                currentMMUPage++;
                for(int j = 0; j < 4; j++)
                    page[j] = "";

            }

            page[wordCount] = temp; //xdf
            wordCount++;
        }
    }
mmu.print_disk_map();
    input.close();
    }
