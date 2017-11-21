cmake_minimum_required(VERSION 3.8)
project(Phase_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(FMT fmt-4.0.0/fmt/format.h fmt-4.0.0/fmt/format.cc)
set(SOURCE_FILES ${FMT} PCB.cpp CPU.cpp Disk.cpp Dispatcher.cpp Loader.cpp Scheduler.cpp Hex_Util.cpp Ram.cpp MMU.h Log.cpp Cache.cpp MMU.cpp Mutex_queues.cpp)
add_executable(Phase_2 ${SOURCE_FILES} main.cpp)

add_executable(LogTests ${SOURCE_FILES} ${FMT} main_log.cpp main_log.cpp.cpp)