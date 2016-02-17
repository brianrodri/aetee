#ifndef HEADER_AETEE_AXIOMS_LENGTH_H_INCLUDED
#define HEADER_AETEE_AXIOMS_LENGTH_H_INCLUDED
#include <aetee/type_c.h>

namespace aetee {

namespace detail {

struct lengthFunctor {
    template <typename Tup>
    constexpr auto operator()(Tup&& t) const
    {
        return idx_c<std::tuple_size<std::decay_t<Tup>>::value>;
    }

    template <typename Tup>
    constexpr auto operator()(type_constant_t<Tup>) const
    {
        return idx_c<std::tuple_size<std::decay_t<Tup>>::value>;
    }
};

}; // namespace detail

static constexpr auto length = detail::lengthFunctor{};

}; // namespace aetee

#endif
