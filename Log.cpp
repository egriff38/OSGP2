//
// Created by Eshin Griffith on 11/15/17.
//

#include <string>
#include <utility>
#include "Log.h"
#include <iostream>
#include <fstream>

void Log::appendLog(std::string name, std::string text) {
    loglock.lock();
    switch (logMap.count(name)){
        case 0: logMap[name] = std::move(text);
        case 1: logMap[name] = logMap[name]+text;
    }
    loglock.unlock();
}

void Log::increment(){
    ++count;
}

void Log::publish() {
    loglock.lock();
    for (auto it=logMap.begin(); it!=logMap.end(); ++it)
        ostrm << it->first << '\n' << it->second << '\n';
    //ostrm << logMap["RamDump"] << '\n';
    ostrm.close();
    loglock.unlock();
}

void Log::print() {
    loglock.lock();

    std::cout << Summary() << '\n';
    for(auto k:logMap) std::cout << k.first << std::endl << k.second << '\n';
    loglock.unlock();
}

std::string Log::pull_met() {
    return Summary();
}

void Log::w_start() {
    w_timer = clock();
}

void Log::w_stop() {
    wait_time = ( std::clock() - w_timer ) / (double) CLOCKS_PER_SEC;
}

void Log::c_start() {
    c_timer = clock();
}

void Log::c_stop() {
    comp_time = ( std::clock() - c_timer ) / (double) CLOCKS_PER_SEC;
}

Log::Log(int id) {
    logMap = std::map<std::string, std::string> ();
    wait_time = 0.0;
    comp_time = 0.0;
    log_id = id;
    count = 0;
}

std::string Log::Summary() {
    return fmt::format(R"(Summary for Job {0}
----------------------
Total runtime:  {1}
Average runtime: {2}
Average completion period: {3}
Average wait time: {4}
I/O Count: {5}
cache density:
Ram density:
PF/IO density:
)", log_id, (wait_time+comp_time),(wait_time+comp_time), comp_time, wait_time, count);

}