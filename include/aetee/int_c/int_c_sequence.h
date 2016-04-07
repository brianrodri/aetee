#ifndef HEADER_AETEE_INT_C_INT_C_SEQUENCE_H_INCLUDED
#define HEADER_AETEE_INT_C_INT_C_SEQUENCE_H_INCLUDED
#include <aetee/int_c/int_c.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

template <std::size_t... I>
constexpr auto generateIndexSequenceImpl(std::index_sequence<I...>)
{
    return std::make_tuple(idx_c<I>...);
}

template <std::size_t N>
constexpr auto generateIndexSequence(idx_t<N>)
{
    return generateIndexSequenceImpl(std::make_index_sequence<N>());
}

} /*namespace detail*/;

template <typename T, T... vs>
using int_c_sequence_t = std::tuple<int_t<T, vs>...>;

template <std::size_t... vs>
using idx_c_sequence_t = int_c_sequence_t<std::size_t, vs...>;

template <std::size_t... I>
static constexpr auto idx_c_sequence = idx_c_sequence_t<I...>{};

template <std::size_t N>
static constexpr auto idx_c_sequence_til = detail::generateIndexSequence(idx_c<N>);

template <typename... C>
static constexpr auto idx_c_sequence_for = detail::generateIndexSequence(arity_c<C...>);

template <typename Tup>
static constexpr auto idx_c_sequence_of = detail::generateIndexSequence(len_c<Tup>);

} /*namespace aetee*/;

#endif
