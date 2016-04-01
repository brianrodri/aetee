#ifndef HEADER_AETEE_AXIOMS_SLICE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_SLICE_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/axioms/value.h>
#include <aetee/hof/filter.h>
#include <aetee/hof/map.h>
#include <aetee/hof/curry.h>
#include <aetee/hof/compose.h>
#include <aetee/math_sugar/op_alias.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

template <typename Step>
struct stepFilterFunctor {

    template <typename T>
    constexpr auto operator()(T val) const
    {
        return 0_c == (val % Step{});
    }

} /*struct stepFilterFunctor*/;

struct sliceFunctor {

    template <typename Tup, typename Lo, typename Hi = decltype(len_c<Tup>), typename Step = decltype(1_c)>
    constexpr auto operator()(Tup&& tup, Lo lo, Hi hi = {}, Step step = {}) const
    {
        return impl(
            std::forward<Tup>(tup)
          , map(
                filter(idx_c_sequence_til<value(hi) - value(lo)>, stepFilterFunctor<Step>{})
              , curry(plus, lo)
                ) // map
            );
    }

private:

    template <typename Tup, size_t... I>
    static constexpr auto impl(Tup&& tup, idx_sequence_t<I...>)
    {
        return std::make_tuple(std::get<I>(std::forward<Tup>(tup))...);
    }

} /*struct sliceFunctor*/;

} /*namespace detail*/;

static constexpr auto slice = detail::sliceFunctor{};

} /*namespace aetee*/;

#endif
