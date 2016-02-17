#ifndef HEADER_AETEE_MATH_SUGAR_H_INCLUDED
#define HEADER_AETEE_MATH_SUGAR_H_INCLUDED
#include <aetee/int_c.h>
#include <algorithm>
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
        return (std::forward<T>(t) + ...);
    }
} /*struct sumFunctor*/;

struct productFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return (std::forward<T>(t) * ...);
    }
} /*struct productFunctor*/;

struct minFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return std::min({ (std::decay_t<T>::value)... });
    }
} /*struct minFunctor*/;

struct maxFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return std::min({ (std::decay_t<T>::value)... });
    }
} /*struct maxFunctor*/;

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
    static constexpr decltype(auto) impl(true_constant_t, true_constant_t, L, H, C&& c)
    {
        return std::forward<C>(c);
    }

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
} /*struct clampFunctor*/;

template <typename F>
class fixedFunctor {
    constexpr fixedFunctor(F&& f) : f{std::forward<F>(f)} {};

    template <typename... A>
    constexpr decltype(auto) operator()(A&&... a)
    {
        return f(std::forward<A>(a)...);
    }

    template <typename... A>
    constexpr decltype(auto) operator()(A&&... a) const
    {
        return f(std::forward<A>(a)...);
    }

private:
    F f;
} /*class fixedFunctor*/;


} /*namespace detail*/;

auto fix = [](auto f) {
    return [=](auto&&... a) { return f(f, a...); };
};

static constexpr auto less_ = detail::lessFunctor{};
static constexpr auto greater_ = detail::greaterFunctor{};
static constexpr auto sum = detail::sumFunctor{};
static constexpr auto product = detail::productFunctor{};
static constexpr auto min_ = detail::minFunctor{};
static constexpr auto max_ = detail::maxFunctor{};
static constexpr auto clamp = detail::clampFunctor{};

} /*namespace aetee*/;

#endif
