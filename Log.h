//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_LOG_H
#define PHASE_2_LOG_H

#include <map>
#include <mutex>

class Log{
public:
    enum Pubstyle{RAM_CSV,RAMDUMP};
    void appendLog(std::string name, std::string text);
    void publish(std::string fileName, Pubstyle p);
    void print(std::string structure);
    Log();

private:
    std::mutex loglock;
    std::map<std::string,std::string> logMap;
};
#endif //PHASE_2_LOG_H
