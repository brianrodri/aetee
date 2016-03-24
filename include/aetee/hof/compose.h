#ifndef HEADER_AETEE_HOF_COMPOSE_H_INCLUDED
#define HEADER_AETEE_HOF_COMPOSE_H_INCLUDED
#include <utility>

namespace aetee {

namespace detail {

template <typename F, typename G>
struct compositionFunctor {
    constexpr compositionFunctor(F&& f_, G&& g_) : f{std::forward<F>(f_)}, g{std::forward<G>(g_)} {};

    template <typename... A>
    constexpr auto operator()(A&&... a)
    {
        return f(g(std::forward<A>(a)...));
    }

    template <typename... A>
    constexpr auto operator()(A&&... a) const
    {
        return f(g(std::forward<A>(a)...));
    }

private:
    F f;
    G g;
} /*struct compositionFunctor*/;

struct composeFunctor {
    template <typename F, typename G>
    constexpr auto operator()(F&& f, G&& g) const
    {
        return compositionFunctor<F, G>{std::forward<F>(f), std::forward<G>(g)};
    }
} /*struct composeFunctor*/;

} /*namespace detail*/;

static constexpr auto compose = detail::composeFunctor{};

} /*namespace aetee*/;

#endif
