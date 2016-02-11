#ifndef HEADER_AETEE_AXIOMS_ALIGNOF_H_INCLUDED
#define HEADER_AETEE_AXIOMS_ALIGNOF_H_INCLUDED
#include <aetee/type_c.h>
#include <type_traits>

namespace aetee {

namespace detail {

struct alignOfFunctor {
    template <typename T>
    constexpr auto operator()(type_constant_t<T>) const
    {
        return index_c<alignof(std::decay_t<T>)>;
    }

    template <typename T>
    constexpr auto operator()(T&&) const
    {
        return index_c<alignof(std::decay_t<T>)>;
    }

    template <typename... T>
    constexpr auto operator()(type_sequence_t<T...>) const
    {
        return alignof(std::aligned_union_t<1, char, T...>);
    }

    template <typename H, typename... T>
    constexpr auto operator()(type_constant_t<H>, type_constant_t<T>...) const
    {
        return alignof(std::aligned_union_t<1, H, T...>);
    }
} /*struct alignOfFunctor*/;

} /*namespace detail*/;

static constexpr auto alignof_ = detail::alignOfFunctor{};

} /*namespace aetee*/;

#endif
