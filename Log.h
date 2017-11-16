//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_LOG_H
#define PHASE_2_LOG_H
class Log{
public:
    void appendLog(std::string name, std::string text);
    void publish(std::string fileName, std::string structure);
    Log();
};
static Log log ();
#endif //PHASE_2_LOG_H
