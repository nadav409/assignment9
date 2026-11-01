#pragma once

#include <sstream>
#include <string>
#include <type_traits>

namespace registration {

template <typename T>
std::string describeType() {
    if constexpr (std::is_same_v<T, std::string>) {
        return "string";
    } else if constexpr (std::is_pointer_v<T>) {
        return "pointer";
    } else if constexpr (std::is_floating_point_v<T>) {
        return "floating-point";
    } else if constexpr (std::is_integral_v<T>) {
        return "integral";
    } else {
        return "other";
    }
}

template <typename T>
constexpr bool isNumeric() {
    return std::is_integral_v<T> || std::is_floating_point_v<T>;
}

template <typename Left, typename Right>
constexpr bool areSameType() {
    return std::is_same_v<Left, Right>;
}

template <typename Number>
std::string numericToString(Number value) {
    if constexpr (std::is_integral_v<Number>) {
        return std::to_string(value);
    } else {
        std::ostringstream output;
        output.setf(std::ios::fixed);
        output.precision(2);
        output << value;
        return output.str();
    }
}

template <typename Left, typename Right>
auto safeAdd(Left left, Right right) {
    using Result = std::conditional_t<std::is_integral_v<Left> && std::is_integral_v<Right>, long long, std::common_type_t<Left, Right>>;
    return static_cast<Result>(left) + static_cast<Result>(right);
}

template <typename T>
T getZero() {
    return T{};
}

} // namespace registration
