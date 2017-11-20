//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_LOG_H
#define PHASE_2_LOG_H

#include <map>
#include <mutex>
#include "fmt-4.0.0/fmt/format.h"
class Log{
public:
    enum Pubstyle{RAM_CSV,RAMDUMP};
    void appendLog(std::string name, std::string text);
    void increment(std::string, double val=1);
    void publish();
    void print();
    Log();

private:
    std::mutex loglock;
    std::map<std::string,std::string> logMap;
    std::string Summary();
};
#endif //PHASE_2_LOG_H
