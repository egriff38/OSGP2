//
// Created by charlie on 10/22/17.
//

#include "Cache.h"
#include <cstdlib>

std::vector<std::string> Cache::read_instructions(int page_num) {
    int cache_page_num = std::get<0>(instruction_words[page_num % INSTRUCTION_CACHE_SIZE]);
    if (cache_page_num == page_num) {
        std::vector<std::string> rd = std::get<1>(instruction_words[page_num % INSTRUCTION_CACHE_SIZE]);
        return rd;
    } else {
        std::vector<std::string> rd = {"", "", "", ""}; //if the page isn't in the cache
        return rd;
    }
}

std::vector<std::string> Cache::read_data(int page_num) {
    int cache_page_num = std::get<0>(data_words[page_num % DATA_CACHE_SIZE]);
    if (cache_page_num == page_num) {
        std::vector<std::string> rd = std::get<1>(data_words[page_num % DATA_CACHE_SIZE]);
        return rd;
    } else {
        std::vector<std::string> rd = {"", "", "", ""}; //if the page isn't in the cache
        return rd;
    }
}

void Cache::write_instructions(int page_num, std::vector<std::string> data) {
    int cache_page_num = std::get<0>(instruction_words[page_num % INSTRUCTION_CACHE_SIZE]);
    if (cache_page_num == page_num) { //if the page isn't already in the cache
        std::get<1>(instruction_words[page_num % INSTRUCTION_CACHE_SIZE]) = data;
    }
}

void Cache::write_data(int page_num, std::vector<std::string> data) {
    int cache_page_num = std::get<0>(data_words[page_num % DATA_CACHE_SIZE]);
    if (cache_page_num == page_num) { //if the page isn't already in the cache
        std::get<1>(data_words[page_num % DATA_CACHE_SIZE]) = data;
    }
}

void Cache::clear_cache() {
    std::vector<std::string> ev = {"", "", "", ""};
    instruction_words.clear();
    data_words.clear();

    for (int i = 0; i < INSTRUCTION_CACHE_SIZE; i++)
        instruction_words[i] = std::make_pair(-1, ev);
    for (int i = 0; i < DATA_CACHE_SIZE; i++)
        data_words[i] = std::make_pair(-1, ev);
}

Cache::Cache() {
    std::vector<std::string> ev = {"", "", "", ""};
    for (int i = 0; i < INSTRUCTION_CACHE_SIZE; i++)
        instruction_words[i] = std::make_pair(-1, ev);
    for (int i = 0; i < DATA_CACHE_SIZE; i++)
        data_words[i] = std::make_pair(-1, ev);
}