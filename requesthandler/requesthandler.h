#pragma once

#include "threadpoolqueue.h"

template <typename T>
class RequestHandler {
   public:
       RequestHandler();
       ~RequestHandler();
       // отправка запроса на выполнение
       void pushRequest(FuncType f, int *array, long left, long right);
   private:
       // пул потоков
       T m_tpool;
};

template <typename T>
RequestHandler<T>::RequestHandler()
{
   m_tpool.start();
}

template <typename T>
RequestHandler<T>::~RequestHandler()
{
   m_tpool.stop();
}

template <typename T>
void RequestHandler<T>::pushRequest(FuncType f, int *array, long left, long right)
{
   m_tpool.push_back(f, array, left, right);
}

using RequestHandlerThreadQueue = RequestHandler<ThreadPoolQueue>;