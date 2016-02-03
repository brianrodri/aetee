#ifndef HEADER_AETEE_AXIOMS_APPLY_H_INCLUDED
#define HEADER_AETEE_AXIOMS_APPLY_H_INCLUDED
#include <type_traits>
#include <utility>

namespace aetee {

namespace detail {

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

private:
    template <typename Tup, typename F, size_t... I>
    constexpr decltype(auto) impl(Tup&& tup, F&& f, std::index_sequence<I...>) const
    {
        return f(std::get<I>(std::forward<F>(f))...);
    }
} /*struct applyFunctor*/;

} /*namespace detail*/;

static constexpr auto apply = detail::applyFunctor{};

} /*namespace aetee*/;

#endif
