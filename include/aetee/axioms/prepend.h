#ifndef HEADER_AETEE_AXIOMS_PREPEND_H_INCLUDED
#define HEADER_AETEE_AXIOMS_PREPEND_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct prependFunctor {
    template <typename Tup, typename X>
    constexpr auto operator()(Tup&& tup, X&& x) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return impl(std::forward<Tup>(tup), std::forward<X>(x), std::make_index_sequence<N>{});
    }

private:
    template <typename Tup, typename X, size_t... I>
    constexpr auto impl(Tup&& tup, X&& x, std::index_sequence<I...>) const
    {
        return std::make_tuple(std::forward<X>(x), std::get<I>(std::forward<Tup>(tup))...);
    }
} /*struct prependFunctor*/;

} /*namespace detail*/;

static constexpr auto prepend = detail::prependFunctor{};

} /*namespace aetee*/;

#endif
