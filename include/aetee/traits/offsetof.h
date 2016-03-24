#ifndef HEADER_AETEE_TRAITS_OFFSETOF_H_INCLUDED
#define HEADER_AETEE_TRAITS_OFFSETOF_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/type_c.h>
#include <array>

namespace aetee {

namespace detail {

struct offsetOfFunctor {
    template <typename... T>
    constexpr auto operator()(type_sequence_t<T...> ts) const
    {
        return idx_c<impl(ts, arity_c<T...>)>;
    }

    template <typename... T, size_t I>
    constexpr auto operator()(type_sequence_t<T...> ts, idx_constant_t<I> i) const
    {
        return idx_c<impl(ts, i)>;
    }

private:
    template <typename... T, size_t I>
    static constexpr size_t impl(type_sequence_t<T...>, idx_constant_t<I>)
    {
        constexpr std::array<size_t, sizeof...(T)> szs{sizeof(T)...};
        constexpr std::array<size_t, sizeof...(T) +1> als{alignof(T)..., 1};
        size_t result{0};
        for (size_t i{1}; i <= I; ++i) {
            result = ((result + szs[i-1] + als[i] - 1) / als[i]) * als[i];
        }
        return result;
    }
} /*struct offsetOfFunctor*/;

} /*namespace detail*/;

static constexpr auto offsetof_ = detail::tupifyFunctor{};

} /*namespace aetee*/;

#endif

