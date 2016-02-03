#ifndef HEADER_AETEE_AXIOMS_COMPOSE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_COMPOSE_H_INCLUDED
#include <aetee/objects.h>
#include <aetee/hof/fold.h>
#include <utility>

namespace aetee {

namespace detail {

struct composeFunctor {
    template <typename F, typename G>
    constexpr auto operator()(F&& f, G&& g) const
    {
        return composition<F, G>{std::forward<F>(f), std::forward<G>(g)};
    }

    template <typename... F>
    constexpr auto operator()(F&&... f) const
    {
        return fold(std::make_tuple(std::forward<F>(f)...), identity, composeFunctor{});
    }

private:
    template <typename F, typename G>
    struct composition {
        template <typename... A>
        constexpr auto operator()(A&&... a) const
        {
            return f(g(std::forward<A>(a)...));
        }

    private:
        F f;
        G g;
    } /*struct composition*/;
} /*struct composeFunctor*/;

} /*namespace detail*/;

static constexpr auto composition = detail::composeFunctor{};

} /*namespace aetee*/;

#endif
