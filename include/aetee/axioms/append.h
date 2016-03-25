#ifndef HEADER_AETEE_AXIOMS_APPEND_H_INCLUDED
#define HEADER_AETEE_AXIOMS_APPEND_H_INCLUDED
#include <aetee/int_c.h>
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct appendFunctor {

    template <typename Tup, typename... X>
    constexpr auto operator()(Tup&& tup, X&&... x) const
    {
        return impl(std::forward<Tup>(tup), idx_sequence_c_of<Tup>, std::forward<X>(x)...);
    }

private:

    template <typename Tup, size_t... I, typename... X>
    constexpr auto impl(Tup&& tup, idx_sequence_t<I...>, X&&... x) const
    {
        return std::make_tuple(std::get<I>(std::forward<Tup>(tup))..., std::forward<X>(x)...);
    }

} /*struct appendFunctor*/;

} /*namespace detail*/;

static constexpr auto append = detail::appendFunctor{};

} /*namespace aetee*/;

#endif
