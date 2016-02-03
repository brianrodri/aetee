#ifndef HEADER_AETEE_MATH_SUGAR_H_INCLUDED
#define HEADER_AETEE_MATH_SUGAR_H_INCLUDED
#include <aetee/aetee.h>
#include <functional>
#include <utility>

namespace aetee {

namespace detail {

struct lessFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return bool_c<(a < b)>;
    }
} /*struct lessFunctor*/;

struct greaterFunctor {
    template <typename A, typename B>
    constexpr auto operator()(A&& a, B&& b) const
    {
        return bool_c<(a > b)>;
    }
} /*struct greaterFunctor*/;

struct sumFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        (std::forward<T>(t) + ...);
    }
} /*struct sumFunctor*/;

struct productFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        (std::forward<T>(t) * ...);
    }
} /*struct productFunctor*/;

struct minFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return fold(std::make_tuple(std::forward<T>(t)...), max_index_c, lessFunctor{});
    }
} /*struct minFunctor*/;

struct maxFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return fold(std::make_tuple(std::forward<T>(t)...), greaterFunctor{});
    }
} /*struct maxFunctor*/;

} /*namespace detail*/;

static constexpr auto less_ = detail::lessFunctor{};
static constexpr auto greater_ = detail::greaterFunctor{};
static constexpr auto sum = detail::sumFunctor{};
static constexpr auto product = detail::productFunctor{};
static constexpr auto min_ = detail::minFunctor{};
static constexpr auto max_ = detail::maxFunctor{};

} /*namespace aetee*/;

#endif
