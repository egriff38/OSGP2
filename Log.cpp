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

void Log::upIO(){
    ++count;
}

void Log::upPF(){
    ++pagefault;
}

void Log::publish() {
    loglock.lock();
    for (auto it=logMap.begin(); it!=logMap.end(); ++it)
        ostrm << it->second << '\n';
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
    wait_time += ( std::clock() - w_timer ) / (double) CLOCKS_PER_SEC;
}

void Log::c_start() {
    c_timer = clock();
}

void Log::c_stop() {
    comp_time += ( std::clock() - c_timer ) / (double) CLOCKS_PER_SEC;
}

void Log::used(int i) {
    cpu_used = i;
}

Log::Log(int id) {
    logMap = std::map<std::string, std::string> ();
    wait_time = 0.0;
    comp_time = 0.0;
    log_id = id;
    count = 0;
    cpu_used = 0;
    pagefault = 0;
    mode = CSV;
}

std::string Log::Summary() {
    if (mode == TXT)
    {
        return fmt::format(R"(
Summary for Job {0}
----------------------
Total runtime:  {1}
Average runtime: {2}
Average completion period: {3}
Average wait time: {4}
I/O Count: {5}
CPU Used: {6}
Page Faults: {7}
)", log_id, (wait_time+comp_time),(wait_time+comp_time), comp_time, wait_time, count, cpu_used, pagefault);
    }

    else if (mode == CSV)
    {
        return fmt::format(R"({0},{1},{2},{3},{4},{5},{6})", log_id,(wait_time+comp_time), comp_time, wait_time, count, cpu_used, pagefault);
    }


}