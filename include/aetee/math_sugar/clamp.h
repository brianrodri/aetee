#ifndef HEADER_AETEE_MATHSUGAR_CLAMP_H_INCLUDED
#define HEADER_AETEE_MATHSUGAR_CLAMP_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/axioms/nothing.h>
#include <aetee/axioms/select.h>
#include <aetee/traits/cast.h>
#include <aetee/traits/is_same.h>
#include <type_traits>
#include <utility>

namespace aetee {

namespace detail {

struct clampFunctor {

    template <typename L, typename H, typename C>
    constexpr auto operator()(L&& lo, H&& hi, C&& clampee) const
    {
        auto retval = select(
            (lo < clampee) + (2_c * (clampee < hi))
          , nothing
          , std::forward<H>(hi)
          , std::forward<L>(lo)
          , std::forward<C>(clampee)
            );
        static_assert(!is_same(retval, nothing));
        return retval;
    }

} /*struct clampFunctor*/;

} /*namespace detail*/;

static constexpr auto clamp = detail::clampFunctor{};

} /*namespace aetee*/;

#endif
