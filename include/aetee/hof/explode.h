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
        return impl(
            idx_sequence_c_for<type_c<Tup>>
          , std::forward<Tup>(tup)
          , std::forward<F>(f)...
            );
    }

private:
    template <size_t... I, typename Tup, typename... F>
    static constexpr auto impl(idx_sequence_t<I...>, Tup&& tup, F&&... f)
    {
        return tupify(f(std::get<I>(std::forward<Tup>(tup)))...);
    }
} /*struct explodeFunctor*/;

} /*namespace detail*/;

static constexpr auto explode = detail::explodeFunctor{};

} /*namespace aetee*/;

#endif
