#ifndef HEADER_AETEE_HOF_COMPOSE_H_INCLUDED
#define HEADER_AETEE_HOF_COMPOSE_H_INCLUDED
#include <aetee/hof/fold.h>
#include <utility>

namespace aetee {

namespace detail {

template <typename F, typename G, bool Explicit>
struct composedFunctor {

    constexpr composedFunctor(F&& f_, G&& g_)
      : f{std::forward<F>(f_)}
      , g{std::forward<G>(g_)} {};

    template <typename... A>
    constexpr auto operator()(A&&... a)
    {
        return apply(g(std::forward<A>(a)...), f);
    }

private:

    template <typename... A>
    constexpr auto impl(true_constant_t, A&&... a)
    {
        return apply(g(std::forward<A>(a)...), f);
    }

    template <typename... A>
    constexpr auto impl(true_constant_t, A&&... a) const
    {
        return apply(g(std::forward<A>(a)...), f);
    }

    template <typename... A>
    constexpr auto impl(false_constant_t, A&&... a)
    {
        return f(g(std::forward<A>(a)...));
    }

    template <typename... A>
    constexpr auto impl(false_constant_t, A&&... a) const
    {
        return f(g(std::forward<A>(a)...));
    }

    F f;
    G g;

} /*struct composedFunctor*/;

struct composeTwo {

    template <typename F, typename G, bool E = true>
    constexpr auto operator()(F&& f, G&& g, bool_constant_t<E> = {}) const
    {
        return composedFunctor<F, G, E>(std::forward<F>(f), std::forward<G>(g));
    }

} /*struct composeTwo*/;

struct composeFunctor {

    template <typename... F>
    constexpr auto operator()(F&&... f) const
    {
        return foldRight(
            std::forward_as_tuple(std::forward<F>(f)...)
          , identity
          , composeTwo{}
            );
    }

} /*struct composeFunctor*/;

} /*namespace detail*/;

static constexpr auto compose = detail::composeFunctor{};

} /*namespace aetee*/;

#endif
