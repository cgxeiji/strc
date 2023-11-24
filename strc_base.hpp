#pragma once

#include <tuple>
#include <type_traits>

namespace cgx {

#ifdef CGX_STRC_8BIT
using strc_id_t = char;
#elif defined(CGX_STRC_16BIT)
using strc_id_t = unsigned short;
#elif defined(CGX_STRC_32BIT)
using strc_id_t = unsigned int;
#elif defined(CGX_STRC_64BIT)
using strc_id_t = unsigned long long;
#else
using strc_id_t = unsigned int;
#endif

template <typename TStrc>
extern auto get_strc_id() -> strc_id_t;

template <typename TStrc>
constexpr auto get_strc_id(TStrc) -> strc_id_t {
    return get_strc_id<TStrc>();
}

template <typename TChar, TChar... chars>
struct strc {
    static constexpr auto id_size = sizeof(strc_id_t);
    strc_id_t id() const { return get_strc_id<strc>(); }
    static constexpr auto split() noexcept {
        return std::make_tuple(strc<TChar, chars>{}...);
    }
};

}  // namespace cgx

template <typename TChar, TChar... chars>
constexpr auto operator""_strc() {
    return cgx::strc<TChar, chars...>{};
}

template <typename TChar, TChar... chars_lhs, TChar... chars_rhs>
constexpr auto operator+(cgx::strc<TChar, chars_lhs...>,
                         cgx::strc<TChar, chars_rhs...>) noexcept {
    return cgx::strc<TChar, chars_lhs..., chars_rhs...>{};
}

template <typename TChar, TChar... chars_lhs, TChar... chars_rhs>
constexpr auto operator==(cgx::strc<TChar, chars_lhs...>,
                          cgx::strc<TChar, chars_rhs...>) noexcept {
    return std::is_same<cgx::strc<TChar, chars_lhs...>,
                        cgx::strc<TChar, chars_rhs...>>::value;
}

template <typename TChar, TChar... chars_lhs, TChar... chars_rhs>
constexpr auto operator!=(cgx::strc<TChar, chars_lhs...>,
                          cgx::strc<TChar, chars_rhs...>) noexcept {
    return !std::is_same<cgx::strc<TChar, chars_lhs...>,
                         cgx::strc<TChar, chars_rhs...>>::value;
}
