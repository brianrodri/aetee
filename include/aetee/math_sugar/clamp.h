#ifndef HEADER_AETEE_MATHSUGAR_CLAMP_H_INCLUDED
#define HEADER_AETEE_MATHSUGAR_CLAMP_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/axioms/nothing.h>
#include <aetee/axioms/select.h>
#include <aetee/traits/cast.h>
#include <utility>

namespace aetee {

namespace detail {

struct clampFunctor {

    template <typename L, typename H, typename C>
    constexpr auto operator()(L&& lo, H&& hi, C&& clampee) const
    {
        return select(
            cast<size_t>(lo < clampee) + (2_c * cast<size_t>(clampee < hi))
          , nothing
          , std::forward<H>(hi)
          , std::forward<L>(lo)
          , std::forward<C>(clampee)
            );
    }

} /*struct clampFunctor*/;

} /*namespace detail*/;

static constexpr auto clamp = detail::clampFunctor{};

} /*namespace aetee*/;

#endif
