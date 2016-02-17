#ifndef HEADER_AETEE_INTEGER_C_H_INCLUDED
#define HEADER_AETEE_INTEGER_C_H_INCLUDED
#include <type_traits>
#include <utility>
#include <limits>

namespace aetee {

//! int_constant_t

//! Overarching types
template <typename T, T V> using int_constant_t = std::integral_constant<T, V>;
template <typename T> using int_minimum_t = std::integral_constant<T, std::numeric_limits<T>::max()>;
template <typename T> using int_maximum_t = std::integral_constant<T, std::numeric_limits<T>::max()>;

//! Helper types
template <std::size_t I> using index_constant_t = int_constant_t<std::size_t, I>;
template <bool B> using bool_constant_t = int_constant_t<bool, B>;
using true_constant_t = bool_constant_t<true>;
using false_constant_t = bool_constant_t<false>;

//! Sequence types
template <std::size_t... I> using index_sequence_t = std::tuple<index_constant_t<I>...>;

//! Helper variables
template <std::size_t I> static constexpr auto index_c = index_constant_t<I>{};
template <bool B> static constexpr auto bool_c = bool_constant_t<B>{};
static constexpr auto true_c = bool_c<true>;
static constexpr auto false_c = bool_c<false>;
static constexpr auto max_index_c = int_maximum_t<std::size_t>{};
template <typename... T> static constexpr auto arity_c = index_c<sizeof...(T)>;

namespace detail {

template <typename T>
struct integerSequenceMaker {
    template <typename _> struct expander;

    template <T... I>
    struct expander<std::integer_sequence<T, I...>> {
        using type = std::tuple<int_constant_t<T, I>...>;
    };

    template <T N>
    static constexpr auto make(int_constant_t<T, N>)
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
static constexpr auto index_sequence_c_til = detail::integerSequenceMaker<std::size_t>{}.make(index_c<N>);
template <typename... C>
static constexpr auto index_sequence_c_for = detail::integerSequenceMaker<std::size_t>{}.make(arity_c<C...>);
template <typename... C>
static constexpr auto index_sequence_c_for<std::tuple<C...>> = detail::integerSequenceMaker<std::size_t>{}.make(arity_c<C...>);

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
template <typename T, T V> constexpr auto operator++(int_constant_t<T, V>) { return int_constant_t<T, (V + 1)>{}; };
template <typename T, T V> constexpr auto operator--(int_constant_t<T, V>) { return int_constant_t<T, (V - 1)>{}; };
template <typename T, T V> constexpr auto operator+(int_constant_t<T, V>) { return int_constant_t<T, (+V)>{}; };
template <typename T, T V> constexpr auto operator-(int_constant_t<T, V>) { return int_constant_t<T, (-V)>{}; };
template <typename T, T V> constexpr auto operator~(int_constant_t<T, V>) { return int_constant_t<T, (~V)>{}; };
template <typename T, T V> constexpr auto operator!(int_constant_t<T, V>) { return int_constant_t<T, (!V)>{}; };
template <typename T, T V, typename H> constexpr auto operator+(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V + h)>{}; };
template <typename T, T V, typename H> constexpr auto operator-(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V - h)>{}; };
template <typename T, T V, typename H> constexpr auto operator*(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V * h)>{}; };
template <typename T, T V, typename H> constexpr auto operator%(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V % h)>{}; };
template <typename T, T V, typename H> constexpr auto operator/(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V / h)>{}; };
template <typename T, T V, typename H> constexpr auto operator&(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V & h)>{}; };
template <typename T, T V, typename H> constexpr auto operator|(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V | h)>{}; };
template <typename T, T V, typename H> constexpr auto operator^(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V ^ h)>{}; };
template <typename T, T V, typename H> constexpr auto operator<<(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V << h)>{}; };
template <typename T, T V, typename H> constexpr auto operator>>(int_constant_t<T, V>, H&& h) { return int_constant_t<T, (V >> h)>{}; };
template <typename T, T V, typename H> constexpr auto operator&&(int_constant_t<T, V>, H&& h) { return bool_c<(V && h)>; };
template <typename T, T V, typename H> constexpr auto operator||(int_constant_t<T, V>, H&& h) { return bool_c<(V || h)>; };
template <typename T, T V, typename H> constexpr auto operator==(int_constant_t<T, V>, H&& h) { return bool_c<(V == h)>; };
template <typename T, T V, typename H> constexpr auto operator!=(int_constant_t<T, V>, H&& h) { return bool_c<(V != h)>; };
template <typename T, T V, typename H> constexpr auto operator<(int_constant_t<T, V>, H&& h) { return bool_c<(V < h)>; };
template <typename T, T V, typename H> constexpr auto operator>(int_constant_t<T, V>, H&& h) { return bool_c<(V > h)>; };
template <typename T, T V, typename H> constexpr auto operator<=(int_constant_t<T, V>, H&& h) { return bool_c<(V <= h)>; };
template <typename T, T V, typename H> constexpr auto operator>=(int_constant_t<T, V>, H&& h) { return bool_c<(V >= h)>; };

} /*namespace aetee*/;

#endif
