#ifndef HEADER_AETEE_INTEGER_C_H_INCLUDED
#define HEADER_AETEE_INTEGER_C_H_INCLUDED
#include <type_traits>
#include <utility>
#include <limits>

namespace aetee {

// Forward Declarations
namespace detail {
template <std::size_t... I>  static constexpr auto indexSequenceFrom(std::index_sequence<I...>);
template <typename ForwardIt>  static constexpr std::size_t stoull(ForwardIt, ForwardIt);
static constexpr bool isDigit(char);
}

//! int_constant_t
/**
 *
 */
template <typename T, T V>
using int_constant_t = std::integral_constant<T, V>;

//! int_constant_t compile-time instance
template <typename T, T V> static constexpr auto int_constant_c = int_constant_t<T, V>{};


//! bool_constant_t
/**
 *
 */
template <bool B>
using bool_constant_t = int_constant_t<bool, B>;
// Additional aliases
using true_constant_t = bool_constant_t<true>;
using false_constant_t = bool_constant_t<false>;

//! bool_constant_t compile-time instance
template <bool B> static constexpr auto bool_c = bool_constant_t<B>{};
static constexpr auto true_c = true_constant_t{};
static constexpr auto false_c = false_constant_t{};


//! idx_constant_t
/**
 *
 */
template <std::size_t I>
using idx_constant_t = int_constant_t<std::size_t, I>;

//! idx_constant_t compile-time instance
template <std::size_t I> static constexpr auto idx_c = idx_constant_t<I>{};
template <typename... T> static constexpr auto arity_c = idx_constant_t<sizeof...(T)>{};
template <typename Tup> static constexpr auto len_c = idx_constant_t<std::tuple_size<std::decay_t<Tup>>::value>{};


//! idx_sequence_t
/**
 *
 */
template <std::size_t... I>
using idx_sequence_t = std::tuple<idx_constant_t<I>...>;
template <std::size_t N>
using idx_sequence_t_til = decltype(detail::indexSequenceFrom(std::make_index_sequence<N>{}));
template <typename... C>
using idx_sequence_t_for = decltype(detail::indexSequenceFrom(std::index_sequence_for<C...>{}));
template <typename Tup>
using idx_sequence_t_of = decltype(detail::indexSequenceFrom(std::make_index_sequence<std::tuple_size<std::decay_t<Tup>>::value>{}));

//! idx_sequence_t compile-time instances
template <std::size_t... I>  static constexpr auto idx_c_sequence = idx_sequence_t<I...>{};
template <std::size_t N>   constexpr auto idx_c_sequence_til = idx_sequence_t_til<N>{};
template <typename... C>   constexpr auto idx_c_sequence_for = idx_sequence_t_for<C...>{};
template <typename Tup>   constexpr auto idx_c_sequence_of = idx_sequence_t_of<Tup>{};


//! operator""_c
/**
 * Allows treatment of compile-time strings that look like "dddd_c" (d in ['0',
 * '9')) into idx_constants
 */
template <char... C>
constexpr auto operator ""_c ()
{
    static_assert((detail::isDigit(C) && ...));
    constexpr char str[]{(C - '0')...};
    return idx_c<detail::stoull(str, str + sizeof...(C))>;
}


//! int_constant_t -- operators
/**
 * Allows intuitive usage of the compile-time instances for more expressive
 * programming.
 */
template <typename T, T V> constexpr auto operator++(int_constant_t<T, V>) { return int_constant_t<T, (V + 1)>{}; };
template <typename T, T V> constexpr auto operator--(int_constant_t<T, V>) { return int_constant_t<T, (V - 1)>{}; };
template <typename T, T V> constexpr auto operator+(int_constant_t<T, V>) { return int_constant_t<T, (+V)>{}; };
template <typename T, T V> constexpr auto operator-(int_constant_t<T, V>) { return int_constant_t<T, (-V)>{}; };
template <typename T, T V> constexpr auto operator~(int_constant_t<T, V>) { return int_constant_t<T, (~V)>{}; };
template <typename T, T V> constexpr auto operator!(int_constant_t<T, V>) { return int_constant_t<T, (!V)>{}; };
template <typename T, T V, typename U> constexpr auto operator+(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V + std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator+(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V + W)>{}; };
template <typename T, T V, typename U> constexpr auto operator-(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V - std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator-(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V - W)>{}; };
template <typename T, T V, typename U> constexpr auto operator*(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V * std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator*(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V * W)>{}; };
template <typename T, T V, typename U> constexpr auto operator%(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V % std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator%(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V % W)>{}; };
template <typename T, T V, typename U> constexpr auto operator/(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V / std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator/(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V / W)>{}; };
template <typename T, T V, typename U> constexpr auto operator&(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V & std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator&(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V & W)>{}; };
template <typename T, T V, typename U> constexpr auto operator|(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V | std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator|(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V | W)>{}; };
template <typename T, T V, typename U> constexpr auto operator^(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V ^ std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator^(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V ^ W)>{}; };
template <typename T, T V, typename U> constexpr auto operator<<(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V << std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator<<(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V << W)>{}; };
template <typename T, T V, typename U> constexpr auto operator>>(int_constant_t<T, V>, U&& w) { return int_constant_t<std::common_type_t<T, U>, (V >> std::forward<U>(w))>{}; };
template <typename T, T V, typename U, U W> constexpr auto operator>>(int_constant_t<T, V>, int_constant_t<U, W>) { return int_constant_t<std::common_type_t<T, U>, (V >> W)>{}; };
template <typename T, T V, typename U> constexpr auto operator&&(int_constant_t<T, V>, U&& w) { return bool_c<(V && std::forward<U>(w))>; };
template <typename T, T V, typename U, U W> constexpr auto operator&&(int_constant_t<T, V>, int_constant_t<U, W>) { return bool_c<(V && W)>; };
template <typename T, T V, typename U> constexpr auto operator||(int_constant_t<T, V>, U&& w) { return bool_c<(V || std::forward<U>(w))>; };
template <typename T, T V, typename U, U W> constexpr auto operator||(int_constant_t<T, V>, int_constant_t<U, W>) { return bool_c<(V || W)>; };
template <typename T, T V, typename U> constexpr auto operator==(int_constant_t<T, V>, U&& w) { return bool_c<(V == std::forward<U>(w))>; };
template <typename T, T V, typename U, U W> constexpr auto operator==(int_constant_t<T, V>, int_constant_t<U, W>) { return bool_c<(V == W)>; };
template <typename T, T V, typename U> constexpr auto operator!=(int_constant_t<T, V>, U&& w) { return bool_c<(V != std::forward<U>(w))>; };
template <typename T, T V, typename U, U W> constexpr auto operator!=(int_constant_t<T, V>, int_constant_t<U, W>) { return bool_c<(V != W)>; };
template <typename T, T V, typename U> constexpr auto operator<(int_constant_t<T, V>, U&& w) { return bool_c<(V < std::forward<U>(w))>; };
template <typename T, T V, typename U, U W> constexpr auto operator<(int_constant_t<T, V>, int_constant_t<U, W>) { return bool_c<(V < W)>; };
template <typename T, T V, typename U> constexpr auto operator>(int_constant_t<T, V>, U&& w) { return bool_c<(V > std::forward<U>(w))>; };
template <typename T, T V, typename U, U W> constexpr auto operator>(int_constant_t<T, V>, int_constant_t<U, W>) { return bool_c<(V > W)>; };
template <typename T, T V, typename U> constexpr auto operator<=(int_constant_t<T, V>, U&& w) { return bool_c<(V <= std::forward<U>(w))>; };
template <typename T, T V, typename U, U W> constexpr auto operator<=(int_constant_t<T, V>, int_constant_t<U, W>) { return bool_c<(V <= W)>; };
template <typename T, T V, typename U> constexpr auto operator>=(int_constant_t<T, V>, U&& w) { return bool_c<(V >= std::forward<U>(w))>; };
template <typename T, T V, typename U, U W> constexpr auto operator>=(int_constant_t<T, V>, int_constant_t<U, W>) { return bool_c<(V >= W)>; };


namespace detail {

template <std::size_t... I>
static constexpr auto indexSequenceFrom(std::index_sequence<I...>)
{
    return idx_c_sequence<I...>;
}

static constexpr bool isDigit(char c)
{
    return '0' <= c && c < '9';
}

template <typename ForwardIt>
static constexpr std::size_t stoull(ForwardIt first, ForwardIt last)
{
    std::size_t retval = 0;
    while (first != last) {
        retval = (retval * 10) + *first++;
    }
    return retval;
}

} /*namespace detail*/;

} /*namespace aetee*/;

#endif
