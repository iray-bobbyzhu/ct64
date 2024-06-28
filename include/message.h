#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "dataframe.h"

#include <string>
#include <vector>

class Message
{
public:
    Message() = default;
    virtual ~Message() = default;

    void SetTxNode(DataFrame::Node node_id);
    void SetTxModule(DataFrame::Module module_id);
    void SetRxNode(DataFrame::Node node_id);
    void SetRxModule(DataFrame::Module module_id);
    void SetCommand(uint8_t command);
    void Push8(uint8_t data8);
    void Push64(uint64_t data64, int length);
    DataFrame::Node GetTxNode();
    DataFrame::Module GetTxModule();
    uint8_t GetCommand();
    uint32_t GetStatus();
    std::vector<uint8_t> GetContent();
    std::string ToString();

private:
    DataFrame::Node m_tx_node, m_rx_node;
    DataFrame::Module m_tx_module, m_rx_module;
    uint8_t m_command;
    std::vector<uint8_t> m_payload;
};
#endif