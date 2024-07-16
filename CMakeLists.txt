cmake_minimum_required(VERSION 3.5)

project(module30homework)

include_directories(blockedqueue)
include_directories(requesthandler)
include_directories(threadpoolqueue)

set(SRC_LIST 
          main.cpp
          threadpoolqueue/threadpoolqueue.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CXX_FLAGS "${CXX_FLAGS} -std=c++17 -Wall")