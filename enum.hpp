#pragma once

#include <cstring>

#include "strc_base.hpp"

namespace cgx {

template <typename TEnum, TEnum Value>
constexpr bool is_valid_enum() {
    constexpr auto fn_name = __PRETTY_FUNCTION__;
    constexpr auto fn_name_len = std::strlen(fn_name);
    static_assert(fn_name_len > 0, "fn_name_len > 0");

    auto i = std::strlen(fn_name);
    for (; i >= 0; i--) {
        if (fn_name[i] == ' ') {
            break;
        }
    }

    char c = fn_name[i + 1];
    if ((c == '(') || (c >= '0' && c <= '0')) {
        return false;
    }

    return true;
}

template <typename TEnum>
constexpr unsigned int enum_count() {
    return 0;
}

template <typename TEnum, TEnum Value, TEnum... Values>
constexpr unsigned int enum_count() {
    constexpr bool is_valid = is_valid_enum<TEnum, Value>();
    return (is_valid ? 1 : 0) + enum_count<TEnum, Values...>();
}

template <typename TEnum, int... Ints>
constexpr unsigned int enum_count(std::integer_sequence<int, Ints...>) {
    return enum_count<TEnum, static_cast<TEnum>(Ints)...>();
}

template <typename TEnum>
constexpr auto size_of() {
    return enum_count<TEnum>(
        std::make_integer_sequence<int, static_cast<int>(100)>{});
}

template <typename TStr>
constexpr auto find_enum_value_idx(TStr value) {
    auto i = std::strlen(value);
    for (; i >= 0; i--) {
        if (value[i] == 'V') {
            break;
        }
    }

    return i + std::strlen("Value = ");
}

template <typename TEnum, TEnum Value, typename Int>
constexpr auto concat_enum_char() {
    return ""_strc;
}

template <typename TEnum, TEnum Value, typename Int, Int First, Int... Ints>
constexpr auto concat_enum_char() {
    constexpr auto fn_name = __PRETTY_FUNCTION__;
    constexpr auto idx = find_enum_value_idx(fn_name);
    return strc<char, fn_name[First + idx]>{} +
           concat_enum_char<TEnum, Value, Int, Ints...>();
}

template <typename TEnum, TEnum Value, typename Int, Int... Ints>
constexpr auto concat_enum_name(std::integer_sequence<Int, Ints...>) {
    return concat_enum_char<TEnum, Value, Int, Ints...>();
}

template <typename TEnum, TEnum Value>
constexpr auto enum_strc() {
    constexpr auto fn_name = __PRETTY_FUNCTION__;
    constexpr auto len = std::strlen(fn_name);
    constexpr auto idx = find_enum_value_idx(fn_name);
    constexpr auto idxs =
        std::make_integer_sequence<std::size_t,
                                   static_cast<std::size_t>(len - idx - 1)>{};

    return concat_enum_name<TEnum, Value>(idxs);
}

template <typename TEnum, TEnum Value>
constexpr auto make_enum_strc() {
    return enum_strc<TEnum, Value>();
}

}  // namespace cgx
