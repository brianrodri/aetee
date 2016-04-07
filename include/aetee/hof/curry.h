#ifndef HEADER_AETEE_HOF_CURRY_H_INCLUDED
#define HEADER_AETEE_HOF_CURRY_H_INCLUDED
#include <aetee/int_c.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

template <class F, bool ToFront, typename... A>
struct curried {

    constexpr curried(F&& f_, A&&... a_) : f{std::forward<F>(f_)}, a{std::forward<A>(a_)...} {};

    template <typename... B>
    constexpr decltype(auto) operator()(B&&... b)
    {
        return impl(bool_c<ToFront>, idx_c_sequence_for<A...>, std::forward<B>(b)...);
    }

    template <typename... B>
    constexpr decltype(auto) operator()(B&&... b) const
    {
        return impl(bool_c<ToFront>, idx_c_sequence_for<A...>, std::forward<B>(b)...);
    }

private:

    F f;
    std::tuple<A&&...> a;

    template <size_t... I, typename... B>
    constexpr decltype(auto) impl(true_t, idx_c_sequence_t<I...>, B&&... b)
    {
        return f(std::get<I>(a)..., std::forward<B>(b)...);
    }

    template <size_t... I, typename... B>
    constexpr decltype(auto) impl(true_t, idx_c_sequence_t<I...>, B&&... b) const
    {
        return f(std::get<I>(a)..., std::forward<B>(b)...);
    }

    template <size_t... I, typename... B>
    constexpr decltype(auto) impl(false_t, idx_c_sequence_t<I...>, B&&... b)
    {
        return f(std::forward<B>(b)..., std::get<I>(a)...);
    }

    template <size_t... I, typename... B>
    constexpr decltype(auto) impl(false_t, idx_c_sequence_t<I...>, B&&... b) const
    {
        return f(std::forward<B>(b)..., std::get<I>(a)...);
    }

} /*struct curried*/;

struct curryFunctor {

    template <typename F, typename... A>
    constexpr decltype(auto) operator()(F&& f, A&&... args) const
    {
        return curried<F, true, A...>{std::forward<F>(f), std::forward<A>(args)...};
    }

} /*struct curryFunctor*/;

struct curryBackFunctor {

    template <typename F, typename... A>
    constexpr decltype(auto) operator()(F&& f, A&&... args) const
    {
        return curried<F, false, A...>{std::forward<F>(f), std::forward<A>(args)...};
    }

} /*struct curryBackFunctor*/;

} /*namespace detail*/;

static constexpr auto curry = detail::curryFunctor{};
static constexpr auto curryBack = detail::curryBackFunctor{};

} /*namespace aetee*/;

#endif
