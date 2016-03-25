#ifndef HEADER_AETEE_TRAITS_IS_SAME_H_INCLUDED
#define HEADER_AETEE_TRAITS_IS_SAME_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/type_c.h>
#include <type_traits>

namespace aetee {

namespace detail {

struct isSameTypeFunctor {

    template <typename T, typename U>
    constexpr auto operator()(type_constant_t<T>, type_constant_t<U>)
    {
        return bool_c<std::is_same<T, U>::value>;
    }

    template <typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const
    {
        return bool_c<std::is_same<std::decay_t<T>, std::decay_t<U>>::value>;
    }

} /*struct isSameTypeFunctor*/;

} /*namespace detail*/;

static constexpr auto is_same = detail::isSameTypeFunctor{};

} /*namespace aetee*/;

#endif
