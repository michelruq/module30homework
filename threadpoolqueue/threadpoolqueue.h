
#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>
#include <future>
#include "blockedqueue.h"

typedef std::function<void()> task_type;

typedef void (*FuncType) (int *array, long left, long right);

class ThreadPoolQueue
{
   private:
       // количество потоков
       int m_thread_count;
       // потоки
       std::vector<std::thread> m_threads;
       // очереди задач для потоков
       std::vector<BlockedQueue<task_type>> m_thread_queues;
       // для равномерного распределения задач
       int m_index;

   public:
      ThreadPoolQueue();
      void start();
      void stop();
      void push_back(FuncType f, int *array, long left, long right);
      void threadFunction(int qindex);

};
