#ifndef HEADER_AETEE_AXIOMS_REPLICATE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_REPLICATE_H_INCLUDED
#include <tuple>
#include <utility>
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

//! replicate -- returns a tuple filled w/ the given repititons of the val
struct replicateFunctor {
    template <typename T, typename N>
    constexpr auto operator()(T&& val, N&& n) const
    {
        return impl(std::forward<T>(val), idx_sequence_c_til<n>);
    }

private:
    template <typename T, size_t... I>
    static constexpr auto impl(T&& val, idx_sequence_t<I...>)
    {
        return std::make_tuple((I, T{val})...);
    }
} /*struct replicateFunctor*/;

} /*namespace detail*/;

static constexpr auto replicate = detail::replicateFunctor{};

} /*namespace aetee*/;

#endif
