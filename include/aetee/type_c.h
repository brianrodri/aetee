#ifndef HEADER_AETEE_TYPE_C_H_INCLUDED
#define HEADER_AETEE_TYPE_C_H_INCLUDED
#include <tuple>
#include <type_traits>
#include <experimental/type_traits>
#include <aetee/int_c.h>

namespace aetee {

//! Forward Declarations
namespace detail {
template <typename T, typename... L> struct type_constant_t;
template <typename T, typename... L> struct type_index_t;
}

//! type_constant_t
/**
 *
 */
template <typename T>
using type_constant_t = typename detail::type_constant_t<std::decay_t<T>>;

//! type_constant_t compile-time instance
template <typename T> constexpr auto type_c = type_constant_t<std::decay_t<T>>{};


//! type_sequence_t
/**
 *
 */
template <typename... T>
using type_sequence_t = std::tuple<type_constant_t<T>...>;

//! type_sequence_t compile-time instance
template <typename... T> constexpr auto type_sequence_c = type_sequence_t<T...>{};


//! type_at_t
/**
 *
 */
template <size_t I, typename... T>
using type_at_t = std::tuple_element_t<I, std::tuple<T...>>;

//! type_at_t compile-time instance
template <size_t I, typename... T> static constexpr auto type_at_c = type_c<type_at_t<I, T...>>;


//! type_index_t
/**
 * Will resolve to either index of `T` in `L...`, or to `sizeof...(L)`
 */
template <typename T, typename... L>
using type_index_t = index_constant_t<detail::type_index_t<T, L...>::value>;

//! type_index_t compile-time instance
template <typename T, typename... L>
static constexpr auto type_index_c = type_index_t<T, L...>{};


//! type_exists_t
/**
 *
 */
template <typename T, typename... L>
using type_exists_t = bool_constant_t<(type_index_c<T, L...> != arity_c<L...>)>;

//! type_exists_t compile-time instance
template <typename T, typename... L>
static constexpr auto type_exists_c = type_exists_t<T, L...>{};



namespace detail {

// type_constant_t -- implementation
    template <typename T> struct type_constant_t<T> { using type = T; };

// type_index_t ----- implementation
/**
 * Chose to use recursion for this implementation b/c each instantiation may
 * act as another instantiation's recursive step.
 */
    template <typename T>
    struct type_index_t<T> : index_constant_t<0> {};
    template <typename T, typename... L>
    struct type_index_t<T, T, L...> : index_constant_t<0> {};
    template <typename T, typename M, typename... L>
    struct type_index_t<T, M, L...> : index_constant_t<type_index_t<T, L...>::value + 1> {};

    // Specializations for our convinience types
    template <typename T, typename... L>
    struct type_index_t<T, type_sequence_t<L...>> : type_index_t<T, L...> {};
    template <typename T, typename... L>
    struct type_index_t<type_constant_t<T>, L...> : type_index_t<T, L...> {};
    template <typename T, typename... L>
    struct type_index_t<type_constant_t<T>, type_sequence_t<L...>> : type_index_t<T, L...> {};

} /*namespace detail*/;

} /*namespace aetee*/;

#endif
