#ifndef HEADER_AETEE_TRAITS_CAST_H_INCLUDED
#define HEADER_AETEE_TRAITS_CAST_H_INCLUDED
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

template <typename U>
struct castFunctor {

    template <typename T, T V>
    constexpr auto operator()(int_t<T, V>) const
    {
        return int_c<U, static_cast<U>(V)>;
    }

} /*struct castFunctor*/;

} /*namespace detail*/;

template <typename U>
static constexpr auto cast = detail::castFunctor<U>{};

} /*namespace aetee*/;

#endif
