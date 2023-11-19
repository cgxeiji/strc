#pragma once

#include <array>
#include <cstdint>
#include <cstring>

#include "strc.hpp"

namespace cgx {

template <typename TStrc, typename... Args>
extern strc_id_t get_fmt_strc_id();

template <typename TStrc, typename... Args>
constexpr auto get_fmt_strc_id(TStrc, Args...) {
    return get_fmt_strc_id<TStrc, Args...>();
}

namespace strc_tools {

template <typename... args>
struct size_of;

// recursive size_of stop
template <>
struct size_of<> {
    static const std::size_t value = 0;
};

// recursive size_of
template <typename T, typename... Args>
struct size_of<T, Args...> {
    static const std::size_t value = sizeof(T) + size_of<Args...>::value;
};

// recursive append stop
template <std::size_t TIndex, typename TByteArray>
constexpr std::array<std::uint8_t, TIndex> append(TByteArray arr) {
    return arr;
}

// recursive append once
template <typename TByteArray, typename TValue, std::size_t TIndex>
constexpr std::array<std::uint8_t, TIndex + sizeof(TValue)> append(
    TByteArray arr, TValue v) {
    std::array<std::uint8_t, TIndex + sizeof(TValue)> new_arr;
    std::memcpy(new_arr.data(), arr.data(), TIndex);
    std::memcpy(new_arr.data() + TIndex, &v, sizeof(TValue));
    return new_arr;
}

// recursive append
template <std::size_t TIndex, typename TByteArray, typename TValue,
          typename... Args>
constexpr std::array<std::uint8_t,
                     TIndex + sizeof(TValue) + size_of<Args...>::value>
append(TByteArray arr, TValue v, Args... args) {
    std::array<std::uint8_t, TIndex + sizeof(TValue) + size_of<Args...>::value>
        new_arr;
    std::memcpy(new_arr.data(), arr.data(), TIndex);
    std::memcpy(new_arr.data() + TIndex, &v, sizeof(TValue));
    return append<TIndex + sizeof(TValue)>(new_arr, args...);
}

}  // namespace strc_tools

template <typename TStrc, typename... Args>
constexpr auto format(TStrc, Args... args) noexcept {
    std::array<std::uint8_t,
               strc_tools::size_of<Args...>::value + TStrc::id_size>
        arr = {};
    auto id = get_fmt_strc_id<TStrc, Args...>();
    std::memcpy(arr.data(), &id, TStrc::id_size);

    return strc_tools::append<TStrc::id_size>(arr, args...);
}

}  // namespace cgx
