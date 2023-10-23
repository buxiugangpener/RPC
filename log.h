#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H

#include<string>
#include<queue>
#include<memory>

namespace Rocket {

    //用于格式化字符串。它使用了可变参数模板和C语言的snprintf函数来实现
    template<typename... Args>
    std::string formatString(const char* str, Args&&... args) {
        int size = snprintf(nullptr, 0, str, args...);

        std::string result;
        if (size > 0) {
            result.resize(size);
            snprintf(&result[0], size + 1, str, args...);
        }
        return result;
    }

#define DEBUGLOG(str,...)\
    std::string msg=(new Rocket::LogEvent(Rocket::LogLevel::Debug))->toString()+Rocket::formatString(str,##__VA_ARGS__);\
    msg+="\n";\
    Rocket::Logger::GetGlobalLogger()->pushLog(msg);\
    Rocket::Logger::GetGlobalLogger()->log()\


    enum LogLevel {
        Unknown = 0,
        Debug = 1,
        Info = 2,
        Error = 3
    };

    //处理日志
    class Logger {
    public:
        typedef std::shared_ptr<Logger>s_ptr;

        void pushLog(const std::string& msg);

        void log();
    public:
        static Logger* GetGlobalLogger();

    private:
        LogLevel m_set_level;
        std::queue<std::string>m_buffer;
    };

    std::string LogLevelToString(LogLevel level);

    class LogEvent {
    public:
        LogEvent(LogLevel level) :m_level(level) {};

        std::string getFileName() const {
            return m_file_name;
        }

        LogLevel getLogLevel() const {
            return m_level;
        }

        std::string toString();
    private:
        std::string m_file_name;
        int32_t m_file_line;
        int32_t m_pid;
        int32_t m_thread_id;

        LogLevel m_level;
    };

}
#endif
/*
整体架构
类1、LogEvent
类2、Logger

*/