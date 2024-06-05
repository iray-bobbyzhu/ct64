#ifndef REGISTER_BASE_H
#define REGISTER_BASE_H

#include <cstdint>
#include <mutex>
#include <atomic>

class RegisterBase
{
public:
    RegisterBase(uint32_t offset);
    virtual ~RegisterBase();

    uint32_t Read();
    void Write(uint32_t value);

protected:
    static std::atomic<int> m_references;    // keep track of how many child objects exist
    static void *m_vmem_ptr;    // virutal memory base address
    static int m_fd;
    static std::mutex m_mutex;  // to pretect memory read & write

    uint32_t m_offset;          // register address offset

private:
    const int SHARED_MEM_SIZE = 0x10000;
    const uint32_t MMIO_BASE_ADDRESS = 0x40000000;
};

#endif