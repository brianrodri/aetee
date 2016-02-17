#ifndef HEADER_AETEE_AXIOMS_TRANSFORM_H_INCLUDED
#define HEADER_AETEE_AXIOMS_TRANSFORM_H_INCLUDED
#include <tuple>
#include <utility>
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

struct transformFunctor {
    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& f) const
    {
        return impl(std::forward<Tup>(tup), std::forward<F>(f), idx_sequence_c_of<Tup>);
    }

private:
    template <typename Tup, typename F, size_t... I>
    static constexpr auto impl(Tup&& tup, F&& f, idx_sequence_t<I...>)
    {
        return std::make_tuple(f(std::get<I>(std::forward<Tup>(tup)))...);
    }
} /*struct transformFunctor*/;

} /*namespace detail*/;

static constexpr auto transform = detail::transformFunctor{};

} /*namespace aetee*/;

#endif
