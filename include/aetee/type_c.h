#ifndef HEADER_AETEE_TYPE_C_H_INCLUDED
#define HEADER_AETEE_TYPE_C_H_INCLUDED
#include <tuple>
#include <type_traits>
#include <experimental/type_traits>
#include <aetee/int_c.h>

namespace aetee {

//! type_constant_t
template <typename T> struct type_constant_t { using type = std::decay_t<T>; };
template <typename T> constexpr auto type_c = type_constant_t<T>{};

template <typename... T> using type_sequence_t = std::tuple<type_constant_t<T>...>;
template <typename... T> constexpr auto type_sequence_c = type_sequence_t<T...>{};

//! type_at_t
template <size_t I, typename... T> using type_at_t = std::tuple_element_t<I, std::tuple<T...>>;

template <size_t I, typename... T>
static constexpr auto type_at_c = type_c<type_at_t<I, T...>>;

//! type_exists
template <typename H, typename... T>
struct type_exists : std::experimental::disjunction<std::is_same<H, T>...> {};

template <typename H, typename... T>
static constexpr auto type_exists_v = type_exists<H, T...>{};

//! type_index
namespace detail {

template <typename H, typename... T>
struct type_index_impl;

template <typename H>
struct type_index_impl<H> : index_constant_t<0> {};

template <typename H, typename... T>
struct type_index_impl<H, H, T...> : index_constant_t<0> {};

template <typename H, typename X, typename... T>
struct type_index_impl<H, X, T...> : index_constant_t<1 + type_index_impl<H, T...>::value> {};

}; // namespace detail

template <typename T, typename... L>
using type_index = detail::type_index_impl<T, L...>;

template <typename T, typename... L>
static constexpr auto type_index_c = type_index<T, L...>{};

template <typename T>
static constexpr auto sizeof_c(type_constant_t<T>) {
    return index_c<sizeof(T)>;
}

template <typename T>
static constexpr auto alignof_c(type_constant_t<T>) {
    return index_c<alignof(T)>;
}

}; // namespace aetee

#endif
