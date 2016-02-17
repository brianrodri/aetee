#ifndef HEADER_AETEE_AXIOMS_SELECT_H_INCLUDED
#define HEADER_AETEE_AXIOMS_SELECT_H_INCLUDED
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

struct selectFunctor {
    template <size_t I, typename... A>
    constexpr decltype(auto) operator()(idx_constant_t<I> i, A&&... args) const
    {
        static_assert(i < arity_c<A...>);
        return impl(i, std::forward<A>(args)...);
    }

private:
    template <size_t I, typename H, typename... T>
    static constexpr decltype(auto) impl(idx_constant_t<I>, H&& head, T&&... tail)
    {
        return impl(idx_c<I-1>, std::forward<T>(tail)...);
    }

    template <typename H, typename... T>
    static constexpr decltype(auto) impl(idx_constant_t<0>, H&& head, T&&... tail)
    {
        return std::forward<H>(head);
    }
} /*struct selectFunctor*/;

} /*namespace detail*/;

static constexpr auto select = detail::selectFunctor{};

} /*namespace aetee*/;

#endif
