#pragma once
#include <string>
#include <vector>

namespace StringUtils {
    std::vector<std::string> split(const std::string& str, char delim);
    std::string trim(const std::string& str);
    std::string toLower(const std::string& str);
    std::vector<std::string> wordWrap(const std::string& str, size_t maxWidth);
    std::string format(const char* fmt, ...);
}
