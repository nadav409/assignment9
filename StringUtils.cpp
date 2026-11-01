#include "StringUtils.hpp"

#include <algorithm>
#include <cctype>

namespace registration {

std::string toUpper(const std::string& text) {
    std::string result = text;
    for (char& ch : result) {
        ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    }
    return result;
}

std::string toLower(const std::string& text) {
    std::string result = text;
    for (char& ch : result) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return result;
}

std::string trim(const std::string& text) {
    const std::string whitespace = " \t\n\r\f\v";
    const auto first = text.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }
    const auto last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> parts;
    std::string current;
    for (char ch : text) {
        if (ch == delimiter) {
            parts.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    parts.push_back(current);
    return parts;
}

std::string join(std::initializer_list<std::string> parts, const std::string& delimiter) {
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

bool startsWith(const std::string& text, const std::string& prefix) {
    return text.rfind(prefix, 0) == 0;
}

bool endsWith(const std::string& text, const std::string& suffix) {
    if (suffix.size() > text.size()) {
        return false;
    }
    return text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string replaceAll(const std::string& text, const std::string& from, const std::string& to) {
    if (from.empty()) {
        return text;
    }

    std::string result = text;
    std::size_t position = 0;
    while ((position = result.find(from, position)) != std::string::npos) {
        result.replace(position, from.size(), to);
        position += to.size();
    }
    return result;
}

int countChar(const std::string& text, char ch) {
    return static_cast<int>(std::count(text.begin(), text.end(), ch));
}

bool isPalindrome(const std::string& text) {
    std::string cleaned;
    cleaned.reserve(text.size());
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            cleaned.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    std::string reversed(cleaned.rbegin(), cleaned.rend());
    return cleaned == reversed;
}

std::string reverseString(const std::string& text) {
    return std::string(text.rbegin(), text.rend());
}

} // namespace registration
