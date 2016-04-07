#ifndef HEADER_AETEE_AXIOMS_TAKE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_TAKE_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/math_sugar/clamp.h>

namespace aetee {

namespace detail {

struct takeBackFunctor {

    template <typename Tup, size_t N>
    constexpr auto operator()(Tup&& tup, idx_t<N> n) const
    {
        constexpr size_t l = clamp(0_c, len_c<Tup>, n);
        return impl(std::forward<Tup>(tup), idx_c_sequence_til<l>);
    }

private:

    template <typename Tup, size_t... I>
    static constexpr auto impl(Tup&& tup, idx_c_sequence_t<I...>)
    {
        return std::make_tuple(std::get<len_c<Tup> - idx_c<sizeof...(I)> + idx_c<I>>(std::forward<Tup>(tup))...);
    }

} /*struct takeBackFunctor*/;

struct takeFrontFunctor {

    template <typename Tup, size_t N>
    constexpr auto operator()(Tup&& tup, idx_t<N> n) const
    {
        constexpr size_t l = clamp(0_c, len_c<Tup>, n);
        return impl(std::forward<Tup>(tup), idx_c_sequence_til<l>);
    }

private:

    template <typename Tup, size_t... I>
    static constexpr auto impl(Tup&& tup, idx_c_sequence_t<I...>)
    {
        return std::make_tuple(std::get<I>(std::forward<Tup>(tup))...);
    }

} /*struct takeFrontFunctor*/;

} /*namespace detail*/;

static constexpr auto take = detail::takeFrontFunctor{};
static constexpr auto& takeFront = take;
static constexpr auto takeBack = detail::takeBackFunctor{};

} /*namespace aetee*/;

#endif
