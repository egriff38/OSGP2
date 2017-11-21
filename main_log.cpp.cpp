//
// Created by Zach Auzenne on 11/20/17.
//

#include <iostream>
#include "Log.h"

int main ()
{
    auto main_log = new Log(0);
    auto log = new Log(0);
    auto log_2 = new Log(0);
    log->w_start();
    for(int i = 0; i < 100; ++i)
        std::cout<<i<<std::endl;
    log->w_stop();
    log->c_start();
    for(int i = 0; i < 1000; ++i)
        std::cout<<i<<std::endl;
    log->c_stop();
    log->print();

    log_2->w_start();
    for(int i = 0; i < 100; ++i)
        std::cout<<i<<std::endl;
    log_2->w_stop();
    log_2->c_start();
    for(int i = 0; i < 1000; ++i)
        std::cout<<i<<std::endl;
    log_2->c_stop();
    log_2->print();

    main_log->appendLog("PCB 1 Metrics", log->pull_met());
    main_log->appendLog("PCB 2 Metrics", log_2->pull_met());
    main_log->publish();


    return 0;
}
