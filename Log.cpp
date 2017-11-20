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

void Log::increment(std::string, double val){

}

void Log::publish() {
    loglock.lock();
    std::ofstream ostrm ("../src/ProgramTranslate.txt", std::ios::binary);
    ostrm << Summary() << '\n';
    ostrm << logMap["RamDump"] << '\n';
    loglock.unlock();
}

void Log::print() {
    loglock.lock();

    std::cout << Summary() << '\n';
    for(auto k:logMap) std::cout << k.first << std::endl << k.second << '\n';
    loglock.unlock();
}

Log::Log() {
    logMap = std::map<std::string, std::string> ();
}

std::string Log::Summary() {
    return fmt::format(R"(Summary
----------------------
Total runtime: {0}
Average runtime: {1}
Average completion period:
Average wait time:
cache density:
Ram density:
PF/IO density:
)", "Butt","Hole");

}