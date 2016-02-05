#ifndef HEADER_AETEE_AXIOMS_APPLY_H_INCLUDED
#define HEADER_AETEE_AXIOMS_APPLY_H_INCLUDED
#include <type_traits>
#include <utility>

namespace aetee {

namespace detail {

// Forward Declaration
template <typename F> struct applyWrapperFunctor;

//! Used as a passable object that makes wrapped apply functions
struct applyWrapperMakerFunctor {
    template <typename F>
    constexpr auto operator()(F&& f) const
    {
        return applyWrapperFunctor<F>(std::forward<F>(f));
    }
} /*applyWrapperMakerFunctor*/;

//!
struct applyFunctor {
    template <typename Tup, typename F>
    constexpr decltype(auto) operator()(Tup&& tup, F&& f) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return impl(
            std::forward<Tup>(tup)
          , std::forward<F>(f)
          , std::make_index_sequence<N>{}
            );
    }

    static constexpr auto wrap = applyWrapperMakerFunctor{};

private:
    template <typename Tup, typename F, size_t... I>
    constexpr decltype(auto) impl(Tup&& tup, F&& f, std::index_sequence<I...>) const
    {
        return f(std::get<I>(std::forward<F>(f))...);
    }
} /*struct applyFunctor*/;

//!
template <typename F>
struct applyWrapperFunctor {
    applyWrapperFunctor(F&& f) : f{std::forward<F>(f)} {};

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
