#ifndef HEADER_AETEE_TRAITS_DECLTYPE_H_INCLUDED
#define HEADER_AETEE_TRAITS_DECLTYPE_H_INCLUDED
#include <aetee/type_c.h>
#include <type_traits>

namespace aetee {

namespace detail {

struct decltypeFunctor {

    template <typename T>
    constexpr auto operator()(T&&) const {
        return type_c<std::decay_t<T>>;
    }

    template <typename T>
    constexpr auto operator()(type_t<T>) const
    {
        return type_c<T>;
    }

} /*struct decltypeFunctor*/;

} /*namespace detail*/;

static constexpr auto decltype_ = detail::decltypeFunctor{};

} /*namespace aetee*/;

#endif
