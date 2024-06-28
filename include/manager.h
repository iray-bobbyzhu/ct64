#ifndef _MANAGERBASE_H
#define _MANAGERBASE_H

#include "dataframe.h"
#include "dataframequeue.h"

#include <thread>

class Manager
{
public:
    Manager(DataFrame::Node this_node, DataFrame::Module this_module);
    virtual ~Manager() = default;

    void EnqueueFrame(DataFrame &frame);
    void SendMessage(uint8_t priority, uint8_t two_way, DataFrame::Node rx_node, DataFrame::Module rx_module, uint8_t command, std::vector<uint8_t> &contents);
    void SendMessage(uint8_t priority, uint8_t two_way, DataFrame::Node rx_node, DataFrame::Module rx_module, uint8_t command, uint64_t contents);
    void SendLoPriority(DataFrame::Node rx_node, DataFrame::Module rx_module, uint8_t command, std::vector<uint8_t> &contents);
    void SendLoPriority(DataFrame::Node rx_node, DataFrame::Module rx_module, uint8_t command, uint64_t content);
    void SendHiPriority(DataFrame::Node rx_node, DataFrame::Module rx_module, uint8_t command, std::vector<uint8_t> &contents);
    void SendHiPriority(DataFrame::Node rx_node, DataFrame::Module rx_module, uint8_t command, uint64_t content);
    void SendNotification(DataFrame::Node rx_node, DataFrame::Module rx_module, uint8_t command, std::vector<uint8_t> &contents);
    void SendNotification(DataFrame::Node rx_node, DataFrame::Module rx_module, uint8_t command, uint64_t content);
    void StopManager();

protected:
    void DequeueLoPriority();
    void DequeueHiPriority();
    void DequeueNotification();

    virtual void DispatchLoPriority(Message &message) = 0;
    virtual void DispatchHiPriority(Message &message) = 0;
    virtual void DispatchNotification(Message &message) = 0;

    DataFrameQueue m_lopriority_queue;
    DataFrameQueue m_hipriority_queue;
    DataFrameQueue m_notification_queue;

    std::thread m_thread_lopriority;
    std::thread m_thread_hipriority;
    std::thread m_thread_notification;

    DataFrame::Node m_this_node;
    DataFrame::Module m_this_module;
};
#endif