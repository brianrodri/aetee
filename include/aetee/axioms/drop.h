#ifndef HEADER_AETEE_AXIOMS_DROP_H_INCLUDED
#define HEADER_AETEE_AXIOMS_DROP_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/math_sugar/clamp.h>

namespace aetee {

namespace detail {

struct dropFunctor {

    template <typename Tup, size_t N>
    constexpr auto operator()(Tup&& tup, idx_constant_t<N> n) const
    {
        constexpr auto len = clamp(0_c, len_c<Tup>, n);
        return impl(std::forward<Tup>(tup), len, idx_sequence_c_til<len_c<Tup> - len>);
    }

private:

    template <typename Tup, size_t L, size_t... I>
    static constexpr auto impl(Tup&& tup, idx_constant_t<L>, idx_sequence_t<I...>)
    {
        return std::make_tuple(std::get<L + I>(std::forward<Tup>(tup))...);
    }

} /*struct dropFunctor*/;

struct dropBackFunctor {

    template <typename Tup, size_t N>
    constexpr auto operator()(Tup&& tup, idx_constant_t<N> n) const
    {
        constexpr auto len = len_c<Tup> - clamp(0_c, len_c<Tup>, n);
        return impl(std::forward<Tup>(tup), idx_sequence_c_til<len>);
    }

private:

    template <typename Tup, size_t... I>
    static constexpr auto impl(Tup&& tup, idx_sequence_t<I...>)
    {
        return std::make_tuple(std::get<I>(std::forward<Tup>(tup))...);
    }

} /*struct dropBackFunctor*/;

} /*namespace detail*/;

static constexpr auto drop = detail::dropFunctor{};
static constexpr auto& dropFront = drop;
static constexpr auto dropBack = detail::dropBackFunctor{};

} /*namespace aetee*/;

#endif
