//
// Created by charlie on 10/22/17.
//

#ifndef OS_GROUP_PROJECT_CACHE_H
#define OS_GROUP_PROJECT_CACHE_H

#include <string>
#include <vector>
#include "Log.h"


class Cache {


public:
    std::vector<std::string> read_instructions(int page_num);
    std::vector<std::string> read_data(int page_num);

    void write_instructions(int page_num, std::vector<std::string> data);
    void write_data(int page_num, std::vector<std::string> data);

    void clear_cache();

    const static int INSTRUCTION_CACHE_SIZE = 6; //both in pages
    const static int DATA_CACHE_SIZE = 6;

    Cache();


private:
    std::map<int, std::pair<int, std::vector<std::string>>> instruction_words;
    std::map<int, std::pair<int, std::vector<std::string>>> data_words;
};


#endif //OS_GROUP_PROJECT_CACHE_H
