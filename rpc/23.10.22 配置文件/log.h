#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H

#include<string>
#include<queue>
#include<memory>
#include"Rocket/common/config.h"
#include"Rocket/common/mutex.h"

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

    //打印日志宏
#define DEBUGLOG(str,...)\
if(Rocket::Logger::GetGlobalLogger()->getLogLevel()<=Rocket::Debug)\
{\
    Rocket::Logger::GetGlobalLogger()->pushLog((new Rocket::LogEvent(Rocket::LogLevel::Debug))->toString()\
    +"["+std::string(__FILE__)+":"+std::to_string(__LINE__)+"]\t"+Rocket::formatString(str,##__VA_ARGS__)+"\n");\
    Rocket::Logger::GetGlobalLogger()->log();\
}\

#define INFOLOG(str,...)\
if(Rocket::Logger::GetGlobalLogger()->getLogLevel()<=Rocket::Info)\
{\
    Rocket::Logger::GetGlobalLogger()->pushLog((new Rocket::LogEvent(Rocket::LogLevel::Info))->toString()\
    +"["+std::string(__FILE__)+":"+std::to_string(__LINE__)+"]\t"+Rocket::formatString(str,##__VA_ARGS__)+"\n");\
    Rocket::Logger::GetGlobalLogger()->log();\
}\

#define ERRORLOG(str,...)\
if(Rocket::Logger::GetGlobalLogger()->getLogLevel()<=Rocket::Error)\
{\
    Rocket::Logger::GetGlobalLogger()->pushLog((new Rocket::LogEvent(Rocket::LogLevel::Error))->toString()\
    +"["+std::string(__FILE__)+":"+std::to_string(__LINE__)+"]\t"+Rocket::formatString(str,##__VA_ARGS__)+"\n");\
    Rocket::Logger::GetGlobalLogger()->log();\
}\


    enum LogLevel {
        Unknown = 0,
        Debug = 1,
        Info = 2,
        Error = 3
    };

    std::string LogLevelToString(LogLevel level);
    LogLevel StringToLogLevel(const std::string& log_level);



    //处理日志
    class Logger {
    public:
        typedef std::shared_ptr<Logger>s_ptr;

        Logger(LogLevel level) :m_set_level(level) {}

        void pushLog(const std::string& msg);

        void log();
        LogLevel getLogLevel() const {
            return m_set_level;
        }

    public:
        static Logger* GetGlobalLogger();
        static void InitGlobalLogger();

    private:
        LogLevel m_set_level;
        std::queue<std::string>m_buffer;

        Mutex m_mutex;

    };




    //日志事件类
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