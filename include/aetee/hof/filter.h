#ifndef HEADER_AETEE_HOF_FILTER_H_INCLUDED
#define HEADER_AETEE_HOF_FILTER_H_INCLUDED
#include <aetee/hof/fold.h>
#include <aetee/hof/map.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

template <typename F>
struct transformingFunctor {

    transformingFunctor(F&& f_) : pred{std::forward<F>(f_)}
    {
    }

    template <typename X>
    constexpr auto operator()(X&& x)
    {
        return impl(pred(std::forward<X>(x)), std::forward<X>(x));
    }

    template <typename X>
    constexpr auto operator()(X&& x) const
    {
        return impl(pred(std::forward<X>(x)), std::forward<X>(x));
    }

private:

    template <typename X>
    constexpr auto impl(true_constant_t, X&& x) const
    {
        return std::make_tuple(std::forward<X>(x));
    }

    template <typename X>
    constexpr auto impl(false_constant_t, X&& x) const
    {
        return std::make_tuple();
    }

    F pred;

} /*struct transformingFunctor*/;

struct filterFunctor {

    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& f) const
    {
        return fold(
            map(std::forward<Tup>(tup), transformingFunctor<F>{std::forward<F>(f)})
          , std::make_tuple()
          , concat
            );
    }

} /*struct filterFunctor*/;

} /*namespace detail*/;

static constexpr auto filter = detail::filterFunctor{};

} /*namespace aetee*/;

#endif
