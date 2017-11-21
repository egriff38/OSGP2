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
    std::vector<std::string> read_data(int page_num);

    void write_data(int page_num, std::vector<std::string> input);

    void clear_cache();

    const static int CACHE_SIZE = 6;

    Cache();


private:
    std::map<int, std::pair<int, std::vector<std::string>>> data;
};


#endif //OS_GROUP_PROJECT_CACHE_H
