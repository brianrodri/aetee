#ifndef HEADER_AETEE_TRAITS_ALIGNOF_H_INCLUDED
#define HEADER_AETEE_TRAITS_ALIGNOF_H_INCLUDED
#include <aetee/type_c.h>
#include <algorithm>
#include <type_traits>

namespace aetee {

namespace detail {

struct alignOfFunctor {

    template <typename... T>
    constexpr auto operator()(type_t<T>...) const
    {
        return idx_c<std::max({size_t{1}, alignof(T)...})>;
    }

    template <typename... T>
    constexpr auto operator()(type_c_sequence_t<T...>) const
    {
        return idx_c<std::max({size_t{1}, alignof(T)...})>;
    }

} /*struct alignOfFunctor*/;

} /*namespace detail*/;

static constexpr auto alignof_ = detail::alignOfFunctor{};

} /*namespace aetee*/;

#endif
