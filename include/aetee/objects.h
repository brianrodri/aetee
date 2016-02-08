#ifndef HEADER_AETEE_OBJECTS_STRINGIFY_H_INCLUDED
#define HEADER_AETEE_OBJECTS_STRINGIFY_H_INCLUDED
#include <string>
#include <type_traits>
#include <aetee/type_c.h>

namespace aetee {

namespace detail {

struct tupifyFunctor {
    template <typename... T>
    constexpr auto operator()(T&&... t) const
    {
        return std::make_tuple(std::forward<T>(t)...);
    }
} /*struct tupifyFunctor*/;

struct stringifyFunctor {
    template <typename T>
    constexpr auto operator()(T&& t) const
    {
        return std::to_string(std::forward<T>(t));
    }
} /*struct stringifyFunctor*/;

struct nothingFunctor {
    constexpr auto operator()(...) const
    {
        return nothingFunctor{};
    }
} /*struct nothingFunctor*/;

struct valueFunctor {
    template <typename T>
    constexpr decltype(auto) operator()(T&& t) const
    {
        return std::decay_t<T>::value;
    }
    template <typename T>
    constexpr decltype(auto) operator()(type_constant_t<T>) const
    {
        return std::decay_t<T>::value;
    }
} /*struct valueFunctor*/;

struct justFunctor {
    template <typename T>
    constexpr auto operator()(T&&) const
    {
        return just<T>{std::forward<T>};
    }

private:
    template <typename T>
    struct just {
        constexpr just(T&& t_) : t{std::forward<T>(t_)} {};

        constexpr operator T() const
        {
            return t;
        }

        constexpr T operator()(...) const
        {
            return t;
        }

    private:
        T t;
    } /*struct just*/;
} /*struct justFunctor*/;

} /*namespace detail*/;

static constexpr auto stringify = detail::stringifyFunctor{};
static constexpr auto nothing = detail::nothingFunctor{};
static constexpr auto just = detail::justFunctor{};
static constexpr auto value = detail::valueFunctor{};
static constexpr auto tupify = detail::tupifyFunctor{};

} /*namespace aetee*/;

#endif
