//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_LOG_H
#define PHASE_2_LOG_H

#include <map>
#include <mutex>
#include "fmt-4.0.0/fmt/format.h"
#include <ctime>
#include <fstream>

class Log{
public:
    enum Pubstyle{RAM_CSV,RAMDUMP};
    void appendLog(std::string name, std::string text);
    void increment();
    void publish();
    void print();
    std::string pull_met();
    void w_start();
    void w_stop();
    void c_start();
    void c_stop();
    Log(int id);

private:
    std::mutex loglock;
    std::map<std::string,std::string> logMap;
    std::ofstream ostrm {("../LogFile.txt")};
    std::string Summary();
    std::clock_t w_timer;
    std::clock_t c_timer;
    double wait_time;
    double comp_time;
    int log_id;
    int count;
};
#endif //PHASE_2_LOG_H
