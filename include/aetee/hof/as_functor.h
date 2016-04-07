#ifndef HEADER_AETEE_HOF_AS_FUNCTOR_H_INCLUDED
#define HEADER_AETEE_HOF_AS_FUNCTOR_H_INCLUDED
#include <aetee/type_c.h>
#include <aetee/axioms/to_c.h>

namespace aetee {

namespace detail {

template <template<typename...> class Predicate>
struct asFunctorFunctor {

    template <typename... Args>
    constexpr decltype(auto) operator()(type_c_sequence_t<Args...>) const
    {
        return int_c<decltype(Predicate<Args...>::value), Predicate<Args...>::value>;
    }

    template <typename... Args>
    constexpr decltype(auto) operator()(type_c_sequence_t<Args>...) const
    {
        return int_c<decltype(Predicate<Args...>::value), Predicate<Args...>::value>;
    }

} /*struct asFunctorFunctor*/;

} /*namespace detail*/;

template<template<typename...> class Predicate>
static constexpr auto as_functor = detail::asFunctorFunctor<Predicate>{};

} /*namespace aetee*/; 

#endif
