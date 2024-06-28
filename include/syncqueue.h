#ifndef _SYNCQUEUE_H
#define _SYNCQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

template <typename T>
class SyncQueue
{
public:
    SyncQueue()
        : m_stop_waiting(false)
    {
    }
    virtual ~SyncQueue() = default;

    void Enqueue(const T &element)
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        m_queue.push(element);

        m_cv.notify_one();
    }

    void Dequeue(T &element)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [&]() { return !m_queue.empty() || m_stop_waiting; });

        if (!m_queue.empty())
        {
            element = m_queue.front();
            m_queue.pop();
        }
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        return m_queue.empty();
    }

    void StopWait()
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        m_stop_waiting = true;
        m_cv.notify_all();
    }

private:
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::queue<T> m_queue;
    bool m_stop_waiting;
};
#endif