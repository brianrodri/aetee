#ifndef HEADER_AETEE_AXIOMS_DROP_H_INCLUDED
#define HEADER_AETEE_AXIOMS_DROP_H_INCLUDED
#include <aetee/axioms/length.h>
#include <aetee/hof/fold.h>
#include <aetee/mathsugar.h>

namespace aetee {

namespace detail {

struct dropBackFunctor {
    template <typename Tup, size_t N>
    constexpr auto operator()(Tup&& tup, index_constant_t<N> n) const
    {
        constexpr size_t l = clamp(0_c, length(type_c<Tup>), n);
        return impl(std::forward<Tup>(tup), std::make_index_sequence<length(type_c<Tup>) - l>{});
    }

private:
    template <typename Tup, size_t... I>
    static constexpr auto impl(Tup&& tup, std::index_sequence<I...>)
    {
        return std::make_tuple(std::get<I>(std::forward<Tup>(tup))...);
    }
} /*struct dropBackFunctor*/;

struct dropFunctor {
    template <typename Tup, size_t N>
    constexpr auto operator()(Tup&& tup, index_constant_t<N> n) const
    {
        constexpr size_t l = clamp(0_c, length(type_c<Tup>), n);
        return impl(std::forward<Tup>(tup), index_c<l>, std::make_index_sequence<length(type_c<Tup>) - l>{});
    }

private:
    template <typename Tup, size_t L, size_t... I>
    static constexpr auto impl(Tup&& tup, index_constant_t<L> l, std::index_sequence<I...>)
    {
        return std::make_tuple(std::get<L + I>(std::forward<Tup>(tup))...);
    }
} /*struct dropFunctor*/;

} /*namespace detail*/;

static constexpr auto drop = detail::dropFunctor{};
static constexpr auto& dropFront = drop;
static constexpr auto dropBack = detail::dropBackFunctor{};

} /*namespace aetee*/;

#endif
