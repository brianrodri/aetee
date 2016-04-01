#ifndef HEADER_AETEE_HOF_MAP_H_INCLUDED
#define HEADER_AETEE_HOF_MAP_H_INCLUDED
#include <aetee/int_c.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct mapFunctor {

    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& f) const
    {
        return impl(std::forward<Tup>(tup), std::forward<F>(f), idx_c_sequence_of<Tup>);
    }

private:

    template <typename Tup, typename F, size_t... I>
    static constexpr auto impl(Tup&& tup, F&& f, idx_sequence_t<I...>)
    {
        return std::make_tuple(f(std::get<I>(std::forward<Tup>(tup)))...);
    }

} /*struct mapFunctor*/;

} /*namespace detail*/;

static constexpr auto map = detail::mapFunctor{};

} /*namespace aetee*/;

#endif
