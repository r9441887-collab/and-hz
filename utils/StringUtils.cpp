#include "../../include/utils/StringUtils.hpp"
#include <sstream>
#include <algorithm>
#include <cstdarg>
#include <cstdio>

namespace StringUtils {

std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        result.push_back(token);
    }
    return result;
}

std::string trim(const std::string& str) {
    if (str.empty()) return str;
    size_t start = 0;
    while (start < str.size() && (str[start] == ' ' || str[start] == '\t' ||
           str[start] == '\r' || str[start] == '\n')) {
        ++start;
    }
    size_t end = str.size();
    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' ||
           str[end - 1] == '\r' || str[end - 1] == '\n')) {
        --end;
    }
    return str.substr(start, end - start);
}

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

std::vector<std::string> wordWrap(const std::string& str, size_t maxWidth) {
    std::vector<std::string> lines;
    std::string current;
    std::string word;
    for (size_t i = 0; i <= str.size(); ++i) {
        if (i == str.size() || str[i] == ' ' || str[i] == '\n') {
            if (current.size() + (current.empty() ? 0 : 1) + word.size() > maxWidth && !current.empty()) {
                lines.push_back(current);
                current.clear();
            }
            if (!current.empty()) current += ' ';
            current += word;
            word.clear();
            if (i < str.size() && str[i] == '\n') {
                lines.push_back(current);
                current.clear();
            }
        } else {
            word += str[i];
        }
    }
    if (!current.empty()) lines.push_back(current);
    if (lines.empty() && !str.empty()) lines.push_back(str);
    return lines;
}

std::string format(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    va_list argsCopy;
    va_copy(argsCopy, args);
    int len = std::vsnprintf(nullptr, 0, fmt, argsCopy);
    va_end(argsCopy);
    if (len < 0) {
        va_end(args);
        return std::string();
    }
    std::string result(static_cast<size_t>(len), '\0');
    std::vsnprintf(&result[0], result.size() + 1, fmt, args);
    va_end(args);
    return result;
}

}
