#ifndef HEADER_AETEE_AXIOMS_VALUE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_VALUE_H_INCLUDED
#include <type_traits>

namespace aetee {

namespace detail {

struct valueFunctor {
    template <typename T>
    constexpr auto operator()(T&&) const
    {
        return std::decay_t<T>::value;
    }

    template <typename T>
    constexpr auto operator()(type_constant_t<T>) const
    {
        return std::decay_t<T>::value;
    }
} /*struct valueFunctor*/;

} /*namespace detail*/;

static constexpr auto value = detail::valueFunctor{};

} /*namespace aetee*/;

#endif
