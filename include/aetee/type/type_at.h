#ifndef HEADER_AETEE_TYPE_TYPE_AT_H_INCLUDED
#define HEADER_AETEE_TYPE_TYPE_AT_H_INCLUDED
#include <aetee/type/type_c.h>

namespace aetee {

namespace detail {

template <std::size_t I, typename H, typename... L>
struct typeAtResolverFunctor {
    using type = typename typeAtResolverFunctor<I-1, L...>::type;
};

template <typename H, typename... L>
struct typeAtResolverFunctor<0, H, L...> {
    using type = H;
};

} /*namespace detail*/;

template <std::size_t I, typename... L> using type_at_t = typename detail::typeAtResolverFunctor<I, L...>::type;
template <std::size_t I, typename... L> static constexpr auto type_at_c = type_c<type_at_t<I, L...>>;

} /*namespace aetee*/;

#endif
