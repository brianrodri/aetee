#ifndef HEADER_AETEE_INTEGER_C_H_INCLUDED
#define HEADER_AETEE_INTEGER_C_H_INCLUDED
#include <type_traits>
#include <utility>
#include <limits>

namespace aetee {

//! Overarching types
template <typename T, T V> using integer_constant_t = std::integral_constant<T, V>;
template <typename T> using integer_minimum_t = std::integral_constant<T, std::numeric_limits<T>::max()>;
template <typename T> using integer_maximum_t = std::integral_constant<T, std::numeric_limits<T>::max()>;

//! Helper types
template <std::size_t I> using index_constant_t = integer_constant_t<std::size_t, I>;
template <bool B> using bool_constant_t = integer_constant_t<bool, B>;
using true_constant_t = bool_constant_t<true>;
using false_constant_t = bool_constant_t<false>;

//! Sequence types
template <std::size_t... I> using index_sequence_t = std::tuple<index_constant_t<I>...>;

//! Helper variables
template <std::size_t I> static constexpr auto index_c = index_constant_t<I>{};
template <bool B> static constexpr auto bool_c = bool_constant_t<B>{};
static constexpr auto true_c = bool_c<true>;
static constexpr auto false_c = bool_c<false>;
static constexpr auto max_index_c = integer_maximum_t<std::size_t>{};
template <typename... T> static constexpr auto arity_c = index_c<sizeof...(T)>;

namespace detail {

template <typename T>
struct integralSequenceMakerFunctor {
    template <typename _> struct expander;

    template <T... I>
    struct expander<std::integer_sequence<T, I...>> {
        using type = std::tuple<integer_constant_t<T, I>...>;
    };

    template <T N>
    static constexpr auto make(integer_constant_t<T, N>)
    {
        using S = typename expander<decltype(std::make_integer_sequence<T, N>{})>::type;
        return S{};
    }
};

template <typename IntSeq, std::size_t... I>
static constexpr auto to_index_sequence_impl(IntSeq&& seq, std::index_sequence<I...>)
{
    return std::index_sequence<std::get<I>(std::forward<IntSeq>(seq))...>{};
}

} /*namespace detail*/;

template <std::size_t N>
static constexpr auto index_sequence_c = detail::integralSequenceMakerFunctor<std::size_t>{}.make(index_c<N>);
template <typename... C>
static constexpr auto index_sequence_c_for = detail::integralSequenceMakerFunctor<std::size_t>{}.make(index_c<sizeof...(C)>);

template <typename IntSeq>
static constexpr auto to_index_sequence(IntSeq&& seq)
{
    return detail::to_index_sequence_impl(seq, std::make_index_sequence<std::tuple_size<IntSeq>::value>{});
}

namespace detail {

template <typename ForwardIt>
constexpr std::size_t _c_impl_(ForwardIt first, ForwardIt last)
{
    std::size_t ret{0};
    for (auto it = first; it != last; ++it) { ret = (ret * 10) + (*it - '0'); }
    return ret;
}

constexpr bool isdigit(char c)
{
    auto val = c - '0';
    return val >= 0 && val < 10;
}

} /*namespace detail*/;

template <char... C>
constexpr auto operator ""_c ()
{
    constexpr char str[]{C...};
    return index_c<detail::_c_impl_(str, str + sizeof...(C))>;
}

// Some useful operators for fun compile-time convinience! :)

//! PLUS
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V + W)>
operator+(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! MINUS
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V - W)>
operator-(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! TIMES
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V * W)>
operator*(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! DIVIDE
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V / W)>
operator/(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! MODULO
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V % W)>
operator%(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! PRE-INCREMENT
template <typename T, T V>
constexpr integer_constant_t<T, (V + 1)>
operator++(integer_constant_t<T, V>)
{ return {}; }

//! PRE-DECREMENT
template <typename T, T V>
constexpr integer_constant_t<T, (V - 1)>
operator--(integer_constant_t<T, V>)
{ return {}; }

//! EQUALITY COMPARISON
template <typename T, T V, typename U, U W>
constexpr bool_constant_t<(V == W)>
operator==(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! INEQUALITY COMPARISON
template <typename T, T V, typename U, U W>
constexpr bool_constant_t<(V != W)>
operator!=(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! LESS-THAN COMPARISON
template <typename T, T V, typename U, U W>
constexpr bool_constant_t<(V < W)>
operator<(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! GREATER-THAN COMPARISON
template <typename T, T V, typename U, U W>
constexpr bool_constant_t<(V > W)>
operator>(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! LESS-THAN-EQUAL COMPARISON
template <typename T, T V, typename U, U W>
constexpr bool_constant_t<(V <= W)>
operator<=(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! GREATER-THAN-EQUAL COMPARISON
template <typename T, T V, typename U, U W>
constexpr bool_constant_t<(V >= W)>
operator>=(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! LOGICAL NOT
template <typename T, T V>
constexpr integer_constant_t<T, (!V)>
operator!(integer_constant_t<T, V>)
{ return {}; }

//! LOGICAL AND
template <typename T, T V, typename U, U W>
constexpr bool_constant_t<(V && W)>
operator&&(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! LOGICAL OR
template <typename T, T V, typename U, U W>
constexpr bool_constant_t<(V || W)>
operator||(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! BITWISE AND
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V & W)>
operator&(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! BITWISE OR
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V | W)>
operator|(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! BITWISE XOR
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V ^ W)>
operator^(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! BITWISE COMPLEMENT
template <typename T, T V>
constexpr integer_constant_t<T, (~V)>
operator~(integer_constant_t<T, V>)
{ return {}; }

//! SHIFT LEFT
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V << W)>
operator<<(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

//! SHIFT RIGHT
template <typename T, T V, typename U, U W>
constexpr integer_constant_t<std::common_type_t<T, U>, (V >> W)>
operator>>(integer_constant_t<T, V>, integer_constant_t<U, W>)
{ return {}; }

}; // namespace aetee

#endif
