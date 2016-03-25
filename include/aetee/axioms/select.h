#ifndef HEADER_AETEE_AXIOMS_SELECT_H_INCLUDED
#define HEADER_AETEE_AXIOMS_SELECT_H_INCLUDED
#include <aetee/int_c.h>
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

} /*namespace detail*/;

static constexpr auto select = detail::selectFunctor{};

} /*namespace aetee*/;

#endif
