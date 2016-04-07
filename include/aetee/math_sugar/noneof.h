#ifndef HEADER_AETEE_MATH_SUGAR_NONEOF_H_INCLUDED
#define HEADER_AETEE_MATH_SUGAR_NONEOF_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/type_c.h>
#include <aetee/axioms/to_c.h>
#include <aetee/axioms/value.h>

namespace aetee {

namespace detail {

struct noneOfFunctor {

    template <typename... X>
    constexpr auto operator()(type_c_sequence_t<X...>) const
    {
        return !bool_c<(X::value || ...)>;
    }

    template <typename... X>
    constexpr auto operator()(type_t<X>...) const
    {
        return !bool_c<(X::value || ...)>;
    }

    template <typename... X>
    constexpr auto operator()(X&&... x) const
    {
        return (value(x) || ...);
    }

} /*struct noneOfFunctor*/;

} /*namespace detail*/;

static constexpr auto noneof = detail::noneOfFunctor{};

} /*namespace aetee*/;

#endif


