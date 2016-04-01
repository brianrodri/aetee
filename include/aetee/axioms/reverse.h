#ifndef HEADER_AETEE_AXIOMS_REVERSE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_REVERSE_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/traits/length.h>

namespace aetee {

namespace detail {

struct reverseFunctor {

    template <typename Tup>
    constexpr auto operator()(Tup&& tup) const
    {
        return impl(std::forward<Tup>(tup), idx_c_sequence_of<Tup>);
    }

private:

    template <typename Tup, size_t... I>
    static constexpr auto impl(Tup&& tup, idx_sequence_t<I...> idxes)
    {
        return std::make_tuple(std::get<idx_c<sizeof...(I) - I - 1>>(std::forward<Tup>(tup))...);
    }

};

} /*namespace detail*/;

static constexpr auto reverse = detail::reverseFunctor{};

} /*namespace aetee*/;

#endif
