#ifndef HEADER_AETEE_MATH_SUGAR_ALLOF_H_INCLUDED
#define HEADER_AETEE_MATH_SUGAR_ALLOF_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/type_c.h>
#include <aetee/axioms/value.h>

namespace aetee {

namespace detail {

struct allOfFunctor {

    template <typename... X>
    constexpr auto operator()(type_c_sequence_t<X...>) const
    {
        return bool_c<(X::value && ... && true)>;
    }

    template <typename T, T... V>
    constexpr auto operator()(int_c_sequence_t<T, V...>) const
    {
        return bool_c<(V && ... && true)>;
    }

    template <typename... X>
    constexpr auto operator()(type_c_sequence_t<X>...) const
    {
        return bool_c<(X::value && ... && true)>;
    }

} /*struct allOfFunctor*/;

} /*namespace detail*/;

static constexpr auto allof = detail::allOfFunctor{};

} /*namespace aetee*/;

#endif
