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
    void Push(uint64_t data64);
    DataFrame::Node GetTxNode();
    DataFrame::Module GetTxModule();
    uint8_t GetCommand();
    uint64_t GetContent(int index);
    std::vector<uint64_t> GetContent();
    std::string ToString();

private:
    DataFrame::Node m_tx_node, m_rx_node;
    DataFrame::Module m_tx_module, m_rx_module;
    uint8_t m_command;
    std::vector<uint64_t> m_payload;
    // void Serialize();
    // void Deserialize();
};
#endif