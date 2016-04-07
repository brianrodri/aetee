#ifndef HEADER_AETEE_TYPE_AT_H_INCLUDED
#define HEADER_AETEE_TYPE_AT_H_INCLUDED
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

template <typename T, typename... L>
struct typeIndexResolverFunctor;

template <typename T>
struct typeIndexResolverFunctor<T> {
    static constexpr std::size_t value = 0;
};

template <typename T, typename... L>
struct typeIndexResolverFunctor<T, T, L...> {
    static constexpr std::size_t value = 0;
};

template <typename T, typename U, typename... L>
struct typeIndexResolverFunctor<T, U, L...> {
    static constexpr std::size_t value = 1 + typeIndexResolverFunctor<T, L...>::value;
};

} /*namespace detail*/;

template <typename T, typename... L>
static constexpr auto type_idx_c = idx_c<detail::typeIndexResolverFunctor<T, L...>>;

} /*namespace aetee*/; 

#endif
