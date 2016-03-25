#ifndef HEADER_AETEE_AXIOMS_OBJECTS_H_INCLUDED
#define HEADER_AETEE_AXIOMS_OBJECTS_H_INCLUDED
#include <aetee/hof/curry.h>
#include <utility>

namespace aetee {

namespace detail {


struct identityFunctor {

    template <typename T>
    constexpr decltype(auto) operator()(T&& t) const
    {
        return std::forward<T>(t);
    }

    template <typename... T>
    constexpr decltype(auto) operator()(T&&... t) const
    {
        return std::forward_as_tuple(std::forward<T>(t)...);
    }

    template <typename T>
    static constexpr auto of(T&& t)
    {
        return curry(identityFunctor{}, std::forward<T>(t));
    }

} /*struct identityFunctor*/;

} /*namespace detail*/;

static constexpr auto identity = detail::identityFunctor{};

} /*namespace aetee*/;

#endif
