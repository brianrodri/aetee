#ifndef HEADER_AETEE_AXIOMS_TAKE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_TAKE_H_INCLUDED
#include <aetee/axioms/length.h>
#include <aetee/hof/fold.h>
#include <aetee/mathsugar.h>

namespace aetee {

namespace detail {

struct takeBackFunctor {
    template <typename Tup, size_t N>
    constexpr auto operator()(Tup&& tup, idx_constant_t<N> n) const
    {
        constexpr size_t l = clamp(0_c, length(type_c<Tup>), n);
        return impl(std::forward<Tup>(tup), idx_sequence_c_til<l>);
    }

private:
    template <typename Tup, size_t... I>
    static constexpr auto impl(Tup&& tup, idx_sequence_t<I...>)
    {
        return std::make_tuple(std::get<length(type_c<Tup>) - idx_c<sizeof...(I)> + idx_c<I>>(std::forward<Tup>(tup))...);
    }
} /*takeBackFunctor*/;

struct takeFunctor {
    template <typename Tup, size_t N>
    constexpr auto operator()(Tup&& tup, idx_constant_t<N> n) const
    {
        constexpr size_t l = clamp(0_c, length(type_c<Tup>), n);
        return impl(std::forward<Tup>(tup), idx_sequence_c_til<l>);
    }

private:
    template <typename Tup, size_t... I>
    static constexpr auto impl(Tup&& tup, idx_sequence_t<I...>)
    {
        return std::make_tuple(std::get<I>(std::forward<Tup>(tup))...);
    }
} /*takeFunctor*/;

} /*namespace detail*/;

static constexpr auto take = detail::takeFunctor{};
static constexpr auto& takeFront = take;
static constexpr auto takeBack = detail::takeBackFunctor{};

} /*namespace aetee*/;

#endif
