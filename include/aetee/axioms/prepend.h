#ifndef HEADER_AETEE_AXIOMS_PREPEND_H_INCLUDED
#define HEADER_AETEE_AXIOMS_PREPEND_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct prependFunctor {

    template <typename Tup, typename... X>
    constexpr auto operator()(Tup&& tup, X&&... x) const
    {
        return impl(std::forward<Tup>(tup), idx_sequence_c_of<Tup>, std::forward<X>(x)...);
    }

private:

    template <typename Tup, size_t... I, typename... X>
    static constexpr auto impl(Tup&& tup, idx_sequence_t<I...>, X&&... x)
    {
        return std::make_tuple(std::forward<X>(x)..., std::get<I>(std::forward<Tup>(tup))...);
    }

} /*struct prependFunctor*/;

} /*namespace detail*/;

static constexpr auto prepend = detail::prependFunctor{};

} /*namespace aetee*/;

#endif
