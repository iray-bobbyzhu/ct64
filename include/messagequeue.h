#ifndef _MESSAGEQUEUE_H
#define _MESSAGEQUEUE_H

#include "dataframe.h"
#include "message.h"

#include <condition_variable>
#include <mutex>
#include <queue>

class DataFrameQueue
{
public:
    DataFrameQueue() = default;
    void Enqueue(DataFrame &frame);
    bool GetMessage(Message &message);
    void StopWaiting();

private:
    bool m_stop_waiting = false;
    std::queue<DataFrame> m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};

#endif