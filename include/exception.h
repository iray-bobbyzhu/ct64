#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include "log.h"
#include <string>

class Exception
{
public:
    Exception(uint32_t code, std::string &message)
        : m_code(code)
        , m_message(message)
    {
        Log::Error(fmt() << "E" << std::hex << std::setw(8) << std::setfill('0') << code << ": " << message);
    }

    virtual ~Exception() = default;

    uint32_t GetCode()
    {
        return m_code;
    }

    std::string GetMessage()
    {
        return m_message;
    }

private:
    uint32_t m_code;
    std::string m_message;
};

#define E_SUCCESS 0x00000000

/*
 * Error code format: 0xE0mmzzzz
 * E0: padding
 * mm: module id
 * zzzz: error code
 */
#define E_XRY_FAIL 0xE001BEEF

#endif