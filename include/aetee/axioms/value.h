#ifndef HEADER_AETEE_AXIOMS_VALUE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_VALUE_H_INCLUDED
#include <type_traits>

namespace aetee {

namespace detail {

template <typename T, typename = void>
struct valueResolvingFunctor {

    constexpr decltype(auto) operator()(T&& t) const
    {
        return std::forward<T>(t);
    }

} /*struct valueResolvingFunctor*/;

template <typename T>
struct valueResolvingFunctor<type_constant_t<T>> {

    constexpr decltype(auto) operator()(type_constant_t<T>) const
    {
        return T::value;
    }

} /*struct valueResolvingFunctor*/;

template <typename T>
struct valueResolvingFunctor<T, std::void_t<decltype(std::decay_t<T>::value)>> {

    constexpr decltype(auto) operator()(T&& t) const
    {
        return std::decay_t<T>::value;
    }

} /*struct valueResolvingFunctor*/;

struct valueFunctor {

    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return valueResolvingFunctor<T>{}(std::forward<T>(t));
    }

} /*struct valueFunctor*/;

} /*namespace detail*/;

static constexpr auto value = detail::valueFunctor{};

} /*namespace aetee*/;

#endif
