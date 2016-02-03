#ifndef HEADER_AETEE_AXIOMS_TRANSFORM_H_INCLUDED
#define HEADER_AETEE_AXIOMS_TRANSFORM_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct transformFunctor {
    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& f) const
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
    constexpr auto impl(Tup&& tup, F&& f, std::index_sequence<I...>) const
    {
        return std::make_tuple(f(std::get<I>(std::forward<Tup>(tup)))...);
    }
} /*struct transformFunctor*/;

} /*namespace detail*/;

static constexpr auto transform = detail::transformFunctor{};

} /*namespace aetee*/;

#endif
