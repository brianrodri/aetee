#ifndef HEADER_AETEE_TRAITS_LENGTH_H_INCLUDED
#define HEADER_AETEE_TRAITS_LENGTH_H_INCLUDED
#include <tuple>
#include <aetee/int_c.h>
#include <aetee/type_c.h>

namespace aetee {

namespace detail {

struct lengthFunctor {

    template <typename Tup>
    constexpr auto operator()(type_constant_t<Tup> t) const
    {
        return idx_c<std::tuple_size<Tup>::value>;
    }

    template <typename Tup>
    constexpr auto operator()(Tup&& t) const
    {
        return idx_c<std::tuple_size<std::decay_t<Tup>>::value>;
    }

} /*struct lengthFunctor*/;

} /*namespace detail*/;

static constexpr auto length = detail::lengthFunctor{};

} /*namespace aetee*/;

#endif
