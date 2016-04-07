#ifndef HEADER_AETEE_INCLUDE_TO_C_H_INCLUDED
#define HEADER_AETEE_INCLUDE_TO_C_H_INCLUDED
#include <type_traits>
#include <utility>
#include <aetee/int_c.h>

namespace aetee {

namespace detail {

template<typename T, T V, typename = void> struct toCResolverFunctor;

template<typename T, T V>
struct toCResolverFunctor<T, V, std::void_t<std::is_integral<T>>> {

    constexpr auto operator()() const
    {
        return int_c<T, V>;
    }

} /*struct toCResolverFunctor<T, std::void_t<std::is_integral<T>>>*/; 

struct toCFunctor {

    template <typename T>
    constexpr auto operator()(T&& val) const
    {
        return toCResolverFunctor<T, val>();
    }

} /*struct toCFunctor*/; 

} /*namespace detail*/; 

static constexpr auto to_c = detail::toCFunctor{};

} /*namespace aetee*/; 

#endif
