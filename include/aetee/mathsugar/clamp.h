#ifndef HEADER_AETEE_MATHSUGAR_CLAMP_H_INCLUDED
#define HEADER_AETEE_MATHSUGAR_CLAMP_H_INCLUDED
#include <utility>
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

struct clampFunctor {
    template <typename L, typename H, typename C>
    constexpr decltype(auto) operator()(L lo, H hi, C clampee) const
    {
        return impl((lo < clampee), (clampee < hi), lo, hi, clampee);
    }

    template <typename L, typename H, typename C, typename F>
    constexpr decltype(auto) operator()(L lo, H hi, C clampee, F&& relation)
    {
        return impl(relation(lo, clampee), relation(clampee, hi), lo, hi, clampee);
    }

private:
    template <typename L, typename H, typename C>
    static constexpr decltype(auto) impl(false_constant_t, true_constant_t, L&& l, H, C)
    {
        return std::forward<L>(l);
    }

    template <typename L, typename H, typename C>
    static constexpr decltype(auto) impl(true_constant_t, false_constant_t, L, H&& h, C)
    {
        return std::forward<H>(h);
    }

    template <typename L, typename H, typename C>
    static constexpr decltype(auto) impl(true_constant_t, true_constant_t, L, H, C&& c)
    {
        return std::forward<C>(c);
    }

} /*struct clampFunctor*/;

} /*namespace detail*/;

static constexpr auto clamp = detail::clampFunctor{};

} /*namespace aetee*/;

#endif
