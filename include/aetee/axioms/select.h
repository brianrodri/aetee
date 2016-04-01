#ifndef HEADER_AETEE_AXIOMS_SELECT_H_INCLUDED
#define HEADER_AETEE_AXIOMS_SELECT_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/axioms/value.h>
#include <aetee/traits/cast.h>
#include <utility>

namespace aetee {

namespace detail {

struct selectFunctor {

    template <size_t I, typename... A>
    constexpr decltype(auto) operator()(idx_constant_t<I> i, A&&... args) const
    {
        static_assert(i < arity_c<A...>);
        return impl(i, std::forward<A>(args)...);
    }

    template <bool C, typename A, typename B>
    constexpr decltype(auto) operator()(bool_constant_t<C>, A&& a, B&& b) const
    {
        return impl(idx_c<(C? 0 : 1)>, std::forward<A>(a), std::forward<B>(b));
    }

private:

    template <typename H, typename... T>
    static constexpr decltype(auto) impl(idx_constant_t<0>, H&& head, T&&...)
    {
        return std::forward<H>(head);
    }

    template <size_t I, typename H, typename... T>
    static constexpr decltype(auto) impl(idx_constant_t<I>, H&&, T&&... tail)
    {
        return impl(idx_c<I-1>, std::forward<T>(tail)...);
    }

} /*struct selectFunctor*/;

template <typename P, typename... A>
struct selectMapFunctor {

    constexpr selectMapFunctor(P&& pIn, A&&... aIn)
        : p{std::forward<P>(pIn)}, transformers{std::forward<A>(aIn)...}
    {}

    template <typename... X>
        //requires Predicate<P, X...>
    constexpr decltype(auto) operator()(X&&... x)
    {
        return impl(idx_c_sequence_for<A...>, std::forward<X>(x)...);
    }

    template <typename... X>
        //requires Predicate<P, X>
    constexpr decltype(auto) operator()(X&&... x) const
    {
        return impl(idx_c_sequence_for<A...>, std::forward<X>(x)...);
    }

private:

    template <typename... X, size_t... I>
    constexpr decltype(auto) impl(idx_sequence_t<I...>, X&&... x)
    {
        return selectFunctor{}(
            p(std::forward<X>(x)...)
          , std::get<I>(transformers)...
            )(std::forward<X>(x)...);
    }

    template <typename... X, size_t... I>
    constexpr decltype(auto) impl(idx_sequence_t<I...>, X&&... x) const
    {
        return selectFunctor{}(
            p(std::forward<X>(x)...)
          , std::get<I>(transformers)...
            )(std::forward<X>(x)...);
    }

    P p;
    std::tuple<A...> transformers;

} /*struct selectMapFunctor*/;

struct selectMapMakerFunctor {

    template <typename P, typename... A>
    constexpr auto operator()(P&& p, A&&... a) const
    {
        return selectMapFunctor<P, A...>{std::forward<P>(p), std::forward<A>(a)...};
    }

} /*struct selectMapMakerFunctor*/;

} /*namespace detail*/;

static constexpr auto select = detail::selectFunctor{};
static constexpr auto selectMap = detail::selectMapMakerFunctor{};

} /*namespace aetee*/;

#endif
