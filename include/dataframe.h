#ifndef _DATAFRAME_H
#define _DATAFRAME_H

#include <cstdint>
#include <linux/can.h>
#include <string>

class DataFrame
{
public:
    enum class Node : uint8_t // 4 bits
    {
        ANY = 0x00,
        MAS = 0x01,
        MAR = 0x02
    };

    enum class Module : uint8_t // 4 bits
    {
        ANY = 0x00,
        XRAY = 0x01,
        COLLIMATOR = 0x02,
        DMS = 0x03,
        LASER = 0x05,
        FILE = 0x0A,
        LOG = 0x0F
    };

    DataFrame();
    DataFrame(struct can_frame &raw_frame);
    virtual ~DataFrame() = default;

    uint32_t GetCanId();
    uint8_t GetCommand();
    uint8_t GetLength();
    DataFrame::Module GetTxModule();
    DataFrame::Module GetRxModule();
    DataFrame::Node GetRxNode();
    DataFrame::Node GetTxNode();
    bool IsFirstFrame();
    bool IsMiddleFrame();
    bool IsLastFrame();
    bool IsHighPriority();
    bool IsNotification();
    uint64_t GetData64();

    void SetCanId(uint32_t can_id);
    void SetCommand(uint8_t command);
    void SetLength(uint8_t length);
    void SetTxModule(uint8_t module);
    void SetRxModule(uint8_t module);
    void SetRxNode(uint8_t node);
    void SetTxNode(uint8_t node);
    void SetFirstFrameFlag(uint8_t value);
    void SetLastFrameFlag(uint8_t value);
    void SetPriorityFlag(uint8_t priority);
    void SetTwowayFlag(uint8_t value);
    void SetData64(uint64_t data64);

    struct can_frame GetRawFrame();
    std::string ToString();

private:
    union
    {
        uint32_t m_can_id;
        struct
        {
            uint32_t m_cmd_code    : 8; // command code
            uint32_t m_rx_module   : 4; // receiver's module id
            uint32_t m_rx_node     : 4; // receiver's node id
            uint32_t m_tx_module   : 4; // sender's module id
            uint32_t m_tx_node     : 4; // sender's node id
            uint32_t m_lst_frame   : 1; // flag of first frame
            uint32_t m_fst_frame   : 1; // flag of last frame
            uint32_t m_two_way     : 1; // bi-directional or notification message
            uint32_t               : 1;
            uint32_t m_lo_priority : 1; // 0:hi, 1:lo
            uint32_t               : 3;
        };
    };

    uint8_t m_length;

    /***********************************************************************************************************
     * can_frame.data[8]:	 [7]        [6]        [5]        [4]        [3]        [2]        [1]        [0]
     *          m_data64: b63...b56, b55...b48, b47...b40, b39...b32, b31...b24, b23...b16, b15...b08, b07...b00
     *        m_data8[8]:    [7]        [6]        [5]        [4]        [3]        [2]        [1]        [0]
     ***********************************************************************************************************/

    union
    {
        uint8_t m_data8[8];
        uint64_t m_data64;
    };
};

#define CMD_XRA_START 0x02
#define CMD_XRA_STOP 0x03
#define CMD_XRA_PREPARE 0x04
#define CMD_XRA_EXPOSE 0x05
#define CMD_XRA_RESET 0x06
#define CMD_XRA_ABORT 0x07
#define CMD_XRA_SKIP 0x08
#define CMD_XRA_WARMUP 0x0a
#define CMD_XRA_SEASON 0x0b
#define CMD_XRA_FILCAL 0x0c
#define CMD_XRA_ESTIMATE 0x0d

#endif