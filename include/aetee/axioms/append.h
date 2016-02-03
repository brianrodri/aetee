#ifndef HEADER_AETEE_AXIOMS_APPEND_H_INCLUDED
#define HEADER_AETEE_AXIOMS_APPEND_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct appendFunctor {
    template <typename Tup, typename X>
    constexpr auto operator()(Tup&& tup, X&& x) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return impl(std::forward<Tup>(tup), std::make_index_sequence<N>{}, std::forward<X>(x));
    }

private:
    template <typename Tup, size_t... I, typename X>
    constexpr auto impl(Tup&& tup, std::index_sequence<I...>, X&& x) const
    {
        return std::make_tuple(std::get<I>(std::forward<Tup>(tup))..., std::forward<X>(x));
    }
} /*struct appendFunctor*/;

} /*namespace detail*/;

static constexpr auto append = detail::appendFunctor{};

} /*namespace aetee*/;

#endif
