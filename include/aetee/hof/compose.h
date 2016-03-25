#ifndef HEADER_AETEE_HOF_COMPOSE_H_INCLUDED
#define HEADER_AETEE_HOF_COMPOSE_H_INCLUDED
#include <aetee/hof/fold.h>
#include <utility>

namespace aetee {

namespace detail {

template <typename F, typename G>
struct composedFunctor {

    constexpr composedFunctor(F&& f_, G&& g_)
      : f{std::forward<F>(f_)}
      , g{std::forward<G>(g_)} {};

    template <typename... A>
    constexpr auto operator()(A&&... a)
    {
        return apply(g(std::forward<A>(a)...), f);
    }

    template <typename... A>
    constexpr auto operator()(A&&... a) const
    {
        return apply(g(std::forward<A>(a)...), f);
    }

private:

    F f;
    G g;

} /*struct composedFunctor*/;

struct composeTwo {

    template <typename F, typename G>
    constexpr auto operator()(F&& f, G&& g) const
    {
        return composedFunctor<F, G>(std::forward<F>(f), std::forward<G>(g));
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
