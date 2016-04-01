#ifndef HEADER_AETEE_HOF_FILTER_H_INCLUDED
#define HEADER_AETEE_HOF_FILTER_H_INCLUDED
#include <aetee/axioms/flatten.h>
#include <aetee/axioms/identity.h>
#include <aetee/axioms/nothing.h>
#include <aetee/axioms/select.h>
#include <aetee/axioms/tupify.h>
#include <aetee/hof/compose.h>
#include <aetee/hof/curry.h>
#include <aetee/hof/map.h>
#include <aetee/traits/cast.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

template <typename F>
struct filterMapper {

    constexpr filterMapper(F&& fIn) : f{std::forward<F>(fIn)} { }

    template <typename A>
    constexpr auto operator()(A&& a)
    {
        return select(cast<bool>(f(std::forward<A>(a))), tupify(std::forward<A>(a)), tupify());
    }

    template <typename A>
    constexpr auto operator()(A&& a) const
    {
        return select(cast<bool>(f(std::forward<A>(a))), tupify(std::forward<A>(a)), tupify());
    }

private:

    F f;

} /*struct filterMapper*/;

struct filterFunctor {

    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& f) const
    {
        return flatten(map(std::forward<Tup>(tup), filterMapper<F>{std::forward<F>(f)}));
    }

} /*struct filterFunctor*/;

} /*namespace detail*/;

static constexpr auto filter = detail::filterFunctor{};

} /*namespace aetee*/;

#endif
