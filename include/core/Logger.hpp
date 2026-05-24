#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <sstream>

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    static Logger& instance();

    void setLevel(LogLevel level);
    void log(LogLevel level, const std::string& message);

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    LogLevel level_ = LogLevel::DEBUG;
    std::ofstream file_;
    std::mutex mutex_;

    static const char* levelToString(LogLevel level);
    static std::string getTimestamp();
};

#define VB_LOG_TRACE(...)   do { std::ostringstream _vb_oss_; _vb_oss_ << __VA_ARGS__; Logger::instance().log(LogLevel::TRACE, _vb_oss_.str()); } while(0)
#define VB_LOG_DEBUG(...)   do { std::ostringstream _vb_oss_; _vb_oss_ << __VA_ARGS__; Logger::instance().log(LogLevel::DEBUG, _vb_oss_.str()); } while(0)
#define VB_LOG_INFO(...)    do { std::ostringstream _vb_oss_; _vb_oss_ << __VA_ARGS__; Logger::instance().log(LogLevel::INFO, _vb_oss_.str()); } while(0)
#define VB_LOG_WARN(...)    do { std::ostringstream _vb_oss_; _vb_oss_ << __VA_ARGS__; Logger::instance().log(LogLevel::WARN, _vb_oss_.str()); } while(0)
#define VB_LOG_ERROR(...)   do { std::ostringstream _vb_oss_; _vb_oss_ << __VA_ARGS__; Logger::instance().log(LogLevel::ERROR, _vb_oss_.str()); } while(0)
