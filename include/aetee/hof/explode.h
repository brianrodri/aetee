#ifndef HEADER_AETEE_HOF_EXPLODE_H_INCLUDED
#define HEADER_AETEE_HOF_EXPLODE_H_INCLUDED
#include <tuple>
#include <aetee/int_c.h>
#include <aetee/axioms/length.h>

namespace aetee {

namespace detail {

struct explodeFunctor {
    template <typename Tup, typename... F>
    constexpr auto operator()(Tup&& tup, F&&... f) const
    {
        static_assert(length(tup) < arity_c<F...>);
        return impl(
            index_sequence_c_for<F...>
          , std::forward<Tup>(tup)
          , std::forward<F>(f)...
            );
    }

private:
    template <size_t... I, typename Tup, typename... F>
    static constexpr auto impl(index_sequence_t<I...>, Tup&& tup, F&&... f)
    {
        return std::make_tuple(f(std::get<I>(std::forward<Tup>(tup)))...);
    }
} /*struct explodeFunctor*/;

} /*namespace detail*/;

static constexpr auto explode = detail::explodeFunctor{};

} /*namespace aetee*/;

#endif
