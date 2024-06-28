#ifndef _DATAFRAMEQUEUE_H
#define _DATAFRAMEQUEUE_H

#include "dataframe.h"
#include "message.h"

#include <condition_variable>
#include <mutex>
#include <queue>

class DataFrameQueue
{
public:
    DataFrameQueue();
    void Enqueue(DataFrame &frame);
    bool GetMessage(Message &message);
    void StopWaiting();

private:
    bool m_stop_waiting;
    std::queue<DataFrame> m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};

#endif