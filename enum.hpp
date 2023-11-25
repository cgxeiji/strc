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
constexpr auto make_enum_strc() {
    constexpr auto fn_name = __PRETTY_FUNCTION__;
    constexpr auto len = std::strlen(fn_name);
    constexpr auto idx = find_enum_value_idx(fn_name);
    constexpr auto idxs =
        std::make_integer_sequence<std::size_t,
                                   static_cast<std::size_t>(len - idx - 1)>{};

    return concat_enum_name<TEnum, Value>(idxs);
}

template <typename TEnum, typename Int, Int... Ints>
constexpr auto make_enum_strc(std::integer_sequence<Int, Ints...>) {
    return std::make_tuple(
        make_enum_strc<TEnum, static_cast<TEnum>(Ints)>()...);
}

template <typename TEnum>
struct enum_strc {
    static_assert(std::is_enum<TEnum>::value, "TEnum must be an enum");
    static constexpr auto size = size_of<TEnum>();
    static_assert(size > 0, "size > 0");

    static constexpr auto values = make_enum_strc<TEnum>(
        std::make_integer_sequence<int, static_cast<int>(size)>{});
};

template <typename TEnum, typename TIndicesArray, typename Int>
static auto concat_enum_indices(TIndicesArray arr) {
    return arr;
}

template <typename TEnum, typename TIndicesArray, typename Int, Int First,
          Int... Ints>
static auto concat_enum_indices(TIndicesArray arr) {
    constexpr auto enums = enum_strc<TEnum>::values;
    arr[First] = get_strc_id(std::get<First>(enums));
    arr = concat_enum_indices<TEnum, TIndicesArray, Int, Ints...>(arr);
    return arr;
}

template <typename TEnum, typename TIndicesArray, typename Int, Int... Ints>
static auto get_enum_str_indices(TIndicesArray arr,
                                 std::integer_sequence<Int, Ints...>) {
    arr = concat_enum_indices<TEnum, TIndicesArray, Int, Ints...>(arr);
    return arr;
}

template <typename TEnum>
static auto get_enum_str_indices() {
    constexpr auto size = size_of<TEnum>();
    constexpr auto idxs =
        std::make_integer_sequence<std::size_t,
                                   static_cast<std::size_t>(size)>{};

    std::array<strc_id_t, size> indices{};
    indices = get_enum_str_indices<TEnum>(indices, idxs);

    return indices;
}

template <typename TEnum>
static auto get_enum_strc_id(TEnum value) -> strc_id_t {
    static auto indices = get_enum_str_indices<TEnum>();
    auto idx = static_cast<std::size_t>(value);

    return indices[idx];
}

}  // namespace cgx
