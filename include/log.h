/*
 *
 * Created on: Oct 3, 2019
 * Author: Bobby Zhu
 */

#ifndef LOG_H_
#define LOG_H_

#include <iomanip>
#include <sstream>
#include <thread>

#include "syncqueue.h"

#ifdef CANBUS_LOG
#include "message_factory.h"
#include "socket_can.h"

using Module = FmiCanFrame::ModuleId;

#define CMD_OUTPUTLOG 0x50
#endif

using base_type = std::ios_base &(std::ios_base &);
using endl_type = std::ostream &(std::ostream &);

template <typename Child>
class FormatterBase
{
public:
    FormatterBase() = default;

    FormatterBase(std::string str)
    {
        m_oss << str;
    }

    virtual ~FormatterBase() = default;

    template <typename T>
    Child &operator<<(const T &content)
    {
        m_oss << content;

        return *((Child *)this);
    }

    Child &operator<<(base_type base)
    {
        m_oss << base;

        return *((Child *)this);
    }

    Child &operator<<(endl_type endl)
    {
        m_oss << endl;

        return *((Child *)this);
    }

    operator std::string()
    {
        return m_oss.str();
    }

protected:
    std::string CurrentTime()
    {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto now_time = system_clock::to_time_t(now);
        auto now_tm = std::localtime(&now_time);

        std::ostringstream oss;

        oss << std::setw(2) << std::setfill('0') << now_tm->tm_year - 100 << std::setw(2) << std::setfill('0') << now_tm->tm_mon + 1 << std::setw(2) << std::setfill('0') << now_tm->tm_mday << "|"
            << std::setw(2) << std::setfill('0') << now_tm->tm_hour << ":" << std::setw(2) << std::setfill('0') << now_tm->tm_min << ":" << std::setw(2) << std::setfill('0') << now_tm->tm_sec << "."
            << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(now.time_since_epoch()).count() % 1000;

        return oss.str();
    }

    std::ostringstream m_oss;

private:
};

struct stamp : FormatterBase<stamp>
{
    stamp()
        : FormatterBase("[" + CurrentTime() + "] "){};

    stamp(const char *message)
        : FormatterBase()
    {
        m_oss << message;
    }

    stamp(const std::string &message)
        : FormatterBase()
    {
        m_oss << message;
    }
};

struct fmt : FormatterBase<fmt>
{
    fmt()
        : FormatterBase(){};

    fmt(const char *message)
        : FormatterBase()
    {
        m_oss << message;
    }

    fmt(const std::string &message)
        : FormatterBase()
    {
        m_oss << message;
    }
};

struct ent : FormatterBase<ent>
{
    ent()
        : FormatterBase()
    {
        m_oss << "i--(>) ";
    }
};

struct ext : FormatterBase<ext>
{

    ext()
        : FormatterBase()
    {
        m_oss << "<--(o) ";
    }
};

class Log
{
public:
    enum class Level : int
    {
        debug = 0,
        info = 1,
        warning = 2,
        error = 3
    };
#ifdef CANBUS_LOG
    enum class Output : int
    {
        none = 0,
        stdcout = 1,
        file = 2,
        can = 4
    };
#else
    enum class Output : int
    {
        none = 0,
        stdcout = 1,
        file = 2
    };
#endif

    virtual ~Log();

    static Log &Get();

    /*
     *   Any messages with level high than or equal to the set level will be logged,
     *   otherwise will be suppressed.
     *   By default, all messages are logged.
     */
    static void SetLevel(Level level);

    /*
     *  Disable logging function
     */
    static void DisableOutput();

    /*
     * Enable messages to be logged in files
     */
    static void EnableFileOutput();

    /*
     * Enable messages to be logged in console
     */
    static void EnableStandardOutput();

#ifdef CANBUS_LOG
    /*
     * Enable messages to be logged through CAN bus
     */
    static void EnableCanbusOutput(SocketCan *socket_can);
#endif

    /*
      Prefix time stamps to messages
     */
    static void EnableTimestamp();

    /*
      Turn off time stamps to messages
     */
    static void DisableTimestamp();
    static void Debug(const std::string &message);
    static void Info(const std::string &message);
    static void Warning(const std::string &message);
    static void Error(const std::string &message);

private:
    Log();

    void StartThread();
    void StopThread();
    void CreateFile();
    void CloseFile();

#ifdef CANBUS_LOG
    void SendMessageCan(std::string &message);
#endif

    void OutputMessage();

    static Level m_level;
    static Output m_output;
    static bool m_timestamp_enabled;

    static bool m_thread_running;
    static std::thread m_output_thread;
    static int m_creation_day;

#ifdef CANBUS_LOG
    static SocketCan *m_socket_can;
#endif

    static SyncQueue<std::string> m_message_queue;
    static std::ofstream m_log_file;
};
#endif /* LOG_H_ */
