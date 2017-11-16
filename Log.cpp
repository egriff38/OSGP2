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

void Log::publish(std::string fileName, Log::Pubstyle p) {
    loglock.lock();
    std::ofstream ostrm (fileName, std::ios::binary);
    ostrm << 123 << "abc" << '\n';
    ostrm << logMap["RamDump"] << '\n';
    std::cout<< "ERROR: NOT DEFINED!";
    loglock.unlock();
}

Log::Log() {
    logMap = std::map<std::string, std::string> ();
}

