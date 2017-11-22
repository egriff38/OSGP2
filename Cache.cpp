//
// Created by charlie on 10/22/17.
//

#include "Cache.h"
#include <cstdlib>


std::vector<std::string> Cache::read_data(int page_num) {
    int cache_page_num = std::get<0>(data[page_num % CACHE_SIZE]);
    if (cache_page_num == page_num) {
        std::vector<std::string> rd = std::get<1>(data[page_num % CACHE_SIZE]);
        return rd;
    } else {
        std::vector<std::string> rd = {"", "", "", ""}; //if the page isn't in the cache
        return rd;
    }
}

void Cache::write_data(int page_num, std::vector<std::string> input) {
    int cache_page_num = std::get<0>(data[page_num % CACHE_SIZE]);
    if (cache_page_num != page_num) { //if the page isn't already in the cache
        std::get<0>(data[page_num % CACHE_SIZE]) = page_num;
        std::get<1>(data[page_num % CACHE_SIZE]) = input;
    }
}

void Cache::clear_cache() {
    std::vector<std::string> ev = {"", "", "", ""};
    data.clear();
    for (int i = 0; i < CACHE_SIZE; i++)
        data[i] = std::make_pair(-1, ev);
}

Cache::Cache() {
    std::vector<std::string> ev = {"", "", "", ""};
    for (int i = 0; i < CACHE_SIZE; i++)
        data[i] = std::make_pair(-1, ev);
}