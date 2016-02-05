#ifndef HEADER_AETEE_AXIOMS_REVERSE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_REVERSE_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/axioms/length.h>

namespace aetee {

namespace detail {

struct reverseFunctor {
    template <typename Tup>
    constexpr auto operator()(Tup&& tup) const
    {
        return impl(std::forward<Tup>(tup), index_sequence_c<length(type_c<Tup>)>);
    }

private:
    template <typename Tup, size_t... I>
    constexpr auto impl(Tup&& tup, index_sequence_t<I...>) const
    {
        return std::make_tuple(std::get<length(type_c<Tup>) - I - 1>(std::forward<Tup>(tup))...);
    }
};

} /*namespace detail*/;

static constexpr auto reverse = detail::reverseFunctor{};

} /*namespace aetee*/;

#endif
