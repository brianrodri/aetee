#ifndef HEADER_AETEE_TRAITS_DECLTYPE_H_INCLUDED
#define HEADER_AETEE_TRAITS_DECLTYPE_H_INCLUDED
#include <type_traits>
#include <aetee/type_c.h>

namespace aetee {

namespace detail {

struct decltypeFunctor {
    template <typename T>
    constexpr auto operator()(T&&) const {
        return type_c<std::decay_t<T>>;
    }

    template <typename T>
    constexpr auto operator()(type_constant_t<T>) const
    {
        return type_c<T>;
    }
} /*struct decltypeFunctor*/;

} /*namespace detail*/;

static constexpr auto decltype_ = detail::decltypeFunctor{};

} /*namespace aetee*/;

#endif
