#ifndef HEADER_AETEE_TRAITS_IS_TUPLE_H_INCLUDED
#define HEADER_AETEE_TRAITS_IS_TUPLE_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/type_c.h>
#include <type_traits>

namespace aetee {

namespace detail {

template <typename T, typename = void>
struct isTuple : false_constant_t {};

template <typename T>
struct isTuple<T, std::void_t<typename std::tuple_size<T>::type>> : true_constant_t {};

struct isTupleFunctor {

    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return isTuple<std::decay_t<T>>{};
    }

    template <typename T>
    constexpr auto operator()(type_constant_t<T>) const
    {
        return isTuple<std::decay_t<T>>{};
    }

} /*struct isTupleFunctor*/;

} /*namespace detail*/;

static constexpr auto is_tuple = detail::isTupleFunctor{};

} /*namespace aetee*/;

#endif
