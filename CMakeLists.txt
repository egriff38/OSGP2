cmake_minimum_required(VERSION 3.8)
project(Phase_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp PCB.cpp CPU.cpp Disk.cpp Dispatcher.cpp Loader.cpp Scheduler.cpp Hex_Util.cpp PCB.cpp Ram.cpp MMU.h Log.h Cache.cpp)
add_executable(Phase_2 ${SOURCE_FILES})