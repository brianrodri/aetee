#ifndef HEADER_AETEE_INT_C_INT_C_H_INCLUDED
#define HEADER_AETEE_INT_C_INT_C_H_INCLUDED
#include <utility>

namespace aetee {

//! Generic integral constants
template <typename T, T v>
using int_t = std::integral_constant<T, v>;

template <typename T, T v>
static constexpr auto int_c = int_t<T, v>{};

//! Boolean constants
template <bool B>
using bool_t = int_t<bool, B>;

using true_t = bool_t<true>;
using false_t = bool_t<false>;

template <bool B>
static constexpr auto bool_c = bool_t<B>{};
static constexpr auto true_c = bool_c<true>;
static constexpr auto false_c = bool_c<false>;

//! Index constants
template <std::size_t I>
using idx_t = int_t<std::size_t, I>;

template <std::size_t I>
static constexpr auto idx_c = idx_t<I>{};

template <typename... T>
static constexpr auto arity_c = idx_c<sizeof...(T)>;

template <typename Tup>
static constexpr auto len_c = idx_c<std::tuple_size<std::decay_t<Tup>>::value>;

} /*namespace aetee*/;

#endif
