#ifndef HEADER_AETEE_MATH_SUGAR_H_INCLUDED
#define HEADER_AETEE_MATH_SUGAR_H_INCLUDED
#include <aetee/aetee.h>
#include <aetee/objects.h>
#include <aetee/axioms/select.h>
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
        return std::min({ std::forward<T>(t)... });
    }

    template <typename... T>
    constexpr auto operator()(type_constant_t<T>...) const
    {
        return std::min({ T::value... });
    }
} /*struct minFunctor*/;

struct maxFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return std::max({ std::forward<T>(t)... });
    }

    template <typename... T>
    constexpr auto operator()(type_constant_t<T>...) const
    {
        return std::max({ T::value... });
    }
} /*struct maxFunctor*/;

struct clampFunctor {
    template <typename T, T L, typename U, U H, typename V, V C>
    constexpr auto operator()(integer_constant_t<T, L> lo, integer_constant_t<U, H> hi, integer_constant_t<V, C> clampee) const
    {
        return aetee::select(index_c<((C < H) << 1) | (L < C)>, 0_c, hi, lo, clampee);
    }
} /*struct clampFunctor*/;

} /*namespace detail*/;

static constexpr auto less_ = detail::lessFunctor{};
static constexpr auto greater_ = detail::greaterFunctor{};
static constexpr auto sum = detail::sumFunctor{};
static constexpr auto product = detail::productFunctor{};
static constexpr auto min_ = detail::minFunctor{};
static constexpr auto max_ = detail::maxFunctor{};
static constexpr auto clamp = detail::clampFunctor{};

} /*namespace aetee*/;

#endif
