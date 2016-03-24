#ifndef HEADER_AETEE_HOF_APPLY_H_INCLUDED
#define HEADER_AETEE_HOF_APPLY_H_INCLUDED
#include <type_traits>
#include <utility>
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

// Forward Declaration
template <typename F> struct applyWrapperFunctor;

//! Used as a passable object that makes wrapped apply functions
struct applyWrapperMakerFunctor {
    template <typename F>
    constexpr decltype(auto) operator()(F&& f) const
    {
        return applyWrapperFunctor<F>{std::forward<F>(f)};
    }
} /*applyWrapperMakerFunctor*/;

//!
struct applyFunctor {
    template <typename Tup, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, F&& f) const
    {
        return impl(std::forward<Tup>(tup), std::forward<F>(f), idx_sequence_c_of<Tup>);
    }

    static constexpr auto wrapper = applyWrapperMakerFunctor{};

private:
    template <typename Tup, typename F, size_t... I>
    static constexpr decltype(auto) impl(Tup&& tup, F&& f, idx_sequence_t<I...>)
    {
        return f(std::get<I>(std::forward<Tup>(tup))...);
    }
} /*struct applyFunctor*/;

//!
template <typename F>
struct applyWrapperFunctor {
    constexpr applyWrapperFunctor(F&& f_) : f{std::forward<F>(f_)} {};

    template <typename Tup>
    constexpr decltype(auto) operator()(Tup&& tup)
    {
        return applyFunctor{}(std::forward<Tup>(tup), f);
    }

    template <typename Tup>
    constexpr decltype(auto) operator()(Tup&& tup) const
    {
        return applyFunctor{}(std::forward<Tup>(tup), f);
    }

private:
    F f;
} /*arrayWrapperFunctor*/;

} /*namespace detail*/;

static constexpr auto apply = detail::applyFunctor{};

} /*namespace aetee*/;

#endif
