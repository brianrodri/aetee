#ifndef HEADER_AETEE_AXIOMS_FLATTEN_H_INCLUDED
#define HEADER_AETEE_AXIOMS_FLATTEN_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/axioms/concat.h>
#include <aetee/axioms/select.h>
#include <aetee/axioms/tupify.h>
#include <aetee/hof/apply.h>
#include <aetee/hof/fold.h>
#include <aetee/hof/map.h>
#include <aetee/traits/is_tuple.h>

namespace aetee {

namespace detail {

struct flattenRecursivelyFunctor {

    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return apply(std::forward<T>(t), select(is_tuple(type_c<T>), *this, tupify));
    }

    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return apply(
            map(std::forward_as_tuple(std::forward<T>(t)...), *this)
          , concat
            );
    }

} /*struct flattenRecursivelyFunctor*/;

static constexpr auto recursiveFlatten = flattenRecursivelyFunctor{};

struct flattenFunctor {

    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return apply(std::forward<T>(t), concat);
    }

    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return concat(std::forward<T>(t)...);
    }

    static constexpr auto& recursive = recursiveFlatten;

} /*struct flattenFunctor*/;

//constexpr auto flattenFunctor::recursive = flattenRecursivelyFunctor{};

} /*namespace detail*/;

static constexpr auto flatten = detail::flattenFunctor{};

} /*namespace aetee*/;

#endif
