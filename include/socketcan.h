#ifndef _SOCKET_CAN_H
#define _SOCKET_CAN_H

#include <chrono>
#include <condition_variable>
#include <linux/can.h>
#include <mutex>
#include <queue>
#include <thread>

struct CanFilter
{
    uint32_t can_id;
    uint32_t can_mask;
    int bit_position;
};

class SocketCan
{
public:
    virtual ~SocketCan() = default;

    static void StartServer(const char *if_name, const std::vector<CanFilter> &filter_list = std::vector<CanFilter>{}, int can_frame_interval = 0);
    static void StopServer();
    static void EnqueueOutgoing(struct can_frame &p_frame);
    static void EnqueueOutgoing(std::vector<struct can_frame> &p_frame_list);
    static bool DequeueIncoming(struct can_frame &p_frame);

private:
    SocketCan() = default;

    static SocketCan &Get();

    static int m_sock;
    static int m_can_frame_interval;

    static bool m_socket_closed;

    static std::queue<struct can_frame> m_incoming_queue;
    static std::queue<struct can_frame> m_outgoing_queue;

    static std::mutex m_incoming_mtx;
    static std::mutex m_outgoing_mtx;

    static std::condition_variable m_incoming_ready_cv;
    static std::condition_variable m_outgoing_ready_cv;

    static void ReadIncoming();
    static std::thread m_thread_read_incoming;

    static void WriteOutgoing();
    static std::thread m_thread_write_outgoing;
};

#endif // _SOCKET_CAN_H
