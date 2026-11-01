#pragma once

#include <initializer_list>
#include <string>
#include <vector>

namespace registration {

std::string toUpper(const std::string& text);
std::string toLower(const std::string& text);
std::string trim(const std::string& text);
std::vector<std::string> split(const std::string& text, char delimiter);

template <typename Range>
std::string join(const Range& parts, const std::string& delimiter) {
    std::string result;
    bool first = true;
    for (const auto& part : parts) {
        if (!first) {
            result += delimiter;
        }
        first = false;
        result += part;
    }
    return result;
}

std::string join(std::initializer_list<std::string> parts, const std::string& delimiter);

bool startsWith(const std::string& text, const std::string& prefix);
bool endsWith(const std::string& text, const std::string& suffix);
std::string replaceAll(const std::string& text, const std::string& from, const std::string& to);
int countChar(const std::string& text, char ch);
bool isPalindrome(const std::string& text);
std::string reverseString(const std::string& text);

} // namespace registration
