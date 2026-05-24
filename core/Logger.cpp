#include "../../include/core/Logger.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

Logger& Logger::instance() {
    static Logger inst;
    return inst;
}

Logger::Logger() {
    file_.open("voidbreaker.log", std::ios::out | std::ios::trunc);
    if (!file_.is_open()) {
        std::cerr << "[Logger] Failed to open voidbreaker.log for writing\n";
    }
}

Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
}

void Logger::setLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(mutex_);
    level_ = level;
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (level < level_) return;

    std::string timestamp = getTimestamp();
    const char* levelStr = levelToString(level);
    std::string output = "[" + timestamp + "][" + levelStr + "] " + message;

    if (file_.is_open()) {
        file_ << output << std::endl;
    }

    if (level >= LogLevel::WARN) {
        std::cerr << output << std::endl;
    } else {
        std::cout << output << std::endl;
    }
}

const char* Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    struct tm tm_buf;
    localtime_s(&tm_buf, &in_time_t);

    std::ostringstream ss;
    ss << std::put_time(&tm_buf, "%H:%M:%S");
    return ss.str();
}
