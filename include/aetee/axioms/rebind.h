#ifndef HEADER_AETEE_AXIOMS_REBIND_H_INCLUDED
#define HEADER_AETEE_AXIOMS_REBIND_H_INCLUDED
#include <aetee/type_c.h>

namespace aetee {

namespace detail {

template <template <typename...> class N>
struct rebindDirectFunctor {

    template <typename... A>
    constexpr auto operator()(std::tuple<type_t<A>...>) const
    {
        return type_c<N<A...>>;
    }

} /*struct rebindDirectFunctor*/;

template <template <typename...> class N>
struct rebindFunctor {

    template <template <typename...> class O, typename... A>
    constexpr auto operator()(type_t<O<A...>>) const
    {
        return type_c<N<A...>>;
    }

    static constexpr auto direct = rebindDirectFunctor<N>{};

} /*struct rebindFunctor*/;

} /*namespace detail*/;

template <template <typename...> class N>
static constexpr auto rebind = detail::rebindFunctor<N>{};

} /*namespace aetee*/;

#endif
